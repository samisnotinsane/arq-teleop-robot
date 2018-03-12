## Touch it, move it, feel it; enhanced object understanding through robot action
A simulation environment in gazebo equipped for exploring image classification of objects as they are moved about with a UR5 arm.


# Setting Up Your PC
## Using A Virtual Environment
I recommend using [Virtualbox](https://www.virtualbox.org/wiki/Downloads) - Just be sure to install the guest additions and extension packs for your system if they are required.

You can download [this ova](https://drive.google.com/file/d/1YD4u1dLc_PCFunNFaEXeKqiDsUFzpHGd/view?usp=sharing), which aims to have all the required software plus the ROS packages used for the simulation. It currently has the following installed and will be updated as work progresses:

- [Ubuntu 14.04 64-bit PC(AMD64)](http://old-releases.ubuntu.com/releases/14.04.0/)
- [Ros Indigo](http://wiki.ros.org/indigo/Installation/Ubuntu)
- [Virtualenv](https://www.tensorflow.org/install/install_linux#InstallingVirtualenv) *helpful for isolating python environments when working with tensorflow. I advice doing all work and installations in this environment.
- [Tensorflow](https://www.tensorflow.org/install/install_linux) *note that Tensorflow requires 64-bit architectures.
- [universal_robot](http://wiki.ros.org/universal_robot)
- [moveit!](http://moveit.ros.org/install/)

The following are for external images via a webcam, and a coding IDE, and multi-tab terminal.
- [cv_camera](http://wiki.ros.org/cv_camera) `$ sudo apt-get install ros-indigo-cv-camera`
- [cv_bridge and opencv3](http://wiki.ros.org/cv_bridge) *should already be installed as dependencies of cv_camera
- [droidcam](https://www.dev47apps.com/) *may require android tools (adb) *not necessary if your webcam works *
- [chrome, git, terminator, java8 & Eclipse -follow link for how to setup eclipse for ros package development](https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/how_to_setup_developer_pc.pdf)


# Starting Up Your Environment
- Currently you can load a ur5 arm in one of the default worlds provided, and use the moveit motion planner to plan its movements.
- Also available is a tensorflow model for classifying images of numbers that are fed in through a webcam. It will be retrained to classify objects that are placed in the gazebo environment, and the image feed will be redirected to come from inside the gazebo environment.

## Starting up UR5 in an empty world and using the moveit rviz planning interface
[See video of how to do this here](https://1drv.ms/v/s!AjMXzGx2ztdEgX4J5WDuIAtWRz-5) or:

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

