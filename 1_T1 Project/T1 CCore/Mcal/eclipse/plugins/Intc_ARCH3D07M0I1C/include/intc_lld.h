/**************************************************************************** 
* 
* Copyright (c) 2023  C*Core -   All Rights Reserved  
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
* @file     intc_lld.h
* @version  1.0
* @date     2023 - 04 - 17
* @brief    Initial version.
*
*****************************************************************************/
#ifndef INTC_LLD_H_
#define INTC_LLD_H_

#include "stdbool.h"
#include "derivative.h"
#include "status.h"
#include "Mcu_LLDriver.h"

/****************************************************************************/
typedef enum {
    INTC_MODE_SOFTWARE_VECTOR,
    INTC_MODE_HARDWARE_VECTOR,
    INTC_MODE_BNUTT,
} IntcMode;

typedef void(* IntrHandle)(void);

void INTC_LLD_Set_Vector_Prefix(register uint32_t prefix);
uint32_t INTC_LLD_Get_Vector_Table(void);
void INTC_LLD_Set_Vector_Table(uint32_t vector_table);
status_t INTC_LLD_Set_IRQ_Disable(IntrId intr_id);
status_t INTC_LLD_Set_IRQ_Enable(IntrId intr_id);
void INTC_LLD_Set_Global_Disable(void);
void INTC_LLD_Set_Global_Enable(void);
status_t INTC_LLD_Set_IRQ_Priority(IntrId intr_id, IntrPrior intr_prior);
status_t INTC_LLD_Set_Global_Priority(IntrPrior intr_prior);
status_t INTC_LLD_Set_IRQ_Handle(IntrId intr_id, IntrHandle intr_handle);
IntrId INTC_LLD_Get_Cur_IRQ_Id(void);
status_t INTC_LLD_Swtich_Mode(IntcMode intc_mode);

#endif
