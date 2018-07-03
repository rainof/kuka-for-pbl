#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"
#include "iiwa_msgs/JointPosition.h"
#include "iiwa_msgs/JointQuantity.h"
#include "conversions.h"
#include "iiwa_ros.h"
#include <math.h>

#include <tf/transform_listener.h>    // Includes the TF conversions

#include "iiwa_ros.h"           // To call time_to_destination
#include <chrono>
#include <thread>               // To wait for time_to_destination


// Does a slow up and down movement by cartesian coordinates.

bool cartMotion(ros::NodeHandle n){
  ros::Publisher pubCartPose = n.advertise<geometry_msgs::PoseStamped>("iiwa/command/CartesianPose", 1000);

  int count = 0;
  geometry_msgs::Point p;
  geometry_msgs::Quaternion q;    // [0,0,0,1] = no rotation (identity)
  geometry_msgs::Pose pose;
  geometry_msgs::PoseStamped ps;  
  q.x = 0;
  q.y = 0;
  q.z = 0;
  q.w = 1;
  // To set the rotation by RPY, you can use:
  // q = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);

  ros::Rate loop_rate(.5);
  while (ros::ok())
  {
    // Prepare pose components
    p.x = .01;
    p.y = .01;
    if (count%4 == 1) {p.z = 1.5;}
    else if (count%4 == 2) {p.z = 1.45;}
    else if (count%4 == 3) {p.z = 1.4;}
    else {p.z = 1.45;}

    // Create the pose
    pose.position = p;
    pose.orientation = q;

    ps.pose = pose;
    ps.header.stamp = ros::Time();

    // ROS_INFO("%s", msg.data.c_str());

    pubCartPose.publish(ps);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }
  return 1;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tnp_testing_node");
  ros::NodeHandle n;

  cartMotion(n);
  return 0;
}