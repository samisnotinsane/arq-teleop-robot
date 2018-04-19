# arq-teleop-robot
ROS based robot for first-person embodiment for robotic telepresence using an arm. 

Pre-requisites for enabling Wireless Communication:
1) Rosserial package installed
2) Arduino development environment
3) Simblee board package installed on the Arduino dev env

Use of Wireless Communication:
1) Ensure that the code for data glove and server-side simblee (SSS) are compiled and uploaded onto their respective Simblee lilypads
2) Create a ROS package inside your catkin workspace (any name is fine, this is where the rawdatahandler.cpp will go) with roscpp dependecy
3) Place processing node code here
4) Run "catkin_make" in catkin workspace
5) Once the node is compiled enable roscore in a terminal
6) In another terminal run the processing node via rosrun (ensure that you are inside the folder with the processing node)
7) In another terminal run the server-side simblee via "rosrun rosserial_python serial_node.py"
8) Send data via "rostopic pub vibe_data std_msgs/Int32 [x]" or "rostopic pub finger_data std_msgs/Int32 [x]" for vibe level or finger respectively, where [x] is the desired message

Pre-requisites for enable Stiffness Simulation:
1) Rosserial package installed
2) Arduino development environment
3) Simblee board package installed on the Arduino dev env
4) ros leap_motion package installed
5) Leap Motion sdk and dependencies installed details for this can be found in: https://github.com/samisnotinsane/arq-teleop-robot/tree/lukas_development

Use of Stiffness Simulation:
1) Run the line "sudo leapd" in a terminal
2) Run the line "roscore" in a terminal
3) Run the line "rosrun leap_motion sender.py"
4) Ensure that terminal is in the directory with the processing node and run the line "./stiffness_node.py"
5) Run the line "rosrun rosserial_python serial_node.py"
6) Run the line "LeapControlPanel" to visualise what the Leap Motion is processing
7) "rostopic pub mapping std_msgs/Int64 [x]" to choose the desired object


Additional notes:
Ensure that SDK is in the home directory, run the line "export PYTHONPATH=$PYTHONPATH:$HOME/LeapSDK/lib:$HOME/LeapSDK/lib/x64"
If the serial port is not enabed then to initialise serial port on linux run in terminal:
sudo usermod -a -G dialout burarara
sudo chmod a+rw /dev/ttyUSB0
