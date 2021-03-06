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
  int n=ret->n_sites; /*numero di siti*/
  int M=0, E=0;  /*magnetizzazione estensiva, Energia estensiva*/
  double m, e;   /*magnetizzazione intensiva, Energia intensiva*/
  int *spin, **neigh; /*puntatori di appoggio*/

  /*APERTURA FILE DI OUTPUT*/
  output=openoutputtemp(t);
  
  /*printf("debug-- %s\n", *output);*/
  
  spin=ret->spin;
  neigh=ret->neigh;

  for(k=0; k<n; k++){
      for(l=0; l<4; l++)
	  E-=(spin[k]*(spin[neigh[k][l]]))/2.;
  }
  
  /*ROUTINE DI INTEGRAZIONE*/
  for (i=0; i<sweep; i++){
      for(j=0; j<n; j++){
      /*printf("debug-- before metropolis #%d\n", j);*/
	  E+=metropolis(spin+n, t);
	  M+=2*spin[n];
      }
     
      
      
    if (i%passistampa==0){
	/*printf("debug-- stampa a i=%d\n", i);*/
	m=(double) M/(double) n;
	e=(double) E/(double) n;
	fprintf(output,"%d %f %f\n", i, m, e);
	fflush(output);
    }
  }
  
  printf("dati scritti in ising2D_t%.3lf.dat\n", t);
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
