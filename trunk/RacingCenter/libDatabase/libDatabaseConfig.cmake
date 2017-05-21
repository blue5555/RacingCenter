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
if (libDatabase_FOUND)
    #return()
endif (libDatabase_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

add_package_RC(libDatabase libCommon)

set(libDatabase_FOUND TRUE CACHE BOOL "libDatabase found")
set(libDatabase_INCLUDE_DIRS ${libDatabase_INCLUDE_DIRS} "${libDatabase_DIR}/include" CACHE STRING "libDatabase include")
set(libDatabase_LIBRARIES ${libDatabase_LIBRARIES} "libDatabase" CACHE STRING "libDatabase libraries")