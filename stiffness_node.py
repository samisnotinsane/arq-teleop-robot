#!/usr/bin/env python
import argparse
import sys
import copy
import rospy
import geometry_msgs.msg
import shape_msgs.msg
import numpy as np
from leap_motion.msg import leapros
from std_msgs.msg import String
from std_msgs.msg import Float64

dist_fingers = 0
pub = rospy.Publisher('vibedata',Float64,queue_size=1)

def datasort(leap_msg):
        lm_thumb_pos = leap_msg.thumb_tip
        thumb_pos = np.array([lm_thumb_pos.x, lm_thumb_pos.y, lm_thumb_pos.z])
        lm_index_pos = leap_msg.index_tip
        index_pos = np.array([lm_index_pos.x, lm_index_pos.y, lm_index_pos.z])
        dist_fingers = np.linalg.norm(thumb_pos-index_pos)
        print dist_fingers
        pub.publish(Float64(dist_fingers))

def leap_sub_pub():
    rospy.init_node('stiffness_node',anonymous = True)
    rospy.Subscriber("/leapmotion/data", leapros, datasort, queue_size=1) # Subscribe to the topic and call lm_move each time we receive some input
    
    pub.publish(Float64(dist_fingers))
    rospy.spin()

if __name__ == '__main__':
    try:
        leap_sub_pub()
    except rospy.ROSInterruptException:
        pass