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
// MAIN API
// Returns location of new data


#define MAX 100
static const int GROWTH_SIZE = 1024;



/////////////////VARIABLES//////////////


int databaseSize;

struct fhdr_s *fhdr;



char  memory_filename[30];
int tmp_flag ; // temporary -t option

/////////////////////////////////


void growDb(int fd) {
    munmap(fhdr, databaseSize);

    databaseSize += GROWTH_SIZE;




    if (databaseSize > MAX_SIZE) {
        printf("Too large a database");
        exit(-1);
    }



    fhdr = mmap(NULL, databaseSize, PROT_READ | PROT_WRITE, databaseSize, fd, 0);
}




void setNext(struct entry_s* entry_p, moffset_t entryLocation) {

    char* ptr = (char*) fhdr;


    moffset_t offset = fhdr->data_start;
    struct entry_s* entryIndex_p;

    do {
        entryIndex_p = (struct entry_s*) (ptr + offset);

        if (entryIndex_p->magic != ENTRY_MAGIC_DATA && entryIndex_p->magic != ENTRY_MAGIC_FREE) {

            fprintf(stderr, "bad magic: not an entry\n");
            exit(6);
        } else if (entryIndex_p->magic == ENTRY_MAGIC_FREE) {
            fprintf(stderr, "bad magic: some entry points to an empty entry\n");
            exit(6);
        }

        if (offset == fhdr->data_start && strcmp(entryIndex_p->str, entry_p->str) > 0) {
            // Entry should be new start
            entry_p->next = offset;
            fhdr->data_start = entryLocation;
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

void merge(struct entry_s* entryLeft_p, struct entry_s* entryRight_p) {
    struct entry_s entryFree = {
            .magic = ENTRY_MAGIC_FREE,
            .len = entryLeft_p->len + sizeof(*entryRight_p) + entryRight_p->len
    };
    memcpy(entryLeft_p, &entryFree, sizeof(entryFree));
}

moffset_t find(char target[]) {
    moffset_t offset = sizeof(*fhdr);

    // If no data
    if (!offset) return 0;



    char* ptr = (char*) fhdr;

    struct entry_s* entry_p;
    while (offset < fhdr->free_start) {
        entry_p = (struct entry_s*) (ptr + offset);

        if (entry_p->magic == ENTRY_MAGIC_DATA || entry_p->magic == ENTRY_MAGIC_FREE) {
            if (entry_p->magic == ENTRY_MAGIC_DATA && strcmp(entry_p->str, target) == 0) {
                return offset;
            }
        } else {

            fprintf(stderr, "bad magic: not an entry\n");
            exit(6);
        }


        offset += sizeof(*entry_p) + entry_p->len;
    }

    return 0;
}





void list() {

    char* ptr = (char*) fhdr;

    moffset_t offset = fhdr->data_start;

    // No data
    if (!offset) return;

    struct entry_s* entry_p;
    do {
        entry_p = (struct entry_s*) (ptr + offset);

        if (entry_p->magic != ENTRY_MAGIC_DATA && entry_p->magic != ENTRY_MAGIC_FREE) {

            fprintf(stderr, "bad magic: not an entry\n");
            exit(6);
        } else if (entry_p->magic == ENTRY_MAGIC_FREE) {
            fprintf(stderr, "bad magic: some entry points to an empty entry\n");
            exit(6);
        }

        printf("%s\n", entry_p->str);


        offset = entry_p->next;
    } while (entry_p->next);
}

void delete(char str[]) {
    moffset_t offset = find(str);

    if (!offset) {
        printf("String not found.\n");
        return;
    }


    char* ptr = (char*) fhdr;

    struct entry_s* entryTarget_p = (struct entry_s*) (ptr + offset);

    if (entryTarget_p->magic != ENTRY_MAGIC_DATA && entryTarget_p->magic != ENTRY_MAGIC_FREE) {

        fprintf(stderr, "bad magic: not an entry\n");
        exit(6);
    } else if (entryTarget_p->magic == ENTRY_MAGIC_FREE) {
        fprintf(stderr, "bad magic: found a deleted entry when deleting\n");
        exit(6);
    }

    // If deleting head
    if (offset == fhdr->data_start) {
        fhdr->data_start = entryTarget_p->next;
    } else {
        // We must find the previous entry and set its next to the deleted entry's next
        struct entry_s* entryIndex_p;
        for (
                entryIndex_p = (struct entry_s*) (ptr + fhdr->data_start);
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
    if (offset != sizeof(*fhdr)) {
        for (
                entryLeft_p = (struct entry_s*) (ptr + sizeof(*fhdr));
                ((char*) entryLeft_p) + sizeof(*entryLeft_p) + entryLeft_p->len != ptr + offset;
                entryLeft_p = (struct entry_s*) (((char*) entryLeft_p) + sizeof(*entryLeft_p) + entryLeft_p->len)
                ) {

        }
        if (entryLeft_p->magic == ENTRY_MAGIC_FREE) {
            merge(entryLeft_p, entryTarget_p);
        } else {
            entryLeft_p = entryTarget_p;
        }
    }

    struct entry_s* entryRight_p = (struct entry_s*) (((char*) entryLeft_p) + sizeof(*entryLeft_p) + entryLeft_p->len);
    if (
            entryRight_p < (struct entry_s*) (ptr + fhdr->free_start)
            && entryRight_p->magic == ENTRY_MAGIC_FREE
            ) {
        merge(entryLeft_p, entryRight_p);
    }

    entryTarget_p->magic = ENTRY_MAGIC_FREE;

    // If deleting last entry
    if (((char*) entryLeft_p) + sizeof(*entryLeft_p) + entryLeft_p->len == ptr + fhdr->free_start) {
        fhdr->free_start = ((char*) entryLeft_p) - ptr;
    }

}




moffset_t add(int fd, char str[]) {

    char* ptr = (char*) fhdr;


    if (find(str)) {
        printf("Data already exists.\n");
        return (-1);
    }

    //Go ahead and add

    struct entry_s entryToAdd = {
            .magic = ENTRY_MAGIC_DATA,
            .len = strlen(str) + 1
    };
    struct entry_s* entryToAdd_p = malloc(sizeof(entryToAdd) + entryToAdd.len);
    memcpy(entryToAdd_p, &entryToAdd, sizeof(entryToAdd));
    memcpy(sizeof(entryToAdd) + (char*) entryToAdd_p, str, entryToAdd.len);

    moffset_t offset = sizeof(*fhdr);

    // If no data
    if (!fhdr->data_start) {
        fhdr->data_start = fhdr->free_start;

        memcpy(ptr + offset, entryToAdd_p, sizeof(entryToAdd) + entryToAdd_p->len);

        fhdr->free_start += sizeof(entryToAdd) + entryToAdd_p->len;

        return offset;
    }

    // Keeps track of current index in loop
    struct entry_s* entryIndex_p;
    while (offset < fhdr->free_start) {
        entryIndex_p = (struct entry_s*) (ptr + offset);



        if (entryIndex_p->magic == ENTRY_MAGIC_FREE && entryToAdd_p->len <= entryIndex_p->len) {
            int spaceLeft = entryIndex_p->len - entryToAdd_p->len;
            moffset_t freeLocationOffset = offset + sizeof(*entryToAdd_p) + entryToAdd_p->len;
            // Add new empty space to the right if it fits
            struct entry_s freeEntry = {
                    .magic = ENTRY_MAGIC_FREE,
                    .len = spaceLeft - sizeof(*entryIndex_p)
            };
            if (freeLocationOffset + spaceLeft >= fhdr->free_start) {
                fhdr->free_start = freeLocationOffset;
            } else if (spaceLeft >= sizeof(freeEntry) + 1) {
                memcpy(ptr + freeLocationOffset, &freeEntry, sizeof(freeEntry));
            } else {
                // Must add back space so we don't leave random floating data
                entryToAdd_p->len += spaceLeft;
            }


            setNext(entryToAdd_p, offset);
            memcpy(ptr + offset, entryToAdd_p, sizeof(entryToAdd) + entryToAdd_p->len);

            return offset;
        }

        offset += sizeof(*entryIndex_p) + entryIndex_p->len;
    }


    // No deleted space found, add at end of list
    offset = fhdr->free_start;
    setNext(entryToAdd_p, offset);

    while (offset + sizeof(entryToAdd) + entryToAdd_p->len > databaseSize) {
        growDb(fd);

        // Have to reassign ptr because fhdr changed in growDb
        ptr = (char*) fhdr;
    }
    memcpy(ptr + offset, entryToAdd_p, sizeof(entryToAdd) + entryToAdd_p->len);

    fhdr->free_start += sizeof(entryToAdd) + entryToAdd_p->len;
    return offset;
}



void createDb(int fd) {

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




    // <FROM STRINGFILE//



    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror(argv[1]);
        exit(2);
    }

    //END FROM STRING FILE

    fhdr = mmap(NULL, INIT_SIZE, PROT_READ | PROT_WRITE, tmp_flag, fd, 0);


//if there is no database
    if (databaseSize == 0) {
        char* ptr = (char*) fhdr;


        fhdr->magic = FILE_MAGIC;
        // no strings, so point to 0;
        fhdr->data_start = 0;
        // no strings, so point to the end of the header
        fhdr->free_start = sizeof(*fhdr);





        databaseSize = INIT_SIZE;
    }



    if (fhdr->magic != FILE_MAGIC) {
        fprintf(stderr, "bad magic: not a strings file!\n");
        exit(6);
    }

    bool running = true;


    while (running) {

        char* str;
        int inputLength = 0;


        char inputArgs[MAX];


        while (fgets(inputArgs, MAX, stdin) == NULL) {
            printf("Failed Fget input");
            exit(-1);
        }


        for (int i = 0; inputArgs[i] != '\n'; i++) {
            inputLength++; //determines the size of the input length
        }



        if (inputArgs[0] == 'a' || inputArgs[0] == 'A' || inputArgs[0] == 'd' || inputArgs[0] == 'D') {
            if (inputLength < 2 || inputArgs[1] != ' ') {
                printf("Bad input. Expecting a space then a string after %c\n", inputArgs[0]);
                continue;
            }

            str = malloc(inputLength + 1);
            for (int i = 2; i < inputLength; i++)
                str[i - 2] = inputArgs[i];
            str[inputLength] = '\0';
        } else if (inputArgs[0] != 'l' && inputArgs[0] != 'L') {
            printf("Bad input. Please use any of: l, a string, d string\n");
            continue;
        }

        switch (inputArgs[0]) {
            case 'l':
            case 'L':
                list();
                break;
            case 'a':
            case 'A':
                add(fd, str);
                break;
            case 'd':
            case 'D':
                delete(str);
                break;
        }
    }

    return 0;

   
}



