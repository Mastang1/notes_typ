/**
*   @file    Lin_43_LLCE_PBcfg.c
*   @implements Lin_PBcfg.c_Artifact
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
#include "Lin_43_LLCE_Cfg.h"

#if (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Lin[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_PBcfg.c
*/
#define LIN_43_LLCE_VENDOR_ID_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C                      43

#define LIN_43_LLCE_AR_RELEASE_MAJOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C       4
#define LIN_43_LLCE_AR_RELEASE_MINOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C       4
#define LIN_43_LLCE_AR_RELEASE_REVISION_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C    0

#define LIN_43_LLCE_SW_MAJOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C               1
#define LIN_43_LLCE_SW_MINOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C               0
#define LIN_43_LLCE_SW_PATCH_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C               10

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
[!NOCODE!][!//
[!INCLUDE "Lin_43_LLCE_VersionCheck_Src_PB.m"!][!//
[!ENDNOCODE!][!//
/* Check if current file and LIN header file are of the same vendor */
#if (LIN_43_LLCE_VENDOR_ID_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != LIN_43_LLCE_CFG_VENDOR_ID)
    #error "Lin_43_LLCE[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_PBcfg.c and Lin_43_LLCE_Cfg.h have different vendor ids"
#endif
/* Check if current file and LIN header file are of the same Autosar version */
#if ((LIN_43_LLCE_AR_RELEASE_MAJOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C    != LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_43_LLCE_AR_RELEASE_MINOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C    != LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION) || \
     (LIN_43_LLCE_AR_RELEASE_REVISION_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != LIN_43_LLCE_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Lin_43_LLCE[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_PBcfg.c and Lin_43_LLCE_Cfg.h are different"
#endif
/* Check if current file and LIN header file are of the same Software version */
#if ((LIN_43_LLCE_SW_MAJOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != LIN_43_LLCE_CFG_SW_MAJOR_VERSION) || \
     (LIN_43_LLCE_SW_MINOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != LIN_43_LLCE_CFG_SW_MINOR_VERSION) || \
     (LIN_43_LLCE_SW_PATCH_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != LIN_43_LLCE_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lin_43_LLCE[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_PBcfg.c and Lin_43_LLCE_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((LIN_43_LLCE_AR_RELEASE_MAJOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != STD_AR_RELEASE_MAJOR_VERSION) || \
         (LIN_43_LLCE_AR_RELEASE_MINOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Lin_43_LLCE[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_PBcfg.c and Std_Types.h are different"
    #endif

    #if (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        /* Check if current file and Dem.h header file are of the same Autosar version */
        #if ((LIN_43_LLCE_AR_RELEASE_MAJOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
             (LIN_43_LLCE_AR_RELEASE_MINOR_VERSION_PBCFG[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_C != DEM_AR_RELEASE_MINOR_VERSION) \
            )
            #error "AutoSar Version Numbers of Lin_43_LLCE[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]_PBcfg.c and Dem.h are different"
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

#define LIN_43_LLCE_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Lin_43_LLCE_MemMap.h"

[!NOCODE!][!//
[!VAR "LFDIV"="0"!][!//
[!VAR "temp1" = "0"!][!//
[!VAR "temp2" = "0"!][!//
[!VAR "LINIBRR" = "0"!][!//
[!VAR "LINFBRR" = "0"!][!//
[!VAR "LINIBRR_LINFBRR" = "0"!][!//
[!VAR "BrkLengthSlave" = "0"!][!//
[!ENDNOCODE!][!//

[!LOOP "LinGlobalConfig/LinChannel/*"!][!//
/**
* @brief          Configuration for Lin Channel [!"LinChannelId"!]
*
* @api
*/

const Lin_43_LLCE_ChannelConfigType Lin_43_LLCE_[!"node:name(.)"!][!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]=
{
    &Lin_43_LLCE_[!"node:name(.)"!]_PC,
[!NOCODE!][!//
    [!VAR "linBaudrate" = "LinChannelBaudRate"!]
    [!SELECT "node:ref(LinClockRef)"!]
    [!INCLUDE "Lin_43_LLCE_BaudRate_Comp.m"!][!//
    [!ENDSELECT!]
[!ENDNOCODE!][!//
    [!"$LINIBRR_LINFBRR"!]U,    /* Baudrate [!"LinChannelBaudRate"!] */
[!NOCODE!][!//
    [!VAR "IntegerBrkLength" = "substring-after(BreakLengthMaster,'_')"!]
    [!IF "$IntegerBrkLength = 36"!]
        [!VAR "VarBreakLength"="14"!]
    [!ELSEIF "$IntegerBrkLength = 50"!]
        [!VAR "VarBreakLength"="15"!]
    [!ELSE!]
        [!VAR "VarBreakLength"="$IntegerBrkLength - 10"!]
    [!ENDIF!]
    [!VAR "BrkLengthSlave" = "11 - num:i(substring-after(BreakLengthSlave,'_'))"!]
[!ENDNOCODE!][!//
    [!CODE!][!//
    [!"num:i($VarBreakLength)"!]U, /* BreakLengthMaster = [!"BreakLengthMaster"!] bits */
    [!"num:i($BrkLengthSlave)"!]U, /* BreakLengthSlave = [!"BreakLengthSlave"!] bits */
    [!"num:i(LinResponseTimeout)"!]U, /* Response timeout value LINTOCR[RTO] */
    [!"num:i(LinHeaderTimeout)"!]U  /* Header timeout value LINTOCR[HTO] */
    [!ENDCODE!][!//
};
[!ENDLOOP!][!//

[!NOCODE!]
[!CODE!][!//
/**
* @brief          Lin Configuration data for [!"as:name(./LinGlobalConfig)"!].
*
* @api
*/
[!IF "(IMPLEMENTATION_CONFIG_VARIANT = 'VariantPreCompile') and (variant:size() <= 1)"!]
const Lin_43_LLCE_ConfigType Lin_43_LLCE_Config =
[!ELSE!]
const Lin_43_LLCE_ConfigType Lin_43_LLCE_Config[!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!] =
[!ENDIF!]
{
    {
[!ENDCODE!]
[!VAR "count"="0"!]
[!VAR "MaxChannelNr" = "num:i(count(LinGlobalConfig/LinChannel/*))"!]
[!FOR "count" = "0" TO "$MaxChannelNr - 1"!]
        [!LOOP "LinGlobalConfig/LinChannel/*"!]
            [!IF "$count = num:i(LinChannelId)"!]
                [!CODE!]
        /**
        * @brief   Configuration for Lin Channel [!"LinChannelId"!].
        */
                [!ENDCODE!]
                [!IF "$count > $MaxChannelNr - 2"!]
                    [!CODE!]
        &Lin_43_LLCE_[!"node:name(.)"!][!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!]
                    [!ENDCODE!]
                [!ELSE!]
                    [!CODE!]
        &Lin_43_LLCE_[!"node:name(.)"!][!IF "var:defined('postBuildVariant')"!]_[!"$postBuildVariant"!][!ENDIF!],
                    [!ENDCODE!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDLOOP!]
[!ENDFOR!]
[!CODE!]
    }
};
[!ENDCODE!]
[!ENDNOCODE!]


#define LIN_43_LLCE_STOP_SEC_CONFIG_DATA_UNSPECIFIED
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
