#! /usr/bin/env python3

import rospy

from enum import Enum

from std_msgs.msg import String
from kw_msgs.srv import Button, ButtonResponse
from kw_msgs.msg import CarrotAction, CarrotGoal, CarrotResult
import actionlib

class RobotMode(Enum):
    Default = 0
    SavingOne = 1
    SavingTwo = 2
    SavingThree =3
    FollowingOne = 4
    FollowingTwo = 5
    FollowingThree = 6
    Stop = 7
    Patrol =8

class PatrolMode(Enum):
    Default = 0
    PathOne = 1
    PathTwo = 2
    PathThree = 3
    End = 4

class Manager:
    def __init__(self):
        self.robot_status = RobotMode(0)
        self.request_status = RobotMode(0)
        self.sequence_status = PatrolMode(0)
        self.gui_service = rospy.Service('/kw/button', Button, self.setStatus)
        self.gui_pub = rospy.Publisher("/kw/status", String, queue_size=10)
        self.carrot_client = actionlib.SimpleActionClient('/kw/carrot', CarrotAction)
        self.carrot_client.wait_for_server()
        self.action_goal = CarrotGoal()
        

    
    def setStatus(self, request):
        if request.btn == "follow_path_1":
            self.request_status = RobotMode.FollowingOne
        elif request.btn == "follow_path_2":
            self.request_status = RobotMode.FollowingTwo
        elif request.btn == "follow_path_3":
            self.request_status = RobotMode.FollowingThree
        elif request.btn == "save_path_1":
            self.request_status = RobotMode.SavingOne
        elif request.btn == "save_path_2":
            self.request_status = RobotMode.SavingTwo
        elif request.btn == "save_path_3":
            self.request_status = RobotMode.SavingThree
        elif request.btn == "patrol":
            self.request_status = RobotMode.Patrol
        else:
            self.request_status = RobotMode.Stop
        return ButtonResponse(True)
        

    def publishStatus(self):
        msg = String()
        if self.robot_status == RobotMode.SavingOne:
            msg.data = "Save path one"
        elif self.robot_status == RobotMode.SavingTwo:
            msg.data = "Save path two"
        elif self.robot_status == RobotMode.SavingThree:
            msg.data = "Save path three"
        elif self.robot_status == RobotMode.FollowingOne:
            msg.data = "Follow path one"
        elif self.robot_status == RobotMode.FollowingTwo:
            msg.data = "Follow path two"
        elif self.robot_status == RobotMode.FollowingThree:
            msg.data = "Follow path three"
        elif self.robot_status == RobotMode.Patrol:
            msg.data = "Patrolling"
        else:
            msg.data = "Waiting"
        
        self.gui_pub.publish(msg)
    
    def setMotion(self):
        if self.robot_status == RobotMode.Default:
            if self.request_status == RobotMode.Stop or self.request_status == RobotMode.Default:
                pass
            elif self.request_status == RobotMode.SavingOne or self.request_status == RobotMode.SavingTwo or self.request_status == RobotMode.SavingThree:
                self.save()
            elif self.request_status == RobotMode.FollowingOne or self.request_status == RobotMode.FollowingTwo or self.request_status == RobotMode.FollowingThree:
                self.follow()
            elif self.request_status == RobotMode.Patrol:
                self.patrol()
        elif self.robot_status == RobotMode.Patrol:
            if self.request_status == RobotMode.Stop:
                self.stop()
            else:
                self.patrol()
        else:
            if self.request_status == RobotMode.Stop:
                self.stop()
            else:
                pass
        self.request_status = RobotMode.Default

            # else:
    def patrol(self):
        if str(self.carrot_client.get_state()) != '1':
            self.action_goal.func = 1
            if self.sequence_status == PatrolMode.Default:
                self.robot_status = RobotMode.Patrol
                self.sequence_status = PatrolMode.PathOne
                self.action_goal.path =1
                self.carrot_client.send_goal(self.action_goal)
            elif self.sequence_status == PatrolMode.PathOne:
                self.robot_status = RobotMode.Patrol
                self.sequence_status = PatrolMode.PathTwo
                self.action_goal.path = 2
                self.carrot_client.send_goal(self.action_goal)
            elif self.sequence_status == PatrolMode.PathTwo:
                self.robot_status = RobotMode.Patrol
                self.sequence_status = PatrolMode.PathThree
                self.action_goal.path = 3
                self.carrot_client.send_goal(self.action_goal)
            elif self.sequence_status == PatrolMode.PathThree:
                self.sequence_status = PatrolMode.End
                self.robot_status = RobotMode.Patrol
            else:
                self.sequence_status = PatrolMode.Default
                self.robot_status = RobotMode.Default
        else:
            pass

            
            
                

    def save(self):
        self.action_goal.func = 0
        if self.request_status == RobotMode.SavingOne:
            self.action_goal.path =1
            self.robot_status = RobotMode.SavingOne
        elif self.request_status == RobotMode.SavingTwo:
            self.action_goal.path =2
            self.robot_status = RobotMode.SavingTwo
        else:
            self.action_goal.path=3
            self.robot_status = RobotMode.SavingThree
        
        self.carrot_client.send_goal(self.action_goal)
        # self.carrot_client.wait_for_result()
        
        
    def follow(self):
        self.action_goal.func = 1
        if self.request_status == RobotMode.FollowingOne:
            self.action_goal.path =1
            self.robot_status = RobotMode.FollowingOne
        elif self.request_status == RobotMode.FollowingTwo:
            self.action_goal.path =2
            self.robot_status = RobotMode.FollowingTwo
        else:
            self.action_goal.path=3
            self.robot_status = RobotMode.FollowingThree
        
        self.carrot_client.send_goal(self.action_goal)

    def stop(self):
        self.carrot_client.cancel_all_goals()
        if self.robot_status == RobotMode.Patrol:
            self.sequence_status = PatrolMode.End

    
    def getActionStatus(self):
        if str(self.carrot_client.get_state()) == '1': #str(self.carrot_client.get_state()) == 'ACTIVE': ## 3은 나중에 처리해야 할 것 같음 요기는 action이 돌아가고 있을 때임
            pass
        else:
            if self.robot_status==RobotMode.Patrol:
                if self.sequence_status == PatrolMode.End:
                    self.robot_status=RobotMode.Default
                    self.sequence_status = RobotMode.Default
                else:
                    pass
            else:
                self.robot_status=RobotMode.Default
        
        # print(str(self.carrot_client.get_state()))
                
    
def main():
    try:
        rospy.init_node('manager')
        robo = Manager()

        rate = rospy.Rate(10)
        while not rospy.is_shutdown():
            robo.getActionStatus()
            robo.publishStatus()
            robo.setMotion()
            rate.sleep()

    except rospy.ROSInterruptException:
        return
    except KeyboardInterrupt:
        return

if __name__ == '__main__':
    main()