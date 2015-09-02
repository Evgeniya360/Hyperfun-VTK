QT       += core

TARGET = cppinterpreter_lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    hfinterpreter.cpp
   

HEADERS += \
    hfinterpreter.h


INCLUDEPATH += "$$PWD/../interpreter_lib"
INCLUDEPATH += $$PWD/../include

LIBS +=  -lBLAS_nowrap -lclapack_nowrap -llibf2c 

    DEFINES += _CRT_SECURE_NO_WARNINGS

