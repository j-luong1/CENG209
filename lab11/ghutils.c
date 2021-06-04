#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ghutils.h"
#include "ghcontrol.h"


//	Global Variables
time_t now;

//	Functions

void GhDisplayHeader (const char * sname)
{
	printf("\n%s's Tech153 Greenhouse Controller\n", sname);
}

int GhGetRandom (int range)
{
	return rand() % range;
}

void GhDelay (int milliseconds)
{
	long wait;
	clock_t now, start;

	wait = milliseconds *(CLOCKS_PER_SEC/1000);
	start = clock();
	now = start;
	while ( (now-start) < wait)
	{
		now = clock();
	}
}

int GhLogData(char *fname, struct readings ghdata)
{
	FILE *fp;
	char ltime[25];
	fp = fopen(fname,"a");
	strcpy(ltime, ctime(&ghdata.rtime));
	ltime[3, 7, 10, 19] = ',';
	fprintf(fp, "\n%.24s,%3.1lf,%3.1lf,%5.1lf,%3.0lf", ltime, ghdata.temperature, ghdata.humidity, ghdata.pressure, ghdata.light);
	if(fp == NULL)
	{
		printf("Can't open file, data not retrieved!\n");
		return 0;
	}
	fclose(fp);
	return 1;
}

int GhSaveSetpoints (char * fname, struct setpoints spts)
{
	FILE *fp;
	fp = fopen(fname, "w");
	if (fp == NULL)
	{
	return 0;
	}
	fwrite(&spts, sizeof(struct setpoints), 1, fp);
	return 1;
}

void GhDisplayReadings(time_t rtime, double dreads[SENSORS], double creadings[SENSORS])
{
		now = time(NULL);
		printf("\n%s\n",ctime(&now));
		printf("Readings\t T: %3.1lfC\t H: %3.0lf%%\t P: %5.1lfmb\t L: %3.0lflux\n", dreads[TEMPERATURE], dreads[HUMIDITY], dreads[PRESSURE], dreads[LIGHT]);
}

void GhDisplaySetpoints(void)
{
	printf("Setpoints\tsT: %3.1lfC\tsH: %3.0lf%%\t\t\tsL: %3.0lflux\n", STEMP, SHUMID, SLIGHT);
}

void GhDisplayControls(int * heater, int * humidifier, int * light)
{
//	printf("Controls\tHeater: %d\tHumidifier: %d\tLights: %d\n", *heater, *humidifier, *light);
}

double PaTomB(double pa)
{
	pa = pa/100.0;
	return pa;
}
