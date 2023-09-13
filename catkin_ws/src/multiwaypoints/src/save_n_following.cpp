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
#include <iostream>

/*for publishing goal*/
#include "move_base_msgs/MoveBaseAction.h"
#include "move_base_msgs/MoveBaseGoal.h"
#include "actionlib/client/simple_action_client.h"
#include "geometry_msgs/Pose.h"

/*for the  path*/
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"

/*for the current position*/
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <string_view>

/*for the action*/
#include <actionlib/server/simple_action_server.h>
#include <kw_msgs/CarrotAction.h>
#include <kw_msgs/CarrotGoal.h>
#include <kw_msgs/CarrotFeedback.h>
#include <kw_msgs/CarrotResult.h>

using namespace std;

class SaveFollow
{
public:
    SaveFollow(const string &file)
    : as_(nh_, "/kw/carrot", boost::bind(&SaveFollow::executeCB, this,_1), false),
    tfListener(tfBuffer),
    mbclient("move_base", true)
    {
        default_dir_ = file;
        as_.start();

        path_pub_ = nh_.advertise<nav_msgs::Path>("waypoints", 10);
        point_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("target", 10);
    }

private:
    //Ros node handle 만들어줌
    ros::NodeHandle nh_;

    //waypoint 저장되는 파일 디렉토리 위치
    string default_dir_;

    /// action client setting
    actionlib::SimpleActionServer<kw_msgs::CarrotAction> as_;

    //to get the current position of map and base_link
    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener;
    geometry_msgs::TransformStamped transformStamped;

    //for the path
    vector<geometry_msgs::PoseStamped> waypoints_;
    ros::Publisher path_pub_;
    nav_msgs::Path path_;

    /*for the move_base*/
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> mbclient;
    move_base_msgs::MoveBaseGoal carrot;
    geometry_msgs::PoseStamped carrot_point;
    ros::Publisher point_pub_;

    void executeCB(const kw_msgs::CarrotGoalConstPtr &goal)
    {
        string filename, fullname;
        if(goal->func == 0) // saving waypoint
        {
            if(goal->path == 1)
                filename = "waypoint_one.csv";
            else if(goal->path == 2)
                filename = "waypoint_two.csv";
            else
                filename = "waypoint_three.csv";
            
            fullname = default_dir_ + filename;

            ofstream outFile(fullname, ios_base::trunc);
            kw_msgs::CarrotFeedback cf;
            cf.current=0;
            cf.remaining=0;

            geometry_msgs::TransformStamped old_transformStamped;

            while(!as_.isPreemptRequested())
            {
                try
                {
                    transformStamped = tfBuffer.lookupTransform("map", "base_link", ros::Time::now(), ros::Duration(3.0));

                    if(sqrt(pow(old_transformStamped.transform.translation.x - transformStamped.transform.translation.x, 2)
                    +pow(old_transformStamped.transform.translation.y - transformStamped.transform.translation.y, 2))>0.1)
                    {
                        outFile << transformStamped.transform.translation.x
                            << ","
                            << transformStamped.transform.translation.y
                            << ","
                            << transformStamped.transform.rotation.x
                            << ","
                            << transformStamped.transform.rotation.y
                            << ","
                            << transformStamped.transform.rotation.z
                            << ","
                            << transformStamped.transform.rotation.w
                            << endl;
                        cf.current++;
                        old_transformStamped = transformStamped;
                    }
                    as_.publishFeedback(cf);
                }
                catch(tf2::TransformException &ex)
                {
                    ROS_WARN("%s",ex.what());
                }
            }

            kw_msgs::CarrotResult cr;
            cr.total = cf.current;

            outFile.close();
            as_.setPreempted(cr);
        }
        else // loading waypoint
        {
            //clearing old waypoints which was saved
            waypoints_.clear();

            //distinguishing path
            if(goal->path == 1)
                filename = "waypoint_one.csv";
            else if(goal->path == 2)
                filename = "waypoint_two.csv";
            else
                filename = "waypoint_three.csv";
            
            fullname = default_dir_ + filename;

            //read file and update to path
            ifstream file(fullname);
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

            ros::Rate r(1);
            while(!as_.isPreemptRequested() && !goalReached())
            {
                getPosition();
                publishGoal();
                r.sleep();
            }

            kw_msgs::CarrotResult cr;
            cr.total = waypoints_.size()-1;

            if(as_.isPreemptRequested())
            {
                as_.setPreempted(cr);
                return;
            }

            as_.setSucceeded(cr);

        }
    }

    bool goalReached()
    {
        bool flag = false;

        double distance = sqrt(pow((waypoints_[waypoints_.size()-2].pose.position.x - transformStamped.transform.translation.x), 2)
                        +pow((waypoints_[waypoints_.size()-2].pose.position.y - transformStamped.transform.translation.y), 2));

        if (distance < 0.1)
        {
            flag = true;
        }
        return flag;
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
        }
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

    geometry_msgs::Pose setGoal()
    {
        geometry_msgs::Pose answer;
        int near_index=findNearestPoint();
        int carrot_index = near_index + 5;
        if((carrot_index) >= waypoints_.size()-1)
        {
            carrot_index = waypoints_.size()-1;
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

};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "save_n_following");

    string pkg_path_ = ros::package::getPath("multiwaypoints");
            
    string file_path_ = pkg_path_ + "/data/";
    SaveFollow sf(file_path_);

    ros::spin();

    return 0;
}