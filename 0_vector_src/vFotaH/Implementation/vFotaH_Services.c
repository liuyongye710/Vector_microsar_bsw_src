/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*        \file  vFotaH_Services.c
 *        \brief  vFotaH source file for UDS
 *
 *      \details
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define VFOTAH_SERVICES_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vFotaH_States.h"
#include "vFotaH_Appl.h"
#include "vFotaH_Priv.h"
#include "vFotaH_Services.h"

#include "SchM_vFotaH.h"
#include "NvM.h"
#include "Rte_Type.h"
#include "vFotaH_vSwUpdM.h"


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if ((VFOTAH_SW_MAJOR_VERSION != (0x03)) || (VFOTAH_SW_MINOR_VERSION != (0x00)) || (VFOTAH_SW_PATCH_VERSION != (0x00)))
# error "Vendor specific version numbers of vFotaH.c and vFotaH.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

#define VFOTAH_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#define VFOTAH_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */


#define VFOTAH_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/* State variables for Routines: */
VFOTAH_LOCAL VAR(vFotaH_FingerprintType, VFOTAH_VAR_NOINIT)           vFotaH_Fingerprint; /* Stores the temporary fingerprint */
VFOTAH_LOCAL VAR(vFotaH_EraseRequestType, VFOTAH_VAR_NOINIT)          vFotaH_EraseRequest; /* Erase request state */
VFOTAH_LOCAL VAR(vFotaH_SwitchBankRequestType, VFOTAH_VAR_NOINIT)     vFotaH_SwitchBankRequest; /* Switch Bank request state */
VFOTAH_LOCAL VAR(vFotaH_VerifyModuleType, VFOTAH_VAR_NOINIT)          vFotaH_VerifyModuleRequest; /* verify Module request state */
VFOTAH_LOCAL VAR(vFotaH_StartRequestType, VFOTAH_VAR_NOINIT)          vFotaH_StartRequest; /* Module Start request state */
VFOTAH_LOCAL VAR(vFotaH_PrepareActivationType, VFOTAH_VAR_NOINIT)     vFotaH_PrepareActivationRequest; /* Prepare Activation state request state */
VFOTAH_LOCAL VAR(vFotaH_UpdateCommitType, VFOTAH_VAR_NOINIT)          vFotaH_UpdateCommitRequest; /* Update Commit state request */
VFOTAH_LOCAL VAR(vFotaH_DownloadMessageInfoType, VFOTAH_VAR_NOINIT)   vFotaH_DownloadMessageInfo; /* PRQA S 3218 */ /* MD_vFotaH_3218 */
VFOTAH_LOCAL VAR(vFotaH_DownloadDataType, VFOTAH_VAR_NOINIT)          vFotaH_DownloadData; /* Download data information structure */

VFOTAH_LOCAL VAR(uint16, VFOTAH_VAR_NOINIT)  vFotaH_ModuleId;
VFOTAH_LOCAL VAR(uint16, VFOTAH_VAR_NOINIT)  vFotaH_AnyDnldActiveModuleId; /* PRQA S 3218 */ /* MD_vFotaH_3218 */
VFOTAH_LOCAL VAR(boolean, VFOTAH_VAR_NOINIT) vFotaH_ModuleValid;
VFOTAH_LOCAL VAR(boolean, VFOTAH_VAR_NOINIT) vFotaH_ProgrammingPreconditionsValid;
VFOTAH_LOCAL VAR(boolean, VFOTAH_VAR_NOINIT) vFotaH_ProgrammingDependenciesValid;
VFOTAH_LOCAL VAR(boolean, VFOTAH_VAR_NOINIT) vFotaH_Hlp_GMSValidate;

VAR(vFotaH_NvMInfoBlockType, VFOTAH_VAR_NOINIT) vFotaH_NvMInfoBlock[VFOTAH_NUMBER_OF_MODULES];

#define VFOTAH_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
*  vFotaH_Hlp_MemAccByteStream2AtomicData()
*********************************************************************************************************************/
/*! \brief       transforms incoming data to individual values.
*  \details     -
*  \param[in]   pByteStream    A pointer to the byte stream.
*  \param[in]   Length         The length of the byte stream.
*  \context     TASK|ISR2
*  \reentrant   TRUE
*  \synchronous TRUE
*  \pre         -
*  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(uint32, VFOTAH_CODE) vFotaH_Hlp_MemAccByteStream2AtomicData(Dcm_MsgType const pByteStream, uint8 Length);

/**********************************************************************************************************************
*  vFotaH_Hlp_AR2DcmRetValue()
*********************************************************************************************************************/
/*! \brief       transforms AUTOSAR return values to DCM return values.
 *  \details     -
 *  \param[in]   In_RetValue      The AUTOSAR return value.
 *  \return      Std_ReturnType   The DCM return value.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_AR2DcmRetValue(Std_ReturnType In_RetValue);

/**********************************************************************************************************************
*  vFotaH_Hlp_IsStartRoutineExecutionOk()
*********************************************************************************************************************/
/*! \brief       checks whether execution of the requested routine is currently possible.
 *  \details     -
 *  \param[in]   RoutineId        The requested routine
 *  \return      E_OK             Execution possible.
 *  \return      E_NOT_OK         Execution not possible, is busy.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_IsStartRoutineExecutionOk(Dcm_OpStatusType OpStatus);

/**********************************************************************************************************************
*  vFotaH_Hlp_InitNvMInfoBlock()
*********************************************************************************************************************/
/*! \brief       provides an initialized NvMInfoBlock.
 *  \details     -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(void, VFOTAH_CODE) vFotaH_Hlp_InitNvMInfoBlock(void);


/**********************************************************************************************************************
*  vFotaH_Hlp_ReadSoftwareVersion()
*********************************************************************************************************************/
/*! \brief       Read the software version from the selected partition
 *  \details     -
 *  \return      E_OK         The operation is finished.
 *  \return      E_PENDING    The operation is in progress.
 *  \return      E_NOT_OK     The operation failed.
 *  \param[in]   OpStatus     The DCM op status.
 *  \param[in]   Partition    The selected partition to read the software version from.
 *  \param[in]   length       The length of the software version.
 *  \param[out]  Data         The software version of all modules concatenated in one string.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_ReadSoftwareVersion(
  Dcm_OpStatusType OpStatus,
  vSwUpdM_PartitionStateType Partition,
  uint16 length,
  P2VAR(uint8, AUTOMATIC, VFOTAH_APPL_VAR) Data);


/**********************************************************************************************************************
*  vFotaH_Hlp_GetModuleState()
*********************************************************************************************************************/
/*! \brief       Gets the current Module state based on vSwUpdM information.
 *  \details     -
 *  \param[out]  ModuleState  The state of the selected module.
 *  \param[in]   ModuleId     The Id of the selected module.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_GetModuleState(P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) ModuleState, uint16 ModuleId);


/**********************************************************************************************************************
*  vFotaH_Hlp_AnyModuleDnldActive()
*********************************************************************************************************************/
/*! \brief       Check whether any other module is in state VFOTAH_RESUME_MODULE_STATE_DNLD_STARTED
 *  \details     -
 *  \return      E_OK         No module is in the state.
 *  \return      VFOTAH_E_PENDING Operation in progress.
 *  \return      E_NOT_OK     Found a module in this state.
 *  \param[in]   OpStatus     The DCM Op Status.
 *  \param[in]   matchId      The id of the own module that can be in this state.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \pre         -
 *  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_AnyModuleDnldActive(Dcm_OpStatusType OpStatus, uint16 MatchId, P2VAR(uint16, AUTOMATIC, VFOTAH_APPL_VAR) ModuleId);



/**********************************************************************************************************************
*  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
* vFotaH_Hlp_AR2DcmRetValue
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_AR2DcmRetValue(Std_ReturnType In_RetValue)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retValue;

  /* ----- Implementation ---------------------------------------------------------------------- */
  switch (In_RetValue)
  {
    case E_OK: retValue = DCM_E_OK; break;
    case E_NOT_OK: retValue = DCM_E_NOT_OK; break;
    case VFOTAH_E_PENDING: retValue = DCM_E_PENDING; break;
    default: retValue = DCM_E_NOT_OK; break;
  }

  return retValue;
} /* vFotaH_Hlp_AR2DcmRetValue */


/**********************************************************************************************************************
* vFotaH_Hlp_IsStartRoutineExecutionOk
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_IsStartRoutineExecutionOk(Dcm_OpStatusType OpStatus)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retValue = E_OK;

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Check if any routine except the selected on is active. If yes, return E_NOT_OK to signal 
         that no further execution is ok. */
  if (OpStatus == DCM_INITIAL)
  {
    if ((vFotaH_EraseRequest.EraseRequest == VFOTAH_ERASE_ROUTINE_INFO_PENDING)
     || (vFotaH_SwitchBankRequest.SwitchBankRequest == VFOTAH_PERFORM_SWITCH_INFO_PENDING)
     || (vFotaH_VerifyModuleRequest.VerifyModuleRequest == VFOTAH_VERIFY_MODULE_INFO_PENDING)
     || (vFotaH_StartRequest.StartRequest == VFOTAH_MODULE_START_INFO_PENDING)
     || (vFotaH_PrepareActivationRequest.PrepareActivationRequest == VFOTAH_PREPARE_ACTIVATION_INFO_PENDING)
     || (vFotaH_UpdateCommitRequest.UpdateCommitRequest == VFOTAH_UPDATE_COMMIT_INFO_PENDING))
    {
      retValue = E_NOT_OK;
    }
  }

  return retValue;
} /* vFotaH_Hlp_IsStartRoutineExecutionOk */


/**********************************************************************************************************************
* vFotaH_Hlp_InitNvMInfoBlock
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(void, VFOTAH_CODE) vFotaH_Hlp_InitNvMInfoBlock(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least i;
  uint16_least j;

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Write all 0. */
  for (i = 0u; i < vFotaH_GetSizeOfLogicalBlockDescriptor(); i++)
  {
    vFotaH_NvMInfoBlock[i].ModuleStatus = 0x00u;
    vFotaH_NvMInfoBlock[i].SwitchBankRequest = VFOTAH_PARTITION_SWITCH_OPTION_NONE;
    for (j = 0u; j < VFOTAH_FINGERPRINT_SIZE; j++)
    {
      vFotaH_NvMInfoBlock[i].Fingerprint_Active[j] = 0u;
      vFotaH_NvMInfoBlock[i].Fingerprint_Inactive[j] = 0u;
    }
  }

  (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);
} /* vFotaH_Hlp_InitNvMInfoBlock */


