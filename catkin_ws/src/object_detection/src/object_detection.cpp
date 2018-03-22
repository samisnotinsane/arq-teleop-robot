
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <mutex>
#include <thread>
#include <chrono>


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

using namespace std;


string windowName;
bool guiActive;


int main (int argc, char **argv) {

    ros::init(argc, argv, "ObjectDetector", ros::init_options::AnonymousName);
    
    //check is the topic exists
    if(ros::names::remap("image") == "image") {
        ROS_WARN("The argument must be in the form image:=<topic name>, please try again");
        return 0;
    }

    ros::NodeHandle nodeHandler;
    ros::NodeHandle localNh("~");

    string topicName = nodeHandler.resolveName("image");
    localNh.param("window_name", windowName, topicName);
    localNh.param("gui", guiActive, true);
}