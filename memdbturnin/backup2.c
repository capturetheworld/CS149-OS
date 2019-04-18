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

struct fhdr_s * fileheader;



char  memory_filename[30];
int tmp_flag ; // temporary -t option

////////////////////////////////////////////


void grow(int fd) {
    munmap(fileheader, databaseSize);

    databaseSize += GROWTH_SIZE;




    if (databaseSize > MAX_SIZE) {
        printf("Too large a database");
        exit(-1);
    }



    fileheader = mmap(NULL, databaseSize, PROT_READ | PROT_WRITE, databaseSize, fd, 0);
}

moffset_t find(char target[]) {
    moffset_t offset = sizeof(*fileheader);

    // If there isn't anything inputted
    if (offset == 0) {
        return 0;
    }


    // Stolen from stringfile.c
    char* ptr = (char*) fileheader;

    struct entry_s* entry_p;
    while (offset < fileheader->free_start) {
        entry_p = (struct entry_s*) (ptr + offset);

        if (entry_p->magic == ENTRY_MAGIC_DATA || entry_p->magic == ENTRY_MAGIC_FREE) {
            if (entry_p->magic == ENTRY_MAGIC_DATA && strcmp(entry_p->str, target) == 0) {
                return offset;
            }
        } else {
            // Stolen from stringfile.c
            fprintf(stderr, "Entry is not correct\n");
            exit(6);
        }


        offset += sizeof(*entry_p) + entry_p->len;
    }

    return 0;
}






void merge(struct entry_s* entryLeft_p, struct entry_s* entryRight_p) {
    struct entry_s entryFree = {
            .magic = ENTRY_MAGIC_FREE,
            .len = entryLeft_p->len + sizeof(*entryRight_p) + entryRight_p->len
    };
    memcpy(entryLeft_p, &entryFree, sizeof(entryFree));
}






void list() {
    // Stolen from stringfile.c
    char* ptr = (char*) fileheader;

    moffset_t offset = fileheader->data_start;

    // No data
    if (!offset) return;

    struct entry_s* entry_p;
    do {
        entry_p = (struct entry_s*) (ptr + offset);

        if (entry_p->magic != ENTRY_MAGIC_DATA && entry_p->magic != ENTRY_MAGIC_FREE) {
            // Stolen from stringfile.c
            fprintf(stderr, "123455 bad magic: not an entry\n");
            exit(6);
        } else if (entry_p->magic == ENTRY_MAGIC_FREE) {
            fprintf(stderr, "bad magic: some entry points to an empty entry\n");
            exit(6);
        }

        printf("%s\n", entry_p->str);


        offset = entry_p->next;
    } while (entry_p->next);



}


void setPointer(struct entry_s* entry_p, moffset_t entryLocation) {
    // Stolen from stringfile.c
    char* ptr = (char*) fileheader;


    moffset_t offset = fileheader->data_start;
    struct entry_s* entryIndex_p;

    do {
        entryIndex_p = (struct entry_s*) (ptr + offset);

        if (entryIndex_p->magic != ENTRY_MAGIC_DATA && entryIndex_p->magic != ENTRY_MAGIC_FREE) {
            // Stolen from stringfile.c
            fprintf(stderr, "bad magic: not an entry\n");
            exit(6);
        } else if (entryIndex_p->magic == ENTRY_MAGIC_FREE) {
            fprintf(stderr, "bad magic: some entry points to an empty entry\n");
            exit(6);
        }

        if (offset == fileheader->data_start && strcmp(entryIndex_p->str, entry_p->str) > 0) {
            // Entry should be new start
            entry_p->next = offset;
            fileheader->data_start = entryLocation;
            return;
        } else if (entryIndex_p->next) {
            struct entry_s* nextEntry_p = (struct entry_s*) (ptr + entryIndex_p->next);
            if (
                    nextEntry_p->magic == ENTRY_MAGIC_DATA
                    && strcmp(nextEntry_p->str, entry_p->str) > 0
                    ) {
                // Entry should be somewhere in the middle
                entry_p->next = entryIndex_p->next;
                entryIndex_p->next = entryLocation;
                return;
            }
        } else {
            // Entry should be at end
            entryIndex_p->next = entryLocation;
            return;
        }


        offset = entryIndex_p->next;
    } while (offset);

    // Defaults to 0 if we can't find a string that goes after
    entry_p->next = 0;
}


