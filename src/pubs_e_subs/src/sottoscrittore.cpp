/*
  Following the ROS tutorials on publishers and subscribers
  Seguo i tutorial ROS di sottoscrittori e editori
*/
#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"

#include <translator_msg_pkg/Translator.h>
#include <nested_msg/msg_env.h>
#include <nested_msg/msg1.h>
#include <nested_msg/msg2.h>

void chatterCallback(const nested_msg::msg_env & msg)
{
  for(int i = 0; i<msg.m1.size(); i++){
    for(int j = 0; j<msg.m1.at(i).m2.size(); j++){
      ROS_INFO("I heard: [ SID: %d, MID: %d ]", msg.sid, msg.m1.at(msg.sid).mid);
    }
  }
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
