int gettype2( int jj)
{int type;

switch (ArrayAtomBasOrb[jj])
	{
	case 'S':
		type=0;
	 break;
	 case 'P':
		 type=1;
	  break;
	 case 'D':
		type=2;
		 break;
	 case 'F':
		  
		type=3;
	 break;
		case 'L':
		  //неизвестно, пока как P
		type=4;
	 break;
	}
	 
	return type;


}
int gettype( int jj)
{int type;
	
// if (jj==15) tekatomnum2++;

if (ArraynewAtoms[tekatomnum2]==jj) //новый атом
{

tekatomnum2++;
 

}
//if (tekatomnum2>=2) tekatomnum2=1;

switch (ArrayAtomBasOrb[jj])
	{
	case 'S':
		type=0;
	 break;
	 case 'P':
		 type=1;
	  break;
	 case 'D':
		type=2;
		 break;
	 case 'F':
		  
		type=3;
	 break;
	 case 'L':
		  //неизвестно, пока как P
		type=4;
	 break;
		
	}
	 
	return type;


}



//Функции возвращающие значение описывающих функция для разных орбиталей
double getfuncorbtypeS(double x, double y,double z, int jj)
{
	      // (2 alpha^3/pi^3)^0.25 exp(-alpha r^2)

		double R;
	double f;
	double dx,dy,dz;
	double bs,es;
	double l1,l2,l3;

		bs=ArrayAtomBasCoefEx[jj];
	//	es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
	es=  ArrayAtomBasCoefCont1[jj];
	dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
	
		  l1=bs/3.14;
		  l1=pow(l1,3);
		  l1=2*l1;
		  l1=pow(l1,0.25);

		//f=es*sqrt(sqrt(((2*bs/3.14)*(2*bs/3.14)*(2*bs/3.14))))*exp(-bs*R);
		  f=es*l1*exp(-bs*R);
		//fprintf(fin2," %d \n",fsum);
		//  fprintf(fin2, "Sorb\n\n");
		//	fprintf(fin2,"dx=%lf - %lf\n",x, AtomCordsX[tekatomnum2]);
				
	return f;
}


double getfuncorbtypePX(double x, double y,double z, int jj)
{
			 		double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
	//	es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
	es=  ArrayAtomBasCoefCont1[jj];
	dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];
	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
			//  pvs1=(2*2*2*2*2*2*2)/(2*2*2*2);
			 pvs2=pow(bs,5);
		 pvs3=pow(3.14,3);
		 pvs1=(128*pvs2)/pvs3;
		 pvs1=pow(pvs1,0.25);

		 pvs1=pvs1*es;
		//  ,pvs2,pvs3
		//f=es*(2*bs/3.14)*exp(-bs*R*R);
		pvs1=pvs1*exp(-bs*R); 
		f=pvs1*x; 
		
			return f;
}


double getfuncorbtypePY(double x, double y,double z, int jj)
{
double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
	//	es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
	es=  ArrayAtomBasCoefCont1[jj];
	dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
			//  pvs1=(2*2*2*2*2*2*2)/(2*2*2*2);
		  pvs2=pow(bs,5);
		 pvs3=pow(3.14,3);
		 pvs1=(128*pvs2)/pvs3;
		 pvs1=pow(pvs1,0.25);

		 pvs1=pvs1*es;
		//  ,pvs2,pvs3
		//f=es*(2*bs/3.14)*exp(-bs*R*R);
		pvs1=pvs1*exp(-bs*R);
		f=pvs1*y; 
		
			return f;
}


double getfuncorbtypePZ(double x, double y,double z, int jj)
{
	double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
	//	es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
	es=  ArrayAtomBasCoefCont1[jj];
		dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
			//  pvs1=(2*2*2*2*2*2*2)/(2*2*2*2);
		 pvs2=pow(bs,5);
		 pvs3=pow(3.14,3);
		 pvs1=(128*pvs2)/pvs3;
		 pvs1=pow(pvs1,0.25);

		 pvs1=pvs1*es;
		//  ,pvs2,pvs3
		//f=es*(2*bs/3.14)*exp(-bs*R*R);
		pvs1=pvs1*exp(-bs*R);
		f=pvs1*z; 
		
			return f;
}



