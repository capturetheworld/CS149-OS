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

	combineArrays(factor_smaller_child1,factor_bigger_child1);


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
	combineArrays(factor_smaller_child2,factor_bigger_child2);


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

