#include <ros/ros.h>//导入ros库
#include <image_transport/image_transport.h>//image_transport应该总被用在image订阅和发布上。
#include <cv_bridge/cv_bridge.h>// CvBridge是一个ROS库，提供ROS和OpenCV之间的接口。
#include <sensor_msgs/image_encodings.h>//调用深度相机的传感器参数
#include <opencv2/imgproc/imgproc.hpp>//图像处理的过滤器
#include <opencv2/highgui/highgui.hpp>//图像处理的过滤器
//设置生成图像的标题
static const std::string OPENCV_WINDOW_COLOR = "Image color window";
static const std::string OPENCV_WINDOW_DEPTH = "Image depth window";
 
class ImageConverter
{
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;
	image_transport::Subscriber image_sub_color;
	image_transport::Subscriber image_sub_depth;
	image_transport::Publisher image_pub_color;
	image_transport::Publisher image_pub_depth;
    //初始化了一些变量，用于image的订阅和发布
 
public:
	ImageConverter()//构造函数
		: it_(nh_)
	{
		// Subscrive to input video feed and publish output video feed
		image_sub_color = it_.subscribe("/camera/color/image_raw", 1, &ImageConverter::imageCb, this);
		image_sub_depth = it_.subscribe("/camera/depth/image_rect_raw", 1, &ImageConverter::depthCb, this);
		image_pub_color = it_.advertise("/image_converter/output_video/color", 1);
		image_pub_depth = it_.advertise("/image_converter/output_video/depth", 1);
//创建一个图像窗口
		cv::namedWindow(OPENCV_WINDOW_COLOR);
		cv::namedWindow(OPENCV_WINDOW_DEPTH);
        
	}
 
	~ImageConverter()
	{
		cv::destroyWindow(OPENCV_WINDOW_COLOR);
		cv::destroyWindow(OPENCV_WINDOW_DEPTH);
//析构函数
        
	}
//建立CV和ros的接口，实现彩色图形化输出
	void imageCb(const sensor_msgs::ImageConstPtr &msg)
	{
		cv_bridge::CvImagePtr cv_ptr;
		try
		{
			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		}
		catch (cv_bridge::Exception &e)
		{
			ROS_ERROR("cv_bridge exception: %s", e.what());
			return;
		}
 
		// Draw an example circle on the video stream
		if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
		{
			cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255, 0, 0));
		}
 
		// Update GUI Window，更新图形化界面
		cv::imshow(OPENCV_WINDOW_COLOR, cv_ptr->image);
		cv::waitKey(3);
 
		// Output modified video stream，输出视频流
		image_pub_color.publish(cv_ptr->toImageMsg());
	}
 
//建立CV和ros的接口，实现深度图的输出
	void depthCb(const sensor_msgs::ImageConstPtr &msg)
	{
		cv_bridge::CvImagePtr cv_ptr;
		try
		{
			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);
		}
		catch (cv_bridge::Exception &e)
		{
			ROS_ERROR("cv_bridge exception: %s", e.what());
			return;
		}
 
		// Draw an example circle on the video stream
		if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
			cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255, 0, 0));
 
		// Update GUI Window
		cv::imshow(OPENCV_WINDOW_DEPTH, cv_ptr->image);
		cv::waitKey(3);
 
		// Output modified video stream
		image_pub_depth.publish(cv_ptr->toImageMsg());
	}
};
 
int main(int argc, char **argv)
{
	ros::init(argc, argv, "image_converter");//初始化节点
	ImageConverter ic;//调用构造函数中的回调函数
	ros::spin();
	return 0;
}