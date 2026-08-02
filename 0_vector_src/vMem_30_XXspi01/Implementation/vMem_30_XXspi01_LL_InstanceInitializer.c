/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  vMem_30_XXspi01_LL_InstanceInitializer.c
 *        \brief  -
 *
 *      \details  -
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_LL_INSTANCEINITIALIZER

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vMem_30_XXspi01_LL_InstanceInitializer.h"
#include "vMem_30_XXspi01_LL_Cbk_Int.h"
#include "vMem_30_XXspi01_LL_FlsCmdSeqBuilder.h"
#include "vMem_30_XXspi01_LL_FlsCmdSeqExecuter.h"
#include "vMem_30_XXspi01_LL_InstanceAccess_Shared.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if !defined(VMEM_30_XXSPI01_LOCAL) /* COV_VMEM_30_XXSPI01_COMPATIBILITY */
#define VMEM_30_XXSPI01_LOCAL static
#endif

/*! Timeout counter init value. */
#define VMEM_LL_INSTANCEINITIALIZER_TIMEOUT_THRESHOLD     (3u)

/*! This enum specifies all possible states of the instance specific initialization. */
typedef enum
{
  VMEM_30_XXSPI01_INSTANCE_UNINIT = 0u, VMEM_30_XXSPI01_INSTANCE_INIT
} vMem_30_XXspi01_InstanceInitResultType;

/*! Internal sub-"state machine" type to indicate the progress of the Hw initialization. */
typedef enum
{
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_IDLE = 0u,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_JEDEC_ID,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_ENABLE_4BYTE_ADDR_MODE,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_4BYTE_ADDR_MODE,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_HYBRID_SECTOR_LAYOUT,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_CONFIGURE_HYBRID_SECTOR_LAYOUT,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_HYBRID_SECTOR_LAYOUT,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_QUAD_SPI_MODE,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_ENABLE_QUAD_SPI_MODE,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_QUAD_SPI_MODE,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_DUMMY_CYCLES,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_CONFIG_DUMMY_CYCLES,
  VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_DUMMY_CYCLES
} vMem_30_XXspi01_InstanceInitializer_ProgressType;

