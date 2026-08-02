/*
********************************************************************************
*
*  File name: Os_Ioc.c
*
*  Copyright Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: HanCL/2021.11.25
* Change: New create.
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: LiG/2022.11.21
* Change: Change OS_VAR_NOINIT to OS_VAR_NO_INIT.
* Cause: Bugfix
********************************************************************************
* Version: 3.2
* Author/Date: LiG/2023.1.28
* Change: Add IOC type to full type.
* Cause: Update
********************************************************************************
* Version: 3.3
* Author/Date: LiG/2023.2.14
* Change: Notes optimization.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date: LiG/2023.2.15
* Change: Modified for QAC.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: LiG/2023.3.28
* Change: Add missing else.
* Cause: Bugfix
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Os_Ioc.h"
#include "Os_Error.h"
#include "Os_Spinlock.h"
#include "Os_App.h"
#include "Os_SysCall.h"
#include "Os_Orti.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/* Get the TX configuration of the IOC. */
#define OS_IOC_GETTXCFG(iocCfg, senderId) ((iocCfg)->iocTxCfg[senderId])
/* Get the RX configuration of the IOC. */
#define OS_IOC_GETRXCFG(iocCfg)           ((iocCfg)->iocRxCfg)
/* Determine whether it is a queue IOC. */
#define OS_IOC_CHRCKISQUEIOC(iocCfg)      ((iocCfg)->func != NULL_PTR)

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
static FUNC(void, OS_CODE) Os_Ioc_Lock
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    CoreIdType coreId,
    P2VAR(Os_Arch_IntState, AUTOMATIC, OS_APPL_DATA) intState
);
static FUNC(void, OS_CODE) Os_Ioc_ULock
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    CoreIdType coreId,
    P2CONST(Os_Arch_IntState, AUTOMATIC, OS_APPL_CONST) intState
);

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
* Function Name: Os_Ioc_Lock
*
* Explanation: Lock when Ioc is executed.
*
* param: iocCfg: Reference to an ioc.
*        coreId: Current core index.
*        intState: interrupt status.
*
* retval: None
********************************************************************************
*/
static FUNC(void, OS_CODE) Os_Ioc_Lock
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    CoreIdType coreId,
    P2VAR(Os_Arch_IntState, AUTOMATIC, OS_APPL_DATA) intState
)
{
    /* If the lock is disable interrupt. */
    if( IOC_LOCKTYPE_INT == iocCfg->lockType )
    {
        /* Disable interrupt. */
        Os_Arch_IntDisable(intState);
    }
    else if( IOC_LOCKTYPE_INT_SPINLOCK == iocCfg->lockType )
    {
        /* Disable interrupt. */
        Os_Arch_IntDisable(intState);
        /* Get spinlock. */
        Os_Spinlock_IntlGetSpinlock(iocCfg->spinlockId, coreId);
    }
    else
    {
        /* Nothing to do. */
    }
}

/*
********************************************************************************
* Function Name: Os_Ioc_ULock
*
* Explanation: Ulock when Ioc is executed.
*
* param: iocCfg: Reference to an ioc.
*        coreId: Current core index.
*        intState: interrupt status.
*
* retval: None
********************************************************************************
*/
static FUNC(void, OS_CODE) Os_Ioc_ULock
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    CoreIdType coreId,
    P2CONST(Os_Arch_IntState, AUTOMATIC, OS_APPL_CONST) intState
)
{
    /* If the lock is disable interrupt. */
    if( IOC_LOCKTYPE_INT == iocCfg->lockType )
    {
        /* Enable interrupt. */
        Os_Arch_IntEnable(*intState);
    }
    else if( IOC_LOCKTYPE_INT_SPINLOCK == iocCfg->lockType )
    {
        /* Enable interrupt. */
        Os_Arch_IntEnable(*intState);
        /* Get spinlock. */
        Os_Spinlock_IntlReleaseSpinlock(iocCfg->spinlockId, coreId);
    }
    else
    {
        /* Nothing to do. */
    }
}

