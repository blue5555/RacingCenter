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
if (libStatistics_FOUND)
    #return()
endif (libStatistics_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

add_package_RC(libStatistics libCommon)
add_package_RC(libStatistics libQwt)

set(libStatistics_FOUND TRUE CACHE BOOL "libStatistics found")
set(libStatistics_INCLUDE_DIRS ${libStatistics_INCLUDE_DIRS} ${Qt5SerialPort_INCLUDE_DIRS} "${libStatistics_DIR}/include" CACHE STRING "libStatistics include")
set(libStatistics_LIBRARIES ${libStatistics_LIBRARIES} ${Qt5SerialPort_LIBRARIES} "libStatistics" CACHE STRING "libStatistics libraries")