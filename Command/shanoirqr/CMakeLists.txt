cmake_minimum_required(VERSION 2.8.10)

project(shanoirqr)


set(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_MODULE_PATH}
    )
find_package(docopt REQUIRED)
add_definitions("-std=c++11")

link_directories(${docopt_LIBRARY_DIRS})
message("docopt include dirs: ${docopt_INCLUDE_DIRS}")

## #############################################################################
## List Sources.
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

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS}
    ${docopt_INCLUDE_DIRS}
    ${DAO_INCLUDE_DIRS}
    ${QuaZip_INCLUDE_DIRS}
    )

## #############################################################################
## exe definition.
## #############################################################################

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_CFILES}
    )

target_link_libraries(${PROJECT_NAME}
    ${QT_LIBRARIES}
    DAO
    docopt
    )

set_lib_install_rules(${PROJECT_NAME})
