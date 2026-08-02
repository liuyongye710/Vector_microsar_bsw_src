/*
********************************************************************************
*
* File name: E2E_P04.c
*
* Copyright 2019-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date: WangJipeng/2019.04.20
* Change: New created
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P04Check Parameter duplication Offset
*         = ConfigPtr->Offset/E2E_8BIT.
* Cause: Bugfix
********************************************************************************
* Version: 1.2
* Author/Date: wanghe/2019.05.06
* Change: Change E2E_P04Check_ChkParam And E2E_P04Protect_ChkParam Judge Branch
*         From if ((Length >= ConfigPtr->MinDataLength) &&
*         (Length <= ConfigPtr->MaxDataLength))
*         to if ((Length >= ConfigPtr->MinDataLength/E2E_8BIT) &&
*         (Length <= ConfigPtr->MaxDataLength/E2E_8BIT)).
* Cause: Bugfix
********************************************************************************
* Version: 1.3
* Author/Date : wanghe/2019.05.20
* Change: E2E_P04Check Function Add Return value
* Cause: Bugfix
********************************************************************************
* Version: 1.4
* Author/Date : wanghe/2019.05.20
* Change: E2E_P04Check_ChkDeltaCounter Function DeltaCounter
*         type change to sint32.
* Cause: Bugfix
********************************************************************************
* Version: 2.0
* Author/Date : WangHe/2019.05.20
* Change: Optimization All Function
* Cause:  Optimization
********************************************************************************
* Version: 2.1
* Author/Date: WangHe/2019.11.22
* Change: Local variables are defined by hump standard and format modification.
* Cause:  Optimization
********************************************************************************
* Version: 2.2
* Author/Date: WangHe/2019.12.13
* Change: E2E_P04Check Function counter difference value reverse.
* Cause:  Bugfix
********************************************************************************
* Version: 3.0
* Author/Date : Baowanglong/2020.03.27
* Change: Nothing
* Cause: Update to V3.0
********************************************************************************
* Version: 3.1
* Author/Date : Tanjingyang/2020.09.29
* Change: 1.Add function of MemMap
*         2.Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.2
* Author/Date : Tanjingyang/2020.10.29
* Change: 1.Modify the function name according to the AUTOSAR specification.
* Cause: Optimization
********************************************************************************
* Version: 3.3
* Author/Date : TanJY/2020.11.03
* Change: Modify code format.
* Cause: Optimization
********************************************************************************
* Version: 3.4
* Author/Date : BaoWL/2021.03.25
* Change: E2E_P04Check function. Modify the DataPtr parameter type to const uint8*.
* Cause: Bugfix
********************************************************************************
* Version: 3.5
* Author/Date: XieYN/2021.08.13
* Change:Modify code specifications.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiDY/2023.07.13
* Change:E2E_P04CheckInit the counter shall be initialized with 0xFFFF
* Cause: Bugfix
********************************************************************************
* Version: 3.7
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.8
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.9
* Author/Date: LiDaY/2024.08.08
* Change: Change copyright information.
* Cause: Update
********************************************************************************
*/
/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "E2E_P04.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
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
#define E2E_START_SEC_CODE
#include "E2E_MemMap.h"

static FUNC(void, E2E_CODE) E2E_P04Protect_WriteData
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length,
    uint16 Counter,
    uint32 DataID
);
static FUNC(void, E2E_CODE) E2E_P04Protect_WriteCrc
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint32 Crc
);
static FUNC(uint16, E2E_CODE) E2E_P04Check_ReadLength
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint16, E2E_CODE) E2E_P04Check_ReadCounter
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint32, E2E_CODE) E2E_P04Check_ReadDataID
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint32, E2E_CODE) E2E_P04Check_ReadCrc
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(void, E2E_CODE) E2E_P04Check_ChkDeltaCounter
(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    sint32 DeltaCounter
);
static FUNC(uint8, E2E_CODE) E2E_P04Protect_ChkParam
(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
);
static FUNC(uint8, E2E_CODE) E2E_P04Check_ChkParam
(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable,
    uint16 Length
);

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"

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
#define E2E_START_SEC_CODE
#include "E2E_MemMap.h"