double getfuncorbtypeDXX(double x, double y,double z, int jj)
{
	    // xx|yy|zz: (2048 alpha^7/9pi^3)^0.25 [xx|yy|zz]exp(-alpha r^2)
      // xy|xz|yz: (2048 alpha^7/pi^3)^0.25 [xy|xz|yz]exp(-alpha r^2)

		double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
		//es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
	es=  ArrayAtomBasCoefCont1[jj];
		dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
	
		   
		 pvs2=pow(bs,7);
		 pvs3=pow(3.14,3)*9;
		 pvs1=(2048*pvs2)/pvs3;

		 pvs1=pow(pvs1,0.25)*es;
		 	pvs1=pvs1*exp(-bs*R); 
		f=pvs1*x*x; 
		
		
	 // f=0;
	return f;
}




double getfuncorbtypeDYY(double x, double y,double z, int jj)
{
	  
		double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
	//	es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
es=  ArrayAtomBasCoefCont1[jj];
	dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
	
		   pvs2=pow(bs,7);
		 pvs3=pow(3.14,3)*9;
		 pvs1=(2048*pvs2)/pvs3;

		 pvs1=pow(pvs1,0.25)*es;
		 	pvs1=pvs1*exp(-bs*R); 
		f=pvs1*y*y; 
		
		
	 // f=0;
	return f;
}




double getfuncorbtypeDZZ(double x, double y,double z, int jj)
{
		double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
//		es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
es=  ArrayAtomBasCoefCont1[jj];
	dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
	
		  pvs2=pow(bs,7);
		 pvs3=pow(3.14,3)*9;
		 pvs1=(2048*pvs2)/pvs3;

		 pvs1=pow(pvs1,0.25)*es;
		 	pvs1=pvs1*exp(-bs*R);  
		f=pvs1*z*z; 
		
		
	 // f=0;
	return f;
}




double getfuncorbtypeDXY(double x, double y,double z, int jj)
{
		double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
	//	es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
es=  ArrayAtomBasCoefCont1[jj];
	dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
	
		   pvs2=pow(bs,7);
		 pvs3=pow(3.14,3);
		 pvs1=(2048*pvs2)/pvs3;

		 pvs1=pow(pvs1,0.25)*es;
		 	pvs1=pvs1*exp(-bs*R); 
		f=pvs1*x*y; 
		
		
	 // f=0;
	return f;
}




double getfuncorbtypeDXZ(double x, double y,double z, int jj)
{
		double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
		//es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
es=  ArrayAtomBasCoefCont1[jj];
	dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
	
		    pvs2=pow(bs,7);
		 pvs3=pow(3.14,3);
		 pvs1=(2048*pvs2)/pvs3;

		 pvs1=pow(pvs1,0.25)*es;
		 	pvs1=pvs1*exp(-bs*R); 

		f=pvs1*x*z; 
		
		
	//  f=0;
	return f;
}




double getfuncorbtypeDYZ(double x, double y,double z, int jj)
{
		double R;
	double f;
	double dx,dy,dz;
	double bs,es;
double pvs1,pvs2,pvs3;
		bs=ArrayAtomBasCoefEx[jj];
	//	es=  ArrayAtomBasCoefCont1[jj]*ArrayAtomBasCoefCont2[jj];
es=  ArrayAtomBasCoefCont1[jj];

	dx=x-AtomCordsX[tekatomnum2];
	dy=y-AtomCordsY[tekatomnum2];
	dz=z-AtomCordsZ[tekatomnum2];

	
	R= dx*dx+dy*dy+dz*dz;
//R= x*x+y*y+z*z;
	
		    pvs2=pow(bs,7);
		 pvs3=pow(3.14,3);
		 pvs1=(2048*pvs2)/pvs3;

		 pvs1=pow(pvs1,0.25)*es;
		 	pvs1=pvs1*exp(-bs*R); 
		f=pvs1*y*z; 
		
		
	// f=0;
	return f;
}





