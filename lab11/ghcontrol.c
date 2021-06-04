#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <string.h>

#include "ghcontrol.h"
#include "ghutils.h"
#include "hshbme280.h"

const char alarmnames[NALARMS][ALARMNMSZ] = {"No Alarms","High Temperature","Low Temperature","High Humidity","Low Humidity","High Pressure","Low Pressure","HighLight","Low Light"};

//	Functions

int GhControllerInit(void)
{
#if SIMULATE
	srand((unsigned)time(NULL));
#endif
	wiringPiSetup();
	mcp23017Setup (HSH_MCP23017_PINBASE, HSH_MCP23017_I2CADR);
	pcf8591Setup (HSH_PCF8591_PINBASE, HSH_PCF8591_I2CADR);
	BME280Setup();	

// 	Setup Control Indicators
	pinMode (HSH_MCP23017_PINBASE+HEATERON, OUTPUT);
	pinMode (HSH_MCP23017_PINBASE+HUMIDIFIERON, OUTPUT);
	pinMode (HSH_MCP23017_PINBASE+GHCOFF, INPUT);

	SetLED(GREEN);
	GhDisplayHeader("Jonathan Luong");

//	if (arecord == NULL) {	return ABNORMAL;}

	return NORMAL;
}

int GhControllerShutdown (int status)
{
//	digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 0);
//	digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 0);	
	if (status == ABNORMAL)
	{
		digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 0);
		digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 0);
		SetLED(RED);
	}
	else
	{
		SetLED(OFF);
	}
	return status;
}

void SetLED(int colour)
{
	pinMode(GEN00, OUTPUT);
	pinMode(GEN01, OUTPUT);

	digitalWrite(GEN00, LOW);
	digitalWrite(GEN01, LOW);
	if (colour == RED)
	{
		digitalWrite(GEN00, HIGH);
	}
	else
	{
		digitalWrite(GEN01, HIGH);
	}
}

readings_s GhGetReadings(void)
{
	struct readings now = {0};
	
	now.rtime = time(NULL);
	now.temperature = GhGetTemperature();
	now.humidity = GhGetHumidity();
	now.pressure = GhGetPressure();
	now.light = GhGetLight();
	return now;
}

setpoint_s GhRetrieveSetpoints(char * fname)
{
	struct setpoints spts = {0.0};
	FILE *fp;
	fp = fopen(fname, "r");
	if (fp == NULL)
	{
		return spts;
	}
	fread(&spts, sizeof(struct setpoints), 1, fp);
	return spts;
}

control_s GhSetControls (setpoint_s spoints, readings_s rdata)
{
	control_s cset;
	if (rdata.temperature < spoints.temperature)
	{
		cset.heater = 1;
		digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 1);
	}
	else
	{
		cset.heater = 0;
		digitalWrite(HSH_MCP23017_PINBASE+HEATERON, 0);
	}
	if (rdata.humidity < spoints.humidity)
	{
		cset.humidifier = 1;
		digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 1);
	}
	else
	{
		cset.humidifier = 0;
		digitalWrite(HSH_MCP23017_PINBASE+HUMIDIFIERON, 0);
	}
	if (rdata.light < spoints.light)
	{
		cset.light = spoints.light-rdata.light;
	}
	return cset;
}

setpoint_s GhGetSetpoints(setpoint_s spoints)
{
	spoints = GhRetrieveSetpoints("setpoints.dat");
	if (spoints.temperature == 0.0)	{spoints.temperature = STEMP;}
	if (spoints.humidity == 0.0)	{spoints.humidity = SHUMID;}
	if (spoints.light == 0.0)		{spoints.light = SLIGHT;}
	GhSaveSetpoints("setpoints.dat", spoints);
	return spoints;
}

double GhGetTemperature(void)
{
//#if SIMTEMP
//	return 55;
	return GhGetRandom(USTEMP-LSTEMP)-LSTEMP;
//#else
//	return GetBME280TempC();
//#endif
}

double GhGetHumidity(void)
{
//#if SIMHUMID
//	return 1;
	return GhGetRandom(USHUMID);
//#else
//	return GetBME280Humidity();
//#endif
}

