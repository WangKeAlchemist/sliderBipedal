
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <sstream>

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


int main(int argc, char **argv)
{

    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Publisher q_tr_roll_pub = n.advertise<std_msgs::Float64>("/mhr/upper_body_roll_position_controller/command", 1000);
    ros::Publisher q_tr_yaw_pub = n.advertise<std_msgs::Float64>("/mhr/upper_body_yaw_position_controller/command", 1000);
    ros::Publisher q1r_pub = n.advertise<std_msgs::Float64>("/mhr/right_hip_roll_position_controller/command", 1000);
    ros::Publisher q2r_pub = n.advertise<std_msgs::Float64>("/mhr/right_hip_pitch_position_controller/command", 1000);
    ros::Publisher q3r_pub = n.advertise<std_msgs::Float64>("/mhr/right_hip_yaw_position_controller/command", 1000);
    ros::Publisher q4r_pub = n.advertise<std_msgs::Float64>("/mhr/right_knee_position_controller/command", 1000);
    ros::Publisher q5r_pub = n.advertise<std_msgs::Float64>("/mhr/right_ankle_roll_position_controller/command", 1000);
    ros::Publisher q6r_pub = n.advertise<std_msgs::Float64>("/mhr/right_ankle_pitch_position_controller/command", 1000);
    ros::Publisher q1l_pub = n.advertise<std_msgs::Float64>("/mhr/left_hip_roll_position_controller/command", 1000);
    ros::Publisher q2l_pub = n.advertise<std_msgs::Float64>("/mhr/left_hip_pitch_position_controller/command", 1000);
    ros::Publisher q3l_pub = n.advertise<std_msgs::Float64>("/mhr/left_hip_yaw_position_controller/command", 1000);
    ros::Publisher q4l_pub = n.advertise<std_msgs::Float64>("/mhr/left_knee_position_controller/command", 1000);
    ros::Publisher q5l_pub = n.advertise<std_msgs::Float64>("/mhr/left_ankle_roll_position_controller/command", 1000);
    ros::Publisher q6l_pub = n.advertise<std_msgs::Float64>("/mhr/left_ankle_pitch_position_controller/command", 1000);
    ros::Rate loop_rate(1000);

    int count = 0;

    std::ifstream q_inFile;
    q_inFile.open("/home/masoud/catkin_ws/src/mhr/trajectories/FlatNormalWalking.txt");

    std::string L_q;


    while (ros::ok())
    {
        std_msgs::Float64 q_tr_roll;
        std_msgs::Float64 q_tr_yaw;
        std_msgs::Float64 q1r;
        std_msgs::Float64 q2r;
        std_msgs::Float64 q3r;
        std_msgs::Float64 q4r;
        std_msgs::Float64 q5r;
        std_msgs::Float64 q6r;
        std_msgs::Float64 q1l;
        std_msgs::Float64 q2l;
        std_msgs::Float64 q3l;
        std_msgs::Float64 q4l;
        std_msgs::Float64 q5l;
        std_msgs::Float64 q6l;

        getline(q_inFile, L_q);
        std::vector<std::string> elems;
        split(L_q.c_str(), ',', elems);

        std::stringstream ss;

        q1r.data = ::atof(elems[0].c_str());
        q2r.data = ::atof(elems[1].c_str());
        q3r.data = ::atof(elems[2].c_str());
        q4r.data = ::atof(elems[3].c_str());
        q5r.data = ::atof(elems[4].c_str());
        q6r.data = ::atof(elems[5].c_str());

        q1l.data = ::atof(elems[6].c_str());
        q2l.data = ::atof(elems[7].c_str());
        q3l.data = ::atof(elems[8].c_str());
        q4l.data = ::atof(elems[9].c_str());
        q5l.data = ::atof(elems[10].c_str());
        q6l.data = ::atof(elems[11].c_str());

        q_tr_roll.data = ::atof(elems[12].c_str());
        q_tr_yaw.data = -::atof(elems[13].c_str());


        q_tr_roll_pub.publish(q_tr_roll);
        q_tr_yaw_pub.publish(q_tr_yaw);

        q1r_pub.publish(q1r);
        q2r_pub.publish(q2r);
        q3r_pub.publish(q3r);
        q4r_pub.publish(q4r);
        q5r_pub.publish(q5r);
        q6r_pub.publish(q6r);

        q1l_pub.publish(q1l);
        q2l_pub.publish(q2l);
        q3l_pub.publish(q3l);
        q4l_pub.publish(q4l);
        q5l_pub.publish(q5l);
        q6l_pub.publish(q6l);

        ros::spinOnce();

        loop_rate.sleep();

        ++count;
    }


    return 0;
}
