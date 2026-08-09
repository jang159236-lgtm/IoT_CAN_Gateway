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

#ifndef POWER_IP_PMC_TYPES_H
#define POWER_IP_PMC_TYPES_H

/**
*   @file       Power_Ip_PMC_Types.h
*   @version    3.0.0
*
*   @brief   POWER IP driver header file.
*   @details POWER IP driver header file.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
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
#include "Power_Ip_Cfg_Defines.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_PMC_TYPES_VENDOR_ID                       43
#define POWER_IP_PMC_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define POWER_IP_PMC_TYPES_AR_RELEASE_MINOR_VERSION        7
#define POWER_IP_PMC_TYPES_AR_RELEASE_REVISION_VERSION     0
#define POWER_IP_PMC_TYPES_SW_MAJOR_VERSION                3
#define POWER_IP_PMC_TYPES_SW_MINOR_VERSION                0
#define POWER_IP_PMC_TYPES_SW_PATCH_VERSION                0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_PMC_Types.h file and Power_Ip_Cfg_Defines.h file have same versions */
#if (POWER_IP_PMC_TYPES_VENDOR_ID  != POWER_IP_CFG_DEFINES_VENDOR_ID)
    #error "Power_Ip_PMC_Types.h and Power_Ip_Cfg_Defines.h have different vendor IDs"
#endif

/* Check if Power_Ip_PMC_Types.h file and Power_Ip_Cfg_Defines.h file are of the same Autosar version */
#if ((POWER_IP_PMC_TYPES_AR_RELEASE_MAJOR_VERSION    != POWER_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PMC_TYPES_AR_RELEASE_MINOR_VERSION    != POWER_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PMC_TYPES_AR_RELEASE_REVISION_VERSION != POWER_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Power_Ip_PMC_Types.h and Power_Ip_Cfg_Defines.h are different"
#endif

/* Check if Power_Ip_PMC_Types.h file and Power_Ip_Cfg_Defines.h file are of the same Software version */
#if ((POWER_IP_PMC_TYPES_SW_MAJOR_VERSION != POWER_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (POWER_IP_PMC_TYPES_SW_MINOR_VERSION != POWER_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (POWER_IP_PMC_TYPES_SW_PATCH_VERSION != POWER_IP_CFG_DEFINES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Power_Ip_PMC_Types.h and Power_Ip_Cfg_Defines.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define PMC_LVDSC1_LVD_ENABLE_U8           ((uint8)(0x20))
#define PMC_LVDSC1_LVD_DISABLE_U8          ((uint8)(0x00))
#define PMC_LVDSC1_LVDRE_ENABLE_U8         ((uint8)(0x10))
#define PMC_LVDSC1_LVDRE_DISABLE_U8        ((uint8)(0x00))
#define PMC_LVDSC2_LVW_ENABLE_U8           ((uint8)(0x20))
#define PMC_LVDSC2_LVW_DISABLE_U8          ((uint8)(0x00))

#define PMC_REGSC_LPO_ENABLE_U8            ((uint8)(0x00))
#define PMC_REGSC_LPO_DISABLE_U8           ((uint8)(0x80))
#define PMC_REGSC_BIAS_ENABLE_U8           ((uint8)(0x01))
#define PMC_REGSC_BIAS_DISABLE_U8          ((uint8)(0x00))
#define PMC_REGSC_CLKBIAS_DISABLE_U8       ((uint8)(0x02))
#define PMC_REGSC_CLKBIAS_ENABLE_U8        ((uint8)(0x00))

#define PMC_AE_CONFIG_LINSUPEN_ENABLE_U32           ((uint32)(0x40))
#define PMC_AE_CONFIG_LINSUPEN_DISABLE_U32          ((uint32)(0x00))
#define PMC_AE_CONFIG_VDDCEN_ENABLE_U32             ((uint32)(0x08))
#define PMC_AE_CONFIG_VDDCEN_DISABLE_U32            ((uint32)(0x00))
#define PMC_AE_CONFIG_LVDVLSSEL_6_5V_U32            ((uint32)(0x20))
#define PMC_AE_CONFIG_LVDVLSSEL_5_5V_U32            ((uint32)(0x00))
#define PMC_AE_CONFIG_LINSUPSEL_VSUP_PIN_U32        ((uint32)(0x00))
#define PMC_AE_CONFIG_LINSUPSEL_HD_PIN_U32          ((uint32)(0x10))
#define PMC_AE_CONFIG_VDDSEL5V_3_3V_U32             ((uint32)(0x00))
#define PMC_AE_CONFIG_VDDSEL5V_5V_U32               ((uint32)(0x01))

