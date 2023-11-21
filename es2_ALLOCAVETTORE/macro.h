#include <stdlib.h>
#define allocaVettore(PTR) \
do{ \
	PTR=(int*)malloc(10*sizeof(int)); \
	if(PTR != NULL){ \
		int j; \
		for(j=0;j<10;j++){ \
			PTR[j]=-1000+j; \
		} \
	} \
}while(0); 
