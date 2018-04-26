# Touch it, move it, feel it; enhanced object understanding through robot action
A simulation environment in gazebo equipped for testing data gathering software which is intended for use on a UR5 arm affixed with an Allegro hand end effector

### Features

An interface to control a simulated robotic arm and multi-digit anthropomorphic robotic hand. 

An interface to a simulated RGB-D camera through which images taken from within the simulation environment can be saved. 

Planned: An interface to simulated tactile sensors through which contact and force measurements taken from within the simulation environment can be saved.  

A simple interface to interact with Convolutional Neural Networks.

# Setting Up Your PC

I recommend using [Virtualbox](https://www.virtualbox.org/wiki/Downloads) for getting started quickly but note that image streaming from Gazebo in a VM does not work and be sure to install the guest additions and extension packs for your system if they are required. The password is simply ```password```.

You can download [this ova](https://drive.google.com/open?id=1xC5ZKkmgtbGCBI5yzFGHQGbfDLVZCa3s). It currently has the following installed:

- [Ubuntu 14.04 64-bit PC(AMD64)](http://old-releases.ubuntu.com/releases/14.04.0/)
- [Ros Kinetic](http://wiki.ros.org/kinetic/Installation/Ubuntu)
- pip 10.0.1
- Git
- Terminator
- [Catkin command line tools](http://catkin-tools.readthedocs.io/en/latest/installing.html#installing-on-ubuntu-with-apt-get) - for using catkin build

## Clone This Repository

```git clone -b Nnadozie_ https://github.com/samisnotinsane/arq-teleop-robot.git```

## Need To Install

- [Virtualenv](https://www.tensorflow.org/install/install_linux#InstallingVirtualenv) *helpful for isolating python environments when working with tensorflow. I advice doing all work and installations in this environment.
- [Tensorflow](https://www.tensorflow.org/install/install_linux) *note that Tensorflow requires 64-bit architectures.
- [universal_robot](http://wiki.ros.org/universal_robot) -- in kinetic this has to be built from source which has been included in this repo under ur_workspace. Simply navigate to ur_workspace/src and run ```catkin_make```
- [moveit!](http://moveit.ros.org/install/)


# Starting Up Your Environment

## Starting up the UR5 and Camera bot in an empty Gazebo

In a terminal of your choice (I recommend using terminator)

#### launch the virtualenv environment where tensorflow is installed

`$ source ~/tensorflow/bin/activate`

This can be added to `~/.bashrc` so it runs each time a new tab is opened

To do so simply:

`$ echo "source ~/tensorflow/bin/activate" >> ~/.bashrc`

#### launch UR5 in gazebo

`$ roslaunch ur_gazebo ur5.launch limited:=true`

If you chose to use the ova file provided, it already has UR5 ros packages installed.

#### launch the motion planner and rviz interface

`$ roslaunch ur5_moveit_config ur5_moveit_planning_execution.launch sim:=true limited:=true`

`$ roslaunch ur5_moveit_config moveit_rviz.launch config:=true`

## Running a number classification tensorflow model that interacts with ros nodes

If you chose not to use the provided ova, the source code for the tensorflow model can be found [here](https://github.com/shunchan0677/Tensorflow_in_ROS).

You can watch this [video](https://1drv.ms/v/s!AjMXzGx2ztdEgX9iOoT1-66_13xy), or follow the instructions in that repo to get things running

# Using the packages in this project
There are currently three packages:
#### ur_positioner:

Used to move the UR5 arm to a position given over a topic. The topic can be configured in the package's config.yaml file by updating subscriber_topic, or setting the parameter in the parameter server.

To launch run `roslaunch ur_positioner ur_positioner.launch`

#### ur_position_publisher:

Can be used to publish positions to the ur_positioner when the control loop isn't closed.

To launch run `roslaunch ur_position_publisher ur_position_publisher.launch`

#### ur_world_objects:

Package containing useful objects such as cups and tables.

These can be located using $(find ur_world_objects)/objects/<object_urdf>

