#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace std;

class ObjectRecogniser {
    public:

    private:
    const string colorTopic, depthTopic;
    
    public:
    ObjectRecogniser(const string &color, const string &depth) 
    : colorTopic(color), depthTopic(depth) {

    }

    ~ObjectRecogniser() {

    }

    void run() {
        cout << "Running Object Recogniser" << endl;
        start();
        stop();
    }

    private:
    void start() {
        cout << "\nStarting Object Recogniser" << endl;

        //Finding camera information about the kinect
        string colorTopicInfo = colorTopic.substr(0, colorTopic.rfind('/')) + "/camera_info";
        string depthTopicInfo = depthTopic.substr(0, depthTopic.rfind('/')) + "/camera_info";


    }

    void stop() {
        cout << "Stopping Object Recogniser" << endl;
    }
};

int main (int argc, char **argv) {

    ros::init(argc, argv, "object_recogniser");

    if(!ros::ok()) {
        cout << "Node has shut down" << endl;
        return 0;
    }

    string colorTopic = "/kinect2/hd/image_color";
    string depthTopic = "/kinect2/sd/image_depth";

    ObjectRecogniser objRecog(colorTopic, depthTopic);
    objRecog.run();
    
    cout << "Completed viewing, ROS node shutting down" << endl;
    ros::shutdown();
    return 0;
}