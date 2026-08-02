;#/**************************************************************************** 
;#* 
;#* Copyright (c) 2023  C*Core -   All Rights Reserved  
;#* 
;#* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
;#* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
;#* 
;#* @file     startup.S
;#* @version  1.0
;#* @date     2023 - 04 - 17
;#* @brief    Initial version.
;#*****************************************************************************/
#ifdef __ghs__    /* GreenHills */
        .section    .startup, axv
        .vle
 
        .align 3  ;# 8 bytes
        
        .extern   main
        .extern __SRAM_SIZE
        .extern __SRAM_BASE_ADDR
        .extern __CAL_SRAM_SIZE
        .extern __CAL_SRAM_BASE_ADDR
        .extern __LOCAL_DMEM0_SIZE
        .extern __LOCAL_DMEM0_BASE_ADDR
        .extern __LOCAL_DMEM1_SIZE
        .extern __LOCAL_DMEM1_BASE_ADDR
        .extern __LOCAL_IMEM0_SIZE
        .extern __LOCAL_IMEM0_ROM_ADDR
        .extern __LOCAL_IMEM0_ADDR
        .extern __LOCAL_IMEM1_SIZE
        .extern __LOCAL_IMEM1_ROM_ADDR
        .extern __LOCAL_IMEM1_ADDR
        .extern __VECTOR_SIZE
        .extern __VECTOR_ROM_ADDR
        .extern __VECTOR_SRAM_ADDR
        .extern __DATA_SIZE
        .extern __DATA_ROM_ADDR
        .extern __DATA_SRAM_ADDR
        .extern __SDATA_SIZE
        .extern __SDATA_ROM_ADDR
        .extern __SDATA_SRAM_ADDR
        .extern __DATA_SHARED_SIZE
        .extern __DATA_SHARED_ROM_ADDR
        .extern __DATA_SHARED_SRAM_ADDR
        .extern __BSS_START                 
        .extern __BSS_END                 
        .extern __BSS_SIZE
        .extern __SP_INIT
        .extern _SDA_BASE_
        .extern _SDA2_BASE_
#endif
#ifdef __GNUC__   /* GCC */
        .section .startup, "ax"
#endif
#ifdef __DCC__ /* Diab */
       .section ".startup",4,rx
#endif
#ifdef __HIGHTEC__ /* HighTec */
#define e_bdnz bdnz
#define e_beq  beq
#define e_subi subi
#define e_bne  bne
#endif
        .globl    _start
        
_start:

;#****************************** Turn off SWTs ********************************
#if defined(DISABLE_SWT2)
;#SWT2
        e_lis    r4, 0xFC05
        e_or2i    r4, 0x8000

        e_li    r3, 0xC520
        e_stw    r3, 0x10(r4)

        e_li    r3, 0xD928
        e_stw    r3, 0x10(r4)

        e_lis    r3, 0xFF00
        e_or2i    r3, 0x010A
        e_stw    r3, 0(r4)
#endif

;#********************************* Enable BTB ********************************
;# Flush & Enable BTB - Set BBFI bit in BUCSR
        e_li    r3, 0x201
        mtspr    1013, r3
        se_isync

;#**************************** Init Core Registers ****************************
;# The E200Z4 core needs its registers initialising before they are used
;# otherwise in Lock Step mode the two cores will contain different random data.
;# If this is stored to memory (e.g. stacked) it will cause a Lock Step error.

;# GPRs 0-31
        e_li    r0, 0
        e_li    r1, 0
        e_li    r2, 0
        e_li    r3, 0
        e_li    r4, 0
        e_li    r5, 0
        e_li    r6, 0
        e_li    r7, 0
        e_li    r8, 0
        e_li    r9, 0
        e_li    r10, 0
        e_li    r11, 0
        e_li    r12, 0
        e_li    r13, 0
        e_li    r14, 0
        e_li    r15, 0
        e_li    r16, 0
        e_li    r17, 0
        e_li    r18, 0
        e_li    r19, 0
        e_li    r20, 0
        e_li    r21, 0
        e_li    r22, 0
        e_li    r23, 0
        e_li    r24, 0
        e_li    r25, 0
        e_li    r26, 0
        e_li    r27, 0
        e_li    r28, 0
        e_li    r29, 0
        e_li    r30, 0
        e_li    r31, 0

