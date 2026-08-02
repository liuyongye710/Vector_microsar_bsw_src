/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS, " AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* @file     mcu_lld.c
* @version  1.0
* @date     2023 - 04 - 17
* @brief    Initial version.
*
*****************************************************************************/

#include "intc_lld.h" /* PRQA S 0380 */
#include "compiler_api.h"
#include "Os.h"

/*******************************************************************************
 * @brief   Set the unified interrupt entry in software interrupt mode
 * @param[in]  register uint32_t prefix
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void INTC_LLD_Set_Vector_Prefix(register uint32_t prefix) /* PRQA S 1503, 3206 # prefix is used in assemble */
{
    MTSPR(SPR_IVPR, prefix); /* PRQA S 1006 */
}

/*******************************************************************************
 * @brief    Get the interrupt vector table
 * @param[in]  None
 * @param[out] None
 * @retval     Interrupt vector table address
 * @notapi
 *******************************************************************************/
static uint32_t g_vector_table;
uint32_t INTC_LLD_Get_Vector_Table(void) /* PRQA S 1505, 1506 */
{
    return g_vector_table;
}

/*******************************************************************************
 * @brief    Set the interrupt vector table
 * @param[in]  Interrupt vector table address
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void INTC_LLD_Set_Vector_Table(uint32_t vector_table) /* PRQA S 1503 */
{
    uint8 core_id = GetCoreID();

    INTC_0.IACKR[core_id].R = vector_table;

    g_vector_table = vector_table;
}

/*******************************************************************************
 * @brief     Get the current interrupt vector number
 * @param[in]  None
 * @param[out] None
 * @retval     Current interrupt vector number
 * @notapi
 *******************************************************************************/
IntrId INTC_LLD_Get_Cur_IRQ_Id(void)
{
    INTC_IACKR_tag IACKR;
    uint32_t vector_base, vector_addr;
    uint8 core_id = GetCoreID();

    IACKR.R = INTC_0.IACKR[core_id].R;
    vector_addr = IACKR.R;
    vector_base = INTC_LLD_Get_Vector_Table();

    return (IntrId)(uint32_t)((vector_addr - vector_base) / sizeof(uint32_t)); /* PRQA S 4342 */
}

/*******************************************************************************
 * @brief    [inner_static] Turn on or Turn off interrupts
 * @param[in]  IntrId intr_id, uint32_t switch_val(on or off)
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
static status_t INTC_LLD_Switch_IRQ(IntrId intr_id, uint32_t switch_val)
{
    uint8 core_id = GetCoreID();

    if (intr_id > INTR_ID_BUTT) {
        return STATUS_MCU_INVALID_INTC_NUM;
    }

    if (core_id >= CORE_ID_BUTT) {
        return STATUS_MCU_INVALID_CORE_ID;
    }

    switch (core_id) {
        case CORE_ID_Z7_0: {
            INTC_0.PSR[intr_id].B.PRC_SELN0 = switch_val;
            break;
        }
        case CORE_ID_Z7_1: {
            INTC_0.PSR[intr_id].B.PRC_SELN1 = switch_val;
            break;
        }
        case CORE_ID_Z4_2: {
            INTC_0.PSR[intr_id].B.PRC_SELN2 = switch_val;
            break;
        }
        default: { /* PRQA S 2024 */
            return STATUS_MCU_INVALID_CORE_ID;
        }
    }

    return STATUS_SUCCESS;
}
status_t INTC_LLD_Set_Soft_IRQ(IntrId intr_id) /* PRQA S 1503,3408 */
{
    if (intr_id > INTR_ID_31) {
        return STATUS_MCU_INVALID_INTC_NUM;
    }

    INTC_0.SSCIR[(uint32_t)intr_id].B.SET = 1U;

    return STATUS_SUCCESS;
}

status_t INTC_LLD_Clr_Soft_IRQ(IntrId intr_id) /* PRQA S 1503,3408 */
{
    if (intr_id > INTR_ID_31) {
        return STATUS_MCU_INVALID_INTC_NUM;
    }

    INTC_0.SSCIR[(uint32_t)intr_id].B.CLR = 1U;

    return STATUS_SUCCESS;
}

