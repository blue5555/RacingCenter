#####################################################################
## Makro definitions for path handling
#####################################################################
macro(MACRO_GETENV_WIN_PATH var name)
   set(${var} $ENV{${name}})
   string( REGEX REPLACE "\\\\" "/" ${var} ${${var}} )
endmacro(MACRO_GETENV_WIN_PATH var name)

macro(MACRO_GET_WIN_PATH var)
   string( REGEX REPLACE "/" "\\\\" var ${var} )
endmacro(MACRO_GET_WIN_PATH var)

macro(SEARCH_CONFIG_FILES result curdir)
  #message(STATUS "${curdir}")
  FILE(GLOB children ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
	IF(IS_DIRECTORY ${child})
		IF(NOT ${child} STREQUAL "${CMAKE_BINARY_DIR}")
			SEARCH_SINGLE_FOLDER(${result} ${child})
		ENDIF()
	ELSE()
	ENDIF(IS_DIRECTORY ${child})
  ENDFOREACH()
endmacro()

macro(SEARCH_SINGLE_FOLDER return_list curdir)
    FILE(GLOB_RECURSE new_list ${curdir}/*.cmake)
    SET(dir_list "")
	#message(STATUS ${new_list})
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        #message(STATUS ${dir_path})
		set(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    LIST(APPEND ${return_list} ${dir_list})
endmacro()

macro(find_package_RC moduleName)
	find_package(${moduleName} PATHS ${RC_MODULES} REQUIRED)
endmacro()

macro(add_package_RC filterName moduleName)
	set(filter_include "")
	set(filter_libs "")
	if(NOT ${moduleName}_FOUND)
		#message(STATUS "add package SP: ${moduleName}")
		find_package_RC(${moduleName})
	endif()
	
	set(${filterName}_INCLUDE_DIRS ${${filterName}_INCLUDE_DIRS} ${${moduleName}_INCLUDE_DIRS})
	set(${filterName}_LIBRARIES ${${filterName}_LIBRARIES} ${${moduleName}_LIBRARIES})
	
	set(filter_include ${${filterName}_INCLUDE_DIRS})
	#set(filter_libs ${${filterName}_LIBRARIES})
	
	LIST(REMOVE_DUPLICATES filter_include)
	set(${filterName}_INCLUDE_DIRS ${filter_include})

endmacro()

macro(add_package filterName moduleName)
	set(filter_include "")
	set(filter_libs "")
	
	if(NOT ${moduleName}_FOUND)	
		find_package(${moduleName} REQUIRED)
	endif()
	set(${filterName}_INCLUDE_DIRS ${${filterName}_INCLUDE_DIRS} ${${moduleName}_INCLUDE_DIRS})
	set(${filterName}_LIBRARIES ${${filterName}_LIBRARIES} ${${moduleName}_LIBRARIES})
	set(filter_include ${${filterName}_INCLUDE_DIRS})
	#set(filter_libs ${${filterName}_LIBRARIES})
	
	LIST(REMOVE_DUPLICATES filter_include)
	set(${filterName}_INCLUDE_DIRS ${filter_include})
endmacro()