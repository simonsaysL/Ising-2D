/*INCLUSIONE DI HEADER STANDARD*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*INCLUSIONE DI HEADER USER DEFINED*/
#include "macros.h"
#include "reticolo2D.h"
#include "montecarlo.h"

FILE *montecarlo(int *spin, double *prob){

  FILE *output;
  int k, t, ix, iy, site;
  int M=0, E=0, dE;  /*magnetizzazione estensiva, Energia estensiva*/
  int aveM=0, aveE=0; /*magn estensiva media, enr estensiva media*/
  double m, e;   /*magnetizzazione intensiva, Energia intensiva*/
  double r;
  int meastime=1, cont=1;
  
  /*APERTURA FILE DI OUTPUT*/
  output=openoutputtemp(T);
  
  for(k=0; k<(L*L); k++){
    
    M+=spin[k];
   
  }
  
  for(ix=0; ix<L; ix++)
    for(iy=0; iy<L; iy++){
      site=ix+L*iy;
      E-=spin[site]*(spin[ix+L*((iy+L-1)%L)]+spin[iy*L+((ix+L+1)%L)]);
    }
  
  /*ROUTINE DI INTEGRAZIONE*/ 
  for (t=0; t<SWEEP; t++){          /*esegui SWEEP sweep (vedi macros.h)*/
      /*MONTECARLO SWEEP*/
      for(ix=0; ix<L; ix++){
	for(iy=0; iy<L; iy++){
	    site=ix+L*iy;
	    dE=spin[site]*((spin[ix+L*((iy+L-1)%L)])+(spin[ix+L*((iy+L+1)%L)])+(spin[iy*L+((ix+L-1)%L)])+(spin[iy*L+((ix+L+1)%L)]));
	    
	    if(dE<=0){
		(spin[k])*=-1;
		M+=2*spin[k];
		E+=(2*dE);
	    }
	    else if ((r=drand48())<=prob[dE]){
		(spin[k])*=-1;
		M+=2*spin[k];
		E=+(2*dE);
	    }
	    
	}
      } /*FINE MONTECARLOSWEEP*/
      if (t>PT){
	  aveM+=M;
	  aveE+=E;
	  cont++;
      }
      if (t==(PT+meastime)){        /*stampa ogni P sweep (vedi macros.h)*/
	  
	  m=(double) aveM/(double) (cont);
	  aveM=0;
	  e=(double) aveE/(double) (cont);
	  aveE=0; 
	  cont=0;
	  meastime*=2;
	  fprintf(output,"%d %f %f\n", t, m, e);
	  fflush(output);
      }
  }
  printf("dati scritti in ising2D_t%.3lf.dat\n", T);
  return (output);
  
}

FILE *openoutputtemp(double t){

  char name[30];
  FILE *output;
 
  sprintf(name,"ising2D_t%.3lf.dat", t);
  if((output=fopen(name, "w"))==NULL){
    printf("ERROR WHILE OPENING OUTPUT FILE\n");
    exit (1);
  }  
  
  return (output);
}


