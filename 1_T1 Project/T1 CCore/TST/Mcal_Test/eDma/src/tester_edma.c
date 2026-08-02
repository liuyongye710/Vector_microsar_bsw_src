#include "shell.h"
#include <string.h>
#include "tester_edma.h"
#include "eDma_Cfg.h"

#define EDMA_TEST_CASE_MAX 1

extern CONST(EDma_ConfigType, EDMA_CONST) EDma_Config;
static CONST(IntrId, EDMA_CONST) s_edmaIrqId[EDMA_MAPPED_CHN_INTERRUPT_LINES] = DMA_CHN_IRQS; /* PRQA S 3218 */

static EdmafuncMachine edma_funcs[] = {
    {"EDMA_0001", EDMA_0001},
};

void EDMA_IRQ_Priority() {
    (void) INTC_LLD_Set_IRQ_Priority(DMA0_ERR0_127_IRQ52, INTR_PRI_1);
    (void) INTC_LLD_Set_IRQ_Handle(DMA0_ERR0_127_IRQ52, &EDMA_Ch0_Ch127_Error_IRQHandler);
    (void) INTC_LLD_Set_IRQ_Enable(DMA0_ERR0_127_IRQ52);
}

void EDMA_0001() {
    EDMA_Init(&EDma_Config);
    PSPRINTF("EDMA_0001 is OK if ReportError is not printed\n");
}

