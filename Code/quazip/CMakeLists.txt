cmake_minimum_required(VERSION 2.6)

project(quazip)

IF (WIN32)
  find_package(ZLIB REQUIRED)
  if (NOT ZLIB_FOUND)
    message(STATUS "ZLib not found")
  endif(NOT ZLIB_FOUND)
  if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
  endif(ZLIB_FOUND)
ENDIF(WIN32)

# QuaZIP: Nice Qt based decompression of zip files, GPL or LGPL license
set(QUAZIP_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/JlCompress.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ioapi.c
  ${CMAKE_CURRENT_SOURCE_DIR}/quaadler32.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/quacrc32.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/quazip.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/quazipfile.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/quazipnewinfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/unzip.c
  ${CMAKE_CURRENT_SOURCE_DIR}/zip.c
)

set (QUAZIP_MOC_HDRS
  ${CMAKE_CURRENT_SOURCE_DIR}/quazipfile.h
)
qt4_wrap_cpp(QUAZIP_MOC_SRCS ${QUAZIP_MOC_HDRS})

add_library(quazip ${QUAZIP_MOC_SRCS} ${QUAZIP_SRCS})

message("{ZLIB_LIBRARY}: ${ZLIB_LIBRARY}")
target_link_libraries(quazip ${QT_LIBRARIES} ${ZLIB_LIBRARY})


install(TARGETS qtshanoir quazip 
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)


