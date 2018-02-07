#!/bin/sh

rosrun xacro xacro --inorder -o kinect.urdf kinect.urdf.xacro
echo "URDF generated into file: kinect.urdf"