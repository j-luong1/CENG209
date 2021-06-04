#ifndef GHCONTROL_H
#define GHCONTROL_H
#include <time.h>

// Constants

#define SENSORS 4
#define TEMPERATURE 0
#define HUMIDITY 1
#define PRESSURE 2
#define LIGHT 3

// Function Prototypes

void GhControllerInit(void);

void GhGetReadings(double readings[SENSORS]);

void GhGetControls(void);

void GhSetControls(void);

void GhSetpoints(void);

void GhSetSetpoints(void);

double GhGetTemperature(void);

double GhGetHumidity(void);

double GhGetPressure(void);

double GhGetLight(void);

void GhGetReading(double readings[SENSORS]);

#endif
