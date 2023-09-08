#! /usr/bin/env python3

import rospy
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal


if __name__  == '__main__':
    rospy.init_node('move_base_client')
    r=rospy.Rate(1) 

    client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
    client.wait_for_server()

    goal =MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    
    waypoint1=MoveBaseGoal().target_pose.pose
    waypoint1.position.x = 0.010657849596359622
    waypoint1.position.y = -0.006651972332909363
    waypoint1.position.z = 0
    waypoint1.orientation.x =0
    waypoint1.orientation.y =0
    waypoint1.orientation.z =0.0017871812402151968
    waypoint1.orientation.w =0.999998402990332

    waypoint2=MoveBaseGoal().target_pose.pose
    waypoint2.position.x = -1.6210173196500213
    waypoint2.position.y = -3.2794229028262336
    waypoint2.position.z = 0
    waypoint2.orientation.x =0
    waypoint2.orientation.y =0
    waypoint2.orientation.z =0.28469856583907704
    waypoint2.orientation.w =0.9586170907141041
    
    waypoint3=MoveBaseGoal().target_pose.pose
    waypoint3.position.x = 5.473832417208267
    waypoint3.position.y = -6.789341210914372
    waypoint3.position.z = 0
    waypoint3.orientation.x =0
    waypoint3.orientation.y =0
    waypoint3.orientation.z =0.9951386017136706
    waypoint3.orientation.w =0.09848433062858489

    waypoint_list = [waypoint1, waypoint2, waypoint3]
    iteration =0

    try:
        while not rospy.is_shutdown():
            iteration+=1
            iteration = iteration % 3
            goal.target_pose.header.stamp = rospy.Time.now()
            goal.target_pose.pose = waypoint_list[iteration]
            client.send_goal(goal)
            client.wait_for_result()
            rospy.sleep(1)
    except rospy.ROSInitException:
        rospy.loginfo("Navigation test finished")
        
