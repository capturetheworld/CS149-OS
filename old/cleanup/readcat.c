#include "util.h"


void printStrArray(char * toPrint[],char * id ){


    
}


int main(int argc, char * argv[]){

    char *storage = NULL;
    size_t n =0;

    printf("argc is: %d\n", argc);




    long long  master_array[MAX];
    int masterindex = 0;


    if(argc == 1){


        while(getline(&storage, &n, stdin) != -1){

        	 char * end;

        	long long temp = strtoll(storage, &end, 10);

        	master_array[masterindex] = temp;

        	masterindex++;





        	
        }

      


        for (int i=(masterindex-1); i>=0; i--){
            printf("the i: %d",i);

        	printf("the number is: %llu \n", master_array[i]);


        }







    }






    






}

