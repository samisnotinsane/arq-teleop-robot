

To use this package, do the following:
1. `catkin_make`
2. `source devel/setup.bash`
3. `roslaunch kinect_bridge kinect_bridge`

This will publish ROS topics which can be viewed using 'rostopic list' and the image can be viewed with `rosrun image_view image_view image:=<topic name>`