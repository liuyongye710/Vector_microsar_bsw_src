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
 *              File: Os_Link_Core1.lsl
 *   Generation Time: 2020-07-28 15:56:23
 *           Project: FAW_MultiCore297_Demo - Version 1.0
 *          Delivery: CBD1600956_D02
 *      Tool Version: DaVinci Configurator  5.17.51 SP2
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CODE SECTIONS
 *********************************************************************************************************************/

#if defined ( OS_LINK_INTVEC_CODE )
if (exists(".text.OS_INTVEC_CORE1_CODE"))
{
  group OS_INTVEC_CORE1_CODE_GROUP(align=32)
  {
    select ".text.OS_INTVEC_CORE1_CODE";
  }
  "_OS_INTVEC_CORE1_CODE_START" = "_lc_gb_OS_INTVEC_CORE1_CODE_GROUP";
  "_OS_INTVEC_CORE1_CODE_END" = "_lc_ge_OS_INTVEC_CORE1_CODE_GROUP";
}
else
{
  "_OS_INTVEC_CORE1_CODE_START" = 0;
  "_OS_INTVEC_CORE1_CODE_END" = 0;
}
#endif

#if defined ( OS_LINK_EXCVEC_CODE )
if (exists(".text.OS_EXCVEC_CORE1_CODE"))
{
  group OS_EXCVEC_CORE1_CODE_GROUP(align=32)
  {
    select ".text.OS_EXCVEC_CORE1_CODE";
  }
  "_OS_EXCVEC_CORE1_CODE_START" = "_lc_gb_OS_EXCVEC_CORE1_CODE_GROUP";
  "_OS_EXCVEC_CORE1_CODE_END" = "_lc_ge_OS_EXCVEC_CORE1_CODE_GROUP";
}
else
{
  "_OS_EXCVEC_CORE1_CODE_START" = 0;
  "_OS_EXCVEC_CORE1_CODE_END" = 0;
}
#endif

#if defined ( OS_LINK_CALLOUT_CODE )
if (exists(".text.OS_Adc0Sr0_Isr_CODE"))
{
  group OS_Adc0Sr0_Isr_CODE_GROUP(align=8)
  {
    select ".text.OS_Adc0Sr0_Isr_CODE";
  }
  "_OS_Adc0Sr0_Isr_CODE_START" = "_lc_gb_OS_Adc0Sr0_Isr_CODE_GROUP";
  "_OS_Adc0Sr0_Isr_CODE_END" = "_lc_ge_OS_Adc0Sr0_Isr_CODE_GROUP";
}
else
{
  "_OS_Adc0Sr0_Isr_CODE_START" = 0;
  "_OS_Adc0Sr0_Isr_CODE_END" = 0;
}
if (exists(".text.OS_Adc1Sr0_Isr_CODE"))
{
  group OS_Adc1Sr0_Isr_CODE_GROUP(align=8)
  {
    select ".text.OS_Adc1Sr0_Isr_CODE";
  }
  "_OS_Adc1Sr0_Isr_CODE_START" = "_lc_gb_OS_Adc1Sr0_Isr_CODE_GROUP";
  "_OS_Adc1Sr0_Isr_CODE_END" = "_lc_ge_OS_Adc1Sr0_Isr_CODE_GROUP";
}
else
{
  "_OS_Adc1Sr0_Isr_CODE_START" = 0;
  "_OS_Adc1Sr0_Isr_CODE_END" = 0;
}
if (exists(".text.OS_Adc2Sr0_Isr_CODE"))
{
  group OS_Adc2Sr0_Isr_CODE_GROUP(align=8)
  {
    select ".text.OS_Adc2Sr0_Isr_CODE";
  }
  "_OS_Adc2Sr0_Isr_CODE_START" = "_lc_gb_OS_Adc2Sr0_Isr_CODE_GROUP";
  "_OS_Adc2Sr0_Isr_CODE_END" = "_lc_ge_OS_Adc2Sr0_Isr_CODE_GROUP";
}
else
{
  "_OS_Adc2Sr0_Isr_CODE_START" = 0;
  "_OS_Adc2Sr0_Isr_CODE_END" = 0;
}
if (exists(".text.OS_Adc3Sr0_Isr_CODE"))
{
  group OS_Adc3Sr0_Isr_CODE_GROUP(align=8)
  {
    select ".text.OS_Adc3Sr0_Isr_CODE";
  }
  "_OS_Adc3Sr0_Isr_CODE_START" = "_lc_gb_OS_Adc3Sr0_Isr_CODE_GROUP";
  "_OS_Adc3Sr0_Isr_CODE_END" = "_lc_ge_OS_Adc3Sr0_Isr_CODE_GROUP";
}
else
{
  "_OS_Adc3Sr0_Isr_CODE_START" = 0;
  "_OS_Adc3Sr0_Isr_CODE_END" = 0;
}
if (exists(".text.OS_Adc4Sr0_Isr_CODE"))
{
  group OS_Adc4Sr0_Isr_CODE_GROUP(align=8)
  {
    select ".text.OS_Adc4Sr0_Isr_CODE";
  }
  "_OS_Adc4Sr0_Isr_CODE_START" = "_lc_gb_OS_Adc4Sr0_Isr_CODE_GROUP";
  "_OS_Adc4Sr0_Isr_CODE_END" = "_lc_ge_OS_Adc4Sr0_Isr_CODE_GROUP";
}
else
{
  "_OS_Adc4Sr0_Isr_CODE_START" = 0;
  "_OS_Adc4Sr0_Isr_CODE_END" = 0;
}
if (exists(".text.OS_Adc5Sr0_Isr_CODE"))
{
  group OS_Adc5Sr0_Isr_CODE_GROUP(align=8)
  {
    select ".text.OS_Adc5Sr0_Isr_CODE";
  }
  "_OS_Adc5Sr0_Isr_CODE_START" = "_lc_gb_OS_Adc5Sr0_Isr_CODE_GROUP";
  "_OS_Adc5Sr0_Isr_CODE_END" = "_lc_ge_OS_Adc5Sr0_Isr_CODE_GROUP";
}
else
{
  "_OS_Adc5Sr0_Isr_CODE_START" = 0;
  "_OS_Adc5Sr0_Isr_CODE_END" = 0;
}
if (exists(".text.OS_Adc6Sr0_Isr_CODE"))
{
  group OS_Adc6Sr0_Isr_CODE_GROUP(align=8)
  {
    select ".text.OS_Adc6Sr0_Isr_CODE";
  }
  "_OS_Adc6Sr0_Isr_CODE_START" = "_lc_gb_OS_Adc6Sr0_Isr_CODE_GROUP";
  "_OS_Adc6Sr0_Isr_CODE_END" = "_lc_ge_OS_Adc6Sr0_Isr_CODE_GROUP";
}
else
{
  "_OS_Adc6Sr0_Isr_CODE_START" = 0;
  "_OS_Adc6Sr0_Isr_CODE_END" = 0;
}
if (exists(".text.OS_Isr_TIM02_CODE"))
{
  group OS_Isr_TIM02_CODE_GROUP(align=8)
  {
    select ".text.OS_Isr_TIM02_CODE";
  }
  "_OS_Isr_TIM02_CODE_START" = "_lc_gb_OS_Isr_TIM02_CODE_GROUP";
  "_OS_Isr_TIM02_CODE_END" = "_lc_ge_OS_Isr_TIM02_CODE_GROUP";
}
else
{
  "_OS_Isr_TIM02_CODE_START" = 0;
  "_OS_Isr_TIM02_CODE_END" = 0;
}
if (exists(".text.OS_Isr_TIM03_CODE"))
{
  group OS_Isr_TIM03_CODE_GROUP(align=8)
  {
    select ".text.OS_Isr_TIM03_CODE";
  }
  "_OS_Isr_TIM03_CODE_START" = "_lc_gb_OS_Isr_TIM03_CODE_GROUP";
  "_OS_Isr_TIM03_CODE_END" = "_lc_ge_OS_Isr_TIM03_CODE_GROUP";
}
else
{
  "_OS_Isr_TIM03_CODE_START" = 0;
  "_OS_Isr_TIM03_CODE_END" = 0;
}
if (exists(".text.OS_Task1000ms_Core1_CODE"))
{
  group OS_Task1000ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task1000ms_Core1_CODE";
  }
  "_OS_Task1000ms_Core1_CODE_START" = "_lc_gb_OS_Task1000ms_Core1_CODE_GROUP";
  "_OS_Task1000ms_Core1_CODE_END" = "_lc_ge_OS_Task1000ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task1000ms_Core1_CODE_START" = 0;
  "_OS_Task1000ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_Task100ms_Core1_CODE"))
{
  group OS_Task100ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task100ms_Core1_CODE";
  }
  "_OS_Task100ms_Core1_CODE_START" = "_lc_gb_OS_Task100ms_Core1_CODE_GROUP";
  "_OS_Task100ms_Core1_CODE_END" = "_lc_ge_OS_Task100ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task100ms_Core1_CODE_START" = 0;
  "_OS_Task100ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_Task10ms_Core1_CODE"))
{
  group OS_Task10ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task10ms_Core1_CODE";
  }
  "_OS_Task10ms_Core1_CODE_START" = "_lc_gb_OS_Task10ms_Core1_CODE_GROUP";
  "_OS_Task10ms_Core1_CODE_END" = "_lc_ge_OS_Task10ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task10ms_Core1_CODE_START" = 0;
  "_OS_Task10ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_Task1ms_Core1_CODE"))
{
  group OS_Task1ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task1ms_Core1_CODE";
  }
  "_OS_Task1ms_Core1_CODE_START" = "_lc_gb_OS_Task1ms_Core1_CODE_GROUP";
  "_OS_Task1ms_Core1_CODE_END" = "_lc_ge_OS_Task1ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task1ms_Core1_CODE_START" = 0;
  "_OS_Task1ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_Task200ms_Core1_CODE"))
{
  group OS_Task200ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task200ms_Core1_CODE";
  }
  "_OS_Task200ms_Core1_CODE_START" = "_lc_gb_OS_Task200ms_Core1_CODE_GROUP";
  "_OS_Task200ms_Core1_CODE_END" = "_lc_ge_OS_Task200ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task200ms_Core1_CODE_START" = 0;
  "_OS_Task200ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_Task20ms_Core1_CODE"))
{
  group OS_Task20ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task20ms_Core1_CODE";
  }
  "_OS_Task20ms_Core1_CODE_START" = "_lc_gb_OS_Task20ms_Core1_CODE_GROUP";
  "_OS_Task20ms_Core1_CODE_END" = "_lc_ge_OS_Task20ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task20ms_Core1_CODE_START" = 0;
  "_OS_Task20ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_Task500ms_Core1_CODE"))
{
  group OS_Task500ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task500ms_Core1_CODE";
  }
  "_OS_Task500ms_Core1_CODE_START" = "_lc_gb_OS_Task500ms_Core1_CODE_GROUP";
  "_OS_Task500ms_Core1_CODE_END" = "_lc_ge_OS_Task500ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task500ms_Core1_CODE_START" = 0;
  "_OS_Task500ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_Task50ms_Core1_CODE"))
{
  group OS_Task50ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task50ms_Core1_CODE";
  }
  "_OS_Task50ms_Core1_CODE_START" = "_lc_gb_OS_Task50ms_Core1_CODE_GROUP";
  "_OS_Task50ms_Core1_CODE_END" = "_lc_ge_OS_Task50ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task50ms_Core1_CODE_START" = 0;
  "_OS_Task50ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_Task5ms_Core1_CODE"))
{
  group OS_Task5ms_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_Task5ms_Core1_CODE";
  }
  "_OS_Task5ms_Core1_CODE_START" = "_lc_gb_OS_Task5ms_Core1_CODE_GROUP";
  "_OS_Task5ms_Core1_CODE_END" = "_lc_ge_OS_Task5ms_Core1_CODE_GROUP";
}
else
{
  "_OS_Task5ms_Core1_CODE_START" = 0;
  "_OS_Task5ms_Core1_CODE_END" = 0;
}
if (exists(".text.OS_TaskInit_Core1_CODE"))
{
  group OS_TaskInit_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_TaskInit_Core1_CODE";
  }
  "_OS_TaskInit_Core1_CODE_START" = "_lc_gb_OS_TaskInit_Core1_CODE_GROUP";
  "_OS_TaskInit_Core1_CODE_END" = "_lc_ge_OS_TaskInit_Core1_CODE_GROUP";
}
else
{
  "_OS_TaskInit_Core1_CODE_START" = 0;
  "_OS_TaskInit_Core1_CODE_END" = 0;
}
if (exists(".text.OS_TaskSchM_Core1_CODE"))
{
  group OS_TaskSchM_Core1_CODE_GROUP(align=8)
  {
    select ".text.OS_TaskSchM_Core1_CODE";
  }
  "_OS_TaskSchM_Core1_CODE_START" = "_lc_gb_OS_TaskSchM_Core1_CODE_GROUP";
  "_OS_TaskSchM_Core1_CODE_END" = "_lc_ge_OS_TaskSchM_Core1_CODE_GROUP";
}
else
{
  "_OS_TaskSchM_Core1_CODE_START" = 0;
  "_OS_TaskSchM_Core1_CODE_END" = 0;
}
#endif

#ifdef OS_LINK_INTVEC_CODE
# undef OS_LINK_INTVEC_CODE
#endif

#ifdef OS_LINK_EXCVEC_CODE
# undef OS_LINK_EXCVEC_CODE
#endif

#ifdef OS_LINK_CALLOUT_CODE
# undef OS_LINK_CALLOUT_CODE
#endif


/**********************************************************************************************************************
 *  CONST SECTIONS
 *********************************************************************************************************************/

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_KERNEL ) || defined ( OS_LINK_CONST_KERNEL_FAR )
if (exists(".rodata.OS_CORE1_CONST"))
{
  group OS_CORE1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_CORE1_CONST";
  }
  "_OS_CORE1_CONST_START" = "_lc_gb_OS_CORE1_CONST_GROUP";
  "_OS_CORE1_CONST_END" = "_lc_ge_OS_CORE1_CONST_GROUP";
}
else
{
  "_OS_CORE1_CONST_START" = 0;
  "_OS_CORE1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_KERNEL ) || defined ( OS_LINK_CONST_KERNEL_NEAR )
if (exists(".zrodata.OS_CORE1_CONST_FAST"))
{
  group OS_CORE1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_CORE1_CONST_FAST";
  }
  "_OS_CORE1_CONST_FAST_START" = "_lc_gb_OS_CORE1_CONST_FAST_GROUP";
  "_OS_CORE1_CONST_FAST_END" = "_lc_ge_OS_CORE1_CONST_FAST_GROUP";
}
else
{
  "_OS_CORE1_CONST_FAST_START" = 0;
  "_OS_CORE1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_INTVEC_CONST )
if (exists(".rodata.OS_INTVEC_CORE1_CONST"))
{
  group OS_INTVEC_CORE1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_INTVEC_CORE1_CONST";
  }
  "_OS_INTVEC_CORE1_CONST_START" = "_lc_gb_OS_INTVEC_CORE1_CONST_GROUP";
  "_OS_INTVEC_CORE1_CONST_END" = "_lc_ge_OS_INTVEC_CORE1_CONST_GROUP";
}
else
{
  "_OS_INTVEC_CORE1_CONST_START" = 0;
  "_OS_INTVEC_CORE1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_EXCVEC_CONST )
if (exists(".rodata.OS_EXCVEC_CORE1_CONST"))
{
  group OS_EXCVEC_CORE1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_EXCVEC_CORE1_CONST";
  }
  "_OS_EXCVEC_CORE1_CONST_START" = "_lc_gb_OS_EXCVEC_CORE1_CONST_GROUP";
  "_OS_EXCVEC_CORE1_CONST_END" = "_lc_ge_OS_EXCVEC_CORE1_CONST_GROUP";
}
else
{
  "_OS_EXCVEC_CORE1_CONST_START" = 0;
  "_OS_EXCVEC_CORE1_CONST_END" = 0;
}
#endif


