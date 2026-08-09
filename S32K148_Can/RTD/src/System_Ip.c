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

/**
*   @file
*
*   @defgroup   System_Ip System IP
*   @ingroup    Platform
*
*   @addtogroup System_Ip
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "System_Ip.h"
#include "Mcal.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_SYSTEM_IP_VENDOR_ID_C                          43
#define CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MAJOR_VERSION_C           4
#define CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MINOR_VERSION_C           7
#define CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_REVISION_VERSION_C        0
#define CDD_PLATFORM_SYSTEM_IP_SW_MAJOR_VERSION_C                   3
#define CDD_PLATFORM_SYSTEM_IP_SW_MINOR_VERSION_C                   0
#define CDD_PLATFORM_SYSTEM_IP_SW_PATCH_VERSION_C                   0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and System_Ip header file are of the same vendor */
#if (CDD_PLATFORM_SYSTEM_IP_VENDOR_ID_C != CDD_PLATFORM_SYSTEM_IP_VENDOR_ID)
    #error "System_Ip.c and System_Ip.h have different vendor ids"
#endif
/* Check if current file and System_Ip header file are of the same Autosar version */
#if ((CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MAJOR_VERSION_C    != CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MINOR_VERSION_C    != CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_REVISION_VERSION_C != CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of System_Ip.c and System_Ip.h are different"
#endif
/* Check if current file and System_Ip header file are of the same Software version */
#if ((CDD_PLATFORM_SYSTEM_IP_SW_MAJOR_VERSION_C != CDD_PLATFORM_SYSTEM_IP_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_SYSTEM_IP_SW_MINOR_VERSION_C != CDD_PLATFORM_SYSTEM_IP_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_SYSTEM_IP_SW_PATCH_VERSION_C != CDD_PLATFORM_SYSTEM_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of System_Ip.c and System_Ip.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_PLATFORM_SYSTEM_IP_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of System_Ip.c and Mcal.h are different"
    #endif
#endif
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
    #if (PLATFORM_IP_ENABLE_SYSTEM == STD_ON)
#if ((STD_ON == SYSTEM_IP_ENABLE_USER_MODE_SUPPORT) && (defined (MCAL_ENABLE_USER_MODE_SUPPORT)))
    #define Call_System_Ip_ConfigIrq(eIrq,bEnable)  \
                OsIf_Trusted_Call2params(System_Ip_ConfigIrqPrivileged,(eIrq),(bEnable))
#else /*STD_ON == SYSTEM_IP_ENABLE_USER_MODE_SUPPORT*/
    #define Call_System_Ip_ConfigIrq(eIrq,bEnable)  \
                System_Ip_ConfigIrqPrivileged((eIrq), (bEnable))
#endif /*STD_ON == SYSTEM_IP_ENABLE_USER_MODE_SUPPORT*/
#endif /* PLATFORM_IP_ENABLE_SYSTEM == STD_ON */

/*==================================================================================================
*                                  LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#if (PLATFORM_IP_ENABLE_SYSTEM == STD_ON)

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

    #if ((SYSTEM_IP_ARM_CORTEXM == STD_ON) && (SYSTEM_FPU_CFG == STD_ON))
void System_Ip_ConfigIrqPrivileged(System_Ip_IrqType eIrq, boolean bEnable);
    #endif


#endif

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#if (PLATFORM_IP_ENABLE_SYSTEM == STD_ON)
/**
 * @brief         Enables/disables core-related interrupt exceptions.
 *
 * @details       This function is non-reentrant and configures core-related interrupt
 *
 * */
    #if ((SYSTEM_IP_ARM_CORTEXM == STD_ON) && (SYSTEM_FPU_CFG == STD_ON))
void System_Ip_ConfigIrqPrivileged(System_Ip_IrqType eIrq, boolean bEnable)
{
        #if (SYSTEM_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check interrupt to be enabled */
    DevAssert((uint32)eIrq < 32U);
        #endif /*(SYSTEM_IP_DEV_ERROR_DETECT == STD_ON) */
    uint32 u32RegValTemp = IP_MCM->ISCR;
        #ifdef MCM_HAS_WABS_SUPPORTED
    u32RegValTemp &= ~(MCM_ISCR_WABS_MASK);
        #endif

    if (bEnable)
    {
        u32RegValTemp |= (1UL << (uint32)eIrq);
    }
    else
    {
        u32RegValTemp &= ~(1UL << (uint32)eIrq);
    }
    IP_MCM->ISCR = u32RegValTemp;
}
    #endif

#endif /* PLATFORM_IP_ENABLE_SYSTEM == STD_ON */
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#if (PLATFORM_IP_ENABLE_SYSTEM == STD_ON)

    #if ((SYSTEM_IP_ARM_CORTEXM == STD_ON) && (SYSTEM_FPU_CFG == STD_ON))
/**
 * @brief         Enables/disables core-related interrupt exceptions.
 *
 * @details       This function is non-reentrant and configures core-related interrupt
 *                exceptions, as defined per each platform.
 *
 * @param[in]     eIrq: core-related interrupt event.
 * @param[in]     bEnable: FALSE - disable interrupt, TRUE - enable interrupt.
 * @return        void
 *
 * @api
 *
 * @implements    System_Ip_ConfigIrq_Activity
 *
 * */
void System_Ip_ConfigIrq(System_Ip_IrqType eIrq, boolean bEnable)
{
    Call_System_Ip_ConfigIrq(eIrq, bEnable);
}
    #endif


#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#endif /* PLATFORM_IP_ENABLE_SYSTEM == STD_ON */

#ifdef __cplusplus
}
#endif

/** @} */
