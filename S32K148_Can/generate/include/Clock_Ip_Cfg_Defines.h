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
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/**
*   @file       Clock_Ip_Cfg_Defines.h
*   @version    3.0.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
*   @{
*/

#ifndef CLOCK_IP_CFG_DEFINES_H
#define CLOCK_IP_CFG_DEFINES_H


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "S32K148_SIM.h"
#include "S32K148_SCG.h"
#include "S32K148_PCC.h"
#include "S32K148_SMC.h"
#include "S32K148_QUADSPI.h"
#include "S32K148_RCM.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_CFG_DEFINES_VENDOR_ID                       43
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION        4
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION        7
#define CLOCK_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION     0
#define CLOCK_IP_CFG_DEFINES_SW_MAJOR_VERSION                3
#define CLOCK_IP_CFG_DEFINES_SW_MINOR_VERSION                0
#define CLOCK_IP_CFG_DEFINES_SW_PATCH_VERSION                0

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/
/**
* @brief            Derivative used.
*/
#define CLOCK_IP_DERIVATIVE_008
/**
* @brief            HW sseries used.
*/
#define CLOCK_IP_DERIVATIVE_NOT_SUPPORT_USER_MODE
/**
* @brief            Max number of internal oscillators
*/
#define CLOCK_IP_IRCOSCS_COUNT       (2U)

/**
* @brief            Max number of external oscillators
*/
#define CLOCK_IP_XOSCS_COUNT       (1U)

/**
* @brief            Max number of pll devices
*/
#define CLOCK_IP_PLLS_COUNT       (1U)

/**
* @brief            Max number of selectors
*/
#define CLOCK_IP_SELECTORS_COUNT       (38U)

/**
* @brief            Max number of dividers
*/
#define CLOCK_IP_DIVIDERS_COUNT       (21U)

/**
* @brief            Max number of divider triggers
*/
#define CLOCK_IP_DIVIDER_TRIGGERS_COUNT       (0U)

/**
* @brief            Max number of fractional dividers
*/
#define CLOCK_IP_FRACTIONAL_DIVIDERS_COUNT       (0U)

/**
* @brief            Max number of external clocks
*/
#define CLOCK_IP_EXT_CLKS_COUNT       (4U)

/**
* @brief            Max number of pcfs
*/
#define CLOCK_IP_PCFS_COUNT       (0U)

/**
* @brief            Max number of clock gates
*/
#define CLOCK_IP_GATES_COUNT       (50U)

/**
* @brief            Max number of clock monitoring units
*/
#define CLOCK_IP_CMUS_COUNT       (0U)

/**
* @brief            Max number of configured frequencies values
*/
#define CLOCK_IP_CONFIGURED_FREQUENCIES_COUNT       (1U)

/**
* @brief             Max number of specific peripheral (eMIOS) units
*/
#define CLOCK_IP_SPECIFIC_PERIPH_COUNT       (0U)

/**
* @brief            Supported power mode.
*/
#define CLOCK_IP_HAS_RUN_MODE                  0U

#define CLOCK_IP_LPO_128K_FREQUENCY            128000U

#define CLOCK_IP_FIRC_FREQUENCY                48000000U

#define CLOCK_IP_SIRC_FREQUENCY                8000000U

#define CLOCK_IP_DEFAULT_SOSC_FREQUENCY        40000000U

#define CLOCK_IP_HAS_LOW_GAIN                  0U

#define CLOCK_IP_HAS_HIGH_GAIN                 1U

#define CLOCK_IP_HAS_MONITOR_DISABLE           0U

#define CLOCK_IP_HAS_MONITOR_INT               1U

#define CLOCK_IP_HAS_MONITOR_RESET             2U

#define CLOCK_IP_HAS_SAFE_CLOCK_DISABLEMENT    1U

#if CLOCK_IP_CMUS_COUNT > 0U
/**
* @brief            Cmu formula constant values.
*/
#define CLOCK_IP_FEATURE_OFFSET_REFERENCE_COUNT_FORMULA1               1U
#define CLOCK_IP_FEATURE_MULTIPLIER_REFERENCE_COUNT_FORMULA1           3U
#define CLOCK_IP_FEATURE_OFFSET_REFERENCE_COUNT_FORMULA2               7U
#define CLOCK_IP_FEATURE_MULTIPLIER_REFERENCE_COUNT_FORMULA2           3U
#endif

#define CLOCK_IP_POWER_NOTIFICATIONS         (STD_ON)

/**
* @brief            Clock ip supports clock frequency.
*/
#define CLOCK_IP_GET_FREQUENCY_API                (STD_OFF)

/**
* @brief            Supports wait states configuration
*/
#define CLOCK_IP_SUPPORTS_WAIT_STATES       STD_OFF


