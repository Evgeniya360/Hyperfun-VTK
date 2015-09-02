/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: Cone.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This example creates a polygonal model of a cone, and then renders it to
// the screen. It will rotate the cone 360 degrees and then exit. The basic
// setup of source -> mapper -> actor -> renderer -> renderwindow is 
// typical of most VTK programs.
//

// First include the required header files for the VTK classes we are using.

#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkOBJReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCell.h>
#include <vtkCellArray.h>
#include <vtkIdList.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPointData.h>
#include "vtkPlane.h"
#include "vtkClipPolyData.h"
#include "vtkImplicitBoolean.h"
#include "vtkSampleFunction.h"
#include "vtkContourFilter.h"
#include "vtkCamera.h"
#include <string>

//--------------------
 #include <vtkSphereSource.h>
 #include <vtkCylinderSource.h>
 #include <vtkLineSource.h> 

 //#include <vtkBooleanOperationPolyDataFilter.h>
#include "vtkAppendPolyData.h"
#include "vtkTubeFilter.h"
#include "vtkProperty.h"

#include <time.h>

 #include "include/hfinterpreter.h"
#include "hf/mainApp.h"
/*
void
init_var (CMainApp *mainapp)
{
	width = mainapp->getWindowSizeX();
	height = mainapp->getWindowSizeY();

	// gives to HF_FACE_LINE_FILL a 0 or 1 value
	// meaning wireframe or solid 
	HF_FACE_LINE_FILL = mainapp->getFaceLineFill();

	// if it has beeen required WireAndSurface from the command line
	// then we should give a value of 2 
	if (mainapp->getWireAndSurface() == 1)
		HF_FACE_LINE_FILL = 2; 

	HF_NORMAL = mainapp->getNormal();
	if (HF_NORMAL)
	{   
		HF_SHOW_NORMAL = mainapp->getNormalDisplay ();
		HF_FLAT_SMOOTH = mainapp->getFlat();
	}
	else // we did not compute the normals so we can not show them
	{
		HF_SHOW_NORMAL = 0;
		HF_FLAT_SMOOTH = 1; // defaut is flat
	}

	first_normal_show = 0;
	HF_SHOW_AXES = 1;

	HF_VERTEX_NORMAL = 1;

	HF_LIGHT_TYPE = mainapp->getLightType (); // 1 diffuse; 2 specular; 
	// 3: diffuse & specular.

	mainapp->getFaceColor(HF_FACE_COLOR);
	mainapp->getLineColor(HF_LINE_COLOR);
	mainapp->getBoundingBox(HF_MIN, HF_MAX);
	mainapp->getViewPos(itsCPos, itsCLookAt);

	//BEN
	HAS_ATTRIBUTES = edi->getAttribute();
TRIANGULATE=edi->getTriangulate();


}






*/

void init_render(CMainApp *edi)
{
	
	/*
			edi->createGLTriangle(true, HF_VERTEX_NORMAL ,false);
		edi->createGLTriangle(false, HF_VERTEX_NORMAL, false);
	
			edi->createImplFunction(true, HF_VERTEX_NORMAL ,false);
				edi->createImplFunction(false, HF_VERTEX_NORMAL, false);
				*/
	edi->createImplFunction(true, false ,false);

}

int main (int argc, char **argv) 

{

		//получение аргументов строки
	CMainApp *edi = new CMainApp (argc, argv);


	//обработка аргументов
	//чтение из файла
	int vn_t = edi->init();
	
	//получение параметров окна (важно - атрибуты)
	//init_var(edi);
	
	// rendering
	init_render (edi);


  return 0;
}
