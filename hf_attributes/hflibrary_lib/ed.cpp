
	FILE*fin;
float ftr;
fin = fopen("4.txt", "r");
FILE* fin2;
//fin2 = fopen("34.txt", "w");
char line [ 80 ]; 

fgets ( line, sizeof line, fin);
//3D Total Electron Density Visible
  fscanf (fin, "%d", &dx);
  fscanf (fin, "%d", &dy);
   fscanf (fin, "%d", &dz);
  
 fgets ( line, sizeof line, fin);
 //nx ny nz


 
 fscanf (fin, "%f", &xst2);
  fscanf (fin, "%f", &yst2);
   fscanf (fin, "%f", &zst2);
 fgets ( line, sizeof line, fin);
//Origin of the 3D grid

 el[0]=xst2;
 el[1]=yst2;
 el[2]=zst2;
 //	this->Pmin=MDPoint(elems_num,el);
 //minimum
	

 fscanf (fin, "%f", &xst);
  fscanf (fin, "%f", &yst);
   fscanf (fin, "%f", &zst);
 fgets ( line, sizeof line, fin);

// xst=xst*10;
// yst=yst*10;
// zst=zst*10;

 for (int i=0; i<MAXDIM;i++)
	{ el[i]=6.0f;
	}
	
 el[0]=xst2+dx*xst-4;
 el[1]=yst2+dy*yst-4;
 el[2]=zst2+dz*zst-4;
 //this->Pmax=MDPoint(elems_num,el);
 //maximum


 float fmain;
Grid=new GRID**[dx];
	for(UINT i=0;i<dx;i++)
	{		
		Grid[i]=new GRID*[dy];
		for(UINT j=0;j<dy;j++)
		{
			Grid[i][j]=new GRID[dz];
			for(UINT k=0;k<dz;k++)
			{
				
				Grid[i][j][k].p.x=xst2+i*xst;
				Grid[i][j][k].p.y=yst2+j*yst;
				Grid[i][j][k].p.z=zst2+k*zst;

				// if (!feof(fin)) {
			fscanf (fin, "%f", &fmain);
			//fprintf (fin2, "%f,", fmain);
			//fmain=fmain-0.1;
			

		//}

				Grid[i][j][k].val=fmain;
			}
		}
	}

fclose(fin);