/**
* @brief            Supported clocks.
*/
#define CLOCK_IP_HAS_LPO_128K_CLK         1U
#define CLOCK_IP_HAS_SIRC_CLK         2U
#define CLOCK_IP_HAS_SIRC_VLP_CLK         3U
#define CLOCK_IP_HAS_SIRC_STOP_CLK         4U
#define CLOCK_IP_HAS_FIRC_CLK         5U
#define CLOCK_IP_HAS_FIRC_VLP_CLK         6U
#define CLOCK_IP_HAS_FIRC_STOP_CLK         7U
#define CLOCK_IP_HAS_SOSC_CLK         8U
#define CLOCK_IP_HAS_SPLL_CLK         9U
#define CLOCK_IP_HAS_SIRCDIV1_CLK         10U
#define CLOCK_IP_HAS_SIRCDIV2_CLK         11U
#define CLOCK_IP_HAS_FIRCDIV1_CLK         12U
#define CLOCK_IP_HAS_FIRCDIV2_CLK         13U
#define CLOCK_IP_HAS_SOSCDIV1_CLK         14U
#define CLOCK_IP_HAS_SOSCDIV2_CLK         15U
#define CLOCK_IP_HAS_SPLLDIV1_CLK         16U
#define CLOCK_IP_HAS_SPLLDIV2_CLK         17U
#define CLOCK_IP_HAS_LPO_32K_CLK         18U
#define CLOCK_IP_HAS_LPO_1K_CLK         19U
#define CLOCK_IP_HAS_TCLK0_REF_CLK         20U
#define CLOCK_IP_HAS_TCLK1_REF_CLK         21U
#define CLOCK_IP_HAS_TCLK2_REF_CLK         22U
#define CLOCK_IP_HAS_RTC_CLKIN         23U
#define CLOCK_IP_HAS_SCS_CLK         24U
#define CLOCK_IP_HAS_SCS_RUN_CLK         25U
#define CLOCK_IP_HAS_SCS_VLPR_CLK         26U
#define CLOCK_IP_HAS_SCS_HSRUN_CLK         27U
#define CLOCK_IP_HAS_CORE_CLK         28U
#define CLOCK_IP_HAS_CORE_RUN_CLK         29U
#define CLOCK_IP_HAS_CORE_VLPR_CLK         30U
#define CLOCK_IP_HAS_CORE_HSRUN_CLK         31U
#define CLOCK_IP_HAS_BUS_CLK         32U
#define CLOCK_IP_HAS_BUS_RUN_CLK         33U
#define CLOCK_IP_HAS_BUS_VLPR_CLK         34U
#define CLOCK_IP_HAS_BUS_HSRUN_CLK         35U
#define CLOCK_IP_HAS_SLOW_CLK         36U
#define CLOCK_IP_HAS_SLOW_RUN_CLK         37U
#define CLOCK_IP_HAS_SLOW_VLPR_CLK         38U
#define CLOCK_IP_HAS_SLOW_HSRUN_CLK         39U
#define CLOCK_IP_HAS_RTC_CLK         40U
#define CLOCK_IP_HAS_LPO_CLK         41U
#define CLOCK_IP_HAS_SCG_CLKOUT_CLK         42U
#define CLOCK_IP_HAS_FTM0_EXT_CLK         43U
#define CLOCK_IP_HAS_FTM1_EXT_CLK         44U
#define CLOCK_IP_HAS_FTM2_EXT_CLK         45U
#define CLOCK_IP_HAS_FTM3_EXT_CLK         46U
#define CLOCK_IP_HAS_FTM4_EXT_CLK         47U
#define CLOCK_IP_HAS_FTM5_EXT_CLK         48U
#define CLOCK_IP_HAS_FTM6_EXT_CLK         49U
#define CLOCK_IP_HAS_FTM7_EXT_CLK         50U
#define CLOCK_IP_FEATURE_PRODUCERS_NO         51U
#define CLOCK_IP_HAS_ADC0_CLK         52U
#define CLOCK_IP_HAS_ADC1_CLK         53U
#define CLOCK_IP_HAS_CLKOUT0_CLK         54U
#define CLOCK_IP_HAS_CMP0_CLK         55U
#define CLOCK_IP_HAS_CRC0_CLK         56U
#define CLOCK_IP_HAS_DMA0_CLK         57U
#define CLOCK_IP_HAS_DMAMUX0_CLK         58U
#define CLOCK_IP_HAS_EIM0_CLK         59U
#define CLOCK_IP_HAS_ENET_CLK         60U
#define CLOCK_IP_HAS_ERM0_CLK         61U
#define CLOCK_IP_HAS_EWM0_CLK         62U
#define CLOCK_IP_HAS_FLEXCAN0_CLK         63U
#define CLOCK_IP_HAS_FLEXCAN1_CLK         64U
#define CLOCK_IP_HAS_FLEXCAN2_CLK         65U
#define CLOCK_IP_HAS_FlexIO_CLK         66U
#define CLOCK_IP_HAS_FTFC_CLK         67U
#define CLOCK_IP_HAS_FTM0_CLK         68U
#define CLOCK_IP_HAS_FTM1_CLK         69U
#define CLOCK_IP_HAS_FTM2_CLK         70U
#define CLOCK_IP_HAS_FTM3_CLK         71U
#define CLOCK_IP_HAS_FTM4_CLK         72U
#define CLOCK_IP_HAS_FTM5_CLK         73U
#define CLOCK_IP_HAS_FTM6_CLK         74U
#define CLOCK_IP_HAS_FTM7_CLK         75U
#define CLOCK_IP_HAS_LPI2C0_CLK         76U
#define CLOCK_IP_HAS_LPI2C1_CLK         77U
#define CLOCK_IP_HAS_LPIT0_CLK         78U
#define CLOCK_IP_HAS_LPSPI0_CLK         79U
#define CLOCK_IP_HAS_LPSPI1_CLK         80U
#define CLOCK_IP_HAS_LPSPI2_CLK         81U
#define CLOCK_IP_HAS_LPTMR0_CLK         82U
#define CLOCK_IP_HAS_LPUART0_CLK         83U
#define CLOCK_IP_HAS_LPUART1_CLK         84U
#define CLOCK_IP_HAS_LPUART2_CLK         85U
#define CLOCK_IP_HAS_MPU0_CLK         86U
#define CLOCK_IP_HAS_MSCM0_CLK         87U
#define CLOCK_IP_HAS_PDB0_CLK         88U
#define CLOCK_IP_HAS_PDB1_CLK         89U
#define CLOCK_IP_HAS_PORTA_CLK         90U
#define CLOCK_IP_HAS_PORTB_CLK         91U
#define CLOCK_IP_HAS_PORTC_CLK         92U
#define CLOCK_IP_HAS_PORTD_CLK         93U
#define CLOCK_IP_HAS_PORTE_CLK         94U
#define CLOCK_IP_HAS_QSPI_CLK         95U
#define CLOCK_IP_HAS_QSPI_SFIF_CLK_HYP_PREMUX_CLK         96U
#define CLOCK_IP_HAS_QSPI_SFIF_CLK         97U
#define CLOCK_IP_HAS_QSPI_2xSFIF_CLK         98U
#define CLOCK_IP_HAS_RTC0_CLK         99U
#define CLOCK_IP_HAS_SAI0_CLK         100U
#define CLOCK_IP_HAS_SAI1_CLK         101U
#define CLOCK_IP_HAS_TRACE_CLK         102U
#define CLOCK_IP_FEATURE_NAMES_NO         103U


