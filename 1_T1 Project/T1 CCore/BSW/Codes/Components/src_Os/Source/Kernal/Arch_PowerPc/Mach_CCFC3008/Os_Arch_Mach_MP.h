/*
********************************************************************************
*
*  File name: Os_Arch_Mach_MP.h
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.23
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: JiangGL/2023.09.05
* Change: Fit for CCFC3008.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: JiangGL/2024.01.09
* Change: Fix the issue of not being able to clear mpu regions.
* Cause: Bugfix
********************************************************************************
*/
#ifndef OS_ARCH_MACH_MP_H_
#define OS_ARCH_MACH_MP_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Arch_Mach_MP_Types.h"
#include "Os_Arch_Mach.h"
#include "Os_Core.h"
#include "Os_Stack.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
/*
********************************************************************************
*    Global Types
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
*    Global Functions
********************************************************************************
*/
#define OS_START_SEC_CODE
#include "Os_MemMap.h"

#if( OS_CORE_MPU == STD_ON )
/*
********************************************************************************
* Function Name: Os_Arch_CoreMpClear
*
* Explanation: Disable MPU egion.
*
* Param: mpRegionCfg: The core region configuration Data.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_CoreMpClear
(
    P2CONST(Os_Arch_CoreMpRegionCfgType, AUTOMATIC, OS_APPL_CONST) mpRegionCfg
)
{
    /* If the region number is in the range. */
    if( mpRegionCfg->mpuRegion < OS_CORE_CMPU_REGION_CNT )
    {
        /* Disable the protective effect of this CMPU region. */
        Os_Hal_WriteSPR (mas0, OS_ARCH_CMPU_MAS0_VALID_MSK |
                        OS_ARCH_CMPU_MAS0_SEL_MSK | OS_ARCH_CMPU_MAS0_ESEL(mpRegionCfg->mpuRegion));
        /* Set CMPU region TID and PID_MASK. */
        Os_Hal_WriteSPR (mas1, OS_ZERO_VALUE);
        /* Set CMPU region upper address. */
        Os_Hal_WriteSPR (mas2, OS_ZERO_VALUE);
        /* Set CMPU region lower address. */
        Os_Hal_WriteSPR (mas3, OS_ZERO_VALUE);
        /* Perform write operations on CMPU entries. */
        __asm volatile("mpuwe   " "\n");
        /* MPU instruction synchronization. */
        __asm volatile("mpusync " "\n");
        /* System instruction synchronization. */
        __asm volatile("se_isync" "\n");
    }
}

extern FUNC(void, OS_CODE) Os_Arch_CoreMpInit
(
    CONST(uint8, OS_CONST) regionCnt,
    P2CONST(Os_Arch_CoreMpRegionCfgType, AUTOMATIC, OS_APPL_CONST) mpRegionCfgInit
);
#endif /* OS_CORE_MPU == STD_ON */

#if( OS_SYSTEM_MPU == STD_ON )
/*
********************************************************************************
* Function Name: Os_Arch_MpDisableAll
*
* Explanation: Disable the system-level MPU.
*
* Param: None
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_MpDisableAll(void)
{
    /* Do nothing. */
    return;
}

/*
********************************************************************************
* Function Name: Os_Arch_MpClear
*
* Explanation: Clear system-level MPU region.
*
* Param: mpRegionCfg: The system MPU region configuration Data.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_MpClear
(
    P2CONST(Os_Arch_MpRegionCfgType, AUTOMATIC, OS_APPL_CONST) mpRegionCfg
)
{
    OS_DUMMY_STATEMENT(mpRegionCfg);
    /* Do nothing. */
    return;
}

/*
********************************************************************************
* Function Name: Os_Arch_MpSwitch
*
* Explanation: Disable the system-level MPU.
*
* Param: mpRegionCfg: The system MPU region configuration Data.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_MpSwitch
(
    P2CONST(Os_Arch_MpRegionCfgType, AUTOMATIC, OS_APPL_CONST) mpRegionCfg
)
{
    OS_DUMMY_STATEMENT(mpRegionCfg);
    /* Do nothing. */
    return;
}

/*
********************************************************************************
* Function Name: Os_Arch_MpInit
*
* Explanation: Initialize the system-level MPU.
*
* Param: regionCnt: Mpu region number.
*        mpRegionCfg: The system MPU region configuration Data.
*
* Retval: None
********************************************************************************
*/
LOCAL_INLINE FUNC(void, OS_CODE) Os_Arch_MpInit
(
    uint32 regionCnt,
    P2CONST(Os_Arch_MpRegionCfgType, AUTOMATIC, OS_APPL_CONST) mpRegionCfg
)
{
    uint32 region;
    CoreIdType coreId;
    const Os_Arch_MpRegionCfgType* mpRegionCfgInit = mpRegionCfg;

    /* Disable the system MPU. */
    Os_Arch_MpDisableAll();
    /* Configure region data. */
    for( region = OS_ARCH_MP_INIT; region < regionCnt; region++ )
    {
        Os_Arch_MpSwitch(mpRegionCfgInit);
        mpRegionCfgInit++;
    }
    /* Get core id. */
    coreId = Os_Core_GetLogicId();
    if( OS_CORE_ISMASTER(coreId) )
    {
        /* Master core enable MPU. */
    }
}
#endif /* OS_SYSTEM_MPU == STD_ON */

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

#endif /* OS_ARCH_MACH_MP_H_ */
