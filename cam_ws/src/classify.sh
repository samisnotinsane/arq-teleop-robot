#!/bin/bash
#make a call to classify_image.py which runs the image classifier
# --image_file is an argument to classify_image.py which takes an absoulut path to the image to be classified
# --Be sure to modify the absolute path of images to be classified whenever the path changes

python ./models/tutorials/image/imagenet/classify_image.py --image_file /home/lorenzo/doz/arq-teleop-robot/cam_ws/src/images/camera_image.jpeg >> classification.log
