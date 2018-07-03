#include "ros/ros.h"
#include "std_msgs/String.h"
#include "iiwa_msgs/JointPosition.h"
#include "iiwa_msgs/JointQuantity.h"
#include "conversions.h"
#include "iiwa_ros.h"


// This displays the JointPosition message when it receives it.


void JointPositionCallback(const iiwa_msgs::JointPosition::ConstPtr& msg)
{
  ROS_INFO("[%.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f]", 
    msg->position.a1, 
    msg->position.a2,
    msg->position.a3,
    msg->position.a4,
    msg->position.a5,
    msg->position.a6,
    msg->position.a7);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("iiwa/state/JointPosition", 1000, JointPositionCallback);

  ros::spin();

  return 0;
}
