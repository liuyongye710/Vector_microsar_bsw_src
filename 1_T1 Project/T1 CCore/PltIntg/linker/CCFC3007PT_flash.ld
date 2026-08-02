INCLUDE "memory.h"

/* Entry Point */
ENTRY(_start)

/* define CPU2 stack size */
__STACK_SIZE = MCORE_STACK_SIZE;

/* define CPU2 heapsize */
__HEAP_SIZE = MCORE_HEAP_SIZE;

/* Define CPU2 FLASH Size */
FLASH_SIZE = MCORE_FLASH_SIZE;
/* Define CPU2 FLASH Base Address */
FLASH_BASE_ADDR = MCORE_FLASH_BASE_ADDR;

/* Define CPU2 SRAM Size */
SRAM_SIZE = MCORE_SRAM_SIZE;
/* Define CPU2 SRAM Base Address */
SRAM_BASE_ADDR = MCORE_SRAM_BASE_ADDR;
/* Define Calibration FLASH Size */
CAL_FLASH_SIZE = MCORE_CAL_FLASH_SIZE;
/* Define Calibration FLASH Base Address */
CAL_FLASH_BASE_ADDR = MCORE_CAL_FLASH_BASE_ADDR;
/* Define Calibration SRAM Size */
CAL_SRAM_SIZE = MCORE_CAL_SRAM_SIZE;
/* Define Calibration SRAM Base Address */
CAL_SRAM_BASE_ADDR = MCORE_CAL_SRAM_BASE_ADDR;

/* Define CPU2 Local Data SRAM0 Allocation */
LOCALDMEM0_SIZE = MCORE_LOCALDMEM0_SIZE;
/* Define CPU2 Local Data SRAM Base Address */
LOCALDMEM0_BASE_ADDR = MCORE_LOCALDMEM0_BASE_ADDR;

/* Define CPU2 Local Data SRAM1 Allocation */
LOCALDMEM1_SIZE = MCORE_LOCALDMEM1_SIZE;
/* Define CPU2 Local Data SRAM Base Address */
LOCALDMEM1_BASE_ADDR = MCORE_LOCALDMEM1_BASE_ADDR;



MEMORY
{
    boot_header    : org = 0x00FC0000         , len = 0x4
    cpu0_reset_vec : org = (0x00FC0000 + 0x10), len = 0x4
    cpu1_reset_vec : org = (0x00FC0000 + 0x14), len = 0x4
    cpu2_reset_vec : org = (0x00FC0000 + 0x04), len = 0x4
    cpuc_reset_vec : org = (0x00FC0000 + 0x18), len = 0x4

    m_text         : org = 0x01080000, len = 3584K
    m_text_cal     : org = 0x09680000, len = 768K
    m_data_cal     : org = 0x40000000, len = 768K
    m_data_nocache : org = 0x400C0000, len = 128K
    m_data         : org = 0x400E0000, len = 640K
    
    local_imem0    : org = 0x50000000, len = 16k
    local_dmem0    : org = 0x50800000, len = 64K
    local_imem1    : org = 0x51000000, len = 16k
    local_dmem1    : org = 0x51800000, len = 64K
   
}

