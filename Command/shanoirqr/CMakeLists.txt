project(shanoirqr)


set(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_MODULE_PATH}
    )
find_package(docopt REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(QuaZip REQUIRED)


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


## #############################################################################
## exe definition.
## #############################################################################

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_CFILES}
    )

## #############################################################################
## include directorie.
## #############################################################################

target_include_directories(${PROJECT_NAME} PUBLIC
    ${${PROJECT_NAME}_INCLUDE_DIRS}
    ${docopt_INCLUDE_DIRS}
    ${yaml-cpp_INCLUDE_DIRS}
    )

## #############################################################################
## Link
## #############################################################################

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Network
    Qt5::Xml
    DAO
    docopt
    yaml-cpp
    )

## #############################################################################
## install
## #############################################################################

set_lib_install_rules(${PROJECT_NAME})
