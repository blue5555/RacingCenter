cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport Concurrent Svg OpenGL REQUIRED)

include_directories(
    ./include/libQwt
	${${PROJNAME}_INCLUDE_DIRS}
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Gui_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5PrintSupport_INCLUDE_DIRS}
	${Qt5Concurrent_INCLUDE_DIRS}
	${Qt5Svg_INCLUDE_DIRS}
	${Qt5OpenGL_INCLUDE_DIRS}
    )
	
file(GLOB libsrc src/*.cpp)
file(GLOB libheader include/libQwt/*.h)

QT5_WRAP_CPP(SOURCES_MOC ${libheader})

add_library(${PROJNAME} STATIC ${libsrc} ${libheader} ${SOURCES_MOC})
	
set_target_properties(${PROJNAME} PROPERTIES FOLDER ${PROJNAME})

target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					  ${Qt5Core_LIBRARIES}
					  ${Qt5Gui_LIBRARIES}
					  ${Qt5Widgets_LIBRARIES}
					  ${Qt5PrintSupport_LIBRARIES}
					  ${Qt5Concurrent_LIBRARIES}
					  ${Qt5Svg_LIBRARIES}
					  ${Qt5OpenGL_LIBRARIES}
					  )