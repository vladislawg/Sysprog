#include "main.h"

void deadlock_avoidance(FILE *fp, Mtx *Restananforderungsmatrix, Mtx* Operation_Matrix,  int *frei, int rows, int cols){

  int counter = 0;
  int operation;
  int Prozesse_no;
  int Betriebsmittel;
  int Anzahl;


  while(counter != Operation_Matrix -> cols){
    operation = Operation_Matrix -> data[0][counter];
    Prozesse_no = Operation_Matrix -> data[1][counter];
    Betriebsmittel = Operation_Matrix -> data[2][counter];
    Anzahl = Operation_Matrix -> data[3][counter];
    for(int i = 0; i < rows; i++){
      if(Restananforderungsmatrix -> data[Prozesse_no][i] > frei[i]){
        break;
      }else{
        //allocate
        if(operation == 1){
          if(Restananforderungsmatrix -> data[Betriebsmittel][Prozesse_no] >= Anzahl && frei[Betriebsmittel] >= Anzahl){
            //subtrahiere anzahl von der Restananforderungsmatrix
            Restananforderungsmatrix -> data[Betriebsmittel][Prozesse_no] = Restananforderungsmatrix -> data[Betriebsmittel][Prozesse_no] - Anzahl;
            frei[Betriebsmittel] = frei[Betriebsmittel] - Anzahl;
            printfile(fp, Restananforderungsmatrix, frei, rows, operation, Prozesse_no, Betriebsmittel, Anzahl);
          }
        }else if(operation == 0){   //release
          frei[Betriebsmittel] = frei[Betriebsmittel] + Anzahl;
          printfile(fp, Restananforderungsmatrix, frei, rows, operation, Prozesse_no, Betriebsmittel, Anzahl);
        }
      }
      break;
    }
    counter ++;
  }
  free(frei);

}
