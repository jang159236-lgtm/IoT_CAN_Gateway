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
*   @internal
*   @addtogroup Platform_Ipw
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "Platform_TypesDef.h"
#include "Platform_Ipw.h"
#include "Mcal.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_IPW_VENDOR_ID_C                         43
#define CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION_C          4
#define CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION_C          7
#define CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION_C       0
#define CDD_PLATFORM_IPW_SW_MAJOR_VERSION_C                  3
#define CDD_PLATFORM_IPW_SW_MINOR_VERSION_C                  0
#define CDD_PLATFORM_IPW_SW_PATCH_VERSION_C                  0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Platform_TypesDef header file are of the same vendor */
#if (CDD_PLATFORM_IPW_VENDOR_ID_C != CDD_PLATFORM_TYPESDEF_VENDOR_ID)
    #error "Platform_Ipw.c and Platform_TypesDef.h have different vendor ids"
#endif
/* Check if current file and Platform_TypesDef header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION_C    != CDD_PLATFORM_TYPESDEF_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION_C    != CDD_PLATFORM_TYPESDEF_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION_C != CDD_PLATFORM_TYPESDEF_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw.c and Platform_TypesDef.h are different"
#endif
/* Check if current file and Platform_Ipw_Cfg header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_SW_MAJOR_VERSION_C != CDD_PLATFORM_TYPESDEF_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_MINOR_VERSION_C != CDD_PLATFORM_TYPESDEF_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_PATCH_VERSION_C != CDD_PLATFORM_TYPESDEF_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw.c and Platform_TypesDef.h are different"
#endif


/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Platform_Ipw header file are of the same vendor */
#if (CDD_PLATFORM_IPW_VENDOR_ID_C != CDD_PLATFORM_IPW_VENDOR_ID)
    #error "Platform_Ipw.c and Platform_Ipw.h have different vendor ids"
#endif
/* Check if current file and Platform_Ipw header file are of the same Autosar version */
#if ((CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION_C    != CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION_C    != CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION_C != CDD_PLATFORM_IPW_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Platform_Ipw.c and Platform_Ipw.h are different"
#endif
/* Check if current file and Platform_Ipw header file are of the same Software version */
#if ((CDD_PLATFORM_IPW_SW_MAJOR_VERSION_C != CDD_PLATFORM_IPW_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_MINOR_VERSION_C != CDD_PLATFORM_IPW_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_IPW_SW_PATCH_VERSION_C != CDD_PLATFORM_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Platform_Ipw.c and Platform_Ipw.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if header file and Platform_Ipw.c header file are of the same Autosar version */
    #if ((CDD_PLATFORM_IPW_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (CDD_PLATFORM_IPW_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Platform_Ipw.c and Mcal.h are different"
    #endif
#endif
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"


#if  (PLATFORM_ENABLE_INT_CTRL == STD_ON)
static Std_ReturnType Platform_Ipw_InitIntCtrl(const IntCtrl_Ip_CtrlConfigType *pIntCtrlCtrlConfig)
{
    uint32 irqIdx;

    for (irqIdx = 0; irqIdx < pIntCtrlCtrlConfig->u32ConfigIrqCount; irqIdx++)
    {
        IntCtrl_Ip_ClearPending(pIntCtrlCtrlConfig->aIrqConfig[irqIdx].eIrqNumber);
        /* interrupt number for which the priority is set */
        IntCtrl_Ip_SetPriority(pIntCtrlCtrlConfig->aIrqConfig[irqIdx].eIrqNumber,
                               pIntCtrlCtrlConfig->aIrqConfig[irqIdx].u8IrqPriority);
        /* Install the configured handler */
        IntCtrl_Ip_InstallHandler(pIntCtrlCtrlConfig->aIrqConfig[irqIdx].eIrqNumber,
                                  pIntCtrlCtrlConfig->aIrqConfig[irqIdx].pfHandler,
                                  NULL_PTR);

        /* Enable interrupt */
        if (pIntCtrlCtrlConfig->aIrqConfig[irqIdx].bIrqEnabled)
        {
            /* enables the interrupt request at interrupt controller level. */
            IntCtrl_Ip_EnableIrq(pIntCtrlCtrlConfig->aIrqConfig[irqIdx].eIrqNumber);
        }
        else
        {
            /* disables the interrupt request at interrupt controller level.*/
            IntCtrl_Ip_DisableIrq(pIntCtrlCtrlConfig->aIrqConfig[irqIdx].eIrqNumber);
        }
    }

    return E_OK;
}
#endif

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
 * @brief         Initializes the platform settings based on user configuration.
 */
