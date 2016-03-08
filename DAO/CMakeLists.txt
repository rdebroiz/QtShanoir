cmake_minimum_required(VERSION 2.8.10)

project(DAO)

find_package(QuaZip REQUIRED)

## #############################################################################
## List Sources
## #############################################################################

list_source_files(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

## #############################################################################
## include directories.
## #############################################################################

list_header_directories_to_include(${PROJECT_NAME}
    ${${PROJECT_NAME}_HEADERS}
    )

## #############################################################################
## Lib definition.
## #############################################################################

add_library(${PROJECT_NAME} SHARED
    ${${PROJECT_NAME}_CFILES}
    )

## #############################################################################
## include directorie.
## #############################################################################

target_include_directories(${PROJECT_NAME} PUBLIC
    ${${PROJECT_NAME}_INCLUDE_DIRS}
    ${QuaZip_INCLUDE_DIRS}
    )

set(${PROJECT_NAME}_INCLUDE_DIRS
    ${${PROJECT_NAME}_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    PARENT_SCOPE
    )

## #############################################################################
## Link
## #############################################################################

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    Qt5::Xml
    quazip
    )

## #############################################################################
## install
## #############################################################################

set_lib_install_rules(${PROJECT_NAME})
