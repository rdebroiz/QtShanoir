cmake_minimum_required(VERSION 2.6)

project(quazip)


# Use system zlib on unix and Qt ZLIB on Windows
if(UNIX)
  find_package(ZLIB REQUIRED)
else()
  set(ZLIB_INCLUDE_DIRS "Qt/src/3rdparty/zlib" CACHE STRING "Path to ZLIB headers of Qt")
  set(ZLIB_LIBRARIES "")
  if(not exists "${ZLIB_INCLUDE_DIRS}/zlib.h")
    message("Please specify a valid zlib include dir")
  endif(not exists "${ZLIB_INCLUDE_DIRS}/zlib.h")
endif()

find_package(Qt4 REQUIRED COMPONENTS QtNetwork QtXml)
include(${QT_USE_FILE})

## #############################################################################
## List Sources
## #############################################################################

list_source_files(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

## #############################################################################
## include directorie.
## #############################################################################

list_header_directories_to_include(${PROJECT_NAME}
  ${${PROJECT_NAME}_HEADERS}
  )

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

set(${PROJECT_NAME}_INCLUDE_DIRS
  ${${PROJECT_NAME}_INCLUDE_DIRS}
  ${QT_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  PARENT_SCOPE)

## #############################################################################
## Lib definition.
## #############################################################################

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_CFILES}
  )

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${ZLIB_LIBRARIES}
  )

set_lib_install_rules(${PROJECT_NAME})