void Platform_Ipw_Init(const Platform_Ipw_ConfigType *pConfig)
{
#if (PLATFORM_SYS_CFG == STD_ON)
    uint8 u8IrqIdx;
#endif
    Std_ReturnType ret = (Std_ReturnType)E_OK;

#if  (PLATFORM_ENABLE_INT_CTRL == STD_ON)
    /* Initialize interrupts at interrupt controller level */
    if (NULL_PTR != pConfig->pIntCtrlConfig)
    {
        ret = Platform_Ipw_InitIntCtrl(pConfig->pIntCtrlConfig);
    }
#endif
    if(ret == (Std_ReturnType)E_OK)
    {
#if (PLATFORM_SYS_CFG == STD_ON)
        if (pConfig->aSystemConfig != NULL_PTR)
        {
            if ((pConfig->aSystemConfig)->u8SysIrqsCount <= SYSTEM_IP_MAX_CORE_INT)
            {
                /* Configure core-related interrupt requests */
                for (u8IrqIdx = 0u; u8IrqIdx < (pConfig->aSystemConfig)->u8SysIrqsCount; u8IrqIdx++)
                {           
                    System_Ip_ConfigIrq((pConfig->aSystemConfig)->aSystemIrqs[u8IrqIdx].eIrq,
                                        (pConfig->aSystemConfig)->aSystemIrqs[u8IrqIdx].bEnable);
                }
            }
        }
#endif
    }
    (void)pConfig;
}


#if (PLATFORM_ENABLE_MPU == STD_ON)
    /*
 * @brief         Initializes the Memory Protection Unit general parameters and
 *                region configurations
 * @details       This function is non-reentrant
 * @param[in]     pConfig: pointer to configuration structure for MPU.
 * @return        void
 * @pre           None
 */
void Platform_Ipw_Mpu_Init(const Platform_Ipw_ConfigType * pIpwConfig)
{
    Mpu_Ip_Init(pIpwConfig->Platform_Ipw_pMpuConfig);
}

/*
 * @brief         Configures the region selected by regionNumber with the data from pUserConfigPtr
 * @details       This function is Reentrant
 * @param[in]     regionNumber: Region to be modified .
 * @param[in]     pUserConfigPtr: pointer to the region configuration structure for MPU.
 * @return        void
 * @pre           None
 */
void Platform_Ipw_Mpu_SetRegionConfig(uint8 u8RegionNum, const Platform_Mpu_RegionConfigType * const pUserConfigPtr)
{
    Mpu_Ip_SetRegionConfig(u8RegionNum, pUserConfigPtr);
}

/*
 * @brief         Enables or disabled a specific region
 * @details       This function is Reentrant
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     bEnable  : Specifies wheter the region is enabled or disabled
 * @return        void
 * @pre           None
 */
void Platform_Ipw_Mpu_EnableRegion(uint8 u8RegionNum, boolean bEnable)
{
    Mpu_Ip_EnableRegion(u8RegionNum, bEnable);
}

/*
 * @brief         Modify the User access mode for a master to a specific region
 * @details       This function is Reentrant
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     eMaster     : Master to be modified
 * @param[in]     eMode       : Specifies the new mode access
 * @return        void
 * @pre           None
 */
void Platform_Ipw_Mpu_SetAccessMode(uint8 u8RegionNum,
                              Platform_Mpu_MasterType eMaster,
                              Platform_Mpu_SupervisorAccessModeType eSupervisorMode,
                              Platform_Mpu_UserAccessModeType eUserMode
                             )
{
    Mpu_Ip_SetAccessMode(u8RegionNum, eMaster, eSupervisorMode, eUserMode);
}

/*
 * @brief         Retrieve error details
 * @details       This function is Reentrant
 * @param[out]    pErrorDetails : Storage where the data will be saved
 * @return        boolean - TRUE if an error was present, FALSE otherwise
 * @pre           None
 */
boolean Platform_Ipw_Mpu_GetErrorDetails(Platform_Mpu_ErrorDetailsType * pErrorDetails)
{
    return Mpu_Ip_GetErrorDetails(pErrorDetails);
}
#endif

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"
