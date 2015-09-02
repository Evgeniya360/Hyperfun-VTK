#include "vtkTransform.h"


class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New() 
    { return new vtkMyCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkTransform *t = vtkTransform::New();
      vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
      widget->GetTransform(t);
      widget->GetProp3D()->SetUserTransform(t);
      t->Delete();
    }
};


/*

class StartInteraction : public vtkCommand
{
public:
  static StartInteraction  *New() 
    { return new StartInteraction ; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {

		  vtkRenderWindow *renWin =  reinterpret_cast<vtkRenderWindow*>(caller);
   renWin-> SetDesiredUpdateRate (10);
    }
};

class EndInteraction : public vtkCommand
{
public:
  static EndInteraction  *New() 
    { return new EndInteraction ; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {

		  vtkRenderWindow *renWin =  reinterpret_cast<vtkRenderWindow*>(caller);
   renWin-> SetDesiredUpdateRate (0.001);
    }
};


class EndInteraction : public vtkCommand
{
public:
  static EndInteraction  *New() 
    { return new EndInteraction ; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
    {

		  vtkRenderWindow *renWin =  reinterpret_cast<vtkRenderWindow*>(caller);
   renWin-> SetDesiredUpdateRate (0.001);
    }
};

*/

/*

# When interaction ends, the requested frame rate is decreased to
# normal levels. This causes a full resolution render to occur.
proc EndInteraction {} {
   renWin SetDesiredUpdateRate 0.001
}

# The implicit function vtkPlanes is used in conjunction with the
# volume ray cast mapper to limit which portion of the volume is
# volume rendered.
vtkPlanes planes
proc ClipVolumeRender {} {
   boxWidget GetPlanes planes
   volumeMapper SetClippingPlanes planes
}
*/