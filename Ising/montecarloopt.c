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
  int k, i, ix, iy, site;
  int M=0, E=0, dE;  /*magnetizzazione estensiva, Energia estensiva*/
  double m, e;   /*magnetizzazione intensiva, Energia intensiva*/
  
  
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
  for (i=0; i<SWEEP; i++){          /*esegui SWEEP sweep (vedi macros.h)*/
  
    for(ix=0; ix<L; ix++){
      for(iy=0; iy<L; iy++){
	site=ix+L*iy;
	dE=spin[site]*((spin[ix+L*((iy+L-1)%L)])+(spin[ix+L*((iy+L+1)%L)])+(spin[iy*L+((ix+L-1)%L)])+(spin[iy*L+((ix+L+1)%L)]));
	E+=accept(spin, site , prob, &M, dE);
	/*M e' aggiornata da accept*/
      }
    }
    if ((i<=300)||(i%P==0)){        /*stampa ogni P sweep (vedi macros.h)*/
      
      m=(double) M/(double) (L*L);
      e=(double) E/(double) (L*L);
      fprintf(output,"%d %f %f\n", i, m, e);
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


int accept(int *spin, int k, double *prob, int *M, int de){

  double r;

  
  
  if(de<=0){
    (spin[k])*=-1;
    (*M)+=2*spin[k];
    return (2*de);
    }
  else if ((r=drand48())<=prob[de]){
    (spin[k])*=-1;
    (*M)+=2*spin[k];
    return (2*de);
  }
  
  else return 0;
}

