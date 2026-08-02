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


#ifndef CDD_COMMON_H_
#define CDD_COMMON_H_

/*******************************************************************************
**                      Other Header File Inclusion                           **
*******************************************************************************/
#include "Cdd_CommonCfg.h"
/*******************************************************************************
**                          Macro Definition                         		  **
*******************************************************************************/

#define MEASINFO_SIZE 		    50
#define FAW_CDD_STM0_ENABLE 	(*(uint32*)STM0_CR_ADDR |= 1)
#define FAW_CDD_STM1_ENABLE 	(*(uint32*)STM1_CR_ADDR |= 1)
#define FAW_CDD_STM2_ENABLE 	(*(uint32*)STM2_CR_ADDR |= 1)

#define FAW_CDD_SET_BGEIN_TS(StmMeasInfo) 	((StmMeasInfo)->Timestamp.ST_Timestamp = *(uint32*)STM0_CNT_ADDR)
// #define FAW_CDD_SET_END_TS(StmMeasInfo) 	((StmMeasInfo)->Timestamp.End_Timestamp = *(uint32*)STM0_CNT_ADDR)
#define FAW_CDD_SET_END_TS(StmMeasInfo){\
((StmMeasInfo)->Timestamp.End_Timestamp = *(uint32*)STM0_CNT_ADDR);\
((StmMeasInfo)->MeasCount ++);\
((StmMeasInfo)->Current = (float)(((StmMeasInfo)->Timestamp.End_Timestamp - (float)(StmMeasInfo)->Timestamp.ST_Timestamp) / STM_CLOCK_MHZ));\
((StmMeasInfo)->MeasInfoStroage[(StmMeasInfo)->MeasCount % MEASINFO_SIZE] = (StmMeasInfo)->Current);\
} 	
/*******************************************************************************
**                          Typedef Definition                         		  **
*******************************************************************************/

/**
* @struct StmTimestampInfo
* @brief 时间戳结构体
*/
typedef struct {
	uint32 ST_Timestamp;  ///< 代码�?始时刻时间戳
	uint32 End_Timestamp; ///< 代码结束时刻时间�?
} StmTimestampInfo;

/**
* @struct StmMeasInfo
* @brief 代码执行时间记录结构�?
*/
typedef struct {
	float Current;
	float Average;
	float Min;
	float Max;
	uint8 ClearMeas_Flag;
	uint32 MeasCount;
	StmTimestampInfo Timestamp;
	float MeasInfoStroage[MEASINFO_SIZE];
} StmMeasInfo;

/*******************************************************************************
**                  Global Variables With Extern Linkage               		  **
*******************************************************************************/


/*******************************************************************************
**                        Global Function Prototypes              	    	  **
*******************************************************************************/
extern void FAW_CDD_ExecTsRec (StmMeasInfo *p);
extern void FAW_CDD_ExecTimeCal (StmMeasInfo *p);
#endif 


