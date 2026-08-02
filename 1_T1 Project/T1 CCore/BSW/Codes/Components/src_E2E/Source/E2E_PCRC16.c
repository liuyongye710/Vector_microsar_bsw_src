/*
********************************************************************************
*
* File name: E2E_PCRC16.c
*
* Copyright 2022-2024 Neusoft Reach Corporation.All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: XieYN/2022.09.09
* Change: New created
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: XieYN/2022.10.31
* Change: Increase the configurable range of counter: 0, 4, 8, 16.
* Cause: Update
********************************************************************************
* Version: 3.2
* Author/Date: XieYN/2022.12.02
* Change: 1. Modify crc calculate startbyte in Crc_CalculateCRC16.
*         2. Modify crcByte in E2E_PCRC16Check when configered with little endian.
* Cause: Bugfix
********************************************************************************
* Version: 3.3
* Author/Date: XieYN/2023.01.09
* Change: Modify read Counter when CounterSize is 4, and which is located in
*         high nibble of the data in E2E_PCRC16_ReadCounter.
* Cause: Bugfix
********************************************************************************
* Version: 3.4
* Author/Date: LiDaY/2023.09.25
* Change: Resolve Compile warnings.
*         Modify the receivedCounter from uint8 type to uint16 in the
*         E2E_PCRC16Check function.
*         E2E_ PCRC16_ WriteCounter adds a parenthesis.
* Cause: Optimization
********************************************************************************
* Version: 3.5
* Author/Date: LiDaY/2024.02.05
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.6
* Author/Date: LiDaY/2024.03.18
* Change: Modifying the label of the input parameter Ptrclass for E2E function
*         and addressing some code inconsistencies.
* Cause: Optimization
********************************************************************************
* Version: 3.7
* Author/Date: LiDaY/2024.04.25
* Change: Add a memory-map label to function and variable declarations.
* Cause: Bugfix
********************************************************************************
* Version: 3.8
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
#include "E2E_PCRC16.h"

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

static FUNC(uint16, E2E_CODE) E2E_PCRC16_ComputeCrc
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 crcStartByte
);
static FUNC(uint8, E2E_CODE) E2E_PCRC16Check_ChkParam
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PCRC16CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable
);
static FUNC(uint8, E2E_CODE) E2E_PCRC16Protect_ChkParam
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PCRC16ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(void, E2E_CODE) E2E_PCRC16_WriteCounter
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC16ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint16, E2E_CODE) E2E_PCRC16_ReadCounter
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
);
static FUNC(uint16, E2E_CODE) E2E_PCRC16_CalDeltaCounter
(
    VAR(uint16, E2E_APPL_DATA) receivedCounter,
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PCRC16CheckStateType, AUTOMATIC, E2E_APPL_DATA) State
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
* Function Name: E2E_PCRC16_ComputeCrc
*
* Explanation: Calculate CRC for pofile CRC16.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        DataPtr: Pointer to Data to be transmitted.
*        crcStartByte: The location of CRC.
*
* retval: Crc Value
********************************************************************************
*/
static FUNC(uint16, E2E_CODE) E2E_PCRC16_ComputeCrc
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    uint16 crcStartByte
)
{
    uint16 lengthBf = E2E_INIT_0;
    uint16 lengthAf = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;

    if( E2E_BIGENDIANESS == ConfigPtr->CRCEndianess)
    {
        lengthAf = (ConfigPtr->DataLength / E2E_8BIT) - crcStartByte - E2E_INDEX_1;
        /* Calculation CRC, Before data and after data of CRC. */
        if( ConfigPtr->CRCOffset >= (E2E_INDEX_1 * E2E_8BIT) )
        {
            lengthBf = crcStartByte - E2E_INDEX_1;
            computedCrc = Crc_CalculateCRC16(DataPtr, lengthBf, E2E_FULL_2BYTE, TRUE);
            computedCrc = Crc_CalculateCRC16(&DataPtr[crcStartByte + E2E_INDEX_1],
                                             lengthAf, computedCrc, FALSE);
        }
        else /* Calculation CRC, after data of CRC. */
        {
            computedCrc = Crc_CalculateCRC16(&DataPtr[crcStartByte + E2E_INDEX_1],
                                             lengthAf, E2E_FULL_2BYTE, TRUE);
        }
    }
    else
    {
        lengthAf = (ConfigPtr->DataLength / E2E_8BIT) - crcStartByte - E2E_INDEX_2;
        if( ConfigPtr->CRCOffset > (E2E_INDEX_1 * E2E_8BIT) )
        {
            lengthBf = crcStartByte;
            computedCrc = Crc_CalculateCRC16(DataPtr, lengthBf, E2E_FULL_2BYTE, TRUE);
            computedCrc = Crc_CalculateCRC16(&DataPtr[crcStartByte + E2E_INDEX_2],
                                             lengthAf, computedCrc, FALSE);
        }
        else /* Calculation CRC, after data of CRC. */
        {
            computedCrc = Crc_CalculateCRC16(&DataPtr[crcStartByte + E2E_INDEX_2],
                                             lengthAf, E2E_FULL_2BYTE, TRUE);
        }
    }
    return computedCrc;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16Check_ChkParam
*
* Explanation: Check parameter of E2E_PCRC16Check.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*        NewDataAvailable: New data available.
*
* retval: CrcValu
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PCRC16Check_ChkParam
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PCRC16CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) NewDataAvailable
)
{
    uint8 rtrnValu;

    /* At least one pointer parameter is a NULL pointer. */
    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {

        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else if( ((ConfigPtr->CounterSize == E2E_PCRC16_COUNTERSIZE_4) &&
               (E2E_PCRC16PROTECT_COUNTERMAX_4 < StatePtr->Counter)) ||
             ((ConfigPtr->CounterSize == E2E_PCRC16_COUNTERSIZE_8) &&
              (E2E_PCRC16PROTECT_COUNTERMAX_8 < StatePtr->Counter)) )
    {
        rtrnValu = E2E_E_INPUTERR_WRONG;
    }
    else
    {
        *NewDataAvailable = TRUE;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16Protect_ChkParam
*
* Explanation: Check parameter of E2E_PCRC16Protect.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Crc Value
********************************************************************************
*/
static FUNC(uint8, E2E_CODE) E2E_PCRC16Protect_ChkParam
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(E2E_PCRC16ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint8 rtrnValu;

    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) )
    {
        /* At least one pointer parameter is a NULL pointer. */
        rtrnValu = E2E_E_INPUTERR_NULL;
    }
    else
    {
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16_WriteCounter
*
* Explanation: Write Counter for profile CRC16.(Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         StatePtr: Pointer to data communication state.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: void
********************************************************************************
*/
static FUNC(void, E2E_CODE) E2E_PCRC16_WriteCounter
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC16ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint16 cntrStartByte = ConfigPtr->CounterOffset / E2E_8BIT;;

    /* CounterSize is 16 bits. */
    if( E2E_PCRC16_COUNTERSIZE_16 == ConfigPtr->CounterSize )
    {
        /* Counter is stored in big endian. */
        if( E2E_BIGENDIANESS == ConfigPtr->CounterEndianess )
        {
            /* Compute the byte where the Counter is Located in. */
            DataPtr[cntrStartByte] = (uint8)StatePtr->Counter;
            DataPtr[cntrStartByte - E2E_INDEX_1] = (uint8)(StatePtr->Counter >> E2E_8BIT);
        }
        else
        {
            /* Compute the byte where the Counter is Located in. */
            cntrStartByte = ConfigPtr->CounterOffset / E2E_8BIT;
            DataPtr[cntrStartByte] = (uint8)StatePtr->Counter;
            DataPtr[cntrStartByte + E2E_INDEX_1] = (uint8)(StatePtr->Counter >> E2E_8BIT);
        }
    }
    /* CounterSize is 8 bits. */
    else if( E2E_PCRC16_COUNTERSIZE_8 == ConfigPtr->CounterSize )
    {
        DataPtr[cntrStartByte] = (uint8)StatePtr->Counter;
    }
    /* CounterSize is 4 bits. */
    else if( E2E_PCRC16_COUNTERSIZE_4 == ConfigPtr->CounterSize )
    {
        if( E2E_JUDGE_0 == (ConfigPtr->CounterOffset % E2E_8BIT) )
        {
            DataPtr[cntrStartByte]
                  = (uint8)((DataPtr[cntrStartByte] & E2E_HIGH_NIBBLE)
                           | ((uint8)StatePtr->Counter & E2E_LOW_NIBBLE));
        }
        else
        {
            DataPtr[cntrStartByte]
              = (uint8)((DataPtr[cntrStartByte] & E2E_LOW_NIBBLE)
                       | (((uint8)StatePtr->Counter << E2E_4BIT) & E2E_HIGH_NIBBLE));
        }
    }
    else
    {
        /* Do nothing. */
    }
}

/*
********************************************************************************
* Function Name: E2E_PCRC16_ReadCounter
*
* Explanation: Read Counter from received data for profile CRC8H2F.(Synchronous)
*
* param:  ConfigPtr: Pointer to static configuration.
*         DataPtr: Pointer to data to be transmitted.
*
* retval: uint16
********************************************************************************
*/
static FUNC(uint16, E2E_CODE) E2E_PCRC16_ReadCounter
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    uint16 receivedCounter = E2E_INIT_FULL1BYTE;
    uint16 cntrStartByte = ConfigPtr->CounterOffset / E2E_8BIT;;

    /* CounterSize is 16 bits. */
    if( E2E_PCRC16_COUNTERSIZE_16 == ConfigPtr->CounterSize )
    {
        /* Counter is stored in big endian. */
        /* Read Data counter. */
        if( E2E_BIGENDIANESS == ConfigPtr->CounterEndianess )
        {
            receivedCounter = ((uint16)DataPtr[cntrStartByte]) |
                              ((uint16)DataPtr[cntrStartByte - E2E_INDEX_1]
                               << E2E_8BIT );
        }
        else
        {
            receivedCounter = ((uint16)DataPtr[cntrStartByte]) |
                              ((uint16)DataPtr[cntrStartByte + E2E_INDEX_1]
                               << E2E_8BIT );
        }
    }
    /* CounterSize is 8 bits. */
    else if( E2E_PCRC16_COUNTERSIZE_8 == ConfigPtr->CounterSize )
    {
        receivedCounter = (uint16)DataPtr[cntrStartByte];
    }
    /* CounterSize is 4 bits. */
    else if( E2E_PCRC16_COUNTERSIZE_4 == ConfigPtr->CounterSize )
    {
        if( E2E_JUDGE_0 == (ConfigPtr->CounterOffset % E2E_8BIT) )
        {
            receivedCounter = (uint16)(DataPtr[cntrStartByte] & E2E_LOW_NIBBLE);
        }
        else
        {
            receivedCounter = (uint16)((DataPtr[cntrStartByte] >> E2E_4BIT)
                                       & E2E_LOW_NIBBLE);
        }
    }
    else
    {
        /* Do nothing. */
    }

    return receivedCounter;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16_CalDeltaCounter
*
* Explanation: Calculate delta Counter for profile CRC8H2F.(Synchronous)
*
* param:  receivedCounter: Counter value of this frame message.
*         Config: Pointer to static configuration.
*         State: Pointer to data communication state.
*
* retval: sint16
********************************************************************************
*/
static FUNC(uint16, E2E_CODE) E2E_PCRC16_CalDeltaCounter
(
    VAR(uint16, E2E_APPL_DATA) receivedCounter,
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) Config,
    P2VAR(E2E_PCRC16CheckStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
    uint16 deltaCounter = E2E_INIT_0;

    if( receivedCounter >= State->Counter )
    {
        deltaCounter = receivedCounter - State->Counter;
    }
    else
    {
        if( E2E_PCRC16_COUNTERSIZE_4 == Config->CounterSize )
        {
            deltaCounter = E2E_PCRC16PROTECT_COUNTERMOD_4
                           + receivedCounter - State->Counter;
        }
        else if( E2E_PCRC16_COUNTERSIZE_8 == Config->CounterSize )
        {
            deltaCounter = E2E_PCRC16PROTECT_COUNTERMOD_8
                           + receivedCounter - State->Counter;
        }
        else
        {
            deltaCounter = E2E_PCRC16PROTECT_COUNTERMOD_16
                           + receivedCounter - State->Counter;
        }
    }

    return deltaCounter;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16Protect
*
* Explanation: Protects the array/buffer to be transmitted using the E2E profile
*              CRC16.(Synchronous)
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to Data to be transmitted.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC16Protect
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC16ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint16 crcStartByte = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;

    /* Check all parameters. */
    rtrnValu = E2E_PCRC16Protect_ChkParam(ConfigPtr, StatePtr, DataPtr);
    if( E2E_E_OK == rtrnValu )
    {
        E2E_PCRC16_WriteCounter(ConfigPtr, StatePtr, DataPtr);
        /* Compute and Write CRC. */
        if( E2E_BIGENDIANESS == ConfigPtr->CRCEndianess)
        {
            /* Compute the byte where the CRC and Counter Located in. */
            crcStartByte = ConfigPtr->CRCOffset / E2E_8BIT;
            /* Compute CRC. */
            computedCrc = E2E_PCRC16_ComputeCrc(ConfigPtr, DataPtr, crcStartByte);
            DataPtr[crcStartByte] = (uint8)computedCrc & E2E_FULL_BYTE;
            DataPtr[crcStartByte - E2E_INDEX_1]
                    = (uint8)(computedCrc >> E2E_8BIT) & E2E_FULL_BYTE;
        }
        else
        {
            /* Compute the byte where the CRC and Counter Located in. */
            crcStartByte = ConfigPtr->CRCOffset / E2E_8BIT;
            /* Compute CRC. */
            computedCrc = E2E_PCRC16_ComputeCrc(ConfigPtr, DataPtr, crcStartByte);
            DataPtr[crcStartByte] = (uint8)computedCrc & E2E_FULL_BYTE;
            DataPtr[crcStartByte + E2E_INDEX_1]
                    = (uint8)(computedCrc >> E2E_8BIT) & E2E_FULL_BYTE;
        }
        /* Increment Counter,Counter beyond range. */
        if( ((ConfigPtr->CounterSize == E2E_PCRC16_COUNTERSIZE_4) &&
            (StatePtr->Counter >= E2E_PCRC16PROTECT_COUNTERMAX_4)) ||
            ((ConfigPtr->CounterSize == E2E_PCRC16_COUNTERSIZE_8) &&
            (StatePtr->Counter == E2E_PCRC16PROTECT_COUNTERMAX_8)) ||
            ((ConfigPtr->CounterSize == E2E_PCRC16_COUNTERSIZE_16) &&
            (StatePtr->Counter == E2E_PCRC16PROTECT_COUNTERMAX_16)) )
        {
            StatePtr->Counter = E2E_INIT_0;
        }
        /* Increment Counter. */
        else
        {
            StatePtr->Counter++;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16ProtectInit
*
* Explanation: Initializes the protection state for profile CRC16.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC16ProtectInit
(
    P2VAR(E2E_PCRC16ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* The parameter is valid. */
    if( NULL_PTR != StatePtr )
    {
        StatePtr->Counter = E2E_INIT_0;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16Check
*
* Explanation: Checks the Data received using the E2E profile CRC16.(Synchronous)
*
* param: ConfigPtr: Pointer to static configuration.
*        StatePtr: Pointer to port/data communication state.
*        DataPtr: Pointer to received data.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC16Check
(
    P2CONST(E2E_PCRC16ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr,
    P2VAR(E2E_PCRC16CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;
    uint8 newDataAvailable = FALSE;
    uint16 receivedCounter = E2E_INIT_FULL2BYTE;
    uint16 crcByte = E2E_INIT_0;
    uint16 receivedCrc = E2E_INIT_0;
    uint16 computedCrc = E2E_INIT_0;
    uint16 deltaCounter = E2E_INIT_0;

    /* Verify inputs of the protect function. */
    rtrnValu = E2E_PCRC16Check_ChkParam(ConfigPtr, StatePtr, DataPtr,
                                        &newDataAvailable);
    if( E2E_E_OK == rtrnValu )
    {
        /* If any new data is available to be checked. */
        if( TRUE == newDataAvailable )
        {
            /* Read counter. */
            receivedCounter = E2E_PCRC16_ReadCounter(ConfigPtr, DataPtr);
            /* Read Crc. */
            if( E2E_BIGENDIANESS == ConfigPtr->CRCEndianess )
            {
                crcByte = ConfigPtr->CRCOffset / E2E_8BIT;
                receivedCrc = ((uint16)DataPtr[crcByte]) |
                              ((uint16)DataPtr[crcByte - E2E_INDEX_1] << E2E_8BIT );
            }
            else
            {
                crcByte = ConfigPtr->CRCOffset / E2E_8BIT;
                receivedCrc = ((uint16)DataPtr[crcByte]) |
                              ((uint16)DataPtr[crcByte + E2E_INDEX_1] << E2E_8BIT );
            }
            /* Compute crc. */
            computedCrc = E2E_PCRC16_ComputeCrc(ConfigPtr, DataPtr, crcByte);
            /* Compare received crc and compute crc. */
            if( receivedCrc == computedCrc )
            {
                if( E2E_PCRC16_COUNTERSIZE_0 != ConfigPtr->CounterSize )
                {
                    /* Compute deltaCounter. */
                    deltaCounter
                      = E2E_PCRC16_CalDeltaCounter(receivedCounter, ConfigPtr, StatePtr);
                    if( deltaCounter <= ConfigPtr->MaxDeltaCounter )
                    {
                        if( deltaCounter > E2E_INIT_0 )
                        {
                            /* The checks of the Data in this cycle were successful
                               including counter check, which was incremented by 1. */
                            if( E2E_INIT_1 == deltaCounter )
                            {
                                StatePtr->Status = E2E_PCRC16STATUS_OK;
                            }
                            /* The checks of the Data in this cycle were successful,
                               ounter check which was incremented within the allowed
                               configured delta. */
                            else
                            {
                                StatePtr->Status = E2E_PCRC16STATUS_OKSOMELOST;
                            }
                        }
                        /* Repeate data. */
                        else
                        {
                            StatePtr->Status = E2E_PCRC16STATUS_REPEATED;
                        }
                    }
                    /* With the exception of counter jump, which changed more than
                       the allowed delta. */
                    else
                    {
                        StatePtr->Status = E2E_PCRC16STATUS_WRONGSEQUENCE;
                    }
                    StatePtr->Counter = receivedCounter;
                }
                else
                {
                    StatePtr->Status = E2E_PCRC16STATUS_OK;
                }
            }
            else
            {
                StatePtr->Status = E2E_PCRC16STATUS_ERROR;
            }
        }
        else
        {
            StatePtr->Status = E2E_PCRC16STATUS_NONEWDATA;
        }
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16CheckInit
*
* Explanation: Initializes the check state for profile CRC16.(Synchronous)
*
* param: StatePtr: Pointer to port/data communication state.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(Std_ReturnType, E2E_CODE) E2E_PCRC16CheckInit
(
    P2VAR(E2E_PCRC16CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr
)
{
    Std_ReturnType rtrnValu = E2E_E_INPUTERR_NULL;

    /* The parameter is valid. */
    if( NULL_PTR != StatePtr )
    {
        StatePtr->Counter = E2E_INIT_0;
        StatePtr->Status = E2E_PCRC16STATUS_ERROR;
        rtrnValu = E2E_E_OK;
    }

    return rtrnValu;
}

/*
********************************************************************************
* Function Name: E2E_PCRC16MapStatusToSM
*
* Explanation: The function maps the check status of Profile 5 to a generic
*              check status,which can be used by E2E state machine check
*              function. The E2E Profile CRC16 delivers a more fine-granular status,
*              but this is not relevant for the E2E state machine.(Synchronous)
*
* param: CheckReturn: Return value of the E2E_PCRC16Check function.
*        Status: Status determined by E2E_PCRC16Check function.
*
* retval: Std_ReturnType
********************************************************************************
*/
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_PCRC16MapStatusToSM
(
    Std_ReturnType CheckReturn,
    E2E_PCRC16CheckStatusType Status
)
{
    E2E_PCheckStatusType rtrnValu = E2E_P_ERROR;

    if( E2E_E_OK == CheckReturn )
    {
        switch( Status )
        {
            case E2E_PCRC16STATUS_OK:
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PCRC16STATUS_OKSOMELOST:
                rtrnValu = E2E_P_OK;
                break;
            case E2E_PCRC16STATUS_ERROR:
                rtrnValu = E2E_P_ERROR;
                break;
            case E2E_PCRC16STATUS_REPEATED:
                rtrnValu = E2E_P_REPEATED;
                break;
            case E2E_PCRC16STATUS_NONEWDATA:
                rtrnValu = E2E_P_NONEWDATA;
                break;
            case E2E_PCRC16STATUS_WRONGSEQUENCE:
                rtrnValu = E2E_P_WRONGSEQUENCE;
                break;
            default:
                break;
        }
    }

    return rtrnValu;
}

#define E2E_STOP_SEC_CODE
#include "E2E_MemMap.h"
