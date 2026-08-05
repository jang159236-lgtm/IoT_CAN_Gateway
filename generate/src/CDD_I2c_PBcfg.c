/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPI2C
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
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may
*   only be used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file
*
*   @addtogroup I2C_DRIVER_CONFIGURATION I2c Driver Configurations
*   @{
*/

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
#include "CDD_I2c_PBcfg.h"
#include "CDD_I2c_Ipw_PBcfg.h"

#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_I2C_PBCFG_VENDOR_ID_C                     43
#define CDD_I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define CDD_I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define CDD_I2C_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define CDD_I2C_PBCFG_SW_MAJOR_VERSION_C              3
#define CDD_I2C_PBCFG_SW_MINOR_VERSION_C              0
#define CDD_I2C_PBCFG_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and CDD_I2c_PBcfg.h header file are of the same vendor */
#if (CDD_I2C_PBCFG_VENDOR_ID_C != CDD_I2C_PBCFG_VENDOR_ID)
    #error "CDD_I2c_PBcfg.c and CDD_I2c_PBcfg.h have different vendor ids"
#endif
/* Check if current file and CDD_I2c_PBcfg.h header file are of the same Autosar version */
#if ((CDD_I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C     != CDD_I2C_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C     != CDD_I2C_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_I2C_PBCFG_AR_RELEASE_REVISION_VERSION_C  != CDD_I2C_PBCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of CDD_I2c_PBcfg.c and CDD_I2c_PBcfg.h are different"
#endif
/* Check if current file and CDD_I2c_PBcfg.h header file are of the same software version */
#if ((CDD_I2C_PBCFG_SW_MAJOR_VERSION_C != CDD_I2C_PBCFG_SW_MAJOR_VERSION) || \
     (CDD_I2C_PBCFG_SW_MINOR_VERSION_C != CDD_I2C_PBCFG_SW_MINOR_VERSION) || \
     (CDD_I2C_PBCFG_SW_PATCH_VERSION_C != CDD_I2C_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of CDD_I2c_PBcfg.c and CDD_I2c_PBcfg.h are different"
#endif

/* Check if current file and CDD_I2c_Ipw_PBcfg.h header file are of the same vendor */
#if (CDD_I2C_PBCFG_VENDOR_ID_C != CDD_I2C_IPW_PBCFG_VENDOR_ID)
    #error "CDD_I2c_PBcfg.c and CDD_I2c_Ipw_PBcfg.h have different vendor ids"
#endif
/* Check if current file and CDD_I2c_Ipw_PBcfg.h header file are of the same Autosar version */
#if ((CDD_I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C     != CDD_I2C_IPW_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C     != CDD_I2C_IPW_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_I2C_PBCFG_AR_RELEASE_REVISION_VERSION_C  != CDD_I2C_IPW_PBCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of CDD_I2c_PBcfg.c and CDD_I2c_Ipw_PBcfg.h are different"
#endif
/* Check if current file and CDD_I2c_Ipw_PBcfg.h header file are of the same software version */
#if ((CDD_I2C_PBCFG_SW_MAJOR_VERSION_C != CDD_I2C_IPW_PBCFG_SW_MAJOR_VERSION) || \
     (CDD_I2C_PBCFG_SW_MINOR_VERSION_C != CDD_I2C_IPW_PBCFG_SW_MINOR_VERSION) || \
     (CDD_I2C_PBCFG_SW_PATCH_VERSION_C != CDD_I2C_IPW_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of CDD_I2c_PBcfg.c and CDD_I2c_Ipw_PBcfg.h are different"
#endif

#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
        /* Check if current file and Dem.h header file are of the same Autosar version */
    #if ((CDD_I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of CDD_I2c_PBcfg.c and Dem.h are different"
    #endif
    #endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
#endif /* I2C_DISABLE_DEM_REPORT_ERROR_STATUS */

/*==================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
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

/**
* @brief          Paritition IDs.
* @details        Paritition IDs.
*
* @api
*/

#define I2C_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "I2c_MemMap.h"

/**
* @brief        Definition of I2c hardware channel structure.
* @details      Configures the hardware peripheral of an I2c channel.
*               Configuration set by calling I2c_Init() API.
*/

static const I2c_HwUnitConfigType I2c_ChannelConfigPB[1] =
{
    /* Start of I2c_ChannelConfig[0] */
    {
        /* The hardware channel ID. */
        (I2c_HwUnitType) I2C_LPI2C_1,

        /* The Partition Id */
        (I2c_PartCoreType) I2C_SPURIOUS_PARTITION_ID,

        /* The master/slave mode of the channel. */
        (I2c_MasterSlaveModeType) I2C_MASTER_MODE,

        /* The hardware channel type */
        I2C_LPI2C_CHANNEL,
        {
            &I2c_Ipw_ChannelConfig0
        }
    } /* end of I2c_ChannelConfig[0]. */
};

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
/**
* @brief          Initialization data for the I2c driver.
* @details        A structure is provided to the I2c initialization routines for configuration.
*                 The configuration structure for spurious_partition.
*
*/
const I2c_ConfigType I2c_Config =
{
    /* The Partition Id */
    (I2c_PartCoreType) I2C_SPURIOUS_PARTITION_ID,

#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    /* Pointer to DEM error reporting configurations. */
    &I2c_DemConfig,
#endif

    /* Pointer to I2C Hardware Unit configuration. */
    &I2c_ChannelConfigPB
};



#define I2C_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "I2c_MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                  LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

