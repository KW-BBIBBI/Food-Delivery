import os
import rospy
import rospkg

from qt_gui.plugin import Plugin
from python_qt_binding import loadUi
from python_qt_binding.QtWidgets import QWidget
from std_msgs.msg import String
from kw_msgs.srv import Button

class KWPlugin(Plugin):

    def __init__(self, context):
        super(KWPlugin, self).__init__(context)
        self.setObjectName('KWPlugin')

        from argparse import ArgumentParser
        parser = ArgumentParser()
        parser.add_argument("-q", "--quiet", action="store_true",
                      dest="quiet",
                      help="Put plugin in silent mode")
        args, unknowns = parser.parse_known_args(context.argv())
        if not args.quiet:
            pass

        self._widget = QWidget()
        ui_file = os.path.join(rospkg.RosPack().get_path('kw_gui'), 'resource', 'KWPlugin.ui')
        loadUi(ui_file, self._widget)

        self._widget.setObjectName('KWPluginUi')

        ## follow button seting
        self._widget.follow_path_1_Button.clicked.connect(self.followPathOneButtonCB)
        self._widget.follow_path_2_Button.clicked.connect(self.followPathTwoButtonCB)
        self._widget.follow_path_3_Button.clicked.connect(self.followPathThreeButtonCB)

        ## save button seting
        self._widget.save_path_1_Button.clicked.connect(self.savePathOneButtonCB)
        self._widget.save_path_2_Button.clicked.connect(self.savePathTwoButtonCB)
        self._widget.save_path_3_Button.clicked.connect(self.savePathThreeButtonCB)

        ## display button setting
        self._widget.SLAM_display_Button.clicked.connect(self.SLAM_displayButtonCB)
        self._widget.Navigation_display_Button.clicked.connect(self.Navigation_displayButtonCB)

        ## stop button setting
        self._widget.stopButton.clicked.connect(self.stopButtonCB)

        ## subscriber setting
        rospy.Subscriber("/kw/status", String, self.labelCB)

        # rospy.wait_for_service('/kw/button')
        self.button_click = rospy.ServiceProxy('/kw/button', Button)

        ## service setting

        if context.serial_number() > 1:
            self._widget.setWindowTitle(self._widget.windowTitle() + (' (%d)' % context.serial_number()))

        context.add_widget(self._widget)
        
    def SLAM_displayButtonCB(self):
        os.system("gnome-terminal -e 'roslaunch kw_gui SLAM_display.launch'")

    def Navigation_displayButtonCB(self):
        os.system("gnome-terminal -e 'roslaunch kw_gui navigation_display.launch'")

    ########### Label callback function ########################
    def labelCB(self, data):
        self._widget.status_Label.setText(data.data)

    ########### Button Callback for follow path ################

    def followPathOneButtonCB(self):
        push_button = "follow_path_1"
        self.button_click(push_button)
    
    def followPathTwoButtonCB(self):
        push_button = "follow_path_2"
        self.button_click(push_button)
    
    def followPathThreeButtonCB(self):
        push_button = "follow_path_3"
        self.button_click(push_button)

    ########### Button Callback for save path ################
    
    def savePathOneButtonCB(self):
        push_button = "save_path_1"
        self.button_click(push_button)
    
    def savePathTwoButtonCB(self):
        push_button = "save_path_2"
        self.button_click(push_button)
    
    def savePathThreeButtonCB(self):
        push_button = "save_path_3"
        self.button_click(push_button)
    
    ########### Button Callback for Stop ######################
    def stopButtonCB(self):
        push_button = "stop"
        self.button_click(push_button)
    





