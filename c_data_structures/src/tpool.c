#include "../include/tpool.h"

// Internal method to create tpool work
static tpool_work_t* tpool_work_create(thread_func_t func, void* arg)
{
    tpool_work_t* work;
    
    if (NULL == func || NULL == arg)
    {
        return NULL;
    }
    
    work = malloc(sizeof(*work));
    work->func = func;
    work->arg = arg;
    work->next = NULL;
    return work;
}

// Internal method to destroy tpool work
static void tpool_work_destroy(tpool_work_t* work)
{
    if (NULL == work)
    {
        return;
    }
    
    free(work);
    work = NULL;
}

// Internal method to pop tpool head
static tpool_work_t* tpool_work_get(tpool_t* tm)
{
    tpool_work_t* work;
    
    if (NULL == tm)
    {
        return NULL;
    }
    
    work = tm->work_first;
    
    if (NULL == work)
    {
        return NULL;
    }
    
    if (NULL == work->next)
    {
        tm->work_first = NULL;
        tm->work_last = NULL;
    }
    else
    {
        tm->work_first = work->next;
    }
    
    return work;
}

// Internal method to handle and process tpool work
static void* tpool_worker(void* arg)
{
    tpool_t* tm = arg;
    tpool_work_t* work;
    
    while (1)
    {
        pthread_mutex_lock(&(tm->work_mutex));
        
        while ((NULL == tm->work_first) && (!tm->stop))
        {
            pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));
        }
        
        if (tm->stop)
        {
            break;
        }
        
        work = tpool_work_get(tm);
        tm->working_cnt++;
        
        pthread_mutex_unlock(&(tm->work_mutex));
        
        if (NULL != work)
        {
            work->func(work->arg);
            tpool_work_destroy(work);
        }
        
        pthread_mutex_lock(&(tm->work_mutex));
        
        tm->working_cnt--;
        
        if (!tm->stop && tm->working_cnt == 0 && NULL == tm->work_first)
        {
            pthread_cond_signal(&(tm->working_cond));
        }
        
        pthread_mutex_unlock(&(tm->work_mutex));
    }
    
    tm->thread_cnt--;
    pthread_cond_signal(&(tm->working_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
    return NULL;
}

// Creates a tpool struct with num threads
tpool_t* tpool_create(size_t num)
{
    tpool_t* tm;
    size_t i;
    
    if (num <= 0 || num > 12)
    {
        num = 4;
    }
    
    tm = calloc(1, sizeof(*tm));
    tm->thread_cnt = num;
    tm->thread_num = num;
    
    tm->pthread_array = calloc(num, sizeof(pthread_t));
    
    pthread_mutex_init(&(tm->work_mutex), NULL);
    pthread_cond_init(&(tm->work_cond), NULL);
    pthread_cond_init(&(tm->working_cond), NULL);
    
    tm->work_first = NULL;
    tm->work_last = NULL;
    
    for (i = 0; i < num; ++i)
    {
        pthread_create(&tm->pthread_array[i], NULL, tpool_worker, tm);
    }
    
    return tm;
}

// Destroy and free tpool struct
void tpool_destroy(tpool_t* tm)
{
    tpool_work_t* work_one;
    tpool_work_t* work_two;
    
    if (NULL == tm)
    {
        return;
    }
    
    pthread_mutex_lock(&(tm->work_mutex));
    work_one = tm->work_first;
    
    while (NULL != work_one)
    {
        work_two = work_one->next;
        tpool_work_destroy(work_one);
        work_one = work_two;
    }
    
    tm->stop = true;
    pthread_cond_broadcast(&(tm->work_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
    
    tpool_wait(tm);
    int error_num;
    
    for (size_t i = 0; i < tm->thread_num; ++i)
    {
        error_num = pthread_join(tm->pthread_array[i], NULL);
        
        if (error_num != 0)
        {
            fprintf(stderr, "Error: Join error %d found\n", error_num);
        }
    }
    
    pthread_mutex_destroy(&(tm->work_mutex));
    pthread_cond_destroy(&(tm->work_cond));
    pthread_cond_destroy(&(tm->working_cond));
    
    free(tm->pthread_array);
    free(tm);
}

// Add work to the tpool queue
bool tpool_add_work(tpool_t* tm, thread_func_t func, void* arg)
{
    tpool_work_t* work;
    
    if (NULL == tm)
    {
        return false;
    }
    
    work = tpool_work_create(func, arg);
    
    if (NULL == work)
    {
        return false;
    }
    
    pthread_mutex_lock(&(tm->work_mutex));
    
    if (NULL == tm->work_first)
    {
        tm->work_first = work;
        tm->work_last = tm->work_first;
    }
    else
    {
        tm->work_last->next = work;
        tm->work_last = work;
    }
    
    pthread_cond_broadcast(&(tm->work_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
    
    return true;
}

// Blocking function that will return when there is no work
void tpool_wait(tpool_t* tm)
{
    if (NULL == tm)
    {
        return;
    }
    
    pthread_mutex_lock(&(tm->work_mutex));
    
    while (1)
    {
        if (tm->working_cnt != 0)
        {
            pthread_cond_wait(&(tm->working_cond), &(tm->work_mutex));
        }
        else
        {
            break;
        }
    }
    
    pthread_mutex_unlock(&(tm->work_mutex));
}
