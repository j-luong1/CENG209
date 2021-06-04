// Lab01.c : Defines the entry point for the console application.
#include <stdio.h>

// Function Prototypes
void GhDisplayHeader(const char * sname);

int main(void)
{
	GhDisplayHeader("Jonathan Luong");	//Prints header to the screen
	printf("\n\nPress ENTER to continue...");
	getchar();

	return 1;
}

void GhDisplayHeader(const char * sname)
{
	printf("\n%s's TECH153 Greenhouse Controller\n", sname);
}
