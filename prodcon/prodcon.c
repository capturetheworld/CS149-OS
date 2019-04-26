#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dlfcn.h>
#include <error.h>
#include <stdbool.h>
#include <memory.h>
#include "prodcon.h"
#include <unistd.h>


struct llist_node {
    struct llist_node *next;
    char *str;
};

struct list_s *head = NULL;

static pthread_cond_t *conditions;
static pthread_mutex_t *locks;
static char *sentinel = NULL;

static pthread_t *consumers;
static pthread_t *producers;

static int prod_complete;


static run_producer_f run_producer;
static run_consumer_f run_consumer;



/**
 * pop a node off the start of the list.
 *
 * @param phead the head of the list. this will be modified by the call unless the list is empty
 * (*phead == NULL).
 * @return NULL if list is empty or a pointer to the string at the top of the list. the caller is
 * incharge of calling free() on the pointer when finished with the string.
 */
char *pop(struct llist_node **phead)
{
    if (*phead == NULL) {
        return NULL;
    }
    char *s = (*phead)->str;
    struct llist_node *next = (*phead)->next;
    free(*phead);
    *phead = next;
    return s;
}

/**
 * push a node onto the start of the list. a copy of the string will be made.
 * @param phead the head of the list. this will be modified by this call to point to the new node
 * being added for the string.
 * @param s the string to add. a copy of the string will be made and placed at the beginning of
 * the list.
 */
void push(struct llist_node **phead, const char *s)
{
    struct llist_node *new_node = malloc(sizeof(*new_node));
    new_node->next = *phead;
    new_node->str = strdup(s);
    *phead = new_node;
}

struct threadData{
    size_t count;
    
    char **argv;

    int argc;
}

// the array of list heads. the size should be equal to the number of consumers
static struct llist_node **heads;

static assign_consumer_f assign_consumer;
static int producer_count;
static int consumer_count;

thread_local int my_consumer_number;

void queue(int consumer, const char *str)
{
    push(&heads[consumer], str);
}

void produce(const char *buffer)
{
    int hash = assign_consumer(consumer_count, buffer);


    queue(hash, buffer);
}

char *consume() {
    char *str = pop(&heads[my_consumer_number]);
    return str;
}

void do_usage(char *prog)
{
    printf("USAGE: %s shared_lib consumer_count producer_count ....\n", prog);
    exit(1);
}


void * startproduction(void * toProduce){
    struct threadData *produced = (struct threadData) toProduce;

    run_producer(threadData->count,produce, threadData->argc,threadData->argv);


}


void startconsumption (void * toConsume){

    struct threadData *consumed = (struct threadData) toConsume;

    struct data *d = toConsume;

    my_consumer_number (size_t) d;

    run_consumer((size_t) toConsume, consume, threadData->argc, threadData->argv );



}

int main(int argc, char **argv)
{

     
 


    if (argc < 4) {
        do_usage(argv[0]);
    }

    char *shared_lib = argv[1];
   pthread_t consumerThreads[consumer_count];
     pthread_t producerThreads[producer_count];

    char **new_argv = &argv[4];
    int new_argc = argc - 4;
    setlinebuf(stdout);

    if (consumer_count <= 0 || producer_count <= 0) {
        do_usage(argv[0]);
    }

    void *dh = dlopen(shared_lib, RTLD_LAZY);

    // load the producer, consumer, and assignment functions from the library
    run_producer_f run_producer = dlsym(dh, "run_producer");
    run_consumer_f run_consumer = dlsym(dh, "run_consumer");
    assign_consumer = dlsym(dh, "assign_consumer");
    if (run_producer == NULL || run_consumer == NULL || assign_consumer == NULL) {
        printf("Error loading functions: prod %p cons %p assign %p\n", run_producer,
                run_consumer, assign_consumer);
        exit(2);
    }

    heads = calloc(consumer_count, sizeof(*heads));
    locks = calloc(consumer_count, sizeof(*locks));
    conditions = calloc(consumer_count, sizeof(*conditions));

  




 for (int k = 0; k < consumer_count; l++) {
        pthread_create(&consumerThreads[k], NULL, startproduction, (void *)(size_t)k);
    }


for (int j = 0; j < consumer_count; j++) {
        pthread_create(&consumerThreads[j], NULL, startconsumption, (void *)(size_t)j);
    }





for(int i = 0; i < consumer_count; i++) {
        push(2, i, &heads[i], sentinel);
    }


    free(locks);
    free(heads);
    free(conditions);

    return 0;
}