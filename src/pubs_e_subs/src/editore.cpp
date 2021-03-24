/*
  Following the ROS tutorials on publishers and subscribers
  Seguo i tutorial ROS di sottoscrittori e editori
*/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "editore");
  // param [2] = string node name

  ros::NodeHandle n;

  ros::Publisher chiacchiere = n.advertise<std_msgs::String>("chiacchiere", 1000);
  // param [0] = topic name, [1] = msg queue size

  ros::Rate loop_rate(10);
  // param [0] = freq in Hz

  /* Count sent msgs */
  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chiacchiere.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
