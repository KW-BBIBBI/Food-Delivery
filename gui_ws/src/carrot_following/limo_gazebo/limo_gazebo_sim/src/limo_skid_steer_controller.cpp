#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

#include <string>

#include "limo_gazebo/limo_skid_steer.hpp"

using namespace wescore;




int main(int argc, char **argv) {
  // setup ROS node
  ros::init(argc, argv, "limo_odom");
  ros::NodeHandle node(""), private_node("~");

  // fetch parameters
  std::string robot_namespace;
  private_node.param<std::string>("robot_namespace", robot_namespace,
                                  std::string("limo_default"));

  ROS_INFO("Namespace: %s", robot_namespace.c_str());

  LimoSkidSteer skid_steer_controller(&node, robot_namespace);
  skid_steer_controller.SetupSubscription();

  ros::Rate rate(30);

  while(ros::ok())
  {
    skid_steer_controller.PublishOdometryToROS();
    // ROS_WARN("Namespace: %lf", skid_steer_controller.getyaw());
    ros::spinOnce();
    rate.sleep();
  }

  

  return 0;
}