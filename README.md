# Touch it, move it, feel it; enhanced object understanding through robot action
A simulation setup in gazebo called Sen, equipped for testing data-gathering software which are intended for use on a UR5 arm affixed with an Allegro hand end-effector.

### Features

An interface to control a UR5 arm.

An interface to a simulated RGB-D camera through which images taken from within the simulation environment can be saved. 

Planned: An interface to simulated tactile sensors through which contact and force measurements taken from within the simulation environment can be saved.  

A simple interface to interact with Convolutional Neural Networks.

# Setting Up Your PC

I highly recommend using a native install of Ubuntu but [Virtualbox](https://www.virtualbox.org/wiki/Downloads) can also be used for getting started quickly, however note that image streaming from Gazebo in a VM does not work, and there is a consistent error with the universal_robot ros package when it is run in a VM. The error is: ERROR: cannot launch node of type [controller_manager/controller_manager]: controller_manager. Also, if using Virtualbox be sure to install the guest additions and extension packs for your Virtualbox if they are required.

A VM will be very problematic but if it is the only option you can download [this ova](https://drive.google.com/open?id=1xC5ZKkmgtbGCBI5yzFGHQGbfDLVZCa3s). The password is simply ```password```. It currently has the following installed:

- [Ubuntu 16.04 64-bit PC(AMD64)](http://old-releases.ubuntu.com/releases/14.04.0/)
- [Ros Kinetic](http://wiki.ros.org/kinetic/Installation/Ubuntu)
- Git
- Terminator
- [Catkin command line tools](http://catkin-tools.readthedocs.io/en/latest/installing.html#installing-on-ubuntu-with-apt-get) - for using catkin build


## Clone This Repository

```git clone -b Nnadozie_ https://github.com/samisnotinsane/arq-teleop-robot.git```

## Need To Have
- Everything installed in the OVA listed above, except terminator. See [this guide](https://www.ethz.ch/content/dam/ethz/special-interest/mavt/robotics-n-intelligent-systems/rsl-dam/ROS2017/how_to_setup_developer_pc.pdf) for instructions on installing them.
- [Virtualenv](https://www.tensorflow.org/install/install_linux#InstallingVirtualenv) *helpful for isolating python environments when working with tensorflow. I advice doing all work and installations in this environment.
- [Tensorflow](https://www.tensorflow.org/install/install_linux) *note that Tensorflow requires 64-bit architectures.
- After installing tensorflow in virtualenv make sure you are NOT in virtualenv then install moveit!:
- [moveit!](http://moveit.ros.org/install/)

# Starting Up Your Environment

Open a new terminal

## Building the required packages
The following must be built and sourced in the order given:

- from arq-teleop-robot run ```cd cam_ws/```
- run ```catkin_make```
- run ```source devel/setup.bash```

- from arq-teleop-robot run ```cd ur_workspace/```
- run ```catkin_make```
- run ```source devel/setup.bash```

- from arq-teleop-robot ```cd catkin_wsu/```
- run ```sudo apt-get install ros-kinetic-moveit-visual-tools```
- run ```catkin build ur_positioner_kinetic```
- run ```source devel/setup.bash```

## 0. To Source Built Packages Each Time a New Terminal is Opened

Be sure to change <path to cam_ws> to the actual path

- ```echo "source <path to cam_ws>/devel/setup.bash" >> ~/.bashrc```
- ```echo "source <path to ur_workspace>/devel/setup.bash" >> ~/.bashrc```
- ```echo "source <path to catkin_wsu>/devel/setup.bash" >> ~/.bashrc```  

# Running Sen

Open a new terminal so your environments are sourced

## 1. Just Sen Publishing Images to a Topic

- If you ignored steps in 0, source the cam_ws and ur_workspace environments ```source <path to cam_ws>/devel/setup.bash``` ```source <path to ur_workspace>/devel/setup.bash```
- Run ```roslaunch rrbot_gazebo rrbot_world.launch```
- to view images being published in a new tab run ```rqt_image_view```
- select /rrbot/camera1/image_raw when the viewing terminal opens
- The camera robot can be moved around in Gazebo for different points of view

## 2. Using Sen's UR5 Keyboard Interface
- Run steps in 1.
- In a new terminal make sure the catkin_wsu and ur_workspace environments are sourced ```source <path to catkin_wsu>/devel/setup.bash``` ```source <path to ur_workspace>/devel/setup.bash```
- Run ```roslaunch ur5_moveit_config ur5_moveit_planning_execution.launch sim:=true limited:=true```
- In a new terminal launch the ur_positioner_kinetic node ```roslaunch ur_positioner_kinetic ur_positioner_kinetic.launch```
- In yet another terminal run ```python <path to arq-teleop-robot>/catkin_wsu/src/ur_keyboard_controller.py```
- If there is a collision with the ground plane start again from step 1, otherwise the UR5 arm should have moved into a starting position.

![image](https://user-images.githubusercontent.com/15310842/39326494-152340b2-498d-11e8-8e26-bfd28a7611b0.png)

### Keyboard usage
u for up on the blue axis

j for down on the blue axis

w for up on the red axis

s for down on the red axis

a for left on the green axis

d for right on the green axis

x to exit

## Automatically Saving Sen's Images and Classifying them
- Run steps in 1.
- Run ```mkdir <path to arq-teleop-robot>/cam_ws/src/<images>```
- Open the file called classify.sh in arq-teleop-robot/cam_ws/images/
- Modify the absolute path /home/lorenzo/doz in the argument to --image_file, to reflect your computers absolute path
- navigate to <path to arq-teleop-robot>/cam_ws/src
- Run ```source <your_path_to_tensorflow>/bin/activate```
- You should see ```(tensorflow) qmul@qmul-VirtualBox:~$``` in place of just ```qmul@qmul-VirtualBox:~$```
- Run ```python classify_gazebo_image.py```
- The classification output is stored in <path to arq-teleop-robot>/cam_ws/src/classification.log
- The first time it runs expect to see the logs for Downloading inception. I suggest renaming the images folder, creating a new images folder and renaming the classification.log file each time a session is completed.






