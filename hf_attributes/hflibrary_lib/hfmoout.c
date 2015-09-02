/*==============================================================================

 Copyright 1998, 1999 Valery Adzhiev, Alexander Pasko, Ken Yoshikawa 
 Copyright 2003-2004 Benjamin Schmitt

 This Work or file is part of the greater total Work, software or group of
 files named HyperFun Polygonizer.

 HyperFun Polygonizer can be redistributed and/or modified under the terms 
 of the CGPL, The Common Good Public License as published by and at CGPL.org
 (http://CGPL.org).  It is released under version 1.0 Beta of the License
 until the 1.0 version is released after which either version 1.0 of the
 License, or (at your option) any later version can be applied.

 THIS WORK, OR SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED (See the
 CGPL, The Common Good Public License for more information.)

 You should have received a copy of the CGPL along with HyperFun Polygonizer;  
 if not, see -  http://CGPL.org to get a copy of the License.

==============================================================================*/


/*
Core HyperFun Library

Primitive: Molecular orbital


*/

#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <assert.h>


//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
//using namespace std;
static int atomsNumFinal=0;
//Mo calculation variables
static int MAX_GRID;// попробовать обойтись без
 // slater coefficients in Bohr
  double* CX ;
  double* CY ;
  double* CZ ;

  // d-orbital partial coefficients in Bohr
  double* DXY ;
  double* DXZ ;
  double* DYZ ;

  // exp(-alpha x^2...)
  double* EX ;
  double* EY ;
  double* EZ ;

//String calculationType;
 int* shells;
 double* expcoef;
 double* contraccoef;
double** gaussians;
  //Hashtable aoOrdersDF;

 double* moCoefficients;
 int moCoeff;
int gaussianPtr;
int firstAtomOffset;
 //bool isElectronDensity;
 float occupancy = 2; //for now -- RHF only
  
//  private float[] nuclearCharges;

  //protected float[][][] voxelDataTemp;
int NShell=0;
char*atomnames[20];
int AtomNum;
static int tekatomnum2=0;

static int findstr=0;
static char* AtomNames;
static double* AtomCordsX;
static double* AtomCordsY;
static double* AtomCordsZ;
static double* AtomCordsCharge;

static int atomnum=0;
static double* ArrayAtomBasCoefEx;
static double* ArrayAtomBasCoefCont1;
static double* ArrayAtomBasCoefCont2;
static int* ArrayAMoN;

static int* ArraynewAtoms;
static int totalcoef;
static int totalrows_coef=0;
static int* ArrayAtomBasNum;
static int* ArrayAtomBasPrim;
static char* ArrayAtomBasOrb;
static double** ArrayAtomMoCoef;
char line[80];
int pos44;
int pos31;
static int numcoef;
char * pch2;
static int totalll;
int pos2;
char c,cc,cc2,cc3,cc5,cc6;
	char * pch;
	int pos3;
	char * pch3;
		int nn=0;
		char * pch4;
		char * pch5;
		char * pch6;
		char * pch7;
	int pos;
	int lll;
	int l=0;
	static double * FuncSum;
	static double * FuncSum2;
static	int fsum=0;
	int tekatomnum=0;
	static double func=0;
