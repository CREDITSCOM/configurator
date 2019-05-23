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
    ui/multiplevalidatoredit.hpp \
    ui/validatorfactory.hpp \
    core/propertyserializer.hpp \
    core/scanner.hpp \
    structures/tree.hpp \
    ui/validators/ipv4validator.hpp \
    ui/validators/ipv6validator.hpp \
    ui/validators/portvalidator.hpp

SOURCES += \
    main.cpp \
    ui/configurator.cpp \
    core/serializer.cpp \
    core/converter.cpp \
    core/hostserializer.cpp \
    ui/ave.cpp \
    ui/multiplevalidatoredit.cpp \
    ui/validatorfactory.cpp \
    core/propertyserializer.cpp \
    core/scanner.cpp \
    structures/tree.cpp \
    ui/validators/ipv4validator.cpp \
    ui/validators/ipv6validator.cpp \
    ui/validators/portvalidator.cpp

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
