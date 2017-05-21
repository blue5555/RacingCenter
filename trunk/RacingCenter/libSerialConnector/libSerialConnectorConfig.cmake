#######################################################################
#
# 
#
# Copyright; 
#
# $Author:  $
# $Date: $
# $Revision: $
#
#######################################################################

# execute only once
if (libSerialConnector_FOUND)
    #return()
endif (libSerialConnector_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

add_package_RC(libSerialConnector libCommon)
add_package_RC(libSerialConnector libConfig)

find_package(Qt5 REQUIRED SerialPort)

set(libSerialConnector_FOUND TRUE CACHE BOOL "libSerialConnector found")
set(libSerialConnector_INCLUDE_DIRS ${libSerialConnector_INCLUDE_DIRS} ${Qt5SerialPort_INCLUDE_DIRS} "${libSerialConnector_DIR}/include" CACHE STRING "libSerialConnector include")
set(libSerialConnector_LIBRARIES ${libSerialConnector_LIBRARIES} ${Qt5SerialPort_LIBRARIES} "libSerialConnector" CACHE STRING "libSerialConnector libraries")