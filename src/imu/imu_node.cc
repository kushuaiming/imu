#include "imu_node.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "ros/ros.h"

IMUNode::IMUNode(const std::string &port, uint32_t baudrate)
    : serial_(port, baudrate, serial::Timeout::simpleTimeout(1000)) {}

int IMUNode::run() {
  if (serial_.isOpen()) {
    std::cout << "Serial port open successfully." << std::endl;
  }
  while (1) {
    parseInfo();
  }
  return 0;
}

void IMUNode::parseInfo() {
  uint8_t header0;
  serial_.read(&header0, 1);
  if (header0 == CommunicationProtocol::flag) {
    uint8_t header1;
    serial_.read(&header1, 1);
    if (header1 == CommunicationProtocol::angle) {
      std::vector<uint8_t> buffer;
      buffer.reserve(9);
      serial_.read(buffer, 9);
      imu_.mutableAngle()->roll_ =
          ((buffer[1] << 8) | buffer[0]) / 32768.0 * 180.0;
      imu_.mutableAngle()->pitch_ =
          ((buffer[3] << 8) | buffer[2]) / 32768.0 * 180.0;
      imu_.mutableAngle()->yaw_ =
          ((buffer[5] << 8) | buffer[4]) / 32768.0 * 180.0;
      std::cout << "Roll: " << imu_.getAngle().roll_
                << ", Pitch: " << imu_.getAngle().pitch_
                << ", Yaw: " << imu_.getAngle().yaw_ << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  std::string port = "/dev/ttyUSB0";
  uint32_t baudrate = 921600;
  IMUNode imu_node(port, baudrate);
  try {
    return imu_node.run();
  } catch (std::exception &exception) {
    std::cerr << "Unhandled std::exception: " << exception.what() << std::endl;
  }
}
