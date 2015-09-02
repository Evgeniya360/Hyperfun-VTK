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

Primitive: sphere (ball)

Definition: R^2-(x-x0)^2-(y-y0)^2-(z-z0)^2

Call: hfSphere(x,center,R);

Parameters:
 x - point coordinates array
 center - sphere center array
 R - sphere radius

Test file: sphere.hpf

C-parameters:
        f_a[0]   corresponds to R
        f_a[1]   corresponds to array center
        f_a[2]   corresponds to array x o

Code by: Pasko, Adzhiev
Last revised: 4.8.98
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
#include "filesheader.h"
//using namespace std;

extern int HF_Get_Runtime_Array(int index, double** array, int* size);
void HF_Fill_Error(PN_T* p_pn, int er_index, Error_Info_T* EI, int ic);

extern double EPS;

static int todoflag = 0;
static int Filedatanum = 0;
//static std::vector<double> FileData;
static double* FileData;
static int firstopened=0;
 unsigned char volumeData[1][1][1];
 unsigned char Rad;
double STR_T(double* f_a, String_Array_T* str_param)
{
	
double R,xt,yt,zt,f;
double* x;
double* center;
int array_index, dim;
int NX;
long num;
//if(readflag == 0){
/*------------------------------------------------------------------*/
 if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"r")))
 {
  printf("Cannot open data file \n");
  ////exit(-1);
 }
  else printf("File %s was opened \n",HF_Get_By_Index(str_param, (int)f_a[0]) );

fseek ( fin , 2 , SEEK_SET );

      fscanf(fin, "%lf", &R);
  //num=fread(volumeData,sizeof(  unsigned char),10,fin);
 // num=fread(Rad,sizeof( unsigned char),1,fin);
 fclose(fin);
 printf("Rad = %lf read \n",R);
 printf("Data file read \n");

 readflag = 1;
/*------------------------------------------------------------------*/
//}
/*

   if(!strcmp(HF_Get_By_Index(str_param, (int)f_a[0]), "Hey stub!"))
     R=10;
   else R=3;
   */
//R=(double)volumeData[0][0][0];
	array_index = (int)f_a[1];
HF_Get_Runtime_Array(array_index, &center, &dim);

array_index = (int)f_a[2];
HF_Get_Runtime_Array(array_index, &x, &dim);

if (dim != 3) return -1111111111111.0;

xt=x[0]-center[0];
yt=x[1]-center[1];
zt=x[2]-center[2];
//f = R*R - xt*xt - yt*yt -zt*zt;

return R;
}







double OPENFILE(double* f_a, String_Array_T* str_param)
{
	
int opened;
opened=-11;
todoflag=0;
// определение режима считывания из файла


// открытие файла
if(readflag == 0){

	if(!strcmp(HF_Get_By_Index(str_param, (int)f_a[1]), "r"))
  
{
	todoflag=0;
	printf("Reading file \n");
}
	else
	{
if(!strcmp(HF_Get_By_Index(str_param, (int)f_a[1]), "rb"))
{
  todoflag=1;
  printf("Reading binary file \n");
}
else
{
if(!strcmp(HF_Get_By_Index(str_param, (int)f_a[1]), "w"))
{
  todoflag=2;
  	printf("Writing file \n");
}
else
{
if(!strcmp(HF_Get_By_Index(str_param, (int)f_a[1]), "wb"))
{
  todoflag=3;
  	printf("Writing binary file \n");
}else
{
	return -11;
}
}

}
	}
/*------------------------------------------------------------------*/
			switch(todoflag){
						case 0 : {

			 if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"r")))
			 {
			  printf("Cannot open data file \n");
			 opened=-11;
			 }
			  else 
			  {
			  printf("Ready for reading file %s\n",HF_Get_By_Index(str_param, (int)f_a[0]));
			//  fclose(fin);
			 // fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"r");
			  opened=11;
			 }
			}
								 break;

						case 1 : {

				 if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"rb")))
				 {
				  printf("Cannot open data file \n");
				  opened=-11;
				 }
				  else
				  {  printf("Ready for binary reading file \n");
					  opened=11;
				 }
				}

								 break;

						case 2 : {

				 if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"w")))
				 {
				  printf("Cannot open data file \n");
				  opened=-11;
				 }
				  else 
				  {  printf("Ready for writing file \n");
					  opened=11;
				 }
				}


								 break;
						case 3 : {

				 if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"wb")))
				 {
				  printf("Cannot open data file \n");
				  opened=-11;
				 }
				  else 
				  {  printf("Ready for writting binary file \n");
				 opened=11;
				 }
				}

								 break;
}
}

