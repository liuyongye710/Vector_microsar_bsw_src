/*
********************************************************************************
*
*  File name:	CanTrcv_119_TJA1145.h
*
*  Copyright	Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date : WangCong/2020.05.29
* Change: New
* Cause: New
********************************************************************************
* Version: 3.1
* Author/Date: WangC/2020.10.24
* Change: Modify the function name according to the AUTOSAR specification, add
*         MemMap.
* Cause: Optimize.
********************************************************************************
* Version: 3.2
* Author/Date: WangC/2020.10.26
* Change: Modify the code according to QAC.
* Cause: Clear QAC warning.
********************************************************************************
* Version: 3.3
* Author/Date: ZhangDX/2020.11.04
* Change: Remove the space after the line of code.
* Cause: Update.
********************************************************************************
* Version: 3.4
* Author/Date: ZhangY/2021.10.29
* Change: Change Macro position.
* Cause: Update.
********************************************************************************
* Version: 3.5
* Author/Date : ZhangY/2021.11.1
* Change: Change CRYIF_SW_PATCH_VERSION to 1.
* Cause: Update
********************************************************************************
* Version: 3.6
* Author/Date : HuangF/2023.02.23
* Change: Include Det.h file.
* Cause: Optimize.
********************************************************************************
*/

#ifndef CANTRCV_119_TJA1145_H_
#define CANTRCV_119_TJA1145_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Spi.h"
#include "CanTrcv_Cfg.h"
#include "CanIf.h"

#if (CANTRCV_DEMEVENT_CFG == STD_ON)
#include "Dem.h"
#endif	/* CANTRCV_DEMEVENT_CFG == STD_ON */

#if (CANTRCV_ECUMWUEVENT_CFG == STD_ON)
#include "EcuM.h"
#endif	/* CANTRCV_ECUMWUEVENT_CFG == STD_ON */

#if (CANTRCV_TIMER_TYPE == CANTRCV_TIMERTYPE_16BIT1US)
#include "Tm.h"
#endif	/* CANTRCV_TIMER_TYPE == CANTRCV_TIMERTYPE_16BIT1US */

#if (CANTRCV_ICUCHN_CFG == STD_ON)
#include "Icu.h"
#endif	/* CANTRCV_ICUCHN_CFG == STD_ON */

#if (CANTRCV_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif/* CANTRCV_DEV_ERROR_DETECT == STD_ON */

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/
#define CANTRCV_119_TJA1145_VENDOR_ID         119U /* NEUSAR */
#define CANTRCV_119_TJA1145_MODULE_ID         70U
#define CANTRCV_119_TJA1145_SW_MAJOR_VERSION  3U
#define CANTRCV_119_TJA1145_SW_MINOR_VERSION  0U
#define CANTRCV_119_TJA1145_SW_PATCH_VERSION  1U

/* TJA1145 INSTANCE ID: 1 */
#define CANTRCV_119_TJA1145_INSTANCE_ID_DET 	(1U)

/* AUTOSAR Version. */
#define CANTRCV_119_TJA1145_AR_RELEASE_MAJOR_VERSION                  (4U)
#define CANTRCV_119_TJA1145_AR_RELEASE_MINOR_VERSION                  (2U)
#define CANTRCV_119_TJA1145_AR_RELEASE_REVISION_VERSION               (2U)


#define CANTRCV_119_TJA1145_MC_SLEEP      			(1U)
#define CANTRCV_119_TJA1145_MC_STANDBY    			(4U)
#define CANTRCV_119_TJA1145_MC_NORMAL     			(7U)

#define CANTRCV_119_TJA1145_BITRATE_50K   			(0U)
#define CANTRCV_119_TJA1145_BITRATE_100K  			(1U)
#define CANTRCV_119_TJA1145_BITRATE_125K  			(2U)
#define CANTRCV_119_TJA1145_BITRATE_250K  			(3U)
#define CANTRCV_119_TJA1145_BITRATE_500K  			(5U)
#define CANTRCV_119_TJA1145_BITRATE_1M    			(7U)

#define CANTRCV_119_TJA1145_BAUDRATE_50K 			(50U)
#define CANTRCV_119_TJA1145_BAUDRATE_100K 			(100U)
#define CANTRCV_119_TJA1145_BAUDRATE_125K 			(125U)
#define CANTRCV_119_TJA1145_BAUDRATE_250K 			(250U)
#define CANTRCV_119_TJA1145_BAUDRATE_500K 			(500U)
#define CANTRCV_119_TJA1145_BAUDRATE_1M   			(1000U)

