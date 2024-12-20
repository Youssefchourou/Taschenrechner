TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += testable
CONFIG += test_coverage

SOURCES += \
    caculator_test.cpp \
    calculator.cpp \
    main.cpp \
    token.cpp

HEADERS += \
    calculator.h \
    token.h

INCLUDEPATH += $$PWD/extern/googletest/googletest/include \
               $$PWD/extern/googletest/googlemock/include

LIBS += -L$$PWD/extern/googletest/build/lib \
        -lgtest -lgtest_main

# Test Coverage Flags für Compiler und Linker
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage

# Qt Testlib hinzufügen
QT += testlib
