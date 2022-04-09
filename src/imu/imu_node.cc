#include "imu_node.h"

#include <iostream>
#include <string>

#include "ros/ros.h"

IMUNode::IMUNode(const std::string &port, uint32_t baudrate)
    : serial_(port, baudrate, serial::Timeout::simpleTimeout(1000)) {}

int IMUNode::Run() {
  if (serial_.isOpen()) {
    std::cout << "Serial port open successfully." << std::endl;
  }
  while (1) {
    imu_.ParseInfo(serial_);
  }
  return 0;
}

int main(int argc, char **argv) {
  std::string port = "/dev/ttyUSB0";
  uint32_t baudrate = 921600;
  IMUNode imu_node(port, baudrate);
  try {
    return imu_node.Run();
  } catch (std::exception &exception) {
    std::cerr << "Unhandled std::exception: " << exception.what() << std::endl;
  }
}