#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_APP ) || defined ( OS_LINK_CONST_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_CONST_APP_OSAPPLICATION_CORE1_FAR )
if (exists(".rodata.OS_OsApplication_Core1_CONST"))
{
  group OS_OsApplication_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_OsApplication_Core1_CONST";
  }
  "_OS_OsApplication_Core1_CONST_START" = "_lc_gb_OS_OsApplication_Core1_CONST_GROUP";
  "_OS_OsApplication_Core1_CONST_END" = "_lc_ge_OS_OsApplication_Core1_CONST_GROUP";
}
else
{
  "_OS_OsApplication_Core1_CONST_START" = 0;
  "_OS_OsApplication_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_APP ) || defined ( OS_LINK_CONST_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_CONST_APP_OSAPPLICATION_CORE1_NEAR )
if (exists(".zrodata.OS_OsApplication_Core1_CONST_FAST"))
{
  group OS_OsApplication_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_OsApplication_Core1_CONST_FAST";
  }
  "_OS_OsApplication_Core1_CONST_FAST_START" = "_lc_gb_OS_OsApplication_Core1_CONST_FAST_GROUP";
  "_OS_OsApplication_Core1_CONST_FAST_END" = "_lc_ge_OS_OsApplication_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_OsApplication_Core1_CONST_FAST_START" = 0;
  "_OS_OsApplication_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_APP ) || defined ( OS_LINK_CONST_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_CONST_APP_OSAPPLICATION_CORE1_INIT )
















#endif

#ifdef OS_LINK_CONST_APP_OSAPPLICATION_CORE1
# undef OS_LINK_CONST_APP_OSAPPLICATION_CORE1
#endif

#ifdef OS_LINK_CONST_APP_OSAPPLICATION_CORE1_FAR
# undef OS_LINK_CONST_APP_OSAPPLICATION_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_APP_OSAPPLICATION_CORE1_NEAR
# undef OS_LINK_CONST_APP_OSAPPLICATION_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_APP_OSAPPLICATION_CORE1_INIT
# undef OS_LINK_CONST_APP_OSAPPLICATION_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_APP ) || defined ( OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_FAR )
if (exists(".rodata.OS_SystemApplication_OsCore1_CONST"))
{
  group OS_SystemApplication_OsCore1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_SystemApplication_OsCore1_CONST";
  }
  "_OS_SystemApplication_OsCore1_CONST_START" = "_lc_gb_OS_SystemApplication_OsCore1_CONST_GROUP";
  "_OS_SystemApplication_OsCore1_CONST_END" = "_lc_ge_OS_SystemApplication_OsCore1_CONST_GROUP";
}
else
{
  "_OS_SystemApplication_OsCore1_CONST_START" = 0;
  "_OS_SystemApplication_OsCore1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_APP ) || defined ( OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_NEAR )
if (exists(".zrodata.OS_SystemApplication_OsCore1_CONST_FAST"))
{
  group OS_SystemApplication_OsCore1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_SystemApplication_OsCore1_CONST_FAST";
  }
  "_OS_SystemApplication_OsCore1_CONST_FAST_START" = "_lc_gb_OS_SystemApplication_OsCore1_CONST_FAST_GROUP";
  "_OS_SystemApplication_OsCore1_CONST_FAST_END" = "_lc_ge_OS_SystemApplication_OsCore1_CONST_FAST_GROUP";
}
else
{
  "_OS_SystemApplication_OsCore1_CONST_FAST_START" = 0;
  "_OS_SystemApplication_OsCore1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_APP ) || defined ( OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_INIT )
















#endif

#ifdef OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1
# undef OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1
#endif

#ifdef OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_FAR
# undef OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_FAR
#endif

#ifdef OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_NEAR
# undef OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_NEAR
#endif

#ifdef OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_INIT
# undef OS_LINK_CONST_APP_SYSTEMAPPLICATION_OSCORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_CONST_TASK_IDLETASK_OSCORE1_FAR )
if (exists(".rodata.OS_IdleTask_OsCore1_CONST"))
{
  group OS_IdleTask_OsCore1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_IdleTask_OsCore1_CONST";
  }
  "_OS_IdleTask_OsCore1_CONST_START" = "_lc_gb_OS_IdleTask_OsCore1_CONST_GROUP";
  "_OS_IdleTask_OsCore1_CONST_END" = "_lc_ge_OS_IdleTask_OsCore1_CONST_GROUP";
}
else
{
  "_OS_IdleTask_OsCore1_CONST_START" = 0;
  "_OS_IdleTask_OsCore1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_CONST_TASK_IDLETASK_OSCORE1_NEAR )
if (exists(".zrodata.OS_IdleTask_OsCore1_CONST_FAST"))
{
  group OS_IdleTask_OsCore1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_IdleTask_OsCore1_CONST_FAST";
  }
  "_OS_IdleTask_OsCore1_CONST_FAST_START" = "_lc_gb_OS_IdleTask_OsCore1_CONST_FAST_GROUP";
  "_OS_IdleTask_OsCore1_CONST_FAST_END" = "_lc_ge_OS_IdleTask_OsCore1_CONST_FAST_GROUP";
}
else
{
  "_OS_IdleTask_OsCore1_CONST_FAST_START" = 0;
  "_OS_IdleTask_OsCore1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_CONST_TASK_IDLETASK_OSCORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_IDLETASK_OSCORE1
# undef OS_LINK_CONST_TASK_IDLETASK_OSCORE1
#endif

#ifdef OS_LINK_CONST_TASK_IDLETASK_OSCORE1_FAR
# undef OS_LINK_CONST_TASK_IDLETASK_OSCORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_IDLETASK_OSCORE1_NEAR
# undef OS_LINK_CONST_TASK_IDLETASK_OSCORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_IDLETASK_OSCORE1_INIT
# undef OS_LINK_CONST_TASK_IDLETASK_OSCORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK1000MS_CORE1_FAR )
if (exists(".rodata.OS_Task1000ms_Core1_CONST"))
{
  group OS_Task1000ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task1000ms_Core1_CONST";
  }
  "_OS_Task1000ms_Core1_CONST_START" = "_lc_gb_OS_Task1000ms_Core1_CONST_GROUP";
  "_OS_Task1000ms_Core1_CONST_END" = "_lc_ge_OS_Task1000ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task1000ms_Core1_CONST_START" = 0;
  "_OS_Task1000ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK1000MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task1000ms_Core1_CONST_FAST"))
{
  group OS_Task1000ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task1000ms_Core1_CONST_FAST";
  }
  "_OS_Task1000ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task1000ms_Core1_CONST_FAST_GROUP";
  "_OS_Task1000ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task1000ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task1000ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task1000ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK1000MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK1000MS_CORE1
# undef OS_LINK_CONST_TASK_TASK1000MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK1000MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK1000MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK1000MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK1000MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK1000MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK1000MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK100MS_CORE1_FAR )
if (exists(".rodata.OS_Task100ms_Core1_CONST"))
{
  group OS_Task100ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task100ms_Core1_CONST";
  }
  "_OS_Task100ms_Core1_CONST_START" = "_lc_gb_OS_Task100ms_Core1_CONST_GROUP";
  "_OS_Task100ms_Core1_CONST_END" = "_lc_ge_OS_Task100ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task100ms_Core1_CONST_START" = 0;
  "_OS_Task100ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK100MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task100ms_Core1_CONST_FAST"))
{
  group OS_Task100ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task100ms_Core1_CONST_FAST";
  }
  "_OS_Task100ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task100ms_Core1_CONST_FAST_GROUP";
  "_OS_Task100ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task100ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task100ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task100ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK100MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK100MS_CORE1
# undef OS_LINK_CONST_TASK_TASK100MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK100MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK100MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK100MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK100MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK100MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK100MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK10MS_CORE1_FAR )
if (exists(".rodata.OS_Task10ms_Core1_CONST"))
{
  group OS_Task10ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task10ms_Core1_CONST";
  }
  "_OS_Task10ms_Core1_CONST_START" = "_lc_gb_OS_Task10ms_Core1_CONST_GROUP";
  "_OS_Task10ms_Core1_CONST_END" = "_lc_ge_OS_Task10ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task10ms_Core1_CONST_START" = 0;
  "_OS_Task10ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK10MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task10ms_Core1_CONST_FAST"))
{
  group OS_Task10ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task10ms_Core1_CONST_FAST";
  }
  "_OS_Task10ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task10ms_Core1_CONST_FAST_GROUP";
  "_OS_Task10ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task10ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task10ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task10ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK10MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK10MS_CORE1
# undef OS_LINK_CONST_TASK_TASK10MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK10MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK10MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK10MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK10MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK10MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK10MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK1MS_CORE1_FAR )
if (exists(".rodata.OS_Task1ms_Core1_CONST"))
{
  group OS_Task1ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task1ms_Core1_CONST";
  }
  "_OS_Task1ms_Core1_CONST_START" = "_lc_gb_OS_Task1ms_Core1_CONST_GROUP";
  "_OS_Task1ms_Core1_CONST_END" = "_lc_ge_OS_Task1ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task1ms_Core1_CONST_START" = 0;
  "_OS_Task1ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK1MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task1ms_Core1_CONST_FAST"))
{
  group OS_Task1ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task1ms_Core1_CONST_FAST";
  }
  "_OS_Task1ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task1ms_Core1_CONST_FAST_GROUP";
  "_OS_Task1ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task1ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task1ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task1ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK1MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK1MS_CORE1
# undef OS_LINK_CONST_TASK_TASK1MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK1MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK1MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK1MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK1MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK1MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK1MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK200MS_CORE1_FAR )
if (exists(".rodata.OS_Task200ms_Core1_CONST"))
{
  group OS_Task200ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task200ms_Core1_CONST";
  }
  "_OS_Task200ms_Core1_CONST_START" = "_lc_gb_OS_Task200ms_Core1_CONST_GROUP";
  "_OS_Task200ms_Core1_CONST_END" = "_lc_ge_OS_Task200ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task200ms_Core1_CONST_START" = 0;
  "_OS_Task200ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK200MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task200ms_Core1_CONST_FAST"))
{
  group OS_Task200ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task200ms_Core1_CONST_FAST";
  }
  "_OS_Task200ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task200ms_Core1_CONST_FAST_GROUP";
  "_OS_Task200ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task200ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task200ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task200ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK200MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK200MS_CORE1
# undef OS_LINK_CONST_TASK_TASK200MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK200MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK200MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK200MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK200MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK200MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK200MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK20MS_CORE1_FAR )
if (exists(".rodata.OS_Task20ms_Core1_CONST"))
{
  group OS_Task20ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task20ms_Core1_CONST";
  }
  "_OS_Task20ms_Core1_CONST_START" = "_lc_gb_OS_Task20ms_Core1_CONST_GROUP";
  "_OS_Task20ms_Core1_CONST_END" = "_lc_ge_OS_Task20ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task20ms_Core1_CONST_START" = 0;
  "_OS_Task20ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK20MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task20ms_Core1_CONST_FAST"))
{
  group OS_Task20ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task20ms_Core1_CONST_FAST";
  }
  "_OS_Task20ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task20ms_Core1_CONST_FAST_GROUP";
  "_OS_Task20ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task20ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task20ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task20ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK20MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK20MS_CORE1
# undef OS_LINK_CONST_TASK_TASK20MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK20MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK20MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK20MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK20MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK20MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK20MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK500MS_CORE1_FAR )
if (exists(".rodata.OS_Task500ms_Core1_CONST"))
{
  group OS_Task500ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task500ms_Core1_CONST";
  }
  "_OS_Task500ms_Core1_CONST_START" = "_lc_gb_OS_Task500ms_Core1_CONST_GROUP";
  "_OS_Task500ms_Core1_CONST_END" = "_lc_ge_OS_Task500ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task500ms_Core1_CONST_START" = 0;
  "_OS_Task500ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK500MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task500ms_Core1_CONST_FAST"))
{
  group OS_Task500ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task500ms_Core1_CONST_FAST";
  }
  "_OS_Task500ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task500ms_Core1_CONST_FAST_GROUP";
  "_OS_Task500ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task500ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task500ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task500ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK500MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK500MS_CORE1
# undef OS_LINK_CONST_TASK_TASK500MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK500MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK500MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK500MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK500MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK500MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK500MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK50MS_CORE1_FAR )
if (exists(".rodata.OS_Task50ms_Core1_CONST"))
{
  group OS_Task50ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task50ms_Core1_CONST";
  }
  "_OS_Task50ms_Core1_CONST_START" = "_lc_gb_OS_Task50ms_Core1_CONST_GROUP";
  "_OS_Task50ms_Core1_CONST_END" = "_lc_ge_OS_Task50ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task50ms_Core1_CONST_START" = 0;
  "_OS_Task50ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK50MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task50ms_Core1_CONST_FAST"))
{
  group OS_Task50ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task50ms_Core1_CONST_FAST";
  }
  "_OS_Task50ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task50ms_Core1_CONST_FAST_GROUP";
  "_OS_Task50ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task50ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task50ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task50ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK50MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK50MS_CORE1
