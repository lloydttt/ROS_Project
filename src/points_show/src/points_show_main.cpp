#include <iostream>
#include <memory>
#include <cstring>
#include <ros/ros.h>
#include <pcl/visualization/cloud_viewer.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/statistical_outlier_removal.h>

#include "pcl/point_types.h"
#include "pcl/PCLPointCloud2.h"
#include "pcl/conversions.h"
#include "pcl_ros/transforms.h"

pcl::visualization::CloudViewer viewer("Cloud Viewer");
// ros::Timer viewer_timer;



// void timerCB(const ros::TimerEvent&)
// {
//     if (viewer.wasStopped())
//     {
//         ros::shutdown();
//     }
// }

void callbacki(const sensor_msgs::PointCloud2::ConstPtr &a){
        pcl::PointCloud<pcl::PointXYZ> cloud;
        pcl::PCLPointCloud2 pcl_pc;
        pcl_conversions::toPCL(*a, pcl_pc);
        pcl::fromPCLPointCloud2(pcl_pc, cloud);
        viewer.showCloud(cloud.makeShared());
        // viewer_timer = nh.createTimer(ros::Duration(0.1), &cloudHandler::timerCB, this);

        return ;
}

int main (int argc, char **argv)
{
    ros::init (argc, argv, "points_show");
    ros::NodeHandle handler;
    ros::Subscriber nn = handler.subscribe("/rslidar_points",1000,callbacki);
    ros::spin();

    return 0;
}