/*******************************************************************************
 * @brief     Set the specified interrupt to disable
 * @param[in]  IntrId intr_id
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
status_t INTC_LLD_Set_IRQ_Disable(IntrId intr_id)
{
    return INTC_LLD_Switch_IRQ(intr_id, OFF);
}

/*******************************************************************************
 * @brief     Set the specified interrupt to enable
 * @param[in]  IntrId intr_id
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
status_t INTC_LLD_Set_IRQ_Enable(IntrId intr_id)
{
    return INTC_LLD_Switch_IRQ(intr_id, ON);
}

/*******************************************************************************
 * @brief      Set global interrupt to disable
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void INTC_LLD_Set_Global_Disable(void)
{
    PPCASM ("wrteei 0"); /* PRQA S 1006 */
}

/*******************************************************************************
 * @brief      Set global interrupt to enable
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void INTC_LLD_Set_Global_Enable(void)
{
    PPCASM ("wrteei 1"); /* PRQA S 1006 */
}

/*******************************************************************************
 * @brief      Set the specified interrupt priority
 * @param[in]  IntrId intr_id, IntrPrior intr_prior
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
status_t INTC_LLD_Set_IRQ_Priority(IntrId intr_id, IntrPrior intr_prior)
{
    if (intr_id > INTR_ID_BUTT) {
        return STATUS_MCU_INVALID_INTC_NUM;
    }

    if (intr_prior > INTR_PRI_BUTT) {
        return STATUS_MCU_INVALID_PRIOR_NUM;
    }

    INTC_0.PSR[intr_id].B.PRIN = (uint32_t)intr_prior;

    return STATUS_SUCCESS;
}

/*******************************************************************************
 * @brief      Set the global interrupt priority
 * @param[in]  IntrId intr_id
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
status_t INTC_LLD_Set_Global_Priority(IntrPrior intr_prior)
{
    uint8 core_id = GetCoreID();

    if (intr_prior > INTR_PRI_BUTT) {
        return STATUS_MCU_INVALID_PRIOR_NUM;
    }

    INTC_0.CPR[core_id].B.PRI = (uint32_t)intr_prior;

    return STATUS_SUCCESS;
}

/*******************************************************************************
 * @brief      Set the specified interrupt callback
 * @param[in]  IntrId intr_id, IntrHandle intr_handle
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
status_t INTC_LLD_Set_IRQ_Handle(IntrId intr_id, IntrHandle intr_handle)
{
    uint32_t vector_base = INTC_LLD_Get_Vector_Table();

    if (intr_id > INTR_ID_BUTT) {
        return STATUS_MCU_INVALID_INTC_NUM;
    }

    *((IntrHandle *)vector_base + (uint32_t)intr_id) = intr_handle;

    return STATUS_SUCCESS;
}

/*******************************************************************************
 * @brief      Switch interrupt handle mode
 * @param[in]  IntcMode intc_mode
 * @param[out] None
 * @retval     status_code
 * @notapi
 *******************************************************************************/
status_t INTC_LLD_Swtich_Mode(IntcMode intc_mode) /* PRQA S 1503 */
{
    INTC_BCR_tag INTC_BCR;
    uint8 core_id = GetCoreID();

    if (core_id >= CORE_ID_BUTT) {
        return STATUS_MCU_INVALID_CORE_ID;
    }

    if (intc_mode >= INTC_MODE_BNUTT) {
        return STATUS_MCU_INVALID_INTC_MODE;
    }

    INTC_BCR.R = INTC_0.BCR.R;

    switch (core_id) {
        case CORE_ID_Z7_0: {
            INTC_BCR.B.HVEN0 = (uint32_t)intc_mode;
            INTC_0.BCR.R = INTC_BCR.R;
            break;
        }
        case CORE_ID_Z7_1: {
            INTC_BCR.B.HVEN1 = (uint32_t)intc_mode;
            INTC_0.BCR.R = INTC_BCR.R;
            break;
        }
        case CORE_ID_Z4_2: {
            INTC_BCR.B.HVEN2 = (uint32_t)intc_mode;
            INTC_0.BCR.R = INTC_BCR.R;
            break;
        }
        default: { /* PRQA S 2024 */
            return STATUS_MCU_INVALID_CORE_ID;
        }
    }

    return STATUS_SUCCESS;
}
