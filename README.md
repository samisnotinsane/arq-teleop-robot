# Revolute Joint controller for Rift (RJcR)

# [<img src="https://github.com/samisnotinsane/arq-teleop-robot/blob/sameen_development/screenshots/gzsim-scene-overview.png" width="480" alt ="RJcR Gazebo simulation"/>](https://github.com/samisnotinsane/arq-teleop-robot/tree/sameen_development) #

RJcR implements a custom robot in [Gazebo](http://gazebosim.org/) which features a revolute joint as its neck and stereo camera for capturing images. It also comes with a [Unity](https://unity3d.com/) client designed for the [Oculus Rift](https://www.oculus.com/rift/) which receives an image stream from the simulated robot and allows teleoperation of simulated robot neck through head tracking on the Rift.


## Getting Started
These instructions will get you a copy of this prototype up and running on your local machine for development and testing. 

### Prerequisites
A full install of ROS-Kinetic is required. We have tested our software on Ubuntu 16.04.4 LTS and we recommend that you use this version too. 

* [ROS-Kinetic](http://wiki.ros.org/kinetic) - Robot control middleware.
* [Gazebo](http://gazebosim.org/download) - An open source robot simulation engine. Use version 7.1 as compatibility with latest version has not been tested.

**Caution for VM users!**
Due to a rendering bug in Gazebo, camera images captured in simulation cannot be streamed not viewed when running this software in VirtualBox. We have not tested with VMWare, mileage may vary.


### Installing
We assume you have installed the prerequisites by following the instructions of the appropriate vendor. After this step is complete, you must have your environment set up to work with ROS. Run the following if you haven't done so already as part of ROS installation tutorial. This will allow you to run ROS commands such as `roscd`, `roslaunch`, `rosrun` from any terminal without having to source the `/kinetic/setup.bash` file each time you open a new terminal.

```
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

On your Ubuntu machine, clone this repository then make sure you are using this branch.

```
git clone https://github.com/samisnotinsane/arq-teleop-robot.git
git checkout sameen_development
```

Next, navigate into `arq-teleop-robot/catkin_ws` directory and compile all code by running:

```
catkin_make
```
Note: You must run `catkin_make` from the `catkin_ws` folder.







