/*INCLUSIONE DI HEADER STANDARD*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*INCLUSIONE DI HEADER USER DEFINED*/
#include "reticolo2D.h"
#include "montecarlo.h"

FILE *montecarlo(int sweep, reticolo *ret, double t,int passistampa){

  FILE *output;
  int i, j, k, l;
  int n=ret->n_sites;
  int M=0, E=0; /*magnetizzazione estensiva, Energia estensiva*/
 

  /*APERTURA FILE DI OUTPUT*/
  output=openoutputtemp(t);
  
  /*printf("debug-- %s\n", *output);*/
  
  /*ROUTINE DI INTEGRAZIONE*/
  for (i=0; i<sweep; i++){
    for(j=0; j<n; j++){
      /*printf("debug-- before metropolis #%d\n", j);*/
      metropolis(ret, t);
    }
    for(k=0; k<n; k++){
      M+=ret->spin[k];
      for(l=0; l<4; l++)
	E-=(ret->spin[k]*(ret->spin[(ret->neigh[k][l])]));
    }
    
    if (i%passistampa==0){
      /*printf("debug-- stampa a i=%d\n", i);*/
      fprintf(output,"%d %d %d\n", i, M, E);
      fflush(output);
    }
  }

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
  /*printf("debug--inside %s\n", *output);*/
  return (output);
}
