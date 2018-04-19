#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <signal.h>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <cmath>

#include <signal.h>

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/SetCameraInfo.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/image_encodings.h>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include <tf/transform_broadcaster.h>

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/config.h>
#include <libfreenect2/registration.h>

using namespace std;
using namespace cv;

string type;

string serial = "";
libfreenect2::Freenect2 freenect2;
libfreenect2::Freenect2Device *dev = nullptr;
libfreenect2::SyncMultiFrameListener *listener;
libfreenect2::PacketPipeline *pipeline = nullptr;
libfreenect2::Registration *registration;
libfreenect2::Freenect2Device::ColorCameraParams colorParams;
libfreenect2::Freenect2Device::IrCameraParams irParams;

Mat colorMat, depthMat, depthMapUndistort, colorDepth;
libfreenect2::Frame undistorted(512, 424, 4), registered(512, 424, 4), depth2color(1920, 1080 + 2, 4);

//should the program be shut down
bool protonect_shutdown = false;
void sigint_handler(int s) {
    protonect_shutdown = true;
}

void registerPipeline() {

    cout << "INFO: Registering Kinect" << endl;

    if(pipeline == nullptr) {
        pipeline = new libfreenect2::CpuPacketPipeline();
    }
}

bool initDevice() {

    if(freenect2.enumerateDevices() == 0) {
        cout << "ERROR: No devices connected" << endl;
        return false;
    }

    if(serial == "") {
        serial = freenect2.getDefaultDeviceSerialNumber();
    }

    return true;
}

void printKinectDetails() {
    cout << "\nINFO: Device details:" << endl;
        cout << "\tDevice serial: " << serial << endl;

        cout << "" << endl;
}

bool setupKinect() {

    if(!initDevice()) {
        cout << "ERROR: Initialisation failed" << endl;
        return false;
    }
    registerPipeline();

    printKinectDetails();

    return true;
}

bool startDevice() {

    if(!dev->start()) {
        cout << "ERROR: could not start Kinect" << endl;
        delete listener;
        return false;
    }

    cout << "INFO: Device serial: " << dev->getSerialNumber() << endl;
    cout << "INFO: Device firmware: " << dev->getFirmwareVersion() << endl;

    return true;
}

void setupRegistration() {

    irParams = dev->getIrCameraParams();
    colorParams = dev->getColorCameraParams();

    registration = new libfreenect2::Registration(irParams, colorParams);
}

