cmake_minimum_required(VERSION 2.8.11)

## #############################################################################
## List Sources
## #############################################################################

list_source_files(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}
  Resources
  )

## #############################################################################
## include directorie.
## #############################################################################

list_header_directories_to_include(${PROJECT_NAME}
  ${${PROJECT_NAME}_HEADERS}
  )

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS}
  ${quazip_INCLUDE_DIRS}
  ${QT_INCLUDE_DIRS}
  )

set(${PROJECT_NAME}_INCLUDE_DIRS
  ${${PROJECT_NAME}_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  PARENT_SCOPE)


## #############################################################################
## Lib definition.
## #############################################################################

message("${PROJECT_NAME}_QRC ${${PROJECT_NAME}_QRC}")

qt4_add_resources(${PROJECT_NAME}_QRC
  ${${PROJECT_NAME}_QRC}
  )

qt4_wrap_ui(${PROJECT_NAME}_UI
  ${${PROJECT_NAME}_UI}
  )

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_CFILES}
  ${${PROJECT_NAME}_QRC}
  ${${PROJECT_NAME}_UI}
  )

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  quazip
  )


set_lib_install_rules(${PROJECT_NAME})
