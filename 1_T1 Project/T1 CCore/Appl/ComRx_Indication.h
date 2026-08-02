/********************************************************************************
*
*  File name:   ComRx_Indication.h
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Std_Types.h"
#include "ComStack_Cfg.h"
#include "ComStack_Types.h"

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
/*********************************************************************************
*   Global Functions
*********************************************************************************/
extern boolean Com_RxIpduCallout_TSC1Mtr_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_EEC2HCU_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_CCVSHCU_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_TC1_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_TC1Handle_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_ETC1_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_ETC2_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_AMT3_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_HCUMCU_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_HCUMCU2_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_SC_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_TSC1Mtr2_D3_sO0(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_DCDC_Status1_VR82BV(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_DCDC_Status2_VR82BV(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_DCDC_Status3_VR82BV(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_HCUDCDC_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_HCUAPCU_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_HCUOPCU_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_HCU3_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_BMS5_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr );
extern boolean Com_RxIpduCallout_MCU2_OjcG_c(PduIdType PduId, const PduInfoType* PduInfoPtr );

extern void Com_RxIpduTimeout_TSC1Mtr_D3_sO0(void);
extern void Com_RxIpduTimeout_EEC2HCU_D3_sO0(void);
extern void Com_RxIpduTimeout_CCVSHCU_D3_sO0(void);
extern void Com_RxIpduTimeout_TC1_D3_sO0(void);
extern void Com_RxIpduTimeout_TC1Handle_D3_sO0(void);
extern void Com_RxIpduTimeout_ETC1_D3_sO0(void);
extern void Com_RxIpduTimeout_ETC2_D3_sO0(void);
extern void Com_RxIpduTimeout_AMT3_D3_sO0(void);
extern void Com_RxIpduTimeout_HCUMCU_D3_sO0(void);
extern void Com_RxIpduTimeout_HCUMCU2_D3_sO0(void);
extern void Com_RxIpduTimeout_SC_D3_sO0(void);
extern void Com_RxIpduTimeout_TSC1Mtr2_D3_sO0(void);
extern void Com_RxIpduTimeout_DCDC_Status1_VR82BV(void);
extern void Com_RxIpduTimeout_DCDC_Status2_VR82BV(void);
extern void Com_RxIpduTimeout_DCDC_Status3_VR82BV(void);
extern void Com_RxIpduTimeout_HCUDCDC_OjcG_c(void);
extern void Com_RxIpduTimeout_HCUAPCU_OjcG_c(void);
extern void Com_RxIpduTimeout_HCUOPCU_OjcG_c(void);
extern void Com_RxIpduTimeout_HCU3_OjcG_c(void);
extern void Com_RxIpduTimeout_BMS5_OjcG_c(void);
extern void Com_RxIpduTimeout_MCU2_OjcG_c(void);