#include "ur_positioner_kinetic/UrPositionerKinetic.hpp"
#include <string>

//#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>

#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <tf/transform_listener.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

namespace ur_positioner_kinetic {

UrPositionerKinetic::UrPositionerKinetic(ros::NodeHandle& nodeHandle)
    : nodeHandle_(nodeHandle)
{
  if (!readParameters()) {
    ROS_ERROR("Could not read parameters.");
    ros::requestShutdown();
  }

  subscriber_ = nodeHandle_.subscribe(subscriberTopic_, 1,
                                      &UrPositionerKinetic::topicCallback, this);
  //spinner.stop();
  //serviceServer_ = nodeHandle_.advertiseService("get_average",
                                                //&RosPackageTemplate::serviceCallback, this);
  ROS_INFO("Successfully launched node.");
}

UrPositionerKinetic::~UrPositionerKinetic()
{
}

bool UrPositionerKinetic::readParameters()
{
  if (!nodeHandle_.getParam("subscriber_topic", subscriberTopic_)) return false;
  return true;
}

void UrPositionerKinetic::topicCallback(geometry_msgs::Pose target_pose1)
{
  ros::AsyncSpinner spinner(1);
  spinner.start();
  static const std::string PLANNING_GROUP = "manipulator";
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  ROS_INFO("About to fail in getting robot state");
  //const robot_state::JointModelGroup *joint_model_group =
  //move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  //namespace rvt = rviz_visual_tools;
//moveit_visual_tools::MoveItVisualTools visual_tools("odom_combined");

  ROS_INFO_NAMED("tutorial", "Reference frame: %s", move_group.getPlanningFrame().c_str());
  ROS_INFO_NAMED("tutorial", "End effector link: %s", move_group.getEndEffectorLink().c_str());
  move_group.setPoseTarget(target_pose1);

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  ROS_INFO("Why are you doing this to me?");

  //bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  //move_group.plan(my_plan);

  ROS_INFO("About to block");
  //ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
  ROS_INFO("Did I get here?");
  //sleep(4.0);
  move_group.move();
  //move_group.execute(my_plan);

		/*std::vector<geometry_msgs::Pose> waypoints;

		//waypoints.push_back(target_pose1);

		target_pose1.position.x += 0.2; //left
		//target_pose1.position.z += 0.2;

		waypoints.push_back(target_pose1);

		target_pose1.position.y -= 0.2;
		waypoints.push_back(target_pose1);  // forward

		//target_pose1.position.z -= 0.2;
		//target_pose1.position.y += 0.2;
		target_pose1.position.x -= 0.2; //right
		waypoints.push_back(target_pose1);


		target_pose1.position.z += 0.2;
		waypoints.push_back(target_pose1);

	move_group.setMaxVelocityScalingFactor(0.1);

	moveit_msgs::RobotTrajectory trajectory;
	const double jump_threshold = 0.0;
	const double eef_step = 0.01;
	ROS_INFO("OKAY what's going on 0?");
	double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
	ROS_INFO("OKAY what's going on?");
	ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (cartesian path) (%.2f%% acheived)", fraction * 100.0);
	ROS_INFO("About to sleep");
	sleep(10.0);
	my_plan.trajectory_ = trajectory;
	ROS_INFO("Just checking you got here");
        move_group.execute(my_plan);*/

}

} /* namespace */
