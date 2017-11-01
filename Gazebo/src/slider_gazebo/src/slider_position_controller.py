#!/usr/bin/env python


import rospy
import math

from std_msgs.msg import Float64
from math import sin,cos,atan2,sqrt,fabs


#Define a RRBot joint positions publisher for joint controllers.
def slider_joint_positions_publisher():

	#Initiate node for controlling 4 joints positions.
	rospy.init_node('slider_joint_positions_node', anonymous=True)

	#Define publishers for each joint position controller commands.
	pub1 = rospy.Publisher('/slider_gazebo/left_base_joint_position_controller/command', Float64, queue_size=10)
	pub2 = rospy.Publisher('/slider_gazebo/base_to_left_leg_position_controller/command', Float64, queue_size=10)
	pub3 = rospy.Publisher('/slider_gazebo/right_base_joint_position_controller/command', Float64, queue_size=10)
	pub4 = rospy.Publisher('/slider_gazebo/base_to_right_leg_position_controller/command', Float64, queue_size=10)


	rate = rospy.Rate(1000) #1000 Hz

	#While loop to have joints follow a certain position, while rospy is not shutdown.
	i = 0
	while not rospy.is_shutdown():

		#Have each joint follow a sine movement of sin(i/100).
		sine_movement = sin(i/500.)

		#Publish the same sine movement to each joint.
		pub1.publish(sine_movement)
		pub2.publish(sine_movement)
		pub3.publish(sine_movement)
		pub4.publish(sine_movement)

		i = i+1 #increment i

		rate.sleep() #sleep for rest of rospy.Rate(100)


#Main section of code that will continuously run unless rospy receives interuption (ie CTRL+C)
if __name__ == '__main__':
	try: slider_joint_positions_publisher()
	except rospy.ROSInterruptException: pass