#define PMC_AE_MONITOR_LVDVLSIE_ENABLE_U32          ((uint32)(0x10000000))
#define PMC_AE_MONITOR_LVDVLSIE_DISABLE_U32         ((uint32)(0x00000000))
#define PMC_AE_MONITOR_LVDCIE_ENABLE_U32            ((uint32)(0x08000000))
#define PMC_AE_MONITOR_LVDCIE_DISABLE_U32           ((uint32)(0x00000000))
#define PMC_AE_MONITOR_HVDVDDIE_ENABLE_U32          ((uint32)(0x04000000))
#define PMC_AE_MONITOR_HVDVDDIE_DISABLE_U32         ((uint32)(0x00000000))
#define PMC_AE_MONITOR_HVDINT15IE_ENABLE_U32        ((uint32)(0x01000000))
#define PMC_AE_MONITOR_HVDINT15IE_DISABLE_U32       ((uint32)(0x00000000))

#if (defined(POWER_IP_DERIVATIVE_009) || defined(POWER_IP_DERIVATIVE_010))
    #define PMC_LVDSC1_RWBITS_MASK8     ((uint8)PMC_142_LVDSC1_LVDRE_MASK  | \
                                                PMC_142_LVDSC1_LVDIE_MASK  | \
                                                PMC_142_LVDSC1_LVDACK_MASK | \
                                                PMC_142_LVDSC1_LVDF_MASK)

    #define PMC_LVDSC2_RWBITS_MASK8     ((uint8)PMC_142_LVDSC2_LVWIE_MASK  | \
                                                PMC_142_LVDSC2_LVWACK_MASK | \
                                                PMC_142_LVDSC2_LVWF_MASK)

    #define PMC_REGSC_RWBITS_MASK8      ((uint8)PMC_142_REGSC_BIASEN_MASK     | \
                                                PMC_142_REGSC_CLKBIASDIS_MASK | \
                                                PMC_142_REGSC_REGFPM_MASK     | \
                                                PMC_142_REGSC_LPOSTAT_MASK    | \
                                                PMC_142_REGSC_LPODIS_MASK)

    #define PMC_LPOTRIM_RWBITS_MASK8            PMC_142_LPOTRIM_LPOTRIM_MASK

    #define POWER_IP_PMC                        IP_PMC_142
    #define POWER_IP_PMC_LVDSC1_LVDF_MASK       PMC_142_LVDSC1_LVDF_MASK
    #define POWER_IP_PMC_LVDSC2_LVWF_MASK       PMC_142_LVDSC2_LVWF_MASK
    #define POWER_IP_PMC_LVDSC1_LVDIE_MASK      PMC_142_LVDSC1_LVDIE_MASK
    #define POWER_IP_PMC_LVDSC2_LVWIE_MASK      PMC_142_LVDSC2_LVWIE_MASK
    #define POWER_IP_PMC_LVDSC1_LVDACK_MASK     PMC_142_LVDSC1_LVDACK_MASK
    #define POWER_IP_PMC_LVDSC2_LVWACK_MASK     PMC_142_LVDSC2_LVWACK_MASK

