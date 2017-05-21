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
if (libDataCore_FOUND)
    #return()
endif (libDataCore_FOUND)

if (WIN32)
    cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
else (WIN32)
    cmake_minimum_required(VERSION 2.8.1 FATAL_ERROR)
endif (WIN32)

if (UNIX AND NOT CMAKE_BUILD_TYPE)
    message (FATAL_ERROR "The CMAKE_BUILD_TYPE has to be specified first!")
endif (UNIX AND NOT CMAKE_BUILD_TYPE)

add_package_RC(libDataCore libCommon)
add_package_RC(libDataCore libDatabase)
add_package_RC(libDataCore libConfig)


set(libDataCore_FOUND TRUE CACHE BOOL "libDataCore found")
set(libDataCore_INCLUDE_DIRS ${libDataCore_INCLUDE_DIRS} "${libDataCore_DIR}/include" CACHE STRING "libDataCore include")
set(libDataCore_LIBRARIES ${libDataCore_LIBRARIES} "libDataCore" CACHE STRING "libDataCore libraries")