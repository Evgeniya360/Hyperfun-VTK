// -*- Mode: c++; c-indentation-style: stroustrup; c-basic-offset: 4 -*-

#include <vtkImplicitFunction.h>
#include "implfunc.h"

//------------------------------------------------------------------------------
ImpFunc * ImpFunc::New()
{
    // Skip factory stuff - create class
    return new ImpFunc;
}

ImpFunc::ImpFunc(){

itsSendingX.resize(3);
}




// Evaluate function
double ImpFunc::EvaluateFunction(double x[3])
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

double* ImpFunc::EvaluateAtr(double x[3])
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

double ImpFunc::EvaluateAtr3(double x[3],int n)
{
	double f=0;
	double* s;
	
	itsSendingX[0]=x[0];
	itsSendingX[1]=x[1];
	itsSendingX[2]=x[2];

for(int p=0;p<itsSSize;p++) itsSAttributesM[p]=0.0;
f=itsInterpreter->calc(itsSendingX,s);
	//printf("%lf\n",f);
//f=-1;



	return s[n];
}

// Evaluate gradient for function
void ImpFunc::EvaluateGradient(double x[3], double n[3])
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

void ImpFunc::PrintSelf(ostream& os, vtkIndent indent)
{
    vtkImplicitFunction::PrintSelf(os,indent);
}
