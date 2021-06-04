#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>

#include "ghcontrol.h"
#include "ghutils.h"


//	Global Variables

//	Functions

int GhControllerInit(void)
{
#if SIMULATE
	srand((unsigned)time(NULL));
#endif
	wiringPiSetup();
	mcp23017Setup (HSH_MCP23017_PINBASE, HSH_MCP23017_I2CADR);
	pcf8591Setup (HSH_PCF8591_PINBASE, HSH_PCF8591_I2CADR);	

	// Setup Control Indicators
	pinMode (HSH_MCP23017_PINBASE+HEATERON, OUTPUT);
	pinMode (HSH_MCP23017_PINBASE+HUMIDIFIERON, OUTPUT);
	pinMode (HSH_MCP23017_PINBASE+GHCOFF, INPUT);

	SetLED(GREEN);
	GhSetSetpoints();
	GhDisplayHeader("Jonathan Luong");
	return NORMAL;
}

int GhControllerShutdown (int status)
{
//	digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 0);
//	digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 0);	
	if (status == ABNORMAL)
	{
		digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 0);
		digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 0);
		SetLED(RED);
	}
	else
	{
		SetLED(OFF);
	}
	return status;
}

void SetLED(int colour)
{
	pinMode(GEN00, OUTPUT);
	pinMode(GEN01, OUTPUT);

	digitalWrite(GEN00, LOW);
	digitalWrite(GEN01, LOW);
	if (colour == RED)
	{
		digitalWrite(GEN00, HIGH);
	}
	else
	{
		digitalWrite(GEN01, HIGH);
	}
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
	if ((readings[0]) < STEMP)
	{
		tempc = ON;
		digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 1);
	}
	else
	{
		tempc = OFF;
		digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 0);
	}
	if ((readings[HUMIDITY]) < SHUMID)
	{
		humidc = ON;
		digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 1);
	}
	else
	{
		humidc = OFF;
		digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON,0);
	}
	lightc = SLIGHT-(readings[LIGHT]);	
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
	if (SIMULATE == ON)
	{
	return GhGetRandom(USTEMP-LSTEMP)-LSTEMP;
	}
	else
	{
		return 20.0;
	}
}

double GhGetHumidity(void)
{
	if (SIMULATE == ON)
	{
		return GhGetRandom(USHUMID);
	}
	else
	{
		return 55.0;
	}
}

double GhGetPressure(void)
{
	if (SIMULATE == ON)
	{
		return GhGetRandom(USPRESS-LSPRESS)+LSPRESS;
	}
	else
	{
		return 1013.0;
	}
}

double GhGetLight(void)
{
	if (SIMLIGHT != ON)
	{
		return analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A0IN);	
	}
	else
	{
		return GhGetRandom(USLIGHT);
	}
}

