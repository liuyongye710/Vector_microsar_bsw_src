/*
********************************************************************************
*
*  File name: BswM_Callout_Stubs.c
*
*  Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : yong.zhang/2018.12.13
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.0
* Author/Date : yong.zhang/2020.07.02
* Change: Add release software number.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Include
********************************************************************************
*/
#include "BswM.h"
#include "CanTrcv.h"
#include "ComM.h"
#include "Dcm.h"
#include "J1939Tp.h"
#include "NvM.h"
#include "string.h"
#include "PduR.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
/*
********************************************************************************
* Function Name: 
*
* Explanation: 
*
* param: none
*
* retval: none
********************************************************************************
*/
#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"
FUNC(void, BSWM_CODE) BswM_CDS_Init(void)
{
  CDS_Init();
}


FUNC(void, BSWM_CODE) BswM_CanIf_Init(void)
{
  CanIf_Init(NULL_PTR);
  Can_Config_Init();/* WangM */
}


FUNC(void, BSWM_CODE) BswM_CanNm_Init(void)
{
  //CanNm_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_CanSM_Init(void)
{
  CanSM_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_CanTp_Init(void)
{
  CanTp_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_CanTrcv_Init(void)
{
  CanTrcv_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_CheckShutDown_MainFunction(void)
{
   if(0)
   {
      BswM_RequestMode(BSWM_GENERIC_ESH_Req_CheckWakeUpEvent, BSWM_GENERICVALUE_ESH_ModeWakeUpEventValid);
   }
   else
   {
      BswM_RequestMode(BSWM_GENERIC_ESH_Req_CheckWakeUpEvent, BSWM_GENERICVALUE_ESH_ModeWakeUpEventInvalid);
   }
}


FUNC(void, BSWM_CODE) BswM_ComMRequestFullComMode(void)
{
 ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
 ComM_RequestComMode(1, COMM_FULL_COMMUNICATION);
 ComM_RequestComMode(2, COMM_FULL_COMMUNICATION);
 ComM_RequestComMode(3, COMM_FULL_COMMUNICATION);
}


FUNC(void, BSWM_CODE) BswM_ComM_Init(void)
{
  ComM_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_ComMRequestNoComMode(void)
{
 ComM_RequestComMode(0, COMM_NO_COMMUNICATION);
 ComM_RequestComMode(1, COMM_NO_COMMUNICATION);
 ComM_RequestComMode(2, COMM_NO_COMMUNICATION);
 ComM_RequestComMode(3, COMM_NO_COMMUNICATION);
}


FUNC(void, BSWM_CODE) BswM_Com_Init(void)
{
  Com_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_Dcm_Init(void)
{
  Dcm_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_Dem_Init(void)
{
  Dem_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_Dcm_Shutdown(void)
{
  Dem_Shutdown();
}


FUNC(void, BSWM_CODE) BswM_Fee_Init(void)
{
  Fee_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_J1939Tp_Init(void)
{
  J1939Tp_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_Init_Nvm_CancelWrite_All(void)
{
  NvM_CancelWriteAll();
}


FUNC(void, BSWM_CODE) BswM_NvM_Init(void)
{
  NvM_Init(NULL_PTR);
}


FUNC(void, BSWM_CODE) BswM_Init_Nvm_Read_All(void)
{
  NvM_ReadAll();
  while((BswM_NvMJobState[0] == NVM_REQ_PENDING))
  {
	NvM_MainFunction();
	Fee_MainFunction();
	Fls_MainFunction();
  }
  memcpy(0x51800000, &dsm_nvm_data[0], 0x8000);
}


FUNC(void, BSWM_CODE) BswM_Init_Nvm_Write_All(void)
{
  uint16 i = 0;

  memcpy(&dsm_nvm_data[0], 0x51800000, 0x8000);
  
  for(i = NVM_COMPILED_CONFIG_ID; i < NVM_NUM_OF_BLOCK_TOTAL; i++)
  {
    NvM_SetRamBlockStatus(i, TRUE);
  }
  NvM_WriteAll();
}


FUNC(void, BSWM_CODE) BswM_PduR_Init(void)
{
  PduR_Init(&PduR_PBConfigTable);
  //PduR_DisableRouting(1, TRUE);
}


FUNC(void, BSWM_CODE) BswM_XcpInit(void)
{
  Xcp_Init();
  CanXcp_Init();
}



#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"

