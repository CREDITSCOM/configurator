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
    core/serializer.hpp \
    core/converter.hpp \
    core/hostserializer.hpp \
    core/utils.hpp \
    ui/ave.h

SOURCES += \
    main.cpp \
    ui/configurator.cpp \
    core/serializer.cpp \
    core/converter.cpp \
    core/hostserializer.cpp \
    ui/ave.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/configurator.ui

RESOURCES += \
    res.qrc
