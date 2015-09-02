#if !defined(IMPLFUNC_H)
#define IMPLFUNC_H
#pragma warning( disable : 4786 )

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "..\..\include\hfinterpreter.h"
#include <vtkImplicitFunction.h>
#include "vtkImageAlgorithm.h"
#include <iostream>
#include <fstream>
#include <vector>

class ImpFunc : public vtkImplicitFunction {
public:
    vtkTypeMacro(ImpFunc,vtkImplicitFunction);
    void PrintSelf(ostream& os, vtkIndent indent);

    // Description
    // Create a new function
    static ImpFunc * New(void);

    // Description
    // Evaluate function
    double EvaluateFunction(double x[3]);
    double EvaluateFunction(double x, double y, double z) {
	return this->vtkImplicitFunction::EvaluateFunction(x, y, z);
    }
    double* EvaluateAtr(double x[3]);
	double EvaluateAtr3(double x[3],int n);

    // Description
    // Evaluate gradient for function
    void EvaluateGradient(double x[3], double n[3]);

    // If you need to set parameters, add methods here

double * itsSAttributesM;
std::vector<std::vector<double> > itsSAttributes;//Size itsSSize
std::vector<double> itsSendingX;
int itsSSize;
void GetInterpreter(HFInterpreter* itsInterpreter2, int vNum)
{
	//itsInterpreter=&itsInterpreter2;
	itsInterpreter=itsInterpreter2;
	itsSSize = itsInterpreter->getSSize();
	itsSAttributesM =new double[itsSSize];
	itsSAttributes.reserve(vNum);

}

template <typename T>
inline void fillVector(const T* d, int size, std::vector<T>& ret) const {
	for(int i=0; i < size; i++){
		ret[i] = (T)d[i];
	}
}

	HFInterpreter* itsInterpreter;
//protected:
  ImpFunc();
    
    ~ImpFunc() {}
    ImpFunc(const ImpFunc&) {}
    void operator=(const ImpFunc&) {}

    // Add parameters/members here if you need
};




#endif //


#if !defined(INVIMPLFUNC_H)
#define INVIMPLFUNC_H
#pragma warning( disable : 4786 )

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "..\..\include\hfinterpreter.h"
#include <vtkImplicitFunction.h>
#include "vtkImageAlgorithm.h"
#include <iostream>
#include <fstream>
#include <vector>

class InverseImpFunc : public vtkImplicitFunction {
public:
    vtkTypeMacro(InverseImpFunc,vtkImplicitFunction);
    void PrintSelf(ostream& os, vtkIndent indent);
ImpFunc *Mainfunct;
    // Description
    // Create a new function
    static InverseImpFunc * New(void);

    // Description
    // Evaluate function
    double EvaluateFunction(double x[3]);
    double EvaluateFunction(double x, double y, double z) {
	return this->vtkImplicitFunction::EvaluateFunction(x, y, z);
    }
     // Description
    // Evaluate gradient for function
    void EvaluateGradient(double x[3], double n[3]);
	void SetFunct(ImpFunc*func)
	{
		this->Mainfunct=func;
	}

    // If you need to set parameters, add methods here




//protected:
  InverseImpFunc();
    
    ~InverseImpFunc() {}
    InverseImpFunc(const InverseImpFunc&) {}
    void operator=(const InverseImpFunc&) {}

    // Add parameters/members here if you need
};



#endif //


#if !defined(SAMPLEFUNC_H)
#define SAMPLEFUNC_H
#pragma warning( disable : 4786 )

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "..\..\include\hfinterpreter.h"
#include <vtkImplicitFunction.h>
#include "vtkImageAlgorithm.h"
#include <iostream>
#include <fstream>
#include <vector>

