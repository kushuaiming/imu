cmake_minimum_required(VERSION 3.0.2)
project(imu)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  std_msgs
)

catkin_package(
   CATKIN_DEPENDS roscpp serial std_msgs
)

include_directories(
  ${PROJECT_SOURCE_DIR}/sensors
  ${catkin_INCLUDE_DIRS}
)

set(SOURCES
  imu_node.cc
  imu_publisher.cc
  sensors/imu.cc
)

add_executable(imu_node ${SOURCES})

target_link_libraries(imu_node
  ${catkin_LIBRARIES}
)