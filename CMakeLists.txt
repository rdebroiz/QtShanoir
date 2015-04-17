cmake_minimum_required(VERSION 2.6)

project(QTSHANOIR)

set(QTSHANOIR_VERSION_MAJOR "0")
set(QTSHANOIR_VERSION_MINOR "1")
set(QTSHANOIR_VERSION_PATCH "0")

#add_definitions(-g -Wno-deprecated)

# option(BUILD_DOCUMENTATION "Build QtShanoir Documentation" OFF)
option(BUILD_PACKAGE "Configure QtShanoir packaging" OFF)
option(BUILD_DEMO "Build example application" OFF)
option(BUILD_SHARED_LIBS "Build QtShanoir with shared libraries." ON)
option(BUILD_DOCUMENTATION "Build QtShanoir Documentation" OFF)

if (BUILD_PACKAGE)
  include (${QTSHANOIR_SOURCE_DIR}/CMake/CPackConfig.cmake)
endif(BUILD_PACKAGE)

set(EXECUTABLE_OUTPUT_PATH "${QTSHANOIR_BINARY_DIR}/bin")
if (WIN32 AND BUILD_SHARED_LIBS)
  set(LIBRARY_OUTPUT_PATH "${QTSHANOIR_BINARY_DIR}/bin")
else (WIN32 AND BUILD_SHARED_LIBS)
  set(LIBRARY_OUTPUT_PATH "${QTSHANOIR_BINARY_DIR}/lib")
endif (WIN32 AND BUILD_SHARED_LIBS)
mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)


#Configure doxygen documentation
if(BUILD_DOCUMENTATION)
  add_subdirectory(Documentation/Doxygen)
endif(BUILD_DOCUMENTATION)

set (QTSHANOIR_CMAKE_MODULE_PATH ${QTSHANOIR_SOURCE_DIR}/CMake)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${QTSHANOIR_CMAKE_MODULE_PATH}" ${PROJECT_SOURCE_DIR})

include (${QTSHANOIR_SOURCE_DIR}/CMake/QtShanoirSettings.cmake)

find_package( Qt4 REQUIRED COMPONENTS QtCore QtGui QtNetwork QtXml)
if(QT4_FOUND)
  set(QT_USE_QTNETWORK true)
  set(QT_USE_QTXML true)
  include(${QT_USE_FILE})
endif(QT4_FOUND)

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/qtshanoir)

install(TARGETS qtshanoir quazip 
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

subdirs(Code/quazip)
subdirs(Code)

if(BUILD_DEMO)
  add_subdirectory(Demo)
endif(BUILD_DEMO)







