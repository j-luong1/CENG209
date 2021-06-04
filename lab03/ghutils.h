#ifndef GHUTILS_H
#define GHUTILS_H
#include <time.h>
#include "ghcontrol.h"

// CONSTANTS

#define GHUPDATE 5000

// Function Prototypes
void GhDisplayHeader (const char * sname);

int GhGetRandom(int range);

void GhDelay(int milliseconds);

void GhDisplayReadings();

void GhDisplaySetpoints(void);

void GhDisplayControls(void);

#endif
