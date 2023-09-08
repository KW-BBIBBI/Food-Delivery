/*
 * limo_skid_steer.hpp
 *
 * Created on: Mar 25, 2020 22:52
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef LIMO_SKID_STEER_HPP
#define LIMO_SKID_STEER_HPP

#include <geometry_msgs/Twist.h>
#include <ros/ros.h>

#include <nav_msgs/Odometry.h>
#include <tf2_ros/transform_broadcaster.h>

#include <ros/console.h>

#include <string>


namespace wescore {
class LimoSkidSteer {
 public:
  LimoSkidSteer(ros::NodeHandle *nh, std::string robot_name = "");

  void SetupSubscription();
  void PublishOdometryToROS();
  double getyaw();

 private:
  std::string robot_name_;
  std::string motor_fr_topic_;
  std::string motor_fl_topic_;
  std::string motor_rl_topic_;
  std::string motor_rr_topic_;
  std::string cmd_topic_;

  const double LIMO_WHEELBASE = 0.27;
  const double LIMO_WHEEL_RADIUS = 0.04512;

  // const double LIMO_WHEELBASE = 0.172;
  // const double LIMO_WHEEL_RADIUS = 0.09;

  ros::NodeHandle *nh_;

  ros::Publisher motor_fr_pub_;
  ros::Publisher motor_fl_pub_;
  ros::Publisher motor_rl_pub_;
  ros::Publisher motor_rr_pub_;

  ros::Subscriber cmd_sub_;

  double linear_speed_ = 0.0;
  double angular_speed_ = 0.0;
  double position_x_ = 0.0;
  double position_y_ = 0.0;
  double theta_ = 0.0;

  double driving_vel=0;
  double steering_vel=0;
  double dt;

  ros::Time last_time_;
  ros::Time current_time_;
  tf2_ros::TransformBroadcaster tf_broadcaster_;
  void TwistCmdCallback(const geometry_msgs::Twist::ConstPtr &msg);

  bool pub_tf = true;

  ros::Publisher odom_publisher_;
  
};
}  // namespace wescore

#endif /* SCOUT_SKID_STEER_HPP */
