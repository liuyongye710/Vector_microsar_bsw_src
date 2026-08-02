/*
********************************************************************************
*
* File name: Rte_KeyM_Type.h
*
* Copyright 2018-2024 Neusoft Reach Corporation. All rights reserved.
*
********************************************************************************
*
*  History
*-------------------------------------------------------------------------------
********************************************************************************
* Version: 1.0
* Author/Date : yong.zhang/2020.06.19
* Change: New created
* Cause: New
********************************************************************************
*/
#ifndef RTE_KEYM_TYPE_H_
#define RTE_KEYM_TYPE_H_

/*
********************************************************************************
*    Includes
********************************************************************************
*/
#include "Std_Types.h"

/*
********************************************************************************
*    Global Macros
********************************************************************************
*/

/*
********************************************************************************
*    Global Types
********************************************************************************
*/
/* [SWS_KeyM_00300] Certificate Element handle. */
#ifndef Rte_TypeDef_KeyM_CertElementIdType
#define Rte_TypeDef_KeyM_CertElementIdType
typedef uint16 KeyM_CertElementIdType;
#endif

/* [SWS_KeyM_00302] Crypto key handle. */
#ifndef Rte_TypeDef_KeyM_CertificateIdType
#define Rte_TypeDef_KeyM_CertificateIdType
typedef uint16 KeyM_CertificateIdType;
#endif

/* [SWS_KeyM_91003] Enumeration of the result type of verification operations. */
#ifndef Rte_TypeDef_KeyM_CertificateStatusType
#define Rte_TypeDef_KeyM_CertificateStatusType
typedef enum
{
    KEYM_CERTIFICATE_VALID = 0x00U,
    KEYM_CERTIFICATE_INVALID = 0x01U,
    KEYM_CERTIFICATE_NOT_PARSED = 0x02U,
    KEYM_CERTIFICATE_PARSED_NOT_VALIDATED = 0x03U,
    KEYM_CERTIFICATE_NOT_AVAILABLE = 0x04U,
    KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL = 0x05U,
    KEYM_E_CERTIFICATE_SIGNATURE_FAIL = 0x06U,
    KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST = 0x07U,
    KEYM_E_CERTIFICATE_INVALID_TYPE = 0x08U,
    KEYM_E_CERTIFICATE_INVALID_FORMAT = 0x09U,
    KEYM_E_CERTIFICATE_INVALID_CONTENT = 0x0AU,
    KEYM_E_CERTIFICATE_REVOKED = 0X0BU,
    
    KEYM_CERTIFICATE_PARSED_IN_VALIDATING = 0x0CU,   /* neusar extend */
}KeyM_CertificateStatusType;
#endif

/* [SWS_KeyM_00038] This type specifies in which mode the key operation will start. The OEM production 
mode provides higher privileges compared to workshop mode. */
#ifndef Rte_TypeDef_KeyM_StartType
#define Rte_TypeDef_KeyM_StartType
typedef enum
{
    KEYM_START_OEM_PRODUCTIONMODE = 0x01,
    KEYM_START_WORKSHOPMODE = 0x02
}KeyM_StartType;
#endif

/* [SWS_KeyM_00039] This type specifies the requested service operation and what information is provided with this function. */
#ifndef Rte_TypeDef_KeyM_ServiceCertificateType
#define Rte_TypeDef_KeyM_ServiceCertificateType
typedef enum
{
    KEYM_SERVICE_CERT_REQUEST_CSR = 0x01,
    KEYM_SERVICE_CERT_UPDATE_SIGNED_CSR = 0x02,
    KEYM_SERVICE_CERT_SET_ROOT = 0x03,
    KEYM_SERVICE_CERT_UPDATE_ROOT = 0x04,
    KEYM_SERVICE_CERT_SET_INTERMEDIATE = 0x05,
    KEYM_SERVICE_CERT_UPDATE_INTERMEDIATE = 0x06,
    KEYM_SERVICE_CERT_UPDATE_CRL = 0x07
}KeyM_ServiceCertificateType;
#endif

/* SWS_KeyM_91008 */
#ifndef Rte_TypeDef_KeyM_ResultType
#define Rte_TypeDef_KeyM_ResultType
typedef enum
{
    KEYM_RT_OK = 0x00U,
    KEYM_RT_NOT_OK  = 0x01U,
    KEYM_RT_KEY_CERT_INVALID = 0x02U,
    KEYM_RT_KEY_CERT_WRITE_FAIL = 0x03U,
    KEYM_RT_KEY_CERT_UPDATE_FAIL = 0x04U,
    KEYM_RT_CERT_INVALID_CHAIN_OF_TRUST = 0x05U
}KeyM_ResultType;
#endif
/*
********************************************************************************
*    Global variables
********************************************************************************
*/
/*
********************************************************************************
*    Global Constants
********************************************************************************
*/
/*
********************************************************************************
*    Global Functions
********************************************************************************
*/

#endif  /* RTE_KEYM_TYPE_H_ */

