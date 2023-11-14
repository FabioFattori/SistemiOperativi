#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define STAMPAPRODOTTO( X, Y ) printf("%i\n",(X)*(Y));
int main(void) {
	STAMPAPRODOTTO( 3, 2 ); /* stampa 6 */
	STAMPAPRODOTTO( 3+5, 2 ); /* stampa 16 */
	return(0);
}
