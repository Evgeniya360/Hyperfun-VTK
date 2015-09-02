



#include "contour3D.h"

void Sound3D::main1 ()
{


	// Initialize OpenAL and clear the error bit.

	alutInit(NULL, 0);
	alGetError();

	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop = AL_TRUE;
	alutLoadWAVFile("BuzzingBee.wav", &format, &data, &size, &freq, &loop);
	alGenBuffers(1, &Buffer);
	alBufferData(Buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);


}
	ALboolean Sound3D::LoadALData()
{

	alGenSources(1, &Source1);
//	alGenSources(1, &Source2);
//	alGenSources(1, &Source3);
//	alGenSources(1, &Source4);
//	alGenSources(1, &Source5);
//	alGenSources(1, &Source6);

	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;



	alSourcei (Source1, AL_BUFFER,   Buffer   );
	alSourcef (Source1, AL_PITCH,    1.0      );
	alSourcef (Source1, AL_GAIN,     1.0      );
	alSourcei (Source1, AL_LOOPING,  1     );



	if(alGetError() == AL_NO_ERROR)
		return AL_TRUE;

	return AL_FALSE;
	
}
void Sound3D::KillALData()
{
	//alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source1);

}

Sound3D::Sound3D(ImpFunc * function, bool Attributes, int size, double k)
{
	this->function=function;
		this->Attributes= Attributes;
		this->sSize=size;
		this->k=k;
	  main1();
		LoadALData();
};

Contour3D::Contour3D(ImpFunc * function, bool Attributes, int size)
		{ this->function=function;
		this->Attributes= Attributes;
		this->sSize=size;
		this->sound=new Sound3D(function,Attributes,size,1);
	
	 
		/*
		for (int i=0;i<6;i++)
		this->bounds[i]=bounds[i];
		*/
	



}



void Contour3D::Delete()
	{
		this->contours->Delete();
		sample->Delete();
		pol->Delete();
		contMapper->Delete();
		//contActor->Delete();
		//delete renhf;
		renhf->Delete();
	}


void Contour3D::CreateContour(HFPCommandLine itsCL)
	{

		bounds[0] = (float)itsCL.itsBBMinMax[0];
	bounds[2] = (float)itsCL.itsBBMinMax[1];
	bounds[4] = (float)itsCL.itsBBMinMax[2]; 

	bounds[1] = (float)itsCL.itsBBMinMax[3];
	bounds[3] = (float)itsCL.itsBBMinMax[4];
	bounds[5] = (float)itsCL.itsBBMinMax[5]; 

	this->sound->setType((float)itsCL.itsSoundK[0]);
	//switch
	if (itsCL.itsAttributes) //2 parameters will be changing
	{
		this->sound->setK((float)itsCL.itsSoundK[1]);
		this->sound->setVol((float)itsCL.itsSoundK[2]);

	}

	else
	this->sound->setK((float)itsCL.itsSoundK[1]);
	sample = SampFunc::New();
	sample->SetSampleDimensions(itsCL.itsGridSize[0],itsCL.itsGridSize[1],itsCL.itsGridSize[2]);
  sample->SetImplicitFunction(function); 
  sample->SetFunAttNum(0);
	 sample->SetModelBounds  	(bounds[0],bounds[1],bounds[2],bounds[3],bounds[4],bounds[5]) ;	
imData.push_back(vtkImageData::New());
sample->Update();
imData[0]->CopyStructure(sample->GetOutput());
	 (imData[0]->GetPointData())->SetScalars((sample->GetOutput())->GetPointData()->GetScalars());

// imData[0]->CopyAndCastFrom(sample->GetOutput(),(sample->GetOutput())->GetExtent());
 imData[0]->Update();
 //imData[0]->GetBounds(bounds);

		//sSize=1;

		if (Attributes)
{

printf("attributes anabled, size=%d\n",sSize);
 for (int i=0;i<sSize;i++)
 	 imData.push_back(vtkImageData::New());
 for (int i=1;i<sSize+1;i++)
 {
	 sample->Delete();
	 	sample = SampFunc::New();
  sample->SetSampleDimensions(itsCL.itsGridSize[0],itsCL.itsGridSize[1],itsCL.itsGridSize[2]);
  sample->SetImplicitFunction(function); 
	 sample->SetFunAttNum(i);
	 sample->SetModelBounds  	(bounds[0],bounds[1],bounds[2],bounds[3],bounds[4],bounds[5]) ;	
	 sample->ComputeNormalsOn();
	//sample->Update();

	 //CopyStructure
	 //imData[i]->CopyStructure(sample->GetOutput());
	
	 sample->Update();
	 imData[i]->CopyStructure(sample->GetOutput());
	 (imData[i]->GetPointData())->SetScalars((sample->GetOutput())->GetPointData()->GetScalars());
// imData[i]->CopyAndCastFrom(sample->GetOutput(),(sample->GetOutput())->GetExtent());

	  imData[i]->Update();
printf("attributes passed, size=%d\n",i);



 }
}


printf("attributes passed2,%d,%d,%d\n",imData.size(),imData[0]->GetNumberOfPoints(),imData[0]->GetNumberOfScalarComponents());  

contours = vtkContourFilter::New();
contours->SetInput(imData[0]);
 // sample->GetOutput()->GetBounds(bounds);
contours->GenerateValues(itsCL.itsContNum, itsCL.itsContMinMax[0], itsCL.itsContMinMax[1]);
printf("Contours number=%d, Cont min=%lf, max=%lf\n",itsCL.itsContNum, itsCL.itsContMinMax[0], itsCL.itsContMinMax[1]);


 pol=vtkPolyData::New();
 contours->Update();
 pol=contours->GetOutput();
// pol->GetBounds(bounds);

 if (Attributes)
 {
	probe2=vtkProbeFilter::New();
    probe2 ->SetInput (pol);
    probe2-> SetSource (imData[1]);
	printf("attributes passed2,%d,%d,%d\n",imData.size(),imData[1]->GetNumberOfPoints(),((imData[1]->GetPointData())->GetScalars())->GetNumberOfTuples());  


	
	clut=vtkLookupTable::New();
    clut-> SetHueRange( 0.67, 0.0);
	//clut->SetAlphaRange(0.2,0.1);
	//clut->SetSaturationRange(0,0.67);
	
	imData[1]->GetScalarRange(range);
	//clut->SetValueRange(range);
    clut-> Build();
	

	
	cast2=vtkCastToConcrete::New();
    cast2-> SetInput (probe2-> GetOutput());
	/*normals=vtkPolyDataNormals::New();
    normals ->SetMaxRecursionDepth( 100);
    normals ->SetInput (cast2 ->GetPolyDataOutput());
    normals ->SetFeatureAngle (45);*/



   
 }


  // map the contours to graphical primitives
  contMapper = vtkPolyDataMapper::New();
 
  if (Attributes)
  {
contMapper->SetInput(cast2->GetPolyDataOutput());//contours->GetOutput());
  contMapper->ScalarVisibilityOn();
 contMapper->SetColorModeToMapScalars();
 //contMapper->SetScalarRange(range);
  // contMapper->SetScalarRange(itsCL.itsContMinMax[2], itsCL.itsContMinMax[3]);

 contMapper ->SetLookupTable( clut);
  }

  else
  {
  contMapper->SetInput(contours->GetOutput());//contours->GetOutput());
   contMapper->SetColorModeToMapScalars();
 contMapper->SetScalarRange(itsCL.itsContMinMax[2], itsCL.itsContMinMax[3]);
 // contMapper->GetBounds(bounds);
  }

  // create an actor for the contours
  contActor = vtkActor::New();
  contActor->SetMapper(contMapper);
  //if(!Attributes)
  contActor->GetProperty()->SetOpacity(0.2);
  contActor->PickableOff();
	contActor->DragableOff();


  //
  
//sound
//sphere
  double boundAct[6];
 
  contActor->GetBounds( boundAct);
  double r=((boundAct[1]-boundAct[0])+(boundAct[3]-boundAct[2])+(boundAct[5]-boundAct[4]))/(3*14);
  
 
 
 // printf("%lf,%lf\n",itsCL.[0], itsCL.itsContMinMax[1]);

CreateAxesScal( itsCL);

	float gain = 0.1;//pblock2->GetFloat(Source_GAIN, t);
		double coords[3];
		coords[0]=boundAct[0];
		coords[1]=boundAct[2];
		coords[2]=boundAct[4];
		

 this->sound->createListener(r,coords);	

		//{(x_min + x_max)/2, (y_min + y_max)/2, (z_min + z_max)/2};
 
	sound->play(coords);

renhf=new HFRenderer(0,contActor,scalarBar,axes2,itsCL);

//должно заносится из командной строки
renhf->StartSound(itsCL.itsAxes,itsCL.itsScalarBar,this->sound);//, KeypressCallbackFunction);



	}