/*some clock defined specific*/
#define CLOCK_IP_HAS_RUN_PRI_DIV_SYS_CLK                 CLOCK_IP_HAS_SCS_RUN_CLK
#define CLOCK_IP_HAS_RUN_CORE_CLK                        CLOCK_IP_HAS_CORE_RUN_CLK
#define CLOCK_IP_HAS_RUN_SYS_CLK                         CLOCK_IP_HAS_CORE_RUN_CLK
#define CLOCK_IP_HAS_RUN_FLASH_CLK                       CLOCK_IP_HAS_SLOW_RUN_CLK
#define CLOCK_IP_HAS_RUN_BUS_CLK                         CLOCK_IP_HAS_BUS_RUN_CLK
#if defined(CLOCK_IP_HAS_SCS_HSRUN_CLK)
#define CLOCK_IP_HAS_HSRUN_PRI_DIV_SYS_CLK               CLOCK_IP_HAS_SCS_HSRUN_CLK
#endif
#if defined(CLOCK_IP_HAS_CORE_HSRUN_CLK)
#define CLOCK_IP_HAS_HSRUN_CORE_CLK                      CLOCK_IP_HAS_CORE_HSRUN_CLK
#define CLOCK_IP_HAS_HSRUN_SYS_CLK                       CLOCK_IP_HAS_CORE_HSRUN_CLK
#endif
#if defined(CLOCK_IP_HAS_SLOW_HSRUN_CLK)
#define CLOCK_IP_HAS_HSRUN_FLASH_CLK                     CLOCK_IP_HAS_SLOW_HSRUN_CLK
#endif
#if defined(CLOCK_IP_HAS_BUS_HSRUN_CLK)
#define CLOCK_IP_HAS_HSRUN_BUS_CLK                       CLOCK_IP_HAS_BUS_HSRUN_CLK
#endif
#define CLOCK_IP_HAS_VLPR_PRI_DIV_SYS_CLK                CLOCK_IP_HAS_SCS_VLPR_CLK
#define CLOCK_IP_HAS_VLPR_CORE_CLK                       CLOCK_IP_HAS_CORE_VLPR_CLK
#define CLOCK_IP_HAS_VLPR_SYS_CLK                        CLOCK_IP_HAS_CORE_VLPR_CLK
#define CLOCK_IP_HAS_VLPR_FLASH_CLK                      CLOCK_IP_HAS_SLOW_VLPR_CLK
#define CLOCK_IP_HAS_VLPR_BUS_CLK                        CLOCK_IP_HAS_BUS_VLPR_CLK


/**
* @brief        Support for MultiPartition.
*/
#define CLOCK_IP_MULTIPARTITION_SUPPORT                (STD_OFF)
#define CLOCK_IP_PARTITION_0                   0U



/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



#ifdef __cplusplus
}
#endif

#endif /* #ifndef CLOCK_IP_CFG_DEFINES_H */

/** @} */