# undef OS_LINK_CONST_TASK_TASK50MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK50MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK50MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK50MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK50MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK50MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK50MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK5MS_CORE1_FAR )
if (exists(".rodata.OS_Task5ms_Core1_CONST"))
{
  group OS_Task5ms_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Task5ms_Core1_CONST";
  }
  "_OS_Task5ms_Core1_CONST_START" = "_lc_gb_OS_Task5ms_Core1_CONST_GROUP";
  "_OS_Task5ms_Core1_CONST_END" = "_lc_ge_OS_Task5ms_Core1_CONST_GROUP";
}
else
{
  "_OS_Task5ms_Core1_CONST_START" = 0;
  "_OS_Task5ms_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK5MS_CORE1_NEAR )
if (exists(".zrodata.OS_Task5ms_Core1_CONST_FAST"))
{
  group OS_Task5ms_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Task5ms_Core1_CONST_FAST";
  }
  "_OS_Task5ms_Core1_CONST_FAST_START" = "_lc_gb_OS_Task5ms_Core1_CONST_FAST_GROUP";
  "_OS_Task5ms_Core1_CONST_FAST_END" = "_lc_ge_OS_Task5ms_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_Task5ms_Core1_CONST_FAST_START" = 0;
  "_OS_Task5ms_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASK5MS_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASK5MS_CORE1
# undef OS_LINK_CONST_TASK_TASK5MS_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASK5MS_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASK5MS_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK5MS_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASK5MS_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASK5MS_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASK5MS_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASKINIT_CORE1_FAR )
if (exists(".rodata.OS_TaskInit_Core1_CONST"))
{
  group OS_TaskInit_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_TaskInit_Core1_CONST";
  }
  "_OS_TaskInit_Core1_CONST_START" = "_lc_gb_OS_TaskInit_Core1_CONST_GROUP";
  "_OS_TaskInit_Core1_CONST_END" = "_lc_ge_OS_TaskInit_Core1_CONST_GROUP";
}
else
{
  "_OS_TaskInit_Core1_CONST_START" = 0;
  "_OS_TaskInit_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASKINIT_CORE1_NEAR )
if (exists(".zrodata.OS_TaskInit_Core1_CONST_FAST"))
{
  group OS_TaskInit_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_TaskInit_Core1_CONST_FAST";
  }
  "_OS_TaskInit_Core1_CONST_FAST_START" = "_lc_gb_OS_TaskInit_Core1_CONST_FAST_GROUP";
  "_OS_TaskInit_Core1_CONST_FAST_END" = "_lc_ge_OS_TaskInit_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_TaskInit_Core1_CONST_FAST_START" = 0;
  "_OS_TaskInit_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASKINIT_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASKINIT_CORE1
# undef OS_LINK_CONST_TASK_TASKINIT_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASKINIT_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASKINIT_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASKINIT_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASKINIT_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASKINIT_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASKINIT_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASKSCHM_CORE1_FAR )
if (exists(".rodata.OS_TaskSchM_Core1_CONST"))
{
  group OS_TaskSchM_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_TaskSchM_Core1_CONST";
  }
  "_OS_TaskSchM_Core1_CONST_START" = "_lc_gb_OS_TaskSchM_Core1_CONST_GROUP";
  "_OS_TaskSchM_Core1_CONST_END" = "_lc_ge_OS_TaskSchM_Core1_CONST_GROUP";
}
else
{
  "_OS_TaskSchM_Core1_CONST_START" = 0;
  "_OS_TaskSchM_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASKSCHM_CORE1_NEAR )
if (exists(".zrodata.OS_TaskSchM_Core1_CONST_FAST"))
{
  group OS_TaskSchM_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_TaskSchM_Core1_CONST_FAST";
  }
  "_OS_TaskSchM_Core1_CONST_FAST_START" = "_lc_gb_OS_TaskSchM_Core1_CONST_FAST_GROUP";
  "_OS_TaskSchM_Core1_CONST_FAST_END" = "_lc_ge_OS_TaskSchM_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_TaskSchM_Core1_CONST_FAST_START" = 0;
  "_OS_TaskSchM_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_TASK ) || defined ( OS_LINK_CONST_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_CONST_TASK_TASKSCHM_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_TASK_TASKSCHM_CORE1
# undef OS_LINK_CONST_TASK_TASKSCHM_CORE1
#endif

#ifdef OS_LINK_CONST_TASK_TASKSCHM_CORE1_FAR
# undef OS_LINK_CONST_TASK_TASKSCHM_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_TASK_TASKSCHM_CORE1_NEAR
# undef OS_LINK_CONST_TASK_TASKSCHM_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_TASK_TASKSCHM_CORE1_INIT
# undef OS_LINK_CONST_TASK_TASKSCHM_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC0SR0_ISR_FAR )
if (exists(".rodata.OS_Adc0Sr0_Isr_CONST"))
{
  group OS_Adc0Sr0_Isr_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Adc0Sr0_Isr_CONST";
  }
  "_OS_Adc0Sr0_Isr_CONST_START" = "_lc_gb_OS_Adc0Sr0_Isr_CONST_GROUP";
  "_OS_Adc0Sr0_Isr_CONST_END" = "_lc_ge_OS_Adc0Sr0_Isr_CONST_GROUP";
}
else
{
  "_OS_Adc0Sr0_Isr_CONST_START" = 0;
  "_OS_Adc0Sr0_Isr_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC0SR0_ISR_NEAR )
if (exists(".zrodata.OS_Adc0Sr0_Isr_CONST_FAST"))
{
  group OS_Adc0Sr0_Isr_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Adc0Sr0_Isr_CONST_FAST";
  }
  "_OS_Adc0Sr0_Isr_CONST_FAST_START" = "_lc_gb_OS_Adc0Sr0_Isr_CONST_FAST_GROUP";
  "_OS_Adc0Sr0_Isr_CONST_FAST_END" = "_lc_ge_OS_Adc0Sr0_Isr_CONST_FAST_GROUP";
}
else
{
  "_OS_Adc0Sr0_Isr_CONST_FAST_START" = 0;
  "_OS_Adc0Sr0_Isr_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC0SR0_ISR_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ADC0SR0_ISR
# undef OS_LINK_CONST_ISR_ADC0SR0_ISR
#endif

#ifdef OS_LINK_CONST_ISR_ADC0SR0_ISR_FAR
# undef OS_LINK_CONST_ISR_ADC0SR0_ISR_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC0SR0_ISR_NEAR
# undef OS_LINK_CONST_ISR_ADC0SR0_ISR_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC0SR0_ISR_INIT
# undef OS_LINK_CONST_ISR_ADC0SR0_ISR_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC1SR0_ISR_FAR )
if (exists(".rodata.OS_Adc1Sr0_Isr_CONST"))
{
  group OS_Adc1Sr0_Isr_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Adc1Sr0_Isr_CONST";
  }
  "_OS_Adc1Sr0_Isr_CONST_START" = "_lc_gb_OS_Adc1Sr0_Isr_CONST_GROUP";
  "_OS_Adc1Sr0_Isr_CONST_END" = "_lc_ge_OS_Adc1Sr0_Isr_CONST_GROUP";
}
else
{
  "_OS_Adc1Sr0_Isr_CONST_START" = 0;
  "_OS_Adc1Sr0_Isr_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC1SR0_ISR_NEAR )
if (exists(".zrodata.OS_Adc1Sr0_Isr_CONST_FAST"))
{
  group OS_Adc1Sr0_Isr_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Adc1Sr0_Isr_CONST_FAST";
  }
  "_OS_Adc1Sr0_Isr_CONST_FAST_START" = "_lc_gb_OS_Adc1Sr0_Isr_CONST_FAST_GROUP";
  "_OS_Adc1Sr0_Isr_CONST_FAST_END" = "_lc_ge_OS_Adc1Sr0_Isr_CONST_FAST_GROUP";
}
else
{
  "_OS_Adc1Sr0_Isr_CONST_FAST_START" = 0;
  "_OS_Adc1Sr0_Isr_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC1SR0_ISR_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ADC1SR0_ISR
# undef OS_LINK_CONST_ISR_ADC1SR0_ISR
#endif

#ifdef OS_LINK_CONST_ISR_ADC1SR0_ISR_FAR
# undef OS_LINK_CONST_ISR_ADC1SR0_ISR_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC1SR0_ISR_NEAR
# undef OS_LINK_CONST_ISR_ADC1SR0_ISR_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC1SR0_ISR_INIT
# undef OS_LINK_CONST_ISR_ADC1SR0_ISR_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC2SR0_ISR_FAR )
if (exists(".rodata.OS_Adc2Sr0_Isr_CONST"))
{
  group OS_Adc2Sr0_Isr_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Adc2Sr0_Isr_CONST";
  }
  "_OS_Adc2Sr0_Isr_CONST_START" = "_lc_gb_OS_Adc2Sr0_Isr_CONST_GROUP";
  "_OS_Adc2Sr0_Isr_CONST_END" = "_lc_ge_OS_Adc2Sr0_Isr_CONST_GROUP";
}
else
{
  "_OS_Adc2Sr0_Isr_CONST_START" = 0;
  "_OS_Adc2Sr0_Isr_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC2SR0_ISR_NEAR )
if (exists(".zrodata.OS_Adc2Sr0_Isr_CONST_FAST"))
{
  group OS_Adc2Sr0_Isr_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Adc2Sr0_Isr_CONST_FAST";
  }
  "_OS_Adc2Sr0_Isr_CONST_FAST_START" = "_lc_gb_OS_Adc2Sr0_Isr_CONST_FAST_GROUP";
  "_OS_Adc2Sr0_Isr_CONST_FAST_END" = "_lc_ge_OS_Adc2Sr0_Isr_CONST_FAST_GROUP";
}
else
{
  "_OS_Adc2Sr0_Isr_CONST_FAST_START" = 0;
  "_OS_Adc2Sr0_Isr_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC2SR0_ISR_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ADC2SR0_ISR
# undef OS_LINK_CONST_ISR_ADC2SR0_ISR
#endif

#ifdef OS_LINK_CONST_ISR_ADC2SR0_ISR_FAR
# undef OS_LINK_CONST_ISR_ADC2SR0_ISR_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC2SR0_ISR_NEAR
# undef OS_LINK_CONST_ISR_ADC2SR0_ISR_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC2SR0_ISR_INIT
# undef OS_LINK_CONST_ISR_ADC2SR0_ISR_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC3SR0_ISR_FAR )
if (exists(".rodata.OS_Adc3Sr0_Isr_CONST"))
{
  group OS_Adc3Sr0_Isr_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Adc3Sr0_Isr_CONST";
  }
  "_OS_Adc3Sr0_Isr_CONST_START" = "_lc_gb_OS_Adc3Sr0_Isr_CONST_GROUP";
  "_OS_Adc3Sr0_Isr_CONST_END" = "_lc_ge_OS_Adc3Sr0_Isr_CONST_GROUP";
}
else
{
  "_OS_Adc3Sr0_Isr_CONST_START" = 0;
  "_OS_Adc3Sr0_Isr_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC3SR0_ISR_NEAR )
if (exists(".zrodata.OS_Adc3Sr0_Isr_CONST_FAST"))
{
  group OS_Adc3Sr0_Isr_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Adc3Sr0_Isr_CONST_FAST";
  }
  "_OS_Adc3Sr0_Isr_CONST_FAST_START" = "_lc_gb_OS_Adc3Sr0_Isr_CONST_FAST_GROUP";
  "_OS_Adc3Sr0_Isr_CONST_FAST_END" = "_lc_ge_OS_Adc3Sr0_Isr_CONST_FAST_GROUP";
}
else
{
  "_OS_Adc3Sr0_Isr_CONST_FAST_START" = 0;
  "_OS_Adc3Sr0_Isr_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC3SR0_ISR_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ADC3SR0_ISR
# undef OS_LINK_CONST_ISR_ADC3SR0_ISR
#endif

#ifdef OS_LINK_CONST_ISR_ADC3SR0_ISR_FAR
# undef OS_LINK_CONST_ISR_ADC3SR0_ISR_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC3SR0_ISR_NEAR
# undef OS_LINK_CONST_ISR_ADC3SR0_ISR_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC3SR0_ISR_INIT
# undef OS_LINK_CONST_ISR_ADC3SR0_ISR_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC4SR0_ISR_FAR )
if (exists(".rodata.OS_Adc4Sr0_Isr_CONST"))
{
  group OS_Adc4Sr0_Isr_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Adc4Sr0_Isr_CONST";
  }
  "_OS_Adc4Sr0_Isr_CONST_START" = "_lc_gb_OS_Adc4Sr0_Isr_CONST_GROUP";
  "_OS_Adc4Sr0_Isr_CONST_END" = "_lc_ge_OS_Adc4Sr0_Isr_CONST_GROUP";
}
else
{
  "_OS_Adc4Sr0_Isr_CONST_START" = 0;
  "_OS_Adc4Sr0_Isr_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC4SR0_ISR_NEAR )
if (exists(".zrodata.OS_Adc4Sr0_Isr_CONST_FAST"))
{
  group OS_Adc4Sr0_Isr_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Adc4Sr0_Isr_CONST_FAST";
  }
  "_OS_Adc4Sr0_Isr_CONST_FAST_START" = "_lc_gb_OS_Adc4Sr0_Isr_CONST_FAST_GROUP";
  "_OS_Adc4Sr0_Isr_CONST_FAST_END" = "_lc_ge_OS_Adc4Sr0_Isr_CONST_FAST_GROUP";
}
else
{
  "_OS_Adc4Sr0_Isr_CONST_FAST_START" = 0;
  "_OS_Adc4Sr0_Isr_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC4SR0_ISR_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ADC4SR0_ISR
# undef OS_LINK_CONST_ISR_ADC4SR0_ISR
#endif

#ifdef OS_LINK_CONST_ISR_ADC4SR0_ISR_FAR
# undef OS_LINK_CONST_ISR_ADC4SR0_ISR_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC4SR0_ISR_NEAR
# undef OS_LINK_CONST_ISR_ADC4SR0_ISR_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC4SR0_ISR_INIT
# undef OS_LINK_CONST_ISR_ADC4SR0_ISR_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC5SR0_ISR_FAR )
if (exists(".rodata.OS_Adc5Sr0_Isr_CONST"))
{
  group OS_Adc5Sr0_Isr_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Adc5Sr0_Isr_CONST";
  }
  "_OS_Adc5Sr0_Isr_CONST_START" = "_lc_gb_OS_Adc5Sr0_Isr_CONST_GROUP";
  "_OS_Adc5Sr0_Isr_CONST_END" = "_lc_ge_OS_Adc5Sr0_Isr_CONST_GROUP";
}
else
{
  "_OS_Adc5Sr0_Isr_CONST_START" = 0;
  "_OS_Adc5Sr0_Isr_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC5SR0_ISR_NEAR )
if (exists(".zrodata.OS_Adc5Sr0_Isr_CONST_FAST"))
{
  group OS_Adc5Sr0_Isr_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Adc5Sr0_Isr_CONST_FAST";
  }
  "_OS_Adc5Sr0_Isr_CONST_FAST_START" = "_lc_gb_OS_Adc5Sr0_Isr_CONST_FAST_GROUP";
  "_OS_Adc5Sr0_Isr_CONST_FAST_END" = "_lc_ge_OS_Adc5Sr0_Isr_CONST_FAST_GROUP";
}
else
{
  "_OS_Adc5Sr0_Isr_CONST_FAST_START" = 0;
  "_OS_Adc5Sr0_Isr_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC5SR0_ISR_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ADC5SR0_ISR
# undef OS_LINK_CONST_ISR_ADC5SR0_ISR
#endif

#ifdef OS_LINK_CONST_ISR_ADC5SR0_ISR_FAR
# undef OS_LINK_CONST_ISR_ADC5SR0_ISR_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC5SR0_ISR_NEAR
# undef OS_LINK_CONST_ISR_ADC5SR0_ISR_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC5SR0_ISR_INIT
# undef OS_LINK_CONST_ISR_ADC5SR0_ISR_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC6SR0_ISR_FAR )
if (exists(".rodata.OS_Adc6Sr0_Isr_CONST"))
{
  group OS_Adc6Sr0_Isr_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Adc6Sr0_Isr_CONST";
  }
  "_OS_Adc6Sr0_Isr_CONST_START" = "_lc_gb_OS_Adc6Sr0_Isr_CONST_GROUP";
  "_OS_Adc6Sr0_Isr_CONST_END" = "_lc_ge_OS_Adc6Sr0_Isr_CONST_GROUP";
}
else
{
  "_OS_Adc6Sr0_Isr_CONST_START" = 0;
  "_OS_Adc6Sr0_Isr_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC6SR0_ISR_NEAR )
if (exists(".zrodata.OS_Adc6Sr0_Isr_CONST_FAST"))
{
  group OS_Adc6Sr0_Isr_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Adc6Sr0_Isr_CONST_FAST";
  }
  "_OS_Adc6Sr0_Isr_CONST_FAST_START" = "_lc_gb_OS_Adc6Sr0_Isr_CONST_FAST_GROUP";
  "_OS_Adc6Sr0_Isr_CONST_FAST_END" = "_lc_ge_OS_Adc6Sr0_Isr_CONST_FAST_GROUP";
}
else
{
  "_OS_Adc6Sr0_Isr_CONST_FAST_START" = 0;
  "_OS_Adc6Sr0_Isr_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_CONST_ISR_ADC6SR0_ISR_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ADC6SR0_ISR
# undef OS_LINK_CONST_ISR_ADC6SR0_ISR
#endif

#ifdef OS_LINK_CONST_ISR_ADC6SR0_ISR_FAR
# undef OS_LINK_CONST_ISR_ADC6SR0_ISR_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC6SR0_ISR_NEAR
# undef OS_LINK_CONST_ISR_ADC6SR0_ISR_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ADC6SR0_ISR_INIT
# undef OS_LINK_CONST_ISR_ADC6SR0_ISR_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR )
if (exists(".rodata.OS_CounterIsr_SystemTimer_Core1_CONST"))
{
  group OS_CounterIsr_SystemTimer_Core1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_CounterIsr_SystemTimer_Core1_CONST";
  }
  "_OS_CounterIsr_SystemTimer_Core1_CONST_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_CONST_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_CONST_END" = "_lc_ge_OS_CounterIsr_SystemTimer_Core1_CONST_GROUP";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_CONST_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR )
if (exists(".zrodata.OS_CounterIsr_SystemTimer_Core1_CONST_FAST"))
{
  group OS_CounterIsr_SystemTimer_Core1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_CounterIsr_SystemTimer_Core1_CONST_FAST";
  }
  "_OS_CounterIsr_SystemTimer_Core1_CONST_FAST_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_CONST_FAST_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_CONST_FAST_END" = "_lc_ge_OS_CounterIsr_SystemTimer_Core1_CONST_FAST_GROUP";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_CONST_FAST_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1
# undef OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1
#endif

#ifdef OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR
# undef OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR
#endif

#ifdef OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR
# undef OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_INIT
# undef OS_LINK_CONST_ISR_COUNTERISR_SYSTEMTIMER_CORE1_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ISR_TIM02 ) || defined ( OS_LINK_CONST_ISR_ISR_TIM02_FAR )
if (exists(".rodata.OS_Isr_TIM02_CONST"))
{
  group OS_Isr_TIM02_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Isr_TIM02_CONST";
  }
  "_OS_Isr_TIM02_CONST_START" = "_lc_gb_OS_Isr_TIM02_CONST_GROUP";
  "_OS_Isr_TIM02_CONST_END" = "_lc_ge_OS_Isr_TIM02_CONST_GROUP";
}
else
{
  "_OS_Isr_TIM02_CONST_START" = 0;
  "_OS_Isr_TIM02_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ISR_TIM02 ) || defined ( OS_LINK_CONST_ISR_ISR_TIM02_NEAR )
if (exists(".zrodata.OS_Isr_TIM02_CONST_FAST"))
{
  group OS_Isr_TIM02_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Isr_TIM02_CONST_FAST";
  }
  "_OS_Isr_TIM02_CONST_FAST_START" = "_lc_gb_OS_Isr_TIM02_CONST_FAST_GROUP";
  "_OS_Isr_TIM02_CONST_FAST_END" = "_lc_ge_OS_Isr_TIM02_CONST_FAST_GROUP";
}
else
{
  "_OS_Isr_TIM02_CONST_FAST_START" = 0;
  "_OS_Isr_TIM02_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ISR_TIM02 ) || defined ( OS_LINK_CONST_ISR_ISR_TIM02_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ISR_TIM02
# undef OS_LINK_CONST_ISR_ISR_TIM02
#endif

#ifdef OS_LINK_CONST_ISR_ISR_TIM02_FAR
# undef OS_LINK_CONST_ISR_ISR_TIM02_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ISR_TIM02_NEAR
# undef OS_LINK_CONST_ISR_ISR_TIM02_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ISR_TIM02_INIT
# undef OS_LINK_CONST_ISR_ISR_TIM02_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ISR_TIM03 ) || defined ( OS_LINK_CONST_ISR_ISR_TIM03_FAR )
if (exists(".rodata.OS_Isr_TIM03_CONST"))
{
  group OS_Isr_TIM03_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_Isr_TIM03_CONST";
  }
  "_OS_Isr_TIM03_CONST_START" = "_lc_gb_OS_Isr_TIM03_CONST_GROUP";
  "_OS_Isr_TIM03_CONST_END" = "_lc_ge_OS_Isr_TIM03_CONST_GROUP";
}
else
{
  "_OS_Isr_TIM03_CONST_START" = 0;
  "_OS_Isr_TIM03_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ISR_TIM03 ) || defined ( OS_LINK_CONST_ISR_ISR_TIM03_NEAR )
if (exists(".zrodata.OS_Isr_TIM03_CONST_FAST"))
{
  group OS_Isr_TIM03_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_Isr_TIM03_CONST_FAST";
  }
  "_OS_Isr_TIM03_CONST_FAST_START" = "_lc_gb_OS_Isr_TIM03_CONST_FAST_GROUP";
  "_OS_Isr_TIM03_CONST_FAST_END" = "_lc_ge_OS_Isr_TIM03_CONST_FAST_GROUP";
}
else
{
  "_OS_Isr_TIM03_CONST_FAST_START" = 0;
  "_OS_Isr_TIM03_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_ISR_TIM03 ) || defined ( OS_LINK_CONST_ISR_ISR_TIM03_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_ISR_TIM03
# undef OS_LINK_CONST_ISR_ISR_TIM03
#endif

#ifdef OS_LINK_CONST_ISR_ISR_TIM03_FAR
# undef OS_LINK_CONST_ISR_ISR_TIM03_FAR
#endif

#ifdef OS_LINK_CONST_ISR_ISR_TIM03_NEAR
# undef OS_LINK_CONST_ISR_ISR_TIM03_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_ISR_TIM03_INIT
# undef OS_LINK_CONST_ISR_ISR_TIM03_INIT
#endif



#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_FAR )
if (exists(".rodata.OS_XSignalIsr_OsCore1_CONST"))
{
  group OS_XSignalIsr_OsCore1_CONST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".rodata.OS_XSignalIsr_OsCore1_CONST";
  }
  "_OS_XSignalIsr_OsCore1_CONST_START" = "_lc_gb_OS_XSignalIsr_OsCore1_CONST_GROUP";
  "_OS_XSignalIsr_OsCore1_CONST_END" = "_lc_ge_OS_XSignalIsr_OsCore1_CONST_GROUP";
}
else
{
  "_OS_XSignalIsr_OsCore1_CONST_START" = 0;
  "_OS_XSignalIsr_OsCore1_CONST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_NEAR )
if (exists(".zrodata.OS_XSignalIsr_OsCore1_CONST_FAST"))
{
  group OS_XSignalIsr_OsCore1_CONST_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    select ".zrodata.OS_XSignalIsr_OsCore1_CONST_FAST";
  }
  "_OS_XSignalIsr_OsCore1_CONST_FAST_START" = "_lc_gb_OS_XSignalIsr_OsCore1_CONST_FAST_GROUP";
  "_OS_XSignalIsr_OsCore1_CONST_FAST_END" = "_lc_ge_OS_XSignalIsr_OsCore1_CONST_FAST_GROUP";
}
else
{
  "_OS_XSignalIsr_OsCore1_CONST_FAST_START" = 0;
  "_OS_XSignalIsr_OsCore1_CONST_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_CONST ) || defined ( OS_LINK_CONST_ISR ) || defined ( OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_INIT )













#endif

#ifdef OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1
# undef OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1
#endif

#ifdef OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_FAR
# undef OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_FAR
#endif

#ifdef OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_NEAR
# undef OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_NEAR
#endif

#ifdef OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_INIT
# undef OS_LINK_CONST_ISR_XSIGNALISR_OSCORE1_INIT
#endif



#ifdef OS_LINK_CONST
# undef OS_LINK_CONST
#endif

#ifdef OS_LINK_CONST_APP
# undef OS_LINK_CONST_APP
#endif

#ifdef OS_LINK_CONST_TASK
# undef OS_LINK_CONST_TASK
#endif

#ifdef OS_LINK_CONST_ISR
# undef OS_LINK_CONST_ISR
#endif

#ifdef OS_LINK_CONST_KERNEL
# undef OS_LINK_CONST_KERNEL
#endif

#ifdef OS_LINK_CONST_KERNEL_FAR
# undef OS_LINK_CONST_KERNEL_FAR
#endif

#ifdef OS_LINK_CONST_KERNEL_NEAR
# undef OS_LINK_CONST_KERNEL_NEAR
#endif

#ifdef OS_LINK_INTVEC_CONST
# undef OS_LINK_INTVEC_CONST
#endif

#ifdef OS_LINK_EXCVEC_CONST
# undef OS_LINK_EXCVEC_CONST
#endif


/**********************************************************************************************************************
 *  VAR SECTIONS
 *********************************************************************************************************************/

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_KERNEL ) || defined ( OS_LINK_VAR_KERNEL_FAR ) || defined ( OS_LINK_VAR_KERNEL_FAR_CACHE ) || defined ( OS_LINK_VAR_KERNEL_FAR_CACHE_INIT )
if (exists(".data.OS_CORE1_VAR"))
{
  group OS_CORE1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORE1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_CORE1_VAR";
    }
    reserved ".pad.OS_CORE1_VAR" (size=16);
  }
  "_OS_CORE1_VAR_START" = "_lc_gb_OS_CORE1_VAR_GROUP";
  "_OS_CORE1_VAR_END" = "_lc_ub__pad_OS_CORE1_VAR";
}
else
{
  "_OS_CORE1_VAR_START" = 0;
  "_OS_CORE1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_KERNEL ) || defined ( OS_LINK_VAR_KERNEL_FAR ) || defined ( OS_LINK_VAR_KERNEL_FAR_CACHE ) || defined ( OS_LINK_VAR_KERNEL_FAR_CACHE_NOINIT )
if (exists(".bss.OS_CORE1_VAR_NOINIT"))
{
  group OS_CORE1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORE1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_CORE1_VAR_NOINIT";
    }
    reserved ".pad.OS_CORE1_VAR_NOINIT" (size=16);
  }
  "_OS_CORE1_VAR_NOINIT_START" = "_lc_gb_OS_CORE1_VAR_NOINIT_GROUP";
  "_OS_CORE1_VAR_NOINIT_END" = "_lc_ub__pad_OS_CORE1_VAR_NOINIT";
}
else
{
  "_OS_CORE1_VAR_NOINIT_START" = 0;
  "_OS_CORE1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_KERNEL ) || defined ( OS_LINK_VAR_KERNEL_NEAR ) || defined ( OS_LINK_VAR_KERNEL_NEAR_CACHE ) || defined ( OS_LINK_VAR_KERNEL_NEAR_CACHE_INIT )
if (exists(".zdata.OS_CORE1_VAR_FAST"))
{
  group OS_CORE1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORE1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_CORE1_VAR_FAST";
    }
    reserved ".pad.OS_CORE1_VAR_FAST" (size=16);
  }
  "_OS_CORE1_VAR_FAST_START" = "_lc_gb_OS_CORE1_VAR_FAST_GROUP";
  "_OS_CORE1_VAR_FAST_END" = "_lc_ub__pad_OS_CORE1_VAR_FAST";
}
else
{
  "_OS_CORE1_VAR_FAST_START" = 0;
  "_OS_CORE1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_KERNEL ) || defined ( OS_LINK_VAR_KERNEL_NEAR ) || defined ( OS_LINK_VAR_KERNEL_NEAR_CACHE ) || defined ( OS_LINK_VAR_KERNEL_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_CORE1_VAR_FAST_NOINIT"))
{
  group OS_CORE1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORE1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_CORE1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_CORE1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_CORE1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_CORE1_VAR_FAST_NOINIT_GROUP";
  "_OS_CORE1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_CORE1_VAR_FAST_NOINIT";
}
else
{
  "_OS_CORE1_VAR_FAST_NOINIT_START" = 0;
  "_OS_CORE1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_KERNEL ) || defined ( OS_LINK_VAR_KERNEL_FAR ) || defined ( OS_LINK_VAR_KERNEL_FAR_NOCACHE ) || defined ( OS_LINK_VAR_KERNEL_FAR_NOCACHE_INIT )
if (exists(".data.OS_CORE1_VAR_NOCACHE"))
{
  group OS_CORE1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORE1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_CORE1_VAR_NOCACHE";
    }
    reserved ".pad.OS_CORE1_VAR_NOCACHE" (size=16);
  }
  "_OS_CORE1_VAR_NOCACHE_START" = "_lc_gb_OS_CORE1_VAR_NOCACHE_GROUP";
  "_OS_CORE1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_CORE1_VAR_NOCACHE";
}
else
{
  "_OS_CORE1_VAR_NOCACHE_START" = 0;
  "_OS_CORE1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_KERNEL ) || defined ( OS_LINK_VAR_KERNEL_FAR ) || defined ( OS_LINK_VAR_KERNEL_FAR_NOCACHE ) || defined ( OS_LINK_VAR_KERNEL_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_CORE1_VAR_NOCACHE_NOINIT"))
{
  group OS_CORE1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORE1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_CORE1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_CORE1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_CORE1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_CORE1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_CORE1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_CORE1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_CORE1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_CORE1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_KERNEL ) || defined ( OS_LINK_VAR_KERNEL_NEAR ) || defined ( OS_LINK_VAR_KERNEL_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_KERNEL_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_CORE1_VAR_FAST_NOCACHE"))
{
  group OS_CORE1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORE1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_CORE1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_CORE1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_CORE1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_CORE1_VAR_FAST_NOCACHE_GROUP";
  "_OS_CORE1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_CORE1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_CORE1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_CORE1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_KERNEL ) || defined ( OS_LINK_VAR_KERNEL_NEAR ) || defined ( OS_LINK_VAR_KERNEL_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_KERNEL_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_CORE1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_CORE1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORE1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_CORE1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_CORE1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_CORE1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_CORE1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_CORE1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_CORE1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_CORE1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_CORE1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_KERNEL_TRACE ) || defined ( OS_LINK_KERNEL_TRACE_FAR )
if (exists(".bss.OS_PUBLIC_CORE1_VAR_NOINIT"))
{
  group OS_PUBLIC_CORE1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_PUBLIC_CORE1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_PUBLIC_CORE1_VAR_NOINIT";
    }
    reserved ".pad.OS_PUBLIC_CORE1_VAR_NOINIT" (size=16);
  }
  "_OS_PUBLIC_CORE1_VAR_NOINIT_START" = "_lc_gb_OS_PUBLIC_CORE1_VAR_NOINIT_GROUP";
  "_OS_PUBLIC_CORE1_VAR_NOINIT_END" = "_lc_ub__pad_OS_PUBLIC_CORE1_VAR_NOINIT";
}
else
{
  "_OS_PUBLIC_CORE1_VAR_NOINIT_START" = 0;
  "_OS_PUBLIC_CORE1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_KERNEL_TRACE ) || defined ( OS_LINK_KERNEL_TRACE_NEAR )
if (exists(".bss.OS_PUBLIC_CORE1_VAR_FAST_NOINIT"))
{
  group OS_PUBLIC_CORE1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_PUBLIC_CORE1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_PUBLIC_CORE1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_PUBLIC_CORE1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_PUBLIC_CORE1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_PUBLIC_CORE1_VAR_FAST_NOINIT_GROUP";
  "_OS_PUBLIC_CORE1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_PUBLIC_CORE1_VAR_FAST_NOINIT";
}
else
{
  "_OS_PUBLIC_CORE1_VAR_FAST_NOINIT_START" = 0;
  "_OS_PUBLIC_CORE1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_KERNEL_BARRIERS ) || defined ( OS_LINK_KERNEL_BARRIERS_FAR )
if (exists(".bss.OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT"))
{
  group OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_BARRIER_CORE1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_KERNEL_BARRIERS ) || defined ( OS_LINK_KERNEL_BARRIERS_NEAR )
if (exists(".bss.OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_BARRIER_CORE1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_KERNEL_CORESTATUS ) || defined ( OS_LINK_KERNEL_CORESTATUS_FAR )
if (exists(".bss.OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT"))
{
  group OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_CORESTATUS_CORE1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_KERNEL_CORESTATUS ) || defined ( OS_LINK_KERNEL_CORESTATUS_NEAR )
if (exists(".bss.OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_CORESTATUS_CORE1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif


#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1
group OS_OsApplication_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_OsApplication_Core1_VAR"))
{
  group OS_OsApplication_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_OsApplication_Core1_VAR";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_START" = "_lc_gb_OS_OsApplication_Core1_VAR_GROUP";
  "_OS_OsApplication_Core1_VAR_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR";
}
else
{
  "_OS_OsApplication_Core1_VAR_START" = 0;
  "_OS_OsApplication_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_OsApplication_Core1_VAR_NOINIT"))
{
  group OS_OsApplication_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_OsApplication_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_NOINIT_START" = "_lc_gb_OS_OsApplication_Core1_VAR_NOINIT_GROUP";
  "_OS_OsApplication_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_NOINIT";
}
else
{
  "_OS_OsApplication_Core1_VAR_NOINIT_START" = 0;
  "_OS_OsApplication_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_OsApplication_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_OsApplication_Core1_VAR_ZERO_INIT"))
{
  group OS_OsApplication_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_OsApplication_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_OsApplication_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_OsApplication_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_OsApplication_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_OsApplication_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_OsApplication_Core1_VAR_FAST"))
{
  group OS_OsApplication_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_OsApplication_Core1_VAR_FAST";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_FAST" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_FAST_START" = "_lc_gb_OS_OsApplication_Core1_VAR_FAST_GROUP";
  "_OS_OsApplication_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_FAST";
}
else
{
  "_OS_OsApplication_Core1_VAR_FAST_START" = 0;
  "_OS_OsApplication_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_OsApplication_Core1_VAR_FAST_NOINIT"))
{
  group OS_OsApplication_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_OsApplication_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_OsApplication_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_OsApplication_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_OsApplication_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_OsApplication_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_OsApplication_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_OsApplication_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_OsApplication_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_OsApplication_Core1_VAR_NOCACHE"))
{
  group OS_OsApplication_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_OsApplication_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_OsApplication_Core1_VAR_NOCACHE_GROUP";
  "_OS_OsApplication_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_NOCACHE";
}
else
{
  "_OS_OsApplication_Core1_VAR_NOCACHE_START" = 0;
  "_OS_OsApplication_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_OsApplication_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_OsApplication_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_OsApplication_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_OsApplication_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_OsApplication_Core1_VAR_FAST_NOCACHE"))
{
  group OS_OsApplication_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_OsApplication_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_OsApplication_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1 ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_OsApplication_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1
reserved ".pad.OS_OsApplication_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_OsApplication_Core1_VAR_ALL_GROUP */
"_OS_OsApplication_Core1_VAR_ALL_START" = "_lc_gb_OS_OsApplication_Core1_VAR_ALL_GROUP";
"_OS_OsApplication_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_OsApplication_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_APP_OSAPPLICATION_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1
group OS_SystemApplication_OsCore1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_INIT )
if (exists(".data.OS_SystemApplication_OsCore1_VAR"))
{
  group OS_SystemApplication_OsCore1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_SystemApplication_OsCore1_VAR";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_SystemApplication_OsCore1_VAR_NOINIT"))
{
  group OS_SystemApplication_OsCore1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_SystemApplication_OsCore1_VAR_NOINIT";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_NOINIT" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_NOINIT_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_NOINIT_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_NOINIT_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_NOINIT";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_NOINIT_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss") || exists(".data.OS_SystemApplication_OsCore1_VAR_ZERO_INIT"))
{
  group OS_SystemApplication_OsCore1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_SystemApplication_OsCore1_VAR_ZERO_INIT_bss";
      select ".data.OS_SystemApplication_OsCore1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_ZERO_INIT_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_ZERO_INIT_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_ZERO_INIT";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_ZERO_INIT_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_SystemApplication_OsCore1_VAR_FAST"))
{
  group OS_SystemApplication_OsCore1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_SystemApplication_OsCore1_VAR_FAST";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_FAST" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_FAST_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_FAST_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_FAST_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_FAST";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_FAST_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_SystemApplication_OsCore1_VAR_FAST_NOINIT"))
{
  group OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_SystemApplication_OsCore1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_FAST_NOINIT";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT"))
{
  group OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_SystemApplication_OsCore1_VAR_NOCACHE"))
{
  group OS_SystemApplication_OsCore1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_SystemApplication_OsCore1_VAR_NOCACHE";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_NOCACHE" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_NOCACHE_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_NOCACHE";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT"))
{
  group OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE"))
{
  group OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_APP ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1 ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_SystemApplication_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1
reserved ".pad.OS_SystemApplication_OsCore1_VAR_ALL_GROUP" (size=16);
} /* OS_SystemApplication_OsCore1_VAR_ALL_GROUP */
"_OS_SystemApplication_OsCore1_VAR_ALL_START" = "_lc_gb_OS_SystemApplication_OsCore1_VAR_ALL_GROUP";
"_OS_SystemApplication_OsCore1_VAR_ALL_END" = "_lc_ub__pad_OS_SystemApplication_OsCore1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_APP_SYSTEMAPPLICATION_OSCORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1
group OS_IdleTask_OsCore1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_INIT )
if (exists(".data.OS_IdleTask_OsCore1_VAR"))
{
  group OS_IdleTask_OsCore1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_IdleTask_OsCore1_VAR";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_GROUP";
  "_OS_IdleTask_OsCore1_VAR_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_IdleTask_OsCore1_VAR_NOINIT"))
{
  group OS_IdleTask_OsCore1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_IdleTask_OsCore1_VAR_NOINIT";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_NOINIT" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_NOINIT_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_NOINIT_GROUP";
  "_OS_IdleTask_OsCore1_VAR_NOINIT_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_NOINIT";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_NOINIT_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_IdleTask_OsCore1_VAR_ZERO_INIT_bss") || exists(".data.OS_IdleTask_OsCore1_VAR_ZERO_INIT"))
{
  group OS_IdleTask_OsCore1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_IdleTask_OsCore1_VAR_ZERO_INIT_bss";
      select ".data.OS_IdleTask_OsCore1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_ZERO_INIT_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_ZERO_INIT_GROUP";
  "_OS_IdleTask_OsCore1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_ZERO_INIT";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_ZERO_INIT_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_IdleTask_OsCore1_VAR_FAST"))
{
  group OS_IdleTask_OsCore1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_IdleTask_OsCore1_VAR_FAST";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_FAST" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_FAST_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_FAST_GROUP";
  "_OS_IdleTask_OsCore1_VAR_FAST_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_FAST";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_FAST_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_IdleTask_OsCore1_VAR_FAST_NOINIT"))
{
  group OS_IdleTask_OsCore1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_IdleTask_OsCore1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_FAST_NOINIT_GROUP";
  "_OS_IdleTask_OsCore1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_FAST_NOINIT";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_FAST_NOINIT_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT"))
{
  group OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_IdleTask_OsCore1_VAR_NOCACHE"))
{
  group OS_IdleTask_OsCore1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_IdleTask_OsCore1_VAR_NOCACHE";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_NOCACHE" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_NOCACHE_GROUP";
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_NOCACHE";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT"))
{
  group OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE"))
{
  group OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_GROUP";
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1 ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_IdleTask_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1
reserved ".pad.OS_IdleTask_OsCore1_VAR_ALL_GROUP" (size=16);
} /* OS_IdleTask_OsCore1_VAR_ALL_GROUP */
"_OS_IdleTask_OsCore1_VAR_ALL_START" = "_lc_gb_OS_IdleTask_OsCore1_VAR_ALL_GROUP";
"_OS_IdleTask_OsCore1_VAR_ALL_END" = "_lc_ub__pad_OS_IdleTask_OsCore1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_IDLETASK_OSCORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1
group OS_Task1000ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task1000ms_Core1_VAR"))
{
  group OS_Task1000ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task1000ms_Core1_VAR";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_GROUP";
  "_OS_Task1000ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR";
}
else
{
  "_OS_Task1000ms_Core1_VAR_START" = 0;
  "_OS_Task1000ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task1000ms_Core1_VAR_NOINIT"))
{
  group OS_Task1000ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task1000ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task1000ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task1000ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task1000ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task1000ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task1000ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task1000ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task1000ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task1000ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task1000ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task1000ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task1000ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task1000ms_Core1_VAR_FAST"))
{
  group OS_Task1000ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task1000ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_FAST_GROUP";
  "_OS_Task1000ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task1000ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task1000ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task1000ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task1000ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task1000ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task1000ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task1000ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task1000ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task1000ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task1000ms_Core1_VAR_NOCACHE"))
{
  group OS_Task1000ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task1000ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task1000ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task1000ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task1000ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task1000ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task1000ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task1000ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task1000ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task1000ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task1000ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1
reserved ".pad.OS_Task1000ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task1000ms_Core1_VAR_ALL_GROUP */
"_OS_Task1000ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task1000ms_Core1_VAR_ALL_GROUP";
"_OS_Task1000ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task1000ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK1000MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1
group OS_Task100ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task100ms_Core1_VAR"))
{
  group OS_Task100ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task100ms_Core1_VAR";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_START" = "_lc_gb_OS_Task100ms_Core1_VAR_GROUP";
  "_OS_Task100ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR";
}
else
{
  "_OS_Task100ms_Core1_VAR_START" = 0;
  "_OS_Task100ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task100ms_Core1_VAR_NOINIT"))
{
  group OS_Task100ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task100ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task100ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task100ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task100ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task100ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task100ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task100ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task100ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task100ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task100ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task100ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task100ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task100ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task100ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task100ms_Core1_VAR_FAST"))
{
  group OS_Task100ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task100ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task100ms_Core1_VAR_FAST_GROUP";
  "_OS_Task100ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task100ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task100ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task100ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task100ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task100ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task100ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task100ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task100ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task100ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task100ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task100ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task100ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task100ms_Core1_VAR_NOCACHE"))
{
  group OS_Task100ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task100ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task100ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task100ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task100ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task100ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task100ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task100ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task100ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task100ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task100ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task100ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task100ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task100ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task100ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task100ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task100ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task100ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task100ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1
reserved ".pad.OS_Task100ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task100ms_Core1_VAR_ALL_GROUP */
"_OS_Task100ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task100ms_Core1_VAR_ALL_GROUP";
"_OS_Task100ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task100ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK100MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK100MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1
group OS_Task10ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task10ms_Core1_VAR"))
{
  group OS_Task10ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task10ms_Core1_VAR";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_START" = "_lc_gb_OS_Task10ms_Core1_VAR_GROUP";
  "_OS_Task10ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR";
}
else
{
  "_OS_Task10ms_Core1_VAR_START" = 0;
  "_OS_Task10ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task10ms_Core1_VAR_NOINIT"))
{
  group OS_Task10ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task10ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task10ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task10ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task10ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task10ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task10ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task10ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task10ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task10ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task10ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task10ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task10ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task10ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task10ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task10ms_Core1_VAR_FAST"))
{
  group OS_Task10ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task10ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task10ms_Core1_VAR_FAST_GROUP";
  "_OS_Task10ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task10ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task10ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task10ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task10ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task10ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task10ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task10ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task10ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task10ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task10ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task10ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task10ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task10ms_Core1_VAR_NOCACHE"))
{
  group OS_Task10ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task10ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task10ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task10ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task10ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task10ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task10ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task10ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task10ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task10ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task10ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task10ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task10ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task10ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task10ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task10ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task10ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task10ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task10ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1
reserved ".pad.OS_Task10ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task10ms_Core1_VAR_ALL_GROUP */
"_OS_Task10ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task10ms_Core1_VAR_ALL_GROUP";
"_OS_Task10ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task10ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK10MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK10MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1
group OS_Task1ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task1ms_Core1_VAR"))
{
  group OS_Task1ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task1ms_Core1_VAR";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_START" = "_lc_gb_OS_Task1ms_Core1_VAR_GROUP";
  "_OS_Task1ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR";
}
else
{
  "_OS_Task1ms_Core1_VAR_START" = 0;
  "_OS_Task1ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task1ms_Core1_VAR_NOINIT"))
{
  group OS_Task1ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task1ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task1ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task1ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task1ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task1ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task1ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task1ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task1ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task1ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task1ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task1ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task1ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task1ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task1ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task1ms_Core1_VAR_FAST"))
{
  group OS_Task1ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task1ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task1ms_Core1_VAR_FAST_GROUP";
  "_OS_Task1ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task1ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task1ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task1ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task1ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task1ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task1ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task1ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task1ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task1ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task1ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task1ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task1ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task1ms_Core1_VAR_NOCACHE"))
{
  group OS_Task1ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task1ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task1ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task1ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task1ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task1ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task1ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task1ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task1ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task1ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task1ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task1ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task1ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task1ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task1ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task1ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task1ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task1ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task1ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1
reserved ".pad.OS_Task1ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task1ms_Core1_VAR_ALL_GROUP */
"_OS_Task1ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task1ms_Core1_VAR_ALL_GROUP";
"_OS_Task1ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task1ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK1MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK1MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1
group OS_Task200ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task200ms_Core1_VAR"))
{
  group OS_Task200ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task200ms_Core1_VAR";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_START" = "_lc_gb_OS_Task200ms_Core1_VAR_GROUP";
  "_OS_Task200ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR";
}
else
{
  "_OS_Task200ms_Core1_VAR_START" = 0;
  "_OS_Task200ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task200ms_Core1_VAR_NOINIT"))
{
  group OS_Task200ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task200ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task200ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task200ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task200ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task200ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task200ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task200ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task200ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task200ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task200ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task200ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task200ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task200ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task200ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task200ms_Core1_VAR_FAST"))
{
  group OS_Task200ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task200ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task200ms_Core1_VAR_FAST_GROUP";
  "_OS_Task200ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task200ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task200ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task200ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task200ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task200ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task200ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task200ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task200ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task200ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task200ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task200ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task200ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task200ms_Core1_VAR_NOCACHE"))
{
  group OS_Task200ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task200ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task200ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task200ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task200ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task200ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task200ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task200ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task200ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task200ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task200ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task200ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task200ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task200ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task200ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task200ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task200ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task200ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task200ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1
reserved ".pad.OS_Task200ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task200ms_Core1_VAR_ALL_GROUP */
"_OS_Task200ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task200ms_Core1_VAR_ALL_GROUP";
"_OS_Task200ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task200ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK200MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK200MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1
group OS_Task20ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task20ms_Core1_VAR"))
{
  group OS_Task20ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task20ms_Core1_VAR";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_START" = "_lc_gb_OS_Task20ms_Core1_VAR_GROUP";
  "_OS_Task20ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR";
}
else
{
  "_OS_Task20ms_Core1_VAR_START" = 0;
  "_OS_Task20ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task20ms_Core1_VAR_NOINIT"))
{
  group OS_Task20ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task20ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task20ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task20ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task20ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task20ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task20ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task20ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task20ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task20ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task20ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task20ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task20ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task20ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task20ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task20ms_Core1_VAR_FAST"))
{
  group OS_Task20ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task20ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task20ms_Core1_VAR_FAST_GROUP";
  "_OS_Task20ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task20ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task20ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task20ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task20ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task20ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task20ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task20ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task20ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task20ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task20ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task20ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task20ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task20ms_Core1_VAR_NOCACHE"))
{
  group OS_Task20ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task20ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task20ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task20ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task20ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task20ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task20ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task20ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task20ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task20ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task20ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task20ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task20ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task20ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task20ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task20ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task20ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task20ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task20ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1
reserved ".pad.OS_Task20ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task20ms_Core1_VAR_ALL_GROUP */
"_OS_Task20ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task20ms_Core1_VAR_ALL_GROUP";
"_OS_Task20ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task20ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK20MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK20MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1
group OS_Task500ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task500ms_Core1_VAR"))
{
  group OS_Task500ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task500ms_Core1_VAR";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_START" = "_lc_gb_OS_Task500ms_Core1_VAR_GROUP";
  "_OS_Task500ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR";
}
else
{
  "_OS_Task500ms_Core1_VAR_START" = 0;
  "_OS_Task500ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task500ms_Core1_VAR_NOINIT"))
{
  group OS_Task500ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task500ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task500ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task500ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task500ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task500ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task500ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task500ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task500ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task500ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task500ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task500ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task500ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task500ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task500ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task500ms_Core1_VAR_FAST"))
{
  group OS_Task500ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task500ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task500ms_Core1_VAR_FAST_GROUP";
  "_OS_Task500ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task500ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task500ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task500ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task500ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task500ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task500ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task500ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task500ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task500ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task500ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task500ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task500ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task500ms_Core1_VAR_NOCACHE"))
{
  group OS_Task500ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task500ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task500ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task500ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task500ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task500ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task500ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task500ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task500ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task500ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task500ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task500ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task500ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task500ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task500ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task500ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task500ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task500ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task500ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1
reserved ".pad.OS_Task500ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task500ms_Core1_VAR_ALL_GROUP */
"_OS_Task500ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task500ms_Core1_VAR_ALL_GROUP";
"_OS_Task500ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task500ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK500MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK500MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1
group OS_Task50ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task50ms_Core1_VAR"))
{
  group OS_Task50ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task50ms_Core1_VAR";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_START" = "_lc_gb_OS_Task50ms_Core1_VAR_GROUP";
  "_OS_Task50ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR";
}
else
{
  "_OS_Task50ms_Core1_VAR_START" = 0;
  "_OS_Task50ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task50ms_Core1_VAR_NOINIT"))
{
  group OS_Task50ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task50ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task50ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task50ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task50ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task50ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task50ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task50ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task50ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task50ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task50ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task50ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task50ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task50ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task50ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task50ms_Core1_VAR_FAST"))
{
  group OS_Task50ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task50ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task50ms_Core1_VAR_FAST_GROUP";
  "_OS_Task50ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task50ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task50ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task50ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task50ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task50ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task50ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task50ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task50ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task50ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task50ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task50ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task50ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task50ms_Core1_VAR_NOCACHE"))
{
  group OS_Task50ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task50ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task50ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task50ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task50ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task50ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task50ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task50ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task50ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task50ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task50ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task50ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task50ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task50ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task50ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task50ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task50ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task50ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task50ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1
reserved ".pad.OS_Task50ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task50ms_Core1_VAR_ALL_GROUP */
"_OS_Task50ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task50ms_Core1_VAR_ALL_GROUP";
"_OS_Task50ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task50ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK50MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK50MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1
group OS_Task5ms_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_Task5ms_Core1_VAR"))
{
  group OS_Task5ms_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task5ms_Core1_VAR";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_START" = "_lc_gb_OS_Task5ms_Core1_VAR_GROUP";
  "_OS_Task5ms_Core1_VAR_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR";
}
else
{
  "_OS_Task5ms_Core1_VAR_START" = 0;
  "_OS_Task5ms_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Task5ms_Core1_VAR_NOINIT"))
{
  group OS_Task5ms_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task5ms_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_NOINIT_START" = "_lc_gb_OS_Task5ms_Core1_VAR_NOINIT_GROUP";
  "_OS_Task5ms_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_NOINIT";
}
else
{
  "_OS_Task5ms_Core1_VAR_NOINIT_START" = 0;
  "_OS_Task5ms_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Task5ms_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_Task5ms_Core1_VAR_ZERO_INIT"))
{
  group OS_Task5ms_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task5ms_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_Task5ms_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_Task5ms_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_Task5ms_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_Task5ms_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_Task5ms_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Task5ms_Core1_VAR_FAST"))
{
  group OS_Task5ms_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task5ms_Core1_VAR_FAST";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_FAST" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_FAST_START" = "_lc_gb_OS_Task5ms_Core1_VAR_FAST_GROUP";
  "_OS_Task5ms_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_FAST";
}
else
{
  "_OS_Task5ms_Core1_VAR_FAST_START" = 0;
  "_OS_Task5ms_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Task5ms_Core1_VAR_FAST_NOINIT"))
{
  group OS_Task5ms_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task5ms_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Task5ms_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_Task5ms_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_Task5ms_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_Task5ms_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Task5ms_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Task5ms_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Task5ms_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_Task5ms_Core1_VAR_NOCACHE"))
{
  group OS_Task5ms_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Task5ms_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_Task5ms_Core1_VAR_NOCACHE_GROUP";
  "_OS_Task5ms_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_NOCACHE";
}
else
{
  "_OS_Task5ms_Core1_VAR_NOCACHE_START" = 0;
  "_OS_Task5ms_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Task5ms_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_Task5ms_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task5ms_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task5ms_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Task5ms_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Task5ms_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Task5ms_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task5ms_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Task5ms_Core1_VAR_FAST_NOCACHE"))
{
  group OS_Task5ms_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Task5ms_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Task5ms_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Task5ms_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1
reserved ".pad.OS_Task5ms_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_Task5ms_Core1_VAR_ALL_GROUP */
"_OS_Task5ms_Core1_VAR_ALL_START" = "_lc_gb_OS_Task5ms_Core1_VAR_ALL_GROUP";
"_OS_Task5ms_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_Task5ms_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASK5MS_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASK5MS_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1
group OS_TaskInit_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_TaskInit_Core1_VAR"))
{
  group OS_TaskInit_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_TaskInit_Core1_VAR";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_START" = "_lc_gb_OS_TaskInit_Core1_VAR_GROUP";
  "_OS_TaskInit_Core1_VAR_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR";
}
else
{
  "_OS_TaskInit_Core1_VAR_START" = 0;
  "_OS_TaskInit_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_TaskInit_Core1_VAR_NOINIT"))
{
  group OS_TaskInit_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_TaskInit_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_NOINIT_START" = "_lc_gb_OS_TaskInit_Core1_VAR_NOINIT_GROUP";
  "_OS_TaskInit_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_NOINIT";
}
else
{
  "_OS_TaskInit_Core1_VAR_NOINIT_START" = 0;
  "_OS_TaskInit_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_TaskInit_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_TaskInit_Core1_VAR_ZERO_INIT"))
{
  group OS_TaskInit_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_TaskInit_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_TaskInit_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_TaskInit_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_TaskInit_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_TaskInit_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_TaskInit_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_TaskInit_Core1_VAR_FAST"))
{
  group OS_TaskInit_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_TaskInit_Core1_VAR_FAST";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_FAST" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_FAST_START" = "_lc_gb_OS_TaskInit_Core1_VAR_FAST_GROUP";
  "_OS_TaskInit_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_FAST";
}
else
{
  "_OS_TaskInit_Core1_VAR_FAST_START" = 0;
  "_OS_TaskInit_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_TaskInit_Core1_VAR_FAST_NOINIT"))
{
  group OS_TaskInit_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_TaskInit_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_TaskInit_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_TaskInit_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_TaskInit_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_TaskInit_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_TaskInit_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_TaskInit_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_TaskInit_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_TaskInit_Core1_VAR_NOCACHE"))
{
  group OS_TaskInit_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_TaskInit_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_TaskInit_Core1_VAR_NOCACHE_GROUP";
  "_OS_TaskInit_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_NOCACHE";
}
else
{
  "_OS_TaskInit_Core1_VAR_NOCACHE_START" = 0;
  "_OS_TaskInit_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_TaskInit_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_TaskInit_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_TaskInit_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_TaskInit_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_TaskInit_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_TaskInit_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_TaskInit_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_TaskInit_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_TaskInit_Core1_VAR_FAST_NOCACHE"))
{
  group OS_TaskInit_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_TaskInit_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_TaskInit_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_TaskInit_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1
reserved ".pad.OS_TaskInit_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_TaskInit_Core1_VAR_ALL_GROUP */
"_OS_TaskInit_Core1_VAR_ALL_START" = "_lc_gb_OS_TaskInit_Core1_VAR_ALL_GROUP";
"_OS_TaskInit_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_TaskInit_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASKINIT_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASKINIT_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1
group OS_TaskSchM_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_TaskSchM_Core1_VAR"))
{
  group OS_TaskSchM_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_TaskSchM_Core1_VAR";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_GROUP";
  "_OS_TaskSchM_Core1_VAR_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR";
}
else
{
  "_OS_TaskSchM_Core1_VAR_START" = 0;
  "_OS_TaskSchM_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_TaskSchM_Core1_VAR_NOINIT"))
{
  group OS_TaskSchM_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_TaskSchM_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_NOINIT_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_NOINIT_GROUP";
  "_OS_TaskSchM_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_NOINIT";
}
else
{
  "_OS_TaskSchM_Core1_VAR_NOINIT_START" = 0;
  "_OS_TaskSchM_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_TaskSchM_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_TaskSchM_Core1_VAR_ZERO_INIT"))
{
  group OS_TaskSchM_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_TaskSchM_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_TaskSchM_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_TaskSchM_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_TaskSchM_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_TaskSchM_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_TaskSchM_Core1_VAR_FAST"))
{
  group OS_TaskSchM_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_TaskSchM_Core1_VAR_FAST";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_FAST" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_FAST_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_FAST_GROUP";
  "_OS_TaskSchM_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_FAST";
}
else
{
  "_OS_TaskSchM_Core1_VAR_FAST_START" = 0;
  "_OS_TaskSchM_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_TaskSchM_Core1_VAR_FAST_NOINIT"))
{
  group OS_TaskSchM_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_TaskSchM_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_TaskSchM_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_TaskSchM_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_TaskSchM_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_TaskSchM_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_TaskSchM_Core1_VAR_NOCACHE"))
{
  group OS_TaskSchM_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_TaskSchM_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_NOCACHE_GROUP";
  "_OS_TaskSchM_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_NOCACHE";
}
else
{
  "_OS_TaskSchM_Core1_VAR_NOCACHE_START" = 0;
  "_OS_TaskSchM_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_TaskSchM_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_TaskSchM_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_TaskSchM_Core1_VAR_FAST_NOCACHE"))
{
  group OS_TaskSchM_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_TaskSchM_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_TASK ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1 ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_TaskSchM_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1
reserved ".pad.OS_TaskSchM_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_TaskSchM_Core1_VAR_ALL_GROUP */
"_OS_TaskSchM_Core1_VAR_ALL_START" = "_lc_gb_OS_TaskSchM_Core1_VAR_ALL_GROUP";
"_OS_TaskSchM_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_TaskSchM_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_TASK_TASKSCHM_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR
group OS_Adc0Sr0_Isr_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_INIT )
if (exists(".data.OS_Adc0Sr0_Isr_VAR"))
{
  group OS_Adc0Sr0_Isr_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc0Sr0_Isr_VAR";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Adc0Sr0_Isr_VAR_NOINIT"))
{
  group OS_Adc0Sr0_Isr_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc0Sr0_Isr_VAR_NOINIT";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_NOINIT" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_NOINIT_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_NOINIT_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_NOINIT_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_NOINIT";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_NOINIT_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Adc0Sr0_Isr_VAR_ZERO_INIT_bss") || exists(".data.OS_Adc0Sr0_Isr_VAR_ZERO_INIT"))
{
  group OS_Adc0Sr0_Isr_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc0Sr0_Isr_VAR_ZERO_INIT_bss";
      select ".data.OS_Adc0Sr0_Isr_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_ZERO_INIT_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_ZERO_INIT_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_ZERO_INIT";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_ZERO_INIT_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Adc0Sr0_Isr_VAR_FAST"))
{
  group OS_Adc0Sr0_Isr_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc0Sr0_Isr_VAR_FAST";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_FAST" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_FAST_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_FAST_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_FAST_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_FAST";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_FAST_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Adc0Sr0_Isr_VAR_FAST_NOINIT"))
{
  group OS_Adc0Sr0_Isr_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc0Sr0_Isr_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_FAST_NOINIT_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_FAST_NOINIT";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOINIT_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT"))
{
  group OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_INIT )
