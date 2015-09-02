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
** HyperFun Library
** ReadScalars function
*/


#include "general.h"
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <string.h>
#include "files.h"
#include "f2c.h"
#include "blaswrap.h"
#include "clapack.h"
#include <math.h>


extern int HF_Get_Runtime_Array(int index, double **array, int *size);
extern void HF_Fill_Error(PN_T *p_pn, int er_index, Error_Info_T *EI, int ic);

/* Auxiliary routines prototypes */
//extern void print_matrix( char* desc, int m, int n, double* a, int lda );



//Additional Lapack conversion functions from 
//http://www-heller.harvard.edu/people/shaw/programs/dgesvd.h


#define Zero 0.00000
#define Minus -10.00000

void dgesvd_ftoc(double *in, double **out, int rows, int cols)
{
  int i, j;

  for (i=0; i<rows; i++) for (j=0; j<cols; j++) out[i][j] = in[i+j*rows];
}

double* dgesvd_ctof(double **in, int rows, int cols)
{
  double *out;
  int i, j;

  out = (double*)malloc(rows*cols*sizeof(double));
	  //new double[rows*cols];
  for (i=0; i<rows; i++) for (j=0; j<cols; j++) out[i+j*rows] = in[i][j];
  return(out);
}

void dgesvd(double **A, int m, int n, double *S, double **U, double **VT)
{
  char jobu, jobvt;
  int lda, ldu, ldvt, lwork, info;
  double *a, *u, *vt, *work;

  int minmn, maxmn;

  jobu = 'A'; /* Specifies options for computing U.
		 A: all M columns of U are returned in array U;
		 S: the first min(m,n) columns of U (the left
		    singular vectors) are returned in the array U;
		 O: the first min(m,n) columns of U (the left
		    singular vectors) are overwritten on the array A;
		 N: no columns of U (no left singular vectors) are
		    computed. */

  jobvt = 'A'; /* Specifies options for computing VT.
		  A: all N rows of V**T are returned in the array
		     VT;
		  S: the first min(m,n) rows of V**T (the right
		     singular vectors) are returned in the array VT;
		  O: the first min(m,n) rows of V**T (the right
		     singular vectors) are overwritten on the array A;
		  N: no rows of V**T (no right singular vectors) are
		     computed. */

  lda = m; // The leading dimension of the matrix a.
  a = dgesvd_ctof(A, lda, n); /* Convert the matrix A from double pointer
			  C form to single pointer Fortran form. */

  ldu = m;

  /* Since A is not a square matrix, we have to make some decisions
     based on which dimension is shorter. */

  if (m>=n) { minmn = n; maxmn = m; } else { minmn = m; maxmn = n; }

  ldu = m; // Left singular vector matrix
  u = (double*)malloc(ldu*minmn*sizeof(double));
	  //new double[ldu*minmn];

  ldvt = minmn; // Right singular vector matrix
  vt = (double*)malloc(ldvt*n*sizeof(double));
	  //new double[ldvt*n];

  lwork = 5*maxmn; // Set up the work array, larger than needed.
  work = (double*)malloc(lwork*sizeof(double));
	  //new double[lwork];

  dgesvd_(&jobu, &jobvt, &m, &n, a, &lda, S, u,
	  &ldu, vt, &ldvt, work, &lwork, &info);

  dgesvd_ftoc(u, U, ldu, minmn);
  dgesvd_ftoc(vt, VT, ldvt, n);
  
  free(a);
  free(u);
  free(vt);
  free(work);
}




