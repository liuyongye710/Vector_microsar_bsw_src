/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3007PT
* DESCRIPTION : console c file
* HISTORY     : Initial version
* @file     console.c
* @version  1.0
* @date     2023 - 05 - 06
* @brief    Initial version.
*
*****************************************************************************/
/*PRQA S 1505,1503,3335,3437 EOF*/
#include "console.h" /* PRQA S 0380 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "intc_lld.h"

static struct Private_Param *Param; /* PRQA S 1504 */
static struct Private_Param ParamN; /* PRQA S 1504, 1514, 0308, 3218 */
static struct Lin_Device STD_DEV; /* PRQA S 1504, 1514 */
/*******************************************************************************
 * @brief   UART_Siu_Conf
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
static void UART_Siu_Conf(const struct Lin_Device *dev) /* PRQA S 1504, 1505 */
{
    volatile const struct LINFlexD_tag *LINFLEX_PTR = dev->lin_num;

    if(LINFLEX_PTR == &LINFlexD_2)
    {
        //LINFlexD_2 SCI_TX PD[14] output
        SIUL2.MSCR_IO[PD14].R = 0x32840002;
        //LINFlexD_2 SCI_RX PD[15] input
        SIUL2.MSCR_IO[PD15].R = 0x308C0000;
        SIUL2.MSCR_MUX[338].R = 1;
    }
    else if(LINFLEX_PTR == &LINFlexD_1)
    {
        //LINFlexD_1 SCI_TX PE[7] output
        SIUL2.MSCR_IO[PE7].R = 0x32840002;
        //LINFlexD_1 SCI_RX PE[6] input
        SIUL2.MSCR_IO[PE6].R = 0x308C0000;
        SIUL2.MSCR_MUX[337].R = 1;
    }
    else if(LINFLEX_PTR == &LINFlexD_16)
    {
         SIUL2.MSCR_IO[PQ13].R = 0x32840002; /* LINFlexD_16 TX PQ[13] */

         SIUL2.MSCR_IO[PQ15].R = 0x308C0000; /* LINFlexD_16 RX PQ[15] */
         SIUL2.MSCR_MUX[352].R = 2;          /* PQ[15] */
    }
    else if(LINFLEX_PTR == &LINFlexD_15)
	{
		 SIUL2.MSCR_IO[PC2].R = 0x32840006; /* LINFlexD_15 TX PC[2] */

		 SIUL2.MSCR_IO[PC1].R = 0x30080000; /* LINFlexD_15 RX PC[1] */
		 SIUL2.MSCR_MUX[351].R = 6;          /* PQ[15] */
	}
    else /* PRQA S 2013 */
    {

    }
}
/*******************************************************************************
 * @brief   UART_CLEAR
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void UART_CLEAR(const struct Lin_Device *dev) /* PRQA S 1503, 3408 */
{
    volatile struct LINFlexD_tag *LINFLEX_PTR;

    LINFLEX_PTR = dev->lin_num;
    LINFLEX_PTR->LINCR1.R &= 1U;
    LINFLEX_PTR->UARTCR.R = 0U;
}
/*******************************************************************************
 * @brief   UART_Set_Baudrate
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void UART_Set_Baudrate(const struct Lin_Device *dev, uint64_t sys_clock, uint64_t baudrate) /* PRQA S 1503, 3408 */
{
    volatile struct LINFlexD_tag *LINFLEX_PTR;
    uint32_t rate,rate_f,rate_m;

    LINFLEX_PTR = dev->lin_num;

    LINFLEX_PTR->LINCR1.B.SLEEP  = DISABLE;
    LINFLEX_PTR->LINCR1.B.BF     = DISABLE;

    LINFLEX_PTR->UARTCR.B.UART   = 1U;
    LINFLEX_PTR->UARTCR.B.RxEn   = ENABLE;
    LINFLEX_PTR->UARTCR.B.TxEn   = ENABLE;

    rate = (uint32_t)(sys_clock / baudrate);
    rate_f = rate % 16U;
    rate_m = rate / 16U;

    LINFLEX_PTR->LINFBRR.B.FBR = rate_f;
    LINFLEX_PTR->LINIBRR.B.IBR = rate_m;

    LINFLEX_PTR->UARTSR.B.DRFRFE = 1U;
    LINFLEX_PTR->UARTSR.B.DTFTFF = 1U;
}
/*******************************************************************************
 * @brief   UART_Set_Param
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/


void UART_Set_Param(const struct Lin_Device *dev,uint8_t parity,uint8_t bit_len,uint8_t tfc,uint8_t rfc) /* PRQA S 1503, 3408 */
{
    volatile struct LINFlexD_tag *LINFLEX_PTR;

    LINFLEX_PTR = dev->lin_num;
    LINFLEX_PTR->LINCR1.B.LBKM = 0U;

    switch(parity)
    {
        case 0:
            LINFLEX_PTR->UARTCR.B.PCE = DISABLE;
            break;
        case UART_ODD_PARITY:
            LINFLEX_PTR->UARTCR.B.PCE = ENABLE;
            LINFLEX_PTR->UARTCR.B.PC0 = 1U; /*Parity sent is odd*/
            break;
        case UART_EVEN_PARITY:
            LINFLEX_PTR->UARTCR.B.PCE = ENABLE;
            LINFLEX_PTR->UARTCR.B.PC0 = 0U; /*Parity sent is even*/
            break;
        default:
            LINFLEX_PTR->UARTCR.B.PCE = DISABLE;
            break;
    }

    switch(bit_len)
    {
        case 7:
            LINFLEX_PTR->UARTCR.B.WL0 = 0U;
            break;
        case 8:
            LINFLEX_PTR->UARTCR.B.WL0 = 1U;
            break;
        default:
            LINFLEX_PTR->UARTCR.B.WL0 = 1U;
            break;
    }

    LINFLEX_PTR->UARTCR.B.TDFL_TFC = tfc;   /* Tx FIFO counter*/
    LINFLEX_PTR->UARTCR.B.RDFL_RFC = rfc;   /* Rx FIFO counter*/
}
/*******************************************************************************
 * @brief   UART_INT_DIS
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void UART_INT_DIS(const struct Lin_Device *dev)
{
    volatile struct LINFlexD_tag *LINFLEX_PTR;
    LINFLEX_PTR = dev->lin_num;
    LINFLEX_PTR->LINIER.R = 0U;

    LINFLEX_PTR->LINIER.B.DRIE = 1;
}
/*******************************************************************************
 * @brief   UART_TX
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void UART_TX(const struct Lin_Device *dev, char data)
{
    volatile struct LINFlexD_tag *LINFLEX_PTR = dev->lin_num;

    LINFLEX_PTR->UARTSR.B.DTFTFF = 1U;

    LINFLEX_PTR->BDRL.B.DATA0 = (uint8_t)data;

    while(LINFLEX_PTR->UARTSR.B.DTFTFF == 0U) {}

}

/*******************************************************************************
 * @brief   UART_RX
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
uint8_t UART_RX(const struct Lin_Device *dev)
{
    uint8_t datain;
    volatile struct LINFlexD_tag *LINFLEX_PTR = dev->lin_num;

    while(LINFLEX_PTR->UARTSR.B.DRFRFE == 0U) {;}

    datain=(uint8_t)(LINFLEX_PTR->BDRM.B.DATA4);
    LINFLEX_PTR->UARTSR.B.DRFRFE = 1U;

    return datain;
}
/*******************************************************************************
 * @brief   UartComm_Rx_Handler
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void UartComm_Rx_Handler(struct Lin_Device *dev)/*PRQA S 3673*/
{
    volatile struct LINFlexD_tag *LINFLEX_PTR = dev->lin_num;

    Param = dev->param_num; /* PRQA S 2919 */

    if(Param->rx_buflen >= 0U)/*PRQA S 2991,2995*/
    {
        Param->rx_buf[0] = (uint8_t)(LINFLEX_PTR->BDRM.B.DATA4);
    }
    if(Param->rx_buflen >= 1U)
    {
        Param->rx_buf[1] = (uint8_t)(LINFLEX_PTR->BDRM.B.DATA5);
    }
    if(Param->rx_buflen >= 2U)
    {
        Param->rx_buf[2] = (uint8_t)(LINFLEX_PTR->BDRM.B.DATA6);
    }
    if(Param->rx_buflen >= 3U)
    {
        Param->rx_buf[3] = (uint8_t)(LINFLEX_PTR->BDRM.B.DATA7);
    }

    Param->rx_flag = 1U;
    Param->rx_count++;

    LINFLEX_PTR->UARTSR.B.DRFRFE = 1U;
}
/*******************************************************************************
 * @brief   UartComm_Tx_Handler
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void UartComm_Tx_Handler(struct Lin_Device *dev)/*PRQA S 3673*/
{
    volatile struct LINFlexD_tag *LINFLEX_PTR = dev->lin_num;

    LINFLEX_PTR->UARTSR.B.DTFTFF = 1U;

    Param = dev->param_num;/*PRQA S 2919*/

    Param->tx_flag = 1U;
    Param->tx_count++;
}
/*******************************************************************************
 * @brief   Uart00_Rx_Handler
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void Uart00_Rx_Handler(void)
{
    UartComm_Rx_Handler(&(STD_DEV));
}
/*******************************************************************************
 * @brief   Uart00_Tx_Handler
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void Uart00_Tx_Handler(void)
{
    UartComm_Tx_Handler(&(STD_DEV));
}
/*******************************************************************************
 * @brief   Std_Dev_Register
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void Std_Dev_Register(struct Lin_Device *lin_dev,volatile struct LINFlexD_tag *base,struct Private_Param *Paramx)
{
    lin_dev->lin_num = base;/*PRQA S 2919*/
    lin_dev->param_num = Paramx;

    return;
}
/*******************************************************************************
 * @brief   LINFLEX_Start_Config
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void LINFLEX_Start_Config(struct Lin_Device *dev)/*PRQA S 3673*/
{
    volatile struct LINFlexD_tag *LINFLEX_PTR;
    LINFLEX_PTR = dev->lin_num;
    LINFLEX_PTR->LINCR1.B.INIT = ENABLE;
}
/*******************************************************************************
 * @brief   LINFLEX_Complete_Config
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void LINFLEX_Complete_Config(struct Lin_Device *dev)/*PRQA S 3673*/
{
    volatile struct LINFlexD_tag *LINFLEX_PTR;
    LINFLEX_PTR = dev->lin_num;
    LINFLEX_PTR->LINCR1.B.INIT   = DISABLE;
}
/*******************************************************************************
 * @brief   Uart_Send_Char
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void Uart_Send_Char(char s)
{
    UART_TX(Param->std_uart,s);
}

/*******************************************************************************
 * @brief   STDIO_OUT_INIT
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void STDIO_OUT_INIT(struct Lin_Device *dev)
{
    uint32_t lin_clockfre;
    Param = dev->param_num;/*PRQA S 2919*/
    Param->std_uart = dev;

    (void)CLOCK_GetModuleClockFreq(LIN_CLK, &lin_clockfre);
    LINFLEX_Start_Config(Param->std_uart);
    UART_Siu_Conf(Param->std_uart);
    UART_Set_Baudrate(Param->std_uart,(uint64_t)lin_clockfre,UART_BAUDRATE);
    UART_Set_Param(Param->std_uart,UART_ODD_PARITY,8U,0U,0U);
    UART_INT_DIS(Param->std_uart);
    LINFLEX_Complete_Config(Param->std_uart);
}