// Функции подсчета значения описывающей функции в зависимости от типа орбитали
double calcsum(int type, double x, double y, double z, int jj)
{ double f;

	switch (type)
	{
	case 0:
		f= getfuncorbtypeS(x,y,z,jj);
		FuncSum[fsum]=FuncSum[fsum]+f;
		

	 break;
	 case 1:
		f= getfuncorbtypePX(x,y,z,jj);
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypePY(x,y,z,jj);

		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypePZ(x,y,z,jj);

		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum=fsum-2;
	  break;
	 case 2:
		f= getfuncorbtypeDXX(x,y,z,jj);
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypeDYY(x,y,z,jj);
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypeDZZ(x,y,z,jj);
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypeDXY(x,y,z,jj);
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypeDXZ(x,y,z,jj);
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypeDYZ(x,y,z,jj);
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum=fsum-5;
		 break;
	 case 3:
		  
		f= 0;
	 break;

	 case 4:
		f= getfuncorbtypeS(x,y,z,jj);
		
		FuncSum[fsum]=FuncSum[fsum]+f;
	    fsum++;
		f= getfuncorbtypePX(x,y,z,jj);
		
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypePY(x,y,z,jj);
		

		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypePZ(x,y,z,jj);
		
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum=fsum-3;
	  break;
		
	}
	return f;
}



double calcone(int type, double x, double y, double z, int jj)
{double f=0;
switch (type)
	{
	case 0:
		
		 f= getfuncorbtypeS(x,y,z,jj);
		
		 FuncSum[fsum]=f;
		
	 break;
	 case 1:
		f= getfuncorbtypePX(x,y,z,jj);
	

		
		FuncSum[fsum]=f;
		fsum++;
		f= getfuncorbtypePY(x,y,z,jj);
		
		FuncSum[fsum]=f;
		fsum++;
		f= getfuncorbtypePZ(x,y,z,jj);
		

		FuncSum[fsum]=f;
		fsum=fsum-2;
	  break;
	 case 2:
		f= getfuncorbtypeDXX(x,y,z,jj);
		FuncSum[fsum]=f;
		fsum++;
		f= getfuncorbtypeDYY(x,y,z,jj);
		FuncSum[fsum]=f;
		fsum++;
		f= getfuncorbtypeDZZ(x,y,z,jj);
		FuncSum[fsum]=f;
		fsum++;
		f= getfuncorbtypeDXY(x,y,z,jj);
		FuncSum[fsum]=f;
		fsum++;
		f= getfuncorbtypeDXZ(x,y,z,jj);
		FuncSum[fsum]=f;
		fsum++;
		f= getfuncorbtypeDYZ(x,y,z,jj);
		FuncSum[fsum]=f;
		fsum=fsum-5;
		 break;
	 case 3:
		  
		f= 0;
	 break;
	 case 4:
		f= getfuncorbtypeS(x,y,z,jj);
		
		FuncSum[fsum]=FuncSum[fsum]+f;
	    fsum++;
		f= getfuncorbtypePX(x,y,z,jj);
		
		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypePY(x,y,z,jj);
		

		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum++;
		f= getfuncorbtypePZ(x,y,z,jj);
		

		FuncSum[fsum]=FuncSum[fsum]+f;
		fsum=fsum-3;
	  break;
		
	}
return f;
}

//Функция подсчета всего массива описывающих функций без молекулярных коэффициентов
void  calcfunction(double x, double y,double z,int jj)
{
	int type,type2;
	double f=0;
 if (jj>0)// не первый элемент
 {
	 if (ArrayAtomBasNum[jj]==ArrayAtomBasNum[jj-1])//сумма функций
	 { 
		
		type= gettype(jj);
	f=calcsum(type,x,y,z,jj);
//		printf("calsum \n)");
	 }
	 else //не сумма функций
	 {
		 type= gettype(jj);
		 type2= gettype2(jj-1);
		//fsum++;
		
		switch (type2)
	{
			case 0:
				fsum++;
				break;
			case 1:
				fsum=fsum+3;
				break;
			case 2:
				fsum=fsum+6;
				break;
			case 3:
				fsum++;
				break;
			case 4:
				fsum=fsum+4;
				break;
		}
	
	//	printf("calcone \n)");

		f=calcone(type,x,y,z,jj);

	 }
 }
 else //первый элемент
 { 
	 fsum=0;

	 	 type= gettype(jj);
		tekatomnum2=0;
		f=calcone(type,x,y,z,jj);
			//	printf("calcone first \n)");
	

 }
	 
	

}



