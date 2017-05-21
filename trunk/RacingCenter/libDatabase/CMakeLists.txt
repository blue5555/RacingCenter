cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

find_package(Qt5 REQUIRED Sql)

add_package_RC(${PROJNAME} libCommon)
add_package_RC(${PROJNAME} libConfig)
add_package_RC(${PROJNAME} libDataCore)

include_directories(
    ./include/libDatabase
	${${PROJNAME}_INCLUDE_DIRS}
	${Qt5Sql_INCLUDE_DIRS}
    )
	
file(GLOB libsrc src/*.cpp include/libDatabase/*.h)
	
add_library(${PROJNAME} STATIC ${libsrc})

set_target_properties(${PROJNAME} PROPERTIES FOLDER ${PROJNAME})

target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					  ${Qt5Sql_LIBRARIES}
					  )