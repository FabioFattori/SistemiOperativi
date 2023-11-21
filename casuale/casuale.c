#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(){
	int counter=0;
	srand(time(NULL));
	
	while(1){
		counter++;
		if((rand()) % 10 == 3){
			break;
		}
	}
	printf("n. extractions => %d\n",counter);
	return 0;
}
