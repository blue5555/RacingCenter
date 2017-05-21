cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

add_package_RC(${PROJNAME} libCommon)
add_package_RC(${PROJNAME} libConfig)
add_package_RC(${PROJNAME} libDatabase)

include_directories(
    ./include/libDataCore
	${${PROJNAME}_INCLUDE_DIRS}
    )
	
file(GLOB libsrc src/*.cpp)
file(GLOB libheader include/libDataCore/*.h)
	
add_library(${PROJNAME} STATIC ${libsrc} ${libheader})

set_target_properties(${PROJNAME} PROPERTIES FOLDER ${PROJNAME})

target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					  )