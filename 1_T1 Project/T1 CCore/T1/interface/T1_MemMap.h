/*********************************************************************************//*!
*   \file           T1_MemMap.h
*
*   \brief          This header selects the T1-TARGET-SW sections for
*                   the GCC compiler.
*
*   \par Visibility
*                   External
*
*   \author         Generated file
*
*   \version 3.5.0.0 r65733
*
*   \copyright GLIWA embedded systems GmbH & Co. KG, Weilheim i.OB. All rights reserved
*************************************************************************************/

#if 0

#elif defined T1_START_SEC_CODE
#   undef T1_START_SEC_CODE
#   pragma section ".T1_code" axv
#elif defined T1_STOP_SEC_CODE
#   undef T1_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE0_START_SEC_CODE
#   undef T1_CORE0_START_SEC_CODE
#   pragma section ".T1_codeCore0" axv
#elif defined T1_CORE0_STOP_SEC_CODE
#   undef T1_CORE0_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE1_START_SEC_CODE
#   undef T1_CORE1_START_SEC_CODE
#   pragma section ".T1_codeCore1" axv
#elif defined T1_CORE1_STOP_SEC_CODE
#   undef T1_CORE1_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE2_START_SEC_CODE
#   undef T1_CORE2_START_SEC_CODE
#   pragma section ".T1_codeCore2" axv
#elif defined T1_CORE2_STOP_SEC_CODE
#   undef T1_CORE2_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE3_START_SEC_CODE
#   undef T1_CORE3_START_SEC_CODE
#   pragma section ".T1_codeCore3" axv
#elif defined T1_CORE3_STOP_SEC_CODE
#   undef T1_CORE3_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE4_START_SEC_CODE
#   undef T1_CORE4_START_SEC_CODE
#   pragma section ".T1_codeCore4" axv
#elif defined T1_CORE4_STOP_SEC_CODE
#   undef T1_CORE4_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE5_START_SEC_CODE
#   undef T1_CORE5_START_SEC_CODE
#   pragma section ".T1_codeCore5" axv
#elif defined T1_CORE5_STOP_SEC_CODE
#   undef T1_CORE5_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE6_START_SEC_CODE
#   undef T1_CORE6_START_SEC_CODE
#   pragma section ".T1_codeCore6" axv
#elif defined T1_CORE6_STOP_SEC_CODE
#   undef T1_CORE6_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE7_START_SEC_CODE
#   undef T1_CORE7_START_SEC_CODE
#   pragma section ".T1_codeCore7" axv
#elif defined T1_CORE7_STOP_SEC_CODE
#   undef T1_CORE7_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE8_START_SEC_CODE
#   undef T1_CORE8_START_SEC_CODE
#   pragma section ".T1_codeCore8" axv
#elif defined T1_CORE8_STOP_SEC_CODE
#   undef T1_CORE8_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE9_START_SEC_CODE
#   undef T1_CORE9_START_SEC_CODE
#   pragma section ".T1_codeCore9" axv
#elif defined T1_CORE9_STOP_SEC_CODE
#   undef T1_CORE9_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE10_START_SEC_CODE
#   undef T1_CORE10_START_SEC_CODE
#   pragma section ".T1_codeCore10" axv
#elif defined T1_CORE10_STOP_SEC_CODE
#   undef T1_CORE10_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE11_START_SEC_CODE
#   undef T1_CORE11_START_SEC_CODE
#   pragma section ".T1_codeCore11" axv
#elif defined T1_CORE11_STOP_SEC_CODE
#   undef T1_CORE11_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE12_START_SEC_CODE
#   undef T1_CORE12_START_SEC_CODE
#   pragma section ".T1_codeCore12" axv
#elif defined T1_CORE12_STOP_SEC_CODE
#   undef T1_CORE12_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE13_START_SEC_CODE
#   undef T1_CORE13_START_SEC_CODE
#   pragma section ".T1_codeCore13" axv
#elif defined T1_CORE13_STOP_SEC_CODE
#   undef T1_CORE13_STOP_SEC_CODE
#   pragma section

#elif defined T1_CORE14_START_SEC_CODE
#   undef T1_CORE14_START_SEC_CODE
#   pragma section ".T1_codeCore14" axv
#elif defined T1_CORE14_STOP_SEC_CODE
#   undef T1_CORE14_STOP_SEC_CODE
#   pragma section

