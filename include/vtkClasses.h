#include "contour3D.h"
#include "colormap.h"


class vtkMyCallback2 : public vtkCommand
{
public:
  vtkVolumeRayCastMapper *rcm;
 ImpFunc* fucnt;
SampFunc*samp2;

  static vtkMyCallback2 *New() 
    { return new vtkMyCallback2; }
    virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
	   vtkBoxWidget *boxWidget = reinterpret_cast<vtkBoxWidget*>(caller);
	   vtkPlanes *planes = vtkPlanes::New();
	   // The implicit function vtkPlanes is used in conjunction with the
	   // volume ray cast mapper to limit which portion of the volume is
	   // volume rendered.
	   boxWidget->GetPlanes(planes);
	   this->rcm->SetClippingPlanes(planes);

	   vtkPlane*plan2= vtkPlane::New(); 
   planes->GetPlane(2,plan2);
   
/*
   vtkImplicitBoolean*bb=vtkImplicitBoolean::New();
    bb->SetOperationTypeToIntersection();
    bb->AddFunction(plan2);
   bb->AddFunction (this->fucnt);
   this->samp2->SetImplicitFunction(bb); 
   */
    }
};







 

class HFRendererVol
{
public:

	vtkRenderer *ren1;
	vtkRenderWindow *renWin;
	vtkRenderWindowInteractor *iren;
	vtkScalarBarActor*scalarBar;
	vtkAxesActor*axesact;
	vtkVolume *contActor;
	vtkVolumeRayCastMapper *contMapper;
	vtkFollower *XActor;
	vtkFollower *YActor;
	vtkFollower *ZActor;
	vtkImageShiftScale*ss2;
	//vtkVolume*volume;
	vtkLight* light;
HFPCommandLine itsCL;
	int vol;
	HFRendererVol( int vol, vtkVolume *cont, vtkScalarBarActor*scalarBar1, vtkAxesActor*axes1,HFPCommandLine itsCL,vtkVolumeRayCastMapper *contMapper,vtkImageShiftScale* ss2)
	{
		this->vol=vol;
		this->itsCL=itsCL;
				this->ss2=ss2;
	
this->contActor=cont;
this->contMapper=contMapper;
	this->axesact=axes1;
	this->scalarBar=scalarBar1;
	}


	void Delete()
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
	// ругается на удаление аctor-в
	
	


			ren1->Delete();
	renWin->Delete();
	iren->Delete();
	
		}

		~HFRendererVol()
		{
			
	
		}
	void Start(int axes, int scal)
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
  // для scalar bar
  ren2->AddActor2D(scalarBar);
   ren2->SetViewport(0.85, 0, 1.0, 1.0);
  ren2->SetBackground(0.3, 0.3, 0.3);
  ren2->SetBackground(0.3, 0.3, 0.3);
 }
  // для scalar bar

 // renWin->SetSize(300,300);



  // add the actors to the scene
   if (axes)
  // axes
   ren1->AddActor(axesact);


ren1->AddVolume(contActor);


 vtkBoxWidget *boxWidget = vtkBoxWidget::New();
    boxWidget->SetInteractor(iren);
    boxWidget->SetPlaceFactor(1.0);
 
  // - - - - - - - - - - - - - - - - - - - - -
  vtkMyCallback2 *mcb = vtkMyCallback2::New();
  mcb->rcm=contMapper;

   boxWidget->AddObserver(vtkCommand::InteractionEvent, mcb);
mcb->Delete();

  // Place the interactor initially. The output of the reader is used to place
  // the box widget.
    boxWidget->SetInput(ss2->GetOutput());
    boxWidget->PlaceWidget();
    boxWidget->InsideOutOn();
    boxWidget->GetOutlineProperty()->SetRepresentationToWireframe();
    boxWidget->GetOutlineProperty()->SetAmbient(1.0);
    boxWidget->GetOutlineProperty()->SetAmbientColor(1,1,1);
    boxWidget->GetOutlineProperty()->SetLineWidth(3);
    boxWidget->GetSelectedOutlineProperty()->SetRepresentationToWireframe();
    boxWidget->GetSelectedOutlineProperty()->SetAmbient(1.0);
    boxWidget->GetSelectedOutlineProperty()->SetAmbientColor(1,0,0);
    boxWidget->GetSelectedOutlineProperty()->SetLineWidth(3);
   boxWidget ->SetKeyPressActivationValue('m');


  ren1->SetBackground(1,1,1); // Background color white
  renWin->Render();
 
  // begin mouse interaction
  iren->Initialize();
  iren->Start();


	}



	
		void SetPosition(double x, double y, double z)
	{
	
  contActor->AddPosition(x,y,z);


	}

	
	void SetLight(double * fp, double* pos)
	{

	
// Set up the lighting.
  //
 light = vtkLight::New();
  light->SetFocalPoint(fp[0],fp[1],fp[2]);
  light->SetPosition(pos[0],pos[1],pos[2]);
  ren1->AddLight(light);
light->Delete();
	}

void SetCamera(double * fp, double* pos, double* v)
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

