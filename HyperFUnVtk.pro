#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T12:55:21
#
#-------------------------------------------------

QT       += core

QT       += gui

TARGET = VTKHyperfun
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

    DEFINES += _CRT_SECURE_NO_WARNINGS
SOURCES += main.cpp \
zip/zipglobal.cpp\
zip/zip.cpp\
zip/unzip.cpp \
    zip/zipproc.cpp\
zip\task.cpp \
    SimpleView.cxx \
    hf/hf_error.cpp \
    hf/hfpcommandline.cpp \
    hf/mainApp.cpp \
    hf/vtk_based_classes/colormap.cpp \
    hf/vtk_based_classes/contour3d.cpp \
    hf/vtk_based_classes/hfrenderer.cpp \
    hf/vtk_based_classes/ImpFunc.cc \
    hf/vtk_based_classes/InverseImpFunc.cc \
    hf/vtk_based_classes/SampleFunction.cc \
    hf/vtk_based_classes/SoundImpFunc.cc

HEADERS += \
    qt/task.h\
zip/zipglobal.h\
zip/zip.h\
zip/zip_p.h\
zip/unzip.h\
zip/unzip_p.h\
zip/zipentry_p.h \
    zip/zipproc.h\
zip\task.h \
    SimpleView.h \
    hf/hf_error.h \
    hf/hfpclhelp.h \
    hf/hfpcommandline.h \
    hf/mainApp.h \
    hf/vtk_based_classes/colormap.h \
    hf/vtk_based_classes/contour3d.h \
    hf/vtk_based_classes/hfrenderer.h \
    hf/vtk_based_classes/implfunc.h \
    hf/vtk_based_classes/soundimplfunc.h

OTHER_FILES += \
    qss/style.css

include(vtk.pri)

LIBS +=  -lQVTK -lvtkWidgets -lvtkInfovis -lvtkViews -lvtkCharts
LIBS += -lvtkHybrid -lvtkRendering -lvtkftgl -lvtkfreetype
LIBS += -lvtkIO -lvtktiff -lvtkjpeg -lvtkpng -lvtkzlib -lvtkexpat
LIBS += -lvtkGraphics -lvtkFiltering -lvtkGenericFiltering -lvtkCommon -lvtksys

#change for minGW

LIBS +=  -lBLAS_nowrap -lclapack_nowrap -llibf2c -lcppinterpreter_lib -lhflibrary_lib -linterpreter_lib

LIBS += -lAlut -lOpenAL32



RESOURCES += \
    resource.qrc \
    Icons/icons.qrc

FORMS += \
    SimpleView.ui
