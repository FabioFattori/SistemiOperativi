/* file:  prod_ConsA+B.c
   NProduttori con K ConsumatoriA e L ConsumatoriB
   che si scambiano prodotti mediante un unico Buffer MA
	 i due consumatori devono prelevare INSIEME.
   Ipotizzo che la durata di deposito e prelievo NON sia infinitesima
	 ma devo far eseguire deposito e prelievo in sezione critica.
   - utilizza tre pthread_cond_var (una per Prod e due per Cons).
   - ed una quarta pthread_cond_var (per aspettare un secondo Cons).
	 - usa una variabile statoBuffer per sapere se aspetto
		un Prod o un ConsA o un ConsB.
   - sveglia i pthread solo quando hanno qualcosa da fare.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include "printerror.h"
#include "DBGpthread.h"

#define NUMPROD 6
#define NUMCONSA 4
#define NUMCONSB 4
#define NUMBUFFER 1 /* NON MODIFICARE MAI */

#define TIPOCONSA 0 /* che tipo di consumatore sono */
#define TIPOCONSB 1

/* valori assunti dallo statoBuffer */
#define SERVEPROD 1	 /* serve un produttore che depositi */
#define SERVEConsA 2 /* serve che arrivi un Consumatore di Tipo A */
#define SERVEConsB 3 /* serve che arrivi un Consumatore di Tipo B */
#define PRELIEVO 4	 /* due cons un A e un B stanno prelevando assieme */

/* dati da proteggere */
uint64_t valGlobale = 0;
char statoBuffer = SERVEPROD; /* buffer vuoto, serve produttore che depositi */

/* variabili per la sincronizzazione */
pthread_mutex_t mutex;
pthread_cond_t condProd, condConsA, condConsB, condSecondo;
int numConsInPrelievo = 0; /* consumatori che stanno prelevando */

void *Produttore(void *arg)
{
	char Plabel[128];
	int indice;
	uint64_t valProdotto = 0;

	indice = *((int *)arg);
	free(arg);
	sprintf(Plabel, "P%d", indice);

	while (1)
	{
		/* QUI IL PRODUTTORE PRODUCE IL DATO, un intero.
		   supponiamo che il produttore impieghi circa
		   un secondo a produrre il dato
		*/
		DBGsleep(1, Plabel);
		printf("ProdA %s PRODUCE dato %lu\n", Plabel, valProdotto + 1);
		fflush(stdout);

		valProdotto++;

		DBGpthread_mutex_lock(&mutex, Plabel);

		while (statoBuffer != SERVEPROD)
		{
			DBGpthread_cond_wait(&condProd, &mutex, Plabel);
		}
		/* riempie il buffer col dato prodotto prima */
		valGlobale = valProdotto;
		statoBuffer = SERVEConsA;

		DBGsleep(1, Plabel);
		printf("Prod %s inserisce %lu \n", Plabel, valGlobale);
		fflush(stdout);

		DBGpthread_cond_signal(&condConsA, Plabel);

		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&mutex, Plabel);
	}
	pthread_exit(NULL);
}