if (exists(".data.OS_Adc0Sr0_Isr_VAR_NOCACHE"))
{
  group OS_Adc0Sr0_Isr_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc0Sr0_Isr_VAR_NOCACHE";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_NOCACHE" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_NOCACHE_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_NOCACHE";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT"))
{
  group OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE"))
{
  group OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc0Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR
reserved ".pad.OS_Adc0Sr0_Isr_VAR_ALL_GROUP" (size=16);
} /* OS_Adc0Sr0_Isr_VAR_ALL_GROUP */
"_OS_Adc0Sr0_Isr_VAR_ALL_START" = "_lc_gb_OS_Adc0Sr0_Isr_VAR_ALL_GROUP";
"_OS_Adc0Sr0_Isr_VAR_ALL_END" = "_lc_ub__pad_OS_Adc0Sr0_Isr_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ADC0SR0_ISR
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC0SR0_ISR_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR
group OS_Adc1Sr0_Isr_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_INIT )
if (exists(".data.OS_Adc1Sr0_Isr_VAR"))
{
  group OS_Adc1Sr0_Isr_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc1Sr0_Isr_VAR";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Adc1Sr0_Isr_VAR_NOINIT"))
{
  group OS_Adc1Sr0_Isr_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc1Sr0_Isr_VAR_NOINIT";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_NOINIT" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_NOINIT_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_NOINIT_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_NOINIT_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_NOINIT";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_NOINIT_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Adc1Sr0_Isr_VAR_ZERO_INIT_bss") || exists(".data.OS_Adc1Sr0_Isr_VAR_ZERO_INIT"))
{
  group OS_Adc1Sr0_Isr_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc1Sr0_Isr_VAR_ZERO_INIT_bss";
      select ".data.OS_Adc1Sr0_Isr_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_ZERO_INIT_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_ZERO_INIT_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_ZERO_INIT";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_ZERO_INIT_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Adc1Sr0_Isr_VAR_FAST"))
{
  group OS_Adc1Sr0_Isr_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc1Sr0_Isr_VAR_FAST";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_FAST" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_FAST_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_FAST_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_FAST_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_FAST";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_FAST_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Adc1Sr0_Isr_VAR_FAST_NOINIT"))
{
  group OS_Adc1Sr0_Isr_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc1Sr0_Isr_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_FAST_NOINIT_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_FAST_NOINIT";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOINIT_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT"))
{
  group OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_INIT )