moffset_t add(int fd, char str[]) {

    // Already exists
    if (find(str)) {
        printf("That input was already on the list.\n");
        return (-1);
    }


    // Entry to add to list
    struct entry_s entryToAdd = {
            .magic = ENTRY_MAGIC_DATA,
            .len = strlen(str) + 1
    };
    struct entry_s* entryToAdd_p = malloc(sizeof(entryToAdd) + entryToAdd.len);
    memcpy(entryToAdd_p, &entryToAdd, sizeof(entryToAdd));
    memcpy(sizeof(entryToAdd) + (char*) entryToAdd_p, str, entryToAdd.len);

    moffset_t offset = sizeof(*fileheader);

    // If no data
    if (!fileheader->data_start) {
        fileheader->data_start = fileheader->free_start;

        memcpy(str + offset, entryToAdd_p, sizeof(entryToAdd) + entryToAdd_p->len);

        fileheader->free_start += sizeof(entryToAdd) + entryToAdd_p->len;

        return offset;
    }

    // Keeps track of current index in loop
    struct entry_s* entryIndex_p;
    while (offset < fileheader->free_start) {
        entryIndex_p = (struct entry_s*) (str + offset);

        if (entryIndex_p->magic != ENTRY_MAGIC_DATA && entryIndex_p->magic != ENTRY_MAGIC_FREE) {
            // Stolen from stringfile.c
            fprintf(stderr, "bad magic: not an entry\n");
            exit(6);
        }

        if (entryIndex_p->magic == ENTRY_MAGIC_FREE && entryToAdd_p->len <= entryIndex_p->len) {
            int spaceLeft = entryIndex_p->len - entryToAdd_p->len;
            moffset_t freeLocationOffset = offset + sizeof(*entryToAdd_p) + entryToAdd_p->len;
            // Add new empty space to the right if it fits
            struct entry_s freeEntry = {
                    .magic = ENTRY_MAGIC_FREE,
                    .len = spaceLeft - sizeof(*entryIndex_p)
            };
            if (freeLocationOffset + spaceLeft >= fileheader->free_start) {
                fileheader->free_start = freeLocationOffset;
            } else if (spaceLeft >= sizeof(freeEntry) + 1) {
                memcpy(fileheader + freeLocationOffset, &freeEntry, sizeof(freeEntry));
            } else {
                // Must add back space so we don't leave random floating data
                entryToAdd_p->len += spaceLeft;
            }


            setPointer(entryToAdd_p, offset);
            memcpy(str + offset, entryToAdd_p, sizeof(entryToAdd) + entryToAdd_p->len);

            return offset;
        }

        offset += sizeof(*entryIndex_p) + entryIndex_p->len;
    }


    // No deleted space found, add at end of list
    offset = fileheader->free_start;
    setPointer(entryToAdd_p, offset);

    while (offset + sizeof(entryToAdd) + entryToAdd_p->len > size) {
        grow(fd);

        // Have to reassign ptr because fhdr changed in growDb
        str = (char*) fileheader;
    }
    memcpy(str + offset, entryToAdd_p, sizeof(entryToAdd) + entryToAdd_p->len);

    fileheader->free_start += sizeof(entryToAdd) + entryToAdd_p->len;
    return offset;




}

