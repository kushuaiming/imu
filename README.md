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
sudo chown :second_user /dev/ttyUSB0
rosrun imu imu_node
```
You can check device id by this command:
```C++
ls /dev/ttyUSB*
```
## 2.3 Get Infomation
Ctrl + Alt + T: Open a new terminal.
```Bash
roscore
rostopic list
rostopic echo /imu
```