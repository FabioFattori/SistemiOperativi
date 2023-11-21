#include <math.h>

static double save = -1;

double dimezzaCos(double x){
	
	save = cos(x)/2;
	
	return save;
}
