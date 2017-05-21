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
if (libLightControl_FOUND)
    #return()
endif (libLightControl_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

add_package_RC(libLightControl libCommon)
add_package_RC(libLightControl libSerialConnector)

set(libLightControl_FOUND TRUE CACHE BOOL "libLightControl found")
set(libLightControl_INCLUDE_DIRS ${libLightControl_INCLUDE_DIRS} "${libLightControl_DIR}/include" CACHE STRING "libLightControl include")
set(libLightControl_LIBRARIES ${libLightControl_LIBRARIES} "libLightControl" CACHE STRING "libLightControl libraries")