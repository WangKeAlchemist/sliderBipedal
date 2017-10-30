#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/JointState.h"
#include <sstream>
float q5l, q6l, q2l, q1l, q3l, q4l, q6r, q5r, q2r, q1r, q3r, q4r, q_tr_roll, q_tr_yaw;
void chatterCallback(const sensor_msgs::JointState::ConstPtr& jjs) // this line has been edited by adding "::" between ContactState and ConstPtr&
{

    q6l = jjs->position[0];
    q5l = jjs->position[1];
    q2l = jjs->position[2];
    q1l = jjs->position[3];
    q3l = jjs->position[4];
    q4l = jjs->position[5];
    q6r = jjs->position[6];
    q5r = jjs->position[7];
    q2r = jjs->position[8];
    q1r = jjs->position[9];
    q3r = jjs->position[10];
    q4r = jjs->position[11];
    q_tr_roll = jjs->position[12];
    q_tr_yaw = jjs->position[13];
    //std::stringstream ss;
    //ss << a;
    //ROS_INFO("The size of recieved ContactState message is: %f", a);
    //ROS_INFO("The size of recieved ContactState message is: %");

    // double z = cs->states[0].total_wrench.force.z; // this line has been commented due to this error : ‘const struct gazebo_msgs::ContactState_<std::allocator<void> >’ has no member named ‘states’
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("mhr/joint_states", 1000, chatterCallback);

    ros::Publisher pub_q5l = n.advertise<std_msgs::Float32>("q5l",1000);
    ros::Publisher pub_q6l = n.advertise<std_msgs::Float32>("q6l",1000);
    ros::Publisher pub_q2l = n.advertise<std_msgs::Float32>("q2l",1000);
    ros::Publisher pub_q1l = n.advertise<std_msgs::Float32>("q1l",1000);
    ros::Publisher pub_q3l = n.advertise<std_msgs::Float32>("q3l",1000);
    ros::Publisher pub_q4l = n.advertise<std_msgs::Float32>("q4l",1000);
    ros::Publisher pub_q6r = n.advertise<std_msgs::Float32>("q6r",1000);
    ros::Publisher pub_q5r = n.advertise<std_msgs::Float32>("q5r",1000);
    ros::Publisher pub_q2r = n.advertise<std_msgs::Float32>("q2r",1000);
    ros::Publisher pub_q1r = n.advertise<std_msgs::Float32>("q1r",1000);
    ros::Publisher pub_q3r = n.advertise<std_msgs::Float32>("q3r",1000);
    ros::Publisher pub_q4r = n.advertise<std_msgs::Float32>("q4r",1000);
    ros::Publisher pub_q_tr_roll = n.advertise<std_msgs::Float32>("q_tr_roll",1000);
    ros::Publisher pub_q_tr_yaw = n.advertise<std_msgs::Float32>("q_tr_yaw",1000);
    ros::Publisher pub = n.advertise<std_msgs::Float32>("q4l",1000);
    std_msgs::Float32 q5l_msg;
    std_msgs::Float32 q6l_msg;
    std_msgs::Float32 q2l_msg;
    std_msgs::Float32 q1l_msg;
    std_msgs::Float32 q3l_msg;
    std_msgs::Float32 q4l_msg;
    std_msgs::Float32 q6r_msg;
    std_msgs::Float32 q5r_msg;
    std_msgs::Float32 q2r_msg;
    std_msgs::Float32 q1r_msg;
    std_msgs::Float32 q3r_msg;
    std_msgs::Float32 q4r_msg;
    std_msgs::Float32 q_tr_roll_msg;
    std_msgs::Float32 q_tr_yaw_msg;
  //msg.data = "Hello"; // this line has been edited due to this error: conversion from ‘const char [6]’ to non-scalar type ‘std_msgs::String’ requested
  
  ros::Rate loop_rate(1000);

    while (ros::ok())
    {
        q5l_msg.data = q5l;
        q6l_msg.data = q6l;
        q2l_msg.data = q2l;
        q1l_msg.data = q1l;
        q3l_msg.data = q3l;
        q4l_msg.data = q4l;
        q6r_msg.data = q6r;
        q5r_msg.data = q5r;
        q2r_msg.data = q2r;
        q1r_msg.data = q1r;
        q3r_msg.data = q3r;
        q4r_msg.data = q4r;
        q_tr_roll_msg.data = q_tr_roll;
        q_tr_yaw_msg.data = q_tr_yaw;

        pub_q5l.publish(q5l_msg);
        pub_q6l.publish(q6l_msg);
        pub_q2l.publish(q2l_msg);
        pub_q1l.publish(q1l_msg);
        pub_q3l.publish(q3l_msg);
        pub_q4l.publish(q4l_msg);
        pub_q6r.publish(q6r_msg);
        pub_q5r.publish(q5r_msg);
        pub_q2r.publish(q2r_msg);
        pub_q1r.publish(q1r_msg);
        pub_q3r.publish(q3r_msg);
        pub_q4r.publish(q4r_msg);
        pub_q_tr_roll.publish(q_tr_roll_msg);
        pub_q_tr_yaw.publish(q_tr_yaw_msg);


        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

