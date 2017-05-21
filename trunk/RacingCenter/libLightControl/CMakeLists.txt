cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

add_package_RC(${PROJNAME} libCommon)
add_package_RC(${PROJNAME} libConfig)

find_package(Qt5 REQUIRED Core)

include_directories(
    ./include
	${${PROJNAME}_INCLUDE_DIRS}
    )
	
file(GLOB libsrc src/*.cpp)
file(GLOB libheader include/libLightControl/*.h)

QT5_WRAP_CPP(SOURCES_MOC ${libheader})

add_library(${PROJNAME} STATIC ${libsrc} ${libheader} ${SOURCES_MOC})
	
set_target_properties(${PROJNAME} PROPERTIES FOLDER ${PROJNAME})

target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					  )
