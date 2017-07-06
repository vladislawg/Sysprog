
Anforderung[i][j]
Belegt[i][j]
Restanforderung[i][j]

verfügbar[i][j]
frei[i][j]

operation[i][j]


int restanforderung ( Anforderung[][], Belegt[][]){

for ( i = 0; i < numberOfProcesses; i++ ){           //vertikel
    for ( j = 0; j < numberOfRessources; j++ ){      //horizontals
            Restanforderung[i][j] = Anforderung[i][j] - Belegt[i][j];
    }
    
    printf("Restanforderung:\n");
        for ( i = 0; i < numberOfProcesses; i++ ){           
            for ( j = 0; j < numberOfRessources; j++ ){     
                printf("Restanforderung[i][j]\n\n");
            }
        }           
    
}


int frei ( Restanforderung[][], verfügbar[][]){

    for ( i = 0; i < numberOfBetriebsmittel; i++ ){     //vertikal durch die Betriebsmittel    
        if ( verfügbar[i][j] - Restanforderung[i][j] >= 0 ){  //genug BM vorhanden?
            frei[i][j] = verfügbar[i][j] - Restanforderung[i][j];
        }else{      // nicht genug BM frei zum beenden des Prozesses
            frei[i][j] = 0;
            status = unsafe;
    }

    if ( mode = unspecific ){   // all fine
        status = save;
    }

    for ( i = 0; i < numberOfBetriebsmittel; i++ ){           
        printf("frei: verfügbar[i][j]");
    }
    printf("\n\n");
    
    
    if( mode == save ){
        printf("SICHER\n");             //printet den modus
    }else{
        printf("UNSICHER\n");
    }
}

int frei2 ( Restanforderung[][], verfügbar[][]){  // freie für d)

//     for ( i = 0; i < numberOfBetriebsmittel; i++ ){     //vertikal durch die Betriebsmittel    
//         if ( verfügbar[i][j] - Restanforderung[i][j] >= 0 ){  //genug BM vorhanden?
//             frei[i][j] = verfügbar[i][j] - Restanforderung[i][j];
//         }else{      // nicht genug BM frei zum beenden des Prozesses
//             frei[i][j] = 0;
//             status = unsafe;
//     }
// 
//     if ( mode = unspecific ){   // all fine
//         status = save;
//     }
// 
//     for ( i = 0; i < numberOfBetriebsmittel; i++ ){           
//         printf("frei: verfügbar[i][j]");
//     }
//     printf("\n\n");
//     
//     
//     if( mode == save ){
//         printf("SICHER\n");             //printet den modus
//     }else{
//         printf("UNSICHER\n");
//     }
}



int operation ( Operation[][] ){
        
    for ( i = 0; i < numberOfBetriebsmittel+1; i++ ){ //+1 wegen A oder R           
        printf("operation[i][j]");
    }
    printf("\n\n");


    if( operation[0][j] == A ){
                restanforderung();
                frei();
    }else{ //operation = R
                release();
                frei2();
    }
}
    
    
int release ( )    {

for ( i = 0; i < numberOfProcesses; i++ ){           //vertikel
    for ( j = 0; j < numberOfRessources; j++ ){      //horizontals
            Restanforderung[i][j] =     ??
    }
    
    printf("Restanforderung:\n");
        for ( i = 0; i < numberOfProcesses; i++ ){           
            for ( j = 0; j < numberOfRessources; j++ ){     
                printf("Restanforderung[i][j]\n\n");
            }
        }    
}
        
        
        
int main(){

        printf("Prozesse: %d / Betriebsmittel: %d\n\n", numberOfProcesses, numberOfBetriebsmittel);
        
        printf("Gesamtanforderung:\n");
        for ( i = 0; i < numberOfProcesses; i++ ){           
            for ( j = 0; j < numberOfRessources; j++ ){      
                printf("Anforderung[i][j]\n\n");
            }       
        }
        printf("Belegung:\n");
        for ( i = 0; i < numberOfProcesses; i++ ){           
            for ( j = 0; j < numberOfRessources; j++ ){     
                printf("Belegt[i][j]\n\n");
            }
        }
        

        for ( i = 0; i < numberOfBetriebsmittel; i++ ){           
            printf("verfügbar: verfügbar[i][j]\n\n");
        }

        
        restanforderung();
        
        frei();
        
        for ( j = 0; j < numberOfOperations; j++){
            operation( Operation[][j] );
        }
            
}        
        
