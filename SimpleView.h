/*=========================================================================

  Program:   Visualization Toolkit
  Module:    SimpleView.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright 2009 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
  license for use of this work by or on behalf of the
  U.S. Government. Redistribution and use in source and binary forms, with
  or without modification, are permitted provided that this Notice and any
  statement of authorship are reproduced on all copies.

=========================================================================*/
#ifndef SimpleView_H
#define SimpleView_H

#include "vtkSmartPointer.h"    // Required for smart pointer internal ivars.
#include <QMainWindow>
#include "hf/mainApp.h"
// Forward Qt class declarations
class Ui_SimpleView;

// Forward VTK class declarations
class vtkQtTableView;


class SimpleView : public QMainWindow
{
  Q_OBJECT

public:

  // Constructor/Destructor
  SimpleView(); 
  ~SimpleView();

  CMainApp *edi;
  void initMain(int argc, char *argv[])
  {
      edi = new CMainApp (argc, argv);


      //обработка аргументов
      //чтение из файла
      int vn_t = edi->init();

      //получение параметров окна (важно - атрибуты)
      //init_var(edi);

      // rendering
      init_render ();
  }


  void init_render();



public slots:

  virtual void slotOpenFile();
  virtual void slotExit();

protected:
   
protected slots:

private:

    
  // Designer form
  Ui_SimpleView *ui;
};

#endif // SimpleView_H
