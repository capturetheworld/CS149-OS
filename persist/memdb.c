#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <zconf.h>
#include <string.h>
#include "memdb.h"

//Free Space Strategy is First Fit i.e. whenever we run out of memory it'll find the first available space
//large enough and just use it.

// A linked list node
struct Node
{
    int data;
    struct Node *next;
};

int main(int argc, char * argv[]) {

    if(argc <= 1){
        printf("not enough args");
        exit(-1);
    }

    if(argv[1] == (char *) 'a'){
        printf("add");
    }
    if(argv[1] == (char *) 'l'){
        printf("list");
    }
    if(argv[1] == (char *) 'd'){
        printf("delete");
    }




    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    // allocate 3 nodes in the heap
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));



    int fd=open("store.txt", O_RDONLY, S_IRUSR |  S_IWUSR);

    struct stat sb;

//    if(fstat(fd,7sb) ==-1){
//        perror("file size not found");
//    }

    char *fileinmem = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0  ); //start at the beginning






}