/**********************************************************************************************************************
* vFotaH_Hlp_GetLogBlockId
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_GetLogBlockId(
  vSwUpdM_ModuleHandleIdType ModuleHd,
  P2VAR(uint16, AUTOMATIC, VFOTAH_APPL_VAR) LogBlockId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint16_least i;
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ---------------------------------------------------------------------- */
  for (i = 0u; i < vFotaH_GetSizeOfLogicalBlockDescriptor(); i++)
  {
    if (vFotaH_GetHandleOfLogicalBlockDescriptor(i) == ModuleHd)
    {
      LogBlockId[0u] = (uint16)i;
      break;
    }
  }

  if (i == vFotaH_GetSizeOfLogicalBlockDescriptor())
  {
    retVal = E_NOT_OK;
  }
  
  return retVal;
} /* vFotaH_Hlp_GetLogBlockId */


/**********************************************************************************************************************
* vFotaH_Hlp_GetLogBlockId
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_AnyModuleDnldActive(Dcm_OpStatusType OpStatus, uint16 MatchId, P2VAR(uint16, AUTOMATIC, VFOTAH_APPL_VAR) ModuleId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  if (OpStatus == DCM_INITIAL)
  {
    vFotaH_AnyDnldActiveModuleId = 0u;
  }

  if ((vFotaH_AnyDnldActiveModuleId != MatchId) && (vFotaH_AnyDnldActiveModuleId < vFotaH_GetSizeOfLogicalBlockDescriptor()))
  {
    uint8 moduleState;

    retVal = vFotaH_Hlp_GetModuleState(&moduleState, vFotaH_AnyDnldActiveModuleId);
    if (retVal == E_OK)
    {
      if (moduleState == VFOTAH_RESUME_MODULE_STATE_DNLD_STARTED)
      {
        ModuleId[0] = vFotaH_AnyDnldActiveModuleId;
        retVal = E_NOT_OK;
      }
      else
      if (vFotaH_AnyDnldActiveModuleId < vFotaH_GetSizeOfLogicalBlockDescriptor())
      {
        vFotaH_AnyDnldActiveModuleId++;
        retVal = VFOTAH_E_PENDING;
      }
      else
      {
        retVal = E_OK;
      }
    }
  }
  else
  {
    if (vFotaH_AnyDnldActiveModuleId < vFotaH_GetSizeOfLogicalBlockDescriptor())
    {
      vFotaH_AnyDnldActiveModuleId++;
      retVal = VFOTAH_E_PENDING;
    }
    else
    {
      retVal = E_OK;
    }
  }
  
  return retVal;
} /* vFotaH_Hlp_GetLogBlockId */

/**********************************************************************************************************************
* vFotaH_Hlp_MemAccByteStream2AtomicData
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(uint32, VFOTAH_CODE) vFotaH_Hlp_MemAccByteStream2AtomicData(
  Dcm_MsgType const pByteStream, /* PRQA S 3673 */ /* MD_vFotaH_3673/9 */
  uint8 Length)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint32 result = 0u;
  uint8 len;
  Dcm_MsgType ptr = pByteStream; /* PRQA S 3679 */ /* MD_vFotaH_3673/9 */

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Convert a byte stream to a numeric value, e.g. merge 4 single bytes to a 32bit value */
  for (len = Length; len != 0u; len--)
  {
    result <<= 8u;
    result |= ptr[0u];
    ptr = &ptr[1u]; /* ptr++ */
  }

  return result;
} /* vFotaH_Hlp_MemAccByteStream2AtomicData */


/**********************************************************************************************************************
* vFotaH_Hlp_ReadSoftwareVersion
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_ReadSoftwareVersion(
  Dcm_OpStatusType OpStatus,
  vSwUpdM_PartitionStateType Partition,
  uint16 length,
  P2VAR(uint8, AUTOMATIC, VFOTAH_APPL_VAR) Data)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  if (OpStatus == DCM_INITIAL)
  {
    vFotaH_ModuleId = 0u;
    vFotaH_ModuleValid = FALSE;
  }

  if (vFotaH_ModuleValid == FALSE)
  {
    vSwUpdM_ModuleInfoType moduleInfo;
    vSwUpdM_PartitionInfoType partitionInfo;

    /* #-- First get all module information */
    retVal = vFotaH_vSwUpdMGetModulePartitionInfo(&moduleInfo, &partitionInfo, vFotaH_GetHandleOfLogicalBlockDescriptor(vFotaH_ModuleId), Partition);
    if (retVal == E_OK)
    {
      if (moduleInfo.IsValid == TRUE)
      {
        vFotaH_ModuleValid = TRUE;
        retVal = VFOTAH_E_PENDING;
      }
      else
      {
        uint16 i;
        /* #-- We can not read software version, because module is not valid. Set default version of 0 */
        Data[vFotaH_ModuleId * (length + 1u)] = (uint8)(vFotaH_GetHandleOfLogicalBlockDescriptor(vFotaH_ModuleId));
        for (i=0u; i<length; i++)
        {
          Data[(vFotaH_ModuleId * (length + 1u)) + i + 1u] = 0u;
        }

        vFotaH_ModuleId++;
        if (vFotaH_ModuleId < VFOTAH_NUMBER_OF_MODULES)
        {
          retVal = VFOTAH_E_PENDING;
        }
      }
    }
  }
  else
  {
    uint32 address;
    vSwUpdM_ModuleIdType moduleId;

    moduleId = vFotaH_GetModuleSnvOfLogicalBlockDescriptor(vFotaH_ModuleId);
    address = vFotaH_Appl_GetSoftwareVersionAddr(moduleId);
    /* #-- Read software version from module */
    retVal = vFotaH_vSwUpdMReadRange(&Data[(vFotaH_ModuleId * (length + 1u)) + 1u], address, length, Partition);
    if (retVal == E_OK)
    {
      Data[vFotaH_ModuleId * (length + 1u)] = (uint8)(vFotaH_GetHandleOfLogicalBlockDescriptor(vFotaH_ModuleId));
      vFotaH_ModuleId++;
      if (vFotaH_ModuleId < VFOTAH_NUMBER_OF_MODULES)
      {
        retVal = VFOTAH_E_PENDING;
        vFotaH_ModuleValid = FALSE;
      }
    }
  }

  return retVal;
} /* vFotaH_Hlp_ReadSoftwareVersion */


/**********************************************************************************************************************
* vFotaH_Hlp_GetModuleState
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Hlp_GetModuleState(P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) ModuleState, uint16 ModuleId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vSwUpdM_ResumeInfoType vSwUpdMResumeInfo;
  vSwUpdM_ModuleInfoType moduleInfo;
  vSwUpdM_PartitionInfoType partitionInfo;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ---------------------------------------------------------------------- */
  if(vFotaH_Hlp_GMSValidate == FALSE)
  {
    retVal = vFotaH_vSwUpdMGetModulePartitionInfo(&moduleInfo, &partitionInfo, vFotaH_GetHandleOfLogicalBlockDescriptor(ModuleId), VSWUPDM_PART_STATE_INACTIVE);
    if (retVal == E_OK)
    {
      switch (moduleInfo.State)
      {
        case VSWUPDM_MODULE_STATE_ERASED:
        {
          ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_ERASED;
        } break;

        case VSWUPDM_MODULE_STATE_RESTART:
        case VSWUPDM_MODULE_STATE_CLEAN:
        {
          ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_DNLD_STARTED;
        } break;

        case VSWUPDM_MODULE_STATE_ERASE_PENDING:
        {
          ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_ERASE_STARTED;
        } break;

        case VSWUPDM_MODULE_STATE_DIRTY:
        {
          uint32 numberOfRegions;
          uint16 i;

          ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_MODULE_INVALID;
          /* #-- Get the resume info. */
          retVal = vSwUpdM_GetResumeInfo(&vSwUpdMResumeInfo);

          if (retVal == E_OK)
          {
            /* #-- If the resume info apply to the inactive partition and the service process stream data was interrupted: */
            if (((vSwUpdMResumeInfo.PartitionState & VSWUPDM_PART_STATE_INACTIVE) == VSWUPDM_PART_STATE_INACTIVE)
              && (vSwUpdMResumeInfo.CurrentService == VSWUPDM_SID_PROCESS_STREAM_DATA))
            {
              /* #-- If there are valid resume info (for download). */
              if (vSwUpdMResumeInfo.IsAddressValid == TRUE)
              {
                retVal = vFotaH_vSwUpdMGetNumberOfRegionsOfModule(&numberOfRegions, vFotaH_GetHandleOfLogicalBlockDescriptor(ModuleId));
                if (retVal == E_OK)
                {
                  for (i = 0u; i < numberOfRegions; i++)
                  {
                    vSwUpdM_RegionInfoType regionInfo;

                    retVal = vFotaH_vSwUpdMGetRegionInfoOfId(&regionInfo, vFotaH_GetHandleOfLogicalBlockDescriptor(ModuleId), i);
                    if (retVal == E_OK)
                    {
                      if ((regionInfo.StartAddress <= vSwUpdMResumeInfo.MemoryAddress)
                        && (regionInfo.EndAddress > vSwUpdMResumeInfo.MemoryAddress))
                      {
                        ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_DNLD_STARTED;
                        break;
                      }
                    }
                  }
                }
              }
            }
          }
        } break;

        case VSWUPDM_MODULE_STATE_VERIFIED:
        {
          if (moduleInfo.IsValid == TRUE)
          {
            if (partitionInfo.IsValid == TRUE)
            {
              ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_PART_VALID;
            }
            else
            {
              ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_MODULE_VALID;
            }
          }
          else
          {
            vFotaH_Hlp_GMSValidate = TRUE;
          }
        } break;

        case VSWUPDM_MODULE_STATE_PROCESS_STARTED:
        case VSWUPDM_MODULE_STATE_PROCESS_DIRTY:
        case VSWUPDM_MODULE_STATE_PROCESS_CLEAN:
        case VSWUPDM_MODULE_STATE_PROCESS_FINISHED:
        {
          ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_PART_VALID;
        } break;

        default:
        {
          ModuleState[0] = VFOTAH_RESUME_MODULE_STATE_MODULE_INVALID;
        } break;
      }
    }
  }

  if(vFotaH_Hlp_GMSValidate == TRUE)
  {
    retVal = vFotaH_vSwUpdMValidateModule(VSWUPDM_PART_STATE_INACTIVE, vFotaH_GetHandleOfLogicalBlockDescriptor(ModuleId));
    if (retVal == E_OK)
    {
      vFotaH_Hlp_GMSValidate = FALSE;
    }
  }

  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
}