#define CANTRCV_119_TJA1145_UNLOCKALL				(0U)

/* TJA1145 Register Map. */
#define CANTRCV_119_TJA1145_REGADDR_MODECTRL      	(0x01U)
#define CANTRCV_119_TJA1145_REGADDR_LOCKCTRL      	(0x0AU)

#define CANTRCV_119_TJA1145_REGADDR_CANCTRL       	(0x20U)
#define CANTRCV_119_TJA1145_REGADDR_TRCVSTA       	(0x22U)
#define CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_EN    (0x23U)

#define CANTRCV_119_TJA1145_REGADDR_DATARATE		(0x26U)
#define CANTRCV_119_TJA1145_REGADDR_ID0       		(0x27U)
#define CANTRCV_119_TJA1145_REGADDR_ID1       		(0x28U)
#define CANTRCV_119_TJA1145_REGADDR_ID2       		(0x29U)
#define CANTRCV_119_TJA1145_REGADDR_ID3       		(0x2AU)
#define CANTRCV_119_TJA1145_REGADDR_IDMASK0       	(0x2BU)
#define CANTRCV_119_TJA1145_REGADDR_IDMASK1       	(0x2CU)
#define CANTRCV_119_TJA1145_REGADDR_IDMASK2       	(0x2DU)
#define CANTRCV_119_TJA1145_REGADDR_IDMASK3       	(0x2EU)
#define CANTRCV_119_TJA1145_REGADDR_FRAMECTRL       (0x2FU)
#define CANTRCV_119_TJA1145_REGADDR_DATAMASK0       (0x68U)
#define CANTRCV_119_TJA1145_REGADDR_DATAMASK1       (0x69U)
#define CANTRCV_119_TJA1145_REGADDR_DATAMASK2       (0x6AU)
#define CANTRCV_119_TJA1145_REGADDR_DATAMASK3       (0x6BU)
#define CANTRCV_119_TJA1145_REGADDR_DATAMASK4       (0x6CU)
#define CANTRCV_119_TJA1145_REGADDR_DATAMASK5       (0x6DU)
#define CANTRCV_119_TJA1145_REGADDR_DATAMASK6       (0x6EU)
#define CANTRCV_119_TJA1145_REGADDR_DATAMASK7       (0x6FU)

#define CANTRCV_119_TJA1145_REGADDR_EVENTCAP_STA    (0x60U)
#define CANTRCV_119_TJA1145_REGADDR_SYSEVENT_STA    (0x61U)
#define CANTRCV_119_TJA1145_REGADDR_TRCVEVENT_STA   (0x63U)
#define CANTRCV_119_TJA1145_REGADDR_WPINEVENT_STA   (0x64U)

/* CFDC = 1, CAN FD tolerance enabled. CMC = 0x01. */
#define CANTRCV_119_TJA1145_REGVALUE_CANCTRL      	(0x41U)
/* Register: TRCVEVENT_STA: CW: CAN wake-up event detected */
#define CANTRCV_119_TJA1145_REGVALUE_CW      		(0x01U)
/* Register: TRCVEVENT_STA: CBS: CAN silence */
#define CANTRCV_119_TJA1145_REGVALUE_CBS      		(0x10U)
/* Register: TRCVEVENT_STA: CF: CAN bus err */
#define CANTRCV_119_TJA1145_REGVALUE_CF      		(0x02U)
/* Register: SYSEVENT_STA: PO: power-on flag */
#define CANTRCV_119_TJA1145_REGVALUE_PO      		(0x10U)
/* Register: CANCTRL: PNCOK = 0, CPNC = 0, CFDC = 1. */
#define CANTRCV_119_TJA1145_CANCTRL_STAWU			(0x40U)
/* Register: CANCTRL: PNCOK = 1, CPNC = 1, CFDC = 1. */
#define CANTRCV_119_TJA1145_CANCTRL_PNWU			(0x70U)
/* Register: TRCVEVENT_EN: CWE = 1. */
#define CANTRCV_119_TJA1145_TRCVEVENT_EN_CANWUEN	(0x01U)
/* Register: FRAMECTRL: IDE = 1. */
#define CANTRCV_119_TJA1145_FRAMECTRL_IDE			(0x80U)
/* Register: FRAMECTRL: PNDM = 1. */
#define CANTRCV_119_TJA1145_FRAMECTRL_PNDM			(0x40U)

