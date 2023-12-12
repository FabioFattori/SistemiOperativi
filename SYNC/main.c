#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "DBGpthread.h"
#include "printerror.h"

#define NTHREADTOCREATE 90

/* data to protect */
int threadCreated = 0;
int decessedThreads = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *threadFunc(void *args)
{
    int id = (*(int *)args);
    free(args);
    printf("thread %d è VIVO\n", id);
    
    DBGsleep(1, "ERROR => non ho sonno");

    DBGpthread_mutex_lock(&mutex, "ERROR => lock error");

    threadCreated++;

    if (threadCreated == NTHREADTOCREATE)
    {
        DBGpthread_cond_broadcast(&cond, "ERROR => brodacast error");
    }

    while (threadCreated != NTHREADTOCREATE)
    {
        DBGpthread_cond_wait(&cond, &mutex, "ERROR => cond wait");
    }

    DBGpthread_mutex_unlock(&mutex, "ERROR => unlock error");

    /* check if thread can end */

    DBGpthread_mutex_lock(&mutex, "ERROR => lock error");

    while (decessedThreads != id)
    {
        DBGpthread_cond_wait(&cond, &mutex, "ERROR => cond wait");
    }

    printf("thread %d MUORE\n", id);

    decessedThreads++;

    DBGpthread_cond_broadcast(&cond, "ERROR => broadcast error");

    DBGpthread_mutex_unlock(&mutex, "ERROR => unlock ERROR");

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int rc, i;
    int *ids;
    pthread_t th;

    rc = pthread_mutex_init(&mutex, NULL);
    if (rc)
        PrintERROR_andExit(rc, "ERROR => mutex init error");

    rc = pthread_cond_init(&cond, NULL);
    if (rc)
        PrintERROR_andExit(rc, "ERROR => cond init error");

    for (i = 0; i < NTHREADTOCREATE; i++)
    {
        ids = (int*)malloc(sizeof(int));
        if (!ids)
            PrintERROR_andExit(rc, "ERROR => malloc fail");
        *ids = i;
        rc = pthread_create(&th, NULL, threadFunc, (void*)ids);
        if (rc)
            PrintERROR_andExit(rc, "ERROR => thread creation error");
    }

    pthread_exit(NULL);
    return 0;
}