#include "functions2.h";
//#include "filesheader.h"
void readMOFile(double xx, double yx, double zx)
{



//-----------------
//int funcint;
//int jjl;
	double R,xt,yt,zt,f;
//double* x;
int array_index, dim;
int NX;
double finalf=0;
int fll=0;
	int numrows;
	int q=0;
	int i=0;
	//int l=0;
	int dl=0;
int numrowcount;
	int dd=0;
//char* cc6;
//int ddd;
int ii;
double value;
int lln=0;
char * stops;
int st;
int  alfabeta;
int funcint, lll_n;



int flll,  jjll, lll_nl,funcint2;
int n=0;
fsum=0;
tekatomnum2=0;
   numcoef=0;
tekatomnum2=0;
tekatomnum=0;
fsum=0;
 l=0;
atomnum=0;
findstr=0;
 totalcoef=0;
totalrows_coef=0;
nn=0;


	AtomNames = (char*)malloc (20*sizeof(char));
	AtomCordsX = (double*)malloc (20*sizeof(double));
	AtomCordsY = (double*)malloc (20*sizeof(double));
	AtomCordsZ = (double*)malloc (20*sizeof(double));
	AtomCordsCharge = (double*)malloc (20*sizeof(double));

	c = fgetc(fin);//) != EOF
while(c!= EOF)
	{
	fgets(line, 80, fin) ;

  pch = strstr (line,"COORDINATES (BOHR)");

	readcordBor();
/*
	fprintf(fin2,"atoms number %d\n", atomnum);
	fprintf(fin2,"atoms number %d\n", tekatomnum);
	fprintf(fin2,"atoms number %d\n", this->tekatomnum2);
		fprintf(fin2,"atoms number %lf\n", this->AtomCordsX[0]);

	fclose (fin2);
	*/



pch3 = strstr (line,"ATOMIC BASIS SET");

	  if (pch3!= NULL)
	{	
		fgets(line, 80, fin) ;
stops=strstr(line,"TYPE PRIM");

		while (stops==NULL)
		{
		fgets(line, 80, fin) ;
		stops=strstr(line,"TYPE PRIM");

		}
		fgets(line, 80, fin) ;
		//fgets(line, 80, fin) ;
		//fgets(line, 80, fin) ;

		c = fgetc(fin);
		c = fgetc(fin);
		if (c==AtomNames[l])
		{
			l++;
			fgets(line, 80, fin) ;
			fgets(line, 80, fin) ;
			//определение приблизительного значения массивов
			pos2=ftell (fin);//запоминание позиции в файле
			pch4 = strstr (line,"TOTAL NUMBER OF SHELLS");
	
			FormArrays(pos2);


			//fscan
			fseek ( fin , pos2 , SEEK_SET );
			fgets(line, 80, fin) ;
			pch5 = strstr (line,"TOTAL NUMBER OF SHELLS");
		
			//while (nn<30)
			
			totalnumread(xx,yx,zx,pos2);

		}	

	 }


  pch6 = strstr (line,"MOLECULAR ORBITALS");

 alfabeta=1;
	if (pch6!= NULL)
	{
		pos3=ftell(fin);
//fgets(line, 80, fin) ;
//	fgets(line, 80, fin) ;
//	fgets(line, 80, fin) ;
		
		for (n=0;n<5;n++)
		{
			fgets(line, 80, fin) ;
	pch6 = strstr (line," ALPHA SET ");

			 if (pch6!= NULL) alfabeta=2;
			 
		}
	{
	
		fseek ( fin , pos3 , SEEK_SET );	
	fgets(line, 80, fin) ;
	lll=0;
		st=0;

	for (q=0;q<alfabeta;q++)//reading alfa + beta
	{
		if (alfabeta==2)
		{
	fgets(line, 80, fin) ;
		printf("///%s--------------  \n",line);

	fgets(line, 80, fin) ;
		printf("///%s--------------  \n",line);
		

if (st==0)
	fgets(line, 80, fin) ;
	printf("///%s--------------  \n",line);



	numrowcount=0;
	pos3=ftell(fin);
	
	fgets(line, 80, fin) ;
		}
		else pos3=ftell(fin);
	st=0;
		printf("///%s finalstr \n",line);
	//	if (alfabeta==1) line[0]='q';
	while ((line[0]!=0x0A)||(strstr(line,"----------------")))
	{
		fseek ( fin , pos3 , SEEK_SET );	
fscanf (fin, "%d", &numrows);
printf("///------------------------------- %d  \n", numrows);

pos3=ftell(fin);
fgets(line, 80, fin) ;
printf("///---- %s  \n", line);

	}
	printf("///-------------------------------  \n");

	
	while ((numrows-numrowcount*5==5)&&(st==0))//пока без последнего
	{
		
coefreader (numrows,numrowcount);

fgets(line, 80, fin) ;//пропуск линии
printf("///-------------------------------  \n");
pos3=ftell(fin);
	fgets(line, 80, fin) ;
	while ((line[0]!=0x0A)&&(st==0))
	{
		fseek ( fin , pos3 , SEEK_SET );	
fscanf (fin, "%d", &numrows);
printf("///- %d  \n", numrows);

pos3=ftell(fin);
pos31=ftell(fin);
fgets(line, 80, fin) ;
if(strstr(line,"BETA SET")!= NULL) 
{
	st=1;
printf("///Betasetfound---  \n");
}

	}
	/*
	pos3=ftell(fin);
	fgets(line, 80, fin) ;
	if((line[0]==0x0A)||(strstr(line,"BETA SET"))) st=1;
			fseek ( fin , pos3 , SEEK_SET );	
*/
numrowcount++;

	}//while
	//	printf("----------------------- ");
	
	fgets(line, 80, fin) ;
	if((line[0]==0x0A)||(strstr(line,"BETA SET"))||(st==1) )
	{
	printf("///Going to next set--------------  \n");
	fseek ( fin , pos3 , SEEK_SET );
//	fgets(line, 80, fin) ;
	//pos3=pos31;
	}

	else
	{
			fseek ( fin , pos31 , SEEK_SET );	
	coefreader (numrows,numrowcount);// обработка последнего столбца
	}
		

	}
fgets(line, 80, fin) ;
fgets(line, 80, fin) ;

fgets(line, 80, fin) ;

	}
	}
	c = fgetc(fin);
	}

fclose(fin);
/*
FILE* fin2;
*/

for ( flll=0; flll<numcoef;flll++)
		{
			FuncSum[flll]=0;
			FuncSum2[flll]=0;
		}
	
		fsum=0;
		tekatomnum2=0;
		jjll=0;


}





