#include <ros/ros.h>
#include <ros/package.h>
#include <fstream>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <string>
#include <iostream>
#include <string_view>
using namespace std;

class SaveWP
{
    public:
        SaveWP(const string &fp)
        :outFile(fp, ios_base::trunc)
        {
            way_sub_=nh_.subscribe("/amcl_pose", 10, &SaveWP::waypointCB, this);
        }

    private:
        ros::NodeHandle nh_;
        ros::Subscriber way_sub_;
        ofstream outFile;

        void waypointCB(const geometry_msgs::PoseWithCovarianceStampedConstPtr & wp)
        {
            outFile << wp->pose.pose.position.x
                    << ","
                    << wp->pose.pose.position.y
                    << ","
                    << wp->pose.pose.orientation.x
                    << ","
                    << wp->pose.pose.orientation.y
                    << ","
                    << wp->pose.pose.orientation.z
                    << ","
                    << wp->pose.pose.orientation.w
                    << endl;
        }
};

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "save_waypoints"); //node initialize
    
    string pkg_path_ = ros::package::getPath("multiwaypoints"); // multiwaypoints라는 패키지의 path get
            
    string file_path_ = pkg_path_ + "/data/waypoints.csv";
    SaveWP swp(file_path_);

    ros::spin();

    return 0;
}