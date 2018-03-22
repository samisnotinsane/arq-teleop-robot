#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <sys/stat.h>

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

//libfreenect2::Frame color;

string serial = "";
libfreenect2::Freenect2 freenect2;
libfreenect2::Freenect2Device *dev = nullptr;
libfreenect2::SyncMultiFrameListener *listenerColor, *listenerDepth;
libfreenect2::PacketPipeline *pipeline = nullptr;
libfreenect2::Registration *registration;
libfreenect2::Freenect2Device::ColorCameraParams colorParams;
libfreenect2::Freenect2Device::IrCameraParams irParams;

//should the program be shut down
bool shutdown = false;
void sigint_handler(int s) {
    shutdown = true;
}

void registerKinect() {

    cout << "INFO: Registering Kinect" << endl;

    registration = new libfreenect2::Registration(irParams, colorParams);
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
    registerKinect();

    printKinectDetails();

    return true;
}

bool startDevice() {

    if(!dev->start()) {
        cout << "ERROR: could not start Kinect" << endl;
        delete listenerColor;
        delete listenerDepth;
        return false;
    }

    cout << "INFO: Device serial: " << dev->getSerialNumber() << endl;
    cout << "INFO: Device firmware: " << dev->getFirmwareVersion() << endl;

    return true;
}

void receiveFrames(libfreenect2::FrameMap frames) {
    cout << "Receiving Frames" << endl;
    libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
    libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];

}

bool openDevice() {

    if(pipeline != nullptr) {
        dev = freenect2.openDevice(serial, pipline);
    } else {
        dev = freenect2.openDevice(serial);
    }

    if(dev == 0) {
        cout << "ERROR: Failed to open device" << endl;
        return false;
    }

    signal(SIGINT, sigint_handler);
    shutdown = false;

    listenerColor = new libfreenect2::SyncMultiFrameListener(libfreenect2::Frame::Color);
    listenerDepth = new libfreenect2::SyncMultiFrameListener(libfreenect2::Frame::Ir | libfreenect2::Frame::Depth);

    libfreenect2::FrameMap frames;

    dev->setColorFrameListener(listenerColor);
    dev->setIrAndDepthFrameListener(listenerDepth);

    if(!startDevice()) {
        cout << "ERROR: Failed to start device" << endl;
    }

    while(ros::ok()) {
        receiveFrames(frames);
    }

    return true;
}

void closeDevice() {
    dev -> stop();
    dev -> close();
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
    
    cout << "Hello" << endl;
}