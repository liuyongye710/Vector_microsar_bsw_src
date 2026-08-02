/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: China FAW Group Corporation
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC297TA
 *    License Scope : The usage is restricted to CBD1600956_D02
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Link_Core1_Stacks.lsl
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  STACK SECTIONS
 *********************************************************************************************************************/

#if defined ( OS_LINK_KERNEL_STACKS )
group OS_CORE1_STACKS_GROUP(ordered, contiguous, fill)
{

/* Stack: OsCore1_Init (1024 Byte) */
group OS_STACK_OSCORE1_INIT_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_INIT_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_INIT_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_INIT_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_INIT_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_INIT_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_INIT_VAR_NOINIT";

/* Stack: OsCore1_Isr_Core (1024 Byte) */
group OS_STACK_OSCORE1_ISR_CORE_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_ISR_CORE_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_ISR_CORE_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_ISR_CORE_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_ISR_CORE_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_ISR_CORE_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_ISR_CORE_VAR_NOINIT";

/* Stack: OsCore1_Kernel (1024 Byte) */
group OS_STACK_OSCORE1_KERNEL_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_KERNEL_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_KERNEL_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_KERNEL_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_KERNEL_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_KERNEL_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_KERNEL_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio100 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO100_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio4294967295 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO4294967295_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio51 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO51_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio52 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO52_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio53 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO53_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio54 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO54_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio55 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO55_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio56 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO56_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio57 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO57_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio58 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO58_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio59 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO59_VAR_NOINIT";

/* Stack: OsCore1_Task_Prio90 (1024 Byte) */
group OS_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
{
  select ".bss.OS_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT";
  reserved ".pad.OS_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT" (size=16);
}
"_OS_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT_START" = "_lc_gb_OS_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT_GROUP";
"_OS_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT_END" = "_lc_ub__pad_OS_STACK_OSCORE1_TASK_PRIO90_VAR_NOINIT";



} /* OS_CORE1_STACKS_GROUP */
"_OS_CORE1_STACKS_START" = "_lc_gb_OS_CORE1_STACKS_GROUP";
"_OS_CORE1_STACKS_END" = "_lc_ge_OS_CORE1_STACKS_GROUP";
"_OS_CORE1_STACKS_END_ALIAS" = (("_lc_ge_OS_CORE1_STACKS_GROUP")&~0xF0000000)|0xD0000000;

#endif

#ifdef OS_LINK_KERNEL_STACKS
# undef OS_LINK_KERNEL_STACKS
#endif


