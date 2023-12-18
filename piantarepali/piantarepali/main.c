#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "DBGpthread.h"
#include "printerror.h"

#define maxPaliToMartellare 4
#define nMartellatori 2

/* data to protect  */
int startMartellare;
int martellatoriCheHannoFinito;
int martelliCreati;
/* variabili per la sincronizzazione */
pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_cond_t condTieniPalo;

void *martellatoreX(void *args)
{
    int id = -1;
    int paliFatti = 0;

    while (1)
    {

        DBGpthread_mutex_lock(&mutex, "DBGpthread_mutex_lock failed");

        if (id == -1)
        {
            id = martelliCreati;
            martelliCreati++;
            printf("martellatore %d initialized\n", id);
        }

        while (startMartellare == 0)
        {
            DBGpthread_cond_wait(&cond, &mutex, "DBGpthread_cond_wait failed");
        }

        printf("martellatore %d inizia\n", id);
        DBGsleep(1, "non ho sonno");
        printf("finito!\n");
        martellatoriCheHannoFinito++;

        paliFatti++;

        if (paliFatti == maxPaliToMartellare)
        {
            paliFatti = 0;
            printf("il martellatore %d si riposa\n", id);
            if (id == 0)
            {
                DBGsleep(5, "non ho sonno");
            }
            else
            {
                DBGsleep(7, "non ho sonno");
            }
        }

        if (martellatoriCheHannoFinito != nMartellatori)
        {
            DBGpthread_cond_wait(&cond, &mutex, "DBGpthread_cond_wait failed");
        }

        printf("TUTTI I MARTELLATORI HANNO FINITO\n");
        martellatoriCheHannoFinito = 0;
        startMartellare = 0;
        DBGpthread_cond_broadcast(&cond, "DBGpthread_cond_broadcast failed");

        DBGpthread_cond_broadcast(&condTieniPalo, "DBGpthread_cond_signal failed");

        DBGpthread_mutex_unlock(&mutex, "DBGpthread_mutex_unlock failed");
    }

    pthread_exit(NULL);
}

void *tieniPalo(void *args)
{
    printf("tieni palo initialized\n");

    while (1)
    {
        DBGpthread_mutex_lock(&mutex, "DBGpthread_mutex_lock failed");
        printf("tieniPalo prende i pali e li posiziona \n");
        martellatoriCheHannoFinito = 0;

        DBGpthread_mutex_unlock(&mutex, "DBGpthread_mutex_unlock failed");

        DBGsleep(1, "non ho sonno");

        DBGpthread_mutex_lock(&mutex, "DBGpthread_mutex_lock failed");
        printf("martellare!\n");
        startMartellare = 1;
        DBGpthread_cond_broadcast(&cond, "DBGpthread_cond_broadcast failed");

        /* aspetto di essere liberato dai martellatori */
        DBGpthread_cond_wait(&condTieniPalo, &mutex, "non ho sonno");

        DBGpthread_mutex_unlock(&mutex, "DBGpthread_mutex_unlock failed");
    }

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t th;
    int rc, i;

    startMartellare = 0;
    martelliCreati = 0;

    DBGpthread_mutex_init(&mutex, NULL, "DBGpthread_mutex_init failed");
    DBGpthread_cond_init(&cond, NULL, "DBGpthread_cond_init failed");
    DBGpthread_cond_init(&condTieniPalo, NULL, "DBGpthread_cond_init failed");

    rc = pthread_create(&th, NULL, tieniPalo, NULL);
    if (rc)
        PrintERROR_andExit(rc, "ERROR CREATING THREAD");

    for (i = 0; i < nMartellatori; i++)
    {
        rc = pthread_create(&th, NULL, martellatoreX, NULL);
        if (rc)
            PrintERROR_andExit(rc, "ERROR CREATING THREAD");
    }

    pthread_exit(NULL);
    return 0;
}
