cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

find_package(Qt5 COMPONENTS Core Gui Xml REQUIRED)

include_directories(
    ./include/libCommon
	${${PROJNAME}_INCLUDE_DIRS}
	${Qt5Core_INCLUDE_DIRS} 
	${Qt5Gui_INCLUDE_DIRS} 
	${Qt5Xml_INCLUDE_DIRS}
    )
	
file(GLOB libsrc src/*.cpp include/libCommon/*.h)
	
add_library(${PROJNAME} STATIC ${libsrc})

set_target_properties(${PROJNAME} PROPERTIES FOLDER ${PROJNAME})

target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					  ${Qt5Core_LIBRARIES} 
					  ${Qt5Gui_LIBRARIES} 
					  ${Qt5Xml_LIBRARIES}
					  )