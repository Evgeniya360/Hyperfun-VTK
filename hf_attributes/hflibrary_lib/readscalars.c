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

extern int HF_Get_Runtime_Array(int index, double **array, int *size);
extern void HF_Fill_Error(PN_T *p_pn, int er_index, Error_Info_T *EI, int ic);

void ReadScalarFile(int f_a, String_Array_T *str_param, int indFile)
{
	
	double fmain;
	FILE* fin;
float ftr;


int j=0;
int i=0;
int k=0;


 if (!(fin=fopen(HF_Get_By_Index(str_param, f_a),"r")))
 {
  printf("Cannot open data file \n");
  ////exit(-1);
 }
  else printf("File %s was really opened \n",HF_Get_By_Index(str_param, f_a) );
//fin = fopen("file31.dat", "r");
	

//Grid[i]=new GRID**[dx];
fscanf (fin, "%d", &dx[indFile]);
fscanf (fin, "%d", &dy[indFile]);
fscanf (fin, "%d", &dz[indFile]);

fscanf (fin, "%lf", &stepx[indFile]);
fscanf (fin, "%lf", &stepy[indFile]);
fscanf (fin, "%lf", &stepz[indFile]);

fscanf (fin, "%lf", &originx[indFile]);
fscanf (fin, "%lf", &originy[indFile]);
fscanf (fin, "%lf", &originz[indFile]);



  grData[indFile] = (GRIDData*)malloc(dx[indFile]*dy[indFile]*dz[indFile]*sizeof(GRIDData));

	for(i=0;i<dx[indFile];i++)
	{		
		//Grid[i]=new GRID*[dy];
		for(j=0;j<dy[indFile];j++)
		{
		//	Grid[i][j]=new GRID[dz];
			for(k=0;k<dz[indFile];k++)
			{
				
				grData[indFile][i*dz[indFile]*dy[indFile]+j*dz[indFile]+k].x=originx[indFile]+i*stepx[indFile];
				grData[indFile][i*dz[indFile]*dy[indFile]+j*dz[indFile]+k].y=originy[indFile]+j*stepy[indFile];
				grData[indFile][i*dz[indFile]*dy[indFile]+j*dz[indFile]+k].z=originz[indFile]+k*stepz[indFile];

				 if (!feof(fin)) {
			fscanf (fin, "%lf", &fmain);
			fmain=fmain;
			grData[indFile][i*dz[indFile]*dy[indFile]+j*dz[indFile]+k].fval=fmain;
		}
				 else {
					 printf("File end was found earlier then it should be\n" );

				 }

			
			}
		}
	}

fclose(fin);

}


