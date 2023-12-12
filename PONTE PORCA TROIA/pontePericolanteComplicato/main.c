#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "DBGpthread.h"
#include "printerror.h"

#define NCarOrarie 4
#define NCarAntiorarieOrarie 4
#define TIMETOCIRCLE 10
#define TIMETOFIRSTHALFPONTE 1
#define TIMETOSECONDHALFPONTE 1

enum carType
{
    O,
    A,
    NONE
};

typedef struct
{
    enum carType type;
    int id;
    int currentBiglietto;
} Car;

/* data to protect */
int bigliettoDistributore[2]; /* bigliettoDistributore[0] => nTicket auto orarie ; bigliettoDistributore[1] => nTicket auto antiorarie */

/* semaphores */
int carIsInHalfOfPonte; /* -1 => no car on ponte ; 0 => false ; 1 => true */
int minCardPresentForOrari;
int minCardPresentForAnti;
enum carType carTypeOnPonte;
pthread_mutex_t biglietteria;
pthread_mutex_t ponte;
pthread_cond_t cond;

void inizializeVariable()
{
    minCardPresentForOrari = 0;
    minCardPresentForAnti = NCarOrarie;
    carTypeOnPonte = NONE;
    bigliettoDistributore[0] = -1;
    bigliettoDistributore[1] = -1;
    carIsInHalfOfPonte = -1;
    DBGpthread_mutex_init(&biglietteria, NULL, "error mutex init");
    DBGpthread_cond_init(&cond, NULL, "error cond init");
}

int takeABiglietto(enum carType mode)
{
    if (mode == A)
    {
        bigliettoDistributore[1]++;
        return bigliettoDistributore[1];
    }
    else if (mode == O)
    {
        bigliettoDistributore[0]++;
        return bigliettoDistributore[0];
    }
    return -1;
}

int checkThisMachineNeedsToWaitOrari(Car *machine)
{
    if (((minCardPresentForAnti != machine->id && carTypeOnPonte != A && machine->type == A) || (machine->type == O && minCardPresentForOrari != machine->id && carTypeOnPonte == O)) && carIsInHalfOfPonte != 1)
        return 1;
    return 0;
}

int checkTicket(int ticketNumber, enum carType mode)
{
    if (mode == A)
    {
        if (ticketNumber != minCardPresentForOrari)
        {
            return 1;
        }
    }
    else if (mode == O)
    {
        if (ticketNumber != minCardPresentForAnti)
        {
            return 1;
        }
    }
    return 0;
}

void *car(void *args)
{
    Car *macchina = ((Car *)args);

    printf("initialized car %d\n", macchina->id);

    while (1)
    {
        DBGpthread_mutex_lock(&biglietteria, "lock error");
        macchina->currentBiglietto = takeABiglietto(macchina->type);
        printf("la macchina %d ha preso il biglietto => %d\n", macchina->id, macchina->currentBiglietto);
        DBGpthread_mutex_unlock(&biglietteria, "unlock error");

        DBGpthread_mutex_lock(&ponte, "lock ponte error");
        while (checkThisMachineNeedsToWaitOrari(macchina) && checkTicket(macchina->currentBiglietto, macchina->type))
        {
            DBGpthread_cond_wait(&cond, &ponte, "wainting error");
        }

        carIsInHalfOfPonte = 0;
        carTypeOnPonte = macchina->type;
        if (macchina->type == A)
        {
            minCardPresentForOrari++;
        }
        else if (macchina->type == O)
        {
            minCardPresentForAnti++;
        }

        printf("la macchina %d sale nella prima metà del ponte\n", macchina->id);

        DBGsleep(TIMETOFIRSTHALFPONTE, "non ho sonno _firstHalf_");

        carIsInHalfOfPonte = 1;

        DBGpthread_cond_signal(&cond, "no signal allowed ;^( ");

        DBGpthread_mutex_unlock(&ponte, "unlock ponte errorr");


        carIsInHalfOfPonte = 1;

        DBGpthread_mutex_lock(&ponte, "lock ponte error");
        printf("la macchina %d inizia la seconda metà del ponte\n", macchina->id);
        sleep(TIMETOSECONDHALFPONTE);

        carTypeOnPonte = NONE;

        if (macchina->type == A)
        {
            bigliettoDistributore[1]--;
            minCardPresentForAnti--;
        }
        else if (macchina->type == O)
        {
            bigliettoDistributore[0]--;
            minCardPresentForOrari--;
        }

        printf("la macchina %d scende nella seconda metà del ponte\n", macchina->id);

        carIsInHalfOfPonte = -1;

        DBGpthread_mutex_unlock(&ponte, "unlock ponte errorr");

        printf("la macchina %d si va a fare un giro nel CERCHIO\n", macchina->id);

        DBGsleep(TIMETOCIRCLE, "no sleep allowed");
    }

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int rc, i;
    Car *createdCar;
    pthread_t th;
    inizializeVariable();

    for (i = 0; i < NCarOrarie; i++)
    {
        createdCar = (Car *)malloc(sizeof(Car));
        if (!createdCar)
            PrintERROR_andExit(1, "no car created");
        createdCar->id = i;
        createdCar->type = O;
        createdCar->currentBiglietto = -1;
        rc = pthread_create(&th, NULL, car, (void *)createdCar);
        if (rc)
            PrintERROR_andExit(rc, "creation error");
    }

    for (i = NCarOrarie; i < NCarOrarie + NCarAntiorarieOrarie; i++)
    {
        createdCar = (Car *)malloc(sizeof(Car));
        if (!createdCar)
            PrintERROR_andExit(1, "no car created");
        createdCar->id = i;
        createdCar->type = A;
        createdCar->currentBiglietto = -1;
        rc = pthread_create(&th, NULL, car, (void *)createdCar);
        if (rc)
            PrintERROR_andExit(rc, "creation error");
    }

    pthread_exit(NULL);
    return 0;
}
