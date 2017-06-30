#include <stdlib.h>
#include <stdio.h>

typedef struct _Mtx{
  int rows;
  int cols;
  int **data;
}Mtx;


Mtx* make_matrix(int n_rows, int n_cols);
void copy_matrix(Mtx* matrix, int array[]);
int *create_Matrix_Array(int array[], int start, int end);
void print_matrix_in_file(FILE* fp, Mtx *matrix);
int to_int(int ascii);
void free_mtx(Mtx* Matrix);
void bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int verfuegbar[], int Betriebsmittel);