;# Init any other CPU register which might be stacked (before being used).

        mtspr    1, r1        ;#XER
        mtcrf    0xFF, r1
        mtspr    CTR, r1
        mtspr    272, r1        ;#SPRG0
        mtspr    273, r1        ;#SPRG1
        mtspr    274, r1        ;#SPRG2
        mtspr    275, r1        ;#SPRG3
        mtspr    58, r1        ;#CSRR0
        mtspr    59, r1        ;#CSRR1
        mtspr    570, r1        ;#MCSRR0
        mtspr    571, r1        ;#MCSRR1
        mtspr    61, r1        ;#DEAR
        mtspr    63, r1        ;#IVPR
        mtspr    256, r1        ;#USPRG0
        mtspr    62, r1        ;#ESR
        mtspr    8,r31        ;#LR

	mfspr   r6,   pir   ; /* Get CoreId. */
	e_cmp16i r6,  2     ; /* Check Z4_2. */
	e_bne    initialise_CACHE ; /* Jmp to other Core. */
    e_bl    Sysclk_Init_Firc;
;#***************************** Initialise SRAM ECC ***************************/
;# Store number of 128Byte (32GPRs) segments in Counter
 e_lis       r5, __SRAM_SIZE@h  # Initialize r5 to size of SRAM (Bytes)
 e_or2i      r5, __SRAM_SIZE@l
 e_srwi      r5, r5, 0x7         # Divide SRAM size by 128
 mtctr       r5                  # Move to counter for use with "bdnz"

;# Base Address of the internal SRAM
 e_lis       r5, __SRAM_BASE_ADDR@h
 e_or2i      r5, __SRAM_BASE_ADDR@l

;# Fill SRAM with writes of 32GPRs    
sram_loop:
    e_stmw      r0,0(r5)            # Write all 32 registers to SRAM
    e_addi      r5,r5,128           # Increment the RAM pointer to next 128bytes
    e_bdnz      sram_loop           # Loop for all of SRAM
;#***************************** Initialise Calibration SRAM ECC ***************************/
;# Store number of 128Byte (32GPRs) segments in Counter
 e_lis       r5, __CAL_SRAM_SIZE@h  # Initialize r5 to size of Calibration SRAM (Bytes)
 e_or2i      r5, __CAL_SRAM_SIZE@l
 e_srwi      r5, r5, 0x7         # Divide Calibration SRAM size by 128
 mtctr       r5                  # Move to counter for use with "bdnz"

;# Base Address of the Calibration SRAM
 e_lis       r5, __CAL_SRAM_BASE_ADDR@h
 e_or2i      r5, __CAL_SRAM_BASE_ADDR@l

;# Fill Calibration SRAM with writes of 32GPRs
cal_sram_loop:
    e_stmw      r0,0(r5)            # Write all 32 registers to Calibration SRAM
    e_addi      r5,r5,128           # Increment the RAM pointer to next 128bytes
    e_bdnz      cal_sram_loop       # Loop for all of Calibration SRAM
;#************************ Initialise Local Data SRAM0 ECC *********************/
;# Store number of 128Byte (32GPRs) segments in Counter
 e_lis       r5, __LOCAL_DMEM0_SIZE@h  # Initialize r5 to size of SRAM (Bytes)
 e_or2i      r5, __LOCAL_DMEM0_SIZE@l
 e_srwi      r5, r5, 0x7         # Divide SRAM size by 128
 mtctr       r5                  # Move to counter for use with "bdnz"

;# Base Address of the Local SRAM
 e_lis       r5, __LOCAL_DMEM0_BASE_ADDR@h
 e_or2i      r5, __LOCAL_DMEM0_BASE_ADDR@l

;# Fill Local SRAM with writes of 32GPRs
ldmem_loop0:
    e_stmw      r0,0(r5)            # Write all 32 registers to SRAM
    e_addi      r5,r5,128           # Increment the RAM pointer to next 128bytes
    e_bdnz      ldmem_loop0          # Loop for all of SRAM