/*
********************************************************************************
* Function Name: E2E_P04Protect_WriteData
*
* Explanation: Write Crc.(Synchronous)
*
* param: DataPtr: Pointer to Data to be transmitted.
*        Length: Length of Transmit Data.
*        Counter: Counter of Transmit Data.
*        DataID: DataID of Transmit Data.
* retval: None
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_P04Protect_WriteData
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length,
    uint16 Counter,
    uint32 DataID
)
{
    uint32 dataId1 = E2E_INIT_0;
    uint32 dataId2 = E2E_INIT_0;

    /* [SWS_E2E_00364] */ /* Write Length. */
    DataPtr[E2E_INDEX_0] = (uint8)((Length >> E2E_8BIT) & E2E_FULL_BYTE);
    /* [SWS_E2E_00364] */
    DataPtr[E2E_INDEX_1] = (uint8)(Length & E2E_FULL_BYTE);
    /* [SWS_E2E_00365]*/ /* Write Counter. */
    DataPtr[E2E_INDEX_2] = (uint8)((Counter >> E2E_8BIT) & E2E_FULL_BYTE);
    /* [SWS_E2E_00365]*/
    DataPtr[E2E_INDEX_3] = (uint8)(Counter & E2E_FULL_BYTE);
    dataId1 = DataID >> E2E_8BIT;  /* [SWS_E2E_00326] */
    dataId1 = dataId1 >> E2E_8BIT; /* [SWS_E2E_00326] */
    /* [SWS_E2E_00326] [SWS_E2E_00366] */ /* Write DataID. */
    DataPtr[E2E_INDEX_4] = (uint8)((dataId1 >> E2E_8BIT) & E2E_FULL_BYTE);
    dataId2 = DataID >> E2E_8BIT;  /* [SWS_E2E_00326] */
    /* [SWS_E2E_00326] [SWS_E2E_00366] */
    DataPtr[E2E_INDEX_5] = (uint8)((dataId2 >> E2E_8BIT) & E2E_FULL_BYTE);
    /* [SWS_E2E_00326] [SWS_E2E_00366]*/
    DataPtr[E2E_INDEX_6] = (uint8)((DataID >> E2E_8BIT) & E2E_FULL_BYTE);
    /* [SWS_E2E_00326] [SWS_E2E_00366] */
    DataPtr[E2E_INDEX_7] = (uint8)(DataID & E2E_FULL_BYTE);
}

/*
********************************************************************************
* Function Name: E2E_P04Protect_WriteCrc
*
* Explanation: Write Crc.(Synchronous)
*
* param: DataPtr: Pointer to Data to be transmitted.
*        Crc: Crc of Calculation.
* retval: None
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_P04Protect_WriteCrc
(
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint32 Crc
)
{
    uint32 crc1 = E2E_INIT_0;
    uint32 crc2 = E2E_INIT_0;

    crc1 = Crc >> E2E_8BIT;  /* [SWS_E2E_00368] */
    crc1 = crc1 >> E2E_8BIT; /* [SWS_E2E_00368] */
    /* [SWS_E2E_00368] */ /* Write CRC. */
    DataPtr[E2E_INDEX_0] = (uint8)((crc1 >> E2E_8BIT) & E2E_FULL_BYTE);
    crc2 = Crc >> E2E_8BIT;  /* [SWS_E2E_00368] */
    /* [SWS_E2E_00368] */
    DataPtr[E2E_INDEX_1] = (uint8)((crc2 >> E2E_8BIT) & E2E_FULL_BYTE);
    /* [SWS_E2E_00368] */
    DataPtr[E2E_INDEX_2] = (uint8)((Crc >> E2E_8BIT) & E2E_FULL_BYTE);
    DataPtr[E2E_INDEX_3] = (uint8)(Crc & E2E_FULL_BYTE); /* [SWS_E2E_00368] */
}

