 
/*
********************************************************************************
*
* File name: SchM_CanIf.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
* History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 3.0
* Author/Date: Gaol/2022.6.14
* Change: New created.
* Cause: New
********************************************************************************
*/
/*
********************************************************************************
*    double include preventio and include files
********************************************************************************
*/
#ifndef SCHM_CANIF_H
#define SCHM_CANIF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "SchM_CanIf_Type.h"

/*
********************************************************************************
*    MainFuntion prototypes
********************************************************************************
*/
FUNC(void, CANIF_CODE) CanIf_MainFunction(void);

/*
********************************************************************************
*    Exclusive_area prototypes
********************************************************************************
*/
FUNC(void, RTE_CODE) SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0(void);

FUNC(void, RTE_CODE) SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0(void);


#ifdef __cplusplus
}
#endif

#endif /* SCHM_CANIF_H */

 
 
 
