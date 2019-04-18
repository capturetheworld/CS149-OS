#include <stdio.h>
#include <stdlib.h> /* strtoll */ 
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100



int main (){

	int input_char1 [20];
	input_char1[0] = 5;
	input_char1[1] = 8;
	input_char1[2] = 12;

	int input_char2 [20];
	input_char1[0] = 14;
	input_char1[1] = 22;
	input_char1[2] = 30;

	


	pid = fork();

	if(pid > 0){ //parent


	}
	else if(pid <0){
		printf("error");
	}
	else { //child

		while(input_char1 != '\0'){

		}


	}







}