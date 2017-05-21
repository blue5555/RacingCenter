cmake_minimum_required(VERSION 2.8.9)

# cmake file for building Stadtpilot Package

# CMake compatibility issues: don't modify this, please!
CMAKE_MINIMUM_REQUIRED( VERSION 2.8.7 FATAL_ERROR)
SET(CMAKE_USE_RELATIVE_PATHS true)

#####################################################################
## allow more human readable "if then else" constructs
#####################################################################
SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )

#####################################################################
## Path to qt
#####################################################################
#set(ENV{QTDIR}          "C:/Qt/Qt5.3.2/5.3/msvc2010_opengl")

#####################################################################
## Path to cmake modules
#####################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" $ENV{QT_DIR})

#####################################################################
## include cmake_adtf makros 
#####################################################################
include(${CMAKE_SOURCE_DIR}/cmake/macros.cmake)

#####################################################################
## Project Racing Center
#####################################################################
project(RacingCenter)

#####################################################################
## search for stadtpilot cmake config modules
#####################################################################
SEARCH_CONFIG_FILES(RC_MODULES "${CMAKE_SOURCE_DIR}")

add_subdirectory(libCommon)
add_subdirectory(libConfig)
add_subdirectory(libSerialConnector)

add_subdirectory(libStatistics)

add_subdirectory(libQwt)

#add_subdirectory(libConnection)
add_subdirectory(libCore)
add_subdirectory(libDatabase)
add_subdirectory(libDataCore)
add_subdirectory(libCUAdapter)
add_subdirectory(libLightControl)

add_subdirectory(gui)