#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/UInt8.h"
#include "std_msgs/UInt8MultiArray.h"

class receive_esignal
{
    private:

       ros::NodeHandle nh;
       ros::Subscriber esignal_sub;

       std_msgs::UInt8 esignal_msg;
       std_msgs::UInt8MultiArray msg;
       

    public:

        void esignalCallback(const std_msgs::UInt8::ConstPtr& esginal_msg){

            int esginal = esginal_msg->data;
            bool esignal_array[8] = {};

            for(int i = 7; i >= 0; i--){
                if(int(esginal / pow(2,i)) == 1){
                    esignal_array[i] = true;
                    esginal = esginal - pow(2,i);
                }             
                else
                    esignal_array[i] = false;

                std::cout << esignal_array[i] << " ";    
            }

            std::cout << std::endl;

            
        }
       
        receive_esignal(){

            ros::Rate rate(100);
            this->esignal_sub = nh.subscribe("/emergency_signal", 10, &receive_esignal::esignalCallback, this);

            while(ros::ok()){
                rate.sleep();
                ros::spinOnce();

            }

        }

};

int main(int argc, char **argv){

    ros::init(argc, argv, "receive_esignal");
    receive_esignal receive_esignal;
    ros::spin();

    return 0;
} 