/*
********************************************************************************
* Function Name: E2E_P04Check_ReadLength
*
* Explanation: Read Length.(Synchronous)
*
* param: DataPtr: Pointer to Data to be transmitted.
*
* retval: uint16
********************************************************************************
*/
/* [SWS_E2E_00357] */
static FUNC(uint16, E2E_CODE) E2E_P04Check_ReadLength
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint16 readLength = E2E_INIT_0;

    readLength = (uint16)DataPtr[E2E_INDEX_0] << E2E_8BIT; /* [SWS_E2E_00357] */
    readLength |= (uint16)(DataPtr[E2E_INDEX_1]);          /* [SWS_E2E_00357] */

    return readLength;                                     /* [SWS_E2E_00357] */
}

/*
********************************************************************************
* Function Name: E2E_P04Check_ReadCounter
*
* Explanation: Read Counter.(Synchronous)
*
* param: DataPtr: Pointer to Data to be transmitted.
*
* retval: uint16
********************************************************************************
*/
/* [SWS_E2E_00358] */
static FUNC(uint16, E2E_CODE) E2E_P04Check_ReadCounter
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint16 receivedCounter = E2E_INIT_0;

    receivedCounter = (uint16)DataPtr[E2E_INDEX_0] << E2E_8BIT; /* [SWS_E2E_00358] */
    receivedCounter |= (uint16)DataPtr[E2E_INDEX_1];        /* [SWS_E2E_00358] */

    return receivedCounter;                                /* [SWS_E2E_00358] */
}

/*
********************************************************************************
* Function Name: E2E_P04Check_ReadDataID
*
* Explanation: Read Data ID.(Synchronous)
*
* param: DataPtr: Pointer to Data to be transmitted.
*
* retval: uint32
********************************************************************************
*/
static FUNC(uint32, E2E_CODE) E2E_P04Check_ReadDataID
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint32 receivedDataId = E2E_INIT_0;
    uint32 dataId1 = E2E_INIT_0;
    uint32 dataId2 = E2E_INIT_0;

    dataId1 = (uint32)DataPtr[E2E_INDEX_0] << E2E_8BIT;    /* [SWS_E2E_00359] */
    dataId1 = dataId1 << E2E_8BIT;                         /* [SWS_E2E_00359] */
    receivedDataId = dataId1 << E2E_8BIT;                  /* [SWS_E2E_00359] */
    dataId2 = (uint32)DataPtr[E2E_INDEX_1] << E2E_8BIT;    /* [SWS_E2E_00359] */
    receivedDataId |= dataId2 << E2E_8BIT;                 /* [SWS_E2E_00359] */
    receivedDataId |= (uint32)DataPtr[E2E_INDEX_2] << E2E_8BIT; /* [SWS_E2E_00359] */
    receivedDataId |= (uint32)DataPtr[E2E_INDEX_3];        /* [SWS_E2E_00359] */

    return receivedDataId;                                 /* [SWS_E2E_00359] */
}

/*
********************************************************************************
* Function Name: E2E_P04Check_ReadCrc
*
* Explanation: Read Crc.(Synchronous)
*
* param: DataPtr: Pointer to Data to be transmitted.
*
* retval: uint32
********************************************************************************
*/
/* [SWS_E2E_00360] */
static FUNC(uint32, E2E_CODE) E2E_P04Check_ReadCrc
(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint32 receivedCrc = E2E_INIT_0;
    uint32 crc1 = E2E_INIT_0;
    uint32 crc2 = E2E_INIT_0;

    crc1 = (uint32)DataPtr[E2E_INDEX_0] << E2E_8BIT;         /* [SWS_E2E_00360] */
    crc1 = crc1 << E2E_8BIT;                                 /* [SWS_E2E_00360] */
    receivedCrc = crc1 << E2E_8BIT;                          /* [SWS_E2E_00360] */
    crc2 = (uint32)DataPtr[E2E_INDEX_1] << E2E_8BIT;         /* [SWS_E2E_00360] */
    receivedCrc |= crc2 << E2E_8BIT;                         /* [SWS_E2E_00360] */
    receivedCrc |= (uint32)DataPtr[E2E_INDEX_2] << E2E_8BIT; /* [SWS_E2E_00360] */
    receivedCrc |= (uint32)DataPtr[E2E_INDEX_3];             /* [SWS_E2E_00360] */

    return receivedCrc;                                      /* [SWS_E2E_00360] */
}