FUNC(void, EDMA_CODE) EDMA_HW_IrqInstall(VAR(uint32, AUTOMATIC) mappedChannel)
{
    VAR(IntrId, AUTOMATIC) irqNumber = NotAvail_IRQn;

    if (mappedChannel < EDMA_MAPPED_CHN_INTERRUPT_LINES)
    {
        irqNumber = s_edmaIrqId[mappedChannel];
    }
    else
    {
        EDMA_DEV_ERR(FALSE);
    }

    switch (mappedChannel)
    {
    case(0U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch0_IRQHandler);
        break;
    }
    case(1U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch1_IRQHandler);
        break;
    }
    case(2U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch2_IRQHandler);
        break;
    }
    case(3U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch3_IRQHandler);
        break;
    }
    case(4U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch4_IRQHandler);
        break;
    }
    case(5U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch5_IRQHandler);
        break;
    }
    case(6U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch6_IRQHandler);
        break;
    }
    case(7U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch7_IRQHandler);
        break;
    }
    case(8U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch8_IRQHandler);
        break;
    }
    case(9U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch9_IRQHandler);
        break;
    }
    case(10U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch10_IRQHandler);
        break;
    }
    case(11U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch11_IRQHandler);
        break;
    }
    case(12U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch12_IRQHandler);
        break;
    }
    case(13U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch13_IRQHandler);
        break;
    }
    case(14U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch14_IRQHandler);
        break;
    }
    case(15U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch15_IRQHandler);
        break;
    }
    case(16U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch16_IRQHandler);
        break;
    }
    case(17U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch17_IRQHandler);
        break;
    }
    case(18U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch18_IRQHandler);
        break;
    }
    case(19U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch19_IRQHandler);
        break;
    }
    case(20U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch20_IRQHandler);
        break;
    }
    case(21U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch21_IRQHandler);
        break;
    }
    case(22U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch22_IRQHandler);
        break;
    }
    case(23U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch23_IRQHandler);
        break;
    }
    case(24U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch24_IRQHandler);
        break;
    }
    case(25U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch25_IRQHandler);
        break;
    }
    case(26U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch26_IRQHandler);
        break;
    }
    case(27U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch27_IRQHandler);
        break;
    }
    case(28U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch28_IRQHandler);
        break;
    }
    case(29U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch29_IRQHandler);
        break;
    }
    case(30U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch30_IRQHandler);
        break;
    }
    case(31U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch31_IRQHandler);
        break;
    }
    case(32U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch32_IRQHandler);
        break;
    }
    case(33U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch33_IRQHandler);
        break;
    }
    case(34U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch34_IRQHandler);
        break;
    }
    case(35U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch35_IRQHandler);
        break;
    }
    case(36U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch36_IRQHandler);
        break;
    }
    case(37U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch37_IRQHandler);
        break;
    }
    case(38U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch38_IRQHandler);
        break;
    }
    case(39U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch39_IRQHandler);
        break;
    }
    case(40U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch40_IRQHandler);
        break;
    }
    case(41U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch41_IRQHandler);
        break;
    }
    case(42U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch42_IRQHandler);
        break;
    }
    case(43U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch43_IRQHandler);
        break;
    }
    case(44U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch44_IRQHandler);
        break;
    }
    case(45U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch45_IRQHandler);
        break;
    }
    case(46U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch46_IRQHandler);
        break;
    }
    case(47U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch47_IRQHandler);
        break;
    }
    case(48U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch48_IRQHandler);
        break;
    }
    case(49U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch49_IRQHandler);
        break;
    }
    case(50U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch50_IRQHandler);
        break;
    }
    case(51U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch51_IRQHandler);
        break;
    }
    case(52U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch52_IRQHandler);
        break;
    }
    case(53U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch53_IRQHandler);
        break;
    }
    case(54U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch54_IRQHandler);
        break;
    }
    case(55U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch55_IRQHandler);
        break;
    }
    case(56U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch56_IRQHandler);
        break;
    }
    case(57U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch57_IRQHandler);
        break;
    }
    case(58U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch58_IRQHandler);
        break;
    }
    case(59U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch59_IRQHandler);
        break;
    }
    case(60U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch60_IRQHandler);
        break;
    }
    case(61U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch61_IRQHandler);
        break;
    }
    case(62U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch62_IRQHandler);
        break;
    }
    case(63U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch63_IRQHandler);
        break;
    }
    case(64U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch64_IRQHandler);
        break;
    }
    case(65U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch65_IRQHandler);
        break;
    }
    case(66U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch66_IRQHandler);
        break;
    }
    case(67U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch67_IRQHandler);
        break;
    }
    case(68U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch68_IRQHandler);
        break;
    }
    case(69U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch69_IRQHandler);
        break;
    }
    case(70U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch70_IRQHandler);
        break;
    }
    case(71U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch71_IRQHandler);
        break;
    }
    case(72U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch72_IRQHandler);
        break;
    }
    case(73U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch73_IRQHandler);
        break;
    }
    case(74U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch74_IRQHandler);
        break;
    }
    case(75U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch75_IRQHandler);
        break;
    }
    case(76U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch76_IRQHandler);
        break;
    }
    case(77U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch77_IRQHandler);
        break;
    }
    case(78U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch78_IRQHandler);
        break;
    }
    case(79U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch79_IRQHandler);
        break;
    }
    case(80U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch80_IRQHandler);
        break;
    }
    case(81U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch81_IRQHandler);
        break;
    }
    case(82U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch82_IRQHandler);
        break;
    }
    case(83U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch83_IRQHandler);
        break;
    }
    case(84U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch84_IRQHandler);
        break;
    }
    case(85U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch85_IRQHandler);
        break;
    }
    case(86U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch86_IRQHandler);
        break;
    }
    case(87U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch87_IRQHandler);
        break;
    }
    case(88U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch88_IRQHandler);
        break;
    }
    case(89U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch89_IRQHandler);
        break;
    }
    case(90U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch90_IRQHandler);
        break;
    }
    case(91U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch91_IRQHandler);
        break;
    }
    case(92U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch92_IRQHandler);
        break;
    }
    case(93U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch93_IRQHandler);
        break;
    }
    case(94U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch94_IRQHandler);
        break;
    }
    case(95U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch95_IRQHandler);
        break;
    }
    case(96U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch96_IRQHandler);
        break;
    }
    case(97U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch97_IRQHandler);
        break;
    }
    case(98U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch98_IRQHandler);
        break;
    }
    case(99U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch99_IRQHandler);
        break;
    }
    case(100U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch100_IRQHandler);
        break;
    }
    case(101U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch101_IRQHandler);
        break;
    }
    case(102U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch102_IRQHandler);
        break;
    }
    case(103U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch103_IRQHandler);
        break;
    }
    case(104U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch104_IRQHandler);
        break;
    }
    case(105U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch105_IRQHandler);
        break;
    }
    case(106U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch106_IRQHandler);
        break;
    }
    case(107U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch107_IRQHandler);
        break;
    }
    case(108U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch108_IRQHandler);
        break;
    }
    case(109U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch109_IRQHandler);
        break;
    }
    case(110U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch110_IRQHandler);
        break;
    }
    case(111U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch111_IRQHandler);
        break;
    }
    case(112U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch112_IRQHandler);
        break;
    }
    case(113U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch113_IRQHandler);
        break;
    }
    case(114U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch114_IRQHandler);
        break;
    }
    case(115U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch115_IRQHandler);
        break;
    }
    case(116U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch116_IRQHandler);
        break;
    }
    case(117U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch117_IRQHandler);
        break;
    }
    case(118U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch118_IRQHandler);
        break;
    }
    case(119U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch119_IRQHandler);
        break;
    }
    case(120U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch120_IRQHandler);
        break;
    }
    case(121U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch121_IRQHandler);
        break;
    }
    case(122U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch122_IRQHandler);
        break;
    }
    case(123U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch123_IRQHandler);
        break;
    }
    case(124U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch124_IRQHandler);
        break;
    }
    case(125U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch125_IRQHandler);
        break;
    }
    case(126U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch126_IRQHandler);
        break;
    }
    case(127U):
    {
        (void) INTC_LLD_Set_IRQ_Priority(irqNumber, INTR_PRI_1);
        (void) INTC_LLD_Set_IRQ_Handle(irqNumber, &EDMA_Ch127_IRQHandler);
        break;
    }
    default:
    {
        EDMA_DEV_ERR(FALSE);
        break;
    }
    }
    (void) INTC_LLD_Set_IRQ_Enable(irqNumber);
}

int edma_func(int argc, char *agrv[])
{
    if ((argc > 3) || (argc < 2)) {
        PSPRINTF("error: The number of parameters exceeds 3 or is less than 2\n");
    }
    else
    {
        EDMA_IRQ_Priority();
        if (argc == 2)
        {
            if (!strcmp(agrv[1], "help"))
            {
                PSPRINTF("[1 - %d] ----- CMD ------- ID of the test case\n", EDMA_TEST_CASE_MAX);
            }
            else
            {
                uint32 id = (uint32)atoi(agrv[1]);
                PSPRINTF("%d\r\n", id);
                if ((id >= 1) && (id <= EDMA_TEST_CASE_MAX)) 
                {
                    if (edma_funcs[id - 1].edmafunc != NULL_PTR)
                    {
                        edma_funcs[id - 1].edmafunc();
                    }
                    else
                    {
                        PSPRINTF("error: The ID entered does not correspond to the test code\n");
                    }
                }
                else
                {
                    PSPRINTF("error: Input invalid parameters[%d], please output [1 - %d] range parameters\n", id, EDMA_TEST_CASE_MAX);
                }
            }
        }
    }
    return 0;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), edma_test, edma_func, deint or number of test case);
