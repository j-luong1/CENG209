// lab03.c : Defines the entry point for the console application.
#include <stdio.h>
#include "ghutils.h"
#include "ghcontrol.h"
#include <stdlib.h>
#include <time.h>

// Function Prototypes

time_t now;

int main(void)
{
	GhControllerInit();	//Prints header to the screen
	while(1) 
	{
//		GhGetSetpoints();
//		GhGetReadings();
//		GhSetControls();
		GhDisplayReadings();
//		GhDisplaySetpoints();
//		GhDisplayControls();
	}
	printf("\n\nPress ENTER to continue...");
	getchar();

	return 1;
}