#elif defined T1_START_SEC_CODE_FAST
#   undef T1_START_SEC_CODE_FAST
#   pragma section ".T1_codeFast" axv
#elif defined T1_STOP_SEC_CODE_FAST
#   undef T1_STOP_SEC_CODE_FAST
#   pragma section

#elif defined T1_START_SEC_CONST_8
#   undef T1_START_SEC_CONST_8
#   pragma section ".T1_const" a
#elif defined T1_STOP_SEC_CONST_8
#   undef T1_STOP_SEC_CONST_8
#   pragma section

#elif defined T1_START_SEC_CONST_16
#   undef T1_START_SEC_CONST_16
#   pragma section ".T1_const" a
#elif defined T1_STOP_SEC_CONST_16
#   undef T1_STOP_SEC_CONST_16
#   pragma section

#elif defined T1_START_SEC_CONST_32
#   undef T1_START_SEC_CONST_32
#   pragma section ".T1_const" a
#elif defined T1_STOP_SEC_CONST_32
#   undef T1_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE0_START_SEC_CONST_32
#   undef T1_CORE0_START_SEC_CONST_32
#   pragma section ".T1_constCore0" a
#elif defined T1_CORE0_STOP_SEC_CONST_32
#   undef T1_CORE0_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE1_START_SEC_CONST_32
#   undef T1_CORE1_START_SEC_CONST_32
#   pragma section ".T1_constCore1" a
#elif defined T1_CORE1_STOP_SEC_CONST_32
#   undef T1_CORE1_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE2_START_SEC_CONST_32
#   undef T1_CORE2_START_SEC_CONST_32
#   pragma section ".T1_constCore2" a
#elif defined T1_CORE2_STOP_SEC_CONST_32
#   undef T1_CORE2_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE3_START_SEC_CONST_32
#   undef T1_CORE3_START_SEC_CONST_32
#   pragma section ".T1_constCore3" a
#elif defined T1_CORE3_STOP_SEC_CONST_32
#   undef T1_CORE3_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE4_START_SEC_CONST_32
#   undef T1_CORE4_START_SEC_CONST_32
#   pragma section ".T1_constCore4" a
#elif defined T1_CORE4_STOP_SEC_CONST_32
#   undef T1_CORE4_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE5_START_SEC_CONST_32
#   undef T1_CORE5_START_SEC_CONST_32
#   pragma section ".T1_constCore5" a
#elif defined T1_CORE5_STOP_SEC_CONST_32
#   undef T1_CORE5_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE6_START_SEC_CONST_32
#   undef T1_CORE6_START_SEC_CONST_32
#   pragma section ".T1_constCore6" a
#elif defined T1_CORE6_STOP_SEC_CONST_32
#   undef T1_CORE6_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE7_START_SEC_CONST_32
#   undef T1_CORE7_START_SEC_CONST_32
#   pragma section ".T1_constCore7" a
#elif defined T1_CORE7_STOP_SEC_CONST_32
#   undef T1_CORE7_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE8_START_SEC_CONST_32
#   undef T1_CORE8_START_SEC_CONST_32
#   pragma section ".T1_constCore8" a
#elif defined T1_CORE8_STOP_SEC_CONST_32
#   undef T1_CORE8_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE9_START_SEC_CONST_32
#   undef T1_CORE9_START_SEC_CONST_32
#   pragma section ".T1_constCore9" a
#elif defined T1_CORE9_STOP_SEC_CONST_32
#   undef T1_CORE9_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE10_START_SEC_CONST_32
#   undef T1_CORE10_START_SEC_CONST_32
#   pragma section ".T1_constCore10" a
#elif defined T1_CORE10_STOP_SEC_CONST_32
#   undef T1_CORE10_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE11_START_SEC_CONST_32
#   undef T1_CORE11_START_SEC_CONST_32
#   pragma section ".T1_constCore11" a
#elif defined T1_CORE11_STOP_SEC_CONST_32
#   undef T1_CORE11_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE12_START_SEC_CONST_32
#   undef T1_CORE12_START_SEC_CONST_32
#   pragma section ".T1_constCore12" a
#elif defined T1_CORE12_STOP_SEC_CONST_32
#   undef T1_CORE12_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE13_START_SEC_CONST_32
#   undef T1_CORE13_START_SEC_CONST_32
#   pragma section ".T1_constCore13" a
#elif defined T1_CORE13_STOP_SEC_CONST_32
#   undef T1_CORE13_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CORE14_START_SEC_CONST_32
#   undef T1_CORE14_START_SEC_CONST_32
#   pragma section ".T1_constCore14" a
#elif defined T1_CORE14_STOP_SEC_CONST_32
#   undef T1_CORE14_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_CLONE_START_SEC_CONST_32
#   undef T1_CLONE_START_SEC_CONST_32
#   pragma section ".T1_constClone" a
#elif defined T1_CLONE_STOP_SEC_CONST_32
#   undef T1_CLONE_STOP_SEC_CONST_32
#   pragma section

