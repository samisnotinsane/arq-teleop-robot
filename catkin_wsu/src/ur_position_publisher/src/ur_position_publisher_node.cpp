#include <ros/ros.h>
//#include <std_msgs/String.h>
#include "geometry_msgs/Pose.h"


int main(int argc, char **argv) {
        ros::init(argc, argv, "ur_position_publisher_node");
        ros::NodeHandle nh;
        ros::Publisher positionPublisher =
                nh.advertise<geometry_msgs::Pose>("/positioner/position", 1);
        ros::Rate loopRate(3000);

        unsigned int count = 0;
        while (ros::ok()) {
                //std_msgs::String message;
                //message.data = "nothing " + std::to_string(count);
		//rostopic pub /positioner/position geometry_msgs/Pose -- '[0.4, -0.4, 0.3]' '[0.0, 0.0, 0.0, 0.0]'
		geometry_msgs::Pose target_pose1;
		target_pose1.orientation.w = 0.5;
                target_pose1.position.x = 0.4;
                target_pose1.position.y = -0.4;
                target_pose1.position.z = 0.2;
                //ROS_INFO_STREAM(message.data);
                positionPublisher.publish(target_pose1);
                ros::spinOnce();
                loopRate.sleep();
                count++;
        }
        return 0;
}