SECTIONS
{
    .boot_header   : 
    {
        KEEP(*(.boot_header))
    } > boot_header

    .cpu0_reset_vector  : 
    {
        KEEP(*(.cpu0_reset_vector))
    } > cpu0_reset_vec

    .cpu1_reset_vector  : 
    {
        KEEP(*(.cpu1_reset_vector))
    } > cpu1_reset_vec

    .cpu2_reset_vector  : 
    {
        KEEP(*(.cpu2_reset_vector))
    } > cpu2_reset_vec

    .cpuc_reset_vector  : 
    {
        KEEP(*(.cpuc_reset_vector))
    } > cpuc_reset_vec

    .cpu0_reset_vector_s  :
    {
        __CPU_Z7_0_FLASH_BASE_ADDR = .;
    } > cpu0_reset_vec_s
    
    .cpu1_reset_vector_s  :
    {
        __CPU_Z7_1_FLASH_BASE_ADDR = .;
    } > cpu1_reset_vec_s

    .startup : ALIGN(32)
    {
        __CPU_Z4_2_FLASH_BASE_ADDR = .;
	__start = . ;
        *(.startup)
    } > m_text
    
    .core_exceptions_table   : ALIGN(4096)
    {
      __IVPR_VALUE = . ;
      KEEP(*(.core_exceptions_table))
    } > m_text

    .boot3 : ALIGN(0x1000)
    {
        ROM_OS_EXCVEC_OSCORE_START = . ;
        KEEP(*(.OS_EXCVEC_OSCORE))
    } > m_text

    .boot4 : ALIGN(0x1000)
    {
        ROM_OS_IRQVEC_OSCORE_START = .;
         KEEP(*(.OS_IRQVEC_OSCORE)) 
    } > m_text

    .intc_vector_table   : ALIGN(4096)
    {
      KEEP(*(.intc_vector_table))
    } > m_data AT>m_text
      
    .text : FLAGS(axv)
    {
      *(.text.startup)
      *(.text)      
      *(.text.*)
      *(.text_vle*)
      KEEP (*(.init))
      KEEP (*(.fini))            
      . = ALIGN(16);
    } > m_text
      
    .ctors :
    {
      __CTOR_LIST__ = .;
      /* gcc uses crtbegin.o to find the start of
         the constructors, so we make sure it is
         first.  Because this is a wildcard, it
         doesn't matter if the user does not
         actually link against crtbegin.o; the
         linker won't look for a file to match a
         wildcard.  The wildcard also means that it
         doesn't matter which directory crtbegin.o
         is in.  */
      KEEP (*crtbegin.o(.ctors))
      KEEP (*crtbegin?.o(.ctors))
      /* We don't want to include the .ctor section from
         from the crtend.o file until after the sorted ctors.
         The .ctor section from the crtend file contains the
         end of ctors marker and it must be last */
      KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors))
      KEEP (*(SORT(.ctors.*)))
      KEEP (*(.ctors))
      __CTOR_END__ = .;
    } > m_text

    .dtors :
    {
      __DTOR_LIST__ = .;
      KEEP (*crtbegin.o(.dtors))
      KEEP (*crtbegin?.o(.dtors))
      KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors))
      KEEP (*(SORT(.dtors.*)))
      KEEP (*(.dtors))
      __DTOR_END__ = .;
    } > m_text
        
    .preinit_array :
    {
      PROVIDE_HIDDEN (__preinit_array_start = .);
      KEEP (*(.preinit_array*))
      PROVIDE_HIDDEN (__preinit_array_end = .);
    } > m_text

    .init_array :
    {
      PROVIDE_HIDDEN (__init_array_start = .);
      KEEP (*(SORT(.init_array.*)))
      KEEP (*(.init_array*))
      PROVIDE_HIDDEN (__init_array_end = .);
    } > m_text

    .fini_array :
    {
      PROVIDE_HIDDEN (__fini_array_start = .);
      KEEP (*(SORT(.fini_array.*)))
      KEEP (*(.fini_array*))
      PROVIDE_HIDDEN (__fini_array_end = .);
    } > m_text
          
    .rodata :
    {
      *(.rodata)
      *(.rodata.*)
    } > m_text

    .OS_CODE :
    {
      *(.OS_CODE)      
      *(.OS_CODE.*)
    } > m_text

    .OS_CONST :
    {
      *(.OS_CONST)      
      *(.OS_CONST.*)
    } > m_text
       
    .VX1000_CODE_SLOW :
    {
      *(.VX1000_CODE_SLOW)      
      *(.VX1000_CODE_SLOW.*)
    } > m_text 
    
    .eh_frame_hdr : { *(.eh_frame_hdr) } > m_text
    .eh_frame     : { KEEP (*(.eh_frame)) } > m_text    
   
    .data : 
    {
      *(.data)
      *(.data.*)
    }  > m_data AT>m_text

    .sdata2 :
    {  
      *(.sdata2)
      *(.sdata2.*)
    } > m_data AT>m_text

    .OS_GLOBAL_NOCACHE_INITVAR                     :   ALIGN(32)
    {
      *(.OS_GLOBAL_NOCACHE_INITVAR)
      *(.OS_GLOBAL_NOCACHE_INITVAR.*)
    } > m_data_nocache

    .OS_INITVAR_OSCORE2                            :   ALIGN(32)
    {
      *(.OS_INITVAR_OSCORE2)
      *(.OS_INITVAR_OSCORE2.*)
    }> local_dmem0 AT>m_text

    .OS_INITVAR_OSCORE1                            :   ALIGN(32)
    {
      *(.OS_INITVAR_OSCORE1)
      *(.OS_INITVAR_OSCORE1.*)
    }> local_dmem0 AT>m_text

    .OS_INITVAR_OSCORE0                            :   ALIGN(32)
    {
      *(.OS_INITVAR_OSCORE0)
      *(.OS_INITVAR_OSCORE0.*)
    }> local_dmem0 AT>m_text
    
    .local_dmem0_value_section  :   ALIGN(32)
	{
		  *(.local_dmem0_value_section)
		  *(.local_dmem0_value_section.*)
	}> local_dmem0 AT>m_text
	
	.local_dmem1_value_section  :   ALIGN(32)
	{
		  *(.local_dmem1_value_section)
		  *(.local_dmem1_value_section.*)
	}> local_dmem1 AT>m_text
	
    .OS_GLOBAL_NOCACHE_VAR                     (NOLOAD)    :   ALIGN(32)
    {
      *(.OS_GLOBAL_NOCACHE_VAR)
      *(.OS_GLOBAL_NOCACHE_VAR.*)
    } > m_data_nocache

    .OS_VAR_OSCORE2                            (NOLOAD)    :   ALIGN(32)
    {
      *(.OS_VAR_OSCORE2)
      *(.OS_VAR_OSCORE2.*)
    } > m_data

    .OS_STACK_OSCORE2                          (NOLOAD)    :   ALIGN(32)
    {
      *(.OS_STACK_OSCORE2)
      *(.OS_STACK_OSCORE2.*)
    } > m_data

    .OS_VAR_OSCORE1                            (NOLOAD)    :   ALIGN(32)
    {
      *(.OS_VAR_OSCORE1)
      *(.OS_VAR_OSCORE1.*)
    } > m_data

    .OS_STACK_OSCORE1                          (NOLOAD)    :   ALIGN(32)
    {
      *(.OS_STACK_OSCORE1)
      *(.OS_STACK_OSCORE1.*)
    } > m_data

    .OS_VAR_OSCORE0                            (NOLOAD)    :   ALIGN(32)
    {
      *(.OS_VAR_OSCORE0)
      *(.OS_VAR_OSCORE0.*)
    } > m_data

    .OS_STACK_OSCORE0                          (NOLOAD)    :   ALIGN(32)
    {
      *(.OS_STACK_OSCORE0)
      *(.OS_STACK_OSCORE0.*)
    } > m_data

    .sbss2    (NOLOAD)   :
    {
      /* _SDA2_BASE_ = .; */ 
      *(.sbss2)
      *(.sbss2.*)
    } > m_data
    
    .sdata  :
    {
      *(.sdata)
      *(.sdata.*)
    } > m_data AT>m_text
    
    .bss   (NOLOAD)  :
    {
      __BSS_START = .;
      *(.sbss)
      *(.sbss.*)    
      *(.bss)
      *(.bss.*)
      *(COMMON)
      __BSS_END = .;
    } > m_data
    
    .stack (NOLOAD) : ALIGN(16) 
    {
      __HEAP = . ;
      PROVIDE (_end = . );
      PROVIDE (end = . );            
      . += __HEAP_SIZE ;
      __HEAP_END = . ;
      _stack_end = . ;
      . +=  __STACK_SIZE ;
      _stack_addr = . ;
      __SP_INIT = . ;
      . += 4;
    } > m_data  /* local_dmem */

    .stackCore0 (NOLOAD) : ALIGN(16)
    {
       . +=  2048 ; /* STACK_SIZE */
        _CORE0_SP_INIT = . ;
    }> m_data  /* local_dmem */

    .stackCore1 (NOLOAD) : ALIGN(16)
    {
       . +=  2048 ; /* STACK_SIZE */
        _CORE1_SP_INIT = . ;
    }> m_data  /* local_dmem */

    .stackCore2 (NOLOAD) : ALIGN(16)
    {
      . +=  2048 ; /* STACK_SIZE */
        _CORE2_SP_INIT = . ;
    }> m_data  /* local_dmem */

    .CAL_VAR : ALIGN(32)
    {
      *(.CAL_VAR)
      *(.CAL_VAR.*)
    }> m_data_cal AT>m_text_cal

    .CAL_CONST : ALIGN(32)
    {
      *(.CAL_CONST)      
      *(.CAL_CONST.*)
    } > m_text_cal

   .DEM_DATA_30K : ALIGN(32)
    {
      *(.DEM_DATA_30K)
      *(.DEM_DATA_30K.*) 
    }> local_dmem1 AT>m_text


    .T1_code : ALIGN(64)
    {
      *(.T1_code)      
      *(.T1_code.*)
    } > m_text

    .T1_codeFast : ALIGN(64)
    {
      *(.T1_codeFast)      
      *(.T1_codeFast.*)
    } > m_text

    .T1_codeCore0 : ALIGN(64)
    {
      *(.T1_codeCore0)      
      *(.T1_codeCore0.*)
    } > m_text

    .T1_codeDMSCore0 : ALIGN(64)
    {
      *(.T1_codeDMSCore0)      
      *(.T1_codeDMSCore0.*)
    } > m_text

    .T1_codeCore1 : ALIGN(64)
    {
      *(.T1_codeCore1)      
      *(.T1_codeCore1.*)
    } > m_text

    .T1_codeDMSCore1 : ALIGN(64)
    {
      *(.T1_codeDMSCore1)      
      *(.T1_codeDMSCore1.*)
    } > m_text

    .T1_codeCore2 : ALIGN(64)
    {
      *(.T1_codeCore2)      
      *(.T1_codeCore2.*)
    } > m_text

    .T1_codeDMSCore2 : ALIGN(64)
    {
      *(.T1_codeDMSCore2)      
      *(.T1_codeDMSCore2.*)
    } > m_text

    .T1_const : ALIGN(32)
    {
      *(.T1_const)      
      *(.T1_const.*)
    } > m_text

    .T1_constCore0 : ALIGN(64)
    {
      *(.T1_constCore0)      
      *(.T1_constCore0.*)
    } > m_text

    .T1_constCore1 : ALIGN(64)
    {
      *(.T1_constCore1)      
      *(.T1_constCore1.*)
    } > m_text

    .T1_constCore2 : ALIGN(64)
    {
      *(.T1_constCore2)      
      *(.T1_constCore2.*)
    } > m_text
    
    .data_share : ALIGN(64)
    {
      *(.data_share)      
      *(.data_share.*)
    } > m_data AT>m_text

    .bss_share : ALIGN(64)
    {
      *(.bss_share)      
      *(.bss_share.*)
    } > m_data
    
    .T1_bss : ALIGN(32)
    {
      *(.T1_bss)      
      *(.T1_bss.*)
    } > m_data_nocache

    .T1_clear : ALIGN(32)
    {
      *(.T1_clear)      
      *(.T1_clear.*)
    } > m_data_nocache

    .T1_bssCoreComms : ALIGN(32)
    {
      *(.T1_bssCoreComms)      
      *(.T1_bssCoreComms.*)
    } > m_data_nocache

    .T1_bssChecked : ALIGN(32)
    {
      *(.T1_bssChecked)      
      *(.T1_bssChecked.*)
    } > m_data_nocache

    .T1_bssCore0 : ALIGN(32)
    {
      *(.T1_bssCore0)      
      *(.T1_bssCore0.*)
    } > m_data_nocache

    .T1_bssDCXCore0 : ALIGN(32)
    {
      *(.T1_bssDCXCore0)      
      *(.T1_bssDCXCore0.*)
    } > m_data_nocache

    .T1_bssCheckedCore0 : ALIGN(32)
    {
      *(.T1_bssCheckedCore0)      
      *(.T1_bssCheckedCore0.*)
    } > m_data_nocache

    .T1_bssCore1 : ALIGN(32)
    {
      *(.T1_bssCore1)      
      *(.T1_bssCore1.*)
    } > m_data_nocache

    .T1_bssDCXCore1 : ALIGN(32)
    {
      *(.T1_bssDCXCore1)      
      *(.T1_bssDCXCore1.*)
    } > m_data_nocache

    .T1_bssCheckedCore1 : ALIGN(32)
    {
      *(.T1_bssCheckedCore1)      
      *(.T1_bssCheckedCore1.*)
    } > m_data_nocache

    .T1_bssCore2 : ALIGN(32)
    {
      *(.T1_bssCore2)      
      *(.T1_bssCore2.*)
    } > m_data_nocache

    .T1_bssDCXCore2 : ALIGN(32)
    {
      *(.T1_bssDCXCore2)      
      *(.T1_bssDCXCore2.*)
    } > m_data_nocache

    .T1_bssCheckedCore2 : ALIGN(32)
    {
      *(.T1_bssCheckedCore2)      
      *(.T1_bssCheckedCore2.*)
    } > m_data_nocache

    .T1_traceBufferCore0 : ALIGN(32)
    {
      *(.T1_traceBufferCore0)      
      *(.T1_traceBufferCore0.*)
    } > m_data_nocache

    .T1_traceBufferCore1 : ALIGN(32)
    {
      *(.T1_traceBufferCore1)      
      *(.T1_traceBufferCore1.*)
    } > m_data_nocache

    .T1_traceBufferCore2 : ALIGN(32)
    {
      *(.T1_traceBufferCore2)      
      *(.T1_traceBufferCore2.*)
    } > m_data_nocache
    
	.local_imem0_code_section :    ALIGN(128)       
	 {                                
	     KEEP(*(.local_imem0_code_section))
	 } > local_imem0 AT>m_text 
	 
	.local_imem1_code_section :    ALIGN(128)       
	 {                                
	     KEEP(*(.local_imem1_code_section))
	 } > local_imem1 AT>m_text 

