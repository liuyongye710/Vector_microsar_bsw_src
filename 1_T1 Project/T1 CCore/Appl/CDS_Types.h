/********************************************************************************
*
*  File name:   CDS_Types.h
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Std_Types.h"
#include "CanIf.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Global  Macros
*********************************************************************************/
#define CDS_MSG_RX_CNT_MAX      CANIF_RXPDU_NUM
#define CDS_MSG_TX_CNT_MAX      CANIF_TXPDU_NUM

/*********************************************************************************
*   Local Struct
*********************************************************************************/
/* Receive Message Config Structure */
 typedef struct
 {
    uint16    SWI_EN_UW;       /* Message Status Enable Or Disable*/
    uint16    node_config;     /* Node ID Config */
    uint32    id_config;       /* ID Config */
    void      (*pFun)(uint8);
    uint8     *pRawErrorFlag;
    uint8     T_TOUT_ERR_UB;
    uint8     T_TOUT_OK_UB;
    uint8     T_CHKSUM_ERR_UB;
    uint8     T_CHKSUM_OK_UB;
    uint8     ERR_MASK_UB;
    uint16    T_PERIOD_UW;
    uint16    T_TICK_UW;
 } TypeRecvMsgCfg;

/* Send Message Config Structure */
 typedef struct
 {
    uint16    SWI_EN_UW;       /* Message Status Enable Or Disable*/
    uint16    node_config;     /* Node ID Config */
    uint32    id_config;       /* ID Config */
    void      (*pFun)(uint8);
    uint16    T_PERIOD_UW;
    uint16    T_TICK_UW;
 } TypeTranMsgCfg;
/*********************************************************************************
*   Global Variables
*********************************************************************************/

/*********************************************************************************
*   Local Variables
*********************************************************************************/

/*********************************************************************************
*   Global Functions
*********************************************************************************/