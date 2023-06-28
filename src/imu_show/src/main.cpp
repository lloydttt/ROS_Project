#include <ros/ros.h>
#include "sensor_msgs/Imu.h"

void callbacki(const sensor_msgs::Imu::ConstPtr &a){
    
}

int main(int argc,char **argv){
    ros::init(argc,argv,"imu_show");
    ros::NodeHandle n;
    ros::Subscriber nn = n.subscribe("/imu/data_raw",1000,callbacki);
    ros::spin();

    return 0;
}