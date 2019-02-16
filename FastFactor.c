#include <stdio.h> 
#include <stdlib.h> /* strtoll */ 
#include <ctype.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100

int main(int argc, char * argv[]) {

	char *pointers;
	char *pointers_array[MAX];

	size_t buf_sz =32;
	size_t memory_read;

	pointers = (char *)malloc(buf_sz * sizeof(char));
	if (pointers == NULL){
		printf("Unable to allocate memory");
		exit(1);
	}

	

	while ((memory_read = getline(&pointers, &buf_sz, stdin)) != -1){
  //	memory_read = getline(&pointers, &buf_sz, stdin); {
		printf(" The line is %s\n", pointers);

		argv[argc] = pointers;
		argc++;
		pointers++;
	}
  	//	printf("argc %s\n", "i am here 0");


	//printf(" The line is %s\n", pointers);

    //printf("argc %s\n", pointers);
	printf("argc %s\n", "i am here 100");

    for (int i = 1; i < argc; i++) //loop through each element
    	

    {
    	printf("argc %s\n", "i am here 9");
    	int fd[2], n, status;
    	char firstfactors[MAX];

    	pipe(fd);
    	char * invalid;
    	long long input = strtol(argv[i], & invalid, 10);

      //printf("the int %d\n", i);
    	if (input <= 0) {
    		printf("argc %s\n", "i am here 10");
    		printf("the int %s\n", argv[i]);
    		printf("%s\n", "Error, only enter numbers and positive numbers greater than 0.");
    		exit(0);

    	}



    	long long finalfactors[100];
    	int iterator = 0;
    	fflush(stdin);
    	int pid = fork();

    	if (pid < 0) {
    		printf("argc %s\n", "i am here 11");
    		printf("%s\n", "Couldn't split processes");
    		exit(-1);

    	}
      //S/O modified to fit with long long
    	else if (pid > 0) {
    		printf("argc %s\n", "i am here 12");
        //parent

        close(fd[1]); // close write of parent
        
        read(fd[0], firstfactors, sizeof(firstfactors));

        for (int i=0; i<n; i++){
        	finalfactors[iterator] = firstfactors[n];
        	printf("argc %s\n", "i am here 3");

        	iterator++;

        }


          //add the second half of the factors here:
        for (long long i = ((input / 2) + 1); i <= input; i++) {
        	printf("argc %s\n", "i am here 6");
        	if (input % i == 0) {
              //is a factor
        		finalfactors[iterator] = i;
        		printf("argc %s\n", "i am here 1");
        	}

        }

        printf("%llu", input); printf("%s\n", ":");
          for (int j = 0; j <= iterator; j++) { //print out array
          	printf("%llu ", finalfactors[iterator]);
          	printf("argc %s\n", "i am here 2");
          }

          exit(0);
      }


//////////////////////////////////////////////////////////////////////////////////////////
      else {
         // printf("%s\n", "Child process created");

          close(fd[0]); // read channel close
          long long int firstfactors[100];
          int indexff = 0;

          for (long long i = 1; i <= (input / 2); i++) {
          	printf("argc %s\n", "i am here 8");
            printf("INPUT IS %llu", input);
          	if (input % i == 0) {
              //is a factor
          		firstfactors[indexff] = i;
          		indexff++;
          		printf("argc %s\n", "i am here 4");


          	}

          }

          


          write(fd[1], firstfactors, sizeof(firstfactors)); // write things

          close(fd[1]); // Parent knows done writing

          wait(&status); // Wait for Parent to read everything and exit
          exit(0);

      }

  }

}
