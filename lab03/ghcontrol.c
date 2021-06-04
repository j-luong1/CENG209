#include <stdio.h>
#include "ghcontrol.h"
#include <time.h>

double creadings[SENSORS] = {0.0};

void GhControllerInit(void)
{
	GhGetRandom();
	GhSetSetpoints();
	GhDisplayHeader("Jonathan Luong");
}

double GhGetTemperature(void)
{
	double y = 20.0;
	return y;
}

double GhGetHumidity(void)
{
	double y = 55.0;
	return y;
}

double GhGetPressure(void)
{
	double y = 1013.0;
	return y;
}

double GhGetLight(void)
{
	double y = 100.0;
	return y;
}

void GhGetReadings(double readings[SENSORS])
{
	readings[TEMPERATURE] = GhGetTemperature();
	readings[HUMIDITY] = GhGetHumidity();
	readings[PRESSURE] = GhGetPressure();
	readings[LIGHT] = GhGetLight();
	double creadings[SENSORS] = {};
}

//void GhGetControls(void);

//void GhSetControls(void);

//void GhSetpoints(void);

void GhSetSetpoints(void)
{
}
