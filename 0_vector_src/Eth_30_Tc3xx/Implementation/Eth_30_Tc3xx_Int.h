/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx_Int.h
 *        \brief  Component private header file
 *
 *      \details  Internal global data declaration and macro defines
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx.h
 *********************************************************************************************************************/
#if !defined (ETH_30_TC3XX_INT_H)
# define ETH_30_TC3XX_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Int.h"
# include "Eth_30_Tc3xx_Types_Int.h"
# include "SchM_Eth_30_Tc3xx.h"

# if (ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON)
#  include "Dem.h"
# endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CHECK OF LT60B OFFSET DEFINES
 *********************************************************************************************************************/
# if(ETH_30_TC3XX_HDR_LEN_BYTE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_HDR_LEN_BYTE is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DST > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DST is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_SRC > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_SRC is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_TYPE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_TYPE is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DATA > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DATA is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DST > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DST is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_SRC > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_SRC is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_TYPE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_TYPE is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DATA > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DATA is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE is too high!"
# endif
# if(ETH_30_TC3XX_MIN_ETH_PAYLOAD_LEN_BYTE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_MIN_ETH_PAYLOAD_LEN_BYTE is too high!"
# endif
/**********************************************************************************************************************
 *  END OF CHECK OF LT60B OFFSET DEFINES CHECK
 *********************************************************************************************************************/
# ifndef ETH_30_TC3XX_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LOCAL_INLINE                                   LOCAL_INLINE
# endif /* ETH_30_TC3XX_LOCAL_INLINE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
# define Eth_30_Tc3xx_TransformToLocalCtrlIdx(GlobalCtrlIdx)          (uint8)((GlobalCtrlIdx) - ETH_30_TC3XX_CTRL_IDX_OFFSET) 
# define Eth_30_Tc3xx_TransformToGlobalCtrlIdx(LocalCtrlIdx)          (uint8)((LocalCtrlIdx) + ETH_30_TC3XX_CTRL_IDX_OFFSET) 
/* PRQA S 0342 2 */ /* MD_MSR_Rule20.10_0342 */
# define Eth_30_Tc3xx_EnterExclusiveArea(Area)                        SchM_Enter_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_##Area()
# define Eth_30_Tc3xx_ExitExclusiveArea(Area)                         SchM_Exit_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_##Area()

/* Diagnostic Event Manager */
# if (ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON)
#  define ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx)  \
                                                                      (Dem_ReportErrorStatus(Eth_30_Tc3xx_GetDemEAccessEventIdOfEthCtrl(CtrlIdx), DEM_EVENT_STATUS_FAILED))
# else
#  define ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx)
# endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
extern VAR(Eth_StateType, ETH_30_TC3XX_VAR_ZERO_INIT) Eth_30_Tc3xx_ModuleInitialized;
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

# define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* ETH_30_TC3XX_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Int.h
 *********************************************************************************************************************/
