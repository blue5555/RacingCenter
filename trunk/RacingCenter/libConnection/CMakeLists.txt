cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

include_directories(
    ./include
	${COMMON_INCLUDE_DIRS}
	${CORE_INCLUDE_DIRS}
	${CONFIG_INCLUDE_DIRS}
	${DATABASE_INCLUDE_DIRS}
	${Qt5Core_INCLUDE_DIRS}
	${Qt5SerialPort_INCLUDE_DIRS}
	${Qt5Network_INCLUDE_DIRS}
    )

set(CONNECTION_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include" PARENT_SCOPE)
	
file(GLOB libsrc src/*.cpp include/*.h)
	
add_library(${PROJNAME} STATIC ${libsrc})

set_target_properties(${PROJNAME} PROPERTIES FOLDER connection)

target_link_libraries(${PROJNAME}
					  ${Qt5Core_LIBRARIES}
					  ${Qt5SerialPort_LIBRARIES}
					  ${Qt5Network_LIBRARIES}
					 )