return opened;
}





double CLOSEFILE(double* f_a, String_Array_T* str_param)
{
	
if(readflag == 0){
 fclose(fin);
 printf("File was closed\n");
}
 readflag = 1;
Filedatanum=1;
return 1;
}








double RESERVEFILE(double* f_a, String_Array_T* str_param)
{
int num;
int i;
num=(int)f_a[1];

if(readflag == 0){
FileData = (double*)malloc(num*sizeof(double));
if (FileData ==NULL)
{
	printf("There is error in allocating memory \n");

	return -11;
}
else
{
	printf("Memmory for %d values was successfully allocated \n",num);

for (i=0;i<num;i++)
{
	FileData[i]=0;
}
}
}
return 11;
}

double WFILE(double* f_a, String_Array_T* str_param)
{
	
double R,xt,yt,zt,f;
double* x;
double* center;
int array_index, dim;
int NX;
long num;
if(readflag == 0){

   //   fscanf(fin, "%lf", &R);
	//  FileData[Filedatanum]=R;
//	  Filedatanum++;
  //num=fread(volumeData,sizeof(  unsigned char),10,fin);
 // num=fread(Rad,sizeof( unsigned char),1,fin);
 //fclose(fin);
fprintf(fin,"%lf ",f_a[1]);
printf("Value = %lf was written \n",f_a[1]);
 //printf("Filedatanum = %d read \n",Filedatanum-1);

}

return 11;

}












double RFILE(double* f_a, String_Array_T* str_param)
{
	
double R,xt,yt,zt,f;
double* x;
double* center;
int array_index, dim;
int NX;
long num;
if(readflag == 0){

      fscanf(fin, "%lf", &R);
	  FileData[Filedatanum]=R;
	  Filedatanum++;
  //num=fread(volumeData,sizeof(  unsigned char),10,fin);
 // num=fread(Rad,sizeof( unsigned char),1,fin);
 //fclose(fin);
printf("Value = %lf read \n",R);
 //printf("Filedatanum = %d read \n",Filedatanum-1);
return FileData[Filedatanum-1];
}

else
{
	Filedatanum++;
	// printf("Filedatanum = %d read \n",Filedatanum-2);
	return FileData[Filedatanum-2];
}


}










double READFILE(double* f_a, String_Array_T* str_param)
{
	
double R,xt,yt,zt,f;
double* x;
double* center;
int array_index, dim;
int NX;
long num;
if(readflag == 0){

fseek ( fin , (int)f_a[1] , SEEK_SET );

      fscanf(fin, "%lf", &R);
	  FileData[Filedatanum]=R;
	  Filedatanum++;
  //num=fread(volumeData,sizeof(  unsigned char),10,fin);
 // num=fread(Rad,sizeof( unsigned char),1,fin);
 //fclose(fin);
printf("Value = %lf read \n",R);
 //printf("Filedatanum = %d read \n",Filedatanum-1);
return FileData[Filedatanum-1];
}

else
{
	Filedatanum++;
	// printf("Filedatanum = %d read \n",Filedatanum-2);
	return FileData[Filedatanum-2];
}


}










double READFILE3(double* f_a, String_Array_T* str_param)
{
	
double R,xt,yt,zt,f;
double* x;
double* center;
int array_index, dim;
int NX;
long num;
if(readflag == 0){
	if(firstopened==0)
	{
 
if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"r")))
 {
  printf("Cannot open data file \n");
  	firstopened=1;
  ////exit(-1);
 }
  else printf("File %s was opened \n",HF_Get_By_Index(str_param, (int)f_a[0]) );
	}

