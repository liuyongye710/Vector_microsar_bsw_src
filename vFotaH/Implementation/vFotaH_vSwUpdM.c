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
/*        \file  vFotaH_vSwUpdM.c
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

#define VFOTAH_VSWUPDM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vFotaH_States.h"
#include "vFotaH_Priv.h"
#include "vFotaH_Services.h"
#include "vFotaH_vSwUpdM.h"
#include "vFotaH_Appl.h"

#include "SchM_vFotaH.h"
#include "vSwUpdM.h"

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

#define VFOTAH_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/* State machine variables. They reflect the current and the target state of each state machine. */
VFOTAH_LOCAL VAR(uint8, VFOTAH_VAR_NOINIT)                      vFotaH_SMCurrentState[VFOTAH_NUMBER_OF_SM];
VFOTAH_LOCAL VAR(uint8, VFOTAH_VAR_NOINIT)                      vFotaH_SMTargetState[VFOTAH_NUMBER_OF_SM];

/* Pointer to information struct about the downlaoded data. */
VFOTAH_LOCAL P2VAR(vFotaH_DownloadDataType, AUTOMATIC, VFOTAH_VAR_NOINIT)   vFotaH_DownloadDatap;
/* Input data information for vStreamProc verification */
VFOTAH_LOCAL VAR(vSwUpdM_ConstDataInfoType, VFOTAH_VAR_NOINIT)              vFotaH_InputData; /* PRQA S 3218 */ /* MD_vFotaH_3218 */
/* Global flags used in several functions */
VFOTAH_LOCAL VAR(boolean, VFOTAH_VAR_NOINIT)                                vFotaH_DownloadInProgress;
VFOTAH_LOCAL VAR(uint8, VFOTAH_VAR_NOINIT)                                  vFotaH_RestartFlag;

#define VFOTAH_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

#define VFOTAH_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/* The value indication error state for each state machine. */
VFOTAH_LOCAL CONST(uint8, VFOTAH_CONST) vFotaH_SMErrorState[VFOTAH_NUMBER_OF_SM] = /* PRQA S 3218 */ /* MD_vFotaH_3218 */
{ VFOTAH_ERASE_ERROR_DETECTED, VFOTAH_SYNCM_ERROR_DETECTED, VFOTAH_SYNCP_ERROR_DETECTED, VFOTAH_VALIDATEP_ERROR_DETECTED, VFOTAH_VALIDATEM_ERROR_DETECTED,
  VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED, VFOTAH_TRANSFERDATA_ERROR_DETECTED, VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED, VFOTAH_FINALIZESEGMENT_ERROR_DETECTED,
  VFOTAH_READRANGE_ERROR_DETECTED, VFOTAH_VERIFYMODULE_ERROR_DETECTED, VFOTAH_SWITCHBANK_ERROR_DETECTED, VFOTAH_GETMODULEINFO_ERROR_DETECTED };

#define VFOTAH_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define VFOTAH_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
*  vFotaH_vSwUpdMBusyCheck()
*********************************************************************************************************************/
/*! \brief      Checks whether the vSwUpdM is Busy or any new request can be issued.
 *  \details     -
 *  \param[in]   smException    The id of the state machine excepted from this check.
 *  \return      E_OK - A new request can be issued.
 *  \return      E_NOT_OK - The vSwUpdM state machine is busy, now new request is allowed.
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     vSwUpdMService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMBusyCheck(uint8 smException);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMErrorCloseModule()
*********************************************************************************************************************/
/*! \brief       If an module is still open, a CloseModule is triggered in this function.
 *  \details     Target state is only set if the CloseModule is successfully triggered.
 *  \param[in]   StateId        The id of the state machine to modify.
 *  \param[in]   TargetState    The target state of this operation.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMErrorCloseModule(uint8 StateId, uint8 TargetState);

/**********************************************************************************************************************
*  vFotaH_vSwUpdMEntryCheck()
*********************************************************************************************************************/
/*! \brief       Check if the requested function is ready to be executed
 *  \details     -
 *  \param[in]   StateId          The id of the state machine to modify.
 *  \return      E_OK             Function is valid to be executed.
 *  \return      VFOTAH_E_PENDING Function is in a pending state, e.g. a confirmation is missing.
 *  \return      E_NOT_OK         Function is not valid to be executed.
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \ingroup     internalService
*********************************************************************************************************************/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMEntryCheck(uint8 StateId);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

 /**********************************************************************************************************************
* vFotaH_vSwUpdMBusyCheck
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMBusyCheck(uint8 smException)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least i;
  Std_ReturnType retVal = E_OK;
  vFotaH_ErrorCode errorId = VFOTAH_E_NO_ERROR;

  /* ----- Development Error Report --------------------------------------- */
# if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  vFotaH_StateType state = vFotaH_InitializationSM_GetState();

  if (state == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
# endif
    /* ----- Implementation ----------------------------------------------- */
  {
    /* #-- Check if any SM is busy. If yes, return VFOTAH_E_PENDING */
    for (i = 0u; i < VFOTAH_NUMBER_OF_SM; i++)
    {
      if (i != smException)
      {
        if ((vFotaH_SMCurrentState[i] != VFOTAH_ANY_STATE_IDLE)
         || (vFotaH_SMTargetState[i] != VFOTAH_ANY_STATE_IDLE))
        {
          retVal = VFOTAH_E_PENDING;
          break;
        }
      }
    }

    if ((vFotaH_DownloadInProgress == TRUE)
      && ((smException != VFOTAH_PREPAREDOWNLOAD_STATE_ID)
       && (smException != VFOTAH_TRANSFERDATA_STATE_ID)
       && (smException != VFOTAH_FINALIZEDOWNLOAD_STATE_ID)))
    {
      /* #-- Special case if the download sequence is interrupted then perform a restart. */
      retVal = E_NOT_OK;
      vFotaH_vSwUpdMResetDownloadInProgress();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_BUSY_CHECK, errorId);
  }
# else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif

  return retVal;
} /* vFotaH_vSwUpdMBusyCheck */

