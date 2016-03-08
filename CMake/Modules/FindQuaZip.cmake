# Try to find the QuaZip library and header
# Once done this will define
#
# QuaZip_FOUND           - system has QuaZip and it can be used
# QuaZip_INCLUDE_DIRS    - directory where the header file can be found
# QuaZip_LIBRARY_DIRS    - Path where QuaZip required libs file can be found
#


set(QuaZip_FOUND FALSE)

find_path(QuaZip_INCLUDE_DIR quazip.h
  ""
  )

set(QuaZip_INCLUDE_DIRS
    ${QuaZip_INCLUDE_DIR}
    )
if(WIN32)
    find_path(QuaZip_LIBRARY_DIR quazip.dll
      ""
      )
else()
find_path(QuaZip_LIBRARY_DIR libquazip.so
  ""
  )
find_path(QuaZip_LIBRARY_DIR libquazip.a
  ""
  )
endif()

set(QuaZip_LIBRARY_DIRS
    ${QuaZip_LIBRARY_DIR}
    )

if(QuaZip_INCLUDE_DIR AND
    QuaZip_LIBRARY_DIR
    )
    set(QuaZip_FOUND TRUE)
    link_directories(${QuaZip_LIBRARY_DIRS})
endif()
