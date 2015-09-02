 #include "../include/hfinterpreter.h"
 #include "hfpcommandline.h"


//This class is rewritten from HyperFun polygonizer
//See copywright of HFP below
/*==============================================================================

Copyright 1999 Eric Fausett
Copyright 2003-2004 Pierre-Alain Fayolle, Benjamin Schmitt

This Work or file is part of the greater total Work, software or group of
files named HyperFun Polygonizer.

HyperFun Polygonizer can be redistributed and/or modified under the terms 
of the CGPL, The Common Good Public License as published by and at CGPL.org
(http://CGPL.org).  It is released under version 1.0 Beta of the License
until the 1.0 version is released after which either version 1.0 of the
License, or (at your option) any later version can be applied.

THIS WORK, OR SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED (See the
CGPL, The Common Good Public License for more information.)

You should have received a copy of the CGPL along with HyperFun Polygonizer;  
if not, see -  http://CGPL.org to get a copy of the License.

==============================================================================*/
#include <QCoreApplication>
#include "zip/task.h"

#include <QApplication>
#include <QTextCodec>
#include <QCleanlooksStyle>
#include "SimpleView.h"


// MainApp.h: interface for the CMainApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(MAINAPP_H)
#define MAINAPP_H

#pragma warning( disable : 4786 )


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <iostream>
#include <fstream>
#ifdef WIN32
#include <windows.h>
#endif
#include "hfpcommandline.h"
#include "..\include\vtkIncludes.h"
#include "..\include\vtkClasses.h"

#define MAX_FILE_SIZE 100000
#define PI 3.14159265
class CMainApp
{
public:
    CMainApp(int & argc, char ** argv);

	virtual ~CMainApp();
	int init ();
	bool Triangulate;
	HFInterpreter itsInterpreter;
	HFPCommandLine itsCL;
	void StartImpl(bool bAttributes);
	void createImplFunction(bool bNormal, bool bVertexNormal, bool bAttributes);

    vtkRenderer *ren1;
    vtkRenderWindow *renWin;
    vtkRenderWindowInteractor *iren;
private:
	void getBoundingBox();
	void readFile();
	void parseString();
	std::string itsString;

	//vtk-s

double bounds[6];
Contour3D* cont;
ColorMap*colorm;
Volume1* vol1;
Volume2* vol2;

ImpFunc * function;
SampFunc *sample;
std::vector<vtkImageData*> imData;
vtkStructuredGrid *sgrid;

vtkContourFilter *contours;
vtkPolyData* pol;
vtkFollower *XActor;
vtkFollower *YActor;
vtkFollower *ZActor;


vtkActor2D* act2d;

double length;

vtkLight *light ;
vtkPolyDataMapper *contMapper;
vtkActor *contActor;
vtkScalarBarActor*scalarBar;
vtkAxes* axes;
vtkActor *axesActor;
vtkVolume *volume;
vtkVolumeRayCastMapper* volumeMapper;
vtkTexture* atext;
vtkImageActor *actori;


	//vtk-s
/*
double bounds[6];
Contour3D* cont;
ColorMap*colorm;
Volume1* vol1;
Volume2* vol2;

	ImpFunc * function;
	SampFunc *sample;
	 vtkStructuredGrid *sgrid;

	vtkContourFilter *contours;
	vtkPolyData* pol;
	vtkFollower *XActor;
	vtkFollower *YActor;
	vtkFollower *ZActor;


	vtkActor2D* act2d;

	double length;
	vtkRenderer *ren1;
	vtkRenderWindow *renWin;
	vtkRenderWindowInteractor *iren;
vtkLight *light ;
vtkPolyDataMapper *contMapper;
	vtkActor *contActor;
	vtkScalarBarActor*scalarBar;
	vtkAxes* axes;
	vtkActor *axesActor;
	vtkVolume *volume;
	vtkVolumeRayCastMapper* volumeMapper;
	vtkTexture* atext;
	vtkImageActor *actori;
*/
	


};

#endif // !defined(MAINAPP_H)
