/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K1_RTD_3_0_0_QLP04_D2509_ASR_REL_4_7_REV_0000_20250930
*
*   Copyright 2020-2025 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef INTCTRL_IP_CFG_DEFINES_H_
#define INTCTRL_IP_CFG_DEFINES_H_

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_VENDOR_ID                          43
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MAJOR_VERSION                   3
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_SW_PATCH_VERSION                   0
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION           7
#define CDD_PLATFORM_INTCTRL_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION        0
/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief Interrupt Controller feature enablement.
*/
#define PLATFORM_IP_ENABLE_INT_CTRL (STD_ON)
#include "S32K148.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/* Development error detection */
/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define INT_CTRL_IP_DEV_ERROR_DETECT              (STD_ON)
/* VTOR address configuration enable */
#define INT_CTRL_IP_ENABLE_VTOR_CONFIG             (STD_OFF)
/* IP standalone APIs  */
#define INT_CTRL_IP_STANDALONE_APIS               (STD_OFF)
/* First implemented interrupt vector */
#define INT_CTRL_IP_IRQ_MIN                       (DMA0_IRQn)
/* Last implemented interrupt vector */
#define INT_CTRL_IP_IRQ_MAX                       (FTM7_Ovf_Reload_IRQn)
/* The interrupt counter value*/
#define INT_CTRL_IP_IRQ_COUNT                     (128U)
/* Arm Cortex M */
#define INT_CTRL_IP_CORTEXM                       (STD_ON)
/* Arm Cortex M0+ */
#define INT_CTRL_IP_CORTEXM0PLUS                  (STD_OFF)
/* Arm Cortex R */
#define INT_CTRL_IP_CORTEXR                       (STD_OFF)
/* Arm Cortex A */
#define INT_CTRL_IP_CORTEXA                       (STD_OFF)

/* Number of nvic priority bits implemented */
#define INT_CTRL_IP_NVIC_PRIO_BITS                (4U)

/*Interrupt Router Shared Peripheral Routing Control Register*/
#define INT_CTRL_IP_ROUTING_CONTROL_REGISTER      (STD_OFF)

/* This instruction invalidates the entire instruction cache or caches */
#define INT_CTRL_IP_INVALIDATE_CACHE              (STD_OFF)

/* User mode support */
#define INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT (STD_OFF)
#endif /* INTCTRL_IP_CFG_DEFINES_H_ */

