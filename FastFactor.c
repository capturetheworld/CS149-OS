#include <stdio.h>
#include <stdlib.h>     /* strtoll */
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	
//printf("argc %d\n", argc);


	 for (int i=1; i <= argc; i++) //loop through each element
		{
		char *invalid;
		long long input = strtol(argv[i], &invalid, 10);

		//printf("the int %d\n", i);
			if(input <= 0){
				printf("the int %s\n", argv[i]);
				printf("%s\n", "Error, only enter numbers and positive numbers greater than 0.");
				exit(0);
		
			}


			//typedef int bool =true;

			//int length = strlen(input);

			//  for (int i = 0; i < length; i++)
			//  {
			//    if (!isdigit(input)
			//      bool = false;
			//  }

			//if (isdigit(input) == false){
			//	printf("%llu\n", input);

			//	printf("%s\n", "Error, only enter numerical numbers, no symbols or other characters.");
			//	exit(0);
			//}




			long long finalfactors[100];
			int iterator = 0;


			int pid = fork();

			if (pid<0){
				printf("%s\n", "Couldn't split processes");
				exit(-1);


			}

			else if(pid>0){
				//parent

				for(long long i=1; i<=input/2; i++){
					if(input%i ==0){
						//is a factor
						finalfactors[iterator] = i;
					}
				}




				printf("%llu", input);
				printf("%s\n", ":");
				for(int j = 0; j <=iterator; j++){//print out array
     				 printf("%llu ", finalfactors[iterator]);
     				}
			}

			else{
				printf("%s\n", "Child process created");

			}

















		}


}


