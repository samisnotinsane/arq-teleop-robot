#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char **argv) {
        ros::init(argc, argv, "ur_position_publisher_node");
        ros::NodeHandle nh;
        ros::Publisher positionPublisher =
                nh.advertise<std_msgs::String>("position", 1);
        ros::Rate loopRate(10);

        unsigned int count = 0;
        while (ros::ok()) {
                std_msgs::String message;
                message.data = "nothing " + std::to_string(count);
                //ROS_INFO_STREAM(message.data);
                positionPublisher.publish(message);
                ros::spinOnce();
                loopRate.sleep();
                count++;
        }
        return 0;
}

