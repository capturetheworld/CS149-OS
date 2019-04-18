#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "memdb.h"
#include <stdbool.h>

//Free Space Strategy is First Fit i.e. whenever we run out of memory it'll find the first available space
//large enough and just use it.



#define MAX 100
static const int GROWTH_SIZE = 1024;




/////////////////VARIABLES/////////////////

int databaseSize;
int size;

struct fhdr_s *node;



char  memory_filename[30];
int tmp_flag ; // temporary -t option

////////////////////////////////////////////


void grow(int fd) {
    munmap(node, databaseSize);

    databaseSize += GROWTH_SIZE;




    if (databaseSize > MAX_SIZE) {
        printf("Too large a database");
        exit(-1);
    }



    node = mmap(NULL, databaseSize, PROT_READ | PROT_WRITE, databaseSize, fd, 0);
}











void list() {



}




moffset_t add(int fd, char str[]) {


}



void delete(char str[]) {


}






int main(int argc, char *argv[]) {

    if (argc <=1 || argc >=4) {
        printf("USAGE: %s [-t option for temporary] memory mapping filename \n", argv[0]);
        exit(1);
    }

    else if (argc ==2) {
        printf("filename is %s\n",argv[1]);
        strcpy(memory_filename,argv[1]);
        printf("filename is %s\n",argv[1]);
        tmp_flag = MAP_SHARED;
    }
    else if (argc ==3 && strcmp(argv[1],"-t") !=0){
        printf("USAGE: %s [-t option for temporary] memory mapping filename \n", argv[0]);
    }
    else if (argc ==3 && (strcmp(argv[1],"-t") ==0)){
        tmp_flag = MAP_PRIVATE;
    }

    // From Stringfile



    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror(argv[1]);
        exit(2);
    }

    //END STRING FILE

    node = mmap(NULL, INIT_SIZE, PROT_READ | PROT_WRITE, tmp_flag, fd, 0);



    if (databaseSize == 0) {
        char* ptr = (char*) node;

        //initilize all the variables

        node->data_start = 0;
        //node->magic = FILE_MAGIC;
        // node->free_start = sizeof(*node);



        // size = INIT_SIZE;
    }



    bool running = true;


    while (running) {


        char inputArgs[MAX];
        int charCount = 0;


        while (fgets(inputArgs,MAX, stdin) == NULL) {
            fprintf(stderr, "getline failed in input loop.\n");
            exit(8);
        }


        for (int i = 0; inputArgs[i] != '\n'; i++) {
            charCount++;
        }


        char *argument;

        if (inputArgs[0] == 'a') {
            //add

            if (charCount < 2) { //error check
                printf("please enter,  a , then an argument e.g. a dogs");


            }

            argument = malloc(charCount + 1);
            for (int i = 2; i < charCount; i++) {
                argument[i - 2] = inputArgs[i];
            }
            //add a null termination
            argument[charCount] = '\0';
            add(fd, argument);

        }
        else if (inputArgs[0] == 'd') {
            argument = malloc(charCount + 1);
            for (int i = 2; i < charCount; i++) {
                argument[i - 2] = inputArgs[i];
            }
            //add a null termination
            argument[charCount] = '\0';
            delete(argument);

        }

        //copy the argument into a string



        if (inputArgs[0] == 'l') {
            //list
            list();
        }

        else {
            printf("The commands are A for add, D for delete, and L for list");
        }


    }

    return 0;
}