/**********************************************************************************************************************
* vFotaH_vSwUpdMErrorCloseModule
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMErrorCloseModule(uint8 StateId, uint8 TargetState)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;
  vSwUpdM_ModuleIdType openedModuleId;

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Request to close the currently opened module if it is still open in an error case. */
  retVal = vSwUpdM_GetOpenModuleId(&openedModuleId);
  if ((retVal == E_OK) && (openedModuleId != VSWUPDM_INVALID_ID))
  {
    retVal = vSwUpdM_CloseModule(openedModuleId);
    if (retVal == E_OK)
    {
      vFotaH_SMTargetState[StateId] = TargetState;
      retVal = VFOTAH_E_PENDING;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* vFotaH_vSwUpdMErrorCloseModule */


/**********************************************************************************************************************
* vFotaH_vSwUpdMEntryCheck
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
VFOTAH_LOCAL FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMEntryCheck(uint8 StateId)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMBusyCheck(StateId);
  if (retVal == E_OK)
  {
    if (vFotaH_SMCurrentState[StateId] != vFotaH_SMTargetState[StateId])
    {
      retVal = VFOTAH_E_PENDING;
    }
  }
  return retVal;
}



/* ################################################################################################################# */
/* Services */
/* ################################################################################################################# */

/**********************************************************************************************************************
 * vFotaH_vSwUpdMSyncPartition
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMSyncPartition(vSwUpdM_PartitionStateType PartitionState)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_SYNCP_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_SYNCP_STATE_ID])
    {
    case (VFOTAH_SYNCP_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_SYNCP_STATE_ID] = VFOTAH_SYNCP_OPENPARTITION_OPENED;
        /* #-- Open the selected partition to sync. */
        retVal = vSwUpdM_OpenPartition(PartitionState);
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_SYNCP_OPENPARTITION_OPENED) :
      {
        vFotaH_SMTargetState[VFOTAH_SYNCP_STATE_ID] = VFOTAH_SYNCP_PARTITION_SYNCED;
        /* #-- Sync the partitition until finished. */
        retVal = vSwUpdM_SyncPartition();
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_SYNCP_PARTITION_SYNCED) :
      {
        vFotaH_SMTargetState[VFOTAH_SYNCP_STATE_ID] = VFOTAH_SYNCP_PARTITION_VALIDATED;
        /* #-- Validate partition, a synced partition is always verified. */
        retVal = vSwUpdM_ValidatePartition();
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
    } break;

    case (VFOTAH_SYNCP_PARTITION_VALIDATED) :
      {
        retVal = E_OK;
      } break;

    case (VFOTAH_SYNCP_ERROR_DETECTED) :
      {
        /* #-- Request to close the currently opened module if it is still open in an error case. */
        retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_SYNCP_STATE_ID, VFOTAH_SYNCP_ERROR_RESOLVED);
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMTargetState[VFOTAH_SYNCP_STATE_ID] = VFOTAH_SYNCP_STATE_IDLE;
      vFotaH_SMCurrentState[VFOTAH_SYNCP_STATE_ID] = VFOTAH_SYNCP_STATE_IDLE;
    }
  }

  return retVal;
  /* PRQA S 6030 1 */ /* MD_MSR_STCYC */
} /* vFotaH_vSwUpdMSyncPartition */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMValidatePartition
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMValidatePartition(vSwUpdM_PartitionStateType PartitionState)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_VALIDATEP_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_VALIDATEP_STATE_ID])
    {
    case (VFOTAH_VALIDATEP_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_VALIDATEP_STATE_ID] = VFOTAH_VALIDATEP_OPENPARTITION_OPENED;
        /* #-- Open the selected partition to validate. */
        retVal = vSwUpdM_OpenPartition(PartitionState);
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_VALIDATEP_OPENPARTITION_OPENED) :
      {
        vFotaH_SMTargetState[VFOTAH_VALIDATEP_STATE_ID] = VFOTAH_VALIDATEP_PARTITION_VALIDATED;
        /* #-- Validate the partition until finished. */
        retVal = vSwUpdM_ValidatePartition();
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_VALIDATEP_PARTITION_VALIDATED) :
      {
        retVal = E_OK;
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMTargetState[VFOTAH_VALIDATEP_STATE_ID] = VFOTAH_VALIDATEP_STATE_IDLE;
      vFotaH_SMCurrentState[VFOTAH_VALIDATEP_STATE_ID] = VFOTAH_VALIDATEP_STATE_IDLE;
    }
  }

  return retVal;
} /* vFotaH_vSwUpdMValidatePartition */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMValidateModule
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMValidateModule(vSwUpdM_PartitionStateType PartitionState, vSwUpdM_ModuleHandleIdType ModuleHd)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vSwUpdM_ModuleIdType moduleId;
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_VALIDATEM_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_VALIDATEM_STATE_ID])
    {
    case (VFOTAH_VALIDATEM_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_VALIDATEM_STATE_ID] = VFOTAH_VALIDATEM_OPENPARTITION_OPENED;
        /* #-- Open the selected partition to validate. */
        retVal = vSwUpdM_OpenPartition(PartitionState);
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_VALIDATEM_OPENPARTITION_OPENED) :
      {
        vFotaH_SMTargetState[VFOTAH_VALIDATEM_STATE_ID] = VFOTAH_VALIDATEM_MODULE_VALIDATED;
        /* #-- Validate the module until finished. */
        retVal = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHd);
        if (retVal == E_OK)
        {
          retVal = vSwUpdM_ValidateModule(moduleId);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
          else
          {
            vFotaH_SMTargetState[VFOTAH_VALIDATEM_STATE_ID] = VFOTAH_VALIDATEM_ERROR_DETECTED;
            vFotaH_SMCurrentState[VFOTAH_VALIDATEM_STATE_ID] = VFOTAH_VALIDATEM_ERROR_DETECTED;
            retVal = VFOTAH_E_PENDING;
          }
        }
      } break;

    case (VFOTAH_VALIDATEM_MODULE_VALIDATED) :
      {
        retVal = E_OK;
      } break;

    case (VFOTAH_SYNCM_ERROR_DETECTED) :
      {
        /* #-- Request to close the currently opened module if it is still open in an error case. */
        retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_VALIDATEM_STATE_ID, VFOTAH_VALIDATEM_ERROR_RESOLVED);
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMTargetState[VFOTAH_VALIDATEM_STATE_ID] = VFOTAH_VALIDATEM_STATE_IDLE;
      vFotaH_SMCurrentState[VFOTAH_VALIDATEM_STATE_ID] = VFOTAH_VALIDATEM_STATE_IDLE;
    }
  }

  return retVal;
} /* vFotaH_vSwUpdMValidateModule */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMSyncModule
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMSyncModule(vSwUpdM_ModuleHandleIdType ModuleHd, vSwUpdM_PartitionStateType PartitionState)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;
  vSwUpdM_ModuleIdType moduleId;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHd);
  if (retVal == E_OK)
  {
    retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_SYNCM_STATE_ID);
    if (retVal == E_OK)
    {
      switch (vFotaH_SMCurrentState[VFOTAH_SYNCM_STATE_ID])
      {
      case (VFOTAH_SYNCM_STATE_IDLE) :
        {
          vFotaH_SMTargetState[VFOTAH_SYNCM_STATE_ID] = VFOTAH_SYNCM_OPENPARTITION_OPENED;
          /* #-- Open the selected partition. */
          retVal = vSwUpdM_OpenPartition(PartitionState);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_SYNCM_OPENPARTITION_OPENED) :
        {
          vSwUpdM_ModuleInfoType moduleInfo;

          vFotaH_SMTargetState[VFOTAH_SYNCM_STATE_ID] = VFOTAH_SYNCM_MODULE_SYNCED;
          /* #-- If the module is erased then sync it, otherwise return an error. */
          retVal = vSwUpdM_GetModuleInfo(&moduleInfo, moduleId);
          if ((retVal == E_OK) && (moduleInfo.State == VSWUPDM_MODULE_STATE_ERASED))
          {
            retVal = vSwUpdM_SyncModule(moduleId);
            if (retVal == E_OK)
            {
              retVal = VFOTAH_E_PENDING;
            }
            else
            {
              vFotaH_SMTargetState[VFOTAH_SYNCM_STATE_ID] = VFOTAH_SYNCM_ERROR_DETECTED;
              vFotaH_SMCurrentState[VFOTAH_SYNCM_STATE_ID] = VFOTAH_SYNCM_ERROR_DETECTED;
              retVal = VFOTAH_E_PENDING;
            }
          }
          else
          {
            retVal = E_NOT_OK;
          }
        } break;

      case (VFOTAH_SYNCM_MODULE_SYNCED) :
        {
          retVal = E_OK;
        } break;

      case (VFOTAH_SYNCM_ERROR_DETECTED) :
        {
          /* #-- Request to close the currently opened module if it is still open in an error case. */
          retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_SYNCM_STATE_ID, VFOTAH_SYNCM_ERROR_RESOLVED);
        } break;

      default :
        {
          retVal = E_NOT_OK;
        } break;
      }

      /* #-- In case of positive or negative result, we return to IDLE state. */
      if (retVal != VFOTAH_E_PENDING)
      {
        vFotaH_SMTargetState[VFOTAH_SYNCM_STATE_ID] = VFOTAH_SYNCM_STATE_IDLE;
        vFotaH_SMCurrentState[VFOTAH_SYNCM_STATE_ID] = VFOTAH_SYNCM_STATE_IDLE;
      }
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_vSwUpdMSyncModule */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMEraseModule
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMEraseModule(vSwUpdM_ModuleHandleIdType ModuleHd)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;
  vSwUpdM_ModuleIdType moduleId;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHd);

  if (retVal == E_OK)
  {
    retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_ERASE_STATE_ID);
    if (retVal == E_OK)
    {
      switch (vFotaH_SMCurrentState[VFOTAH_ERASE_STATE_ID])
      {
      case (VFOTAH_ERASE_STATE_IDLE) :
        {
          vFotaH_SMTargetState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_OPENPARTITION_OPENED;
          /* #-- Open the selected partition. */
          retVal = vSwUpdM_OpenPartition(VSWUPDM_PART_STATE_INACTIVE);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_ERASE_OPENPARTITION_OPENED) :
        {
          vFotaH_SMTargetState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_MODULE_ERASED;
          /* #-- Erase the selected module until finished. */
          retVal = vSwUpdM_EraseModule(moduleId);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_ERASE_MODULE_ERASED) :
        {
          vFotaH_SMTargetState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_MODULE_OPENED;
          /* #-- Open the module, this is required for segment operation. */
          retVal = vSwUpdM_OpenModule(moduleId);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_ERASE_MODULE_OPENED) :
        {
          vFotaH_SMTargetState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_SEGMENT_ERASED;
          /* #-- Clear all segment information of the now erased module. */
          retVal = vSwUpdM_ClearSegmentsOfModule(moduleId);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
          else
          {
            vFotaH_SMCurrentState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_ERROR_DETECTED;
            vFotaH_SMTargetState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_ERROR_DETECTED;
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_ERASE_SEGMENT_ERASED) :
        {
          vFotaH_SMTargetState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_MODULE_CLOSED;
          /* #-- And close the module again. */
          retVal = vSwUpdM_CloseModule(moduleId);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_ERASE_MODULE_CLOSED) :
        {
          retVal = E_OK;
        } break;

      case (VFOTAH_ERASE_ERROR_DETECTED) :
        {
          /* #-- Request to close the currently opened module if it is still open in an error case. */
          retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_ERASE_STATE_ID, VFOTAH_ERASE_ERROR_RESOLVED);
        } break;

      default :
        {
          retVal = E_NOT_OK;
        } break;
      }

      /* #-- In case of positive or negative result, we return to IDLE state. */
      if (retVal != VFOTAH_E_PENDING)
      {
        vFotaH_SMCurrentState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_STATE_IDLE;
        vFotaH_SMTargetState[VFOTAH_ERASE_STATE_ID] = VFOTAH_ERASE_STATE_IDLE;
      }
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vFotaH_vSwUpdMEraseModule */



/**********************************************************************************************************************
 * vFotaH_vSwUpdMVerifyModule
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMVerifyModule(P2CONST(uint8, AUTOMATIC, VFOTAH_APPL_VAR) VerifyData, uint16 VerifySize, vSwUpdM_ModuleHandleIdType ModuleHd)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;
  vSwUpdM_ModuleIdType moduleId;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHd);

  if (retVal == E_OK)
  {
    retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_VERIFYMODULE_STATE_ID);
    if (retVal == E_OK)
    {
      switch (vFotaH_SMCurrentState[VFOTAH_VERIFYMODULE_STATE_ID])
      {
      case (VFOTAH_VERIFYMODULE_STATE_IDLE) :
        {
          vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_OPENPARTITION_OPENED;
          /* #-- Open the inactive partition. */
          retVal = vSwUpdM_OpenPartition(VSWUPDM_PART_STATE_INACTIVE);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_VERIFYMODULE_OPENPARTITION_OPENED) :
        {
          vSwUpdM_ModuleIdType openedModuleId;
          vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
          retVal = vSwUpdM_GetOpenModuleId(&openedModuleId);

          if (retVal == E_OK)
          {
            /* #-- If a module is already opened then throw an error, otherwise open it. */
            if (openedModuleId == VSWUPDM_INVALID_ID)
            {
              vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_MODULE_OPENED;
              retVal = vSwUpdM_OpenModule(moduleId);

              if (retVal == E_OK)
              {
                retVal = VFOTAH_E_PENDING;
              }
            }
            else
            {
              retVal = E_NOT_OK;
            }
          }
      } break;

      case (VFOTAH_VERIFYMODULE_MODULE_OPENED) :
        {
          vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_MODULE_FINALIZED;
          /* #-- Finalize the module before it is verified. */
          retVal = vSwUpdM_FinalizeModule(moduleId);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
          else
          {
            vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
            vFotaH_SMCurrentState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_VERIFYMODULE_MODULE_FINALIZED) :
        {
          vSwUpdM_ProcessInfoType ProcessInfo;

          retVal = vSwUpdM_InitProcessInfo(&ProcessInfo);

          if (retVal == E_OK)
          {
            vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_VERIFIED;
            /* #-- Verify the module with either a CRC or a Signature. This is transparent and passed on as parameter. */
            vFotaH_InputData.DataPtr = &VerifyData[0];
            vFotaH_InputData.Length = VerifySize;
            ProcessInfo.InputData = &vFotaH_InputData;
            ProcessInfo.InputCount = 1u;
            ProcessInfo.OutputData = NULL_PTR;
            ProcessInfo.OutputCount = 0u;

            retVal = vSwUpdM_VerifyModule(moduleId, &ProcessInfo);

            if (retVal == E_OK)
            {
              retVal = VFOTAH_E_PENDING;
            }
            else
            {
              vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
              vFotaH_SMCurrentState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
              retVal = VFOTAH_E_PENDING;
            }
          }
          else
          {
            vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
            vFotaH_SMCurrentState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
            retVal = VFOTAH_E_PENDING;
          }
        } break;

        case (VFOTAH_VERIFYMODULE_VERIFIED) :
        {
          vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_VALIDATED;
          /* #-- Validate the module after verification. */
          retVal = vSwUpdM_ValidateModule(moduleId);

          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
          else
          {
            vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
            vFotaH_SMCurrentState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_ERROR_DETECTED;
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_VERIFYMODULE_VALIDATED) :
        {
          vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_MODULE_CLOSED;
          /* #-- We are finished, close the module again. */
          retVal = vSwUpdM_CloseModule(moduleId);

          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_VERIFYMODULE_MODULE_CLOSED) :
        {
          retVal = E_OK;
        } break;

      case (VFOTAH_VERIFYMODULE_ERROR_DETECTED) :
        {
          /* #-- We have detected an error, close the module for a safe state. */
          retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_VERIFYMODULE_STATE_ID, VFOTAH_VERIFYMODULE_ERROR_RESOLVED);
        } break;

      default :
        {
          retVal = E_NOT_OK;
        } break;
      }

      /* #-- In case of positive or negative result, we return to IDLE state. */
      if (retVal != VFOTAH_E_PENDING)
      {
        vFotaH_SMCurrentState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_STATE_IDLE;
        vFotaH_SMTargetState[VFOTAH_VERIFYMODULE_STATE_ID] = VFOTAH_VERIFYMODULE_STATE_IDLE;
      }
    }
  }

  return retVal;
  /* PRQA S 6030 3 */ /* MD_MSR_STCYC */
  /* PRQA S 6050 2 */ /* MD_MSR_STCAL */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_vSwUpdMVerifyModule */

