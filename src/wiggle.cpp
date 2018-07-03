#include "ros/ros.h"
#include "std_msgs/String.h"
#include "iiwa_msgs/JointPosition.h"
#include "iiwa_msgs/JointQuantity.h"
#include "conversions.h"
#include "iiwa_ros.h"
#include <math.h>

// This function sends positions to the kuka periodically for a wiggley motion.
// Start the robot in fully extended position.

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sendmotion");

  ros::NodeHandle n;

  ros::Publisher sendmotion_pub = 
    n.advertise<iiwa_msgs::JointPosition>("iiwa/command/JointPosition", 1000);

  ros::Rate loop_rate(10);

  iiwa_msgs::JointPosition my_joint_position;

  int count = 0;
  double speed = 0.1;
  while (ros::ok())
  {
    ROS_INFO("count %d", count);

    my_joint_position.position.a1 = 0.3*sin(count*speed *1);
    my_joint_position.position.a2 = 0.3*sin(count*speed *1.1);
    my_joint_position.position.a3 = 0.3*sin(count*speed *1.2);
    my_joint_position.position.a4 = 0.3*sin(count*speed *1.3);
    my_joint_position.position.a5 = 0.3*sin(count*speed *1.4);
    my_joint_position.position.a6 = 0.3*sin(count*speed *1.5);
    my_joint_position.position.a7 = 0.3*sin(count*speed *1.6);

    sendmotion_pub.publish(my_joint_position);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}

