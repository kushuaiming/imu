#ifndef IMU_NODE_H_
#define IMU_NODE_H_

#include "imu.h"
#include "serial/serial.h"

class IMUNode {
 public:
  IMUNode(const std::string&, uint32_t baudrate);
  int Run();
 private:
  serial::Serial serial_;
  IMU imu_;
};

#endif  // IMU_NODE_H_