//---------------------
//RBF Function evaluation
//----------------------
void RBFReadScalarFile( int f_a, String_Array_T *str_param, int indFile, int addition)
{
	
	double fmain;
	int numP; //number of points
	FILE* fin;

  int i, j;
  double addMin=0.8;
  double Xmin,Xmax, Ymin,Ymax,Zmin,Zmax,x0,y0,z0;

  




 if (!(fin=fopen(HF_Get_By_Index(str_param, f_a),"r")))
 {
  printf("Cannot open data file \n");
  ////exit(-1);
 }
  else printf("File %s was really opened \n",HF_Get_By_Index(str_param, f_a) );


fscanf (fin, "%d", &numP);


  grData[indFile] = (GRIDData*)malloc((numP+addition)*sizeof(GRIDData)); //+central point
//points of bounding box
for(i=0;i<numP;i++)
	{		
		 if (!feof(fin)) {
			fscanf (fin, "%lf", &fmain);
				
				grData[indFile][i].x=fmain;
				fscanf (fin, "%lf", &fmain);
				grData[indFile][i].y=fmain;
				fscanf (fin, "%lf", &fmain);
				grData[indFile][i].z=fmain;

				grData[indFile][i].fval=0.0;

			
		}
				 else {
					 printf("File end was found earlier then it should be\n" );

				 }

		
	}

fclose(fin);
 printf("File sucessfully read\n" );

 //bounding box calculation
	Xmin= grData[indFile][0].x;
		Ymin= grData[indFile][0].y;
		Zmin= grData[indFile][0].z;
		 Xmax= grData[indFile][0].x;
		Ymax= grData[indFile][0].y;
		Zmax= grData[indFile][0].z;
	if (addition>0)
		{
	for(i=0; i < numP; i++) {
      

		if( Xmin> grData[indFile][i].x) Xmin= grData[indFile][i].x;
		if( Ymin>  grData[indFile][i].y) Ymin= grData[indFile][i].y;
		if( Zmin>  grData[indFile][i].z) Zmin= grData[indFile][i].z;

		if( Xmax< grData[indFile][i].x) Xmax= grData[indFile][i].x;
		if( Ymax<  grData[indFile][i].y) Ymax= grData[indFile][i].y;
		if( Zmax<  grData[indFile][i].z) Zmax= grData[indFile][i].z;
	}
	
	x0= Xmin+( Xmax- Xmin)/2;
	y0= Ymin+( Ymax- Ymin)/2;
	z0= Zmin+( Zmax- Zmin)/2;
		
	
grData[indFile][numP].x=x0;
grData[indFile][numP].y=y0;
grData[indFile][numP].z=z0;
}

		if(addition>1) //boounding box points
		{

Xmin-=addMin;
Ymin-=addMin;
Zmin-=addMin;

Xmax+=addMin;
Ymax+=addMin;
Zmax+=addMin;

grData[indFile][numP+8].x=Xmin;
grData[indFile][numP+8].y=Ymin;
grData[indFile][numP+8].z=Zmin;

grData[indFile][numP+1].x=Xmin;
grData[indFile][numP+1].y=Ymax;
grData[indFile][numP+1].z=Zmin;

grData[indFile][numP+2].x=Xmin;
grData[indFile][numP+2].y=Ymin;
grData[indFile][numP+2].z=Zmax;

grData[indFile][numP+3].x=Xmin;
grData[indFile][numP+3].y=Ymax;
grData[indFile][numP+3].z=Zmax;

grData[indFile][numP+4].x=Xmax;
grData[indFile][numP+4].y=Ymax;
grData[indFile][numP+4].z=Zmax;

grData[indFile][numP+5].x=Xmax;
grData[indFile][numP+5].y=Ymax;
grData[indFile][numP+5].z=Zmin;

grData[indFile][numP+6].x=Xmax;
grData[indFile][numP+6].y=Ymin;
grData[indFile][numP+6].z=Zmin;

grData[indFile][numP+7].x=Xmax;
grData[indFile][numP+7].y=Ymin;
grData[indFile][numP+7].z=Zmax;
		}
		numP=numP+addition; //center point, bounding box points

printf("All points added\n" );
//number of points stored
dx[indFile]=numP;
printf("dx[indFile]=%d\n" ,dx[indFile]);
}


//------------------------------------
// Fill A matrix and calculate S,U,VT
//------------------------------------

void RBFFillScalarFile(double *S, double **U,double  **VT, int indFile)
{
	double **A;
double xx,y,z,distance;
int numP=dx[indFile];
int n=numP+4;

int i,j;

A = (double**)malloc(n*sizeof(double*));
	  //new double*[m];
  for ( i=0; i<n; i++) A[i] = (double*)malloc(n*sizeof(double));
  // Allocate the storage space for the output arrays and call the solver

    for(i=0; i < numP; i++) {
      for(j=0; j < numP; j++) {

		 xx= grData[indFile][i].x-grData[indFile][j].x;
		 y= grData[indFile][i].y-grData[indFile][j].y;
		 z= grData[indFile][i].z-grData[indFile][j].z;
               //vD = vert[i] - vert[j];
            
        distance = sqrt(xx*xx+y*y+z*z);
		A[i][j] = distance;



      }
	 A[numP][i]= 1.0;
	  A[i][numP]= 1.0;
		//A(rusultPNumber+1,i+1) = 1.0;
		//A(i+1,rusultPNumber+1) = 1.0;

	   A[numP+1][i]= grData[indFile][i].x;
	  A[i][numP+1]= grData[indFile][i].x;

	   A[numP+2][i]= grData[indFile][i].y;
	  A[i][numP+2]= grData[indFile][i].y;

	   A[i][numP+3]= grData[indFile][i].z;
	  A[numP+3][i]= grData[indFile][i].z;


   }

	
  dgesvd(A, n, n, S, U, VT);



	readfiles[indFile]=0;
	free(A);
	
	// Output the results
	/*
printf("\n");
  for ( i=0; i<minmn; i++) printf("%lf ",S[i]);
printf("\n");*/
	}


