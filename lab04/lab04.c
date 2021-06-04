//	Lab04.c : Defines the entry point  for the console application
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ghutils.h"
#include "ghcontrol.h"

//	Global Variables
time_t now;
double readings[SENSORS] = {0.0};
double dreads[SENSORS] = {0.0};
double creadings[SENSORS] = {0.0};


//	Function Prototypes


int main(void)
{
	int *heater, * humidifier, *light;
	int tempc, humidc, lightc;
	srand((unsigned)time(NULL));
	GhControllerInit();	//Prints header to the screen
	while (1)
	{
		now = time(NULL);
		GhGetSetpoints();
		GhGetReadings(readings, creadings);
		heater = &tempc;
		humidifier = &humidc;
		light = &lightc;
		//Where GhSetControls should be
		GhDisplayReadings(now, readings, creadings);		
		GhDisplaySetpoints();
		GhSetControls(heater, humidifier, light, readings, tempc, humidc, lightc);
		GhDisplayControls(heater, humidifier, light);
		GhDelay(GHUPDATE);
	}
	printf("\n\nPress ENTER to continue...");
	getchar();
	return 1;
}
