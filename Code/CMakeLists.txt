set(QTSHANOIR_RCCS
    ${QTSHANOIR_SOURCE_DIR}/Resources/qtshanoir.qrc
)

set(SAMPLE_SRCS
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirSettingsWidget.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirUploadWidget.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirSearchWidget.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirWebService.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirProgressWidget.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirTreeWidget.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoir.cpp
  ${QTSHANOIR_SOURCE_DIR}/Code/QtSoap.cpp
)

set(SAMPLE_HDRS
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirSettingsWidget.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirUploadWidget.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirSearchWidget.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirWebService.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirProgressWidget.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirTreeWidget.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoir.h
  ${QTSHANOIR_SOURCE_DIR}/Code/QtSoap.h
)

set(SAMPLE_UIS
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoir.ui
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoirprogress.ui
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoirsettingswidget.ui
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoirsearchwidget.ui
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoiruploadwidget.ui
  ${QTSHANOIR_SOURCE_DIR}/Code/qtshanoirtreewidget.ui
)

set(SAMPLE_MOC_HDRS ${SAMPLE_HDRS})

set(QTSHANOIR_SRCS
  ${QTSHANOIR_SOURCE_DIR}/Code/QtShanoirSettings.cpp
)

qt4_add_resources(QTSHANOIR_RCC_SRCS ${QTSHANOIR_RCCS})
qt4_wrap_ui( SAMPLE_UI_HDRS ${SAMPLE_UIS})
qt4_wrap_cpp( SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS})

include_directories(${CMAKE_BINARY_DIR} ${QTSHANOIR_SOURCE_DIR}/Code/ ${QTSHANOIR_BINARY_DIR})

add_library(qtshanoir ${QTSHANOIR_SRCS} ${SAMPLE_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_UI_HDRS} ${QTSHANOIR_RCC_SRCS})

target_link_libraries(qtshanoir ${QT_LIBRARIES} ${QT_QTNETWORK_LIBRARY} ${QT_QTXML_LIBRARY} quazip)