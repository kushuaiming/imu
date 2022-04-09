#include "imu.h"

#include <iostream>
#include <vector>

namespace {
enum CommunicationProtocol {
  flag = 0x55,
  acceleration = 0x51,
  angular_velocity = 0x52,
  angle = 0x53,
  magnetic_field = 0x54,
  quaternion = 0x59
};
}  // namespace

std::stringstream IMU::ParseInfo(serial::Serial& serial) {
  std::stringstream ss;
  while (1) {
    uint8_t header0;
    serial.read(&header0, 1);
    if (header0 == CommunicationProtocol::flag) {
      uint8_t header1;
      serial.read(&header1, 1);
      if (header1 == CommunicationProtocol::angle) {
        std::vector<uint8_t> buffer;
        buffer.reserve(9);
        serial.read(buffer, 9);
        angle_.roll_ = ((buffer[1] << 8) | buffer[0]) / 32768.0 * 180.0;
        angle_.pitch_ = ((buffer[3] << 8) | buffer[2]) / 32768.0 * 180.0;
        angle_.yaw_ = ((buffer[5] << 8) | buffer[4]) / 32768.0 * 180.0;
        ss << "Roll: " << angle_.roll_ << ", Pitch: " << angle_.pitch_
           << ", Yaw: " << angle_.yaw_;
        break;
      }
    }
  }
  return ss;
}