/**********************************************************************************************************************
* vFotaH_vSwUpdMGetModuleIdByRange
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMGetModuleIdByRange(P2VAR(vSwUpdM_ModuleIdType, AUTOMATIC, VFOTAH_APPL_VAR) ModuleId, vFotaH_AddrType MemAddr, vFotaH_LengthType MemLength)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vSwUpdM_GetModuleIdByRange(ModuleId, MemAddr, MemLength);

  return retVal;
} /* vFotaH_vSwUpdMGetModuleIdByRange */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMPrepareDownload
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMPrepareDownload(vFotaH_AddrType MemAddr, vFotaH_LengthType MemLength, vSwUpdM_ProcessingOperationType Dfi)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  vSwUpdM_ModuleIdType pDSMModuleId = VSWUPDM_INVALID_ID;
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vSwUpdM_GetModuleIdByRange(&pDSMModuleId, MemAddr, MemLength);

  if (retVal == E_OK)
  {
    retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_PREPAREDOWNLOAD_STATE_ID);
    if (retVal == E_OK)
    {
      switch (vFotaH_SMCurrentState[VFOTAH_PREPAREDOWNLOAD_STATE_ID])
      {
      case (VFOTAH_PREPAREDOWNLOAD_STATE_IDLE) :
      {
        retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_PREPAREDOWNLOAD_STATE_ID, VFOTAH_PREPAREDOWNLOAD_MODULE_CLOSED);
        if (retVal == E_NOT_OK)
        {
          vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_MODULE_CLOSED;
          vFotaH_SMCurrentState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_MODULE_CLOSED;
        }
        retVal = VFOTAH_E_PENDING;
      } break;

      case (VFOTAH_PREPAREDOWNLOAD_MODULE_CLOSED) :
        {
          vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_OPENPARTITION_OPENED;
          /* #-- Open the inactive partition. */
          retVal = vSwUpdM_OpenPartition(VSWUPDM_PART_STATE_INACTIVE);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_PREPAREDOWNLOAD_OPENPARTITION_OPENED) :
        {
          vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_MODULE_OPENED;
          /* #-- Open the module that fits the memory range. */
          retVal = vSwUpdM_OpenModule(pDSMModuleId);
          if (retVal == E_OK)
          {
            retVal = VFOTAH_E_PENDING;
          }
        } break;

      case (VFOTAH_PREPAREDOWNLOAD_MODULE_OPENED) :
        {
          vSwUpdM_SegmentIdType segmentId;

          vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_SEGMENT_OPENED;

          /* #-- Request the segment at the given memory range. */
          retVal = vSwUpdM_GetSegmentIdByRange(
               &segmentId,
               (vSwUpdM_AddressType)MemAddr,
               (vSwUpdM_LengthType)MemLength);

          /* #-- If there is no segment, create a new one in this range. */
          if (retVal != E_OK)
          {
            vSwUpdM_SegmentInfoType segmentInfo;
            (void)vSwUpdM_InitSegmentInfo(&segmentInfo);
            segmentInfo.StartAddress = (vSwUpdM_AddressType)MemAddr;
            segmentInfo.Length = (vSwUpdM_LengthType)MemLength;
            segmentInfo.IsOverflowable = FALSE;
            segmentInfo.LengthHandling = VSWUPDM_LENGTH_HANDLING_FIXED;
      
            retVal = vSwUpdM_AddSegment(&segmentInfo);

            if (retVal == E_OK)
            {
              segmentId = segmentInfo.Id;
            }
            else
            {
              vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED;
              vFotaH_SMCurrentState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED;
              retVal = VFOTAH_E_PENDING;
            }
          }
          /* Otherwise, there is already a segment. */

          if (retVal == E_OK)
          {
            vSwUpdM_SegmentIdType openedSegmentId;

            retVal = vSwUpdM_GetOpenSegmentId(&openedSegmentId);

            /* #-- If the required segment is already opened, skip to open it.
             *     Otherwise, request to open it. */
            if ((retVal == E_OK) && ((openedSegmentId.DynamicSegmentId != VSWUPDM_INVALID_ID)
             || (openedSegmentId.StaticSegmentId != VSWUPDM_INVALID_ID)))
            {
              if ((openedSegmentId.DynamicSegmentId == segmentId.DynamicSegmentId)
                && (openedSegmentId.StaticSegmentId == segmentId.StaticSegmentId))
              {
                retVal = VFOTAH_E_PENDING;
              }
              else
              {
                retVal = vSwUpdM_OpenSegment(segmentId);
              }
            }
            else
            {
              retVal = vSwUpdM_OpenSegment(segmentId);
            }

            if (retVal == E_OK)
            {
              retVal = VFOTAH_E_PENDING;
            }
            else
            if (retVal != VFOTAH_E_PENDING)
            {
              vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED;
              vFotaH_SMCurrentState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED;
              retVal = VFOTAH_E_PENDING;
            }
            else
            {
              /* Concluding else */
            }
          }
        } break;

      case (VFOTAH_PREPAREDOWNLOAD_SEGMENT_OPENED) :
        {
          vSwUpdM_StreamInfoType streamInfo;

          vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_STREAM_STARTED;
          /* #-- Start the stream, pass the dfi on for data operation. */
          (void)vSwUpdM_InitStreamInfo(&streamInfo);

          streamInfo.Operation = Dfi;
          streamInfo.InputLength = 0u;
          retVal = vSwUpdM_StartStream(&streamInfo);
        
          if (retVal == E_OK)
          {
            vFotaH_DownloadInProgress = TRUE;
            retVal = VFOTAH_E_PENDING;
          }
          else
          {
            vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED;
            vFotaH_SMCurrentState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED;
            retVal = VFOTAH_E_PENDING;
          }
      } break;

      case (VFOTAH_PREPAREDOWNLOAD_STREAM_STARTED) :
        {
          retVal = E_OK;
        } break;

      case (VFOTAH_PREPAREDOWNLOAD_ERROR_DETECTED) :
        {
          /* #-- We have detected an error, close the module for a safe state. */
          retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_PREPAREDOWNLOAD_STATE_ID, VFOTAH_PREPAREDOWNLOAD_ERROR_RESOLVED);
        } break;

      default :
        {
          retVal = E_NOT_OK;
        } break;
      }
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMCurrentState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_STATE_IDLE;
      vFotaH_SMTargetState[VFOTAH_PREPAREDOWNLOAD_STATE_ID] = VFOTAH_PREPAREDOWNLOAD_STATE_IDLE;
    }
  }

  return retVal;
  /* PRQA S 6010 4 */ /* MD_MSR_STPTH */
  /* PRQA S 6030 3 */ /* MD_MSR_STCYC */
  /* PRQA S 6050 2 */ /* MD_MSR_STCAL */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_vSwUpdMPrepareDownload */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMTransferData
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMTransferData(P2VAR(vFotaH_DownloadDataType, AUTOMATIC, VFOTAH_VAR_NOINIT) DownloadDatap)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_TRANSFERDATA_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_TRANSFERDATA_STATE_ID])
    {
    case (VFOTAH_TRANSFERDATA_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_TRANSFERDATA_STATE_ID] = VFOTAH_TRANSFERDATA_WRITE_PENDING;
        /* #-- Process the stream data. */
        vFotaH_DownloadDatap = DownloadDatap;
        retVal = vSwUpdM_ProcessStreamData(DownloadDatap->BlockSize);

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
        else
        {
          vFotaH_SMTargetState[VFOTAH_TRANSFERDATA_STATE_ID] = VFOTAH_TRANSFERDATA_ERROR_DETECTED;
          vFotaH_SMCurrentState[VFOTAH_TRANSFERDATA_STATE_ID] = VFOTAH_TRANSFERDATA_ERROR_DETECTED;
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_TRANSFERDATA_WRITE_PENDING) :
      {
        retVal = E_OK;
      } break;

    case (VFOTAH_TRANSFERDATA_ERROR_DETECTED) :
      {
        /* #-- We have detected an error, close the module for a safe state. */
        retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_TRANSFERDATA_STATE_ID, VFOTAH_TRANSFERDATA_ERROR_RESOLVED);
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMCurrentState[VFOTAH_TRANSFERDATA_STATE_ID] = VFOTAH_TRANSFERDATA_STATE_IDLE;
      vFotaH_SMTargetState[VFOTAH_TRANSFERDATA_STATE_ID] = VFOTAH_TRANSFERDATA_STATE_IDLE;
    }
  }

  return retVal;
} /* vFotaH_vSwUpdMTransferData */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMFinalizeDownload
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMFinalizeDownload(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_FINALIZEDOWNLOAD_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID])
    {
    case (VFOTAH_FINALIZEDOWNLOAD_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_STREAM_END;

        /* #-- Request to terminate the stream. */
        retVal = vSwUpdM_EndStream();
        vFotaH_DownloadInProgress = FALSE;

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
        else
        {
          vFotaH_SMTargetState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED;
          vFotaH_SMCurrentState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED;
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_FINALIZEDOWNLOAD_STREAM_END) :
      {
        vSwUpdM_SegmentIdType openedSegmentId;
        vFotaH_SMTargetState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_SEGMENT_FINALIZED;

        /* #-- Get the currently opened segment and request to finalize it. */
        retVal = vSwUpdM_GetOpenSegmentId(&openedSegmentId);
        if ((retVal == E_OK) && ((openedSegmentId.DynamicSegmentId != VSWUPDM_INVALID_ID)
          || (openedSegmentId.StaticSegmentId != VSWUPDM_INVALID_ID)))
        {
          retVal = vSwUpdM_FinalizeSegment(openedSegmentId);
        }

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
        else
        {
          vFotaH_SMTargetState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED;
          vFotaH_SMCurrentState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED;
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_FINALIZEDOWNLOAD_SEGMENT_FINALIZED) :
      {
        vSwUpdM_SegmentIdType openedSegmentId;
        vFotaH_SMTargetState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_SEGMENT_CLOSED;

        /* #-- Get the currently opened segment and request to close it. */
        retVal = vSwUpdM_GetOpenSegmentId(&openedSegmentId);
        if ((retVal == E_OK) && ((openedSegmentId.DynamicSegmentId != VSWUPDM_INVALID_ID)
                              || (openedSegmentId.StaticSegmentId != VSWUPDM_INVALID_ID)))
        {
          retVal = vSwUpdM_CloseSegment(openedSegmentId);
        }

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
        else
        {
          vFotaH_SMTargetState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED;
          vFotaH_SMCurrentState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED;
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_FINALIZEDOWNLOAD_SEGMENT_CLOSED) :
      {
        vSwUpdM_ModuleIdType openedModuleId;
        vFotaH_SMTargetState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_MODULE_CLOSED;

        /* #-- Request to close the currently opened module. */
        retVal = vSwUpdM_GetOpenModuleId(&openedModuleId);
        if (retVal == E_OK)
        {
          if (openedModuleId != VSWUPDM_INVALID_ID)
          {
            retVal = vSwUpdM_CloseModule(openedModuleId);
          }
          else
          {
            vFotaH_SMCurrentState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_MODULE_CLOSED;
          }
        }

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_FINALIZEDOWNLOAD_MODULE_CLOSED) :
      {
        retVal = E_OK;
      } break;

    case (VFOTAH_FINALIZEDOWNLOAD_ERROR_DETECTED) :
      {
        /* #-- Request to close the currently opened module if it is still open in an error case. */
        retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_FINALIZEDOWNLOAD_STATE_ID, VFOTAH_FINALIZEDOWNLOAD_ERROR_RESOLVED);
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMCurrentState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_STATE_IDLE;
      vFotaH_SMTargetState[VFOTAH_FINALIZEDOWNLOAD_STATE_ID] = VFOTAH_FINALIZEDOWNLOAD_STATE_IDLE;
    }
  }

  return retVal;
  /* PRQA S 6030 2 */ /* MD_MSR_STCYC */
  /* PRQA S 6050 1 */ /* MD_MSR_STCAL */
} /* vFotaH_vSwUpdMFinalizeDownload */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMCheckFinalizeSegment
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMCheckFinalizeSegment(vSwUpdM_AddressType SegmentAddress)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_FINALIZESEGMENT_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_FINALIZESEGMENT_STATE_ID])
    {
    case (VFOTAH_FINALIZESEGMENT_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_OPENPARTITION_OPENED;
        /* #-- We want to do operation on inactive partition. */
        retVal = vSwUpdM_OpenPartition(VSWUPDM_PART_STATE_INACTIVE);
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;


    case (VFOTAH_FINALIZESEGMENT_OPENPARTITION_OPENED) :
      {
        vSwUpdM_ModuleIdType moduleId;

        vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_OPENMODULE_OPENED;
        /* #-- Open the module, this is required for segment operation. */
        retVal = vSwUpdM_GetModuleIdByRange(&moduleId, SegmentAddress, 1u);

        if (retVal == E_OK)
        {
          retVal = vSwUpdM_OpenModule(moduleId);
        }

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;


    case (VFOTAH_FINALIZESEGMENT_OPENMODULE_OPENED) :
      {
        vSwUpdM_SegmentIdType segmentId;

        vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_SEGMENT_FINALIZED;
        /* #-- Finalize the segment of the selected range. */
        retVal = vSwUpdM_GetSegmentIdByRange(&segmentId, SegmentAddress, 1u);
        if (retVal == E_OK)
        {
          vSwUpdM_SegmentInfoType segmentInfo;

          /* #-- Get the segment info to determine segment boundaries. */
          retVal = vSwUpdM_GetSegmentInfo(&segmentInfo, segmentId);
          if (retVal == E_OK)
          {
            /* #-- If the segment is filled completely we have to start finalizing the segment here as this is missing. */
            if (SegmentAddress == segmentInfo.EndAddress)
            {
              retVal = vSwUpdM_FinalizeSegment(segmentId);

              if (retVal == E_OK)
              {
                retVal = VFOTAH_E_PENDING;
              }
              else
              {
                vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_ERROR_DETECTED;
                vFotaH_SMCurrentState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_ERROR_DETECTED;
                retVal = VFOTAH_E_PENDING;
              }
            }
            else
            {
              vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_SEGMENT_CLOSED;
              vFotaH_SMCurrentState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_SEGMENT_CLOSED;
              retVal = VFOTAH_E_PENDING;
            }
          }
        }

      } break;

    case (VFOTAH_FINALIZESEGMENT_SEGMENT_FINALIZED) :
      {
        vSwUpdM_SegmentIdType openedSegmentId;
        vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_SEGMENT_CLOSED;

        /* #-- Get the currently opened segment and request to close it. */
        retVal = vSwUpdM_GetOpenSegmentId(&openedSegmentId);
        if ((retVal == E_OK) && ((openedSegmentId.DynamicSegmentId != VSWUPDM_INVALID_ID)
                              || (openedSegmentId.StaticSegmentId != VSWUPDM_INVALID_ID)))
        {
          retVal = vSwUpdM_CloseSegment(openedSegmentId);
        }

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
        else
        {
          vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_ERROR_DETECTED;
          vFotaH_SMCurrentState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_ERROR_DETECTED;
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_FINALIZESEGMENT_SEGMENT_CLOSED) :
      {
        vSwUpdM_ModuleIdType openedModuleId;
        vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_MODULE_CLOSED;

        /* #-- Request to close the currently opened module. */
        retVal = vSwUpdM_GetOpenModuleId(&openedModuleId);
        if (retVal == E_OK)
        {
          if (openedModuleId != VSWUPDM_INVALID_ID)
          {
            retVal = vSwUpdM_CloseModule(openedModuleId);
          }
          else
          {
            vFotaH_SMCurrentState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_MODULE_CLOSED;
          }
        }

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_FINALIZESEGMENT_MODULE_CLOSED) :
      {
        retVal = E_OK;
      } break;

    case (VFOTAH_FINALIZESEGMENT_ERROR_DETECTED) :
      {
        /* #-- Request to close the currently opened module if it is still open in an error case. */
        retVal = vFotaH_vSwUpdMErrorCloseModule(VFOTAH_FINALIZESEGMENT_STATE_ID, VFOTAH_FINALIZESEGMENT_ERROR_RESOLVED);
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMCurrentState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_STATE_IDLE;
      vFotaH_SMTargetState[VFOTAH_FINALIZESEGMENT_STATE_ID] = VFOTAH_FINALIZESEGMENT_STATE_IDLE;
    }
  }

  return retVal;
  /* PRQA S 6030 3 */ /* MD_MSR_STCYC */
  /* PRQA S 6050 2 */ /* MD_MSR_STCAL */
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_vSwUpdMCheckFinalizeSegment */



/**********************************************************************************************************************
 * vFotaH_vSwUpdMSwitchBank
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMSwitchBank(vSwUpdM_PartitionStateType PartitionState)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_SWITCHBANK_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_SWITCHBANK_STATE_ID])
    {
    case (VFOTAH_SWITCHBANK_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_SWITCHBANK_STATE_ID] = VFOTAH_SWITCHBANK_OPENPARTITION_OPENED;
        /* #-- Open the selected partition. */
        retVal = vSwUpdM_OpenPartition(PartitionState);
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_SWITCHBANK_OPENPARTITION_OPENED) :
      {
        vSwUpdM_ProcessInfoType processInfo;
        vFotaH_SMTargetState[VFOTAH_SWITCHBANK_STATE_ID] = VFOTAH_SWITCHBANK_PARTITION_CHECKED;
        /* #-- Check the partition consistency. */
        (void)vSwUpdM_InitProcessInfo(&processInfo);
        retVal = vSwUpdM_CheckPartitionConsistency(&processInfo);

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_SWITCHBANK_PARTITION_CHECKED) :
      {
        vFotaH_SMTargetState[VFOTAH_SWITCHBANK_STATE_ID] = VFOTAH_SWITCHBANK_BANK_SWITCHED;
        /* #-- And perform the switch to the selected partition (inactive/backup). */
        retVal = vSwUpdM_SwapActivePartition();
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_SWITCHBANK_BANK_SWITCHED) :
      {
        retVal = E_OK;
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMCurrentState[VFOTAH_SWITCHBANK_STATE_ID] = VFOTAH_SWITCHBANK_STATE_IDLE;
      vFotaH_SMTargetState[VFOTAH_SWITCHBANK_STATE_ID] = VFOTAH_SWITCHBANK_STATE_IDLE;
    }
  }

  return retVal;
} /* vFotaH_vSwUpdMSwitchBank */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMReadRange
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMReadRange(P2VAR(uint8, AUTOMATIC, VFOTAH_APPL_VAR) target, uint32 address, uint32 length, vSwUpdM_PartitionStateType psType)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_READRANGE_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_READRANGE_STATE_ID])
    {
    case (VFOTAH_READRANGE_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_READRANGE_STATE_ID] = VFOTAH_READRANGE_OPENPARTITION_OPENED;
        /* #-- Open the selected partition. */
        retVal = vSwUpdM_OpenPartition(psType);

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_READRANGE_OPENPARTITION_OPENED) :
      {
        vFotaH_SMTargetState[VFOTAH_READRANGE_STATE_ID] = VFOTAH_READRANGE_DATA_READ;

        /* #-- Read the requested range from flash. */
        retVal = vSwUpdM_ReadRange(target, address, length);

        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_READRANGE_DATA_READ) :
      {
        retVal = E_OK;
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMCurrentState[VFOTAH_READRANGE_STATE_ID] = VFOTAH_READRANGE_STATE_IDLE;
      vFotaH_SMTargetState[VFOTAH_READRANGE_STATE_ID] = VFOTAH_READRANGE_STATE_IDLE;
    }
  }

  return retVal;
} /* vFotaH_vSwUpdMReadRange */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMGetModuleInfo
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMGetModulePartitionInfo(P2VAR(vSwUpdM_ModuleInfoType, AUTOMATIC, VFOTAH_APPL_VAR) ModuleInfo, P2VAR(vSwUpdM_PartitionInfoType, AUTOMATIC, VFOTAH_APPL_VAR) PartitionInfo, vSwUpdM_ModuleHandleIdType ModuleHd, vSwUpdM_PartitionStateType PartitionState)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;
  vSwUpdM_ModuleIdType moduleId;

  /* ----- Implementation ---------------------------------------------------------------------- */
  retVal = vFotaH_vSwUpdMEntryCheck(VFOTAH_GETMODULEINFO_STATE_ID);
  if (retVal == E_OK)
  {
    switch (vFotaH_SMCurrentState[VFOTAH_GETMODULEINFO_STATE_ID])
    {
    case (VFOTAH_GETMODULEINFO_STATE_IDLE) :
      {
        vFotaH_SMTargetState[VFOTAH_GETMODULEINFO_STATE_ID] = VFOTAH_GETMODULEINFO_OPENPARTITION_OPENED;
        /* #-- Open the selected partition. */
        retVal = vSwUpdM_OpenPartition(PartitionState);
        if (retVal == E_OK)
        {
          retVal = VFOTAH_E_PENDING;
        }
      } break;

    case (VFOTAH_GETMODULEINFO_OPENPARTITION_OPENED) :
      {
        /* #-- Retrieve the requested information. */
        retVal = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHd);
        if (retVal == E_OK)
        {
          retVal = vSwUpdM_GetModuleInfo(ModuleInfo, moduleId);

          if (retVal == E_OK)
          {
            retVal = vSwUpdM_GetPartitionInfo(PartitionInfo, PartitionState);
          }
        }
      } break;

    default :
      {
        retVal = E_NOT_OK;
      } break;
    }

    /* #-- In case of positive or negative result, we return to IDLE state. */
    if (retVal != VFOTAH_E_PENDING)
    {
      vFotaH_SMTargetState[VFOTAH_GETMODULEINFO_STATE_ID] = VFOTAH_GETMODULEINFO_STATE_IDLE;
      vFotaH_SMCurrentState[VFOTAH_GETMODULEINFO_STATE_ID] = VFOTAH_GETMODULEINFO_STATE_IDLE;
    }
  }

  return retVal;
} /* vFotaH_vSwUpdMGetModuleInfo */


