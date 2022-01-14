cmake_minimum_required(VERSION 2.8.3)
project(ecu_control)
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ecu_control
  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(ecu_control src/ecu_control.cpp include/ecu_control/ecu.cpp)
target_link_libraries(ecu_control ${catkin_LIBRARIES})