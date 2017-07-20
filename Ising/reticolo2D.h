/*****************************************/
/*   STRUTTURA CHE CONTIENE IL RETICOLO  */
/*           BIDIMENSIONALE              */
/*****************************************/
typedef struct {
  int **neigh; /*lista di adiacenza*/
  int *spin;   /*vettore che contiene i valori degli spin*/
  int n_sites;
} reticolo;

/********************************************************/
/*                                                      */
/*FUNZIONE CHE ESEGUE IL RIAGGIORNAMENTO DELLE VARIABILI*/
/*CON UN ALGORITMO DI METROPOLIS                        */
/*                                                      */
/********************************************************/
int metropolis(reticolo *ret, double Tc);
