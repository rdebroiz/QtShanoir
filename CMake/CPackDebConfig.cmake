set(BUILD_SHARED_LIBS CACHE FORCE "Build QtShanoir with shared libraries." ON)
set(CPACK_GENERATOR ${CPACK_GENERATOR};DEB)
set(CPACK_DEB "ON")
if (BUILD_PACKAGE_BINARY)
  option(BUILD_PACKAGE_DEV "Package development distribution of QtShanoir" OFF)
  set(CPACK_PACKAGE_NAME "qtshanoir")
  set(CPACK_DEB_PACKAGE_DESCRIPTION "")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt4-gui (>=4.3)")
else (BUILD_PACKAGE_BINARY)
    option(BUILD_PACKAGE_BINARY "Package binary distribution of QtShanoir" OFF)
    set(CPACK_PACKAGE_NAME "qtshanoir-dev")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "QtShanoir provides widgets for Shanoir support, This package is for development use")
    set(CPACK_PACKAGE_FILE_NAME "qtshanoir-dev-${QTSHANOIR_VERSION_MAJOR}.${QTSHANOIR_VERSION_MINOR}.${QTSHANOIR_VERSION_PATCH}")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "qtshanoir (>=0.1), cmake (>=2.6)")
endif(BUILD_PACKAGE_BINARY)