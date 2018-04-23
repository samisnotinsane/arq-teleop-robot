# Revolute Joint controller for Rift (RJcR)

# [<img src="https://github.com/samisnotinsane/arq-teleop-robot/blob/sameen_development/screenshots/gzsim-scene-overview.png" width="480" alt ="RJcR Gazebo simulation"/>](https://github.com/samisnotinsane/arq-teleop-robot/tree/sameen_development) #

# [<img src="https://github.com/samisnotinsane/arq-teleop-robot/blob/sameen_development/screenshots/robot-eye-stream-scene.PNG" width="480" alt ="RJcR Unity VR application"/>](https://github.com/samisnotinsane/arq-teleop-robot/blob/sameen_development/rift-ros-win32client.unitypackage) #


RJcR implements a custom robot in [Gazebo](http://gazebosim.org/) which features a revolute joint as its neck and stereo camera for capturing images. It also comes with a [Unity](https://unity3d.com/) client designed for the [Oculus Rift](https://www.oculus.com/rift/) which receives an image stream from the simulated robot and allows teleoperation of simulated robot neck through head tracking on the Rift.


## Getting Started
These instructions will get you a copy of this prototype up and running on your local machine for development and testing. 

### Prerequisites
You will need two PCs, one that acts as a client and the other, as server. 

**Development server specifications (min requirements may be lower)**
* Processor: Intel® Core™ i7-8700 CPU @ 3.20GHz × 12 
* Memory: 15.4 GiB
* Graphics: GeForce GTX 1070/PCIe/SSE2
* OS: 64-bit Ubuntu 16.04.4 LTS
* Storage capacity: 2.9 TB

**Required software**
* [ROS-Kinetic](http://wiki.ros.org/kinetic) - Robot control middleware.
* [Gazebo](http://gazebosim.org/download) - An open source robot simulation engine. Use version 7.1 as compatibility with latest version has not been tested.

**Caution for VM users!**
Due to a rendering bug in Gazebo, camera images captured in simulation cannot be streamed nor viewed when running this software in VirtualBox (nature of error you will see is documented in issue #1). We have not tested with VM Ware - your mileage may vary (in which case let us know by recording an issue). All thigs considered, we recommend using a physical machine for best performance.

**Client specifications (min requirements may be lower)**
* Processor: Intel® Core™ i7-6700K CPU @ 4.00GHz 4.00GHz
* Memory: 15.0 GiB
* Graphics: Intel® HD Graphics 530 8271 MB
* OS: 64-bit Windows 10
* Storage capacity: 2 TB

**Required hardware and software**
* [Oculus Rift](https://www.oculus.com/rift/) - VR headset used for telepresence and robotic teleoperation through head orientation tracking (only compatible with Windows).
* [Unity](https://unity3d.com/) - A multi-platform game engine. Required for running VR application on the Rift headset.


### Installation
For both machines, we assume you have installed the prerequisites as specified in the previous section by following the instructions of the appropriate vendor.

**Server**
Ensure that your environment set up to work with ROS. Run the following if you haven't done so already as part of ROS installation tutorial. This will allow you to run ROS commands such as `roscd`, `roslaunch`, `rosrun` from any terminal without having to source the `/kinetic/setup.bash` file each time you open a new terminal.

```
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

From your home folder, clone this repository and make sure you are using this branch.

```
git clone https://github.com/samisnotinsane/arq-teleop-robot.git
git checkout sameen_development
```

Next, navigate into the Catkin workspace, compile all code.

```
cd ~/arq-teleop-robot/catkin_ws
catkin_make
```
Important: You must run `catkin_make` from the `catkin_ws` folder.

You may want to avoid sourcing the workspace each time you open a new terminal, in which case, execute the following:

```
echo "source ~/arq-teleop-robot/catkin_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

Followed by...
```
echo "export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:~/arq-teleop-robot/catkin_ws/devel/lib" >> ~/.bashrc
source ~/.bashrc
```

Finally, start the simulation and prepare the server for simulation based robot teleop by running:

```
roslaunch pan_tilt_gazebo pan_tilt_xacro.launch
```

This will open two extra terminal windows. These are ROS nodes listening for keyboard commands for moving the turtlebot. You can drive around the turtlebot by keeping the terminal window `[ROSNODE] key_publisher.py` focused and using the following controls:

* `w` - drive forward
* `a` - rotate left
* `d` - rotate right

Ensure that port `:9090` is not blocked as the client will need to establish a WebSocket connection for telepresence and teleoperation through the VR headset. Also keep the ip address of the server machine handy as you will need to enter this into Unity. This is the `inet addr` if you're using `ifconfig`.



