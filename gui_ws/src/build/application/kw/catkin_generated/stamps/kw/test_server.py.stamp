#! /usr/bin/env python3
import rospy

import actionlib
from kw_msgs.msg import CarrotAction, CarrotGoal, CarrotResult

def do_test(goal):
	print("server called!")
	rate = rospy.Rate(10)
	for i in range(0, 51):
		if server.is_preempt_requested():
			result = CarrotResult()
			result.total=3
			server.set_preempted(result, 'Timer preempted')
			return
		rate.sleep()
	result = CarrotResult()
	result.total=3
	server.set_succeeded(result)
	return

rospy.init_node('action_server_test')
server = actionlib.SimpleActionServer('/kw/carrot', CarrotAction, do_test, False)
server.start()
rospy.spin()