/**********************************************************************************************************************
vFotaH_vSwUpdMHasActivePartitionLaterSoftware
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMHasActivePartitionLaterSoftware(P2VAR(boolean, AUTOMATIC, VFOTAH_VAR_NOINIT) LaterSW)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  Std_ReturnType vSwUpdM_RetVal_active;
  Std_ReturnType vSwUpdM_RetVal_inactive;
  Std_ReturnType vSwUpdM_RetVal_backup;
  vSwUpdM_PartitionInfoType activePartInfo;
  vSwUpdM_PartitionInfoType inactivePartInfo;
  vSwUpdM_PartitionInfoType backupPartInfo;

  /* ----- Implementation ---------------------------------------------------------------------- */
  /* #-- Get info of active, backup and inactive partition. */
  vSwUpdM_RetVal_active = vSwUpdM_GetPartitionInfo(&activePartInfo, VSWUPDM_PART_STATE_ACTIVE);
  vSwUpdM_RetVal_inactive = vSwUpdM_GetPartitionInfo(&inactivePartInfo, VSWUPDM_PART_STATE_INACTIVE);
  vSwUpdM_RetVal_backup = vSwUpdM_GetPartitionInfo(&backupPartInfo, VSWUPDM_PART_STATE_BACKUP_TARGET);

  if (vSwUpdM_RetVal_active == E_OK)
  {
    /* #-- If the backup partition is available, the active partition must have a later software revision than the
    *       backup partition after a successful switch.
    *     Otherwise if the inactive partition is valid, the active partition must have a later software revision than
    *       the inactive partition after a successful switch.
    *     Otherwise, error occurred. */
    if (vSwUpdM_RetVal_backup == E_OK)
    {
      if (activePartInfo.Revision > backupPartInfo.Revision)
      {
        LaterSW[0] = TRUE;
      }
      else
      {
        LaterSW[0] = FALSE;
      }
    }
    else if (vSwUpdM_RetVal_inactive == E_OK)
    {
      if (activePartInfo.Revision > inactivePartInfo.Revision)
      {
        LaterSW[0] = TRUE;
      }
      else
      {
        LaterSW[0] = FALSE;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
} /* vFotaH_vSwUpdMHasActivePartitionLaterSoftware */


/**********************************************************************************************************************
vFotaH_vSwUpdMIsBasicUseCase
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(boolean, VFOTAH_CODE) vFotaH_vSwUpdMIsBasicUseCase(void)
{
  /* ----- Local Variables ------------------------------------------------ */
  vSwUpdM_PartitionInfoType partInfo;
  boolean retVal;

  /* ----- Implementation ------------------------------------------------- */
  /* #-- If vSwUpdM_GetPartitionInfo to get the backup partition returns E_OK, the extended use case is active.
  *     Otherwise, the basic use case is active. */
  retVal = vSwUpdM_GetPartitionInfo(&partInfo, VSWUPDM_PART_STATE_BACKUP_TARGET);

  if (retVal == E_OK)
  {
    retVal = FALSE;
  }
  else
  {
    retVal = TRUE;
  }

  return retVal;
} /* vFotaH_vSwUpdMIsBasicUseCase */


/**********************************************************************************************************************
vFotaH_vSwUpdMGetNumberOfRegionsOfModule
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMGetNumberOfRegionsOfModule(P2VAR(uint32, AUTOMATIC, VFOTAH_VAR_NOINIT) NumberOfRegions, vSwUpdM_ModuleHandleIdType ModuleHd)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal;
  vSwUpdM_ModuleIdType moduleId;

  /* ----- Implementation ------------------------------------------------- */
  retVal = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHd);

  if (retVal == E_OK)
  {
    retVal = vSwUpdM_GetNumberOfRegionsOfModule(NumberOfRegions, moduleId);
  }

  return retVal;
} /* vFotaH_vSwUpdMGetNumberOfRegionsOfModule */


