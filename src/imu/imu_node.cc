#include "imu_node.h"

#include <iostream>
#include <sstream>
#include <string>

#include "ros/ros.h"

IMUNode::IMUNode(const std::string &port, uint32_t baudrate,
                 ros::NodeHandle &node_handle)
    : serial_(port, baudrate, serial::Timeout::simpleTimeout(1000)) {
  imu_publisher_.reset(new IMUPublisher(node_handle));
}

int IMUNode::Run() {
  ros::Rate loop_rate(10);
  if (serial_.isOpen()) {
    std::cout << "Serial port open successfully." << std::endl;
  }
  while (ros::ok()) {
    std_msgs::String msg;
    std::stringstream ss = imu_.ParseInfo(serial_);
    msg.data = ss.str();
    imu_publisher_->Publish(msg);
    ros::spinOnce();
    // TODO: use sleep method.
    // loop_rate.sleep();
  }
  return 0;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "imu_node");
  ros::NodeHandle node_handle;
  std::string port = "/dev/ttyUSB0";
  uint32_t baudrate = 921600;
  IMUNode imu_node(port, baudrate, node_handle);
  try {
    return imu_node.Run();
  } catch (std::exception &exception) {
    std::cerr << "Unhandled std::exception: " << exception.what() << std::endl;
  }
}
