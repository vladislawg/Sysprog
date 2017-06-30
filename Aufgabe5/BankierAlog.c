#include "main.h"


int *frei(Mtx* Matrix, int verfuegbar[]){
  int *array = calloc(Matrix -> rows, sizeof(int)) ;
//  printf("%d, %d", Matrix -> rows, Matrix -> cols
   for(int i = 0; i < Matrix -> cols; i++){
     for(int j = 0; j < Matrix -> rows; j++){
       array[i] = array[i] + Matrix -> data[j][i];
     }
   }
   return array;
}


int find_prozess(Mtx* Anforderungsmatrix, int *Restvektor){
  int Prozess = 0;

  return 1;
}

void bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int verfuegbar[], int Betriebsmittel){

//Calculate Freie Betriebsmittel
  int *Betriebsmittelrestvektor = frei(Belegungsmatrix, verfuegbar);

   for(int i = 0; i < Belegungsmatrix -> cols; i++){
     printf("%d\n", Betriebsmittelrestvektor[i]);
   }

   find_prozess(Gesamtanforderung, Betriebsmittelrestvektor);

}
