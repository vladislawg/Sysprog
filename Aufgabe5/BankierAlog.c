#include "main.h"


int *frei(Mtx* Matrix, int verfuegbar[]){
  int *array = calloc(Matrix -> rows, sizeof(int)) ;
 printf("%d, %d\n", Matrix -> rows, Matrix -> cols);
   for(int i = 0; i < Matrix -> cols; i++){
     for(int j = 0; j < Matrix -> rows; j++){
       array[i] = array[i] + Matrix -> data[j][i];
     }
   }

   printf("Restvektor:");
   for(int i = 0; i < Matrix -> cols; i++){
     array[i] = verfuegbar[i] - array[i];
     printf(" %d", array[i]);
   }
   printf("\n");
   return array;
}

int *get_col(Mtx* Matrix, int index){
  int *array = calloc(Matrix -> cols, sizeof(int));
  for(int i = 0; i < Matrix -> cols; i++){
    array[i] = Matrix -> data[index][i];
  }
  return array;
}

int check_array(int *array1, int *array2, int array_len){
  for(int i = 0; i < array_len; i++){
    if(array1[i] <= array2[i]){
      printf("array: %d, rest: %d\n", array1[i], array2[i]);
      continue;
    }else if (array1[i] > array2[i]){
      printf("array: %d, rest: %d\n", array1[i], array2[i]);
      printf("return -1\n");
      return -1;
    }
  }
  return 1;
}

int find_prozess(Mtx* Anforderungsmatrix, int *Restvektor){

  int *array = NULL;
  int index = -1;

  for(int i = 0; i < Anforderungsmatrix -> rows; i++){
    //nimmt sich die i-te Zeile in der Matrix
    array = get_col(Anforderungsmatrix, i);

    //passenden Prozess suchen
    printf("index: %d\n",i);
    if(check_array(array, Restvektor, Anforderungsmatrix -> cols) < 0){
      continue;
    }else{
      index = i;
    }
  }

  return index;
}

void Update_Matrix(Mtx* Matrix, int *array, char operation){

  if(operation == 43){
    printf("plus\n");

  }else if(operation == 45){
    printf("minus\n");
  }

}

//weiß noch nicht ob man das braucht 
void update_array(int *array1, int *array2, char operation, int array_len){
  if(operation == 43){
    printf("plus\n");
    for(int i = 0; i < array_len, i++){
      array1[i] = array1[i] + array2[i];
    }
  }else if(operation == 45){
    printf("minus\n");
    for(int i = 0; i < array_len, i++){
      array1[i] = array1[i] - array2[i];
    }
  }
}


void bankieralgo(Mtx *Gesamtanforderung, Mtx *Belegungsmatrix, int verfuegbar[], int Betriebsmittel){

  //Berechne Freie Betriebsmittel
  int *Betriebsmittelrestvektor = frei(Belegungsmatrix, verfuegbar);

   for(int i = 0; i < Belegungsmatrix -> cols; i++){
     printf("%d", Betriebsmittelrestvektor[i]);
   }
   printf("\n");

   //finde passenden Parozess
   //int i = find_prozess(Gesamtanforderung, Betriebsmittelrestvektor);
   int i = 0;
  // while(1){
     i = find_prozess(Gesamtanforderung, Betriebsmittelrestvektor);
     if (i < 0){
       printf("Kein prozess gefunden\n");
      // break;
     } else {
       //zuweisen der Betirebsmittel für den Prozess --> Update Gesamtanforderung
       //Update Betriebsmittelrestvektor
       //Update Belegungsmatrix
       Update_Matrix(Gesamtanforderung, Betriebsmittelrestvektor, '+');


     }
     printf("Prozess: %d\n", i);

  // }


}
