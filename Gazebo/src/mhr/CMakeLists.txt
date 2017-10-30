cmake_minimum_required(VERSION 2.8.3)
project(mhr)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  rviz
  std_msgs
  tf
  urdf
  xacro
)


generate_messages(
   DEPENDENCIES
   std_msgs
 )


catkin_package(

)


include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(pid_feed src/pid_feed.cpp)
target_link_libraries(pid_feed ${catkin_LIBRARIES})
add_dependencies(pid_feed mhr_generate_messages_cpp)

add_executable(fs src/fs.cpp)
target_link_libraries(fs ${catkin_LIBRARIES})
add_dependencies(fs mhr_generate_messages_cpp)

add_executable(js src/js.cpp)
target_link_libraries(js ${catkin_LIBRARIES})
add_dependencies(js mhr_generate_messages_cpp)


