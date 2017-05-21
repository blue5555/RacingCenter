cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

include_directories(
    ./include
	${COMMON_INCLUDE_DIRS}
	${CORE_INCLUDE_DIRS}
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Svg_INCLUDE_DIRS}
	${Qt5Gui_INCLUDE_DIRS}
	${Qt5OpenGL_INCLUDE_DIRS}
    )

QT5_ADD_RESOURCES (ResourceSources forms/widgets.qrc)
	
file(GLOB libsrc src/*.cpp src/*/*.cpp src/*/*/*.cpp 
		         include/*.h include/*/*.h include/*/*/*.h)
	
add_library(${PROJNAME} STATIC ${libsrc} ${ResourceSources})

set_target_properties(${PROJNAME} PROPERTIES FOLDER gui/widgets)

target_link_libraries(${PROJNAME}
					  ${Qt5Core_LIBRARIES}
					  ${Qt5Gui_LIBRARIES}
					  ${Qt5SerialPort_LIBRARIES}
					  ${Qt5Widgets_LIBRARIES}
					  ${Qt5Svg_LIBRARIES}
					  ${Qt5OpenGL_LIBRARIES}
					 )