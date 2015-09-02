/*
 * Copyright 2007 Sandia Corporation.
 * Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 * license for use of this work by or on behalf of the
 * U.S. Government. Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that this Notice and any
 * statement of authorship are reproduced on all copies.
 */


#include "ui_SimpleView.h"
#include "SimpleView.h"

#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkVectorText.h>

#include "vtkSmartPointer.h"
#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

// Constructor
SimpleView::SimpleView() 
{
  this->ui = new Ui_SimpleView;
  this->ui->setupUi(this);



  // VTK/Qt wedded
    //TODO: remove from Contour renWin
    //Make abstract class for all objects
    //Cсюда будет передаваться рендерер
  //this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(edi->ren1);


  // Set up action signals and slots
  connect(this->ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

};

void SimpleView::init_render()
{

    /*
            edi->createGLTriangle(true, HF_VERTEX_NORMAL ,false);
        edi->createGLTriangle(false, HF_VERTEX_NORMAL, false);

            edi->createImplFunction(true, HF_VERTEX_NORMAL ,false);
                edi->createImplFunction(false, HF_VERTEX_NORMAL, false);
                */

    //TODO:
    //убрать дублирующее окно
    this->edi->createImplFunction(true, false ,false);
    this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(this->edi->ren1);

}
SimpleView::~SimpleView()
{
  // The smart pointers should clean up for up

}

// Action to be taken upon file open 
void SimpleView::slotOpenFile()
{
//TODO: WriteSome text here
}

void SimpleView::slotExit() {
  qApp->exit();
}