void Uart_SendStr(const char * s)
{
    const char * tmp = s;

    while(tmp < (s + strlen(s)))
    {
        Uart_Send_Char(*tmp++);/* PRQA S 3387, 3440 */
    }
}

/*******************************************************************************
 * @brief   PSPRINTF
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void PSPRINTF(const char *fmt, ...)/*PRQA S 1337*/
{
    char string[255];
    va_list ap;

    (void)va_start(ap , fmt);

    (void)vsprintf(string, fmt, ap);

    (void)Uart_SendStr(string);

    (void)va_end(ap);/*PRQA S 5140,3119*/
}

uint8_t Uart_Get_Char(struct Lin_Device *dev)/*PRQA S 3673*/
{
    uint32_t datain = 0;
    volatile struct LINFlexD_tag *LINFLEX_PTR = dev->lin_num;
    if(LINFLEX_PTR->UARTSR.B.DRFRFE == 1U)
    {
        datain = LINFLEX_PTR->BDRM.B.DATA4;
        LINFLEX_PTR->UARTSR.B.DRFRFE = 1U;
        return (uint8_t)datain;
    }
    else
    {
        return (uint8_t)-1;
    }
}

int8_t GETCHAR(uint8* data, uint16 num)
{
    if (LINFlexD_15.UARTSR.B.DRFRFE == 1U) {
        LINFlexD_15.UARTSR.B.DRFRFE = 1;
        *data = LINFlexD_15.BDRM.B.DATA4;/* PRQA S 2857 */
        return 1;
    }
    return 0;
}


