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
if (libCommon_FOUND)
    #return()
endif (libCommon_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

find_package(Qt5 COMPONENTS Core Gui Xml REQUIRED)

set(libCommon_FOUND TRUE CACHE BOOL "libCommon found")
set(libCommon_INCLUDE_DIRS ${libCommon_INCLUDE_DIRS} "${libCommon_DIR}/include" ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS} CACHE STRING "libCommon include")
set(libCommon_LIBRARIES ${libCommon_LIBRARIES} "libCommon" ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Xml_LIBRARIES} CACHE STRING "libCommon libraries")