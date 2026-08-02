/********************************************************************************
*
*  File name:   Vol_DiagForCan.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Vol_DiagForCanLin.h"
#include "PduR.h"
#include "IoHwAb.h"
#include "Can.h"
#include "ComM.h" 
#include "CanIf.h"
#include "Dcm.h"   
/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Global  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/
extern Can_DriverStateType g_eCan_DriverState;
extern uint8 LinSM_Sts_Cur;
extern uint8 LinSM_Sts_Req;
/*********************************************************************************
*   Local Variables
*********************************************************************************/

/*********************************************************************************
*   Global Functions
*********************************************************************************/
float IoHwAb_Get_Voltage(void)
{
    float Vbat = 0;
    uint16 Vbat_ori = 0;

//    Vbat_ori = IoHwAb_AdcIn_ReadChannel(I_A_UC_VBR_FLT_FB);
	Vbat = Vbat_ori/4096*50/0.091;

    return 24;
}

void Voltage_CheckForControlCAN(void)
{
    float Vbat = 0;
    uint8 ComM_Mode = COMM_NO_COMMUNICATION;
    static boolean ComM_Status = FALSE;

    Vbat = IoHwAb_Get_Voltage();
    ComM_GetCurrentComMode(0, &ComM_Mode);

    if((FALSE == ComM_Status) && (COMM_FULL_COMMUNICATION == ComM_Mode))
    {
        ComM_Status = TRUE;
    }
    if(TRUE == ComM_Status)
    {
        if((Vbat > V_CAN_LIN_HIGH) || (Vbat < V_CAN_LIN_LOW))
        {
            if(g_eCan_DriverState == CAN_READY)
            {
                Can_SetControllerMode(0, CAN_CS_STOPPED);
                Can_SetControllerMode(1, CAN_CS_STOPPED);
                Can_SetControllerMode(2, CAN_CS_STOPPED);
                Can_SetControllerMode(3, CAN_CS_STOPPED);
                Can_SetControllerMode(4, CAN_CS_STOPPED);
                Can_DeInit();
            }
        }
        else
        {
            if(g_eCan_DriverState != CAN_READY)
            {
                Can_Init(&Can_Config);
                Can_SetControllerMode(0, CAN_CS_STARTED);
                Can_SetControllerMode(1, CAN_CS_STARTED);
                Can_SetControllerMode(2, CAN_CS_STARTED);
                Can_SetControllerMode(3, CAN_CS_STARTED);
                Can_SetControllerMode(4, CAN_CS_STARTED);
            }
        }
    }
}

void Voltage_CheckForControlDiag(void)
{
    static boolean PduR_State = FALSE;
    static uint32  Diag_TimerCnt = 0;
    static boolean Diag_Start_State = FALSE;
    float  Vbat = 0;
    Vbat = IoHwAb_Get_Voltage();

    if(FALSE == Diag_Start_State)
    {
        if((Vbat >= V_DIAG_LOW) && (Vbat <= V_DIAG_HIGH))
        {
            Diag_TimerCnt++;
            if(T_DIAG_START == Diag_TimerCnt)
            {
                PduR_EnableRouting(1);
                Diag_TimerCnt = 0;
                Diag_Start_State = TRUE;
                PduR_State = TRUE;
            }
        }
        else
        {
            Diag_TimerCnt = 0;
        }
    }
    else
    {
        if((Vbat >= V_DIAG_LOW) && (Vbat <= V_DIAG_HIGH))
        {
            if(FALSE == PduR_State)
            {
                Diag_TimerCnt++;
                if(T_DIAG_RESTART == Diag_TimerCnt)
                {
                    PduR_EnableRouting(1);
                    Diag_TimerCnt = 0;
                    PduR_State = TRUE;
                }
            }
        }
        else
        {
            if(TRUE == PduR_State)
            {
                PduR_DisableRouting(1, TRUE);
                PduR_State = FALSE;
            }
        }
    }
}

void Voltage_CheckForControlLIN(void)
{
    float Vbat = 0;

    Vbat = IoHwAb_Get_Voltage();

    if((Vbat > V_CAN_LIN_HIGH) || (Vbat < V_CAN_LIN_LOW))
    {
        LinSM_Sts_Req = V_LIN_SCHEDULE_0;
    }
    else
    {
        LinSM_Sts_Req = V_LIN_SCHEDULE_1;
    }
}
