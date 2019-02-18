#include <stdio.h> 
#include <stdlib.h> /* strtoll */ 
#include <ctype.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100
long long int inputList[100]; //global input array of long long integers
int inputTally; //global integer of index of last element in inputList (starts at 0)
char* inputPointers[MAX];

//implicit declarations

void convertPointer(int inputIndex){

    char * invalid;


    inputList[inputIndex] =  strtol(inputPointers[inputIndex], &invalid, 10);


  }


  void hasError(int errorNum){

    if(errorNum == 1){
      printf("\nFound a non-numerical number, use only numerical numbers");
      exit(-1);


    }
    else if(errorNum == 2){

      printf("\nFound a negative number or 0, use only positive numerical numbers");
      exit(-1);
      
    }
    else if(errorNum == 3){

      //printf("\nCan't factor 1, it is only itself");
      printf("\n1: 1");
      exit(-1);

      
    }

    else if(errorNum == 4){

      printf("\nNo input was detected");
      exit(-1);

      
    }
    else {

      printf("\n Unknown error occured");
      exit(-1);


    }





  }










  void verifyInput(){

      


    for(int j = 0; j<=inputTally; j++){

      char* toTest = inputPointers[j];

      int length = strlen(toTest); //grab length of each input

      for (int k = 0; k < length; k++)
          {
            printf("BRACKET K %c", toTest[k]);
            if (!isdigit(toTest[k])) //should grab first char of the char in the array

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
  }

  


  




void computeFactors() {

  for(int i = 0; i<=inputTally; i++){

     printf("\n The following inputs: %llu", inputList[i]);





  }

  	

}



int main(int argc, char * argv[]) {

  //c for dummies
  char *pointer;
  
  size_t n =32; //buffer size
  size_t memory_read;



  if(argc == 1 || argv[1] == NULL){ //only possible case for < file redirect

     inputTally = 0;//reset input tally


      pointer = (char *)malloc(n * sizeof(char));
      if (pointer == NULL){
        printf("Unable to allocate memory");
        exit(1);
      }

      printf(" The line is 5");



      while ((memory_read = getline(&pointer, &n, stdin)) != -1){
        //  memory_read = getline(&pointers, &buf_sz, stdin); {
        //printf(" The line is %s\n", pointers);
         printf(" The line is 1");

        //inputPointers[inputTally] = pointer;
        inputTally++;
        pointer++;
      }


    }
    else{ //command line input

      printf(" The line is 6");

      inputTally = 0; //reset inputTally

      for (int i = 1; i<argc; ++i){ //loop through argv using argc, skipping first element

        inputPointers[inputTally] = argv[argc]; //place argv elements into argc, end at element before argc e.g. (0[X]1[X]2[] argc =2)
        inputTally++; //increment input tally, should have index of last elements
      }
    }

    

  


  // done with input run conversion spit out errors

printf(" The line is 2");
  //verifyInput();
  printf(" The line is 3");
//  computeFactors();




}