#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ContactsState.h"
#include "std_msgs/Float32.h"
//#include "gazebo_msgs/LinkState.h"
#include <sstream>
float Fz_r, Fz_l;
double Fz_l_measured;
int count_l = 0;
double A_l = 1.0; // Transition matrix
double R_l = 0.05; // variance noise measurements
double Q_l = 0.0001; // variance noise process
double pre_P_l, pre_Y_l;


double Fz_r_measured;
int count_r = 0;
double A_r = 1.0; // Transition matrix
double R_r = 0.05; // variance noise measurements
double Q_r = 0.0001; // variance noise process
double pre_P_r, pre_Y_r;


void chatterCallback_Left(const gazebo_msgs::ContactsState::ConstPtr& cs) // this line has been edited by adding "::" between ContactState and ConstPtr&
{


  int a;
  a = sizeof(cs->states);
  std::stringstream ss;
  ss << a;


  //double z = 0;

    if (cs->states.empty()) {
        Fz_l_measured = 0;
    } else {
        Fz_l_measured = cs->states[0].total_wrench.force.z;
    }

    if (count_l==0) {
        pre_P_l = 1.01;
        pre_Y_l = 0;
        count_l =  count_l + 1;
    }
    else {
        double X_temp = pre_Y_l;
        double P_temp = A_l * pre_P_l * A_l + Q_l;
        double K_l = P_temp / (P_temp + R_l);
        // Measurement Update
        double Fz_l_Kf = X_temp + (K_l * (Fz_l_measured - X_temp));
        pre_Y_l = Fz_l_Kf;
        pre_P_l = (1 - K_l) * P_temp;

    }
    Fz_l = pre_Y_l;

  /*for( int i = 0; i < a; i = i + 1 )
   {

       z = z + cs->states[a].total_wrench.force.z;
   }*/
  
  ROS_INFO("Total Force in Z direction is: %f", Fz_l);
}

void chatterCallback_Right(const gazebo_msgs::ContactsState::ConstPtr& cs) // this line has been edited by adding "::" between ContactState and ConstPtr&
{
    if (cs->states.empty()) {
        Fz_r_measured = 0;
    } else {
        Fz_r_measured = cs->states[0].total_wrench.force.z;
    }

    if (count_r==0) {
        pre_P_r = 1.01;
        pre_Y_r = 0;
        count_r =  count_r + 1;
    }
    else {
        double X_temp = pre_Y_r;
        double P_temp = A_r * pre_P_r * A_r + Q_r;
        double K_r = P_temp / (P_temp + R_r);
        // Measurement Update
        double Fz_r_Kf = X_temp + (K_r * (Fz_r_measured - X_temp));
        pre_Y_r = Fz_r_Kf;
        pre_P_r = (1 - K_r) * P_temp;

    }
    Fz_r = pre_Y_r;

}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    ros::Subscriber subR = n.subscribe("RightFootFTS", 1000, chatterCallback_Right);
    ros::Subscriber subL = n.subscribe("LeftFootFTS", 1000, chatterCallback_Left);

  ros::Publisher pub = n.advertise<std_msgs::Float32>("Left_FZ_KF",1000); //here is for you question 2).
    ros::Publisher pub2 = n.advertise<std_msgs::Float32>("Left_FZ",1000); //here is for you question 2).
    ros::Publisher pub3 = n.advertise<std_msgs::Float32>("Right_FZ_KF",1000); //here is for you question 2).
    ros::Publisher pub4 = n.advertise<std_msgs::Float32>("Right_FZ",1000); //here is for you question 2).
  std_msgs::Float32 msg;
    std_msgs::Float32 msg2;
    std_msgs::Float32 msg3;
    std_msgs::Float32 msg4;
   // this line has been edited due to this error: conversion from ‘const char [6]’ to non-scalar type ‘std_msgs::String’ requested

  ros::Rate loop_rate(1000);

  while (ros::ok())
  {
      msg.data = Fz_l;
      msg2.data = Fz_l_measured;
      pub.publish(msg);
      pub2.publish(msg2);
      msg3.data = Fz_r;
      msg4.data = Fz_r_measured;
      pub3.publish(msg3);
      pub4.publish(msg4);

      ros::spinOnce();
      loop_rate.sleep();
  }
  return 0;
}

