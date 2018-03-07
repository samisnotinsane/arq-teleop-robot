#include <ros/ros.h>
#include <ur_positioner/UrPositioner.hpp>

int main(int argc, char **argv) {
	ros::init(argc, argv, "ur_positioner");
	ros::NodeHandle nodeHandle("~");

	ur_positioner::UrPositioner urPositioner(nodeHandle);
	ros::spin();
	return 0;
}
