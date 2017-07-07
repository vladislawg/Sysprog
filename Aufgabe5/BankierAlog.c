#include <stdbool.h>

#include "main.h"

Status bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int rows, int cols, int *Betriebsmittelrestvektor, Mtx* Restananforderungsmatrix ){

  //suche nach Prozesse
  int counter = 0;
  int Prozess = 0;
  int del = 0;
  Status state = UNDEFINED;

  while(state == UNDEFINED){
    for(int i = 0; i < cols; i++){
      counter = 0;
      for(int j = 0; j < rows; j++){
        if(Betriebsmittelrestvektor[j] >= Restananforderungsmatrix -> data[j][i]){
          counter ++;
          if(counter == rows){
            Prozess = i;
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
      if(i == cols-1){
        state = UNSAFE;
      }
    }
    if(del == 1){
      for(int j = 0; j < rows; j++){
        Betriebsmittelrestvektor[j] = Betriebsmittelrestvektor[j] + Belegungsmatrix -> data[j][Prozess];
      }
      cols --;
    }
    if(cols == 0){
      state = SAFE;
   }
  }
    return state;
}