// Функция считывания 
/*
 ATOM      ATOMIC                      COORDINATES (BOHR)
           CHARGE         X                   Y                   Z
		   */
void readcordBor()
{
	double charge;
int i=0;

	if (pch!= NULL)
	{
	printf(" %s  \n",line);
	fgets(line, 80, fin) ;
	printf(" %s  \n",line);
	c = fgetc(fin);
	c = fgetc(fin);
	AtomNames[i]=c;

	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);

pos=ftell (fin);
		
		
fscanf (fin, "%lf %lf %lf %lf ",&AtomCordsCharge[i], &AtomCordsX[i], &AtomCordsY[i], &AtomCordsZ[i]);
atomsNumFinal++;
fseek ( fin , pos , SEEK_SET );

	fgets(line, 80, fin) ;
	printf(" %s  \n",line);
	printf(" %c  \n",c);
	i++;
	pch2 = strstr (line,"INTERNUCLEAR DISTANCES (ANGS.)");
		while (pch2== NULL)
		{

		c = fgetc(fin);
		c = fgetc(fin);
		AtomNames[i]=c;
		c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
	c = fgetc(fin);
pos=ftell (fin);
		
		
fscanf (fin, "%lf %lf %lf %lf ",&AtomCordsCharge[i], &AtomCordsX[i], &AtomCordsY[i], &AtomCordsZ[i]);
fseek ( fin , pos , SEEK_SET );
		fgets(line, 1000, fin) ;
	//	printf(" %s  \n",line);
		printf(" %c  \n",c);
		i++;
		pos=ftell (fin);
		//printf(" %d  \n",pos);
		fgets(line, 1000, fin) ;
		fgets(line, 1000, fin) ;
		//printf(" %s  \n",line);
		pch2 = strstr (line,"INTERNUCLEAR DISTANCES (ANGS.)");
		fseek ( fin , pos , SEEK_SET );
		pos=ftell (fin);
		//printf(" %d  \n",pos);
		}
	atomnum=i;

	}
//	double nl=0.986;
//			fprintf(fin2,"tried %lf\n", nl);

}	


// формирование массивов
void FormArrays( int  pos2)
{int fll=0;
		int ll=0;
int i=0;
	int pp=0;
	

	while (pch4== NULL)
		{
			ll++;
			fgets(line, 80, fin) ;
			pch4 = strstr (line,"TOTAL NUMBER OF SHELLS");

		}

	for (pp=0;pp<40;pp++)
	{
		cc3=fgetc(fin);
	}
	fscanf (fin, "%d", &numcoef);
	printf(" -----------%d  \n",numcoef);
	FuncSum=  (double*) malloc (numcoef*sizeof(double));
		for ( fll=0; fll<numcoef;fll++)
			FuncSum[fll]=0;

			FuncSum2= (double*) malloc (numcoef*sizeof(double));
		for ( fll=0; fll<numcoef;fll++)
			FuncSum2[fll]=0;
ArrayAMoN= (int *)malloc (numcoef*sizeof(int));
	ArrayAtomMoCoef=(double*) malloc (numcoef*sizeof(double));
	for(i = 0; i < numcoef; i++)
	{
ArrayAtomMoCoef[i]=(double*) malloc (numcoef*sizeof(double));
ArrayAMoN[i]=0;
	}
		fseek ( fin , pos2 , SEEK_SET );
		//возвращение на позицию в файле и формирование массивов
		//pos2=ftell(fin);
//printf(" %d  \n",pos2);
		 ArrayAtomBasCoefEx=(double*) malloc (ll*sizeof(double));
		 ArrayAtomBasCoefCont1=(double*) malloc (ll*sizeof(double));
		 ArrayAtomBasCoefCont2=(double*) malloc (ll*sizeof(double));
		 ArrayAtomBasNum=(int*) malloc (ll*sizeof(int));
		ArrayAtomBasPrim=(int*) malloc (ll*sizeof(int));
		ArrayAtomBasOrb = (char*) malloc (ll*sizeof(char));
		ArraynewAtoms=(int*) malloc (ll*sizeof(int));

		totalll=ll;
}


