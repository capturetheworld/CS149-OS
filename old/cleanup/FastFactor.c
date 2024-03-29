#include <stdio.h>
#include <stdlib.h> /* strtoll */ 
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100


/////////////////////////////////////////////////////////////////////////
// Global Variables

long long int inputList[100]; //global input array of long long integers
int inputTally;  //global integer counter
char* inputPointers[MAX];



/////////////////////////////////////////////////////////////////////////







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
	long long int temp = strtoll(inputPointers[inputIndex], &invalid, 10);

	if(invalid == NULL){
		inputList[inputIndex] = temp;

	}
	else {
		hasError(1);
	}

}

//////////////////////PRINT OUT ARRAYS////////////////////////


//////////////////////VERIFY////////////////////////
void verifyInput(){
	if(inputTally ==0){
		hasError(4);
	}

	int length = strlen(inputPointers[0]); //grab length of each input

	for(int j = 0; j<inputTally; j++){
		if(length ==0){
			printf("input pointers %s \n", inputPointers[j]);
			hasError(4);

		}
		else{
			convertString(j);
		}
	}
}

//////////////////////COMPUTE////////////////////////
void computeFactors() {
	for(int i = 0; i<inputTally; i++){
		printf("\n The following inputs: %llu", inputList[i]);
	}
}




//////////////////////MAIN////////////////////////


int main(int argc, char * argv[]) {
	char *storage = NULL;
	size_t n =0;

	if(argc == 1){ //only possible case for < file redirect
		inputTally = 0;//reset input tally

		while (getline(&storage, &n, stdin) != -1){
			printf("\n The pointer to be inputted is %s", storage);
			inputPointers[inputTally] = storage;
			inputTally++;
		}

		printf("\ninput tally main is %d", inputTally);
		verifyInput();
	}

	else{ //command line input
		inputTally = 0; //reset inputTally
		
		for (int i = 1; i<argc; ++i){  //loop through argv using argc, skipping first element
			inputPointers[inputTally] = argv[argc];  //place argv elements into argc, end at element before argc e.g. (0[X]1[X]2[] argc =2)
			inputTally++; //increment input tally, should have index of last elements
		}

		printf("\ninput tally main is %d", inputTally);
	}
}