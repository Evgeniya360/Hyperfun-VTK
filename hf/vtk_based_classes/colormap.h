
#if !defined(HFCOLORMAP_H)
#define HFCOLORMAP_H




#include "hfrenderer.h";
#include "implfunc.h"
#include "vtkCutter.h"
#include "vtkPlane.h"
#include "vtkImageData.h" 
#include "vtkStripper.h"
#include "vtkClipDataSet.h"
#include "vtkTriangleFilter.h"
#include "vtkCaptionActor2D.h"
#include "vtkContourFilter.h"
#include "vtkOutlineFilter.h"


class ColorMap
    {
	private:
		ImpFunc*func;
		bool bAttributes;
		//vtkContourFilter *contours;
		vtkCutter* planeCut;
		SampFunc *sample;
		vtkPolyData* pol;
		double length;
		vtkPolyDataMapper *contMapper;
		vtkActor *contActor;
		HFRenderer* renhf;
		vtkScalarBarActor*scalarBar;
		vtkAxesActor*axes2;
		vtkDataSetMapper* clipMapper;
	public:
		ColorMap(SampFunc *samp,ImpFunc* func, bool bAttributes);

		void Delete();

		~ColorMap()
		{

		}


		void CreateMap(HFPCommandLine itsCL);
		void	CreateAxesScal( HFPCommandLine itsCL,int tab=0);

};


#endif //