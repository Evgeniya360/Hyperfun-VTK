#include "HFRenderer.h"

vtkStandardNewMacro(KeyPressInteractorStyle);


void KeypressCallbackFunction ( vtkObject* caller, long unsigned int eventId, void* clientData, void* callData )

//void KeypressCallbackFunction ( vtkObject* caller, long unsigned int veventId), void* vtkNotUsed(clientData), void* vtkNotUsed(callData) )
{
 // std::cout << "Keypress callback" << std::endl;
 
  vtkRenderWindowInteractor *iren = 
    static_cast<vtkRenderWindowInteractor*>(caller);
 int*x;
 int *y;
  //std::cout << "Pressed: " << iren->GetKeySym() << std::endl;
 //std::cout << "Pressed: " << iren->GetKeyCode() << std::endl;

  const char* key = "Return";
        //    if(strcmp ((iren->GetKeySym()),key)==0)
			{
    //            printf("Found\n");
Sound3D * quadric = 
    static_cast<Sound3D *>(clientData);
 	//pblock2->GetFloat(Source_GAIN, t);
		double coords[3];
	//	iren->GetMousePosition(
		quadric->spActor->GetPosition(coords);
		//{(x_min + x_max)/2, (y_min + y_max)/2, (z_min + z_max)/2};
		quadric->play(coords);
	//	iren->GetPicker()->GetActors();

  //iren->GetRenderWindow()->Render();
 
  //iren->Start();

			}

			
				/*
  if(iren->GetKeySym()=='k')
  {
	  iren->GetMousePosition(x,y);
		  std::cout << "x,y: " << x << std::endl;
  }
  */
}



HFRenderer::HFRenderer( int clip, vtkActor *cont, vtkScalarBarActor*scalarBar1, vtkAxesActor*axes1,HFPCommandLine itsCL)
	{
		this->clip=clip;
		this->itsCL=itsCL;
			//	this->contMapper=contMapper;
			//	this->clipMapper=clipMapper;
		this->contActor=cont;
	this->axesact=axes1;
	this->scalarBar=scalarBar1;
	}


void HFRenderer::Delete()
		{
			/*
			if (axes2)
			{
scalarBar->Delete();
axes->Delete();
	axesActor->Delete();
	XActor->Delete();
	YActor->Delete();
	ZActor->Delete();
			}
			
	if (vol)
	volume->Delete();
	else
	contActor->Delete();
*/
	// ругаетс€ на удаление аctor-в
	
	


			ren1->Delete();
	renWin->Delete();
	iren->Delete();
	
		}



		
void HFRenderer::StartSound(int axes, int scal,Sound3D*sp)//,void (*ff)(vtkObject *caller, unsigned long eid,
                                    // void *clientdata, void *calldata))
	{
		

  // -- render both of the objects --

  // a renderer and render window
 ren1 = vtkRenderer::New();
 
 vtkRenderer *ren2 = vtkRenderer::New();

  renWin = vtkRenderWindow::New();
  if (scal)
    renWin->SetMultiSamples(0);

  renWin->AddRenderer(ren1);
   if (scal)
 renWin->AddRenderer(ren2);


   
 iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);
 if (scal)
 {
  // дл€ scalar bar
  ren2->AddActor2D(scalarBar);
   ren2->SetViewport(0.85, 0, 1.0, 1.0);
  ren2->SetBackground(0.3, 0.3, 0.3);
  ren2->SetBackground(0.3, 0.3, 0.3);
 }

 /*
 KeyPressInteractorStyle* style =   KeyPressInteractorStyle::New();
 style->setSourceAndFunction(sp);
  iren->SetInteractorStyle(style);*/

   vtkCallbackCommand* keypressCallback = vtkCallbackCommand::New();
  keypressCallback->SetCallback (KeypressCallbackFunction);
  keypressCallback->SetClientData(sp);
  iren->AddObserver ( vtkCommand::KeyReleaseEvent, keypressCallback );/**/
  //sound is played when a key is released
  // to drag obgect middle mouse should be used

  // дл€ scalar bar




  // add the actors to the scene
   if (axes)
  // axes
   ren1->AddActor(axesact);

   ren1->AddActor(sp->spActor);
  ren1->AddActor(contActor);
//	ren1->AddActor2D(act2d);
 
//contMapper->SetScalarMaterialModeToAmbient();
//contMapper->SetScalarMaterialModeToDiffuse();
//  contActor->GetProperty()->ShadingOff();
  ren1->SetBackground(1,1,1); // Background color white
//SetAmbiantDifSpec(0.4,0.4,0.1);
  // render an image (lights and cameras are created automatically)
  // в некоторых необходимо отключать
  renWin->Render();
 
  // begin mouse interaction
  iren->Initialize();
  iren->Start();


	}

		
