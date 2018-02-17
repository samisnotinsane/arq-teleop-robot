#include "ros/ros.h"
#include "std_msgs/Int32.h"

#include <sstream>

int messageVariable = 0;

void rawdataCallback(const std_msgs::Int32 msg){
	//Edit data here
	ROS_INFO("Obtained: [%d]", msg.data);
	messageVariable = msg.data;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "rawdatahandler");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("raw_data", 1000, rawdataCallback);
	ros::Publisher chatter_pub = n.advertise<std_msgs::Int32>("ble_com", 1000);

  	ros::Rate loop_rate(10);   

  	int count = 0;
  	std_msgs::Int32 msg;

  	while (ros::ok())
  	{

    	msg.data = messageVariable;	

    	chatter_pub.publish(msg);

    	ros::spinOnce();

    	loop_rate.sleep();
    	++count;
  }


  ros::spin();

	return 0;
}