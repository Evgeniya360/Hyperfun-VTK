#if !defined(CONTOUR3D_H)
#define CONTOUR3D_H

//http://www.rug.nl/cit/hpcv/visualisation/VTK/3Ds/man.html
//http://vtkblog.blogspot.com/2007/04/tutorial-multiple-renderer-in-single.html

#include "implfunc.h"
#include "vtkContourFilter.h"
#include "vtkCaptionActor2D.h"
#include "vtkProbeFilter.h"
#include "vtkImageData.h"
#include "vtkLookupTable.h"
#include "vtkCastToConcrete.h"
#include "vtkPolyDataNormals.h"
#include "vtkPointData.h"
#include "vtkTextActor.h"
#include "HFRenderer.h"

#include "../sound3d.h" 

class Contour3D
    {
	private:
	int dim;
	

	SampFunc* sample;
	vtkCastToConcrete* cast2;
	vtkPolyDataNormals* normals;
	 vtkProbeFilter* probe2;
	 double range[2];
	 vtkLookupTable* clut;
	std::vector<vtkImageData*> imData;
	 bool Attributes;
	 int sSize;

	vtkPolyData* pol;
	vtkContourFilter* contours ;
	vtkProbeFilter* probe;
	double length;
	vtkPolyDataMapper *contMapper;
	vtkActor *contActor;
	HFRenderer* renhf;
	vtkScalarBarActor*scalarBar;
	vtkAxesActor*axes2;
	double bounds[6];
	

	


    public:
		ImpFunc * function;
		Contour3D(ImpFunc * function, bool Attributes, int size);
		Sound3D *sound;
		

		void Delete();
	~Contour3D()
	{
		
	}


	
	void CreateContour(HFPCommandLine itsCL);
	void	CreateAxesScal( HFPCommandLine itsCL,int tab=0);
    vtkRenderer* getRenderer(){return renhf->GetRenderer();}
	


	};





#endif // !defined(CONTOUR3D_H)
