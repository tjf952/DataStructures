#include "include/tpool.h"

#define THREADS 4

void worker(void* argument)
{
    int arg = *(int *)argument;
    int sum = 0;
    
    printf("[Thread %d in worker function]\n", arg);

    if (arg > 0)
    {
        int fib[arg+1];
        fib[0] = 0;
        fib[1] = 1;
        
        sum = fib[0] + fib[1];
        
        for (int i = 2; i <= arg; ++i)
        {
            fib[i] = fib[i-1] + fib[i-2];
            sum += fib[i];
        }
    }
    
    printf("[Sum given argumet %d: %d]\n", arg, sum);
}

int main(void)
{
    int** data = calloc(20, sizeof(int*));

    for (int i = 0; i < 20; ++i)
    {
        data[i] = calloc(1, sizeof(int));
        *data[i] = i;
    }

    /*** TPOOL TESTING START ***/
    
    tpool_t* tm = tpool_create(THREADS);
    
    for (int i = 0; i < 20; ++i)
    {
        tpool_add_work(tm, worker, data[i]);
    }
    
    sleep(1); // Need to have threadpool increment
    tpool_wait(tm);
    tpool_destroy(tm);

    /*** TPOOL TESTING END ***/

    printf("\n");

    for (int i = 0; i < 20; ++i)
    {
        free(data[i]);
    }
    free(data);
}
  
