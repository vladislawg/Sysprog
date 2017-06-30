#include "main.h"


int *frei(Mtx* Matrix, int verfuegbar[]){
  int *array = calloc(Matrix -> rows, sizeof(int)) ;
 printf("%d, %d\n", Matrix -> rows, Matrix -> cols);
   for(int i = 0; i < Matrix -> cols; i++){
     for(int j = 0; j < Matrix -> rows; j++){
       array[i] = array[i] + Matrix -> data[j][i];
     }
   }

   for(int i = 0; i < Matrix -> cols; i++){
     array[i] = verfuegbar[i] - array[i];  
   }
   return array;
}

int *get_col(Mtx* Matrix, int index){
  int *array = calloc(Matrix -> cols, sizeof(int));
  for(int i = 0; i < Matrix -> cols; i++){
    array[i] = Matrix -> data[index][i];
  }
  return array;
}

int find_prozess(Mtx* Anforderungsmatrix, int *Restvektor){

  int *array = NULL;
  int index = 0;

  for(int i = 0; i < Anforderungsmatrix -> rows; i++){
    array = get_col(Anforderungsmatrix, i);

    for(int j = 0; j < Anforderungsmatrix -> cols; j++){
      printf("array: %d\n", array[j]);
      printf("rest: %d\n", Restvektor[j]);
      if(array[j] <= Restvektor[j]){
        index = i;
      } else {
        index = -1;
      }
    }
  }
  return index;
}

void bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int verfuegbar[], int Betriebsmittel){

//Calculate Freie Betriebsmittel
  int *Betriebsmittelrestvektor = frei(Belegungsmatrix, verfuegbar);

   for(int i = 0; i < Belegungsmatrix -> cols; i++){
     printf("%d", Betriebsmittelrestvektor[i]);
   }
   printf("\n");

   int i = find_prozess(Gesamtanforderung, Betriebsmittelrestvektor);
   printf("Prozess: %d\n", i);
   if (i < 0){
     printf("Kein prozess gefunden\n");
     exit(1);
   }

}
