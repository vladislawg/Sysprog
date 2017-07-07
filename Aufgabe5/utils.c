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

void add_Elements_to_Matrix(Mtx* Matrix, int operation, int Prozessnummer, int Betriebsmittel, int Anzahl, int index){
  printf("\nAdd Elements to Matrix\n");
  Matrix -> data[0][index] = operation;
  Matrix -> data[1][index] = Prozessnummer;
  Matrix -> data[2][index] = Betriebsmittel;
  Matrix -> data[3][index] = Anzahl;
}

void free_mtx(Mtx* Matrix){
  for(int x = 0; x < Matrix -> cols; x++){
      free(Matrix -> data[x]);
  }
  free(Matrix -> data);
  free(Matrix);
}