;#************************ Initialise Local Data SRAM1 ECC *********************/
;# Store number of 128Byte (32GPRs) segments in Counter
 e_lis       r5, __LOCAL_DMEM1_SIZE@h  # Initialize r5 to size of SRAM (Bytes)
 e_or2i      r5, __LOCAL_DMEM1_SIZE@l
 e_srwi      r5, r5, 0x7         # Divide SRAM size by 128
 mtctr       r5                  # Move to counter for use with "bdnz"

;# Base Address of the Local SRAM
 e_lis       r5, __LOCAL_DMEM1_BASE_ADDR@h
 e_or2i      r5, __LOCAL_DMEM1_BASE_ADDR@l

;# Fill Local SRAM with writes of 32GPRs
ldmem_loop1:
    e_stmw      r0,0(r5)            # Write all 32 registers to SRAM
    e_addi      r5,r5,128           # Increment the RAM pointer to next 128bytes
    e_bdnz      ldmem_loop1          # Loop for all of SRAM
    
;#************************ Initialise CPU0 Local Instruction SRAM ECC **************/
;# Store number of 128Byte (32GPRs) segments in Counter
 e_lis       r5, __LOCAL_IMEM0_SIZE@h  # Initialize r5 to size of SRAM (Bytes)
 e_or2i      r5, __LOCAL_IMEM0_SIZE@l
 e_srwi      r5, r5, 0x7         # Divide SRAM size by 128
 mtctr       r5                  # Move to counter for use with "bdnz"
;# Base Address of the Local SRAM
 e_lis       r5, __LOCAL_IMEM0_ADDR@h
 e_or2i      r5, __LOCAL_IMEM0_ADDR@l
;# Fill Local SRAM with writes of 32GPRs
limem_loop:
    e_stmw      r0,0(r5)            # Write all 32 registers to SRAM
    e_addi      r5,r5,128           # Increment the RAM pointer to next 128bytes
    e_bdnz      limem_loop          # Loop for all of SRAM
	mfspr       r9, 286             ;# Save coreid to r9
	e_cmp16i    r9, 0
	e_beq       ROMCPYEND
	e_cmp16i    r9, 1
	e_beq       ROMCPYEND

;#************************ Initialise CPU1 Local Instruction SRAM ECC **************/
;# Store number of 128Byte (32GPRs) segments in Counter
 e_lis       r5, __LOCAL_IMEM1_SIZE@h  # Initialize r5 to size of SRAM (Bytes)
 e_or2i      r5, __LOCAL_IMEM1_SIZE@l
 e_srwi      r5, r5, 0x7         # Divide SRAM size by 128
 mtctr       r5                  # Move to counter for use with "bdnz"
;# Base Address of the Local SRAM
 e_lis       r5, __LOCAL_IMEM1_ADDR@h
 e_or2i      r5, __LOCAL_IMEM1_ADDR@l
;# Fill Local SRAM with writes of 32GPRs
limem_loop1:
    e_stmw      r0,0(r5)            # Write all 32 registers to SRAM
    e_addi      r5,r5,128           # Increment the RAM pointer to next 128bytes
    e_bdnz      limem_loop1          # Loop for all of SRAM
	mfspr       r9, 286             ;# Save coreid to r9
	e_cmp16i    r9, 0
	e_beq       ROMCPYEND
	e_cmp16i    r9, 1
	e_beq       ROMCPYEND
;#*************** Load Initialised Data Values from Flash into RAM ************/
;# Initialised Vector - ".intc_vector_table"
VECTORCOPY:
    e_lis       r9, __VECTOR_SIZE@ha      # Load upper SRAM load size (# of bytes) into R9
    e_or2i      r9, __VECTOR_SIZE@l       # Load lower SRAM load size into R9
    e_cmp16i    r9,0                    # Compare to see if equal to 0
    e_beq       DMA_DATA_COPY               # Exit cfg_ROMCPY if size is zero (no data to initialise)

    mtctr       r9                      # Store no. of bytes to be moved in counter

    e_lis       r10, __VECTOR_ROM_ADDR@h  # Load address of first SRAM load into R10
    e_or2i      r10, __VECTOR_ROM_ADDR@l  # Load lower address of SRAM load into R10
    e_subi      r10,r10, 1              # Decrement address to prepare for ROMCPYLOOP

    e_lis       r5, __VECTOR_SRAM_ADDR@h  # Load upper SRAM address into R5 (from linker file)
    e_or2i      r5, __VECTOR_SRAM_ADDR@l  # Load lower SRAM address into R5 (from linker file)
    e_subi      r5, r5, 1               # Decrement address to prepare for ROMCPYLOOP
    cmp         cr0,r5, r10
    e_beq       DMA_DATA_COPY               # Skip to SDATA copy if addresses is equal (no need to copy data)

