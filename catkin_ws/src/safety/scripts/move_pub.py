#!/usr/bin/env python
import rospy

class ROSNode:
    def __init__(self):
        rospy.init_node("name_node")
        rospy.loginfo("Starting ROSNode as name_node.")

        


if __name__ == "__main__":
    name_node = ROSNode()
    rospy.spin()