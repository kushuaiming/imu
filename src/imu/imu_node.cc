#include <iostream>
#include <memory>
#include <vector>

#include "imu.h"
#include "serial/serial.h"

void print_usage() {
  std::cerr << "Usage: imu_node <serial port address> <baudrate>}."
            << std::endl;
}

void parseInfo(const std::shared_ptr<serial::Serial> &serial) {
  uint8_t header0;
  serial->read(&header0, 1);
  if (header0 == CommunicationProtocol::flag) {
    uint8_t header1;
    serial->read(&header1, 1);
    if (header1 == CommunicationProtocol::angle) {
      std::vector<uint8_t> buffer;
      buffer.reserve(9);
      serial->read(buffer, 9);
      double roll = ((buffer[1] << 8) | buffer[0]) / 32768.0 * 180.0;
      double pitch = ((buffer[3] << 8) | buffer[2]) / 32768.0 * 180.0;
      double yaw = ((buffer[5] << 8) | buffer[4]) / 32768.0 * 180.0;
      std::cout << "Roll: " << roll << ", Pitch: " << pitch << ", Yaw: " << yaw
                << std::endl;
    }
  }
}

int run(int argc, char **argv) {
  if (argc < 2) {
    print_usage();
    return 0;
  }

  std::string port(argv[1]);
  unsigned long baudrate = std::stoul(argv[2]);
  // timeout in milliseconds
  auto serial(std::make_shared<serial::Serial>(
      port, baudrate, serial::Timeout::simpleTimeout(1000)));

  if (serial->isOpen())
    std::cout << "Serial port open successfully." << std::endl;

  while (1) {
    parseInfo(serial);
  }

  return 0;
}

int main(int argc, char **argv) {
  try {
    return run(argc, argv);
  } catch (std::exception &exception) {
    std::cerr << "Unhandled std::exception: " << exception.what() << std::endl;
  }
}