#elif defined T1_START_SEC_VAR_CLEARED_32
#   undef T1_START_SEC_VAR_CLEARED_32
#   pragma section ".T1_clear" aBw
#elif defined T1_STOP_SEC_VAR_CLEARED_32
#   undef T1_STOP_SEC_VAR_CLEARED_32
#   pragma section

#elif defined T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbss" aBws
#elif defined T1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore0" aBws
#elif defined T1_CORE0_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE0_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore1" aBws
#elif defined T1_CORE1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore2" aBws
#elif defined T1_CORE2_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE2_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore3" aBws
#elif defined T1_CORE3_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE3_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore4" aBws
#elif defined T1_CORE4_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE4_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore5" aBws
#elif defined T1_CORE5_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE5_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore6" aBws
#elif defined T1_CORE6_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE6_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore7" aBws
#elif defined T1_CORE7_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE7_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore8" aBws
#elif defined T1_CORE8_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE8_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore9" aBws
#elif defined T1_CORE9_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE9_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore10" aBws
#elif defined T1_CORE10_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE10_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore11" aBws
#elif defined T1_CORE11_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE11_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore12" aBws
#elif defined T1_CORE12_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE12_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore13" aBws
#elif defined T1_CORE13_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE13_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCore14" aBws
#elif defined T1_CORE14_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE14_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssCoreComms" aBws
#elif defined T1_CORE_COMMS_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CORE_COMMS_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section ".T1_sbssClone" aBws
#elif defined T1_CLONE_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   undef T1_CLONE_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbss" aBws
#elif defined T1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore0" aBws
#elif defined T1_CORE0_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE0_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore1" aBws
#elif defined T1_CORE1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore2" aBws
#elif defined T1_CORE2_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE2_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore3" aBws
#elif defined T1_CORE3_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE3_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore4" aBws
#elif defined T1_CORE4_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE4_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore5" aBws
#elif defined T1_CORE5_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE5_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore6" aBws
#elif defined T1_CORE6_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE6_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore7" aBws
#elif defined T1_CORE7_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE7_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore8" aBws
#elif defined T1_CORE8_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE8_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore9" aBws
#elif defined T1_CORE9_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE9_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore10" aBws
#elif defined T1_CORE10_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE10_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore11" aBws
#elif defined T1_CORE11_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE11_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore12" aBws
#elif defined T1_CORE12_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE12_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore13" aBws
#elif defined T1_CORE13_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE13_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCore14" aBws
#elif defined T1_CORE14_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE14_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssCoreComms" aBws
#elif defined T1_CORE_COMMS_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CORE_COMMS_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section ".T1_sbssClone" aBws
#elif defined T1_CLONE_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   undef T1_CLONE_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbss" aBws
#elif defined T1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore0" aBws
#elif defined T1_CORE0_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE0_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore1" aBws
#elif defined T1_CORE1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE1_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore2" aBws
#elif defined T1_CORE2_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE2_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore3" aBws
#elif defined T1_CORE3_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE3_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore4" aBws
#elif defined T1_CORE4_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE4_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore5" aBws
#elif defined T1_CORE5_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE5_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore6" aBws
#elif defined T1_CORE6_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE6_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore7" aBws
#elif defined T1_CORE7_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE7_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore8" aBws
#elif defined T1_CORE8_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE8_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore9" aBws
#elif defined T1_CORE9_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE9_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore10" aBws
#elif defined T1_CORE10_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE10_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore11" aBws
#elif defined T1_CORE11_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE11_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore12" aBws
#elif defined T1_CORE12_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE12_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore13" aBws
#elif defined T1_CORE13_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE13_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCore14" aBws
#elif defined T1_CORE14_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE14_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssCoreComms" aBws
#elif defined T1_CORE_COMMS_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CORE_COMMS_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section ".T1_sbssClone" aBws
#elif defined T1_CLONE_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   undef T1_CLONE_STOP_SEC_VAR_NEAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bss" aBw
#elif defined T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore0" aBw
#elif defined T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore1" aBw
#elif defined T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore2" aBw
#elif defined T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore3" aBw
#elif defined T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore4" aBw
#elif defined T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore5" aBw
#elif defined T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore6" aBw
#elif defined T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore7" aBw
#elif defined T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore8" aBw
#elif defined T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore9" aBw
#elif defined T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore10" aBw
#elif defined T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore11" aBw
#elif defined T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore12" aBw
#elif defined T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore13" aBw
#elif defined T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCore14" aBw
#elif defined T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssCoreComms" aBw
#elif defined T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section ".T1_bssClone" aBw
#elif defined T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   undef T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_8
#   pragma section

