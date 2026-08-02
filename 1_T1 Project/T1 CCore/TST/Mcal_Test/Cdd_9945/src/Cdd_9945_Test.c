#include "Spi.h"
#include "CDD_9945_Test.h"
#include "Spi_LLDriver.h"
#include "CDD_9945_LLDriver.h"
#include "console.h"
#include "IoHwAb.h"
#include "CDD_9945.h"
#include "CDD_9945_Cfg.h"

#define ADC_TEST_CASE_MAX sizeof(cdd_funcs) / sizeof(Cdd9945funcMachine)

// for cdd_9945_test
uint32_t Writer_save_0002[15] = {0};
uint32_t Read_save_0002[15] = {0};
uint32_t Writer_save_0001 = 0;
uint32_t Read_save_0001[70] = {0};
unsigned int cdd_9945_test_id_cur = 105;
unsigned int cdd_9945_test_id_last = 0;
uint8_t count_cddtime = 0;
uint16_t count2 = 0;
uint8_t flg = 0;
uint8_t flag_9945_test = 0;
uint8_t flag_9945_PH = 0;

const static Cdd9945funcMachine cdd_funcs[] =
{
    {104, cdd_9945_test_0104},
    {105, cdd_9945_test_0105},
    {109, cdd_9945_test_0109},
    {110, cdd_9945_test_0110},
    {111, cdd_9945_test_0111},
    {112, cdd_9945_test_0112},
    {113, cdd_9945_test_0113},
    {114, cdd_9945_test_0114},
    {115, cdd_9945_test_0115},
    {116, cdd_9945_test_0116},
    {117, cdd_9945_test_0117},
    {118, cdd_9945_test_0118},

    {201, cdd_9945_test_0201},
    {202, cdd_9945_test_0202},
    {203, cdd_9945_test_0203},
    {204, cdd_9945_test_0204},
    {205, cdd_9945_test_0205},
    {206, cdd_9945_test_0206},
    {207, cdd_9945_test_0207},
    {208, cdd_9945_test_0208},
    {209, cdd_9945_test_0209},
    {210, cdd_9945_test_0210},
    {211, cdd_9945_test_0211},
    {212, cdd_9945_test_0212},
    {213, cdd_9945_test_0213},
    {214, cdd_9945_test_0214},
    {215, cdd_9945_test_0215},
    {216, cdd_9945_test_0216},

    {295, cdd_9945_test_0295},
    {296, cdd_9945_test_0296},
    {297, cdd_9945_test_0297},
    {298, cdd_9945_test_0298},
    {299, cdd_9945_test_0299},

    {301, cdd_9945_test_0301},
    {302, cdd_9945_test_0302},
    {303, cdd_9945_test_0303},
    {304, cdd_9945_test_0304},
    {305, cdd_9945_test_0305},
    {306, cdd_9945_test_0306},
    {307, cdd_9945_test_0307},
    {308, cdd_9945_test_0308},
    {309, cdd_9945_test_0309},

//    {401, cdd_9945_test_0401},
//    {402, cdd_9945_test_0402},
//    {403, cdd_9945_test_0403},
//    {404, cdd_9945_test_0404},
//    {405, cdd_9945_test_0405},
//    {406, cdd_9945_test_0406},
    {407, cdd_9945_test_0407},
    {408, cdd_9945_test_0408},
    {409, cdd_9945_test_0409},
    {410, cdd_9945_test_0410},
//    {411, cdd_9945_test_0411},
//    {412, cdd_9945_test_0412},
//    {413, cdd_9945_test_0413},
//    {414, cdd_9945_test_0414},
//    {415, cdd_9945_test_0415},
//    {416, cdd_9945_test_0416},
    {417, cdd_9945_test_0417},
    {418, cdd_9945_test_0418},
    {419, cdd_9945_test_0419},
    {420, cdd_9945_test_0420},

    {501, cdd_9945_test_0501},
    {502, cdd_9945_test_0502},
    {503, cdd_9945_test_0503},
    {504, cdd_9945_test_0504},
    {505, cdd_9945_test_0505},
    {506, cdd_9945_test_0506},
    {507, cdd_9945_test_0507},
    {508, cdd_9945_test_0508},
    {509, cdd_9945_test_0509},
    {510, cdd_9945_test_0510},
    {511, cdd_9945_test_0511},
    {512, cdd_9945_test_0512},
    {513, cdd_9945_test_0513},
    {514, cdd_9945_test_0514},

};

