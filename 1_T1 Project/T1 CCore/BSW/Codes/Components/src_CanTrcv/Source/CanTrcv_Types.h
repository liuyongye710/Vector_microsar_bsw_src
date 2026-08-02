/*
********************************************************************************
*                                                                              
*  File name:   CanTrcv_Types.h                                                  
*                                                                              
*  Copyright    Neusoft Reach Corporation. All rights reserved.                
*                                                                              
********************************************************************************
*                                                                              
* History                                                                      
*------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : WangCong/2019.10.01
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date : WangCong/2020.05.12
* Change: Modify the code specification.
* Cause: Optimize.
********************************************************************************
* Version: 3.2
* Author/Date : WangCong/2020.06.02
* Change: Add macro definition.
* Cause: Optimize.
********************************************************************************
*/

#ifndef CANTRCV_TYPES_H_
#define CANTRCV_TYPES_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define CANTRCV_VALUE_ZERO    						(0U)
#define CANTRCV_VALUE_ONE     						(1U)
#define CANTRCV_VALUE_TWO     						(2U)
#define CANTRCV_VALUE_THREE                       	(3U)
#define CANTRCV_VALUE_FOUR                        	(4U)
#define CANTRCV_VALUE_FIVE                        	(5U)
#define CANTRCV_VALUE_SIX                         	(6U)
#define CANTRCV_VALUE_SEVEN                       	(7U)
#define CANTRCV_VALUE_EIGHT                       	(8U)
#define CANTRCV_VALUE_SIXTEEN                     	(16U)
#define CANTRCV_VALUE_TWENTY  					  	(20U)
#define CANTRCV_VALUE_TWENTYFOUR                  	(24U)

#define CANTRCV_VALUE_CLEARREG_0xFF              	(0xFFU)
#define CANTRCV_VALUE_CLEAR_0x0F              	    (0x0FU)

#define CANTRCV_VALUE_0x000007C0         (0x000007C0U)
#define CANTRCV_VALUE_0x0000003F         (0x0000003FU)
#define CANTRCV_VALUE_0x1F000000         (0x1F000000U)
#define CANTRCV_VALUE_0x00FF0000         (0x00FF0000U)
#define CANTRCV_VALUE_0x0000FF00         (0x0000FF00U)
#define CANTRCV_VALUE_0x000000FF         (0x000000FFU)

#define CANTRCV_DUMMY_STATEMENT(v) (v)=(v) 

#define CANTRCV_NO_ICUCHNCFG					(0xFFU)
#define CANTRCV_NO_ECUMWUSRCCFG					(0xFFU)
#define CANTRCV_NO_BUSERREVENTID				(0U)

/* APIs Service Id */
#define CANTRCV_SERVICEID_INIT                      0x00U
#define CANTRCV_SERVICEID_SETOPMODE                 0x01U
#define CANTRCV_SERVICEID_GETOPMODE                 0x02U
#define CANTRCV_SERVICEID_GETBUSWUREASON            0x03U
#define CANTRCV_SERVICEID_GETVERSIONINFO            0x04U
#define CANTRCV_SERVICEID_SETWAKEUPMODE             0x05U
#define CANTRCV_SERVICEID_GETTRCVSYSTEMDATA         0x09U
#define CANTRCV_SERVICEID_CLEARTRCVWUFLAG           0x0AU
#define CANTRCV_SERVICEID_READTRCVTIMEOUTFLAG       0x0BU
#define CANTRCV_SERVICEID_CLEARTIMEOUTFLAG          0x0CU
#define CANTRCV_SERVICEID_READTRCVSILENCEFLAG       0x0DU
#define CANTRCV_SERVICEID_CHECKWAKEUP               0x07U
#define CANTRCV_SERVICEID_SETPNACTIVATIONSTATE      0x0FU
#define CANTRCV_SERVICEID_CHECKWAKEUPFLAG           0x0EU
#define CANTRCV_SERVICEID_MAINFUNCTION              0x06U
#define CANTRCV_SERVICEID_MAINFUNCTIONDIAGNOSTICS   0x08U

/* Development Errors */
#define CANTRCV_E_NO_ERR                       0x00U
#define CANTRCV_E_INVALID_TRANSCEIVER          0x01U
#define CANTRCV_E_PARAM_POINTER                0x02U
#define CANTRCV_E_UNINIT                       0x11U
#define CANTRCV_E_TRCV_NOT_STANDBY             0x21U
#define CANTRCV_E_TRCV_NOT_NORMAL              0x22U
#define CANTRCV_E_PARAM_TRCV_WAKEUP_MODE       0x23U
#define CANTRCV_E_PARAM_TRCV_OPMODE            0x24U
#define CANTRCV_E_BAUDRATE_NOT_SUPPORTED       0x25U
#define CANTRCV_E_INIT_FAILED                  0x27U
#define CANTRCV_E_CLR_TRCV_WUF_NOT_CALLED      0x30U
#define CANTRCV_E_NO_TRCV_CONTROL              0x40U 

#define CANTRCV_TIMERTYPE_NONE  				(0U)
#define CANTRCV_TIMERTYPE_16BIT1US				(1U)

#define CANTRCV_WAKEUP_NOT_SUPPORTED			(0U)
#define CANTRCV_WAKEUP_BY_POLLING				(1U)
/*
********************************************************************************
*    Global Types
********************************************************************************
*/
typedef struct 
{
    VAR(uint8, TYPEDEF) ConfigType;
}CanTrcv_ConfigType;

typedef enum 
{
  PN_DISABLED = 0U, /* PN wakeup functionality in CanTrcv is enabled */
  PN_ENABLED        /* PN wakeup functionality in CanTrcv is disabled */
} CanTrcv_PNActivationType;

