cmake_minimum_required (VERSION 3.6)
project (Algorithms-Test)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Configuration types" FORCE)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glog")
  message(FATAL_ERROR "The glog submodule directory is missing! "
    "You probably did not clone the project with --recursive, or first checked out "
    "before it was added. It is possible to recover by running "
    "\"git submodule update --init --recursive\"")
endif()

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON) 

## 3rd party dependencies
#######################################################################################
if(WIN32)
  add_definitions( -D GOOGLE_GLOG_DLL_DECL= )
endif()
set(WITH_GFLAGS OFF CACHE BOOL "Use gflags")
set(BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
set(BUILD_TESTING OFF CACHE BOOL "Build the glog unit test.")
#message(STATUS "OPT BEFORE=${BUILD_TESTING}")
add_subdirectory(thirdparty/glog)
#message(STATUS "OPT AFTER=${BUILD_TESTING}")
set_property(TARGET glog PROPERTY FOLDER "dependencies")
include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glog/src
  ${CMAKE_BINARY_DIR}/thirdparty/glog
)

## source files
#######################################################################################
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/
  ${CMAKE_CURRENT_SOURCE_DIR}/common/
  ${CMAKE_CURRENT_SOURCE_DIR}/common/profiler.h
)

file(GLOB  Common_SRC_FILES
	${CMAKE_SOURCE_DIR}/common/profiler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/common/profiler.h
)

file(GLOB  SORT_SRC_FILES
	${CMAKE_SOURCE_DIR}/sort.cpp
)
file(GLOB  List_SRC_FILES
	${CMAKE_SOURCE_DIR}/list.cpp
)
file(GLOB  Array_SRC_FILES
	${CMAKE_SOURCE_DIR}/array.cpp
)
file(GLOB  Tree_SRC_FILES
	${CMAKE_SOURCE_DIR}/binTree.cpp
)
file(GLOB  Mem_SRC_FILES
	${CMAKE_SOURCE_DIR}/mem.cpp
)


## Output include directory for debug
#######################################################################################
get_property(includes DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${includes})
    message(STATUS "include dir='${dir}'")
endforeach()


## macro definition
#######################################################################################
macro(group_src_files src_files target)
	foreach(f ${src_files})
		message(STATUS "check parameters original source file :${f}")
	endforeach()
	message(STATUS "check parameters new group name :${target}")
    
    foreach(f ${src_files})
		# Get the path of the file relative to ${DIRECTORY},
		# then alter it (not compulsory)
		file(RELATIVE_PATH SRCGR ${CMAKE_SOURCE_DIR} ${f})
		set(SRCGR "${target}/${SRCGR}")
		
		# Extract the folder, ie remove the filename part
		string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

		# Source_group expects \\ (double antislash), not / (slash)
		string(REPLACE / \\ SRCGR ${SRCGR})
		source_group("${SRCGR}" FILES ${f})
		message(STATUS "New group name :${SRCGR}")
	endforeach()
endmacro()

## Regroup source code structure
#######################################################################################
group_src_files("${Common_SRC_FILES}" "Shared")
group_src_files("${SORT_SRC_FILES}"  "Sort-Test")
group_src_files("${List_SRC_FILES}"  "List-Test")
group_src_files("${Array_SRC_FILES}" "Array-Test")
group_src_files("${Tree_SRC_FILES}"  "Tree-Test")
group_src_files("${Mem_SRC_FILES}"  "Mem-Test")

## custom settings
#######################################################################################
set(ENABLE_HIDECONSOLE_BUILD FALSE CACHE BOOL "TRUE to hide console for Windows sys" FORCE)
if(ENABLE_HIDECONSOLE_BUILD)
	message(STATUS "Console is hidden")
else()
	message(STATUS "Console is visible")
endif()

## preproc
#######################################################################################
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-DBX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS=1)
add_definitions(-D__STDC_LIMIT_MACROS)
add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-DUSE_DL_PREFIX)
if(${ENABLE_HIDECONSOLE_BUILD})
	if(MSVC)
		add_definitions(-DWIN32)
		add_definitions(-D_WIN32)
		add_definitions(-DNOMINMAX)
	endif()
endif()

if(WINDOWS)
  set(GUI_TYPE WIN32)
elseif(MACOSX)
  set(GUI_TYPE MACOSX_BUNDLE)
endif()

## external libraries
#######################################################################################
find_package(OpenMP)
if(OPENMP_FOUND)
	message(STATUS "OpenMP found")
	if(MSVC)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /openmp")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")
		#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	endif()
endif()

## link options
#######################################################################################
if(MSVC)
    if(ENABLE_HIDECONSOLE_BUILD)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE ")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    endif()
endif(MSVC)

SET(LINK_OPTIONS " ")


## macro definition
#######################################################################################
macro(default_property EXE_NAME)
    message(STATUS "set default output property of target:${EXE_NAME}")
    set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin )
    set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin )
    set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin )
    set_target_properties(${EXE_NAME} PROPERTIES DEBUG_POSTFIX "_d")
    set_target_properties(${EXE_NAME} PROPERTIES RELWITHDEBINFO_POSTFIX "RelWithDebInfo")
    set_target_properties(${EXE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
	if(ENABLE_HIDECONSOLE_BUILD)
		if(WINDOWS)
			set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
			set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
		endif()
	endif()
endmacro()


## Source file Not need to list
#######################################################################################
file ( GLOB GTEST_SOURCE
    ${CMAKE_SOURCE_DIR}/thirdparty/gtest/*.h
    ${CMAKE_SOURCE_DIR}/thirdparty/gtest/*.cc
)

## target: Sort
#######################################################################################
set(EXE_NAME "Sort-Test")
add_executable(${EXE_NAME} ${SORT_SRC_FILES} ${Common_SRC_FILES})
target_link_libraries(${EXE_NAME} glog)
default_property(${EXE_NAME})

## target: List
#######################################################################################
set(EXE_NAME "List-Test")
add_executable(${EXE_NAME} ${List_SRC_FILES})
target_link_libraries(${EXE_NAME} glog)
default_property(${EXE_NAME})

## target: Array
#######################################################################################
set(EXE_NAME "Array-Test")
add_executable(${EXE_NAME} ${Array_SRC_FILES} ${GTEST_SOURCE})
target_link_libraries(${EXE_NAME} glog)
default_property(${EXE_NAME})

## target: Tree
#######################################################################################
set(EXE_NAME "Tree-Test")
add_executable(${EXE_NAME} ${Tree_SRC_FILES} ${GTEST_SOURCE})
target_link_libraries(${EXE_NAME} glog)
default_property(${EXE_NAME})

## target: Memory
#######################################################################################
set(EXE_NAME "Mem-Test")
add_executable(${EXE_NAME} ${Mem_SRC_FILES} ${GTEST_SOURCE})
target_link_libraries(${EXE_NAME} glog)
default_property(${EXE_NAME})

#######################################################################################
##For reference
##https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties
#######################################################################################
