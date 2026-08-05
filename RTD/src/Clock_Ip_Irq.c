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
*   @file       Clock_Ip_Irq.c
*   @version    3.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Ip Driver
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
#include "Clock_Ip_Private.h"
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_IRQ_VENDOR_ID_C                      43
#define CLOCK_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_IRQ_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_IRQ_SW_MAJOR_VERSION_C               3
#define CLOCK_IP_IRQ_SW_MINOR_VERSION_C               0
#define CLOCK_IP_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Irq.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_IRQ_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Irq.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Irq.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_IRQ_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Irq.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Irq.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_IRQ_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_IRQ_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_IRQ_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Irq.c and Clock_Ip_Private.h are different"
#endif
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
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                    GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/



/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef CLOCK_IP_PMC_SCG_CMU
#if CLOCK_IP_CMU_INFO_SIZE > 0U
#ifndef CLOCK_IP_POWER_NOTIFICATIONS
    ISR(Mcu_PMC_SCG_CMU_Isr);
/**
* @brief       This function represents the ISR handler for CMU PMC SCG related events.
* @details     This interrupt is triggered if one of the enabled CMU PMC SCG detect an out of range clock.
*
* @return       void
*
*/
    ISR(Mcu_PMC_SCG_CMU_Isr)
    {
        /* CMU1 interrupt */
        Clock_Ip_CMU_ClockFailInt();

        EXIT_INTERRUPT();
    }
#elif (STD_OFF == CLOCK_IP_POWER_NOTIFICATIONS)

    ISR(Mcu_PMC_SCG_CMU_Isr);
/**
* @brief       This function represents the ISR handler for CMU PMC SCG related events.
* @details     This interrupt is triggered if one of the enabled CMU PMC SCG detect an out of range clock.
*
* @return       void
*
*/
    ISR(Mcu_PMC_SCG_CMU_Isr)
    {
        /* CMU1 interrupt */
        Clock_Ip_CMU_ClockFailInt();

        EXIT_INTERRUPT();
    }
#endif
#endif
#endif



#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
