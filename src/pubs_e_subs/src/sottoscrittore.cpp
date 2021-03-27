/*
  Following the ROS tutorials on publishers and subscribers
  Seguo i tutorial ROS di sottoscrittori e editori
*/
#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"

#include <translator_msg_pkg/Translator.h>

void chatterCallback(const translator_msg_pkg::Translator& msg)
{
  ROS_INFO("I heard: [ [%s]: %f, %f, %f, %f]", msg.state_name.c_str(), msg.position_data.at(0), msg.position_data.at(1), msg.position_data.at(2), msg.position_data.at(3));
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sottoscrittore");
  // param [2] = string node name

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("chiacchiere", 1000, chatterCallback);

  ros::spin(); // loop and pump callbacks

  return 0;
}
