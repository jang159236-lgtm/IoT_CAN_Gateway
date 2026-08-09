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

#ifndef RAM_IP_CFG_DEFINES_H
#define RAM_IP_CFG_DEFINES_H

/**
*   @file       Ram_Ip_Cfg_Defines.h
*   @version    3.0.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup RAM_DRIVER_CONFIGURATION Ram Ip Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RAM_IP_CFG_DEFINES_VENDOR_ID                       43
#define RAM_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION        4
#define RAM_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION        7
#define RAM_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION     0
#define RAM_IP_CFG_DEFINES_SW_MAJOR_VERSION                3
#define RAM_IP_CFG_DEFINES_SW_MINOR_VERSION                0
#define RAM_IP_CFG_DEFINES_SW_PATCH_VERSION                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/

/**
* @brief            Pre-processor switch to enable/disable the API Ram_Ip_GetRamState.
*/

#define RAM_IP_GET_RAM_STATE_API        (STD_OFF)

/**
* @brief            HW sseries used.
*/
#define RAM_IP_SPECIFC

/**
* @brief        Support for MultiPartition.
*/
#define RAM_IP_MULTIPARTITION_SUPPORT            (STD_OFF)
#define RAM_IP_PARTITION_0                       ((uint8)0UL)
/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



#ifdef __cplusplus
}
#endif

/** @} */
#endif /* #ifndef RAM_IP_CFG_DEFINES_H */



