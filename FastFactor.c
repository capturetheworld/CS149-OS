#include <stdio.h>
#include <stdlib.h>     /* strtoll */

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
				exit( );
		
			}
			if (!(isDigit(input)){
				printf("%s\n", "Error, only enter numerical numbers, no symbols or other characters.");
				exit( );
			}

			int finalfactors[];

















		}


}