double GhGetPressure(void)
{
double press;
//#if SIMPRESS
	return GhGetRandom(USPRESS-LSPRESS)+LSPRESS;
//#else
//	press = PaTomB(GetBME280Pressure());
//	return press;
//#endif
}

double GhGetLight(void)
{
#if 1
	return GhGetRandom(USLIGHT);
#else
	return GetBME280Light();
#endif
}
//		return analogRead(HSH_PCF8591_PINBASE+HSH_PCF8591_A0IN);

alarmlimit_s GhSetAlarmLimits(void)
{
	alarmlimit_s calarm;
	calarm.hight = UATEMP;
	calarm.lowt = LATEMP;
	calarm.highh = UAHUMID;
	calarm.lowh = LAHUMID;
	calarm.highp = UAPRESS;
	calarm.lowp = LAPRESS;
	calarm.highl = UALIGHT;
	calarm.lowl = LALIGHT;
	return calarm;
}

alarm_s * GhSetAlarms(alarm_s * head, alarmlimit_s alarmpt, readings_s rdata)
{
	int i;
	
	if(rdata.temperature >= alarmpt.hight)
	{
		GhSetOneAlarm(HTEMP,rdata.rtime,rdata.temperature,head);
	}
	else
	{
		head=GhClearOneAlarm(HTEMP,head);
	}
	if(rdata.temperature <= alarmpt.lowt)
	{
		GhSetOneAlarm(LTEMP,rdata.rtime,rdata.temperature,head);
	}
	else
	{
		head=GhClearOneAlarm(LTEMP,head);
	}
	if(rdata.humidity >= alarmpt.highh)
	{
		GhSetOneAlarm(HHUMID,rdata.rtime,rdata.humidity,head);
	}
	else
	{
		head=GhClearOneAlarm(HHUMID,head);
	}
	if(rdata.humidity <= alarmpt.lowh)
	{
		GhSetOneAlarm(LHUMID,rdata.rtime,rdata.humidity,head);
	}
	else
	{
		head=GhClearOneAlarm(LHUMID,head);
	}
	if(rdata.pressure >= alarmpt.highp)
	{
		GhSetOneAlarm(HPRESS,rdata.rtime,rdata.pressure,head);
	}
	else
	{
		head=GhClearOneAlarm(HPRESS,head);
	}
	if(rdata.pressure <= alarmpt.lowp)
	{
		GhSetOneAlarm(LPRESS,rdata.rtime,rdata.pressure,head);
	}
	else
	{
		head=GhClearOneAlarm(LPRESS,head);
	}
	if(rdata.light >= alarmpt.highl)
	{
		GhSetOneAlarm(HLIGHT,rdata.rtime,rdata.light,head);
	}
	else
	{
		head=GhClearOneAlarm(HLIGHT,head);
	}
	if(rdata.light <= alarmpt.lowl)
	{
		GhSetOneAlarm(LLIGHT, rdata.rtime,rdata.light,head);
	}
	else
	{
		head=GhClearOneAlarm(LLIGHT,head);
	}
}
int GhSetOneAlarm(alarm_e code, time_t atime, double value, alarm_s * head)
{
	alarm_s * cur;
	alarm_s * last;
	
	cur = head;

	if(cur->code != NOALARM)
	{
		while(cur != NULL)
		{
			if(cur->code == code) 
			{
				return 0;
			}
			last = cur;
			cur = cur->next;
		}
		cur = (alarm_s *) calloc(1,sizeof(alarm_s));
		last = (alarm_s *) calloc(1,sizeof(alarm_s));

		if (cur == NULL) 
		{
			return 0;
		}
		last->next = cur;
	}
	cur->code = code;
	cur->atime = atime;
	cur->value = value;
	cur->next = NULL;

	return 1;
}

alarm_s * GhClearOneAlarm(alarm_e code, alarm_s * head)
{
	alarm_s * cur;
	alarm_s * last;
	
	cur = head;
	last = head;

	if((cur->code == code) && (cur->next == NULL))
	{
		cur->code = NOALARM;
		return head;
	}

	if((cur->code == code) && (cur->next != NULL))
	{
		head = cur->next;
		free(cur);
		return head;
	}
	
	while(cur != NULL)
	{
		if(cur->code == code)
		{
			last->next = cur->next;
			free(cur);
			return head;
		}
		last = cur;
		cur = cur->next;
	}
	return head;
}
