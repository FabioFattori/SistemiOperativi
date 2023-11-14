#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
char str[]="9876543210";
int main(void) {
	str[1]='f';
	printf("str= %s \n", str ); /* stampa 9f76543210 ? */
	fflush(stdout);
	return(0);
}

