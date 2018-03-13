#include "ur_positioner/UrPositioner.hpp"
#include <string>

#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

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
		
		moveit::planning_interface::MoveGroup group("manipulator");
		/**
		<joint name="elbow_joint" value="0" />
		<joint name="shoulder_lift_joint" value="0" />
		<joint name="shoulder_pan_joint" value="0" />
		<joint name="wrist_1_joint" value="0" />
		<joint name="wrist_2_joint" value="0" />
		<joint name="wrist_3_joint" value="0" />
		**/		
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

