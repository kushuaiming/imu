#ifndef IMU_PUBLISHER_H_
#define IMU_PUBLISHER_H_
#include "ros/ros.h"
#include "std_msgs/String.h"

class IMUPublisher {
 public:
  IMUPublisher(ros::NodeHandle& node_handle);
  void Publish(const std_msgs::String& msg);

 private:
  ros::Publisher imu_publish_;
};

#endif  // IMU_PUBLISHER_H_