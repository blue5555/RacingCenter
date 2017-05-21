cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

add_package_RC(${PROJNAME} libCommon)

include_directories(
    ./include/libConfig
	${${PROJNAME}_INCLUDE_DIRS}
    )
	
file(GLOB libsrc src/*.cpp include/libConfig/*.h)
	
add_library(${PROJNAME} STATIC ${libsrc})

set_target_properties(${PROJNAME} PROPERTIES FOLDER ${PROJNAME})

target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					 )