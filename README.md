# Touch it, move it, feel it; enhanced object understanding through robot action
A simulation environment in gazebo equipped for testing data gathering software which is intended for use on a UR5 arm affixed with an Allegro hand end effector

### Features

An interface to control a simulated robotic arm and multi-digit anthropomorphic robotic hand. 

An interface to a simulated RGB-D camera through which images taken from within the simulation environment can be saved. 

Planned: An interface to simulated tactile sensors through which contact and force measurements taken from within the simulation environment can be saved.  

A simple interface to interact with Convolutional Neural Networks.

# Setting Up Your PC

I recommend using [Virtualbox](https://www.virtualbox.org/wiki/Downloads) for getting started quickly but note that image streaming from Gazebo in a VM does not work and be sure to install the guest additions and extension packs for your system if they are required.

You can download [this ova](https://drive.google.com/open?id=1xC5ZKkmgtbGCBI5yzFGHQGbfDLVZCa3s). The password is simply ```password```.. It currently has the following installed:

- [Ubuntu 14.04 64-bit PC(AMD64)](http://old-releases.ubuntu.com/releases/14.04.0/)
- [Ros Kinetic](http://wiki.ros.org/kinetic/Installation/Ubuntu)
- pip 10.0.1
- Git
- Terminator
- [Catkin command line tools](http://catkin-tools.readthedocs.io/en/latest/installing.html#installing-on-ubuntu-with-apt-get) - for using catkin build


## Clone This Repository

```git clone -b Nnadozie_ https://github.com/samisnotinsane/arq-teleop-robot.git```

## Need To Have
- Everything installed in the OVA listed above, except terminator. See [this guide](https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/how_to_setup_developer_pc.pdf). Instructions for updating pip are contained in the Virtualenv installation guide below.
- [Virtualenv](https://www.tensorflow.org/install/install_linux#InstallingVirtualenv) *helpful for isolating python environments when working with tensorflow. I advice doing all work and installations in this environment.
- [Tensorflow](https://www.tensorflow.org/install/install_linux) *note that Tensorflow requires 64-bit architectures.
- [universal_robot](http://wiki.ros.org/universal_robot) -- in kinetic this has to be built from source which has been included in this repo under ur_workspace. Simply navigate to /ur_workspace and run ```catkin_make```
- [moveit!](http://moveit.ros.org/install/)

## To Re-Source Your Environment Each Time a New Terminal is Opened

```echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc``` to source your kinetic environment. This also sources moveit!
change <your_path_to_tensorflow> to your actual path to tensorflow
```echo "source <your_path_to_tensorflow>/bin/activate" >> ~/.bashrc``` for bash, sh, ksh, or zsh users
```echo "source <your_path_to_tensorflow>/bin/activate.csh" >> ~/.bashrc``` for csh or tcsh users

Now when you open a new terminal you should see ```(tensorflow) qmul@qmul-VirtualBox:~$``` 

# Starting Up Your Environment
## Building the required packages
The following must be built and sourced in the order given:

- from arq-teleop-robot ```cd cam_ws/```
- run catkin_make
- run ```source devel/setup.bash```

- If you didn't do so above, from arq-teleop-robot ```cd ur_workspace/```
- run ```catkin_make```
- run ```source devel/setup.bash```

- from arq-teleop-robot ```cd catkin_wsu/```
- run ```sudo apt-get install ros-kinetic-moveit-visual-tools```
- run ```catkin build ur_positioner_kinetic```
- run ```source devel/setup.bash```

**installed ros control

## To Source Built Packages Each Time a New Terminal is Opened

echo "source <path to cam_ws>/devel/setup.bash" >> ~/.bashrc
echo "source <path to ur_workspace>/devel/setup.bash" >> ~/.bashrc
echo "source <path to catkin_wsu>/devel/setup.bash" >> ~/.bashrc
  

# Running Sen

Open a new terminal so your environments are sourced

## Just Sen Publishing Images to a Topic
- from cam_ws






