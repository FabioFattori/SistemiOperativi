/* file:  formicai.c */

#include <unistd.h> /* exit() etc */
#include <stdlib.h> /* random  srandom */
#include <stdio.h>
#include <string.h> /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h>	  /* timespec{} for pselect() */
#include <limits.h>	  /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <stdint.h>	  /* uint64_t intptr_t */
#include <inttypes.h> /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "printerror.h"
#include "DBGpthread.h"

#define NUMFORMICAI 5
#define NUMFACHIRI (NUMFORMICAI - 1)

#define SECATTESA 2

/* dati da proteggere */
/* variabili per la sincronizzazione */
pthread_mutex_t mutexPalo;
pthread_mutex_t mutexFormicaio[NUMFORMICAI];

void attendi(int min, int max)
{
	int secrandom = 0;
	if (min > max)
		return;
	else if (min == max)
		secrandom = min;
	else
		secrandom = min + (random() % (max - min + 1));
	do
	{
		/* printf("attendi %i\n", secrandom);fflush(stdout); */
		secrandom = sleep(secrandom);
		if (secrandom > 0)
		{
			printf("sleep interrupted - continue\n");
			fflush(stdout);
		}
	} while (secrandom > 0);
	return;
}

void *Fachiro(void *arg)
{
	char Plabel[128];
	intptr_t indice;
	int formicaioattuale, formicaiosuccessivo;

	indice = (intptr_t)arg;
	sprintf(Plabel, "Fachiro%" PRIiPTR "", indice);

	/* prendo possesso del formicaio che ha il mio stesso indice */
	formicaioattuale = indice;
	DBGpthread_mutex_lock(&mutexFormicaio[formicaioattuale], Plabel);

	/* fachiro dice su quale formicaio si trova */
	printf("fachiro %s si trova sul formicaio %i \n", Plabel, formicaioattuale);
	fflush(stdout);

	while (1)
	{

		/* aspetto qualche secondo prima di saltare */
		attendi(SECATTESA, SECATTESA);

		/* fachiro definisce su quale formicaio deve andare */
		formicaiosuccessivo = (formicaioattuale + 1) % NUMFORMICAI;

		/* fachiro inizia PASSAGGIO sul formicaio successivo */
		/* COMPLETARE DA QUI IN AVANTI  */

		DBGpthread_mutex_lock(&mutexFormicaio[formicaiosuccessivo], "DBGpthread_mutex_lock failed");
		DBGpthread_mutex_lock(&mutexPalo, "DBGpthread_mutex_lock failed");

		DBGpthread_mutex_unlock(&mutexFormicaio[formicaioattuale], "DBGpthread_mutex_lock failed");
		printf("fachiro %s si appoggia al palo e inizia passaggio verso %i \n", Plabel, formicaiosuccessivo);
		fflush(stdout);

		/* fachiro ha iniziato il passaggio e
		   impiega tra 1 e 3 secondi per passare
		   sul formicaio successivo
		*/
		attendi(1, 3);

		/* stampo a video che sono arrivato sul palo successivo */
		printf("fachiro %s si trova completamente sul formicaio %i e molla il palo \n", Plabel, formicaiosuccessivo);
		fflush(stdout);

		DBGpthread_mutex_unlock(&mutexPalo, "DBGpthread_mutex_lock failed");

		/* COMPLETARE FINO A QUI */

		/* ho finito il passaggio,
		 * il formicaio successivo e' diventato l'attuale */
		/* formicaioattuale = (formicaioattuale+1) % NUMFORMICAI; */
		formicaioattuale = formicaiosuccessivo;
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t th;
	int rc;
	intptr_t i = 0;
	int seme;

	seme = time(NULL);
	srandom(seme);

	/* INIZIALIZZATE LE VOSTRE VARIABILI CONDIVISE / fate voi */
	rc = pthread_mutex_init(&mutexPalo, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_mutex_init failed");
	for (i = 0; i < NUMFORMICAI; i++)
	{
		rc = pthread_mutex_init(&mutexFormicaio[i], NULL);
		if (rc)
			PrintERROR_andExit(rc, "pthread_mutex_init failed");
	}
	/* blocco tutti i massi */
	for (i = 0; i < NUMFORMICAI; i++)
		DBGpthread_mutex_lock(&mutexFormicaio[i], "main");

	/* CREAZIONE PTHREAD
	   consento a ciascun fachiro di prendere possesso di un formicaio,
	   quello di indice pari all'indice del fachiro,
	   invece rimane bloccato dal main l'ultimo formicaio,
	   quello di indice NUMFACHIRI.
	*/

	for (i = NUMFACHIRI - 1; i >= 0; i--)
	{
		DBGpthread_mutex_unlock(&mutexFormicaio[i], "main");
		rc = pthread_create(&th, NULL, Fachiro, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	/* aspetto 2 secondi */
	attendi(2, 2);
	/* libero il formicaio numero NUMFORMICAI-1  cioe' NUMFACHIRI */
	DBGpthread_mutex_unlock(&mutexFormicaio[NUMFORMICAI - 1], "main");

	pthread_exit(NULL);
	return (0);
}
