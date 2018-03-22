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

#include <signal.h>

#include <opencv2/opencv.hpp>

#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/SetCameraInfo.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/image_encodings.h>

#include <tf/transform_broadcaster.h>

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/config.h>
#include <libfreenect2/registration.h>

using namespace std;
using namespace cv;

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

    imshow("Color", color);

    registration -> apply(rgb, depth, &undistorted, &registered, true, &depth2color);

    Mat(undistorted.height, undistorted.width, CV_32FC1, undistorted.data).copyTo(depthMapUndistort);
    Mat(registered.height, registered.width, CV_8UC4, registered.data).copyTo(colorDepth);

    imshow("Depth", depthMapUndistort/4500.0f);
    imshow("Color and Depth", colorDepth);
}

void beginCollection(libfreenect2::FrameMap frames) {
    
    //Maybe not needed
    //Mat irMat;

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