void cdd_9945_0000_forspiinit(void)
{
    Spi_Init(&Spi_Configuration);
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
}

void cdd_9945_0001_sub(uint32_t* data, int index);

void cdd_9945_test_task(void)
{
    int index = 0;
    if(cdd_9945_test_id_cur != cdd_9945_test_id_last)
    {
        for(index=0;index<ADC_TEST_CASE_MAX;index++)
        {
             if(cdd_funcs[index].testid == cdd_9945_test_id_cur)
             {
                cdd_funcs[index].cddfunc();
                break;
             }
        }
    }

}

void cdd_9945_0001(void)
{
    int timecount = 0;
    int index = 0;

    for(index=0;index<14;index++)
    {
        switch(index)
        {
            case 0:
                Writer_save_0001 = 0x08000001;
                break;
            case 1:
                Writer_save_0001 = 0x18000000;                
                break;
            case 2:
                Writer_save_0001 = 0x28000000;
                break;
            case 3:
                Writer_save_0001 = 0x38000001;
                break;
            case 4:
                Writer_save_0001 = 0x48000000;
                break;
            case 5:
                Writer_save_0001 = 0x58000001;
                break;
            case 6:
                Writer_save_0001 = 0x68000001;
                break;
            case 7:
                Writer_save_0001 = 0x78000000;
                break;
            case 8:
                Writer_save_0001 = 0x88000000;
                break;
            case 9:
                Writer_save_0001 = 0x98000001;
                break;
            case 10:
                Writer_save_0001 = 0xA8000001;
                break;
            case 11:
                Writer_save_0001 = 0xBAAAAAAB;
                break;
            case 12:
                Writer_save_0001 = 0xCAAAAAAA;
                break;
            case 13:
                Writer_save_0001 = 0xDAAAAAAB;
                break;
            default:
                break;
        }
        cdd_9945_0001_sub(&Writer_save_0001,index);
    }

    return ;
}

void cdd_9945_0001_sub(uint32_t* data, int index)
{
    uint32_t Writer_save_0001_blank = 0xFFFFFFFE;

    Spi_SetupEB(0,data, &Read_save_0001[index*5+0],1);
    Spi_SyncTransmit(0);

    Spi_SetupEB(0,&Writer_save_0001_blank,&Read_save_0001[index*5+0],1);
    Spi_SyncTransmit(0);

    Spi_SetupEB(1,data,&Read_save_0001[index*5+1],1);
    Spi_SyncTransmit(1);

    Spi_SetupEB(1,&Writer_save_0001_blank,&Read_save_0001[index*5+1],1);
    Spi_SyncTransmit(1);

    Spi_SetupEB(2,data,&Read_save_0001[index*5+2],1);
    Spi_SyncTransmit(2);

    Spi_SetupEB(2,&Writer_save_0001_blank,&Read_save_0001[index*5+2],1);
    Spi_SyncTransmit(2);

    Spi_SetupEB(3,data,&Read_save_0001[index*5+3],1);
    Spi_SyncTransmit(3);

    Spi_SetupEB(3,&Writer_save_0001_blank,&Read_save_0001[index*5+3],1);
    Spi_SyncTransmit(3);

    Spi_SetupEB(4,data,&Read_save_0001[index*5+4],1);
    Spi_SyncTransmit(4);

    Spi_SetupEB(4,&Writer_save_0001_blank,(uint8 *)&Read_save_0001[index*5+4],1);
    Spi_SyncTransmit(4);

}


void cdd_9945_0001_sub2(uint32_t* data, int index)
{
    uint32_t Writer_save_0001_blank = 0xFFFFFFFE;

    Spi_SetupEB(0,data, &Read_save_0001[index*5+0],1);
    Spi_SyncTransmit(0);

    Spi_SetupEB(0,&Writer_save_0001_blank, &Read_save_0001[index*5+0],1);
    Spi_SyncTransmit(0);

    Spi_SetupEB(1,data, Read_save_0001[index*5+1],1);
    Spi_SyncTransmit(1);

    Spi_SetupEB(1,&Writer_save_0001_blank,&Read_save_0001[index*5+1],1);
    Spi_SyncTransmit(1);

    Spi_SetupEB(2,data,&Read_save_0001[index*5+2],1);
    Spi_SyncTransmit(2);

    Spi_SetupEB(2,&Writer_save_0001_blank,&Read_save_0001[index*5+2],1);
    Spi_SyncTransmit(2);

    Spi_SetupEB(3,&Writer_save_0001_blank,&Read_save_0001[index*5+3],1);
    Spi_SyncTransmit(3);

    Spi_SetupEB(4,data,&Read_save_0001[index*5+4],1);
    Spi_SyncTransmit(4);

    Spi_SetupEB(4,&Writer_save_0001_blank,&Read_save_0001[index*5+4],1);
    Spi_SyncTransmit(4);
}

