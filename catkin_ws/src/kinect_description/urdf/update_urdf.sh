#!/bin/sh

rosrun xacro xacro --inorder -o kineck.urdf kinect.urdf.xacro
echo "URDF generated into file: kinect.urdf"