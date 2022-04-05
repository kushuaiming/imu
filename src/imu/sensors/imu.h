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

struct Angle {
  double roll_;
  double pitch_;
  double yaw_;
};

class IMU {
 public:
  const Angle& getAngle() { return angle_; }
  Angle* mutableAngle() { return &angle_; }

 private:
  Angle angle_;
};

#endif  // SENSORS_IMU_H_