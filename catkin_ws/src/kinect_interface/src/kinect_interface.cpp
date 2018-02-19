
#include <kinect_interface/interface.h>

using namespace std;

int main(int argc, char **argv) {
    Kinect kinect;
    kinect.initialize();

    return 0;
}

bool Kinect::initialize() {

    std::string sensor;

    /*
     *
     * Setup ROS parameters
     *
     */

    if(!initDevice(sensor)) {
        return false;
    }

    initConfig(true, true, 0.1, 15);

    //initCalibration(calib_path, sensor);
/*
    if(!initRegistration(reg_method, reg_dev, maxDepth))
    {
        if(!device->close())
        {
            OUT_ERROR("could not close device!");
        }
        delete listenerIrDepth;
        delete listenerColor;
        return false;
    }
*/
    //createCameraInfo();
    //initTopics(queueSize, base_name);

    return true;
}

void Kinect::initConfig(const bool bilateral_filter, const bool edge_aware_filter, const double minDepth, const double maxDepth)
{
    libfreenect2::Freenect2Device::Config config;
    config.EnableBilateralFilter = bilateral_filter;
    config.EnableEdgeAwareFilter = edge_aware_filter;
    config.MinDepth = minDepth;
    config.MaxDepth = maxDepth;
    device->setConfiguration(config);
}

bool Kinect::initDevice(string &sensor) {

    bool deviceFound = false;
    const int numOfDevs = freenect2.enumerateDevices();

    if(numOfDevs <= 0)
    {
        cout << "ERROR: no Kinect2 devices found!" << endl;
        //delete packetPipeline;
        return false;
    }

    if(sensor.empty())
    {
        sensor = freenect2.getDefaultDeviceSerialNumber();
    }

    cout << "INFO: Kinect2 devices found: " << endl;
    for(int i = 0; i < numOfDevs; ++i)
    {
        const std::string &s = freenect2.getDeviceSerialNumber(i);
        deviceFound = deviceFound || s == sensor;
        cout << "  " << i << ": " << s << (s == sensor ? " (selected)" : "") << endl;
    }

    if(!deviceFound)
    {
        cout << "ERROR: Device with serial '" << sensor << "' not found!" << endl;
        delete packetPipeline;
        return false;
    }

    device = freenect2.openDevice(sensor, packetPipeline);

    if(device == 0)
    {
        cout << "INFO: no device connected or failure opening the default one!" << endl;
        return false;
    }

    listenerColor = new libfreenect2::SyncMultiFrameListener(libfreenect2::Frame::Color);
    listenerIrDepth = new libfreenect2::SyncMultiFrameListener(libfreenect2::Frame::Ir | libfreenect2::Frame::Depth);

    cout << "INFO: starting kinect2" << endl;
    if(!device->start())
    {
        cout << "ERROR: could not start device!" << endl;
        delete listenerIrDepth;
        delete listenerColor;
        return false;
    }

    cout << "INFO:   device serial: " << sensor << endl;
    cout << "INFO:   device firmware: "  << device->getFirmwareVersion() << endl;

    colorParams = device->getColorCameraParams();
    irParams = device->getIrCameraParams();

    if(!device->stop())
    {
        cout << "ERROR: could not stop device!" << endl;
        delete listenerIrDepth;
        delete listenerColor;
        return false;
    }

    cout << "DEBUG: default ir camera parameters: " << endl;
    cout << "DEBUG: fx: " << irParams.fx << ", fy: " << irParams.fy << ", cx: " << irParams.cx << ", cy: " << irParams.cy << endl;
    cout << "DEBUG: k1: " << irParams.k1 << ", k2: " << irParams.k2 << ", p1: " << irParams.p1 << ", p2: " << irParams.p2 << ", k3: " << irParams.k3 << endl;

    cout << "DEBUG: default color camera parameters: " << endl;
    cout << "DEBUG: fx: " << colorParams.fx << ", fy: " << colorParams.fy << ", cx: " << colorParams.cx << ", cy: " << colorParams.cy << endl;

    /*
     *
     *
     *
     * EDIT THE MATRICIES AS NEEDED HERE
     * IF NEEDED
     *
     */

    return true;
}