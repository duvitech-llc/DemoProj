/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.28 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : BASIC_HelloWorld.c
Purpose     : Simple demo drawing "Hello world"
Requirements: WindowManager - ( )
MemoryDevices - ( )
AntiAliasing  - ( )
VNC-Server    - ( )
PNG-Library   - ( )
TrueTypeFonts - ( )
----------------------------------------------------------------------
*/
#include <Windows.h>
#include "GUI.h"
#include "DisplayThread.h"
#include "FirstpersonDataStructures.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)
static bool bRunning = false;

static bool Initialize(void);

extern unsigned char nuke_png[8251];

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {

	bRunning = Initialize();
	int x0 = 160;
	int y0 = 180;
	int i;
	char ac[4];
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_SetPenSize(5);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(&GUI_FontComic18B_ASCII);
	GUI_SetColor(GUI_BLACK);
	GUI_DrawArc(x0, y0, 150, 150, -30, 210);

	for (i = 0; i <= 23; i++) {
		float a = (-30 + i * 10)*3.1415926 / 180;
		int x = -141 * cos(a) + x0;
		int y = -141 * sin(a) + y0;
		if (i % 2 == 0)
			GUI_SetPenSize(5);
		else
			GUI_SetPenSize(4);
		GUI_DrawPoint(x, y);
		if (i % 2 == 0) {
			x = -123 * cos(a) + x0;
			y = -130 * sin(a) + y0;
			sprintf(ac, "%d", 10 * i);
			GUI_SetTextAlign(GUI_TA_VCENTER);
			GUI_DispStringHCenterAt(ac, x, y);
		}
	}

	GUI_PNG_Draw(nuke_png, 8251, 50, 50);
	while (bRunning){

		Sleep(100);
	}
}

static bool Initialize(void){

	GUI_Init();

	//
	// Check if recommended memory for the sample is available
	//
	if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
		GUI_ErrorOut("Not enough memory available.");
		return false;
	}

	return true;
}

/*************************** End of file ****************************/

