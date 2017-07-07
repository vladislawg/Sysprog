#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _Mtx{
  int rows;
  int cols;
  int **data;
}Mtx;

typedef enum _State{SAFE, UNSAFE, UNDEFINED} Status;

void copy_matrix(Mtx* matrix, int array[]);

void print_matrix_in_file(FILE* fp, Mtx *matrix);

void free_mtx(Mtx* Matrix);

void printMtx(Mtx *Matrix);

void add_Elements_to_Matrix(Mtx* Matrix, int operation, int Prozessnummer, int Betirebsmittel, int Anzahl, int index);

int *create_Matrix_Array(int array[], int start, int end);

int *calc_free_array(Mtx* Matrix, int verfuegbar[]);

Mtx* make_matrix(int n_rows, int n_cols);

Mtx* calc_Restanforderung(Mtx* Gesamtanforderung, Mtx* Belegungsmatrix, int rows, int cols);

Status bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int rows, int cols, int *Betriebsmittelrestvektor, Mtx* Restananforderungsmatrix );

bool check_matrix(Mtx* Matrix);

void deadlock_avoidance(FILE* fp, Mtx *Restananforderungsmatrix, Mtx* Operation_Matrix,  int *frei, int rows, int cols);

void print_array(int *array, int array_len);

void printfile(FILE *fp, Mtx* Restananforderungsmatrix, int *array, int rows, int operation, int Prozesse_no, int Betriebsmittel, int Anzahl);