/*! This struct merges all instance specific parameters regarding their initialization status. */
typedef struct
{
  vMem_30_XXspi01_InstanceIdType InstanceId;
  vMem_30_XXspi01_InstanceInitResultType InitStatus;
  vMem_30_XXspi01_InstanceInitializer_ProgressType InitProgress;
  vMem_30_XXspi01_MemSectorLengthOfvMemInstanceType CurrentCheckSectorIndex; /*! This parameter specifies the currently checked sector. */
  vMem_30_XXspi01_MemSectorLengthOfvMemInstanceType LastCheckSectorIndex; /*! This parameter specifies last sector index belonging to this vMemInstance. */
  uint8 InitTimeoutCounter; /*! Specifies the number of attempts to initialize the external flash device. */
  vMem_30_XXspi01_NumberOfDiesOfvMemInstanceType CurrentCheckDie; /*! Specifies the currently checked die. */
  vMem_30_XXspi01_NumberOfDiesOfvMemInstanceType LastCheckDie; /*! Specifies the total number of dies. */
} vMem_30_XXspi01_InstanceInitStateType;
typedef P2VAR(vMem_30_XXspi01_InstanceInitStateType, AUTOMATIC, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_InstanceInitStatePtrType;

/*********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_DeviceIdType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_DeviceId[vMem_30_XXspi01_GetSizeOfvMemInstance()];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_BUFFER
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* According to [SWS_Spi_00355] and [SWS_Spi_00437] each of these data buffers must be 32 bit aligned. Therefore, the size is initialized with VMEM_30_XXSPI01_32BIT_ALIGNMENT (4u). */
/*! Defines a buffer for each configured flash device to store the content of read device registers. */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_InitRegisterDataBuffers[vMem_30_XXspi01_GetSizeOfvMemInstance()][VMEM_30_XXSPI01_32BIT_ALIGNMENT];

VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_SpiDataType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_JedecIdBufferPtr[vMem_30_XXspi01_GetSizeOfvMemInstance()][VMEM_30_XXSPI01_32BIT_ALIGNMENT];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_BUFFER
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define VMEM_30_XXSPI01_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Indicates the initialization status of each instance. */
VMEM_30_XXSPI01_LOCAL VAR(vMem_30_XXspi01_InstanceInitStateType, VMEM_30_XXSPI01_VAR) vMem_30_XXspi01_InstanceInitState[vMem_30_XXspi01_GetSizeOfvMemInstance()];

#define VMEM_30_XXSPI01_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VMEM_30_XXSPI01_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ReadJedecId()
 *********************************************************************************************************************/
/*! \brief        Reads the flash device's JEDEC ID.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ReadJedecId(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_CheckPresenceOfJedecId()
 *********************************************************************************************************************/
/*! \brief        Checks whether the previously read JEDEC ID matches the JEDEC ID of one of the configured devices.
 *  \details      If the read JEDEC ID matches, the configuration of the 4 Byte address mode is triggered.
 *                Otherwise, the job failed.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_CheckPresenceOfJedecId(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Initiate4ByteAddressModeConfig()
 *********************************************************************************************************************/
/*! \brief        Initiates the configuration of the 4 Byte address mode.
 *  \details      Initiates the configuration of the 4 Byte address mode if required. If not required, triggers
 *                the configuration of the hybrid sector layout.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Initiate4ByteAddressModeConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Enable4ByteAddressMode()
 *********************************************************************************************************************/
/*! \brief        Enables the 4 Byte address mode.
 *  \details      Transmits the Flash command to enable the 4 Byte address mode to the external device.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Enable4ByteAddressMode(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Read4ByteAddrModeRegister()
 *********************************************************************************************************************/
/*! \brief        Sets up the FLash command sequence to read the 4 Byte address mode register.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Read4ByteAddrModeRegister(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Check4ByteAddressModeEnabled()
 *********************************************************************************************************************/
/*! \brief        Checks if the 4 Byte address mode is enabled.
 *  \details      In case of multi-die devices this check is performed for every configured sector batch of the external
 *                Flash device.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Check4ByteAddressModeEnabled(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitiateHybridSectorLayoutConfig()
 *********************************************************************************************************************/
/*! \brief        Initiates the configuration of the hybrid sector layout.
 *  \details      If configuration is required, reads the configuration register of the hybrid sector layout.
 *                If configuration is not required, triggers the configuration of the Quad Spi mode.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitiateHybridSectorLayoutConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitialReadHybridSectorLayoutReg()
 *********************************************************************************************************************/
/*! \brief        Initially reads the hybrid sector layout register to retrieve the current value of the register.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitialReadHybridSectorLayoutReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ConfigureHybridSectorLayout()
 *********************************************************************************************************************/
/*! \brief        Configures the hybrid sector layout for the currently processed instance.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ConfigureHybridSectorLayout(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ReadBackHybridSectorLayoutReg()
 *********************************************************************************************************************/
/*! \brief        Reads the hybrid sector layout register to check if the configuration succeeded.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ReadBackHybridSectorLayoutReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_CheckHybridSectorLayout()
 *********************************************************************************************************************/
/*! \brief        Checks if the configuration of the hybrid sector layout succeeded.
 *  \details      If the configuration of the hybrid sector layout succeeded, the configuration of the Quad SPI mode is
 *                triggered. Otherwise, the initialization failed.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_CheckHybridSectorLayout(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitiateQuadSpiModeConfig()
 *********************************************************************************************************************/
/*! \brief        Initiates the configuration of the Quad SPI mode.
 *  \details      If configuration is required, reads the configuration register of the Quad SPI mode feature.
 *                If configuration is not required, triggers the configuration of the dummy cycles.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitiateQuadSpiModeConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitialReadQuadSpiModeReg()
 *********************************************************************************************************************/
/*! \brief        Initially read the value of the configuration register of the Quad SPI feature.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitialReadQuadSpiModeReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_EnableQuadSpiMode()
 *********************************************************************************************************************/
/*! \brief        Writes to the Quad SPI Mode register to enable the Quad SPI mode.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_EnableQuadSpiMode(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ReadBackQuadSpiModeReg()
 *********************************************************************************************************************/
/*! \brief        Reads the configuration register of the Quad SPI mode feature.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ReadBackQuadSpiModeReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_CheckQuadSpiMode()
 *********************************************************************************************************************/
/*! \brief        Checks if the Quad SPI mode was successfully enabled.
 *  \details      If the configuration of the Quad SPI mode succeeded, the configuration of the dummy cycles is triggered.
 *                Otherwise, the initialization failed.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_CheckQuadSpiMode(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitiateDummyCycleConfig()
 *********************************************************************************************************************/
/*! \brief        Initiates the configuration of the dummy cycles.
 *  \details      If configuration is required, reads the dummy cycle configuration register.
 *                If configuration is not required, the overall initialization is finished.
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitiateDummyCycleConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitialReadDummyCycleConfig()
 *********************************************************************************************************************/
/*! \brief        Initially reads the value of the dummy cycle configuration register.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitialReadDummyCycleConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_GetBitmaskShiftOffset()
 *********************************************************************************************************************/
/*! \brief        This function returns the shift offset of the given bitmask.
 *  \details      -
 *  \param[in]    bitmask         Bitmask which shall be used during register access. The value must not be 0.
 *  \return       Shift offset value
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(uint32, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_GetBitmaskShiftOffset(uint32 bitmask);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ConfigureDummyCycleSettings()
 *********************************************************************************************************************/
/*! \brief        Writes to the dummy cycle configuration register to enable the Quad SPI mode.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ConfigureDummyCycleSettings(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ReadBackDummyCycleReg()
 *********************************************************************************************************************/
/*! \brief        Reads the dummy cycle configuration register.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ReadBackDummyCycleReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_CheckDummyCycleConfig()
 *********************************************************************************************************************/
/*! \brief        Checks if the dummy cycles were successfully configured.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_CheckDummyCycleConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitHwFinish()
 *********************************************************************************************************************/
/*! \brief        Resets the InstanceInitializer's state machine and sets the instance's init result to OK.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitHwFinish(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed()
 *********************************************************************************************************************/
/*! \brief        Resets the InstanceInitializer's state machine and sets the instance's init result to FAILED.
 *  \details      -
 *  \param[in]    processedInitializerInstance       Pointer to the currently processed instance.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *********************************************************************************************************************/
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance);