if (exists(".data.OS_Adc1Sr0_Isr_VAR_NOCACHE"))
{
  group OS_Adc1Sr0_Isr_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc1Sr0_Isr_VAR_NOCACHE";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_NOCACHE" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_NOCACHE_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_NOCACHE";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT"))
{
  group OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE"))
{
  group OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc1Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR
reserved ".pad.OS_Adc1Sr0_Isr_VAR_ALL_GROUP" (size=16);
} /* OS_Adc1Sr0_Isr_VAR_ALL_GROUP */
"_OS_Adc1Sr0_Isr_VAR_ALL_START" = "_lc_gb_OS_Adc1Sr0_Isr_VAR_ALL_GROUP";
"_OS_Adc1Sr0_Isr_VAR_ALL_END" = "_lc_ub__pad_OS_Adc1Sr0_Isr_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ADC1SR0_ISR
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC1SR0_ISR_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR
group OS_Adc2Sr0_Isr_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_INIT )
if (exists(".data.OS_Adc2Sr0_Isr_VAR"))
{
  group OS_Adc2Sr0_Isr_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc2Sr0_Isr_VAR";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Adc2Sr0_Isr_VAR_NOINIT"))
{
  group OS_Adc2Sr0_Isr_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc2Sr0_Isr_VAR_NOINIT";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_NOINIT" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_NOINIT_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_NOINIT_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_NOINIT_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_NOINIT";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_NOINIT_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Adc2Sr0_Isr_VAR_ZERO_INIT_bss") || exists(".data.OS_Adc2Sr0_Isr_VAR_ZERO_INIT"))
{
  group OS_Adc2Sr0_Isr_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc2Sr0_Isr_VAR_ZERO_INIT_bss";
      select ".data.OS_Adc2Sr0_Isr_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_ZERO_INIT_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_ZERO_INIT_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_ZERO_INIT";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_ZERO_INIT_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Adc2Sr0_Isr_VAR_FAST"))
{
  group OS_Adc2Sr0_Isr_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc2Sr0_Isr_VAR_FAST";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_FAST" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_FAST_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_FAST_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_FAST_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_FAST";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_FAST_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Adc2Sr0_Isr_VAR_FAST_NOINIT"))
{
  group OS_Adc2Sr0_Isr_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc2Sr0_Isr_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_FAST_NOINIT_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_FAST_NOINIT";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOINIT_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT"))
{
  group OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_INIT )