/**********************************************************************************************************************
vFotaH_vSwUpdMGetNumberOfRegionsOfModule
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMGetRegionInfoOfId(P2VAR(vSwUpdM_RegionInfoType, AUTOMATIC, VFOTAH_VAR_NOINIT) RegionInfo, vSwUpdM_ModuleHandleIdType ModuleHd, uint16 Index)
{
  /* ----- Local Variables ------------------------------------------------ */
  Std_ReturnType retVal;
  vSwUpdM_RegionIdType regionId;
  vSwUpdM_ModuleIdType moduleId;

  /* ----- Implementation ------------------------------------------------- */
  retVal = vSwUpdM_GetModuleIdByHandle(&moduleId, ModuleHd);

  if (retVal == E_OK)
  {
    retVal = vSwUpdM_GetRegionIdOfModuleByIndex(&regionId, moduleId, Index);

    if (retVal == E_OK)
    {
      retVal = vSwUpdM_GetRegionInfo(RegionInfo, regionId);
    }
  }

  return retVal;
} /* vFotaH_vSwUpdMGetNumberOfRegionsOfModule */



/**********************************************************************************************************************
* vFotaH_vSwUpdMCopyStreamData
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(BufReq_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMCopyStreamData(
  P2CONST(vSwUpdM_StreamDataInfoType, AUTOMATIC, VFOTAH_APPL_CONST) Info,
  P2VAR(vSwUpdM_StreamLengthType, AUTOMATIC, VFOTAH_APPL_DATA) AvailableDataPtr)
{
  /* ----- Local Variables ------------------------------------------------ */
  vSwUpdM_StreamLengthType i;
  vFotaH_ErrorCodeType errorId = VFOTAH_E_NO_ERROR;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Development Error Report --------------------------------------- */
