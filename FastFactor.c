#include <stdio.h>

int main(int argc, char *argv[]){

	long long input;


	 for (int i=0; i < argc; i++)
		{
			if(argv[i] ==NaN || argv[i] <= 0){
				printf("Error, only enter numbers and positive numbers greater than 0. %s\n");
				exit();

			}


		}


}