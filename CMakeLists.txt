cmake_minimum_required (VERSION 3.10)
project(DDSense VERSION 0.1.0
                DESCRIPTION "DDS-based Sensor Data Pipeline"
                LANGUAGES CXX)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    message(STATUS "Found ccache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif ()

## Project Options
option(BUILD_TESTING "Build tests" OFF)
option(ENABLE_LOGGING "Enable logging module" ON)

# Fast DDS
option(BUILD_FAST_DEPENDENCIES "Build Fast DDS dependencies" OFF)
option(BUILD_FAST_DDS "Build Fast DDS" OFF)
option(FAST_DDS_SAMPLE "Build Fast DDS HelloWorld sample" OFF)

## Set compiler to use c++ 17 features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
      "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

## Use GNUInstalDirs to install libraries into correct location on all platforms
include(GNUInstallDirs)

## Put all binary files into /bin and libraries into /lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

message(STATUS "Enable logging: ${ENABLE_LOGGING}")

## Build tests
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME AND BUILD_TESTING)
  enable_testing()
  include(GoogleTest)
  set(BUILD_TESTS ON)
  message(STATUS "Tests will be built")
else ()
  set(BUILD_TESTS OFF)
  message(STATUS "Tests will not be built")
endif ()

add_subdirectory(third_party)

## Add libraries
add_executable(main
    src/main.cpp
    src/project_class.cpp)
target_include_directories(main PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

if (BUILD_TESTS)
  add_subdirectory(test)
endif ()