#include <ros/ros.h>
#include <std_msgs/String.h>

void positionCallback(const std_msgs::String& msg) {
	ROS_INFO("UR5 does: [%s] right now", msg.data.c_str());
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "ur_positioner_node");
	ros::NodeHandle nodeHandle;

	ros::Subscriber subscriber = 
		nodeHandle.subscribe("position",10,positionCallback);
	ros::spin();
	return 0;
}
