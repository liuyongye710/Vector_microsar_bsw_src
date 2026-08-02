/*
 * POWER_Ctrl.c
 *
 *  Created on: 2025年1月3日
 *      Author: liuziyu
 */
#include "IoHwAb.h"
#include"Spi.h"
uint32 unlock_send=0xABEF5612;//解锁
uint32 unlock_read;
uint16 send_fault=0x8A01;//关闭故障寄存器
uint16 read_fault;
uint16 send_watchdog=0x8D21;//关闭看门狗
uint16 read_watchdog;
uint16 send_ldosty=0x8800;//关闭LDO_STY
uint16 read_ldosty;
uint32 lock_send=0xDF34BECA;//上锁
uint32 lock_read;

uint16 send_LDOcurrent=0x8418;//LDO配置阈值100mA
uint16 read_LDOcurrent;
uint16 send_5Voutp=0x01F4;//配置5V输出
uint16 read_5Voutp;
uint16 send_5Voutn=0xAC0A;//配置5V输出取反
uint16 read_5Voutn;
void POWER_init(void)
{
    IoHwAb_Dio_WriteChannel(DO_DB_15V_SW1,1);
    IoHwAb_Dio_WriteChannel(DO_DB_15V_SW2,1);

    Spi_SetupEB(1,&unlock_send, &unlock_read,2);   /*Write configuration*/
    Spi_SyncTransmit(1);
    for(uint8 i;i<100;i++)
    Spi_SetupEB(1,&send_fault, &read_fault,1);   /*Write configuration*/
    Spi_SyncTransmit(1);
    Spi_SetupEB(1,&send_watchdog, &read_watchdog,1);   /*Write configuration*/
    Spi_SyncTransmit(1);
    Spi_SetupEB(1,&send_ldosty, &read_ldosty,1);   /*Write configuration*/
    Spi_SyncTransmit(1);
    Spi_SetupEB(1,&lock_send, &lock_read,2);   /*Write configuration*/
    Spi_SyncTransmit(1);

    Spi_SetupEB(1,&send_LDOcurrent, &read_LDOcurrent,1);   /*Write configuration*/
    Spi_SyncTransmit(1);
    Spi_SetupEB(1,&send_5Voutp, &read_5Voutp,1);   /*Write configuration*/
    Spi_SyncTransmit(1);
    Spi_SetupEB(1,&send_5Voutn, &read_5Voutn,1);   /*Write configuration*/
    Spi_SyncTransmit(1);

}
