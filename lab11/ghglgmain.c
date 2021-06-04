//
//  This example demonstrates how to use GLG control widgets as they are,
//  without emdedding them into another GLG drawing, and handle user
//  interaction.
//
//  The drawing name is GhControls.g.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GlgApi.h"
#include "ghglgmain.h"
#include "ghcontrol.h"
#include "ghutils.h"

// Top level global variables
GlgAppContext AppContext;
GlgObject GhDrawing;
GlgLong UpdateInterval = UPDATE_INTERVAL;
struct readings creadings = {0};
alarm_s * arecord;

// Defines a platform-specific program entry point
#include "GlgMain.h"

int GlgMain(int argc,char *argv[],GlgAppContext InitAppContext )
{
	// Initialization Section
	AppContext = GlgInit( False, InitAppContext, argc, argv );
	GlgSetDResource(AppContext,"$config/GlgOpenGLMode",0.); // Disable openGL
	GhControllerInit();
//	if (GhControllerInit() == ABNORMAL)
//	{
//		GhControllerShutdown(ABNORMAL);
//	}
	arecord = (alarm_s *) calloc(1,sizeof(alarm_s));
	if (arecord == NULL)
	{
		printf("\nCannot allocate memory\n");
		return 0;
	}
//	GhSetSetpoints();
	// Load a drawing from the file.
	GhDrawing = GlgLoadWidgetFromFile( "GhGUI.g" );

	if(!GhDrawing) { exit( 1 ); }

	// Setting widget dimensions using world coordinates [-1000;1000].
	GlgSetGResource(GhDrawing,"Point1",-600.,-600.,0.);
	GlgSetGResource(GhDrawing,"Point2",600.,600.,0.);

	// Setting the window name (title).
	GlgSetSResource(GhDrawing,"ScreenName","Greenhouse Controls" );

	// Add Input callback to handle user interraction in the GLG control.
	GlgAddCallback(GhDrawing,GLG_INPUT_CB,(GlgCallbackProc)Input,NULL );

	// Paint the drawing.
	GlgInitialDraw(GhDrawing);
	GlgAddTimeOut(AppContext,UpdateInterval,(GlgTimerProc)UpdateControls,NULL );
	return (int) GlgMainLoop( AppContext );
}
//
// This callback is invoked when user interacts with input objects in GLG
// a  drawing, such as a slider, dial or a button.
//
void Input(GlgObject GhDrawing,GlgAnyType client_data,GlgAnyType call_data)
{
	GlgObject message_obj;
	char * format,* action,* origin, * full_origin;
	double pstate,svalue;
	message_obj = (GlgObject) call_data;

	// Get the message's format, action and origin.
	GlgGetSResource(message_obj,"Format", &format);
	GlgGetSResource(message_obj,"Action",&action);
	GlgGetSResource(message_obj,"Origin",&origin);
	GlgGetSResource(message_obj,"FullOrigin",&full_origin);

	// Handle window closing. May use GhDrawing's name.
	if(strcmp(format,"Window") == 0 &&
		strcmp(action,"DeleteWindow") == 0)
	{ exit(0); }

	// Retreive a current data value from the slider
	if( strcmp( origin, "Update1" ) == 0 )
	{
		GlgGetDResource(GhDrawing, "Update1/Value", &svalue );
		if(svalue <= 1.0) { svalue = 1.0; }
		GlgSetDResource(GhDrawing,"Update1/Value",(GlgLong) svalue);
		UpdateInterval = (GlgLong) svalue * 1000;
	}
}

//
// Timer procedure to update controls, and drawing values
//
void UpdateControls(GlgAnyType data,GlgIntervalID * id)
{
	int logged;
	time_t current;
	setpoint_s sets = {0};
	struct controls ctrl = {0};
	alarmlimit_s alimits = {0};

	readings_s creadings = GhGetReadings();
	logged = GhLogData("ghdata.txt", creadings);
	alimits = GhSetAlarmLimits();
	GhSetAlarms(arecord, alimits, creadings);
//	GhGetSetpoints(sets);
	sets.temperature = STEMP;
	sets.humidity = SHUMID;
	sets.light = SLIGHT;
	ctrl = GhSetControls(sets, creadings);

	GlgSetDResource(GhDrawing,"Light1/Value",creadings.light);
 	GlgSetDResource(GhDrawing,"Light2/Value",ctrl.light);
	GlgSetDResource(GhDrawing,"Temp1/Value",creadings.temperature);
	GlgSetDResource(GhDrawing,"Humid1/Value",creadings.humidity);
	GlgSetDResource(GhDrawing,"Press1/Value",creadings.pressure);
	if (ctrl.heater == 1)
	{
		GlgSetDResource(GhDrawing,"Heater/Visibility",1);
	}
	else
	{
		GlgSetDResource(GhDrawing,"Heater/Visibility",0);
	}
	if (ctrl.humidifier == 1)
	{
		GlgSetDResource(GhDrawing,"Humidifier/Visibility",1);
	}
	else
	{
		GlgSetDResource(GhDrawing,"Humidifier/Visibility",0);
	}
	GhShowAlarms(arecord);
	GlgUpdate(GhDrawing);
	GlgAddTimeOut(AppContext,UpdateInterval,(GlgTimerProc)UpdateControls,NULL );
}

void GhShowAlarms(alarm_s * head)
{
	int i;
	char amsg[45];
	alarm_s * cur;

	extern const char alarmnames[NALARMS][ALARMNMSZ];
	GlgSetSResource(GhDrawing,"talarm/String","");
	GlgSetSResource(GhDrawing,"halarm/String","");
	GlgSetSResource(GhDrawing,"palarm/String","");
	GlgSetSResource(GhDrawing,"lalarm/String","");

	cur = head;

	while (cur != NULL)
	{
		for (i = 1; i<NALARMS; i++)
		{
			if(cur->code != NOALARM)
			{
				sprintf(amsg,"%s %s",alarmnames[cur->code],ctime(&cur->atime));
		switch(cur->code)
				{
				case 1:
				case 2:
				GlgSetSResource(GhDrawing,"talarm/String",amsg);
				break;
				case 3:
				case 4: 
				GlgSetSResource(GhDrawing,"halarm/String",amsg);
				break;
				case 5:
				case 6: 
				GlgSetSResource(GhDrawing,"palarm/String",amsg);
				break;
				case 7:
				case 8: 
				GlgSetSResource(GhDrawing,"lalarm/String",amsg);
				break;
				}
			}
		}
		cur = cur->next;
	}
}