void	Contour3D::CreateAxesScal( HFPCommandLine itsCL,int tab)
{

if (itsCL.itsScalarBar)
{
	// scalar bar

	scalarBar=vtkScalarBarActor::New();
	// if ((itsCL.itsVolume)||(tab))
	//	 scalarBar->SetLookupTable(table);
	// else
	 if(Attributes)
scalarBar->SetLookupTable(clut);
	 else
	 {
		 vtkLookupTable* lut=vtkLookupTable::New();
 lut=(vtkLookupTable *)contMapper->GetLookupTable();
 double ranh[2];
 lut->GetHueRange(ranh);
 lut->SetHueRange (ranh[1], ranh[0]);
 lut->Build();
contMapper->SetLookupTable(lut);
contMapper->SetColorModeToMapScalars();
scalarBar->SetLookupTable(contMapper->GetLookupTable());
	 }
	 
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
  axes2->SetConeRadius    ( 0.2 * axes2->GetConeRadius() );
  axes2->SetSphereRadius  ( 0.500 * axes2->GetSphereRadius() );
  axes2->GetXAxisCaptionActor2D ()->GetTextActor()->SetTextScaleModeToNone(); 
  axes2->GetYAxisCaptionActor2D ()->GetTextActor()->SetTextScaleModeToNone(); 
  axes2->GetZAxisCaptionActor2D ()->GetTextActor()->SetTextScaleModeToNone(); 

  vtkTextProperty* tprop = axes2->GetXAxisCaptionActor2D()->
    GetCaptionTextProperty();
  tprop->ItalicOn();
  tprop->ShadowOn();
  tprop->SetColor(0,0,0);
  tprop->SetFontSize(16);
  tprop->SetOpacity(0.8);
  tprop->SetFontFamilyToTimes();
 // axes2->GetXAxisCaptionActor2D()->SetWidth(0.5);

  axes2->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
  axes2->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
  }
//axes->SetOrigin(bounds[0], bounds[1], bounds[2]);


	
   //  axes->SetScaleFactor(length);
	
	
	
	}



