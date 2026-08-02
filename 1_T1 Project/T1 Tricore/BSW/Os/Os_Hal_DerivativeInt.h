/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \ingroup      Os_Hal
 *  \defgroup     Os_Hal_Derivative HAL Derivative
 *  \brief        Defines derivative specific functionality.
 *  \details
 *  This modules decides which HAL specific sub components are needed to implement HAL functionality on a specific
 *  derivative.
 *
 *  \{
 *
 * \file          Os_Hal_DerivativeInt.h
 *  \brief        Selects a derivative specific header and includes it.
 *
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/


#if !defined(OS_HAL_DERIVATIVEINT_H)
# define OS_HAL_DERIVATIVEINT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os hal dependencies */
# if defined(OS_CFG_DERIVATIVEGROUP_TC21X)                                                                              /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
#  include "Os_Hal_Derivative_TC21xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC22X)
#  include "Os_Hal_Derivative_TC22xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC23X)
#  include "Os_Hal_Derivative_TC23xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC24X)
#  include "Os_Hal_Derivative_TC24xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC26X)
#  include "Os_Hal_Derivative_TC26xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC27X)
#  include "Os_Hal_Derivative_TC27xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC29X)
#  include "Os_Hal_Derivative_TC29xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC38X)
#  include "Os_Hal_Derivative_TC38xInt.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC39X)
#  include "Os_Hal_Derivative_TC39xInt.h"
# else
#  error "The selected derivative is not supported!"
# endif /* OS_CFG_DERIVATIVEGROUP_<> */

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif /* OS_HAL_DERIVATIVEINT_H */

/*!
 * \}
 */
/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_DerivativeInt.h
 **********************************************************************************************************************/
