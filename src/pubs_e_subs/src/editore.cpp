/*
  Following the ROS tutorials on publishers and subscribers
  Seguo i tutorial ROS di sottoscrittori e editori
*/
#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"
#include <sstream>

#include <translator_msg_pkg/Translator.h>
#include <nested_msg/msg_env.h>
#include <nested_msg/msg1.h>
#include <nested_msg/msg2.h>

int SENSOR_SZ = 5; // use # set in msg_env.msg -> msg1[SENSOR_SZ]
int MARKER_SZ = 120; // use # set in msg1.msg -> msg2[MARKER_SZ]

int main(int argc, char **argv)
{
  ros::init(argc, argv, "editore");
  // param [2] = string node name

  ros::NodeHandle n;

  ros::Publisher chiacchiere = n.advertise<nested_msg::msg_env>("chiacchiere", 1000);
  // param [0] = topic name, [1] = msg queue size

  ros::Rate loop_rate(10);
  // param [0] = freq in Hz

  /* Count sent msgs */
  int count = 0;
  int sid_shuffle = 0;
  int mid_shuffle = 0;
  bool flip = false;
  while (ros::ok())
  {
    nested_msg::msg_env msg;

    // // resizing
    // msg.m1.resize(SENSOR_SZ);
    // for(int i =0; i<SENSOR_SZ; i++){
    //   msg.m1.at(i).m2.resize(MARKER_SZ);
    //   for(int j=0; j<MARKER_SZ; j++){
    //     msg.m1.at(i).m2.at(j).data.resize(2); // for x, and y coordinate
    //   }
    // }

    // set sid to sid_shuffle and mid to sid_shuffle
    msg.sid = sid_shuffle;
    msg.m1.at(sid_shuffle).mid = mid_shuffle;

    msg.m1.at(sid_shuffle).m2.at(mid_shuffle).flag = !flip;
    // if(sid_shuffle == 0 && mid_shuffle == 0) msg.m1.at(sid_shuffle).m2.at(mid_shuffle).flag = true;


    if(msg.m1.at(sid_shuffle).m2.at(mid_shuffle).flag == true){
      msg.m1.at(sid_shuffle).m2.at(mid_shuffle).data.at(0) = 100;
      msg.m1.at(sid_shuffle).m2.at(mid_shuffle).data.at(1) = 100;
    }

    int sz = msg.m1.at(sid_shuffle).m2.at(mid_shuffle).data.size();
    int sz2 = msg.m1.at(sid_shuffle).m2.size();
    int sz3 = msg.m1.size();
    std::string flag = "True";
    if(msg.m1.at(sid_shuffle).m2.at(mid_shuffle).flag == false) flag = "False";


    if(msg.m1.at(sid_shuffle).m2.at(mid_shuffle).flag == true){
      ROS_INFO("\n{msg_env}\nSID: %d\n     {msg1}\n     MID: %d\n          {msg2}\n               [flag: %s]\n               [x: %d]\n               [y: %d]\n               [size: %dx%dx%d]", msg.sid, msg.m1.at(sid_shuffle).mid, flag.c_str(), msg.m1.at(sid_shuffle).m2.at(mid_shuffle).data.at(0), msg.m1.at(sid_shuffle).m2.at(mid_shuffle).data.at(1), sz3, sz2, sz);
    }
    else{
      ROS_INFO("ID not flagged...\n{msg_env}\nSID: %d\n     {msg1}\n     MID: %d\n          {msg2}\n               [flag: %s]\n               [x: %d]\n               [y: %d]\n               [sz: %dx%dx%d]", msg.sid, msg.m1.at(sid_shuffle).mid, flag.c_str(), msg.m1.at(sid_shuffle).m2.at(mid_shuffle).data.at(0), msg.m1.at(sid_shuffle).m2.at(mid_shuffle).data.at(1), sz3, sz2, sz);
    }

    sid_shuffle++;
    mid_shuffle++;
    flip = !flip;
    if(sid_shuffle>SENSOR_SZ-1) sid_shuffle = 0; // ROLL OVER
    if(mid_shuffle>MARKER_SZ-1) mid_shuffle = 0; // ROLL OVER

    chiacchiere.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