/*-------- LABELS USED IN CODE -------------------------------*/


    RAM_OS_GLOBAL_NOCACHE_VAR_START                     =   ADDR(.OS_GLOBAL_NOCACHE_VAR);
    RAM_OS_GLOBAL_NOCACHE_VAR_END                       =   RAM_OS_GLOBAL_NOCACHE_VAR_START + SIZEOF(.OS_GLOBAL_NOCACHE_VAR);
    RAM_OS_GLOBAL_NOCACHE_INITVAR_START                 =   ADDR(.OS_GLOBAL_NOCACHE_INITVAR);
    RAM_OS_GLOBAL_NOCACHE_INITVAR_END                   =   RAM_OS_GLOBAL_NOCACHE_INITVAR_START + SIZEOF(.OS_GLOBAL_NOCACHE_INITVAR);
    ROM_OS_GLOBAL_NOCACHE_INITVAR_START                 =   LOADADDR(.OS_GLOBAL_NOCACHE_INITVAR);

    RAM_OS_VAR_OSCORE2_START                            =   ADDR(.OS_VAR_OSCORE2);
    RAM_OS_VAR_OSCORE2_END                              =   RAM_OS_VAR_OSCORE2_START + SIZEOF(.OS_VAR_OSCORE2);

    RAM_OS_INITVAR_OSCORE2_START                        =   ADDR(.OS_INITVAR_OSCORE2);
    RAM_OS_INITVAR_OSCORE2_END                          =   RAM_OS_INITVAR_OSCORE2_START + SIZEOF(.OS_INITVAR_OSCORE2);
    ROM_OS_INITVAR_OSCORE2_START                        =   LOADADDR(.OS_INITVAR_OSCORE2);

    RAM_OS_VAR_OSCORE1_START                            =   ADDR(.OS_VAR_OSCORE1);
    RAM_OS_VAR_OSCORE1_END                              =   RAM_OS_VAR_OSCORE1_START + SIZEOF(.OS_VAR_OSCORE1);

    RAM_OS_INITVAR_OSCORE1_START                        =   ADDR(.OS_INITVAR_OSCORE1);
    RAM_OS_INITVAR_OSCORE1_END                          =   RAM_OS_INITVAR_OSCORE1_START + SIZEOF(.OS_INITVAR_OSCORE1);
    ROM_OS_INITVAR_OSCORE1_START                        =   LOADADDR(.OS_INITVAR_OSCORE1);

    RAM_OS_VAR_OSCORE0_START                            =   ADDR(.OS_VAR_OSCORE0);
    RAM_OS_VAR_OSCORE0_END                              =   RAM_OS_VAR_OSCORE0_START + SIZEOF(.OS_VAR_OSCORE0);

    RAM_OS_INITVAR_OSCORE0_START                        =   ADDR(.OS_INITVAR_OSCORE0);
    RAM_OS_INITVAR_OSCORE0_END                          =   RAM_OS_INITVAR_OSCORE0_START + SIZEOF(.OS_INITVAR_OSCORE0);
    ROM_OS_INITVAR_OSCORE0_START                        =   LOADADDR(.OS_INITVAR_OSCORE0);
    
    RAM_APP_INITVAR_DMEM0_START                        =   ADDR(.local_dmem0_value_section);
    RAM_APP_INITVAR_DMEM0_END                          =   RAM_APP_INITVAR_DMEM0_START + SIZEOF(.local_dmem0_value_section);
    ROM_APP_INITVAR_DMEM0_START                        =   LOADADDR(.local_dmem0_value_section);
    
    RAM_APP_INITVAR_DMEM1_START                        =   ADDR(.local_dmem1_value_section);
    RAM_APP_INITVAR_DMEM1_END                          =   RAM_APP_INITVAR_DMEM1_START + SIZEOF(.local_dmem1_value_section);
    ROM_APP_INITVAR_DMEM1_START                        =   LOADADDR(.local_dmem1_value_section);

