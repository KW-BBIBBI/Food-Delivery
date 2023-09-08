#! /usr/bin/env python3

import rospy

from kw_msgs.srv import Button, ButtonResponse

def print_button(request):
	print(request.btn)
	return ButtonResponse(True)

rospy.init_node('service_server_test')

service = rospy.Service('/kw/button', Button, print_button)

rospy.spin()