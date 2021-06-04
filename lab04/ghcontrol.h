#ifndef GHCONTROL_H
#define GHCONTROL_H
#include <time.h>

//	CONSTANTS
#define GHUPDATE 5000
#define ON 1
#define OFF 0

#define TEMPERATURE 0
#define HUMIDITY 1
#define PRESSURE 2
#define LIGHT 3
#define SENSORS 4

#define SIMULATE 1
#define USTEMP 50
#define LSTEMP -10
#define USHUMID 100
#define LSHUMID 0
#define USPRESS 1016
#define LSPRESS 985
#define USLIGHT 255
#define LSLIGHT 0

#define STEMP 25.0
#define SHUMID 55.0
#define SLIGHT 255.0

//	FUNCTION PROTOTYPES

void GhControllerInit(void);

void GhGetReadings(double readings[SENSORS], double creadings[SENSORS]);

void GhGetControls(void);

void GhSetControls(int * heater, int * humidifier, int * light, double readings[SENSORS], int tempc, int humidc, int lightc);

void GhGetSetpoints(void);

void GhSetSetpoints(void);


double GhGetTemperature(void);

double GhGetHumidity(void);

double GhGetPressure(void);

double GhGetLight(void);

#endif
