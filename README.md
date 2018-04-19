# arq-teleop-robot

# Wael Khawam's Branch

Inside the robot mind: Accessing 3D scene reconstruction through Virtual Reality technologies

# 1. Requirements  

- Ubuntu 16.04
- Kinect v2
- Robot Operating System
- libfreenect2

# 2. Cloning this branch

1. `git clone https://github.com/samisnotinsane/arq-teleop-robot.git`
2. Navigate into the folder.
3. `git checkout wael_development`. You are now in this branch
4. You can now use the project in the way you like, build the workspace with catkin_make

# 4. Included

1. Modified version of iai_kinect2.
2. Interface with different features such as basic object location and edge detection.

To use the packages, do the following from inside the catkin_ws folder:
1. `catkin_make`
2. `source devel/setup.bash`
3. either `roslaunch kinect2_bridge kinect2_bridge`
    or `rosrun object_locator object_locator <type>`

    where `<type>` can be `color`, `depth`, `both`, `objects_image` or `edges_depth`