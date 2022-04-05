# 1. Environment set
## 1.1 Install ROS Serial Package
[rosserial - ROS Wiki](http://wiki.ros.org/rosserial)
```C++
sudo apt install ros-noetic-serial
```
## 1.2 Install Serial Communication Library
[serial - ROS Wiki](http://wiki.ros.org/serial)
```C++
git clone https://github.com/wjwwood/serial.git
make
make test
make install
```
# 2. Build and Run
## 2.1 Build
```C++
catkin_make
```
## 2.2 Run
```C++
source devel/setup.bash
ls /dev/ttyUSB*
sudo chown :second_user /dev/ttyUSB0
rosrun imu imu_node
```