/*
********************************************************************************
*
* File name: Rte_Compiler_Cfg.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: Gaol/2022.6.14
* Change: New created.
* Cause: New
********************************************************************************
*/
#ifndef RTE_COMPILER_CFG_H_
#define RTE_COMPILER_CFG_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
/*
********************************************************************************
*    RTE_CODE
********************************************************************************
*/

/* used for code */
#define RTE_CODE

/* used for all global or static variables that are not initialized by the startup code of the compiler */
#define RTE_VAR_NOINIT

/* used for global or static variables that are initialized with zero by the startup code of the compiler or in Rte_InitMemory */
#define RTE_VAR_ZERO_INIT

/* used for global or static variables that are initialized by the startup code of the compiler or in Rte_InitMemory */
#define RTE_VAR_INIT

/* used for global or static constants */
#define RTE_CONST

/* used for references on application data (variables or constants) */
#define RTE_APPL_DATA

/* used for references on application variables */
#define RTE_APPL_VAR

/* used for references on application functions */
#define RTE_APPL_CODE

/* non cacheable memory variant */
#define RTE_VAR_NOINIT_NOCACHE

/* non cacheable memory variant */
#define RTE_VAR_ZERO_INIT_NOCACHE

/* non cacheable memory variant */
#define RTE_VAR_INIT_NOCACHE

#define RTE_CONST_DEFAULT_RTE_CDATA_GROUP

#define RTE_CONST_DEFAULT_RTE_CALPRM_GROUP

#define RTE_VAR_DEFAULT_RTE_PIM_GROUP

/* used for E2EPW global or static constants */
#define E2EPW_CONST

#define E2EPW_APPL_CONST

/* used for E2EPW global or static variables that are initialized by the 
   startup code of the compiler or in Rte_InitMemory */
#define E2EPW_VAR_INIT

/* used for E2EPW code */
#define E2EPW_CODE

/* used for E2EPW references on application data (variables or constants) */
#define E2EPW_APPL_DATA

/*
********************************************************************************
*    RTE_BSWM_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_BSWM_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_BSWM_APPL_DATA

/* used for references on application functions */
#define RTE_BSWM_APPL_CODE

/* used for references on application constants */
#define RTE_BSWM_APPL_CONST

/* used for SWC specific code */
#define BswM_CODE

/* used for global or static SWC specific constants */
#define BswM_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define BswM_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define BswM_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define BswM_VAR_ZERO_INIT

/*
********************************************************************************
*    RTE_COMM_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_COMM_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_COMM_APPL_DATA

/* used for references on application functions */
#define RTE_COMM_APPL_CODE

/* used for references on application constants */
#define RTE_COMM_APPL_CONST

/* used for SWC specific code */
#define ComM_CODE

/* used for global or static SWC specific constants */
#define ComM_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define ComM_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define ComM_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define ComM_VAR_ZERO_INIT


/*
********************************************************************************
*    RTE_DCM_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_DCM_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_DCM_APPL_DATA

/* used for references on application functions */
#define RTE_DCM_APPL_CODE

/* used for references on application constants */
#define RTE_DCM_APPL_CONST

/* used for SWC specific code */
#define Dcm_CODE

/* used for global or static SWC specific constants */
#define Dcm_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define Dcm_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define Dcm_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define Dcm_VAR_ZERO_INIT

/*
********************************************************************************
*    RTE_DEM_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_DEM_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_DEM_APPL_DATA

/* used for references on application functions */
#define RTE_DEM_APPL_CODE

/* used for references on application constants */
#define RTE_DEM_APPL_CONST

/* used for SWC specific code */
#define Dem_CODE

/* used for global or static SWC specific constants */
#define Dem_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define Dem_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define Dem_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define Dem_VAR_ZERO_INIT

/*
********************************************************************************
*    RTE_ECUM_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_ECUM_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_ECUM_APPL_DATA

/* used for references on application functions */
#define RTE_ECUM_APPL_CODE

/* used for references on application constants */
#define RTE_ECUM_APPL_CONST

/* used for SWC specific code */
#define EcuM_CODE

/* used for global or static SWC specific constants */
#define EcuM_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define EcuM_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define EcuM_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define EcuM_VAR_ZERO_INIT

/*
********************************************************************************
*    RTE_FIM_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_FIM_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_FIM_APPL_DATA

/* used for references on application functions */
#define RTE_FIM_APPL_CODE

/* used for references on application constants */
#define RTE_FIM_APPL_CONST

/* used for SWC specific code */
#define FiM_CODE

/* used for global or static SWC specific constants */
#define FiM_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define FiM_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define FiM_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define FiM_VAR_ZERO_INIT

/*
********************************************************************************
*    RTE_NVM_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_NVM_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_NVM_APPL_DATA

/* used for references on application functions */
#define RTE_NVM_APPL_CODE

/* used for references on application constants */
#define RTE_NVM_APPL_CONST

/* used for SWC specific code */
#define NvM_CODE

/* used for global or static SWC specific constants */
#define NvM_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define NvM_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define NvM_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define NvM_VAR_ZERO_INIT

/*
********************************************************************************
*    RTE_WDGM_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_WDGM_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_WDGM_APPL_DATA

/* used for references on application functions */
#define RTE_WDGM_APPL_CODE

/* used for references on application constants */
#define RTE_WDGM_APPL_CONST

/* used for SWC specific code */
#define WdgM_CODE

/* used for global or static SWC specific constants */
#define WdgM_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define WdgM_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define WdgM_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define WdgM_VAR_ZERO_INIT

/*
********************************************************************************
*    RTE_IoHwAb_APPL
********************************************************************************
*/

/* used for references on application variables */
#define RTE_IoHwAb_APPL_VAR

/* used for references on application data (constants or variables) */
#define RTE_IoHwAb_APPL_DATA

/* used for references on application functions */
#define RTE_IoHwAb_APPL_CODE

/* used for references on application constants */
#define RTE_IoHwAb_APPL_CONST

/* used for SWC specific code */
#define IoHwAb_CODE

/* used for global or static SWC specific constants */
#define IoHwAb_CONST

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
#define IoHwAb_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
#define IoHwAb_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
#define IoHwAb_VAR_ZERO_INIT

/*
********************************************************************************
*    RTE_SWC_APPL
********************************************************************************
*/

#endif /* RTE_COMPILER_CFG_H_ */

