/*INCLUSIONE FILE DI HEADER STANDARD*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*INCLUSIONE FILE DI HEADER SPECIFICI (USER DEFINED)*/
#include "reticolo2D.h" /*Contiene la definizione del tipo struttura reticolo*/
#include "montecarlo.h"
/*PROTOTIPI DI FUNZIONE*/
int neighborhood2D(int **neighlist, int n_sites);
int config_ini(int *spin, int lin_dim);

/***************DEFINIZIONE DI MACRO****************/
#ifndef L
#define L 50   /*dimensione lineare del reticolo*/
#endif

#ifndef T
#define T 5  /*temperatura del sistema*/
#endif

#ifndef NITER 
#define NITER 10000  /*numero di iterazioni montecarlo (sweep)*/
#endif

#ifndef SEED 
#define SEED 1  /*seme per il generatore di numeri casuali*/
#endif

#ifndef P
#define P 100     /*ogni quanti sweep bisogna stampare*/
#endif

#define GAMMA 4
/****************************************************/

int main(void){
    
    reticolo ret;           /*struttura che contiene il reticolo*/
    int static c=GAMMA;     /*connetivita' dei siti*/
    int n_sites=L*L;        /*numero di siti (vertici)*/
    int i,j;                  /*contatori di loop*/
    int sweep=NITER;
    double t=T;
    FILE *output;

    /*inizializzazione del generatore di numeri casuali*/
    srand(SEED);

    /*allocazione della memoria*/
    ret.n_sites=n_sites;
    ret.spin=(int *) malloc(n_sites*sizeof(int));
    ret.neigh=(int **) malloc(n_sites*sizeof(int *));
    for (i=0; i<n_sites; i++)
	ret.neigh[i]=(int *) malloc(c*sizeof(int));
    
    /*generazione della lista di adiacenza*/
    neighborhood2D(ret.neigh, L);
    /*generazione della configurazione iniziale*/
    config_ini(ret.spin, n_sites);
    /*algoritmo di montecarlo*/
    output=montecarlo(sweep, &ret, t, P);

    return 0;

}


int neighborhood2D(int **neighlist, int lin_dim){

    int ix, iy;
    int i; /*indice dell'elemento*/
    int r, l, up, dow; /*indici dei primi vicini di destra, sin, su, giu*/
 
    for(ix<0; ix<lin_dim; ix++){
	for(iy=0; iy<lin_dim; iy++){
	    i=ix+lin_dim*iy;
	    if ((r=i+1)>=lin_dim)   /*condizioni periodiche al bordo*/
		r=r-lin_dim;
	    if ((l=i-1)<0)
		l+=lin_dim;
	    if((up=i+lin_dim)>lin_dim*lin_dim)
		up=ix;
	    if((dow=i-lin_dim)<0)
		dow+=lin_dim*(lin_dim);
	    neighlist[i][0]=l;
	    neighlist[i][1]=r;
	    neighlist[i][2]=up;
	    neighlist[i][3]=dow;
	}
    }
    
    return 0;
}


int config_ini(int *spin, int n_sites){

    int i;
    double r;
    int check=0;   /*escludo il valore  di soglia 0.5*/

    for(i=0; i<n_sites; i++)
	while(check==0){
	    if ((r=(double) (1.0*rand())/(RAND_MAX+1.0))<0.5){
		spin[i]=-1;
		check=1;
	    }
	    else if (r>0.5){ 
		spin[i]=+1;
		check=1;
	    }
	}

    return 0;
}
						       