/*
********************************************************************************
* Function Name: E2E_P04Check_ChkDeltaCounter
*
* Explanation: Check parameter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DeltaCounter: This frame message counter to last frame message
*                      counter difference value.
* retval: None
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_P04Check_ChkDeltaCounter
(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    sint32 DeltaCounter
)
{
    sint32 e2eJudge0 = (sint32)E2E_INIT_0;
    sint32 e2eJudge1 = (sint32)E2E_INIT_1;

    /* DeltaCounter is limit range. */
    if( (DeltaCounter <= (sint32)ConfigPtr->MaxDeltaCounter) &&
        (DeltaCounter >= e2eJudge0) )  /* [SWS_E2E_00361] */
    {
        if( DeltaCounter > e2eJudge0 ) /* [SWS_E2E_00361] */
        {
            /* data counter is continuity. */
            if( e2eJudge1 == DeltaCounter ) /* [SWS_E2E_00361] */
            {
                StatePtr->Status = E2E_P04STATUS_OK; /* [SWS_E2E_00361] */
            }
            /* [SWS_E2E_00361] */
            /* DeltaCounter is  too big,but is in config limit. */
            else
            {
                /* [SWS_E2E_00361] */
                StatePtr->Status = E2E_P04STATUS_OKSOMELOST;
            }
        }
        else /* [SWS_E2E_00361] */ /* repeated data. */
        {
            StatePtr->Status = E2E_P04STATUS_REPEATED; /* [SWS_E2E_00361] */
        }
    }
    else /* [SWS_E2E_00361] */ /* DeltaCounter go beyond range. */
    {
        StatePtr->Status = E2E_P04STATUS_WRONGSEQUENCE; /* [SWS_E2E_00361] */
    }
}

/*
********************************************************************************
* Function Name: E2E_P04Protect_ChkParam
*
* Explanation: Check parameter (Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        Length: Daata length.
*
* retval: Std_ReturnType
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_P04Protect_ChkParam
(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00363] */
    uint16 minDataByte = E2E_INIT_0;      /* [SWS_E2E_00363] */
    uint16 maxDataByte = E2E_INIT_0;      /* [SWS_E2E_00363] */

    /* [SWS_E2E_00363] */
    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;   /* [SWS_E2E_00363] */
    }
    else
    {
        minDataByte = ConfigPtr->MinDataLength / E2E_8BIT; /* [SWS_E2E_00363] */
        maxDataByte = ConfigPtr->MaxDataLength / E2E_8BIT; /* [SWS_E2E_00363] */
        /* [SWS_E2E_00363] */
        /* data length is in limit range. */
        if( (Length >= minDataByte) && (Length <= maxDataByte) )
        {
            rtrnValu = E2E_E_OK; /* [SWS_E2E_00363] */
        }
        else
        {
            rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00363] */
        }
    }

    return rtrnValu; /* [SWS_E2E_00363] */
}

