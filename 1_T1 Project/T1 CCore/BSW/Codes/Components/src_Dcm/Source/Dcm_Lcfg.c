/*
********************************************************************************
*
* File name: Dcm_Lcfg.c
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : TanLixiang/2018.11.14
* Change: Neusar
* Cause: New
********************************************************************************
* Version: 1.1
* Author/Date : TanLixiang/2019.05.13
* Change: Modify
* Cause:
*(1)Modify file structure.
********************************************************************************
* Version: 1.2
* Author/Date : Songqw/2019.09.02
* Change: Revert 10 service about the 82 subfunction
* Cause: bugfix
********************************************************************************
* Version: 1.3
* Author/Date : Songqw/2019.11.11
* Change: Add the address type to the Dcm_DslProtocol structure.
* Cause: update
********************************************************************************
* Version: 1.4
* Author/Date : Liuziyang/2019.11.21
* Change: The format of code and comment.
* Cause: Modify the code according to the coding specification.
********************************************************************************
* Version: 1.5
* Author/Date : songqingwei/2020.01.22
* Change: Modify the Dcm_22_2E_ServiceInfo struction.
* Cause: How to association with Nvm about the DID buffer point.
********************************************************************************
* Version: 3.0
* Author/Date: ZhuCY/2021.10.28
* Change: Modify header file.
* Cause: Optimization.
********************************************************************************
* Version: 3.1
* Author/Date: LQiao/2023.02.06
* Change: Add Struct. Add 38 service. 
* Cause: Optimization
********************************************************************************
*/
/*
********************************************************************************
*    Include
********************************************************************************
*/
#include "Dcm.h"
#include "Dem.h"
#include "CanIf.h"
#include "Dcm_Callback.h"

/*
********************************************************************************
*    Local Macros
********************************************************************************
*/
/*
********************************************************************************
*    Local Types
********************************************************************************
*/
/*
********************************************************************************
*    Local Variables
********************************************************************************
*/
/*
********************************************************************************
*    Local Constants
********************************************************************************
*/
/*
********************************************************************************
*    Local Functions
********************************************************************************
*/
/*
********************************************************************************
*    Global Variables
********************************************************************************
*/
#define DCM_START_SEC_VAR_INIT
#include "Dcm_MemMap.h"

VAR(uint8, DCM_VAR_INIT) Dcm_DslBufferRx[DCM_DSL_BUFFERLENRX] = {0U};

VAR(uint32, DCM_VAR_INIT) Dcm_ProgrammingLength = DCM_ZERO;

#if( STD_ON == DCM_SERVICE_11_ENABLED )
VAR(uint8, DCM_VAR_INIT) Dcm_11_NvMBuf[DCM_FOUR] = {DCM_ZERO};
#endif /* STD_ON == DCM_SERVICE_11_ENABLED */
 
VAR(Dcm_ReadBlockId_st, DCM_VAR_INIT) Dcm_ReadBlockId[DCM_READ_BLOCK_NUM + 1] =
{
    {DCM_INVALID_BLOCKID, DCM_E_NOT_OK, DCM_E_NOT_OK, NULL_PTR, NULL_PTR, 0}
};

 
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )

VAR(uint8, DCM_VAR_INIT) Dcm_Did0120Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0121Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0122Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0123Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0124Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0125Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0126Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0127Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0128Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0129Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did012ABuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did012BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did012CBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did012DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did012EBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did012FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0130Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0131Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0132Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0210Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0212Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0211Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0214Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0215Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0216Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0217Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0218Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0219Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did021ABuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did021BBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did021CBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did021DBuffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did021EBuffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did021FBuffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0220Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0221Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0222Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0223Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0224Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0225Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0226Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0213Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0133Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0134Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0135Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0136Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0137Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0138Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0139Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did013ABuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did013BBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did013CBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did013DBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did013EBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did013FBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0140Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0141Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0142Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0143Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0144Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0145Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0146Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0147Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0148Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0149Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did014ABuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did014BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did014CBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did014DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did014EBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did014FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0150Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0151Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0152Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0153Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0154Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0155Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0156Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0157Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0158Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0159Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did015ABuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did015BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did015CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did015DBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did015EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did015FBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0160Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0161Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0162Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0163Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0164Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0165Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0166Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0167Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0168Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0169Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did016ABuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did016BBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did016CBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did016DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did016EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did016FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0170Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0171Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0172Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0173Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0174Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0175Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0176Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0177Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0178Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0179Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did017ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did017BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did017CBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did017DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did017EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did017FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0180Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0181Buffer[90] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0182Buffer[90] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0185Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did018CBuffer[15] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did018DBuffer[15] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did018EBuffer[15] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did018FBuffer[15] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0190Buffer[15] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0191Buffer[15] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0192Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0193Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0194Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0195Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0196Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0197Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0198Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0199Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF120Buffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did019ABuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did019BBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did019CBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did019DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did019FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did019EBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A0Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A2Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A4Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A6Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A8Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01A9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01AABuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01ABBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01ACBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01ADBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01AEBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01AFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B0Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B2Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B3Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B4Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B5Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B6Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B7Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B8Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01B9Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01BABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01BBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01BCBuffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01BDBuffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01BEBuffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01BFBuffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C0Buffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C1Buffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C2Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C3Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C4Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C5Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C6Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C7Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01C9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01CABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01CBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01CCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01CDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01CEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01CFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D4Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D5Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D6Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D8Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01D9Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01DABuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01DBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01DCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01DDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01DEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E0Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01DFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E1Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E3Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E4Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E5Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E6Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E7Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01E9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01EABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01EBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01ECBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01EDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01EEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01EFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01F9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01FABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01FBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01FCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01FDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01FEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did01FFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0250Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0251Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0252Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0253Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0254Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0255Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0256Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0257Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0258Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0259Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did025ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did025BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did025CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did025DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did025EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did025FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0260Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0261Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0262Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0263Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0264Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0265Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0266Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0267Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0268Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0269Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did026ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did026BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did026CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did026DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did026EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did026FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0270Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0271Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0272Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0273Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0274Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0275Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0276Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0277Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0278Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0279Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did027ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did027BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did027CBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did027DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did027EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did027FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0280Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0281Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0282Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0283Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0284Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0285Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0286Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0287Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0288Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0289Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did028ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did028BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did028CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did028DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did028EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did028FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0290Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0291Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0292Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0293Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0294Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0295Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0296Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0297Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0298Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0299Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did029ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did029BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did029CBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did029DBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did029EBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did029FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A0Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A1Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02A9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02AABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02ABBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02ACBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02ADBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02AEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02AFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02B9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02BABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02BBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02BCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02BDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02BEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02BFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02C9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02CABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02CBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02CCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02CDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02CEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02CFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02D9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02DABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02DBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02DCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02DDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02DEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02DFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02E9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02EABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02EBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02ECBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02EDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02EEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02EFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02F9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02FABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02FBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02FCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02FDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02FEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did02FFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0300Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0301Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0302Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0303Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0304Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0305Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0306Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0307Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0308Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0309Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did030ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did030BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did030CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did030DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did030EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did030FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0310Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0311Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0312Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0313Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0314Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0315Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0316Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0317Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0318Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0319Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did031ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did031BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did031CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did031DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did031EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did031FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0320Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0321Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0322Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0323Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0324Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0325Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0326Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0327Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0328Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0329Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did032ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did032BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did032CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did032DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did032EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did032FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0330Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0331Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0332Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0333Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0334Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0335Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0336Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0337Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0338Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0339Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did033ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did033BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did033CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did033DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did033EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did033FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0340Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0341Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0342Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0343Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0344Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0345Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0346Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0347Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0348Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0349Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did034ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did034BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did034CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did034DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did034EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did034FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0350Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0351Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0352Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0353Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0354Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0355Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0356Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0357Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0358Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0359Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did035ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did035BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did035CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did035DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did035EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did035FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0360Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0361Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0362Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0363Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0364Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0365Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0366Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0367Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0368Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0369Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did036ABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did036BBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did036CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did036DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did036EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF187Buffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF15ABuffer[9] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF182Buffer[40] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF189Buffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF18ABuffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF190Buffer[17] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF192Buffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF193Buffer[8] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF195Buffer[13] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF197Buffer[22] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF1A5Buffer[22] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF1A6Buffer[17] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0201Buffer[48] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0202Buffer[16] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0203Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0204Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0205Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0206Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0207Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0208Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_Did0209Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF400Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF401Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF402Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF404Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF405Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF40BBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF40CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF40DBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF40FBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF410Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF411Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF41CBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF41EBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF41FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF420Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF421Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF423Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF42CBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF42DBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF42FBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF430Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF431Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF432Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF433Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF43CBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF43DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF43EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF43FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF440Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF441Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF442Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF444Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF445Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF446Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF449Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF44ABuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF44CBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF44DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF44EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF44FBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF450Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF459Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF45ABuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF45CBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF45DBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF45EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF460Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF461Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF462Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF463Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF464Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF465Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF466Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF467Buffer[3] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF468Buffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF469Buffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF46BBuffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF46CBuffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF46DBuffer[11] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF46EBuffer[9] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF46FBuffer[3] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF470Buffer[10] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF471Buffer[6] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF472Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF473Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF474Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF475Buffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF476Buffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF477Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF478Buffer[9] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF47ABuffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF47BBuffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF47CBuffer[9] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF47DBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF47EBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF47FBuffer[13] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF480Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF481Buffer[41] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF482Buffer[41] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF483Buffer[9] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF485Buffer[10] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF486Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF487Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF488Buffer[13] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF489Buffer[41] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF48BBuffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF48CBuffer[17] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF48EBuffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF48FBuffer[7] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF490Buffer[3] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF491Buffer[5] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF492Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF493Buffer[3] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF494Buffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF498Buffer[9] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF49DBuffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF49EBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF49FBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A0Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A6Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4A9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4AABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4ABBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4ACBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4ADBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4AEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4AFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4B8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4BFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4CFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4D9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DCBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4DFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E8Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E9Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EABuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EBBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4ECBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EDBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EEBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4EFBuffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F0Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F1Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F2Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F3Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F4Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F5Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F6Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4F7Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4FFBuffer[10] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4C0Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF4E0Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF800Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF802Buffer[17] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF804Buffer[16] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF806Buffer[4] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF80ABuffer[20] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF80BBuffer[36] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF80DBuffer[17] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF810Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF811Buffer[11] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF812Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF813Buffer[12] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF814Buffer[2] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF815Buffer[1] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF816Buffer[32] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF817Buffer[16] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF818Buffer[16] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF819Buffer[24] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF81ABuffer[24] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF81BBuffer[16] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF81CBuffer[24] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF81DBuffer[32] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_DidF15BBuffer[40] = {0x00U};
VAR(uint16, DCM_VAR_INIT) Dcm_22_DidList[DCM_22_MAX_DID_LIST_NUM] = {0};
VAR(uint16, DCM_VAR_INIT) Dcm_22_DidResLen[DCM_22_MAX_DID_LIST_NUM] = {0};
#endif

 
#if (STD_ON == DCM_SERVICE_27_ENABLED)
VAR(Dcm_27_Security_cfg, DCM_VAR_INIT) Dcm_27_Security_Data[DCM_27_SUB_NUM + 1U] = {{0x00U}, {0x00U}, {0x00U}, {0x00U}};
VAR(Dcm_27_Security_cfg, DCM_VAR_INIT) Dcm_27_Security_INIT_Data[DCM_27_SUB_NUM + 1U] = {{0x00U}, {0x00U}, {0x00U}, {0x00U}};
VAR(uint32, DCM_VAR_INIT) Dcm_27_TimerEngine[DCM_27_SUB_NUM + 1U] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_security_key[DCM_27_MAX_SEED_LENGTH + 1U] = {0x00U};
VAR(uint8, DCM_VAR_INIT) Dcm_security_seed[DCM_27_MAX_SEED_LENGTH + 1U] = {0x00U};
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */

#if( STD_ON == DCM_SERVICE_2C_ENABLED )
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
VAR(Dcm_86_NvMEventInfo_st, DCM_VAR_INIT) Dcm_86_NvMInfo = {DCM_ZERO};
#endif/* STD_ON == DCM_SERVICE_86_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)
VAR(uint8, DCM_VAR_INIT) Dcm_AuthenticationState[DCM_29_AUT_ROLE_NUM + 1U][DCM_29_AUT_CONN_NUM + 1U] = {{FALSE}};
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#define DCM_STOP_SEC_VAR_INIT
#include "Dcm_MemMap.h"

