#include "dimezza.h"
#include "quadrato.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static double salva=-1;

int main(){
	
	salva = quadrato(dimezzaCos(13.17));
	
	printf("value => %f",salva);
	
	return 0;
}
