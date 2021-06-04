#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ghcontrol.h"
#include "ghutils.h"


//	Global Variables

//	Functions

void GhControllerInit(void)
{
	srand((unsigned)time(NULL));
	GhSetSetpoints();
	GhDisplayHeader("Jonathan Luong");
}

void GhGetReadings(double readings[SENSORS], double creadings[SENSORS])
{
	readings[TEMPERATURE] = GhGetTemperature();
	readings[HUMIDITY] = GhGetHumidity();
	readings[PRESSURE] = GhGetPressure();
	readings[LIGHT] = GhGetLight();
}

void GhGetControls(void);

void GhSetControls(int * heater, int * humidifier, int * light, double readings[SENSORS], int tempc, int humidc, int lightc)
{
		heater = &tempc;
		humidifier = &humidc;
		light = &lightc;
		lightc = SLIGHT-(readings[3]);
		if ((readings[0]) < STEMP)
		{
			tempc = ON;
		}
		else
		{
			tempc = OFF;
		}
		if ((readings[HUMIDITY]) < SHUMID)
		{
			humidc = ON;
		}
		else
		{
			humidc = OFF;
		}
		printf("Controls\tHeater: %d\tHumidifier: %d\tLights: %d\n", *heater, *humidifier, *light);
}

void GhGetSetpoints(void)
{
}

void GhSetSetpoints(void)
{
}


double GhGetTemperature(void)
{
	return GhGetRandom(USTEMP-LSTEMP)-LSTEMP;
}

double GhGetHumidity(void)
{
	return GhGetRandom(USHUMID);
}

double GhGetPressure(void)
{
	return GhGetRandom(USPRESS-LSPRESS)+LSPRESS;
}

double GhGetLight(void)
{
	return GhGetRandom(USLIGHT);
}
