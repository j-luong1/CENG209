#ifndef GHCONTROL_H
#define GHCONTROL_H
//#include <time.h>

//	CONSTANTS
#define GHUPDATE 	5000
#define ON 		1
#define OFF 		0
#define NORMAL		1
#define ABNORMAL	0
#define GHCOFF		2

//	On/Off Pins
#define GEN00		0
#define GEN01		1
#define NOCOLOUR	0
#define RED		1
#define	GREEN		3

//	I2C Device Addresses
#define HSH_RTC_I2CADR		0x68
#define HSH_MCP23017_I2CADR	0x20
#define HSH_PCF8591_I2CADR	0x48
#define HSH_BME280_I2CADR	0x76

//	wiringPi Device Pin Base
#define HSH_MCP23017_PINBASE	100
#define HSH_PCF8591_PINBASE	200
#define HSH_BME280_PINBASE	300
#define HSH_PCF8591_A0IN	3

//	Controls
#define HEATERON	0
#define HUMIDIFIERON	1

//	Sensor Values
#define TEMPERATURE 	0
#define HUMIDITY 	1
#define PRESSURE 	2
#define LIGHT 		3
#define SENSORS 	4


//	Simulated Values
#define SIMULATE 	1
#define USTEMP 		50
#define LSTEMP 		-10
#define USHUMID 	100
#define LSHUMID 	0
#define USPRESS 	1016
#define LSPRESS 	985
#define USLIGHT 	255
#define LSLIGHT 	0
#define SIMLIGHT	0

//	Set Values
#define STEMP 		25.0
#define SHUMID 		55.0
#define SLIGHT 		255.0

//	FUNCTION PROTOTYPES

int GhControllerInit(void);

int GhControllerShutdown(int status);

void SetLED(int colour);

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
