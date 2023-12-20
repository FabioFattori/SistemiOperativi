#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "DBGpthread.h"
#include "printerror.h"

#define nUbriachi 2
#define nSobri 4
#define nFunivie 1
#define nPersoneABordoSobrie 2
#define nPersoneABordoUbriache 1


/* variabili per la sincronizzazione */
pthread_mutex_t mutexFunivia;
pthread_mutex_t mutexPersone;
pthread_cond_t listaDiAttesa;
pthread_cond_t waintingFunivia;

/* variabili da proteggere */
int nPersoneSuFunivia;
int nUbriachiSuFunivia;
int funiviaATerra; /* 0 => è in viaggio , 1 => è a terra */

void *persona(void *arg)
{
    int indice;

    indice = *((int *)arg);

    DBGsleep(1,"non ho sonno");

    printf("persona %i creata \n", indice);
    free(arg);


    while (1)
    {
        DBGpthread_mutex_lock(&mutexPersone, "DBGpthread_mutex_lock failed");
        while (funiviaATerra != 1 || (nPersoneSuFunivia == nPersoneABordoSobrie || nUbriachiSuFunivia > 0))
        {
            DBGpthread_cond_wait(&listaDiAttesa, &mutexPersone, "DBGpthread_cond_wait failed");
        }

        printf("la persona %i entra \n",indice);
        
        nPersoneSuFunivia++;
        if(nPersoneSuFunivia == nPersoneABordoSobrie || nUbriachiSuFunivia > 0){
            DBGpthread_cond_broadcast(&waintingFunivia, "DBGpthread_cond_broadcast failed");
        }
        DBGpthread_mutex_unlock(&mutexPersone, "DBGpthread_mutex_unlock failed");
        DBGsleep(10,"non ho sonno");
    }

    pthread_exit(NULL);
}

void* ubriaco(void* arg){
    int indice;

    indice = *((int *)arg);

    DBGsleep(1,"non ho sonno");
    printf("persona %i creata , è ubriaco \n", indice);
    free(arg);


    while (1)
    {
        DBGpthread_mutex_lock(&mutexPersone, "DBGpthread_mutex_lock failed");
        while (funiviaATerra != 1 || (nPersoneSuFunivia > 0 || nUbriachiSuFunivia > 0))
        {
            DBGpthread_cond_wait(&listaDiAttesa, &mutexPersone, "DBGpthread_cond_wait failed");
        }

        printf("la persona %i entra \n",indice);
        
        printf("la persona %i è ubriaco \n",indice);
        

        nUbriachiSuFunivia++;
        
        nPersoneSuFunivia++;
        
        if(nPersoneSuFunivia == nPersoneABordoSobrie || nUbriachiSuFunivia > 0){
            DBGpthread_cond_broadcast(&waintingFunivia, "DBGpthread_cond_broadcast failed");
        }
        DBGpthread_mutex_unlock(&mutexPersone, "DBGpthread_mutex_unlock failed");
        DBGsleep(10,"non ho sonno");
    }

    pthread_exit(NULL);
}

void *funivia(void *arg)
{
    int indice;

    indice = *((int *)arg);
    free(arg);

    printf("funivia %i creata\n", indice);

    while (1)
    {
        DBGpthread_mutex_lock(&mutexFunivia, "DBGpthread_mutex_lock failed");
        printf("la funivia aspetta che le persone entrino\n");
        
        DBGpthread_cond_wait(&waintingFunivia, &mutexFunivia, "DBGpthread_cond_wait failed");
        
        funiviaATerra = 0;

        if (nPersoneSuFunivia == nPersoneABordoUbriache && nUbriachiSuFunivia == nPersoneABordoUbriache)
        {
            printf("la funivia parte con %i ubriaco/hi\n", nPersoneABordoUbriache);
        }
        else if (nPersoneSuFunivia == nPersoneABordoSobrie)
        {
            printf("la funivia parte con %i persone\n", nPersoneABordoSobrie);
        }

        DBGpthread_mutex_unlock(&mutexFunivia, "DBGpthread_mutex_unlock failed");

        DBGsleep(1, "non ho sonno");

        printf("la funivia ha raggiunto la vetta ,ora si torna indietro\n");

        DBGsleep(1, "non ho sonno");

        printf("la funivia è tornata a terra\n");

        DBGpthread_mutex_lock(&mutexFunivia, "DBGpthread_mutex_lock failed");

        nPersoneSuFunivia = 0;
        nUbriachiSuFunivia = 0;
        funiviaATerra = 1;
        DBGpthread_cond_broadcast(&listaDiAttesa, "DBGpthread_cond_broadcast failed");

        DBGpthread_mutex_unlock(&mutexFunivia, "DBGpthread_mutex_unlock failed");
    }

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int rc, i, *intptr;
    pthread_t th;
    nPersoneSuFunivia = 0;
    nUbriachiSuFunivia = 0;
    funiviaATerra = 1;

    DBGpthread_mutex_init(&mutexFunivia, NULL, "DBGpthread_mutex_init failed");
    DBGpthread_cond_init(&waintingFunivia, NULL, "DBGpthread_cond_init failed");

    for (i = 0; i < nFunivie; i++)
    {
        intptr = malloc(sizeof(int));
        if (!intptr)
        {
            printf("malloc failed\n");
            exit(1);
        }
        *intptr = i;
        rc = pthread_create(&th, NULL, funivia, intptr);
        if (rc)
            PrintERROR_andExit(rc, "pthread_create failed");
    }

    DBGpthread_cond_init(&listaDiAttesa, NULL, "DBGpthread_cond_init failed");
    DBGpthread_mutex_init(&mutexPersone, NULL, "DBGpthread_mutex_init failed");
    for (i = 0; i < nSobri; i++)
    {
        intptr = malloc(sizeof(int));
        if (!intptr)
        {
            printf("malloc failed\n");
            exit(1);
        }
        *intptr = i;
        rc = pthread_create(&th, NULL, persona, intptr);

        if (rc)
            PrintERROR_andExit(rc, "pthread_create failed");
    }

    for (i = nSobri; i < nUbriachi + nSobri; i++)
    {
        intptr = malloc(sizeof(int));
        if (!intptr)
        {
            printf("malloc failed\n");
            exit(1);
        }
        *intptr = i;
        rc = pthread_create(&th, NULL, ubriaco, intptr);
        if (rc)
            PrintERROR_andExit(rc, "pthread_create failed");
    }

    pthread_exit(NULL);

    return 0;
}