if (exists(".data.OS_Adc2Sr0_Isr_VAR_NOCACHE"))
{
  group OS_Adc2Sr0_Isr_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc2Sr0_Isr_VAR_NOCACHE";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_NOCACHE" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_NOCACHE_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_NOCACHE";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT"))
{
  group OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE"))
{
  group OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc2Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR
reserved ".pad.OS_Adc2Sr0_Isr_VAR_ALL_GROUP" (size=16);
} /* OS_Adc2Sr0_Isr_VAR_ALL_GROUP */
"_OS_Adc2Sr0_Isr_VAR_ALL_START" = "_lc_gb_OS_Adc2Sr0_Isr_VAR_ALL_GROUP";
"_OS_Adc2Sr0_Isr_VAR_ALL_END" = "_lc_ub__pad_OS_Adc2Sr0_Isr_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ADC2SR0_ISR
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC2SR0_ISR_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR
group OS_Adc3Sr0_Isr_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_INIT )
if (exists(".data.OS_Adc3Sr0_Isr_VAR"))
{
  group OS_Adc3Sr0_Isr_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc3Sr0_Isr_VAR";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Adc3Sr0_Isr_VAR_NOINIT"))
{
  group OS_Adc3Sr0_Isr_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc3Sr0_Isr_VAR_NOINIT";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_NOINIT" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_NOINIT_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_NOINIT_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_NOINIT_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_NOINIT";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_NOINIT_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Adc3Sr0_Isr_VAR_ZERO_INIT_bss") || exists(".data.OS_Adc3Sr0_Isr_VAR_ZERO_INIT"))
{
  group OS_Adc3Sr0_Isr_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc3Sr0_Isr_VAR_ZERO_INIT_bss";
      select ".data.OS_Adc3Sr0_Isr_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_ZERO_INIT_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_ZERO_INIT_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_ZERO_INIT";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_ZERO_INIT_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Adc3Sr0_Isr_VAR_FAST"))
{
  group OS_Adc3Sr0_Isr_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc3Sr0_Isr_VAR_FAST";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_FAST" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_FAST_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_FAST_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_FAST_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_FAST";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_FAST_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Adc3Sr0_Isr_VAR_FAST_NOINIT"))
{
  group OS_Adc3Sr0_Isr_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc3Sr0_Isr_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_FAST_NOINIT_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_FAST_NOINIT";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOINIT_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT"))
{
  group OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_INIT )
if (exists(".data.OS_Adc3Sr0_Isr_VAR_NOCACHE"))
{
  group OS_Adc3Sr0_Isr_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc3Sr0_Isr_VAR_NOCACHE";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_NOCACHE" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_NOCACHE_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_NOCACHE";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT"))
{
  group OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE"))
{
  group OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc3Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR
reserved ".pad.OS_Adc3Sr0_Isr_VAR_ALL_GROUP" (size=16);
} /* OS_Adc3Sr0_Isr_VAR_ALL_GROUP */
"_OS_Adc3Sr0_Isr_VAR_ALL_START" = "_lc_gb_OS_Adc3Sr0_Isr_VAR_ALL_GROUP";
"_OS_Adc3Sr0_Isr_VAR_ALL_END" = "_lc_ub__pad_OS_Adc3Sr0_Isr_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ADC3SR0_ISR
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC3SR0_ISR_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR
group OS_Adc4Sr0_Isr_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_INIT )
if (exists(".data.OS_Adc4Sr0_Isr_VAR"))
{
  group OS_Adc4Sr0_Isr_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc4Sr0_Isr_VAR";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Adc4Sr0_Isr_VAR_NOINIT"))
{
  group OS_Adc4Sr0_Isr_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc4Sr0_Isr_VAR_NOINIT";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_NOINIT" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_NOINIT_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_NOINIT_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_NOINIT_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_NOINIT";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_NOINIT_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Adc4Sr0_Isr_VAR_ZERO_INIT_bss") || exists(".data.OS_Adc4Sr0_Isr_VAR_ZERO_INIT"))
{
  group OS_Adc4Sr0_Isr_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc4Sr0_Isr_VAR_ZERO_INIT_bss";
      select ".data.OS_Adc4Sr0_Isr_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_ZERO_INIT_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_ZERO_INIT_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_ZERO_INIT";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_ZERO_INIT_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Adc4Sr0_Isr_VAR_FAST"))
{
  group OS_Adc4Sr0_Isr_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc4Sr0_Isr_VAR_FAST";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_FAST" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_FAST_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_FAST_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_FAST_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_FAST";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_FAST_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Adc4Sr0_Isr_VAR_FAST_NOINIT"))
{
  group OS_Adc4Sr0_Isr_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc4Sr0_Isr_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_FAST_NOINIT_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_FAST_NOINIT";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOINIT_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT"))
{
  group OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_INIT )
if (exists(".data.OS_Adc4Sr0_Isr_VAR_NOCACHE"))
{
  group OS_Adc4Sr0_Isr_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc4Sr0_Isr_VAR_NOCACHE";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_NOCACHE" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_NOCACHE_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_NOCACHE";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT"))
{
  group OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE"))
{
  group OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc4Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR
reserved ".pad.OS_Adc4Sr0_Isr_VAR_ALL_GROUP" (size=16);
} /* OS_Adc4Sr0_Isr_VAR_ALL_GROUP */
"_OS_Adc4Sr0_Isr_VAR_ALL_START" = "_lc_gb_OS_Adc4Sr0_Isr_VAR_ALL_GROUP";
"_OS_Adc4Sr0_Isr_VAR_ALL_END" = "_lc_ub__pad_OS_Adc4Sr0_Isr_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ADC4SR0_ISR
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC4SR0_ISR_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR
group OS_Adc5Sr0_Isr_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_INIT )
if (exists(".data.OS_Adc5Sr0_Isr_VAR"))
{
  group OS_Adc5Sr0_Isr_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc5Sr0_Isr_VAR";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Adc5Sr0_Isr_VAR_NOINIT"))
{
  group OS_Adc5Sr0_Isr_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc5Sr0_Isr_VAR_NOINIT";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_NOINIT" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_NOINIT_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_NOINIT_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_NOINIT_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_NOINIT";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_NOINIT_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Adc5Sr0_Isr_VAR_ZERO_INIT_bss") || exists(".data.OS_Adc5Sr0_Isr_VAR_ZERO_INIT"))
{
  group OS_Adc5Sr0_Isr_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc5Sr0_Isr_VAR_ZERO_INIT_bss";
      select ".data.OS_Adc5Sr0_Isr_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_ZERO_INIT_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_ZERO_INIT_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_ZERO_INIT";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_ZERO_INIT_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Adc5Sr0_Isr_VAR_FAST"))
{
  group OS_Adc5Sr0_Isr_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc5Sr0_Isr_VAR_FAST";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_FAST" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_FAST_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_FAST_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_FAST_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_FAST";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_FAST_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Adc5Sr0_Isr_VAR_FAST_NOINIT"))
{
  group OS_Adc5Sr0_Isr_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc5Sr0_Isr_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_FAST_NOINIT_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_FAST_NOINIT";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOINIT_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT"))
{
  group OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_INIT )
if (exists(".data.OS_Adc5Sr0_Isr_VAR_NOCACHE"))
{
  group OS_Adc5Sr0_Isr_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc5Sr0_Isr_VAR_NOCACHE";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_NOCACHE" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_NOCACHE_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_NOCACHE";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT"))
{
  group OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE"))
{
  group OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc5Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR
reserved ".pad.OS_Adc5Sr0_Isr_VAR_ALL_GROUP" (size=16);
} /* OS_Adc5Sr0_Isr_VAR_ALL_GROUP */
"_OS_Adc5Sr0_Isr_VAR_ALL_START" = "_lc_gb_OS_Adc5Sr0_Isr_VAR_ALL_GROUP";
"_OS_Adc5Sr0_Isr_VAR_ALL_END" = "_lc_ub__pad_OS_Adc5Sr0_Isr_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ADC5SR0_ISR
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC5SR0_ISR_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR
group OS_Adc6Sr0_Isr_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_INIT )
if (exists(".data.OS_Adc6Sr0_Isr_VAR"))
{
  group OS_Adc6Sr0_Isr_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc6Sr0_Isr_VAR";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Adc6Sr0_Isr_VAR_NOINIT"))
{
  group OS_Adc6Sr0_Isr_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc6Sr0_Isr_VAR_NOINIT";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_NOINIT" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_NOINIT_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_NOINIT_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_NOINIT_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_NOINIT";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_NOINIT_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Adc6Sr0_Isr_VAR_ZERO_INIT_bss") || exists(".data.OS_Adc6Sr0_Isr_VAR_ZERO_INIT"))
{
  group OS_Adc6Sr0_Isr_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc6Sr0_Isr_VAR_ZERO_INIT_bss";
      select ".data.OS_Adc6Sr0_Isr_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_ZERO_INIT_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_ZERO_INIT_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_ZERO_INIT";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_ZERO_INIT_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Adc6Sr0_Isr_VAR_FAST"))
{
  group OS_Adc6Sr0_Isr_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc6Sr0_Isr_VAR_FAST";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_FAST" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_FAST_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_FAST_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_FAST_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_FAST";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_FAST_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Adc6Sr0_Isr_VAR_FAST_NOINIT"))
{
  group OS_Adc6Sr0_Isr_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc6Sr0_Isr_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_FAST_NOINIT_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_FAST_NOINIT";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOINIT_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT"))
{
  group OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_INIT )
if (exists(".data.OS_Adc6Sr0_Isr_VAR_NOCACHE"))
{
  group OS_Adc6Sr0_Isr_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Adc6Sr0_Isr_VAR_NOCACHE";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_NOCACHE" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_NOCACHE_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_NOCACHE";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT"))
{
  group OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE"))
{
  group OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Adc6Sr0_Isr_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR
reserved ".pad.OS_Adc6Sr0_Isr_VAR_ALL_GROUP" (size=16);
} /* OS_Adc6Sr0_Isr_VAR_ALL_GROUP */
"_OS_Adc6Sr0_Isr_VAR_ALL_START" = "_lc_gb_OS_Adc6Sr0_Isr_VAR_ALL_GROUP";
"_OS_Adc6Sr0_Isr_VAR_ALL_END" = "_lc_ub__pad_OS_Adc6Sr0_Isr_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ADC6SR0_ISR
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ADC6SR0_ISR_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1
group OS_CounterIsr_SystemTimer_Core1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_INIT )
if (exists(".data.OS_CounterIsr_SystemTimer_Core1_VAR"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_CounterIsr_SystemTimer_Core1_VAR";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_bss") || exists(".data.OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_bss";
      select ".data.OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_CounterIsr_SystemTimer_Core1_VAR_FAST"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_CounterIsr_SystemTimer_Core1_VAR_FAST";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_FAST" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_FAST";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1 ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_CounterIsr_SystemTimer_Core1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1
reserved ".pad.OS_CounterIsr_SystemTimer_Core1_VAR_ALL_GROUP" (size=16);
} /* OS_CounterIsr_SystemTimer_Core1_VAR_ALL_GROUP */
"_OS_CounterIsr_SystemTimer_Core1_VAR_ALL_START" = "_lc_gb_OS_CounterIsr_SystemTimer_Core1_VAR_ALL_GROUP";
"_OS_CounterIsr_SystemTimer_Core1_VAR_ALL_END" = "_lc_ub__pad_OS_CounterIsr_SystemTimer_Core1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_COUNTERISR_SYSTEMTIMER_CORE1_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ISR_TIM02
group OS_Isr_TIM02_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_INIT )
if (exists(".data.OS_Isr_TIM02_VAR"))
{
  group OS_Isr_TIM02_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Isr_TIM02_VAR";
    }
    reserved ".pad.OS_Isr_TIM02_VAR" (size=16);
  }
  "_OS_Isr_TIM02_VAR_START" = "_lc_gb_OS_Isr_TIM02_VAR_GROUP";
  "_OS_Isr_TIM02_VAR_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR";
}
else
{
  "_OS_Isr_TIM02_VAR_START" = 0;
  "_OS_Isr_TIM02_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Isr_TIM02_VAR_NOINIT"))
{
  group OS_Isr_TIM02_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Isr_TIM02_VAR_NOINIT";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_NOINIT" (size=16);
  }
  "_OS_Isr_TIM02_VAR_NOINIT_START" = "_lc_gb_OS_Isr_TIM02_VAR_NOINIT_GROUP";
  "_OS_Isr_TIM02_VAR_NOINIT_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_NOINIT";
}
else
{
  "_OS_Isr_TIM02_VAR_NOINIT_START" = 0;
  "_OS_Isr_TIM02_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Isr_TIM02_VAR_ZERO_INIT_bss") || exists(".data.OS_Isr_TIM02_VAR_ZERO_INIT"))
{
  group OS_Isr_TIM02_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Isr_TIM02_VAR_ZERO_INIT_bss";
      select ".data.OS_Isr_TIM02_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Isr_TIM02_VAR_ZERO_INIT_START" = "_lc_gb_OS_Isr_TIM02_VAR_ZERO_INIT_GROUP";
  "_OS_Isr_TIM02_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_ZERO_INIT";
}
else
{
  "_OS_Isr_TIM02_VAR_ZERO_INIT_START" = 0;
  "_OS_Isr_TIM02_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Isr_TIM02_VAR_FAST"))
{
  group OS_Isr_TIM02_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Isr_TIM02_VAR_FAST";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_FAST" (size=16);
  }
  "_OS_Isr_TIM02_VAR_FAST_START" = "_lc_gb_OS_Isr_TIM02_VAR_FAST_GROUP";
  "_OS_Isr_TIM02_VAR_FAST_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_FAST";
}
else
{
  "_OS_Isr_TIM02_VAR_FAST_START" = 0;
  "_OS_Isr_TIM02_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Isr_TIM02_VAR_FAST_NOINIT"))
{
  group OS_Isr_TIM02_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Isr_TIM02_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Isr_TIM02_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Isr_TIM02_VAR_FAST_NOINIT_GROUP";
  "_OS_Isr_TIM02_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_FAST_NOINIT";
}
else
{
  "_OS_Isr_TIM02_VAR_FAST_NOINIT_START" = 0;
  "_OS_Isr_TIM02_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Isr_TIM02_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Isr_TIM02_VAR_FAST_ZERO_INIT"))
{
  group OS_Isr_TIM02_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Isr_TIM02_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Isr_TIM02_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Isr_TIM02_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Isr_TIM02_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Isr_TIM02_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Isr_TIM02_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Isr_TIM02_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_INIT )