double MOORBITAL(double* f_a, String_Array_T* str_param)
{ 


	
  

//-----------------
//int funcint;
//int jjl;
	double* center;

	double x,y,z;
double R,xt,yt,zt,f;
//double* x;
int array_index, dim;
int NX;
int numrows;
int numrowcount;
//char* cc6;
//int ddd;

int ii,j;
double value;




//-----------------------
int flll,  jjll, lll_nl,funcint2;

long num;
	int dd=0;

int fll=0;
	double finalf=0;

	int q=0;
	int i=0;
	//int l=0;
	int dl=0;

double ffinal=0;
double ffres=0;
int lln=0;
finalf=0;
fsum=0;
tekatomnum2=0;
tekatomnum2=0;
tekatomnum=0;
fsum=0;
 l=0;
atomnum=0;
findstr=0;
totalrows_coef=0;
nn=0;

fsum=0;
tekatomnum2=0;
array_index = (int)f_a[1];
HF_Get_Runtime_Array(array_index, &center, &dim);

x=center[0];
y=center[1];
z=center[2];

if(readflag == 0)
{
	
	readMOFile(x,y,z);
}




for ( flll=0; flll<numcoef;flll++)
		{
			FuncSum[flll]=0;
			FuncSum2[flll]=0;
		}
	
		fsum=0;
		tekatomnum2=0;
		jjll=0;

for (jjll=0;jjll<totalll;jjll++)
{
	calcfunction(x,y,z,jjll);
}

lll_nl=0;
  value = 0;
 //printf("%d\n",totalcoef);
  //printf("%d\n",numcoef);

//totalcoef=10;
for (lll_nl=0; lll_nl<totalcoef;lll_nl++) //26 
{

	for (funcint2=0; funcint2<numcoef;funcint2++) //58
{

FuncSum[funcint2]=FuncSum[funcint2]*ArrayAtomMoCoef[lll_nl][funcint2];
//printf("%lf \n", ArrayAtomMoCoef[lll_nl][funcint2]);
	}



for (funcint2=0; funcint2<numcoef;funcint2++)
{
	ffinal= FuncSum[funcint2]+ffinal;
	
	//printf("function = %lf \n",FuncSum[funcint2]);
}

FuncSum2[lll_nl]=ffinal;
ffinal=0;
}


//printf("%d\n",totalcoef);
 for(ii=0; ii<totalcoef; ii++){
    value =value + FuncSum2[ii] * FuncSum2[ii];
	
   // for(j=0; j<i; j++)
   //   value += FuncSum2[i] * FuncSum2[j] * 2.0;
 }



//if (ffinal>=0)

//return ffinal-0.1;
//else
return value;


}



double EDA_ED(double* f_a, String_Array_T* str_param){
double f;
double a;
double b;
double *center;
double x,y,z,dx,dy,dz, tmin, tmax;
double R;
int array_index, dim;
int i,j, cont;


double epot,value,tdel;
array_index = (int)f_a[1];
HF_Get_Runtime_Array(array_index, &center, &dim);

x=center[0];
y=center[1];
z=center[2];
i=0;
epot=0;
tmin=0;
tmax=0;
/*
while (i<atomsNumFinal)
{
	dx=-2-AtomCordsX[i];
	dy=-2-AtomCordsY[i];
	dz=-2-AtomCordsZ[i];

	R= dx*dx+dy*dy+dz*dz;

tmin=tmin+(AtomCordsCharge[i])/(4*3,14*8,854187*R);
	i++;
}

i=0;

while (i<atomsNumFinal)
{
	dx=2-AtomCordsX[i];
	dy=2-AtomCordsY[i];
	dz=2-AtomCordsZ[i];

	R= dx*dx+dy*dy+dz*dz;

tmax=tmax+(AtomCordsCharge[i])/(4*3,14*8,854187*R);
	i++;
}
*/
i=0;
epot=0;
//atomsNumFinal=atomsNumFinal+1;
i=0;
while (i<=atomsNumFinal)
{
	dx=x-AtomCordsX[i];
	dy=y-AtomCordsY[i];
	dz=z-AtomCordsZ[i];

	R= dx*dx+dy*dy+dz*dz;
	R=sqrt(R);

epot=epot+((AtomCordsCharge[i])/(R*10));//(4*3,14*8,854187*R);
	
	//printf ("%lf+%d\n", epot,i);
	//printf ("%lf\n", AtomCordsCharge[1]);
	//printf("%d\n",i);
	i++;
}
//printf ("%lf\n", epot);


//printf("%d\n",atomsNumFinal+1);
//value=0;
//tdel=(tmax-tmin)/7;

return epot;

}


double hfA_EDensity(double* f_a, String_Array_T* str_param)
{
	return 0;
}

