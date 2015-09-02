#include "mainApp.h"


/*

Basic class rewritten from HFPolygonizer so that it transmit 
HF object to Implicit function of VTK


*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainApp::CMainApp(int & argc, char ** argv)
{
#ifdef DEBUG
    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); // Get current flag
    flag |= _CRTDBG_LEAK_CHECK_DF;
    flag |= _CRTDBG_ALLOC_MEM_DF;
    flag |= _CRTDBG_CHECK_ALWAYS_DF;
    flag |= _CRTDBG_CHECK_CRT_DF;
    _CrtSetDbgFlag(flag); // Set flag to the new value
#endif


    try{
        //ѕолучение аргументов строки
        itsCL.Init(argc, argv);
        Triangulate=itsCL.itsTriangulate;
    }
    catch(CommandLineError err){
        std::cout << err.error << "\n\n";



        std::cout << err.help << "\n\n";
        std::cout << "Exiting..." << "\n\n";
        exit(0);
    }
}


CMainApp::~CMainApp(){
	//if(itsPolyMesh_!=NULL)
		//delete itsPolyMesh_;
}
void CMainApp::getBoundingBox(){
	bounds[0] = (float)itsCL.itsBBMinMax[0];
	bounds[2] = (float)itsCL.itsBBMinMax[1];
	bounds[4] = (float)itsCL.itsBBMinMax[2]; 

	bounds[1] = (float)itsCL.itsBBMinMax[3];
	bounds[3] = (float)itsCL.itsBBMinMax[4];
	bounds[5] = (float)itsCL.itsBBMinMax[5]; 
}


int CMainApp::init( ) {
	std::cout << "Initialization.";
	if(itsCL.itsTimeReport) std::cout << "\n\n";
//	if(itsCL.itsTimeReport) itsTimer.start("Time to Read and Parse File");
	readFile();
//	if(!itsCL.itsTimeReport) std::cout << ".";
	parseString();
//	if(!itsCL.itsTimeReport) std::cout << ".";
//	if(itsCL.itsTimeReport) itsTimer.stop();
/*if(itsCL.itsTriangulate)
{
	generateTriangles();
}*/
	
	getBoundingBox();


	return 0;
}


void CMainApp::readFile(){
	// ********** READ FILE *************
	//Read file
	std::ifstream fromFile(itsCL.itsModel.c_str());
	if(!fromFile){
		std::cout << "\n File: " << itsCL.itsModel << " not found\n";
		exit(0);
	}
	//Read file into string
	char ch;
	// int i=0;
	while(fromFile.get(ch))	itsString+=ch;
	ch = '\0';
	itsString+=ch;
	//Check correct transfer
	if(!fromFile.eof()){
		std::cout << "\nFile Read Error.\n";
		exit(0);
	}
	//Close fromFile
	fromFile.close();
	// **********************************
}


void CMainApp::parseString(){

	try{
		itsInterpreter.parse(itsString, itsCL.itsObject);
	}
	//Check for memory error during Parse
	catch(MemoryError me){
		std::cout << "\nMemory Allocation Error on Parse!\nNot Enough Memory to complete Parse!\n";
		std::cout << "Occured at: " << me.error << "\n";
		std::cout << "Exiting..." << "\n";
		exit(0);
	}
	//Check for Errors in File while parsing
	catch(ParseError pe){
		std::cout << "Error: " << pe.error; 
		std::cout << "\n" << "       line = " << pe.line;
		std::cout << " , position = " << pe.pos << "\n" << "\n";
		std::cout << "Exiting..." << "\n";
		exit(0);
	}


	//Set itsObject
	//itsInterpreter.object(itsCL.itsObject);


}

