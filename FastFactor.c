#include <stdio.h>
#include <stdlib.h>     /* strtoll */

int main(int argc, char *argv[]){

	
printf("argc %d\n", argc);


	 for (int i=1; i <= argc; i++)
		{
		char *invalid;
		long long input = strtol(argv[i], &invalid, 10);

		printf("the int %d\n", i);
			if(input <= 0){
				printf("the int %s\n", argv[i]);
				printf("%s\n", "Error, only enter numbers and positive numbers greater than 0.");
				

			}


		}


}
