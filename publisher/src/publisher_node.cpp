#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <string>

std::string custom_message = "hello world";

void inputCallback(const std_msgs::String::ConstPtr& msg)
{
  custom_message = msg->data;
  ROS_INFO("Updated custom message to: %s", custom_message.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ROS_INFO("chung toi dang hoc claude");

  ros::NodeHandle n;

  ros::Publisher chatter_pub =
           n.advertise<std_msgs::String>("chatter", 1000);

  ros::Subscriber input_sub =
           n.subscribe("input_text", 1000, inputCallback);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok()) {
    std_msgs::String msg;

    std::stringstream ss;
    ss << custom_message << " " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}

