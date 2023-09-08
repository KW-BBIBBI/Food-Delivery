/*
 * limo_skid_steer.cpp
 *
 * Created on: Mar 25, 2020 22:54
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "limo_gazebo/limo_skid_steer.hpp"

#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>

#include <tf/transform_broadcaster.h>

namespace wescore {
LimoSkidSteer::LimoSkidSteer(ros::NodeHandle *nh, std::string robot_name)
    : nh_(nh), robot_name_(robot_name) {
  motor_fr_topic_ = robot_name_ + "/limo_motor_fr_controller/command";
  motor_fl_topic_ = robot_name_ + "/limo_motor_fl_controller/command";
  motor_rl_topic_ = robot_name_ + "/limo_motor_rl_controller/command";
  motor_rr_topic_ = robot_name_ + "/limo_motor_rr_controller/command";
  cmd_topic_ = robot_name_ + "/cmd_vel";
  if(!nh->getParam("/limo_skid_steer_controller/pub_tf", pub_tf))
    pub_tf=true;
}

void LimoSkidSteer::SetupSubscription() {
  // command subscriber
  cmd_sub_ = nh_->subscribe<geometry_msgs::Twist>(
      cmd_topic_, 5, &LimoSkidSteer::TwistCmdCallback, this);

  // motor command publisher
  motor_fr_pub_ = nh_->advertise<std_msgs::Float64>(motor_fr_topic_, 50);
  motor_fl_pub_ = nh_->advertise<std_msgs::Float64>(motor_fl_topic_, 50);
  motor_rl_pub_ = nh_->advertise<std_msgs::Float64>(motor_rl_topic_, 50);
  motor_rr_pub_ = nh_->advertise<std_msgs::Float64>(motor_rr_topic_, 50);

  odom_publisher_ = nh_->advertise<nav_msgs::Odometry>("/odom", 50);
  // ros::param::param<bool>("pub_tf", pub_tf, true);
  
}

void LimoSkidSteer::TwistCmdCallback(
    const geometry_msgs::Twist::ConstPtr &msg) {
  std_msgs::Float64 motor_cmd[4];

  

  driving_vel = msg->linear.x;
  steering_vel = msg->angular.z;

  // PublishOdometryToROS(driving_vel, steering_vel, dt);

  double left_side_velocity =
      (driving_vel - steering_vel * LIMO_WHEELBASE) / LIMO_WHEEL_RADIUS;
  double right_side_velocity =
      (driving_vel + steering_vel * LIMO_WHEELBASE) / LIMO_WHEEL_RADIUS;

  motor_cmd[0].data = right_side_velocity;
  motor_cmd[1].data = -left_side_velocity;
  motor_cmd[2].data = -left_side_velocity;
  motor_cmd[3].data = right_side_velocity;

  motor_fr_pub_.publish(motor_cmd[0]);
  motor_fl_pub_.publish(motor_cmd[1]);
  motor_rl_pub_.publish(motor_cmd[2]);
  motor_rr_pub_.publish(motor_cmd[3]);

  
}

void LimoSkidSteer::PublishOdometryToROS()
{
  current_time_ = ros::Time::now();
  static bool init_run = true;
  if (init_run)
  {                   
    last_time_ = current_time_;
    init_run = false;
    return;
  }

  dt = (current_time_ - last_time_).toSec();
  linear_speed_ = driving_vel;
  angular_speed_ = steering_vel;


  double d_theta = angular_speed_ * dt;
  theta_ += d_theta;

  ROS_DEBUG("yaw: %lf", theta_);
  double d_x = linear_speed_ * std::cos(theta_) * dt;
  double d_y = linear_speed_ * std::sin(theta_) * dt;
  

  position_x_ += d_x;
  position_y_ += d_y;
  

  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta_);

  geometry_msgs::TransformStamped tf_msg;
  tf_msg.header.stamp = current_time_;
  tf_msg.header.frame_id = "odom";
  tf_msg.child_frame_id = "base_link";

  tf_msg.transform.translation.x = position_x_;
  tf_msg.transform.translation.y = position_y_;
  tf_msg.transform.translation.z = 0.0;
  tf_msg.transform.rotation = odom_quat;

  if(pub_tf)
    tf_broadcaster_.sendTransform(tf_msg);

  nav_msgs::Odometry odom_msg;
    odom_msg.header.stamp = current_time_;
    odom_msg.header.frame_id = "odom";
    odom_msg.child_frame_id = "base_link";

    odom_msg.pose.pose.position.x = position_x_;
    odom_msg.pose.pose.position.y = position_y_;
    odom_msg.pose.pose.position.z = 0.0;
    odom_msg.pose.pose.orientation = odom_quat;

    odom_msg.twist.twist.linear.x = linear_speed_;
    odom_msg.twist.twist.linear.y = 0.0;
    odom_msg.twist.twist.angular.z = angular_speed_;

    odom_publisher_.publish(odom_msg);

    last_time_ = current_time_;
}

double LimoSkidSteer::getyaw()
{
  return theta_;  
}
}  // namespace wescore