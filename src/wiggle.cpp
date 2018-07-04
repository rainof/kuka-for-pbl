#include "ros/ros.h"
#include "std_msgs/String.h"
#include "iiwa_msgs/JointPosition.h"
#include "iiwa_msgs/JointQuantity.h"
#include "conversions.h"
#include "iiwa_ros.h"
#include <math.h>

// This function sends positions to the kuka periodically for a wiggley motion.
// Start the robot in fully extended position.

// void callback1(const ros::TimerEvent&)
// {
//   ROS_INFO("Callback 1 triggered");
//   // my_joint_position.position.a1 = 0;
//   // my_joint_position.position.a2 = -1.5;
//   // my_joint_position.position.a3 = 0;
//   // my_joint_position.position.a4 = 0;
//   // my_joint_position.position.a5 = 0;
//   // my_joint_position.position.a6 = 0;
//   // my_joint_position.position.a7 = 0;
//   sendmotion_pub.publish(my_joint_position);
// }

// void callback2(const ros::TimerEvent&)
// {
//   ROS_INFO("Callback 2 triggered");
//   my_joint_position.position.a1 = 0;
//   my_joint_position.position.a2 = 0;
//   my_joint_position.position.a3 = 0;
//   my_joint_position.position.a4 = 0;
//   my_joint_position.position.a5 = 0;
//   my_joint_position.position.a6 = 0;
//   sendmotion_pub.publish(my_joint_position);
// }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sendmotion");
  ros::NodeHandle n;
  iiwa_msgs::JointPosition my_joint_position;
  ros::Publisher sendmotion_pub = n.advertise<iiwa_msgs::JointPosition>("iiwa/command/JointPosition", 1000);
  ros::Rate loop_rate(10);

  int count = 0;
  double speed = 0.1;
  while (ros::ok())
  {
    ROS_INFO("count %d", count);

    // ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);
    // ros::Timer timer2 = n.createTimer(ros::Duration(1.0), callback2);

    my_joint_position.position.a1 = 0;
    my_joint_position.position.a2 = -1.5;
    my_joint_position.position.a3 = 0;
    my_joint_position.position.a4 = 0;
    my_joint_position.position.a5 = 0;
    my_joint_position.position.a6 = 0;
    my_joint_position.position.a7 = 0;
    sendmotion_pub.publish(my_joint_position);
    ros::Duration(8).sleep();
    ROS_INFO("NEXT\n");
    my_joint_position.position.a1 = 0;
    my_joint_position.position.a2 = 0;
    my_joint_position.position.a3 = 0;
    my_joint_position.position.a4 = 0;
    my_joint_position.position.a5 = 0;
    my_joint_position.position.a6 = 0;
    my_joint_position.position.a7 = 0;
    sendmotion_pub.publish(my_joint_position);
    ros::Duration(8).sleep();
    ROS_INFO("FINISH\n");
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  ROS_INFO("BREAK\n");

  return 0;
}