/**********************************************************************************************************************
*  GLOBAL FUNCTIONS
**********************************************************************************************************************/

/* ################################################################################################################# */
/* Services */
/* ################################################################################################################# */

/**********************************************************************************************************************
 * vFotaH_Serv_InitMemory
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_Serv_InitMemory(void)
{
} /* vFotaH_Serv_InitMemory */

/**********************************************************************************************************************
 * vFotaH_Serv_PreInit
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_Serv_PreInit(void)
{
  vFotaH_Fingerprint.FingerprintValid = FALSE;

  vFotaH_EraseRequest.EraseRequest = VFOTAH_ERASE_ROUTINE_INFO_COMPLETE;
  vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_COMPLETE;
  vFotaH_VerifyModuleRequest.VerifyModuleRequest = VFOTAH_VERIFY_MODULE_INFO_COMPLETE;
  
  vFotaH_StartRequest.StartRequest = VFOTAH_MODULE_START_INFO_COMPLETE;
  vFotaH_StartRequest.ModuleInfoValid = FALSE;
  vFotaH_StartRequest.UpdateStartValid = FALSE;

  vFotaH_PrepareActivationRequest.PrepareActivationRequest = VFOTAH_PREPARE_ACTIVATION_INFO_COMPLETE;
  vFotaH_UpdateCommitRequest.UpdateCommitRequest = VFOTAH_UPDATE_COMMIT_INFO_COMPLETE;

  vFotaH_Hlp_GMSValidate = FALSE;
  vFotaH_ModuleId = 0u;
  vFotaH_ModuleValid = FALSE;
  vFotaH_ProgrammingPreconditionsValid = FALSE;
  vFotaH_ProgrammingDependenciesValid = FALSE;

  vFotaH_Appl_Init();
} /* vFotaH_Serv_PreInit */

/**********************************************************************************************************************
 * vFotaH_Serv_Init
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Serv_Init(void) /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;
  NvM_RequestResultType result;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = NvM_GetErrorStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), &result);
  if (retVal == E_OK)
  {
    if (result == NVM_REQ_OK)
    {
      /* All ok. */
    }
    else
    if (result == NVM_REQ_PENDING)
    {
      retVal = VFOTAH_E_PENDING; /* Waiting */
    }
    else
    if ((result == NVM_REQ_NOT_OK)
     || (result == NVM_REQ_BLOCK_SKIPPED)
     || (result == NVM_REQ_CANCELED))
    {
      retVal = NvM_ReadBlock((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), &vFotaH_NvMInfoBlock[0]); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
      if (retVal != E_OK)
      {
        vFotaH_Hlp_InitNvMInfoBlock();
        retVal = E_OK;
      }
    }
    else
    {
      vFotaH_Hlp_InitNvMInfoBlock();
      retVal = E_OK;
    }
  }

  if (retVal == E_OK)
  {
    boolean activeLaterSW;

    /* #-- We check if the bank switch was successful and set the RoutineResult accordingly. */
    (void)vFotaH_vSwUpdMHasActivePartitionLaterSoftware(&activeLaterSW);
    if (vFotaH_NvMInfoBlock[0u].SwitchBankRequest == VFOTAH_PARTITION_SWITCH_OPTION_ACTIVATE)
    {
      if (activeLaterSW == FALSE)
      {
        vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_FAILED;
        vFotaH_NvMInfoBlock[0u].SwitchBankRequest = VFOTAH_PARTITION_SWITCH_OPTION_NONE;
      }
      else
      {
        vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_COMPLETE;
        vFotaH_NvMInfoBlock[0u].SwitchBankRequest = VFOTAH_PARTITION_SWITCH_OPTION_PENDING;
      }
    }
    else
    if (vFotaH_NvMInfoBlock[0u].SwitchBankRequest == VFOTAH_PARTITION_SWITCH_OPTION_REVERT)
    {
      if (activeLaterSW == TRUE)
      {
        vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_FAILED;
        vFotaH_NvMInfoBlock[0u].SwitchBankRequest = VFOTAH_PARTITION_SWITCH_OPTION_PENDING;
      }
      else
      {
        vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_COMPLETE;
        vFotaH_NvMInfoBlock[0u].SwitchBankRequest = VFOTAH_PARTITION_SWITCH_OPTION_NONE;
      }
    }
    else
    {
      /* Concluding else. */
    }
    (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);
  }

  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_Serv_Init */


/*
 * Functions declared by DCM.
 */

