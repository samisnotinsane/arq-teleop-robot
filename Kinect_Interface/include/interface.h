//
// Created by wael on 14/02/18.
//

#ifndef KINECT_INTERFACE_INTERFACE_H
#define KINECT_INTERFACE_INTERFACE_H


#include <iostream>

#include "libfreenect.h"
#include "ros_headers.h"

using namespace std;

class interface {


};

class Kinect {

private:
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *device;
    libfreenect2::SyncMultiFrameListener *listenerColor, *listenerIrDepth;
    libfreenect2::PacketPipeline *packetPipeline;
    libfreenect2::Registration *registration;
    libfreenect2::Freenect2Device::ColorCameraParams colorParams;
    libfreenect2::Freenect2Device::IrCameraParams irParams;

public:
    bool initialize();
    bool initDevice(string &sensor);
    void initConfig(const bool bilateral_filter, const bool edge_aware_filter, const double minDepth, const double maxDepth);
};


#endif //KINECT_INTERFACE_INTERFACE_H
