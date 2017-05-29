#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

#include "main.h"
#include "utils.h"
#include "bruteforce.h"

#define BILLION 1000000000L


int main(int argc, char** argv)
{
    // Process Commandline arguments
    if(argc != 5 || !strcmp("-h", argv[1]) || !strcmp("--help", argv[1]))
    {
        printf("\nUsage: %s <sha256 hash> <process count> <min> <max>\n\n", argv[0]);
        printf("\t\t<sha256 hash>  \t = 64 character long hex character sequence\n");
        printf("\t\t<process count>\t = Number of processes to split workload to\n");
        printf("\t\t<min>          \t = lowest number of cleartext length\n");
        printf("\t\t<max>          \t = highest number of cleartext length\n\n");
        return 0;
    }

    process_count = atoi(argv[2]);
    min_password_length = atoi(argv[3]);
    max_password_length = atoi(argv[4]);

	/* CRACK THE FOLLOWING SHA256 HASH:

		fab6b3381ec4dc44084b23206f3a1e7ea3b2fb795a0e5e01e42f6cff11d4c175
	*/

  pid_t pid = 0;
  char** work = malloc((process_count+1)*sizeof(char*));
  split_work(work, (26/process_count));
  int index = 0;

  //Erstellen von Prozessen
  for(int i = 0; i < process_count; i++){
    pid = fork();
    if(pid == 0){
      //kinderprozess
      index = i;
      break;
    }
  }

  if(pid == 0){
    //kinderprozess
    //Soll bruteforce auf einen bestimmten bereich ausführen
    char *pw = NULL;
  //  char* hash = malloc(strlen(argv[1])*sizeof(char));
    char* hash = argv[1];
    char* start = work[index];
    char* end = work[index+1];
    printf("Index: %d, start: %s, end: %s\n", index, start, end);

    struct timespec starttime;
    struct timespec stoptime;
    clock_gettime(CLOCK_REALTIME, &starttime);

    pw = brute(hash, start, end);
    if(pw != NULL){
      printf("The Passwort is: %s \n", pw);

      clock_gettime(CLOCK_REALTIME, &stoptime);
    	double accnum = (stoptime.tv_sec - starttime.tv_sec)+ (double)(stoptime.tv_nsec - starttime.tv_nsec)/BILLION;
    	printf("Dauer: %lf nsec\n", accnum);

      for(int i=0; i < process_count+1; i++)
      {
          free(work[i]);
          work[i] = NULL;
      }

      kill(pid, SIGKILL);
    }

  }else if(pid > 0){
    for(int i = 0; i < process_count; i++){
      wait(0);
  }
    printf("Passwort not found\n");
  }else{
    printf("Error in Process\n");
    exit(0);
  }

}
