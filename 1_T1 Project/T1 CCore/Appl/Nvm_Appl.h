/********************************************************************************
*
*  File name:   Nvm_Appl.h
*
*********************************************************************************/
/*********************************************************************************
*    Includes
*********************************************************************************/
#include "Std_Types.h"

/*********************************************************************************
*   Local  Macros
*********************************************************************************/

/*********************************************************************************
*   Global  Macros
*********************************************************************************/
#define DSM_NVM_DATA_LENGTH      (32768U)  /* 32k */
#define APP_NVM_DATA_LENGTH      (16384U)  /* 16k */
#define DATA_NVM_ONFLY_LENGTH    (1024U)   /* 1k  */

#define IS_RELEASED         1
#define NOT_RELEASED        0
#define SHUTDOWN_DELAY      (STD_OFF)

extern uint8 lv_power_down_enable;
/*********************************************************************************
*   Local Struct
*********************************************************************************/

/*********************************************************************************
*   Global Variables
*********************************************************************************/
extern const uint8 dsm_default_data[DSM_NVM_DATA_LENGTH];
extern const uint8 app_default_data[APP_NVM_DATA_LENGTH];
extern const uint8 data_onfly_default[DATA_NVM_ONFLY_LENGTH];

extern uint8 dsm_nvm_data[DSM_NVM_DATA_LENGTH];
extern uint8 app_nvm_data[APP_NVM_DATA_LENGTH];
extern uint8 data_nvm_onfly[DATA_NVM_ONFLY_LENGTH];
/*********************************************************************************
*   Local Variables
*********************************************************************************/

/*********************************************************************************
*   Global Functions
*********************************************************************************/
void Appl_RequestPowerDown(void);
uint8 Action_GetPowerDownPermission(void);
uint8 Appl_NvMonFlyRestoreRequest(void);
void debounceKeyStatusFilter(void);
void shutDownRequest(void);
