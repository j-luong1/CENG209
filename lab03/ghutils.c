#include <stdio.h>
#include "ghutils.h"
#include "ghcontrol.h"
#include <time.h>

//Function Prototypes

time_t now;

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

void GhDisplayReadings()
{
	now = time(NULL);
	printf("\n%s",ctime(&now));
	printf("Readings\tT: %3.1lfC\tH: %3.0lf%\t P: %5.1lfmb\tL: %3.0lflux\n", GhGetTemperature(), GhGetHumidity(), GhGetPressure(), GhGetLight());
	double creadings[SENSORS] = {};
	GhDelay (GHUPDATE);
}

//void GhDisplaySetpoints(void);

//void DisplayControls(void);

