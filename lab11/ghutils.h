#ifndef GHUTILS_H
#define GHUTILS_H
#include <time.h>

#include "ghcontrol.h"

//	CONSTANTS

#define GHUPDATE 5000
typedef enum {NOCOLOUR, RED, YELLOW, GREEN} ledcolour_e;

//	FUNCTION PROTOTYPES
void GhDisplayHeader (const char * sname);

int GhGetRandom (int range);

void GhDelay (int milliseconds);

int GhLogData (char *fname, struct readings ghdata);

int GhSaveSetpoints(char *fname, struct setpoints spts);

void GhDisplayReadings(time_t rtime, double dreads[SENSORS], double creadings[SENSORS]);

void GhDisplaySetpoints(void);

void GhDisplayControls(int * heater, int * humidifier, int * light);

double PaTomB(double pa);

#endif