/*
********************************************************************************
* Function Name: E2E_P04Check_ChkParam
*
* Explanation: Check parameter.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        NewDataAvailable: New Data avaiable.
*        Length: Daata length.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00356] */
static FUNC(uint8, E2E_CODE) E2E_P04Check_ChkParam
(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable,
    uint16 Length
)
{
    uint8 rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00356] */
    uint16 minDataByte = E2E_INIT_0;      /* [SWS_E2E_00356] */
    uint16 maxDataByte = E2E_INIT_0;      /* [SWS_E2E_00356] */

    /* [SWS_E2E_00356] */
    /* At least one pointer parameter is a NULL pointer. */
    if( (NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr) )
    {
        /* [SWS_E2E_00356] */ /* data Meet the requirements. */
        if( ((NULL_PTR != DataPtr) && (E2E_JUDGE_0 != Length)) ||
            ((NULL_PTR == DataPtr) && (E2E_JUDGE_0 == Length)) )
        {
            if( NULL_PTR != DataPtr ) /* [SWS_E2E_00356] */
            {
                /* [SWS_E2E_00356] */
                minDataByte = ConfigPtr->MinDataLength / E2E_8BIT;
                /* [SWS_E2E_00356] */
                maxDataByte = ConfigPtr->MaxDataLength / E2E_8BIT;
                /* [SWS_E2E_00356] */ /* data length is in limit range. */
                if( (Length >= minDataByte) && (Length <= maxDataByte) )
                {
                    *NewDataAvailable = TRUE; /* [SWS_E2E_00356] */
                    rtrnValu = E2E_E_OK; /* [SWS_E2E_00356] */
                }
                else /* [SWS_E2E_00356] */
                {
                    rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00356] */
                }
            }
            else /* [SWS_E2E_00356] */ /* data is ok. */
            {
                rtrnValu = E2E_E_OK; /* [SWS_E2E_00356] */
            }
        }
        else /* [SWS_E2E_00356] */
        {
            rtrnValu = E2E_E_INPUTERR_WRONG; /* [SWS_E2E_00356] */
        }
    }
    else /* [SWS_E2E_00356] */
    {
        rtrnValu = E2E_E_INPUTERR_NULL;  /* [SWS_E2E_00356] */
    }

    return rtrnValu; /* [SWS_E2E_00356] */
}

/*
********************************************************************************
* Function Name: E2E_P04Protect
*
* Explanation: Protects the array/buffer to be transmitted using the E2E
*              profile 4.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        Length: Length of the data in bytes.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P04Protect
(
    P2VAR(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint16 offset = E2E_INIT_0;
    uint16 lengthbf = E2E_INIT_0;
    uint16 lengthaf = E2E_INIT_0;
    uint32 crcValu = E2E_INIT_0;

    /* [SWS_E2E_00362] */   /* Verify inputs of the protect function. */
    rtrnValu = E2E_P04Protect_ChkParam(ConfigPtr, StatePtr, DataPtr, Length);
    if( E2E_E_OK == rtrnValu ) /* [SWS_E2E_00362] */
    {
        /* Compute offset. */
        offset = ConfigPtr->Offset / E2E_8BIT; /* [SWS_E2E_00376] */
        /* [SWS_E2E_00362] */   /* Write Length, Counter, DataID in DataPtr. */
        E2E_P04Protect_WriteData(&DataPtr[offset], Length, StatePtr->Counter,
                                 ConfigPtr->DataID);
        lengthbf = offset + E2E_8BIT; /* [SWS_E2E_00362]  [SWS_E2E_00367]*/
        /* [SWS_E2E_00362]  [SWS_E2E_00367]*/
        /* compute CRC over bytes that are before CRC. */
        crcValu = Crc_CalculateCRC32P4(DataPtr, lengthbf, E2E_FULL_4BYTE, TRUE);
        /* Compute CRC over bytes that are after CRC (if any). */
        if( (offset + E2E_12BIT) < Length ) /* [SWS_E2E_00362] [SWS_E2E_00367]*/
        {
            /* [SWS_E2E_00362] [SWS_E2E_00367]*/
            lengthaf = Length - (offset + E2E_12BIT);
            /* [SWS_E2E_00362] [SWS_E2E_00367]*/
            crcValu = Crc_CalculateCRC32P4(&DataPtr[offset + E2E_12BIT],
                                           lengthaf, crcValu, FALSE);
        }
        /* [SWS_E2E_00362] [SWS_E2E_00368] */ /* Write CRC. */
        E2E_P04Protect_WriteCrc(&DataPtr[offset + E2E_8BIT], crcValu);
        /* [SWS_E2E_00478] */
        if( StatePtr->Counter < E2E_P04PROTECT_COUNTERMAX )
        {
            StatePtr->Counter++; /* [SWS_E2E_00478] [SWS_E2E_00369]*/
        }
        else
        {
            StatePtr->Counter = E2E_INIT_0; /* [SWS_E2E_00478] [SWS_E2E_00369]*/
        }
    }

    return rtrnValu; /* [SWS_E2E_00362] */
}

