#ifndef SENSORS_IMU_H_
#define SENSORS_IMU_H_

#include <sstream>

#include "serial/serial.h"

struct Angle {
  double roll_;
  double pitch_;
  double yaw_;
};

class IMU {
 public:
  IMU() = default;
  std::stringstream ParseInfo(serial::Serial& serial);

 private:
  Angle angle_;
};

#endif  // SENSORS_IMU_H_