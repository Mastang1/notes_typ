/**
*   @file    Lin_43_LLCE_Cfg.c
*   @implements Lin_Cfg.c_Artifact
*   @version 1.0.10
*
*   @brief   AUTOSAR Lin_43_LLCE - Brief file description (one line).
*   @details Detailed file description (can be multiple lines).
*
*   @addtogroup LIN_LLCE
*   @{
*/
/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : LLCE
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.10
*   Build Version        : S32_RTD_1_0_10_D2505_ASR_REL_4_4_REV_0000_20250516
*
*   Copyright 2006-2016 Freescale Semiconductor, Inc.
*   Copyright 2020-2025 NXP
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be used strictly in
*   accordance with the applicable license terms.
*   By expressly accepting such terms or by downloading, installing, activating and/or otherwise using
*   the software, you are agreeing that you have read, and that you agree to comply with and are bound
*   by, such license terms.  If you do not agree to be bound by the applicable license terms, then you
*   may not retain, install, activate or otherwise use the software.
==================================================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Mcal.h"
#include "Lin_43_LLCE_Cfg.h"

#if (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Lin_43_LLCE_Cfg.c
*/
#define LIN_43_LLCE_CFG_VENDOR_ID_C                      43
#define LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION_C       4
#define LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION_C       4
#define LIN_43_LLCE_CFG_AR_RELEASE_REVISION_VERSION_C    0
#define LIN_43_LLCE_CFG_SW_MAJOR_VERSION_C               1
#define LIN_43_LLCE_CFG_SW_MINOR_VERSION_C               0
#define LIN_43_LLCE_CFG_SW_PATCH_VERSION_C               10

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
[!NOCODE!][!//
[!INCLUDE "Lin_43_LLCE_VersionCheck_Src.m"!][!//
[!ENDNOCODE!][!//
/* Check if current file and Lin_43_LLCE_Cfg.h header file are of the same Autosar version */
#if (LIN_43_LLCE_CFG_VENDOR_ID_C != LIN_43_LLCE_CFG_VENDOR_ID)
    #error "Lin_43_LLCE_Cfg.c and Lin_43_LLCE_Cfg.h have different vendor ids"
#endif
#if ((LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION_C    != LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION_C    != LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION) || \
     (LIN_43_LLCE_CFG_AR_RELEASE_REVISION_VERSION_C != LIN_43_LLCE_CFG_AR_RELEASE_REVISION_VERSION) \
    )
  #error "AutoSar Version Numbers of Lin_43_LLCE_Cfg.c and Lin_43_LLCE_Cfg.h are different"
#endif
/* Check if current file and Lin_43_LLCE_Cfg.h header file are of the same Software version */
#if ((LIN_43_LLCE_CFG_SW_MAJOR_VERSION_C != LIN_43_LLCE_CFG_SW_MAJOR_VERSION) || \
     (LIN_43_LLCE_CFG_SW_MINOR_VERSION_C != LIN_43_LLCE_CFG_SW_MINOR_VERSION) || \
     (LIN_43_LLCE_CFG_SW_PATCH_VERSION_C != LIN_43_LLCE_CFG_SW_PATCH_VERSION) \
    )
  #error "Software Version Numbers of Lin_43_LLCE_Cfg.c and Lin_43_LLCE_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  #if ((LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
       (LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION) \
      )
    #error "AutoSar Version Numbers of Lin_43_LLCE_Cfg.c and Std_Types.h are different"
  #endif
  #if (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    /* Check if current file and Dem.h header file are of the same Autosar version */
    #if ((LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Lin_43_LLCE_Cfg.c and Dem.h are different"
    #endif
  #endif /* (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
#define LIN_43_LLCE_START_SEC_CONST_UNSPECIFIED
#include "Lin_43_LLCE_MemMap.h"

[!NOCODE!][!//
[!LOOP "LinGlobalConfig/LinChannel/*"!][!//
    [!CODE!]
const Lin_43_LLCE_StaticConfig_ChannelConfigType Lin_43_LLCE_[!"node:name(.)"!]_PC=
{
    (uint8)[!"LinChannelId"!]U,     /* Lin Channel ID */
    [!"LinHwChannel"!],             /* Lin Hardware Channel */
    [!IF "contains(node:value(LinNodeType), 'MASTER')"!][!//
    LLCE_LIN_MASTER_NODE,                /* Lin Master Node */
    [!ELSE!][!//
    LLCE_LIN_SLAVE_NODE,                 /* Lin Slave Node */
    [!ENDIF!][!//
    [!IF "LinChannelWakeupSupport"!][!//
    (uint8)STD_ON,                 /* Wakeup support enabled */
    [!ELSE!][!//
    (uint8)STD_OFF,                /* Wakeup support disabled */
    [!ENDIF!][!//
    [!IF "LinChannelDisableFrameTimeout"!][!//
    (uint8)STD_ON,                 /* Disable frame timeout */
    [!ELSE!][!//
    (uint8)STD_OFF,                /* Disable frame timeout */
    [!ENDIF!][!//
    [!IF "(node:exists(LinChannelEcuMWakeupSource) = 'true') and (node:value(LinChannelEcuMWakeupSource) != '')"!][!//
    (EcuM_WakeupSourceType)((uint32)1U<<(uint32)[!"as:ref(LinChannelEcuMWakeupSource)/EcuMWakeupSourceId"!]U) /* Wakeup Source transmitted to the Ecu State Manager (used only when Wakeup Support is true) */
    [!ELSE!][!//
    (EcuM_WakeupSourceType)LIN_43_LLCE_NONE_ECUM_WAKEUP_SOURCE_REF /* None Wakeup Source was referred */
    [!ENDIF!][!//
};
    [!ENDCODE!]
[!ENDLOOP!][!//

[!CODE!]
#if (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
 * @brief   DEM error parameters
 */
const Mcal_DemErrorType Lin_43_LLCE_E_TimeoutCfg =
{
[!ENDCODE!]

[!VAR "LinDemErrorEnable" = "'false'"!]
[!IF "AutosarExt/LinDisableDemReportErrorStatus ='false'"!][!//
    [!IF "node:exists(LinDemEventParameterRefs)"!]
        [!VAR "LinDemErrorEnable" = "'true'"!]
    [!ENDIF!]
[!ENDIF!]

[!IF "$LinDemErrorEnable"!]
    [!IF "node:exists(LinDemEventParameterRefs/LIN_E_TIMEOUT)"!]
        [!IF "node:exists(node:value(LinDemEventParameterRefs/LIN_E_TIMEOUT))"!]
            [!CODE!]
    (uint32)STD_ON,
    DemConf_DemEventParameter_[!"node:name(node:ref(LinDemEventParameterRefs/LIN_E_TIMEOUT))"!]
            [!ENDCODE!]
        [!ELSE!]
            [!ERROR "Invalid reference for LIN_E_ERROR"!]
        [!ENDIF!]
    [!ELSE!]
        [!CODE!]
    (uint32)STD_OFF,
    0U
        [!ENDCODE!]
    [!ENDIF!]
[!ELSE!]
    [!CODE!]
    (uint32)STD_OFF,
    0U
    [!ENDCODE!]
[!ENDIF!]

[!CODE!]
};
#endif /* LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF */
[!ENDCODE!]
[!ENDNOCODE!][!//

#define LIN_43_LLCE_STOP_SEC_CONST_UNSPECIFIED
#include "Lin_43_LLCE_MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
