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
 *  \ingroup    Os_Hal
 *  \defgroup   Os_Hal_Compiler  HAL Compiler
 *  \brief      Abstraction of compiler specific keywords to allow the compiler to generate more efficient code.
 *  \details
 *  The kernel should be able to give the compiler meta information to generate more efficient code.
 *  It also needs to tell the linker where to put data and code to implement Memory Protection.
 *  In multi core systems there may be the need for data/code duplication.
 *  The keywords to provide this information are not part of ANSI-C and are highly compiler dependent.
 *
 *  AUTOSAR already defines concepts to abstract compiler specifics:
 *  - [AUTOSAR Compiler Abstraction](http://www.autosar.org/fileadmin/files/releases/4-2/software-architecture/
 *                                   implementation-integration/standard/AUTOSAR_SWS_CompilerAbstraction.pdf)
 *  - [AUTOSAR Memory Mapping](http://www.autosar.org/fileadmin/files/releases/3-2/software-architecture/implementation
 *                             -integration/standard/AUTOSAR_SWS_MemoryMapping.pdf)
 *
 *  They are used in MICROSAR OS. This module defines additional compiler abstraction keywords for MICROSAR OS.
 *  They are relevant to provide OS functionality or improve efficiency.
 *
 *  \{
 *
 *  \file       Os_Hal_CompilerInt.h
 *  \brief      Additional services defined here are available to the user.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/


#if !defined (OS_HAL_COMPILERINT_H)
# define OS_HAL_COMPILERINT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */
# include "Os_Cfg.h"
# include "Os_CommonInt.h"

/* Os hal dependencies */


# ifdef CDK_CHECK_MISRA
#  ifndef OS_STATIC_CODE_ANALYSIS
#    define OS_STATIC_CODE_ANALYSIS
#  endif
# endif
  
  
# if defined(OS_STATIC_CODE_ANALYSIS)
#  include "Os_Hal_StaticCodeAnalysis.h"
# else
#  if defined (OS_CFG_COMPILER_TASKING)
#   include "Os_Hal_Compiler_TaskingInt.h"
#  elif defined (OS_CFG_COMPILER_HIGHTEC) || defined (OS_CFG_COMPILER_GNU)
#   include "Os_Hal_Compiler_HighTecInt.h"
#  else
#   error "Undefined or unsupported compiler"
#  endif
# endif





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

#endif /* OS_HAL_COMPILERINT_H */

/* module specific MISRA deviations:
 MD_Os_Hal_3112:
      Reason:     This statement is used to avoid warnings caused by unused parameters. Parameters are defined by
                  standardized API requirements, and not needed in case a feature is disabled by configuration.
                  It is either impossible due to API standardization or necessary code duplication (severe maintenance
                  increase) to provide feature dependent APIs with different signatures.
      Risk:       Unavoidable compiler warning or error because of either unused statements or unused parameter.
      Prevention: None.
 MD_Os_Hal_0303:
      Reason:     This statement converts an integral address to a pointer or vice versa. This is unavoidable for
                  memory access of that address or put a pointer to a core register.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0305:
      Reason:     This statement converts a function pointer to an integral address. This is unavoidable to put the
                  function pointer to a core register.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0306:
      Reason:     This statement converts an integral address to a pointer or vice versa. This is unavoidable for
                  memory access of that address or put a pointer to a core register.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3410:
      Reason:     Macro used in structures, which do not allow brackets e.g. declaration of functions and variables.
      Risk:       None, type errors will be detected by the compiler.
      Prevention: Used parameter is always atomic.
 MD_Os_Hal_3648:
      Reason:     This empty external array declaration is used to define the linker symbol.
      Risk:       None, this will not be used as an array.
      Prevention: None.
 MD_Os_Hal_0881:
      Reason:     Correctness of glue operator evaluation is checked by compiler as incorrect order would lead to
                  compilation errors.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0883:
      Reason:     The protection against repeated inclusion is complete and correct. The MISRA tool is unable to
                  detect this.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3219:
      Reason:     This function is inlined and therefore it has to be implemented here. The function is not used
                  by all implementation files which include this header file.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3673:
      Reason:     This input parameter will only be modified in some configurations. Avoiding this violation will
                  increase code complexity.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_3673_NotUsed:
      Reason:     This input parameter is not used in this HAL implementation, thus it is not modified. However, since
                  it may be used or modified in other platforms, it is unavoidable to keep it as "pointer to non-const".
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0489_StackPointer:
      Reason:     The increment or decrement operation on pointer is explicitly required here.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0489_GenData:
      Reason:     The increment or decrement operation on pointer is not avoidable sue to the usage of macro defined
                  in core code: "OS_STACK_GETHIGHADDRESS".
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0428:
      Reason:     This statement uses the function pointer on purpose, thus a following () is not needed.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0685_MpuRegionAddress:
      Reason:     This is a linker symbol given by the user. MISRA can not recognize this as a constant.
      Risk:       None.
      Prevention: None.
 MD_Os_Hal_0685_CoreEntrySymbol:
      Reason:     This is a linker symbol of core entry point given by the user. MISRA can not recognize this as a 
                  constant.
      Risk:       None.
      Prevention: None.
 */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_CompilerInt.h
 **********************************************************************************************************************/

