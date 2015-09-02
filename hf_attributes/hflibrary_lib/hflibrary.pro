QT       += core

TARGET = hflibrary_lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    hfA_CheckerBoard.c \
    Bezier.c \
    hfA_Circles.c \
    hfA_Crackles.c \
    hfA_HSVToRGB.c \
    hfA_lerp.c \
    hfA_LookUpTable.c \
    hfA_noiseg.c \
    hfA_noisep.c \
    hfA_RGBToHSV.c \
    hfA_SetAttributes.c \
    hfA_SetColor.c \
    hfA_SmoothLookUpTable.c \
    hfA_spline.c \
    hfA_ToolBox.c \
    hfA_turbulence.c \
    hfA_Union.c \
    hfA_Wave.c \
    hfArrayInput.c \
    hfBezierPatch.c \
    hfBezierVolume.c \
    hfblendint.c \
    hfblenduni.c \
    hfblobby.c \
    hfblock.c \
    hfBSplineVolume.c \
    hfConeX.c \
    hfConeY.c \
    hfConeZ.c \
    hfConvArc.c \
    hfConvCurve.c \
    hfConvLine.c \
    hfconvliner.c \
    hfConvMesh.c \
    hfConvPoint.c \
    hfConvTriangle.c \
    hfCubicBSpline.c \
    hfcylinderx.c \
    hfcylindery.c \
    hfcylinderz.c \
    hfEllConeX.c \
    hfEllConeY.c \
    hfEllConeZ.c \
    hfellcylx.c \
    hfellcyly.c \
    hfellcylz.c \
    hfellipsoid.c \
    hffmapblob.c \
    hfmetaball.c \
    hfmoout.c \
    hfNoiseG.c \
    hfproj.c \
    hfrotate3dx.c \
    hfrotate3dy.c \
    hfrotate3dz.c \
    hfscale3d.c \
    hfshift3d.c \
    hfsoft.c \
    hfSpaceMapCubic.c \
    hfSpaceMapExp.c \
    hfsphere.c \
    hfstr_t.c \
    hfstretch3d.c \
    hfSuperell.c \
    hftaperx.c \
    hftapery.c \
    hftaperz.c \
    hftorusx.c \
    hftorusy.c \
    hftorusz.c \
    hftwistx.c \
    hftwisty.c \
    hftwistz.c \
    hfvoxel.c \
    myfunc.c \
    rbfscalars.c \
    readscalars.c \
    SplineFunc.c



INCLUDEPATH += "$$PWD/../interpreter_lib"
INCLUDEPATH += $$PWD/../include

LIBS +=  -lBLAS_nowrap -lclapack_nowrap -llibf2c 

    DEFINES += _CRT_SECURE_NO_WARNINGS

HEADERS += \
    archyp.h \
    atanh.h \
    Bezier.h \
    cubicspline.h \
    files.h \
    filesheader.h \
    functions2.h \
    hflib.h \
    hfvoxel.h \
    pattern.h \
    perlin.h \
    SplineFunc.h

