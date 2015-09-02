#if !defined(HFSound_H)
#define HFSound_H

#include "implfunc.h"

#include "al.h" 
#include "alc.h"
#include "Al\alut.h"
#include "vtkCallbackCommand.h"
#include "vtkPicker.h"

#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"

#define IsLoop 1

class Sound3D
{
public:
	ImpFunc * function;
	bool Attributes;
	int sSize;
		ALuint  Source1;
	ALuint Buffer;
	vtkActor* spActor;
	double k;
	double Vol;
	int type;

		void main1 ();
		void setK(double k){
				this->k=k;
};
		void setVol(double Vol){
				this->Vol=Vol;
};
		void setType(int t){
				this->type=t;
};

ALboolean LoadALData();
	void KillALData();
	void play(double*coords)
	{
		double gain = 0.1;
		double pitch = function->EvaluateFunction(coords);
		if(this->type==2) //attributes should be mapped also
		{
			gain=function->EvaluateAtr(coords)[0]; //should be adjusted afterwards
			gain=(this->Vol)*gain;
		}
pitch=(this->k)*pitch;
	//gain=pitch;
	printf("pitch=%f\n",pitch);
	printf("volume=%f\n",gain);

	alSourcei (Source1, AL_BUFFER,  Buffer);
	alSourcef (Source1, AL_PITCH,   pitch);
	alSourcef (Source1, AL_GAIN,    gain);
	alSourcei (Source1, AL_LOOPING, 0);


	//if(!First)
	//	alSourceStop(quadric->Source1);

	//First = false;
	alSourcePlay(Source1);




	};
	
		void Delete();
		Sound3D(ImpFunc * function, bool Attributes, int size, double k);
		
		void createListener(double r,double*coords)
		{

			 vtkSphereSource* sp=vtkSphereSource::New();
sp->SetRadius(r);
  vtkPolyDataMapper *spMap = vtkPolyDataMapper::New();
  spMap->SetInput(sp->GetOutput());
  

   spActor = vtkActor::New();
 spActor->SetMapper(spMap);
 	spActor->SetPosition(coords);
		spActor->PickableOn();
		spActor->DragableOn();
		spActor->GetProperty()->SetColor(1,0,0);
		};

	~Sound3D()
	{
		
	}
};
#endif //