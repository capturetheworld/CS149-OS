#include "util.h"



 long long  firstfactors[MAX];
 long long  finalfactors[MAX];
 int final_iterator =0;
 int first_iterator =0;
 long long prime[MAX] ={2,3, 5, 7, 9, 11, 13};


	long long child1_array[MAX];	
	long long child2_array[MAX];	
	long long child3_array[MAX];	

		
int main(int argc, char * argv[]) {

	char *pointers;
	char *pointers_array[MAX];
	int fd1[2], fd2[2], fd3[2], fd4[2];

	size_t buf_sz =32;
//	size_t memory_read;
	int count=0;
	int index=1;
//	char * pointers_index;

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
	long long factor_smaller_parent[MAX];
	long long factor_smaller_child1[MAX];
	long long factor_smaller_child2[MAX];
	long long factor_bigger_parent[MAX];
	long long factor_bigger_child1[MAX];
	long long factor_bigger_child2[MAX];
	long long input;
	
	input = 9412132121238; // teacher 's test
	input = 94121324123883888; // a good number to factor upper bound is 44538
	input = 542649999999999998; // boundary exceeded
	input = 9412132121238; // teacher 's test
	input = 48;
	long long bound_range [3];
	long long lower_bound, upper_bound;


    for (int i = 0; i < count; i++) //loop through each element

    {
    	char * invalid;

	startPipe(fd1,fd2,fd3,fd4);



	getTriRanges(input, bound_range) ;


	input = strtol(pointers_array[i],&invalid,10);

      printf("\nThe input after strtol is %llu\n", input);
        

    	if (input <= 0) {
    		printf("%s\n", "Error, only enter numbers and positive numbers greater than 0.");
    		exit(0);
    	}

    	fflush(stdin);

    	int pid = fork();

    	if (pid < 0) {
    		printf("%s\n", "Couldn't split processes");
    		exit(-1);

    	}
	else if (pid ==0) { // first child
// first child process


	lower_bound =bound_range[0] +1;
	upper_bound =bound_range[1];
	getFactors(input,factor_smaller_child1, factor_bigger_child1,lower_bound,upper_bound);

	combineSmallBig(factor_smaller_child1,factor_bigger_child1);


//        fillChild(child1_array);	
//        /*
/*	int size = sizeof(child1_array);
	printLLArray(child1_array,"\nChildArray in child process has");
	*/

int size = sizeof(factor_smaller_child1);
	 writeToPipe(factor_smaller_child1, fd2[1],size);


          	//firstRangeFactors(input); 
          }
    	else if (pid > 0) { //parent  starting another process

		int pid2 = fork();

		if (pid2 == 0){  // 2nd child
// 2nd child process





	lower_bound =bound_range[1] +1;
	upper_bound =bound_range[2];
	getFactors(input,factor_smaller_child2, factor_bigger_child2,lower_bound,upper_bound);
	combineSmallBig(factor_smaller_child2,factor_bigger_child2);


int size = sizeof(factor_smaller_child2);
	 writeToPipe(factor_smaller_child2,fd4[1],size);
	 //close(fd4[1]);

          }

	   else { 
// parent 

 		long long child_obtained[MAX];


		lower_bound =2;
		upper_bound =bound_range[0];
		getFactors(input,factor_smaller_parent, factor_bigger_parent,lower_bound,upper_bound);


		wait(NULL);
// read from first child

 		int size = sizeof(child_obtained);
	 		readFromPipe(child_obtained, fd2[0], size);
	 		extractArray(factor_smaller_parent, factor_bigger_parent,child_obtained);

//printLLArray(child_obtained,"\n***Child_obtained has");

// read from 2nd child
// debug
// /
  		size = sizeof(child_obtained);
	 		readFromPipe(child_obtained, fd4[0], size);

	 extractArray(factor_smaller_parent, factor_bigger_parent,child_obtained);
printLLArray(factor_smaller_parent,"\n++++factor_smaller_parent");
printLLArray(factor_bigger_parent,"\n++++factor_bigger_parent");

          }


      }

 }
}
