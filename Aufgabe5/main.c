#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "main.h"

int main(int argc, char *argv[]){
  //rows = Betirebsmittel
  //cols = Prozesse

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
  Mtx *Matrix = NULL;
  int linecounter = 0;

  if(input_file == NULL){
    printf("Could not open input file!\n");
    exit(1);
  }else{
    fscanf(input_file, "%2d\n%2d", &Prozesse, &Betriebsmittel);

    if(Prozesse == 0 || Betriebsmittel == 0) exit(1);

    Gesamtanforderung = make_matrix(Betriebsmittel, Prozesse);
    Belegungsmatrix = make_matrix(Betriebsmittel, Prozesse);
    verfuegbar = calloc(Betriebsmittel, sizeof(int));

    printf("%d %d\n", Prozesse, Betriebsmittel);

    for(int j = 0; j < Prozesse; j++){
      for(int i = 0; i < Betriebsmittel; i++){
        fscanf(input_file, "%2d", &Gesamtanforderung -> data[i][j]);
      }
    }

    printMtx(Gesamtanforderung);


    for(int j = 0; j < Prozesse; j++){
      for(int i = 0; i < Betriebsmittel; i++){
        fscanf(input_file, "%2d", &Belegungsmatrix -> data[i][j]);
      }
    }

    printMtx(Belegungsmatrix);

    for(int j = 0; j < Betriebsmittel; j++){
      fscanf(input_file, "%2d", &verfuegbar[j]);
    }

    if(Gesamtanforderung == NULL || Belegungsmatrix == NULL || verfuegbar == NULL)
      exit(1);

    if(!check_matrix(Gesamtanforderung)) exit(1);
    if(!check_matrix(Belegungsmatrix)) exit(1);


    char c;
    while((c = fgetc(input_file)) != EOF){
      if(c == 'A' || c == 'R') linecounter ++;
    }
    fseek(input_file, 0, SEEK_SET); // zurucksetzen des Cursor

    int operation = 0;
    int Prozessnumber = 0;
    int Betriebs = 0;
    int Anzahl = 0;
    Matrix = make_matrix(4, linecounter); //4 steht für die 4 Spalten in der Matrix
    int i = 0;

    while((c = fgetc(input_file)) != EOF){
      if(c == 'A'){
        operation = 1;    //1 für alocate (A)
        fscanf(input_file, "%2d %2d %2d", &Prozessnumber, &Betriebs, &Anzahl);
        printf("%d %d %d %d",operation, Prozessnumber, Betriebs, Anzahl);
        add_Elements_to_Matrix(Matrix, operation, Prozessnumber, Betriebs, Anzahl, i);
        i++;
      }else if(c == 'R'){
        operation = 0;    //0 für Release (R)
        fscanf(input_file, "%2d %2d %2d", &Prozessnumber, &Betriebs, &Anzahl);
        printf("%d %d %d %d",operation, Prozessnumber, Betriebs, Anzahl);
        add_Elements_to_Matrix(Matrix, operation, Prozessnumber, Betriebs, Anzahl, i);
        i++;
      }else{
        continue;
      }
    }
    fclose(input_file);
    printMtx(Matrix);
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
  for(int i = 0; i < Betriebsmittel; i++)
    fprintf(output_file, "  %d", verfuegbar[i]);

///////////////////////////////////////////////////////////////////
  Mtx *Restananforderungsmatrix = calc_Restanforderung(Gesamtanforderung, Belegungsmatrix, Betriebsmittel, Prozesse);
  int *frei = calc_free_array(Belegungsmatrix, verfuegbar);
//////////////////////////////////////////////////////////////////


  fprintf(output_file, "\n");
  fprintf(output_file, "\n");
  fprintf(output_file, "Restanforderungen:\n");
  print_matrix_in_file(output_file, Restananforderungsmatrix);
  fprintf(output_file, "\n");
  fprintf(output_file, "frei:");
  for(int i = 0; i < Betriebsmittel; i++){
    fprintf(output_file, "  %d", frei[i]);
  }
  fprintf(output_file, "\n");

///////////////////////////////////////////////////////////////////////////
  Status state = bankieralgo(Gesamtanforderung, Belegungsmatrix, Betriebsmittel, Prozesse, calc_free_array(Belegungsmatrix, verfuegbar),  Restananforderungsmatrix);
  if(state == UNSAFE) fprintf(output_file, "\nUNSICHER\n");
  if(state == SAFE)   fprintf(output_file, "\nSICHER\n");
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
  if(linecounter > 0)
    deadlock_avoidance(output_file, Restananforderungsmatrix, Matrix, calc_free_array(Belegungsmatrix, verfuegbar), Betriebsmittel, Prozesse);
//////////////////////////////////////////////////////////////////////////

  fclose(output_file);
  free_mtx(Gesamtanforderung);
  free_mtx(Belegungsmatrix);
  free_mtx(Restananforderungsmatrix);
  free_mtx(Matrix);
  free(frei);
  free(verfuegbar);
  return 0;
}
