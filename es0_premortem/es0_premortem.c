
/*  i simboli _THREAD_SAFE _REENTRANT _POSIX_C_SOURCE=200112L
*   sono stati definiti nella riga di comando per la compilazione con il gcc
*   nel Makefile
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 100
#define WAITING_TIME 1000

typedef struct{
	pthread_t parentID;
	int currentID;
}arg;

void *CreateTreadh(void *p_index)
{
	int rc;
	
	printf("\n parentID = %ld , currentID = %d\n", ((arg*)p_index)->parentID, ((arg*)p_index)->currentID);
	
	((arg*)p_index)->currentID++;
	usleep(WAITING_TIME);
	
	if(((arg*)p_index)->currentID < NUM_THREADS){
		
		rc=pthread_create (&((arg*)p_index)->parentID, NULL, CreateTreadh, p_index );
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
		}
		((arg*)p_index)->parentID = pthread_self();
	}else{
		free(p_index); 
	}
	
	
	pthread_exit (NULL);
}

int main()
{
	int rc;       /* notare la variabile puntatore p */
	arg* toPass = (arg*)malloc(sizeof(arg));
	if(toPass==NULL) {
			perror("malloc failed: ");
			pthread_exit (NULL);
	}
	
	toPass->currentID = 1;

		      
		
		toPass->parentID =pthread_self();
		printf("Creating thread %ld\n", toPass->parentID);
		rc = pthread_create (&toPass->parentID, NULL, CreateTreadh, toPass );  /* NOTARE l'ultimo parametro */
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
		}

	

	printf("fine main \n"); 
	fflush(stdout);
	
	pthread_exit (NULL);  /* provare a commentare questa riga */
	return(0);
}
