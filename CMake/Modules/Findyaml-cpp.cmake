# Try to find the yaml-cpp library and header
# Once done this will define
#
# yaml-cpp_FOUND           - system has yaml-cpp and it can be used
# yaml-cpp_INCLUDE_DIRS    - directory where the header file can be found
# yaml-cpp_LIBRARY_DIRS    - Path where yaml-cpp required libs file can be found
#


set(yaml-cpp_FOUND FALSE)

find_path(yaml-cpp_INCLUDE_DIR yaml.h
  ""
  )

set(yaml-cpp_INCLUDE_DIRS
    ${yaml-cpp_INCLUDE_DIR}
    )

find_path(yaml-cpp_LIBRARY_DIR libyaml-cpp.so
  ""
  )

set(yaml-cpp_LIBRARY_DIRS
    ${yaml-cpp_LIBRARY_DIR}
    )

if(yaml-cpp_INCLUDE_DIR AND
    yaml-cpp_LIBRARY_DIR
    )
    set(yaml-cpp_FOUND TRUE)
    link_directories(${yaml-cpp_LIBRARY_DIRS})
endif()
