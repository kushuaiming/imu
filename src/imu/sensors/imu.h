#ifndef SENSORS_IMU_H_
#define SENSORS_IMU_H_

enum CommunicationProtocol {
  flag = 0x55,
  acceleration = 0x51,
  angular_velocity = 0x52,
  angle = 0x53,
  magnetic_field = 0x54,
  quaternion = 0x59
};

class Angle {
 private:
  int roll_;
  int pitch_;
  int yaw_;
};

class IMU {
 private:
  Angle angle_;
};

#endif  // SENSORS_IMU_H_