#include "dht11.h"

void dht11_getInfo(int *tem, int *hum)
{
	static int count = 0;
	
	*tem = count % 5 + 20;
	*hum = count % 4 + 50;
	
	count++;
}