double
READSCALARS(double *f_a, String_Array_T *str_param)
{
  double xt, yt, zt;
  double *x, *center, S;
  int arrayIndex, dim;
  double f;
  int vv;
int ftrx,ftry,ftrz;
double fmain,f1,f2,f3,f4,x1,x2,x3;
	double xd,yd,zd,i1,i2,i3,j1,j2,w1,w2;


int i=0;
int indFile;

f=0;

	indFile=(int) f_a[2];
	indFile=indFile-1;
  arrayIndex = (int) f_a[1];
  HF_Get_Runtime_Array(arrayIndex, &x, &dim); 

 

if(readfiles[indFile])
{
	ReadScalarFile((int)f_a[0], str_param,indFile);
	readfiles[indFile]=0;
	printf("dx,dy=%d,%d,%d\n",dx[indFile],dy[indFile],dz[indFile]);
	printf("origin=%lf,%lf,%lf\n",originx[indFile],originy[indFile],originz[indFile]);
	printf("step=%lf,%lf,%lf\n",stepx[indFile],stepy[indFile],stepz[indFile]);
	//for(i=(dx*dz); i<(dy*dz+dx);i++)
	vv=(dy[indFile]*dz[indFile]*dx[indFile])-1;
	printf("grid=%lf,%lf,%lf,%lf\n",grData[indFile][vv].x,grData[indFile][vv].y,grData[indFile][vv].z,grData[indFile][vv].fval);

	vv=0;
	printf("grid0=%lf,%lf,%lf,%lf\n",grData[indFile][vv].x,grData[indFile][vv].y,grData[indFile][vv].z,grData[indFile][vv].fval);

		

}

ftrx=-10;
ftry=-10;
ftrz=-10;
i=0;
while ((ftrx<0)&&(i<dx[indFile]))
	{
		
if (fabs(x[0]-(originx[indFile]+i*stepx[indFile]))<stepx[indFile])
{
ftrx=i;
}
else i++;
		
	}
/*
while (ftrx==-1)
	{
if (x[0]-i<1) ftrx=i;
else i++;
	}
	*/
 i=0;

while ((ftry<0)&&(i<dy[indFile]))
	{
		
if (fabs(x[1]-(originy[indFile]+i*stepy[indFile]))<stepy[indFile])
{
ftry=i;
}
else i++;
		
	}
i=0;
while ((ftrz<0)&&(i<dz[indFile]))
	{
		
if (fabs(x[2]-(originz[indFile]+i*stepz[indFile]))<stepz[indFile])
{
ftrz=i;
}
else i++;
		
	}

if(ftrz<0)
return -10.0;
if(ftrx<0)
return -10.0;
if(ftry<0)
return -10.0;
 if (ftrx>=dx[indFile])
return -10.0;
 if (ftry>=dy[indFile])
return -10.0;
 if (ftrz>=dz[indFile])
return -10.0;

if ((ftrz<0)||(ftrx<0)||(ftry<0)||(ftrx+1>=dx[indFile])||(ftry+1>=dy[indFile])||(ftrz+1>=dz[indFile]))
f=-10.0f;

else
{
xd=(x[0]-grData[indFile][ftrx*dz[indFile]*dy[indFile]+ftry*dz[indFile]+ftrz].x)/stepx[indFile];
yd=(x[1]-grData[indFile][ftrx*dz[indFile]*dy[indFile]+ftry*dz[indFile]+ftrz].y)/stepy[indFile];
zd=(x[2]-grData[indFile][ftrx*dz[indFile]*dy[indFile]+ftry*dz[indFile]+ftrz].z)/stepz[indFile];

i1=(grData[indFile][ftrx*dz[indFile]*dy[indFile]+ftry*dz[indFile]+ftrz].fval)*(1-xd)+xd*(grData[indFile][(ftrx+1)*dz[indFile]*dy[indFile]+ftry*dz[indFile]+ftrz].fval);
i2=(grData[indFile][ftrx*dz[indFile]*dy[indFile]+ftry*dz[indFile]+ftrz+1].fval)*(1-xd)+xd*grData[indFile][(ftrx+1)*dz[indFile]*dy[indFile]+ftry*dz[indFile]+ftrz+1].fval;
j1=(grData[indFile][ftrx*dz[indFile]*dy[indFile]+(ftry+1)*dz[indFile]+ftrz].fval)*(1-xd)+xd*grData[indFile][(ftrx+1)*dz[indFile]*dy[indFile]+(ftry+1)*dz[indFile]+ftrz].fval;
//error in line
j2=(grData[indFile][ftrx*dz[indFile]*dy[indFile]+(ftry+1)*dz[indFile]+ftrz+1].fval)*(1-xd)+xd*grData[indFile][(ftrx+1)*dz[indFile]*dy[indFile]+(ftry+1)*dz[indFile]+ftrz+1].fval;
/*
j2=(Grid[ftrx+1][ftry+1][ftrz+1] )*(1-xd)+xd*Grid[ftrx+1][ftry+1][ftrz+1] ;
*/
w1=i1*(1-yd)+j1*yd;
w2=i2*(1-yd)+j2*yd;

f=w1*(1-zd)+w2*zd;
//printf("%lf,found\n",f);
}

//ѕересечение с обрамл€ющим параллелепипедом
/*f1=(x[0]+f-sqrt(f*f+x[0]*x[0]-2*f*x[0]))/2;
f2=(x[1]+f1-sqrt(f1*f1+x[1]*x[1]-2*f1*x[1]))/2;
f3=(x[2]+f2-sqrt(f2*f2+x[2]*x[2]-2*f2*x[2]))/2;
x1=31-x[0];
x2=31-x[1];
x3=31-x[2];
f1=f3;
f2=x1+f1-sqrt(f1*f1+x1*x1-2*f1*x1);
f3=x2+f2-sqrt(f2*f2+x2*x2-2*f2*x2);
f4=x3+f3-sqrt(f3*f3+x3*x3-2*f3*x3);

*/

//f=0.16-f;

	return f;
}


