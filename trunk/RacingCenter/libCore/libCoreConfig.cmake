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
if (libCore_FOUND)
    return()
endif (libCore_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

# we require
add_package_RC(libCore libCommon)
add_package_RC(libCore libConfig)
add_package_RC(libCore libDatabase)
add_package_RC(libCore libCUAdapter)
add_package_RC(libCore libDataCore)
add_package_RC(libCore libRaceResults)
add_package_RC(libCore libRaceDisplay)
add_package_RC(libCore libStartlight)

set(libCore_FOUND TRUE CACHE BOOL "libCore found")
set(libCore_INCLUDE_DIRS ${libCore_INCLUDE_DIRS} "${libCore_DIR}/include" CACHE STRING "libCore include")
set(libCore_LIBRARIES ${libCore_LIBRARIES} "libCore" CACHE STRING "libCore libraries")