#elif defined T1_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bss" aBw
#elif defined T1_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore0" aBw
#elif defined T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore1" aBw
#elif defined T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore2" aBw
#elif defined T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore3" aBw
#elif defined T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore4" aBw
#elif defined T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore5" aBw
#elif defined T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore6" aBw
#elif defined T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore7" aBw
#elif defined T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore8" aBw
#elif defined T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore9" aBw
#elif defined T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore10" aBw
#elif defined T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore11" aBw
#elif defined T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore12" aBw
#elif defined T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore13" aBw
#elif defined T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCore14" aBw
#elif defined T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssCoreComms" aBw
#elif defined T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section ".T1_bssClone" aBw
#elif defined T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   undef T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_16
#   pragma section

#elif defined T1_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bss" aBw
#elif defined T1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore0" aBw
#elif defined T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore1" aBw
#elif defined T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore2" aBw
#elif defined T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore3" aBw
#elif defined T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore4" aBw
#elif defined T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore5" aBw
#elif defined T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore6" aBw
#elif defined T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore7" aBw
#elif defined T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore8" aBw
#elif defined T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore9" aBw
#elif defined T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore10" aBw
#elif defined T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore11" aBw
#elif defined T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore12" aBw
#elif defined T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore13" aBw
#elif defined T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCore14" aBw
#elif defined T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCoreComms" aBw
#elif defined T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CORE_COMMS_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssClone" aBw
#elif defined T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssChecked" aBw
#elif defined T1_CHECKED_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore0" aBw
#elif defined T1_CHECKED_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore1" aBw
#elif defined T1_CHECKED_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore2" aBw
#elif defined T1_CHECKED_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore3" aBw
#elif defined T1_CHECKED_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore4" aBw
#elif defined T1_CHECKED_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore5" aBw
#elif defined T1_CHECKED_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore6" aBw
#elif defined T1_CHECKED_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore7" aBw
#elif defined T1_CHECKED_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore8" aBw
#elif defined T1_CHECKED_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore9" aBw
#elif defined T1_CHECKED_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore10" aBw
#elif defined T1_CHECKED_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore11" aBw
#elif defined T1_CHECKED_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore12" aBw
#elif defined T1_CHECKED_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore13" aBw
#elif defined T1_CHECKED_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedCore14" aBw
#elif defined T1_CHECKED_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_CHECKED_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_bssCheckedClone" aBw
#elif defined T1_CHECKED_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_CHECKED_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBuffer" aBw
#elif defined T1_TRACEBUFFER_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore0" aBw
#elif defined T1_TRACEBUFFER_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE0_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore1" aBw
#elif defined T1_TRACEBUFFER_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE1_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore2" aBw
#elif defined T1_TRACEBUFFER_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE2_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore3" aBw
#elif defined T1_TRACEBUFFER_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE3_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore4" aBw
#elif defined T1_TRACEBUFFER_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE4_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore5" aBw
#elif defined T1_TRACEBUFFER_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE5_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore6" aBw
#elif defined T1_TRACEBUFFER_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE6_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore7" aBw
#elif defined T1_TRACEBUFFER_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE7_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore8" aBw
#elif defined T1_TRACEBUFFER_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE8_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore9" aBw
#elif defined T1_TRACEBUFFER_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE9_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore10" aBw
#elif defined T1_TRACEBUFFER_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE10_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore11" aBw
#elif defined T1_TRACEBUFFER_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE11_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore12" aBw
#elif defined T1_TRACEBUFFER_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE12_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore13" aBw
#elif defined T1_TRACEBUFFER_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE13_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferCore14" aBw
#elif defined T1_TRACEBUFFER_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CORE14_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#elif defined T1_TRACEBUFFER_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section ".T1_traceBufferClone" aBw
#elif defined T1_TRACEBUFFER_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   undef T1_TRACEBUFFER_CLONE_STOP_SEC_VAR_POWER_ON_CLEARED_32
#   pragma section