void cdd_9945_0001_write(void)
{
    int timecount = 0;
    int index = 0;

    for(index=0;index<14;index++)
    {
        switch(index)
        {
            case 0:
                Writer_save_0001 = 0x6000000;
                break;
            case 1:
                Writer_save_0001 = 0x14650146;
                break;
            case 2:
                Writer_save_0001 = 0x24650143;
                break;
            case 3:
                Writer_save_0001 = 0x33650143;
                break;
            case 4:
                Writer_save_0001 = 0x416501C2;
                break;
            case 5:
                Writer_save_0001 = 0x54A78147;
                break;
            case 6:
                Writer_save_0001 = 0x64A78147;
                break;
            case 7:
                Writer_save_0001 = 0x72A501C2;
                break;
            case 8:
                Writer_save_0001 = 0x84A501C2;
                break;
            case 9:
                Writer_save_0001 = 0x9AAA0000;
                break;
            case 10:
                Writer_save_0001 = 0xAAAAAAAC;
                break;
            case 11:
                Writer_save_0001 = 0xBAAAAAAB;
                break;
            case 12:
                Writer_save_0001 = 0xCAAAAAAA;
                break;
            case 13:
                Writer_save_0001 = 0xDAAAAAAB;
                break;
            default:
                break;
        }
        cdd_9945_0001_sub(Writer_save_0001,index);
    }
    return;
}
void cdd_9945_0002(void)
{
    CDD_9945_EN_ReturnType RetVal;
    RetVal = CDD_9945_LLD_Init();
}




// ---------- 9945 -------------------

void cdd_9945_test_0001(void)
{
    CDD_9945_EN_ReturnType RetVal;
    RetVal = CDD_9945_LLD_Init();
}

// ---------- 9945-1 -------------------
// // void cdd_9945_test_0101(void)
// // {
// //     IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF_01,0XC40000,0x2000);
// // }

// // void cdd_9945_test_0102(void)
// // {
// //     IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF_01,1000,0x2000);
// // }    

// // void cdd_9945_test_0103(void)
// // {
// //      if(count_cddtime == 50)
// //      {
// //      	count_cddtime = 0;
// //          if(flg == 0)
// //          {
// //              flg = 1;
// //              IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,0);
// //          }
// //          else
// //          {
// //              flg = 0;
// //              IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,1);
// //          }
// //      }  
// // }

void cdd_9945_test_0104(void)
{
	uint32 index = 0;
    if(flag_9945_PH == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS_01,0);
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL1);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL1);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL1);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        flag_9945_PH = 1;
    }
}

void cdd_9945_test_0105(void)
{
    str_CDD_9945_Peak_Hold_Para PeakHoldPara = {0};
    CDD_9945_PH_ReturnType ret;
    PeakHoldPara.PeakHold_PeakTime = 200;
    PeakHoldPara.PeakHold_WinTime = 200;
    PeakHoldPara.PeakHold_PullinTime = 100;
    PeakHoldPara.PeakHold_HoldTime = 1600;
    PeakHoldPara.PeakHold_HoldDc = 8192;
    PeakHoldPara.PeakHold_HoldPer = 2000;
    PeakHoldPara.PeakHold_PullInDc = 4096;
    PeakHoldPara.PeakHold_PullInPer = 2000;
    ret = CDD_9945_PeakHoldParaSet(CDD_9945_PEAKHOLD_CHANNEL1,PeakHoldPara);
//    uint32 index = 0;
//    if(flag_9945_PH == 0)
//    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS_01,0);
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL1);
//        for(index = 0;index < 10000000; index++)
//        {
//            ;
//        }
//        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL1);
//        for(index = 0;index < 10000000; index++)
//        {
//            ;
//        }
//        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL1);
//        for(index = 0;index < 10000000; index++)
//        {
//            ;
//        }
//        flag_9945_PH = 1;
//    }
}

void cdd_9945_test_0109(void)
{
    uint32 index = 0;
    if(flag_9945_PH == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS_02,0);
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL2);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL2);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL2);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        flag_9945_PH = 1;
    }
}

