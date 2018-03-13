#include "ur_positioner/UrPositioner.hpp"
#include <string>

#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayTrajectory.h>
#include <tf/transform_listener.h>


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
		
		ROS_INFO("Got here: 1");
		//const boost::shared_ptr<tf::Transformer>& tf_ = boost::shared_ptr<tf::Transformer>();
		//const ros::Duration& max_rate = ros::Duration(5);		
		//moveit::planning_interface::MoveGroup group("manipulator", tf_,  max_rate);

		moveit::planning_interface::MoveGroup group("manipulator");
		/**
		<joint name="elbow_joint" value="0" />
		<joint name="shoulder_lift_joint" value="0" />
		<joint name="shoulder_pan_joint" value="0" />
		<joint name="wrist_1_joint" value="0" />
		<joint name="wrist_2_joint" value="0" />
		<joint name="wrist_3_joint" value="0" />
		**/
		ROS_INFO("Got here: 2");
		moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
		
		ROS_INFO("Got here: 3");
		ros::Publisher display_publisher = nodeHandle_.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
		
		ROS_INFO("Got here: 4");
		moveit_msgs::DisplayTrajectory display_trajectory;
		
		ROS_INFO("Got here: 5");		

		ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
		ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());
		geometry_msgs::Pose target_pose1;
		target_pose1.orientation.w = 1.0;
		target_pose1.position.x = 0.28;
		target_pose1.position.y = -0.7;
		target_pose1.position.z = 1.0;
		group.setPoseTarget(target_pose1);
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

