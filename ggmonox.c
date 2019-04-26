#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <memory.h>
#include "prodcon.h"
#include <pthread.h>
#include <stdbool.h>
#include<time.h>
#include<threads.h>
static bool finished=false;//finished is set when producers are done
static pthread_mutex_t *conslock;//array of locks for heads
static pthread_cond_t *cond;//array of condition variables for locks
thread_local int my_consumer_number=0;// id for threads

typedef struct producer_arg
{
    int id;
    int producer_count;
    void (*produce)(const char* buffer); //syntax from stackoverflow
    void (*run_producer_f)(int num, int producer_count, produce_f produce, int argc, char **argv);
    int new_argc;
    char** new_argv;

}Producer;

typedef struct consumer_arg
{
    int id;
    void (*consume) ;
    void (*run_consumer_f)(int num, consume_f consume, int argc, char **argv);
    int new_argc;
    char** new_argv;

}Consumer;

struct llist_node {
    struct llist_node *next;
    char *str;
};



void* startProducer(void *arg)
{
    Producer *producer=(Producer*)arg;
    my_consumer_number=producer->id;
    producer->run_producer_f(producer->id,producer->producer_count,producer->produce,
    producer->new_argc,producer->new_argv);
}

void* startConsumer(void *arg)
{

    Consumer *consumer=(Consumer*)arg;
    my_consumer_number=consumer->id;
    consumer->run_consumer_f(consumer->id,consumer->consume,
    consumer->new_argc,consumer->new_argv);
}





/**
 * pop a node off the start of the list.
 *
 * @param phead the head of the list. this will be modified by the call unless the list is empty
 * (*phead == NULL).
 * @return NULL if list is empty or a pointer to the string at the top of the list. the caller is
 * incharge of calling free() on the pointer when finished with the string.
 */
char *pop(struct llist_node **phead,int consumerId) //touch up pop
{
    pthread_mutex_lock(&conslock[consumerId]);
    if(*phead==NULL&&finished)
    {
        return NULL;
    }
    while(*phead == NULL) {
        
        if(finished)// prevent race condition between push and pop
        {
            return NULL;
        }
        else
        {
            pthread_cond_wait(&cond[consumerId],&conslock[consumerId]);
        }
    }
    char *s = (*phead)->str;
    struct llist_node *next = (*phead)->next;
    free(*phead);
    *phead = next;
    pthread_mutex_unlock(&conslock[consumerId]);
    return s;
}

/**
 * push a node onto the start of the list. a copy of the string will be made.
 * @param phead the head of the list. this will be modified by this call to point to the new node
 * being added for the string.
 * @param s the string to add. a copy of the string will be made and placed at the beginning of
 * the list.
 */
void push(struct llist_node **phead, const char *s,int my_consumer_number)//TODO try to fix empty
{
    pthread_mutex_lock(&conslock[my_consumer_number]);
    bool empty=false;
    if(*phead==NULL)
    {
        empty=true;
    }
    struct llist_node *new_node = malloc(sizeof(*new_node));
    new_node->next = *phead;
    new_node->str = strdup(s);
    *phead = new_node;
    if(empty)
    {
        pthread_cond_signal(&cond[my_consumer_number]);
    }
    
    pthread_mutex_unlock(&conslock[my_consumer_number]);
}

// the array of list heads. the size should be equal to the number of consumers

static struct llist_node **heads;
static pthread_t *pthreadArr;
static pthread_t *cthreadArr;
static assign_consumer_f assign_consumer;
static int producer_count;
static int consumer_count;


void queue(int consumer, const char *str)
{
    push(&heads[consumer], str,consumer);
}

void produce(const char *buffer)
{

    int hash = assign_consumer(consumer_count, buffer);
    queue(hash, buffer);
}

char *consume() {
    char *str = pop(&heads[my_consumer_number],my_consumer_number);
    return str;
}

void do_usage(char *prog)
{
    printf("USAGE: %s shared_lib consumer_count producer_count ....\n", prog);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 4) {
        do_usage(argv[0]);
    }

    char *shared_lib = argv[1];
    producer_count = strtol(argv[2], NULL, 10);
    consumer_count = strtol(argv[3], NULL, 10);

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
    pthreadArr=calloc(producer_count,sizeof(pthread_t));
    Producer prodarr[producer_count];
    conslock=calloc(consumer_count,sizeof(pthread_mutex_t));
    cthreadArr=calloc(consumer_count,sizeof(pthread_t));
    cond=calloc(consumer_count,sizeof(pthread_cond_t));
    Consumer consarr[consumer_count];
    if(heads==NULL||pthreadArr==NULL||conslock==NULL||cthreadArr==NULL||cond==NULL)
    {// if not enough memory to allocate to heap print error and exit
        printf("Error out of memory\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<consumer_count;i++)//initialize consumer locks
    {
        pthread_cond_init(&cond[i],NULL);
        pthread_mutex_init(&conslock[i],NULL);
    }

    clock_t clock1=clock();
    for (int i = 0; i < producer_count; i++) {
        Producer p;
        p.id=i;
        p.new_argc=new_argc;
        p.new_argv=new_argv;
        p.produce=produce;
        p.run_producer_f=run_producer;
        p.producer_count=producer_count;
        prodarr[i]=p;
        pthread_create(&pthreadArr[i],NULL,startProducer,(void*)&prodarr[i]);
    }

    for (int j = 0; j < consumer_count; j++) {
        my_consumer_number = j;
        Consumer c;
        c.id=j;
        c.consume=consume;
        c.new_argc=new_argc;
        c.new_argv=new_argv;
        c.run_consumer_f=run_consumer;
        consarr[j]=c;
        pthread_create(&cthreadArr[j],NULL,startConsumer,(void*)&consarr[j]);
    }


    for (int i = 0; i < producer_count; i++) {
        pthread_join(pthreadArr[i],NULL);
    }
    finished=true;
    for(int i=0;i<consumer_count;i++)//signal all condition variables to ensure no infinite loop occurs
    {
        pthread_cond_signal(&cond[i]);
    }


    for (int i = 0; i < consumer_count; i++) {
        pthread_join(cthreadArr[i],NULL);
    }

    clock_t clock2=clock();
    free(cond);
    free(conslock);
    free(cthreadArr);
    free(pthreadArr);
    free(heads);
    printf("time is: %f seconds\n",(double)(clock2-clock1)/ CLOCKS_PER_SEC);//timer implementation from stackoverflow
    return 0;
}