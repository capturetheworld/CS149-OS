#include <stdio.h> 
#include <stdlib.h> /* strtoll */ 
#include <ctype.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100
long long int inputList[100]; //global input array of long long integers
int inputTally; //global integer counter
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




  for(int j = 0; j<inputTally; j++){

    printf("\ninput tally is %d", inputTally);


    //char* toTest = inputPointers[j];
    //printf("\n totest %s", toTest);

     printf("\n*** length is  the str is %s****\n", inputPointers[j]);
     int length = strlen(inputPointers[j]); //grab length of each input

     char tmp[MAX];
  //   tmp = inputPointers[j];
     printf("\n*** length is %d the str is %s****\n", length,inputPointers[j]);

       for (int k = 0; k < length; k++)
           {
		   if(isdigit(inputPointers[j][k]) )
			   printf("the index is %d, the char is %c\n",k,inputPointers[j][k]);
      //       printf("BRACKET K %c", toTest[k]);
      //       // if (!isdigit(toTest[k])) //should grab first char of the char in the array

      //       //   hasError(1);
           }


      // convertPointer(j);




      // if (inputList[j] <= 0) { //is negative or 0
      //   hasError(2);

    

      // }

      // if (inputList[j] == 1){

      //   hasError(3);

      // }
  }
}









void computeFactors() {

  for(int i = 0; i<inputTally; i++){

   printf("\n The following inputs: %llu", inputList[i]);





 }



}



int main(int argc, char * argv[]) {

  //c for dummies
  char *pointer;
  
  size_t n =32; //buffer size
  size_t memory_read;



  if(argc == 1 || argv[1] == NULL){ //only possible case for < file redirect

int     inputTally = 0;//reset input tally


     pointer = (char *)malloc(n * sizeof(char));
     if (pointer == NULL){
      printf("Unable to allocate memory");
      exit(1);
    }

   // printf(" The line is 5");


    while ((getline(&pointer, &n, stdin)) != -1){
if(inputTally>0)
        printf("\n The pointer to be inputted is %s", pointer);


      inputPointers[inputTally] = pointer;

      printf("\n The inputted value is %s", inputPointers[inputTally]);
      inputTally++;
      pointer++;
     pointer = (char *)malloc(n * sizeof(char));
    }

    int r=0;
    while (r<inputTally){
	printf("\n^^^he string is %s\n",inputPointers[r]);
	r++;
    }

    printf("\ninput tally main is %d", inputTally);


  }
    else{ //command line input


      inputTally = 0; //reset inputTally

      for (int i = 1; i<argc; ++i){ //loop through argv using argc, skipping first element

        inputPointers[inputTally] = argv[argc]; //place argv elements into argc, end at element before argc e.g. (0[X]1[X]2[] argc =2)
        inputTally++; //increment input tally, should have index of last elements
      }

      printf("\ninput tally main is %d", inputTally);


    }
	printf("the first string is %s\n",inputPointers[0]);
int index;
for (index=0; index<strlen(inputPointers[0]);index++){

		printf("char in first string is %c\n",inputPointers[0][index]);
		}
  // done with input run conversion spit out errors


    verifyInput();

//  computeFactors();




  }




