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
#include <obstacle_detector/Obstacles.h> //---> 질문!

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

            
            obs_subs = nh_.subscribe("/raw_obstacles",1,&WaypointFollowing::obstaclesCB, this);
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
            double safe_dis=10.0;
            //obs_flag=obs_checker();

            if (distance_calc()<safe_dis)
            {
                /* code
                장애물 발견된 경우 stop하는 코드 작성            
                 */
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
            else{
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
        }


        void obstaclesCB(const obstacle_detector::Obstacles::ConstPtr& msg)
        {
            obstacles_msg = msg;
            _segments[] = msg.segments;
            _circles[] = msg.circles;
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
        obstacle_detector::Obstacles::ConstPtr obstacles_msg;
        obstacle_detector::SegmentObstacle[] _segments;
        obstacle_detector::CircleObstacle[] _circles;
        //obstacle_detector::obstacles_msg;

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

        geometry_msgs::Pose setGoal_Post()
        {
            geometry_msgs::Pose answer;
            int near_index=findNearestPoint();
            int carrot_index = near_index + 5;
            if((carrot_index) > waypoints_.size() - 1)
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

        double distance_calc(int i=0)
        {

            //segments배열 안에있는 segment의 거리들중에서도 최소인애 발견시 멈춰야함 
            double min_obs_dist = 9999999.0; // MAX
            /*
            precondition: get segment's first/last x,y value
            postcondition: return shortest distance
            */
           
            geometry_msgs::Point first_seg, last_seg, seg_point;
            first_seg=_segments[i].first_point;
            last_seg=_segments[i].last_seg;
            // double seg_length=sqrt(pow(first_seg.x-last_seg.x,2)+pow(first_seg.y-last_seg.y,2),2);
            
            // for(int i=0; i < seg_length; i++)
            // {
            //     seg_point.x = i * first_seg.x + (seg_length - i) * last_seg.x / seg_length;
            //     seg_point.y = i * first_seg.y + (seg_length - i) * last_seg.y / seg_length; 

            //     //장애물과 로봇 사이의 거리구하는 함수
            //     double dist = sqrt(pow(seg_point.x, 2) + pow(seg_point.y, 2), 2);
            //     if(min_obs_dist > dist) min_obs_dist = dist;
            // }
            return sqrt(pow(((last_seg.y-first_seg.y)*first_seg.x)-((last_seg.x-first_seg.x)*first_seg.y),2),2)/sqrt(pow(last_seg.y-first_seg.y,2)+pow(last_seg.x-first_seg.x,2)); 
        }

        bool obs_checker()
        {
            if (_segments.empty() && _circles.empty())
            {
                seg_point.x = (i * first_seg.x + (seg_length - i) * last_seg.x) / seg_length;
                seg_point.y = (i * first_seg.y + (seg_length - i) * last_seg.y) / seg_length; 

                //장애물과 로봇 사이의 거리구하는 함수
                double dist = sqrt(pow(seg_point.x, 2) + pow(seg_point.y, 2));
                if(min_obs_dist > dist) min_obs_dist = dist;

                //sqrt(pow(((last_seg.y-first_seg.y)*first_seg.x)-((last_seg.x-first_seg.x)*first_seg.y),2),2)/sqrt(pow(last_seg.y-first_seg.y,2)+pow(last_seg.x-first_seg.x,2))
            }
            return min_obs_dist; 
        }

        // bool obs_checker()
        // {
        //     if (_segments.empty())
        //     {
        //         // No obstacles detected
        //         ROS_INFO("No obstacles detected.");
        //         return false;
        //     }
        //     else
        //     {
        //         // Obstacles detected
        //         ROS_WARN("Obstacles detected.");
        //         return true;
        //     }
        // }

};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "follow_waypoints");


    string pkg_path_ = ros::package::getPath("multiwaypoints");        
    string file_path_ = pkg_path_ + "/data/waypoints.csv";

    WaypointFollowing wp(file_path_);

    ros::Rate rate(0.1);

    while(ros::ok())
    {
        wp.getPosition();
        wp.publishGoal();
        rate.sleep();
    }
    return 0;
}
