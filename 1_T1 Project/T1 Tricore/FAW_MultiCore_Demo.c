
#include "EcuM.h"
#include "Os.h"
#include "Rte_Main.h"
/*多核工程，配置P33.7,P33.8,P33.9分别指示三个核的运行状态，翻转周期为200ms*/
#include "T1_AppInterface.h"
#include "CanIf.h"
#include "ComM.h"
#include "Com.h"

int main (void)
{
		Os_InitMemory();
		Os_Init();
		EcuM_Init();
        return 0;
}

TASK(TaskInit_Core0)
{
	EcuM_StartupTwo();
	ComM_CommunicationAllowed(0, TRUE);
	ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
	(void)TerminateTask();
}
TASK(TaskInit_Core1)
{
	EcuM_StartupTwo();
	Rte_Start();
	(void)TerminateTask();
}
TASK(TaskInit_Core2)
{
	EcuM_StartupTwo();
	Rte_Start();
	(void)TerminateTask();
}

ISR(Adc0Sr0_Isr)
{

}

ISR(Adc1Sr0_Isr)
{

}

ISR(Adc2Sr0_Isr)
{

}

ISR(Adc3Sr0_Isr)
{

}

ISR(Adc4Sr0_Isr)
{

}

ISR(Adc5Sr0_Isr)
{

}

ISR(Adc6Sr0_Isr)
{

}

ISR(Isr_TIM02)
{

}

ISR(Isr_TIM03)
{

}

FUNC(boolean, COM_APPL_CODE) T1_AppReceive(PduIdType PduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
	T1_AppRxCallback( PduInfoPtr->SduDataPtr );
}