/*********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ReadJedecId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ReadJedecId(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readJedecIdSequencePtr;

  readJedecIdSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetJedecIdSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      processedInitializerInstance->InstanceId, vMem_30_XXspi01_JedecIdBufferPtr[processedInitializerInstance->InstanceId]);

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readJedecIdSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_JEDEC_ID; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, readJedecIdSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_ReadJedecId */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_CheckPresenceOfJedecId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_CheckPresenceOfJedecId(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId;
  boolean matchingDeviceFound = FALSE;
  vMem_30_XXspi01_InstanceIdType instanceId = processedInitializerInstance->InstanceId;

  for (deviceId = 0; deviceId < vMem_30_XXspi01_GetSizeOfvMemDeviceConfig(); deviceId++)
  {
    if ((vMem_30_XXspi01_LL_CfgDevice_GetManufacturerId(deviceId)
        == vMem_30_XXspi01_JedecIdBufferPtr[instanceId][0])
        && (vMem_30_XXspi01_LL_CfgDevice_GetMemoryTypeId(deviceId)
            == vMem_30_XXspi01_JedecIdBufferPtr[instanceId][1])
        && (vMem_30_XXspi01_LL_CfgDevice_GetMemoryDensityId(deviceId)
            == vMem_30_XXspi01_JedecIdBufferPtr[instanceId][2]))
    {
      vMem_30_XXspi01_DeviceId[instanceId] = deviceId; /* SBSW_vMem_30_XXspi01_WriteToArrayJedecIdBufferPtr */
      matchingDeviceFound = TRUE;
      break;
    }
  }

  if(matchingDeviceFound == TRUE)
  {
    vMem_30_XXspi01_LL_InstanceInitializer_Initiate4ByteAddressModeConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }

} /* vMem_30_XXspi01_LL_InstanceInitializer_CheckPresenceOfJedecId */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Initiate4ByteAddressModeConfig()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Initiate4ByteAddressModeConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  if (vMem_30_XXspi01_LL_CfgDevice_Is4ByteAddressModeEnabled(vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId]))
  {
    processedInitializerInstance->InitTimeoutCounter = VMEM_LL_INSTANCEINITIALIZER_TIMEOUT_THRESHOLD; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
    vMem_30_XXspi01_LL_InstanceInitializer_Enable4ByteAddressMode(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitiateHybridSectorLayoutConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }

} /* vMem_30_XXspi01_LL_InstanceInitializer_Initiate4ByteAddressModeConfig */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Enable4ByteAddressMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Enable4ByteAddressMode(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType enable4ByteAddrModeSequencePtr;

  enable4ByteAddrModeSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetEnable4ByteAddressModeSequence(
      processedInitializerInstance->InstanceId, deviceId);

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(enable4ByteAddrModeSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_ENABLE_4BYTE_ADDR_MODE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, enable4ByteAddrModeSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_Enable4ByteAddressMode */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Read4ByteAddrModeRegister()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Read4ByteAddrModeRegister(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer = vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readAddrModeSequencePtr;

  /* Find the last sector within the currently checked die. */
  for (; processedInitializerInstance->CurrentCheckSectorIndex < processedInitializerInstance->LastCheckSectorIndex;
      processedInitializerInstance->CurrentCheckSectorIndex++) /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
  {
    if (vMem_30_XXspi01_LL_CfgSector_IsLastSectorOfDie(processedInitializerInstance->CurrentCheckSectorIndex))
    {
      readAddrModeSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetAddressModeRegisterSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
          processedInitializerInstance->InstanceId, deviceId, processedInitializerInstance->CurrentCheckSectorIndex,
          registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

      if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readAddrModeSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
      {
        processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_4BYTE_ADDR_MODE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, readAddrModeSequencePtr->SpiSequence);
#endif
      }
      else
      {
        vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
      }

      break;
    }
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_Read4ByteAddrModeRegister */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Check4ByteAddressModeEnabled()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Check4ByteAddressModeEnabled(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstSpiDataPtrType registerDataBuffer =
      vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_AddressMode4ByteBitMaskOfvMemDeviceConfigType addrMode4ByteBitMask =
      vMem_30_XXspi01_LL_CfgDevice_GetAddressMode4ByteBitMask(deviceId);
  vMem_30_XXspi01_SpiDataType registerContent;

  registerContent = vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, registerDataBuffer); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  if ((registerContent & (vMem_30_XXspi01_SpiDataType) addrMode4ByteBitMask) == (vMem_30_XXspi01_SpiDataType) addrMode4ByteBitMask)
  {
    processedInitializerInstance->CurrentCheckSectorIndex++; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    processedInitializerInstance->CurrentCheckDie++; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

    if (processedInitializerInstance->CurrentCheckDie == processedInitializerInstance->LastCheckDie)
    {
      processedInitializerInstance->CurrentCheckSectorIndex = /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
          (vMem_30_XXspi01_MemSectorLengthOfvMemInstanceType) vMem_30_XXspi01_LL_CfgInstance_GetMemSectorStartIdx(
              processedInitializerInstance->InstanceId);
      processedInitializerInstance->CurrentCheckDie = 0u; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

      vMem_30_XXspi01_LL_InstanceInitializer_InitiateHybridSectorLayoutConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
    }
    else
    {
      /*!
       * You may wonder, why the "Enable 4 Byte address mode" - command is not transmitted for each
       * configured die. The command enables the "4 Byte address mode" for the whole device (instance),
       * but the check must be performed for each sector batch in case the sectors lie in different
       * dies.
       */
      vMem_30_XXspi01_LL_InstanceInitializer_Read4ByteAddrModeRegister(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
    }
  }
  else if (processedInitializerInstance->InitTimeoutCounter > 0u)
  {
    processedInitializerInstance->InitTimeoutCounter--; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    vMem_30_XXspi01_LL_InstanceInitializer_Enable4ByteAddressMode(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_Check4ByteAddressModeEnabled */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitiateHybridSectorLayoutConfig()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitiateHybridSectorLayoutConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];

  if (vMem_30_XXspi01_LL_CfgDevice_IsHybridSectorLayoutConfigurationEnabled(deviceId))
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitialReadHybridSectorLayoutReg(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitiateQuadSpiModeConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitiateHybridSectorLayoutConfig */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitialReadHybridSectorLayoutReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitialReadHybridSectorLayoutReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer = vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readHybridSectorLayoutSequencePtr;

  for (; processedInitializerInstance->CurrentCheckSectorIndex < processedInitializerInstance->LastCheckSectorIndex;
      processedInitializerInstance->CurrentCheckSectorIndex++) /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
  {
    if (vMem_30_XXspi01_LL_CfgSector_IsLastSectorOfDie(processedInitializerInstance->CurrentCheckSectorIndex))
    {
      readHybridSectorLayoutSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadHybridSectorLayoutSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      processedInitializerInstance->InstanceId, deviceId, processedInitializerInstance->CurrentCheckSectorIndex,
      registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

      if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readHybridSectorLayoutSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
      {
        processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_HYBRID_SECTOR_LAYOUT; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

    #if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
        vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, readHybridSectorLayoutSequencePtr->SpiSequence);
    #endif
      }
      else
      {
        vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
      }
      break;
    }
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitialReadHybridSectorLayoutReg */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ConfigureHybridSectorLayout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ConfigureHybridSectorLayout(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType enableHybridSectorLayoutSequencePtr;
  vMem_30_XXspi01_InstanceIdType instanceId = processedInitializerInstance->InstanceId;
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[instanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer = vMem_30_XXspi01_InitRegisterDataBuffers[instanceId];
  vMem_30_XXspi01_HybridSectorLayoutBitMaskOfvMemDeviceConfigType hybridSectorLayoutBitMask =
      vMem_30_XXspi01_LL_CfgDevice_GetHybridSectorLayoutBitMask(deviceId);
  vMem_30_XXspi01_SpiDataType registerContent;

  registerContent = vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, registerDataBuffer); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  /*
   * Configure the write buffer with the right bit value for the hybrid sector layout register.
   * +-------------------------+----------------------------+-----------------------------+
   * |                         | HybridSectorLayoutInverted | !HybridSectorLayoutInverted |
   * +-------------------------+----------------------------+-----------------------------+
   * | hybridSectorLayoutUsed  | set bit at given bitmask   | clear bit at given bitmask  |
   * +-------------------------+----------------------------+-----------------------------+
   * | !hybridSectorLayoutUsed | clear bit at given bitmask | set bit at given bitmask    |
   * +-------------------------+----------------------------+-----------------------------+
   */

  if (vMem_30_XXspi01_LL_CfgSector_IsDieSpecificHybridSectorLayout(
      processedInitializerInstance->CurrentCheckSectorIndex)
      == (vMem_30_XXspi01_LL_CfgDevice_IsHybridSectorLayoutInverted(deviceId)))
  {
    registerDataBuffer[0u] = ((registerContent | (vMem_30_XXspi01_SpiDataType) hybridSectorLayoutBitMask)); /* SBSW_vMem_30_XXspi01_PointerWriteUsinginstanceId */
  }
  else
  {
    registerDataBuffer[0u] = ((registerContent & ((vMem_30_XXspi01_SpiDataType) ~((vMem_30_XXspi01_SpiDataType) hybridSectorLayoutBitMask)))); /* SBSW_vMem_30_XXspi01_PointerWriteUsinginstanceId */
  }

  enableHybridSectorLayoutSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteHybridSectorLayoutSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      instanceId, deviceId, processedInitializerInstance->CurrentCheckSectorIndex, registerDataBuffer, 1u);

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(enableHybridSectorLayoutSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_CONFIGURE_HYBRID_SECTOR_LAYOUT; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, enableHybridSectorLayoutSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_ConfigureHybridSectorLayout */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ReadBackHybridSectorLayoutReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ReadBackHybridSectorLayoutReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer = vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readHybridSectorLayoutSequencePtr;

  readHybridSectorLayoutSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadHybridSectorLayoutSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      processedInitializerInstance->InstanceId, deviceId, processedInitializerInstance->CurrentCheckSectorIndex,
      registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readHybridSectorLayoutSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_HYBRID_SECTOR_LAYOUT; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, readHybridSectorLayoutSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_ReadBackHybridSectorLayoutReg */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_CheckHybridSectorLayout()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_CheckHybridSectorLayout(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstSpiDataPtrType registerDataBuffer = vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_HybridSectorLayoutBitMaskOfvMemDeviceConfigType hybridSectorLayoutBitMask =
      vMem_30_XXspi01_LL_CfgDevice_GetHybridSectorLayoutBitMask(deviceId);
  vMem_30_XXspi01_SpiDataType registerContent;
  vMem_30_XXspi01_SpiDataType checkBitMask;

  /* If the register flag to configure the hybrid sector layout is inverted (0 is active), the checkBitMask must be 0. */
  checkBitMask =
      (vMem_30_XXspi01_LL_CfgSector_IsDieSpecificHybridSectorLayout(
          processedInitializerInstance->CurrentCheckSectorIndex)
          == (vMem_30_XXspi01_LL_CfgDevice_IsHybridSectorLayoutInverted(deviceId))) ?
          (vMem_30_XXspi01_SpiDataType) hybridSectorLayoutBitMask : 0u;

  registerContent = vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, registerDataBuffer); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  if ((registerContent & (vMem_30_XXspi01_SpiDataType) hybridSectorLayoutBitMask) == checkBitMask) /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
  {
    processedInitializerInstance->CurrentCheckSectorIndex++; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    processedInitializerInstance->CurrentCheckDie++; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
    if (processedInitializerInstance->CurrentCheckDie == processedInitializerInstance->LastCheckDie)
    {
      processedInitializerInstance->CurrentCheckSectorIndex = /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
          (vMem_30_XXspi01_MemSectorLengthOfvMemInstanceType) vMem_30_XXspi01_LL_CfgInstance_GetMemSectorStartIdx(
              processedInitializerInstance->InstanceId);
      processedInitializerInstance->CurrentCheckDie = 0u; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

      vMem_30_XXspi01_LL_InstanceInitializer_InitiateQuadSpiModeConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
    }
    else
    {
      vMem_30_XXspi01_LL_InstanceInitializer_InitialReadHybridSectorLayoutReg(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
    }
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_CheckHybridSectorLayout */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitiateQuadSpiModeConfig()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitiateQuadSpiModeConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];

  if (vMem_30_XXspi01_LL_CfgDevice_IsQuadSpiModeConfigEnabled(deviceId))
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitialReadQuadSpiModeReg(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitiateDummyCycleConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitiateQuadSpiModeConfig */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitialReadQuadSpiModeReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitialReadQuadSpiModeReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer = vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readQuadSpiModeRegSequencePtr;

  readQuadSpiModeRegSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadQuadSpiModeRegisterSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      processedInitializerInstance->InstanceId, deviceId, registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readQuadSpiModeRegSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_QUAD_SPI_MODE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, readQuadSpiModeRegSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitialReadQuadSpiModeReg */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_EnableQuadSpiMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_EnableQuadSpiMode(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer =
      vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataType registerContent;
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType enableQuadSpiModeSequencePtr;

  registerContent = vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, registerDataBuffer); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  registerDataBuffer[0u] = ((registerContent | (vMem_30_XXspi01_SpiDataType) (vMem_30_XXspi01_LL_CfgDevice_GetQuadSpiModeBitMask(deviceId)))); /* SBSW_vMem_30_XXspi01_PointerWriteUsinginstanceId */

  enableQuadSpiModeSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteQuadSpiModeRegisterSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      processedInitializerInstance->InstanceId, deviceId, registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(enableQuadSpiModeSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_ENABLE_QUAD_SPI_MODE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, enableQuadSpiModeSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_EnableQuadSpiMode */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ReadBackQuadSpiModeReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ReadBackQuadSpiModeReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer =
      vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readQuadSpiModeRegisterSequencePtr;

  readQuadSpiModeRegisterSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadQuadSpiModeRegisterSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      processedInitializerInstance->InstanceId, deviceId, registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readQuadSpiModeRegisterSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_QUAD_SPI_MODE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, readQuadSpiModeRegisterSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_ReadBackQuadSpiModeReg */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_CheckQuadSpiMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_CheckQuadSpiMode(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstSpiDataPtrType registerDataBuffer =
      vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_QuadSpiModeBitMaskOfvMemDeviceConfigType quadSpiModeBitMask =
      vMem_30_XXspi01_LL_CfgDevice_GetQuadSpiModeBitMask(deviceId);
  vMem_30_XXspi01_SpiDataType registerContent;

  registerContent = vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, registerDataBuffer); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  if ((registerContent & (vMem_30_XXspi01_SpiDataType) quadSpiModeBitMask) == (vMem_30_XXspi01_SpiDataType) quadSpiModeBitMask) /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitiateDummyCycleConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_CheckQuadSpiMode */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitiateDummyCycleConfig()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitiateDummyCycleConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];

  if (vMem_30_XXspi01_LL_CfgDevice_IsDummyCyclesConfigEnabled(deviceId))
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitialReadDummyCycleConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFinish(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitiateDummyCycleConfig */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitialReadDummyCycleConfig()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitialReadDummyCycleConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer =
      vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readDummyCycleRegSequencePtr;

  readDummyCycleRegSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadDummyCycleRegisterSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      processedInitializerInstance->InstanceId, deviceId, registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readDummyCycleRegSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_DUMMY_CYCLES; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, readDummyCycleRegSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitialReadDummyCycleConfig */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_GetBitmaskShiftOffset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(uint32, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_GetBitmaskShiftOffset(
    uint32 bitmask)
{
  boolean searchShiftOffset = TRUE;
  uint32 shiftOffset = 0u;
  uint32 compareBitmask = 1u;

  if(bitmask != 0u)
  {
    while (searchShiftOffset == TRUE)
    {
      if(((bitmask >> shiftOffset) & compareBitmask) == compareBitmask)
      {
        searchShiftOffset = FALSE;
      }
      else
      {
        shiftOffset++;
      }
    }
  }

  return shiftOffset;
} /* vMem_30_XXspi01_LL_InstanceInitializer_GetBitmaskShiftOffset */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ConfigureDummyCycleSettings()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ConfigureDummyCycleSettings(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_DummyCycleConfigBitMaskOfvMemDeviceConfigType dummyCycleBitMask =
      vMem_30_XXspi01_LL_CfgDevice_GetDummyCycleConfigBitMask(deviceId);
  vMem_30_XXspi01_NumberOfDummyCyclesOfvMemInstanceType numberOfDummyCycles =
      vMem_30_XXspi01_LL_CfgInstance_GetNumberOfDummyCycles(processedInitializerInstance->InstanceId);
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer =
      vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType configureDummyCyclesSequencePtr;
  vMem_30_XXspi01_SpiDataType registerContent;
  vMem_30_XXspi01_SpiDataType shiftedBitMask;
  uint32 shiftOffset;


  registerContent = vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, registerDataBuffer); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */

  /*
   * The stored dummy cycle bitmask is not the actual value to be written to the corresponding config register. The bitmask is used to determine the number of bit shifts
   * which must be performed for the number of dummy cycles to calculate the correct bitmask.
   */
  shiftOffset = vMem_30_XXspi01_LL_InstanceInitializer_GetBitmaskShiftOffset(dummyCycleBitMask);
  shiftedBitMask = (vMem_30_XXspi01_SpiDataType) (numberOfDummyCycles << shiftOffset);

  /* Check if the dummy cycles are already configured. */
  if((registerContent & shiftedBitMask) == shiftedBitMask)
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFinish(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    registerDataBuffer[0u] = /* SBSW_vMem_30_XXspi01_PointerWriteUsinginstanceId */
        ((registerContent | (vMem_30_XXspi01_SpiDataType) (numberOfDummyCycles << shiftOffset)));

    configureDummyCyclesSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetWriteDummyCycleRegisterSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
        processedInitializerInstance->InstanceId, deviceId, registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

    if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(configureDummyCyclesSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
    {
      processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_CONFIG_DUMMY_CYCLES; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

  #if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
      vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, configureDummyCyclesSequencePtr->SpiSequence);
  #endif
    }
    else
    {
      vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
    }
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_ConfigureDummyCycleSettings */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_ReadBackDummyCycleReg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_ReadBackDummyCycleReg(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_SpiDataPtrType registerDataBuffer =
      vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstFlsCmdSequencePtrType readDummyCycleRegisterSequencePtr;

  readDummyCycleRegisterSequencePtr = vMem_30_XXspi01_LL_FlsCmdSeqBuilder_GetReadDummyCycleRegisterSequence( /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
      processedInitializerInstance->InstanceId, deviceId, registerDataBuffer, vMem_30_XXspi01_LL_CfgDevice_GetRegisterAccessLength(deviceId));

  if (vMem_30_XXspi01_LL_FlsCmdSeqExecuter_Execute(readDummyCycleRegisterSequencePtr) == E_OK) /* SBSW_vMem_30_XXspi01_ExecuteSequence */
  {
    processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_DUMMY_CYCLES; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

#if (VMEM_30_XXSPI01_SPI_ASYNCTRANSMIT_API_ENABLED == STD_OFF)
    vMem_30_XXspi01_LLSeqEndNotification(processedInitializerInstance->InstanceId, readDummyCycleRegisterSequencePtr->SpiSequence);
#endif
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_ReadBackDummyCycleReg */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_CheckDummyCycleConfig()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_CheckDummyCycleConfig(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  vMem_30_XXspi01_DeviceIdType deviceId = vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_ConstSpiDataPtrType registerDataBuffer =
      vMem_30_XXspi01_InitRegisterDataBuffers[processedInitializerInstance->InstanceId];
  vMem_30_XXspi01_QuadSpiModeBitMaskOfvMemDeviceConfigType dummyCycleBitMask =
      vMem_30_XXspi01_LL_CfgDevice_GetDummyCycleConfigBitMask(deviceId);
  vMem_30_XXspi01_SpiDataType registerContent;
  vMem_30_XXspi01_SpiDataType shiftedBitMask;
  uint32 shiftOffset;

  registerContent = vMem_30_XXspi01_LL_InstanceAccess_GetRegisterContent(deviceId, registerDataBuffer); /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
  shiftOffset = vMem_30_XXspi01_LL_InstanceInitializer_GetBitmaskShiftOffset(dummyCycleBitMask);
  shiftedBitMask = (vMem_30_XXspi01_SpiDataType) (dummyCycleBitMask << shiftOffset);

  if ((registerContent & shiftedBitMask) == shiftedBitMask) /* SBSW_vMem_30_XXspi01_FunctionCallWithBufferPointer */
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFinish(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
  else
  {
    vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithGivenDataPointers */
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_CheckDummyCycleConfig */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitHwFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitHwFinish(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  processedInitializerInstance->InitStatus = VMEM_30_XXSPI01_INSTANCE_INIT; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
  processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

  vMem_30_XXspi01_LL_Cbk_InitSucceeded(processedInitializerInstance->InstanceId,
      vMem_30_XXspi01_DeviceId[processedInitializerInstance->InstanceId]);
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitHwFinish */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
VMEM_30_XXSPI01_LOCAL FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed(
    vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance)
{
  processedInitializerInstance->InitStatus = VMEM_30_XXSPI01_INSTANCE_UNINIT; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */
  processedInitializerInstance->InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_IDLE; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrCaller */

  vMem_30_XXspi01_LL_Cbk_JobFailed(processedInitializerInstance->InstanceId);
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitHwFailed */

/*********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_GetJedecIdInformation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(vMem_30_XXspi01_SpiDataPtrType, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_GetJedecIdInformation(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  return vMem_30_XXspi01_JedecIdBufferPtr[instanceId];
} /* vMem_30_XXspi01_LL_InstanceInitializer_GetJedecIdInformation */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  return (vMem_30_XXspi01_InstanceInitState[instanceId].InitStatus == VMEM_30_XXSPI01_INSTANCE_INIT) ? TRUE : FALSE;
} /* vMem_30_XXspi01_LL_InstanceInitializer_IsInstanceInitialized */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Init(void)
{
  vMem_30_XXspi01_InstanceIdType instanceId;
  uint8 jedecIdBufferIndex;

  for (instanceId = 0; instanceId < vMem_30_XXspi01_GetSizeOfvMemInstance(); instanceId++)
  {
    vMem_30_XXspi01_InstanceInitState[instanceId].InitProgress = VMEM_30_XXSPI01_INSTANCEINITIALIZER_IDLE; /* SBSW_vMem_30_XXspi01_WriteToArrayinstanceIdLoop */
    vMem_30_XXspi01_InstanceInitState[instanceId].InitStatus = VMEM_30_XXSPI01_INSTANCE_UNINIT; /* SBSW_vMem_30_XXspi01_WriteToArrayinstanceIdLoop */

    for (jedecIdBufferIndex = 0; jedecIdBufferIndex < VMEM_30_XXSPI01_JEDECID_BUFFER_LENGTH; jedecIdBufferIndex++)
    {
      vMem_30_XXspi01_JedecIdBufferPtr[instanceId][jedecIdBufferIndex] = 0u; /* SBSW_vMem_30_XXspi01_WriteToArrayJedecIdBufferPtr */
    }
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_Init */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_InitInstance()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_InitInstance(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance = &vMem_30_XXspi01_InstanceInitState[instanceId];

  processedInitializerInstance->InstanceId = instanceId; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  processedInitializerInstance->CurrentCheckDie = 0; /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  processedInitializerInstance->LastCheckDie = vMem_30_XXspi01_LL_CfgInstance_GetNumberOfDies(instanceId); /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
  processedInitializerInstance->CurrentCheckSectorIndex = vMem_30_XXspi01_LL_CfgInstance_GetMemSectorStartIdx( /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
      instanceId);
  processedInitializerInstance->LastCheckSectorIndex = vMem_30_XXspi01_LL_CfgInstance_GetMemSectorEndIdx( /* SBSW_vMem_30_XXspi01_WriteToInstanceStateMachinePtrParameter */
      instanceId);

  vMem_30_XXspi01_LL_InstanceInitializer_ReadJedecId(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
} /* vMem_30_XXspi01_LL_InstanceInitializer_InitInstance */

/**********************************************************************************************************************
 *  vMem_30_XXspi01_LL_InstanceInitializer_Processing()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, VMEM_30_XXSPI01_CODE) vMem_30_XXspi01_LL_InstanceInitializer_Processing(
    vMem_30_XXspi01_InstanceIdType instanceId)
{
  vMem_30_XXspi01_InstanceInitStatePtrType processedInitializerInstance = &vMem_30_XXspi01_InstanceInitState[instanceId];

  switch (processedInitializerInstance->InitProgress)
  {
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_JEDEC_ID:
    vMem_30_XXspi01_LL_InstanceInitializer_CheckPresenceOfJedecId(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_ENABLE_4BYTE_ADDR_MODE:
    vMem_30_XXspi01_LL_InstanceInitializer_Read4ByteAddrModeRegister(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_4BYTE_ADDR_MODE:
    vMem_30_XXspi01_LL_InstanceInitializer_Check4ByteAddressModeEnabled(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_HYBRID_SECTOR_LAYOUT:
    vMem_30_XXspi01_LL_InstanceInitializer_ConfigureHybridSectorLayout(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_CONFIGURE_HYBRID_SECTOR_LAYOUT:
    vMem_30_XXspi01_LL_InstanceInitializer_ReadBackHybridSectorLayoutReg(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_HYBRID_SECTOR_LAYOUT:
    vMem_30_XXspi01_LL_InstanceInitializer_CheckHybridSectorLayout(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_QUAD_SPI_MODE:
    vMem_30_XXspi01_LL_InstanceInitializer_EnableQuadSpiMode(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_ENABLE_QUAD_SPI_MODE:
    vMem_30_XXspi01_LL_InstanceInitializer_ReadBackQuadSpiModeReg(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_QUAD_SPI_MODE:
    vMem_30_XXspi01_LL_InstanceInitializer_CheckQuadSpiMode(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_INITIAL_READ_DUMMY_CYCLES:
    vMem_30_XXspi01_LL_InstanceInitializer_ConfigureDummyCycleSettings(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_CONFIG_DUMMY_CYCLES:
    vMem_30_XXspi01_LL_InstanceInitializer_ReadBackDummyCycleReg(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  case VMEM_30_XXSPI01_INSTANCEINITIALIZER_READ_BACK_DUMMY_CYCLES:
    vMem_30_XXspi01_LL_InstanceInitializer_CheckDummyCycleConfig(processedInitializerInstance); /* SBSW_vMem_30_XXspi01_FunctionCallWithDataPointersViaParameter */
    break;
  default: /* VMEM_30_XXSPI01_INSTANCEINITIALIZER_IDLE */
    /* Nothing to do. */
    break;
  }
} /* vMem_30_XXspi01_LL_InstanceInitializer_Processing */ /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */

#define VMEM_30_XXSPI01_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* SBSW_JUSTIFICATION_BEGIN
 \ID SBSW_vMem_30_XXspi01_FunctionCallGetAddressModeRegisterSequence
 \DESCRIPTION The function vMem_LL_FlsCmdSeqBuilder_GetAddressModeRegisterSequence() is called with a pointer
 to the InitRegisterDataBuffers[instanceId].
 \COUNTERMEASURE \N No countermeasure necessary, because the InitRegisterDataBuffers[] is defined on global scope.
 The size of the array is the number of instances.
 The instanceId initially comes from vMem_LLProcessig() where it is ensured that a valid
 instanceId is passed.

  \ID SBSW_vMem_30_XXspi01_FunctionCallWithPointerArgument
 \DESCRIPTION The function is called with a pointer to the InitRegisterDataBuffers[instanceId].
 \COUNTERMEASURE \N No countermeasure necessary, because the InitRegisterDataBuffers[] is defined on global scope.
 The size of the array is the number of instances.
 The instanceId initially comes from vMem_LLProcessig() where it is ensured that a valid
 instanceId is passed.

 \ID SBSW_vMem_30_XXspi01_WriteToArrayinstanceIdLoop
 \DESCRIPTION A write access is made to an array using the instanceId.
 \COUNTERMEASURE \N No countermeasure is necessary because the array is accessed using a loop variable as index. The
 referenced structure array is preallocated with one entry for each configured flash device. The
 loop iterates over every configured device and therefore only provides valid indices.

 \ID SBSW_vMem_30_XXspi01_PointerWriteUsinginstanceId
 \DESCRIPTION A pointer write access is performed. The value of the pointer is retrieved using the instanceId.
 \COUNTERMEASURE \N No countermeasure necessary, because the instanceId used to retrieve the pointer initially comes
 from the caller of the service functions of the vMem_LL_InstanceInitializer. The caller (vMem_LL) ensures
 that the instanceId is in the valid range.
 The referenced structure array is preallocated with one entry for each configured flash
 device (instance).
 SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: vMem_30_XXspi01_LL_InstanceInitializer.c
 *********************************************************************************************************************/
