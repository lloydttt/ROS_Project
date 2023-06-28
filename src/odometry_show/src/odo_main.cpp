#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include <iostream>


void callbacki(const nav_msgs::Odometry::ConstPtr& a){
    

}




int main(int argc, char **argv){
    ros::init(argc,argv,"odo_show");
    ros::NodeHandle n;
    ros::Subscriber nn = n.subscribe("/odom",1000,callbacki);
    ros::spin();

    return 0;


}



