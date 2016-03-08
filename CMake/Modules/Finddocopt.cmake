# Try to find the docopt library and header
# Once done this will define
#
# docopt_FOUND           - system has docopt and it can be used
# docopt_INCLUDE_DIRS    - directory where the header file can be found
# docopt_LIBRARY_DIRS    - Path where docopt required libs file can be found
#


set(docopt_FOUND FALSE)

find_path(docopt_INCLUDE_DIR docopt.h
  ""
  )

set(docopt_INCLUDE_DIRS
    ${docopt_INCLUDE_DIR}
    )

find_path(docopt_LIBRARY_DIR libdocopt.so
  ""
  )

set(docopt_LIBRARY_DIRS
    ${docopt_LIBRARY_DIR}
    )

if(docopt_INCLUDE_DIR AND
    docopt_LIBRARY_DIR
    )
    set(docopt_FOUND TRUE)
    link_directories(${docopt_LIBRARY_DIRS})
endif()
