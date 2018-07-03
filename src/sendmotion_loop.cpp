#include "ros/ros.h"
#include "std_msgs/String.h"
#include "iiwa_msgs/JointPosition.h"
#include "iiwa_msgs/JointQuantity.h"
#include "conversions.h"
#include "iiwa_ros.h"

// This function sends a position to the kuka periodically. This can be used to check if the robot is responding.
// This is equivalent to sending the position via this command on the CLI:
// rostopic pub -r 5 /iiwa/command/JointPosition iiwa_msgs/JointPosition...    (press tab in the terminal at the "...")

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sendmotion");

  ros::NodeHandle n;

  ros::Publisher sendmotion_pub = 
    n.advertise<iiwa_msgs::JointPosition>("iiwa/command/JointPosition", 1000);

  ros::Rate loop_rate(0.2);

  // current setting [0.156, 0.374, 0.120, -0.750, -0.049, 0.509, -1.571]
  iiwa_msgs::JointPosition my_joint_position;
  my_joint_position.position.a1 = 0.156;
  my_joint_position.position.a2 = 0.374;
  my_joint_position.position.a3 = 0.120;
  my_joint_position.position.a4 = -0.750;
  my_joint_position.position.a5 = -0.049;
  my_joint_position.position.a6 = 0.509;
  // my_joint_position.position.a6 = 0.6;
  my_joint_position.position.a7 = -1.3;

  int count = 0;
  while (ros::ok())
  {
    ROS_INFO("count %d", count);

    sendmotion_pub.publish(my_joint_position);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
