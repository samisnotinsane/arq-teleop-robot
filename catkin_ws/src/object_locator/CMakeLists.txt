cmake_minimum_required(VERSION 2.8.3)
project(object_locator)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

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

find_package(freenect2 REQUIRED HINTS "$ENV{HOME}/freenect2")

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
find_package(freenect2 REQUIRED)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${freenect2_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(object_locator src/object_locator.cpp)
target_link_libraries(object_locator
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${PCL_LIBRARIES}
  ${freenect2_LIBRARIES}
)