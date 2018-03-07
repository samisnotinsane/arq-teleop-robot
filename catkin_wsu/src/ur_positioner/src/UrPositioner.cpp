#include "ur_positioner/UrPositioner.hpp"
#include <string>

namespace ur_positioner {
	UrPositioner::UrPositioner(ros::NodeHandle& nodeHandle)
		: nodeHandle_(nodeHandle)
	{
		if(!readParameters()) {
			ROS_ERROR("Could not read parameters.");
			ros::requestShutdown();
		}
		subscriber_ = nodeHandle_.subscribe(subscriberTopic_, 1, &UrPositioner::topicCallback, this);
		ROS_INFO("Successfully launched node.");
	}

	UrPositioner::~UrPositioner() {
	}

	bool UrPositioner::readParameters() {
		if(!nodeHandle_.getParam("subscriber_topic", subscriberTopic_)) return false;
		return true;
	}

	void UrPositioner::topicCallback(const std_msgs::String& msg) {
		ROS_INFO("UR5 does: [%s] right now", msg.data.c_str());
	}	
	
} /*namespace*/

