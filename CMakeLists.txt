cmake_minimum_required(VERSION 2.8.11)
project(qtshanoir)


## #############################################################################
## Version number.
## #############################################################################

set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_PATCH 0)
set(${PROJECT_NAME}_VERSION
    ${PROJECT_NAME}_VERSION_MAJOR.${PROJECT_NAME}_VERSION_MINOR.${PROJECT_NAME}_VERSION_PATCH
    )
add_definitions(-D${PROJECT_NAME}_VERSION="${${PROJECT_NAME}_VERSION}")


## #############################################################################
## Additionals modules
## #############################################################################

set(${PROJECT_NAME}_CMAKE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake
  ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules
  )

set(CMAKE_MODULE_PATH
  ${${PROJECT_NAME}_CMAKE_DIR}
  ${CMAKE_MODULE_PATH}
  )

include(list_source_files)
include(list_header_directories_to_include)
include(set_lib_install_rules)


## #############################################################################
## Find packages.
## #############################################################################

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

find_package(QuaZip REQUIRED)

## #############################################################################
## Qt Automoc
## #############################################################################

set(CMAKE_AUTOMOC ON)
#   Find includes in corresponding build (and source) directories
#   (nedded for generated files)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


## #############################################################################
## Configure the application
## #############################################################################

add_subdirectory(Code)
