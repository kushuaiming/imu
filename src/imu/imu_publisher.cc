#include "imu_publisher.h"

#include "std_msgs/String.h"

IMUPublisher::IMUPublisher(ros::NodeHandle& node_handle) {
  imu_publish_ = node_handle.advertise<std_msgs::String>("imu/", 1000);
}

void IMUPublisher::Publish(const std_msgs::String& msg) {
  imu_publish_.publish(msg);
}