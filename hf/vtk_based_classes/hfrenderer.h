
#if !defined(HFR_H)
#define HFR_H


#include "vtkPolyDataMapper.h";
#include "vtkActor.h";

#include "vtkScalarBarActor.h";
#include "vtkAxesActor.h";
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h" 
#include "vtkDataSetMapper.h"
#include "vtkTextProperty.h"
#include "vtkFollower.h"
#include "vtkProperty.h"
#include "vtkLight.h"
#include "vtkCamera.h"

#include "../hfpcommandline.h"

#include "vtkObjectFactory.h"
#include "../sound3d.h" 
#include "vtkInteractorStyleTrackballCamera.h"
//#include "contour3d.h"

// Define interaction style
class KeyPressInteractorStyle : public vtkInteractorStyleTrackballCamera
{
  public:
    static KeyPressInteractorStyle* New();
    vtkTypeMacro(KeyPressInteractorStyle, vtkInteractorStyleTrackballCamera);

	//Contour3D* cont;
	//vtkActor*spActor;
	Sound3D*sound;
	void setSourceAndFunction(Sound3D*sp)
	{
		//this->cont=f;
		this->sound=sp;
	};
 
    virtual void OnKeyPress() 
    {
      // Get the keypress
      vtkRenderWindowInteractor *rwi = this->Interactor;
      std::string key = rwi->GetKeySym();
 
      // Output the key that was pressed
      std::cout << "Pressed " << key << std::endl;
  double coords[3];
  sound->spActor->GetPosition(coords);
  bool startPlay=false;
  double inc=0.2;
      // Handle an arrow key
      if(key == "Up")
        {
        std::cout << "The up arrow was pressed." << std::endl;
		coords[2]=coords[2]+inc;
		startPlay=true;
        }
	  if(key == "Down")
        {
        std::cout << "The down arrow was pressed." << std::endl;
		coords[2]=coords[2]-inc;
		startPlay=true;
        }
	   if(key == "Righ")
        {
        std::cout << "The right arrow was pressed." << std::endl;
		coords[2]=coords[1]+inc;
		startPlay=true;
        }
	   if(key == "Left")
        {
        std::cout << "The left arrow was pressed." << std::endl;
		coords[2]=coords[1]-inc;
		startPlay=true;
        }
	     if(startPlay)
        {
        
       
 
      // Handle a "normal" key
    
	//  rwi->GetMousePosition(coords[0],coords[1]);
	//	iren->GetMousePosition(
		sound->spActor->SetPosition(coords);
		rwi->GetRenderWindow()->Render();
		//{(x_min + x_max)/2, (y_min + y_max)/2, (z_min + z_max)/2};
	double pitch = sound->function->EvaluateFunction(coords);
	//gain=pitch;
	printf("function val=%f\n",pitch);
	printf("pos=%f,%f,%f\n",coords[0],coords[1],coords[2]);
	sound->play(coords);
      vtkInteractorStyleTrackballCamera::OnKeyPress();
		 }
    }
 
};


class HFRenderer
{
public:

	
	void StartSound(int axes, int scal, Sound3D* sp);//,void (*ff)(vtkObject *caller, unsigned long eid,
                                    // void *clientdata, void *calldata));
	HFRenderer( int clip, vtkActor *cont, vtkScalarBarActor*scalarBar1, vtkAxesActor*axes1,HFPCommandLine itsCL);
	
	~HFRenderer()
		{
			
	
		}
	void Delete();
	void Start(int axes, int scal);
	void SetRepresentationS(int i);
	void SetInterpolation();

	void SetRepresentation ();
	void SetOptics(double R, double G, double B, double Op, int Shade);

	void SetPosition(double x, double y, double z);

	void SetColor(double r, double g, double b);

	void SetAmbiantDifSpec(double x, double y, double z);

	void SetLight(double * fp, double* pos);

void SetCamera(double * fp, double* pos, double* v);

void SetCameraParal(int v);
vtkRenderer* GetRenderer(){return ren1;}
private:
		vtkRenderer *ren1;
	vtkRenderWindow *renWin;
	vtkRenderWindowInteractor *iren;
	vtkScalarBarActor*scalarBar;
	vtkAxesActor*axesact;
	vtkActor *contActor;
	//vtkActor *spActor;
		vtkPolyDataMapper *contMapper;
	vtkDataSetMapper* clipMapper;
	vtkFollower *XActor;
	vtkFollower *YActor;
	vtkFollower *ZActor;
	vtkVolume*volume;
	vtkLight* light;
HFPCommandLine itsCL;
	int clip;

};




#endif //
