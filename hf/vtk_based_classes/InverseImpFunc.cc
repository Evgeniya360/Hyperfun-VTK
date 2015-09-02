// -*- Mode: c++; c-indentation-style: stroustrup; c-basic-offset: 4 -*-

#include <vtkImplicitFunction.h>
#include "implfunc.h"

//------------------------------------------------------------------------------
InverseImpFunc * InverseImpFunc::New()
{
    // Skip factory stuff - create class
    return new InverseImpFunc;
}

InverseImpFunc::InverseImpFunc(){


}




// Evaluate function
double InverseImpFunc::EvaluateFunction(double x[3])
{
	double f=0;
	
	f=Mainfunct->EvaluateFunction(x);
	f=-f;
	return f;
}

// Evaluate gradient for function
void InverseImpFunc::EvaluateGradient(double x[3], double n[3])
{
    double val=this->EvaluateFunction(x);
	double pos[3];
	double itsNormDelt[3];
	itsNormDelt[0]=itsNormDelt[1]=itsNormDelt[2]=0.00001;
	pos[0]=x[0];
	pos[1]=x[1];
	pos[2]=x[2];
	//XPoint
	x[0]+=itsNormDelt[0];
	n[0]=-((this->EvaluateFunction(x)-val)/itsNormDelt[0]);
	//YPoint
	x[1]+=itsNormDelt[1];
	x[0]=pos[0];
	n[1]=-((this->EvaluateFunction(x)-val)/itsNormDelt[1]);
	//ZPoint
	x[2]+=itsNormDelt[2];
	x[1]=pos[1];
	n[2]=-((this->EvaluateFunction(x)-val)/itsNormDelt[2]);
	//Normalize
	double length=sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
	if(length!=0.0) {
		n[0]/=length;
		n[1]/=length;
		n[2]/=length;
	}   
	


}

void InverseImpFunc::PrintSelf(ostream& os, vtkIndent indent)
{
    vtkImplicitFunction::PrintSelf(os,indent);
}
