
#include "colormap.h"


ColorMap::ColorMap(SampFunc *samp,ImpFunc* func, bool bAttributes)

{ this->sample=samp;
this->func=func;
this->bAttributes=bAttributes;
}

void ColorMap::Delete()
{
planeCut->Delete();
sample->Delete();
pol->Delete();
contMapper->Delete();
//	contActor->Delete();
//delete renhf;
renhf->Delete();
}


void ColorMap::CreateMap(HFPCommandLine itsCL)
{

vtkPlane* plane=vtkPlane::New();
plane->SetOrigin(sample->GetOutput()->GetCenter());
plane-> SetNormal (0, 0, -1);

planeCut=vtkCutter::New();
planeCut->SetInput(sample->GetOutput());

InverseImpFunc* funct=InverseImpFunc::New();
funct->SetFunct(func);

planeCut ->SetCutFunction ((vtkImplicitFunction*)funct);

planeCut-> GenerateCutScalarsOff();
// planeCut-> SetValue (0, 0.5);

vtkStripper* cutStrips=vtkStripper::New();//; #Forms loops (closed polylines) from cutter
cutStrips-> SetInputConnection (planeCut-> GetOutputPort());
cutStrips ->Update();
vtkPolyData* cutPoly=vtkPolyData::New(); //#This trick defines polygons as polyline loop
cutPoly-> SetPoints (cutStrips-> GetOutput()-> GetPoints());
cutPoly-> SetPolys (cutStrips ->GetOutput()-> GetLines());
vtkTriangleFilter* cutTriangles=vtkTriangleFilter::New(); //#Triangulates the polygons to create cut surface
cutTriangles ->SetInput (cutPoly);
//funct->Update();
//funct->ComputeNormalsOff();

vtkClipDataSet* clip=vtkClipDataSet::New();
clip ->SetInputConnection (sample->GetOutputPort());
clip-> SetClipFunction ((vtkImplicitFunction*)funct);
clip-> InsideOutOn();
clip-> SetValue (0.0);
clip->GenerateClipScalarsOff();


pol=vtkPolyData::New();
pol=cutPoly;
// pol=clip->GetOutput();
// pol->GetBounds(bounds);

clipMapper=vtkDataSetMapper::New();
clipMapper-> SetInputConnection (clip-> GetOutputPort());
clipMapper-> SetScalarRange (planeCut-> GetOutput()-> GetScalarRange());
//clipMapper->SetScalarRange(itsCL.itsContMinMax[2], itsCL.itsContMinMax[3]);


// map the contours to graphical primitives
contMapper = vtkPolyDataMapper::New();
contMapper->SetInput(planeCut->GetOutput());//cutPoly);
// contMapper->SetInputConnection(cutTriangles->GetOutputPort());//contours->GetOutput());
contMapper->SetColorModeToMapScalars();
//  contMapper->SetScalarRange(itsCL.itsContMinMax[2], itsCL.itsContMinMax[3]);

contMapper->SetScalarRange(planeCut->GetOutput()->GetScalarRange());//sample->GetOutput()->GetScalarRange());
// contMapper->GetBounds(bounds);

// create an actor for the contours
contActor = vtkActor::New();
contActor->SetMapper(contMapper);
//contActor->GetProperty()->SetOpacity(0.2);


CreateAxesScal( itsCL);

renhf=new HFRenderer(0,contActor,scalarBar,axes2,itsCL);

//должно заносится из командной строки
renhf->Start(itsCL.itsAxes,itsCL.itsScalarBar);


}

void	ColorMap::CreateAxesScal( HFPCommandLine itsCL,int tab)

{

if (itsCL.itsScalarBar)
{
// scalar bar

scalarBar=vtkScalarBarActor::New();
// if ((itsCL.itsVolume)||(tab))
//	 scalarBar->SetLookupTable(table);
// else

scalarBar->SetLookupTable(contMapper->GetLookupTable());

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
tprop->SetFontFamilyToTimes();

axes2->GetYAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
axes2->GetZAxisCaptionActor2D()->GetCaptionTextProperty()->ShallowCopy( tprop );
}
//axes->SetOrigin(bounds[0], bounds[1], bounds[2]);



//  axes->SetScaleFactor(length);



}






