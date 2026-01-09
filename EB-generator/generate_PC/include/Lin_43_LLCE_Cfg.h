/**
*   @file    Lin_43_LLCE_Cfg.h
*   @version 1.0.10
*
*   @brief   AUTOSAR Lin_43_LLCE - High level header of LIN driver.
*   @details This file contains declarations of the functions defined by AutoSAR.
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

#ifndef LIN_43_LLCE_CFG_H
#define LIN_43_LLCE_CFG_H

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
[!NOCODE!]
[!// check for duplicated channel id, or hw channel id
    [!VAR "tmp_ch_id" = "-1"!]
    [!VAR "tmp_hw_ch" = "-1"!]
    [!VAR "tmp_channel_index" = "0"!]
    [!VAR "max_channel_nr" = "count(LinChannel/*)"!]
    [!LOOP "LinChannel/*"!]
        [!VAR "i" = "0"!]
        [!VAR "tmp_channel_index" = "$tmp_channel_index + 1"!]
        [!VAR "tmp_ch_id" = "LinChannelId"!]
        [!VAR "tmp_hw_ch" = "substring-after(LinHwChannel,'_')"!]
        [!FOR "i" = "$tmp_channel_index + 1" TO "$max_channel_nr"!]
            [!IF "$tmp_ch_id = ../*[num:i($i)]/LinChannelId"!]
                [!ERROR!] Duplicate LinChannelId.[!ENDERROR!]
            [!ENDIF!]
            [!IF "$tmp_hw_ch = substring-after(../*[num:i($i)]/LinHwChannel,'_')"!]
                [!ERROR!] Duplicate LinHwChannel IDs.[!ENDERROR!]
            [!ENDIF!]
        [!ENDFOR!]
    [!ENDLOOP!]
[!// end check for duplicated channel id, or hw channel id
[!CODE!][!//
#include "EcuM_Externals.h"
[!ENDCODE!][!//
[!ENDNOCODE!][!//
#include "Mcal.h"
[!IF "var:defined('postBuildVariant')"!][!//
[!LOOP "variant:all()"!][!//
#include "Lin_43_LLCE_[!"."!]_PBcfg.h"
[!ENDLOOP!][!//
[!ELSE!][!//
#include "Lin_43_LLCE_PBcfg.h"
[!ENDIF!][!//
#include "Llce_InterfaceLinTypes.h"
#include "OsIf.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Lin_43_LLCE_Cfg.h
*/
[!NOCODE!][!//
[!INCLUDE "Lin_43_LLCE_VersionCheck_Inc.m"!][!//
[!ENDNOCODE!][!//

/* Inclusion of incompatible header files shall be avoided */

#define LIN_43_LLCE_CFG_VENDOR_ID                    43
#define LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION     4
#define LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION     4
#define LIN_43_LLCE_CFG_AR_RELEASE_REVISION_VERSION  0
#define LIN_43_LLCE_CFG_SW_MAJOR_VERSION             1
#define LIN_43_LLCE_CFG_SW_MINOR_VERSION             0
#define LIN_43_LLCE_CFG_SW_PATCH_VERSION             10
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
[!NOCODE!]
[!IF "var:defined('postBuildVariant')"!]
[!LOOP "variant:all()"!]
[!CODE!][!//
/* Checks against Lin_[!"."!]_PBcfg.h */
#if (LIN_43_LLCE_CFG_VENDOR_ID != LIN_43_LLCE_[!"."!]_PBCFG_VENDOR_ID)
    #error "Lin_Cfg.h and Lin_[!"."!]_PBcfg.h have different vendor ids"
#endif
#if ((LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION    != LIN_43_LLCE_[!"."!]_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION    != LIN_43_LLCE_[!"."!]_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (LIN_43_LLCE_CFG_AR_RELEASE_REVISION_VERSION != LIN_43_LLCE_[!"."!]_PBCFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Lin_Cfg.h and Lin_[!"."!]_PBcfg.h are different"
#endif
#if ((LIN_43_LLCE_CFG_SW_MAJOR_VERSION != LIN_43_LLCE_[!"."!]_PBCFG_SW_MAJOR_VERSION) || \
     (LIN_43_LLCE_CFG_SW_MINOR_VERSION != LIN_43_LLCE_[!"."!]_PBCFG_SW_MINOR_VERSION) || \
     (LIN_43_LLCE_CFG_SW_PATCH_VERSION != LIN_43_LLCE_[!"."!]_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lin_Cfg.h and Lin_[!"."!]_PBcfg.h are different"
#endif
[!ENDCODE!]
[!ENDLOOP!]
[!ELSE!]
[!CODE!][!//
/* Checks against Lin_PBcfg.h */
#if (LIN_43_LLCE_CFG_VENDOR_ID != LIN_43_LLCE_PBCFG_VENDOR_ID)
    #error "Lin_Cfg.h and Lin_PBcfg.h have different vendor ids"
#endif
#if ((LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION    != LIN_43_LLCE_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION    != LIN_43_LLCE_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (LIN_43_LLCE_CFG_AR_RELEASE_REVISION_VERSION != LIN_43_LLCE_PBCFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Lin_Cfg.h and Lin_PBcfg.h are different"
#endif
#if ((LIN_43_LLCE_CFG_SW_MAJOR_VERSION != LIN_43_LLCE_PBCFG_SW_MAJOR_VERSION) || \
     (LIN_43_LLCE_CFG_SW_MINOR_VERSION != LIN_43_LLCE_PBCFG_SW_MINOR_VERSION) || \
     (LIN_43_LLCE_CFG_SW_PATCH_VERSION != LIN_43_LLCE_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lin_Cfg.h and Lin_PBcfg.h are different"
#endif
[!ENDCODE!]
[!ENDIF!]
[!ENDNOCODE!]

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  /* Check if the source file and EcuM_Cbk header file are of the same version */
  #if ((LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION != ECUM_CBK_AR_RELEASE_MAJOR_VERSION) || \
       (LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION != ECUM_CBK_AR_RELEASE_MINOR_VERSION) \
      )
    #error "AutoSar Version Numbers of Lin_43_LLCE_Cfg.h and EcuM_Externals.h are different"
  #endif
  /* Check if current file and Mcal.h header file are of the same Autosar version */
    #if ((LIN_43_LLCE_CFG_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (LIN_43_LLCE_CFG_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Lin_43_LLCE_Cfg.h and Mcal.h are different"
    #endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
[!NOCODE!]
[!// check for duplicated channel id, or hw channel id
    [!VAR "tmp_ch_id" = "-1"!]
    [!VAR "tmp_hw_ch" = "-1"!]
    [!VAR "tmp_channel_index" = "0"!]
    [!VAR "max_channel_nr" = "count(LinChannel/*)"!]
    [!VAR "LinMasterNodeUsed"= "'false'"!]
    [!VAR "LinSlaveNodeUsed"= "'false'"!]

    [!LOOP "LinChannel/*"!]
        [!VAR "i" = "0"!]
        [!VAR "tmp_channel_index" = "$tmp_channel_index + 1"!]
        [!VAR "tmp_ch_id" = "LinChannelId"!]
        [!VAR "tmp_hw_ch" = "substring-after(LinHwChannel,'_')"!]
        [!FOR "i" = "$tmp_channel_index + 1" TO "$max_channel_nr"!]
            [!IF "$tmp_ch_id = ../*[num:i($i)]/LinChannelId"!]
                [!ERROR!] Duplicate LinChannelId.[!ENDERROR!]
            [!ENDIF!]
            [!IF "$tmp_hw_ch = substring-after(../*[num:i($i)]/LinHwChannel,'_')"!]
                [!ERROR!] Duplicate LinHwChannel IDs.[!ENDERROR!]
            [!ENDIF!]
        [!ENDFOR!]
    [!ENDLOOP!]

    [!LOOP "LinGlobalConfig/LinChannel/*"!][!//
        [!IF "contains(node:value(LinNodeType),'MASTER')"!]
            [!VAR "LinMasterNodeUsed"= "'true'"!]
        [!ENDIF!]
        [!IF "contains(node:value(LinNodeType),'SLAVE')"!]
            [!VAR "LinSlaveNodeUsed"= "'true'"!]
        [!ENDIF!]
    [!ENDLOOP!][!//

[!// end check for duplicated channel id, or hw channel id
[!ENDNOCODE!][!//

/**
* @brief   No of Channels configured.
*
*
* @api
*/
#define LIN_43_LLCE_HW_MAX_MODULES [!"num:i(count(LinGlobalConfig/LinChannel/*))"!]U

/**
* @brief          Lin Master Node Used
* @details        When LinGlobalConfig/LinChannel/LinNodeType contains at least one MASTER channel.
*
* @api
*/
#define LIN_43_LLCE_MASTER_NODE_USED [!IF "$LinMasterNodeUsed = 'true'"!](STD_ON) /* Used Master Node */ [!ELSE!] (STD_OFF) /* Not Used Master Node */ [!ENDIF!][!//

/**
* @brief          Lin Slave Node Used
* @details        When LinGlobalConfig/LinChannel/LinNodeType contains at least one SLAVE channel.
*
* @api
*/
#define LIN_43_LLCE_SLAVE_NODE_USED [!IF "$LinSlaveNodeUsed = 'true'"!](STD_ON) /* Used Slave Node */ [!ELSE!] (STD_OFF) /* Not Used Slave Node */ [!ENDIF!][!//

/**
* @brief   This will set the timer source for osif that will be used for timeout.
*
* @api
*/
#define  LIN_43_LLCE_SERVICE_TIMEOUT_TYPE    [!"LinGeneral/LinTimeoutMethod"!]

/**
* @brief   Number of loops before returning LIN_43_LLCE_E_TIMEOUT.
*
* @api
*/
#define  LIN_43_LLCE_TIMEOUT_DURATION ((uint32)[!"LinGeneral/LinTimeoutDuration"!]U)

/**
* @brief   Switches the Default Error Detection and Notification ON or OFF.
*
* @api
*/
#define LIN_43_LLCE_DEV_ERROR_DETECT [!IF "LinGeneral/LinDevErrorDetect"!](STD_ON) /* Enable Default Error Detection */[!ELSE!](STD_OFF) /* Disable Default Error Detection */[!ENDIF!]

/**
* @brief          Support for version info API.
* @details        Switches the Lin_43_LLCE_GetVersionInfo() API ON or OFF.
*
* @api
*/
#define LIN_43_LLCE_VERSION_INFO_API [!IF "LinGeneral/LinVersionInfoApi"!](STD_ON) /* Enable API Lin_43_LLCE_GetVersionInfo */[!ELSE!](STD_OFF) /* Disable API Lin_43_LLCE_GetVersionInfo */[!ENDIF!]

[!NOCODE!]
[!CODE!]
/**
* @brief          Link Lin channels symbolic names with Lin channel IDs.
* @details        Link Lin channels symbolic names with Lin channel IDs.
*
* @api
*/
[!ENDCODE!]
[!VAR "LinHwChannels" = "'LinHWCh_0 LinHWCh_1 LinHWCh_2 LinHWCh_3'"!][!//
[!FOR "index" = "0" TO "num:i(4)-1"!][!//
    [!VAR "MaxHwChannels" = "string(text:split($LinHwChannels)[$index+1])"!][!//
    [!VAR "ChannelFound" = "0"!][!//
    [!LOOP "LinGlobalConfig/LinChannel/*"!][!//
        [!VAR "HardwareChannel" = "string(LinHwChannel)"!][!//
        [!IF "$MaxHwChannels = $HardwareChannel"!][!//
            [!IF "$ChannelFound = 0"!][!//
                [!CODE!][!//

#define [!"$MaxHwChannels"!]    [!"substring-after(LinHwChannel,'_')"!]U[!//

                [!ENDCODE!][!//
                [!VAR "ChannelFound" = "1"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDFOR!][!//
[!ENDNOCODE!]

/**
* @brief          Symbolic names for configured channels.
* @details        Symbolic names for configured channels.
*
* @api
*/
[!LOOP "LinGlobalConfig/LinChannel/*"!][!//
#define LinConf_43_LLCE_LinChannelConfiguration_[!"node:name(.)"!]         [!"LinChannelId"!]
[!ENDLOOP!][!//

/**
* @brief   Switches the Production Error Detection and Notification OFF
*
* @api
*/
[!NOCODE!]
[!VAR "LinDemErrorEnable" = "'false'"!]
[!IF "AutosarExt/LinDisableDemReportErrorStatus ='false'"!][!//
    [!IF "node:exists(LinDemEventParameterRefs)"!]
        [!VAR "LinDemErrorEnable" = "'true'"!]
    [!ENDIF!]
[!ENDIF!]
[!ENDNOCODE!]

#define LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS [!IF "$LinDemErrorEnable"!](STD_OFF) /* Enable Production Error Detection */[!ELSE!](STD_ON) /* Disable Production Error Detection */[!ENDIF!]

#define LIN_43_LLCE_PRECOMPILE_SUPPORT [!IF "(IMPLEMENTATION_CONFIG_VARIANT = 'VariantPreCompile' or IMPLEMENTATION_CONFIG_VARIANT='VariantLinkTime') and (variant:size() <= 1)"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

[!NOCODE!][!//
[!VAR "EnableAllLinChannelEcuMWakeupSource"="'false'"!]
[!LOOP "LinGlobalConfig/LinChannel/*"!]
    [!IF "not(node:exists(LinChannelEcuMWakeupSource))"!]
        [!VAR "EnableAllLinChannelEcuMWakeupSource"="'true'"!]
    [!ENDIF!]
[!ENDLOOP!]
[!IF "$EnableAllLinChannelEcuMWakeupSource"!]
    [!CODE!]
/**
* @brief          None EcuMWakeUpSource was referrd when LinChannelWakeupSupport is disable
*/
#define LIN_43_LLCE_NONE_ECUM_WAKEUP_SOURCE_REF (uint32)0U
    [!ENDCODE!]
[!ENDIF!]
[!ENDNOCODE!][!//

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
[!IF "not(IMPLEMENTATION_CONFIG_VARIANT !='VariantPostBuild' and (variant:size()<=1))"!][!//
#define LIN_43_LLCE_CONFIG_EXT \
[!IF "var:defined('postBuildVariant')"!][!//
[!LOOP "variant:all()"!][!//
 LIN_43_LLCE_CONFIG_[!"."!]_PB \
[!ENDLOOP!][!//
[!ELSE!][!//
 LIN_43_LLCE_CONFIG_PB
[!ENDIF!]
[!ENDIF!]

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          LIN channel configuration type structure.
* @details        This is the type of the external data structure containing
*                 the overall initialization data for one LIN Channel.
*                 A pointer to such a structure is provided to the LIN channel
*                 initialization routine for configuration of the LIN hardware
*                 channel.
*
* @api
*/
typedef struct
{
    uint8 u8LinChannelID;                     /**< @brief Lin Channel ID */
    uint8 u8LinHwChannel;                     /**< @brief LIN Hardware Channel.*/
    const Llce_Lin_NodeType eLinNodeType;         /*!< @brief LIN Node Type.*/
    uint8 u8LinChannelWakeupSupport;          /**< @brief Is wake-up supported by the LIN channel ?.*/
    uint8 u8LinChannelDisableFrameTimeout;    /**< @brief Disable frame timeout for this channel.*/
    EcuM_WakeupSourceType LinChannelEcuMWakeupSource;    /**< @brief [LIN098] This parameter contains a reference to the Wakeup Source for this controller as defined in the ECU State Manager.*/
} Lin_43_LLCE_StaticConfig_ChannelConfigType;

/**
* @brief          LIN channel configuration type structure.
* @details        This is the type of the external data structure containing
*                 the overall initialization data for one LIN Channel.
*                 A pointer to such a structure is provided to the LIN channel
*                 initialization routine for configuration of the LIN hardware
*                 channel.
*
* @api
*/
typedef struct
{
    const Lin_43_LLCE_StaticConfig_ChannelConfigType * pChannelConfigPC;  /* @brief Pointer to precompile configuration structure */
    uint32 u32LinBaudRateRegValue;            /**< @brief LIN baudrate value.*/
    uint8 u8LinChannelBrkLengthMaster;        /*!< @brief These bits indicate the Break length in Master mode.*/
    uint8 u8LinChannelBrkLengthSlave;         /*!< @brief These bits indicate the Break length in Slave mode.*/
    uint8 u8ResponseTimeout;                  /*!< @brief Response timeout value LINTOCR[RTO].*/
    uint8 u8HeaderTimeout;                    /*!< @brief Header timeout value LINTOCR[HTO].*/
} Lin_43_LLCE_ChannelConfigType;

/**
* @brief          LIN driver configuration type structure.
* @details        This is the type of the pointer to the external data
*                 LIN Channels.
*                 A pointer of such a structure is provided to the LIN driver
*                 initialization routine for configuration of the LIN hardware
*                 channel.
*
* @api
*
* @implements Lin_ConfigType_struct
*/
typedef struct
{
    /**
     * @brief     Hardware channel.
     * @details   Constant pointer of the constant external data
     *            structure containing the overall initialization data
     *            for all the LIN Channels.
     */
    const Lin_43_LLCE_ChannelConfigType * const pLin_Channel[LIN_43_LLCE_HW_MAX_MODULES];
} Lin_43_LLCE_ConfigType;

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define LIN_43_LLCE_START_SEC_CONST_UNSPECIFIED
#include "Lin_43_LLCE_MemMap.h"

[!NOCODE!][!//
[!LOOP "LinGlobalConfig/LinChannel/*"!][!//
    [!CODE!][!//
extern const Lin_43_LLCE_StaticConfig_ChannelConfigType Lin_43_LLCE_[!"node:name(.)"!]_PC;
    [!ENDCODE!]
[!ENDLOOP!][!//
[!ENDNOCODE!][!//

#if (LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
extern const Mcal_DemErrorType Lin_43_LLCE_E_TimeoutCfg;
#endif /* LIN_43_LLCE_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF */

#define LIN_43_LLCE_STOP_SEC_CONST_UNSPECIFIED
#include "Lin_43_LLCE_MemMap.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                  EXTERNAL CONSTANTS
==================================================================================================*/

#endif /* LIN_43_LLCE_CFG_H */

#ifdef __cplusplus
}
#endif
