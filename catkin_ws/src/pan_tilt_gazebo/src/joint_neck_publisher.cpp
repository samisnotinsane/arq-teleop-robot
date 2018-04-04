#include <ros/ros.h>
#include <std_msgs/Float64.h>

/* 2018 - Sameen Islam - Queen Mary University of London.
 * Publishes position of where the neck joint should move to. 
 */

int main(int argc, char **argv) {
  ros::init(argc, argv, "joint_neck_publisher");
  ros::NodeHandle n;
  ros::Publisher publisher_object = n.advertise<std_msgs::Float64>("joint_head_to_base_position_controller/command", 1);
  std_msgs::Float64 input_float;
  input_float.data = 0.0;

  ros::Rate naptime(1.0);  // node will update at 1Hz.

  while(ros::ok()) {
    input_float.data += 0.1;
    publisher_object.publish(input_float);
    naptime.sleep();
  }
}