/* Labels for Copying Initialised Data from Flash to RAM */
__VECTOR_SRAM_ADDR  = ADDR(.intc_vector_table);
__DATA_SRAM_ADDR  = ADDR(.data);
__SDATA_SRAM_ADDR = ADDR(.sdata);
__DATA_SHARED_SRAM_ADDR = ADDR(.data_share);

__VECTOR_SIZE   = SIZEOF(.intc_vector_table);
__DATA_SIZE   = SIZEOF(.data);
__SDATA_SIZE  = SIZEOF(.sdata);
__DATA_SHARED_SIZE = SIZEOF(.data_share);

__VECTOR_ROM_ADDR  = LOADADDR(.intc_vector_table);
__DATA_ROM_ADDR  = LOADADDR(.data);
__SDATA_ROM_ADDR = LOADADDR(.sdata);
__DATA_SHARED_ROM_ADDR = LOADADDR(.data_share);
   
/* Labels Used for Initialising SRAM ECC */
__SRAM_SIZE = SRAM_SIZE;
__SRAM_BASE_ADDR = SRAM_BASE_ADDR;

__CAL_SRAM_SIZE = CAL_SRAM_SIZE;
__CAL_SRAM_BASE_ADDR = CAL_SRAM_BASE_ADDR;

__LOCAL_DMEM0_SIZE = LOCALDMEM0_SIZE;
__LOCAL_DMEM0_BASE_ADDR = LOCALDMEM0_BASE_ADDR;

__LOCAL_DMEM1_SIZE = LOCALDMEM1_SIZE;
__LOCAL_DMEM1_BASE_ADDR = LOCALDMEM1_BASE_ADDR;

__LOCAL_IMEM0_SIZE = 16K;
__LOCAL_IMEM0_ADDR = ADDR(.local_imem0_code_section);
__LOCAL_IMEM0_ROM_ADDR = LOADADDR(.local_imem0_code_section);

__LOCAL_IMEM1_SIZE = 16K;
__LOCAL_IMEM1_ADDR = ADDR(.local_imem1_code_section);
__LOCAL_IMEM1_ROM_ADDR = LOADADDR(.local_imem1_code_section);


__BSS_SIZE    = __BSS_END - __BSS_START;      
      
}