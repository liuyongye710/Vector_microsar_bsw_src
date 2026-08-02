/********************************************************************************
*
*  File name:   Nrd_Cfg.c
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Nrd_Cfg.h"
#include "Can.h"
#include "Com.h"


/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/

/*********************************************************************************
*   Local Variables
*********************************************************************************/
Nrd_RXCheckSumType CheckSumPar_RX[NRD_RX_MSG_NUM] = 
{
/*Node, EN, ID, LcBuffer, LcFailCnt, MsgLen, LCStart, LCErrThreshold, LCMaxCounter, CsStart, CsAlg, uw_TOCnt*/
/* 0*/{ Nrd_CAN2, 1, 0x0C002703, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* TSC1Mtr_D3_sO0      */
/* 1*/{ Nrd_CAN2, 1, 0x0CF00327, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* EEC2HCU_D3_sO0      */
/* 2*/{ Nrd_CAN2, 1, 0x18FEF127, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 1000 }, /* CCVSHCU_D3_sO0      */
/* 3*/{ Nrd_CAN2, 1, 0x0C010327, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* TC1_D3_sO0          */
/* 4*/{ Nrd_CAN2, 1, 0x0C010005, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* TC1Handle_D3_sO0    */
/* 5*/{ Nrd_CAN2, 1, 0x0CF00203, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* ETC1_D3_sO0         */
/* 6*/{ Nrd_CAN2, 1, 0x18F00503, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 1000 }, /* ETC2_D3_sO0         */
/* 7*/{ Nrd_CAN2, 1, 0x18FF6503, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 3000 }, /* AMT3_D3_sO0         */
/* 8*/{ Nrd_CAN2, 1, 0x0BFF0527, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* HCUMCU_D3_sO0       */
/* 9*/{ Nrd_CAN2, 1, 0x0BFF9327, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* HCUMCU2_D3_sO0      */
/*10*/{ Nrd_CAN2, 1, 0x18FF0227, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 1000 }, /* SC_D3_sO0           */
/*11*/{ Nrd_CAN2, 1, 0x0C002704, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* TSC1Mtr2_D3_sO0     */

/*12*/{ Nrd_CAN0, 1, 0x00000302, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* DCDC_Status1_VR82BV */
/*13*/{ Nrd_CAN0, 1, 0x00000303, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* DCDC_Status2_VR82BV */
/*14*/{ Nrd_CAN0, 1, 0x00000304, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* DCDC_Status3_VR82BV */

/*15*/{ Nrd_CAN4, 1, 0x18FF0727, NULL_PTR, NULL_PTR, 3, 0, 0, 0, 0, 0, 1000 }, /* HCUDCDC_OjcG_c      */
/*16*/{ Nrd_CAN4, 1, 0x18FF0827, NULL_PTR, NULL_PTR, 3, 0, 0, 0, 0, 0, 1000 }, /* HCUAPCU_OjcG_c      */
/*17*/{ Nrd_CAN4, 1, 0x18FF0627, NULL_PTR, NULL_PTR, 3, 0, 0, 0, 0, 0, 1000 }, /* HCUOPCU_OjcG_c      */
/*18*/{ Nrd_CAN4, 1, 0x18FF0F27, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 1000 }, /* HCU3_OjcG_c         */
/*19*/{ Nrd_CAN4, 1, 0x18FF3AF3, NULL_PTR, NULL_PTR, 8, 0, 0, 0, 0, 0, 500  }, /* BMS5_OjcG_c         */
/*20*/{ Nrd_CAN4, 1, 0x18FFDFEF, NULL_PTR, NULL_PTR, 3, 0, 0, 0, 0, 0, 1000 }, /* MCU2_OjcG_c         */
};


Nrd_TXCheckSumType CheckSumPar_TX[NRD_TX_MSG_NUM] = 
{
/*Node, EN, ID, LcFailCnt, MsgLen, LCStart, LCMaxCounter, CsStart, CsAlg*/
/* 0*/{ Nrd_CAN2, 1, 0x0CFFDEEF, NULL_PTR, 8, 0, 0, 0, 0 }, /* MCU1_D3_sO0        */
/* 1*/{ Nrd_CAN2, 1, 0xFFFFFFFF, NULL_PTR, 8, 0, 0, 0, 0 }, /* J1939Tp_ECMCU*******/
/* 2*/{ Nrd_CAN2, 1, 0x18FF3EEF, NULL_PTR, 8, 0, 0, 0, 0 }, /* MCU3_D3_sO0        */
/* 3*/{ Nrd_CAN2, 1, 0x0CFFDEF0, NULL_PTR, 8, 0, 0, 0, 0 }, /* MCU21_D3_sO0       */
/* 4*/{ Nrd_CAN2, 1, 0x18FFDFF0, NULL_PTR, 8, 0, 0, 0, 0 }, /* MCU22_D3_sO0       */
/* 5*/{ Nrd_CAN2, 1, 0x18FF3EF0, NULL_PTR, 8, 0, 0, 0, 0 }, /* MCU23_D3_sO0       */
/* 6*/{ Nrd_CAN2, 1, 0xFFFFFFFF, NULL_PTR, 8, 0, 0, 0, 0 }, /* J1939Tp_DM1MCU******/
/* 7*/{ Nrd_CAN2, 1, 0xFFFFFFFF, NULL_PTR, 8, 0, 0, 0, 0 }, /* J1939Tp_DM1MCU2*****/
/* 8*/{ Nrd_CAN2, 1, 0x18FFDFEF, NULL_PTR, 8, 0, 0, 0, 0 }, /* MCU2_D3_sO0        */

/* 9*/{ Nrd_CAN0, 1, 0x00000300, NULL_PTR, 8, 0, 0, 0, 0 }, /* DCDC_Cmd1_VR82BV   */

/*10*/{ Nrd_CAN4, 1, 0x18FFE830, NULL_PTR, 8, 0, 0, 0, 0 }, /* APCU1_OjcG_c         */
/*11*/{ Nrd_CAN4, 1, 0x18FFE930, NULL_PTR, 8, 0, 0, 0, 0 }, /* APCU2_OjcG_c         */
/*12*/{ Nrd_CAN4, 1, 0xFFFFFFFF, NULL_PTR, 8, 0, 0, 0, 0 }, /* J1939Tp_DM1APCU*******/
/*13*/{ Nrd_CAN4, 1, 0x18FFE31A, NULL_PTR, 8, 0, 0, 0, 0 }, /* DCDC1_OjcG_c         */
/*14*/{ Nrd_CAN4, 1, 0xFFFFFFFF, NULL_PTR, 8, 0, 0, 0, 0 }, /* J1939Tp_DM1DCDC*******/
/*15*/{ Nrd_CAN4, 1, 0xFFFFFFFF, NULL_PTR, 8, 0, 0, 0, 0 }, /* J1939Tp_DM1OPCU*******/
/*16*/{ Nrd_CAN4, 1, 0x18FFE02E, NULL_PTR, 8, 0, 0, 0, 0 }, /* OPCU1_OjcG_c         */
/*17*/{ Nrd_CAN4, 1, 0x18FFE12E, NULL_PTR, 8, 0, 0, 0, 0 }, /* OPCU2_OjcG_c         */
/*18*/{ Nrd_CAN4, 1, 0x18FFE760, NULL_PTR, 8, 0, 0, 0, 0 }, /* RelayState_OjcG_c    */
/*19*/{ Nrd_CAN4, 1, 0x18FFB460, NULL_PTR, 8, 0, 0, 0, 0 }, /* RelayState2_OjcG_c   */
/*20*/{ Nrd_CAN4, 1, 0x18FF0960, NULL_PTR, 8, 0, 0, 0, 0 }, /* IMCU1PTU_OjcG_c      */
/*21*/{ Nrd_CAN4, 1, 0x18FFED60, NULL_PTR, 8, 0, 0, 0, 0 }, /* MECU1Reserved_OjcG_c */
/*22*/{ Nrd_CAN4, 1, 0xFFFFFFFF, NULL_PTR, 8, 0, 0, 0, 0 }, /* J1939Tp_DM1PTU********/
};

Nrd_ComTimeoutId Rx_ComTimeoutId[NRD_RX_MSG_NUM] = 
{
/* 0*/{ Nrd_CAN2, COMCONF_COMSIGNAL_TSC1MTR_D3_SO0_OVRDCTRLMODETSC1MTR_TSC1MTR_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 1*/{ Nrd_CAN2, COMCONF_COMSIGNAL_EEC2HCU_D3_SO0_ACCRPEDLAPPOSN_EEC2HCU_EEC2HCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 2*/{ Nrd_CAN2, COMCONF_COMSIGNAL_CCVSHCU_D3_SO0_PRKGBRKSWTCCVSHCU_CCVSHCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 3*/{ Nrd_CAN2, COMCONF_COMSIGNAL_TC1_D3_SO0_TRSMREQEDGEARTC1_TC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 4*/{ Nrd_CAN2, COMCONF_COMSIGNAL_TC1HANDLE_D3_SO0_TRSMREQEDGEARTC1HANDLE_TC1HANDLE_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 5*/{ Nrd_CAN2, COMCONF_COMSIGNAL_ETC1_D3_SO0_SHIFTINPROCETC1_ETC1_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 6*/{ Nrd_CAN2, COMCONF_COMSIGNAL_ETC2_D3_SO0_SELEDGEARETC2_ETC2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 7*/{ Nrd_CAN2, COMCONF_COMSIGNAL_AMT3_D3_SO0_REQHCUTOCTRLTHEMOTAMT3_AMT3_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 8*/{ Nrd_CAN2, COMCONF_COMSIGNAL_HCUMCU_D3_SO0_THEREQEDMOTOPERATINGMODEHCUMCU_HCUMCU_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/* 9*/{ Nrd_CAN2, COMCONF_COMSIGNAL_HCUMCU2_D3_SO0_THEREQEDMOTOPERATINGMODEHCUMCU2_HCUMCU2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/*10*/{ Nrd_CAN2, COMCONF_COMSIGNAL_SC_D3_SO0_PTOSWTCMDSC_SC_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},
/*11*/{ Nrd_CAN2, COMCONF_COMSIGNAL_TSC1MTR2_D3_SO0_OVRDCTRLMODETSC1MTR2_TSC1MTR2_FAW_MCD_MCU_CAN_V1_4_1_DBC_RX},

/*12*/{ Nrd_CAN0, COMCONF_COMSIGNAL_DCDC_STATUS1_VR82BV_DCDC_VIN_DCDC_STATUS1_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX},
/*13*/{ Nrd_CAN0, COMCONF_COMSIGNAL_DCDC_STATUS2_VR82BV_DCDC_COUTLIMIT_DCDC_STATUS2_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX},
/*14*/{ Nrd_CAN0, COMCONF_COMSIGNAL_DCDC_STATUS3_VR82BV_DCDC_SOFTVER_DCDC_STATUS3_CAN_MATRIX_DCDC_V0_1_20250414_DBC_RX},

/*15*/{ Nrd_CAN4, COMCONF_COMSIGNAL_HCUDCDC_OJCG_C_DCDCOUTPUREQHCUDCDC_HCUDCDC_FAW3_HVAC_V2_0DBC_DBC_RX},
/*16*/{ Nrd_CAN4, COMCONF_COMSIGNAL_HCUAPCU_OJCG_C_AIRPUMPMOTWORKINGENAHCUAPCU_HCUAPCU_FAW3_HVAC_V2_0DBC_DBC_RX},
/*17*/{ Nrd_CAN4, COMCONF_COMSIGNAL_HCUOPCU_OJCG_C_OILPUMPMOTWORKINGENACMDHCUOPCU_HCUOPCU_FAW3_HVAC_V2_0DBC_DBC_RX},
/*18*/{ Nrd_CAN4, COMCONF_COMSIGNAL_HCU3_OJCG_C_MAINPOSHIGHURLYCTRLCMDHCU3_HCU3_FAW3_HVAC_V2_0DBC_DBC_RX},
/*19*/{ Nrd_CAN4, COMCONF_COMSIGNAL_BMS5_OJCG_C_DIRTCURCHRG1POSRLYCTRLCMDBMS5_BMS5_FAW3_HVAC_V2_0DBC_DBC_RX},
/*20*/{ Nrd_CAN4, COMCONF_COMSIGNAL_MCU2_OJCG_C_MOTCTRLLERBUSUMCU2_MCU2_FAW3_HVAC_V2_0DBC_DBC_RX},
};

uint8 Nrd_CanBusOff_Status[NRD_CAN_BUSOFF_CHANNEL_NUM] = {CANSM_T_NOT_BUS_OFF};
Nrd_s_RxCfgType Rx_Msg_Status[NRD_RX_MSG_NUM] = {0};
/*********************************************************************************
*   Global Functions
*********************************************************************************/

/*********************************************************************************
*   Local Functions
*********************************************************************************/
