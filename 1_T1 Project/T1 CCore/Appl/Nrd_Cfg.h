/********************************************************************************
*
*  File name:   Nrd_Cfg.h
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Nrd_Proj.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/
/*********************************************************************************
*   Global  Macros
*********************************************************************************/
#define Nrd_CAN0        0U
#define Nrd_CAN1        1U
#define Nrd_CAN2        2U
#define Nrd_CAN3        3U
#define Nrd_CAN4        4U

/*********************************************************************************
*   Local Struct
*********************************************************************************/
typedef struct
{
    boolean  b_MsgFlg;
    boolean  b_EnableFlg;
    boolean  b_RxFlg;
    boolean  b_AppRxFlg;
    boolean  b_MsgTOError;
    boolean  b_MsgLCError;
    boolean  b_MsgCSError;
}Nrd_s_RxCfgType;

typedef struct
{
    uint8    CHNindex;
    uint8    ub_Enable;
    uint32   id;
    uint8*   LcBuffer;
    uint8*   LcFailCnt;
    uint8    MsgLen;
    uint8    LCStart;
    uint8    LCErrThreshold;
    uint8    LCMaxCounter;
    uint8    CsStart; 
    uint8    CsAlg;
    uint16   uw_TOCnt;
}Nrd_RXCheckSumType;

typedef struct
{
    uint8    CHNindex;
    uint8    ub_Enable;
    uint32   id;
    uint8*   LcFailCnt;
    uint8    MsgLen;
    uint8    LCStart; 
    uint8    LCMaxCounter;
    uint8    CsStart; 
    uint8    CsAlg;
}Nrd_TXCheckSumType;

typedef struct
{
    uint8   CHNindex;
    uint16  uw_SignalId;
}Nrd_ComTimeoutId;
/*********************************************************************************
*   Global Variables
*********************************************************************************/
extern Nrd_RXCheckSumType CheckSumPar_RX[NRD_RX_MSG_NUM];
extern Nrd_TXCheckSumType CheckSumPar_TX[NRD_TX_MSG_NUM];
extern uint8 Nrd_CanBusOff_Status[NRD_CAN_BUSOFF_CHANNEL_NUM];
extern Nrd_s_RxCfgType Rx_Msg_Status[NRD_RX_MSG_NUM];
extern Nrd_ComTimeoutId Rx_ComTimeoutId[NRD_RX_MSG_NUM];
/*********************************************************************************
*   Local Variables
*********************************************************************************/

/*********************************************************************************
*   Global Functions
*********************************************************************************/
