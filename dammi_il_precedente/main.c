#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "dammi_il_precedente.h"

int main(){
	int nEstrazioni = 0;		
	srand(time(NULL));
	
	while(1){
		nEstrazioni++;
		if(dammi_il_precedente(rand()) % 10 == 3){
			break;
		}
	}
	
	printf("n. Estrazioni => %d\n",nEstrazioni);
	return 0;	
}
