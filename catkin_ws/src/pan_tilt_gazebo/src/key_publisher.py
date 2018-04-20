#!/usr/bin/env python
import sys, select, tty, termios
import rospy
from std_msgs.msg import String

if __name__ == '__main__':
    key_pub = rospy.Publisher('keys', String, queue_size=1)
    rospy.init_node("turtlebot_keyboard_driver")
    print("[ROSNODE] key_publisher.py")
    rate = rospy.Rate(100)
    print("Keep this terminal in focus to control the turtlebot in Gazebo.\nClose after terminating simulation!")
    old_attr = termios.tcgetattr(sys.stdin)
    tty.setcbreak(sys.stdin.fileno())
    print("Press Ctrl-C to exit...")
    
    while not rospy.is_shutdown():
        if select.select([sys.stdin], [], [], 0)[0] ==[sys.stdin]:
            key_pub.publish(sys.stdin.read(1))
        rate.sleep()
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_attr)
