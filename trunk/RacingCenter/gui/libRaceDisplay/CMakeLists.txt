cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

add_package_RC(${PROJNAME} libCommon)
add_package_RC(${PROJNAME} libConfig)
add_package_RC(${PROJNAME} libDataCore)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(
    ./include
	${${PROJNAME}_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
    )

#file(GLOB libsrc src/*.cpp)
#file(GLOB libheader include/libRaceDisplay/*.h)

set(libsrc
	src/cRaceDisplaySimple.cpp
	src/cLabel.cpp
	src/cProgressBar.cpp
	)

set(libheader
	include/libRaceDisplay/cRaceDisplaySimple.h
	include/libRaceDisplay/cLabel.h
	include/libRaceDisplay/cProgressBar.h
	)

QT5_WRAP_UI (UIS_HDRS 
			 forms/racedisplay.ui)
	
QT5_ADD_RESOURCES (ResourceSources forms/racedisplay.qrc)

QT5_WRAP_CPP(SOURCES_MOC ${libheader})

add_library(${PROJNAME} ${libsrc} ${libheader} ${UIS_HDRS} ${ResourceSources} ${SOURCES_MOC} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
	
set_target_properties(${PROJNAME} PROPERTIES FOLDER gui/racedisplay)
	
target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					  ${Qt5Widgets_LIBRARIES}
					  ${Qt5Gui_LIBRARIES}
					  )