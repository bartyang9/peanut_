cmake_minimum_required(VERSION 2.8.3)
project(peanut)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  actionlib_msgs
)

# catkin_package(
#   CATKIN_DEPENDS actionlib_msgs
# )

add_action_files(
  DIRECTORY action
  FILES
  MoveRobot.action
)

add_executable(peanut_server src/peanut_server.cpp)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

target_link_libraries(peanut_server, ${catkin_LIBRARIES})

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs
)