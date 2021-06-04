#include "projectile.h"
#include "stdio.h"
#include "math.h"

void ProjectileInformation(void)
{
	char operation;

	printf("\n\nProjectile Information\n\n");
	while(1)
	{
		printf("\n\nEnter 'H' for a Height Table\n");
		printf("Enter 'R' for a Range Table\n");
		printf("Enter 'Q' to Quit\n\n");
		scanf(" %c",&operation);
		switch(operation)
		{
			case 'H':
			case 'h':
				HeightTable();
                break; // error #1
			case 'R':
			case 'r':
				RangeTable();
				break;
			case 'Q':
			case 'q':
				return;
			default:
				printf("\nInvalid Selection ..Try Again\n");

		}
		operation = '\0';
	}

}

double ConvertToRadians(double degrees)
{
	return degrees * PI / 180; // error # 2
}

double ConvertToDegrees(double rads)
{
	return rads * 180 / PI; // error # 3
}

double FlightTime(double velocity, double anglerads)
{
	return (2 * velocity * sin(anglerads)) / GRAV;
}

double MaxHeight(double velocity, double anglerads)
{
	double halftime;
	halftime = FlightTime(velocity,anglerads)/2;
	return (velocity*sin(anglerads)*halftime) - (0.5*GRAV*halftime*halftime);
}

double Height(double velocity, double anglerads, double time)
{
	return (velocity*time*sin(anglerads)) - (0.5*GRAV*time*time); //error #5
}

double Range(double velocity, double anglerads)
{
	return (velocity * velocity * sin(2*anglerads)) / GRAV; //error #9
}

void RangeTable(void)
{
	int i=0,j=0;
	double Vmax = 0;
	double Amax = 0;

	printf("\nEnter the Projectile Velocity: ");
	scanf(" %lf", &Vmax);
	printf("\nEnter the Projectile Angle: ");
	scanf(" %lf", &Amax);

	printf("\nRange Table (m - Velocity vs Angle)\n");
	printf("\nFiring Angle(Degrees)->\n");
	printf("Velocity(m/s)    \n");
	printf("        ");
	for(i=5; i <= Amax; i+=5) //error #10
	{
		printf("%8d",i);
	}
	printf("\n");
	for(i=10; i <= Vmax; i+=10)
	{
		printf("%8d",i);
		for(j=5; j <= Amax; j+=5)
		{
			printf("%8.1lf",Range(i,ConvertToRadians(j))); //error #8
		}
		printf("\n");
	}
}

void HeightTable(void)
{
	int i=0;
	double H; //error #4
	double Velocity = 0;
	double Angle = 0;

	printf("\nEnter the Projectile Velocity: ");
	scanf(" %lf", &Velocity);
	printf("\nEnter the Projectile Angle: ");
	scanf(" %lf", &Angle);

	printf("\nHeight Table (m - Height vs Time)\n");
	printf("\nTime(s)->\n");
	printf("Height(m)\n");
	for(i=5; i <= FlightTime(Velocity,ConvertToRadians(Angle)); i+=5)
	{
		printf("%8d",i);
	}
	printf("\n");
	for(i=5; i <= FlightTime(Velocity,ConvertToRadians(Angle)); i+=5)
	{
		H = Height(Velocity,ConvertToRadians(Angle),i);
		if(H>0)
		{
			printf("%8.1lf",H);
		}
	}
	printf("\n");
}
