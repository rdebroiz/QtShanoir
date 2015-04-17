cmake_minimum_required(VERSION 2.6)

project(qtshanoir-demo)

add_definitions(-g -Wno-deprecated)

# find_package(QTSHANOIR REQUIRED)
# if (QTSHANOIR_FOUND)
#   include(${QTSHANOIR_USE_FILE})
# endif (QTSHANOIR_FOUND)


message("qtshanoir_INCLUDE_DIRS from Demo ${qtshanoir_INCLUDE_DIRS}")

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

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS}
  ${qtshanoir_INCLUDE_DIRS}
  )

## #############################################################################
## Lib definition.
## #############################################################################

qt5_wrap_ui(${PROJECT_NAME}_UI
  ${${PROJECT_NAME}_UI}
  )

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_CFILES}
  ${${PROJECT_NAME}_UI}
  )

target_link_libraries(${PROJECT_NAME}
  Qt5::Core
  Qt5::Widgets
  Qt5::Network
  Qt5::Xml
  ${QUAZIP_LIBRARIES}
  qtshanoir
  )

set_exe_install_rules(${PROJECT_NAME})
