#include "main.h"

Mtx* make_matrix(int n_rows, int n_cols) {
    Mtx* matrix = malloc(sizeof(Mtx));
    matrix -> rows = n_rows;
    matrix -> cols = n_cols;
    int** data = malloc(sizeof(int*) * n_rows);
    for(int x = 0; x < n_rows; x++){
        data[x] = calloc(n_cols, sizeof(int));
    }
    matrix -> data = data;
    return matrix;
}

int to_int(int ascii){
  return ascii - '0';
}

void copy_matrix(Mtx* matrix, int array[]) {
  for(int i = 0; i < matrix -> rows; i++){
    for(int j = 0; j < matrix -> cols; j++){
      matrix -> data[i][j] = array[matrix -> cols * i+j];
    }
  }
}

int *create_Matrix_Array(int array[], int start, int end){
  int *newarray = malloc((end - start)*sizeof(int));

  int new_array_index = 0;
  for(int i = start; i < end; ++i){
    newarray[new_array_index] = array[i];
    new_array_index++;
  }

  return newarray;
}

void print_matrix_in_file(FILE* fp, Mtx *matrix){
  for(int i = 0; i < matrix -> rows; i++){
    for(int j = 0; j < matrix -> cols; j++){
      fprintf(fp, " %d", matrix -> data[i][j]);
      if(i < matrix -> rows && j < matrix -> cols-1 ){
        fprintf(fp, " ");
      }
    }
    fprintf(fp, "\n");
  }
}
