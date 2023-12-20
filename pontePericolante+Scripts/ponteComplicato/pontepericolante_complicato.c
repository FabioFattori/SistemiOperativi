/* file:  ponte_pericolante_complicato.c */

#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif

#include "printerror.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMAUTOORARIO 4
#define NUMAUTOANTIORARIO 4
#define INDICESENSOORARIO 0
#define INDICESENSOANTIORARIO 1

/* variabili condivise da proteggere */
int bigliettoDistributore[2];
int biglietto[2];
int indiceAutoSuPonte;

/* aggiungete le variabili che credete vi servano */

/* variabili per la distribuzione del biglietto */
pthread_mutex_t mutexDistributori;
pthread_mutex_t mutexPrimaPartePonte;
pthread_mutex_t mutexSecondaPartePonte;
pthread_cond_t waintingCond;

/* aggiungete le vostre variabili per la sincronizzazione */

void *Auto(void *arg)
{
	char Plabel[128];
	intptr_t indiceAuto;
	int myBiglietto, indiceSenso;
	char senso; /* O orario  A antiorario */

	/* aggiungete le vostre variabili locali */

	indiceAuto = (intptr_t)arg;
	if (indiceAuto < NUMAUTOORARIO)
	{
		senso = 'O';
		indiceSenso = INDICESENSOORARIO;
	}
	else
	{
		senso = 'A';
		indiceSenso = INDICESENSOANTIORARIO;
	}

	sprintf(Plabel, "%c%" PRIiPTR "", senso, indiceAuto);

	while (1)
	{
		/* auto prende il biglietto */
		DBGpthread_mutex_lock(&mutexDistributori, Plabel);
		myBiglietto = bigliettoDistributore[indiceSenso];
		bigliettoDistributore[indiceSenso]++;
		DBGpthread_mutex_unlock(&mutexDistributori, Plabel);

		printf("auto %s ha preso biglietto %i \n", Plabel, myBiglietto);
		fflush(stdout);

		/* completare */
		DBGpthread_mutex_lock(&mutexPrimaPartePonte, "DBGpthread_mutex_lock failed");
		if (indiceAutoSuPonte == -1)
		{
			indiceAutoSuPonte = indiceSenso;
		}
		while (biglietto[indiceSenso] != myBiglietto || indiceAutoSuPonte != indiceSenso)
		{
			DBGpthread_cond_wait(&waintingCond, &mutexPrimaPartePonte, Plabel);
		}

		printf("auto %s attraversa ponte biglietto %i \n", Plabel,
			   myBiglietto);
		fflush(stdout);

		/* completare */
		DBGpthread_mutex_unlock(&mutexPrimaPartePonte, "DBGpthread_mutex_unlock failed");

		sleep(1); /* attraverso la prima meta' del ponte */

		/* completare */
		DBGpthread_mutex_lock(&mutexSecondaPartePonte, "DBGpthread_mutex_lock failed");
		printf("auto %s supera meta\' ponte \n", Plabel);
		fflush(stdout);

		/* completare */
		biglietto[indiceSenso]++;
		DBGpthread_cond_broadcast(&waintingCond, "DBGpthread_cond_broadcast failed");
		if(indiceSenso != indiceAutoSuPonte){
			printf("auto %s esce dal ponte \n", Plabel);
		}
		sleep(1); /*attraverso seconda meta' del ponte */
		if(indiceSenso == indiceAutoSuPonte){
			printf("auto %s esce dal ponte \n", Plabel);
		}

		/* completare */
		if(biglietto[INDICESENSOANTIORARIO] - biglietto[INDICESENSOORARIO] >= 1){
			indiceAutoSuPonte = INDICESENSOORARIO;
		}else if(biglietto[INDICESENSOANTIORARIO] - biglietto[INDICESENSOORARIO] <= -1){
			indiceAutoSuPonte = INDICESENSOANTIORARIO;
		}
		DBGpthread_mutex_unlock(&mutexSecondaPartePonte, "DBGpthread_mutex_lock failed");
		printf("auto %s gira intorno\n", Plabel);
		fflush(stdout);
		sleep(10); /* faccio il giro attorno a Villa Inferno */
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t th;
	int rc;
	intptr_t i;

	rc = pthread_mutex_init(&mutexDistributori, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_mutex_init failed");

	/* configuro le variabili */
	for (i = 0; i < 2; i++)
	{
		bigliettoDistributore[i] = 0;
		biglietto[i] = 0;
	}

	/* completare con l'inizializzazione delle vostre variabili */
	indiceAutoSuPonte = -1;
	rc = pthread_mutex_init(&mutexPrimaPartePonte, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_mutex_init failed");
	rc = pthread_cond_init(&waintingCond, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_cond_init failed");

	for (i = 0; i < NUMAUTOORARIO + NUMAUTOANTIORARIO; i++)
	{
		rc = pthread_create(&th, NULL, Auto, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	pthread_exit(NULL);
	return (0);
}