typedef enum 
{
  CANTRCV_FLAG_SET = 0u,    /* The flag is set in the transceiver hardware */
  CANTRCV_FLAG_CLEARED      /* The flag is cleared in the transceiver hardware */
} CanTrcv_TrcvFlagStateType;

typedef struct
{
	VAR(uint8, TYPEDEF) dioChnNum;					/* CanTrcvDioChannelAccesss Num */
	P2CONST(uint16, TYPEDEF, CANTRCV_APPL_CONST) dioChnIdPtr;			/* CanTrcvDioChannelAccesss */
} CanTrcv_DioAccessType;

typedef struct CanTrcvSpiAccessTypeTag
{    
    VAR(boolean, TYPEDEF) SpiAccessSyn;           /* CanTrcvSpiAccessSynchronous */
    VAR(uint8, TYPEDEF) SpiChannelId;             /* CanTrcvSpiSequenceName */
    VAR(uint8, TYPEDEF) SpiSequenceId;            /* CanTrcvSpiSequenceName */
} CanTrcv_SpiAccessType;

typedef struct CanTrcvPartialNetworkTypeTag
{    
    VAR(uint16, TYPEDEF) BaudRate;                /* CanTrcvBaudRate,LSB:kbps */
	VAR(boolean, TYPEDEF) busErrFlag;				/* CanTrcvBusErrFlag */
    VAR(boolean, TYPEDEF) PnCanIdIsExtended;      /* CanTrcvPnCanIdIsExtended */
    VAR(boolean, TYPEDEF) PnEnabled;              /* CanTrcvPnEnabled */
    VAR(uint32, TYPEDEF) PnFrameCanId;            /* CanTrcvPnFrameCanId */
    VAR(uint32, TYPEDEF) PnFrameCanIdMask;        /* CanTrcvPnFrameCanIdMask */
    VAR(uint8, TYPEDEF) PnFrameDlc;               /* CanTrcvPnFrameDlc */
	VAR(boolean, TYPEDEF) powerOnFlag;			/* CanTrcvPowerOnFlag */
    uint8 PnFrameDataMask[8];       /* CanTrcvPnFrameDataMaskSpec */
} CanTrcv_PartialNetworkType;

typedef struct 
{    
	VAR(CanTrcv_TrcvModeType, TYPEDEF) currMode;
	VAR(CanTrcv_TrcvModeType, TYPEDEF) reqMode;
	VAR(CanTrcv_TrcvWakeupReasonType, TYPEDEF) wuReason;
	VAR(CanTrcv_TrcvWakeupModeType, TYPEDEF) wuMode;
	VAR(CanTrcv_PNActivationType, TYPEDEF) pnAct;
	VAR(boolean, TYPEDEF) spiCommTimeoutFlag;
	VAR(boolean, TYPEDEF) busErrFlag;
	VAR(boolean, TYPEDEF) porFlag;
} CanTrcv_ChannelVarType;

typedef struct CanTrcvChannelTypeTag
{    
    VAR(uint8, TYPEDEF) ChannelId;   								/* CanTrcvChannelId */
    VAR(boolean, TYPEDEF) ChannelUsed;   							/* CanTrcvChannelUsed */
    VAR(boolean, TYPEDEF) CtrlPowSupply;  						/* CanTrcvControlsPowerSupply */
    VAR(boolean, TYPEDEF) HwPnSupport;    						/* CanTrcvHwPnSupport */
    VAR(CanTrcv_TrcvModeType, TYPEDEF) InitState; 				/* CanTrcvInitState */
	VAR(uint16, TYPEDEF) maxBaudrate;								/* CanTrcvMaxBaudrate */
	VAR(boolean	wakeupByBusUsed, TYPEDEF) ;						/* CanTrcvWakeupByBusUsed */
	VAR(uint16, TYPEDEF) icuChnId;								/* CanTrcvIcuChannelRef->IcuChannel->IcuChannelId. */
	VAR(uint8, TYPEDEF) ecumWakeupSrcId;              			/* CanTrcvWakeupSourceRef->EcuMWakeupSource->EcuMWakeupSourceId. */
	VAR(uint8, TYPEDEF) ecumPorWakeupSrcId;              			/* CanTrcvPorWakeupSourceRef->EcuMWakeupSource->EcuMWakeupSourceId. */
	VAR(uint8, TYPEDEF) ecumSyserrWakeupSrcId;              		/* CanTrcvSyserrWakeupSourceRef->EcuMWakeupSource->EcuMWakeupSourceId. */
	VAR(uint16, TYPEDEF) eventIdBusErr; 							/* CanTrcvDemEventParameterRefs->DemEventParameter->DemEventId */
    P2CONST(CanTrcv_PartialNetworkType, TYPEDEF, CANTRCV_APPL_CONST) PnNetworkPtr; /* CanTrcvPartialNetwork */
    P2CONST(CanTrcv_SpiAccessType, TYPEDEF, CANTRCV_APPL_CONST) SpiAccessPtr;      /* CanTrcvSpiAccess */
	P2CONST(CanTrcv_DioAccessType, TYPEDEF, CANTRCV_APPL_CONST) dioAccessPtr;		/* CanTrcvDioAccess */
	P2VAR(CanTrcv_ChannelVarType, TYPEDEF, CANTRCV_APPL_DATA) chnVarPtr;				/* Record information for this channel. */
} CanTrcv_ChannelType;

/*
********************************************************************************
*    Global variables
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

#endif /* CANTRCV_TYPES_H_ */

