#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#include "reticolo2D.h"

int metropolis(reticolo *ret, double t){

    double DE=0; /*differenza di energia*/
    int k; /*indice dello spin da invertire*/
    int sk;
    int i, j;
    double r; 

    /* printf("debug-- i'm inside\n");*/
/*genero un numero casuale fra 0 e n_sites da usare come indice*/
    k=(int) (((double) ret->n_sites)*rand()/(RAND_MAX+1.0)); 
    /* printf("debug-- after estrazione\n");*/
    sk=(-1)*(ret->spin[k]); /*inverto lo spin*/
    /*printf("debug-- after inversion\n");*/
    
    for(i=0; i<4; i++){
	j=ret->neigh[k][i];
	DE+=ret->spin[j];
    }
    
    DE*=sk;

    if(DE<=0){
	(ret->spin[k])=sk;
	return 0;
    }
    else if ((r=(double) (1.0*rand()/(RAND_MAX+1.0)))<=exp(-DE/t)){
	(ret->spin[k])=sk;
	return 0;
    }
    
    return 1;
}
