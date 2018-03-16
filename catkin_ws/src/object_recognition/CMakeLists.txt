cmake_minimum_required(VERSION 2.8.3)
project(object_recognition)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  genmsg
  image_transport
)

catkin_package()

find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(object_recognition src/object_recognition.cpp)
target_link_libraries(object_recognition
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${PCL_LIBRARIES}
)