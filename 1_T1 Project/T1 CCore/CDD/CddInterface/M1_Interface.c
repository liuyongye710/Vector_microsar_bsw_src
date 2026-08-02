/**
 * @file    
 * @brief   implements TM Drivers Interface 
 * @author  lyy
 * @date    2024/11/20
 * @version v0.1
 * @par Copyright(c) : FAW JIEFANG corporation
 * @par History :
 *      Version Author Date       Description
 *      V0.1    Lyy    24/11/20   1.Initialize the documentation using the doxygen 
 *                                  annotation method                           
 */

/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "Cdd_Interface.h"
#include "PhC_Drv.h"
#include "Pwm3ph.h"
#include "TM1_RSD.h"
#include "Gp_06_RslvrSW.h"
#include "FM.h"
#include "rtwtypes.h"
#include "FM_private.h"
#include "FM.h"
#include "SC2167.h"
#include "petter.h"
#include "Dio_Cfg.h"
#include "Gpt_Stm_LLDriver.h"

/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                   Static Local Variables Definition              		  **
*******************************************************************************/


/*******************************************************************************
**                     Global Variables Definition              		      **
*******************************************************************************/
#define FAW_CORE0_DMEM0_VALUE_START
#include "FAW_MemMap.h"

Pwm3phInIFType temp_Pwm3phIn={0.5,0.5,0.5,10000,3}; /*240429 FAW-LYY Add*/
Pwm3phOutIFType temp_Pwm3Out={0}; /*240429 FAW-LYY Add*/
PhCOutIFType temp_Phc={0};

StmMeasInfo isrExcutionTime;
StmMeasInfo isrASWExcutionTime;

sint16  Gp_IoHwAbCore2_adcMotARslvrCosValueRaw_vs16;		/*IoHwAb_MeasurableVariable*/
sint16  Gp_IoHwAbCore2_adcMotARslvrSinValueRaw_vs16;		/*IoHwAb_MeasurableVariable*/

uint32 test_TM1_BSW_timTimeCurTrigerTimeStamp_vf32;
 volatile real32_T TM1_RSD_CosGain_kf32=0.96f;
 volatile real32_T TM1_RSD_SinGain_kf32=1.0f;
volatile real32_T TM1_RSD_CosOffset_kf32=10.0f;
 volatile real32_T TM1_RSD_SinOffset_kf32=0.0f;

#define FAW_CORE0_DMEM0_VALUE_STOP
#include "FAW_MemMap.h"

/*******************************************************************************
**                  Static Local Function Declaration            		      **
*******************************************************************************/


/*******************************************************************************
**                 		  Function Source Code            		              **
*******************************************************************************/
uint32 isrSDadcSinCount;
void eDMA_SDADC_Notification()
{
	isrSDadcSinCount++;
//	Gp_06_RslvrSw_GetPos(   &Gp_IoHwAbCore2_adcMotARslvrSinValueRaw_vs16,
//		            				&Gp_IoHwAbCore2_adcMotARslvrCosValueRaw_vs16);
//
//
//			 TM1_BSW_uDsadcCosValVol_vf32=Gp_IoHwAbCore2_adcMotARslvrSinValueRaw_vs16*TM1_RSD_CosGain_kf32+TM1_RSD_CosOffset_kf32;
//			 TM1_BSW_uDsadcSinValVol_vf32=Gp_IoHwAbCore2_adcMotARslvrCosValueRaw_vs16*TM1_RSD_SinGain_kf32+TM1_RSD_SinOffset_kf32;
//			 TM1_RSD_DSADCDecoder_sys();
//
//				 	Gp_06_RslvrSw_CddIo();
//				 	Gp_06_RslvrSw_GetTimeStampSig(&test_TM1_BSW_timTimeCurTrigerTimeStamp_vf32);
//				 		TM1_BSW_timTimeCurTrigerTimeStamp_vf32=test_TM1_BSW_timTimeCurTrigerTimeStamp_vf32&0xFFFFFF;


}
#define FAW_CORE0_IMEM0_CODE_START
#include "FAW_MemMap.h"
uint64 isrAtomCount;
uint32 test=2;
uint64 convfre=100;
void AB_GTM_ATOM10_ISRfunc(void)
{

    FAW_CDD_SET_BGEIN_TS(&isrExcutionTime);
    isrAtomCount++;
    /**************************** Code End *****************************/
    /* Reading the rotor angle starts */
//    Gp_06_RslvrSw_GetCurTimeStampSig(&test);
//    TM1_RSD_CalPwmEAngle_sys();
    RDC_agRtrEe=((real32_T)(SC2167_Angle()/16)/4095)*360;
    /* Reading the rotor angle end */

    /* Get three-phase current */
    Adc_RegTrigConversion_Core0(isrAtomCount,convfre);

    M1_PhC_GetResult_MCUHwAdc(&temp_Phc);
    FAW_CDD_SET_BGEIN_TS(&isrASWExcutionTime);
    /* 100us FOC Func Begin */
    iUNoOff=temp_Phc.iUNoOff;
    iVNoOff=temp_Phc.iVNoOff;
    iWNoOff=temp_Phc.iWNoOff;
    tri_100us();
	temp_Pwm3phIn.Pwm_Mode_u8=(uint8)MCF_stpwmMode;
	temp_Pwm3phIn.Pwm_Freq_u16=(uint16)MCF_frqPwm;
    temp_Pwm3phIn.PwmDutyCyclePhaseU1_f32=(float32)(MCF_dycU);
    temp_Pwm3phIn.PwmDutyCyclePhaseV1_f32=(float32)(MCF_dycV);
    temp_Pwm3phIn.PwmDutyCyclePhaseW1_f32=(float32)(MCF_dycW);
    /* 100us FOC Func End */
    FAW_CDD_SET_END_TS(&isrASWExcutionTime);

    /* upadte SVPWM paraments */
    M1_Pwm3ph_SetOutput(&temp_Pwm3phIn);

//    Gp_06_Pwm3phSetOutput_CddIo(temp_Pwm3phIn.Pwm_Mode_u8,
//    						temp_Pwm3phIn.Pwm_Freq_u16,
//    						temp_Pwm3phIn.PwmDutyCyclePhaseU1_f32,
//							temp_Pwm3phIn.PwmDutyCyclePhaseV1_f32,
//							temp_Pwm3phIn.PwmDutyCyclePhaseW1_f32);

    /**************************** Code End *****************************/

    FAW_CDD_SET_END_TS(&isrExcutionTime);

}

#define FAW_CORE0_IMEM0_CODE_STOP
#include "FAW_MemMap.h"



void Handle_BUSBAR_OV()
{
	Emgercy_ASC();
}
void Handle_SA47321_nINT_ERROR()
{
}
void Handle_Smotor_CURRENT_OC()
{
	Emgercy_ASC();
}
void Handle_Mmotor_IGBT_ERROR()
{
}
void Handle_Efuse_CURRENT_OC()
{
}
void Handle_Smotor_IGBT_ERROR()
{
}
void Handle_Mmotor_CURRENT_OC()
{
	//	if(ISR_ERR_Flags.Busbar_OV==0){
	//			Emgercy_SPO();}
	Emgercy_ASC();
}
void Handle_Efuse_ERROR()
{
}









/*******************************************************************************

*******************************************************************************/
