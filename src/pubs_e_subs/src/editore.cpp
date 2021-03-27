/*
  Following the ROS tutorials on publishers and subscribers
  Seguo i tutorial ROS di sottoscrittori e editori
*/
#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"
#include <sstream>

#include <translator_msg_pkg/Translator.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "editore");
  // param [2] = string node name

  ros::NodeHandle n;

  ros::Publisher chiacchiere = n.advertise<translator_msg_pkg::Translator>("chiacchiere", 1000);
  // param [0] = topic name, [1] = msg queue size

  ros::Rate loop_rate(10);
  // param [0] = freq in Hz

  /* Count sent msgs */
  int count = 0;
  while (ros::ok())
  {
    translator_msg_pkg::Translator msg;
    msg.position_data.resize(4);
    for(int i=0;i<4;i++){
      msg.position_data.at(i) = i;
    }

    msg.state_name = "NOMINAL-STATE";

    ROS_INFO("[%s]: %f, %f, %f, %f", msg.state_name.c_str(), msg.position_data.at(0), msg.position_data.at(1), msg.position_data.at(2), msg.position_data.at(3));

    chiacchiere.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
