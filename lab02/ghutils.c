#include <stdio.h>
#include "ghutils.h"
#include <time.h>

void GhDisplayHeader (const char * sname)
{
	printf("\n%s's Tech153 Greenhouse Controller\n", sname);
}

int GhGetRandom(int range)
{
	return rand() % range;
}

void GhDelay(int milliseconds)
{
	long wait;
	clock_t now,start;

	wait = milliseconds*(CLOCKS_PER_SEC/1000);
	start = clock();
	now = start;
	while(	(now-start) < wait)
	{
		now = clock();
	}
}
