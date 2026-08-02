/****************************************************************************
*
* Copyright (c) 2023  C*Core -   All Rights Reserved
*
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED,
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* PROJECT     : CCFC3007PT
* DESCRIPTION : console h file
* HISTORY     : Initial version
* @file     console.h
* @version  1.0
* @date     2023 - 05 - 06
* @brief    Initial version.
*
*****************************************************************************/

#ifndef COMMON_INC_CONSOLE_H_
#define COMMON_INC_CONSOLE_H_

#include <stdlib.h>
#include <stdio.h>
#include "derivative.h"
// #include "demo.h"

/*PRQA S 3630, 0659 EOF*/

#define UART_BAUDRATE           (115200U)

#ifndef DISABLE
#define DISABLE                 (0U)         /*Bit-Field Is Disabled */
#endif

#ifndef ENABLE
#define ENABLE                  (1U)         /*Bit-Field Is Enabled  */
#endif

#define UART_DISABLE_PARITY     (0U)
#define UART_ODD_PARITY         (1U)
#define UART_EVEN_PARITY        (2U)

struct Private_Param
{
    uint8_t tx_buf[4];
    uint8_t rx_buf[4];

    uint8_t tx_buflen;
    uint8_t rx_buflen;

    uint8_t tx_flag;
    uint8_t rx_flag;

    uint32_t tx_count;
    uint32_t rx_count;

    struct Lin_Device *std_uart;

};

struct Lin_Device
{
    volatile struct LINFlexD_tag *lin_num;
    struct Private_Param *param_num;
    uint8_t MSid;
};

void UART_INT_DIS(const struct Lin_Device *dev);
void UART_TX(const struct Lin_Device *dev, char data);
uint8_t UART_RX(const struct Lin_Device *dev);
void UartComm_Rx_Handler(struct Lin_Device *dev);
void UartComm_Tx_Handler(struct Lin_Device *dev);
void Uart00_Rx_Handler(void);
void Uart00_Tx_Handler(void);
void Std_Dev_Register(struct Lin_Device *lin_dev,volatile struct LINFlexD_tag *base,struct Private_Param *Paramx);
void LINFLEX_Start_Config(struct Lin_Device *dev);
void LINFLEX_Complete_Config(struct Lin_Device *dev);
void Uart_Send_Char(char s);
void STDIO_OUT_INIT(struct Lin_Device *dev);
uint8_t Uart_Get_Char(struct Lin_Device *dev);
int8_t GETCHAR(uint8* data, uint16 num);
void HandleDebugCmd(uint8_t cmdChar);
void Uart_SendStr(const char * s);

extern void LINFLEXD2_UART_RxIRQHandler(void);
extern void Console_Init(void);
extern void PSPRINTF(const char *fmt, ...);

#if DEMO_TEST
#define Uart_Printf         PSPRINTF
#else
#define Uart_Printf(...)
#endif

#endif /* COMMON_INC_CONSOLE_H_ */
