#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "macros.h"
#include "reticolo2D.h"

int metropolis(int *spin, int k, double *prob, int *M, int DE){

    if((DE<=0) || (((double) (1.0*rand()/(RAND_MAX+1.0)))<=prob[DE])){
	(spin[k])*=-1;
	(*M)+=
	return (2*DE);
    }
    
    return ;
}
