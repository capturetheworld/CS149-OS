#include <stdio.h>
#include <stdlib.h>     /* strtoll */
#include <ctype.h>

int main(int argc, char *argv[]){

	
printf("argc %d\n", argc);


	 for (int i=1; i <= argc; i++) //loop through each element
		{
		char *invalid;
		long long input = strtol(argv[i], &invalid, 10);

		printf("the int %d\n", i);
			if(input <= 0){
				printf("the int %s\n", argv[i]);
				printf("%s\n", "Error, only enter numbers and positive numbers greater than 0.");
				exit(0);
		
			}
			if (isDigit(input) == 0){
				printf("%s\n", "Error, only enter numerical numbers, no symbols or other characters.");
				exit(0);
			}

			long long finalfactors[20];

















		}


}