# if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (vFotaH_InitializationSM_GetState() != VFOTAH_INIT_STATE_INITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
  if ((AvailableDataPtr == NULL_PTR)
    || (Info == NULL_PTR)
    || (Info->DataPtr == NULL_PTR)
    || (vFotaH_DownloadDatap == NULL_PTR))
  {
    errorId = VFOTAH_E_INV_POINTER;
  }
  else
# endif
  /* ----- Implementation ------------------------------------------------- */
  {
    vSwUpdM_StreamLengthType streamLength = Info->Length;
    vSwUpdM_StreamLengthType streamOffset = Info->Offset;

    /* #-- Copy data and calculating remaining length */
    if (vFotaH_DownloadDatap->BlockSize >= (streamLength + streamOffset))
    {
      for (i = 0u; i < streamLength; i++)
      {
        Info->DataPtr[i] = vFotaH_DownloadDatap->DcmSourceBufferPtr[i + streamOffset];
      }
      vFotaH_DownloadDatap->RemainingBlockSize = (vFotaH_DownloadDatap->BlockSize - (streamLength + streamOffset));
      AvailableDataPtr[0] = vFotaH_DownloadDatap->RemainingBlockSize;

      retVal = BUFREQ_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif

  return retVal;
} /* vFotaH_vSwUpdMCopyStreamData */


/**********************************************************************************************************************
* vFotaH_vSwUpdMConfirmation
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(void, VFOTAH_CODE) vFotaH_vSwUpdMConfirmation(
  vSwUpdM_ServiceIdType ConfirmedServiceId,
  Std_ReturnType Result) /* PRQA S 1505 */ /* MD_MSR_Rule8.7 */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least i;
  vFotaH_ErrorCode errorId = VFOTAH_E_NO_ERROR;
  vFotaH_StateType state = vFotaH_InitializationSM_GetState();

  /* ----- Development Error Report --------------------------------------- */
# if (VFOTAH_DEV_ERROR_DETECT == STD_ON)
  if (state == VFOTAH_INIT_STATE_UNINITIALIZED)
  {
    errorId = VFOTAH_E_NOT_INITIALIZED;
  }
  else
# endif
    /* ----- Implementation ----------------------------------------------- */
  {
    if ((state == VFOTAH_INIT_STATE_INIT_PENDING)
     || (state == VFOTAH_INIT_STATE_SHUTDOWN_PENDING))
    {
      if (ConfirmedServiceId == VSWUPDM_SID_START)
      {
        vFotaH_State_vSwUpdMInitNotification();
      }
      else
      if (ConfirmedServiceId == VSWUPDM_SID_SHUTDOWN)
      {
        if (vFotaH_RestartFlag == VFOTAH_PERFORM_RESTART)
        {
          (void)vSwUpdM_Start();
        }
      }
      else
      {
        /* Intentionally left empty */
      }
    }
    else
    {
      /* #-- Check if any SM needs to be moved forward due to positive confirmation. */
      for (i = 0u; i < VFOTAH_NUMBER_OF_SM; i++)
      {
        if (vFotaH_SMCurrentState[i] != vFotaH_SMTargetState[i])
        {
          if (Result == E_OK)
          {
            vFotaH_SMCurrentState[i] = vFotaH_SMTargetState[i];
          }
          else
          {
            vFotaH_SMCurrentState[i] = vFotaH_SMErrorState[i];
            vFotaH_SMTargetState[i] = vFotaH_SMErrorState[i];
          }
          break;
        }
      }
    }
  }

  vFotaH_Appl_vSwUpdMConfirmation(ConfirmedServiceId, Result);

  /* ----- Development Error Report --------------------------------------- */
# if (VFOTAH_DEV_ERROR_REPORT == STD_ON)
  if (errorId != VFOTAH_E_NO_ERROR)
  {
    vFotaH_DetReportError(VFOTAH_SID_CONFIRMATION, errorId);
  }
# else
  VFOTAH_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e438 */
# endif
  /* PRQA S 6080 1 */ /* MD_MSR_STMIF */
} /* vFotaH_vSwUpdMConfirmation */

