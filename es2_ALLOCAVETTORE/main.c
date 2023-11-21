#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(){
	int* vet;
	int k;
	
	allocaVettore(vet);
	
	
		
	for(k=0;k<10;k++){
		printf("before => %d\n",vet[k]);
		vet[k]=-19+k;
		printf("after => %d\n",vet[k]);
	}
	
	return 0;
}
