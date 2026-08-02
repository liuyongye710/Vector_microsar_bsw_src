/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Lin_Fp_Slave.h
 *        \brief  AUTOSAR LIN Driver Frame Processor
 *
 *      \details  Header for Slave specific functions for ASCLIN hardware frame processor (Tricore)
 *
 *********************************************************************************************************************/

#if !defined (LIN_FP_SLAVE_H)
# define LIN_FP_SLAVE_H

# if ( LIN_ABDOFCHANNELCONFIG == STD_ON ) /* COV_LIN_NO_ABD */
/***********************************************************************************************************************
 *  Lin_Fp_ConfigureBRD
 **********************************************************************************************************************/
/*! \brief       Configure the Autobaudrate detection
 *  \details     -
 *  \param[in]   ChannelConfigIdx: Access to all Channel data (register, data, ...)
 *  \pre         Internal function. Do not call.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 *  \config      LIN_ABDOFCHANNELCONFIG
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_ConfigureBRD( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );
# endif /* LIN_ABDOFCHANNELCONFIG == STD_ON */

/***********************************************************************************************************************
 *  Lin_Fp_EnableHeaderReception
 **********************************************************************************************************************/
/*! \brief       Enable the Header reception
 *  \details     -
 *  \param[in]   ChannelConfigIdx: Access to all Channel data (register, data, ...)
 *  \pre         Internal function. Do not call.
 *  \context     TASK/ISR
 *  \reentrant   TRUE for different LIN channels
 *  \synchronous FALSE
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE) Lin_Fp_EnableHeaderReception( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );

/***********************************************************************************************************************
 *  Lin_Fp_Slave_Interrupt_Error_Occurred
 **********************************************************************************************************************/
/*! \brief       The Slave specific error handling interrupt function
 *  \details     -
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \param[in]   Flags: The read value of Flags register
 *  \param[in]   RxFifoCon: The read value of RxFifoCon register
 *  \pre         -
 *  \context     ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 *  \synchronous FALSE
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE_ISR) Lin_Fp_Slave_Interrupt_Error_Occurred( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx, uint32 Flags, uint32 RxFifoCon );

/***********************************************************************************************************************
 *  Lin_Fp_Slave_Interrupt
 **********************************************************************************************************************/
/*! \brief       The Slave specific interrupt function
 *  \details     -
 *  \param[in]   ChannelConfigIdx: The valid index of the 1:1 relation pointing to Lin_ChannelConfig or Lin_ChannelData
 *  \pre         -
 *  \context     ISR
 *  \reentrant   TRUE for different handles (LIN channels)
 *  \synchronous FALSE
 **********************************************************************************************************************/
LIN_LOCAL_INLINE FUNC(void, LIN_CODE_ISR) Lin_Fp_Slave_Interrupt( Lin_ChannelConfigIdxOfChannelIdType ChannelConfigIdx );


#endif /* LIN_FP_SLAVE_H */
