#if !defined(SoundIMPLFUNC_H)
#define SoundIMPLFUNC_H
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

class SoundImpFunc : public vtkImplicitFunction {
public:
    vtkTypeMacro(SoundImpFunc,vtkImplicitFunction);
    void PrintSelf(ostream& os, vtkIndent indent);

    // Description
    // Create a new function
    static SoundImpFunc * New(void);

    // Description
    // Evaluate function
    double EvaluateFunction(double x[3]);
    double EvaluateFunction(double x, double y, double z) {
	return this->vtkImplicitFunction::EvaluateFunction(x, y, z);
    }
    double* EvaluateAtr(double x[3]);

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
  SoundImpFunc();
    
    ~SoundImpFunc() {}
    SoundImpFunc(const SoundImpFunc&) {}
    void operator=(const SoundImpFunc&) {}

    // Add parameters/members here if you need
};




#endif //

