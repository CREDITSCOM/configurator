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
    ui/ave.h \
    ui/validatorfactory.hpp \
    core/propertyserializer.hpp \
    core/scanner.hpp \
    structures/tree.hpp

SOURCES += \
    main.cpp \
    ui/configurator.cpp \
    core/serializer.cpp \
    core/converter.cpp \
    core/hostserializer.cpp \
    ui/ave.cpp \
    ui/validatorfactory.cpp \
    core/propertyserializer.cpp \
    core/scanner.cpp \
    structures/tree.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/configurator.ui

RESOURCES += \
    res.qrc

#for win app icon
win32 {
    RC_ICONS += resources/cs.ico
}
