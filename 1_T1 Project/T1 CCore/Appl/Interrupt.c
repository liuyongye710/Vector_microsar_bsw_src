/********************************************************************************
*
*  File name:   Interrupt.c
*
*  Copyright    Neusoft Reach Corporation. All rights reserved.
*
*********************************************************************************/

/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Interrupt.h"
#include "CCFC3007PT_features.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/

/*********************************************************************************
*   Local Variables
*********************************************************************************/
void Can1_Isr_Handler(void)
{
    ISR_M_CAN1_0();
}
void Can2_Isr_Handler(void)
{
    ISR_M_CAN9_0();
}
void Can3_Isr_Handler(void)
{
    ISR_M_CAN10_0();
}
void Can4_Isr_Handler(void)
{
    ISR_M_CAN11_0();
}
void Can5_Isr_Handler(void)
{
    //ISR_M_CAN10_0();
}

//void LinRx0_Isr_Handler(void)
//{
//    LINFLEX0_LLD_RXI_IRQ_HANDLER();
//}
//void LinTx0_Isr_Handler(void)
//{
//    LINFLEX0_LLD_TXI_IRQ_HANDLER();
//}
//void LinError0_Isr_Handler(void)
//{
//    LINFLEX0_LLD_ERR_IRQ_HANDLER();
//}
//
//void LinRx1_Isr_Handler(void)
//{
//    LINFLEX1_LLD_RXI_IRQ_HANDLER();
//}
//void LinTx1_Isr_Handler(void)
//{
//    LINFLEX1_LLD_TXI_IRQ_HANDLER();
//}
//void LinError1_Isr_Handler(void)
//{
//    LINFLEX1_LLD_ERR_IRQ_HANDLER();
//}

void GTM_PSM07_ISRfunc(void)
{

}

void GTM_TIM00_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_TIM00]));
  
//   CX_ISR_HOOK(HK_GTM_ISR_TIM00);
  
//   Tst_ISR_Cnt[HK_GTM_ISR_TIM00]++;
//   SIUL2.GPDO[64].B.PDO = (Tst_ISR_Cnt[HK_GTM_ISR_TIM00]&1);
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_TIM00]));
}

void GTM_TIM01_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_TIM01]));
  
//   CX_ISR_HOOK(HK_GTM_ISR_TIM01);
  
//   Tst_ISR_Cnt[HK_GTM_ISR_TIM01]++;
  
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_TIM01]));
}

void GTM_TIM04_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_TIM04]));
  
//   CX_ISR_HOOK(HK_GTM_ISR_TIM04);
  
//   Tst_ISR_Cnt[HK_GTM_ISR_TIM04]++;

//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_TIM04]));
}
void GTM_MCS00_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS00]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS00);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS00]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS00]));
}

void GTM_MCS04_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS04]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS04);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS04]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS04]));
}

void GTM_MCS05_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS05]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS05);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS05]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS05]));
}

void GTM_MCS06_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS06]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS06);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS06]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS06]));
}

void GTM_MCS07_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS07]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS07);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS07]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS07]));
}

void GTM_MCS23_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS23]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS23);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS23]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS23]));
}

void GTM_MCS24_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS24]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS24);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS24]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS24]));
}

void GTM_MCS25_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS25]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS25);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS25]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS25]));
}
void GTM_MCS26_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS26]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS26);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS26]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS26]));
}

void GTM_MCS27_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS27]));
	
//   CX_ISR_HOOK(HK_GTM_ISR_MCS27);
	
//   Tst_ISR_Cnt[HK_GTM_ISR_MCS27]++;
	
//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_MCS27]));
}
void GTM_ATOM20_ISRfunc(void)
{

}

void GTM_ATOM35_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_ATOM35]));
  
//   CX_ISR_HOOK(HK_GTM_ISR_ATOM35);
  
//   Tst_ISR_Cnt[HK_GTM_ISR_ATOM35]++;

//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_GTM_ISR_ATOM35]));
}

//CX logic use software isr to manage the internal callback system.
void GTM_PSI50_ISRfunc(void)
{
//   CX_Entry_Meas(&(Tst_CX_ISR_Exe_Timing[HK_SOFT_ISR_CH03]));
  
//   CX_ISR_HOOK(HK_SOFT_ISR_CH03);

//   Tst_ISR_Cnt[HK_SOFT_ISR_CH03]++;

//   CX_Exit_Meas(&(Tst_CX_ISR_Exe_Timing[HK_SOFT_ISR_CH03]));
}
//void GTM_ATOM10_ISRfunc(void)
//{
//	AB_GTM_ATOM10_ISRfunc();
//	Pwm_Atom_isr_handle(1,0,1);
//	return;
//}
void FccuAlarmCallback(void)
{
    return;
}

void FccuTimeoutCallback(void)
{
    return;
}
