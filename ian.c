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

void convertString(int inputIndex){

char * invalid;

long long int temp =  strtoll(inputPointers[inputIndex], &invalid, 10);

if(invalid == NULL){

 inputList[inputIndex] =  temp;
}
else {

 hasError(1);
}

}











void verifyInput(){

if(inputTally ==0){
 printf("we are here 2 \n");
 hasError(4);
}


printf("\nverifyInputv erifinput pointers here %s  \n", inputPointers[0]);
     int length = strlen(inputPointers[0]); //grab length of each input
     printf("\nlength is %d\n",length);


for(int j = 0; j<inputTally; j++){

 printf("\ninput tally is %d \n", inputTally);


printf("\nverifyInput index is %d input pointers here %s  \n",j, inputPointers[j]);

     //int length = strlen(inputPointers[j]); //grab length of each input



     if(length ==0){
       printf("input pointers %s  \n", inputPointers[j]);

      hasError(4);
     }
     else{

    //  convertString(j);


     }

     // printf("\n length is %d", length);

     //   for (int k = 0; k < length; k++)
     //        {
     //         printf("\nVALUE IN STRING LEN %c \n", inputPointers[j][k]);

     //       }




 }

}









void computeFactors() {

for(int i = 0; i<inputTally; i++){

 printf("\n The following inputs: %llu", inputList[i]);

}

}



int main(int argc, char * argv[]) {

char *storage = NULL;
size_t n =0;



  if(argc == 1){ //only possible case for < file redirect

     inputTally = 0;//reset input tally


     while (getline(&storage, &n, stdin) != -1){

      printf("\n The pointer to be inputted is %s", storage);


      inputPointers[inputTally] = storage;

      printf("input TALLY IN MAIN METHOD %s  \n", inputPointers[inputTally]);


     // printf("\n The inputted value is %s", inputPointers[inputTally]);
      inputTally++;
      

      
     }

     printf("\ninput tally main is %d", inputTally);
     
verifyInput();


 }
    else{ //command line input



      inputTally = 0; //reset inputTally

      for (int i = 1; i<argc; ++i){ //loop through argv using argc, skipping first element

        inputPointers[inputTally] = argv[argc]; //place argv elements into argc, end at element before argc e.g. (0[X]1[X]2[] argc =2)
        inputTally++; //increment input tally, should have index of last elements
    }

    printf("\ninput tally main is %d", inputTally);


}






  // done with input run conversion spit out errors


//verifyInput();

//  computeFactors();




}