/**********************************************************************************************************************
* vFotaH_DcmModuleStartStart
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmModuleStartStart(
  uint8 In_RoutineOption,
  uint8 In_ModuleHd,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((Out_RoutineInfo == NULL_PTR)
    || (ErrorCode == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
  {
    ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
    /* #-- If vFotaH is completely initialized, execute the service request. Otherwise, indicate busy. */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      /* #-- If the service is still to be executed: */
      if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
      {
        if (vFotaH_Hlp_IsStartRoutineExecutionOk(OpStatus) == E_NOT_OK)
        {
          ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
        }
        else
        if ((In_RoutineOption <= VFOTAH_MODULE_START_SYNC)
         && (vFotaH_StartRequest.UpdateStartValid == TRUE))
        {
          uint16 logBlockId;

          vFotaH_ProgrammingPreconditionsValid = FALSE;
          vFotaH_ProgrammingDependenciesValid = FALSE;
          vFotaH_StartRequest.ModuleInfoValid = FALSE;

          retVal = vFotaH_Hlp_GetLogBlockId(In_ModuleHd, &logBlockId);

          /* #-- If we have found the respective block id */
          if (retVal == E_OK)
          {
            uint16 moduleId;
            retVal = vFotaH_Hlp_AnyModuleDnldActive(OpStatus, logBlockId, &moduleId);

            if (retVal == E_OK)
            {
              vSwUpdM_ModuleInfoType moduleInfo;
              vSwUpdM_PartitionInfoType partitionInfo;

              /* #-- We store the information for later use */
              vFotaH_StartRequest.StartRequest = VFOTAH_MODULE_START_INFO_PENDING;
              vFotaH_StartRequest.RoutineOp = In_RoutineOption;
              vFotaH_StartRequest.LogBlockId = logBlockId;
              vFotaH_StartRequest.ModuleHd = In_ModuleHd;

              retVal = vFotaH_vSwUpdMGetModulePartitionInfo(&moduleInfo, &partitionInfo, In_ModuleHd, VSWUPDM_PART_STATE_INACTIVE);

              if (retVal == E_OK)
              {
                if (In_RoutineOption == VFOTAH_MODULE_START_SYNC)
                {
                  /* #-- In case of sync we request an erase sequence */
                  if (moduleInfo.State != VSWUPDM_MODULE_STATE_ERASED)
                  {
                    vFotaH_EraseRequest.EraseRequest = VFOTAH_ERASE_ROUTINE_INFO_PENDING;
                  }
                }

                vFotaH_StartRequest.ModuleInfoValid = TRUE;
                Out_RoutineInfo[0] = VFOTAH_MODULE_START_INFO_PENDING;
              }
            }
            else
            if (retVal == E_NOT_OK)
            {
              retVal = E_NOT_OK;
              ErrorCode[0] = DCM_E_REQUESTSEQUENCEERROR;
            }
            else
            {
              /* Intentionally left empty */
            }
          }
          else
          {
            retVal = E_NOT_OK;
            ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
          }
        }
        else
        {
          retVal = E_NOT_OK;
          ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
        }
      }
      else /* DCM_CANCEL */
      {
        retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
      }
    }
    else
    {
      retVal = E_NOT_OK;
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_MODULE_START_START, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6030 3 */ /* MD_MSR_STCYC */
  /* PRQA S 6050 2 */ /* MD_MSR_STCAL */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmModuleStartStart */

/**********************************************************************************************************************
* vFotaH_DcmModuleStartResult
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmModuleStartResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode) /* PRQA S 3673 */ /* MD_vFotaH_3673 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((Out_RoutineInfo == NULL_PTR)
    || (ErrorCode == NULL_PTR)
    || (Out_Progress == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
  {
    Out_RoutineInfo[0] = vFotaH_StartRequest.StartRequest;
    Out_Progress[0] = VFOTAH_PROGRESS_RESULT;
    retVal = DCM_E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_MODULE_START_RESULT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(ErrorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  return retVal;
} /* vFotaH_DcmModuleStartResult */



/**********************************************************************************************************************
 * vFotaH_DcmEraseStart
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmEraseStart(
  uint8 In_ALFI,
  P2CONST(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) In_ComplexAddressAndLength,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  uint16 DataLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId         = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((Out_RoutineInfo == NULL_PTR)
   || (ErrorCode == NULL_PTR)
   || (In_ComplexAddressAndLength == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
    /* #-- If vFotaH is completely initialized, execute the service request. Otherwise, indicate busy. */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      uint32 address;
      uint32 length;

      if (vFotaH_Hlp_IsStartRoutineExecutionOk(OpStatus) == E_NOT_OK)
      {
        ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
      }
      else

      if (vFotaH_StartRequest.ModuleInfoValid != TRUE)
      {
        ErrorCode[0] = DCM_E_REQUESTSEQUENCEERROR;
      }
      else

      /* #-- If we have no valid Fingerprint set, an incorrect ALFI, or an incomplete message, we reject SW update */
      if ((vFotaH_Fingerprint.FingerprintValid != TRUE) || (In_ALFI != 0x44u) || (DataLength != 8u))
      {
        ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
      }
      else

      {
        address = ((uint32)In_ComplexAddressAndLength[0] << 24u)
                | ((uint32)In_ComplexAddressAndLength[1] << 16u)
                | ((uint32)In_ComplexAddressAndLength[2] << 8u)
                | In_ComplexAddressAndLength[3];
        length = ((uint32)In_ComplexAddressAndLength[4] << 24u)
               | ((uint32)In_ComplexAddressAndLength[5] << 16u)
               | ((uint32)In_ComplexAddressAndLength[6] << 8u)
               | In_ComplexAddressAndLength[7];
        if ((address >= vFotaH_GetAddressOfLogicalBlockDescriptor(vFotaH_StartRequest.LogBlockId))
          && ((address+length) <= ((uint32)vFotaH_GetAddressOfLogicalBlockDescriptor(vFotaH_StartRequest.LogBlockId)
                                        + vFotaH_GetLengthOfLogicalBlockDescriptor(vFotaH_StartRequest.LogBlockId))))
        {
          /* Request erase routine and mark module as non comitted. */
          vFotaH_EraseRequest.EraseRequest = VFOTAH_ERASE_ROUTINE_INFO_PENDING;
          vFotaH_NvMInfoBlock[0u].ModuleStatus &= (~VFOTAH_MODULE_STATUS_COMMIT);
          (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);

          Out_RoutineInfo[0] = VFOTAH_ERASE_ROUTINE_INFO_PENDING;
          retVal = DCM_E_OK;
        }
        else
        {
          ErrorCode[0] = DCM_E_REQUESTOUTOFRANGE;
        }
      }
    }
    else
    {
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_ERASE_START, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  return retVal;
  /* PRQA S 6060 2 */ /* MD_MSR_STPAR */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmEraseStart */


/**********************************************************************************************************************
 * vFotaH_DcmEraseResult
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmEraseResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode) /* PRQA S 3673 */ /* MD_vFotaH_3673 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId         = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((Out_RoutineInfo == NULL_PTR)
   || (ErrorCode == NULL_PTR)
   || (Out_Progress == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    Out_RoutineInfo[0] = vFotaH_EraseRequest.EraseRequest;
    Out_Progress[0] = VFOTAH_PROGRESS_RESULT;
    retVal = DCM_E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_ERASE_RESULT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(ErrorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  return retVal;
} /* vFotaH_DcmEraseResult */


/**********************************************************************************************************************
 * vFotaH_DcmPerformPartitionSwitchStart
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmPerformPartitionSwitchStart(
  uint8 In_SwitchOption,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId         = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
   || (Out_RoutineInfo == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Otherwise: */
  {
    ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
    /* #-- If the initialization of vFotaH is already completed: */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      /* #-- If the service is still to be executed: */
      if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
      {
        if (vFotaH_Hlp_IsStartRoutineExecutionOk(OpStatus) == E_NOT_OK)
        {
          ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
        }
        else
        {
          uint8 moduleState;
          
          retVal = vFotaH_Hlp_GetModuleState(&moduleState, vFotaH_StartRequest.LogBlockId);

         /* #-- If the request is valid for switch/rollback and the requested partition is the active or inactive
         *     partition:
         *       Start the service execution and indicate success.
         *     Otherwise, report NRC DCM_E_CONDITIONSNOTCORRECT. */
          if (retVal == E_OK)
          {
            if (moduleState == VFOTAH_RESUME_MODULE_STATE_PART_VALID)
            {
              if (In_SwitchOption == VFOTAH_PARTITION_SWITCH_OPTION_ACTIVATE)
              {
                if ((vFotaH_ProgrammingPreconditionsValid == TRUE) && (vFotaH_ProgrammingDependenciesValid == TRUE))
                {
                  vFotaH_ProgrammingPreconditionsValid = FALSE;
                  vFotaH_ProgrammingDependenciesValid = FALSE;
                  vFotaH_SwitchBankRequest.SwitchOption = In_SwitchOption;
                  vFotaH_NvMInfoBlock[0u].SwitchBankRequest = In_SwitchOption;
                  (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);
                  vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_PENDING;
                  vFotaH_SwitchBankRequest.ResetPending = FALSE;
                  Out_RoutineInfo[0] = VFOTAH_PERFORM_SWITCH_INFO_PENDING;
                }
                else
                {
                  ErrorCode[0] = DCM_E_REQUESTSEQUENCEERROR;
                  retVal = E_NOT_OK;
                }
              }
              else
              if (In_SwitchOption == VFOTAH_PARTITION_SWITCH_OPTION_REVERT)
              {
                /* #-- In case module is already committed, we prevent a rollback. */
                if ((vFotaH_NvMInfoBlock[0u].ModuleStatus & VFOTAH_MODULE_STATUS_COMMIT) == VFOTAH_MODULE_STATUS_COMMIT)
                {
                  ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
                  retVal = E_NOT_OK;
                }
                else
                if (vFotaH_ProgrammingPreconditionsValid == TRUE)
                {
                  /* #-- Otherwise we prepare rollback if conditions are correct. */
                  vFotaH_ProgrammingPreconditionsValid = FALSE;
                  vFotaH_SwitchBankRequest.SwitchOption = In_SwitchOption;
                  vFotaH_NvMInfoBlock[0u].SwitchBankRequest = In_SwitchOption;
                  (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);
                  vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_PENDING;
                  vFotaH_SwitchBankRequest.ResetPending = FALSE;
                  Out_RoutineInfo[0] = VFOTAH_PERFORM_SWITCH_INFO_PENDING;
                }
                else
                {
                  ErrorCode[0] = DCM_E_REQUESTSEQUENCEERROR;
                  retVal = E_NOT_OK;
                }
              }
              else
              {
                ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
                retVal = E_NOT_OK;
              }
            }
            else
            {
              ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
              retVal = E_NOT_OK;
            }
          }
          else
          if (retVal == E_NOT_OK)
          {
            ErrorCode[0] = DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION;
          }
          else
          {
            /* Concluding else */
          }
        }
      }
      else /* DCM_CANCEL */
      {
        retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
      }
    }
    /* #-- Otherwise init pending, report NRC DCM_E_BUSYREPEATREQUEST. */
    else
    {
      /* Reject the request when received from tester (not FOTA-GW). */
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_SWITCH_BANK_START, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmPerformPartitionSwitchStart */


/**********************************************************************************************************************
 * vFotaH_DcmPerformPartitionSwitchResult
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmPerformPartitionSwitchResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
   || (Out_RoutineInfo == NULL_PTR)
   || (Out_Progress == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Otherwise: */
  {
    /* #-- If the initialization of the vFotaH is already completed:
     *       Indicate success and if the switch bank request is already done or still pending.
     *     Otherwise, report NRC DCM_E_BUSYREPEATREQUEST. */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      Out_Progress[0] = VFOTAH_PROGRESS_RESULT;
      Out_RoutineInfo[0] = vFotaH_SwitchBankRequest.SwitchBankRequest;
      retVal = DCM_E_OK;
    }
    else
    {
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_SWITCH_BANK_RESULT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmPerformPartitionSwitchResult */


/**********************************************************************************************************************
* vFotaH_DcmPrepareActivationStart
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmPrepareActivationStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    /* #-- If the initialization of vFotaH is already completed: */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      if (vFotaH_Hlp_IsStartRoutineExecutionOk(OpStatus) == E_NOT_OK)
      {
        ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
      }
      else
      {
        /* #-- Then request PrepareActivation operation which is performed in the MainFunction. */
        vFotaH_PrepareActivationRequest.PrepareActivationRequest = VFOTAH_PREPARE_ACTIVATION_INFO_PENDING;
        Out_RoutineInfo[0] = VFOTAH_PREPARE_ACTIVATION_INFO_PENDING;
        retVal = DCM_E_OK;
      }
    }
    /* #-- Otherwise, report NRC DCM_E_CONDITIONSNOTCORRECT. */
    else
    {
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_PREPARE_ACTIVATION_START, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmPrepareActivationStart */



/**********************************************************************************************************************
* vFotaH_DcmPrepareActivationResult
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmPrepareActivationResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode) /* PRQA S 3673 */ /* MD_vFotaH_3673 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR)
    || (Out_Progress == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    Out_RoutineInfo[0] = vFotaH_PrepareActivationRequest.PrepareActivationRequest;
    Out_Progress[0] = VFOTAH_PROGRESS_RESULT;
    retVal = DCM_E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_PREPARE_ACTIVATION_RESULT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(ErrorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmPrepareActivationResult */



/**********************************************************************************************************************
* vFotaH_DcmVerifyModuleStart
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmVerifyModuleStart(
  uint8 In_ModuleHd,
  uint8 In_VerifyOption,
  P2CONST(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) In_ComplexData,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  uint16 DataLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (In_ComplexData == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
    /* #-- If the initialization of vFotaH is already completed: */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      /* #-- If the service is still to be executed: */
      if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
      {
        if (vFotaH_Hlp_IsStartRoutineExecutionOk(OpStatus) == E_NOT_OK)
        {
          ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
        }
        else
        if (vFotaH_StartRequest.ModuleInfoValid != TRUE)
        {
          ErrorCode[0] = DCM_E_REQUESTSEQUENCEERROR;
        }
        else
        if (In_ModuleHd != vFotaH_StartRequest.ModuleHd)
        {
          ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
        }
        else

        {
          uint8 moduleState;
          retVal = vFotaH_Hlp_GetModuleState(&moduleState, vFotaH_StartRequest.LogBlockId);

          if (retVal == E_OK)
          {
            if (moduleState != VFOTAH_RESUME_MODULE_STATE_DNLD_STARTED)
            {
              ErrorCode[0] = DCM_E_REQUESTSEQUENCEERROR;
              retVal = E_NOT_OK;
            }

            else
            /* #-- If the request is valid for CRC
            *       Start the service execution and indicate success.
            *     Otherwise, report NRC DCM_E_CONDITIONSNOTCORRECT. */
            if (In_VerifyOption == VFOTAH_VERIFY_OPTION_CRC)
            {
              vFotaH_VerifyModuleRequest.VerifyOption = In_VerifyOption;
              if (DataLength == 4u)
              {
                /* Store the CRC in little endian format */
                vFotaH_VerifyModuleRequest.VerifyData[0] = In_ComplexData[3u];
                vFotaH_VerifyModuleRequest.VerifyData[1] = In_ComplexData[2u];
                vFotaH_VerifyModuleRequest.VerifyData[2] = In_ComplexData[1u];
                vFotaH_VerifyModuleRequest.VerifyData[3] = In_ComplexData[0u];
            
                vFotaH_VerifyModuleRequest.SizeofVerifyData = DataLength;
                vFotaH_VerifyModuleRequest.VerifyModuleRequest = VFOTAH_VERIFY_MODULE_INFO_PENDING;
                Out_RoutineInfo[0] = VFOTAH_VERIFY_MODULE_INFO_PENDING;
              }
              else
              {
                ErrorCode[0] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                retVal = E_NOT_OK;
              }
            }

            else
            if (In_VerifyOption == VFOTAH_VERIFY_OPTION_SIGNATURE)
            {
              vFotaH_VerifyModuleRequest.VerifyOption = In_VerifyOption;
              if (DataLength == VFOTAH_SIZE_OF_SIGNATURE)
              {
                uint16_least i;

                for (i = 0u; i < VFOTAH_SIZE_OF_SIGNATURE; i++)
                {
                  /* Store the Signature */
                  vFotaH_VerifyModuleRequest.VerifyData[i] = In_ComplexData[i];
                }
    
                vFotaH_VerifyModuleRequest.SizeofVerifyData = DataLength;
                vFotaH_VerifyModuleRequest.VerifyModuleRequest = VFOTAH_VERIFY_MODULE_INFO_PENDING;
                Out_RoutineInfo[0] = VFOTAH_VERIFY_MODULE_INFO_PENDING;
              }
              else
              {
                ErrorCode[0] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                retVal = E_NOT_OK;
              }
            }
            else
            {
              ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
              retVal = E_NOT_OK;
            }
          }
        }
      }
      /* #-- Otherwise, report that the service was aborted and indicate success. */
      else
      {
        retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
      }
    }
    /* #-- Otherwise, report NRC DCM_E_CONDITIONSNOTCORRECT. */
    else
    {
      /* Reject the request when received from tester (not FOTA-GW). */
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_VERIFY_MODULE_START, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6080 3 */ /* MD_MSR_STMIF */
  /* PRQA S 6060 2 */ /* MD_MSR_STPAR */
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vFotaH_DcmVerifyModuleStart */


/**********************************************************************************************************************
* vFotaH_DcmVerifyModuleResult
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmVerifyModuleResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode) /* PRQA S 3673 */ /* MD_vFotaH_3673 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR)
    || (Out_Progress == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    Out_RoutineInfo[0] = vFotaH_VerifyModuleRequest.VerifyModuleRequest;
    Out_Progress[0] = VFOTAH_PROGRESS_RESULT;
    retVal = DCM_E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_VERIFY_MODULE_RESULT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(ErrorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmVerifyModuleResult */



/**********************************************************************************************************************
* vFotaH_DcmUpdateCommitStart
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmUpdateCommitStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Otherwise: */
  {
    /* #-- If the initialization of vFotaH is already completed: */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      if (vFotaH_Hlp_IsStartRoutineExecutionOk(OpStatus) == E_NOT_OK)
      {
        ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
      }
      else
      {
        vFotaH_UpdateCommitRequest.UpdateCommitRequest = VFOTAH_UPDATE_COMMIT_INFO_PENDING;

        vFotaH_NvMInfoBlock[0u].ModuleStatus |= VFOTAH_MODULE_STATUS_COMMIT;
        /* Prevent further rollback by API */
        if (vFotaH_NvMInfoBlock[0u].SwitchBankRequest == VFOTAH_PARTITION_SWITCH_OPTION_PENDING)
        {
          vFotaH_NvMInfoBlock[0u].SwitchBankRequest = VFOTAH_PARTITION_SWITCH_OPTION_NONE;
        }
        (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);

        Out_RoutineInfo[0] = VFOTAH_UPDATE_COMMIT_INFO_PENDING;
        retVal = DCM_E_OK;
      }
    }
    /* #-- Otherwise, report NRC DCM_E_CONDITIONSNOTCORRECT. */
    else
    {
      /* Reject the request when received from tester (not FOTA-GW). */
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_UPDATE_COMMIT_START, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmUpdateCommitStart */


/**********************************************************************************************************************
* vFotaH_DcmUpdateCommitResult
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmUpdateCommitResult(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_Progress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode) /* PRQA S 3673 */ /* MD_vFotaH_3673 */
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR)
    || (Out_Progress == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    Out_RoutineInfo[0] = vFotaH_UpdateCommitRequest.UpdateCommitRequest;
    Out_Progress[0] = VFOTAH_PROGRESS_RESULT;
    retVal = DCM_E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_UPDATE_COMMIT_RESULT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(ErrorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmUpdateCommitResult */


/**********************************************************************************************************************
* vFotaH_DcmUpdateStart
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmUpdateStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    /* #-- If the initialization of vFotaH is already completed, report state. */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      retVal = vFotaH_Appl_CheckUpdateStart();
      if (retVal == E_OK)
      {
        Out_RoutineInfo[0] = VFOTAH_CHECK_UPDATE_START_INFO_COMPLETE;
        vFotaH_StartRequest.UpdateStartValid = TRUE;
      }
      else
      {
        Out_RoutineInfo[0] = VFOTAH_CHECK_UPDATE_START_INFO_FAILED;
        vFotaH_StartRequest.UpdateStartValid = FALSE;
      }
      retVal = DCM_E_OK;
    }
    /* #-- Otherwise, report NRC DCM_E_BUSYREPEATREQUEST. */
    else
    {
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_UPDATE_START, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmUpdateStart */



/**********************************************************************************************************************
* vFotaH_DcmCheckProgrammingPreconditions
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmCheckProgrammingPreconditions(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    /* #-- If the initialization of vFotaH is already completed: */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      retVal = vFotaH_Appl_CheckProgrammingPreconditions();
      if (retVal == E_OK)
      {
        vFotaH_ProgrammingPreconditionsValid = TRUE;
        Out_RoutineInfo[0] = VFOTAH_CHECK_PROGRAMMING_PRECONDITIONS_INFO_COMPLETE;
        retVal = DCM_E_OK;
      }
      else
      if (retVal == E_NOT_OK)
      {
        Out_RoutineInfo[0] = VFOTAH_CHECK_PROGRAMMING_PRECONDITIONS_INFO_FAILED;
        retVal = DCM_E_OK;
      }
      else
      {
        /* Concluding else */
      }
    }
    /* #-- Otherwise, report NRC DCM_E_CONDITIONSNOTCORRECT. */
    else
    {
      /* Reject the request when received from tester (not FOTA-GW). */
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_CHCK_PROG_PRECONDITIONS, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */

  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmCheckProgrammingPreconditions */


/**********************************************************************************************************************
* vFotaH_DcmCheckProgrammingDependencies
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmCheckProgrammingDependencies(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Out_RoutineInfo,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((ErrorCode == NULL_PTR)
    || (Out_RoutineInfo == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
    /* #-- If the initialization of vFotaH is already completed: */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      /* #-- If the service is still to be executed: */
      if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
      {
        if (OpStatus == DCM_INITIAL)
        {
          vFotaH_ModuleId = 0u;
        }

        /* #-- First check all Modules for validity */
        if (vFotaH_ModuleId < vFotaH_GetSizeOfLogicalBlockDescriptor())
        {
          uint8 moduleState;

          retVal = vFotaH_Hlp_GetModuleState(&moduleState, vFotaH_ModuleId);

          if (retVal == E_OK)
          {
            if ((moduleState == VFOTAH_RESUME_MODULE_STATE_MODULE_VALID)
             || (moduleState == VFOTAH_RESUME_MODULE_STATE_PART_VALID))
            {
              if (vFotaH_ModuleId < vFotaH_GetSizeOfLogicalBlockDescriptor())
              {
                vFotaH_ModuleId++;
                retVal = VFOTAH_E_PENDING;
              }
            }
            else
            {
              ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
              retVal = E_NOT_OK;
            }
          }
          else
          if (retVal == E_NOT_OK)
          {
            ErrorCode[0] = DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION;
          }
          else
          {
            /* Concluding else for VFOTAH_E_PENDING */
          }
        }
        else
        {
          retVal = E_OK;
        }

        if (retVal == E_OK)
        {
          /* #-- Request the dependency status and set the Partition state to valid if ok */
          retVal = vFotaH_Appl_CheckProgrammingDependencies();
          if (retVal == VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_SUCCESS)
          {
            vFotaH_ProgrammingDependenciesValid = TRUE;
            retVal = vFotaH_vSwUpdMValidatePartition(VSWUPDM_PART_STATE_INACTIVE);
            if (retVal == E_OK)
            {
              Out_RoutineInfo[0] = VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_SUCCESS;
            }
            else
            if (retVal == E_NOT_OK)
            {
              Out_RoutineInfo[0] = VFOTAH_CHECK_PROGRAMMING_DEPENDENCIES_GENERAL_FAILURE;
              retVal = E_OK;
            }
            else
            {
              /* Concluding else for VFOTAH_E_PENDING */
            }
          }
          else
          {
            Out_RoutineInfo[0] = retVal;
            retVal = E_OK;
          }
        }
      }
      /* #-- Otherwise, report that the service was aborted and indicate success. */
      else
      {
        retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
      }
    }
    /* #-- Otherwise, report NRC DCM_E_CONDITIONSNOTCORRECT. */
    else
    {
      /* Reject the request when received from tester (not FOTA-GW). */
      ErrorCode[0] = DCM_E_BUSYREPEATREQUEST;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_CHCK_PROG_DEPENDENCIES, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6010 3 */ /* MD_MSR_STPTH */
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmCheckProgrammingDependencies */


/**********************************************************************************************************************
 * vFotaH_DcmRequestDownload
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmRequestDownload(
  Dcm_OpStatusType opStatus,                 /* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (pMsgContext == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
  if (ErrorCode == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
    /* #-- If the service is still to be executed: */
    if ((opStatus == DCM_INITIAL) || (opStatus == DCM_PENDING))
    {
      if (vFotaH_StartRequest.ModuleInfoValid != TRUE)
      {
        ErrorCode[0] = DCM_E_REQUESTSEQUENCEERROR;
      }
      else

      /* #-- If the received RequestDownload is too short for vFotaH requirements,
      *       indicate an invalid request message length and indicate that processing is terminated. */
      if (pMsgContext->reqDataLen < VFOTAH_DCM_REQ_MSG_MIN_LENGTH)
      {
        ErrorCode[0] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
      else
      {
        vFotaH_DownloadMessageInfo.MemSizeLength = (pMsgContext->reqData[1] >> 4);
        vFotaH_DownloadMessageInfo.MemAddressLength = (pMsgContext->reqData[1] & 0x0Fu);

        /* #-- If the specified memory address length or the memory size length is in invalid range,
        *       indicate that the specified request is out of range and the processing is terminated. */
        if ((vFotaH_DownloadMessageInfo.MemAddressLength < VFOTAH_DCM_REQ_MSG_MEM_ADDR_LENGTH_MIN)
          || (vFotaH_DownloadMessageInfo.MemAddressLength > VFOTAH_DCM_REQ_MSG_MEM_ADDR_LENGTH_MAX)
          || (vFotaH_DownloadMessageInfo.MemSizeLength < VFOTAH_DCM_REQ_MSG_MEM_SIZE_LENGTH_MIN)
          || (vFotaH_DownloadMessageInfo.MemSizeLength > VFOTAH_DCM_REQ_MSG_MEM_SIZE_LENGTH_MAX))
        {
          ErrorCode[0] = DCM_E_REQUESTOUTOFRANGE;
        }
        else
        {
          /* #-- If the specified memory address length and memory size length are in range of the received message:
          *       Read the memory address and size and return the values.
          *     Otherwise, indicate an invalid request message length and indicate that processing is terminated. */
          if (pMsgContext->reqDataLen >= ((VFOTAH_DCM_REQ_MSG_OFFSET + vFotaH_DownloadMessageInfo.MemAddressLength) + vFotaH_DownloadMessageInfo.MemSizeLength))
          {
            retVal = E_OK;
            if (opStatus == DCM_INITIAL)
            {
              vSwUpdM_ModuleIdType openedModuleId = 0u;
              uint16_least i;

              vFotaH_DownloadMessageInfo.MemAddress = vFotaH_Hlp_MemAccByteStream2AtomicData(
                &pMsgContext->reqData[VFOTAH_DCM_REQ_MSG_MEM_ADDR_INDEX],
                vFotaH_DownloadMessageInfo.MemAddressLength);
              vFotaH_DownloadMessageInfo.MemSize = vFotaH_Hlp_MemAccByteStream2AtomicData(
                &pMsgContext->reqData[VFOTAH_DCM_REQ_MSG_MEM_ADDR_INDEX + vFotaH_DownloadMessageInfo.MemAddressLength],
                vFotaH_DownloadMessageInfo.MemSizeLength);
              vFotaH_DownloadMessageInfo.ProcessingInfo = (uint8)(pMsgContext->reqData[VFOTAH_DCM_REQ_MSG_DATA_PROCESSING_INDEX]);

              vFotaH_DownloadMessageInfo.IsMemDataValid = TRUE;

              /* #-- If we have no valid Fingerprint set, we reject SW update */
              if (vFotaH_Fingerprint.FingerprintValid != TRUE)
              {
                ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
                retVal = E_NOT_OK;
              }
              else
              {
                retVal = vFotaH_vSwUpdMGetModuleIdByRange(&openedModuleId, vFotaH_DownloadMessageInfo.MemAddress, vFotaH_DownloadMessageInfo.MemSize);
                if (retVal == E_OK)
                {
                  /* #-- Find the logical block id of the now opened module */
                  for (i = 0u; i < vFotaH_GetSizeOfLogicalBlockDescriptor(); i++)
                  {
                    if (vFotaH_GetModuleSnvOfLogicalBlockDescriptor(i) == openedModuleId)
                    {
                      vFotaH_DownloadData.LogBlockId = (uint16)i;
                      break;
                    }
                  }

                  if (i == vFotaH_GetSizeOfLogicalBlockDescriptor())
                  {
                    ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
                    retVal = E_NOT_OK;
                  }
                }
                else
                {
                  ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
                }
              }
            }

            if (retVal == E_OK)
            {
              retVal = vFotaH_vSwUpdMPrepareDownload(vFotaH_DownloadMessageInfo.MemAddress, vFotaH_DownloadMessageInfo.MemSize, vFotaH_DownloadMessageInfo.ProcessingInfo);
              if (retVal == E_OK)
              {
                uint32 blockLength = vFotaH_GetFotaDcmDslBufferSize();

                /* Prepare positive response */
                pMsgContext->resDataLen += VFOTAH_REQUEST_DOWNLOAD_RESPONSE_LENGTH; /* add 3 bytes of response 1 for LFI and 2 for blockLength */
                pMsgContext->resData[0] = VFOTAH_REQUEST_DOWNLOAD_LENGTHFORMATIDENTIFIER;
                pMsgContext->resData[1] = 0x00u;
                pMsgContext->resData[2] = 0x00u;
                pMsgContext->resData[3] = (uint8)(blockLength >> 8u);
                pMsgContext->resData[4] = (uint8)(blockLength & 0xFFu);

                /* Set upload state variables */
                vFotaH_DownloadData.Address = (vSwUpdM_AddressType)vFotaH_DownloadMessageInfo.MemAddress;
                vFotaH_DownloadData.DataSize = (vSwUpdM_LengthType)vFotaH_DownloadMessageInfo.MemSize;
                vFotaH_DownloadData.RemainingBlockSize = blockLength;
                vFotaH_DownloadData.BlockSize = blockLength; /* block size may vary for first and for last block */
                vFotaH_DownloadData.MaxBlockSize = blockLength; /* this size is fixed */
                vFotaH_DownloadData.BytesProcessed = 0u;
                vFotaH_DownloadData.SeqCnt = 1u;
              }
              else if (retVal != VFOTAH_E_PENDING)
              {
                /* #-- Segment could not be added/opened, return error code. */
                ErrorCode[0] = DCM_E_GENERALPROGRAMMINGFAILURE;
                retVal = E_NOT_OK; /* no reason to call function again */
              }
              else
              {
                /* Concluding else */
              }
            }
          }
          else
          {
            ErrorCode[0] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            retVal = E_NOT_OK; /* no reason to call function again */
          }
        }
      }
    }
    else /* DCM_CANCEL */
    {
      retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_DIAGNOSTIC_SERVICE_0x34, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6010 3 */ /* MD_MSR_STPTH */
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmRequestDownload */

/**********************************************************************************************************************
 * vFotaH_DcmTransferData
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
/* PRQA S 0777 1 */ /* MD_MSR_Rule5.1 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmTransferData(
  Dcm_OpStatusType opStatus,            /* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (pMsgContext == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
  if (ErrorCode == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
  {
    ErrorCode[0] = DCM_E_CONDITIONSNOTCORRECT;
    /* #-- If the service is still to be executed: */
    if ((opStatus == DCM_INITIAL) || (opStatus == DCM_PENDING))
    {
      /* #-- If expected data is received: */
      if ((pMsgContext->reqDataLen > 0u)
        && (pMsgContext->reqDataLen <= (vFotaH_DownloadData.MaxBlockSize - 1u))) /* Service Number not considered */
      {
        /* #-- If the sequence counter is as expected: */
        if (pMsgContext->reqData[0] == vFotaH_DownloadData.SeqCnt)
        {
          /* store block size */
          vFotaH_DownloadData.RemainingBlockSize = pMsgContext->reqDataLen - 1u;
          vFotaH_DownloadData.BlockSize = pMsgContext->reqDataLen - 1u;

          /* #-- If more bytes received than expected, buffer overflows, thus notify DCM.  */
          if (vFotaH_DownloadData.DataSize < (vFotaH_DownloadData.BytesProcessed + (pMsgContext->reqDataLen - 1u)))
          {
            ErrorCode[0] = DCM_E_REQUESTOUTOFRANGE;
            retVal = E_NOT_OK;
          }
          /* #-- Otherwise, vFotaH is ready to write data, thus trigger memory copy in vSwUpdM. */
          else
          {
            vFotaH_DownloadData.DcmSourceBufferPtr = &(pMsgContext->reqData[1]);
            retVal = vFotaH_vSwUpdMTransferData(&vFotaH_DownloadData);

            /* #-- If vSwUpdM service was accepted or another job is pending, do nothing.
            *     Otherwise, the vSwUpdM cannot handle the stream data, notify DCM about this error.*/
            if (retVal == E_OK)
            {
              /* #-- Write finished; prepare positive response. */
              pMsgContext->resData[0] = vFotaH_DownloadData.SeqCnt;
              pMsgContext->resDataLen += 1u;
              /* Send final positive response */

              /* #-- Set download state variables */
              vFotaH_DownloadData.SeqCnt++;
              vFotaH_DownloadData.Address += vFotaH_DownloadData.BlockSize;
              vFotaH_DownloadData.BytesProcessed += vFotaH_DownloadData.BlockSize;
            }
            else
            if (retVal == VFOTAH_E_PENDING)
            {
              /* Intentionally do nothing. */
            }
            else
            {
              ErrorCode[0] = DCM_E_GENERALPROGRAMMINGFAILURE;
              retVal = E_NOT_OK;
            }
          }
        }
        /* #-- Otherwise if the download of the last block is repeated: */
        else if (pMsgContext->reqData[0] == (vFotaH_DownloadData.SeqCnt - 1u))
        {
          /* #-- Write already done; prepare positive response. */
          pMsgContext->resData[0] = vFotaH_DownloadData.SeqCnt - 1u;
          pMsgContext->resDataLen += 1u;
          retVal = E_OK;
        }
        /* #-- Otherwise, the sequence counter is invalid, thus notify DCM. */
        else
        {
          ErrorCode[0] = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
          retVal = E_NOT_OK;
        }
      }
      /* #-- Otherwise, the buffer is too big, thus do not inform higher layer in this case, just sent NRC
      *       (see FP5_6443). */
      else
      {
        ErrorCode[0] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        retVal = E_NOT_OK;
      }
    }
    /* #-- Otherwise, clear the already received data and indicate that processing is
    *       successfully terminated. */
    else
    {
      retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_DIAGNOSTIC_SERVICE_0x36, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmTransferData */

/**********************************************************************************************************************
* vFotaH_DcmRequestTransferExit
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
/* PRQA S 0777 2 */ /* MD_MSR_Rule5.1 */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmRequestTransferExit(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized or a NULL_PTR is passed, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((pMsgContext == NULL_PTR)
    || (ErrorCode == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
    /* ----- Implementation ---------------------------------------------------------------------- */
    /* #-- Otherwise: */
  {
    ErrorCode[0] = DCM_E_GENERALPROGRAMMINGFAILURE;
    /* #-- If the service is still to be executed: */
    if ((opStatus == DCM_INITIAL) || (opStatus == DCM_PENDING))
    {
      /* #-- Execute the service if currently allowed. */
      retVal = vFotaH_vSwUpdMFinalizeDownload();
    }
    /* #-- Otherwise, clear the already received data and indicate that processing is
    *       successfully terminated. */
    else
    {
      retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_DIAGNOSTIC_SERVICE_0x37, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  VFOTAH_DUMMY_STATEMENT(pMsgContext); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmRequestTransferExit */


/**********************************************************************************************************************
* vFotaH_DcmReadCommitStatus
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
/* PRQA S 0777 2 */ /* MD_MSR_Rule5.1 */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadCommitStatus(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (Data == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      /* #-- Copy commit information into response string. */
      Data[0u] = vFotaH_NvMInfoBlock[0u].ModuleStatus & VFOTAH_MODULE_STATUS_COMMIT;
      retVal = E_OK;
    }
    /* #-- Otherwise: indicate pending until init finished. */
    else
    {
      retVal = VFOTAH_E_PENDING;
    }
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_READ_COMMIT_STATUS, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif
  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmReadCommitStatus */


/**********************************************************************************************************************
* vFotaH_DcmReadSoftwareVersionLength
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadSoftwareVersionLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, VFOTAH_VAR_NOINIT) DataLength)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (DataLength == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    /* #-- Calculate the length +1 for Block ID. */
    DataLength[0] = (vFotaH_GetFotaVersionInfoLength() + 1u) * vFotaH_GetSizeOfLogicalBlockDescriptor();
    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_SW_VERSION_LENGTH, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  return retVal;
} /* vFotaH_DcmReadSoftwareVersionLength */


/**********************************************************************************************************************
* vFotaH_DcmReadActiveSoftwareVersion
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
/* PRQA S 0777 2 */ /* MD_MSR_Rule5.1 */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadActiveSoftwareVersion(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (Data == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      /* #-- If the DCM service is cancelled, clear all states. */
      if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
      {
        retVal = vFotaH_Hlp_ReadSoftwareVersion(OpStatus, VSWUPDM_PART_STATE_ACTIVE, vFotaH_GetFotaVersionInfoLength(), Data);
      }
      else
      {
        retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
      }
    }
    /* #-- Otherwise:
    *       Otherwise, indicate failure. */
    else
    {
      retVal = VFOTAH_E_PENDING;
    }
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_READ_ACTIVE_SW_VERSION, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmReadActiveSoftwareVersion */



/**********************************************************************************************************************
* vFotaH_DcmReadInactiveSoftwareVersion
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
/* PRQA S 0777 2 */ /* MD_MSR_Rule5.1 */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadInactiveSoftwareVersion(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (Data == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    /* #-- If the DCM service is cancelled, clear all states. */
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      /* #-- If the DCM service is cancelled, clear all states. */
      if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
      {
        retVal = vFotaH_Hlp_ReadSoftwareVersion(OpStatus, VSWUPDM_PART_STATE_INACTIVE, vFotaH_GetFotaVersionInfoLength(), Data);
      }
      else
      {
        retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
      }
    }
    /* #-- Otherwise:
    *       Otherwise, indicate failure. */
    else
    {
      retVal = VFOTAH_E_PENDING;
    }
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_READ_INACTIVE_SW_VERSION, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmReadInactiveSoftwareVersion */


/**********************************************************************************************************************
* vFotaH_DcmReadSoftwareFingerprintLength
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadSoftwareFingerprintLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, VFOTAH_VAR_NOINIT) DataLength)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (DataLength == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    DataLength[0] = (VFOTAH_FINGERPRINT_SIZE + 1u) * vFotaH_GetSizeOfLogicalBlockDescriptor();
    retVal = E_OK;
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_SW_FINGERPRINT_LENGTH, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  return retVal;
} /* vFotaH_DcmReadSoftwareFingerprintLength */


/**********************************************************************************************************************
* vFotaH_DcmReadInactiveSoftwareFingerprint
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
/* PRQA S 0777 2 */ /* MD_MSR_Rule5.1 */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadInactiveSoftwareFingerprint(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (Data == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      uint16_least i;

      /* #-- Copy Fingerprint information for each module into repsonse string. */
      for (i = 0u; i < VFOTAH_NUMBER_OF_MODULES; i++)
      {
        uint16_least j;

        Data[i * (VFOTAH_FINGERPRINT_SIZE + 1u)] = (uint8)(vFotaH_GetHandleOfLogicalBlockDescriptor(i));
        for (j = 0u; j < VFOTAH_FINGERPRINT_SIZE; j++)
        {
          Data[(i * (VFOTAH_FINGERPRINT_SIZE + 1u)) + j + 1u] = vFotaH_NvMInfoBlock[i].Fingerprint_Inactive[j];
        }
      }
      retVal = E_OK;
    }
    /* #-- Otherwise: indicate pending until init finished. */
    else
    {
      retVal = VFOTAH_E_PENDING;
    }
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_READ_INACTIVE_SW_FINGERPRINT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmReadInactiveSoftwareFingerprint */



/**********************************************************************************************************************
* vFotaH_DcmReadActiveSoftwareFingerprint
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
/* PRQA S 0777 2 */ /* MD_MSR_Rule5.1 */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadActiveSoftwareFingerprint(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (Data == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      uint16_least i;

      /* #-- Write Fingerprint information for each module. */
      for (i = 0u; i < VFOTAH_NUMBER_OF_MODULES; i++)
      {
        uint16_least j;

        Data[i * (VFOTAH_FINGERPRINT_SIZE + 1u)] = (uint8)(vFotaH_GetHandleOfLogicalBlockDescriptor(i));
        for (j = 0u; j < VFOTAH_FINGERPRINT_SIZE; j++)
        {
          Data[(i * (VFOTAH_FINGERPRINT_SIZE + 1u)) + j + 1u] = vFotaH_NvMInfoBlock[i].Fingerprint_Active[j];
        }
      }
      retVal = E_OK;
    }
    /* #-- Otherwise:
    *       Otherwise, indicate failure. */
    else
    {
      retVal = VFOTAH_E_PENDING;
    }
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_READ_ACTIVE_SW_FINGERPRINT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(OpStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmReadActiveSoftwareFingerprint */


/**********************************************************************************************************************
* vFotaH_DcmWriteInactiveSoftwareFingerprint
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
/* PRQA S 0777 2 */ /* MD_MSR_Rule5.1 */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmWriteInactiveSoftwareFingerprint(
  P2CONST(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, VFOTAH_VAR_NOINIT) ErrorCode)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((Data == NULL_PTR)
   || (ErrorCode == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    uint16_least i;

    vFotaH_Fingerprint.FingerprintValid = TRUE;
    for (i = 0u; i < VFOTAH_FINGERPRINT_SIZE; i++)
    {
      vFotaH_Fingerprint.Fingerprint[i] = Data[i];
    }
    retVal = DCM_E_OK;
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_WRITE_INACTIVE_SW_FINGERPRINT, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  VFOTAH_DUMMY_STATEMENT(ErrorCode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
  return retVal;
} /* vFotaH_DcmWriteInactiveSoftwareFingerprint */


/**********************************************************************************************************************
* vFotaH_DcmReadDownloadResumeAddress
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
/* PRQA S 0777 2 */ /* MD_MSR_Rule5.1 */
/* PRQA S 3673 4 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadDownloadResumeAddress(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vSwUpdM_ResumeInfoType vSwUpdMResumeInfo;
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (Data == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      if (OpStatus == DCM_INITIAL)
      {
        Data[0] = 0x04;
        Data[1] = 0xffu;
        Data[2] = 0xffu;
        Data[3] = 0xffu;
        Data[4] = 0xffu;

        /* #-- Get the resume info. */
        retVal = vSwUpdM_GetResumeInfo(&vSwUpdMResumeInfo);

        /* #-- If the request succeeded: */
        if (retVal == E_OK)
        {
          /* #-- If the resume info apply to the inactive partition and the service process stream data was interrupted: */
          if (((vSwUpdMResumeInfo.PartitionState & VSWUPDM_PART_STATE_INACTIVE) == VSWUPDM_PART_STATE_INACTIVE)
            && (vSwUpdMResumeInfo.CurrentService == VSWUPDM_SID_PROCESS_STREAM_DATA))
          {
            /* #-- If there are valid resume info (for download). */
            if (vSwUpdMResumeInfo.IsAddressValid == TRUE)
            {
              if (vSwUpdMResumeInfo.ServiceState == VSWUPDM_RESUME_STATE_PENDING)
              {
                retVal = vFotaH_vSwUpdMCheckFinalizeSegment(vSwUpdMResumeInfo.MemoryAddress);
              }

              Data[1] = (uint8)(vSwUpdMResumeInfo.StreamAddress >> 24u);
              Data[2] = (uint8)(vSwUpdMResumeInfo.StreamAddress >> 16u);
              Data[3] = (uint8)(vSwUpdMResumeInfo.StreamAddress >> 8u);
              Data[4] = (uint8)vSwUpdMResumeInfo.StreamAddress;
            }
          }
        }
      }
      else
      {
        /* #-- Continue to finalize segment until finished. */
        retVal = vSwUpdM_GetResumeInfo(&vSwUpdMResumeInfo);
        if (retVal == E_OK)
        {
          retVal = vFotaH_vSwUpdMCheckFinalizeSegment(vSwUpdMResumeInfo.MemoryAddress);
        }
      }
    }
    else
    {
      retVal = VFOTAH_E_PENDING;
    }
  }
  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_DOWNLOAD_RESUME_STATUS, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif
  
  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6080 2 */ /* MD_MSR_STMIF */
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vFotaH_DcmReadDownloadResumeAddress */


/**********************************************************************************************************************
 * vFotaH_DcmReadResumeInfo
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_DcmReadResumeInfo(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, VFOTAH_VAR_NOINIT) Data)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 moduleState;
  vFotaH_ReturnType retVal = DCM_E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if (Data == NULL_PTR)
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  {
    if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_INITIALIZED)
    {
      if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
      {
        if (OpStatus == DCM_INITIAL)
        {
          vFotaH_ModuleId = 0u;
        }
        retVal = vFotaH_Hlp_GetModuleState(&moduleState, vFotaH_ModuleId);

        if (retVal == E_OK)
        {
          Data[vFotaH_ModuleId * 2u] = (uint8)(vFotaH_GetHandleOfLogicalBlockDescriptor(vFotaH_ModuleId));
          Data[(vFotaH_ModuleId * 2u) + 1u] = moduleState;
          if (vFotaH_ModuleId < (vFotaH_GetSizeOfLogicalBlockDescriptor() - 1u))
          {
            vFotaH_ModuleId++; /* PRQA S 2880 */ /* vFotaH_module_Simplification */
            retVal = VFOTAH_E_PENDING;
          }
        }
      }
      else
      {
        retVal = vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
      }
    }
    /* #-- Otherwise:
    *       Otherwise, indicate pending. */
    else
    {
      retVal = VFOTAH_E_PENDING;
    }
  }

  /* ----- Development Error Report ------------------------------------------------------------ */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_READ_RESUME_INFO, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif

  retVal = vFotaH_Hlp_AR2DcmRetValue(retVal);
  return retVal;
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_DcmReadResumeInfo */


/**********************************************************************************************************************
 * vFotaH_DcmSessionChangeNotification
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_DcmSessionChangeNotification(
  Dcm_SesCtrlType formerSesCtrlId,
  Dcm_SesCtrlType newSesCtrlId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8 errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------------------------------ */
  /* #-- If Dev Error Detect is enabled and vFotaH is not initialized, report an error. */
#if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
#endif
  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Otherwise, process the session change notification. */
  {
    /* #-- Check if the FOTA session is left. If yes, reset the download state machine by performing an vSwUpdM shutdown. */
    if (formerSesCtrlId == VFOTAH_SESSION_ID_FOTA)
    {
      vFotaH_StartRequest.ModuleInfoValid = FALSE;
      vFotaH_vSwUpdMResetDownloadInProgress();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_SESSION_CHANGE_NOTIFICATION, errorId);
  }
#else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
#endif
  VFOTAH_DUMMY_STATEMENT(newSesCtrlId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
} /* vFotaH_DcmSessionChangeNotification */


/**********************************************************************************************************************
* vFotaH_ServicesMainFunction
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(void, VFOTAH_CODE) vFotaH_ServicesMainFunction(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vFotaH_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Perform an erase request. Set the current Fingerprint. */
  if (vFotaH_EraseRequest.EraseRequest == VFOTAH_ERASE_ROUTINE_INFO_PENDING)
  {
    retVal = vFotaH_vSwUpdMEraseModule(vFotaH_StartRequest.ModuleHd);
    if (retVal == E_OK)
    {
      uint16_least i;

      /* #-- If we erase for a sync operation we copy the active Fingerprint, otherwise we copy the received fingerprint. */
      if (vFotaH_StartRequest.StartRequest == VFOTAH_MODULE_START_INFO_PENDING)
      {
        for (i = 0u; i < VFOTAH_FINGERPRINT_SIZE; i++)
        {
          vFotaH_NvMInfoBlock[vFotaH_StartRequest.LogBlockId].Fingerprint_Inactive[i] = 
                      vFotaH_NvMInfoBlock[vFotaH_StartRequest.LogBlockId].Fingerprint_Active[i];
        }
      }
      else
      {
        for (i = 0u; i < VFOTAH_FINGERPRINT_SIZE; i++)
        {
          vFotaH_NvMInfoBlock[vFotaH_StartRequest.LogBlockId].Fingerprint_Inactive[i] = vFotaH_Fingerprint.Fingerprint[i];
        }
      }
      (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);

      vFotaH_EraseRequest.EraseRequest = VFOTAH_ERASE_ROUTINE_INFO_COMPLETE;
    }
    else
    if (retVal == E_NOT_OK)
    {
      vFotaH_EraseRequest.EraseRequest = VFOTAH_ERASE_ROUTINE_INFO_FAILED;
    }
    else
    {
      /* Concluding else */
    }
  }

  else
  /* Perform a module.Start request. An erase is performed in case of a sync operation. */
  if (vFotaH_StartRequest.StartRequest == VFOTAH_MODULE_START_INFO_PENDING)
  {
    if (vFotaH_StartRequest.RoutineOp == VFOTAH_MODULE_START_SYNC)
    {
      retVal = vFotaH_vSwUpdMSyncModule(vFotaH_StartRequest.ModuleHd, VSWUPDM_PART_STATE_INACTIVE);

      if (retVal == E_OK)
      {
        uint16_least i;

        for (i = 0u; i < VFOTAH_FINGERPRINT_SIZE; i++)
        {
          vFotaH_NvMInfoBlock[vFotaH_StartRequest.LogBlockId].Fingerprint_Inactive[i] = vFotaH_Fingerprint.Fingerprint[i];
        }
        (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);
        vFotaH_StartRequest.StartRequest = VFOTAH_MODULE_START_INFO_COMPLETE;
      }
      else
      if (retVal == E_NOT_OK)
      {
        vFotaH_StartRequest.StartRequest = VFOTAH_MODULE_START_INFO_FAILED;
      }
      else
      {
        /* Concluding else */
      }
    }
    else
    {
      vFotaH_StartRequest.StartRequest = VFOTAH_MODULE_START_INFO_COMPLETE;
    }
  }

  else
  /* #-- Perform a switch bank or rollback operation. */
  if (vFotaH_SwitchBankRequest.SwitchBankRequest == VFOTAH_PERFORM_SWITCH_INFO_PENDING)
  {
    boolean activeLaterSW;

    if (vFotaH_SwitchBankRequest.ResetPending == FALSE)
    {
      (void)vFotaH_vSwUpdMHasActivePartitionLaterSoftware(&activeLaterSW);

      if (activeLaterSW == FALSE)
      {
        if (vFotaH_SwitchBankRequest.SwitchOption == VFOTAH_PARTITION_SWITCH_OPTION_ACTIVATE)
        {
          /* This is a normal activation, perform a Bank Switch */
          retVal = vFotaH_vSwUpdMSwitchBank(VSWUPDM_PART_STATE_INACTIVE);
        }
        else
        {
          /* This is a early revert */
          retVal = vFotaH_vSwUpdMSwitchBank(VSWUPDM_PART_STATE_ACTIVE);
        }
      }
      else
      {
        if (vFotaH_SwitchBankRequest.SwitchOption == VFOTAH_PARTITION_SWITCH_OPTION_ACTIVATE)
        {
          /* This is a don't care */
          retVal = E_NOT_OK;
        }
        else
        {
          /* This is a revert operation, perform rollback */
          if (vFotaH_ActiveUseCase == VFOTAH_ACTIVE_USE_CASE_BASIC)
          {
            retVal = vFotaH_vSwUpdMSwitchBank(VSWUPDM_PART_STATE_INACTIVE);
          }
          else
          {
            retVal = vFotaH_vSwUpdMSwitchBank(VSWUPDM_PART_STATE_BACKUP_SOURCE);
          }
        }
      }
    }
    else
    {
      retVal = E_OK;
    }

    if (retVal == E_OK)
    {
      retVal = vFotaH_Appl_RequestReset();
      if (retVal == VFOTAH_E_PENDING)
      {
        vFotaH_SwitchBankRequest.ResetPending = TRUE;
      }
      else
      if (retVal == E_OK)
      {
        vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_COMPLETE;
        vFotaH_SwitchBankRequest.ResetPending = FALSE;
      }
      else
      {
        vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_FAILED;
        vFotaH_SwitchBankRequest.ResetPending = FALSE;
      }
    }
    else
    if (retVal == E_NOT_OK)
    {
      vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_FAILED;
      vFotaH_SwitchBankRequest.ResetPending = FALSE;
    }
    else
    {
      /* Concluding else */
    }
  }

  else
  if (vFotaH_VerifyModuleRequest.VerifyModuleRequest == VFOTAH_VERIFY_MODULE_INFO_PENDING)
  {
    retVal = vFotaH_vSwUpdMVerifyModule(&vFotaH_VerifyModuleRequest.VerifyData[0], vFotaH_VerifyModuleRequest.SizeofVerifyData, vFotaH_StartRequest.ModuleHd);

    if (retVal == E_OK)
    {
      vFotaH_VerifyModuleRequest.VerifyModuleRequest = VFOTAH_VERIFY_MODULE_INFO_COMPLETE;
    }
    else
    if (retVal == E_NOT_OK)
    {
      vFotaH_VerifyModuleRequest.VerifyModuleRequest = VFOTAH_VERIFY_MODULE_INFO_FAILED;
    }
    else
    {
      /* Concluding else */
    }
  }

  else
  /* #-- Perform a prepare activation operation. In case of extended use case a backup is created. */
  if (vFotaH_PrepareActivationRequest.PrepareActivationRequest == VFOTAH_PREPARE_ACTIVATION_INFO_PENDING)
  {
    if (vFotaH_ActiveUseCase == VFOTAH_ACTIVE_USE_CASE_EXTENDED)
    {
      /* Create Backup */
      retVal = vFotaH_vSwUpdMSyncPartition(VSWUPDM_PART_STATE_BACKUP_TARGET);
    }
    else
    {
      retVal = E_OK;
    }

    if (retVal == E_OK)
    {
      vFotaH_PrepareActivationRequest.PrepareActivationRequest = VFOTAH_PREPARE_ACTIVATION_INFO_COMPLETE;
    }
    else
    if (retVal == E_NOT_OK)
    {
      vFotaH_PrepareActivationRequest.PrepareActivationRequest = VFOTAH_PREPARE_ACTIVATION_INFO_FAILED;
    }
    else
    {
      /* Concluding else */
    }
  }

  else
  if (vFotaH_UpdateCommitRequest.UpdateCommitRequest == VFOTAH_UPDATE_COMMIT_INFO_PENDING)
  {
    vFotaH_UpdateCommitRequest.UpdateCommitRequest = VFOTAH_UPDATE_COMMIT_INFO_COMPLETE;
  }
  else
  {
    /* Concluding else */
  }
  /* PRQA S 6030 3 */ /* MD_MSR_STCYC */
  /* PRQA S 6050 2 */ /* MD_MSR_STCAL */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_ServicesMainFunction */


/***********************************************************************************************************************
*  vFotaH_DcmSecLevelChangeNotification()
***********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
FUNC(void, VFOTAH_CODE) vFotaH_DcmSecLevelChangeNotification(Dcm_SecLevelType FormerSecLevelId,
  Dcm_SecLevelType NewSecLevelId)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  if ((vFotaH_SwitchBankRequest.SwitchBankRequest != VFOTAH_PERFORM_SWITCH_INFO_PENDING)
   && (FormerSecLevelId == VFOTAH_UDS_SECURITY_ACCESS_TYPE))
  {
    (void)vFotaH_Shutdown(VFOTAH_PERFORM_RESTART);
  }

  VFOTAH_DUMMY_STATEMENT(NewSecLevelId); /* PRQA S 1338, 2983 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  vFotaH_Rollback
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_Rollback(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = VFOTAH_E_PENDING;
  vFotaH_InitializationStateType initState = vFotaH_InitializationSM_GetState();

  /* ----- Implementation ----------------------------------------------- */
  if (initState == VFOTAH_INIT_STATE_INITIALIZED)
  {
    /* #-- We perform a sw triggered rollback if it is allowed due to update state (after activation and before commit). */
    if (vFotaH_NvMInfoBlock[0u].SwitchBankRequest == VFOTAH_PARTITION_SWITCH_OPTION_PENDING)
    {
      vFotaH_SwitchBankRequest.SwitchBankRequest = VFOTAH_PERFORM_SWITCH_INFO_PENDING;
      vFotaH_SwitchBankRequest.SwitchOption = VFOTAH_PARTITION_SWITCH_OPTION_REVERT;

      vFotaH_NvMInfoBlock[0u].SwitchBankRequest = VFOTAH_PARTITION_SWITCH_OPTION_NONE;
      (void)NvM_SetRamBlockStatus((NvM_BlockIdType)vFotaH_GetFotaModuleInfoNvMSnv(), TRUE);

      retVal = E_OK;
    }
    else
    {
      retVal = VFOTAH_E_ROLLBACK_NOT_ALLOWED;
    }
  }

  return retVal;
} /* vFotaH_Rollback */


#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_Services.c
 *********************************************************************************************************************/