void cdd_9945_test_0110(void)
{    
    uint32 index = 0;
    if(flag_9945_PH == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS_02,1);
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL2);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL2);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL2);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        flag_9945_PH = 1;
    }

}

void cdd_9945_test_0111(void)
{
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;

    Writer_save_0001_blank = 0X06600060;

    Spi_SetupEB(0,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(0);
}

void cdd_9945_test_0112(void)
{
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;

    Writer_save_0001_blank = 0X06600000;

    Spi_SetupEB(0,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(0);
}

void cdd_9945_test_0113(void)
{
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;

    Writer_save_0001_blank = 0X06600060;

    Spi_SetupEB(0,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(0);
}

void cdd_9945_test_0114(void)
{
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;

    Writer_save_0001_blank = 0X06600000;

    Spi_SetupEB(0,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(0);
}

void cdd_9945_test_0115(void)
{
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF00,0XC40000,0x2000);
}

void cdd_9945_test_0116(void)
{
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF00,1000,0x2000);
}

void cdd_9945_test_0117(void)
{
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF05,0XC40000,0x2000);
}

void cdd_9945_test_0118(void)
{
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF05,1000,0x2000);
}

// ---------- 9945-1 end----------------


// ---------- 9945-2 -------------------

void cdd_9945_test_0201(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF03,1000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,0);
}

void cdd_9945_test_0202(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF03,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,0);
}

void cdd_9945_test_0203(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF03,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,1);
}


void cdd_9945_test_0204(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF03,0XC40000,0x2000);
    if(count_cddtime == 50)
    {
    	count_cddtime = 0;
        if(flg == 0)
        {
            flg = 1;
            IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,0);
        }
        else
        {
            flg = 0;
            IoHwAb_Dio_WriteChannel(O_D_UC_LSS03,1);
        }
    }
}

void cdd_9945_test_0205(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF04,1000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,0);
}

void cdd_9945_test_0206(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF04,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,0);
}

void cdd_9945_test_0207(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF04,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,1);
}


void cdd_9945_test_0208(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF04,0XC40000,0x2000);
    if(count_cddtime == 50)
    {
        count_cddtime = 0;
        if(flg == 0)
        {
            flg = 1;
            IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,0);
        }
        else
        {
            flg = 0;
            IoHwAb_Dio_WriteChannel(O_D_UC_LSS04,1);
        }
    }
}


void cdd_9945_test_0209(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF02,0XC40000,0x2000);
}

void cdd_9945_test_0210(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF02,1000,0x2000);
}


void cdd_9945_test_0211(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF07,0XC40000,0x2000);
}

void cdd_9945_test_0212(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF07,1000,0x2000);
}

void cdd_9945_test_0213(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;
    uint32_t Read_save_0001_blank;

    Read_save_0001_blank = 0XFFFFFFFE;
    Writer_save_0001_blank = 0X07800180;

    Spi_SetupEB(1,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(1);
}

void cdd_9945_test_0214(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;

    Writer_save_0001_blank = 0X07800000;

    Spi_SetupEB(1,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(1);
}

void cdd_9945_test_0215(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;

    Writer_save_0001_blank = 0X07800180;

    Spi_SetupEB(1,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(1);
}

void cdd_9945_test_0216(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;
 
    Writer_save_0001_blank = 0X07800000;

    Spi_SetupEB(1,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(1);
}

void cdd_9945_test_0295(void)
{
    str_CDD_9945_CCInfoType CC_Info;
    CDD_9945_ReadCC(CDD_9945_CHIP_2, &CC_Info);
}

void cdd_9945_test_0296(void)
{
    CDD_9945_UN_DataInfoType ReadDataInfo;
    CDD_9945_LLD_ReadData_ByCmdID(CDD_9945_CHIP_2,CDD_9945_COMMAND_2,&ReadDataInfo);
}

void cdd_9945_test_0297(void)
{
    CDD_9945_UN_DataInfoType WriterDataInfo;
    WriterDataInfo.Data = 0X24650146;
    WriterDataInfo.Command2_tag.N_P_CONFIG_02 = 0x0;
    WriterDataInfo.Command2_tag.OC_READ_02 = 0X0;
    WriterDataInfo.Command2_tag.LS_HS_CONFIG_02 = 0x0;
    CDD_9945_LLD_WriteData_ByCmdID(CDD_9945_CHIP_2,WriterDataInfo);
}

void cdd_9945_test_0298(void)
{
    char Diag_code[3] = {0};
    uint32_t Output_pin = 5;
    CDD_9945_ReadDiagCode(CDD_9945_CHIP_2,&Diag_code, Output_pin);
}

void cdd_9945_test_0299(void)
{
    CDD_9945_ResetSpi(CDD_9945_CHIP_2);
}

// ---------- 9945-2 end----------------


// ---------- 9945-3 -------------------
void cdd_9945_test_0301(void)
{
    uint32 index = 0;
    if(flag_9945_PH == 0)
	{
        CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS05,0);
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL3);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL3);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL3);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        flag_9945_PH = 1;
    }
}

