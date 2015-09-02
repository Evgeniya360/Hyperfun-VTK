QT       += core

TARGET = interpreter_lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    int_serial.c \
    int_array.c \
    int_calc.c \
    int_global.c \
    int_list.c \
    int_parse_N.c \
    int_scanner.c
   



INCLUDEPATH += "$$PWD/../hflibrary_lib"
INCLUDEPATH += $$PWD/../include

LIBS +=  -lBLAS_nowrap -lclapack_nowrap -llibf2c 

    DEFINES += _CRT_SECURE_NO_WARNINGS

HEADERS += \
    general.h