/**********************************************************************************************************************
* vFotaH_vSwUpdMReset
**********************************************************************************************************************/
/*!
*
* Internal comment removed.
 *
 *
*/
FUNC(void, VFOTAH_CODE) vFotaH_vSwUpdMReset(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8_least i;

  /* ----- Implementation ---------------------------------------------------------------------- */
  for (i = 0u; i < VFOTAH_NUMBER_OF_SM; i++)
  {
    /* Initialize to IDLE */
    vFotaH_SMCurrentState[i] = VFOTAH_ANY_STATE_IDLE;
    vFotaH_SMTargetState[i] = VFOTAH_ANY_STATE_IDLE;
  }
} /* vFotaH_vSwUpdMReset */

/**********************************************************************************************************************
 * vFotaH_vSwUpdMInit
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_vSwUpdMInit(void)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  uint8_least i;

  /* ----- Implementation ---------------------------------------------------------------------- */
  for (i = 0u; i < VFOTAH_NUMBER_OF_SM; i++)
  {
    /* Initialize to IDLE */
    vFotaH_SMCurrentState[i] = VFOTAH_ANY_STATE_IDLE;
    vFotaH_SMTargetState[i] = VFOTAH_ANY_STATE_IDLE;
  }

  vFotaH_DownloadInProgress = FALSE;
  vFotaH_RestartFlag = VFOTAH_PERFORM_RESTART;
} /* vFotaH_vSwUpdMInit */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMShutdown
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, VFOTAH_CODE) vFotaH_vSwUpdMShutdown(uint8 RestartSelect)
{
  /* ----- Local Variables --------------------------------------------------------------------- */
  Std_ReturnType retVal;
  /* ----- Implementation ---------------------------------------------------------------------- */

  vFotaH_DownloadInProgress = FALSE;
  vFotaH_RestartFlag = RestartSelect;
  retVal = vSwUpdM_Shutdown();

  return retVal;
} /* vFotaH_vSwUpdMShutdown */


/**********************************************************************************************************************
 * vFotaH_vSwUpdMResetDownloadInProgress
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
FUNC(void, VFOTAH_CODE) vFotaH_vSwUpdMResetDownloadInProgress(void)
{
  /* ----- Implementation ---------------------------------------------------------------------- */
  if (vFotaH_DownloadInProgress == TRUE)
  {
    vFotaH_State_vSwUpdMInitRestart();
    (void)vFotaH_vSwUpdMShutdown(VFOTAH_PERFORM_RESTART);
  }
} /* vFotaH_vSwUpdMResetDownloadInProgress */

#define VFOTAH_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */ /*lint -e451 */

/**********************************************************************************************************************
 *  END OF FILE: vFotaH_vSwUpdM.c
 *********************************************************************************************************************/
