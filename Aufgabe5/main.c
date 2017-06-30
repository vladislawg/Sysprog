#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "main.h"

#define MAX_LEN_LINE 100

int main(int argc, char *argv[]){

  if(argc != 3){
    printf("Use: [Input_File.txt] [Output_File.txt]\n");
    exit(1);
  }

  FILE *input_file;

  //oeffnen im Lesemodus
  input_file = fopen(argv[1], "r");

//Read an Parse input File
  int Prozesse;
  int Betriebsmittel;
  Mtx *Gesamtanforderung = NULL;
  Mtx *Belegungsmatrix = NULL;
  int *verfuegbar = NULL;
  if(input_file == NULL){
    printf("Could not open input file!\n");
    exit(1);
  }else{
    fscanf(input_file, "%d\n%d", &Prozesse, &Betriebsmittel);
    Gesamtanforderung = make_matrix(Prozesse, Betriebsmittel);
    Belegungsmatrix = make_matrix(Prozesse, Betriebsmittel);

    int temp;
    int array[(2*(Prozesse*Betriebsmittel)+Betriebsmittel)];
    int count = 0;
    int number = 0;
    while((temp = fgetc(input_file))!=EOF){
      if(isdigit(temp)){
        number = to_int(temp);
        array[count] = number;
        printf("number: %d\n", number);
        count ++;
      }
    }
    fclose(input_file);
    copy_matrix(Gesamtanforderung, create_Matrix_Array(array, 0, (Prozesse*Betriebsmittel)));
    copy_matrix(Belegungsmatrix, create_Matrix_Array(array, (Prozesse*Betriebsmittel), 2*(Prozesse*Betriebsmittel)));
    verfuegbar = create_Matrix_Array(array, 2*(Prozesse*Betriebsmittel), 2*(Prozesse*Betriebsmittel+Betriebsmittel));
    printf("laal\n");
  }

//Write output file
  FILE *output_file;
  output_file = fopen(argv[2], "w");
  if(output_file == NULL){
    printf("Could not open output file!\n");
    free_mtx(Gesamtanforderung);
    free_mtx(Belegungsmatrix);
    free(verfuegbar);
    exit(1);
  }

  fprintf(output_file, "Prozesse:  %d / Betriebsmittel:  %d\n\n", Prozesse, Betriebsmittel);
  fprintf(output_file, "Gesamtanforderungen:\n");
  print_matrix_in_file(output_file, Gesamtanforderung);
  fprintf(output_file, "\n");
  fprintf(output_file, "Belegungen:\n");
  print_matrix_in_file(output_file, Belegungsmatrix);
  fprintf(output_file, "\n");
  fprintf(output_file, "verfügbar:");
  for(int i = 0; i < Betriebsmittel; i++){
    fprintf(output_file, "  %d",verfuegbar[i]);
  }
  fprintf(output_file, "\n");
  fclose(output_file);

  bankieralgo(Gesamtanforderung, Belegungsmatrix, verfuegbar, Betriebsmittel);

  free_mtx(Gesamtanforderung);
  free_mtx(Belegungsmatrix);
  free(verfuegbar);

  return 0;
}
