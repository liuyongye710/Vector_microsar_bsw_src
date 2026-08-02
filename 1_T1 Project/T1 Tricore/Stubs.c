/*
 * stubs.c
 *
 *  Created on: 2020-6-15
 *      Author: Jeremy Ma
 */

#include "Platform_Types.h"
#include "Mcal_WdgLib.h"
void Mcal_SafeErrorHandler(void)
{
	while(1);
}
void Appl_UnlockEndinit(void)
{
	Mcal_ResetENDINIT();
}

void Appl_LockEndinit(void)
{
	Mcal_SetENDINIT();
}

void Appl_Unlockinit(void)
{
	Mcal_ResetENDINIT();
}

void Appl_Lockinit(void)
{
	Mcal_SetENDINIT();
}
static volatile uint32 mydummy;
void ApplCanWaitSetMCR(void)
{
  uint32 i;
  for (i=0; i<10000; i++)
  {
    mydummy++;
  }
}

void Appl_Det_ReportError(uint32 ErrorType)
{
    while(1);
}

