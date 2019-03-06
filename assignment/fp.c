

void startPipe(int l_fd1[2], int l_fd2[2], int l_fd3[2], int l_fd4[2]) {

	// call pipe() and check  return value 
	// -1 which means fail to invoke pipe()
	// exit()
}

void readFromPipe(long long data_array[], int read_port, int size){

	// read from read_port to read from another process -- in our case, the child process.
	// In other words, the parent process reading from child process
	// store it in data_array
	// size is the size of data_array, which function should you call to find size of array?
	// 2 lines of code
}

void writeTPipe(long long data_array[], int write_port, int size){

	// write data_array to write_port to send to another process -- in our case parent process
	// In other words, the child process writing to child process
	// send the  data_array
	// size is the size of data_array, which function should you call to find size of array?
	// 2 lines of code
}

#include "util.h"



int main(int argc, char * argv[]) {



	long long combine[MAX];
	long long input_child1[] = {48, 75, 100};
	long long input_child2[] = {14, 30, 80};

// 1) Create 2 child processes
// 2) Child 1 process input_child1 and add 2 to each input
// 3) Child 2 process input_child2 and divide each input by 2
// 4) write them to parent process
// 5) Parent process read them all
// 6) print out  both input and output for each array

}
	



