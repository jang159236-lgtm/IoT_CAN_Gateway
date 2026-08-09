/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K14X
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 3.0.0
* Build Version : S32K1_RTD_3_0_0_QLP04_D2509_ASR_REL_4_7_REV_0000_20250930
*
* Copyright 2020-2025 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file OsIf_Software_Semaphore.c
*
*   @addtogroup  osif_drv
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "OsIf_Software_Semaphore.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define OSIF_SOFTWARE_SEMAPHORE_VENDOR_ID_C                       43
#define OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MAJOR_VERSION_C        4
#define OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MINOR_VERSION_C        7
#define OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_REVISION_VERSION_C     0
#define OSIF_SOFTWARE_SEMAPHORE_SW_MAJOR_VERSION_C                3
#define OSIF_SOFTWARE_SEMAPHORE_SW_MINOR_VERSION_C                0
#define OSIF_SOFTWARE_SEMAPHORE_SW_PATCH_VERSION_C                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against OsIf_Software_Semaphore.h */
#if (OSIF_SOFTWARE_SEMAPHORE_VENDOR_ID_C != OSIF_SOFTWARE_SEMAPHORE_VENDOR_ID_H)
    #error "OsIf_Software_Semaphore.c and OsIf_Software_Semaphore.h have different vendor ids"
#endif
#if ((OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MAJOR_VERSION_C    != OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MAJOR_VERSION_H) || \
     (OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MINOR_VERSION_C    != OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MINOR_VERSION_H) || \
     (OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_REVISION_VERSION_C != OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_REVISION_VERSION_H))
    #error "AUTOSAR Version Numbers of OsIf_Software_Semaphore.c and OsIf_Software_Semaphore.h are different"
#endif
#if ((OSIF_SOFTWARE_SEMAPHORE_SW_MAJOR_VERSION_C != OSIF_SOFTWARE_SEMAPHORE_SW_MAJOR_VERSION_H) || \
     (OSIF_SOFTWARE_SEMAPHORE_SW_MINOR_VERSION_C != OSIF_SOFTWARE_SEMAPHORE_SW_MINOR_VERSION_H) || \
     (OSIF_SOFTWARE_SEMAPHORE_SW_PATCH_VERSION_C != OSIF_SOFTWARE_SEMAPHORE_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of OsIf_Software_Semaphore.c and OsIf_Software_Semaphore.h are different"
#endif

/*==================================================================================================
 *                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef OSIF_SOFTWARE_SEMAPHORE_ENABLE
#if (OSIF_SOFTWARE_SEMAPHORE_ENABLE == STD_ON)

#define BASENXP_START_SEC_CODE
#include "BaseNXP_MemMap.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Software_Semaphore_Lock.
 * Description   : Lock semaphore.
 * 
 *END**************************************************************************/
boolean OsIf_Software_Semaphore_Lock(const uint32 *Semaphore,
                                     uint32 Lockval
                                    )
{
    uint32 u32Result = 0U;
    /* Store lock value to shemaphore if it is unlock */
/*LDRA_NOANALYSIS*/
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    ASM_KEYWORD (" LDREX %0, [%1] \n\t"
                 " CMP %0, #0 \n\t"
                 " IT EQ\n\t"
                 " STREXEQ %0, %2, [%1]"
                 : "=&r" (u32Result) 
                 : "r" (Semaphore), "r" (Lockval));
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
/*LDRA_ANALYSIS*/
    return (u32Result == 0U);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Software_Semaphore_Unlock.
 * Description   : Unlock semaphore.
 * 
 *END**************************************************************************/
boolean OsIf_Software_Semaphore_Unlock(const uint32 *Semaphore,
                                       uint32 Lockval
                                      )
{
    uint32 u32Result = 0U;
    uint32 u32UnlockValue = OSIF_SOFTWARE_SEMAPHORE_UNLOCKED_VALUE;
    /* Store unlock value to shemaphore if the lock value is matched */
/*LDRA_NOANALYSIS*/
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    ASM_KEYWORD (" LDREX %0, [%2] \n\t"
                 " CMP %0, %3 \n\t"
                 " IT EQ\n\t"
                 " STREXEQ %0, %1, [%2]"
                 : "=&r" (u32Result)
                 : "r" (u32UnlockValue), "r" (Semaphore), "r" (Lockval));
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
/*LDRA_ANALYSIS*/
    return (u32Result == 0U);
}

#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"

#endif /* #if (OSIF_SOFTWARE_SEMAPHORE_ENABLE == STD_ON) */
#endif /* #ifdef OSIF_SOFTWARE_SEMAPHORE_ENABLE */

#ifdef __cplusplus
}
#endif

/** @} */
