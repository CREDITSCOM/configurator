QT += core gui widgets

if (MSVC) {
  QMAKE_CXXFLAGS += -std=c++17 /std:c++17
} else {
  CONFIG += c++17
}

CONFIG += app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    ui/configurator.hpp \
    core/common.hpp \
    ui/configurator.hpp

SOURCES += \
    main.cpp \
    ui/configurator.cpp \
    ui/configurator.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/configurator.ui