/*========================== */

/*==========================*/

void HandleDebugCmd(uint8_t cmdChar)
{

}

void LINFLEXD2_UART_RxIRQHandler(void)
{
    uint8_t data = 0U;
    if (LINFlexD_2.UARTSR.B.DRFRFE == 1U)
    {
        LINFlexD_2.UARTSR.B.DRFRFE = 1U;
        data = LINFlexD_2.BDRM.B.DATA4;
        HandleDebugCmd(data);
    }
}

void LINFLEXD15_UART_RxIRQHandler(void)
{
    uint8_t data = 0U;
    if(LINFlexD_15.UARTSR.B.DRFRFE == 1U)
    {
        LINFlexD_15.UARTSR.B.DRFRFE = 1U;
        data = LINFlexD_15.BDRM.B.DATA4;
        HandleDebugCmd(data);
    }
}
void LINFLEXD16_UART_RxIRQHandler(void)
{
    uint8_t data = 0U;
    if(LINFlexD_16.UARTSR.B.DRFRFE == 1U)
    {
        LINFlexD_16.UARTSR.B.DRFRFE = 1U;
        data = LINFlexD_16.BDRM.B.DATA4;
        HandleDebugCmd(data);
    }
}

/*******************************************************************************
 * @brief      Console_Init
 *
 * @param[in]  None
 * @param[out] None
 * @retval     None
 * @notapi
 *******************************************************************************/
void Console_Init(void)
{
    /* Interrupt Initialize */
//    INTC_LLD_Set_IRQ_Priority(INTR_ID_436, INTR_PRI_6);
//    INTC_LLD_Set_IRQ_Handle(INTR_ID_436, LINFLEXD15_UART_RxIRQHandler);
//    INTC_LLD_Set_IRQ_Enable(INTR_ID_436);
    Std_Dev_Register(&STD_DEV,&LINFlexD_15,&ParamN);
    STDIO_OUT_INIT(&STD_DEV);
}
