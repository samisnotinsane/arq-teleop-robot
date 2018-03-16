
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


//ros
#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <ros/spinner.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

//image_transport
#include <image_transport/image_transport.h>
#include <image_transport/subscriber_filter.h>

//message_filers
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

//point cloud library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

#include "std_msgs/String.h"

class ObjectRecogniser {
    public:

    private:
    const std::string colorTopic, depthTopic;
    const int queueSize;
    bool updateImage, running;

    typedef message_filters::sync_policies::ExactTime<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::CameraInfo, sensor_msgs::CameraInfo> ExactSyncPolicy;

    ros::NodeHandle nodeHandler;
    ros::AsyncSpinner spinner;

    cv::Mat color, depth;

    image_transport::ImageTransport imageTransporter;
    image_transport::SubscriberFilter *subscriberColor, *subscriberDepth;
    message_filters::Subscriber<sensor_msgs::CameraInfo> *subscriberColorInfo, *subscriberDepthInfo;

    message_filters::Synchronizer<ExactSyncPolicy> *syncColorandDepth;

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud;

    //std::thread imageViewerThread;
    
    public:
    ObjectRecogniser(const std::string &color, const std::string &depth) 
    : colorTopic(color), depthTopic(depth), spinner(0), updateImage(false),
        queueSize(5), nodeHandler("~"), imageTransporter(nodeHandler) {

    }

    ~ObjectRecogniser() {

    }

    void run() {
        std::cout << "\nObject Recogniser enter run()" << std::endl;
        start();
        stop();
    }

    private:
    void start() {
        std::cout << "\nStarting Object Recogniser" << std::endl;

        //Finding camera information about the kinect
        std::string colorTopicInfo = colorTopic.substr(0, colorTopic.rfind('/')) + "/camera_info";
        std::string depthTopicInfo = depthTopic.substr(0, depthTopic.rfind('/')) + "/camera_info";

        image_transport::TransportHints transportHints("raw");
        subscriberColor = new image_transport::SubscriberFilter(imageTransporter, colorTopic, queueSize, transportHints);
        subscriberDepth = new image_transport::SubscriberFilter(imageTransporter, depthTopic, queueSize, transportHints);

        subscriberColorInfo = new message_filters::Subscriber<sensor_msgs::CameraInfo>(nodeHandler, colorTopicInfo, queueSize);
        subscriberDepthInfo = new message_filters::Subscriber<sensor_msgs::CameraInfo>(nodeHandler, depthTopicInfo, queueSize);

        syncColorandDepth = new message_filters::Synchronizer<ExactSyncPolicy>(ExactSyncPolicy(5), *subscriberColor, *subscriberDepth, *subscriberColorInfo, *subscriberDepthInfo);
        syncColorandDepth->registerCallback(boost::bind(&ObjectRecogniser::callback, this, _1, _2, _3, _4));

        spinner.start();

        cloud = pcl::PointCloud<pcl::PointXYZRGBA>::Ptr(new pcl::PointCloud<pcl::PointXYZRGBA>());
        cloud->height = color.rows;
        cloud->width = color.cols;
        cloud->is_dense = false;
        cloud->points.resize(cloud->height * cloud->width);
        createLookup(this->color.cols, this->color.rows);

        //imageViewerThread = std::thread(&ObjectRecogniser::imageViewer, this);
        cloudViewer();
    }

    void stop() {
        std::cout << "Stopping Object Recogniser" << std::endl;

        spinner.stop();

        running = false;

        delete syncColorandDepth;
        delete subscriberColor;
        delete subscriberDepth;
        delete subscriberColorInfo;
        delete subscriberDepthInfo;
        
        //imageViewerThread.join();
    }

    void callback(const sensor_msgs::Image::ConstPtr imageColor, const sensor_msgs::Image::ConstPtr imageDepth,
                    const sensor_msgs::CameraInfo::ConstPtr cameraInfoColor, const sensor_msgs::CameraInfo::ConstPtr cameraInfoDepth) {
        updateImage = true;
    }

    void createLookup(size_t width, size_t height) {
        std::cout << "In lookup" << std::endl;
    }

    void imageViewer() {

    }

    void cloudViewer() {

    }
};

int main (int argc, char **argv) {

    std::cout << "Object Recogniser Begin" << std::endl;
    ros::init(argc, argv, "object_recogniser");

    if(!ros::ok()) {
        std::cout << "Node has shut down" << std::endl;
        return 0;
    }

    std::string colorTopic = "/kinect2/hd/image_color";
    std::string depthTopic = "/kinect2/sd/image_depth";

    ObjectRecogniser objRecog(colorTopic, depthTopic);
    objRecog.run();
    
    std::cout << "Completed viewing, ROS node shutting down" << std::endl;
    ros::shutdown();
    return 0;
}