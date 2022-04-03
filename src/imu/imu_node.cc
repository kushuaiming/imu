#include <iostream>
#include <string>

#include "serial/serial.h"

void enumerate_ports() {
  std::vector<serial::PortInfo> devices_found = serial::list_ports();
  for (auto device : devices_found) {
    std::cout << "device port: " << device.port.c_str()
              << ", device description: " << device.description.c_str()
              << ", device hardware id: " << device.hardware_id.c_str()
              << std::endl;
  }
}

void print_usage() {
  std::cerr << "Usage: imu_node <serial port address> <baudrate>}." << std::endl;
}

int run(int argc, char **argv) {
  if (argc < 2) {
    print_usage();
    return 0;
  }

  std::string port(argv[1]);
  unsigned long baudrate = std::stoul(argv[2]);
  // timeout in milliseconds
  serial::Serial serial(port, baudrate, serial::Timeout::simpleTimeout(1000));

  if (serial.isOpen())
    std::cout << "Serial port open successfully." << std::endl;

  while (1) {
    uint8_t result;
    serial.read(&result, 1);
    std::cout << std::hex << static_cast<int>(result) << " ";
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
