/*INCLUSIONE FILE DI HEADER STANDARD*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*INCLUSIONE FILE DI HEADER SPECIFICI (USER DEFINED)*/
#include "macros.h"
#include "reticolo2D.h" /*Contiene la definizione del tipo struttura reticolo*/
#include "montecarlo.h"
/*PROTOTIPI DI FUNZIONE*/
int config_ini(int *spin);
int assign(void);

int  main(void){
    
    int *spin;           /*struttura che contiene il reticolo*/
    double prob[9];
    int i,j;                  /*contatori di loop*/
    FILE *output;

    /*inizializzazione del generatore di numeri casuali*/
    srand48(SEED);
    /*calcolo le probabilita' dei valori di energia*/
    for(i=0; i<9; i++)
	prob[i]=exp(-2.*(double)i/T);

    /*allocazione della memoria*/
    spin=(int *) malloc(L*L*sizeof(int));
       
    /*generazione della configurazione iniziale*/
    config_ini(spin);
    
    /*algoritmo di montecarlo*/
    output=montecarlo(spin, prob);

    return 0;

}

config_ini(int *spin){

    int i;
    for(i=0; i<(L*L); i++)
      spin[i]=assign();

    return 0;
}
						       

int assign(void){

  double r;

  if ((r=(double) (1.0*rand())/(RAND_MAX+1.0))<0.5)
    return (-1);
  else if (r>0.5)
    return (1);
  else return assign();  /*escludo il valore di soglia 0.5*/
}