/*
********************************************************************************
* Function Name: E2E_P04ProtectInit
*
* Explanation: Initializes the protection state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00373] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04ProtectInit
(
    P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00377] */

    if( NULL_PTR != StatePtr ) /* [SWS_E2E_00377] */ /* the param is valid. */
    {
        StatePtr->Counter = E2E_INIT_0; /* [SWS_E2E_00377] */
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu; /* [SWS_E2E_00377] */
}

/*
********************************************************************************
* Function Name: E2E_P04Check
*
* Explanation: Checks the Data received using the E2E profile 4.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to received data.
*        Length: Length of the data in bytes.
*
* retval: Std_ReturnType
********************************************************************************
*/
 /* [SWS_E2E_00339] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04Check
(
    P2VAR(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 Length
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 newDataAvailable = FALSE;
    uint16 offset = E2E_INIT_0;
    uint16 receivedLength = E2E_INIT_0;
    uint16 receivedCounter = E2E_INIT_FULL2BYTE;
    uint16 lengthbf = E2E_INIT_0;
    uint16 lengthaf = E2E_INIT_0;
    uint32 receivedDataId = E2E_INIT_0;
    uint32 receivedCrc = E2E_INIT_0;
    uint32 computedCrc = E2E_INIT_0;
    sint32 deltaCounter = (sint32)E2E_INIT_0;

    /* [SWS_E2E_00355] */   /* Verify inputs of the protect function. */
    rtrnValu = E2E_P04Check_ChkParam(ConfigPtr, StatePtr, DataPtr,
                                     &newDataAvailable, Length);
    if( E2E_E_OK == rtrnValu ) /* [SWS_E2E_00355] */
    {
        /* If any NEW data is available to be checked. */
        if( TRUE == newDataAvailable ) /* [SWS_E2E_00361] */
        {
            offset = ConfigPtr->Offset / E2E_8BIT; /* [SWS_E2E_00355] */
            /* [SWS_E2E_00355] */ /* Read Data lenth. */
            receivedLength = E2E_P04Check_ReadLength(&DataPtr[offset]);
            /* [SWS_E2E_00355] */ /* Read Data counter. */
            receivedCounter = E2E_P04Check_ReadCounter(&DataPtr[offset + E2E_2BIT]);
            /* [SWS_E2E_00355] */ /* Read Data ID. */
            receivedDataId = E2E_P04Check_ReadDataID(&DataPtr[offset + E2E_4BIT]);
            /* [SWS_E2E_00355] */ /* Read Data CRC. */
            receivedCrc = E2E_P04Check_ReadCrc(&DataPtr[offset + E2E_8BIT]);
            lengthbf = offset + E2E_8BIT; /* [SWS_E2E_00355] */
            /* [SWS_E2E_00329] [SWS_E2E_00355] */
            /* compute CRC over bytes that are before CRC. */
            computedCrc = Crc_CalculateCRC32P4(DataPtr, lengthbf, E2E_FULL_4BYTE, TRUE);

            /* Compute CRC over bytes that are after CRC (if any). */
            if( (offset + E2E_12BIT) < Length ) /* [SWS_E2E_00355] */
            {
                lengthaf = Length - (offset + E2E_12BIT); /* [SWS_E2E_00355] */
                /* [SWS_E2E_00355] */
                /* Computation based on the acquired data count crc. */
                computedCrc = Crc_CalculateCRC32P4(&DataPtr[offset + E2E_12BIT],
                                                   lengthaf, computedCrc, FALSE);
            }
            /* [SWS_E2E_00361] */ /* compare received crc and compute crc. */
            if( receivedCrc == computedCrc )
            {
                /* [SWS_E2E_00361] */
                /* compare received data and actual data id. */
                if( receivedDataId == ConfigPtr->DataID )
                {
                    /* [SWS_E2E_00361] */
                    /* compare received data length and actual data length. */
                    if( receivedLength == Length )
                    {
                        /* [SWS_E2E_00361] */
                        if( receivedCounter >= StatePtr->Counter )
                        {
                            deltaCounter = (sint32)receivedCounter
                                           - (sint32)StatePtr->Counter;
                        }
                        else /* [SWS_E2E_00361] */
                        {
                            /* [SWS_E2E_00361] */
                            deltaCounter = (sint32)receivedCounter
                                           - (sint32)StatePtr->Counter
                                           + (sint32)E2E_P04PROTECT_COUNTERMAX
                                           + (sint32)E2E_COUNTER_1;
                        }
                        /* [SWS_E2E_00361] */
                        E2E_P04Check_ChkDeltaCounter(ConfigPtr, StatePtr, deltaCounter);
                        /* [SWS_E2E_00361] */
                        StatePtr->Counter = receivedCounter;
                    }
                    /* [SWS_E2E_00361] */
                    /* error not related to data length. */
                    else
                    {
                        /* [SWS_E2E_00361] */
                        StatePtr->Status = E2E_P04STATUS_ERROR;
                    }
                }
                else /* [SWS_E2E_00361] */ /* error not related to data ID. */
                {
                    /* [SWS_E2E_00361] */
                    StatePtr->Status = E2E_P04STATUS_ERROR;
                }
            }
            else /* [SWS_E2E_00361] */ /* error not related to crc. */
            {
                StatePtr->Status = E2E_P04STATUS_ERROR; /* [SWS_E2E_00361] */
            }
        }
        else /* [SWS_E2E_00361] */
        {
            StatePtr->Status = E2E_P04STATUS_NONEWDATA; /* [SWS_E2E_00361] */
        }
    }

    return rtrnValu; /* [SWS_E2E_00355] */
}

