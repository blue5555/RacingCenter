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
if (libQwt_FOUND)
    #return()
endif (libQwt_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport Concurrent Svg OpenGL REQUIRED)

set(libQwt_FOUND TRUE CACHE BOOL "libQwt found")
set(libQwt_INCLUDE_DIRS ${libQwt_INCLUDE_DIRS} "${libQwt_DIR}/include" ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5PrintSupport_INCLUDE_DIRS} ${Qt5Concurrent_INCLUDE_DIRS} ${Qt5Svg_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} CACHE STRING "libQwt include")
set(libQwt_LIBRARIES ${libQwt_LIBRARIES} "libQwt" ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5PrintSupport_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Svg_LIBRARIES} ${Qt5OpenGL_LIBRARIES} CACHE STRING "libQwt libraries")