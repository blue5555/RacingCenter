cmake_minimum_required (VERSION 2.6) 

get_filename_component(PROJNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJNAME})

include_directories(
    ./include
	${COMMON_INCLUDE_DIRS}
	${COMMON_WIDGETS_INCLUDE_DIRS}
	${CORE_INCLUDE_DIRS}
	${DATABASE_INCLUDE_DIRS}
	${CONFIG_INCLUDE_DIRS}
	${Qt5Core_INCLUDE_DIRS}
	${Qt5SerialPort_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Svg_INCLUDE_DIRS}
    )

#QT5_WRAP_UI (UIS_HDRS forms/startlight.ui)
	
qt5_add_resources (ResourceSources forms/driverDisplay.qrc)
	
file(GLOB libsrc src/*.cpp include/*.h)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

#if(WIN32)
	add_library(${PROJNAME} ${libsrc} ${UIS_HDRS} ${ResourceSources})
	
	set_target_properties(${PROJNAME} PROPERTIES FOLDER gui/driverDisplay)
	
	target_link_libraries(${PROJNAME}
						  #${Qt5Core_QTMAIN_LIBRARIES}
						  ${Qt5Widgets_LIBRARIES}
						  ${Qt5Svg_LIBRARIES}
					 	  #${Qt5Core_LIBRARIES}
					      #${Qt5SerialPort_LIBRARIES}
						  core
						  widgets
						  )
						  
	# Use the Widgets module from Qt 5.
	qt5_use_modules(${PROJNAME} Widgets)
	
#else ()
#endif()