#else

    #define PMC_LVDSC1_RWBITS_MASK8     ((uint8)PMC_LVDSC1_LVDRE_MASK  | \
                                                PMC_LVDSC1_LVDIE_MASK  | \
                                                PMC_LVDSC1_LVDACK_MASK | \
                                                PMC_LVDSC1_LVDF_MASK)

    #define PMC_LVDSC2_RWBITS_MASK8     ((uint8)PMC_LVDSC2_LVWIE_MASK  | \
                                                PMC_LVDSC2_LVWACK_MASK | \
                                                PMC_LVDSC2_LVWF_MASK)

    #define PMC_REGSC_RWBITS_MASK8      ((uint8)PMC_REGSC_BIASEN_MASK     | \
                                                PMC_REGSC_CLKBIASDIS_MASK | \
                                                PMC_REGSC_REGFPM_MASK     | \
                                                PMC_REGSC_LPOSTAT_MASK    | \
                                                PMC_REGSC_LPODIS_MASK)

    #define PMC_LPOTRIM_RWBITS_MASK8            PMC_LPOTRIM_LPOTRIM_MASK

    #define POWER_IP_PMC                        IP_PMC
    #define POWER_IP_PMC_LVDSC1_LVDF_MASK       PMC_LVDSC1_LVDF_MASK
    #define POWER_IP_PMC_LVDSC2_LVWF_MASK       PMC_LVDSC2_LVWF_MASK
    #define POWER_IP_PMC_LVDSC1_LVDACK_MASK     PMC_LVDSC1_LVDACK_MASK
    #define POWER_IP_PMC_LVDSC2_LVWACK_MASK     PMC_LVDSC2_LVWACK_MASK
    #define POWER_IP_PMC_LVDSC1_LVDIE_MASK      PMC_LVDSC1_LVDIE_MASK
    #define POWER_IP_PMC_LVDSC2_LVWIE_MASK      PMC_LVDSC2_LVWIE_MASK
#endif /* ddefined(POWER_IP_DERIVATIVE_009) || defined(POWER_IP_DERIVATIVE_010) */

#define PMC_AE_CONFIG_RWBITS_MASK32 ((uint32)PMC_AE_CONFIG_LINSUPEN_MASK  | \
                                             PMC_AE_CONFIG_LVDVLSSEL_MASK | \
                                             PMC_AE_CONFIG_LINSUPSEL_MASK | \
                                             PMC_AE_CONFIG_VDDCEN_MASK    | \
                                             PMC_AE_CONFIG_VDDSEL5V_MASK)

#define PMC_AE_MONITOR_RWBITS_MASK32 ((uint32)PMC_AE_MONITOR_LVDVLSIE_MASK | \
                                              PMC_AE_MONITOR_LVDCIE_MASK   | \
                                              PMC_AE_MONITOR_HVDVDDIE_MASK | \
                                              PMC_AE_MONITOR_HVDINT15IE_MASK)

#define PMC_AE_MONITOR_INTERRUPT_FLAGS_MASK32 ((uint32)PMC_AE_MONITOR_LVDVLSF_MASK | \
                                                       PMC_AE_MONITOR_LVDCF_MASK   | \
                                                       PMC_AE_MONITOR_HVDVDDF_MASK | \
                                                       PMC_AE_MONITOR_HVDINTF_MASK | \
                                                       PMC_AE_MONITOR_HVD15F_MASK)

