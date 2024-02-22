#ifndef _WORKERS_H
#define _WORKERS_H

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

typedef void (*thread_func_t)(void* arg);

// TPOOL_WORK struct
typedef struct tpool_work
{
    thread_func_t func;
    void* arg;
    struct tpool_work* next;
}
tpool_work_t;

// TPOOL struct
typedef struct tpool
{
    pthread_t* pthread_array;
    tpool_work_t* work_first;
    tpool_work_t* work_last;
    pthread_mutex_t work_mutex;
    pthread_cond_t work_cond;
    pthread_cond_t working_cond;
    size_t working_cnt;
    size_t thread_cnt;
    size_t thread_num;
    bool stop;
}
tpool_t;

tpool_t* tpool_create(size_t num);
void tpool_destroy(tpool_t* tm);

bool tpool_add_work(tpool_t* tm, thread_func_t func, void* arg);
void tpool_wait(tpool_t* tm);

#endif