void HFRenderer::Start(int axes, int scal)
	{

  // -- render both of the objects --

  // a renderer and render window
 ren1 = vtkRenderer::New();
 
 vtkRenderer *ren2 = vtkRenderer::New();

  renWin = vtkRenderWindow::New();
  if (scal)
    renWin->SetMultiSamples(0);

  renWin->AddRenderer(ren1);
   if (scal)
 renWin->AddRenderer(ren2);


   
 iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);
 if (scal)
 {
  // дл€ scalar bar
  ren2->AddActor2D(scalarBar);
   ren2->SetViewport(0.85, 0, 1.0, 1.0);
  ren2->SetBackground(0.3, 0.3, 0.3);
  ren2->SetBackground(0.3, 0.3, 0.3);
 }
  // дл€ scalar bar

 // renWin->SetSize(300,300);



  // add the actors to the scene
   if (axes)
  // axes
   ren1->AddActor(axesact);


  ren1->AddActor(contActor);
//	ren1->AddActor2D(act2d);
 
//contMapper->SetScalarMaterialModeToAmbient();
//contMapper->SetScalarMaterialModeToDiffuse();
//  contActor->GetProperty()->ShadingOff();
  ren1->SetBackground(1,1,1); // Background color white
//SetAmbiantDifSpec(0.4,0.4,0.1);
  // render an image (lights and cameras are created automatically)
  // в некоторых необходимо отключать
  renWin->Render();
 
  // begin mouse interaction
  iren->Initialize();
  iren->Start();


	}



void HFRenderer::SetRepresentationS(int i)
	{
switch (i)
{
case 0:
contActor->GetProperty()->SetRepresentationToPoints();
		break;

		case 1:
contActor->GetProperty()->SetRepresentationToSurface();
		break;

		case 2:
contActor->GetProperty()->SetRepresentationToWireframe();
		break;

	}
	}

void HFRenderer::SetInterpolation()
{
	//варианты интерпол€ции
	switch(itsCL.interpType)
	{
		case 0:
contActor->GetProperty()->SetInterpolationToPhong();
		break;

		case 1:
contActor->GetProperty()->SetInterpolationToFlat();
		break;

		case 2:
contActor->GetProperty()->SetInterpolationToGouraud();
		break;

	}

}

void HFRenderer::SetRepresentation ()
	{
		//варианты представлени€ как сейчас в Hyperfun


		if (itsCL.itsWireframe) 
		contActor->GetProperty()->SetRepresentationToWireframe();
	   
		if (itsCL.itsWireAndSurface) 
		contActor->GetProperty()->SetRepresentationToSurface();

	    if (itsCL.itsDiffuse)
		contActor->GetProperty()->SetDiffuse(0.3);
		if (itsCL.itsSpecular)
		contActor->GetProperty()->SetSpecular(0.3);
		if (itsCL.itsFlat)
	    contActor->GetProperty()->SetInterpolationToFlat();

		// itsNormals=false;
	   // itsNormalsDisplay=false;

	}
void HFRenderer::SetOptics(double R, double G, double B, double Op, int Shade)
	{
		//настройки цвета и прозрачности и тени

contMapper->ScalarVisibilityOff();
contActor->GetProperty()->SetColor(R,G,B);
contActor->GetProperty()->SetOpacity(Op);
if (Shade)
  contActor->GetProperty()->ShadingOn();
else
  contActor->GetProperty()->ShadingOff();




	}

void HFRenderer::SetPosition(double x, double y, double z)
	{
	
  contActor->AddPosition(x,y,z);


	}

void HFRenderer::SetColor(double r, double g, double b)
	{
	
 contActor->GetProperty()->SetColor(r,g,b);

	}

void HFRenderer::SetAmbiantDifSpec(double x, double y, double z)
	{
		//ambiant difuse specular

 
 contActor->GetProperty()->SetAmbient(x);
 contActor->GetProperty()->SetDiffuse(y);
contActor->GetProperty()->SetSpecular(z);
 

	}

void HFRenderer::SetLight(double * fp, double* pos)
	{

	
// Set up the lighting.
  //
 light = vtkLight::New();
  light->SetFocalPoint(fp[0],fp[1],fp[2]);
  light->SetPosition(pos[0],pos[1],pos[2]);
  ren1->AddLight(light);
light->Delete();
	}

void HFRenderer::SetCamera(double * fp, double* pos, double* v)
	{
  // We want to eliminate perspective effects on the apparent lighting.
  // Parallel camera projection will be used. To zoom in parallel projection
  // mode, the ParallelScale is set.
  //
  ren1->GetActiveCamera()->SetFocalPoint(fp[0],fp[1],fp[2]);
  ren1->GetActiveCamera()->SetPosition(pos[0],pos[1],pos[2]);
  ren1->GetActiveCamera()->SetViewUp(v[0],v[1],v[2]);
  ren1->GetActiveCamera()->ParallelProjectionOn();
	}

void HFRenderer::SetCameraParal(int v)
	{
		if (v)
		 ren1->GetActiveCamera()->ParallelProjectionOn();
		else
		ren1->GetActiveCamera()->ParallelProjectionOff();
	}

