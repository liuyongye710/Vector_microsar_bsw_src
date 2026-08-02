// TASKING VX-toolset for TriCore
// Eclipse project linker script file
// 
#if defined(__PROC_TC29X__)
#include "_tc29x.lsl"
derivative my_tc29x extends tc29x
{
}
#else
#include <cpu.lsl>
#endif
/* ------------ User action required ------------------------- */
/* Please define which cores are used by your OS configuration */
#define CORE0_IS_ASR
#define CORE1_IS_ASR
#define CORE2_IS_ASR
/* ----------------------------------------------------------- */

section_layout mpe:vtc:linear
{

#if defined(__PROC_TC29X__)
  group OSCodeConst( run_addr = mem:mpe:pflash1 )
#else
  group OSCodeConst( ordered, run_addr = 0x80110000 )
#endif
  {
    #if defined(CORE0_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include "Appl\GenData\Os_Link_Core0.lsl"
    #endif

    #if defined(CORE1_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include "Appl\GenData\Os_Link_Core1.lsl"
    #endif

    #if defined(CORE2_IS_ASR)
     #define OS_LINK_INTVEC_CODE
     #define OS_LINK_EXCVEC_CODE
     #define OS_LINK_CALLOUT_CODE
     #define OS_LINK_CONST
      #include "Appl\GenData\Os_Link_Core2.lsl"
    #endif

    #define OS_LINK_CODE
    #define OS_LINK_CALLOUT_CODE
     #include "Appl\GenData\Os_Link.lsl"
  } 
	group oscore0stack(ordered,contiguous,fill,align=8,run_addr=mem:mpe:dspr0)
	{
	#define  OS_LINK_KERNEL_STACKS 
	#include "Appl\GenData\Os_Link_Core0_Stacks.lsl"
	#undef  OS_LINK_KERNEL_STACKS
	}
	group oscore1stack(ordered,contiguous,fill,align=8,run_addr=mem:mpe:dspr1)
	{
	#define  OS_LINK_KERNEL_STACKS 
	#include "Appl\GenData\Os_Link_Core1_Stacks.lsl"
	#undef  OS_LINK_KERNEL_STACKS
	}	
	group oscore2stack(ordered,contiguous,fill,align=8,run_addr=mem:mpe:dspr2)
	{
	#define  OS_LINK_KERNEL_STACKS 
	#include "Appl\GenData\Os_Link_Core2_Stacks.lsl"
	#undef  OS_LINK_KERNEL_STACKS
	}	
	group ustack_test(run_addr = mem:mpe:pflash1)
	{
	select ".BswMCode";
	}
}
section_layout :vtc:linear
{
	group T1Code ( run_addr = mem:mpe:pflash0, ordered, contiguous ,attributes = x)
    {
        select ".T1_code";
        select ".T1_codeFast";
    }
    
    group T1Data ( run_addr = mem:mpe:dflash0, ordered, contiguous ,attributes = r, align = 32)
    {
        select ".T1_const";
    }
    
    group T1Code_Core0 (run_addr = mem:mpe:pspr0, ordered, contiguous ,attributes = x)
    {
    	select ".T1_codeCore0";
        select ".T1_codeDMSCore0";
    }
    
    group T1Code_Core1 (run_addr = mem:mpe:pspr1, ordered, contiguous ,attributes = x)
    {
    	select ".T1_codeCore1";
        select ".T1_codeDMSCore1";
    }
    
    group T1Code_Core2 (run_addr = mem:mpe:pspr2, ordered, contiguous ,attributes = x)
    {
    	select ".T1_codeCore2";
        select ".T1_codeDMSCore2";
    }
    
    group T1Data_Core0 ( run_addr = mem:mpe:dspr0, ordered, contiguous , attributes = rw, align = 32 )
    {
        select "*.T1_bss";
        select "*.T1_traceBuffer";
        select "*.T1_bssCore0";
        select "*.T1_traceBufferCore0";
        select "*.T1_bssDCXCore0";
    }
    
    group T1Data_Core1 ( run_addr = mem:mpe:dspr1, ordered, contiguous, attributes = rw, align = 32  )
    {
        select "*.T1_bssCore1";
        select "*.T1_traceBufferCore1";
        select "*.T1_bssDCXCore1";
    }

    group T1Data_Core2 ( run_addr = mem:mpe:dspr2, ordered, contiguous, attributes = rw, align = 32  )
    {
        select "*.T1_bssCore2";
        select "*.T1_traceBufferCore2";
        select "*.T1_bssDCXCore2";
    }
}