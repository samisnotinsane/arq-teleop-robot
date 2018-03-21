cmake_minimum_required(VERSION 2.8.3)
project(object_detection)

INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF(COMPILER_SUPPORTS_CXX11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF(COMPILER_SUPPORTS_CXX0X)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ELSE()
  MESSAGE(ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
ENDIF()

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rostime
  std_msgs
  sensor_msgs
  message_filters
  image_transport
  genmsg
  image_transport
  cv_bridge
)

catkin_package()

find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(object_detection src/object_detection.cpp)
target_link_libraries(object_detection
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${PCL_LIBRARIES}
)