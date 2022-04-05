#ifndef SENSORS_IMU_H_
#define SENSORS_IMU_H_

#include "serial/serial.h"

struct Angle {
  double roll_;
  double pitch_;
  double yaw_;
};

class IMU {
 public:
  void ParseInfo(serial::Serial& serial);

 private:
  Angle angle_;
};

#endif  // SENSORS_IMU_H_