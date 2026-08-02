#include"SC2167.h"
#include"Platform_Types.h"
#include "IoHwAb.h"
#include "Dio.h"
#include"spi.h"
uint8 send_fault_ad=0xFF;
uint8 read_fault_data;
uint8 send_exc_f_ad=0x91;
uint8 send_control_ad=0x92;
uint8 read_exc_f_ad;
uint8 read_control_ad;
uint8 send_exc_f_data=0x28;
uint8 send_control_data=0x6A;
uint8 read_exc_f_data;
uint8 read_control_data;
uint16 send_angle=0x8000;
uint16 read_angle;
uint16 send_speed=0x8200;
uint16 read_speed;
void SC2167_init(void)
{
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SOE].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 1;
    for(int i=0;i<2;i++);//16ns
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 0;
    for(int i=0;i<3;i++);//�ӳ�700ns
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_A0].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_A1].B.PDO = 1;
    Spi_SetupEB(0,&send_fault_ad, &read_fault_data,1);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 0;
    Spi_SyncTransmit(0);

    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 0;
    for(int i=0;i<2;i++);//16ns
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_RES0].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_RES1].B.PDO = 1;//12bit
    Spi_SetupEB(0,&send_exc_f_ad, &read_exc_f_ad,1);   /*Write configuration*/
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 0;
    Spi_SyncTransmit(0);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 1;
    Spi_SetupEB(0,&send_exc_f_data, &read_exc_f_data,1);   /*Write configuration*/
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 0;
    Spi_SyncTransmit(0);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 1;
    Spi_SetupEB(0,&send_control_ad, &read_control_ad,1);   /*Write configuration*/
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 0;
    Spi_SyncTransmit(0);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 1;
    Spi_SetupEB(0,&send_control_data, &read_control_data,1);   /*Write configuration*/
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 0;
    Spi_SyncTransmit(0);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_A0].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_A1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 1;
}

uint16 SC2167_Angle(void){
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_A0].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_A1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 0;
    for(uint8 i=0;i<10;i++);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 0;
    Spi_SetupEB(3,&send_angle, &read_angle,1);
    Spi_SyncTransmit(3);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 1;
    return read_angle;
}
uint16 SC2167_Speed(void){

    SIUL2.GPDO[DioConf_DioChannel_DO_RT_A0].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_A1].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 0;
    for(uint8 i=0;i<10;i++);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_SAMPLE].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 0;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 0;
    Spi_SetupEB(3,&send_speed, &read_speed,1);
    Spi_SyncTransmit(3);
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_WRN].B.PDO = 1;
    SIUL2.GPDO[DioConf_DioChannel_DO_RT_CSn_M1].B.PDO = 1;
    return read_speed;
}
void SC2167_Angle_Speed(void){
    IoHwAb_Dio_WriteChannel(DO_RT_A0,0);
    IoHwAb_Dio_WriteChannel(DO_RT_A1,0);
    IoHwAb_Dio_WriteChannel(DO_RT_SAMPLE,0);
    for(uint8 i=0;i<10;i++);//�ӳ�2us
    IoHwAb_Dio_WriteChannel(DO_RT_SAMPLE,1);
    Dio_WriteChannel(DioConf_DioChannel_DO_RT_CSn_M1, 0);
    IoHwAb_Dio_WriteChannel(DO_RT_WRN,0);
    Spi_SetupEB(0,&send_angle, &read_angle,2);
    Spi_SyncTransmit(0);
    IoHwAb_Dio_WriteChannel(DO_RT_WRN,1);
    Dio_WriteChannel(DioConf_DioChannel_DO_RT_CSn_M1, 1);//λ�����
    IoHwAb_Dio_WriteChannel(DO_RT_A0,0);
    IoHwAb_Dio_WriteChannel(DO_RT_A1,1);
    Dio_WriteChannel(DioConf_DioChannel_DO_RT_CSn_M1, 0);
    IoHwAb_Dio_WriteChannel(DO_RT_WRN,0);
    Spi_SetupEB(0,&send_speed, &read_speed,2);
    Spi_SyncTransmit(0);
    IoHwAb_Dio_WriteChannel(DO_RT_WRN,1);
    Dio_WriteChannel(DioConf_DioChannel_DO_RT_CSn_M1, 1);//�ٶ����
}
void SC2167_diag(void){
    IoHwAb_Dio_WriteChannel(DO_RT_A0,1);
    IoHwAb_Dio_WriteChannel(DO_RT_A1,1);
    Spi_SetupEB(0,&send_fault_ad, &read_fault_data,1);
    Dio_WriteChannel(DioConf_DioChannel_DO_RT_CSn_M1, 0);
    IoHwAb_Dio_WriteChannel(DO_RT_WRN,0);
    Spi_SyncTransmit(0);
    IoHwAb_Dio_WriteChannel(DO_RT_WRN,1);
    Dio_WriteChannel(DioConf_DioChannel_DO_RT_CSn_M1, 1);
    Spi_SetupEB(0,&send_fault_ad, &read_fault_data,1);
    Dio_WriteChannel(DioConf_DioChannel_DO_RT_CSn_M1, 0);
    IoHwAb_Dio_WriteChannel(DO_RT_WRN,0);
    Spi_SyncTransmit(0);
    IoHwAb_Dio_WriteChannel(DO_RT_WRN,1);
    Dio_WriteChannel(DioConf_DioChannel_DO_RT_CSn_M1, 1);//������
}
