/********************************************************************************
*
*  File name:   FAW_MemMap.h.h
*
*********************************************************************************/

/********************************************************************************
*    Includes
*********************************************************************************/

/********************************************************************************
*    Global Macros
*********************************************************************************/
#ifdef XCP_START_SEC_CONST_CORE0_BLOCK0
#pragma section ".CAL_CONST"

#undef XCP_START_SEC_CONST_CORE0_BLOCK0
#endif


#ifdef XCP_STOP_SEC_CONST_CORE0_BLOCK0
#pragma section

#undef XCP_STOP_SEC_CONST_CORE0_BLOCK0
#endif

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
#ifdef FAW_CORE0_IMEM0_CODE_START
#pragma section ".local_imem0_code_section" axv

#undef FAW_CORE0_IMEM0_CODE_START
#endif

#ifdef FAW_CORE0_IMEM0_CODE_STOP
#pragma section
#undef FAW_CORE0_IMEM0_CODE_STOP
#endif

#ifdef FAW_CORE0_DMEM0_VALUE_START
#pragma section ".local_dmem0_value_section"
#undef FAW_CORE0_DMEM0_VALUE_START
#endif

#ifdef FAW_CORE0_DMEM0_VALUE_STOP
#pragma section
#undef FAW_CORE0_DMEM0_VALUE_STOP
#endif