VECTORCPYLOOP:
    e_lbzu      r4, 1(r10)              # Load data byte at R10 into R4,incrementing (update) ROM address
    e_stbu      r4, 1(r5)               # Store R4 data byte into SRAM at R5 and update SRAM address
    e_bdnz      VECTORCPYLOOP             # Branch if more bytes to load from ROM
;# Initialised Data - ".data"

DMA_DATA_COPY:
    e_bl        data_ram_copy_dma

;# Small Initialised Data - ".sdata"
SDATACOPY:    
    e_lis       r9, __SDATA_SIZE@ha     # Load upper SRAM load size (# of bytes) into R9
    e_or2i      r9, __SDATA_SIZE@l      # Load lower SRAM load size into R9                                     
    e_cmp16i    r9,0                    # Compare to see if equal to 0                                  
    e_beq       DATASHAREDCOPY          # Exit cfg_ROMCPY if size is zero (no data to initialise)
                                        
    mtctr       r9                      # Store no. of bytes to be moved in counter
                                        
    e_lis       r10, __SDATA_ROM_ADDR@h # Load address of first SRAM load into R10
    e_or2i      r10, __SDATA_ROM_ADDR@l # Load lower address of SRAM load into R10
    e_subi      r10,r10, 1              # Decrement address to prepare for ROMCPYLOOP

    e_lis       r5, __SDATA_SRAM_ADDR@h # Load upper SRAM address into R5 (from linker file)
    e_or2i      r5, __SDATA_SRAM_ADDR@l # Load lower SRAM address into R5 (from linker file)
    e_subi      r5, r5, 1               # Decrement address to prepare for ROMCPYLOOP
    cmp         cr0,r5, r10
    e_beq       DATASHAREDCOPY          # Skip copy if addresses is equal (no need to copy data)

SDATACPYLOOP:
    e_lbzu      r4, 1(r10)              # Load data byte at R10 into R4,incrementing (update) ROM address
    e_stbu      r4, 1(r5)               # Store R4 data byte into SRAM at R5 and update SRAM address 
    e_bdnz      SDATACPYLOOP            # Branch if more bytes to load from ROM


;#Initialised Data Shared - ".data_share"
DATASHAREDCOPY:
    e_lis       r9, __DATA_SHARED_SIZE@ha     # Load upper SRAM load size (# of bytes) into R9
    e_or2i      r9, __DATA_SHARED_SIZE@l      # Load lower SRAM load size into R9
    e_cmp16i    r9,0                          # Compare to see if equal to 0
    e_beq       ROMCPYEND                     # Exit cfg_ROMCPY if size is zero (no data to initialise)

    mtctr       r9                            # Store no. of bytes to be moved in counter

    e_lis       r10, __DATA_SHARED_ROM_ADDR@h # Load address of first SRAM load into R10
    e_or2i      r10, __DATA_SHARED_ROM_ADDR@l # Load lower address of SRAM load into R10
    e_subi      r10,r10, 1                    # Decrement address to prepare for ROMCPYLOOP

    e_lis       r5, __DATA_SHARED_SRAM_ADDR@h # Load upper SRAM address into R5 (from linker file)
    e_or2i      r5, __DATA_SHARED_SRAM_ADDR@l # Load lower SRAM address into R5 (from linker file)
    e_subi      r5, r5, 1                     # Decrement address to prepare for ROMCPYLOOP
    cmp         cr0,r5, r10
    e_beq       ROMCPYEND                     # Skip copy if addresses is equal (no need to copy data)

DATASHAREDCPYLOOP:
    e_lbzu      r4, 1(r10)                    # Load data byte at R10 into R4,incrementing (update) ROM address
    e_stbu      r4, 1(r5)                     # Store R4 data byte into SRAM at R5 and update SRAM address
    e_bdnz      DATASHAREDCPYLOOP             # Branch if more bytes to load from ROM


 ;#*************************** CPU0 IMEM COPY DATA *****************************
