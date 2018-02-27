#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"

#include <sstream>

float forceVariable = 0;
int fingerVariable = 0;
float messageVariable = 0;
int vibeStatus[] = {0,0,0,0,0,0};


void vibeDataCallback(const std_msgs::Int32 msg){
	ROS_INFO("Obtained: [%d]Newtons", msg.data);
	if(msg.data==0){
		forceVariable = 0;
	}
	else if(msg.data<=50){
		forceVariable = 0.1;
	}
	else if(msg.data<=150 && msg.data>=51){
		forceVariable = 0.2;
	}
	else if(msg.data<=300 && msg.data>=151){
		forceVariable = 0.3;
	} 
	else if(msg.data>=301){
		forceVariable = 0.4;
	}

}

void fingerDataCallback(const std_msgs::Int32 msg){
	ROS_INFO("On the [%d] finger", msg.data);
	if(msg.data==0){
		fingerVariable = 0;
	}
	else if(msg.data==1){
		fingerVariable = 1;
	}
	else if(msg.data==2){
		fingerVariable = 2;
	}
	else if(msg.data==3){
		fingerVariable = 3;
	}
	else if(msg.data==4){
		fingerVariable = 4;
	}
	else if(msg.data==5){
		fingerVariable = 5;
	}
 
}

//This function is used to update the status of the vibes and check it at the same time

int main(int argc, char **argv){
	ros::init(argc, argv, "rawdatahandler");
	ros::NodeHandle n;
	ros::Subscriber sub1 = n.subscribe("vibe_data", 1000, vibeDataCallback);
	ros::Subscriber sub2 = n.subscribe("finger_data", 1000, fingerDataCallback);
	ros::Publisher chatter_pub = n.advertise<std_msgs::Float32>("ble_com", 1000);

  	ros::Rate loop_rate(10);   

  	int count = 0;
  	std_msgs::Float32 msg;

  	while (ros::ok())
  	{
  		messageVariable = fingerVariable + forceVariable;
    	msg.data = messageVariable;	
  			
    	chatter_pub.publish(msg);

    	ros::spinOnce();

    	loop_rate.sleep();
    	++count;
  }


  ros::spin();

	return 0;
}