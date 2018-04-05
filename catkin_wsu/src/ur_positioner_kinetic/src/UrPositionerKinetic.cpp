#include "ur_positioner_kinetic/UrPositionerKinetic.hpp"
#include <string>

//#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>

#include <moveit_msgs/DisplayTrajectory.h>
#include <tf/transform_listener.h>


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

void UrPositionerKinetic::topicCallback(const geometry_msgs::Pose target_pose1)
{
  ROS_INFO("Got in callback: 1");
}

} /* namespace */