if (exists(".data.OS_Isr_TIM02_VAR_NOCACHE"))
{
  group OS_Isr_TIM02_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Isr_TIM02_VAR_NOCACHE";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_NOCACHE" (size=16);
  }
  "_OS_Isr_TIM02_VAR_NOCACHE_START" = "_lc_gb_OS_Isr_TIM02_VAR_NOCACHE_GROUP";
  "_OS_Isr_TIM02_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_NOCACHE";
}
else
{
  "_OS_Isr_TIM02_VAR_NOCACHE_START" = 0;
  "_OS_Isr_TIM02_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Isr_TIM02_VAR_NOCACHE_NOINIT"))
{
  group OS_Isr_TIM02_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Isr_TIM02_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Isr_TIM02_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Isr_TIM02_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Isr_TIM02_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Isr_TIM02_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Isr_TIM02_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Isr_TIM02_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Isr_TIM02_VAR_FAST_NOCACHE"))
{
  group OS_Isr_TIM02_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Isr_TIM02_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Isr_TIM02_VAR_FAST_NOCACHE_GROUP";
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Isr_TIM02_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02
reserved ".pad.OS_Isr_TIM02_VAR_ALL_GROUP" (size=16);
} /* OS_Isr_TIM02_VAR_ALL_GROUP */
"_OS_Isr_TIM02_VAR_ALL_START" = "_lc_gb_OS_Isr_TIM02_VAR_ALL_GROUP";
"_OS_Isr_TIM02_VAR_ALL_END" = "_lc_ub__pad_OS_Isr_TIM02_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ISR_TIM02
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM02_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_ISR_TIM03
group OS_Isr_TIM03_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_INIT )
if (exists(".data.OS_Isr_TIM03_VAR"))
{
  group OS_Isr_TIM03_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Isr_TIM03_VAR";
    }
    reserved ".pad.OS_Isr_TIM03_VAR" (size=16);
  }
  "_OS_Isr_TIM03_VAR_START" = "_lc_gb_OS_Isr_TIM03_VAR_GROUP";
  "_OS_Isr_TIM03_VAR_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR";
}
else
{
  "_OS_Isr_TIM03_VAR_START" = 0;
  "_OS_Isr_TIM03_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_NOINIT )
if (exists(".bss.OS_Isr_TIM03_VAR_NOINIT"))
{
  group OS_Isr_TIM03_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Isr_TIM03_VAR_NOINIT";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_NOINIT" (size=16);
  }
  "_OS_Isr_TIM03_VAR_NOINIT_START" = "_lc_gb_OS_Isr_TIM03_VAR_NOINIT_GROUP";
  "_OS_Isr_TIM03_VAR_NOINIT_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_NOINIT";
}
else
{
  "_OS_Isr_TIM03_VAR_NOINIT_START" = 0;
  "_OS_Isr_TIM03_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_Isr_TIM03_VAR_ZERO_INIT_bss") || exists(".data.OS_Isr_TIM03_VAR_ZERO_INIT"))
{
  group OS_Isr_TIM03_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Isr_TIM03_VAR_ZERO_INIT_bss";
      select ".data.OS_Isr_TIM03_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_ZERO_INIT" (size=16);
  }
  "_OS_Isr_TIM03_VAR_ZERO_INIT_START" = "_lc_gb_OS_Isr_TIM03_VAR_ZERO_INIT_GROUP";
  "_OS_Isr_TIM03_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_ZERO_INIT";
}
else
{
  "_OS_Isr_TIM03_VAR_ZERO_INIT_START" = 0;
  "_OS_Isr_TIM03_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_INIT )
if (exists(".zdata.OS_Isr_TIM03_VAR_FAST"))
{
  group OS_Isr_TIM03_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Isr_TIM03_VAR_FAST";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_FAST" (size=16);
  }
  "_OS_Isr_TIM03_VAR_FAST_START" = "_lc_gb_OS_Isr_TIM03_VAR_FAST_GROUP";
  "_OS_Isr_TIM03_VAR_FAST_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_FAST";
}
else
{
  "_OS_Isr_TIM03_VAR_FAST_START" = 0;
  "_OS_Isr_TIM03_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_Isr_TIM03_VAR_FAST_NOINIT"))
{
  group OS_Isr_TIM03_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Isr_TIM03_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_Isr_TIM03_VAR_FAST_NOINIT_START" = "_lc_gb_OS_Isr_TIM03_VAR_FAST_NOINIT_GROUP";
  "_OS_Isr_TIM03_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_FAST_NOINIT";
}
else
{
  "_OS_Isr_TIM03_VAR_FAST_NOINIT_START" = 0;
  "_OS_Isr_TIM03_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_Isr_TIM03_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_Isr_TIM03_VAR_FAST_ZERO_INIT"))
{
  group OS_Isr_TIM03_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Isr_TIM03_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_Isr_TIM03_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_Isr_TIM03_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_Isr_TIM03_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_Isr_TIM03_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_Isr_TIM03_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_Isr_TIM03_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_INIT )
if (exists(".data.OS_Isr_TIM03_VAR_NOCACHE"))
{
  group OS_Isr_TIM03_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_Isr_TIM03_VAR_NOCACHE";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_NOCACHE" (size=16);
  }
  "_OS_Isr_TIM03_VAR_NOCACHE_START" = "_lc_gb_OS_Isr_TIM03_VAR_NOCACHE_GROUP";
  "_OS_Isr_TIM03_VAR_NOCACHE_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_NOCACHE";
}
else
{
  "_OS_Isr_TIM03_VAR_NOCACHE_START" = 0;
  "_OS_Isr_TIM03_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_Isr_TIM03_VAR_NOCACHE_NOINIT"))
{
  group OS_Isr_TIM03_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Isr_TIM03_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Isr_TIM03_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_Isr_TIM03_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_Isr_TIM03_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_Isr_TIM03_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_Isr_TIM03_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Isr_TIM03_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_Isr_TIM03_VAR_FAST_NOCACHE"))
{
  group OS_Isr_TIM03_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_Isr_TIM03_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_Isr_TIM03_VAR_FAST_NOCACHE_GROUP";
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_FAST_NOCACHE";
}
else
{
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_START" = 0;
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03 ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_Isr_TIM03_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03
reserved ".pad.OS_Isr_TIM03_VAR_ALL_GROUP" (size=16);
} /* OS_Isr_TIM03_VAR_ALL_GROUP */
"_OS_Isr_TIM03_VAR_ALL_START" = "_lc_gb_OS_Isr_TIM03_VAR_ALL_GROUP";
"_OS_Isr_TIM03_VAR_ALL_END" = "_lc_ub__pad_OS_Isr_TIM03_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_ISR_TIM03
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_ISR_TIM03_NEAR_NOCACHE_ZERO_INIT
#endif



#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1
group OS_XSignalIsr_OsCore1_VAR_ALL_GROUP(ordered, contiguous, fill, align=8)
{
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_INIT )
if (exists(".data.OS_XSignalIsr_OsCore1_VAR"))
{
  group OS_XSignalIsr_OsCore1_VAR_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_XSignalIsr_OsCore1_VAR";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_NOINIT )
if (exists(".bss.OS_XSignalIsr_OsCore1_VAR_NOINIT"))
{
  group OS_XSignalIsr_OsCore1_VAR_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_XSignalIsr_OsCore1_VAR_NOINIT";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_NOINIT" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_NOINIT_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_NOINIT_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_NOINIT_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_NOINIT";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_NOINIT_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_ZERO_INIT )
if (exists(".bss.OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_bss") || exists(".data.OS_XSignalIsr_OsCore1_VAR_ZERO_INIT"))
{
  group OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_bss";
      select ".data.OS_XSignalIsr_OsCore1_VAR_ZERO_INIT";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_ZERO_INIT" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_ZERO_INIT";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_INIT )
if (exists(".zdata.OS_XSignalIsr_OsCore1_VAR_FAST"))
{
  group OS_XSignalIsr_OsCore1_VAR_FAST_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_FAST_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_XSignalIsr_OsCore1_VAR_FAST";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_FAST" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_FAST_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_FAST_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_FAST_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_FAST";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_FAST_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_FAST_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_NOINIT )
if (exists(".zbss.OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT"))
{
  group OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_ZERO_INIT )
if (exists(".zbss.OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_bss") || exists(".zdata.OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT"))
{
  group OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_bss";
      select ".zdata.OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_FAST_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_INIT )
if (exists(".data.OS_XSignalIsr_OsCore1_VAR_NOCACHE"))
{
  group OS_XSignalIsr_OsCore1_VAR_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".data.OS_XSignalIsr_OsCore1_VAR_NOCACHE";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_NOCACHE" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_NOCACHE_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_NOCACHE";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_NOINIT )
if (exists(".bss.OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT"))
{
  group OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_ZERO_INIT )
if (exists(".bss.OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_bss") || exists(".data.OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT"))
{
  group OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".bss.OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_bss";
      select ".data.OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_INIT )
if (exists(".zdata.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE"))
{
  group OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zdata.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_NOINIT )
if (exists(".zbss.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT"))
{
  group OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_NOINIT_END" = 0;
}
#endif

#if defined ( OS_LINK_VAR ) || defined ( OS_LINK_VAR_ISR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1 ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE ) || defined ( OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_ZERO_INIT )
if (exists(".zbss.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss") || exists(".zdata.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT"))
{
  group OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP(ordered, contiguous, fill, align=8)
  {
    section "OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_SECTION" (blocksize=2, attributes=rw)
    {
      select ".zbss.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_bss";
      select ".zdata.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT";
    }
    reserved ".pad.OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT" (size=16);
  }
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_GROUP";
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT";
}
else
{
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_START" = 0;
  "_OS_XSignalIsr_OsCore1_VAR_FAST_NOCACHE_ZERO_INIT_END" = 0;
}
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1
reserved ".pad.OS_XSignalIsr_OsCore1_VAR_ALL_GROUP" (size=16);
} /* OS_XSignalIsr_OsCore1_VAR_ALL_GROUP */
"_OS_XSignalIsr_OsCore1_VAR_ALL_START" = "_lc_gb_OS_XSignalIsr_OsCore1_VAR_ALL_GROUP";
"_OS_XSignalIsr_OsCore1_VAR_ALL_END" = "_lc_ub__pad_OS_XSignalIsr_OsCore1_VAR_ALL_GROUP";

# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_FAR_NOCACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_INIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_CACHE_ZERO_INIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_ZERO_INIT
# undef OS_LINK_VAR_ISR_XSIGNALISR_OSCORE1_NEAR_NOCACHE_ZERO_INIT
#endif


#ifdef OS_LINK_VAR
# undef OS_LINK_VAR
#endif

#ifdef OS_LINK_VAR_APP
# undef OS_LINK_VAR_APP
#endif

#ifdef OS_LINK_VAR_TASK
# undef OS_LINK_VAR_TASK
#endif

#ifdef OS_LINK_VAR_ISR
# undef OS_LINK_VAR_ISR
#endif

#ifdef OS_LINK_KERNEL_TRACE
# undef OS_LINK_KERNEL_TRACE
#endif

#ifdef OS_LINK_KERNEL_TRACE_FAR
# undef OS_LINK_KERNEL_TRACE_FAR
#endif

#ifdef OS_LINK_KERNEL_TRACE_NEAR
# undef OS_LINK_KERNEL_TRACE_NEAR
#endif

#ifdef OS_LINK_KERNEL_BARRIERS
# undef OS_LINK_KERNEL_BARRIERS
#endif

#ifdef OS_LINK_KERNEL_BARRIERS_FAR
# undef OS_LINK_KERNEL_BARRIERS_FAR
#endif

#ifdef OS_LINK_KERNEL_BARRIERS_NEAR
# undef OS_LINK_KERNEL_BARRIERS_NEAR
#endif

#ifdef OS_LINK_KERNEL_CORESTATUS
# undef OS_LINK_KERNEL_CORESTATUS
#endif

#ifdef OS_LINK_KERNEL_CORESTATUS_FAR
# undef OS_LINK_KERNEL_CORESTATUS_FAR
#endif

#ifdef OS_LINK_KERNEL_CORESTATUS_NEAR
# undef OS_LINK_KERNEL_CORESTATUS_NEAR
#endif

#ifdef OS_LINK_VAR_KERNEL
# undef OS_LINK_VAR_KERNEL
#endif

#ifdef OS_LINK_VAR_KERNEL_FAR
# undef OS_LINK_VAR_KERNEL_FAR
#endif

#ifdef OS_LINK_VAR_KERNEL_FAR_CACHE
# undef OS_LINK_VAR_KERNEL_FAR_CACHE
#endif

#ifdef OS_LINK_VAR_KERNEL_FAR_CACHE_INIT
# undef OS_LINK_VAR_KERNEL_FAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_KERNEL_FAR_CACHE_NOINIT
# undef OS_LINK_VAR_KERNEL_FAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_KERNEL_FAR_NOCACHE
# undef OS_LINK_VAR_KERNEL_FAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_KERNEL_FAR_NOCACHE_INIT
# undef OS_LINK_VAR_KERNEL_FAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_KERNEL_FAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_KERNEL_FAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR
# undef OS_LINK_VAR_KERNEL_NEAR
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR_CACHE
# undef OS_LINK_VAR_KERNEL_NEAR_CACHE
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR_CACHE_INIT
# undef OS_LINK_VAR_KERNEL_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR_CACHE_NOINIT
# undef OS_LINK_VAR_KERNEL_NEAR_CACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR_NOCACHE
# undef OS_LINK_VAR_KERNEL_NEAR_NOCACHE
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR_NOCACHE_INIT
# undef OS_LINK_VAR_KERNEL_NEAR_NOCACHE_INIT
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR_NOCACHE_NOINIT
# undef OS_LINK_VAR_KERNEL_NEAR_NOCACHE_NOINIT
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR_CACHE_INIT
# undef OS_LINK_VAR_KERNEL_NEAR_CACHE_INIT
#endif

#ifdef OS_LINK_VAR_KERNEL_NEAR_CACHE_INIT
# undef OS_LINK_VAR_KERNEL_NEAR_CACHE_INIT
#endif


