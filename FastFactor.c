#include <stdio.h> 
#include <stdlib.h> /* strtoll */ 
#include <ctype.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100

  int main(int argc, char * argv[]) {

size_t n =0;

while(getline != ""){
	argv[argc] = getline(&ptr, &n, stdin);



}
    //printf("argc %d\n", argc);

    for (int i = 1; i <= argc; i++) //loop through each element

    {
      int fd[2], n, status;
      char buffer[MAX];
      pipe(fd);
      char * invalid;
      long long input = strtol(argv[i], & invalid, 10);

      //printf("the int %d\n", i);
      if (input <= 0) {
        printf("the int %s\n", argv[i]);
        printf("%s\n", "Error, only enter numbers and positive numbers greater than 0.");
        exit(0);

      }

      //typedef int bool =true;

      //int length = strlen(input);

      //  for (int i = 0; i < length; i++)
      //  {
      //    if (!isdigit(input)
      //      bool = false;
      //  }

      //if (isdigit(input) == false){
      //	printf("%llu\n", input);

      //	printf("%s\n", "Error, only enter numerical numbers, no symbols or other characters.");
      //	exit(0);
      //}

      long long finalfactors[100];
      int iterator = 0;

      int pid = fork();

      if (pid < 0) {
        printf("%s\n", "Couldn't split processes");
        exit(-1);

      }
      //S/O modified to fit with long long
      else if (pid > 0) {
        //parent

        close(fd[1]); // close write of parent
        
            write(STDOUT_FILENO, *buffer, n);

            for (int i=0; i<n; i++){
            finalfactors[iterator] = *buffer[n];
            
            iterator++;

         }
         
          
          for (long long i = ((input / 2) + 1); i <= input; i++) {
            if (input % i == 0) {
              //is a factor
              finalfactors[iterator] = i;
            }

          }

          printf("%llu", input); printf("%s\n", ":");
          for (int j = 0; j <= iterator; j++) { //print out array
            printf("%llu ", finalfactors[iterator]);
          }
        }

        else {
         // printf("%s\n", "Child process created");

          close(fd[0]); // read channel close
           long long firstfactors[100];
           int indexff = 0;

          for (long long i = 1; i <= input / 2; i++) {
            if (input % i == 0) {
              //is a factor
            	firstfactors[indexff] = i;
            	indexff++;
              

            }

          }

          

   			
          write(fd[1], firstfactors, sizeof(firstfactors)); // write things

          close(fd[1]); // Parent knows done writing

          wait(&status); // Wait for Parent to read everything and exit
          exit(0);

        }

      }

    }