IMEMCOPY:
    e_lis       r9, __LOCAL_IMEM0_SIZE@ha     # Load upper SRAM load size (# of bytes) into R9
    e_or2i      r9, __LOCAL_IMEM0_SIZE@l      # Load lower SRAM load size into R9
    e_cmp16i    r9,0                    # Compare to see if equal to 0
    e_beq       ROMCPYEND               # Exit cfg_ROMCPY if size is zero (no data to initialise)
    mtctr       r9                      # Store no. of bytes to be moved in counter
    e_lis       r10, __LOCAL_IMEM0_ROM_ADDR@h # Load address of first SRAM load into R10
    e_or2i      r10, __LOCAL_IMEM0_ROM_ADDR@l # Load lower address of SRAM load into R10
    e_subi      r10,r10, 1              # Decrement address to prepare for ROMCPYLOOP
    e_lis       r5, __LOCAL_IMEM0_ADDR@h # Load upper SRAM address into R5 (from linker file)
    e_or2i      r5, __LOCAL_IMEM0_ADDR@l # Load lower SRAM address into R5 (from linker file)
    e_subi      r5, r5, 1               # Decrement address to prepare for ROMCPYLOOP
    cmp         cr0,r5, r10
    e_beq       ROMCPYEND               # Skip copy if addresses is equal (no need to copy data)
IMEMCOPYLOOP:
    e_lbzu      r4, 1(r10)              # Load data byte at R10 into R4,incrementing (update) ROM address
    e_stbu      r4, 1(r5)               # Store R4 data byte into SRAM at R5 and update SRAM address
    e_bdnz      IMEMCOPYLOOP            # Branch if more bytes to load from ROM


 ;#*************************** CPU1 IMEM COPY DATA *****************************
IMEMCOPY1:
    e_lis       r9, __LOCAL_IMEM1_SIZE@ha     # Load upper SRAM load size (# of bytes) into R9
    e_or2i      r9, __LOCAL_IMEM1_SIZE@l      # Load lower SRAM load size into R9
    e_cmp16i    r9,0                    # Compare to see if equal to 0
    e_beq       ROMCPYEND               # Exit cfg_ROMCPY if size is zero (no data to initialise)
    mtctr       r9                      # Store no. of bytes to be moved in counter
    e_lis       r10, __LOCAL_IMEM1_ROM_ADDR@h # Load address of first SRAM load into R10
    e_or2i      r10, __LOCAL_IMEM1_ROM_ADDR@l # Load lower address of SRAM load into R10
    e_subi      r10,r10, 1              # Decrement address to prepare for ROMCPYLOOP
    e_lis       r5, __LOCAL_IMEM1_ADDR@h # Load upper SRAM address into R5 (from linker file)
    e_or2i      r5, __LOCAL_IMEM1_ADDR@l # Load lower SRAM address into R5 (from linker file)
    e_subi      r5, r5, 1               # Decrement address to prepare for ROMCPYLOOP
    cmp         cr0,r5, r10
    e_beq       ROMCPYEND               # Skip copy if addresses is equal (no need to copy data)
IMEMCOPYLOOP1:
    e_lbzu      r4, 1(r10)              # Load data byte at R10 into R4,incrementing (update) ROM address
    e_stbu      r4, 1(r5)               # Store R4 data byte into SRAM at R5 and update SRAM address
    e_bdnz      IMEMCOPYLOOP1            # Branch if more bytes to load from ROM
ROMCPYEND:

;#*************************** Enable ME Bit in MSR *****************************
    mfmsr    r6
    e_or2i   r6,0x1000
    mtmsr    r6

;#****************************** Initialize BSS section ******************************/
bss_Init:
    e_lis        r9, __BSS_SIZE@h       # Load upper BSS load size (# of bytes) into R9
    e_or2i       r9, __BSS_SIZE@l       # Load lower BSS load size into R9 and compare to zero
    e_cmp16i     r9,0
    e_beq        bss_Init_end           # Exit if size is zero (no data to initialise)

    mtctr        r9                     # Store no. of bytes to be moved in counter

    e_lis        r5, __BSS_START@h      # Load upper BSS address into R5 (from linker file)
    e_or2i       r5, __BSS_START@l      # Load lower BSS address into R5 (from linker file)
    e_subi       r5, r5, 1              # Decrement address to prepare for bss_Init_loop

    e_lis        r4, 0x0

