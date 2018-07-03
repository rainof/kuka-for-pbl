#include "ros/ros.h"
#include "std_msgs/String.h"
#include "iiwa_msgs/JointPosition.h"
#include "iiwa_msgs/JointQuantity.h"
#include "conversions.h"
#include "iiwa_ros.h"

// Sends a single joint position to the KUKA. This is equivalent to sending the position via this command on the CLI:
// rostopic pub /iiwa/command/JointPosition iiwa_msgs/JointPosition...    (press tab in the terminal at the "...")

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sendmotion");

  ros::NodeHandle n;

  ros::Publisher sendmotion_pub = 
    n.advertise<iiwa_msgs::JointPosition>("iiwa/command/JointPosition", 1000);

  // current setting [0.156, 0.374, 0.120, -0.750, -0.049, 0.509, -1.571]
  iiwa_msgs::JointPosition my_joint_position;
  my_joint_position.position.a1 = 0.15;
  my_joint_position.position.a2 = 0.35;
  my_joint_position.position.a3 = 0.12;
  my_joint_position.position.a4 = -0.75;
  my_joint_position.position.a5 = -0.05;
  my_joint_position.position.a6 = 0.50;
  // my_joint_position.position.a7 = -1.571;
  my_joint_position.position.a7 = -1.3;

  //wait until the connection is completed
  ROS_INFO("wait until the connection is completed");
  ros::Rate loop_rate(100);
  while(sendmotion_pub.getNumSubscribers() == 0) {
    loop_rate.sleep();
  }

  // once connection is ok, send the command
  ROS_INFO("publishing single command");
  if(ros::ok()){ 
    sendmotion_pub.publish(my_joint_position); 
    ros::spinOnce();
  }
  else {
    ROS_INFO("ros not ok");  
  }
  ROS_INFO("done");

  // no loop needed

  return 0;
}