//(int)f_a[1]
fseek ( fin , (int)f_a[1] , SEEK_SET );

      fscanf(fin, "%lf", &R);
	   FileData[Filedatanum]=R;
Filedatanum++;
  //num=fread(volumeData,sizeof(  unsigned char),10,fin);
 // num=fread(Rad,sizeof( unsigned char),1,fin);
 fclose(fin);
 printf("Rad = %lf read \n",R);
  printf("Filedatanum = %d read \n",Filedatanum-1);
 printf("Data file read \n");
}

else
{
R=FileData[Filedatanum-1];
Filedatanum++;
}
return R;
}








double READFILE4(double* f_a, String_Array_T* str_param)
{
	
double R,xt,yt,zt,f;
double* x;
double* center;
int array_index, dim;
int NX;
long num;
//if(readflag == 0){
 
if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"r")))
 {
  printf("Cannot open data file \n");
  ////exit(-1);
 }
  else printf("File %s was opened \n",HF_Get_By_Index(str_param, (int)f_a[0]) );
//(int)f_a[1]
fseek ( fin , (int)f_a[1] , SEEK_SET );

      fscanf(fin, "%lf", &R);
	  FileData[Filedatanum]=R;
	 Filedatanum++;
  //num=fread(volumeData,sizeof(  unsigned char),10,fin);
 // num=fread(Rad,sizeof( unsigned char),1,fin);
 fclose(fin);
 printf("Rad = %lf read \n",R);
 printf("Filedatanum = %d read \n",Filedatanum-1);

 //readflag = 1;


return R;
}





double FILEREAD(double* f_a, String_Array_T* str_param)
{
	
double R,xt,yt,zt,f;
double* x;
double* center;
int array_index, dim;
int NX;
long num;
//if(readflag == 0){
 
if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"r")))
 {
  printf("Cannot open data file \n");
  ////exit(-1);
 }
  else printf("File %s was opened \n",HF_Get_By_Index(str_param, (int)f_a[0]) );
//(int)f_a[1]
fseek ( fin , 2 , SEEK_SET );

      fscanf(fin, "%lf", &R);
  //num=fread(volumeData,sizeof(  unsigned char),10,fin);
 // num=fread(Rad,sizeof( unsigned char),1,fin);
 fclose(fin);
 printf("Rad = %lf read \n",R);
 printf("Data file read \n");

 readflag = 1;
/*------------------------------------------------------------------*/
//}
/*

   if(!strcmp(HF_Get_By_Index(str_param, (int)f_a[0]), "Hey stub!"))
     R=10;
   else R=3;
   */
//R=(double)volumeData[0][0][0];
	array_index = (int)f_a[1];
HF_Get_Runtime_Array(array_index, &center, &dim);

array_index = (int)f_a[2];
HF_Get_Runtime_Array(array_index, &x, &dim);

if (dim != 3) return -1111111111111.0;

xt=x[0]-center[0];
yt=x[1]-center[1];
zt=x[2]-center[2];
//f = R*R - xt*xt - yt*yt -zt*zt;


return R;
}





double FREAD(double* f_a, String_Array_T* str_param)
{
	
double R,xt,yt,zt,f;
double* x;
double* center;
int filepos;
int NX;
long num;
if(readflag == 0){
/*------------------------------------------------------------------*/
 if (!(fin=fopen(HF_Get_By_Index(str_param, (int)f_a[0]),"r")))
 {
  printf("Cannot open data file \n");
  ////exit(-1);
 }
  else printf("File %s was opened \n",HF_Get_By_Index(str_param, (int)f_a[0]) );
	filepos = (int)f_a[1];
fseek ( fin , filepos , SEEK_SET );

      fscanf(fin, "%lf", &R);
 fclose(fin);
 printf("Value = %lf read from pos %d \n",R,filepos);
 

 readflag = 1;
/*------------------------------------------------------------------*/
}



return R;
}






#include "hfmoout.c"
#include "readscalars.c"