void cdd_9945_test_0302(void)
{
    uint32 index = 0;
    if(flag_9945_PH == 0)
	{
        CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
        IoHwAb_Dio_WriteChannel(O_D_UC_LSS05,1);
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL3);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL3);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        CDD_9945_PeakHoldActive(CDD_9945_PEAKHOLD_CHANNEL3);
        for(index = 0;index < 10000000; index++)
        {
            ;
        }
        flag_9945_PH = 1;
    }
}

void cdd_9945_test_0303(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF01,0XC40000,0x2000);
}

void cdd_9945_test_0304(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF01,1000,0x2000);
}

void cdd_9945_test_0305(void)
{
    // CDD_9945_Dis_Enable(CDD_9945_CHIP_2);
    CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HSF04,0XC40000,0x2000);
    if(count_cddtime == 50)
    {
        count_cddtime = 0;
        if(flg == 0)
        {
            flg = 1;
            IoHwAb_Dio_WriteChannel(O_D_UC_LSS13,0);
        }
        else
        {
            flg = 0;
            IoHwAb_Dio_WriteChannel(O_D_UC_LSS13,1);
        }
    }
}

void cdd_9945_test_0306(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB2_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB2_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_DIR,1);   
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_HIZ,0);
}

void cdd_9945_test_0307(void)
{
    int timecount = 0;
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB2_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB2_PWM,3333333,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_DIR,1);   
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_HIZ,0);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_DIR,0); 
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
}

void cdd_9945_test_0308(void)
{
    int timecount = 0;
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB2_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB2_PWM,3333333,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_DIR,0);   
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_HIZ,0);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_DIR,1); 
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
}

void cdd_9945_test_0309(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB2_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_3);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB2_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_DIR,1);   
    IoHwAb_Dio_WriteChannel(O_D_UC_HB2_HIZ,1);
}
// ---------- 9945-3 end ---------------


// ---------- 9945-4 -------------------
// void cdd_9945_test_0401(void)
// {
//     IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB1_PWM,0XC40000,0x2000);
// }

// void cdd_9945_test_0402(void)
// {
//     IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB1_PWM,1000,0x2000);
// }

// void cdd_9945_test_0403(void)
// {
//     IoHwAb_Dio_WriteChannel(O_D_UC_HB1_DIR,0);
// }

// void cdd_9945_test_0404(void)
// {
//     IoHwAb_Dio_WriteChannel(O_D_UC_HB1_DIR,1);
// }

// void cdd_9945_test_0405(void)
// {
//     IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,0);
// }

// void cdd_9945_test_0406(void)
// {
//     IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,1);
// }

void cdd_9945_test_0407(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB1_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_DIR,1);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,0);
}

void cdd_9945_test_0408(void)
{
    int timecount = 0;
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB1_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_DIR,1);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,0);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_DIR,0);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
}

void cdd_9945_test_0409(void)
{
    int timecount = 0;
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB1_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_DIR,0);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,0);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_DIR,1);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
}

void cdd_9945_test_0410(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB1_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_DIR,1);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB1_HIZ,1);
}

// void cdd_9945_test_0411(void)
// {
//     IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB3_PWM,0XC40000,0x2000);
// }

// void cdd_9945_test_0412(void)
// {
//     IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB3_PWM,1000,0x2000);
// }

// void cdd_9945_test_0413(void)
// {
//     IoHwAb_Dio_WriteChannel(O_D_UC_HB3_DIR,1);
// }

// void cdd_9945_test_0414(void)
// {
//     IoHwAb_Dio_WriteChannel(O_D_UC_HB3_DIR,0);
// }

// void cdd_9945_test_0415(void)
// {
//     IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,1);
// }

// void cdd_9945_test_0416(void)
// {
//     IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,0);
// }