// Функция считывания молекулярных коэффициентов
void coefreader(int numrows, int numrowcount )
{
int dd2=0;
int ddd=0;
	int dl;
	dl=0;
	fseek ( fin , pos3 , SEEK_SET );	
	//printf("%d  \n", numrows);
	fgets(line, 80, fin) ;
	fgets(line, 80, fin) ;
	fgets(line, 80, fin) ;
//	printf(" %s  \n",line);
	pos3=ftell(fin);
  //pch7 = strstr (line,"MOLECULAR ORBITALS");



for (dl=0;dl<numrows-numrowcount*5;dl++)
{
	dd2=0;
//	printf("Printing row %d  \n", dl);
fseek ( fin , pos3 , SEEK_SET );	
pos44=ftell(fin);
//запоминание позиции файла
	
{
	
  		while (dd2<numcoef)
		{
		
		cc5=fgetc(fin);
	//	printf(" --error  \n");

			for (ddd=0;ddd<16+11*dl;ddd++)//константы -  не debugging
			{
			fscanf (fin, "%c", &cc6);
			/*
			fscanf (fin, "%d", &ArrayAMoN[dd2]);
			fscanf (fin, "%c", &cc6);
			fscanf (fin, "%c", &cc6);
			fscanf (fin, "%c", &cc6);
			fscanf (fin, "%c", &cc6);
			*/
			

			}
			
		
			 fscanf (fin, "%lf", &ArrayAtomMoCoef[lll][dd2]);

			 //умножение на коеффициенты
			// FuncSum[dd2]=FuncSum[dd2]+FuncSum[dd2]*ArrayAtomMoCoef[lll][dd2];
			//printf("%lf  ", ArrayAtomMoCoef[lll][dd2]);
			fgets(line, 80, fin) ;

			dd2++;
		}
		lll++;
//	printf("\n");
	totalcoef=lll;
totalrows_coef=dd2;
}
}



}




//Функция считывания базисных коэффициентов
void totalnumread(double xx, double yx, double zx, int pos2)
{
	int jj=0;
while (pch5== NULL)
		{
		fseek ( fin , pos2 , SEEK_SET );	
		pos2=ftell(fin);
		fgets(line, 80, fin) ;
		while(line[0]==0x0A)//пустая строка
		{
			pos2=ftell(fin);//пропуск
			fgets(line, 80, fin) ;
			
		}
		fseek ( fin , pos2 , SEEK_SET );
		cc=fgetc(fin);
		//printf(" %c  ",cc2);
	//	if (cc2== ' ')
		{
		cc=fgetc(fin);
	
if (cc== ' ')//не название атома
		{
		 fscanf (fin, "%d", &ArrayAtomBasNum[jj]);
		 fscanf (fin, "%c", &cc);
		  fscanf (fin, "%c", &cc);
		   fscanf (fin, "%c", &cc);
		  fscanf (fin, "%c", &ArrayAtomBasOrb[jj]);
 fscanf (fin, "%d", &ArrayAtomBasPrim[jj]);
		  fscanf (fin, "%lf", &ArrayAtomBasCoefEx[jj]);
		   fscanf (fin, "%lf", &ArrayAtomBasCoefCont1[jj]);
		   fscanf (fin, "%c", &cc);
		  fscanf (fin, "%c", &cc);
		   fscanf (fin, "%c", &cc);
		    fscanf (fin, "%lf", &ArrayAtomBasCoefCont2[jj]);
			// Подсчет функции
			//calcfunction(x,y,z,jj);

printf("%d  %c  %d  %lf  %lf (%lf) \n",ArrayAtomBasNum[jj],ArrayAtomBasOrb[jj],ArrayAtomBasPrim[jj],ArrayAtomBasCoefEx[jj],ArrayAtomBasCoefCont1[jj],ArrayAtomBasCoefCont2[jj]);
jj++;
fgets(line, 80, fin) ;

}
		

else
{

	if (cc==AtomNames[l])//атом
		{
			fgets(line, 80, fin) ;// пропуск 
			fgets(line, 80, fin) ;// пропуск  
			
			ArraynewAtoms[tekatomnum]=jj;//где новый атом
			tekatomnum++;
			printf(" New atom %c \n",cc);
			
	}
		
	
}
		} 
totalll=jj;
pos2=ftell(fin);
	fgets(line, 80, fin) ;
	fgets(line, 80, fin) ;
		pch5 = strstr (line,"TOTAL NUMBER OF SHELLS");
		nn++;
		}

}