///----------------------------------------------
//-----------VTK
//-------------------------------------------------
void CMainApp::StartImpl(bool bAttributes)
	{
  
function = ImpFunc::New();
function->GetInterpreter(&itsInterpreter,itsCL.itsGridSize[0]*itsCL.itsGridSize[1]*itsCL.itsGridSize[2]);

double fval=function->EvaluateFunction(0,0,0);
printf("%lf \n",fval);
//error somewhere - used for volume
/*
{
sgrid = vtkStructuredGrid::New();
      sgrid->SetDimensions(itsCL.itsGridSize[0],itsCL.itsGridSize[1],itsCL.itsGridSize[2]);

	  double p[3];
	  double spacing[3];
spacing [0]=(itsCL.itsBBMinMax[4]-itsCL.itsBBMinMax[0])/itsCL.itsGridSize[0];
spacing [1]=(itsCL.itsBBMinMax[5]-itsCL.itsBBMinMax[1])/itsCL.itsGridSize[1];
spacing [2]=(itsCL.itsBBMinMax[6]-itsCL.itsBBMinMax[2])/itsCL.itsGridSize[2];
vtkPoints *points = vtkPoints::New();
vtkFloatArray *scal = vtkFloatArray::New();

   for (int i=0; i <= itsCL.itsGridSize[0]; i++ )
    {
		p[0] = itsCL.itsBBMinMax[0] + i*spacing[0];
     for (int j=0; j <= itsCL.itsGridSize[1]; j++ )
      {
      p[1] = itsCL.itsBBMinMax[1] + j*spacing[1];
      for (int k=0; k <= itsCL.itsGridSize[2]; k++ )
      {
      p[2] = itsCL.itsBBMinMax[2] + k*spacing[2];
     points->InsertNextPoint(p);
scal->InsertNextTuple1(function->FunctionValue(p));
	  }
	  }
	}

	sgrid->SetPoints(points);
 // points->Delete();
  sgrid->GetPointData()->SetScalars(scal);
  //scal->Delete();

     
	
}
*/
{
sample = SampFunc::New();
  sample->SetSampleDimensions(itsCL.itsGridSize[0],itsCL.itsGridSize[1],itsCL.itsGridSize[2]);
  sample->SetImplicitFunction(function); 
  // 0 - function value
  //-1 - 3 attributes to color
  /*
if (bAttributes)
{

 for (int i=0;i<function->itsSSize-1;i++)
 	 imData.push_back(vtkImageData::New());
 for (int i=1;i<function->itsSSize;i++)
 {
	 sample->SetFunAttNum(i);
	 sample->SetModelBounds  	(bounds[0],bounds[1],bounds[2],bounds[3],bounds[4],bounds[5]) ;	
	 sample->ComputeNormalsOn();
	 sample->Update();
	 //CopyStructure
	 imData[i]->CopyStructure(sample->GetOutput());
 }
}

 */
  sample->SetFunAttNum(0);

 sample->SetModelBounds  	(bounds[0],bounds[1],bounds[2],bounds[3],bounds[4],bounds[5]) ;	
 
  sample->ComputeNormalsOn();
  sample->Update();


 // this bounds are not set
//sample->GetOutput()->GetBounds(bounds);




}
  //sample->ComputeNormalsOff();
	}


void CMainApp::createImplFunction(bool bNormal, bool bVertexNormal, bool bAttributes)
{

	//”же создана триангулированна€ поверхность???? - поставить заглушку чтобы не создавалась
	//int t = itsPolyMesh_->TriangleNum();

//	printf ("t=%d\n",t);
	int index;
	double* color;
	 
	  double * point;
	  double ex=0;
	  double scalval=0;


int realp;
realp=0;
getBoundingBox();
//StartImpl(itsCL.itsAttributes);
function = ImpFunc::New();
function->GetInterpreter(&itsInterpreter,itsCL.itsGridSize[0]*itsCL.itsGridSize[1]*itsCL.itsGridSize[2]);

double fval=function->EvaluateFunction(0,0,0);
int DimF=itsInterpreter.getXSize();
//if(DimF==3)
{
this->cont=new Contour3D(this->function,this->itsCL.itsAttributes,this->function->itsSSize );
		this->cont->CreateContour(this->itsCL);
    this->ren1=cont->getRenderer();
}

/*
else // right now it's 4
{
	int gsize=itsCL.itsGridSize[3];
	//bounds[4],bounds[5]
	double tt;
	for (int j=0;j<1;j++)
	{
		tt=bounds[4]+j*(bounds[5]-bounds[4])/gsize;

	}

}
*/

//old code from first version
//some of all this is not needed any longer

/*
if (itsCL.itsCont) //itsCL.itsContNum>0)
  {
 
	  if (bAttributes)
	  {
	   //цветова€ карта
	
		this->colorm=new ColorMap(this->sample,this->function,bAttributes);
		this->colorm->CreateMap(this->itsCL);
		 //delete cause crash
//this->colorm->Delete();
	  }
	  else
	  {

		  // карта изолиний
		  this->cont=new Contour3D(this->sample,this->itsCL.itsAttributes,this->function->itsSSize );
		this->cont->CreateContour(this->itsCL);
		 //delete cause crash
//this->cont->Delete();
	  }
}
   if (itsCL.itsVolume)

  {	   if (bAttributes)
	  {
		   this->vol2=new Volume2(this->sample);
		   this->vol2->CreateVolumeUns(this->itsCL);
		    //delete cause crash
//this->vol2->Delete();
	
	  }
  else
  {
	  this->vol1=new Volume1(this->sample);
	  if (itsCL.itsVolumeType==0)
	  {
		  

	
		this->vol1->CreateVolume1(this->itsCL);
		
	

  }



  if (itsCL.itsVolumeType==1)
	  {
		  
		  
		this->vol1->CreateVolume4(this->itsCL);
		
  }





  if (itsCL.itsVolumeType==2)
	  {
		  
		  
		this->vol1->CreateVolume3(this->itsCL);
		
  }

 //delete cause crash
//this->vol1->Delete();

  }

 }
 
*/

 
}


