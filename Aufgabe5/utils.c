#include <stdbool.h>

#include "main.h"

Mtx* make_matrix(int n_rows, int n_cols) {
    Mtx* matrix = malloc(sizeof(Mtx));
    matrix -> rows = n_rows;
    matrix -> cols = n_cols;
    int** data = calloc(n_rows,sizeof(int*));
    for(int x = 0; x < n_rows; x++){
        data[x] = calloc(n_cols, sizeof(int));
    }
    matrix -> data = data;
    return matrix;
}

void print_matrix_in_file(FILE* fp, Mtx *matrix){
  for(int j = 0; j < matrix -> cols; j++){
    for(int i = 0; i < matrix -> rows; i++){
      fprintf(fp, " %d", matrix -> data[i][j]);
      if(i < matrix -> cols && j < matrix -> rows-1 ){
        fprintf(fp, " ");
      }
    }
    fprintf(fp, "\n");
  }
}

void printMtx(Mtx *Matrix){
  printf("printMtx\n");
  for(int j = 0; j < Matrix -> cols; j++){
    for(int i = 0; i < Matrix -> rows; i++){
      printf("%d ", Matrix -> data[i][j]);
    }
    printf("\n");
  }
}

bool check_matrix(Mtx* Matrix){
  int counter = 0;

  for(int j = 0; j < Matrix -> cols; j++){
    for(int i = 0; i < Matrix -> rows; i++){
      if(Matrix -> data[i][j] == 0){
        counter ++;
      }
    }
  }

  if(counter == (Matrix -> rows * Matrix -> cols)) return false;

  return true;
}

void print_array(int *array, int array_len){
  for(int i = 0; i < array_len; i++){
    printf("%d", array[i]);
  }
  printf("\n");
}

void add_Elements_to_Matrix(Mtx* Matrix, int operation, int Prozessnummer, int Betriebsmittel, int Anzahl, int index){
  //
  printf("\nAdd Elements to Matrix\n");
  Matrix -> data[0][index] = operation;
  Matrix -> data[1][index] = Prozessnummer;
  Matrix -> data[2][index] = Betriebsmittel;
  Matrix -> data[3][index] = Anzahl;
}

void free_mtx(Mtx* Matrix){
  for(int x = 0; x < Matrix -> rows; x++){
      free(Matrix -> data[x]);
  }
  free(Matrix -> data);
  free(Matrix);
}

void printfile(FILE *fp, Mtx* Restananforderungsmatrix, int *array, int rows, int operation, int Prozesse_no, int Betriebsmittel, int Anzahl){

  if(operation == 1){
    fprintf(fp, "Operation: %c %d %d %d\n", 'A', Prozesse_no, Betriebsmittel, Anzahl);
  }else if(operation == 0){
    fprintf(fp, "Operation: %c %d %d %d\n", 'R', Prozesse_no, Betriebsmittel, Anzahl);
  }

  fprintf(fp, "\nRestanforderungen:\n");
  print_matrix_in_file(fp, Restananforderungsmatrix);

  fprintf(fp, "\nf:");
  for(int i = 0; i < rows; i++){
    fprintf(fp, "  %d", array[i]);
  }
  fprintf(fp, "\n\n");
}

int *calc_free_array(Mtx* Matrix, int verfuegbar[]){
  int *array = calloc(Matrix -> rows, sizeof(int*));
  for(int j = 0; j < Matrix -> rows; j++){
    array[j] = verfuegbar[j];
  }
  for(int j = 0; j < Matrix -> rows; j++){
   for(int i = 0; i < Matrix -> cols; i++){
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
