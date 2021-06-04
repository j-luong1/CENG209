#ifndef PROJECTILE_H
#define PROJECTILE_H

// Constants
#define GRAV 9.81           // Gravity  //error #6
#define PI   3.1415926      // Pi       //error #7

// Function Prototypes
void ProjectileInformation(void);
double ConvertToRadians(double degrees);
double ConvertToDegrees(double rads);
double FlightTime(double velocity, double anglerads);
double Height(double velocity, double anglerads, double time);
double MaxHeight(double velocity, double anglerads);
double Range(double velocity, double anglerads);
void RangeTable(void);
void HeightTable(void);

#endif