/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
#define DCM_START_SEC_CONFIG_DATA
#include "Dcm_MemMap.h"

 
CONST(Dcm_ServiceTableType_st, DCM_CONFIG_DATA) Dcm_DspServiceInfoTable[DCM_NUM_SERVICES + 1] =
{
	{0x10U,	DCM_SERVICE_UDS,	2U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_10_CheckRule,	Dcm_10_Process,	Dcm_10_Init,	Dcm_10_PostProcess},
	{0x11U,	DCM_SERVICE_UDS,	2U,	{0x0000000CU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_11_CheckRule,	Dcm_11_Process,	Dcm_11_Init,	Dcm_11_PostProcess},
	{0x27U,	DCM_SERVICE_UDS,	2U,	{0x0000000CU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY,	{0x0U, NULL_PTR},	Dcm_27_CheckRule,	Dcm_27_Process,	Dcm_27_Init,	Dcm_27_PostProcess},
	{0x28U,	DCM_SERVICE_UDS,	3U,	{0x0000000CU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_28_CheckRule,	Dcm_28_Process,	Dcm_28_Init,	Dcm_28_PostProcess},
	{0x3EU,	DCM_SERVICE_UDS,	2U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_3E_CheckRule,	Dcm_3E_Process,	Dcm_3E_Init,	Dcm_3E_PostProcess},
	{0x85U,	DCM_SERVICE_UDS,	2U,	{0x0000000CU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_85_CheckRule,	Dcm_85_Process,	Dcm_85_Init,	Dcm_85_PostProcess},
	{0x22U,	DCM_SERVICE_UDS,	3U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_22_CheckRule,	Dcm_22_Process,	Dcm_22_Init,	Dcm_22_PostProcess},
	{0x2EU,	DCM_SERVICE_UDS,	4U,	{0x0000000CU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY,	{0x0U, NULL_PTR},	Dcm_2E_CheckRule,	Dcm_2E_Process,	Dcm_2E_Init,	Dcm_2E_PostProcess},
	{0x14U,	DCM_SERVICE_UDS,	4U,	{0x0000000DU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_14_CheckRule,	Dcm_14_Process,	Dcm_14_Init,	Dcm_14_PostProcess},
	{0x19U,	DCM_SERVICE_UDS,	2U,	{0x0000000DU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY_FUN,	{0x0U, NULL_PTR},	Dcm_19_CheckRule,	Dcm_19_Process,	Dcm_19_Init,	Dcm_19_PostProcess},
	{0x2FU,	DCM_SERVICE_UDS,	4U,	{0x0000000CU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY,	{0x0U, NULL_PTR},	Dcm_2F_CheckRule,	Dcm_2F_Process,	Dcm_2F_Init,	Dcm_2F_PostProcess},
	{0x34U,	DCM_SERVICE_UDS,	5U,	{0x0000000EU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY,	{0x0U, NULL_PTR},	Dcm_34_CheckRule,	Dcm_34_Process,	Dcm_34_Init,	Dcm_34_PostProcess},
	{0x36U,	DCM_SERVICE_UDS,	2U,	{0x0000000EU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY,	{0x0U, NULL_PTR},	Dcm_36_CheckRule,	Dcm_36_Process,	Dcm_36_Init,	Dcm_36_PostProcess},
	{0x37U,	DCM_SERVICE_UDS,	1U,	{0x0000000EU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY,	{0x0U, NULL_PTR},	Dcm_37_CheckRule,	Dcm_37_Process,	Dcm_37_Init,	Dcm_37_PostProcess},
	{0x31U,	DCM_SERVICE_UDS,	4U,	{0x00000004U, 0x7FFFFFFFU},	0x0001U,	DCM_PHY,	{0x0U, NULL_PTR},	Dcm_31_CheckRule,	Dcm_31_Process,	Dcm_31_Init,	Dcm_31_PostProcess},
	{0x87U,	DCM_SERVICE_UDS,	2U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	0x0001U,	DCM_PHY,	{0x0U, NULL_PTR},	Dcm_87_CheckRule,	Dcm_87_Process,	Dcm_87_Init,	Dcm_87_PostProcess},
    {0xFFU, 0xFFU,              1U, {0x7FFFFFFFU, 0x7FFFFFFFU}, 0xFFFFU, 0xFFU,          {0x00U, NULL_PTR},	NULL_PTR,   NULL_PTR,       NULL_PTR,       NULL_PTR          }
};

CONST(Dcm_DSDInfo_st, DCM_CONFIG_DATA) Dcm_gcaDSDInfo =
{
    Dcm_DspServiceInfoTable
};

CONST(Dcm_DslBufferType, DCM_CONFIG_DATA) Dcm_DslBuffer[DCM_DSL_BUFFERNUM + 1] =
{
    {
        &Dcm_DslBufferRx[0U],
        DCM_DSL_BUFFERLENRX
    },
    {
        &Dcm_DslBufferRx[0U],
        DCM_DSL_BUFFERLENRX
    },
    {
        NULL_PTR,
        0xFFFFU
    }
};

 
CONST(Dcm_DslProtocol_st, DCM_CONFIG_DATA) Dcm_DslProtocol[DCM_DSL_PROTOCOL_NUM + 1] =
{
	{0U,	21U,	DCM_FUN,	DCM_UDS_ON_CAN,	0U,	0x1U,	0xFFFFU,	0x18DBEFF1U, FALSE, 0x2U},
	{1U,	21U,	DCM_PHY,	DCM_UDS_ON_CAN,	0U,	0x1U,	0xFFFFU,	0x18DAEFF1U, FALSE, 0x2U},
    {0xFFFFU, 0xFFFFU, 0xFFU, DCM_NO_ACTIVE_PROTOCOL, 0xFFU, 0x0U, 0xFFFFU, 0xFFFFFFFFU, FALSE, 0xFFU}
};

CONST(uint8, DCM_CONFIG_DATA) Dcm_CfgNetConnComMChannelMap[DCM_DSL_CHANNEL_NUM + 1] =
{
	0x02U,
    0xFFU
};

#if ( STD_ON == DCM_SERVICE_01_ENABLED )	
	
CONST(Dcm_01_PidType_st, DCM_CONFIG_DATA) Dcm_01_SupportPID[DCM_01_SUPPRORTPID + 1] =
{
	{0xFFU, 0x00U, NULL_PTR, NULL_PTR,},
};
	
CONST(Dcm_01_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_01_PIDInfo[DCM_01_SUBID + 1] =
{
	{0x00U, DCM_01_MRESQ, NULL_PTR, 0x00000000U},
	{0x20U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x40U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x60U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x80U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xA0U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xC0U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xE0U, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xFFU, DCM_01_NO_MRESQ, NULL_PTR, 0x00000000U},
};

CONST(Dcm_01_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_01_Dispatcher =
{
    Dcm_01_PIDInfo,
    Dcm_01_SupportPID,
};
#endif/* DCM_SERVICE_01_ENABLED */

#if ( STD_ON == DCM_SERVICE_02_ENABLED )
	
CONST(Dcm_02_PidType_st, DCM_CONFIG_DATA) Dcm_02_SupportPID[DCM_02_SUPPRORTPID + 1] =
{
	{0xFFU, 0x00U, NULL_PTR, NULL_PTR, 0U}
};
	
CONST(Dcm_02_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_02_PIDInfo[DCM_02_SUBID + 1] =
{
	{0x00U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x20U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x40U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x60U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x80U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xA0U, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xFFU, DCM_02_NO_MRESQ, NULL_PTR, 0x00000000U},
};

CONST(Dcm_02_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_02_Dispatcher =
{
    Dcm_02_PIDInfo,
    Dcm_02_SupportPID,
    Dcm_02_PidList

};
#endif /* STD_ON == DCM_SERVICE_02_ENABLED */

#if ( STD_ON == DCM_SERVICE_09_ENABLED )
	
CONST(Dcm_09_PidType_st, DCM_CONFIG_DATA) Dcm_09_SupportPID[DCM_09_SUPPRORTPID + 1] =
{
	{0xFFU, 0x00U, NULL_PTR, NULL_PTR},
};
	
CONST(Dcm_09_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_09_PIDInfo[DCM_09_SUBID + 1] =
{
	{0x00U, DCM_09_MRESQ, NULL_PTR, 0x00000000U},
	{0x20U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x40U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x60U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0x80U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xA0U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xC0U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xE0U, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
	{0xFFU, DCM_09_NO_MRESQ, NULL_PTR, 0x00000000U},
};

CONST(Dcm_09_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_09_Dispatcher =
{
    Dcm_09_PIDInfo,
    Dcm_09_SupportPID,
};
#endif /* STD_ON == DCM_SERVICE_09_ENABLED */

 
#if (STD_ON == DCM_SERVICE_10_ENABLED)
CONST(Dcm_10_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_10_ServiceInfo[DCM_10_SUBID + 1] =
{
	{0x01U,	DCM_PHY_FUN,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_01, DCM_P2EX_TIME_01},	DCM_NO_BOOT,	DCM_SESSION_DEFAULT_LEVEL,	NULL_PTR},
	{0x02U,	DCM_PHY,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_02, DCM_P2EX_TIME_02},	DCM_SYS_BOOT,	DCM_SESSION_PROG_LEVEL,	Dcm_Check10SubProgrammingFunc},
	{0x03U,	DCM_PHY_FUN,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_03, DCM_P2EX_TIME_03},	DCM_NO_BOOT,	DCM_SESSION_EXTEND_LEVEL,	Dcm_Check10SubextendedFunc},
	{0x04U,	DCM_PHY_FUN,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_04, DCM_P2EX_TIME_04},	DCM_NO_BOOT,	DCM_10_SESSION_04_LEVEL,	NULL_PTR},
	{0x81U,	DCM_PHY_FUN,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_01, DCM_P2EX_TIME_01},	DCM_NO_BOOT,	DCM_SESSION_DEFAULT_LEVEL,	NULL_PTR},
	{0x82U,	DCM_PHY,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_02, DCM_P2EX_TIME_02},	DCM_SYS_BOOT,	DCM_SESSION_PROG_LEVEL,	Dcm_Check10SubProgrammingFunc},
	{0x83U,	DCM_PHY_FUN,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_03, DCM_P2EX_TIME_03},	DCM_NO_BOOT,	DCM_SESSION_EXTEND_LEVEL,	Dcm_Check10SubextendedFunc},
	{0x84U,	DCM_PHY_FUN,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{DCM_P2_TIME_04, DCM_P2EX_TIME_04},	DCM_NO_BOOT,	DCM_10_SESSION_04_LEVEL,	NULL_PTR},
	{0xFFU,	DCM_PHY_FUN,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},   {0xFFU, 0xFFU},	DCM_NO_BOOT,	DCM_SESSION_DEFAULT_LEVEL,	NULL_PTR}
};
CONST(Dcm_10_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_10_Dispatcher =
{
	Dcm_10_ServiceInfo
};
#endif /* STD_ON == DCM_SERVICE_10_ENABLED */

 
#if (STD_ON == DCM_SERVICE_11_ENABLED)
CONST(Dcm_11_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_11_ServiceInfo[DCM_11_SUBID + 1] = 
{
	{0x01U,	DCM_PHY_FUN,	DCM_BEFORE_RESET,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check11SubResetFunc},
	{0x81U,	DCM_PHY_FUN,	DCM_BEFORE_RESET,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check11SubResetFunc},
	{0xFFU,	DCM_PHY_FUN,    DCM_BEFORE_RESET,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	NULL_PTR}
};
CONST(Dcm_11_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_11_Dispatcher =
{
	Dcm_11_ServiceInfo
};
#endif /* STD_ON == DCM_SERVICE_11_ENABLED */

 
#if (STD_ON == DCM_SERVICE_14_ENABLED)
CONST(Dcm_14_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_14_ServiceInfo[DCM_14_SUBID_NUM + 1] =
{
	{{0x7FFFFFFFU, 0x7FFFFFFFU},	Dcm_14_CheckRuleFunc,	Dcm_ClearCallBackFunc}
};
CONST(Dcm_g14DispatherInfo_st, DCM_CONFIG_DATA) Dcm_14_Dispatcher =
{
	Dcm_14_ServiceInfo,
};
#endif /* STD_ON == DCM_SERVICE_14_ENABLED */

 
#if (STD_ON == DCM_SERVICE_19_ENABLED)
CONST(Dcm_19_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_19_ServiceInfo[DCM_19_SUBIDNUM + 1] = 
{
	{0x01U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x01U,	Dcm_Dsp_1901_Process,	NULL_PTR},
	{0x02U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x01U,	Dcm_Dsp_1902_Process,	NULL_PTR},
	{0x03U,	DCM_PHY_FUN,	DCM_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x00U,	Dcm_Dsp_1903_Process,	NULL_PTR},
	{0x04U,	DCM_PHY_FUN,	DCM_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x04U,	Dcm_Dsp_1904_Process,	NULL_PTR},
	{0x06U,	DCM_PHY_FUN,	DCM_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x04U,	Dcm_Dsp_1906_Process,	NULL_PTR},
	{0x0AU,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x00U,	Dcm_Dsp_190A_Process,	NULL_PTR},
	{0x42U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x03U,	Dcm_Dsp_1942_Process,	NULL_PTR},
	{0x55U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x01U,	Dcm_Dsp_1955_Process,	NULL_PTR},
	{0x81U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x01U,	Dcm_Dsp_1901_Process,	NULL_PTR},
	{0x82U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x01U,	Dcm_Dsp_1902_Process,	NULL_PTR},
	{0x83U,	DCM_PHY_FUN,	DCM_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x00U,	Dcm_Dsp_1903_Process,	NULL_PTR},
	{0x84U,	DCM_PHY_FUN,	DCM_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x04U,	Dcm_Dsp_1904_Process,	NULL_PTR},
	{0x86U,	DCM_PHY_FUN,	DCM_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x04U,	Dcm_Dsp_1906_Process,	NULL_PTR},
	{0x8AU,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x00U,	Dcm_Dsp_190A_Process,	NULL_PTR},
	{0xC2U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x03U,	Dcm_Dsp_1942_Process,	NULL_PTR},
	{0xD5U,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,	{0x0000000DU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	0x01U,	Dcm_Dsp_1955_Process,	NULL_PTR},
	{0xFFU,	DCM_PHY_FUN,	DCM_NO_STOP_DTC,		{0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR},   0x00U,	NULL_PTR,	NULL_PTR},
};
CONST(Dcm_19_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_19_Dispatcher = 
{
	Dcm_19_ServiceInfo,
};
#endif /* STD_ON == DCM_SERVICE_19_ENABLED */

 
#if ( (STD_ON == DCM_SERVICE_22_ENABLED) || (STD_ON == DCM_SERVICE_2E_ENABLED) || (STD_ON == DCM_SERVICE_2A_ENABLED) || (STD_ON == DCM_SERVICE_2C_ENABLED) )
CONST(Dcm_22_2E_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_22_2E_ServiceInfo[DCM_NUM_DIDS + 1] =
{
	{0x0120U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0120Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0120_ReadData, NULL_PTR}, Dcm_DidMgr_0120_ReadDataLength, {Dcm_DidMgr_0120_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0121U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0121Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0121_ReadData, NULL_PTR}, Dcm_DidMgr_0121_ReadDataLength, {Dcm_DidMgr_0121_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0122U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0122Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0122_ReadData, NULL_PTR}, Dcm_DidMgr_0122_ReadDataLength, {Dcm_DidMgr_0122_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0123U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0123Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0123_ReadData, NULL_PTR}, Dcm_DidMgr_0123_ReadDataLength, {Dcm_DidMgr_0123_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0124U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0124Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0124_ReadData, NULL_PTR}, Dcm_DidMgr_0124_ReadDataLength, {Dcm_DidMgr_0124_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0125U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0125Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0125_ReadData, NULL_PTR}, Dcm_DidMgr_0125_ReadDataLength, {Dcm_DidMgr_0125_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0126U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0126Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0126_ReadData, NULL_PTR}, Dcm_DidMgr_0126_ReadDataLength, {Dcm_DidMgr_0126_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0127U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0127Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0127_ReadData, NULL_PTR}, Dcm_DidMgr_0127_ReadDataLength, {Dcm_DidMgr_0127_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0128U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0128Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0128_ReadData, NULL_PTR}, Dcm_DidMgr_0128_ReadDataLength, {Dcm_DidMgr_0128_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0129U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0129Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0129_ReadData, NULL_PTR}, Dcm_DidMgr_0129_ReadDataLength, {Dcm_DidMgr_0129_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x012AU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did012ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_012A_ReadData, NULL_PTR}, Dcm_DidMgr_012A_ReadDataLength, {Dcm_DidMgr_012A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x012BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did012BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_012B_ReadData, NULL_PTR}, Dcm_DidMgr_012B_ReadDataLength, {Dcm_DidMgr_012B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x012CU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did012CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_012C_ReadData, NULL_PTR}, Dcm_DidMgr_012C_ReadDataLength, {Dcm_DidMgr_012C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x012DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did012DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_012D_ReadData, NULL_PTR}, Dcm_DidMgr_012D_ReadDataLength, {Dcm_DidMgr_012D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x012EU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did012EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_012E_ReadData, NULL_PTR}, Dcm_DidMgr_012E_ReadDataLength, {Dcm_DidMgr_012E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x012FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did012FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_012F_ReadData, NULL_PTR}, Dcm_DidMgr_012F_ReadDataLength, {Dcm_DidMgr_012F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0130U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0130Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0130_ReadData, NULL_PTR}, Dcm_DidMgr_0130_ReadDataLength, {Dcm_DidMgr_0130_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0131U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0131Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0131_ReadData, NULL_PTR}, Dcm_DidMgr_0131_ReadDataLength, {Dcm_DidMgr_0131_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0132U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0132Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0132_ReadData, NULL_PTR}, Dcm_DidMgr_0132_ReadDataLength, {Dcm_DidMgr_0132_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0210U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0210Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0210_ReadData, NULL_PTR}, Dcm_DidMgr_0210_ReadDataLength, {Dcm_DidMgr_0210_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0210_WriteData, NULL_PTR}, Dcm_DidMgr_0210_ConditionCheckWrite, NULL_PTR},
	{0x0212U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0212Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0212_ReadData, NULL_PTR}, Dcm_DidMgr_0212_ReadDataLength, {Dcm_DidMgr_0212_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0211U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0211Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0211_ReadData, NULL_PTR}, Dcm_DidMgr_0211_ReadDataLength, {Dcm_DidMgr_0211_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0214U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0214Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0214_ReadData, NULL_PTR}, Dcm_DidMgr_0214_ReadDataLength, {Dcm_DidMgr_0214_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0215U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0215Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0215_ReadData, NULL_PTR}, Dcm_DidMgr_0215_ReadDataLength, {Dcm_DidMgr_0215_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0216U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0216Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0216_ReadData, NULL_PTR}, Dcm_DidMgr_0216_ReadDataLength, {Dcm_DidMgr_0216_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0217U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0217Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0217_ReadData, NULL_PTR}, Dcm_DidMgr_0217_ReadDataLength, {Dcm_DidMgr_0217_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0218U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0218Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0218_ReadData, NULL_PTR}, Dcm_DidMgr_0218_ReadDataLength, {Dcm_DidMgr_0218_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0219U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0219Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0219_ReadData, NULL_PTR}, Dcm_DidMgr_0219_ReadDataLength, {Dcm_DidMgr_0219_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x021AU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did021ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_021A_ReadData, NULL_PTR}, Dcm_DidMgr_021A_ReadDataLength, {Dcm_DidMgr_021A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x021BU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did021BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_021B_ReadData, NULL_PTR}, Dcm_DidMgr_021B_ReadDataLength, {Dcm_DidMgr_021B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x021CU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did021CBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_021C_ReadData, NULL_PTR}, Dcm_DidMgr_021C_ReadDataLength, {Dcm_DidMgr_021C_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_021C_WriteData, NULL_PTR}, Dcm_DidMgr_021C_ConditionCheckWrite, NULL_PTR},
	{0x021DU, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did021DBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_021D_ReadData, NULL_PTR}, Dcm_DidMgr_021D_ReadDataLength, {Dcm_DidMgr_021D_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_021D_WriteData, NULL_PTR}, Dcm_DidMgr_021D_ConditionCheckWrite, NULL_PTR},
	{0x021EU, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did021EBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_021E_ReadData, NULL_PTR}, Dcm_DidMgr_021E_ReadDataLength, {Dcm_DidMgr_021E_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_021E_WriteData, NULL_PTR}, Dcm_DidMgr_021E_ConditionCheckWrite, NULL_PTR},
	{0x021FU, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did021FBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_021F_ReadData, NULL_PTR}, Dcm_DidMgr_021F_ReadDataLength, {Dcm_DidMgr_021F_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_021F_WriteData, NULL_PTR}, Dcm_DidMgr_021F_ConditionCheckWrite, NULL_PTR},
	{0x0220U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0220Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0220_ReadData, NULL_PTR}, Dcm_DidMgr_0220_ReadDataLength, {Dcm_DidMgr_0220_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0220_WriteData, NULL_PTR}, Dcm_DidMgr_0220_ConditionCheckWrite, NULL_PTR},
	{0x0221U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0221Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0221_ReadData, NULL_PTR}, Dcm_DidMgr_0221_ReadDataLength, {Dcm_DidMgr_0221_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0221_WriteData, NULL_PTR}, Dcm_DidMgr_0221_ConditionCheckWrite, NULL_PTR},
	{0x0222U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0222Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0222_ReadData, NULL_PTR}, Dcm_DidMgr_0222_ReadDataLength, {Dcm_DidMgr_0222_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0222_WriteData, NULL_PTR}, Dcm_DidMgr_0222_ConditionCheckWrite, NULL_PTR},
	{0x0223U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0223Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0223_ReadData, NULL_PTR}, Dcm_DidMgr_0223_ReadDataLength, {Dcm_DidMgr_0223_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0223_WriteData, NULL_PTR}, Dcm_DidMgr_0223_ConditionCheckWrite, NULL_PTR},
	{0x0224U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0224Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0224_ReadData, NULL_PTR}, Dcm_DidMgr_0224_ReadDataLength, {Dcm_DidMgr_0224_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0224_WriteData, NULL_PTR}, Dcm_DidMgr_0224_ConditionCheckWrite, NULL_PTR},
	{0x0225U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0225Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0225_ReadData, NULL_PTR}, Dcm_DidMgr_0225_ReadDataLength, {Dcm_DidMgr_0225_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0225_WriteData, NULL_PTR}, Dcm_DidMgr_0225_ConditionCheckWrite, NULL_PTR},
	{0x0226U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0226Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0226_ReadData, NULL_PTR}, Dcm_DidMgr_0226_ReadDataLength, {Dcm_DidMgr_0226_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0226_WriteData, NULL_PTR}, Dcm_DidMgr_0226_ConditionCheckWrite, NULL_PTR},
	{0x0213U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0213Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0213_ReadData, NULL_PTR}, Dcm_DidMgr_0213_ReadDataLength, {Dcm_DidMgr_0213_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0133U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0133Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0133_ReadData, NULL_PTR}, Dcm_DidMgr_0133_ReadDataLength, {Dcm_DidMgr_0133_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0134U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0134Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0134_ReadData, NULL_PTR}, Dcm_DidMgr_0134_ReadDataLength, {Dcm_DidMgr_0134_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0135U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0135Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0135_ReadData, NULL_PTR}, Dcm_DidMgr_0135_ReadDataLength, {Dcm_DidMgr_0135_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0136U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0136Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0136_ReadData, NULL_PTR}, Dcm_DidMgr_0136_ReadDataLength, {Dcm_DidMgr_0136_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0137U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0137Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0137_ReadData, NULL_PTR}, Dcm_DidMgr_0137_ReadDataLength, {Dcm_DidMgr_0137_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0138U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0138Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0138_ReadData, NULL_PTR}, Dcm_DidMgr_0138_ReadDataLength, {Dcm_DidMgr_0138_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0139U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0139Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0139_ReadData, NULL_PTR}, Dcm_DidMgr_0139_ReadDataLength, {Dcm_DidMgr_0139_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x013AU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did013ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_013A_ReadData, NULL_PTR}, Dcm_DidMgr_013A_ReadDataLength, {Dcm_DidMgr_013A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x013BU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did013BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_013B_ReadData, NULL_PTR}, Dcm_DidMgr_013B_ReadDataLength, {Dcm_DidMgr_013B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x013CU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did013CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_013C_ReadData, NULL_PTR}, Dcm_DidMgr_013C_ReadDataLength, {Dcm_DidMgr_013C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x013DU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did013DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_013D_ReadData, NULL_PTR}, Dcm_DidMgr_013D_ReadDataLength, {Dcm_DidMgr_013D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x013EU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did013EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_013E_ReadData, NULL_PTR}, Dcm_DidMgr_013E_ReadDataLength, {Dcm_DidMgr_013E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x013FU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did013FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_013F_ReadData, NULL_PTR}, Dcm_DidMgr_013F_ReadDataLength, {Dcm_DidMgr_013F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0140U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0140Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0140_ReadData, NULL_PTR}, Dcm_DidMgr_0140_ReadDataLength, {Dcm_DidMgr_0140_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0141U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0141Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0141_ReadData, NULL_PTR}, Dcm_DidMgr_0141_ReadDataLength, {Dcm_DidMgr_0141_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0142U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0142Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0142_ReadData, NULL_PTR}, Dcm_DidMgr_0142_ReadDataLength, {Dcm_DidMgr_0142_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0143U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0143Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0143_ReadData, NULL_PTR}, Dcm_DidMgr_0143_ReadDataLength, {Dcm_DidMgr_0143_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0144U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0144Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0144_ReadData, NULL_PTR}, Dcm_DidMgr_0144_ReadDataLength, {Dcm_DidMgr_0144_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0145U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0145Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0145_ReadData, NULL_PTR}, Dcm_DidMgr_0145_ReadDataLength, {Dcm_DidMgr_0145_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0146U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0146Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0146_ReadData, NULL_PTR}, Dcm_DidMgr_0146_ReadDataLength, {Dcm_DidMgr_0146_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0147U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0147Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0147_ReadData, NULL_PTR}, Dcm_DidMgr_0147_ReadDataLength, {Dcm_DidMgr_0147_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0148U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0148Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0148_ReadData, NULL_PTR}, Dcm_DidMgr_0148_ReadDataLength, {Dcm_DidMgr_0148_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0149U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0149Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0149_ReadData, NULL_PTR}, Dcm_DidMgr_0149_ReadDataLength, {Dcm_DidMgr_0149_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x014AU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did014ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_014A_ReadData, NULL_PTR}, Dcm_DidMgr_014A_ReadDataLength, {Dcm_DidMgr_014A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x014BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did014BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_014B_ReadData, NULL_PTR}, Dcm_DidMgr_014B_ReadDataLength, {Dcm_DidMgr_014B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x014CU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did014CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_014C_ReadData, NULL_PTR}, Dcm_DidMgr_014C_ReadDataLength, {Dcm_DidMgr_014C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x014DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did014DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_014D_ReadData, NULL_PTR}, Dcm_DidMgr_014D_ReadDataLength, {Dcm_DidMgr_014D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x014EU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did014EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_014E_ReadData, NULL_PTR}, Dcm_DidMgr_014E_ReadDataLength, {Dcm_DidMgr_014E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x014FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did014FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_014F_ReadData, NULL_PTR}, Dcm_DidMgr_014F_ReadDataLength, {Dcm_DidMgr_014F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0150U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0150Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0150_ReadData, NULL_PTR}, Dcm_DidMgr_0150_ReadDataLength, {Dcm_DidMgr_0150_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0151U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0151Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0151_ReadData, NULL_PTR}, Dcm_DidMgr_0151_ReadDataLength, {Dcm_DidMgr_0151_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0152U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0152Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0152_ReadData, NULL_PTR}, Dcm_DidMgr_0152_ReadDataLength, {Dcm_DidMgr_0152_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0153U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0153Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0153_ReadData, NULL_PTR}, Dcm_DidMgr_0153_ReadDataLength, {Dcm_DidMgr_0153_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0154U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0154Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0154_ReadData, NULL_PTR}, Dcm_DidMgr_0154_ReadDataLength, {Dcm_DidMgr_0154_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0155U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0155Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0155_ReadData, NULL_PTR}, Dcm_DidMgr_0155_ReadDataLength, {Dcm_DidMgr_0155_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0156U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0156Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0156_ReadData, NULL_PTR}, Dcm_DidMgr_0156_ReadDataLength, {Dcm_DidMgr_0156_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0157U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0157Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0157_ReadData, NULL_PTR}, Dcm_DidMgr_0157_ReadDataLength, {Dcm_DidMgr_0157_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0158U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0158Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0158_ReadData, NULL_PTR}, Dcm_DidMgr_0158_ReadDataLength, {Dcm_DidMgr_0158_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0159U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0159Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0159_ReadData, NULL_PTR}, Dcm_DidMgr_0159_ReadDataLength, {Dcm_DidMgr_0159_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x015AU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did015ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_015A_ReadData, NULL_PTR}, Dcm_DidMgr_015A_ReadDataLength, {Dcm_DidMgr_015A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x015BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did015BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_015B_ReadData, NULL_PTR}, Dcm_DidMgr_015B_ReadDataLength, {Dcm_DidMgr_015B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x015CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did015CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_015C_ReadData, NULL_PTR}, Dcm_DidMgr_015C_ReadDataLength, {Dcm_DidMgr_015C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x015DU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did015DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_015D_ReadData, NULL_PTR}, Dcm_DidMgr_015D_ReadDataLength, {Dcm_DidMgr_015D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x015EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did015EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_015E_ReadData, NULL_PTR}, Dcm_DidMgr_015E_ReadDataLength, {Dcm_DidMgr_015E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x015FU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did015FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_015F_ReadData, NULL_PTR}, Dcm_DidMgr_015F_ReadDataLength, {Dcm_DidMgr_015F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0160U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0160Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0160_ReadData, NULL_PTR}, Dcm_DidMgr_0160_ReadDataLength, {Dcm_DidMgr_0160_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0161U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0161Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0161_ReadData, NULL_PTR}, Dcm_DidMgr_0161_ReadDataLength, {Dcm_DidMgr_0161_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0162U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0162Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0162_ReadData, NULL_PTR}, Dcm_DidMgr_0162_ReadDataLength, {Dcm_DidMgr_0162_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0163U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0163Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0163_ReadData, NULL_PTR}, Dcm_DidMgr_0163_ReadDataLength, {Dcm_DidMgr_0163_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0164U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0164Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0164_ReadData, NULL_PTR}, Dcm_DidMgr_0164_ReadDataLength, {Dcm_DidMgr_0164_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0165U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0165Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0165_ReadData, NULL_PTR}, Dcm_DidMgr_0165_ReadDataLength, {Dcm_DidMgr_0165_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0166U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0166Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0166_ReadData, NULL_PTR}, Dcm_DidMgr_0166_ReadDataLength, {Dcm_DidMgr_0166_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0167U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0167Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0167_ReadData, NULL_PTR}, Dcm_DidMgr_0167_ReadDataLength, {Dcm_DidMgr_0167_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0168U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0168Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0168_ReadData, NULL_PTR}, Dcm_DidMgr_0168_ReadDataLength, {Dcm_DidMgr_0168_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0169U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0169Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0169_ReadData, NULL_PTR}, Dcm_DidMgr_0169_ReadDataLength, {Dcm_DidMgr_0169_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x016AU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did016ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_016A_ReadData, NULL_PTR}, Dcm_DidMgr_016A_ReadDataLength, {Dcm_DidMgr_016A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x016BU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did016BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_016B_ReadData, NULL_PTR}, Dcm_DidMgr_016B_ReadDataLength, {Dcm_DidMgr_016B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x016CU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did016CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_016C_ReadData, NULL_PTR}, Dcm_DidMgr_016C_ReadDataLength, {Dcm_DidMgr_016C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x016DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did016DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_016D_ReadData, NULL_PTR}, Dcm_DidMgr_016D_ReadDataLength, {Dcm_DidMgr_016D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x016EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did016EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_016E_ReadData, NULL_PTR}, Dcm_DidMgr_016E_ReadDataLength, {Dcm_DidMgr_016E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x016FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did016FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_016F_ReadData, NULL_PTR}, Dcm_DidMgr_016F_ReadDataLength, {Dcm_DidMgr_016F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0170U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0170Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0170_ReadData, NULL_PTR}, Dcm_DidMgr_0170_ReadDataLength, {Dcm_DidMgr_0170_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0171U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0171Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0171_ReadData, NULL_PTR}, Dcm_DidMgr_0171_ReadDataLength, {Dcm_DidMgr_0171_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0172U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0172Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0172_ReadData, NULL_PTR}, Dcm_DidMgr_0172_ReadDataLength, {Dcm_DidMgr_0172_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0173U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0173Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0173_ReadData, NULL_PTR}, Dcm_DidMgr_0173_ReadDataLength, {Dcm_DidMgr_0173_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0174U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0174Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0174_ReadData, NULL_PTR}, Dcm_DidMgr_0174_ReadDataLength, {Dcm_DidMgr_0174_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0175U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0175Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0175_ReadData, NULL_PTR}, Dcm_DidMgr_0175_ReadDataLength, {Dcm_DidMgr_0175_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0176U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0176Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0176_ReadData, NULL_PTR}, Dcm_DidMgr_0176_ReadDataLength, {Dcm_DidMgr_0176_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0177U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0177Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0177_ReadData, NULL_PTR}, Dcm_DidMgr_0177_ReadDataLength, {Dcm_DidMgr_0177_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0178U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0178Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0178_ReadData, NULL_PTR}, Dcm_DidMgr_0178_ReadDataLength, {Dcm_DidMgr_0178_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0179U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0179Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0179_ReadData, NULL_PTR}, Dcm_DidMgr_0179_ReadDataLength, {Dcm_DidMgr_0179_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x017AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did017ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_017A_ReadData, NULL_PTR}, Dcm_DidMgr_017A_ReadDataLength, {Dcm_DidMgr_017A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x017BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did017BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_017B_ReadData, NULL_PTR}, Dcm_DidMgr_017B_ReadDataLength, {Dcm_DidMgr_017B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x017CU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did017CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_017C_ReadData, NULL_PTR}, Dcm_DidMgr_017C_ReadDataLength, {Dcm_DidMgr_017C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x017DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did017DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_017D_ReadData, NULL_PTR}, Dcm_DidMgr_017D_ReadDataLength, {Dcm_DidMgr_017D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x017EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did017EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_017E_ReadData, NULL_PTR}, Dcm_DidMgr_017E_ReadDataLength, {Dcm_DidMgr_017E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x017FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did017FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_017F_ReadData, NULL_PTR}, Dcm_DidMgr_017F_ReadDataLength, {Dcm_DidMgr_017F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0180U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0180Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0180_ReadData, NULL_PTR}, Dcm_DidMgr_0180_ReadDataLength, {Dcm_DidMgr_0180_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0181U, TRUE, 0x5AU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0181Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0181_ReadData, NULL_PTR}, Dcm_DidMgr_0181_ReadDataLength, {Dcm_DidMgr_0181_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0181_WriteData, NULL_PTR}, Dcm_DidMgr_0181_ConditionCheckWrite, NULL_PTR},
	{0x0182U, TRUE, 0x5AU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0182Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0182_ReadData, NULL_PTR}, Dcm_DidMgr_0182_ReadDataLength, {Dcm_DidMgr_0182_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0182_WriteData, NULL_PTR}, Dcm_DidMgr_0182_ConditionCheckWrite, NULL_PTR},
	{0x0185U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0185Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0185_ReadData, NULL_PTR}, Dcm_DidMgr_0185_ReadDataLength, {Dcm_DidMgr_0185_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x018CU, TRUE, 0x0FU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did018CBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_018C_ReadData, NULL_PTR}, Dcm_DidMgr_018C_ReadDataLength, {Dcm_DidMgr_018C_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_018C_WriteData, NULL_PTR}, Dcm_DidMgr_018C_ConditionCheckWrite, NULL_PTR},
	{0x018DU, TRUE, 0x0FU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did018DBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_018D_ReadData, NULL_PTR}, Dcm_DidMgr_018D_ReadDataLength, {Dcm_DidMgr_018D_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_018D_WriteData, NULL_PTR}, Dcm_DidMgr_018D_ConditionCheckWrite, NULL_PTR},
	{0x018EU, TRUE, 0x0FU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did018EBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_018E_ReadData, NULL_PTR}, Dcm_DidMgr_018E_ReadDataLength, {Dcm_DidMgr_018E_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_018E_WriteData, NULL_PTR}, Dcm_DidMgr_018E_ConditionCheckWrite, NULL_PTR},
	{0x018FU, TRUE, 0x0FU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did018FBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_018F_ReadData, NULL_PTR}, Dcm_DidMgr_018F_ReadDataLength, {Dcm_DidMgr_018F_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_018F_WriteData, NULL_PTR}, Dcm_DidMgr_018F_ConditionCheckWrite, NULL_PTR},
	{0x0190U, TRUE, 0x0FU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0190Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0190_ReadData, NULL_PTR}, Dcm_DidMgr_0190_ReadDataLength, {Dcm_DidMgr_0190_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0190_WriteData, NULL_PTR}, Dcm_DidMgr_0190_ConditionCheckWrite, NULL_PTR},
	{0x0191U, TRUE, 0x0FU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0191Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0191_ReadData, NULL_PTR}, Dcm_DidMgr_0191_ReadDataLength, {Dcm_DidMgr_0191_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0191_WriteData, NULL_PTR}, Dcm_DidMgr_0191_ConditionCheckWrite, NULL_PTR},
	{0x0192U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0192Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0192_ReadData, NULL_PTR}, Dcm_DidMgr_0192_ReadDataLength, {Dcm_DidMgr_0192_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0193U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0193Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0193_ReadData, NULL_PTR}, Dcm_DidMgr_0193_ReadDataLength, {Dcm_DidMgr_0193_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0194U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0194Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0194_ReadData, NULL_PTR}, Dcm_DidMgr_0194_ReadDataLength, {Dcm_DidMgr_0194_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0194_WriteData, NULL_PTR}, Dcm_DidMgr_0194_ConditionCheckWrite, NULL_PTR},
	{0x0195U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0195Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0195_ReadData, NULL_PTR}, Dcm_DidMgr_0195_ReadDataLength, {Dcm_DidMgr_0195_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0195_WriteData, NULL_PTR}, Dcm_DidMgr_0195_ConditionCheckWrite, NULL_PTR},
	{0x0196U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0196Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0196_ReadData, NULL_PTR}, Dcm_DidMgr_0196_ReadDataLength, {Dcm_DidMgr_0196_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0196_WriteData, NULL_PTR}, Dcm_DidMgr_0196_ConditionCheckWrite, NULL_PTR},
	{0x0197U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0197Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0197_ReadData, NULL_PTR}, Dcm_DidMgr_0197_ReadDataLength, {Dcm_DidMgr_0197_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0197_WriteData, NULL_PTR}, Dcm_DidMgr_0197_ConditionCheckWrite, NULL_PTR},
	{0x0198U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0198Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0198_ReadData, NULL_PTR}, Dcm_DidMgr_0198_ReadDataLength, {Dcm_DidMgr_0198_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0198_WriteData, NULL_PTR}, Dcm_DidMgr_0198_ConditionCheckWrite, NULL_PTR},
	{0x0199U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0199Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0199_ReadData, NULL_PTR}, Dcm_DidMgr_0199_ReadDataLength, {Dcm_DidMgr_0199_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF120U, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF120Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F120_ReadData, NULL_PTR}, Dcm_DidMgr_F120_ReadDataLength, {Dcm_DidMgr_F120_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x019AU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did019ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_019A_ReadData, NULL_PTR}, Dcm_DidMgr_019A_ReadDataLength, {Dcm_DidMgr_019A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x019BU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did019BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_019B_ReadData, NULL_PTR}, Dcm_DidMgr_019B_ReadDataLength, {Dcm_DidMgr_019B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x019CU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did019CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_019C_ReadData, NULL_PTR}, Dcm_DidMgr_019C_ReadDataLength, {Dcm_DidMgr_019C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x019DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did019DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_019D_ReadData, NULL_PTR}, Dcm_DidMgr_019D_ReadDataLength, {Dcm_DidMgr_019D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x019FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did019FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_019F_ReadData, NULL_PTR}, Dcm_DidMgr_019F_ReadDataLength, {Dcm_DidMgr_019F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x019EU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did019EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_019E_ReadData, NULL_PTR}, Dcm_DidMgr_019E_ReadDataLength, {Dcm_DidMgr_019E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A0U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A0_ReadData, NULL_PTR}, Dcm_DidMgr_01A0_ReadDataLength, {Dcm_DidMgr_01A0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A1_ReadData, NULL_PTR}, Dcm_DidMgr_01A1_ReadDataLength, {Dcm_DidMgr_01A1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A2U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A2_ReadData, NULL_PTR}, Dcm_DidMgr_01A2_ReadDataLength, {Dcm_DidMgr_01A2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A3_ReadData, NULL_PTR}, Dcm_DidMgr_01A3_ReadDataLength, {Dcm_DidMgr_01A3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A4U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A4_ReadData, NULL_PTR}, Dcm_DidMgr_01A4_ReadDataLength, {Dcm_DidMgr_01A4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A5_ReadData, NULL_PTR}, Dcm_DidMgr_01A5_ReadDataLength, {Dcm_DidMgr_01A5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A6U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A6_ReadData, NULL_PTR}, Dcm_DidMgr_01A6_ReadDataLength, {Dcm_DidMgr_01A6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A7_ReadData, NULL_PTR}, Dcm_DidMgr_01A7_ReadDataLength, {Dcm_DidMgr_01A7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A8U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A8_ReadData, NULL_PTR}, Dcm_DidMgr_01A8_ReadDataLength, {Dcm_DidMgr_01A8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01A9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01A9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01A9_ReadData, NULL_PTR}, Dcm_DidMgr_01A9_ReadDataLength, {Dcm_DidMgr_01A9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01AAU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01AABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01AA_ReadData, NULL_PTR}, Dcm_DidMgr_01AA_ReadDataLength, {Dcm_DidMgr_01AA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01ABU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01ABBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01AB_ReadData, NULL_PTR}, Dcm_DidMgr_01AB_ReadDataLength, {Dcm_DidMgr_01AB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01ACU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01ACBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01AC_ReadData, NULL_PTR}, Dcm_DidMgr_01AC_ReadDataLength, {Dcm_DidMgr_01AC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01ADU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01ADBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01AD_ReadData, NULL_PTR}, Dcm_DidMgr_01AD_ReadDataLength, {Dcm_DidMgr_01AD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01AEU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01AEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01AE_ReadData, NULL_PTR}, Dcm_DidMgr_01AE_ReadDataLength, {Dcm_DidMgr_01AE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01AFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01AFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01AF_ReadData, NULL_PTR}, Dcm_DidMgr_01AF_ReadDataLength, {Dcm_DidMgr_01AF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B0U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B0_ReadData, NULL_PTR}, Dcm_DidMgr_01B0_ReadDataLength, {Dcm_DidMgr_01B0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B1_ReadData, NULL_PTR}, Dcm_DidMgr_01B1_ReadDataLength, {Dcm_DidMgr_01B1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B2U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B2_ReadData, NULL_PTR}, Dcm_DidMgr_01B2_ReadDataLength, {Dcm_DidMgr_01B2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B3U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B3_ReadData, NULL_PTR}, Dcm_DidMgr_01B3_ReadDataLength, {Dcm_DidMgr_01B3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B4U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B4_ReadData, NULL_PTR}, Dcm_DidMgr_01B4_ReadDataLength, {Dcm_DidMgr_01B4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B5U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B5_ReadData, NULL_PTR}, Dcm_DidMgr_01B5_ReadDataLength, {Dcm_DidMgr_01B5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B6U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B6_ReadData, NULL_PTR}, Dcm_DidMgr_01B6_ReadDataLength, {Dcm_DidMgr_01B6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B7U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B7_ReadData, NULL_PTR}, Dcm_DidMgr_01B7_ReadDataLength, {Dcm_DidMgr_01B7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B8U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B8_ReadData, NULL_PTR}, Dcm_DidMgr_01B8_ReadDataLength, {Dcm_DidMgr_01B8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01B9U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01B9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01B9_ReadData, NULL_PTR}, Dcm_DidMgr_01B9_ReadDataLength, {Dcm_DidMgr_01B9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01BAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01BABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01BA_ReadData, NULL_PTR}, Dcm_DidMgr_01BA_ReadDataLength, {Dcm_DidMgr_01BA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01BBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01BBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01BB_ReadData, NULL_PTR}, Dcm_DidMgr_01BB_ReadDataLength, {Dcm_DidMgr_01BB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01BCU, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01BCBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01BC_ReadData, NULL_PTR}, Dcm_DidMgr_01BC_ReadDataLength, {Dcm_DidMgr_01BC_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_01BC_WriteData, NULL_PTR}, Dcm_DidMgr_01BC_ConditionCheckWrite, NULL_PTR},
	{0x01BDU, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01BDBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01BD_ReadData, NULL_PTR}, Dcm_DidMgr_01BD_ReadDataLength, {Dcm_DidMgr_01BD_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_01BD_WriteData, NULL_PTR}, Dcm_DidMgr_01BD_ConditionCheckWrite, NULL_PTR},
	{0x01BEU, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01BEBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01BE_ReadData, NULL_PTR}, Dcm_DidMgr_01BE_ReadDataLength, {Dcm_DidMgr_01BE_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_01BE_WriteData, NULL_PTR}, Dcm_DidMgr_01BE_ConditionCheckWrite, NULL_PTR},
	{0x01BFU, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01BFBuffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01BF_ReadData, NULL_PTR}, Dcm_DidMgr_01BF_ReadDataLength, {Dcm_DidMgr_01BF_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_01BF_WriteData, NULL_PTR}, Dcm_DidMgr_01BF_ConditionCheckWrite, NULL_PTR},
	{0x01C0U, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C0Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C0_ReadData, NULL_PTR}, Dcm_DidMgr_01C0_ReadDataLength, {Dcm_DidMgr_01C0_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_01C0_WriteData, NULL_PTR}, Dcm_DidMgr_01C0_ConditionCheckWrite, NULL_PTR},
	{0x01C1U, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C1Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C1_ReadData, NULL_PTR}, Dcm_DidMgr_01C1_ReadDataLength, {Dcm_DidMgr_01C1_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_01C1_WriteData, NULL_PTR}, Dcm_DidMgr_01C1_ConditionCheckWrite, NULL_PTR},
	{0x01C2U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C2_ReadData, NULL_PTR}, Dcm_DidMgr_01C2_ReadDataLength, {Dcm_DidMgr_01C2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01C3U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C3_ReadData, NULL_PTR}, Dcm_DidMgr_01C3_ReadDataLength, {Dcm_DidMgr_01C3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01C4U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C4_ReadData, NULL_PTR}, Dcm_DidMgr_01C4_ReadDataLength, {Dcm_DidMgr_01C4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01C5U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C5_ReadData, NULL_PTR}, Dcm_DidMgr_01C5_ReadDataLength, {Dcm_DidMgr_01C5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01C6U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C6_ReadData, NULL_PTR}, Dcm_DidMgr_01C6_ReadDataLength, {Dcm_DidMgr_01C6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01C7U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C7_ReadData, NULL_PTR}, Dcm_DidMgr_01C7_ReadDataLength, {Dcm_DidMgr_01C7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01C8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C8_ReadData, NULL_PTR}, Dcm_DidMgr_01C8_ReadDataLength, {Dcm_DidMgr_01C8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01C9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01C9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01C9_ReadData, NULL_PTR}, Dcm_DidMgr_01C9_ReadDataLength, {Dcm_DidMgr_01C9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01CAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01CABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01CA_ReadData, NULL_PTR}, Dcm_DidMgr_01CA_ReadDataLength, {Dcm_DidMgr_01CA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01CBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01CBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01CB_ReadData, NULL_PTR}, Dcm_DidMgr_01CB_ReadDataLength, {Dcm_DidMgr_01CB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01CCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01CCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01CC_ReadData, NULL_PTR}, Dcm_DidMgr_01CC_ReadDataLength, {Dcm_DidMgr_01CC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01CDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01CDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01CD_ReadData, NULL_PTR}, Dcm_DidMgr_01CD_ReadDataLength, {Dcm_DidMgr_01CD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01CEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01CEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01CE_ReadData, NULL_PTR}, Dcm_DidMgr_01CE_ReadDataLength, {Dcm_DidMgr_01CE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01CFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01CFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01CF_ReadData, NULL_PTR}, Dcm_DidMgr_01CF_ReadDataLength, {Dcm_DidMgr_01CF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D0_ReadData, NULL_PTR}, Dcm_DidMgr_01D0_ReadDataLength, {Dcm_DidMgr_01D0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D1_ReadData, NULL_PTR}, Dcm_DidMgr_01D1_ReadDataLength, {Dcm_DidMgr_01D1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D2_ReadData, NULL_PTR}, Dcm_DidMgr_01D2_ReadDataLength, {Dcm_DidMgr_01D2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D3_ReadData, NULL_PTR}, Dcm_DidMgr_01D3_ReadDataLength, {Dcm_DidMgr_01D3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D4U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D4_ReadData, NULL_PTR}, Dcm_DidMgr_01D4_ReadDataLength, {Dcm_DidMgr_01D4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D5U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D5_ReadData, NULL_PTR}, Dcm_DidMgr_01D5_ReadDataLength, {Dcm_DidMgr_01D5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D6U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D6_ReadData, NULL_PTR}, Dcm_DidMgr_01D6_ReadDataLength, {Dcm_DidMgr_01D6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D7_ReadData, NULL_PTR}, Dcm_DidMgr_01D7_ReadDataLength, {Dcm_DidMgr_01D7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D8U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D8_ReadData, NULL_PTR}, Dcm_DidMgr_01D8_ReadDataLength, {Dcm_DidMgr_01D8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01D9U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01D9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01D9_ReadData, NULL_PTR}, Dcm_DidMgr_01D9_ReadDataLength, {Dcm_DidMgr_01D9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01DAU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01DABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01DA_ReadData, NULL_PTR}, Dcm_DidMgr_01DA_ReadDataLength, {Dcm_DidMgr_01DA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01DBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01DBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01DB_ReadData, NULL_PTR}, Dcm_DidMgr_01DB_ReadDataLength, {Dcm_DidMgr_01DB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01DCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01DCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01DC_ReadData, NULL_PTR}, Dcm_DidMgr_01DC_ReadDataLength, {Dcm_DidMgr_01DC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01DDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01DDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01DD_ReadData, NULL_PTR}, Dcm_DidMgr_01DD_ReadDataLength, {Dcm_DidMgr_01DD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01DEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01DEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01DE_ReadData, NULL_PTR}, Dcm_DidMgr_01DE_ReadDataLength, {Dcm_DidMgr_01DE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E0U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E0_ReadData, NULL_PTR}, Dcm_DidMgr_01E0_ReadDataLength, {Dcm_DidMgr_01E0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01DFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01DFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01DF_ReadData, NULL_PTR}, Dcm_DidMgr_01DF_ReadDataLength, {Dcm_DidMgr_01DF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E1U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E1_ReadData, NULL_PTR}, Dcm_DidMgr_01E1_ReadDataLength, {Dcm_DidMgr_01E1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E2_ReadData, NULL_PTR}, Dcm_DidMgr_01E2_ReadDataLength, {Dcm_DidMgr_01E2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E3U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E3_ReadData, NULL_PTR}, Dcm_DidMgr_01E3_ReadDataLength, {Dcm_DidMgr_01E3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E4U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E4_ReadData, NULL_PTR}, Dcm_DidMgr_01E4_ReadDataLength, {Dcm_DidMgr_01E4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E5U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E5_ReadData, NULL_PTR}, Dcm_DidMgr_01E5_ReadDataLength, {Dcm_DidMgr_01E5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E6U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E6_ReadData, NULL_PTR}, Dcm_DidMgr_01E6_ReadDataLength, {Dcm_DidMgr_01E6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E7U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E7_ReadData, NULL_PTR}, Dcm_DidMgr_01E7_ReadDataLength, {Dcm_DidMgr_01E7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E8_ReadData, NULL_PTR}, Dcm_DidMgr_01E8_ReadDataLength, {Dcm_DidMgr_01E8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01E9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01E9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01E9_ReadData, NULL_PTR}, Dcm_DidMgr_01E9_ReadDataLength, {Dcm_DidMgr_01E9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01EAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01EABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01EA_ReadData, NULL_PTR}, Dcm_DidMgr_01EA_ReadDataLength, {Dcm_DidMgr_01EA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01EBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01EBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01EB_ReadData, NULL_PTR}, Dcm_DidMgr_01EB_ReadDataLength, {Dcm_DidMgr_01EB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01ECU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01ECBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01EC_ReadData, NULL_PTR}, Dcm_DidMgr_01EC_ReadDataLength, {Dcm_DidMgr_01EC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01EDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01EDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01ED_ReadData, NULL_PTR}, Dcm_DidMgr_01ED_ReadDataLength, {Dcm_DidMgr_01ED_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01EEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01EEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01EE_ReadData, NULL_PTR}, Dcm_DidMgr_01EE_ReadDataLength, {Dcm_DidMgr_01EE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01EFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01EFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01EF_ReadData, NULL_PTR}, Dcm_DidMgr_01EF_ReadDataLength, {Dcm_DidMgr_01EF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F0_ReadData, NULL_PTR}, Dcm_DidMgr_01F0_ReadDataLength, {Dcm_DidMgr_01F0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F1_ReadData, NULL_PTR}, Dcm_DidMgr_01F1_ReadDataLength, {Dcm_DidMgr_01F1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F2_ReadData, NULL_PTR}, Dcm_DidMgr_01F2_ReadDataLength, {Dcm_DidMgr_01F2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F3_ReadData, NULL_PTR}, Dcm_DidMgr_01F3_ReadDataLength, {Dcm_DidMgr_01F3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F4_ReadData, NULL_PTR}, Dcm_DidMgr_01F4_ReadDataLength, {Dcm_DidMgr_01F4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F5_ReadData, NULL_PTR}, Dcm_DidMgr_01F5_ReadDataLength, {Dcm_DidMgr_01F5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F6_ReadData, NULL_PTR}, Dcm_DidMgr_01F6_ReadDataLength, {Dcm_DidMgr_01F6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F7_ReadData, NULL_PTR}, Dcm_DidMgr_01F7_ReadDataLength, {Dcm_DidMgr_01F7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F8_ReadData, NULL_PTR}, Dcm_DidMgr_01F8_ReadDataLength, {Dcm_DidMgr_01F8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01F9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01F9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01F9_ReadData, NULL_PTR}, Dcm_DidMgr_01F9_ReadDataLength, {Dcm_DidMgr_01F9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01FAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01FABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01FA_ReadData, NULL_PTR}, Dcm_DidMgr_01FA_ReadDataLength, {Dcm_DidMgr_01FA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01FBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01FBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01FB_ReadData, NULL_PTR}, Dcm_DidMgr_01FB_ReadDataLength, {Dcm_DidMgr_01FB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01FCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01FCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01FC_ReadData, NULL_PTR}, Dcm_DidMgr_01FC_ReadDataLength, {Dcm_DidMgr_01FC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01FDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01FDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01FD_ReadData, NULL_PTR}, Dcm_DidMgr_01FD_ReadDataLength, {Dcm_DidMgr_01FD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01FEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01FEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01FE_ReadData, NULL_PTR}, Dcm_DidMgr_01FE_ReadDataLength, {Dcm_DidMgr_01FE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x01FFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did01FFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_01FF_ReadData, NULL_PTR}, Dcm_DidMgr_01FF_ReadDataLength, {Dcm_DidMgr_01FF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0250U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0250Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0250_ReadData, NULL_PTR}, Dcm_DidMgr_0250_ReadDataLength, {Dcm_DidMgr_0250_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0251U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0251Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0251_ReadData, NULL_PTR}, Dcm_DidMgr_0251_ReadDataLength, {Dcm_DidMgr_0251_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0252U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0252Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0252_ReadData, NULL_PTR}, Dcm_DidMgr_0252_ReadDataLength, {Dcm_DidMgr_0252_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0253U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0253Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0253_ReadData, NULL_PTR}, Dcm_DidMgr_0253_ReadDataLength, {Dcm_DidMgr_0253_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0254U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0254Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0254_ReadData, NULL_PTR}, Dcm_DidMgr_0254_ReadDataLength, {Dcm_DidMgr_0254_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0255U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0255Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0255_ReadData, NULL_PTR}, Dcm_DidMgr_0255_ReadDataLength, {Dcm_DidMgr_0255_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0256U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0256Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0256_ReadData, NULL_PTR}, Dcm_DidMgr_0256_ReadDataLength, {Dcm_DidMgr_0256_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0257U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0257Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0257_ReadData, NULL_PTR}, Dcm_DidMgr_0257_ReadDataLength, {Dcm_DidMgr_0257_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0258U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0258Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0258_ReadData, NULL_PTR}, Dcm_DidMgr_0258_ReadDataLength, {Dcm_DidMgr_0258_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0259U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0259Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0259_ReadData, NULL_PTR}, Dcm_DidMgr_0259_ReadDataLength, {Dcm_DidMgr_0259_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x025AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did025ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_025A_ReadData, NULL_PTR}, Dcm_DidMgr_025A_ReadDataLength, {Dcm_DidMgr_025A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x025BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did025BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_025B_ReadData, NULL_PTR}, Dcm_DidMgr_025B_ReadDataLength, {Dcm_DidMgr_025B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x025CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did025CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_025C_ReadData, NULL_PTR}, Dcm_DidMgr_025C_ReadDataLength, {Dcm_DidMgr_025C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x025DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did025DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_025D_ReadData, NULL_PTR}, Dcm_DidMgr_025D_ReadDataLength, {Dcm_DidMgr_025D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x025EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did025EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_025E_ReadData, NULL_PTR}, Dcm_DidMgr_025E_ReadDataLength, {Dcm_DidMgr_025E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x025FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did025FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_025F_ReadData, NULL_PTR}, Dcm_DidMgr_025F_ReadDataLength, {Dcm_DidMgr_025F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0260U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0260Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0260_ReadData, NULL_PTR}, Dcm_DidMgr_0260_ReadDataLength, {Dcm_DidMgr_0260_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0261U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0261Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0261_ReadData, NULL_PTR}, Dcm_DidMgr_0261_ReadDataLength, {Dcm_DidMgr_0261_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0262U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0262Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0262_ReadData, NULL_PTR}, Dcm_DidMgr_0262_ReadDataLength, {Dcm_DidMgr_0262_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0263U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0263Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0263_ReadData, NULL_PTR}, Dcm_DidMgr_0263_ReadDataLength, {Dcm_DidMgr_0263_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0264U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0264Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0264_ReadData, NULL_PTR}, Dcm_DidMgr_0264_ReadDataLength, {Dcm_DidMgr_0264_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0265U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0265Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0265_ReadData, NULL_PTR}, Dcm_DidMgr_0265_ReadDataLength, {Dcm_DidMgr_0265_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0266U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0266Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0266_ReadData, NULL_PTR}, Dcm_DidMgr_0266_ReadDataLength, {Dcm_DidMgr_0266_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0267U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0267Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0267_ReadData, NULL_PTR}, Dcm_DidMgr_0267_ReadDataLength, {Dcm_DidMgr_0267_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0268U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0268Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0268_ReadData, NULL_PTR}, Dcm_DidMgr_0268_ReadDataLength, {Dcm_DidMgr_0268_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0269U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0269Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0269_ReadData, NULL_PTR}, Dcm_DidMgr_0269_ReadDataLength, {Dcm_DidMgr_0269_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x026AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did026ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_026A_ReadData, NULL_PTR}, Dcm_DidMgr_026A_ReadDataLength, {Dcm_DidMgr_026A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x026BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did026BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_026B_ReadData, NULL_PTR}, Dcm_DidMgr_026B_ReadDataLength, {Dcm_DidMgr_026B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x026CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did026CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_026C_ReadData, NULL_PTR}, Dcm_DidMgr_026C_ReadDataLength, {Dcm_DidMgr_026C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x026DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did026DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_026D_ReadData, NULL_PTR}, Dcm_DidMgr_026D_ReadDataLength, {Dcm_DidMgr_026D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x026EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did026EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_026E_ReadData, NULL_PTR}, Dcm_DidMgr_026E_ReadDataLength, {Dcm_DidMgr_026E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x026FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did026FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_026F_ReadData, NULL_PTR}, Dcm_DidMgr_026F_ReadDataLength, {Dcm_DidMgr_026F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0270U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0270Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0270_ReadData, NULL_PTR}, Dcm_DidMgr_0270_ReadDataLength, {Dcm_DidMgr_0270_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0271U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0271Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0271_ReadData, NULL_PTR}, Dcm_DidMgr_0271_ReadDataLength, {Dcm_DidMgr_0271_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0272U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0272Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0272_ReadData, NULL_PTR}, Dcm_DidMgr_0272_ReadDataLength, {Dcm_DidMgr_0272_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0273U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0273Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0273_ReadData, NULL_PTR}, Dcm_DidMgr_0273_ReadDataLength, {Dcm_DidMgr_0273_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0274U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0274Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0274_ReadData, NULL_PTR}, Dcm_DidMgr_0274_ReadDataLength, {Dcm_DidMgr_0274_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0275U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0275Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0275_ReadData, NULL_PTR}, Dcm_DidMgr_0275_ReadDataLength, {Dcm_DidMgr_0275_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0276U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0276Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0276_ReadData, NULL_PTR}, Dcm_DidMgr_0276_ReadDataLength, {Dcm_DidMgr_0276_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0277U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0277Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0277_ReadData, NULL_PTR}, Dcm_DidMgr_0277_ReadDataLength, {Dcm_DidMgr_0277_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0278U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0278Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0278_ReadData, NULL_PTR}, Dcm_DidMgr_0278_ReadDataLength, {Dcm_DidMgr_0278_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0279U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0279Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0279_ReadData, NULL_PTR}, Dcm_DidMgr_0279_ReadDataLength, {Dcm_DidMgr_0279_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x027AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did027ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_027A_ReadData, NULL_PTR}, Dcm_DidMgr_027A_ReadDataLength, {Dcm_DidMgr_027A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x027BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did027BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_027B_ReadData, NULL_PTR}, Dcm_DidMgr_027B_ReadDataLength, {Dcm_DidMgr_027B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x027CU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did027CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_027C_ReadData, NULL_PTR}, Dcm_DidMgr_027C_ReadDataLength, {Dcm_DidMgr_027C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x027DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did027DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_027D_ReadData, NULL_PTR}, Dcm_DidMgr_027D_ReadDataLength, {Dcm_DidMgr_027D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x027EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did027EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_027E_ReadData, NULL_PTR}, Dcm_DidMgr_027E_ReadDataLength, {Dcm_DidMgr_027E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x027FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did027FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_027F_ReadData, NULL_PTR}, Dcm_DidMgr_027F_ReadDataLength, {Dcm_DidMgr_027F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0280U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0280Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0280_ReadData, NULL_PTR}, Dcm_DidMgr_0280_ReadDataLength, {Dcm_DidMgr_0280_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0281U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0281Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0281_ReadData, NULL_PTR}, Dcm_DidMgr_0281_ReadDataLength, {Dcm_DidMgr_0281_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0282U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0282Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0282_ReadData, NULL_PTR}, Dcm_DidMgr_0282_ReadDataLength, {Dcm_DidMgr_0282_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0283U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0283Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0283_ReadData, NULL_PTR}, Dcm_DidMgr_0283_ReadDataLength, {Dcm_DidMgr_0283_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0284U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0284Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0284_ReadData, NULL_PTR}, Dcm_DidMgr_0284_ReadDataLength, {Dcm_DidMgr_0284_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0285U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0285Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0285_ReadData, NULL_PTR}, Dcm_DidMgr_0285_ReadDataLength, {Dcm_DidMgr_0285_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0286U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0286Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0286_ReadData, NULL_PTR}, Dcm_DidMgr_0286_ReadDataLength, {Dcm_DidMgr_0286_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0287U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0287Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0287_ReadData, NULL_PTR}, Dcm_DidMgr_0287_ReadDataLength, {Dcm_DidMgr_0287_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0288U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0288Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0288_ReadData, NULL_PTR}, Dcm_DidMgr_0288_ReadDataLength, {Dcm_DidMgr_0288_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0289U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0289Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0289_ReadData, NULL_PTR}, Dcm_DidMgr_0289_ReadDataLength, {Dcm_DidMgr_0289_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x028AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did028ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_028A_ReadData, NULL_PTR}, Dcm_DidMgr_028A_ReadDataLength, {Dcm_DidMgr_028A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x028BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did028BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_028B_ReadData, NULL_PTR}, Dcm_DidMgr_028B_ReadDataLength, {Dcm_DidMgr_028B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x028CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did028CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_028C_ReadData, NULL_PTR}, Dcm_DidMgr_028C_ReadDataLength, {Dcm_DidMgr_028C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x028DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did028DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_028D_ReadData, NULL_PTR}, Dcm_DidMgr_028D_ReadDataLength, {Dcm_DidMgr_028D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x028EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did028EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_028E_ReadData, NULL_PTR}, Dcm_DidMgr_028E_ReadDataLength, {Dcm_DidMgr_028E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x028FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did028FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_028F_ReadData, NULL_PTR}, Dcm_DidMgr_028F_ReadDataLength, {Dcm_DidMgr_028F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0290U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0290Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0290_ReadData, NULL_PTR}, Dcm_DidMgr_0290_ReadDataLength, {Dcm_DidMgr_0290_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0291U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0291Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0291_ReadData, NULL_PTR}, Dcm_DidMgr_0291_ReadDataLength, {Dcm_DidMgr_0291_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0292U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0292Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0292_ReadData, NULL_PTR}, Dcm_DidMgr_0292_ReadDataLength, {Dcm_DidMgr_0292_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0293U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0293Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0293_ReadData, NULL_PTR}, Dcm_DidMgr_0293_ReadDataLength, {Dcm_DidMgr_0293_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0294U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0294Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0294_ReadData, NULL_PTR}, Dcm_DidMgr_0294_ReadDataLength, {Dcm_DidMgr_0294_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0295U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0295Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0295_ReadData, NULL_PTR}, Dcm_DidMgr_0295_ReadDataLength, {Dcm_DidMgr_0295_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0296U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0296Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0296_ReadData, NULL_PTR}, Dcm_DidMgr_0296_ReadDataLength, {Dcm_DidMgr_0296_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0297U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0297Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0297_ReadData, NULL_PTR}, Dcm_DidMgr_0297_ReadDataLength, {Dcm_DidMgr_0297_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0298U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0298Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0298_ReadData, NULL_PTR}, Dcm_DidMgr_0298_ReadDataLength, {Dcm_DidMgr_0298_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0299U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0299Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0299_ReadData, NULL_PTR}, Dcm_DidMgr_0299_ReadDataLength, {Dcm_DidMgr_0299_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x029AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did029ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_029A_ReadData, NULL_PTR}, Dcm_DidMgr_029A_ReadDataLength, {Dcm_DidMgr_029A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x029BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did029BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_029B_ReadData, NULL_PTR}, Dcm_DidMgr_029B_ReadDataLength, {Dcm_DidMgr_029B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x029CU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did029CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_029C_ReadData, NULL_PTR}, Dcm_DidMgr_029C_ReadDataLength, {Dcm_DidMgr_029C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x029DU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did029DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_029D_ReadData, NULL_PTR}, Dcm_DidMgr_029D_ReadDataLength, {Dcm_DidMgr_029D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x029EU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did029EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_029E_ReadData, NULL_PTR}, Dcm_DidMgr_029E_ReadDataLength, {Dcm_DidMgr_029E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x029FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did029FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_029F_ReadData, NULL_PTR}, Dcm_DidMgr_029F_ReadDataLength, {Dcm_DidMgr_029F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A0U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A0_ReadData, NULL_PTR}, Dcm_DidMgr_02A0_ReadDataLength, {Dcm_DidMgr_02A0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A1U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A1_ReadData, NULL_PTR}, Dcm_DidMgr_02A1_ReadDataLength, {Dcm_DidMgr_02A1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A2_ReadData, NULL_PTR}, Dcm_DidMgr_02A2_ReadDataLength, {Dcm_DidMgr_02A2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A3_ReadData, NULL_PTR}, Dcm_DidMgr_02A3_ReadDataLength, {Dcm_DidMgr_02A3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A4_ReadData, NULL_PTR}, Dcm_DidMgr_02A4_ReadDataLength, {Dcm_DidMgr_02A4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A5_ReadData, NULL_PTR}, Dcm_DidMgr_02A5_ReadDataLength, {Dcm_DidMgr_02A5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A6_ReadData, NULL_PTR}, Dcm_DidMgr_02A6_ReadDataLength, {Dcm_DidMgr_02A6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A7_ReadData, NULL_PTR}, Dcm_DidMgr_02A7_ReadDataLength, {Dcm_DidMgr_02A7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A8_ReadData, NULL_PTR}, Dcm_DidMgr_02A8_ReadDataLength, {Dcm_DidMgr_02A8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02A9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02A9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02A9_ReadData, NULL_PTR}, Dcm_DidMgr_02A9_ReadDataLength, {Dcm_DidMgr_02A9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02AAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02AABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02AA_ReadData, NULL_PTR}, Dcm_DidMgr_02AA_ReadDataLength, {Dcm_DidMgr_02AA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02ABU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02ABBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02AB_ReadData, NULL_PTR}, Dcm_DidMgr_02AB_ReadDataLength, {Dcm_DidMgr_02AB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02ACU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02ACBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02AC_ReadData, NULL_PTR}, Dcm_DidMgr_02AC_ReadDataLength, {Dcm_DidMgr_02AC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02ADU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02ADBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02AD_ReadData, NULL_PTR}, Dcm_DidMgr_02AD_ReadDataLength, {Dcm_DidMgr_02AD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02AEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02AEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02AE_ReadData, NULL_PTR}, Dcm_DidMgr_02AE_ReadDataLength, {Dcm_DidMgr_02AE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02AFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02AFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02AF_ReadData, NULL_PTR}, Dcm_DidMgr_02AF_ReadDataLength, {Dcm_DidMgr_02AF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B0_ReadData, NULL_PTR}, Dcm_DidMgr_02B0_ReadDataLength, {Dcm_DidMgr_02B0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B1_ReadData, NULL_PTR}, Dcm_DidMgr_02B1_ReadDataLength, {Dcm_DidMgr_02B1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B2_ReadData, NULL_PTR}, Dcm_DidMgr_02B2_ReadDataLength, {Dcm_DidMgr_02B2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B3_ReadData, NULL_PTR}, Dcm_DidMgr_02B3_ReadDataLength, {Dcm_DidMgr_02B3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B4_ReadData, NULL_PTR}, Dcm_DidMgr_02B4_ReadDataLength, {Dcm_DidMgr_02B4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B5_ReadData, NULL_PTR}, Dcm_DidMgr_02B5_ReadDataLength, {Dcm_DidMgr_02B5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B6_ReadData, NULL_PTR}, Dcm_DidMgr_02B6_ReadDataLength, {Dcm_DidMgr_02B6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B7_ReadData, NULL_PTR}, Dcm_DidMgr_02B7_ReadDataLength, {Dcm_DidMgr_02B7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B8_ReadData, NULL_PTR}, Dcm_DidMgr_02B8_ReadDataLength, {Dcm_DidMgr_02B8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02B9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02B9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02B9_ReadData, NULL_PTR}, Dcm_DidMgr_02B9_ReadDataLength, {Dcm_DidMgr_02B9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02BAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02BABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02BA_ReadData, NULL_PTR}, Dcm_DidMgr_02BA_ReadDataLength, {Dcm_DidMgr_02BA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02BBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02BBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02BB_ReadData, NULL_PTR}, Dcm_DidMgr_02BB_ReadDataLength, {Dcm_DidMgr_02BB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02BCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02BCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02BC_ReadData, NULL_PTR}, Dcm_DidMgr_02BC_ReadDataLength, {Dcm_DidMgr_02BC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02BDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02BDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02BD_ReadData, NULL_PTR}, Dcm_DidMgr_02BD_ReadDataLength, {Dcm_DidMgr_02BD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02BEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02BEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02BE_ReadData, NULL_PTR}, Dcm_DidMgr_02BE_ReadDataLength, {Dcm_DidMgr_02BE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02BFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02BFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02BF_ReadData, NULL_PTR}, Dcm_DidMgr_02BF_ReadDataLength, {Dcm_DidMgr_02BF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C0_ReadData, NULL_PTR}, Dcm_DidMgr_02C0_ReadDataLength, {Dcm_DidMgr_02C0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C1_ReadData, NULL_PTR}, Dcm_DidMgr_02C1_ReadDataLength, {Dcm_DidMgr_02C1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C2_ReadData, NULL_PTR}, Dcm_DidMgr_02C2_ReadDataLength, {Dcm_DidMgr_02C2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C3_ReadData, NULL_PTR}, Dcm_DidMgr_02C3_ReadDataLength, {Dcm_DidMgr_02C3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C4_ReadData, NULL_PTR}, Dcm_DidMgr_02C4_ReadDataLength, {Dcm_DidMgr_02C4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C5_ReadData, NULL_PTR}, Dcm_DidMgr_02C5_ReadDataLength, {Dcm_DidMgr_02C5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C6_ReadData, NULL_PTR}, Dcm_DidMgr_02C6_ReadDataLength, {Dcm_DidMgr_02C6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C7_ReadData, NULL_PTR}, Dcm_DidMgr_02C7_ReadDataLength, {Dcm_DidMgr_02C7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C8_ReadData, NULL_PTR}, Dcm_DidMgr_02C8_ReadDataLength, {Dcm_DidMgr_02C8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02C9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02C9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02C9_ReadData, NULL_PTR}, Dcm_DidMgr_02C9_ReadDataLength, {Dcm_DidMgr_02C9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02CAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02CABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02CA_ReadData, NULL_PTR}, Dcm_DidMgr_02CA_ReadDataLength, {Dcm_DidMgr_02CA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02CBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02CBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02CB_ReadData, NULL_PTR}, Dcm_DidMgr_02CB_ReadDataLength, {Dcm_DidMgr_02CB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02CCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02CCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02CC_ReadData, NULL_PTR}, Dcm_DidMgr_02CC_ReadDataLength, {Dcm_DidMgr_02CC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02CDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02CDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02CD_ReadData, NULL_PTR}, Dcm_DidMgr_02CD_ReadDataLength, {Dcm_DidMgr_02CD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02CEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02CEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02CE_ReadData, NULL_PTR}, Dcm_DidMgr_02CE_ReadDataLength, {Dcm_DidMgr_02CE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02CFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02CFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02CF_ReadData, NULL_PTR}, Dcm_DidMgr_02CF_ReadDataLength, {Dcm_DidMgr_02CF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D0_ReadData, NULL_PTR}, Dcm_DidMgr_02D0_ReadDataLength, {Dcm_DidMgr_02D0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D1_ReadData, NULL_PTR}, Dcm_DidMgr_02D1_ReadDataLength, {Dcm_DidMgr_02D1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D2_ReadData, NULL_PTR}, Dcm_DidMgr_02D2_ReadDataLength, {Dcm_DidMgr_02D2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D3_ReadData, NULL_PTR}, Dcm_DidMgr_02D3_ReadDataLength, {Dcm_DidMgr_02D3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D4_ReadData, NULL_PTR}, Dcm_DidMgr_02D4_ReadDataLength, {Dcm_DidMgr_02D4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D5_ReadData, NULL_PTR}, Dcm_DidMgr_02D5_ReadDataLength, {Dcm_DidMgr_02D5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D6_ReadData, NULL_PTR}, Dcm_DidMgr_02D6_ReadDataLength, {Dcm_DidMgr_02D6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D7_ReadData, NULL_PTR}, Dcm_DidMgr_02D7_ReadDataLength, {Dcm_DidMgr_02D7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D8_ReadData, NULL_PTR}, Dcm_DidMgr_02D8_ReadDataLength, {Dcm_DidMgr_02D8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02D9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02D9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02D9_ReadData, NULL_PTR}, Dcm_DidMgr_02D9_ReadDataLength, {Dcm_DidMgr_02D9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02DAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02DABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02DA_ReadData, NULL_PTR}, Dcm_DidMgr_02DA_ReadDataLength, {Dcm_DidMgr_02DA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02DBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02DBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02DB_ReadData, NULL_PTR}, Dcm_DidMgr_02DB_ReadDataLength, {Dcm_DidMgr_02DB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02DCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02DCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02DC_ReadData, NULL_PTR}, Dcm_DidMgr_02DC_ReadDataLength, {Dcm_DidMgr_02DC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02DDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02DDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02DD_ReadData, NULL_PTR}, Dcm_DidMgr_02DD_ReadDataLength, {Dcm_DidMgr_02DD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02DEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02DEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02DE_ReadData, NULL_PTR}, Dcm_DidMgr_02DE_ReadDataLength, {Dcm_DidMgr_02DE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02DFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02DFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02DF_ReadData, NULL_PTR}, Dcm_DidMgr_02DF_ReadDataLength, {Dcm_DidMgr_02DF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E0_ReadData, NULL_PTR}, Dcm_DidMgr_02E0_ReadDataLength, {Dcm_DidMgr_02E0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E1_ReadData, NULL_PTR}, Dcm_DidMgr_02E1_ReadDataLength, {Dcm_DidMgr_02E1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E2_ReadData, NULL_PTR}, Dcm_DidMgr_02E2_ReadDataLength, {Dcm_DidMgr_02E2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E3_ReadData, NULL_PTR}, Dcm_DidMgr_02E3_ReadDataLength, {Dcm_DidMgr_02E3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E4_ReadData, NULL_PTR}, Dcm_DidMgr_02E4_ReadDataLength, {Dcm_DidMgr_02E4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E5_ReadData, NULL_PTR}, Dcm_DidMgr_02E5_ReadDataLength, {Dcm_DidMgr_02E5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E6_ReadData, NULL_PTR}, Dcm_DidMgr_02E6_ReadDataLength, {Dcm_DidMgr_02E6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E7_ReadData, NULL_PTR}, Dcm_DidMgr_02E7_ReadDataLength, {Dcm_DidMgr_02E7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E8_ReadData, NULL_PTR}, Dcm_DidMgr_02E8_ReadDataLength, {Dcm_DidMgr_02E8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02E9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02E9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02E9_ReadData, NULL_PTR}, Dcm_DidMgr_02E9_ReadDataLength, {Dcm_DidMgr_02E9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02EAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02EABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02EA_ReadData, NULL_PTR}, Dcm_DidMgr_02EA_ReadDataLength, {Dcm_DidMgr_02EA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02EBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02EBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02EB_ReadData, NULL_PTR}, Dcm_DidMgr_02EB_ReadDataLength, {Dcm_DidMgr_02EB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02ECU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02ECBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02EC_ReadData, NULL_PTR}, Dcm_DidMgr_02EC_ReadDataLength, {Dcm_DidMgr_02EC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02EDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02EDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02ED_ReadData, NULL_PTR}, Dcm_DidMgr_02ED_ReadDataLength, {Dcm_DidMgr_02ED_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02EEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02EEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02EE_ReadData, NULL_PTR}, Dcm_DidMgr_02EE_ReadDataLength, {Dcm_DidMgr_02EE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02EFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02EFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02EF_ReadData, NULL_PTR}, Dcm_DidMgr_02EF_ReadDataLength, {Dcm_DidMgr_02EF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F0_ReadData, NULL_PTR}, Dcm_DidMgr_02F0_ReadDataLength, {Dcm_DidMgr_02F0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F1_ReadData, NULL_PTR}, Dcm_DidMgr_02F1_ReadDataLength, {Dcm_DidMgr_02F1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F2_ReadData, NULL_PTR}, Dcm_DidMgr_02F2_ReadDataLength, {Dcm_DidMgr_02F2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F3_ReadData, NULL_PTR}, Dcm_DidMgr_02F3_ReadDataLength, {Dcm_DidMgr_02F3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F4_ReadData, NULL_PTR}, Dcm_DidMgr_02F4_ReadDataLength, {Dcm_DidMgr_02F4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F5_ReadData, NULL_PTR}, Dcm_DidMgr_02F5_ReadDataLength, {Dcm_DidMgr_02F5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F6_ReadData, NULL_PTR}, Dcm_DidMgr_02F6_ReadDataLength, {Dcm_DidMgr_02F6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F7_ReadData, NULL_PTR}, Dcm_DidMgr_02F7_ReadDataLength, {Dcm_DidMgr_02F7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F8_ReadData, NULL_PTR}, Dcm_DidMgr_02F8_ReadDataLength, {Dcm_DidMgr_02F8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02F9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02F9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02F9_ReadData, NULL_PTR}, Dcm_DidMgr_02F9_ReadDataLength, {Dcm_DidMgr_02F9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02FAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02FABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02FA_ReadData, NULL_PTR}, Dcm_DidMgr_02FA_ReadDataLength, {Dcm_DidMgr_02FA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02FBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02FBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02FB_ReadData, NULL_PTR}, Dcm_DidMgr_02FB_ReadDataLength, {Dcm_DidMgr_02FB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02FCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02FCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02FC_ReadData, NULL_PTR}, Dcm_DidMgr_02FC_ReadDataLength, {Dcm_DidMgr_02FC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02FDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02FDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02FD_ReadData, NULL_PTR}, Dcm_DidMgr_02FD_ReadDataLength, {Dcm_DidMgr_02FD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02FEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02FEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02FE_ReadData, NULL_PTR}, Dcm_DidMgr_02FE_ReadDataLength, {Dcm_DidMgr_02FE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x02FFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did02FFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_02FF_ReadData, NULL_PTR}, Dcm_DidMgr_02FF_ReadDataLength, {Dcm_DidMgr_02FF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0300U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0300Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0300_ReadData, NULL_PTR}, Dcm_DidMgr_0300_ReadDataLength, {Dcm_DidMgr_0300_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0301U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0301Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0301_ReadData, NULL_PTR}, Dcm_DidMgr_0301_ReadDataLength, {Dcm_DidMgr_0301_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0302U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0302Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0302_ReadData, NULL_PTR}, Dcm_DidMgr_0302_ReadDataLength, {Dcm_DidMgr_0302_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0303U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0303Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0303_ReadData, NULL_PTR}, Dcm_DidMgr_0303_ReadDataLength, {Dcm_DidMgr_0303_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0304U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0304Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0304_ReadData, NULL_PTR}, Dcm_DidMgr_0304_ReadDataLength, {Dcm_DidMgr_0304_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0305U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0305Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0305_ReadData, NULL_PTR}, Dcm_DidMgr_0305_ReadDataLength, {Dcm_DidMgr_0305_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0306U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0306Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0306_ReadData, NULL_PTR}, Dcm_DidMgr_0306_ReadDataLength, {Dcm_DidMgr_0306_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0307U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0307Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0307_ReadData, NULL_PTR}, Dcm_DidMgr_0307_ReadDataLength, {Dcm_DidMgr_0307_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0308U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0308Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0308_ReadData, NULL_PTR}, Dcm_DidMgr_0308_ReadDataLength, {Dcm_DidMgr_0308_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0309U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0309Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0309_ReadData, NULL_PTR}, Dcm_DidMgr_0309_ReadDataLength, {Dcm_DidMgr_0309_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x030AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did030ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_030A_ReadData, NULL_PTR}, Dcm_DidMgr_030A_ReadDataLength, {Dcm_DidMgr_030A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x030BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did030BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_030B_ReadData, NULL_PTR}, Dcm_DidMgr_030B_ReadDataLength, {Dcm_DidMgr_030B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x030CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did030CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_030C_ReadData, NULL_PTR}, Dcm_DidMgr_030C_ReadDataLength, {Dcm_DidMgr_030C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x030DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did030DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_030D_ReadData, NULL_PTR}, Dcm_DidMgr_030D_ReadDataLength, {Dcm_DidMgr_030D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x030EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did030EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_030E_ReadData, NULL_PTR}, Dcm_DidMgr_030E_ReadDataLength, {Dcm_DidMgr_030E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x030FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did030FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_030F_ReadData, NULL_PTR}, Dcm_DidMgr_030F_ReadDataLength, {Dcm_DidMgr_030F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0310U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0310Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0310_ReadData, NULL_PTR}, Dcm_DidMgr_0310_ReadDataLength, {Dcm_DidMgr_0310_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0311U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0311Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0311_ReadData, NULL_PTR}, Dcm_DidMgr_0311_ReadDataLength, {Dcm_DidMgr_0311_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0312U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0312Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0312_ReadData, NULL_PTR}, Dcm_DidMgr_0312_ReadDataLength, {Dcm_DidMgr_0312_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0313U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0313Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0313_ReadData, NULL_PTR}, Dcm_DidMgr_0313_ReadDataLength, {Dcm_DidMgr_0313_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0314U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0314Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0314_ReadData, NULL_PTR}, Dcm_DidMgr_0314_ReadDataLength, {Dcm_DidMgr_0314_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0315U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0315Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0315_ReadData, NULL_PTR}, Dcm_DidMgr_0315_ReadDataLength, {Dcm_DidMgr_0315_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0316U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0316Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0316_ReadData, NULL_PTR}, Dcm_DidMgr_0316_ReadDataLength, {Dcm_DidMgr_0316_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0317U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0317Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0317_ReadData, NULL_PTR}, Dcm_DidMgr_0317_ReadDataLength, {Dcm_DidMgr_0317_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0318U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0318Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0318_ReadData, NULL_PTR}, Dcm_DidMgr_0318_ReadDataLength, {Dcm_DidMgr_0318_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0319U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0319Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0319_ReadData, NULL_PTR}, Dcm_DidMgr_0319_ReadDataLength, {Dcm_DidMgr_0319_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x031AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did031ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_031A_ReadData, NULL_PTR}, Dcm_DidMgr_031A_ReadDataLength, {Dcm_DidMgr_031A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x031BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did031BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_031B_ReadData, NULL_PTR}, Dcm_DidMgr_031B_ReadDataLength, {Dcm_DidMgr_031B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x031CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did031CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_031C_ReadData, NULL_PTR}, Dcm_DidMgr_031C_ReadDataLength, {Dcm_DidMgr_031C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x031DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did031DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_031D_ReadData, NULL_PTR}, Dcm_DidMgr_031D_ReadDataLength, {Dcm_DidMgr_031D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x031EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did031EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_031E_ReadData, NULL_PTR}, Dcm_DidMgr_031E_ReadDataLength, {Dcm_DidMgr_031E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x031FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did031FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_031F_ReadData, NULL_PTR}, Dcm_DidMgr_031F_ReadDataLength, {Dcm_DidMgr_031F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0320U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0320Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0320_ReadData, NULL_PTR}, Dcm_DidMgr_0320_ReadDataLength, {Dcm_DidMgr_0320_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0321U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0321Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0321_ReadData, NULL_PTR}, Dcm_DidMgr_0321_ReadDataLength, {Dcm_DidMgr_0321_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0322U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0322Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0322_ReadData, NULL_PTR}, Dcm_DidMgr_0322_ReadDataLength, {Dcm_DidMgr_0322_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0323U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0323Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0323_ReadData, NULL_PTR}, Dcm_DidMgr_0323_ReadDataLength, {Dcm_DidMgr_0323_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0324U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0324Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0324_ReadData, NULL_PTR}, Dcm_DidMgr_0324_ReadDataLength, {Dcm_DidMgr_0324_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0325U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0325Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0325_ReadData, NULL_PTR}, Dcm_DidMgr_0325_ReadDataLength, {Dcm_DidMgr_0325_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0326U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0326Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0326_ReadData, NULL_PTR}, Dcm_DidMgr_0326_ReadDataLength, {Dcm_DidMgr_0326_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0327U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0327Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0327_ReadData, NULL_PTR}, Dcm_DidMgr_0327_ReadDataLength, {Dcm_DidMgr_0327_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0328U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0328Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0328_ReadData, NULL_PTR}, Dcm_DidMgr_0328_ReadDataLength, {Dcm_DidMgr_0328_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0329U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0329Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0329_ReadData, NULL_PTR}, Dcm_DidMgr_0329_ReadDataLength, {Dcm_DidMgr_0329_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x032AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did032ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_032A_ReadData, NULL_PTR}, Dcm_DidMgr_032A_ReadDataLength, {Dcm_DidMgr_032A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x032BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did032BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_032B_ReadData, NULL_PTR}, Dcm_DidMgr_032B_ReadDataLength, {Dcm_DidMgr_032B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x032CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did032CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_032C_ReadData, NULL_PTR}, Dcm_DidMgr_032C_ReadDataLength, {Dcm_DidMgr_032C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x032DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did032DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_032D_ReadData, NULL_PTR}, Dcm_DidMgr_032D_ReadDataLength, {Dcm_DidMgr_032D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x032EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did032EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_032E_ReadData, NULL_PTR}, Dcm_DidMgr_032E_ReadDataLength, {Dcm_DidMgr_032E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x032FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did032FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_032F_ReadData, NULL_PTR}, Dcm_DidMgr_032F_ReadDataLength, {Dcm_DidMgr_032F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0330U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0330Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0330_ReadData, NULL_PTR}, Dcm_DidMgr_0330_ReadDataLength, {Dcm_DidMgr_0330_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0331U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0331Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0331_ReadData, NULL_PTR}, Dcm_DidMgr_0331_ReadDataLength, {Dcm_DidMgr_0331_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0332U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0332Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0332_ReadData, NULL_PTR}, Dcm_DidMgr_0332_ReadDataLength, {Dcm_DidMgr_0332_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0333U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0333Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0333_ReadData, NULL_PTR}, Dcm_DidMgr_0333_ReadDataLength, {Dcm_DidMgr_0333_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0334U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0334Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0334_ReadData, NULL_PTR}, Dcm_DidMgr_0334_ReadDataLength, {Dcm_DidMgr_0334_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0335U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0335Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0335_ReadData, NULL_PTR}, Dcm_DidMgr_0335_ReadDataLength, {Dcm_DidMgr_0335_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0336U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0336Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0336_ReadData, NULL_PTR}, Dcm_DidMgr_0336_ReadDataLength, {Dcm_DidMgr_0336_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0337U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0337Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0337_ReadData, NULL_PTR}, Dcm_DidMgr_0337_ReadDataLength, {Dcm_DidMgr_0337_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0338U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0338Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0338_ReadData, NULL_PTR}, Dcm_DidMgr_0338_ReadDataLength, {Dcm_DidMgr_0338_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0339U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0339Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0339_ReadData, NULL_PTR}, Dcm_DidMgr_0339_ReadDataLength, {Dcm_DidMgr_0339_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x033AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did033ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_033A_ReadData, NULL_PTR}, Dcm_DidMgr_033A_ReadDataLength, {Dcm_DidMgr_033A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x033BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did033BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_033B_ReadData, NULL_PTR}, Dcm_DidMgr_033B_ReadDataLength, {Dcm_DidMgr_033B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x033CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did033CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_033C_ReadData, NULL_PTR}, Dcm_DidMgr_033C_ReadDataLength, {Dcm_DidMgr_033C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x033DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did033DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_033D_ReadData, NULL_PTR}, Dcm_DidMgr_033D_ReadDataLength, {Dcm_DidMgr_033D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x033EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did033EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_033E_ReadData, NULL_PTR}, Dcm_DidMgr_033E_ReadDataLength, {Dcm_DidMgr_033E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x033FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did033FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_033F_ReadData, NULL_PTR}, Dcm_DidMgr_033F_ReadDataLength, {Dcm_DidMgr_033F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0340U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0340Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0340_ReadData, NULL_PTR}, Dcm_DidMgr_0340_ReadDataLength, {Dcm_DidMgr_0340_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0341U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0341Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0341_ReadData, NULL_PTR}, Dcm_DidMgr_0341_ReadDataLength, {Dcm_DidMgr_0341_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0342U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0342Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0342_ReadData, NULL_PTR}, Dcm_DidMgr_0342_ReadDataLength, {Dcm_DidMgr_0342_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0343U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0343Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0343_ReadData, NULL_PTR}, Dcm_DidMgr_0343_ReadDataLength, {Dcm_DidMgr_0343_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0344U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0344Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0344_ReadData, NULL_PTR}, Dcm_DidMgr_0344_ReadDataLength, {Dcm_DidMgr_0344_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0345U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0345Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0345_ReadData, NULL_PTR}, Dcm_DidMgr_0345_ReadDataLength, {Dcm_DidMgr_0345_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0346U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0346Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0346_ReadData, NULL_PTR}, Dcm_DidMgr_0346_ReadDataLength, {Dcm_DidMgr_0346_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0347U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0347Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0347_ReadData, NULL_PTR}, Dcm_DidMgr_0347_ReadDataLength, {Dcm_DidMgr_0347_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0348U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0348Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0348_ReadData, NULL_PTR}, Dcm_DidMgr_0348_ReadDataLength, {Dcm_DidMgr_0348_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0349U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0349Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0349_ReadData, NULL_PTR}, Dcm_DidMgr_0349_ReadDataLength, {Dcm_DidMgr_0349_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x034AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did034ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_034A_ReadData, NULL_PTR}, Dcm_DidMgr_034A_ReadDataLength, {Dcm_DidMgr_034A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x034BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did034BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_034B_ReadData, NULL_PTR}, Dcm_DidMgr_034B_ReadDataLength, {Dcm_DidMgr_034B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x034CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did034CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_034C_ReadData, NULL_PTR}, Dcm_DidMgr_034C_ReadDataLength, {Dcm_DidMgr_034C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x034DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did034DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_034D_ReadData, NULL_PTR}, Dcm_DidMgr_034D_ReadDataLength, {Dcm_DidMgr_034D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x034EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did034EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_034E_ReadData, NULL_PTR}, Dcm_DidMgr_034E_ReadDataLength, {Dcm_DidMgr_034E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x034FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did034FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_034F_ReadData, NULL_PTR}, Dcm_DidMgr_034F_ReadDataLength, {Dcm_DidMgr_034F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0350U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0350Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0350_ReadData, NULL_PTR}, Dcm_DidMgr_0350_ReadDataLength, {Dcm_DidMgr_0350_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0351U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0351Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0351_ReadData, NULL_PTR}, Dcm_DidMgr_0351_ReadDataLength, {Dcm_DidMgr_0351_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0352U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0352Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0352_ReadData, NULL_PTR}, Dcm_DidMgr_0352_ReadDataLength, {Dcm_DidMgr_0352_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0353U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0353Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0353_ReadData, NULL_PTR}, Dcm_DidMgr_0353_ReadDataLength, {Dcm_DidMgr_0353_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0354U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0354Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0354_ReadData, NULL_PTR}, Dcm_DidMgr_0354_ReadDataLength, {Dcm_DidMgr_0354_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0355U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0355Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0355_ReadData, NULL_PTR}, Dcm_DidMgr_0355_ReadDataLength, {Dcm_DidMgr_0355_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0356U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0356Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0356_ReadData, NULL_PTR}, Dcm_DidMgr_0356_ReadDataLength, {Dcm_DidMgr_0356_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0357U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0357Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0357_ReadData, NULL_PTR}, Dcm_DidMgr_0357_ReadDataLength, {Dcm_DidMgr_0357_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0358U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0358Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0358_ReadData, NULL_PTR}, Dcm_DidMgr_0358_ReadDataLength, {Dcm_DidMgr_0358_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0359U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0359Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0359_ReadData, NULL_PTR}, Dcm_DidMgr_0359_ReadDataLength, {Dcm_DidMgr_0359_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x035AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did035ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_035A_ReadData, NULL_PTR}, Dcm_DidMgr_035A_ReadDataLength, {Dcm_DidMgr_035A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x035BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did035BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_035B_ReadData, NULL_PTR}, Dcm_DidMgr_035B_ReadDataLength, {Dcm_DidMgr_035B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x035CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did035CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_035C_ReadData, NULL_PTR}, Dcm_DidMgr_035C_ReadDataLength, {Dcm_DidMgr_035C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x035DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did035DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_035D_ReadData, NULL_PTR}, Dcm_DidMgr_035D_ReadDataLength, {Dcm_DidMgr_035D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x035EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did035EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_035E_ReadData, NULL_PTR}, Dcm_DidMgr_035E_ReadDataLength, {Dcm_DidMgr_035E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x035FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did035FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_035F_ReadData, NULL_PTR}, Dcm_DidMgr_035F_ReadDataLength, {Dcm_DidMgr_035F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0360U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0360Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0360_ReadData, NULL_PTR}, Dcm_DidMgr_0360_ReadDataLength, {Dcm_DidMgr_0360_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0361U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0361Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0361_ReadData, NULL_PTR}, Dcm_DidMgr_0361_ReadDataLength, {Dcm_DidMgr_0361_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0362U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0362Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0362_ReadData, NULL_PTR}, Dcm_DidMgr_0362_ReadDataLength, {Dcm_DidMgr_0362_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0363U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0363Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0363_ReadData, NULL_PTR}, Dcm_DidMgr_0363_ReadDataLength, {Dcm_DidMgr_0363_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0364U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0364Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0364_ReadData, NULL_PTR}, Dcm_DidMgr_0364_ReadDataLength, {Dcm_DidMgr_0364_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0365U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0365Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0365_ReadData, NULL_PTR}, Dcm_DidMgr_0365_ReadDataLength, {Dcm_DidMgr_0365_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0366U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0366Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0366_ReadData, NULL_PTR}, Dcm_DidMgr_0366_ReadDataLength, {Dcm_DidMgr_0366_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0367U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0367Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0367_ReadData, NULL_PTR}, Dcm_DidMgr_0367_ReadDataLength, {Dcm_DidMgr_0367_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0368U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0368Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0368_ReadData, NULL_PTR}, Dcm_DidMgr_0368_ReadDataLength, {Dcm_DidMgr_0368_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0369U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0369Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0369_ReadData, NULL_PTR}, Dcm_DidMgr_0369_ReadDataLength, {Dcm_DidMgr_0369_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x036AU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did036ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_036A_ReadData, NULL_PTR}, Dcm_DidMgr_036A_ReadDataLength, {Dcm_DidMgr_036A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x036BU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did036BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_036B_ReadData, NULL_PTR}, Dcm_DidMgr_036B_ReadDataLength, {Dcm_DidMgr_036B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x036CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did036CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_036C_ReadData, NULL_PTR}, Dcm_DidMgr_036C_ReadDataLength, {Dcm_DidMgr_036C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x036DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did036DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_036D_ReadData, NULL_PTR}, Dcm_DidMgr_036D_ReadDataLength, {Dcm_DidMgr_036D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x036EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did036EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_036E_ReadData, NULL_PTR}, Dcm_DidMgr_036E_ReadDataLength, {Dcm_DidMgr_036E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF187U, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF187Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F187_ReadData, NULL_PTR}, Dcm_DidMgr_F187_ReadDataLength, {Dcm_DidMgr_F187_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF15AU, TRUE, 0x09U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF15ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F15A_ReadData, NULL_PTR}, Dcm_DidMgr_F15A_ReadDataLength, {Dcm_DidMgr_F15A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF182U, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF182Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F182_ReadData, NULL_PTR}, Dcm_DidMgr_F182_ReadDataLength, {Dcm_DidMgr_F182_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF189U, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF189Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F189_ReadData, NULL_PTR}, Dcm_DidMgr_F189_ReadDataLength, {Dcm_DidMgr_F189_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF18AU, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF18ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F18A_ReadData, NULL_PTR}, Dcm_DidMgr_F18A_ReadDataLength, {Dcm_DidMgr_F18A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF190U, TRUE, 0x11U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF190Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F190_ReadData, NULL_PTR}, Dcm_DidMgr_F190_ReadDataLength, {Dcm_DidMgr_F190_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_F190_WriteData, NULL_PTR}, Dcm_DidMgr_F190_ConditionCheckWrite, NULL_PTR},
	{0xF192U, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF192Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F192_ReadData, NULL_PTR}, Dcm_DidMgr_F192_ReadDataLength, {Dcm_DidMgr_F192_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF193U, TRUE, 0x08U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF193Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F193_ReadData, NULL_PTR}, Dcm_DidMgr_F193_ReadDataLength, {Dcm_DidMgr_F193_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF195U, TRUE, 0x0DU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF195Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F195_ReadData, NULL_PTR}, Dcm_DidMgr_F195_ReadDataLength, {Dcm_DidMgr_F195_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF197U, TRUE, 0x16U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF197Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F197_ReadData, NULL_PTR}, Dcm_DidMgr_F197_ReadDataLength, {Dcm_DidMgr_F197_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF1A5U, TRUE, 0x16U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF1A5Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F1A5_ReadData, NULL_PTR}, Dcm_DidMgr_F1A5_ReadDataLength, {Dcm_DidMgr_F1A5_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_F1A5_WriteData, NULL_PTR}, Dcm_DidMgr_F1A5_ConditionCheckWrite, NULL_PTR},
	{0xF1A6U, TRUE, 0x11U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF1A6Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F1A6_ReadData, NULL_PTR}, Dcm_DidMgr_F1A6_ReadDataLength, {Dcm_DidMgr_F1A6_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_F1A6_WriteData, NULL_PTR}, Dcm_DidMgr_F1A6_ConditionCheckWrite, NULL_PTR},
	{0x0201U, TRUE, 0x30U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0201Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0201_ReadData, NULL_PTR}, Dcm_DidMgr_0201_ReadDataLength, {Dcm_DidMgr_0201_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0202U, TRUE, 0x10U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0202Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0202_ReadData, NULL_PTR}, Dcm_DidMgr_0202_ReadDataLength, {Dcm_DidMgr_0202_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0202_WriteData, NULL_PTR}, Dcm_DidMgr_0202_ConditionCheckWrite, NULL_PTR},
	{0x0203U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0203Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0203_ReadData, NULL_PTR}, Dcm_DidMgr_0203_ReadDataLength, {Dcm_DidMgr_0203_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0204U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0204Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0204_ReadData, NULL_PTR}, Dcm_DidMgr_0204_ReadDataLength, {Dcm_DidMgr_0204_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0205U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0205Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0205_ReadData, NULL_PTR}, Dcm_DidMgr_0205_ReadDataLength, {Dcm_DidMgr_0205_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0205_WriteData, NULL_PTR}, Dcm_DidMgr_0205_ConditionCheckWrite, NULL_PTR},
	{0x0206U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0206Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0206_ReadData, NULL_PTR}, Dcm_DidMgr_0206_ReadDataLength, {Dcm_DidMgr_0206_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0206_WriteData, NULL_PTR}, Dcm_DidMgr_0206_ConditionCheckWrite, NULL_PTR},
	{0x0207U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0207Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0207_ReadData, NULL_PTR}, Dcm_DidMgr_0207_ReadDataLength, {Dcm_DidMgr_0207_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0x0208U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0208Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0208_ReadData, NULL_PTR}, Dcm_DidMgr_0208_ReadDataLength, {Dcm_DidMgr_0208_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0208_WriteData, NULL_PTR}, Dcm_DidMgr_0208_ConditionCheckWrite, NULL_PTR},
	{0x0209U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_Did0209Buffer, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x0000000CU, 0x00000007U}, {0x0U, NULL_PTR}, {Dcm_DidMgr_0209_ReadData, NULL_PTR}, Dcm_DidMgr_0209_ReadDataLength, {Dcm_DidMgr_0209_ConditionCheckRead, NULL_PTR}, {Dcm_DidMgr_0209_WriteData, NULL_PTR}, Dcm_DidMgr_0209_ConditionCheckWrite, NULL_PTR},
	{0xF400U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF400Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F400_ReadData, NULL_PTR}, Dcm_DidMgr_F400_ReadDataLength, {Dcm_DidMgr_F400_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF401U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF401Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F401_ReadData, NULL_PTR}, Dcm_DidMgr_F401_ReadDataLength, {Dcm_DidMgr_F401_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF402U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF402Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F402_ReadData, NULL_PTR}, Dcm_DidMgr_F402_ReadDataLength, {Dcm_DidMgr_F402_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF404U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF404Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F404_ReadData, NULL_PTR}, Dcm_DidMgr_F404_ReadDataLength, {Dcm_DidMgr_F404_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF405U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF405Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F405_ReadData, NULL_PTR}, Dcm_DidMgr_F405_ReadDataLength, {Dcm_DidMgr_F405_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF40BU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF40BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F40B_ReadData, NULL_PTR}, Dcm_DidMgr_F40B_ReadDataLength, {Dcm_DidMgr_F40B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF40CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF40CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F40C_ReadData, NULL_PTR}, Dcm_DidMgr_F40C_ReadDataLength, {Dcm_DidMgr_F40C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF40DU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF40DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F40D_ReadData, NULL_PTR}, Dcm_DidMgr_F40D_ReadDataLength, {Dcm_DidMgr_F40D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF40FU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF40FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F40F_ReadData, NULL_PTR}, Dcm_DidMgr_F40F_ReadDataLength, {Dcm_DidMgr_F40F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF410U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF410Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F410_ReadData, NULL_PTR}, Dcm_DidMgr_F410_ReadDataLength, {Dcm_DidMgr_F410_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF411U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF411Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F411_ReadData, NULL_PTR}, Dcm_DidMgr_F411_ReadDataLength, {Dcm_DidMgr_F411_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF41CU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF41CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F41C_ReadData, NULL_PTR}, Dcm_DidMgr_F41C_ReadDataLength, {Dcm_DidMgr_F41C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF41EU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF41EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F41E_ReadData, NULL_PTR}, Dcm_DidMgr_F41E_ReadDataLength, {Dcm_DidMgr_F41E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF41FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF41FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F41F_ReadData, NULL_PTR}, Dcm_DidMgr_F41F_ReadDataLength, {Dcm_DidMgr_F41F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF420U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF420Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F420_ReadData, NULL_PTR}, Dcm_DidMgr_F420_ReadDataLength, {Dcm_DidMgr_F420_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF421U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF421Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F421_ReadData, NULL_PTR}, Dcm_DidMgr_F421_ReadDataLength, {Dcm_DidMgr_F421_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF423U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF423Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F423_ReadData, NULL_PTR}, Dcm_DidMgr_F423_ReadDataLength, {Dcm_DidMgr_F423_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF42CU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF42CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F42C_ReadData, NULL_PTR}, Dcm_DidMgr_F42C_ReadDataLength, {Dcm_DidMgr_F42C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF42DU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF42DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F42D_ReadData, NULL_PTR}, Dcm_DidMgr_F42D_ReadDataLength, {Dcm_DidMgr_F42D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF42FU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF42FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F42F_ReadData, NULL_PTR}, Dcm_DidMgr_F42F_ReadDataLength, {Dcm_DidMgr_F42F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF430U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF430Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F430_ReadData, NULL_PTR}, Dcm_DidMgr_F430_ReadDataLength, {Dcm_DidMgr_F430_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF431U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF431Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F431_ReadData, NULL_PTR}, Dcm_DidMgr_F431_ReadDataLength, {Dcm_DidMgr_F431_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF432U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF432Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F432_ReadData, NULL_PTR}, Dcm_DidMgr_F432_ReadDataLength, {Dcm_DidMgr_F432_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF433U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF433Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F433_ReadData, NULL_PTR}, Dcm_DidMgr_F433_ReadDataLength, {Dcm_DidMgr_F433_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF43CU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF43CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F43C_ReadData, NULL_PTR}, Dcm_DidMgr_F43C_ReadDataLength, {Dcm_DidMgr_F43C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF43DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF43DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F43D_ReadData, NULL_PTR}, Dcm_DidMgr_F43D_ReadDataLength, {Dcm_DidMgr_F43D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF43EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF43EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F43E_ReadData, NULL_PTR}, Dcm_DidMgr_F43E_ReadDataLength, {Dcm_DidMgr_F43E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF43FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF43FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F43F_ReadData, NULL_PTR}, Dcm_DidMgr_F43F_ReadDataLength, {Dcm_DidMgr_F43F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF440U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF440Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F440_ReadData, NULL_PTR}, Dcm_DidMgr_F440_ReadDataLength, {Dcm_DidMgr_F440_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF441U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF441Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F441_ReadData, NULL_PTR}, Dcm_DidMgr_F441_ReadDataLength, {Dcm_DidMgr_F441_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF442U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF442Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F442_ReadData, NULL_PTR}, Dcm_DidMgr_F442_ReadDataLength, {Dcm_DidMgr_F442_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF444U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF444Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F444_ReadData, NULL_PTR}, Dcm_DidMgr_F444_ReadDataLength, {Dcm_DidMgr_F444_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF445U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF445Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F445_ReadData, NULL_PTR}, Dcm_DidMgr_F445_ReadDataLength, {Dcm_DidMgr_F445_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF446U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF446Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F446_ReadData, NULL_PTR}, Dcm_DidMgr_F446_ReadDataLength, {Dcm_DidMgr_F446_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF449U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF449Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F449_ReadData, NULL_PTR}, Dcm_DidMgr_F449_ReadDataLength, {Dcm_DidMgr_F449_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF44AU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF44ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F44A_ReadData, NULL_PTR}, Dcm_DidMgr_F44A_ReadDataLength, {Dcm_DidMgr_F44A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF44CU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF44CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F44C_ReadData, NULL_PTR}, Dcm_DidMgr_F44C_ReadDataLength, {Dcm_DidMgr_F44C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF44DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF44DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F44D_ReadData, NULL_PTR}, Dcm_DidMgr_F44D_ReadDataLength, {Dcm_DidMgr_F44D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF44EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF44EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F44E_ReadData, NULL_PTR}, Dcm_DidMgr_F44E_ReadDataLength, {Dcm_DidMgr_F44E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF44FU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF44FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F44F_ReadData, NULL_PTR}, Dcm_DidMgr_F44F_ReadDataLength, {Dcm_DidMgr_F44F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF450U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF450Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F450_ReadData, NULL_PTR}, Dcm_DidMgr_F450_ReadDataLength, {Dcm_DidMgr_F450_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF459U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF459Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F459_ReadData, NULL_PTR}, Dcm_DidMgr_F459_ReadDataLength, {Dcm_DidMgr_F459_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF45AU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF45ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F45A_ReadData, NULL_PTR}, Dcm_DidMgr_F45A_ReadDataLength, {Dcm_DidMgr_F45A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF45CU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF45CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F45C_ReadData, NULL_PTR}, Dcm_DidMgr_F45C_ReadDataLength, {Dcm_DidMgr_F45C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF45DU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF45DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F45D_ReadData, NULL_PTR}, Dcm_DidMgr_F45D_ReadDataLength, {Dcm_DidMgr_F45D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF45EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF45EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F45E_ReadData, NULL_PTR}, Dcm_DidMgr_F45E_ReadDataLength, {Dcm_DidMgr_F45E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF460U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF460Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F460_ReadData, NULL_PTR}, Dcm_DidMgr_F460_ReadDataLength, {Dcm_DidMgr_F460_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF461U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF461Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F461_ReadData, NULL_PTR}, Dcm_DidMgr_F461_ReadDataLength, {Dcm_DidMgr_F461_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF462U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF462Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F462_ReadData, NULL_PTR}, Dcm_DidMgr_F462_ReadDataLength, {Dcm_DidMgr_F462_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF463U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF463Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F463_ReadData, NULL_PTR}, Dcm_DidMgr_F463_ReadDataLength, {Dcm_DidMgr_F463_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF464U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF464Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F464_ReadData, NULL_PTR}, Dcm_DidMgr_F464_ReadDataLength, {Dcm_DidMgr_F464_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF465U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF465Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F465_ReadData, NULL_PTR}, Dcm_DidMgr_F465_ReadDataLength, {Dcm_DidMgr_F465_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF466U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF466Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F466_ReadData, NULL_PTR}, Dcm_DidMgr_F466_ReadDataLength, {Dcm_DidMgr_F466_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF467U, TRUE, 0x03U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF467Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F467_ReadData, NULL_PTR}, Dcm_DidMgr_F467_ReadDataLength, {Dcm_DidMgr_F467_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF468U, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF468Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F468_ReadData, NULL_PTR}, Dcm_DidMgr_F468_ReadDataLength, {Dcm_DidMgr_F468_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF469U, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF469Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F469_ReadData, NULL_PTR}, Dcm_DidMgr_F469_ReadDataLength, {Dcm_DidMgr_F469_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF46BU, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF46BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F46B_ReadData, NULL_PTR}, Dcm_DidMgr_F46B_ReadDataLength, {Dcm_DidMgr_F46B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF46CU, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF46CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F46C_ReadData, NULL_PTR}, Dcm_DidMgr_F46C_ReadDataLength, {Dcm_DidMgr_F46C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF46DU, TRUE, 0x0BU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF46DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F46D_ReadData, NULL_PTR}, Dcm_DidMgr_F46D_ReadDataLength, {Dcm_DidMgr_F46D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF46EU, TRUE, 0x09U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF46EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F46E_ReadData, NULL_PTR}, Dcm_DidMgr_F46E_ReadDataLength, {Dcm_DidMgr_F46E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF46FU, TRUE, 0x03U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF46FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F46F_ReadData, NULL_PTR}, Dcm_DidMgr_F46F_ReadDataLength, {Dcm_DidMgr_F46F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF470U, TRUE, 0x0AU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF470Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F470_ReadData, NULL_PTR}, Dcm_DidMgr_F470_ReadDataLength, {Dcm_DidMgr_F470_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF471U, TRUE, 0x06U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF471Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F471_ReadData, NULL_PTR}, Dcm_DidMgr_F471_ReadDataLength, {Dcm_DidMgr_F471_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF472U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF472Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F472_ReadData, NULL_PTR}, Dcm_DidMgr_F472_ReadDataLength, {Dcm_DidMgr_F472_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF473U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF473Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F473_ReadData, NULL_PTR}, Dcm_DidMgr_F473_ReadDataLength, {Dcm_DidMgr_F473_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF474U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF474Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F474_ReadData, NULL_PTR}, Dcm_DidMgr_F474_ReadDataLength, {Dcm_DidMgr_F474_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF475U, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF475Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F475_ReadData, NULL_PTR}, Dcm_DidMgr_F475_ReadDataLength, {Dcm_DidMgr_F475_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF476U, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF476Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F476_ReadData, NULL_PTR}, Dcm_DidMgr_F476_ReadDataLength, {Dcm_DidMgr_F476_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF477U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF477Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F477_ReadData, NULL_PTR}, Dcm_DidMgr_F477_ReadDataLength, {Dcm_DidMgr_F477_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF478U, TRUE, 0x09U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF478Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F478_ReadData, NULL_PTR}, Dcm_DidMgr_F478_ReadDataLength, {Dcm_DidMgr_F478_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF47AU, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF47ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F47A_ReadData, NULL_PTR}, Dcm_DidMgr_F47A_ReadDataLength, {Dcm_DidMgr_F47A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF47BU, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF47BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F47B_ReadData, NULL_PTR}, Dcm_DidMgr_F47B_ReadDataLength, {Dcm_DidMgr_F47B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF47CU, TRUE, 0x09U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF47CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F47C_ReadData, NULL_PTR}, Dcm_DidMgr_F47C_ReadDataLength, {Dcm_DidMgr_F47C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF47DU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF47DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F47D_ReadData, NULL_PTR}, Dcm_DidMgr_F47D_ReadDataLength, {Dcm_DidMgr_F47D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF47EU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF47EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F47E_ReadData, NULL_PTR}, Dcm_DidMgr_F47E_ReadDataLength, {Dcm_DidMgr_F47E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF47FU, TRUE, 0x0DU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF47FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F47F_ReadData, NULL_PTR}, Dcm_DidMgr_F47F_ReadDataLength, {Dcm_DidMgr_F47F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF480U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF480Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F480_ReadData, NULL_PTR}, Dcm_DidMgr_F480_ReadDataLength, {Dcm_DidMgr_F480_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF481U, TRUE, 0x29U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF481Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F481_ReadData, NULL_PTR}, Dcm_DidMgr_F481_ReadDataLength, {Dcm_DidMgr_F481_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF482U, TRUE, 0x29U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF482Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F482_ReadData, NULL_PTR}, Dcm_DidMgr_F482_ReadDataLength, {Dcm_DidMgr_F482_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF483U, TRUE, 0x09U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF483Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F483_ReadData, NULL_PTR}, Dcm_DidMgr_F483_ReadDataLength, {Dcm_DidMgr_F483_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF485U, TRUE, 0x0AU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF485Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F485_ReadData, NULL_PTR}, Dcm_DidMgr_F485_ReadDataLength, {Dcm_DidMgr_F485_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF486U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF486Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F486_ReadData, NULL_PTR}, Dcm_DidMgr_F486_ReadDataLength, {Dcm_DidMgr_F486_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF487U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF487Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F487_ReadData, NULL_PTR}, Dcm_DidMgr_F487_ReadDataLength, {Dcm_DidMgr_F487_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF488U, TRUE, 0x0DU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF488Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F488_ReadData, NULL_PTR}, Dcm_DidMgr_F488_ReadDataLength, {Dcm_DidMgr_F488_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF489U, TRUE, 0x29U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF489Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F489_ReadData, NULL_PTR}, Dcm_DidMgr_F489_ReadDataLength, {Dcm_DidMgr_F489_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF48BU, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF48BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F48B_ReadData, NULL_PTR}, Dcm_DidMgr_F48B_ReadDataLength, {Dcm_DidMgr_F48B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF48CU, TRUE, 0x11U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF48CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F48C_ReadData, NULL_PTR}, Dcm_DidMgr_F48C_ReadDataLength, {Dcm_DidMgr_F48C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF48EU, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF48EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F48E_ReadData, NULL_PTR}, Dcm_DidMgr_F48E_ReadDataLength, {Dcm_DidMgr_F48E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF48FU, TRUE, 0x07U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF48FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F48F_ReadData, NULL_PTR}, Dcm_DidMgr_F48F_ReadDataLength, {Dcm_DidMgr_F48F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF490U, TRUE, 0x03U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF490Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F490_ReadData, NULL_PTR}, Dcm_DidMgr_F490_ReadDataLength, {Dcm_DidMgr_F490_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF491U, TRUE, 0x05U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF491Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F491_ReadData, NULL_PTR}, Dcm_DidMgr_F491_ReadDataLength, {Dcm_DidMgr_F491_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF492U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF492Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F492_ReadData, NULL_PTR}, Dcm_DidMgr_F492_ReadDataLength, {Dcm_DidMgr_F492_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF493U, TRUE, 0x03U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF493Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F493_ReadData, NULL_PTR}, Dcm_DidMgr_F493_ReadDataLength, {Dcm_DidMgr_F493_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF494U, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF494Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F494_ReadData, NULL_PTR}, Dcm_DidMgr_F494_ReadDataLength, {Dcm_DidMgr_F494_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF498U, TRUE, 0x09U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF498Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F498_ReadData, NULL_PTR}, Dcm_DidMgr_F498_ReadDataLength, {Dcm_DidMgr_F498_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF49DU, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF49DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F49D_ReadData, NULL_PTR}, Dcm_DidMgr_F49D_ReadDataLength, {Dcm_DidMgr_F49D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF49EU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF49EBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F49E_ReadData, NULL_PTR}, Dcm_DidMgr_F49E_ReadDataLength, {Dcm_DidMgr_F49E_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF49FU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF49FBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F49F_ReadData, NULL_PTR}, Dcm_DidMgr_F49F_ReadDataLength, {Dcm_DidMgr_F49F_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A0U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A0_ReadData, NULL_PTR}, Dcm_DidMgr_F4A0_ReadDataLength, {Dcm_DidMgr_F4A0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A1_ReadData, NULL_PTR}, Dcm_DidMgr_F4A1_ReadDataLength, {Dcm_DidMgr_F4A1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A2_ReadData, NULL_PTR}, Dcm_DidMgr_F4A2_ReadDataLength, {Dcm_DidMgr_F4A2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A3_ReadData, NULL_PTR}, Dcm_DidMgr_F4A3_ReadDataLength, {Dcm_DidMgr_F4A3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A4_ReadData, NULL_PTR}, Dcm_DidMgr_F4A4_ReadDataLength, {Dcm_DidMgr_F4A4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A5_ReadData, NULL_PTR}, Dcm_DidMgr_F4A5_ReadDataLength, {Dcm_DidMgr_F4A5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A6U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A6_ReadData, NULL_PTR}, Dcm_DidMgr_F4A6_ReadDataLength, {Dcm_DidMgr_F4A6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A7_ReadData, NULL_PTR}, Dcm_DidMgr_F4A7_ReadDataLength, {Dcm_DidMgr_F4A7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A8_ReadData, NULL_PTR}, Dcm_DidMgr_F4A8_ReadDataLength, {Dcm_DidMgr_F4A8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4A9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4A9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4A9_ReadData, NULL_PTR}, Dcm_DidMgr_F4A9_ReadDataLength, {Dcm_DidMgr_F4A9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4AAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4AABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4AA_ReadData, NULL_PTR}, Dcm_DidMgr_F4AA_ReadDataLength, {Dcm_DidMgr_F4AA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4ABU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4ABBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4AB_ReadData, NULL_PTR}, Dcm_DidMgr_F4AB_ReadDataLength, {Dcm_DidMgr_F4AB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4ACU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4ACBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4AC_ReadData, NULL_PTR}, Dcm_DidMgr_F4AC_ReadDataLength, {Dcm_DidMgr_F4AC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4ADU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4ADBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4AD_ReadData, NULL_PTR}, Dcm_DidMgr_F4AD_ReadDataLength, {Dcm_DidMgr_F4AD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4AEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4AEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4AE_ReadData, NULL_PTR}, Dcm_DidMgr_F4AE_ReadDataLength, {Dcm_DidMgr_F4AE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4AFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4AFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4AF_ReadData, NULL_PTR}, Dcm_DidMgr_F4AF_ReadDataLength, {Dcm_DidMgr_F4AF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B0_ReadData, NULL_PTR}, Dcm_DidMgr_F4B0_ReadDataLength, {Dcm_DidMgr_F4B0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B1_ReadData, NULL_PTR}, Dcm_DidMgr_F4B1_ReadDataLength, {Dcm_DidMgr_F4B1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B2_ReadData, NULL_PTR}, Dcm_DidMgr_F4B2_ReadDataLength, {Dcm_DidMgr_F4B2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B3_ReadData, NULL_PTR}, Dcm_DidMgr_F4B3_ReadDataLength, {Dcm_DidMgr_F4B3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B4_ReadData, NULL_PTR}, Dcm_DidMgr_F4B4_ReadDataLength, {Dcm_DidMgr_F4B4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B5_ReadData, NULL_PTR}, Dcm_DidMgr_F4B5_ReadDataLength, {Dcm_DidMgr_F4B5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B6_ReadData, NULL_PTR}, Dcm_DidMgr_F4B6_ReadDataLength, {Dcm_DidMgr_F4B6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B7_ReadData, NULL_PTR}, Dcm_DidMgr_F4B7_ReadDataLength, {Dcm_DidMgr_F4B7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B9_ReadData, NULL_PTR}, Dcm_DidMgr_F4B9_ReadDataLength, {Dcm_DidMgr_F4B9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4B8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4B8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4B8_ReadData, NULL_PTR}, Dcm_DidMgr_F4B8_ReadDataLength, {Dcm_DidMgr_F4B8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4BAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4BABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4BA_ReadData, NULL_PTR}, Dcm_DidMgr_F4BA_ReadDataLength, {Dcm_DidMgr_F4BA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4BBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4BBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4BB_ReadData, NULL_PTR}, Dcm_DidMgr_F4BB_ReadDataLength, {Dcm_DidMgr_F4BB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4BCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4BCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4BC_ReadData, NULL_PTR}, Dcm_DidMgr_F4BC_ReadDataLength, {Dcm_DidMgr_F4BC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4BDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4BDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4BD_ReadData, NULL_PTR}, Dcm_DidMgr_F4BD_ReadDataLength, {Dcm_DidMgr_F4BD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4BEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4BEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4BE_ReadData, NULL_PTR}, Dcm_DidMgr_F4BE_ReadDataLength, {Dcm_DidMgr_F4BE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4BFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4BFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4BF_ReadData, NULL_PTR}, Dcm_DidMgr_F4BF_ReadDataLength, {Dcm_DidMgr_F4BF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C1_ReadData, NULL_PTR}, Dcm_DidMgr_F4C1_ReadDataLength, {Dcm_DidMgr_F4C1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C2_ReadData, NULL_PTR}, Dcm_DidMgr_F4C2_ReadDataLength, {Dcm_DidMgr_F4C2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C3_ReadData, NULL_PTR}, Dcm_DidMgr_F4C3_ReadDataLength, {Dcm_DidMgr_F4C3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C4_ReadData, NULL_PTR}, Dcm_DidMgr_F4C4_ReadDataLength, {Dcm_DidMgr_F4C4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C5_ReadData, NULL_PTR}, Dcm_DidMgr_F4C5_ReadDataLength, {Dcm_DidMgr_F4C5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C6_ReadData, NULL_PTR}, Dcm_DidMgr_F4C6_ReadDataLength, {Dcm_DidMgr_F4C6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C7_ReadData, NULL_PTR}, Dcm_DidMgr_F4C7_ReadDataLength, {Dcm_DidMgr_F4C7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C8_ReadData, NULL_PTR}, Dcm_DidMgr_F4C8_ReadDataLength, {Dcm_DidMgr_F4C8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C9_ReadData, NULL_PTR}, Dcm_DidMgr_F4C9_ReadDataLength, {Dcm_DidMgr_F4C9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4CAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4CABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4CA_ReadData, NULL_PTR}, Dcm_DidMgr_F4CA_ReadDataLength, {Dcm_DidMgr_F4CA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4CBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4CBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4CB_ReadData, NULL_PTR}, Dcm_DidMgr_F4CB_ReadDataLength, {Dcm_DidMgr_F4CB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4CCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4CCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4CC_ReadData, NULL_PTR}, Dcm_DidMgr_F4CC_ReadDataLength, {Dcm_DidMgr_F4CC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4CDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4CDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4CD_ReadData, NULL_PTR}, Dcm_DidMgr_F4CD_ReadDataLength, {Dcm_DidMgr_F4CD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4CEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4CEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4CE_ReadData, NULL_PTR}, Dcm_DidMgr_F4CE_ReadDataLength, {Dcm_DidMgr_F4CE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4CFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4CFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4CF_ReadData, NULL_PTR}, Dcm_DidMgr_F4CF_ReadDataLength, {Dcm_DidMgr_F4CF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D0_ReadData, NULL_PTR}, Dcm_DidMgr_F4D0_ReadDataLength, {Dcm_DidMgr_F4D0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D1_ReadData, NULL_PTR}, Dcm_DidMgr_F4D1_ReadDataLength, {Dcm_DidMgr_F4D1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D2_ReadData, NULL_PTR}, Dcm_DidMgr_F4D2_ReadDataLength, {Dcm_DidMgr_F4D2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D3_ReadData, NULL_PTR}, Dcm_DidMgr_F4D3_ReadDataLength, {Dcm_DidMgr_F4D3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D4_ReadData, NULL_PTR}, Dcm_DidMgr_F4D4_ReadDataLength, {Dcm_DidMgr_F4D4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D5_ReadData, NULL_PTR}, Dcm_DidMgr_F4D5_ReadDataLength, {Dcm_DidMgr_F4D5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D6_ReadData, NULL_PTR}, Dcm_DidMgr_F4D6_ReadDataLength, {Dcm_DidMgr_F4D6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D7_ReadData, NULL_PTR}, Dcm_DidMgr_F4D7_ReadDataLength, {Dcm_DidMgr_F4D7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D8_ReadData, NULL_PTR}, Dcm_DidMgr_F4D8_ReadDataLength, {Dcm_DidMgr_F4D8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4D9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4D9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4D9_ReadData, NULL_PTR}, Dcm_DidMgr_F4D9_ReadDataLength, {Dcm_DidMgr_F4D9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4DAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4DABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4DA_ReadData, NULL_PTR}, Dcm_DidMgr_F4DA_ReadDataLength, {Dcm_DidMgr_F4DA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4DBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4DBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4DB_ReadData, NULL_PTR}, Dcm_DidMgr_F4DB_ReadDataLength, {Dcm_DidMgr_F4DB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4DCU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4DCBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4DC_ReadData, NULL_PTR}, Dcm_DidMgr_F4DC_ReadDataLength, {Dcm_DidMgr_F4DC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4DDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4DDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4DD_ReadData, NULL_PTR}, Dcm_DidMgr_F4DD_ReadDataLength, {Dcm_DidMgr_F4DD_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4DEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4DEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4DE_ReadData, NULL_PTR}, Dcm_DidMgr_F4DE_ReadDataLength, {Dcm_DidMgr_F4DE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4DFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4DFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4DF_ReadData, NULL_PTR}, Dcm_DidMgr_F4DF_ReadDataLength, {Dcm_DidMgr_F4DF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E1_ReadData, NULL_PTR}, Dcm_DidMgr_F4E1_ReadDataLength, {Dcm_DidMgr_F4E1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E2_ReadData, NULL_PTR}, Dcm_DidMgr_F4E2_ReadDataLength, {Dcm_DidMgr_F4E2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E3_ReadData, NULL_PTR}, Dcm_DidMgr_F4E3_ReadDataLength, {Dcm_DidMgr_F4E3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E4_ReadData, NULL_PTR}, Dcm_DidMgr_F4E4_ReadDataLength, {Dcm_DidMgr_F4E4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E5_ReadData, NULL_PTR}, Dcm_DidMgr_F4E5_ReadDataLength, {Dcm_DidMgr_F4E5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E6_ReadData, NULL_PTR}, Dcm_DidMgr_F4E6_ReadDataLength, {Dcm_DidMgr_F4E6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E7_ReadData, NULL_PTR}, Dcm_DidMgr_F4E7_ReadDataLength, {Dcm_DidMgr_F4E7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E8U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E8Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E8_ReadData, NULL_PTR}, Dcm_DidMgr_F4E8_ReadDataLength, {Dcm_DidMgr_F4E8_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E9U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E9Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E9_ReadData, NULL_PTR}, Dcm_DidMgr_F4E9_ReadDataLength, {Dcm_DidMgr_F4E9_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4EAU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4EABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4EA_ReadData, NULL_PTR}, Dcm_DidMgr_F4EA_ReadDataLength, {Dcm_DidMgr_F4EA_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4EBU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4EBBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4EB_ReadData, NULL_PTR}, Dcm_DidMgr_F4EB_ReadDataLength, {Dcm_DidMgr_F4EB_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4ECU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4ECBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4EC_ReadData, NULL_PTR}, Dcm_DidMgr_F4EC_ReadDataLength, {Dcm_DidMgr_F4EC_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4EDU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4EDBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4ED_ReadData, NULL_PTR}, Dcm_DidMgr_F4ED_ReadDataLength, {Dcm_DidMgr_F4ED_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4EEU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4EEBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4EE_ReadData, NULL_PTR}, Dcm_DidMgr_F4EE_ReadDataLength, {Dcm_DidMgr_F4EE_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4EFU, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4EFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4EF_ReadData, NULL_PTR}, Dcm_DidMgr_F4EF_ReadDataLength, {Dcm_DidMgr_F4EF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4F0U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4F0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4F0_ReadData, NULL_PTR}, Dcm_DidMgr_F4F0_ReadDataLength, {Dcm_DidMgr_F4F0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4F1U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4F1Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4F1_ReadData, NULL_PTR}, Dcm_DidMgr_F4F1_ReadDataLength, {Dcm_DidMgr_F4F1_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4F2U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4F2Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4F2_ReadData, NULL_PTR}, Dcm_DidMgr_F4F2_ReadDataLength, {Dcm_DidMgr_F4F2_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4F3U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4F3Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4F3_ReadData, NULL_PTR}, Dcm_DidMgr_F4F3_ReadDataLength, {Dcm_DidMgr_F4F3_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4F4U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4F4Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4F4_ReadData, NULL_PTR}, Dcm_DidMgr_F4F4_ReadDataLength, {Dcm_DidMgr_F4F4_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4F5U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4F5Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4F5_ReadData, NULL_PTR}, Dcm_DidMgr_F4F5_ReadDataLength, {Dcm_DidMgr_F4F5_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4F6U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4F6Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4F6_ReadData, NULL_PTR}, Dcm_DidMgr_F4F6_ReadDataLength, {Dcm_DidMgr_F4F6_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4F7U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4F7Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4F7_ReadData, NULL_PTR}, Dcm_DidMgr_F4F7_ReadDataLength, {Dcm_DidMgr_F4F7_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4FFU, TRUE, 0x0AU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4FFBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4FF_ReadData, NULL_PTR}, Dcm_DidMgr_F4FF_ReadDataLength, {Dcm_DidMgr_F4FF_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4C0U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4C0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4C0_ReadData, NULL_PTR}, Dcm_DidMgr_F4C0_ReadDataLength, {Dcm_DidMgr_F4C0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF4E0U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF4E0Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F4E0_ReadData, NULL_PTR}, Dcm_DidMgr_F4E0_ReadDataLength, {Dcm_DidMgr_F4E0_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF800U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF800Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F800_ReadData, NULL_PTR}, Dcm_DidMgr_F800_ReadDataLength, {Dcm_DidMgr_F800_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF802U, TRUE, 0x11U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF802Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F802_ReadData, NULL_PTR}, Dcm_DidMgr_F802_ReadDataLength, {Dcm_DidMgr_F802_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF804U, TRUE, 0x10U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF804Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F804_ReadData, NULL_PTR}, Dcm_DidMgr_F804_ReadDataLength, {Dcm_DidMgr_F804_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF806U, TRUE, 0x04U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF806Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F806_ReadData, NULL_PTR}, Dcm_DidMgr_F806_ReadDataLength, {Dcm_DidMgr_F806_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF80AU, TRUE, 0x14U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF80ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F80A_ReadData, NULL_PTR}, Dcm_DidMgr_F80A_ReadDataLength, {Dcm_DidMgr_F80A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF80BU, TRUE, 0x24U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF80BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F80B_ReadData, NULL_PTR}, Dcm_DidMgr_F80B_ReadDataLength, {Dcm_DidMgr_F80B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF80DU, TRUE, 0x11U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF80DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F80D_ReadData, NULL_PTR}, Dcm_DidMgr_F80D_ReadDataLength, {Dcm_DidMgr_F80D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF810U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF810Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F810_ReadData, NULL_PTR}, Dcm_DidMgr_F810_ReadDataLength, {Dcm_DidMgr_F810_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF811U, TRUE, 0x0BU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF811Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F811_ReadData, NULL_PTR}, Dcm_DidMgr_F811_ReadDataLength, {Dcm_DidMgr_F811_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF812U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF812Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F812_ReadData, NULL_PTR}, Dcm_DidMgr_F812_ReadDataLength, {Dcm_DidMgr_F812_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF813U, TRUE, 0x0CU, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF813Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F813_ReadData, NULL_PTR}, Dcm_DidMgr_F813_ReadDataLength, {Dcm_DidMgr_F813_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF814U, TRUE, 0x02U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF814Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F814_ReadData, NULL_PTR}, Dcm_DidMgr_F814_ReadDataLength, {Dcm_DidMgr_F814_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF815U, TRUE, 0x01U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF815Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F815_ReadData, NULL_PTR}, Dcm_DidMgr_F815_ReadDataLength, {Dcm_DidMgr_F815_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF816U, TRUE, 0x20U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF816Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F816_ReadData, NULL_PTR}, Dcm_DidMgr_F816_ReadDataLength, {Dcm_DidMgr_F816_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF817U, TRUE, 0x10U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF817Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F817_ReadData, NULL_PTR}, Dcm_DidMgr_F817_ReadDataLength, {Dcm_DidMgr_F817_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF818U, TRUE, 0x10U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF818Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F818_ReadData, NULL_PTR}, Dcm_DidMgr_F818_ReadDataLength, {Dcm_DidMgr_F818_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF819U, TRUE, 0x18U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF819Buffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F819_ReadData, NULL_PTR}, Dcm_DidMgr_F819_ReadDataLength, {Dcm_DidMgr_F819_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF81AU, TRUE, 0x18U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF81ABuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F81A_ReadData, NULL_PTR}, Dcm_DidMgr_F81A_ReadDataLength, {Dcm_DidMgr_F81A_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF81BU, TRUE, 0x10U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF81BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F81B_ReadData, NULL_PTR}, Dcm_DidMgr_F81B_ReadDataLength, {Dcm_DidMgr_F81B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF81CU, TRUE, 0x18U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF81CBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F81C_ReadData, NULL_PTR}, Dcm_DidMgr_F81C_ReadDataLength, {Dcm_DidMgr_F81C_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF81DU, TRUE, 0x20U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF81DBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F81D_ReadData, NULL_PTR}, Dcm_DidMgr_F81D_ReadDataLength, {Dcm_DidMgr_F81D_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xF15BU, TRUE, 0x28U, DCM_INVALID_BLOCKID, NULL_PTR,	Dcm_DidF15BBuffer, DCM_RAED_ACESS, USE_DATA_SYNCH_FNC, {0x00000004U, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR}, {Dcm_DidMgr_F15B_ReadData, NULL_PTR}, Dcm_DidMgr_F15B_ReadDataLength, {Dcm_DidMgr_F15B_ConditionCheckRead, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR},
	{0xFFFFU, FALSE, 0xFFU, DCM_INVALID_BLOCKID, NULL_PTR, NULL_PTR, DCM_RAED_AND_WRITE_ACESS, USE_DATA_SYNCH_FNC, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, {NULL_PTR, NULL_PTR}, {NULL_PTR, NULL_PTR}, NULL_PTR, NULL_PTR}
};
CONST(Dcm_22_2E_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_22_2E_Dispatcher =
{
	Dcm_22_DidList,
	Dcm_22_DidResLen,
	Dcm_22_2E_ServiceInfo,
};
#endif

 
#if (STD_ON == DCM_SERVICE_27_ENABLED)
CONST(Dcm_27_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_27_ServiceInfo[DCM_27_SUB_NUM + 1] =
{
	{0x01U,	DCM_PHY,	{0x0000000CU, 0x7FFFFFFFU},	{0x7FFFFFFFU,0x7FFFFFFFU},	{0x0U, NULL_PTR},	DCM_2701_ATTCOUNTER,	DCM_2701_MAX_SEED_LENGTH,	DCM_2701_MAX_KEY_LENGTH,	DCM_2701_ATTDELAY,	Dcm_SecurityAccess_Level_01_GetSeed,	Dcm_SecurityAccess_Level_01_CompareKey,	Dcm_SecurityAccess_Level_01_CheckRule,	&Dcm_27_Security_Data[0],	Dcm_SecurityAccess_Level_01_GetAttemptCounter,	Dcm_SecurityAccess_Level_01_SetAttemptCounter},
	{0x05U,	DCM_PHY,	{0x0000000CU, 0x7FFFFFFFU},	{0x7FFFFFFFU,0x7FFFFFFFU},	{0x0U, NULL_PTR},	DCM_2705_ATTCOUNTER,	DCM_2705_MAX_SEED_LENGTH,	DCM_2705_MAX_KEY_LENGTH,	DCM_2705_ATTDELAY,	Dcm_SecurityAccess_Level_05_GetSeed,	Dcm_SecurityAccess_Level_05_CompareKey,	Dcm_SecurityAccess_Level_05_CheckRule,	&Dcm_27_Security_Data[1],	Dcm_SecurityAccess_Level_05_GetAttemptCounter,	Dcm_SecurityAccess_Level_05_SetAttemptCounter},
	{0x03U,	DCM_PHY,	{0x0000000CU, 0x7FFFFFFFU},	{0x7FFFFFFFU,0x7FFFFFFFU},	{0x0U, NULL_PTR},	DCM_2703_ATTCOUNTER,	DCM_2703_MAX_SEED_LENGTH,	DCM_2703_MAX_KEY_LENGTH,	DCM_2703_ATTDELAY,	Dcm_SecurityAccess_Level_03_GetSeed,	Dcm_SecurityAccess_Level_03_CompareKey,	Dcm_SecurityAccess_Level_03_CheckRule,	&Dcm_27_Security_Data[2],	Dcm_SecurityAccess_Level_03_GetAttemptCounter,	Dcm_SecurityAccess_Level_03_SetAttemptCounter},
	{0x41U,	DCM_PHY,	{0x0000000CU, 0x7FFFFFFFU},	{0x7FFFFFFFU,0x7FFFFFFFU},	{0x0U, NULL_PTR},	DCM_2741_ATTCOUNTER,	DCM_2741_MAX_SEED_LENGTH,	DCM_2741_MAX_KEY_LENGTH,	DCM_2741_ATTDELAY,	Dcm_SecurityAccess_Level_41_GetSeed,	Dcm_SecurityAccess_Level_41_CompareKey,	Dcm_SecurityAccess_Level_41_CheckRule,	&Dcm_27_Security_Data[3],	Dcm_SecurityAccess_Level_41_GetAttemptCounter,	Dcm_SecurityAccess_Level_41_SetAttemptCounter},
	{0xFFU,	DCM_PHY_FUN,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR},	0xFFU,	0xFFU,	0xFFU,	0xFFU,	NULL_PTR,	NULL_PTR,	NULL_PTR,   NULL_PTR,   NULL_PTR,   NULL_PTR}
};
CONST(Dcm_27_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_27_Dispatcher =
{
	Dcm_27_ServiceInfo,
};
#endif/* STD_ON == DCM_SERVICE_27_ENABLED */

 
#if (STD_ON == DCM_SERVICE_28_ENABLED)
CONST(uint8, DCM_CONFIG_DATA) Dcm_28_ControlState[DCM_28_CONTROL_STATE_NUM] = 
{
	0x01U,
	0x02U,
	0x03U
};
CONST(uint8, DCM_CONFIG_DATA) Dcm_28_ChannelId[DCM_28_CHANNLE_NUM + 1U] = 
{
	0x00U,
	0x01U,
	0x02U,
	0x03U,
	0xFFU
};
CONST(Dcm_28_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_28_ServiceInfoTable[DCM_28_SUBID_NUM + 1] = 
{
	{0x00U,	DCM_PHY_FUN,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check28SubComMFunc},
	{0x03U,	DCM_PHY_FUN,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check28SubComMFunc},
	{0x80U,	DCM_PHY_FUN,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check28SubComMFunc},
	{0x83U,	DCM_PHY_FUN,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check28SubComMFunc},
	{0xFFU,	DCM_PHY_FUN,	{0x7FFFFFFFU, 0x7FFFFFFFU}, {0x0U, NULL_PTR},	NULL_PTR}
};
CONST(Dcm_28_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_28_Dispatcher =
{
	Dcm_28_ControlState,
	Dcm_28_ServiceInfoTable,
};
#endif/* STD_ON == DCM_SERVICE_28_ENABLED */

 
#if (STD_ON == DCM_SERVICE_2F_ENABLED)
CONST(Dcm_2F_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2F_ServiceInfo[DCM_2F_MAX_SUB_DID_NUM + 1] =
{
	{0x1004U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1004_ReturnControlToECU,	InputOutput_1004_ResetToDefault,	InputOutput_1004_FreezeCurrentState,	InputOutput_1004_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1015U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1015_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1015_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1055U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1055_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1055_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1054U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1054_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1054_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1053U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1053_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1053_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1052U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1052_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1052_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1051U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1051_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1051_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1050U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1050_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1050_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x104FU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_104F_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_104F_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x104EU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_104E_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_104E_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x104DU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_104D_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_104D_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x104CU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_104C_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_104C_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x104BU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_104B_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_104B_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x104AU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_104A_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_104A_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1049U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1049_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1049_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1048U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1048_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1048_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1047U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1047_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1047_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1046U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1046_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1046_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1045U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1045_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1045_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1044U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1044_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1044_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1043U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1043_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1043_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1042U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1042_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1042_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1041U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1041_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1041_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1040U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1040_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1040_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x103FU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_103F_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_103F_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x103EU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_103E_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_103E_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x103DU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_103D_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_103D_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x103CU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_103C_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_103C_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x103BU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_103B_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_103B_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x103AU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_103A_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_103A_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1039U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1039_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1039_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1038U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x02U, 0x00U},	InputOutput_1038_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1038_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1037U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x02U, 0x00U},	InputOutput_1037_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1037_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1036U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x02U, 0x00U},	InputOutput_1036_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1036_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1035U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x02U, 0x00U},	InputOutput_1035_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1035_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1034U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x02U, 0x00U},	InputOutput_1034_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1034_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1033U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x02U, 0x00U},	InputOutput_1033_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1033_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1032U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1032_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1032_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1031U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1031_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1031_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1030U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1030_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1030_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x102FU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_102F_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_102F_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x102EU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_102E_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_102E_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x102DU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_102D_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_102D_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x102CU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_102C_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_102C_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x102BU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_102B_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_102B_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x102AU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_102A_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_102A_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1029U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1029_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1029_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1028U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1028_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1028_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1027U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1027_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1027_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1026U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1026_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1026_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1025U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1025_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1025_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1024U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1024_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1024_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1023U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1023_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1023_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1022U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1022_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1022_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1021U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1021_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1021_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1020U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1020_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1020_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x101FU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_101F_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_101F_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x101EU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_101E_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_101E_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x101DU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_101D_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_101D_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1003U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1003_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1003_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1006U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1006_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1006_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1002U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1002_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1002_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1005U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1005_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1005_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1001U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1001_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1001_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1007U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1007_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1007_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1008U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1008_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1008_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1009U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1009_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1009_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x100AU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_100A_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_100A_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x100BU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_100B_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_100B_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x100CU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_100C_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_100C_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x100DU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_100D_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_100D_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x100EU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_100E_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_100E_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x100FU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_100F_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_100F_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1010U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1010_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1010_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1011U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1011_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1011_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1012U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1012_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1012_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1013U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1013_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1013_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1014U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1014_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1014_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1016U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1016_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1016_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1017U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1017_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1017_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1018U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1018_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1018_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x1019U,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_1019_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_1019_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x101AU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_101A_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_101A_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x101BU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_101B_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_101B_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0x101CU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x0000000CU, 0x00000003U},	{0x0U, NULL_PTR},	{0x0U, 0x01U, 0x00U},	InputOutput_101C_ReturnControlToECU,	NULL_PTR,	NULL_PTR,	InputOutput_101C_ShortTermAdjustment,	Dcm_Check2FSubIOFunc},
	{0xFFFFU,	TRUE,	DCM_2F_SIGNAL_TYPE_FIXED,	{0x7FFFFFFFU, 0x7FFFFFFFU},    {0x0U, NULL_PTR},   {0x0U, 0x0U, 0x0U},	NULL_PTR,	NULL_PTR,	NULL_PTR,	NULL_PTR,	NULL_PTR}
};
CONST(Dcm_2F_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2F_Dispatcher =
{
	Dcm_2F_ServiceInfo,
};
#endif/* STD_ON == DCM_SERVICE_2F_ENABLED */

 
#if (STD_ON == DCM_SERVICE_31_ENABLED)
CONST(Dcm_31_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_31_ServiceInfo[DCM_31_SUBID_NUM + 1] =
{
	{0xFF00U,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,	{0x00000004U, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{1U, 1U},	{0U, 0U},	{0U, 0U},	Dcm_31_0xFF00_Start,	Dcm_31_0xFF00_Stop,	Dcm_31_0xFF00_RequestResult,	NULL_PTR},
	{0xFF01U,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,	{0x00000004U, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0U, 1U},	{0U, 0U},	{0U, 0U},	Dcm_31_0xFF01_Start,	Dcm_31_0xFF01_Stop,	Dcm_31_0xFF01_RequestResult,	NULL_PTR},
	{0x0203U,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,	{0x00000004U, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},	{0U, 0U},	{0U, 0U},	{0U, 0U},	Dcm_31_0x0203_Start,	Dcm_31_0x0203_Stop,	Dcm_31_0x0203_RequestResult,	NULL_PTR},
	{0xFFFFU,	DCM_PHY_FUN,	TRUE,	DCM_31_SIGNAL_TYPE_FIXED,		{0x7FFFFFFFU, 0x7FFFFFFFU}, 	{0x0U, NULL_PTR}, 	{0x0U, NULL_PTR},	{0x0U, NULL_PTR},  {0U, 0U},	{0U, 0U},	{0U, 0U},	NULL_PTR,	NULL_PTR,	NULL_PTR,	NULL_PTR}
};
CONST(Dcm_31_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_31_Dispatcher =
{
	Dcm_31_ServiceInfo,
};
#endif/* STD_ON == DCM_SERVICE_31_ENABLED */

 
#if (STD_ON == DCM_SERVICE_3E_ENABLED)
CONST(Dcm_3E_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_3E_ServiceInfo[DCM_3E_SUBID + 1] =
{
	{0x00U,	DCM_PHY_FUN,	1U,	{0x0000000DU, 0x7FFFFFFFU},	NULL_PTR},
	{0x80U,	DCM_PHY_FUN,	1U,	{0x0000000DU, 0x7FFFFFFFU},	NULL_PTR},
	{0xFFU,	DCM_PHY_FUN,	1U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	NULL_PTR}
};
CONST(Dcm_3E_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_3E_Dispatcher =
{
	Dcm_3E_ServiceInfo,
};
#endif/* STD_ON == DCM_SERVICE_3E_ENABLED */

 
#if (STD_ON == DCM_SERVICE_85_ENABLED)
CONST(Dcm_85_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_85_ServiceInfo[DCM_85_SUBID_NUM + 1] =
{
	{0x01U,	DCM_PHY_FUN,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check85SubDtcSettingFunc},
	{0x02U,	DCM_PHY_FUN,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check85SubDtcSettingFunc},
	{0x81U,	DCM_PHY_FUN,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check85SubDtcSettingFunc},
	{0x82U,	DCM_PHY_FUN,	{0x0000000CU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Check85SubDtcSettingFunc},
	{0xFFU,	DCM_PHY_FUN,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},   NULL_PTR}
};
CONST(Dcm_85_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_85_Dispatcher =
{
	Dcm_85_ServiceInfo
};
#endif/* STD_ON == DCM_SERVICE_85_ENABLED */

 
#if (STD_ON == DCM_SERVICE_87_ENABLED)
CONST(Dcm_87_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_87_ServiceInfo[DCM_87_SUBID_NUM + 1] =
{
	{0x01U,	DCM_PHY_FUN,	0x01U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Dsp_8701_Process,	Dcm_LinkControl_01_02_03},
	{0x02U,	DCM_PHY_FUN,	0x03U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Dsp_8702_Process,	Dcm_LinkControl_01_02_03},
	{0x03U,	DCM_PHY_FUN,	0x00U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Dsp_8703_Process,	Dcm_LinkControl_01_02_03},
	{0x81U,	DCM_PHY_FUN,	0x01U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Dsp_8701_Process,	Dcm_LinkControl_01_02_03},
	{0x82U,	DCM_PHY_FUN,	0x03U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Dsp_8702_Process,	Dcm_LinkControl_01_02_03},
	{0x83U,	DCM_PHY_FUN,	0x00U,	{0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},	Dcm_Dsp_8703_Process,	Dcm_LinkControl_01_02_03},
	{0xFFU,	DCM_PHY_FUN, 0x00U, {0x7FFFFFFFU, 0x7FFFFFFFU},	{0x0U, NULL_PTR},  NULL_PTR,  NULL_PTR}
};
CONST(Dcm_87_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_87_Dispatcher =
{
	Dcm_87_ServiceInfo
};
#endif/* STD_ON == DCM_SERVICE_87_ENABLED */

CONST(Dcm_DspMemoryInfoType_st, DCM_CONFIG_DATA) Dcm_DspReadMemoryInfo[DCM_DSP_READMEMORY_NUM + 1] = 
{
	{ 0U, 0U, {0x7FFFFFFFU, 0x7FFFFFFFU}, NULL_PTR }
};

CONST(Dcm_DspMemoryInfoType_st, DCM_CONFIG_DATA) Dcm_DspWriteMemoryInfo[DCM_DSP_WRITEMEMORY_NUM + 1] = 
{
	{ 0xFC0000U, 0x167FFFFU, {0x7FFFFFFFU, 0x7FFFFFFFU}, Dcm_WriteMemoryRangeCheckRule_J2fvKS },
	{ 0U, 0U, {0x7FFFFFFFU, 0x7FFFFFFFU}, NULL_PTR }
};

#if (STD_ON == DCM_SERVICE_2A_ENABLED)
	
CONST(Dcm_2A_Channel_st, DCM_CONFIG_DATA) Dcm_2A_Channel[DCM_2A_TX_CHANNEL_NUM + 1U] = 
{
	{
		0xFFFFU,
		0xFFFFU,
	}
};


	
CONST(Dcm_2A_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2A_ServiceInfo[DCM_2A_NUM_DIDS + 1U] = 
{
	{
		0xFFFFU,
		FALSE,
		0xFFU,
		USE_DATA_SYNCH_FNC,
		{0x7FFFFFFFU, 0x7FFFFFFFU},
		{0x0U, NULL_PTR},
		{NULL_PTR, NULL_PTR},
		NULL_PTR,
		{NULL_PTR, NULL_PTR},
		NULL_PTR
	}
};

CONST(Dcm_2A_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2A_Dispatcher =
{
     Dcm_2A_ServiceInfo
};
#endif/* STD_ON == DCM_SERVICE_2A_ENABLED */

 
#if (STD_ON == DCM_SERVICE_2C_ENABLED)
CONST(uint8, DCM_CONFIG_DATA) Dcm_2C_SubFunc[DCM_2C_SUB_NUM_DIDS] =
{
	0x01U,
	0x02U,
	0x03U
};
CONST(Dcm_2C_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_2C_ServiceInfo[DCM_2C_NUM_DIDS + 1U] ={
	{0xFFFFU, 1U, {0x7FFFFFFFU,0x7FFFFFFFU}, {0x0U, NULL_PTR},   NULL_PTR, NULL_PTR}
};
CONST(Dcm_2C_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_2C_Dispatcher =
{
	Dcm_2C_SubFunc,
	Dcm_2C_ServiceInfo
};
#endif /* STD_ON == DCM_SERVICE_2C_ENABLED */

#if (STD_ON == DCM_SERVICE_86_ENABLED)
#endif /* STD_ON == DCM_SERVICE_86_ENABLED */

#if (STD_ON == DCM_SERVICE_29_ENABLED)

CONST(Dcm_29_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_29_Dispatcher =
{
     Dcm_29_ServiceInfo
};

CONST(Dcm_29_AutConn_st, DCM_CONFIG_DATA) Dcm_29_AutConn[DCM_29_AUT_CONN_NUM + 1] = 
{
    {
      /*Dcm_CertVerfCallNotifyRef      = */ FALSE,
      /*Dcm_RandSeedCallNotifyRef      = */ FALSE,
      /*Dcm_SignatureGenerateNotifyRef = */ FALSE,
      /*Dcm_SignatureVerifyNotifyRef   = */ FALSE,
      /*Dcm_EcuChallengeLength         = */ 0xFFFFU,
      /*Dcm_ClientCertIdx              = */ 0xFFFFU,
      /*Dcm_ConnectionCertIdx          = */ 0xFFFFU,
      /*Dcm_ConnectionMainConnectionIdx= */ 0xFFFFU,
      /*Dcm_ECUCertificateKeyElmtIdx   = */ 0xFFFFU,
      /*Dcm_ECUCertificateIdx          = */ 0xFFFFU,
      /*Dcm_PublicKeyElmtIdx           = */ 0xFFFFU,
      /*Dcm_RoleElmtIdx                = */ 0xFFFFU,
      /*Dcm_WLDIDElmtIdx               = */ 0xFFFFU,
      /*Dcm_WLMemorySelectionElmtIdx   = */ 0xFFFFU,
      /*Dcm_WLRIDElmntIdx              = */ 0xFFFFU,
      /*Dcm_WLServicesElementIdx       = */ 0xFFFFU,
      /*Dcm_CertPublicKeyStoreJobIdx   = */ 0xFFFFFFFFU,
      /*Dcm_ClientChallengeSignJobIdx  = */ 0xFFFFFFFFU,
      /*Dcm_RandomJobIdx               = */ 0xFFFFFFFFU,
      /*Dcm_VerifyPOWNJobIdx           = */ 0xFFFFFFFFU,
      /*Dcm_CheckRuleRef               = */ NULL_PTR
    }
};

CONST(Dcm_29_AutTransCert_st, DCM_CONFIG_DATA) Dcm_29_AutTransCert[DCM_29_AUT_TRANSCERT_NUM + 1] = 
{
    {
        0xFFFFU,
        0xFFFFU,
        NULL_PTR
    }
};
#endif /* STD_ON == DCM_SERVICE_29_ENABLED */

#if (STD_ON == DCM_SERVICE_38_ENABLED)
CONST(Dcm_38_ServiceInfoType_st, DCM_CONFIG_DATA) Dcm_38_ServiceInfo[DCM_38_SUBID_NUM + 1U] =
{
};

CONST(Dcm_38_DispatherInfo_st, DCM_CONFIG_DATA) Dcm_38_Dispatcher =
{
     Dcm_38_ServiceInfo
};
#endif/* STD_ON == DCM_SERVICE_38_ENABLED */

#if ( STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED )
CONST(Dcm_ServiceRequestManufacturerNotification_st, DCM_CONFIG_DATA) Dcm_ServiceRequestManufacturerNotification =
{
    {
        NULL_PTR
    },
    {
        NULL_PTR
    }
};
#endif /* STD_ON == DCM_REQUESTMANUFACTURERNOTIFICATION_ENABLED */

#if ( STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED )
CONST(Dcm_ServiceRequestSupplierNotification_st, DCM_CONFIG_DATA) Dcm_ServiceRequestSupplierNotification = 
{
    {
        NULL_PTR
    },
    {
        NULL_PTR
    }
};
#endif /* STD_ON == DCM_REQUESTSUPPLIERNOTIFICATION_ENABLED */

#define DCM_STOP_SEC_CONFIG_DATA
#include "Dcm_MemMap.h"

