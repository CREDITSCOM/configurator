QT += core gui widgets testlib

if (MSVC) {
    QMAKE_CXXFLAGS += -std=c++17 /std:c++17
} else {
    CONFIG += c++17
}

HEADERS += \
    test_hostserializer.hpp \
    ../src/core/common.hpp \
    ../src/core/converter.hpp \
    ../src/core/hostserializer.hpp \
    ../src/core/serializer.hpp \
    ../src/core/scanner.hpp \
    ../src/structures/tree.hpp \
    test_scanner.hpp

SOURCES += \
    tests.cpp \
    test_hostserializer.cpp \
    ../src/core/converter.cpp \
    ../src/core/hostserializer.cpp \
    ../src/core/serializer.cpp \
    ../src/core/scanner.cpp \
    ../src/structures/tree.cpp \
    test_scanner.cpp

INCLUDEPATH += \
    ../src
