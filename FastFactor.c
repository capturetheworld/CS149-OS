#include <stdio.h> 
#include <stdlib.h> /* strtoll */ 
#include <ctype.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define MAX 100

 long long  firstfactors[MAX];
 long long  finalfactors[MAX];
 int final_iterator =0;
 int first_iterator =0;
 long long prime[MAX] ={2,3, 5, 7, 9, 11, 13};

int isFactor(long long l_input, int divider){
        	if (l_input % divider == 0) { //is a factor
			return divider;
        		//finalfactors[iterator] = index;
        	}
		else
			return 0;

}
void  fillChild(long long l_input[]){
int index;
	for (index=0; index<5; index++){
		l_input[index] = index+5;
	}
	for (index=0; index<5; index++){
		printf("fillChild: child_array has %llu\n",l_input[index]);
	}
	l_input[index] = 0;

}
void  fillParent(long long l_input[]){
int index=0;
	for (index=0; index<5; index++){
		l_input[index] = index;
	}
	for (index=0; index<5; index++){
		printf("fillParent: parent_array has %llu\n",l_input[index]);
	}
	l_input[index] = 0;

}
void  printLLArray(long long l_input[],char * des){
	int index=0;
	while (index<5){
		printf("\n***%s index %d has %llu\n",des,index,l_input[index]);
		index++;
	}


}



void   finalRangeFactors(long long l_input, long long l_finalfactors[]){
	long long tmp_ll;
        for (long long index = ((l_input / 2) + 1); index <= l_input; index++) {
		tmp_ll = isFactor(l_input,index);	
		if (tmp_ll){
			l_finalfactors[final_iterator] = tmp_ll;
        		printf("\n factor found in finalRangeFactor  parent pid %llu\n", tmp_ll);
        	}
        }
}


void   firstRangeFactors(long long l_input){
	long long tmp_ll;
	long long upperLimit = l_input/2;

        for ( int long long index = 1; index <= upperLimit; index++) {

		tmp_ll = isFactor(l_input,index);	

		if (tmp_ll){
			firstfactors[first_iterator] = tmp_ll;
        		printf("\n factor in firstRangeFactor %llu\n", tmp_ll);
        	}
        }
}



void printArray(char** testArray, char *desc){

	int l_index =0;

	while (testArray[l_index] != NULL){
		printf("\n%s index %d is %s\n",desc,l_index, testArray[l_index]);
		l_index++;
	}
}

void startPipe(int l_fd1[2], int l_fd2[2]){
 	if (pipe(l_fd1) == -1){
	 	fprintf(stderr,"Pipe Failed");
		exit(0);
	}
 	if (pipe(l_fd2) == -1){
	 	fprintf(stderr,"Pipe Failed");
		exit(0);
	}

}
		
int main(int argc, char * argv[]) {

	char *pointers;
	char *pointers_array[MAX];
	int fd1[2], fd2[2];

	size_t buf_sz =32;
	size_t memory_read;
	int count=0;
	int index=1;
	char * pointers_index;

	printf("argc is %d\n",argc);

	if (argc ==1) {
	pointers = (char *)malloc(buf_sz * sizeof(char));
	if (pointers == NULL){
		printf("Unable to allocate memory");
		exit(1);
	}

	
	while (( getline(&pointers, &buf_sz, stdin)) != -1){

		pointers_array[count] = pointers;
		count++;
		pointers++;
	pointers = (char *)malloc(buf_sz * sizeof(char));
	}
		pointers_array[count] = NULL;
	} // finish reading the data iniput file thru <
	else{

		printf("argc is %d",argc);
		while (index < argc) {
		pointers_array[count] = argv[index];
		count++;
		printf("argv index %d is %s\n", index, argv[index]);
		index++;
		pointers_array[count] = NULL;
		}
	}


	printArray(pointers_array,"\nTesting pointers_array"); //debug

	printf("argc %s\n", "i am here 100");

		char debug_input_str[] = "The first part of string";
		char debug_fixed_str[] = "forgeeks.org";
    for (int i = 0; i < count; i++) //loop through each element

    {
    	int  n, status;
    	static long long  firstfactors[MAX];
    	static long long  finalfactors[MAX];
    	char * invalid;

    	//pipe(fd);
	startPipe(fd1,fd2);

    	long long input = strtol(pointers_array[i], &invalid, 10);

      printf("\nThe input after strtol is %llu\n", input);
    	if (input <= 0) {
    		printf("%s\n", "Error, only enter numbers and positive numbers greater than 0.");
    		exit(0);

    	}


    	fflush(stdin);

    	int pid = fork();

    	if (pid < 0) {
    		printf("argc %s\n", "i am here 11");
    		printf("%s\n", "Couldn't split processes");
    		exit(-1);

    	}
      //S/O modified to fit with long long
    	else if (pid > 0) { //paren gets the last range when input is split into 2 ranges

 	long long parent_array[MAX];

 	long long child_array_obtained[MAX];
		char debug_concat_str[100];

//	printLLArray(parent_array,"Original data in parent_array");	
fillParent(parent_array);		
printLLArray(parent_array,"printLLArray has");
//
int index;
int size;
size = sizeof(parent_array)/sizeof(parent_array[0]);
printf("\nsize is %d\n",size);
		close(fd1[0]); // close read of first pipe
        
		write(fd1[1], debug_input_str, strlen(debug_input_str)+1);
		close(fd1[1]);

		wait(NULL);
		close(fd2[1]);
		read(fd2[0], child_array_obtained,100);
		close(fd2[0]);
printLLArray(child_array_obtained,"\n***Child_array_obtained has");

	      long long child_final_range [MAX];
        	finalRangeFactors(input,child_final_range); 
		printf("child_final_range index 0 is %llu",child_final_range[0]);
        	firstRangeFactors(input); 
        	}

      else {
	long long child_array[MAX];	
        fillChild(child_array);	
	int size = sizeof(child_array);
printLLArray(child_array,"\nChildArray in child process has");
          	close(fd1[1]); // read channel close
		char debug_concat_str[100];

		read(fd1[0], debug_concat_str,100);

		int k= strlen(debug_concat_str);
		close(fd1[0]);
		close(fd2[0]);
		write(fd2[1], child_array, size);
		close(fd2[1]);



          	//firstRangeFactors(input); 
          }


      }


}
