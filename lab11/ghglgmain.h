#ifndef GHGLGMAIN_H
#define GHGLGMAIN_H
#include "GlgApi.h"
#include "ghcontrol.h"

// CONSTANTS
#define UPDATE_INTERVAL 5000	// Initially 5 second update

// Function Prototypes
/* Function prototypes */
void Input(GlgObject viewport,GlgAnyType client_data,GlgAnyType call_data);
void UpdateControls(GlgAnyType data,GlgIntervalID * id);
void GhShowAlarms(alarm_s * head);

#endif
