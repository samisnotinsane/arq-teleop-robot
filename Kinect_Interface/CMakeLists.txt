cmake_minimum_required(VERSION 3.9)
project(Kinect_Interface)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/interface.cpp include/interface.h include/libfreenect.h)

include_directories("/opt/ros/kinetic/include")

include_directories("/usr/include/libusb-1.0")

IF(NOT DEFINED CMAKE_BUILD_TYPE)
    # No effect for multi-configuration generators (e.g. for Visual Studio)
    SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose: RelWithDebInfo Release Debug MinSizeRel None")
ENDIF()

SET(MY_DIR ${Kinect_Interface_Source_SOURCE_DIR})
SET(DEPENDS_DIR "${MY_DIR}/../depends" CACHE STRING "Dependency directory")

# The example build system is standalone and will work out-of-tree with these files copied
SET(freenect2_ROOT_DIR ${MY_DIR}/..)

IF(TARGET freenect2)
    MESSAGE(STATUS "Using in-tree freenect2 target")
    SET(freenect2_LIBRARIES freenect2)
    SET(freenect2_DLLS ${LIBFREENECT2_DLLS})
ELSE()
    FIND_PACKAGE(freenect2 REQUIRED)
    # Out-of-tree build will have to have DLLs manually copied.
ENDIF()

INCLUDE_DIRECTORIES(
        ${freenect2_INCLUDE_DIR}
        ${catkin_INCLUDE_DIR}
)

SET(Kinect_Interface_src
        src/interface.cpp
        include/ros_headers.h)

SET(Kinect_Interface_LIBRARIES
        ${freenect2_LIBRARIES}
        ${catkin_LIBRARIES}
        )

SET(Kinect_Interface_DLLS
        ${freenect2_DLLS}
        )

ADD_EXECUTABLE(Kinect_Interface
        ${Kinect_Interface_src} ${SOURCE_FILES}
        )

TARGET_LINK_LIBRARIES(Kinect_Interface
        ${Kinect_Interface_LIBRARIES}
        )
