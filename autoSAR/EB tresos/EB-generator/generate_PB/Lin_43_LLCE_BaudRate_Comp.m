[!/*
    @file    Lin_BaudRate_Comp.m
    @version 1.0.10

    @brief   AUTOSAR Lin_43_LLCE - Baud rate computation for Lin_Cfg.c, Lin_PBcfg.c.
    @details Baud rate computation for Lin_Cfg.c, Lin_PBcfg.c
    
    Project RTD AUTOSAR 4.4
    Patform CORTEXM
    Peripheral LLCE
    Dependencies 
    
    ARVersion 4.4.0
    ARRevision ASR_REL_4_4_REV_0000
    ARConfVariant
    SWVersion 1.0.10
    BuildVersion S32_RTD_1_0_10_D2505_ASR_REL_4_4_REV_0000_20250516

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
*/!]
[!VAR "ClockFrequencyFromMcu" = "McuClockReferencePointFrequency"!] /* LIN_BAUD_CLK */
    [!VAR "LFDIV" = "($ClockFrequencyFromMcu div ($linBaudrate * 16))"!][//
    [!VAR "temp1" = "num:i($LFDIV)"!][!//
    [!VAR "temp2" = "$LFDIV - $temp1"!][!//
    [!VAR "LINFBRR" = "round($temp2 * 16)"!][!//
    [!VAR "LINFBRR" = "num:inttohex($LINFBRR,8)"!][!//
    [!VAR "LINIBRR" = "num:inttohex($temp1,8)"!][!//
    [!VAR "LINIBRR" = "num:hextoint($LINIBRR)"!][!//
    [!VAR "LINFBRR" = "num:hextoint($LINFBRR)"!][!//
    [!VAR "LINIBRR" = "bit:shl($LINIBRR,8)"!][!//
    [!VAR "LINIBRR_LINFBRR" = "bit:or($LINIBRR,$LINFBRR)"!][!//
    [!VAR "LINIBRR_LINFBRR" = "num:inttohex($LINIBRR_LINFBRR,8)"!][!//
