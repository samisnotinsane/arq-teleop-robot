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


	}


	UrPositioner::~UrPositioner() {
	}

	bool UrPositioner::readParameters() {
		if(!nodeHandle_.getParam("subscriber_topic", subscriberTopic_)) return false;
		return true;
	}

	void UrPositioner::topicCallback(geometry_msgs::Pose target_pose1) {
		
		ros::AsyncSpinner spinner(1);
                spinner.start();

		//ROS_INFO("UR5 will move to  [%s]", target_pose1.c_str());
		
                ROS_INFO("Got in callback: 1");
   
                moveit::planning_interface::MoveGroup group("manipulator");

                ROS_INFO("Got in callback: 2");
                moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

                ROS_INFO("Got in callback: 3");
                ros::Publisher display_publisher = nodeHandle_.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);

                ROS_INFO("Got in callback: 4");
                moveit_msgs::DisplayTrajectory display_trajectory;

                ROS_INFO("Got in callback: 5");

                ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
                ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());
                
                group.setPoseTarget(target_pose1);
		
		/*robot_trajectory::RobotTrajectory rt(group.getCurrentState()->getRobotModel(), "manipulator");
		rt.setRobotTrajectoryMsg(*group.getCurrentState(), trajectory);		
		trajectory_processing::IterativeParabolicTimeParameterization iptp;
		bool success = iptp.computeTimeStamps(rt);
		ROS_INFO("Computed time stamp %s",success?"SUCCEDED":"FAILED");
	
		rt.getRobotTrajectoryMsg(trajectory);
		plan.trajectory_ = trajectory;*/

				
	
		ROS_INFO("Got in callback: 5a");
                moveit::planning_interface::MoveGroup::Plan my_plan;
		ROS_INFO("Got in callback: 5b");
                bool success = group.plan(my_plan);

                ROS_INFO("Visualizing plan 1 (pose goal) %s",success?"":"FAILED");
                sleep(4.0);
		//group.execute(plan);
                group.move();
                sleep(5.0);
                ROS_INFO("Got in callback: 6*");

		std::vector<geometry_msgs::Pose> waypoints;

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

		moveit_msgs::RobotTrajectory trajectory;
		//group.setPlanningTime(10.0);
		double fraction = group.computeCartesianPath(waypoints,
                                             0.01,  // eef_step
                                             0.0,   // jump_threshold
                                             trajectory);

		ROS_INFO("Visualizing plan 4 (cartesian path) (%.2f%% acheived)",
      fraction * 100.0);
		sleep(5.0);
		my_plan.trajectory_ = trajectory;
		group.execute(my_plan);
		//group.move();

		/**
		if (1) {
                        ROS_INFO("Visualizing plan 1 (again)");
                        display_trajectory.trajectory_start = my_plan.start_state_;
                        display_trajectory.trajectory.push_back(my_plan.trajectory_);
                        display_publisher.publish(display_trajectory);
                        // Sleep to give Rviz time to visualize the plan. 
                        sleep(5.0);
                }**/


	}	
	
} /*namespace*/