//----------------------
//Calculate coefficients
//-----------------------
void EvalFunction(double *S, double **U, double **VT, int indFile, int addition )
{
	
double *H;
double * Xx;
int i,j;
int numP=dx[indFile];
int numIn=dx[indFile]-addition;
	int n=numP+4;
	printf("n=%d\n" ,n);
 H = (double*)malloc(n*sizeof(double)); 
 Xx = (double*)malloc(n*sizeof(double));
 Xx2[indFile] = (double*)malloc(n*sizeof(double));

	if(addition>0)
H[numIn]=10.0;
	if(addition>1)
	{
		for ( i=1;i<9;i++)
		H[numIn+i]=-1.2;
		
	}
//printf("H array\n" );
//for ( i=0; i<n; i++) printf("%lf ",H[i]);
//printf("Xx array\n" );

   for (i=0;i<n;i++)
   {
      for ( j=0;j<n;j++)
      {

         Xx[i]=U[j][i]*H[j]+Xx[i] ;

      }

   }
//for ( i=0; i<n; i++) printf("%lf ",Xx[i]);
printf("Xx array2\n" );
   for( i=0; i < n; i++)       Xx[i]=S[i]*Xx[i];
for ( i=0; i<n; i++) printf("%lf ",Xx[i]);




   for(i=0; i < n; i++) {
      for( j=0; j < n; j++) {

         Xx2[indFile][i]=VT[j][i]*Xx[j]+Xx2[indFile][i];
      }

	// printf("Function coeff filled\n" );
   }

/*
printf("\n");
  for ( i=0; i<n; i++) printf("%lf ",Xx2[indFile][i]);
printf("\n");
*/
 free(H);
 free(Xx);
}


double
RBFSCALARS(double *f_a, String_Array_T *str_param)
{
  double *x, *center;
  int arrayIndex, dim;
 
  double  distanceSquared,xt,yt,zt,f;
 double *S, **U, **VT;

int indFile;
int i;
int NumP;
int  n;


	indFile=(int) f_a[2];
	indFile=indFile-1;
  arrayIndex = (int) f_a[1];
  HF_Get_Runtime_Array(arrayIndex, &x, &dim); 

 
f=0;

if(readfiles[indFile])
{


   
int addition=9;
	RBFReadScalarFile((int)f_a[0], str_param,indFile,addition);
	
	 n=dx[indFile]+4;
	 printf("n=%d\n" ,n);
 
  S = (double*)malloc(n*sizeof(double));
  U = (double**)malloc(n*sizeof(double*)); 
    for ( i=0; i<n; i++) U[i] = (double*)malloc(n*sizeof(double));
  
  VT = (double**)malloc(n*sizeof(double*)); 
    for ( i=0; i<n; i++) VT[i] = (double*)malloc(n*sizeof(double));
	
	RBFFillScalarFile(S, U, VT, indFile);

	 
	EvalFunction(S, U, VT,indFile,addition );
	 free(S);
	  free(VT);
	  free(U);
for ( i=0; i<n; i++) printf("%lf ",Xx2[i]);
printf("%d ,%d \n",dx[indFile],n);
}   // RBF part

f=0;
 NumP=dx[indFile];     
 for (i = 0; i <NumP; i++)
      {
         

xt=x[0]-grData[indFile][i].x;
yt=x[1]-grData[indFile][i].y;
zt=x[2]-grData[indFile][i].z;
        

        distanceSquared = sqrt(xt*xt+yt*yt+zt*zt);

		 // distanceSquared = distanceSquared * distanceSquared * distanceSquared ;
         f =f+ Xx2[indFile][i] * distanceSquared;//fabs(vD.x);//distanceSquared;//distanceSquared*distanceSquared;//T(rbfFunction(distanceSquared));
        
      }


      //affine part
      
         f =f+  Xx2[indFile][NumP]+Xx2[indFile][NumP+1]*x[0]+Xx2[indFile][NumP+2]*x[1]+Xx2[indFile][NumP+3]*x[2];
  
  	


	return f;
}




//---------------------
//RBF DeformFunction evaluation
//----------------------