/*
********************************************************************************
* Function Name: Os_Ioc_IntlWrite
*
* Explanation: ioc internal write function.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to write.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Application permission error.
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_IntlWrite
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    uint32 senderId,
    P2CONST(void*const, AUTOMATIC, OS_APPL_CONST) data
)
{
    Std_ReturnType ret = IOC_E_OK;
    uint8 dataTypeId;
    CoreIdType coreId;
    const void* dataSrcAddr;
    const Os_IocDataType* iocDataType;
    Os_Arch_IntState intState;

    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();
    if( OS_APPMATCH((uint32)OS_IOC_GETTXCFG(iocCfg, senderId).accessingApps, OS_CORE_GETAPPID(coreId)) )
    {
        ret = IOC_E_NOK;
    }
    else
    {
        /* IOC data lock. */
        Os_Ioc_Lock(iocCfg, coreId, &intState);
        /* Get ioc data type. */
        iocDataType = iocCfg->dataType;
        /* Loop through data types. */
        for( dataTypeId = IOC_INIT; dataTypeId < iocCfg->dataTypeCnt; dataTypeId++ )
        {
            /* Get source data address. */
            dataSrcAddr = data[dataTypeId];
            if( IOC_DATATYPE_BL == iocDataType->dataType )
            {
                boolean* bufferAddr_BL;
                /* Get buffer address. */
                bufferAddr_BL = (boolean*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_BL = *(boolean*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_U8 == iocDataType->dataType )
            {
                uint8* bufferAddr_U8;
                /* Get buffer address. */
                bufferAddr_U8 = (uint8*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_U8 = *(uint8*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_U16 == iocDataType->dataType )
            {
                uint16* bufferAddr_U16;
                /* Get buffer address. */
                bufferAddr_U16 = (uint16*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_U16 = *(uint16*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_U32 == iocDataType->dataType )
            {
                uint32* bufferAddr_U32;
                /* Get buffer address. */
                bufferAddr_U32 = (uint32*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_U32 = *(uint32*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_U64 == iocDataType->dataType )
            {
                uint64* bufferAddr_U64;
                /* Get buffer address. */
                bufferAddr_U64 = (uint64*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_U64 = *(uint64*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_S8 == iocDataType->dataType )
            {
                sint8* bufferAddr_S8;
                /* Get buffer address. */
                bufferAddr_S8 = (sint8*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_S8 = *(sint8*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_S16 == iocDataType->dataType )
            {
                sint16* bufferAddr_S16;
                /* Get buffer address. */
                bufferAddr_S16 = (sint16*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_S16 = *(sint16*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_S32 == iocDataType->dataType )
            {
                sint32* bufferAddr_S32;
                /* Get buffer address. */
                bufferAddr_S32 = (sint32*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_S32 = *(sint32*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_S64 == iocDataType->dataType )
            {
                sint64* bufferAddr_S64;
                /* Get buffer address. */
                bufferAddr_S64 = (sint64*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_S64 = *(sint64*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_FL == iocDataType->dataType )
            {
                float32* bufferAddr_FL;
                /* Get buffer address. */
                bufferAddr_FL = (float32*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_FL = *(float32*)dataSrcAddr;
            }
            else if( IOC_DATATYPE_DB == iocDataType->dataType )
            {
                float64* bufferAddr_DB;
                /* Get buffer address. */
                bufferAddr_DB = (float64*)(iocDataType->buffer);
                /* Write input data to IOC buffer. */
                *bufferAddr_DB = *(float64*)dataSrcAddr;
            }
            else
            {
                /* Copy input data to IOC buffer. */
                uint32 cnt;
                uint8* bufferAddr_PTR;
                uint8* data_PTR;

                data_PTR = (uint8*)dataSrcAddr;
                /* Get buffer address. */
                bufferAddr_PTR = (uint8*)(iocDataType->buffer);
                for( cnt = IOC_INIT; cnt < iocDataType->dataSize; cnt++ )
                {
                    *bufferAddr_PTR = *data_PTR;
                    bufferAddr_PTR++;
                    data_PTR++;
                }
            }
            /* Increase data type address. */
            iocDataType++;
        }
        /* IOC data unlock. */
        Os_Ioc_ULock(iocCfg, coreId, &intState);
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Ioc_IntlRead
*
* Explanation: ioc internal read function.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to read.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Application permission error.
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_IntlRead
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    P2CONST(void*const, AUTOMATIC, OS_APPL_CONST) data
)
{
    Std_ReturnType ret = IOC_E_OK;
    uint8 dataTypeId;
    CoreIdType coreId;
    const void* dataSrcAddr;
    const Os_IocDataType* iocDataType;
    Os_Arch_IntState intState;

    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();
    if( OS_APPMATCH(OS_IOC_GETRXCFG(iocCfg)->accessingApps, OS_CORE_GETAPPID(coreId)) )
    {
        ret = IOC_E_NOK;
    }
    else
    {
        /* IOC data lock. */
        Os_Ioc_Lock(iocCfg, coreId, &intState);
        /* Get ioc data type. */
        iocDataType = iocCfg->dataType;
        /* Loop through data types. */
        for( dataTypeId = IOC_INIT; dataTypeId < iocCfg->dataTypeCnt; dataTypeId++ )
        {
             /* Get source data address. */
            dataSrcAddr = data[dataTypeId];
            if( IOC_DATATYPE_BL == iocDataType->dataType )
            {
                boolean* bufferAddr_BL;
                /* Get buffer address. */
                bufferAddr_BL = (boolean*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(boolean*)dataSrcAddr = *bufferAddr_BL;
            }
            else if( IOC_DATATYPE_U8 == iocDataType->dataType )
            {
                uint8* bufferAddr_U8;
                /* Get buffer address. */
                bufferAddr_U8 = (uint8*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(uint8*)dataSrcAddr = *bufferAddr_U8;
            }
            else if( IOC_DATATYPE_U16 == iocDataType->dataType )
            {
                uint16* bufferAddr_U16;
                /* Get buffer address. */
                bufferAddr_U16 = (uint16*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(uint16*)dataSrcAddr = *(uint16*)bufferAddr_U16;
            }
            else if( IOC_DATATYPE_U32 == iocDataType->dataType )
            {
                uint32* bufferAddr_U32;
                /* Get buffer address. */
                bufferAddr_U32 = (uint32*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(uint32*)dataSrcAddr = *bufferAddr_U32;
            }
            else if( IOC_DATATYPE_U64 == iocDataType->dataType )
            {
                uint64* bufferAddr_U64;
                /* Get buffer address. */
                bufferAddr_U64 = (uint64*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(uint64*)dataSrcAddr = *bufferAddr_U64;
            }
            else if( IOC_DATATYPE_S8 == iocDataType->dataType )
            {
                sint8* bufferAddr_S8;
                /* Get buffer address. */
                bufferAddr_S8 = (sint8*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(uint8*)dataSrcAddr = *bufferAddr_S8;
            }
            else if( IOC_DATATYPE_S16 == iocDataType->dataType )
            {
                sint16* bufferAddr_S16;
                /* Get buffer address. */
                bufferAddr_S16 = (sint16*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(sint16*)dataSrcAddr = *(sint16*)bufferAddr_S16;
            }
            else if( IOC_DATATYPE_S32 == iocDataType->dataType )
            {
                sint32* bufferAddr_S32;
                /* Get buffer address. */
                bufferAddr_S32 = (sint32*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(sint32*)dataSrcAddr = *bufferAddr_S32;
            }
            else if( IOC_DATATYPE_S64 == iocDataType->dataType )
            {
                sint64* bufferAddr_S64;
                /* Get buffer address. */
                bufferAddr_S64 = (sint64*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(sint64*)dataSrcAddr = *bufferAddr_S64;
            }
            else if( IOC_DATATYPE_FL == iocDataType->dataType )
            {
                float32* bufferAddr_FL;
                /* Get buffer address. */
                bufferAddr_FL = (float32*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(float32*)dataSrcAddr = *(float32*)bufferAddr_FL;
            }
            else if( IOC_DATATYPE_DB == iocDataType->dataType )
            {
                float64* bufferAddr_DB;
                /* Get buffer address. */
                bufferAddr_DB = (float64*)(iocDataType->buffer);
                /* Read data from IOC buffer to the output data. */
                *(float64*)dataSrcAddr = *bufferAddr_DB;
            }
            else
            {
                /* Copy data from IOC buffer to the output data. */
                uint32 cnt;
                uint8* bufferAddr_PTR;
                uint8* data_PTR;

                bufferAddr_PTR = (uint8*)(iocDataType->buffer);
                data_PTR = (uint8*)dataSrcAddr;
                for( cnt = IOC_INIT; cnt < iocDataType->dataSize; cnt++ )
                {
                    *data_PTR = *bufferAddr_PTR;
                    bufferAddr_PTR++;
                    data_PTR++;
                }
            }
            /* Increase data type address. */
            iocDataType++;
        }
        /* IOC data unlock. */
        Os_Ioc_ULock(iocCfg, coreId, &intState);
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Ioc_IntlSend
*
* Explanation: ioc internal send function.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to send.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Application permission error.
*         IOC_E_LIMIT: Ioc buffer is full;
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_IntlSend
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    uint32 senderId,
    P2CONST(void*const, AUTOMATIC, OS_APPL_CONST) data
)
{
    Std_ReturnType ret = IOC_E_OK;
    CoreIdType coreId;
    void* bufferAddr;
    const void* dataSrcAddr;
    Os_Arch_IntState intState;

    /* Get logic core id. */
    coreId = Os_Core_GetLogicId();
    if( OS_APPMATCH((uint32)OS_IOC_GETTXCFG(iocCfg, senderId).accessingApps, (uint32)OS_CORE_GETAPPID(coreId)) )
    {
        ret = IOC_E_NOK;
    }
    else
    {
        /* IOC data lock. */
        Os_Ioc_Lock(iocCfg, coreId, &intState);
        /* Get buffer address. */
        bufferAddr = iocCfg->dataType->buffer;
        /* Get source data address. */
        dataSrcAddr = data[IOC_INIT];
        if( IOC_DATATYPE_BL == iocCfg->dataType->dataType )
        {
            Os_QueueType_BL* bufferAddr_TypeBL;
            bufferAddr_TypeBL = (Os_QueueType_BL*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeBL) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                boolean dataTmp_BL;
                dataTmp_BL = (boolean)(*(boolean*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeBL, dataTmp_BL);
            }
        }
        else if( IOC_DATATYPE_U8 == iocCfg->dataType->dataType )
        {
            Os_QueueType_U8* bufferAddr_TypeU8;
            bufferAddr_TypeU8 = (Os_QueueType_U8*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeU8) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                uint8 dataTmp_U8;
                dataTmp_U8 = (uint8)(*(uint8*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeU8, dataTmp_U8);
            }
        }
        else if( IOC_DATATYPE_U16 == iocCfg->dataType->dataType )
        {
            Os_QueueType_U16* bufferAddr_TypeU16;
            bufferAddr_TypeU16 = (Os_QueueType_U16*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeU16) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                uint16 dataTmp_U16;
                dataTmp_U16 = (uint16)(*(uint16*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeU16, dataTmp_U16);
            }
        }
        else if( IOC_DATATYPE_U32 == iocCfg->dataType->dataType )
        {
            Os_QueueType_U32* bufferAddr_TypeU32;
            bufferAddr_TypeU32 = (Os_QueueType_U32*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeU32) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                uint32 dataTmp_U32;

                dataTmp_U32 = (uint32)(*(uint32*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeU32, dataTmp_U32);
            }
        }
        else if( IOC_DATATYPE_U64 == iocCfg->dataType->dataType )
        {
            Os_QueueType_U64* bufferAddr_TypeU64;
            bufferAddr_TypeU64 = (Os_QueueType_U64*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeU64) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                uint64 dataTmp_U64;

                dataTmp_U64 = (uint64)(*(uint64*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeU64, dataTmp_U64);
            }
        }
        else if( IOC_DATATYPE_S8 == iocCfg->dataType->dataType )
        {
            Os_QueueType_S8* bufferAddr_TypeS8;
            bufferAddr_TypeS8 = (Os_QueueType_S8*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeS8) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                sint8 dataTmp_S8;
                dataTmp_S8 = (sint8)(*(sint8*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeS8, dataTmp_S8);
            }
        }
        else if( IOC_DATATYPE_S16 == iocCfg->dataType->dataType )
        {
            Os_QueueType_S16* bufferAddr_TypeS16;
            bufferAddr_TypeS16 = (Os_QueueType_S16*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeS16) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                sint16 dataTmp_S16;
                dataTmp_S16 = (sint16)(*(sint16*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeS16, dataTmp_S16);
            }
        }
        else if( IOC_DATATYPE_S32 == iocCfg->dataType->dataType )
        {
            Os_QueueType_S32* bufferAddr_TypeS32;
            bufferAddr_TypeS32 = (Os_QueueType_S32*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeS32) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                sint32 dataTmp_S32;

                dataTmp_S32 = (sint32)(*(sint32*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeS32, dataTmp_S32);
            }
        }
        else if( IOC_DATATYPE_S64 == iocCfg->dataType->dataType )
        {
            Os_QueueType_S64* bufferAddr_TypeS64;
            bufferAddr_TypeS64 = (Os_QueueType_S64*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeS64) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                sint64 dataTmp_S64;

                dataTmp_S64 = (sint64)(*(sint64*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeS64, dataTmp_S64);
            }
        }
        else if( IOC_DATATYPE_FL == iocCfg->dataType->dataType )
        {
            Os_QueueType_FL* bufferAddr_TypeFL;
            bufferAddr_TypeFL = (Os_QueueType_FL*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeFL) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                float32 dataTmp_FL;
                dataTmp_FL = (float32)(*(float32*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeFL, dataTmp_FL);
            }
        }
        else if( IOC_DATATYPE_DB == iocCfg->dataType->dataType )
        {
            Os_QueueType_DB* bufferAddr_TypeDB;
            bufferAddr_TypeDB = (Os_QueueType_DB*)bufferAddr;
            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypeDB) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                float64 dataTmp_DB;

                dataTmp_DB = (float64)(*(float64*)dataSrcAddr);
                /* Write input data to IOC queue. */
                OS_QUEUE_PUSH(bufferAddr_TypeDB, dataTmp_DB);
            }
        }
        else
        {
            uint32 cnt;

            Os_QueueType_Point* bufferAddr_TypePTR;
            bufferAddr_TypePTR = (Os_QueueType_Point*)bufferAddr;

            /* Check if the send queue is full. */
            if( OS_QUEUE_ISFULL(bufferAddr_TypePTR) )
            {
                ret = IOC_E_LIMIT;
                iocCfg->iocDyn->iocState = IOC_STATE_LOST;
            }
            else
            {
                uint8* dataSrcAddrTmp;
                uint8* databufferAddr;
                dataSrcAddrTmp = (uint8*)dataSrcAddr;
                databufferAddr = (uint8*)((uint8*)bufferAddr_TypePTR->data +
                                    (bufferAddr_TypePTR->writeId * iocCfg->dataType->dataSize));
                /* Copy input data to IOC queue. */
                for( cnt = IOC_INIT; cnt < iocCfg->dataType->dataSize; cnt++ )
                {
                    /* Write input data to IOC buffer. */
                    *databufferAddr = *dataSrcAddrTmp;
                    databufferAddr++;
                    dataSrcAddrTmp++;
                }
                /* Increase the queue write counter. */
                OS_QUEUE_INCREASEINDEX(bufferAddr_TypePTR);
            }
        }
        /* IOC data unlock. */
        Os_Ioc_ULock(iocCfg, coreId, &intState);
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Ioc_IntlReceive
*
* Explanation: ioc internal receive function.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to send.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Application permission error.
*         IOC_E_NO_DATA: Ioc buffer is empty.
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_IntlReceive
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    P2CONST(void*const, AUTOMATIC, OS_APPL_CONST) data
)
{
    Std_ReturnType ret = IOC_E_OK;
    CoreIdType coreId;
    void* bufferAddr;
    const void* dataSrcAddr;
    Os_Arch_IntState intState;

    /* Get logic core id */
    coreId = Os_Core_GetLogicId();
    if( OS_APPMATCH(OS_IOC_GETRXCFG(iocCfg)->accessingApps, OS_CORE_GETAPPID(coreId)) )
    {
        ret = IOC_E_NOK;
    }
    else
    {
        /* IOC data lock. */
        Os_Ioc_Lock(iocCfg, coreId, &intState);
        /* Get buffer address. */
        bufferAddr = iocCfg->dataType->buffer;
        /* Get source data address. */
        dataSrcAddr = data[IOC_INIT];
        /* Check if the queue is lost data. */
        if( IOC_STATE_LOST == iocCfg->iocDyn->iocState )
        {
            ret = (Std_ReturnType)(IOC_E_LOST_DATA);
        }

        if( IOC_DATATYPE_BL == iocCfg->dataType->dataType )
        {
           Os_QueueType_BL* bufferAddr_TypeBL;
           bufferAddr_TypeBL = (Os_QueueType_BL*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeBL) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeBL, (boolean*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_U8 == iocCfg->dataType->dataType )
        {
           Os_QueueType_U8* bufferAddr_TypeU8;
           bufferAddr_TypeU8 = (Os_QueueType_U8*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeU8) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeU8, (uint8*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_U16 == iocCfg->dataType->dataType )
        {
           Os_QueueType_U16* bufferAddr_TypeU16;
           bufferAddr_TypeU16 = (Os_QueueType_U16*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeU16) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeU16, (uint16*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_U32 == iocCfg->dataType->dataType )
        {
           Os_QueueType_U32* bufferAddr_TypeU32;
           bufferAddr_TypeU32 = (Os_QueueType_U32*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeU32) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeU32, (uint32*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_U64 == iocCfg->dataType->dataType )
        {
           Os_QueueType_U64* bufferAddr_TypeU64;
           bufferAddr_TypeU64 = (Os_QueueType_U64*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeU64) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeU64, (uint64*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_S8 == iocCfg->dataType->dataType )
        {
           Os_QueueType_S8* bufferAddr_TypeS8;
           bufferAddr_TypeS8 = (Os_QueueType_S8*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeS8) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeS8, (sint8*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_S16 == iocCfg->dataType->dataType )
        {
           Os_QueueType_S16* bufferAddr_TypeS16;
           bufferAddr_TypeS16 = (Os_QueueType_S16*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeS16) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeS16, (sint16*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_S32 == iocCfg->dataType->dataType )
        {
           Os_QueueType_S32* bufferAddr_TypeS32;
           bufferAddr_TypeS32 = (Os_QueueType_S32*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeS32) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeS32, (sint32*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_S64 == iocCfg->dataType->dataType )
        {
           Os_QueueType_S64* bufferAddr_TypeS64;
           bufferAddr_TypeS64 = (Os_QueueType_S64*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeS64) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeS64, (sint64*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_FL == iocCfg->dataType->dataType )
        {
           Os_QueueType_FL* bufferAddr_TypeFL;
           bufferAddr_TypeFL = (Os_QueueType_FL*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeFL) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeFL, (float32*)dataSrcAddr);
           }
        }
        else if( IOC_DATATYPE_DB == iocCfg->dataType->dataType )
        {
           Os_QueueType_DB* bufferAddr_TypeDB;
           bufferAddr_TypeDB = (Os_QueueType_DB*)bufferAddr;
           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypeDB) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               /* Read data from IOC queue. */
               OS_QUEUE_POP(bufferAddr_TypeDB, (float64*)dataSrcAddr);
           }
        }
        else
        {
           uint32 cnt;
           Os_QueueType_Point* bufferAddr_TypePTR;
           bufferAddr_TypePTR = (Os_QueueType_Point*)bufferAddr;

           /* Check if the queue is empty. */
           if( OS_QUEUE_ISEMPTY(bufferAddr_TypePTR) )
           {
               ret = IOC_E_NO_DATA;
           }
           else
           {
               uint8* dataSrcAddrTmp;
               uint8* databufferAddr;
               dataSrcAddrTmp = (uint8*)dataSrcAddr;
               databufferAddr = (uint8*)((uint8*)bufferAddr_TypePTR->data +
                                        (bufferAddr_TypePTR->readId * iocCfg->dataType->dataSize));
               /* Copy input data to IOC queue. */
               for( cnt = IOC_INIT; cnt < iocCfg->dataType->dataSize; cnt++ )
               {
                   /* Write input data to IOC buffer. */
                   *dataSrcAddrTmp = *databufferAddr;
                   dataSrcAddrTmp++;
                   databufferAddr++;
               }
               /* Increase the queue write counter. */
               OS_QUEUE_DECREASEINDEX(bufferAddr_TypePTR);
           }
        }
        /* Clear the lost flag. */
        iocCfg->iocDyn->iocState = IOC_STATE_OK;
        /* IOC data unlock. */
        Os_Ioc_ULock(iocCfg, coreId, &intState);
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Ioc_ClearQueue
*
* Explanation: Clear the IOC queue
*
* param: iocCfg: Reference to an ioc.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Ioc_ClearQueue
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg
)
{
    uint32 queueCnt;
    void* bufferAddr;

    /* Get buffer address. */
    bufferAddr = iocCfg->dataType->buffer;

    if( IOC_DATATYPE_BL == iocCfg->dataType->dataType )
    {
        Os_QueueType_BL* bufferAddr_TypeBL;
        bufferAddr_TypeBL = (Os_QueueType_BL*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeBL->size; queueCnt++ )
        {
            bufferAddr_TypeBL->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeBL);
    }
    else if( IOC_DATATYPE_U8 == iocCfg->dataType->dataType )
    {
        Os_QueueType_U8* bufferAddr_TypeU8;
        bufferAddr_TypeU8 = (Os_QueueType_U8*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeU8->size; queueCnt++ )
        {
            bufferAddr_TypeU8->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeU8);
    }
    else if( IOC_DATATYPE_U16 == iocCfg->dataType->dataType )
    {
        Os_QueueType_U16* bufferAddr_TypeU16;
        bufferAddr_TypeU16 = (Os_QueueType_U16*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeU16->size; queueCnt++ )
        {
            bufferAddr_TypeU16->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeU16);
    }
    else if( IOC_DATATYPE_U32 == iocCfg->dataType->dataType )
    {
        Os_QueueType_U32* bufferAddr_TypeU32;
        bufferAddr_TypeU32 = (Os_QueueType_U32*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeU32->size; queueCnt++ )
        {
            bufferAddr_TypeU32->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeU32);
    }
    else if( IOC_DATATYPE_U64 == iocCfg->dataType->dataType )
    {
        Os_QueueType_U64* bufferAddr_TypeU64;
        bufferAddr_TypeU64 = (Os_QueueType_U64*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeU64->size; queueCnt++ )
        {
            bufferAddr_TypeU64->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeU64);
    }
    else if( IOC_DATATYPE_S8 == iocCfg->dataType->dataType )
    {
        Os_QueueType_S8* bufferAddr_TypeS8;
        bufferAddr_TypeS8 = (Os_QueueType_S8*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeS8->size; queueCnt++ )
        {
            bufferAddr_TypeS8->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeS8);
    }
    else if( IOC_DATATYPE_S16 == iocCfg->dataType->dataType )
    {
        Os_QueueType_S16* bufferAddr_TypeS16;
        bufferAddr_TypeS16 = (Os_QueueType_S16*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeS16->size; queueCnt++ )
        {
            bufferAddr_TypeS16->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeS16);
    }
    else if( IOC_DATATYPE_S32 == iocCfg->dataType->dataType )
    {
        Os_QueueType_S32* bufferAddr_TypeS32;
        bufferAddr_TypeS32 = (Os_QueueType_S32*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeS32->size; queueCnt++ )
        {
            bufferAddr_TypeS32->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeS32);
    }
    else if( IOC_DATATYPE_S64 == iocCfg->dataType->dataType )
    {
        Os_QueueType_S64* bufferAddr_TypeS64;
        bufferAddr_TypeS64 = (Os_QueueType_S64*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeS64->size; queueCnt++ )
        {
            bufferAddr_TypeS64->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeS64);
    }
    else if( IOC_DATATYPE_FL == iocCfg->dataType->dataType )
    {
        Os_QueueType_FL* bufferAddr_TypeFL;
        bufferAddr_TypeFL = (Os_QueueType_FL*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeFL->size; queueCnt++ )
        {
            bufferAddr_TypeFL->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeFL);
    }
    else if( IOC_DATATYPE_DB == iocCfg->dataType->dataType )
    {
        Os_QueueType_DB* bufferAddr_TypeDB;
        bufferAddr_TypeDB = (Os_QueueType_DB*)bufferAddr;
        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypeDB->size; queueCnt++ )
        {
            bufferAddr_TypeDB->data[queueCnt] = IOC_INIT;
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypeDB);
    }
    else
    {
        uint32 cnt;
        uint8* dataTmp;
        Os_QueueType_Point* bufferAddr_TypePTR;
        bufferAddr_TypePTR = (Os_QueueType_Point*)bufferAddr;

        /* Clear the queue data. */
        for( queueCnt = IOC_INIT; queueCnt < bufferAddr_TypePTR->size; queueCnt++ )
        {
            dataTmp = (uint8*)((uint8*)(bufferAddr_TypePTR->data) + (queueCnt * iocCfg->dataType->dataSize));
            /* Clear the queue data. */
            for( cnt = IOC_INIT; cnt < iocCfg->dataType->dataSize; cnt++ )
            {
                /* Clear the queue data. */
                *dataTmp = IOC_INIT;
            }
        }
        OS_QUEUE_SETEMPTY(bufferAddr_TypePTR);
    }
}

/*
********************************************************************************
* Function Name: Os_Ioc_Init
*
* Explanation: Uses to init an ioc.
*
* param: iocCfg: Reference to an ioc.
*
* retval: None
********************************************************************************
*/
FUNC(void, OS_CODE) Os_Ioc_Init
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg
)
{
    /* Check the spinlockCfg is not NULL_PTR. */
    Os_ParamCheck(NULL_PTR != iocCfg);
    /* Init ioc state. */
    iocCfg->iocDyn->iocState = IOC_STATE_OK;
    if( OS_IOC_CHRCKISQUEIOC(iocCfg) )
    {
        IocQueueInit iocInitFunc = iocCfg->func;
        iocInitFunc();
    }
}

/*
********************************************************************************
* Function Name: Os_Ioc_Write
*
* Explanation: Write data to an ioc.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to write.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Application permission error.
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_Write
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    uint32 senderId,
    P2CONST(void*const, AUTOMATIC, OS_APPL_CONST) data
)
{
    Std_ReturnType ret;

    if( (NULL_PTR != iocCfg) && (NULL_PTR != data) )
    {
        if( senderId < iocCfg->senderCnt )
        {
            OS_ORTI_API_MONITOR_ENTRY(OSServiceId_IocWrite);

#if( OS_MEMORY_PROTECTION == STD_ON )
            if( TRUE == iocCfg->sysCall )
            {
                Os_SysCallParamType sysCallParam;
                sysCallParam.Os_IocWrite.iocCfg = iocCfg;
                sysCallParam.Os_IocWrite.senderId = senderId;
                sysCallParam.Os_IocWrite.data = data;
                Os_SysCall(Os_Syscall_IocWrite_ID, &sysCallParam);
                ret = (Std_ReturnType)sysCallParam.Os_IocWrite.retVal;
            }
            else
#endif
            {
                /* Write data to the buffer. */
                ret = Os_Ioc_IntlWrite(iocCfg, senderId, data);
            }
            OS_ORTI_API_MONITOR_EXIT(OSServiceId_IocWrite);
        }
        else
        {
            ret = IOC_E_NOK;
        }
    }
    else
    {
        ret = IOC_E_NOK;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Ioc_Read
*
* Explanation: Read data to an ioc.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to read.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Application permission error.
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_Read
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    P2CONST(void*const, AUTOMATIC, OS_APPL_CONST) data
)
{
    Std_ReturnType ret;

    if( (NULL_PTR != iocCfg) && (NULL_PTR != data) )
    {
        OS_ORTI_API_MONITOR_ENTRY(OSServiceId_IocRead);

#if( OS_MEMORY_PROTECTION == STD_ON )
        if( TRUE == iocCfg->sysCall )
        {
            Os_SysCallParamType sysCallParam;
            sysCallParam.Os_IocRead.iocCfg = iocCfg;
            sysCallParam.Os_IocRead.data = data;
            Os_SysCall(Os_Syscall_IocRead_ID, &sysCallParam);
            ret = (Std_ReturnType)sysCallParam.Os_IocRead.retVal;
        }
        else
#endif
        {
            /* Read data from the buffer. */
            ret = Os_Ioc_IntlRead(iocCfg, data);
        }

        OS_ORTI_API_MONITOR_EXIT(OSServiceId_IocRead);
    }
    else
    {
        ret = IOC_E_NOK;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Ioc_Send
*
* Explanation: Send data to an ioc.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to send.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Application permission error.
*         IOC_E_LIMIT: Ioc buffer is full;
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_Send
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    uint32 senderId,
    P2CONST(void*const, AUTOMATIC, OS_APPL_CONST) data
)
{
    Std_ReturnType ret;

    if( (NULL_PTR != iocCfg) && (NULL_PTR != data) )
    {
        if( senderId < iocCfg->senderCnt )
        {
            OS_ORTI_API_MONITOR_ENTRY(OSServiceId_IocSend);

#if( OS_MEMORY_PROTECTION == STD_ON )
            if( TRUE == iocCfg->sysCall )
            {
                Os_SysCallParamType sysCallParam;
                sysCallParam.Os_IocSend.iocCfg = iocCfg;
                sysCallParam.Os_IocSend.senderId = senderId;
                sysCallParam.Os_IocSend.data = data;
                Os_SysCall(Os_Syscall_IocSend_ID, &sysCallParam);
                ret = (Std_ReturnType)sysCallParam.Os_IocSend.retVal;
            }
            else
#endif
            {
                /* Write data to the buffer. */
                ret = Os_Ioc_IntlSend(iocCfg, senderId, data);
            }

            OS_ORTI_API_MONITOR_EXIT(OSServiceId_IocSend);
        }
        else
        {
            ret = IOC_E_NOK;
        }
    }
    else
    {
        ret = IOC_E_NOK;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Ioc_Receive
*
* Explanation: receive data to an ioc.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to send.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Application permission error.
*         IOC_E_NO_DATA: Ioc buffer is empty.
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_Receive
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg,
    P2CONST(void*const, AUTOMATIC, OS_APPL_CONST) data
)
{
    Std_ReturnType ret;

    if( (NULL_PTR != iocCfg) && (NULL_PTR != data) )
    {
        OS_ORTI_API_MONITOR_ENTRY(OSServiceId_IocReceive);

#if( OS_MEMORY_PROTECTION == STD_ON )
        if( TRUE == iocCfg->sysCall )
        {
            Os_SysCallParamType sysCallParam;
            sysCallParam.Os_IocReceive.iocCfg = iocCfg;
            sysCallParam.Os_IocReceive.data = data;
            Os_SysCall(Os_Syscall_IocReceive_ID, &sysCallParam);
            ret = (Std_ReturnType)sysCallParam.Os_IocReceive.retVal;
        }
        else
#endif
        {
            /* Read data from the buffer. */
            ret = Os_Ioc_IntlReceive(iocCfg, data);
        }

        OS_ORTI_API_MONITOR_EXIT(OSServiceId_IocReceive);
    }
    else
    {
        ret = IOC_E_NOK;
    }

    return ret;
}

/*
********************************************************************************
* Function Name: Os_Ioc_EmptyQueue
*
* Explanation: Empty the IOC's queue.
*
* param: iocCfg: Reference to an ioc.
*        data: Data to send.
*
* retval: IOC_E_OK: No error.
*         IOC_E_NOK: Parameter error.
********************************************************************************
*/
FUNC(Std_ReturnType, OS_CODE) Os_Ioc_EmptyQueue
(
    P2CONST(Os_IocCfgType, AUTOMATIC, OS_APPL_CONST) iocCfg
)
{
    Std_ReturnType ret = IOC_E_OK;

    if( NULL_PTR != iocCfg )
    {
        if( iocCfg->bufferLength > IOC_INIT )
        {
            OS_ORTI_API_MONITOR_ENTRY(OSServiceId_IocEmptyQueue);

#if( OS_MEMORY_PROTECTION == STD_ON )
            if( TRUE == iocCfg->sysCall )
            {
                Os_SysCallParamType sysCallParam;
                sysCallParam.Os_IocEmptyQueue.iocCfg = iocCfg;
                Os_SysCall(Os_Syscall_IocEmptyQueue_ID, &sysCallParam);
            }
            else
#endif
            {
                /* Clear the ioc queue. */
                Os_Ioc_ClearQueue(iocCfg);
            }

            OS_ORTI_API_MONITOR_EXIT(OSServiceId_IocEmptyQueue);
        }
        else
        {
            ret = IOC_E_NOK;
        }
    }
    else
    {
        ret = IOC_E_NOK;
    }

    return ret;
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap.h"

