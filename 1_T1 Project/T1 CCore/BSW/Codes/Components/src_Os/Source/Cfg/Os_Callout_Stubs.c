/*
********************************************************************************
*
*  File name:	Os_Callout_Stubs.c
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os.h"
#include "Os_Core.h"
#include "Os_Lcfg.h"
#include "Os_Error.h"
#include "T1_AppInterface.h"/* for T1 */
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
#define OS_START_SEC_CODE 
#include "Os_MemMap.h"
/*
********************************************************************************
* Function Name: ErrorHook
*
* Explanation: User hook for centralized application error handling.
*
* param: None.
*
* retval: None.
********************************************************************************
*/
#if(OS_CFG_ERRORHOOK_SYSTEM == STD_ON)
void ErrorHook(StatusType Error)
{
}
#endif

/*
********************************************************************************
* Function Name: ShutdownHook
*
* Explanation: User hook which is called during system shut down.
*
* param: Fatalerror: error occurred.
*
* retval: None.
********************************************************************************
*/
#if(OS_CFG_SHUTDOWNHOOK_SYSTEM == STD_ON)
void ShutdownHook(StatusType Fatalerror)
{
    EcuM_Shutdown();/* WangM */
}
#endif
/*
********************************************************************************
* Function Name: StartupHook
*
* Explanation: User hook which is called after OS startup and before scheduling.
*
* param: None.
*
* retval: None.
********************************************************************************
*/
#if(OS_CFG_STARTUPHOOK_SYSTEM == STD_ON)
void StartupHook(void)
{
}
#endif
/*
********************************************************************************
* Function Name: ProtectionHook
*
* Explanation: User hook for protection error handling.
*
* param: Fatalerror: The error which caused the call to the protection hook.
*
* retval: PRO_IGNORE :Do nothing.
*         PRO_TERMINATETASKISR :forcibly terminate the Task/Category 2 ISR which causes the problem.
*         PRO_TERMINATEAPPL :Forcibly terminate the OS-Application the Task/Category 2 ISR belong.
*         PRO_TERMINATEAPPL_RESTART :Optional with restart.
*         PRO_SHUTDOWN :Shutdown the system.
********************************************************************************
*/
#if(OS_CFG_PROTECTIONHOOK_SYSTEM == STD_ON)
ProtectionReturnType ProtectionHook(StatusType Fatalerror)
{
    return PRO_SHUTDOWN;
}
#endif
void Os_Task_Idle_Task_Core0(void)
{
    while(TRUE)
    {
        T1_AppBackgroundHandler();/* for T1 */
    }
}
void Os_Task_Idle_Task_Core1(void)
{
    while(TRUE)
    {
        T1_AppBackgroundHandler();/* for T1 */
    }
}
void Os_Task_Idle_Task_Core2(void)
{
    while(TRUE)
    {
        T1_AppBackgroundHandler();/* for T1 */
    }
}
#define OS_STOP_SEC_CODE 
#include "Os_MemMap.h"

