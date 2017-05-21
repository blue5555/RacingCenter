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
if (libWidgets_FOUND)
    #return()
endif (libWidgets_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(libWidgets_FOUND TRUE CACHE BOOL "libWidgets found")
set(libWidgets_INCLUDE_DIRS ${libWidgets_INCLUDE_DIRS} "${libWidgets_DIR}/include" ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} CACHE STRING "libWidgets include")
set(libWidgets_LIBRARIES ${libWidgets_LIBRARIES} "libWidgets" ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES} CACHE STRING "libWidgets libraries")