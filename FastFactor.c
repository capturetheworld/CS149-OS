#include <stdio.h>

int main(int argc, char *argv[]){

	long long input;
printf("argc %d\n", argc);


	 for (int i=0; i < argc-1; i++)
		{
		printf("the int %d\n", i);
			if(argv[i] <= 0){
				printf("the int %d\n", argv[i]);
				printf("%s\n", "Error, only enter numbers and positive numbers greater than 0.");
				

			}


		}


}