bss_Init_loop:
    e_stbu       r4, 1(r5)              # Store zero byte into BSS at R5 and update BSS address
    e_bdnz       bss_Init_loop          # Branch if more bytes to load
    e_bl        Sysclk_Init_Reback

bss_Init_end:

initialise_CACHE:
    mfspr   r6,   pir   ; /* Get CoreId. */
    e_cmp16i   r6,   0     ; /* Core0. */
    e_lis	r1, _CORE0_SP_INIT@h	;# Initialize stack pointer r1 to
    e_or2i	r1, _CORE0_SP_INIT@l	;# value in linker command file.
    e_beq	stack_set_end     ;
    e_lis	r1, _CORE1_SP_INIT@h	;# Initialize stack pointer r1 to
    e_or2i	r1, _CORE1_SP_INIT@l	;# value in linker command file.
    e_cmp16i   r6,   1     ; /* Core1. */
    e_beq	stack_set_end     ;
    e_lis	r1, _CORE2_SP_INIT@h	;# Initialize stack pointer r1 to
    e_or2i	r1, _CORE2_SP_INIT@l	;# value in linker command file.
stack_set_end:

#ifdef ICACHE_ENABLE
;#****************** Invalidate and Enable the Instruction cache **************

__icache_cfg:
    e_lis    r7, 0x0000
    e_or2i    r7, 0x03FF        #create mask for lower 11 bits
    mfspr    r5, 516            #in lower 11 bits we have icache size
    and.    r7, r7, r5        #check if we have icache
    e_beq    _skip_i_cache    #branch if not
mfspr    r7, 1011
    e_li    r5, 0x2
    mtspr    1011,r5
mfspr    r7, 1011
    e_li    r7, 0x4
    e_li    r8, 0x2
    ;#e_lwi r11, 0xFFFFFFFB
    e_lis    r11,0xFFFF
    e_or2i    r11,0xFFFB

__icache_inv:
    mfspr    r9, 1011
    and.    r10, r7, r9
    e_beq    __icache_no_abort
    and.    r10, r11, r9
    mtspr    1011, r10
    e_b        __icache_cfg

__icache_no_abort:
    and.    r10, r8, r9
    e_bne    __icache_inv    
    mfspr    r5, 1011
    e_ori    r5, r5, 0x0001
    se_isync
    ;#msync
    mtspr    1011, r5
_skip_i_cache:
#endif

#ifdef DCACHE_ENABLE
;#****************** Invalidate and Enable the Data cache **************
__dcache_cfg:
        e_lis    r7, 0x0000
        e_or2i    r7, 0x03FF        #create mask for lower 11 bits
        mfspr    r5, 515            #in lower 11 bits we have dcache size
        and.    r7, r7, r5        #check if we have dcache
        e_beq    _skip_d_cache    #branch if not


        e_li r5, 0x2
        mtspr 1010,r5

        e_li r7, 0x4
        e_li r8, 0x2
        e_lis    r11,0xFFFF
        e_or2i    r11,0xFFFB

__dcache_inv:
        mfspr r9, 1010
        and.  r10, r7, r9
        e_beq   __dcache_no_abort
        and.  r10, r11, r9
        mtspr 1010, r10
        e_b __dcache_cfg

__dcache_no_abort:
        and.  r10, r8, r9
        e_bne __dcache_inv

        mfspr r5, 1010
        e_ori   r5, r5, 0x0001
        se_isync
        msync
        mtspr 1010, r5
_skip_d_cache:
#endif

;#****************************** Configure Stack ******************************/
#ifndef __HIGHTEC__ /* HighTec */
        e_lis    r13, _SDA_BASE_@h    ;# Initialize r13 to sdata base
        e_or2i    r13, _SDA_BASE_@l    ;# (provided by linker).

        e_lis    r2, _SDA2_BASE_@h    ;# Initialize r2 to sdata2 base
        e_or2i    r2, _SDA2_BASE_@l    ;# (provided by linker).
#endif
        e_stwu    r0,-64(r1)            ;# Terminate stack.

#ifdef __DCC__ /* Diab */
        e_bl    __init_main
#endif

;# Jump to Main
        e_bl    main
