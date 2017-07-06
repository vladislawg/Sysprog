#include "main.h"

void printMtx(Mtx *Matrix){
  printf("printMtx\n");
  for(int j = 0; j < Matrix -> cols; j++){
    for(int i = 0; i < Matrix -> rows; i++){
      printf("%d ", Matrix -> data[i][j]);
    }
    printf("\n");
  }
}

int *calc_free_array(Mtx* Matrix, int verfuegbar[]){
  int *array = calloc(Matrix -> rows, sizeof(int*));
  for(int j = 0; j < Matrix -> rows; j++){
    array[j] = verfuegbar[j];
  }
   for(int i = 0; i < Matrix -> cols; i++){
     for(int j = 0; j < Matrix -> rows; j++){
       array[j] = array[j] - Matrix -> data[j][i];
     }
   }
 return array;
}

Mtx* calc_Restanforderung(Mtx* Gesamtanforderung, Mtx* Belegungsmatrix, int rows, int cols){
  Mtx *Restananforderungsmatrix = make_matrix(rows, cols);
  for(int j = 0; j < cols; j++){
    for(int i = 0; i < rows; i++){
      Restananforderungsmatrix -> data[i][j] = Gesamtanforderung -> data[i][j] - Belegungsmatrix -> data[i][j];
    }
  }
  return Restananforderungsmatrix;
}

Status bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int verfuegbar[], int rows, int cols){

  //Berechne Freie Betriebsmittel
  int *Betriebsmittelrestvektor = calc_free_array(Belegungsmatrix, verfuegbar);
  Mtx* Restananforderungsmatrix = calc_Restanforderung(Gesamtanforderung, Belegungsmatrix, rows, cols);

  //suche nach Prozesse
  int counter = 0;
  int Prozess = 0;
  int del = 0;
  Status state = UNDEFINED; //0 undefindes, -1 unsafe, 1 safe

  printMtx(Restananforderungsmatrix);
  for(int i = 0; i < rows; i++)
    printf("%d", Betriebsmittelrestvektor[i]);
printf("\n");

 while(state == UNDEFINED){
    for(int i = 0; i < cols; i++){
      counter = 0;
      for(int j = 0; j < rows; j++){
        printf("i:%d\n",i);
        printf("j:%d\n",j);
        printf("%d >= %d\n",Betriebsmittelrestvektor[j], Restananforderungsmatrix -> data[j][i]);
        if(Betriebsmittelrestvektor[j] >= Restananforderungsmatrix -> data[j][i]){
          counter ++;
          printf("c %d\n",counter );
          if(counter == rows){
            Prozess = i;
            printf("%d\n", Prozess);
            del = 1;
            break;
           }
           continue;
         }else{
           break;
         }
      }
      if(del == 1){
        break;
      }
      printf("''''''''''''i: %d\n", i);
      printf("//////////////%d\n", cols -1);
      if(i == cols-1){
        printf("undsafe\n");
        state = UNSAFE;
      }
    }
    printf("%d\n", Prozess);

    if(del == 1){
      for(int j = 0; j < rows; j++){
        Betriebsmittelrestvektor[j] = Betriebsmittelrestvektor[j] + Belegungsmatrix -> data[j][Prozess];
      }
      cols --;
    }
    if(cols == 0){
      //safe
      state = SAFE;
   }
 }
    return state;
}
