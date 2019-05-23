#include <stdio.h>
#include <stdatomic.h>

atomic_int ai;
atomic_flag flag = ATOMIC_FLAG_INIT;


//locks give atomicity, so w/o locks this is not thread safe

int i;
int j;

int main(){
_Bool rc = atomic_flag_test_and_set(&flag);
j=i;
i+=3;
printf("%d %d %d\n", j, i, ai);
j=ai;
ai+=3; //second atomic
printf("%d %d %d\n", j, i, ai);
atomic_flag_clear(&flag);


//no other memory is being used


}

//mfence any changes that happen before that, pushed out the cache (sync point)