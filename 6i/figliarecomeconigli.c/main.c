#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "DBGpthread.h"
#include "printerror.h"

#define maxThread 5

/* data to protect */
int nThread;
pthread_mutex_t mutex;

void *conigliator(void *args);

void tryToCreateAThread(int waitingTime)
{
    pthread_t th;
    int rc;
    DBGsleep(waitingTime, "non ho sono");
    DBGpthread_mutex_lock(&mutex, "DBGpthread_mutex_lock failed");

    if (nThread < maxThread)
    {
        nThread++;
        if (waitingTime == 5)
            printf("PADRE:thread Created => %d\n", nThread);
        else
            printf("FIGLIO:thread Created => %d\n", nThread);
        rc = pthread_create(&th, NULL, conigliator, NULL);
        if (rc)
            PrintERROR_andExit(rc, "pthread_create failed");
    }
    else
    {
        nThread--;
        if (waitingTime == 5)
            printf("PADRE:thread Deleted => %d\n", nThread);
        else
            printf("FIGLIO:thread Deleted => %d\n", nThread);

        DBGpthread_mutex_unlock(&mutex, "DBGpthread_mutex_unlock failed");
        pthread_exit(NULL);
    }

    DBGpthread_mutex_unlock(&mutex, "DBGpthread_mutex_unlock failed");
}

void *conigliator(void *args)
{
    while (1)
    {
        tryToCreateAThread(1);
    }
}

int main(int argc, char const *argv[])
{

    nThread = 0;

    DBGpthread_mutex_init(&mutex, NULL, "DBGpthread_mutex_init failed");

    while (1)
    {
        tryToCreateAThread(5);
    }

    return 0;
}