class SampFunc : public vtkImageAlgorithm
{
public:
  vtkTypeRevisionMacro(SampFunc,vtkImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  //for function or attribute

  int FunAttNum;
  void SetFunAttNum(int num)
  {
	  this->FunAttNum=num;
	    int numat=((ImpFunc*)ImplicitFunction)->itsSSize;
		/*if (FunAttNum>numat) // 0 -for function value, if we taken value greater then stack of attributes
		FunAttNum=0;*/


  }

  // Description:
  // Construct with ModelBounds=(-1,1,-1,1,-1,1), SampleDimensions=(50,50,50),
  // Capping turned off, and normal generation on.
  static SampFunc *New();

  // Description:
  // Specify the implicit function to use to generate data.
  virtual void SetImplicitFunction(vtkImplicitFunction*);
  vtkGetObjectMacro(ImplicitFunction,vtkImplicitFunction);

  // Description:
  // Set what type of scalar data this source should generate.
  vtkSetMacro(OutputScalarType,int);
  vtkGetMacro(OutputScalarType,int);
  void SetOutputScalarTypeToDouble()
    {this->SetOutputScalarType(VTK_DOUBLE);}
  void SetOutputScalarTypeToFloat()
    {this->SetOutputScalarType(VTK_FLOAT);}
  void SetOutputScalarTypeToLong()
    {this->SetOutputScalarType(VTK_LONG);}
  void SetOutputScalarTypeToUnsignedLong()
    {this->SetOutputScalarType(VTK_UNSIGNED_LONG);};
  void SetOutputScalarTypeToInt()
    {this->SetOutputScalarType(VTK_INT);}
  void SetOutputScalarTypeToUnsignedInt()
    {this->SetOutputScalarType(VTK_UNSIGNED_INT);}
  void SetOutputScalarTypeToShort()
    {this->SetOutputScalarType(VTK_SHORT);}
  void SetOutputScalarTypeToUnsignedShort()
    {this->SetOutputScalarType(VTK_UNSIGNED_SHORT);}
  void SetOutputScalarTypeToChar()
    {this->SetOutputScalarType(VTK_CHAR);}
  void SetOutputScalarTypeToUnsignedChar()
    {this->SetOutputScalarType(VTK_UNSIGNED_CHAR);}

  // Description:
  // Control the type of the scalars object by explicitly providing a scalar
  // object.  THIS IS DEPRECATED, although it still works!!! Please use
  // SetOutputScalarType instead.
  virtual void SetScalars(vtkDataArray *da);

  // Description:
  // Specify the dimensions of the data on which to sample.
  void SetSampleDimensions(int i, int j, int k);

  // Description:
  // Specify the dimensions of the data on which to sample.
  void SetSampleDimensions(int dim[3]);
  vtkGetVectorMacro(SampleDimensions,int,3);

  // Description:
  // Specify the region in space over which the sampling occurs. The
  // bounds is specified as (xMin,xMax, yMin,yMax, zMin,zMax).
  vtkSetVector6Macro(ModelBounds,double);
  vtkGetVectorMacro(ModelBounds,double,6);

  // Description:
  // Turn on/off capping. If capping is on, then the outer boundaries of the
  // structured point set are set to cap value. This can be used to insure
  // surfaces are closed.
  vtkSetMacro(Capping,int);
  vtkGetMacro(Capping,int);
  vtkBooleanMacro(Capping,int);
  
  // Description:
  // Set the cap value.
  vtkSetMacro(CapValue,double);
  vtkGetMacro(CapValue,double);

  // Description:
  // Turn on/off the computation of normals (normals are float values).
  vtkSetMacro(ComputeNormals,int);
  vtkGetMacro(ComputeNormals,int);
  vtkBooleanMacro(ComputeNormals,int);

  // Description:
  // Set/get the scalar array name for this data set. Initial value is
  // "scalars".
  vtkSetStringMacro(ScalarArrayName);
  vtkGetStringMacro(ScalarArrayName);
  
  // Description:
  // Set/get the normal array name for this data set. Initial value is
  // "normals".
  vtkSetStringMacro(NormalArrayName);
  vtkGetStringMacro(NormalArrayName);
  
  // Description:
  // Return the MTime also considering the implicit function.
  unsigned long GetMTime();

protected:
  // Description:
  // Default constructor.
  // Construct with ModelBounds=(-1,1,-1,1,-1,1), SampleDimensions=(50,50,50),
  // Capping turned off, CapValue=VTK_DOUBLE_MAX, normal generation on,
  // OutputScalarType set to VTK_DOUBLE, ImplicitFunction set to NULL,
  // ScalarArrayName is "" and NormalArrayName is "".
  SampFunc();
  
  ~SampFunc();

  virtual void ReportReferences(vtkGarbageCollector*);

  void ExecuteData(vtkDataObject *);
  virtual int RequestInformation (vtkInformation *, 
                                  vtkInformationVector **,
                                  vtkInformationVector *);
  void Cap(vtkDataArray *s);

  int OutputScalarType;
  int SampleDimensions[3];
  double ModelBounds[6];
  int Capping;
  double CapValue;
  vtkImplicitFunction *ImplicitFunction;
  int ComputeNormals;
  char *ScalarArrayName;
  char *NormalArrayName;
  
private:
  SampFunc(const SampFunc&);  // Not implemented.
  void operator=(const SampFunc&);  // Not implemented.
};
#endif //