#else
#   error "T1_MemMap.h: no valid section define used."
#endif

#if defined T1_DOXYGEN_ONLY
/*! \brief Code (in flash) shared by all cores */
#   define T1_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 0 */
#   define T1_CORE0_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 1 */
#   define T1_CORE1_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 2 */
#   define T1_CORE2_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 3 */
#   define T1_CORE3_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 4 */
#   define T1_CORE4_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 5 */
#   define T1_CORE5_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 6 */
#   define T1_CORE6_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 7 */
#   define T1_CORE7_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 8 */
#   define T1_CORE8_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 9 */
#   define T1_CORE9_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 10 */
#   define T1_CORE10_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 11 */
#   define T1_CORE11_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 12 */
#   define T1_CORE12_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 13 */
#   define T1_CORE13_START_SEC_CODE (1)
/*! \brief Code (in flash) for T1 logical core 14 */
#   define T1_CORE14_START_SEC_CODE (1)
/*! \brief Code relevant to T1-TARGET-SW overheads shared by all cores */
#   define T1_START_SEC_CODE_FAST (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 8-bit accesses shared by all cores */
#   define T1_START_SEC_CONST_8 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 16-bit accesses shared by all cores */
#   define T1_START_SEC_CONST_16 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses shared by all cores */
#   define T1_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 0 */
#   define T1_CORE0_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 1 */
#   define T1_CORE1_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 2 */
#   define T1_CORE2_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 3 */
#   define T1_CORE3_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 4 */
#   define T1_CORE4_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 5 */
#   define T1_CORE5_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 6 */
#   define T1_CORE6_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 7 */
#   define T1_CORE7_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 8 */
#   define T1_CORE8_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 9 */
#   define T1_CORE9_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 10 */
#   define T1_CORE10_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 11 */
#   define T1_CORE11_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 12 */
#   define T1_CORE12_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 13 */
#   define T1_CORE13_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses for T1 logical core 14 */
#   define T1_CORE14_START_SEC_CONST_32 (1)
/*! \brief Constant data (in flash or write-protected RAM) aligned for 32-bit accesses duplicated for each core */
#   define T1_CLONE_START_SEC_CONST_32 (1)
/*! \brief Shared zeroed RAM aligned for 32-bit accesses shared by all cores */
#   define T1_START_SEC_VAR_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses shared by all cores */
#   define T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 0 */
#   define T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 1 */
#   define T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 2 */
#   define T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 3 */
#   define T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 4 */
#   define T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 5 */
#   define T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 6 */
#   define T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 7 */
#   define T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 8 */
#   define T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 9 */
#   define T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 10 */
#   define T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 11 */
#   define T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 12 */
#   define T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 13 */
#   define T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 logical core 14 */
#   define T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses for T1 communications core */
#   define T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 8-bit accesses duplicated for each core */
#   define T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_8 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses shared by all cores */
#   define T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 0 */
#   define T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 1 */
#   define T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 2 */
#   define T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 3 */
#   define T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 4 */
#   define T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 5 */
#   define T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 6 */
#   define T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 7 */
#   define T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 8 */
#   define T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 9 */
#   define T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 10 */
#   define T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 11 */
#   define T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 12 */
#   define T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 13 */
#   define T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 logical core 14 */
#   define T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses for T1 communications core */
#   define T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 16-bit accesses duplicated for each core */
#   define T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_16 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses shared by all cores */
#   define T1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 0 */
#   define T1_CORE0_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 1 */
#   define T1_CORE1_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 2 */
#   define T1_CORE2_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 3 */
#   define T1_CORE3_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 4 */
#   define T1_CORE4_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 5 */
#   define T1_CORE5_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 6 */
#   define T1_CORE6_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 7 */
#   define T1_CORE7_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 8 */
#   define T1_CORE8_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 9 */
#   define T1_CORE9_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 10 */
#   define T1_CORE10_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 11 */
#   define T1_CORE11_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 12 */
#   define T1_CORE12_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 13 */
#   define T1_CORE13_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 logical core 14 */
#   define T1_CORE14_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses for T1 communications core */
#   define T1_CORE_COMMS_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Near uninitialized RAM aligned for 32-bit accesses duplicated for each core */
#   define T1_CLONE_START_SEC_VAR_NEAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses shared by all cores */
#   define T1_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 0 */
#   define T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 1 */
#   define T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 2 */
#   define T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 3 */
#   define T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 4 */
#   define T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 5 */
#   define T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 6 */
#   define T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 7 */
#   define T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 8 */
#   define T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 9 */
#   define T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 10 */
#   define T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 11 */
#   define T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 12 */
#   define T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 13 */
#   define T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 logical core 14 */
#   define T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses for T1 communications core */
#   define T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 8-bit accesses duplicated for each core */
#   define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_8 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses shared by all cores */
#   define T1_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 0 */
#   define T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 1 */
#   define T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 2 */
#   define T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 3 */
#   define T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 4 */
#   define T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 5 */
#   define T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 6 */
#   define T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 7 */
#   define T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 8 */
#   define T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 9 */
#   define T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 10 */
#   define T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 11 */
#   define T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 12 */
#   define T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 13 */
#   define T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 logical core 14 */
#   define T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses for T1 communications core */
#   define T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 16-bit accesses duplicated for each core */
#   define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_16 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses shared by all cores */
#   define T1_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 0 */
#   define T1_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 1 */
#   define T1_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 2 */
#   define T1_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 3 */
#   define T1_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 4 */
#   define T1_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 5 */
#   define T1_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 6 */
#   define T1_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 7 */
#   define T1_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 8 */
#   define T1_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 9 */
#   define T1_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 10 */
#   define T1_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 11 */
#   define T1_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 12 */
#   define T1_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 13 */
#   define T1_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 logical core 14 */
#   define T1_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses for T1 communications core */
#   define T1_CORE_COMMS_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM aligned for 32-bit accesses duplicated for each core */
#   define T1_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses shared by all cores */
#   define T1_CHECKED_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 0 */
#   define T1_CHECKED_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 1 */
#   define T1_CHECKED_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 2 */
#   define T1_CHECKED_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 3 */
#   define T1_CHECKED_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 4 */
#   define T1_CHECKED_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 5 */
#   define T1_CHECKED_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 6 */
#   define T1_CHECKED_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 7 */
#   define T1_CHECKED_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 8 */
#   define T1_CHECKED_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 9 */
#   define T1_CHECKED_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 10 */
#   define T1_CHECKED_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 11 */
#   define T1_CHECKED_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 12 */
#   define T1_CHECKED_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 13 */
#   define T1_CHECKED_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses for T1 logical core 14 */
#   define T1_CHECKED_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Uninitialized RAM with protection against corruption aligned for 32-bit accesses duplicated for each core */
#   define T1_CHECKED_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses shared by all cores */
#   define T1_TRACEBUFFER_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 0 */
#   define T1_TRACEBUFFER_CORE0_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 1 */
#   define T1_TRACEBUFFER_CORE1_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 2 */
#   define T1_TRACEBUFFER_CORE2_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 3 */
#   define T1_TRACEBUFFER_CORE3_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 4 */
#   define T1_TRACEBUFFER_CORE4_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 5 */
#   define T1_TRACEBUFFER_CORE5_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 6 */
#   define T1_TRACEBUFFER_CORE6_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 7 */
#   define T1_TRACEBUFFER_CORE7_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 8 */
#   define T1_TRACEBUFFER_CORE8_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 9 */
#   define T1_TRACEBUFFER_CORE9_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 10 */
#   define T1_TRACEBUFFER_CORE10_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 11 */
#   define T1_TRACEBUFFER_CORE11_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 12 */
#   define T1_TRACEBUFFER_CORE12_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 13 */
#   define T1_TRACEBUFFER_CORE13_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses for T1 logical core 14 */
#   define T1_TRACEBUFFER_CORE14_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
/*! \brief Trace buffer RAM aligned for 32-bit accesses duplicated for each core */
#   define T1_TRACEBUFFER_CLONE_START_SEC_VAR_POWER_ON_CLEARED_32 (1)
#endif /* defined T1_DOXYGEN_ONLY */
