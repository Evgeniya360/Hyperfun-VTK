// -*- Mode: c++; c-indentation-style: stroustrup; c-basic-offset: 4 -*-

#include <vtkImplicitFunction.h>
#include "soundimplfunc.h"

//------------------------------------------------------------------------------
SoundImpFunc * SoundImpFunc::New()
{
    // Skip factory stuff - create class
    return new SoundImpFunc;
}

SoundImpFunc::SoundImpFunc(){

itsSendingX.resize(3);
}




// Evaluate function
double SoundImpFunc::EvaluateFunction(double x[3])
{
	double f=0;
	
	itsSendingX[0]=x[0];
	itsSendingX[1]=x[1];
	itsSendingX[2]=x[2];

for(int p=0;p<itsSSize;p++) itsSAttributesM[p]=0.0;
f=itsInterpreter->calc(itsSendingX,itsSAttributesM);

std::vector<double> vs(itsSSize,0.0);
	fillVector(itsSAttributesM, itsSSize, vs);
	itsSAttributes.push_back(vs);
	return f;
}

double* SoundImpFunc::EvaluateAtr(double x[3])
{
	double f=0;
	
	itsSendingX[0]=x[0];
	itsSendingX[1]=x[1];
	itsSendingX[2]=x[2];

for(int p=0;p<itsSSize;p++) itsSAttributesM[p]=0.0;
f=itsInterpreter->calc(itsSendingX,itsSAttributesM);
	//printf("%lf\n",f);
//f=-1;



	return itsSAttributesM;
}

// Evaluate gradient for function
void SoundImpFunc::EvaluateGradient(double x[3], double n[3])
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

void SoundImpFunc::PrintSelf(ostream& os, vtkIndent indent)
{
    vtkImplicitFunction::PrintSelf(os,indent);
}
