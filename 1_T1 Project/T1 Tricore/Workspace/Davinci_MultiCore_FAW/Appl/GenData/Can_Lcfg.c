/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Can
 *           Program: MSR_Vector_SLP4
 *          Customer: China FAW Group Corporation
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC297TA
 *    License Scope : The usage is restricted to CBD1600956_D02
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Can_Lcfg.c
 *   Generation Time: 2020-07-28 17:14:33
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/


#define CAN_LCFG_SOURCE

/* PRQA S 0857 EOF */ /* MD_Can_0857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/* -----------------------------------------------------------------------------
    Includes
 ----------------------------------------------------------------------------- */

#include "Can_Cfg.h"

/* -----------------------------------------------------------------------------
    Hw specific
 ----------------------------------------------------------------------------- */



/**********************************************************************************************************************
  ComStackLib
**********************************************************************************************************************/
/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  Can_CanIfChannelId
**********************************************************************************************************************/
/** 
  \var    Can_CanIfChannelId
  \brief  indirection table Can to CanIf controller ID
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_CanIfChannelIdType, CAN_CONST) Can_CanIfChannelId[1] = {
  /* Index    CanIfChannelId      Comment */
  /*     0 */             0U   /* [CT_CAN00_1adbe8e8] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerConfig
**********************************************************************************************************************/
/** 
  \var    Can_ControllerConfig
  \brief  Global configuration for all controllers
  \details
  Element                         Description
  CanControllerDefaultBaudrate
  MailboxRxBasicEndIdx            the end index of the 0:n relation pointing to Can_Mailbox
  MailboxRxBasicLength            the number of relations pointing to Can_Mailbox
  MailboxRxBasicStartIdx          the start index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicEndIdx            the end index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicLength            the number of relations pointing to Can_Mailbox
  MailboxTxBasicStartIdx          the start index of the 0:n relation pointing to Can_Mailbox
  MailboxUnusedEndIdx             the end index of the 0:n relation pointing to Can_Mailbox
  MailboxUnusedLength             the number of relations pointing to Can_Mailbox
  MailboxUnusedStartIdx           the start index of the 0:n relation pointing to Can_Mailbox
  RxBasicHwStart              
  RxBasicHwStop               
  RxFullHwStart               
  RxFullHwStop                
  TxBasicHwStart              
  TxBasicHwStop               
  TxFullHwStart               
  TxFullHwStop                
  UnusedHwStart               
  UnusedHwStop                
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerConfig[1] = {
    /* Index    CanControllerDefaultBaudrate  MailboxRxBasicEndIdx                                                                                                                                               MailboxRxBasicLength                                                                                                                                               MailboxRxBasicStartIdx                                                                                                                                               MailboxTxBasicEndIdx                                                                                                                                               MailboxTxBasicLength                                                                                                                                               MailboxTxBasicStartIdx                                                                                                                                               MailboxUnusedEndIdx                                                                                                                                              MailboxUnusedLength                                                                                                                                              MailboxUnusedStartIdx                                                                                                                                              RxBasicHwStart  RxBasicHwStop  RxFullHwStart  RxFullHwStop  TxBasicHwStart  TxBasicHwStop  TxFullHwStart  TxFullHwStop  UnusedHwStart  UnusedHwStop        Comment                         Referable Keys */
  { /*     0 */                         500U,                   2U  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,                   1U  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,                     1U  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,                   1U  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,                   1U  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,                     0U  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,                  3U  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,                  1U  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,                    2U  /* UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController) */,             1U,            3U,            1U,           1U,             0U,            1U,            0U,           0U,            3U,           7U }   /* [CT_CAN00_1adbe8e8] */  /* [/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_GlobalInterruptPendingMask
**********************************************************************************************************************/
/** 
  \var    Can_GlobalInterruptPendingMask
  \brief  Mask of all interrupt objects.
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_GlobalInterruptPendingMaskType, CAN_CONST) Can_GlobalInterruptPendingMask[8] = {
  /* Index    GlobalInterruptPendingMask      Comment */
  /*     0 */               0x00000007UL,  /* [CT_CAN00_1adbe8e8, Mailbox 0-31] */
  /*     1 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 32-63] */
  /*     2 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 64-95] */
  /*     3 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 96-127] */
  /*     4 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 128-159] */
  /*     5 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 160-191] */
  /*     6 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 192-223] */
  /*     7 */               0x00000000UL   /* [CT_CAN00_1adbe8e8, Mailbox 224-255] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitBT
**********************************************************************************************************************/
/** 
  \var    Can_InitBT
  \brief  Bit timing.
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitBTType, CAN_CONST) Can_InitBT[1] = {
  /* Index    InitBT       Comment */
  /*     0 */ 0x1404U   /* [CT_CAN00_1adbe8e8 - CanControllerBaudrateConfig] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitCodeH
**********************************************************************************************************************/
/** 
  \var    Can_InitCodeH
  \brief  BasicCAN acceptance filter.
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitCodeHType, CAN_CONST) Can_InitCodeH[1] = {
  /* Index    InitCodeH      Comment */
  /*     0 */   0x0000U   /* [CT_CAN00_1adbe8e8 - CanControllerBaudrateConfig, CanFilterMask] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitCodeL
**********************************************************************************************************************/
/** 
  \var    Can_InitCodeL
  \brief  BasicCAN acceptance filter.
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitCodeLType, CAN_CONST) Can_InitCodeL[1] = {
  /* Index    InitCodeL      Comment */
  /*     0 */   0x0000U   /* [CT_CAN00_1adbe8e8 - CanControllerBaudrateConfig, CanFilterMask] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitMaskH
**********************************************************************************************************************/
/** 
  \var    Can_InitMaskH
  \brief  BasicCAN acceptance filter.
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitMaskHType, CAN_CONST) Can_InitMaskH[1] = {
  /* Index    InitMaskH      Comment */
  /*     0 */   0x2000U   /* [CT_CAN00_1adbe8e8 - CanControllerBaudrateConfig, CanFilterMask] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitMaskL
**********************************************************************************************************************/
/** 
  \var    Can_InitMaskL
  \brief  BasicCAN acceptance filter.
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitMaskLType, CAN_CONST) Can_InitMaskL[1] = {
  /* Index    InitMaskL      Comment */
  /*     0 */   0x0000U   /* [CT_CAN00_1adbe8e8 - CanControllerBaudrateConfig, CanFilterMask] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBaudrate
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBaudrate
  \brief  baudrates ('InitStruct' as index)
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitObjectBaudrateType, CAN_CONST) Can_InitObjectBaudrate[1] = {
  /* Index    InitObjectBaudrate      Comment */
  /*     0 */               500U   /* [CT_CAN00_1adbe8e8 - CanControllerBaudrateConfig] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectStartIndex
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectStartIndex
  \brief  Start index of 'InitStruct' / baudratesets (controllers as index)
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitObjectStartIndexType, CAN_CONST) Can_InitObjectStartIndex[2] = {
  /* Index    InitObjectStartIndex      Comment */
  /*     0 */                   0U,  /* [CT_CAN00_1adbe8e8] */
  /*     1 */                   1U   /* [stop index] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitPortSel
**********************************************************************************************************************/
/** 
  \var    Can_InitPortSel
  \brief  Receive input selection.
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_InitPortSelType, CAN_CONST) Can_InitPortSel[1] = {
  /* Index    InitPortSel      Comment */
  /*     0 */          1U   /* [CT_CAN00_1adbe8e8] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_IsrOsId
**********************************************************************************************************************/
/** 
  \var    Can_IsrOsId
  \brief  OS Symbolic Name Value for all controller interrupts.
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_IsrOsIdType, CAN_CONST) Can_IsrOsId[1] = {
  /* Index    IsrOsId       Comment */
  /*     0 */CanIsr_0    /* [CT_CAN00_1adbe8e8 / Node0] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_Mailbox
**********************************************************************************************************************/
/** 
  \var    Can_Mailbox
  \brief  mailbox configuration (over all controllers)
  \details
  Element                Description
  ControllerConfigIdx    the index of the 1:1 relation pointing to Can_ControllerConfig
  IDValue            
  DLC_FIFO           
  HwHandle           
  MailboxType        
  MaxDataLen         
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_MailboxType, CAN_CONST) Can_Mailbox[3] = {
    /* Index    ControllerConfigIdx                                                        IDValue  DLC_FIFO  HwHandle  MailboxType                                MaxDataLen        Comment                            Referable Keys */
  { /*     0 */                  0U  /* /ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 */, 0x0000U,       1U,       0U, CAN_TX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,         8U },  /* [CN_CAN00_d9752b68_Tx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN00_d9752b68_Tx (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8, TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController)] */
  { /*     1 */                  0U  /* /ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 */, 0x0000U,       2U,       1U, CAN_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,         8U },  /* [CN_CAN00_30c2e17c_Rx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_CAN00_30c2e17c_Rx (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8, RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController)] */
  { /*     2 */                  0U  /* /ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 */, 0x0000U,       4U,       3U,  CAN_UNUSED_CAN_TYPE_MAILBOXTYPEOFMAILBOX,         0U }   /* []                     */  /* [undefined, /ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8, UNUSED_CAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_CAN00_1adbe8e8 (DefRef: /MICROSAR/Can_TricoreMultican/Can/CanConfigSet/CanController)] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_NodeAdr
**********************************************************************************************************************/
/** 
  \var    Can_NodeAdr
  \brief  Physical node address.
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_NodeAdrType, CAN_CONST) Can_NodeAdr[1] = {
  /* Index    NodeAdr           Comment */
  /*     0 */ 0xF0018200UL   /* [CT_CAN00_1adbe8e8] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_NodeNum
**********************************************************************************************************************/
/** 
  \var    Can_NodeNum
  \brief  Physical node.
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_NodeNumType, CAN_CONST) Can_NodeNum[1] = {
  /* Index    NodeNum      Comment */
  /*     0 */      0U   /* [CT_CAN00_1adbe8e8] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_PhysPrio
**********************************************************************************************************************/
/** 
  \var    Can_PhysPrio
  \brief  Interrupt priority.
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_PhysPrioType, CAN_CONST) Can_PhysPrio[4] = {
  /* Index    PhysPrio             Comment */
  /*     0 */             10U,  /* [Physical channel 0] */
  /*     1 */ CAN_NO_PHYSPRIO,  /* [dummy entry] */
  /*     2 */ CAN_NO_PHYSPRIO,  /* [dummy entry] */
  /*     3 */ CAN_NO_PHYSPRIO   /* [dummy entry] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_RxBasicInterruptPendingMask
**********************************************************************************************************************/
/** 
  \var    Can_RxBasicInterruptPendingMask
  \brief  Mask of Rx BasicCAN interrupt objects.
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_RxBasicInterruptPendingMaskType, CAN_CONST) Can_RxBasicInterruptPendingMask[8] = {
  /* Index    RxBasicInterruptPendingMask      Comment */
  /*     0 */                0x00000006UL,  /* [CT_CAN00_1adbe8e8, Mailbox 0-31] */
  /*     1 */                0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 32-63] */
  /*     2 */                0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 64-95] */
  /*     3 */                0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 96-127] */
  /*     4 */                0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 128-159] */
  /*     5 */                0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 160-191] */
  /*     6 */                0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 192-223] */
  /*     7 */                0x00000000UL   /* [CT_CAN00_1adbe8e8, Mailbox 224-255] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_RxFullInterruptPendingMask
**********************************************************************************************************************/
/** 
  \var    Can_RxFullInterruptPendingMask
  \brief  Mask of Rx FullCAN interrupt objects.
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_RxFullInterruptPendingMaskType, CAN_CONST) Can_RxFullInterruptPendingMask[8] = {
  /* Index    RxFullInterruptPendingMask      Comment */
  /*     0 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 0-31] */
  /*     1 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 32-63] */
  /*     2 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 64-95] */
  /*     3 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 96-127] */
  /*     4 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 128-159] */
  /*     5 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 160-191] */
  /*     6 */               0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 192-223] */
  /*     7 */               0x00000000UL   /* [CT_CAN00_1adbe8e8, Mailbox 224-255] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_SrcNum
**********************************************************************************************************************/
/** 
  \var    Can_SrcNum
  \brief  Interrupt source register.
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_SrcNumType, CAN_CONST) Can_SrcNum[1] = {
  /* Index    SrcNum      Comment */
  /*     0 */     0U   /* [CT_CAN00_1adbe8e8] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_TxInterruptPendingMask
**********************************************************************************************************************/
/** 
  \var    Can_TxInterruptPendingMask
  \brief  Mask of Tx interrupt objects.
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_TxInterruptPendingMaskType, CAN_CONST) Can_TxInterruptPendingMask[8] = {
  /* Index    TxInterruptPendingMask      Comment */
  /*     0 */           0x00000001UL,  /* [CT_CAN00_1adbe8e8, Mailbox 0-31] */
  /*     1 */           0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 32-63] */
  /*     2 */           0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 64-95] */
  /*     3 */           0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 96-127] */
  /*     4 */           0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 128-159] */
  /*     5 */           0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 160-191] */
  /*     6 */           0x00000000UL,  /* [CT_CAN00_1adbe8e8, Mailbox 192-223] */
  /*     7 */           0x00000000UL   /* [CT_CAN00_1adbe8e8, Mailbox 224-255] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_TxOffsetHwToLog
**********************************************************************************************************************/
/** 
  \var    Can_TxOffsetHwToLog
  \brief  tx hardware to logical handle indirection table
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Can_TxOffsetHwToLogType, CAN_CONST) Can_TxOffsetHwToLog[1] = {
  /* Index    TxOffsetHwToLog      Comment */
  /*     0 */               0   /* [CT_CAN00_1adbe8e8] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_ActiveSendObject
**********************************************************************************************************************/
/** 
  \var    Can_ActiveSendObject
  \brief  temporary data for TX object
  \details
  Element    Description
  Pdu        buffered PduId for confirmation or cancellation
  State      send state like cancelled or send activ
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Can_ActiveSendObjectType, CAN_VAR_NOINIT) Can_ActiveSendObject[2];
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerData
**********************************************************************************************************************/
/** 
  \var    Can_ControllerData
  \brief  struct for all controller related variable data
  \details
  Element                  Description
  BusOffNotified           Controls BusOff notifications.
  CanInterruptCounter      CAN interrupt disable counter for each controller
  Halt                     Reflects halt status of the controller.
  IsBusOff                 CAN state for each controller: busoff occur
  IsHardwareCanceled       hw loop timeout occur for controller
  LastInitObject           last set baudrate for reinit
  LogStatus                CAN state for each controller: UNINIT=0x00, START=0x01, STOP=0x02, INIT=0x04, INCONSISTENT=0x08, WARNING =0x10, PASSIVE=0x20, BUSOFF=0x40, SLEEP=0x80
  StatusReq                CAN state request for each controller: START=0x01, STOP=0x02, WAKEUP=0x08, SLEEP=0x80
  CanInterruptOldStatus    last CAN interrupt status for restore interrupt for each controller
  LoopTimeout              hw loop timeout for each controller
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Can_ControllerDataType, CAN_VAR_NOINIT) Can_ControllerData[1];
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Can_TmpRxMsgMailbox
**********************************************************************************************************************/
/** 
  \var    Can_TmpRxMsgMailbox
  \brief  Temporary buffer for received messages.
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(tCanTmpMsgObjStruct, CAN_VAR_NOINIT) Can_TmpRxMsgMailbox[1];
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/




