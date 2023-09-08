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

/*for obstacle*/
#include <obstacle_detector/Obstacles.h>

#define SAFE 0 // 안전
#define DANGER 1 // 위험
#define SAFE_DIST 10.0 // 안전 거리


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

            obs_subs = nh_.subscribe<obstacle_detector::Obstacles>("/obstacles",1000,&WaypointFollowing::obstaclesCB, this);

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
            if (obs_flag) // 장애물 없는 경우 (안전)
            {
                path_.header.frame_id="map";
                path_.header.stamp = ros::Time::now();
                path_.poses = waypoints_;
                path_pub_.publish(path_);

                carrot.target_pose.pose=setGoal();
                prev_carrot.target_pose.pose=carrot.target_pose.pose;

                carrot.target_pose.header.frame_id = "map";
                carrot.target_pose.header.stamp = ros::Time::now();
            
                carrot_point.header.frame_id = "map";
                carrot_point.header.stamp = ros::Time::now();
                carrot_point.pose = carrot.target_pose.pose;

                point_pub_.publish(carrot_point);
            }
            else
            {
                path_.header.frame_id="map";
                path_.header.stamp = ros::Time::now();
                path_.poses = waypoints_;
                path_pub_.publish(path_);

                carrot.target_pose.pose=prev_carrot.target_pose.pose;
                carrot.target_pose.header.frame_id = "map";
                carrot.target_pose.header.stamp = ros::Time::now();
            
                carrot_point.header.frame_id = "map";
                carrot_point.header.stamp = ros::Time::now();
                carrot_point.pose = carrot.target_pose.pose;

                point_pub_.publish(carrot_point);
            }
        }


        void obstaclesCB(const obstacle_detector::Obstacles::ConstPtr& msg)
        {
            _circles = msg->circles;
            _segments = msg->segments;

            int obstacles_num = _circles.size() + _segments.size(); // 장애물의 개수 (circle + segment)

            if(obstacles_num) // 장애물 있는 경우
            {
                if(obstacle_dist()) obs_flag = SAFE; // 장애물이 있지만 안전한 거리
                else obs_flag = DANGER; // 위험
            }
            else obs_flag = SAFE; // 장애물이 없는 경우
        }

    private:
        bool obs_flag=false;

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
        move_base_msgs::MoveBaseGoal prev_carrot;
        geometry_msgs::PoseStamped carrot_point;
        ros::Publisher point_pub_;

        /*for obstacle*/
        ros::Subscriber obs_subs;
        vector<obstacle_detector::SegmentObstacle> _segments;
        vector<obstacle_detector::CircleObstacle> _circles;
        
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
            if((carrot_index) > waypoints_.size() - 1)
            {
                carrot_index = waypoints_.size();
            }
            
            answer.position.x = waypoints_[carrot_index].pose.position.x;
            answer.position.y = waypoints_[carrot_index].pose.position.y;
            answer.position.z = waypoints_[carrot_index].pose.position.z;
            answer.orientation.w = waypoints_[carrot_index].pose.orientation.w;
            answer.orientation.x = waypoints_[carrot_index].pose.orientation.x;
            answer.orientation.y = waypoints_[carrot_index].pose.orientation.y;
            answer.orientation.z = waypoints_[carrot_index].pose.orientation.z;

            return answer;
        }

        geometry_msgs::Pose setGoal_Post()
        {
            geometry_msgs::Pose answer;
            int near_index=findNearestPoint();
            int carrot_index = near_index + 5;
            if((carrot_index) > waypoints_.size() - 1)
            {
                carrot_index = waypoints_.size();
            }

            answer.position.x = waypoints_[carrot_index].pose.position.x;
            answer.position.y = waypoints_[carrot_index].pose.position.y;
            answer.position.z = waypoints_[carrot_index].pose.position.z;
            answer.orientation.w = waypoints_[carrot_index].pose.orientation.w;
            answer.orientation.x = waypoints_[carrot_index].pose.orientation.x;
            answer.orientation.y = waypoints_[carrot_index].pose.orientation.y;
            answer.orientation.z = waypoints_[carrot_index].pose.orientation.z;
            return answer;
        }

        bool obstacle_dist()
        {
            for(int i=0; i<_circles.size(); i++)
            {
                //로봇과 원 중심까지 거리
                double center_to_robot = sqrt(pow(_circles[i].center.x - transformStamped.transform.translation.x,2) +
                pow(_circles[i].center.y - transformStamped.transform.translation.y,2));
                
                // 원의 중심과 로봇의 거리 > 안전 거리 + 원의 반지름인 경우 (위험)
                if(center_to_robot - _circles[i].radius < SAFE_DIST) return DANGER;
            }

            for(int i=0; i<_segments.size(); i++)
            {
                geometry_msgs::Point seg_point;

                // segment 하나의 길이
                double seg_len = sqrt(pow(_segments[i].first_point.x - _segments[i].last_point.x, 2) + pow(_segments[i].first_point.y - _segments[i].last_point.y, 2));

                // segment의 길이만큼 등분한 것의 좌표 계산
                for(int k=0; k< seg_len; k++)
                {
                    // 내분된 좌표
                    seg_point.x = (k * _segments[i].first_point.x + (seg_len - k) * _segments[i].last_point.x) / seg_len;
                    seg_point.y = (k * _segments[i].first_point.y + (seg_len - k) * _segments[i].last_point.y) / seg_len;

                    // seg의 내분된 좌표와 로봇까지 거리 < 안전 거리 (위험)
                    if(sqrt(pow(seg_point.x - transformStamped.transform.translation.x,2) + pow(seg_point.y - transformStamped.transform.translation.y,2)) < SAFE_DIST) return DANGER;
                }
            }
            return SAFE; // 장애물이 있지만 안전거리 보다 먼 경우 (안전)
        }
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "follow_waypoints");


    string pkg_path_ = ros::package::getPath("multiwaypoints");        
    string file_path_ = pkg_path_ + "/data/waypoints.csv";

    WaypointFollowing wp(file_path_);

    ros::Rate rate(1);

    while(ros::ok())
    {
        wp.getPosition();
        wp.publishGoal();
        ros::spinOnce();
    }
    return 0;
}
