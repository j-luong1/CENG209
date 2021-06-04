//	Lab05.c : Defines the entry point  for the console application
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>

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
//	GhControllerInit(); //Prints header to the screen
	if (GhControllerInit() == ABNORMAL)
	{
		GhControllerShutdown(ABNORMAL);
	}
	while (1)
	{
		now = time(NULL);
		GhGetSetpoints();
		GhGetReadings(readings, creadings);
		heater = &tempc;
		humidifier = &humidc;
		light = &lightc;

		GhDisplayReadings(now, readings, creadings);		
		GhDisplaySetpoints();
		GhSetControls(heater, humidifier, light, readings, tempc, humidc, lightc);
		GhDisplayControls(heater, humidifier, light);
		if (digitalRead(HSH_MCP23017_PINBASE+GHCOFF) == 1)
		{
			break;
		}
		GhDelay(GHUPDATE);
	}
	printf("\n\nPress ENTER to continue...");
	getchar();
	return GhControllerShutdown(NORMAL);
}
