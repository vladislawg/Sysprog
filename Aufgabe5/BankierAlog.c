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
  int *array = calloc(Matrix -> rows, sizeof(int)) ;
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

int find_prozess(Mtx* Restananforderungsmatrix, int *Betriebsmittelrestvektor, int rows, int cols){
  int counter = 0;

  printMtx(Restananforderungsmatrix);
  for(int i = 0; i < rows; i++){
    printf("%d", Betriebsmittelrestvektor[i]);
  }

  for(int i = 0; i < cols; i++){
    counter = 0;
    for(int j = 0; j < rows; j++){
      printf("i: %d\n",i);
      printf("j: %d\n",j);
      printf("counter%d\n",counter);
      printf("rows%d\n",rows);
      if(Betriebsmittelrestvektor[j] >= Restananforderungsmatrix -> data[j][i]){
        counter ++;
      }else{
        break;
      }
    }
    if(counter == rows){
      //printf("counter%d\n",counter);
      printf("return\n");
      return i;
    }
  }
   return -1;
}

void bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int verfuegbar[], int rows, int cols){

  //Berechne Freie Betriebsmittel
  Mtx *Gesamtanforderung_cp = Gesamtanforderung;
  Mtx *Belegungsmatrix_cp = Belegungsmatrix;

  int *Betriebsmittelrestvektor = calc_free_array(Belegungsmatrix, verfuegbar);
  Mtx *Restananforderungsmatrix = make_matrix(rows, cols);

  //Berechne Restananforderungsmatrix
  for(int j = 0; j < cols; j++){
    for(int i = 0; i < rows; i++){
      Restananforderungsmatrix -> data[i][j] = Gesamtanforderung -> data[i][j] - Belegungsmatrix -> data[i][j];
    }
  }

  int del = 0;

    int Prozess = find_prozess(Restananforderungsmatrix, Betriebsmittelrestvektor, rows, cols);
    printf("\n%d\n", Prozess);
    if(Prozess == -1){
      printf("kein Prozess gefunden\n");
    } else {
      del = 1;
    }

    if(del == 1){
      //Bullshit
      for(int i = 0; i < rows; i++){
        Restananforderungsmatrix -> data[i][Prozess] = Restananforderungsmatrix -> data[i][Prozess-1];
        Betriebsmittelrestvektor[i] = Betriebsmittelrestvektor[i] + Restananforderungsmatrix -> data[i][Prozess-1];
        Belegungsmatrix_cp -> data[i][Prozess] = Belegungsmatrix_cp -> data[i][Prozess-1];
      }
    }

    printMtx(Belegungsmatrix);
    printMtx(Restananforderungsmatrix);

}
  //suche nach Prozesse
//   int counter = 0;
//   int Prozess = 0;
//   int del = 0;
//   int status = 0; //0 undefindes, -1 unsafe, 1 safe
//
//   while(status == 0)
//     for(int i = 0; i < Restananforderungsmatrix -> cols; i++){
//       counter = 0;
//       for(int j = 0; j < Restananforderungsmatrix -> rows; j++){
//         if(Betriebsmittelrestvektor[i] >= Restananforderungsmatrix -> data[i][j]){
//           counter ++;
//           if(counter == Restananforderungsmatrix -> rows){
//             Prozess = j;
//             printf("%d\n", Prozess);
//             del = 1;
//             break;
//            }
//            continue;
//          }else {
//            break;
//          }
//       }
//
//       if(del == 1){
//         break;
//       }
//       if(i == cols - 1){
//         //set safe
//         status = -1;
//         printf("unsafe\n");
//       }
//     }
//     if(del == 1){
//       for(int i = 0; i < rows; i++){
//         Restananforderungsmatrix -> data[Prozess][i] = Restananforderungsmatrix -> data[Prozess-1][i];
//         Betriebsmittelrestvektor[i] = Betriebsmittelrestvektor[i] + Restananforderungsmatrix -> data[Prozess][i];
//         Belegungsmatrix -> data[Prozess][i] = Belegungsmatrix -> data[Prozess-1][i];
//       }
//       rows --;
//     }
//     if(rows == 0){
//       //safe
//       status = 1;
//     }
// }
