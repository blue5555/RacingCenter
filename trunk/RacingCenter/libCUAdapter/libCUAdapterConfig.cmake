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
if (libCUAdapter_FOUND)
    #return()
endif (libCUAdapter_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

add_package_RC(libCUAdapter libCommon)
add_package_RC(libCUAdapter libConfig)
add_package_RC(libCUAdapter libSerialConnector)

set(libCUAdapter_FOUND TRUE CACHE BOOL "libCUAdapter found")
set(libCUAdapter_INCLUDE_DIRS ${libCUAdapter_INCLUDE_DIRS} "${libCUAdapter_DIR}/include" CACHE STRING "libCUAdapter include")
set(libCUAdapter_LIBRARIES ${libCUAdapter_LIBRARIES} "libCUAdapter" CACHE STRING "libCUAdapter libraries")