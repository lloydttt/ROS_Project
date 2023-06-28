#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include <iostream>


void callbacki(const nav_msgs::Odometry::ConstPtr& a){
    std::cout << "std_msgs/Header header" << std::endl;
    std::cout << "uint32 seq: " << a->header.seq << std::endl;
    std::cout << "time stamp: " << a->header.stamp << std::endl;
    std::cout << "frame_id: " << a->header.frame_id << std::endl;
    std::cout << "child_frame_id: " << a->child_frame_id << std::endl;
    std::cout << "geometry_msgs/PoseWithCovariance pose" << std::endl;
    std::cout << "geometry_msgs/Pose pose" << std::endl;
    std::cout << "geometry_msgs/Point position" << std::endl;
    std::cout << "float64 x: " << a->pose.pose.position.x << std::endl;
    std::cout << "float64 y: " << a->pose.pose.position.y << std::endl;
    std::cout << "float64 z: " << a->pose.pose.position.z << std::endl;
    std::cout << "geometry_msgs/Quaternion orientation" << std::endl;
    std::cout << "float64 x: " << a->pose.pose.orientation.x << std::endl;
    std::cout << "float64 y: " << a->pose.pose.orientation.y << std::endl;
    std::cout << "float64 z: " << a->pose.pose.orientation.z << std::endl;
    std::cout << "float64 w: " << a->pose.pose.orientation.w << std::endl;
    std::cout << "covariance: " << std::endl;
    for (int i = 0; i < 36; ++i) {
        std::cout << a->pose.covariance[i] << " ";
    }
    std::cout<<std::endl;
    std::cout << "geometry_msgs/TwistWithCovariance twist" << std::endl;
    std::cout << "geometry_msgs/Twist twist" << std::endl;
    std::cout << "geometry_msgs/Vector3 linear" << std::endl;
    std::cout << "float64 x: " << a->twist.twist.linear.x << std::endl;
    std::cout << "float64 y: " << a->twist.twist.linear.y << std::endl;
    std::cout << "float64 z: " << a->twist.twist.linear.z << std::endl;
    std::cout << "geometry_msgs/Vector3 angular" << std::endl;
    std::cout << "float64 x: " << a->twist.twist.angular.x << std::endl;
    std::cout << "float64 y: " << a->twist.twist.angular.y << std::endl;
    std::cout << "float64 z: " << a->twist.twist.angular.z << std::endl;
    std::cout << "covariance: " << std::endl;
    for (int i = 0; i < 36; ++i) {
        std::cout << a->twist.covariance[i] << " ";
    }
    std::cout<<std::endl;
    std::cout << "                  end               " << std::endl;
    return ;

}




int main(int argc, char **argv){
    ros::init(argc,argv,"odo_show");
    ros::NodeHandle n;
    ros::Subscriber nn = n.subscribe("/odom",1000,callbacki);
    ros::spin();

    return 0;


}



