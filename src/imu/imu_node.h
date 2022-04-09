#ifndef IMU_NODE_H_
#define IMU_NODE_H_

#include "imu.h"
#include "imu_publisher.h"
#include "serial/serial.h"

class IMUNode {
 public:
  IMUNode(const std::string&, uint32_t baudrate, ros::NodeHandle& node_handle);
  int Run();

 private:
  serial::Serial serial_;
  IMU imu_;

  std::unique_ptr<IMUPublisher> imu_publisher_;
};

#endif  // IMU_NODE_H_