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
if (libConfig_FOUND)
    #return()
endif (libConfig_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

add_package_RC(libConfig libCommon)

set(libConfig_FOUND TRUE CACHE BOOL "libConfig found")
set(libConfig_INCLUDE_DIRS ${libConfig_INCLUDE_DIRS} "${libConfig_DIR}/include" CACHE STRING "libConfig include")
set(libConfig_LIBRARIES ${libConfig_LIBRARIES} "libConfig" CACHE STRING "libConfig libraries")