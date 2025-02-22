#include <stdlib.h>

#define PI 3.14159
#define getmax(a,b) a>b?a:b

namespace interfaceNUCLEO
{
	bool START=true;
		
	void inicializa_NUCLEO(void)
	{
		
	}
	
	float random_float(float min, float max) 
	{
		return ((float)rand() / RAND_MAX) * (max - min) + min;
	}
}