QT += core gui widgets testlib

if (MSVC) {
    QMAKE_CXXFLAGS += -std=c++17 /std:c++17
} else {
    CONFIG += c++17
}

HEADERS += \

SOURCES += \
    tests.cpp