void showImages(libfreenect2::FrameMap frames, Mat &color, Mat &dep) {
    
    listener->waitForNewFrame(frames);
    libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
    libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];

    Mat(rgb->height, rgb->width, CV_8UC4, rgb->data).copyTo(color);

    if(type == "color") {
        imshow("Color", color);
        return;
    }

    registration -> apply(rgb, depth, &undistorted, &registered, true, &depth2color);

    Mat(undistorted.height, undistorted.width, CV_32FC1, undistorted.data).copyTo(depthMapUndistort);
    Mat(registered.height, registered.width, CV_8UC4, registered.data).copyTo(colorDepth);

    if(type == "depth") {
        imshow("Depth", depthMapUndistort/4500.0f);
        return;
    } else if (type == "both") {
        imshow("Color and Depth", colorDepth);
    }

    else if (type == "edges") {
        //Convert color image to grey
        Mat greyColor;

        cvtColor(color, greyColor, CV_BGR2GRAY);
        CvMemStorage* store = cvCreateMemStorage(0);

        //smooth to prevent false circles being detected
        blur(greyColor, greyColor, Size(3,3));

        Mat dst, detectedEdges;
        Canny(greyColor, greyColor, 100, 300, 3);
        dst = Scalar::all(0);

        color.copyTo(dst, greyColor);
        imshow("Objects", dst);

        return;
    }

    else if (type == "objects_image") {
        
        Mat hsv;
        cvtColor(color, hsv, CV_RGB2HSV);

        Scalar min(110, 175, 100);
        Scalar max(130, 255, 255);

        Mat seg;
        inRange(hsv, min, max, seg);

        vector<vector<Point>> contour;
        vector<Vec4i> heirarchy;
        vector<Point2i> center;
        vector<int> rad;
        string distance;
        
        findContours(seg.clone(), contour, heirarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

        for(int i=0; i<contour.size(); i++) {
            Point2f cent; float r;
            minEnclosingCircle(contour[i], cent, r);

            if(r >= 10) {
                center.push_back(cent);
                rad.push_back(r);
            }
        }

        Scalar redColor(255,0,0);

        for(int i=0; i<center.size(); i++) {
            Point2f topLeft(center[i].x+rad[i], center[i].y+rad[i]);
            Point2f bottomRight(center[i].x-rad[i], center[i].y-rad[i]);

            rectangle(seg, topLeft, bottomRight, redColor, 1, 8, 0);
            
            string r = to_string(rad[i]);
            string top = "Radius = " + r;
            string c = "Center = " + format("(%d,%d)", center[i].x, center[i].y);
            
            Point2f topLeftText(center[i].x-(10+rad[i]), center[i].y-(10+rad[i]));
            Point2f centPointText(center[i].x-rad[i], center[i].y + rad[i]+20);
            Point2f point(center[i].x, center[i].y);

            Scalar black(0,0,255);
            circle(seg, point, 2, black, -1, 8, 0);

            putText(seg, top, topLeftText, FONT_HERSHEY_COMPLEX_SMALL, 1, redColor);
            putText(seg, c, centPointText, FONT_HERSHEY_COMPLEX_SMALL, 1, redColor);
            
        }

        imshow("Segmentation", seg);

        return;
    }


    if(type == "edges_depth") {
        
        Mat depth = depthMapUndistort/4500.0f;
        Mat depthSeg = Mat::zeros(depth.rows, depth.cols, CV_32FC1);
        Scalar redColor(255,0,0);
        for(int i=1; i<depth.rows; i++) {
            for(int j=0; j<depth.cols; j++) {
                int difference = abs(depth.at<int>(i,j) - depth.at<int>(i-1,j));
                if(difference > 1000000) {
                    Point2f point(j,i);
                    line(depthSeg, point, point, redColor);
                }
            }
        }
        imshow("depth", depthSeg);

        return;
    }
}

void beginCollection(libfreenect2::FrameMap frames) {

    while(!protonect_shutdown) {
        showImages(frames, colorMat, depthMat);

        //Wait for key input, shutdown on escape
        int inputKey = waitKey(1);
        protonect_shutdown = protonect_shutdown || (((inputKey & 0xFF) == 27) && inputKey > 0);
        listener->release(frames);
    }
}

bool openDevice() {

    if(pipeline != nullptr) {
        dev = freenect2.openDevice(serial, pipeline);
    } else {
        dev = freenect2.openDevice(serial);
    }

    if(dev == 0) {
        cout << "ERROR: Failed to open device" << endl;
        return false;
    }

    signal(SIGINT, sigint_handler);
    protonect_shutdown = false;

    listener = new libfreenect2::SyncMultiFrameListener(
        libfreenect2::Frame::Color | libfreenect2::Frame::Ir | libfreenect2::Frame::Depth
        );

    libfreenect2::FrameMap frames;

    dev->setColorFrameListener(listener);
    dev->setIrAndDepthFrameListener(listener);

    if(!startDevice()) {
        cout << "ERROR: Failed to start device" << endl;
    }

    setupRegistration();

    beginCollection(frames);

    return true;
}

void closeDevice() {
    dev -> stop();
    dev -> close();

    delete registration;
}

int main (int argc, char **argv) {

    if( argc != 2 )
    {
        cout << "\nIncorrect launch command" << endl;
        cout << "Launch command format: " << endl;
        cout << "rosrun object_locator object_locator [color | depth | both | edges | objects_image]" << endl;

        return 0;
    } 
    type = argv[1];
    if (!(type == "color"   ||
          type == "depth"   ||
          type == "both"    ||
          type == "edges"   ||
          type == "edges_depth"    ||
          type == "objects_image"    ))
    {
        cout << "The final argument must be [color | depth | both | edges | edges_depth | objects_image]" << endl;
        return 0;
    }

    if(!setupKinect()) {
        cout << "ERROR: Kinect Setup Failed" << endl;
        return -1;
    }

    if(!openDevice()) {
        cout << "ERROR: Open Device Failed" << endl;
        return -1;
    }

    closeDevice();
    
    cout << "Object Locator Completed Successfully" << endl;
}