// Lab02.c : Defines the entry point for the console application.
#include <stdio.h>
#include "ghutils.h"
#include <stdlib.h>
#include <time.h>

// Function Prototypes

time_t now;
// srand ((unsigned) time(NULL));

int main(void)
{
	GhDisplayHeader("Jonathan Luong");	//Prints header to the screen
	while(1) 
	{
		now = time(NULL);
		printf("\n%sTemperature: %3.1lf\n",ctime(&now), GhGetRandom(100)-50.0);
		GhDelay (GHUPDATE);
	}
	printf("\n\nPress ENTER to continue...");
	getchar();

	return 1;
}

