#pragma once

// ROS
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <memory>
#include <tf/transform_broadcaster.h>

namespace ur_positioner_kinetic {

/*!
 * Main class for the node to handle the ROS interfacing.
 */
class UrPositionerKinetic
{
 public:
  /*!
   * Constructor.
   * @param nodeHandle the ROS node handle.
   */
  UrPositionerKinetic(ros::NodeHandle& nodeHandle);

  /*!
   * Destructor.
   */
  virtual ~UrPositionerKinetic();

 private:
  /*!
   * Reads and verifies the ROS parameters.
   * @return true if successful.
   */
  bool readParameters();

  /*!
   * ROS topic callback method.
   * @param message the received message.
   */
  void topicCallback(geometry_msgs::Pose target_pose1);

  /*!
   * ROS service server callback.
   * @param request the request of the service.
   * @param response the provided response.
   * @return true if successful, false otherwise.
   */
 // bool serviceCallback(std_srvs::Trigger::Request& request,
                       //std_srvs::Trigger::Response& response);

  //! ROS node handle.
  ros::NodeHandle& nodeHandle_;

  //! ROS topic subscriber.
  ros::Subscriber subscriber_;

  //! ROS topic name to subscribe to.
  std::string subscriberTopic_;

  //! ROS service server.
  //ros::ServiceServer serviceServer_;

  //! Algorithm computation object.
  //Algorithm algorithm_;
};

} /* namespace */