/*
********************************************************************************
* Function Name: E2E_P04CheckInit
*
* Explanation: Initializes the check state.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
/* [SWS_E2E_00350] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04CheckInit
(
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL; /* [SWS_E2E_00378] */

    if( NULL_PTR != StatePtr ) /* [SWS_E2E_00378] */ /* the param is valid. */
    {
        StatePtr->Counter = E2E_INIT_FULL2BYTE;         /* [SWS_E2E_00378] */
        StatePtr->Status = E2E_P04STATUS_ERROR; /* [SWS_E2E_00378] */
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu; /* [SWS_E2E_00378] */
}

/*
********************************************************************************
* Function Name: E2E_P04MapStatusToSM
*
* Explanation: The function maps the check status of Profile 4 to a generic
*              check status.(Synchronous)
* param: CheckReturn: Return value of the E2E_P04Check function.
*        Status: Status determined by E2E_P04Check function.
*
* retval: E2E_PCheckStatusType
********************************************************************************
*/
/* [SWS_E2E_00349] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P04MapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_P04CheckStatusType Status
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00352] */

    if( E2E_E_OK == CheckReturn ) /* [SWS_E2E_00351] */
    {
        switch( Status )
        {
            case E2E_P04STATUS_OK:
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00351] */
                break;
            case E2E_P04STATUS_OKSOMELOST:
                rtrnValu = E2E_P_OK; /* [SWS_E2E_00351] */
                break;
            case E2E_P04STATUS_ERROR:
                rtrnValu = E2E_P_ERROR; /* [SWS_E2E_00351] */
                break;
            case E2E_P04STATUS_REPEATED:
                rtrnValu = E2E_P_REPEATED; /* [SWS_E2E_00351] */
                break;
            case E2E_P04STATUS_NONEWDATA:
                rtrnValu = E2E_P_NONEWDATA; /* [SWS_E2E_00351] */
                break;
            case E2E_P04STATUS_WRONGSEQUENCE:
                rtrnValu = E2E_P_WRONGSEQUENCE; /* [SWS_E2E_00351] */
                break;
            default:
                break;
        }
    }

    return rtrnValu; /* [SWS_E2E_00352] [SWS_E2E_00351] */
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
