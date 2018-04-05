#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Joy.h>

/* 2018 - Sameen Islam - Queen Mary University of London.
 * Publishes position of where the neck joint should move to. 
 */

ros::Publisher publisher_object;
void joyCallback(const sensor_msgs::Joy::ConstPtr& msg);

int main(int argc, char **argv) {
  ros::init(argc, argv, "joint_neck_publisher");
  ros::NodeHandle n;
  publisher_object = 
	  n.advertise<std_msgs::Float64>("joint_head_to_base_position_controller/command", 1);
  ros::Subscriber joy_subscriber = n.subscribe("joy", 10, joyCallback);

  std_msgs::Float64 input_float;
  input_float.data = 0.0;

  //ros::Rate naptime(1.0);  // node will update at 1Hz.
  /*
  while(ros::ok()) {
    // input_float.data += 0.1;
    // publisher_object.publish(input_float);
	  ros::spinOnce();
	  naptime.sleep();
  }
  */
  ros::spin();
}

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
	  // ROS_INFO("I heard: [%f]", msg->axes[0]);
	  // ROS_INFO("I heard: [%f]", msg->axes[1]);
	  std_msgs::Float64 n_msg;
	  n_msg.data = msg->axes[0];
	  publisher_object.publish(n_msg);
	  ros::spinOnce();
}