void SetCameraParal(int v)
	{
		if (v)
		 ren1->GetActiveCamera()->ParallelProjectionOn();
		else
		ren1->GetActiveCamera()->ParallelProjectionOff();
	}



};



	class Volume1
	{
public:

	SampFunc *sample;
		double length;
	

vtkPolyDataMapper *contMapper;
	vtkActor *contActor;
	HFRendererVol* renhf;
	vtkScalarBarActor*scalarBar;
vtkAxesActor*axes2;

vtkLookupTable*table;
vtkImageShiftScale* ss2;
vtkVolumeRayCastCompositeFunction*compositeFunction;
vtkVolumeRayCastMapper* volumeMapper;
vtkVolumeProperty* volumeProperty;
//vtkVolume* volume2;
vtkVolume* volume;


		Volume1(SampFunc *samp)
		
		{ this->sample=samp;
		}

		void Delete()
	{
		
		renhf->Delete();
	}
	~Volume1()
	{
		
	}


void CreateVolume1( HFPCommandLine itsCL)
	{
		vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	opacityTransferFunction->AddPoint(0, 0.0);
	opacityTransferFunction->AddPoint(149, 0.00);
	opacityTransferFunction->AddPoint(150, 0.1);
	//близкие значения для уменьшения 
	opacityTransferFunction->AddPoint(151, 1.0);
	opacityTransferFunction->AddPoint(255, 0.8);
	

	// Create transfer mapping scalar value to color
	vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint( 0.0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(149, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint( 150, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint( 151, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint(255, 0.0, 0.0, 1.0);
	//colorTransferFunction->AddRGBPoint( 255, 0.0, 0.1, 0.1);


	// пробные

	vtkPiecewiseFunction* surface
		= vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	surface->AddPoint(0, 0.0);
	surface->AddPoint(149, 0.1);
	surface->AddPoint(150, 0.4);
	//surface->AddPoint(160, 0.4);
	//surface->AddPoint(180, 0.4);


	surface->AddPoint(255, 1.0);


	vtkClipVolume* clip=	vtkClipVolume::New();
  clip-> SetInputConnection (sample-> GetOutputPort());
  clip-> SetValue (1.0);
  clip-> GenerateClippedOutputOff();


		vtkImageData* im=sample->GetOutput();//->SetScalarTypeToChar();
//	im->SetScalarTypeToUnsignedChar();

	double* range=sample->GetOutput()->GetScalarRange();


	vtkImageCast *imageCast = vtkImageCast::New();
 imageCast->SetInput(im ); 
 imageCast->SetOutputScalarTypeToUnsignedChar();

	//im->SetExtent(0,255,0,255,0,255);
	vtkImageThreshold* t1=vtkImageThreshold::New();
t1-> SetInput(im);//imageCast->GetOutput());

t1 ->ReplaceInOn();
t1-> SetInValue (0);
t1 ->ThresholdBetween (150, 255);
//t1->ThresholdBetween( 0,range[1]);
//  t1-> SetInValue (255);
  //t1->SetOutValue (0);
 t1-> Update();



vtkImageShiftScale *ss=vtkImageShiftScale::New();
ss ->SetInputConnection (t1-> GetOutputPort());
ss-> SetOutputScalarTypeToUnsignedChar();

double range2[2];
im->GetScalarRange(range2);
double diff=range2[1]-range2[0];
double slope = 255/diff;
double inter=-slope*range2[0];
double shift=inter/slope;

//printf("%lf=range_max",range2[1]);
table = vtkLookupTable::New();
  table->SetRange((range2[0]+shift)*slope, (range2[1]+shift)*slope); // image intensity range
table->SetHueRange (0, 1);
 table->SetSaturationRange (1, 1);
 table->SetValueRange (1, 1); 
 table->SetRampToLinear();
  table->Build();


ss2=vtkImageShiftScale::New();
ss2->SetShift(shift);
ss2->SetScale(slope);
ss2-> SetOutputScalarTypeToUnsignedChar();
ss2 ->SetInput (im);
ss2->ReleaseDataFlagOff();
ss2->Update();
	

	vtkPiecewiseFunction* gop=vtkPiecewiseFunction::New();
gop-> AddPoint   (0, 1.0);
gop-> AddPoint ( shift*slope-1, 1.0);
gop-> AddPoint ( shift*slope, 0.9);
gop-> AddPoint ( shift*slope+20, 0.0);
gop-> AddPoint (255, 0.0);


	vtkColorTransferFunction* rainbow=vtkColorTransferFunction::New();
rainbow-> SetColorSpaceToHSV();
rainbow ->HSVWrapOff();
rainbow ->AddHSVPoint   (shift*slope-40, 0.1, 1.0, 1.0);
rainbow ->AddHSVPoint (255, 0.9, 1.0, 1.0);




vtkPiecewiseFunction* constant1=vtkPiecewiseFunction::New();

constant1 ->AddPoint  ( 0 ,0.9);
constant1 ->AddPoint (255, 0.7);



	// The property describes how the data will look
	vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
//iso
//	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->SetScalarOpacity(gop);
	volumeProperty->SetColor(rainbow);
//several
//	volumeProperty->SetScalarOpacity(surface);
  // volumeProperty-> SetGradientOpacity (constant1);
	volumeProperty->ShadeOff();
	//volumeProperty->SetInterpolationTypeToNearest();
	volumeProperty->SetInterpolationTypeToLinear();
	//volumeProperty->SetDisableGradientOpacity(0);
//volumeProperty->SetGradientOpacity(opacityTransferFunction);
volumeProperty->SetAmbient(0.3);
volumeProperty->SetDiffuse(1.0);
volumeProperty->SetSpecular(0.2);
volumeProperty->SetSpecularPower(10.0);
	// prop2->SetColor( cTFun );
   
 vtkFiniteDifferenceGradientEstimator *gradest = 
    vtkFiniteDifferenceGradientEstimator::New();
 gradest->SetZeroNormalThreshold(0.1);




compositeFunction=vtkVolumeRayCastCompositeFunction::New();
 volumeMapper=vtkVolumeRayCastMapper::New();
//compositeFunction->SetCompositeMethodToClassifyFirst();
//compositeFunction->SetCompositeMethodToInterpolateFirst();
//volumeMapper->SetGradientEstimator(gradest);
    volumeMapper-> SetVolumeRayCastFunction (compositeFunction);

	volumeMapper-> SetBlendModeToComposite();



	volumeMapper-> SetInput(ss2->GetOutput());//imageCast->GetOutput());//im);//sgrid);
	volumeMapper->SetSampleDistance((itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0])/(itsCL.itsGridSize[0]*2));
		
	volume = vtkVolume::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	

	


	CreateAxesScal( itsCL);

renhf=new HFRendererVol(1,volume,scalarBar,axes2,itsCL,volumeMapper,ss2);

//должно заносится из командной строки
renhf->Start(itsCL.itsAxes,itsCL.itsScalarBar);


	}

void	CreateAxesScal( HFPCommandLine itsCL,int tab=0)

	{

if (itsCL.itsScalarBar)
{
	// scalar bar

	scalarBar=vtkScalarBarActor::New();
	// if ((itsCL.itsVolume)||(tab))
	//	 scalarBar->SetLookupTable(table);
	// else
	 
scalarBar->SetLookupTable(table);
	 
//atext->Update();
//	 scalarBar->SetLookupTable(atext->GetLookupTable());
  scalarBar->SetTitle("Attributes");
  scalarBar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
  scalarBar->GetPositionCoordinate()->SetValue(0.01, 0.05);
  scalarBar->SetOrientationToVertical();
  scalarBar->SetWidth(0.4);
  scalarBar->SetHeight(0.9);
  scalarBar->SetLabelFormat("%-#3.3f");
scalarBar->SetPosition(scalarBar->GetPosition());
  scalarBar->SetNumberOfLabels(8);

// scalar bar
}


  if (itsCL.itsAxes)
  {
 //axes
 axes2 = vtkAxesActor::New();

  // simulate a left-handed coordinate system
  //
  
  axes2->SetShaftTypeToCylinder();
  //axes2->SetUserTransform( transform );
  axes2->SetXAxisLabelText( "x" );
  axes2->SetYAxisLabelText( "y" );
  axes2->SetZAxisLabelText( "z" );
  axes2->SetOrigin(0,0,0);
 // axes2->SetNormalizedShaftLength(0.5,0.5,0.5);
  //axes2->SetNormalizedTipLength(0.5,0.5,0.5);
  //axes2->setT
 length= itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0];
 length=length/2;
  axes2->SetTotalLength( length, length, length );
  axes2->SetCylinderRadius( 0.100 * axes2->GetCylinderRadius() );
  axes2->SetConeRadius    ( 0.5 * axes2->GetConeRadius() );
  axes2->SetSphereRadius  ( 1.500 * axes2->GetSphereRadius() );

  vtkTextProperty* tprop = axes2->GetXAxisCaptionActor2D()->
    GetCaptionTextProperty();
  tprop->ItalicOn();
  tprop->ShadowOn();
  tprop->SetColor(0,0,1);
  tprop->SetFontFamilyToTimes();

  axes2->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
  axes2->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
  }
//axes->SetOrigin(bounds[0], bounds[1], bounds[2]);


	
   //  axes->SetScaleFactor(length);
	
	
	
	}








	void CreateVolume4(HFPCommandLine itsCL)
	{
		vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	opacityTransferFunction->AddPoint(0, 1.0);
	opacityTransferFunction->AddPoint(149, 1.00);
	opacityTransferFunction->AddPoint(150, 0.4);
	//близкие значения для уменьшения 
	opacityTransferFunction->AddPoint(151, 0.4);
	opacityTransferFunction->AddPoint(255, 0.1);
	

	// Create transfer mapping scalar value to color
	vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint( 0.0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(149, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint( 150, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint( 151, 0.0, 1.0, 1.0);
	colorTransferFunction->AddRGBPoint(255, 1.0, 0.0, 1.0);
	//colorTransferFunction->AddRGBPoint( 255, 0.0, 0.1, 0.1);


	// пробные

	vtkPiecewiseFunction* surface
		= vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	surface->AddPoint(0, 0.0);
	surface->AddPoint(149, 0.1);
	surface->AddPoint(150, 0.4);
	//surface->AddPoint(160, 0.4);
	//surface->AddPoint(180, 0.4);


	surface->AddPoint(255, 1.0);



		vtkImageData* im=sample->GetOutput();//->SetScalarTypeToChar();
//	im->SetScalarTypeToUnsignedChar();

	double* range=sample->GetOutput()->GetScalarRange();


	vtkImageCast *imageCast = vtkImageCast::New();
 imageCast->SetInput(im ); 
 imageCast->SetOutputScalarTypeToUnsignedChar();

	//im->SetExtent(0,255,0,255,0,255);
	vtkImageThreshold* t1=vtkImageThreshold::New();
t1-> SetInput(im);//imageCast->GetOutput());

t1 ->ReplaceInOn();
t1-> SetInValue (0);
t1 ->ThresholdBetween (150, 255);
//t1->ThresholdBetween( 0,range[1]);
//  t1-> SetInValue (255);
  //t1->SetOutValue (0);
 t1-> Update();



vtkImageShiftScale *ss=vtkImageShiftScale::New();
ss ->SetInputConnection (t1-> GetOutputPort());
ss-> SetOutputScalarTypeToUnsignedChar();

double range2[2];
im->GetScalarRange(range2);
double diff=range2[1]-range2[0];
double slope = 255/diff;
double inter=-slope*range2[0];
double shift=inter/slope;

//printf("%lf=range_max",range2[1]);
table = vtkLookupTable::New();
  table->SetRange((range2[0]+shift)*slope, (range2[1]+shift)*slope); // image intensity range
table->SetHueRange (0, 1);
 table->SetSaturationRange (1, 1);
 table->SetValueRange (1, 1); 
 table->SetRampToLinear();
  table->Build();


ss2=vtkImageShiftScale::New();
ss2->SetShift(shift);
ss2->SetScale(slope);
ss2-> SetOutputScalarTypeToUnsignedChar();
ss2 ->SetInput (im);
ss2->ReleaseDataFlagOff();
ss2->Update();
	

	vtkPiecewiseFunction* gop=vtkPiecewiseFunction::New();
gop-> AddPoint   (0, 1.0);
gop-> AddPoint ( shift*slope, 1.0);
gop-> AddPoint ( shift*slope+3, 0.1);
gop-> AddPoint ( shift*slope+7, 0.01);
//gop-> AddPoint ( shift*slope+20, 0.0);
gop-> AddPoint (255, 0.001);


	vtkColorTransferFunction* rainbow=vtkColorTransferFunction::New();
rainbow-> SetColorSpaceToHSV();
rainbow ->HSVWrapOff();
rainbow ->AddHSVPoint   (shift*slope-40, 0.1, 1.0, 1.0);
rainbow ->AddHSVPoint (255, 0.9, 1.0, 1.0);




vtkPiecewiseFunction* constant1=vtkPiecewiseFunction::New();

constant1 ->AddPoint  ( 0 ,0.9);
constant1 ->AddPoint (255, 0.7);



	// The property describes how the data will look
	vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
//iso
//	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->SetScalarOpacity(gop);
//	volumeProperty->SetColor(rainbow);
//several
//	volumeProperty->SetScalarOpacity(surface);
  // volumeProperty-> SetGradientOpacity (constant1);
	volumeProperty->ShadeOn();
	//volumeProperty->SetInterpolationTypeToNearest();
	volumeProperty->SetInterpolationTypeToLinear();
	//volumeProperty->SetDisableGradientOpacity(0);
//volumeProperty->SetGradientOpacity(opacityTransferFunction);
volumeProperty->SetAmbient(2.8);
volumeProperty->SetDiffuse(1.0);
volumeProperty->SetSpecular(2.0);

volumeProperty->SetSpecularPower(90.0);
	// prop2->SetColor( cTFun );
   
 vtkFiniteDifferenceGradientEstimator *gradest = 
    vtkFiniteDifferenceGradientEstimator::New();
 gradest->SetZeroNormalThreshold(0.1);




compositeFunction=vtkVolumeRayCastCompositeFunction::New();
 volumeMapper=vtkVolumeRayCastMapper::New();
//compositeFunction->SetCompositeMethodToClassifyFirst();
//compositeFunction->SetCompositeMethodToInterpolateFirst();
//volumeMapper->SetGradientEstimator(gradest);
    volumeMapper-> SetVolumeRayCastFunction (compositeFunction);

	volumeMapper-> SetBlendModeToComposite();



	volumeMapper-> SetInput(ss2->GetOutput());//imageCast->GetOutput());//im);//sgrid);
	volumeMapper->SetSampleDistance((itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0])/(itsCL.itsGridSize[0]*2));
//iso
	
  //  volumeMapper-> SetInput(ss->GetOutput());//(imageCast->GetOutput());//im);//sgrid);
/*
	vtkVolumeProMapper* volumeMapper2=vtkVolumeProMapper::New();
//compositeFunction->SetCompositeMethodToClassifyFirst();
//compositeFunction->SetCompositeMethodToInterpolateFirst();
//volumeMapper->SetGradientEstimator(gradest);
   // volumeMapper2-> SetVolumeRayCastFunction (compositeFunction);

	//volumeMapper2-> SetBlendModeToComposite();

  volumeMapper2->SetInputConnection(ss2->GetOutputPort());
volumeMapper2->SetCutPlane (0);
//volumeMapper2->SetSampleDistance((itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0])/(itsCL.itsGridSize[0]*2));
*/



		
	volume = vtkVolume::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	

	CreateAxesScal( itsCL);

renhf=new HFRendererVol(1,volume,scalarBar,axes2,itsCL,volumeMapper,ss2);

//должно заносится из командной строки
renhf->Start(itsCL.itsAxes,itsCL.itsScalarBar);

	


	
	}



	void CreateVolume3(HFPCommandLine itsCL)
	{
		vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	opacityTransferFunction->AddPoint(0, 1.0);
	//opacityTransferFunction->AddPoint(149, 0.00);
	//opacityTransferFunction->AddPoint(150, 0.1);
	//близкие значения для уменьшения 
	opacityTransferFunction->AddPoint(151, 0.1);
	opacityTransferFunction->AddPoint(255, 0.1);
	

	// Create transfer mapping scalar value to color
	vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint( 0.0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(149, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint( 150, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint( 151, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint(255, 0.0, 0.0, 1.0);
	//colorTransferFunction->AddRGBPoint( 255, 0.0, 0.1, 0.1);


	// пробные

	vtkPiecewiseFunction* surface
		= vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	surface->AddPoint(0, 0.0);
	surface->AddPoint(149, 0.1);
	surface->AddPoint(150, 0.4);
	//surface->AddPoint(160, 0.4);
	//surface->AddPoint(180, 0.4);


	surface->AddPoint(255, 1.0);



		vtkImageData* im=sample->GetOutput();//->SetScalarTypeToChar();
//	im->SetScalarTypeToUnsignedChar();

	double* range=sample->GetOutput()->GetScalarRange();


	vtkImageCast *imageCast = vtkImageCast::New();
 imageCast->SetInput(im ); 
 imageCast->SetOutputScalarTypeToUnsignedChar();

	//im->SetExtent(0,255,0,255,0,255);
	vtkImageThreshold* t1=vtkImageThreshold::New();
t1-> SetInput(im);//imageCast->GetOutput());

t1 ->ReplaceInOn();
t1-> SetInValue (0);
t1 ->ThresholdBetween (150, 255);
//t1->ThresholdBetween( 0,range[1]);
//  t1-> SetInValue (255);
  //t1->SetOutValue (0);
 t1-> Update();



vtkImageShiftScale *ss=vtkImageShiftScale::New();
ss ->SetInputConnection (t1-> GetOutputPort());
ss-> SetOutputScalarTypeToUnsignedChar();

double range2[2];
im->GetScalarRange(range2);
double diff=range2[1]-range2[0];
double slope = 255/diff;
double inter=-slope*range2[0];
double shift=inter/slope;

//printf("%lf=range_max",range2[1]);
table = vtkLookupTable::New();
  table->SetRange((range2[0]+shift)*slope, (range2[1]+shift)*slope); // image intensity range
table->SetHueRange (0, 1);
 table->SetSaturationRange (1, 1);
 table->SetValueRange (1, 1); 
 table->SetRampToLinear();
  table->Build();


ss2=vtkImageShiftScale::New();
ss2->SetShift(shift);
ss2->SetScale(slope);
ss2-> SetOutputScalarTypeToUnsignedChar();
ss2 ->SetInput (im);
ss2->ReleaseDataFlagOff();
ss2->Update();
	

	vtkPiecewiseFunction* gop=vtkPiecewiseFunction::New();
gop-> AddPoint   (0, 1.0);
gop-> AddPoint ( shift*slope-1, 1.0);
gop-> AddPoint ( shift*slope, 0.9);
gop-> AddPoint ( shift*slope+20, 0.0);
gop-> AddPoint (255, 0.0);


	vtkColorTransferFunction* rainbow=vtkColorTransferFunction::New();
rainbow-> SetColorSpaceToHSV();
rainbow ->HSVWrapOff();
rainbow ->AddHSVPoint   (shift*slope-40, 0.1, 1.0, 1.0);
rainbow ->AddHSVPoint (255, 0.9, 1.0, 1.0);




vtkPiecewiseFunction* constant1=vtkPiecewiseFunction::New();

constant1 ->AddPoint  ( 0 ,0.9);
constant1 ->AddPoint (255, 0.7);



	// The property describes how the data will look
	vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
//iso
volumeProperty->SetScalarOpacity(opacityTransferFunction);
//	volumeProperty->SetScalarOpacity(gop);
	volumeProperty->SetColor(rainbow);
//several
//	volumeProperty->SetScalarOpacity(surface);
  // volumeProperty-> SetGradientOpacity (constant1);
	volumeProperty->ShadeOn();
	//volumeProperty->SetInterpolationTypeToNearest();
	volumeProperty->SetInterpolationTypeToLinear();
	//volumeProperty->SetDisableGradientOpacity(0);
//volumeProperty->SetGradientOpacity(opacityTransferFunction);
volumeProperty->SetAmbient(0.3);
volumeProperty->SetDiffuse(1.0);
volumeProperty->SetSpecular(0.2);
volumeProperty->SetSpecularPower(10.0);
	// prop2->SetColor( cTFun );
   
 vtkFiniteDifferenceGradientEstimator *gradest = 
    vtkFiniteDifferenceGradientEstimator::New();
 gradest->SetZeroNormalThreshold(0.1);




compositeFunction=vtkVolumeRayCastCompositeFunction::New();
 volumeMapper=vtkVolumeRayCastMapper::New();
//compositeFunction->SetCompositeMethodToClassifyFirst();
//compositeFunction->SetCompositeMethodToInterpolateFirst();
//volumeMapper->SetGradientEstimator(gradest);
    volumeMapper-> SetVolumeRayCastFunction (compositeFunction);

	volumeMapper-> SetBlendModeToComposite();



	volumeMapper-> SetInput(ss2->GetOutput());//imageCast->GetOutput());//im);//sgrid);
	volumeMapper->SetSampleDistance((itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0])/(itsCL.itsGridSize[0]*2));




		
	volume = vtkVolume::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	

	

	CreateAxesScal( itsCL);

renhf=new HFRendererVol(1,volume,scalarBar,axes2,itsCL,volumeMapper,ss2);

//должно заносится из командной строки
renhf->Start(itsCL.itsAxes,itsCL.itsScalarBar);


	
	}



	void CreateVolumePlane(HFPCommandLine itsCL)
	{
		vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	opacityTransferFunction->AddPoint(0, 0.0);
	opacityTransferFunction->AddPoint(149, 0.00);
	opacityTransferFunction->AddPoint(150, 0.1);
	//близкие значения для уменьшения 
	opacityTransferFunction->AddPoint(151, 1.0);
	opacityTransferFunction->AddPoint(255, 0.8);
	

	// Create transfer mapping scalar value to color
	vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint( 0.0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(149, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint( 150, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint( 151, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint(255, 0.0, 0.0, 1.0);
	//colorTransferFunction->AddRGBPoint( 255, 0.0, 0.1, 0.1);


	// пробные

	vtkPiecewiseFunction* surface
		= vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	surface->AddPoint(0, 0.0);
	surface->AddPoint(149, 0.1);
	surface->AddPoint(150, 0.4);
	//surface->AddPoint(160, 0.4);
	//surface->AddPoint(180, 0.4);


	surface->AddPoint(255, 1.0);



		vtkImageData* im=sample->GetOutput();//->SetScalarTypeToChar(); //зачем здесь был sample2???
//	im->SetScalarTypeToUnsignedChar();

	double* range=sample->GetOutput()->GetScalarRange();


	vtkImageCast *imageCast = vtkImageCast::New();
 imageCast->SetInput(im ); 
 imageCast->SetOutputScalarTypeToUnsignedChar();

	//im->SetExtent(0,255,0,255,0,255);
	vtkImageThreshold* t1=vtkImageThreshold::New();
t1-> SetInput(im);//imageCast->GetOutput());

t1 ->ReplaceInOn();
t1-> SetInValue (0);
t1 ->ThresholdBetween (150, 255);
//t1->ThresholdBetween( 0,range[1]);
//  t1-> SetInValue (255);
  //t1->SetOutValue (0);
 t1-> Update();



vtkImageShiftScale *ss=vtkImageShiftScale::New();
ss ->SetInputConnection (t1-> GetOutputPort());
ss-> SetOutputScalarTypeToUnsignedChar();

double range2[2];
im->GetScalarRange(range2);
double diff=range2[1]-range2[0];
double slope = 255/diff;
double inter=-slope*range2[0];
double shift=inter/slope;

//printf("%lf=range_max",range2[1]);
table = vtkLookupTable::New();
  table->SetRange((range2[0]+shift)*slope, (range2[1]+shift)*slope); // image intensity range
table->SetHueRange (0, 1/slope);
 table->SetSaturationRange (1, 1);
 table->SetValueRange (1, 1); 
 table->SetRampToLinear();
  table->Build();


ss2=vtkImageShiftScale::New();
ss2->SetShift(shift);
ss2->SetScale(slope);
ss2-> SetOutputScalarTypeToUnsignedChar();
ss2 ->SetInput (im);
ss2->ReleaseDataFlagOff();
ss2->Update();
	

	vtkPiecewiseFunction* gop=vtkPiecewiseFunction::New();
gop-> AddPoint   (0, 1.0);
gop-> AddPoint ( shift*slope-1, 1.0);
gop-> AddPoint ( shift*slope, 0.9);
gop-> AddPoint ( shift*slope+20, 0.0);
gop-> AddPoint (255, 0.0);


	vtkColorTransferFunction* rainbow=vtkColorTransferFunction::New();
rainbow-> SetColorSpaceToHSV();
rainbow ->HSVWrapOff();
rainbow ->AddHSVPoint   (shift*slope-40, 0.1, 1.0, 1.0);
rainbow ->AddHSVPoint (255, 0.9, 1.0, 1.0);




vtkPiecewiseFunction* constant1=vtkPiecewiseFunction::New();

constant1 ->AddPoint  ( 0 ,0.9);
constant1 ->AddPoint (255, 0.7);



	// The property describes how the data will look
	vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
//iso
//	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->SetScalarOpacity(gop);
	volumeProperty->SetColor(rainbow);
//several
//	volumeProperty->SetScalarOpacity(surface);
  // volumeProperty-> SetGradientOpacity (constant1);
	volumeProperty->ShadeOff();
	//volumeProperty->SetInterpolationTypeToNearest();
	volumeProperty->SetInterpolationTypeToLinear();
	//volumeProperty->SetDisableGradientOpacity(0);
//volumeProperty->SetGradientOpacity(opacityTransferFunction);
volumeProperty->SetAmbient(0.3);
volumeProperty->SetDiffuse(1.0);
volumeProperty->SetSpecular(0.2);
volumeProperty->SetSpecularPower(10.0);
	// prop2->SetColor( cTFun );
   
 vtkFiniteDifferenceGradientEstimator *gradest = 
    vtkFiniteDifferenceGradientEstimator::New();
 gradest->SetZeroNormalThreshold(0.1);




 vtkVolumeRayCastCompositeFunction* compositeFunction=vtkVolumeRayCastCompositeFunction::New();
 vtkVolumeRayCastMapper*volumeMapper=vtkVolumeRayCastMapper::New();
//compositeFunction->SetCompositeMethodToClassifyFirst();
//compositeFunction->SetCompositeMethodToInterpolateFirst();
//volumeMapper->SetGradientEstimator(gradest);
    volumeMapper-> SetVolumeRayCastFunction (compositeFunction);

	volumeMapper-> SetBlendModeToComposite();



	volumeMapper-> SetInput(ss2->GetOutput());//imageCast->GetOutput());//im);//sgrid);
	volumeMapper->SetSampleDistance((itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0])/(itsCL.itsGridSize[0]*2));

		
	volume = vtkVolume::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	

	volume->VisibilityOff();
 volume->SetPosition(10,10,0);


	CreateAxesScal( itsCL);

renhf=new HFRendererVol(1,volume,scalarBar,axes2,itsCL,volumeMapper,ss2);

//должно заносится из командной строки
renhf->Start(itsCL.itsAxes,itsCL.itsScalarBar);

	
	}



	void CreateVolume2(HFPCommandLine itsCL)
	{
		

	// Create transfer mapping scalar value to color
	vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint( 0.0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(149, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint( 150, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint( 151, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint(255, 0.0, 0.0, 1.0);
	//colorTransferFunction->AddRGBPoint( 255, 0.0, 0.1, 0.1);


	


		vtkImageData* im=sample->GetOutput();//->SetScalarTypeToChar();
//	im->SetScalarTypeToUnsignedChar();

	double* range=sample->GetOutput()->GetScalarRange();


	vtkImageThreshold* t1=vtkImageThreshold::New();
t1-> SetInput(im);//imageCast->GetOutput());

t1 ->ReplaceInOn();
t1-> SetInValue (0);
t1 ->ThresholdBetween (150, 255);

t1-> Update();



double range2[2];
im->GetScalarRange(range2);
double diff=range2[1]-range2[0];
double slope = 255/diff;
double inter=-slope*range2[0];
double shift=inter/slope;

//printf("%lf=range_max",range2[1]);
table = vtkLookupTable::New();
  table->SetRange((range2[0]+shift)*slope, (range2[1]+shift)*slope); // image intensity range
table->SetHueRange (0, 1/slope);
 table->SetSaturationRange (1, 1);
 table->SetValueRange (1, 1); 
 table->SetRampToLinear();
  table->Build();

/*

vtkLookupTable ColorLookupTable
ColorLookupTable SetNumberOfTableValues 256

for { set i 0 } { $i < 256 } { incr i } {
    set r [colorTransferFunction GetRedValue $i]
    set g [colorTransferFunction GetGreenValue $i]
    set b [colorTransferFunction GetBlueValue $i]
    set a [opacityTransferFunction GetValue $i]
    set a [expr $a * 10.0]
    if { $a > 1.0 } { set a 1.0 }
    ColorLookupTable SetTableValue $i $r $g $b $a
}

*/
vtkImageShiftScale *ss2=vtkImageShiftScale::New();
ss2->SetShift(shift);
ss2->SetScale(slope);
ss2-> SetOutputScalarTypeToUnsignedChar();
ss2 ->SetInput (im);
ss2->ReleaseDataFlagOff();
ss2->Update();

int roundSech=(int)itsCL.itsGridSize[1]/2;

		vtkExtractVOI *extract = vtkExtractVOI::New();
	extract->SetInput(ss2->GetOutput());
extract->SetVOI(0, itsCL.itsGridSize[0],  roundSech-1, roundSech,0, itsCL.itsGridSize[2]);
extract->SetSampleRate((itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0])/itsCL.itsGridSize[0], (itsCL.itsBBMinMax[4]-itsCL.itsBBMinMax[1])/itsCL.itsGridSize[1], (itsCL.itsBBMinMax[5]-itsCL.itsBBMinMax[2])/itsCL.itsGridSize[2]);


	

	vtkPiecewiseFunction* gop=vtkPiecewiseFunction::New();
gop-> AddPoint   (0, 1.0);
//gop-> AddPoint ( shift*slope-100, 1.0);
gop-> AddPoint ( shift*slope, 0.9);
gop-> AddPoint ( shift*slope+20, 0.0);
gop-> AddPoint (255, 0.0);


	vtkColorTransferFunction* rainbow=vtkColorTransferFunction::New();
rainbow-> SetColorSpaceToHSV();
rainbow ->HSVWrapOff();
rainbow ->AddHSVPoint   (0.0, 0.1, 1.0, 1.0);
rainbow ->AddHSVPoint (255, 0.9, 1.0, 1.0);



	// The property describes how the data will look
	volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
	volumeProperty->SetScalarOpacity(gop);
	volumeProperty->SetColor(rainbow);
	volumeProperty->ShadeOff();
	volumeProperty->SetInterpolationTypeToLinear();
volumeProperty->SetAmbient(0.3);
volumeProperty->SetDiffuse(1.0);
volumeProperty->SetSpecular(0.2);
volumeProperty->SetSpecularPower(10.0);
   
 vtkFiniteDifferenceGradientEstimator *gradest = 
    vtkFiniteDifferenceGradientEstimator::New();
 gradest->SetZeroNormalThreshold(0.1);




vtkVolumeRayCastCompositeFunction*  compositeFunction=vtkVolumeRayCastCompositeFunction::New();
 volumeMapper=vtkVolumeRayCastMapper::New();
    volumeMapper-> SetVolumeRayCastFunction (compositeFunction);

	volumeMapper-> SetBlendModeToComposite();
	volumeMapper-> SetInput(extract->GetOutput());//imageCast->GetOutput());//im);//sgrid);
	volumeMapper->SetSampleDistance((itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0])/(itsCL.itsGridSize[0]*2));

		
	
	CreateAxesScal( itsCL);

renhf=new HFRendererVol(1,volume,scalarBar,axes2,itsCL,volumeMapper,ss2);

//должно заносится из командной строки
renhf->Start(itsCL.itsAxes,itsCL.itsScalarBar);

	
	}
	


};


class HFRendererVol2
{
public:

	vtkRenderer *ren1;
	vtkRenderWindow *renWin;
	vtkRenderWindowInteractor *iren;
	vtkScalarBarActor*scalarBar;
	vtkAxesActor*axesact;
	vtkVolume *contActor;
	vtkUnstructuredGridVolumeRayCastMapper *contMapper;
	vtkFollower *XActor;
	vtkFollower *YActor;
	vtkFollower *ZActor;
	vtkImageShiftScale*ss2;
	//vtkVolume*volume;
	vtkLight* light;
HFPCommandLine itsCL;
	int vol;
	HFRendererVol2( int vol, vtkVolume *cont, vtkScalarBarActor*scalarBar1, vtkAxesActor*axes1,HFPCommandLine itsCL,vtkUnstructuredGridVolumeRayCastMapper *contMapper,vtkImageShiftScale* ss2)
	{
		this->vol=vol;
		this->itsCL=itsCL;
				this->ss2=ss2;
	
this->contActor=cont;
this->contMapper=contMapper;
	this->axesact=axes1;
	this->scalarBar=scalarBar1;
	}


	void Delete()
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
	// ругается на удаление аctor-в
	
	


			ren1->Delete();
	renWin->Delete();
	iren->Delete();
	
		}

		~HFRendererVol2()
		{
			
	
		}
	void Start(int axes, int scal)
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
  // для scalar bar
  ren2->AddActor2D(scalarBar);
   ren2->SetViewport(0.85, 0, 1.0, 1.0);
  ren2->SetBackground(0.3, 0.3, 0.3);
  ren2->SetBackground(0.3, 0.3, 0.3);
 }
  // для scalar bar

 // renWin->SetSize(300,300);



  // add the actors to the scene
   if (axes)
  // axes
   ren1->AddActor(axesact);


ren1->AddVolume(contActor);


 

  ren1->SetBackground(1,1,1); // Background color white
  renWin->Render();
 
  // begin mouse interaction
  iren->Initialize();
  iren->Start();


	}



	
		void SetPosition(double x, double y, double z)
	{
	
  contActor->AddPosition(x,y,z);


	}

	
	void SetLight(double * fp, double* pos)
	{

	
// Set up the lighting.
  //
 light = vtkLight::New();
  light->SetFocalPoint(fp[0],fp[1],fp[2]);
  light->SetPosition(pos[0],pos[1],pos[2]);
  ren1->AddLight(light);
light->Delete();
	}

void SetCamera(double * fp, double* pos, double* v)
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

void SetCameraParal(int v)
	{
		if (v)
		 ren1->GetActiveCamera()->ParallelProjectionOn();
		else
		ren1->GetActiveCamera()->ParallelProjectionOff();
	}



};



	class Volume2
	{
public:

	SampFunc *sample;
		double length;
	

vtkPolyDataMapper *contMapper;
	vtkActor *contActor;
	HFRendererVol2* renhf;
	vtkScalarBarActor*scalarBar;
vtkAxesActor*axes2;

vtkLookupTable*table;
vtkImageShiftScale* ss2;
vtkVolumeRayCastCompositeFunction*compositeFunction;
vtkVolumeRayCastMapper* volumeMapper;
vtkVolumeProperty* volumeProperty;
//vtkVolume* volume2;
vtkVolume* volume;


		Volume2(SampFunc *samp)
		
		{ this->sample=samp;
		}

		void Delete()
	{
		
		renhf->Delete();
	}
	~Volume2()
	{
		
	}

void CreateVolumeUns( HFPCommandLine itsCL)
	{
		vtkPiecewiseFunction *opacityTransferFunction = vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	opacityTransferFunction->AddPoint(0, 0.0);
	opacityTransferFunction->AddPoint(149, 0.00);
	opacityTransferFunction->AddPoint(150, 0.1);
	//близкие значения для уменьшения 
	opacityTransferFunction->AddPoint(151, 1.0);
	opacityTransferFunction->AddPoint(255, 0.8);
	

	// Create transfer mapping scalar value to color
	vtkColorTransferFunction *colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint( 0.0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(149, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint( 150, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint( 151, 0.0, 0.0, 1.0);
	colorTransferFunction->AddRGBPoint(255, 0.0, 0.0, 1.0);
	//colorTransferFunction->AddRGBPoint( 255, 0.0, 0.1, 0.1);


	// пробные

	vtkPiecewiseFunction* surface
		= vtkPiecewiseFunction::New();
	//opacityTransferFunction->AddPoint(0, -0.01);
	surface->AddPoint(0, 0.0);
	surface->AddPoint(149, 0.1);
	surface->AddPoint(150, 0.4);
	//surface->AddPoint(160, 0.4);
	//surface->AddPoint(180, 0.4);


	surface->AddPoint(255, 1.0);




		vtkImageData* im=sample->GetOutput();//->SetScalarTypeToChar();
//	im->SetScalarTypeToUnsignedChar();

	double* range=sample->GetOutput()->GetScalarRange();


	vtkImageCast *imageCast = vtkImageCast::New();
 imageCast->SetInput(im ); 
 imageCast->SetOutputScalarTypeToUnsignedChar();

	//im->SetExtent(0,255,0,255,0,255);
	vtkImageThreshold* t1=vtkImageThreshold::New();
t1-> SetInput(im);//imageCast->GetOutput());

t1 ->ReplaceInOn();
t1-> SetInValue (0);
t1 ->ThresholdBetween (150, 255);
//t1->ThresholdBetween( 0,range[1]);
//  t1-> SetInValue (255);
  //t1->SetOutValue (0);
 t1-> Update();



vtkImageShiftScale *ss=vtkImageShiftScale::New();
ss ->SetInputConnection (t1-> GetOutputPort());
ss-> SetOutputScalarTypeToUnsignedChar();

double range2[2];
im->GetScalarRange(range2);
double diff=range2[1]-range2[0];
double slope = 255/diff;
double inter=-slope*range2[0];
double shift=inter/slope;

//printf("%lf=range_max",range2[1]);
table = vtkLookupTable::New();
  table->SetRange((range2[0]+shift)*slope, (range2[1]+shift)*slope); // image intensity range
table->SetHueRange (0, 1);
 table->SetSaturationRange (1, 1);
 table->SetValueRange (1, 1); 
 table->SetRampToLinear();
  table->Build();


ss2=vtkImageShiftScale::New();
ss2->SetShift(shift);
ss2->SetScale(slope);
ss2-> SetOutputScalarTypeToUnsignedChar();
ss2 ->SetInput (im);
ss2->ReleaseDataFlagOff();
ss2->Update();
	

	vtkPiecewiseFunction* gop=vtkPiecewiseFunction::New();
gop-> AddPoint   (0, 1.0);
gop-> AddPoint ( shift*slope-1, 1.0);
gop-> AddPoint ( shift*slope, 0.9);
gop-> AddPoint ( shift*slope+20, 0.0);
gop-> AddPoint (255, 0.0);


	vtkColorTransferFunction* rainbow=vtkColorTransferFunction::New();
rainbow-> SetColorSpaceToHSV();
rainbow ->HSVWrapOff();
rainbow ->AddHSVPoint   (shift*slope-40, 0.1, 1.0, 1.0);
rainbow ->AddHSVPoint (255, 0.9, 1.0, 1.0);




vtkPiecewiseFunction* constant1=vtkPiecewiseFunction::New();

constant1 ->AddPoint  ( 0 ,0.9);
constant1 ->AddPoint (255, 0.7);



	// The property describes how the data will look
	vtkVolumeProperty *volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
//iso
//	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->SetScalarOpacity(gop);
	volumeProperty->SetColor(rainbow);
//several
//	volumeProperty->SetScalarOpacity(surface);
  // volumeProperty-> SetGradientOpacity (constant1);
	volumeProperty->ShadeOff();
	//volumeProperty->SetInterpolationTypeToNearest();
	volumeProperty->SetInterpolationTypeToLinear();
	//volumeProperty->SetDisableGradientOpacity(0);
//volumeProperty->SetGradientOpacity(opacityTransferFunction);
volumeProperty->SetAmbient(0.3);
volumeProperty->SetDiffuse(1.0);
volumeProperty->SetSpecular(0.2);
volumeProperty->SetSpecularPower(10.0);
	// prop2->SetColor( cTFun );
   
 vtkFiniteDifferenceGradientEstimator *gradest = 
    vtkFiniteDifferenceGradientEstimator::New();
 gradest->SetZeroNormalThreshold(0.1);



	vtkPlane* plane=vtkPlane::New();
   plane->SetOrigin(ss2->GetOutput()->GetCenter());
   plane-> SetNormal (0, 0, -1);

   /*
 	vtkClipVolume* clip=	vtkClipVolume::New();
  clip-> SetInputConnection (ss2-> GetOutputPort());
 // clip-> SetValue (1.0);
  clip->SetClipFunction(plane);
  clip-> GenerateClippedOutputOff();
  */
 vtkClipDataSet* clip=vtkClipDataSet::New();
   clip ->SetInputConnection (ss2->GetOutputPort());
   clip-> SetClipFunction (plane);
   clip-> InsideOutOn();
   clip-> SetValue (0.0);
   clip->GenerateClipScalarsOff();



  vtkUnstructuredGridVolumeRayCastMapper *volumeMapper =
   vtkUnstructuredGridVolumeRayCastMapper::New();
vtkDataSetTriangleFilter *tri = vtkDataSetTriangleFilter::New();
tri->SetInput(clip->GetOutput());
volumeMapper->SetInputConnection(clip->GetOutputPort());


  


	volumeMapper-> SetInput(ss2->GetOutput());//imageCast->GetOutput());//im);//sgrid);
	//volumeMapper->SetSampleDistance((itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0])/(itsCL.itsGridSize[0]*2));
		
	volume = vtkVolume::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	

	


	CreateAxesScal( itsCL);

renhf=new HFRendererVol2(1,volume,scalarBar,axes2,itsCL, volumeMapper, ss2);

//должно заносится из командной строки
renhf->Start(itsCL.itsAxes,itsCL.itsScalarBar);


	}



	void	CreateAxesScal( HFPCommandLine itsCL,int tab=0)

	{

if (itsCL.itsScalarBar)
{
	// scalar bar

	scalarBar=vtkScalarBarActor::New();
	// if ((itsCL.itsVolume)||(tab))
	//	 scalarBar->SetLookupTable(table);
	// else
	 
scalarBar->SetLookupTable(table);
	 
//atext->Update();
//	 scalarBar->SetLookupTable(atext->GetLookupTable());
  scalarBar->SetTitle("Attributes");
  scalarBar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
  scalarBar->GetPositionCoordinate()->SetValue(0.01, 0.05);
  scalarBar->SetOrientationToVertical();
  scalarBar->SetWidth(0.4);
  scalarBar->SetHeight(0.9);
  scalarBar->SetLabelFormat("%-#3.3f");
scalarBar->SetPosition(scalarBar->GetPosition());
  scalarBar->SetNumberOfLabels(8);

// scalar bar
}


  if (itsCL.itsAxes)
  {
 //axes
 axes2 = vtkAxesActor::New();

  // simulate a left-handed coordinate system
  //
  
  axes2->SetShaftTypeToCylinder();
  //axes2->SetUserTransform( transform );
  axes2->SetXAxisLabelText( "x" );
  axes2->SetYAxisLabelText( "y" );
  axes2->SetZAxisLabelText( "z" );
  axes2->SetOrigin(0,0,0);
 // axes2->SetNormalizedShaftLength(0.5,0.5,0.5);
  //axes2->SetNormalizedTipLength(0.5,0.5,0.5);
  //axes2->setT
 length= itsCL.itsBBMinMax[3]-itsCL.itsBBMinMax[0];
 length=length/2;
  axes2->SetTotalLength( length, length, length );
  axes2->SetCylinderRadius( 0.100 * axes2->GetCylinderRadius() );
  axes2->SetConeRadius    ( 0.5 * axes2->GetConeRadius() );
  axes2->SetSphereRadius  ( 1.500 * axes2->GetSphereRadius() );

  vtkTextProperty* tprop = axes2->GetXAxisCaptionActor2D()->
    GetCaptionTextProperty();
  tprop->ItalicOn();
  tprop->ShadowOn();
  tprop->SetColor(0,0,1);
  tprop->SetFontFamilyToTimes();

  axes2->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
  axes2->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
  }
//axes->SetOrigin(bounds[0], bounds[1], bounds[2]);


	
   //  axes->SetScaleFactor(length);
	
	
	
	}











};

