#include <stdlib.h>
#include <stdio.h>

typedef struct _Mtx{
  int rows;
  int cols;
  int **data;
}Mtx;

typedef enum _State{SAFE, UNSAFE, UNDEFINED} Status;



Mtx* make_matrix(int n_rows, int n_cols);
void copy_matrix(Mtx* matrix, int array[]);
int *create_Matrix_Array(int array[], int start, int end);
void print_matrix_in_file(FILE* fp, Mtx *matrix);
int to_int(int ascii);
void free_mtx(Mtx* Matrix);
Status bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int verfuegbar[], int rows, int cols);
void printMtx(Mtx *Matrix);
void add_Elements_to_Matrix(Mtx* Matrix, int operation, int Prozessnummer, int Betirebsmittel, int Anzahl, int index);
Mtx* calc_Restanforderung(Mtx* Gesamtanforderung, Mtx* Belegungsmatrix, int rows, int cols);