void delete(char str[]) {
    moffset_t offset = find(str);

    if (!offset) {
        printf("String not found.\n");
        return;
    }

    //Stolen from stringfile.c
    char* ptr = (char*) fileheader;

    struct entry_s* entryTarget_p = (struct entry_s*) (ptr + offset);

    if (entryTarget_p->magic != ENTRY_MAGIC_DATA && entryTarget_p->magic != ENTRY_MAGIC_FREE) {
        // Stolen from stringfile.c
        fprintf(stderr, "bad magic: not an entry\n");
        exit(6);
    } else if (entryTarget_p->magic == ENTRY_MAGIC_FREE) {
        fprintf(stderr, "bad magic: found a deleted entry when deleting\n");
        exit(6);
    }

    // If deleting head
    if (offset == fileheader->data_start) {
        fileheader->data_start = entryTarget_p->next;
    } else {
        // We must find the previous entry and set its next to the deleted entry's next
        struct entry_s* entryIndex_p;
        for (
                entryIndex_p = (struct entry_s*) (ptr + fileheader->data_start);
                entryIndex_p->next != offset;
                entryIndex_p = (struct entry_s*) (ptr + entryIndex_p->next)
                ) {
            if (entryIndex_p->magic != ENTRY_MAGIC_DATA && entryIndex_p->magic != ENTRY_MAGIC_FREE) {
                // Stolen from stringfile.c
                fprintf(stderr, "bad magic: not an entry\n");
                exit(6);
            } else if (entryIndex_p->magic == ENTRY_MAGIC_FREE) {
                fprintf(stderr, "bad magic: found a deleted entry when deleting\n");
                exit(6);
            }
        }
        entryIndex_p->next = entryTarget_p->next;
    }

    // We must merge left entry and/or right entry if necessary
    struct entry_s* entryLeft_p = entryTarget_p;
    // If not first entry
    if (offset != sizeof(*fileheader)) {
        for (
                entryLeft_p = (struct entry_s*) (ptr + sizeof(*fileheader));
                ((char*) entryLeft_p) + sizeof(*entryLeft_p) + entryLeft_p->len != ptr + offset;
                entryLeft_p = (struct entry_s*) (((char*) entryLeft_p) + sizeof(*entryLeft_p) + entryLeft_p->len)
                ) {
            if (entryLeft_p->magic != ENTRY_MAGIC_DATA && entryLeft_p->magic != ENTRY_MAGIC_FREE) {
                // Stolen from stringfile.c
                fprintf(stderr, "bad magic: not an entry\n");
                exit(6);
            }
        }
        if (entryLeft_p->magic == ENTRY_MAGIC_FREE) {
            merge(entryLeft_p, entryTarget_p);
        } else {
            entryLeft_p = entryTarget_p;
        }
    }

    struct entry_s* entryRight_p = (struct entry_s*) (((char*) entryLeft_p) + sizeof(*entryLeft_p) + entryLeft_p->len);
    if (
            entryRight_p < (struct entry_s*) (ptr + fileheader->free_start)
            && entryRight_p->magic == ENTRY_MAGIC_FREE
            ) {
        merge(entryLeft_p, entryRight_p);
    }

    entryTarget_p->magic = ENTRY_MAGIC_FREE;

    // If deleting last entry
    if (((char*) entryLeft_p) + sizeof(*entryLeft_p) + entryLeft_p->len == ptr + fileheader->free_start) {
        fileheader->free_start = ((char*) entryLeft_p) - ptr;
    }


}






int main(int argc, char *argv[]) {






    if (argc <=1 || argc >=4) {
        printf("USAGE: %s [-t option for temporary] memory mapping filename \n", argv[0]);
        exit(1);
    }

    else if (argc ==2) {
        printf("Welcome, please input data using a as your command, the database filename is %s\n",argv[1]);
        strcpy(memory_filename,argv[1]);
     //   printf("filename is %s\n",argv[1]);
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

    fileheader = mmap(NULL, INIT_SIZE, PROT_READ | PROT_WRITE, tmp_flag, fd, 0);

//create a database

    if (databaseSize == 0) {
        char* ptr = (char*) fileheader;

        //initilize all the variables

        if (ftruncate(fd, INIT_SIZE) == -1) {
            perror("Ftruncate has failed");
            exit(-1);
        }

//        from stringfile.c

        fileheader->data_start = 0;
        fileheader->magic = FILE_MAGIC;
        fileheader->free_start = sizeof(*fileheader);



        size = INIT_SIZE;
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

        //printf("INPUT ARGUMENT %c", inputArgs[0]);
        if (inputArgs[0] == 'a') {
            //add
           // printf("we are here");


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



        else if (inputArgs[0] == 'l') {
            //list
            list();
        }

        else {
            printf("The commands are A for add, D for delete, and L for list");
        }


    }

    return 0;




}