void *Consumatore(void *arg)
{
	uint64_t val;
	char Clabel[128];
	int indice, tipoCons, indicetemp;

	indicetemp = *((int *)arg);
	free(arg);
	indice = indicetemp % NUMCONSA;

	tipoCons = indicetemp / NUMCONSA;
	/* NOTARE CHE ORA LA VARIABILE tipoCons DICE CHE TIPO
		DI CONSUMATORE E' IL NOSTRO CONSUMATORE
		se tipo==0 e' ConsB, se tipo==1 e' consB */
	if (tipoCons == TIPOCONSA)
		sprintf(Clabel, "CA%i", indice);
	if (tipoCons == TIPOCONSB)
		sprintf(Clabel, "CB%i", indice);

	while (1)
	{
		DBGpthread_mutex_lock(&mutex, Clabel);

		/* se non sono il tipo richiesto aspetto */
		if (tipoCons == TIPOCONSA)
		{
			while (statoBuffer != SERVEConsA)
				DBGpthread_cond_wait(&condConsA, &mutex, Clabel);
		}
		else
		{ /* tipoCons==TIPOCONSB */
			while (statoBuffer != SERVEConsB)
				DBGpthread_cond_wait(&condConsB, &mutex, Clabel);
		}
		/* sono stato svegliato e sono del tipo giusto.
			 - se sono del tipo A devo aspettare il tipo B,
			 - se sono del tipo B allora il tipo B e' gia' arrivato
			   e dobbiamo cominciare a consumare entrambi
			*/
		/* AGGIUNGERE CODICE */

		if (tipoCons == TIPOCONSA)
		{
			/* aspetto arrivo del secondo consumatore (B) */
			statoBuffer = SERVEConsB;
			/* AGGIUNGERE CODICE */
			numConsInPrelievo = 1;
			printf("consumatore A %i aspetta un consumatore B\n", indice);
			DBGpthread_cond_signal(&condConsB, "cond signal error");
			while (numConsInPrelievo == 1)
			{
				DBGpthread_cond_wait(&condSecondo, &mutex, "cond wait error");
			}
		}
		else
		{ /* tipoCons==TIPOCONSB */
			printf("consumatore B %i arriva e sveglia consumatore A\n", indice);

			/* sveglio il primo cons arrivato */
			statoBuffer = PRELIEVO;
			numConsInPrelievo = 2;
			/* AGGIUNGERE CODICE */
			DBGpthread_cond_signal(&condSecondo, "cond signal error");
		}
		/* rilascio mutua esclusione e prendo
			la mia parte di buffer ASSIEME all'altro */
		/* AGGIUNGERE CODICE */
		DBGpthread_mutex_unlock(&mutex, Clabel);
		/* prelievo */
		val = valGlobale;
		printf("Cons %s prende %lu \n", Clabel, val);
		fflush(stdout);
		DBGsleep(1, Clabel);

		/* prendo la mutua esclusione per svuotare
			il buffer, cambiarne lo stato e svegliare chi serve.
			*/
		DBGpthread_mutex_lock(&mutex, Clabel);
		/* FINE AGGIUNTA CODICE */

		numConsInPrelievo--;
		if (numConsInPrelievo == 0)
		{
			statoBuffer = SERVEPROD;
			DBGpthread_cond_signal(&condProd, Clabel);
		}
		/* FINE AGGIUNTA CODICE */
		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&mutex, Clabel);

		/* fuori da mutua esclusione, uso il dato
		   supponiamo che ci voglia 1 secondo
		*/
		printf("Cons %s USA dati %lu \n", Clabel, val);
		fflush(stdout);
		DBGsleep(2, Clabel);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t th;
	int rc, i, *intptr;

	rc = pthread_cond_init(&condProd, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_cond_init failed");
	rc = pthread_cond_init(&condConsA, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_cond_init failed");
	rc = pthread_cond_init(&condConsB, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_cond_init failed");
	rc = pthread_cond_init(&condSecondo, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_cond_init failed");
	rc = pthread_mutex_init(&mutex, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_mutex_init failed");

	/* all'inizio i Cons devono aspettare il primo Prod */
	statoBuffer = SERVEPROD;

	for (i = 0; i < NUMCONSA + NUMCONSB; i++)
	{
		intptr = malloc(sizeof(int));
		if (!intptr)
		{
			printf("malloc failed\n");
			exit(1);
		}
		*intptr = i;
		rc = pthread_create(&th, NULL, Consumatore, (void *)intptr);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	for (i = 0; i < NUMPROD; i++)
	{
		intptr = malloc(sizeof(int));
		if (!intptr)
		{
			printf("malloc failed\n");
			exit(1);
		}
		*intptr = i;
		rc = pthread_create(&th, NULL, Produttore, (void *)intptr);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	pthread_exit(NULL);
	return (0);
}
