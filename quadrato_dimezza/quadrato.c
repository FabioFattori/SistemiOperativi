#include <math.h>

static double save = -1;

double quadrato(double x){
	
	save = x * x;
	
	return save;
}
