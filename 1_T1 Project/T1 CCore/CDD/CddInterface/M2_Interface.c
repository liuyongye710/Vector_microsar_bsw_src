/**
 * @file    
 * @brief   implements BM Drivers Interface 
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

#include "FM_FQ.h"
#include "rtwtypes.h"
#include "FM_FQ_private.h"

#include "petter.h"


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
#define FAW_CORE1_DMEM1_VALUE_START
#include "FAW_MemMap.h"

Pwm3phInIFType temp_Pwm3phIn_M2={0.5,0.5,0.5,10000,3}; /*240429 FAW-LYY Add*/
Pwm3phOutIFType temp_Pwm3Out_M2={0}; /*240429 FAW-LYY Add*/
PhCOutIFType temp_Phc_M2={0};

#define FAW_CORE1_DMEM1_VALUE_STOP
#include "FAW_MemMap.h"
/*******************************************************************************
**                  Static Local Function Declaration            		      **
*******************************************************************************/


/*******************************************************************************
**                 		  Function Source Code            		              **
*******************************************************************************/


#define FAW_CORE1_IMEM1_CODE_START
#include "FAW_MemMap.h"
uint64 M2_isrAtomCount;
void AB_GTM_ATOM40_ISRfunc(void)
{
	M2_isrAtomCount++;
	/* Reading the rotor angle starts */

	/* Reading the rotor angle end */
	M2_PhC_GetResult_MCUHwAdc(&temp_Phc_M2);
		Adc_RegTrigConversion_Core1(M2_isrAtomCount,(uint64)100);
    /* 100us FOC Func Begin */
		iUNoOff_FQ=temp_Phc_M2.iUNoOff;
	iVNoOff_FQ=temp_Phc_M2.iVNoOff;
	iWNoOff_FQ=temp_Phc_M2.iWNoOff;
	tri_100us_FQ();
	temp_Pwm3phIn_M2.Pwm_Mode_u8=(uint8)MCF_stpwmMode_FQ;
	temp_Pwm3phIn_M2.Pwm_Freq_u16=(uint16)MCF_frqPwm_FQ;
	temp_Pwm3phIn_M2.PwmDutyCyclePhaseU1_f32=(float32)(MCF_dycU_FQ);
	temp_Pwm3phIn_M2.PwmDutyCyclePhaseV1_f32=(float32)(MCF_dycV_FQ);
	temp_Pwm3phIn_M2.PwmDutyCyclePhaseW1_f32=(float32)(MCF_dycW_FQ);
    /* 100us FOC Func End */
	M2_Pwm3ph_SetOutput(&temp_Pwm3phIn_M2);

}

#define FAW_CORE1_IMEM1_CODE_STOP
#include "FAW_MemMap.h"










/*******************************************************************************

*******************************************************************************/
