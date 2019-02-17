#include <stdio.h> 
#include <stdlib.h> /* strtoll */ 
#include <ctype.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100
extern long long int inputList[100]; //global input array of long long integers
extern int inputTally; //global integer of index of last element in inputList (starts at 0)
char* inputPointers[MAX];

int main(int argc, char * argv[]) {

  //c for dummies
  char *pointer;
  
  size_t n =32; //buffer size
  size_t memory_read;

  if(argc <= 1){ //only inputed program name
    error();
  }


  if(argc == 3 && argv[1] == '<'){ //only possible case for < file redirect

     inputTally = 0;//reset input tally


      pointer = (char *)malloc(buf_sz * sizeof(char));
      if (pointer == NULL){
        printf("Unable to allocate memory");
        exit(1);
      }



      while ((memory_read = getline(&pointer, &n, stdin)) != -1){
        //  memory_read = getline(&pointers, &buf_sz, stdin); {
        //printf(" The line is %s\n", pointers);

        inputPointers[inputTally] = pointer;
        inputTally++;
        pointers++;
      }


    }
    else{ //command line input

      inputTally = 0; //reset inputTally

      for (int i = 1; i<argc; ++i){ //loop through argv using argc, skipping first element

        inputPointers[inputTally] = argv[argc]; //place argv elements into argc, end at element before argc e.g. (0[X]1[X]2[] argc =2)
        inputTally++; //increment input tally, should have index of last elements
      }
    }

    

  


  // done with input run conversion spit out errors


  verifyInput();
  computerFactors();



}





  void verifyInput(){

      


    for(int j = 0; j<=inputTally; j++){

      int length = strlen(inputPointers[j]); //grab length of each input

      for (int k = 0; i < length; k++)
          {
            if (!isdigit(  inputPointers[j[k]] )) //should grab first char of the char in the array
              hasError(1);
          }


      convertPointer(j);




      if (inputList[j] <= 0) { //is negative or 0
        hasError(2);

    

      }

      if (inputList[j] == 1){

        hasError(3);

      }



    





          


  }

  void convertPointer(int inputIndex){

    char * invalid;


    inputList[inputIndex] =  strtol(inputPointers[inputIndex], & invalid, 10);










  }


  void hasError(int errorNum){



  }


  




void computeFactors() {

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
