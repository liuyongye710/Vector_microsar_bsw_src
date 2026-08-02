/**
 * @file    
 * @brief   This function implements Cdd Common Drivers mainly based on GTM 
 * @author  lyy
 * @date    2024/11/20
 * @version v0.2
 * @par Copyright(c) : FAW JIEFANG corporation
 * @par History :
 *      Version Author Date       Description
 *      V0.1    Lyy    24/11/20   1.Initialize the documentation using the doxygen 
 *                                  annotation method                     
 */


/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "Cdd_Common.h"

/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/


/*******************************************************************************
**                   Static Local Variables Definition              		  **
*******************************************************************************/


/*******************************************************************************
**                     Global Variables Definition              		      **
*******************************************************************************/
// #define CDD_START_SEC_VALUE_CORE0
// #include "FAW_MemMap.h"




// #define CDD_STOP_SEC_VALUE_CORE0
// #include "FAW_MemMap.h"

/*******************************************************************************
**                  Static Local Function Declaration            		      **
*******************************************************************************/


/*******************************************************************************
**                 		  Function Source Code            		              **
*******************************************************************************/


/**
* @brief Timestamps insert function
* @author Archie
* @param[in] p ????????????
* @param[out] NULL
* @note ??TM CNT????????measure????????AW_CDD_SET_BGEIN_TS/FAW_CDD_SET_END_TS??????
*/
void FAW_CDD_ExecTsRec (StmMeasInfo *p)
{
	p->MeasCount ++;
	p->Current = (float)((p->Timestamp.End_Timestamp - p->Timestamp.ST_Timestamp) / STM_CLOCK_MHZ);
	p->MeasInfoStroage[p->MeasCount % MEASINFO_SIZE] = p->Current;
}

/**
* @brief ?$??g?????????
* @author Archie
* @param[in] p ????????????
* @param[out] NULL
* @note ?$??g???????????????????????????
*/
void FAW_CDD_ExecTimeCal (StmMeasInfo *p)
{
	float sum = 0;
	int size = sizeof(p->MeasInfoStroage) / sizeof(p->MeasInfoStroage[0]);
	if (p->Min == 0){ p->Min = 100;}
	for(int i=0 ; i < size ; i++)
	{
		if (p->MeasInfoStroage[i] < p->Min)
		p->Min = p->MeasInfoStroage[i];
		if (p->MeasInfoStroage[i] > p->Max)
		p->Max = p->MeasInfoStroage[i];

		sum += p->MeasInfoStroage[i];
	}

	p->Average =(p->Average + (float)( sum / size ))/2;

	if(p->ClearMeas_Flag != 0)
	{
		for (int i = 0;i < size; i++)
		{
			p->MeasInfoStroage[i] = 0;
		}
		p->MeasCount = 0;
		p->Max = 0;
		p->Min = 0 ;
		p->ClearMeas_Flag = 0;
		p->Average = 0;
	}
}










