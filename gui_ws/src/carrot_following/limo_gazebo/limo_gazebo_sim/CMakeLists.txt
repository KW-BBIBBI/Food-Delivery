cmake_minimum_required(VERSION 2.8.3)
project(limo_gazebo_sim)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS    
  roslaunch
  roslint
  roscpp
  std_msgs
  sensor_msgs
  geometry_msgs
  tf
  tf2
  tf2_ros
  gazebo_dev
  gazebo_msgs
  nav_msgs
)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES  gazebo_ros_ackerman
  CATKIN_DEPENDS roscpp sensor_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(gazebo_ros_ackerman src/gazebo_ros_ackerman_drive.cpp)
target_link_libraries(gazebo_ros_ackerman ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_library(limo_gazebo STATIC src/limo_skid_steer.cpp)
target_link_libraries(limo_gazebo ${catkin_LIBRARIES})

add_executable(limo_skid_steer_controller src/limo_skid_steer_controller.cpp)
target_link_libraries(limo_skid_steer_controller limo_gazebo ${catkin_LIBRARIES})

install(TARGETS gazebo_ros_ackerman
ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