/* Cfg defined for TJA1145 */
#define CanTrcv_119_TJA1145_ChannelInfo				CanTrcv_ChannelInfo
#define CANTRCV_119_TJA1145_CHN_ALL_NUM 			CANTRCV_CHN_ALL_NUM
#define CANTRCV_119_TJA1145_INDEX 					CANTRCV_INDEX
#define CANTRCV_119_TJA1145_DEV_ERROR_DETECT   		CANTRCV_DEV_ERROR_DETECT
#define CANTRCV_119_TJA1145_GETVERSIONINFO_API    	CANTRCV_GETVERSIONINFO_API
#define CANTRCV_119_TJA1145_MAINFUNC_DIAG_PERIOD    CANTRCV_MAINFUNC_DIAG_PERIOD
#define CANTRCV_119_TJA1145_MAINFUNC_PERIOD    		CANTRCV_MAINFUNC_PERIOD
#define CANTRCV_119_TJA1145_TIMER_TYPE				CANTRCV_TIMER_TYPE
#define CANTRCV_119_TJA1145_WAIT_TIME	 			CANTRCV_WAIT_TIME
#define CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE		CANTRCV_HWPNSUPPORT_ENABLE
#define CANTRCV_119_TJA1145_SPICOMM_RETRIES			CANTRCV_SPICOMM_RETRIES
#define CANTRCV_119_TJA1145_SPICOMM_TIMEOUT			CANTRCV_SPICOMM_TIMEOUT
#define CANTRCV_119_TJA1145_ECUMWUEVENT_CFG			CANTRCV_ECUMWUEVENT_CFG
#define CANTRCV_119_TJA1145_CANBUSERRFLAG_CFG		CANTRCV_CANBUSERRFLAG_CFG
#define CANTRCV_119_TJA1145_DEMEVENT_CFG			CANTRCV_DEMEVENT_CFG
#define CANTRCV_119_TJA1145_ICUCHN_CFG				CANTRCV_ICUCHN_CFG
#define CANTRCV_119_TJA1145_WAKEUP_SUPPORT         	CANTRCV_WAKEUP_SUPPORT

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
extern FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_Init
(
	P2CONST(CanTrcv_ConfigType, AUTOMATIC, CANTRCV_APPL_CONST) ConfigPtr
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_SetOpMode
(
	uint8 Transceiver,
	CanTrcv_TrcvModeType OpMode
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_GetOpMode
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_APPL_DATA) OpMode
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_GetBusWuReason
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_APPL_DATA) reason
);
extern FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_GetVersionInfo
(
	P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_APPL_DATA) versioninfo
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_SetWakeupMode
(
	uint8 Transceiver,
	CanTrcv_TrcvWakeupModeType TrcvWakeupMode
);

#if (CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE == STD_ON)
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_GetTrcvSystemData
(
	uint8 Transceiver,
	P2CONST(uint32, AUTOMATIC, CANTRCV_APPL_CONST) TrcvSysData
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ClearTrcvWufFlag
(
	uint8 Transceiver
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ReadTrcvTimeoutFlag
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ClearTrcvTimeoutFlag
(
	uint8 Transceiver
);
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_ReadTrcvSilenceFlag
(
	uint8 Transceiver,
	P2VAR(CanTrcv_TrcvFlagStateType, AUTOMATIC, CANTRCV_APPL_DATA) FlagState
);
#endif	/* CANTRCV_119_TJA1145_HWPNSUPPORT_ENABLE == STD_ON */

#if (CANTRCV_119_TJA1145_ECUMWUEVENT_CFG == STD_ON)
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_CheckWakeup
(
	uint8 Transceiver
);
#endif	/* CANTRCV_119_TJA1145_ECUMWUEVENT_CFG == STD_ON */

extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_SetPNActivationState
(
	CanTrcv_PNActivationType ActivationState
);

#if (CANTRCV_119_TJA1145_ECUMWUEVENT_CFG == STD_ON)
extern FUNC(Std_ReturnType, CANTRCV_CODE) CanTrcv_119_TJA1145_CheckWakeFlag
(
	uint8 Transceiver
);
#endif	/* CANTRCV_119_TJA1145_ECUMWUEVENT_CFG == STD_ON */

extern FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_MainFunction
(
	void
);
extern FUNC(void, CANTRCV_CODE) CanTrcv_119_TJA1145_MainFunctionDiagnostics
(
	void
);

#endif /* CANTRCV_119_TJA1145_H_ */

