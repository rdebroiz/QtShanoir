cmake_minimum_required(VERSION 2.8.11)

## #############################################################################
## List Sources
## #############################################################################

list_source_files(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

message("${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}")
message("QUAZIP_LIBRARIES ${QUAZIP_LIBRARIES}")

## #############################################################################
## include directorie.
## #############################################################################

list_header_directories_to_include(${PROJECT_NAME}
  ${${PROJECT_NAME}_HEADERS}
  )

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS}
  ${QUAZIP_LIBRARIES}
  ${QUAZIP_INCLUDE_DIRS}
  )

## #############################################################################
## Lib definition.
## #############################################################################

qt5_add_resources(${PROJECT_NAME}_QRC
  ${${PROJECT_NAME}_QRC}
  )

qt5_wrap_ui(${PROJECT_NAME}_UI
  ${${PROJECT_NAME}_UI}
  )

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_CFILES}
  ${${PROJECT_NAME}_QRC}
  ${${PROJECT_NAME}_UI}
  )

target_link_libraries(${PROJECT_NAME}
  Qt5::Core
  Qt5::Widgets
  Qt5::Network
  ${QUAZIP_LIBRARIES}
  )


set_lib_install_rules(${PROJECT_NAME})