#ifndef GHCONTROL_H
#define GHCONTROL_H
#include <time.h>

//	CONSTANTS
#define GHUPDATE 	5000
typedef enum {OFF, ON} switch_e;
typedef enum {ABNORMAL, NORMAL, GHCOFF} status_e;

//	On/Off Pins
typedef enum {GEN00, GEN01} power_e;

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
typedef enum {TEMPERATURE, HUMIDITY, PRESSURE, LIGHT, SENSORS} sensors_e;

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

//	Alarm Settings
#define NALARMS		9
#define LATEMP		10
#define UATEMP		30
#define LAHUMID		25
#define UAHUMID		70
#define LAPRESS		985
#define UAPRESS		1016
#define LALIGHT		0
#define UALIGHT		255
typedef enum { NOALARM,HTEMP,LTEMP,HHUMID,LHUMID,HPRESS,LPRESS,HLIGHT,LLIGHT} alarm_e;

#define ALARMNMSZ	18

//	Structures

typedef struct readings
{
	time_t rtime;
	double temperature;
	double humidity;
	double pressure;
	double light;
}readings_s;

typedef struct setpoints
{
	double temperature;
	double humidity;
	double light;
}setpoint_s;

typedef struct controls
{
	int heater;
	int humidifier;
	int light;
}control_s;

typedef struct alarmlimits
{
	double hight;
	double lowt;
	double highh;
	double lowh;
	double highp;
	double lowp;
	double highl;
	double lowl;
}alarmlimit_s;

typedef struct alarms
{
	alarm_e code;
	time_t atime;
	double value;
	struct alarms * next;
}alarm_s;

//	FUNCTION PROTOTYPES

//	Initial Functions
int GhControllerInit(void);
int GhControllerShutdown(int status);
void SetLED(int colour);

//	Functions for Controls
control_s GhSetControls(setpoint_s spoints, readings_s rdata);

//	Functions for Setpoints
setpoint_s GhGetSetPoints(setpoint_s spoints);
setpoint_s GhRetrieveSetPoints (char * fname);

//	Functions for Readings
readings_s GhGetReadings(void);
double GhGetTemperature(void);
double GhGetHumidity(void);
double GhGetPressure(void);
double GhGetLight(void);

//	Functions for Alarms
alarmlimit_s GhSetAlarmLimits(void);
alarm_s * GhSetAlarms(alarm_s * head, alarmlimit_s alarmpt, readings_s rdata);

int GhSetOneAlarm(alarm_e code, time_t atime, double value, alarm_s * head);
alarm_s * GhClearOneAlarm(alarm_e code, alarm_s * head);

#endif
