/*
  Following the ROS tutorials on publishers and subscribers
  Seguo i tutorial ROS di sottoscrittori e editori
*/
#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
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
