/*ros basics*/
#include "ros/ros.h"
#include <ros/package.h>

/*to get the data of map to base link*/
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/TransformStamped.h"

/*cpp basics*/
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

/*for publishing goal*/
#include "move_base_msgs/MoveBaseAction.h"
#include "move_base_msgs/MoveBaseGoal.h"
#include "actionlib/client/simple_action_client.h"
#include "geometry_msgs/Pose.h"

/*for the  path*/
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"

using namespace std;

class WaypointFollowing
{
    public:
        WaypointFollowing(const string &file_path)
        :tfListener(tfBuffer),
        mbclient("move_base", true)
        {
            ifstream file(file_path);
            std::string line;
            while(std::getline(file, line))
            {
                std::istringstream iss(line);
                std::string value;
                std::vector<double> data_values;

                while(std::getline(iss, value,','))
                {
                    double data_value = std::stod(value);
                    data_values.push_back(data_value);
                }

                geometry_msgs::PoseStamped new_goal;
                new_goal.pose.orientation.w = data_values[5];
                new_goal.pose.orientation.z = data_values[4];
                new_goal.pose.orientation.y = data_values[3];
                new_goal.pose.orientation.x = data_values[2];
                new_goal.pose.position.y = data_values[1];
                new_goal.pose.position.x = data_values[0];
                waypoints_.push_back(new_goal);
            }
            file.close();

            path_pub_ = nh_.advertise<nav_msgs::Path>("waypoints", 10);
            point_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("target", 10);

        }

        void getPosition()
        {
            try
            {
                transformStamped = tfBuffer.lookupTransform("map", "base_link", ros::Time::now(), ros::Duration(3.0));
            }
            catch(tf2::TransformException &ex)
            {
                ROS_WARN("%s",ex.what());
                // ros::Duration(0.1).sleep();
            }
            cout<<transformStamped<<endl;
        }

        void publishGoal()
        {
            path_.header.frame_id="map";
            path_.header.stamp = ros::Time::now();
            path_.poses = waypoints_;
            path_pub_.publish(path_);

            carrot.target_pose.pose=setGoal();
            carrot.target_pose.header.frame_id = "map";
            carrot.target_pose.header.stamp = ros::Time::now();
            
            carrot_point.header.frame_id = "map";
            carrot_point.header.stamp = ros::Time::now();
            carrot_point.pose = carrot.target_pose.pose;

            point_pub_.publish(carrot_point);

            
            mbclient.sendGoal(carrot);


        }

    private:
        ros::NodeHandle nh_;
        
        //to get the current position of map and base_link
        tf2_ros::Buffer tfBuffer;
        tf2_ros::TransformListener tfListener;
        geometry_msgs::TransformStamped transformStamped;

        /*for the path*/
        vector<geometry_msgs::PoseStamped> waypoints_;
        ros::Publisher path_pub_;
        nav_msgs::Path path_;

        /*for the move_base*/
        actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> mbclient;
        move_base_msgs::MoveBaseGoal carrot;
        geometry_msgs::PoseStamped carrot_point;
        ros::Publisher point_pub_;

        int findNearestPoint()
        {
            double distance = numeric_limits<double>::max();
            int index =0;
            for(int i=0; i<waypoints_.size(); i++)
            {
                double temp = sqrt(pow(waypoints_[i].pose.position.x - transformStamped.transform.translation.x,2)+
                pow(waypoints_[i].pose.position.y - transformStamped.transform.translation.y,2));

                if(temp < distance)
                {
                    distance=temp;
                    index = i;
                }
            }
            return index;
        }

        geometry_msgs::Pose setGoal()
        {
            geometry_msgs::Pose answer;
            int near_index=findNearestPoint();
            int carrot_index = near_index + 5;
            if((carrot_index) > waypoints_.size())
            {
                carrot_index = waypoints_.size();
            }

            // cout<<carrot_index<<endl;
            
            answer.position.x = waypoints_[carrot_index].pose.position.x;
            answer.position.y = waypoints_[carrot_index].pose.position.y;
            answer.position.z = waypoints_[carrot_index].pose.position.z;
            answer.orientation.w = waypoints_[carrot_index].pose.orientation.w;
            answer.orientation.x = waypoints_[carrot_index].pose.orientation.x;
            answer.orientation.y = waypoints_[carrot_index].pose.orientation.y;
            answer.orientation.z = waypoints_[carrot_index].pose.orientation.z;
            return answer;
        }
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "follow_waypoints");


    string pkg_path_ = ros::package::getPath("multiwaypoints");        
    string file_path_ = pkg_path_ + "/data/waypoints.csv";

    WaypointFollowing wp(file_path_);

    ros::Rate rate(20);

    while(ros::ok())
    {
        wp.getPosition();
        wp.publishGoal();
        rate.sleep();
    }
    return 0;
}