void cdd_9945_test_0417(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB3_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_DIR,1);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,0);
}

void cdd_9945_test_0418(void)
{
    int timecount = 0;
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB3_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_DIR,1);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,0);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_DIR,0);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
}

void cdd_9945_test_0419(void)
{
    int timecount = 0;
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB3_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_DIR,0);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,0);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_DIR,1);
    for(timecount = 0; timecount < 5000000; timecount++)
    {
        ;
    }
}

void cdd_9945_test_0420(void)
{
    int timecount = 0;
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_HB3_PWM,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_DIR,1);
    IoHwAb_Dio_WriteChannel(O_D_UC_HB3_HIZ,1);
}

// ---------- 9945-4 end-------------------

// ---------- 9945-5-------------------
void cdd_9945_test_0501(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF04,1000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,0); 
}

void cdd_9945_test_0502(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF04,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,0);
}

void cdd_9945_test_0503(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF04,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,1);
}

void cdd_9945_test_0504(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF04,0XC40000,0x2000);
    if(count_cddtime == 50)
    {
        count_cddtime = 0;
        if(flg == 0)
        {
            flg = 1;
            IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,0);
        }
        else
        {
            flg = 0;
            IoHwAb_Dio_WriteChannel(O_D_UC_HSS06,1);
        }
    }
}

void cdd_9945_test_0505(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF03,1000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,0);
}

void cdd_9945_test_0506(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF03,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,0);
}

void cdd_9945_test_0507(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF03,0XC40000,0x2000);
    IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,1);
}

void cdd_9945_test_0508(void)
{
    uint16_t delay_9945 = 0;
    if(flag_9945_test == 0)
    {
        IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,1);
        for(delay_9945 = 0; delay_9945 < 2000; delay_9945++)
        {
            ;
        }
        flag_9945_test = 1;
    }
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF03,0XC40000,0x2000);
    if(count_cddtime == 50)
    {
        count_cddtime = 0;
        if(flg == 0)
        {
            flg = 1;
            IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,0);
        }
        else
        {
            flg = 0;
            IoHwAb_Dio_WriteChannel(O_D_UC_HSS05,1);
        }
    }
}

void cdd_9945_test_0509(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    // IoHwAb_Dio_WriteChannel(O_D_UC_LSS07_EN,1);
    if(count_cddtime == 50)
    {
        count_cddtime = 0;
        if(flg == 0)
        {
            flg = 1;
            IoHwAb_Dio_WriteChannel(O_D_UC_HSS07,0);
        }
        else
        {
            flg = 0;
            IoHwAb_Dio_WriteChannel(O_D_UC_HSS07,1);
        }
    }
}

void cdd_9945_test_0510(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    // IoHwAb_Dio_WriteChannel(O_D_UC_LSS07_EN,1);
    if(count_cddtime == 50)
    {
        count_cddtime = 0;
        if(flg == 0)
        {
            flg = 1;
            IoHwAb_Dio_WriteChannel(O_D_UC_LSS07,0);
        }
        else
        {
            flg = 0;
            IoHwAb_Dio_WriteChannel(O_D_UC_LSS07,1);
        }
    }
}

void cdd_9945_test_0511(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    // IoHwAb_Dio_WriteChannel(O_D_UC_LSS07_EN,1);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF06,0XC40000,0x2000);
}

void cdd_9945_test_0512(void)
{
    
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    // IoHwAb_Dio_WriteChannel(O_D_UC_LSS07_EN,1);
    IoHwAb_PwmOut_SetPeriodAndDuty(O_F_UC_LSF06,1000,0x2000);
}

void cdd_9945_test_0513(void)
{
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;

    Writer_save_0001_blank = 0X07000100;

    // IoHwAb_Dio_WriteChannel(O_D_UC_LSS07_EN,1);
    Spi_SetupEB(4,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(4);
    return;
}

void cdd_9945_test_0514(void)
{
    uint32_t Writer_save_0001_blank;
    uint32_t Writer_save_0001_blank2;

    Writer_save_0001_blank = 0X07000001;
    CDD_9945_Dis_Enable(CDD_9945_CHIP_5);
    // IoHwAb_Dio_WriteChannel(O_D_UC_LSS07_EN,1);
    Spi_SetupEB(4,&Writer_save_0001_blank,&Writer_save_0001_blank2,1);
    Spi_SyncTransmit(4);
}
// ---------- 9945-5 end-------------------
