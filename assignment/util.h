#include <stdio.h> 
#include <stdlib.h> /* strtoll */ 
#include <ctype.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#define MAX 1000
#define DELM  1




void combineSmallBig(long long factor_smaller_child[],long long factor_bigger_child[]);

void	 extractArray(long long factor_smaller_parent[], long long factor_bigger_parent[],long long child_obtained[]);
void getTriRanges(long long input, long long l_ranges[2]); 



void getFactors( long long input,long long l_factor_smaller[],long long l_factor_bigger[],long long lower_bound,long long upper_bound); 



void writeToPipe(long long data_array[], int write_port,int size);


void readFromPipe(long long data_array[], int read_port, int size);

int isFactor(long long l_input, int divider);


void  fillChild2(long long l_input[]);
void  fillChild(long long l_input[]);

void  fillParent(long long l_input[]);

void  printLLArray(long long l_input[],char * des);


void   finalRangeFactors(long long l_input, long long l_finalfactors[],int final_iterator);



void   firstRangeFactors(long long l_input, long long firstfactors[],int first_iterator);




void printArray(char** testArray, char *desc);


void startPipe(int l_fd1[2], int l_fd2[2], int l_fd3[2], int l_fd4[2]);



		