#define PMC_LPOTRIM_NO_CHANGED_U8         ((uint8)(0x30))
#define PMC_LPOTRIM_DECREASE_16_U8        ((uint8)(0x10))
#define PMC_LPOTRIM_DECREASE_15_U8        ((uint8)(0x11))
#define PMC_LPOTRIM_DECREASE_14_U8        ((uint8)(0x12))
#define PMC_LPOTRIM_DECREASE_13_U8        ((uint8)(0x13))
#define PMC_LPOTRIM_DECREASE_12_U8        ((uint8)(0x14))
#define PMC_LPOTRIM_DECREASE_11_U8        ((uint8)(0x15))
#define PMC_LPOTRIM_DECREASE_10_U8        ((uint8)(0x16))
#define PMC_LPOTRIM_DECREASE_09_U8        ((uint8)(0x17))
#define PMC_LPOTRIM_DECREASE_08_U8        ((uint8)(0x18))
#define PMC_LPOTRIM_DECREASE_07_U8        ((uint8)(0x19))
#define PMC_LPOTRIM_DECREASE_06_U8        ((uint8)(0x1A))
#define PMC_LPOTRIM_DECREASE_05_U8        ((uint8)(0x1B))
#define PMC_LPOTRIM_DECREASE_04_U8        ((uint8)(0x1C))
#define PMC_LPOTRIM_DECREASE_03_U8        ((uint8)(0x1D))
#define PMC_LPOTRIM_DECREASE_02_U8        ((uint8)(0x1E))
#define PMC_LPOTRIM_DECREASE_01_U8        ((uint8)(0x1F))
#define PMC_LPOTRIM_TYPICAL_U8            ((uint8)(0x00))
#define PMC_LPOTRIM_INCREASE_01_U8        ((uint8)(0x01))
#define PMC_LPOTRIM_INCREASE_02_U8        ((uint8)(0x02))
#define PMC_LPOTRIM_INCREASE_03_U8        ((uint8)(0x03))
#define PMC_LPOTRIM_INCREASE_04_U8        ((uint8)(0x04))
#define PMC_LPOTRIM_INCREASE_05_U8        ((uint8)(0x05))
#define PMC_LPOTRIM_INCREASE_06_U8        ((uint8)(0x06))
#define PMC_LPOTRIM_INCREASE_07_U8        ((uint8)(0x07))
#define PMC_LPOTRIM_INCREASE_08_U8        ((uint8)(0x08))
#define PMC_LPOTRIM_INCREASE_09_U8        ((uint8)(0x09))
#define PMC_LPOTRIM_INCREASE_10_U8        ((uint8)(0x0A))
#define PMC_LPOTRIM_INCREASE_11_U8        ((uint8)(0x0B))
#define PMC_LPOTRIM_INCREASE_12_U8        ((uint8)(0x0C))
#define PMC_LPOTRIM_INCREASE_13_U8        ((uint8)(0x0D))
#define PMC_LPOTRIM_INCREASE_14_U8        ((uint8)(0x0E))
#define PMC_LPOTRIM_INCREASE_15_U8        ((uint8)(0x0F))

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
#if ((defined(POWER_IP_VOLTAGE_ERROR_ISR_USED) && (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON)) || \
     (defined(POWER_IP_PMCAECONFIG_API) && (STD_ON == POWER_IP_PMCAECONFIG_API)) \
    )
typedef enum
{
    PMC_UNINIT = 0,  /**< @brief The PMC driver is uninitialized. */
    PMC_INIT = 1     /**< @brief The PMC driver is initialized. */
} Power_Ip_PMC_StatusType;
#endif

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief            Configuration for PMC.
* @details          The power control unit (PMC) acts as a bridge for mapping the PMC peripheral
 *                  to the PMC address space.
*/
typedef struct
{
#if(STD_ON == POWER_IP_PMC_LVDSC1_SUPPORT)
    uint8 Lvdsc1;                   /**< @brief Low Voltage Detect Status and Control 1 Register (PMC_LVDSC1). */
#endif
    uint8 Lvdsc2;                   /**< @brief Low Voltage Detect Status and Control 2 Register (PMC_LVDSC2). */
    uint8 Regsc;                    /**< @brief Regulator Status and Control Register (PMC_REGSC). */
    uint8 Lpotrim;                  /**< @brief Low Power Oscillator Trim Register (PMC_LPOTRIM). */
#if(STD_ON == POWER_IP_PMC_AE_SUPPORT)
    uint32 PmcAeConfig;             /**< @brief PMC_AE Configuration Register (PMC_AE_CONFIG). */
    uint32 PmcAeMonitor;            /**< @brief PMC_AE Monitor Register (PMC_AE_MONITOR). */
#endif
} Power_Ip_PMC_ConfigType;

typedef enum
{
#if(STD_ON == POWER_IP_PMC_LVDSC1_SUPPORT)
    POWER_IP_PMC_LOW_VOLTAGE_DETECT             = 0x01,             /**< @brief Low Voltage Detect Flag (LVDF). */
    POWER_IP_PMC_LOW_VOLTAGE_DETECT_AND_WARNING = 0x02,             /**< @brief Low Voltage Detect Flag (LVDF) and Low Voltage Warning Flag (LVWF) . */
#endif
    POWER_IP_PMC_LOW_VOLTAGE_WARNING            = 0x03,             /**< @brief Low Voltage Warning Flag (LVWF). */
    POWER_IP_PMC_NO_LOW_VOLTAGE                 = 0x99              /**< @brief No Low Voltage Detect. */
}Power_Ip_LowVoltageType;

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */
#endif /* POWER_IP_PMC_TYPES_H */

