#include <iostream>
#include <cstring>
#include <thread>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>

cv::Mat map;

void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{

    double scale = 1.0;
    int width = 1200;
    int height = 1200;
    cv::Point offset = {-1600, -1600};
    map = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);

    for (int i = 0; i < msg->info.width * msg->info.height; ++i) {
        int x = (i % msg->info.width + offset.x) * scale;
        int y = (i / msg->info.width + offset.y) * scale;
        if (msg->data[i] == -1) {
            cv::circle(map, cv::Point(x, y), 1, cv::Scalar(255, 255, 255), -1);
        } else if (msg->data[i] >= 80) {
            cv::circle(map, cv::Point(x, y), 3, cv::Scalar(0, 0, 0), -1);
        } else {
            cv::circle(map, cv::Point(x, y), 3, cv::Scalar(64, 64, 64), -1);
        }
    }

    cv::imshow("My Slam Map", map);
    cv::waitKey(1000);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "show_map");
    ros::NodeHandle n;
    ros::Subscriber nn = n.subscribe<nav_msgs::OccupancyGrid>("/map", 1000, mapCallback);

    // cv::namedWindow("Slam Map", cv::WINDOW_NORMAL);

    ros::spin();

    return 0;
}
