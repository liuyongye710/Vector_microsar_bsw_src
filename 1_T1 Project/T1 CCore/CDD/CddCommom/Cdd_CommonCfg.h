/**
 * @file
 * @brief   This function implements Cdd Common Drivers mainly based on GTM
 * @author  lyy
 * @date    2024/11/20
 * @version v0.1
 * @par Copyright(c) : FAW JIEFANG corporation
 * @par History :
 *      Version Author Date       Description
 *      v0.1    Lyy    24/11/20   Initialize the documentation using the doxygen
 *                                annotation method
 */


#ifndef CDD_COMMONCFG_H_
#define CDD_COMMONCFG_H_

/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "platform_types.h"


/******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/
#define _CDD_SIMULATION   0u /*set 1 debug mode;set 0 realse mode  */
#define TEST_USE_MCAL     0u
#define CHIP_PLATFORM_CCFC3007PT
// #define CHIP_PLATFORM_TC397       




#if (TEST_USE_MCAL == 1U)
	#define ATOM10_Prio			30U
	#define ADC0DMACH1_Prio		29U
	#define ADC1DMACH3_Prio		28U
	#define ADC2DMACH16_Prio	27U
#endif

#define STM_CLOCK_HZ			50000000
#define STM_CLOCK_MHZ			50

#define STM0_CR_ADDR			0xFC068000
#define STM1_CR_ADDR			0xFC06C000
#define STM2_CR_ADDR			0xFC070000

#define STM0_CNT_ADDR			0xFC068004
#define STM1_CNT_ADDR			0xFC06C004
#define STM2_CNT_ADDR			0xFC070004
/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                  Global Variables With Extern Linkage               		  **
*******************************************************************************/


/*******************************************************************************
**                        Global Function Prototypes              	    	  **
*******************************************************************************/


#endif
