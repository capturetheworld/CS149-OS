
#include "util.h"

/** Instruction: Assignment 8: complie like "gcc -o  forpipe
 * Please note I have used a util.h as header file
 * 1)use getline to read a command line option 48,54 , check for user error like no input 
 * 1a) Convert the string to long long
 * 2) put it in a long long array long long data[MAX}
 * 2a) Create a function startPipe() to check if pipe() starts successful, otherwise print stderr error and exit(EXIT_FAILURE);
 *
 * 3) use fork() to start 2 processes: parent and child 
 * 4) check pid<0; pid==0 means child ; pid>0 meand parent process 
 * 5) fd[0] where the index 0 stands for reading pipe
 * 6) fd[1] where the index 1 stands for writing pipe
 * 7) In child process  write a function with argument like void addOne(long long l_input],long long l_output[]) to loop thru data array and increment each value by 1.  Call the function with addOne(data,result); * store the new value in  long long result[MAX];
 *
 * 8)write(port, input, size) to write into the pipe. port refers to fd[1], input refers to in your case  reslut[], size is sizeof(data)
 * 9) In parent process read pipe by read(read_port, input, size). In your program, create a new long long data_read[MAX] as input,
 * read_port is fd[0], size is sizeof(data_read);
 * 10) print out the array data_read. It should have the data from nums  incremented by 1. So if nums has 12 the data_read should have 13 etc.
 * */



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
