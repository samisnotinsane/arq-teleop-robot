#!/bin/sh
rosrun xacro xacro --inorder -o pan_tilt.urdf pan_tilt.urdf.xacro
echo "URDF generated into file: pan_tilt.urdf"