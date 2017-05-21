cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

add_package_RC(${PROJNAME} libCommon)
add_package_RC(${PROJNAME} libCore)
add_package_RC(${PROJNAME} libStartlight)
add_package_RC(${PROJNAME} libLightControl)
add_package_RC(${PROJNAME} libStatistics)

find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport Concurrent Svg OpenGL SerialPort Xml Multimedia REQUIRED)

include_directories(
    ./include
	${${PROJNAME}_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Xml_INCLUDE_DIRS}
	${Qt5SerialPort_INCLUDE_DIRS}
	${Qt5Multimedia_INCLUDE_DIRS}
    )

file(GLOB libsrc src/*.cpp)
file(GLOB libheader include/*.h)

QT5_WRAP_UI (UIS_HDRS
			 forms/mainwindow.ui)
	
QT5_ADD_RESOURCES (ResourceSources forms/mainwindow.qrc)

QT5_WRAP_CPP(SOURCES_MOC ${libheader})

add_executable(${PROJNAME} ${libsrc} ${libheader} ${UIS_HDRS} ${ResourceSources} ${SOURCES_MOC})
	
set_target_properties(${PROJNAME} PROPERTIES FOLDER gui/mainmenu)
	
target_link_libraries(${PROJNAME}
					  ${${PROJNAME}_LIBRARIES}
					  ${Qt5Widgets_LIBRARIES}
					  ${Qt5Xml_LIBRARIES}
					  ${Qt5SerialPort_LIBRARIES}
					  ${Qt5Multimedia_LIBRARIES}
					  )