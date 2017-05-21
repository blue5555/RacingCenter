cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

find_package(Qt5 REQUIRED Core)

add_package_RC(${PROJNAME} libCommon)
add_package_RC(${PROJNAME} libConfig)
add_package_RC(${PROJNAME} libDatabase)
add_package_RC(${PROJNAME} libCUAdapter)
add_package_RC(${PROJNAME} libDataCore)
add_package_RC(${PROJNAME} libRaceDisplay)
add_package_RC(${PROJNAME} libRaceResults)
add_package_RC(${PROJNAME} libStartlight)
add_package_RC(${PROJNAME} libLightControl)

include_directories(
    ./include
	${CMAKE_CURRENT_BINARY_DIR}
	${${PROJNAME}_INCLUDE_DIRS}
    )

file(GLOB libsrc src/*.cpp)
file(GLOB libheader include/libCore/*.h)

QT5_WRAP_CPP(SOURCES_MOC ${libheader})

add_library(${PROJNAME} ${libsrc} ${libheader} ${SOURCES_MOC})

set_target_properties(${PROJNAME} PROPERTIES FOLDER ${PROJNAME})

target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					 )