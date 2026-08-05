/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : PORT_CI
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
*   @file    Port_Cfg.c
*
*   @addtogroup Port_CFG
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Port.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
* @brief        Parameters that shall be published within the Port driver header file and also in the
*               module description file
* @details      The integration of incompatible files shall be avoided.
*
*/
#define PORT_VENDOR_ID_CFG_C                       43
#define PORT_AR_RELEASE_MAJOR_VERSION_CFG_C        4
#define PORT_AR_RELEASE_MINOR_VERSION_CFG_C        7
#define PORT_AR_RELEASE_REVISION_VERSION_CFG_C     0
#define PORT_SW_MAJOR_VERSION_CFG_C                3
#define PORT_SW_MINOR_VERSION_CFG_C                0
#define PORT_SW_PATCH_VERSION_CFG_C                0

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if Port_Cfg.c and Port.h are of the same Autosar version */
#if (PORT_VENDOR_ID_CFG_C != PORT_VENDOR_ID)
    #error "Port_Cfg.c and Port.h have different vendor ids"
#endif
/* Check if Port_Cfg.c and Port.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_CFG_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_CFG_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_CFG_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Port_Cfg.c and Port.h are different"
#endif
/* Check if Port_Cfg.c and Port.h are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_CFG_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_CFG_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_CFG_C != PORT_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port_Cfg.c and Port.h are different"
#endif

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/

/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/
#define PORT_START_SEC_CONST_16
#include "Port_MemMap.h"

#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief Port Pin description data
*/
const uint16 Port_au16PinDescription[8][10] = 
{
    /*  Mode PORT_ALT0_FUNC_MODE: */
    {
        /* Pads   0 ...  15 : PORT0_ADC0_SE0 |
        PORT0_CMP0_IN0 |
        PORT1_ADC0_SE1 |
        PORT1_CMP0_IN1 |
        PORT2_ADC1_SE0 |
        PORT3_ADC1_SE1 |
        PORT4_DISABLED |
        PORT5_DISABLED |
        PORT6_ADC0_SE2 |
        PORT7_ADC0_SE3 |
        PORT8_DISABLED |
        PORT9_DISABLED |
        PORT10_DISABLED |
        PORT11_DISABLED |
        PORT12_DISABLED |
        PORT13_DISABLED |
        PORT14_DISABLED |
        PORT15_ADC1_SE12 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  16 ...  31 : PORT16_ADC1_SE13 |
        PORT17_DISABLED |
        PORT25_DISABLED |
        PORT26_DISABLED |
        PORT27_DISABLED |
        PORT28_DISABLED |
        PORT29_DISABLED |
        PORT30_DISABLED |
        PORT31_DISABLED */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  32 ...  47 : PORT32_ADC0_SE4 |
        PORT32_ADC1_SE14 |
        PORT33_ADC0_SE5 |
        PORT33_ADC1_SE15 |
        PORT34_ADC0_SE6 |
        PORT35_ADC0_SE7 |
        PORT36_DISABLED |
        PORT37_DISABLED |
        PORT38_XTAL |
        PORT39_EXTAL |
        PORT40_DISABLED |
        PORT41_DISABLED |
        PORT42_DISABLED |
        PORT43_DISABLED |
        PORT44_ADC1_SE7 |
        PORT45_ADC1_SE8 |
        PORT45_ADC0_SE8 |
        PORT46_ADC1_SE9 |
        PORT46_ADC0_SE9 |
        PORT47_ADC1_SE14 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  48 ...  63 : PORT48_ADC1_SE15 |
        PORT49_DISABLED |
        PORT50_ADC0_SE16 |
        PORT52_ADC0_SE17 |
        PORT53_ADC0_SE18 |
        PORT54_ADC0_SE19 |
        PORT55_ADC0_SE20 |
        PORT57_ADC0_SE21 |
        PORT59_ADC0_SE22 |
        PORT60_ADC0_SE23 |
        PORT61_ADC0_SE24 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13)
                ),
        /* Pads  64 ...  79 : PORT64_ADC0_SE8 |
        PORT65_ADC0_SE9 |
        PORT66_ADC0_SE10 |
        PORT66_CMP0_IN5 |
        PORT67_ADC0_SE11 |
        PORT67_CMP0_IN4 |
        PORT68_CMP0_IN2 |
        PORT69_DISABLED |
        PORT70_ADC1_SE4 |
        PORT71_ADC1_SE5 |
        PORT72_DISABLED |
        PORT73_DISABLED |
        PORT74_DISABLED |
        PORT75_DISABLED |
        PORT76_DISABLED |
        PORT77_DISABLED |
        PORT78_ADC0_SE12 |
        PORT79_ADC0_SE13 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  80 ...  95 : PORT80_ADC0_SE14 |
        PORT81_ADC0_SE15 |
        PORT83_ADC0_SE25 |
        PORT87_ADC0_SE26 |
        PORT91_ADC0_SE27 |
        PORT92_ADC0_SE28 |
        PORT93_ADC0_SE29 |
        PORT94_ADC0_SE30 |
        PORT95_ADC0_SE31 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  96 ... 111 : PORT96_DISABLED |
        PORT97_DISABLED |
        PORT98_ADC1_SE2 |
        PORT99_ADC1_SE3 |
        PORT100_ADC1_SE6 |
        PORT101_DISABLED |
        PORT102_CMP0_IN7 |
        PORT103_CMP0_IN6 |
        PORT104_DISABLED |
        PORT105_DISABLED |
        PORT106_DISABLED |
        PORT107_DISABLED |
        PORT108_DISABLED |
        PORT109_DISABLED |
        PORT110_DISABLED |
        PORT111_DISABLED */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 112 ... 127 : PORT112_DISABLED |
        PORT113_DISABLED |
        PORT114_ADC1_SE16 |
        PORT115_ADC1_SE17 |
        PORT118_ADC1_SE18 |
        PORT119_ADC1_SE19 |
        PORT120_ADC1_SE20 |
        PORT123_ADC1_SE21 |
        PORT124_ADC1_SE22 |
        PORT125_ADC1_SE23 |
        PORT126_ADC1_SE24 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14)
                ),
        /* Pads 128 ... 143 : PORT128_DISABLED |
        PORT129_DISABLED |
        PORT130_ADC1_SE10 |
        PORT131_DISABLED |
        PORT132_DISABLED |
        PORT133_DISABLED |
        PORT134_ADC1_SE11 |
        PORT135_DISABLED |
        PORT136_CMP0_IN3 |
        PORT137_DISABLED |
        PORT138_DISABLED |
        PORT139_DISABLED |
        PORT140_DISABLED |
        PORT141_DISABLED |
        PORT142_DISABLED |
        PORT143_DISABLED */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 144 ... 159 : PORT144_DISABLED |
        PORT147_ADC1_SE25 |
        PORT148_ADC1_SE26 |
        PORT149_ADC1_SE27 |
        PORT150_ADC1_SE28 |
        PORT151_ADC1_SE29 |
        PORT152_ADC1_SE30 |
        PORT153_ADC1_SE31 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9)
                )
    }
    ,
    /*  Mode PORT_GPIO_MODE: */
    {
        /* Pads   0 ...  15 : PORT0_GPIO |
        PORT1_GPIO |
        PORT2_GPIO |
        PORT3_GPIO |
        PORT4_GPIO |
        PORT5_GPIO |
        PORT6_GPIO |
        PORT7_GPIO |
        PORT8_GPIO |
        PORT9_GPIO |
        PORT10_GPIO |
        PORT11_GPIO |
        PORT12_GPIO |
        PORT13_GPIO |
        PORT14_GPIO |
        PORT15_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  16 ...  31 : PORT16_GPIO |
        PORT17_GPIO |
        PORT25_GPIO |
        PORT26_GPIO |
        PORT27_GPIO |
        PORT28_GPIO |
        PORT29_GPIO |
        PORT30_GPIO |
        PORT31_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  32 ...  47 : PORT32_GPIO |
        PORT33_GPIO |
        PORT34_GPIO |
        PORT35_GPIO |
        PORT36_GPIO |
        PORT37_GPIO |
        PORT38_GPIO |
        PORT39_GPIO |
        PORT40_GPIO |
        PORT41_GPIO |
        PORT42_GPIO |
        PORT43_GPIO |
        PORT44_GPIO |
        PORT45_GPIO |
        PORT46_GPIO |
        PORT47_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  48 ...  63 : PORT48_GPIO |
        PORT49_GPIO |
        PORT50_GPIO |
        PORT52_GPIO |
        PORT53_GPIO |
        PORT54_GPIO |
        PORT55_GPIO |
        PORT57_GPIO |
        PORT59_GPIO |
        PORT60_GPIO |
        PORT61_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13)
                ),
        /* Pads  64 ...  79 : PORT64_GPIO |
        PORT65_GPIO |
        PORT66_GPIO |
        PORT67_GPIO |
        PORT68_GPIO |
        PORT69_GPIO |
        PORT70_GPIO |
        PORT71_GPIO |
        PORT72_GPIO |
        PORT73_GPIO |
        PORT74_GPIO |
        PORT75_GPIO |
        PORT76_GPIO |
        PORT77_GPIO |
        PORT78_GPIO |
        PORT79_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  80 ...  95 : PORT80_GPIO |
        PORT81_GPIO |
        PORT83_GPIO |
        PORT87_GPIO |
        PORT91_GPIO |
        PORT92_GPIO |
        PORT93_GPIO |
        PORT94_GPIO |
        PORT95_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  96 ... 111 : PORT96_GPIO |
        PORT97_GPIO |
        PORT98_GPIO |
        PORT99_GPIO |
        PORT100_GPIO |
        PORT101_GPIO |
        PORT102_GPIO |
        PORT103_GPIO |
        PORT104_GPIO |
        PORT105_GPIO |
        PORT106_GPIO |
        PORT107_GPIO |
        PORT108_GPIO |
        PORT109_GPIO |
        PORT110_GPIO |
        PORT111_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 112 ... 127 : PORT112_GPIO |
        PORT113_GPIO |
        PORT114_GPIO |
        PORT115_GPIO |
        PORT118_GPIO |
        PORT119_GPIO |
        PORT120_GPIO |
        PORT123_GPIO |
        PORT124_GPIO |
        PORT125_GPIO |
        PORT126_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14)
                ),
        /* Pads 128 ... 143 : PORT128_GPIO |
        PORT129_GPIO |
        PORT130_GPIO |
        PORT131_GPIO |
        PORT132_GPIO |
        PORT133_GPIO |
        PORT134_GPIO |
        PORT135_GPIO |
        PORT136_GPIO |
        PORT137_GPIO |
        PORT138_GPIO |
        PORT139_GPIO |
        PORT140_GPIO |
        PORT141_GPIO |
        PORT142_GPIO |
        PORT143_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 144 ... 159 : PORT144_GPIO |
        PORT147_GPIO |
        PORT148_GPIO |
        PORT149_GPIO |
        PORT150_GPIO |
        PORT151_GPIO |
        PORT152_GPIO |
        PORT153_GPIO */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9)
                )
    }
    ,
    /*  Mode PORT_ALT2_FUNC_MODE: */
    {
        /* Pads   0 ...  15 : PORT0_FTM2_CH1 |
        PORT1_FTM1_CH1 |
        PORT2_FTM3_CH0 |
        PORT3_FTM3_CH1 |
        PORT6_FTM0_FLT1 |
        PORT7_FTM0_FLT2 |
        PORT8_LPUART2_RX |
        PORT9_LPUART2_TX |
        PORT10_FTM1_CH4 |
        PORT11_FTM1_CH5 |
        PORT12_FTM1_CH6 |
        PORT13_FTM1_CH7 |
        PORT14_FTM0_FLT0 |
        PORT15_FTM1_CH2 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  16 ...  31 : PORT16_FTM1_CH3 |
        PORT17_FTM0_CH6 |
        PORT25_FTM5_CH0 |
        PORT26_FTM5_CH1 |
        PORT27_FTM5_CH2 |
        PORT28_FTM5_CH3 |
        PORT29_FTM5_CH4 |
        PORT30_FTM5_CH5 |
        PORT31_FTM5_CH6 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  32 ...  47 : PORT32_LPUART0_RX |
        PORT33_LPUART0_TX |
        PORT34_FTM1_CH0 |
        PORT35_FTM1_CH1 |
        PORT36_FTM0_CH4 |
        PORT37_FTM0_CH5 |
        PORT38_LPI2C0_SDA |
        PORT39_LPI2C0_SCL |
        PORT40_FTM3_CH0 |
        PORT41_FTM3_CH1 |
        PORT42_FTM3_CH2 |
        PORT43_FTM3_CH3 |
        PORT44_FTM0_CH0 |
        PORT45_FTM0_CH1 |
        PORT46_FTM0_CH2 |
        PORT47_FTM0_CH3 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  48 ...  63 : PORT48_FTM0_CH4 |
        PORT49_FTM0_CH5 |
        PORT50_FTM5_CH7 |
        PORT52_FTM6_CH0 |
        PORT53_FTM6_CH1 |
        PORT54_FTM6_CH2 |
        PORT55_FTM6_CH3 |
        PORT57_FTM6_CH5 |
        PORT59_FTM6_CH7 |
        PORT60_FTM7_CH0 |
        PORT61_FTM7_CH1 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13)
                ),
        /* Pads  64 ...  79 : PORT64_FTM0_CH0 |
        PORT65_FTM0_CH1 |
        PORT66_FTM0_CH2 |
        PORT67_FTM0_CH3 |
        PORT68_FTM1_CH0 |
        PORT69_FTM2_CH0 |
        PORT70_LPUART1_RX |
        PORT71_LPUART1_TX |
        PORT72_LPUART1_RX |
        PORT73_LPUART1_TX |
        PORT74_FTM3_CH4 |
        PORT75_FTM3_CH5 |
        PORT76_FTM3_CH6 |
        PORT77_FTM3_CH7 |
        PORT78_FTM1_CH2 |
        PORT79_FTM1_CH3 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  80 ...  95 : PORT80_FTM1_FLT2 |
        PORT81_FTM1_FLT3 |
        PORT83_FTM7_CH5 |
        PORT87_LPSPI0_SCK |
        PORT91_FTM4_CH4 |
        PORT92_FTM4_CH7 |
        PORT93_FTM5_CH2 |
        PORT94_FTM5_CH4 |
        PORT95_FTM5_CH6 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  96 ... 111 : PORT96_FTM0_CH2 |
        PORT97_FTM0_CH3 |
        PORT98_FTM3_CH4 |
        PORT99_FTM3_CH5 |
        PORT100_FTM0_FLT3 |
        PORT101_FTM2_CH3 |
        PORT102_LPUART2_RX |
        PORT103_LPUART2_TX |
        PORT104_LPI2C1_SDA |
        PORT105_LPI2C1_SCL |
        PORT106_FTM2_CH0 |
        PORT107_FTM2_CH1 |
        PORT108_FTM2_CH2 |
        PORT109_FTM2_CH4 |
        PORT110_FTM2_CH5 |
        PORT111_FTM0_CH0 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 112 ... 127 : PORT112_FTM0_CH1 |
        PORT113_FTM0_FLT2 |
        PORT114_FTM5_CH7 |
        PORT115_FTM6_CH0 |
        PORT118_FTM6_CH3 |
        PORT119_FTM6_CH4 |
        PORT120_FTM6_CH5 |
        PORT123_FTM7_CH0 |
        PORT124_FTM7_CH1 |
        PORT125_FTM7_CH2 |
        PORT126_FTM7_CH3 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14)
                ),
        /* Pads 128 ... 143 : PORT128_LPSPI0_SCK |
        PORT129_LPSPI0_SIN |
        PORT130_LPSPI0_SOUT |
        PORT131_FTM0_FLT0 |
        PORT132_ETM_TRACE_D1 |
        PORT133_TCLK2 |
        PORT134_LPSPI0_PCS2 |
        PORT135_FTM0_CH7 |
        PORT136_FTM0_CH6 |
        PORT137_FTM0_CH7 |
        PORT138_CLKOUT |
        PORT139_LPSPI2_PCS0 |
        PORT140_FTM0_FLT3 |
        PORT141_FTM4_CH5 |
        PORT142_FTM0_FLT1 |
        PORT143_LPUART1_CTS */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 144 ... 159 : PORT144_LPUART1_RTS |
        PORT147_FTM7_CH7 |
        PORT148_FTM4_CH0 |
        PORT149_FTM4_CH1 |
        PORT150_FTM4_CH2 |
        PORT151_FTM4_CH3 |
        PORT152_FTM4_CH4 |
        PORT153_FTM4_CH5 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9)
                )
    }
    ,
    /*  Mode PORT_ALT3_FUNC_MODE: */
    {
        /* Pads   0 ...  15 : PORT0_LPI2C0_SCLS |
        PORT1_LPI2C0_SDAS |
        PORT2_LPI2C0_SDA |
        PORT3_LPI2C0_SCL |
        PORT5_TCLK1 |
        PORT6_LPSPI1_PCS1 |
        PORT7_FTM5_CH3 |
        PORT8_LPSPI2_SOUT |
        PORT9_LPSPI2_PCS0 |
        PORT12_CAN1_RX |
        PORT13_CAN1_TX |
        PORT14_FTM3_FLT1 |
        PORT15_LPSPI0_PCS3 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  16 ...  31 : PORT16_LPSPI1_PCS2 |
        PORT17_FTM3_FLT0 |
        PORT26_LPSPI1_PCS0 |
        PORT27_LPSPI1_SOUT |
        PORT28_LPSPI1_SCK |
        PORT30_LPUART2_RX */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(14)
                ),
        /* Pads  32 ...  47 : PORT32_LPSPI0_PCS0 |
        PORT33_LPSPI0_SOUT |
        PORT34_LPSPI0_SCK |
        PORT35_LPSPI0_SIN |
        PORT36_LPSPI0_SOUT |
        PORT37_LPSPI0_PCS1 |
        PORT41_LPI2C0_SCLS |
        PORT42_LPI2C0_SDAS |
        PORT43_LPI2C0_HREQ |
        PORT44_FTM3_FLT2 |
        PORT45_FTM3_FLT1 |
        PORT46_LPSPI1_SCK |
        PORT47_LPSPI1_SIN */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  48 ...  63 : PORT48_LPSPI1_SOUT |
        PORT49_LPSPI1_PCS3 |
        PORT54_MII_CRS |
        PORT55_LPUART1_RX */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7)
                ),
        /* Pads  64 ...  79 : PORT64_LPSPI2_SIN |
        PORT65_LPSPI2_SOUT |
        PORT66_CAN0_RX |
        PORT67_CAN0_TX |
        PORT68_RTC_CLKOUT |
        PORT69_RTC_CLKOUT |
        PORT70_CAN1_RX |
        PORT71_CAN1_TX |
        PORT72_FTM1_FLT0 |
        PORT73_FTM1_FLT1 |
        PORT75_FTM4_CH2 |
        PORT76_FTM2_CH6 |
        PORT77_FTM2_CH7 |
        PORT78_LPSPI2_PCS0 |
        PORT79_LPSPI2_SCK */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  80 ...  95 : PORT80_CAN2_RX |
        PORT81_CAN2_TX |
        PORT94_FXIO_D0 |
        PORT95_FXIO_D1 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  96 ... 111 : PORT96_LPSPI1_SCK |
        PORT97_LPSPI1_SIN |
        PORT98_LPSPI1_SOUT |
        PORT99_LPSPI1_PCS0 |
        PORT100_FTM3_FLT3 |
        PORT101_LPTMR0_ALT2 |
        PORT104_MII_RXD3 |
        PORT105_FXIO_D0 |
        PORT106_FTM2_QD_PHB |
        PORT107_FTM2_QD_PHA |
        PORT108_LPI2C1_HREQ |
        PORT109_LPUART1_RX |
        PORT110_LPUART1_TX |
        PORT111_ETM_TRACE_D3 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 112 ... 127 : PORT112_ETM_TRACE_D2 |
        PORT113_LPUART2_RX |
        PORT114_FXIO_D2 |
        PORT115_FXIO_D3 |
        PORT126_FTM6_FLT1 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(14)
                ),
        /* Pads 128 ... 143 : PORT128_TCLK1 |
        PORT129_LPI2C0_HREQ |
        PORT130_LPTMR0_ALT3 |
        PORT131_LPUART2_RTS |
        PORT132_FTM2_QD_PHB |
        PORT133_FTM2_QD_PHA |
        PORT134_FTM7_FLT1 |
        PORT135_FTM3_FLT0 |
        PORT137_LPUART2_CTS |
        PORT138_LPSPI2_PCS1 |
        PORT139_LPTMR0_ALT1 |
        PORT140_LPUART2_TX |
        PORT141_LPSPI2_PCS2 |
        PORT143_LPSPI2_SCK */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 144 ... 159 : PORT144_LPSPI2_SIN |
        PORT152_CAN2_TX |
        PORT153_CAN2_RX */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9)
                )
    }
    ,
    /*  Mode PORT_ALT4_FUNC_MODE: */
    {
        /* Pads   0 ...  15 : PORT0_FXIO_D2 |
        PORT1_FXIO_D3 |
        PORT2_EWM_OUT_B |
        PORT3_EWM_IN |
        PORT4_CMP0_OUT |
        PORT6_FTM5_CH5 |
        PORT7_RTC_CLKIN |
        PORT8_FXIO_D6 |
        PORT9_FXIO_D7 |
        PORT10_FXIO_D0 |
        PORT11_FXIO_D1 |
        PORT12_LPI2C1_SDAS |
        PORT13_LPI2C1_SCLS |
        PORT14_EWM_IN |
        PORT15_LPSPI2_PCS3 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  16 ...  31 : PORT17_EWM_OUT_B |
        PORT26_LPSPI0_PCS0 |
        PORT27_LPUART0_TX |
        PORT28_LPUART0_RX |
        PORT29_LPUART2_TX |
        PORT30_LPSPI0_SOUT |
        PORT31_LPSPI0_PCS1 */
        (uint16)( SHL_PAD_U16(1) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  32 ...  47 : PORT32_LPTMR0_ALT3 |
        PORT33_TCLK0 |
        PORT34_FTM1_QD_PHB |
        PORT35_FTM1_QD_PHA |
        PORT37_LPSPI0_PCS0 |
        PORT40_SAI1_BCLK |
        PORT41_SAI1_D0 |
        PORT42_SAI1_MCLK |
        PORT44_CAN2_RX |
        PORT45_CAN2_TX */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13)
                ),
        /* Pads  48 ...  63 : PORT49_FTM5_FLT1 |
        PORT50_LPSPI1_PCS1 |
        PORT55_MII_COL */
        (uint16)( SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(7)
                ),
        /* Pads  64 ...  79 : PORT64_MII_RMII_RXD_1 |
        PORT65_MII_RMII_RXD_1 |
        PORT66_LPUART0_RX |
        PORT67_LPUART0_TX |
        PORT69_LPI2C1_HREQ |
        PORT70_FTM3_CH2 |
        PORT71_FTM3_CH3 |
        PORT72_FTM5_CH1 |
        PORT73_FTM5_CH0 |
        PORT76_LPUART2_CTS |
        PORT77_LPUART2_RTS |
        PORT78_MII_COL |
        PORT79_MII_CRS */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  80 ...  95 : PORT80_LPI2C1_SDAS |
        PORT81_LPI2C1_SCLS |
        PORT94_LPI2C1_SDAS |
        PORT95_LPI2C1_SDA */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  96 ... 111 : PORT96_FTM2_CH0 |
        PORT97_FTM2_CH1 |
        PORT98_FXIO_D4 |
        PORT99_FXIO_D5 |
        PORT101_FTM2_FLT1 |
        PORT102_FTM2_FLT2 |
        PORT103_FTM2_FLT3 |
        PORT104_FTM2_FLT2 |
        PORT105_FTM2_FLT3 |
        PORT106_ETM_TRACE_D3 |
        PORT107_ETM_TRACE_D2 |
        PORT108_ETM_TRACE_D1 |
        PORT111_LPSPI0_SCK */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 112 ... 127 : PORT112_LPSPI0_SIN |
        PORT113_FTM5_FLT1 |
        PORT114_LPI2C1_SCLS |
        PORT115_LPI2C1_SCL */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3)
                ),
        /* Pads 128 ... 143 : PORT128_LPI2C1_SDA |
        PORT129_LPI2C1_SCL |
        PORT130_FTM3_CH6 |
        PORT131_FTM2_FLT0 |
        PORT132_FTM2_CH2 |
        PORT133_FTM2_CH3 |
        PORT134_FTM3_CH7 |
        PORT138_FTM2_CH4 |
        PORT139_FTM2_CH5 |
        PORT140_FTM5_FLT0 |
        PORT141_FTM2_FLT0 |
        PORT142_FTM2_FLT1 |
        PORT143_FTM2_CH6 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 144 ... 159 : PORT144_FTM2_CH7 */
        (uint16)( SHL_PAD_U16(0)
                )
    }
    ,
    /*  Mode PORT_ALT5_FUNC_MODE: */
    {
        /* Pads   0 ...  15 : PORT0_FTM2_QD_PHA |
        PORT1_FTM1_QD_PHA |
        PORT2_FXIO_D4 |
        PORT3_FXIO_D5 |
        PORT4_EWM_OUT_B |
        PORT8_FTM3_FLT3 |
        PORT9_FTM3_FLT2 |
        PORT11_CMP0_RRT |
        PORT15_FTM7_FLT0 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  16 ...  31 : PORT17_FTM5_FLT0 |
        PORT27_CAN0_TX |
        PORT28_CAN0_RX |
        PORT29_LPSPI1_SIN */
        (uint16)( SHL_PAD_U16(1) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13)
                ),
        /* Pads  32 ...  47 : PORT32_CAN0_RX |
        PORT33_CAN0_TX |
        PORT36_MII_RMII_MDIO |
        PORT37_CLKOUT |
        PORT44_FTM6_FLT1 |
        PORT45_FTM6_FLT0 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13)
                ),
        /* Pads  48 ...  63 : PORT54_LPUART1_TX |
        PORT57_LPSPI2_PCS0 |
        PORT59_LPSPI2_SOUT |
        PORT60_LPSPI2_SIN |
        PORT61_LPSPI2_SCK */
        (uint16)( SHL_PAD_U16(6) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13)
                ),
        /* Pads  64 ...  79 : PORT64_MII_RMII_RXD_0 |
        PORT65_MII_RMII_RXD_0 |
        PORT66_MII_RMII_TXD_0 |
        PORT67_MII_TX_ER |
        PORT68_EWM_IN */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4)
                ),
        /* Pads  80 ...  95 : PORT80_MII_RMII_RX_ER |
        PORT81_MII_RMII_RX_DV |
        PORT83_LPSPI2_PCS1 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(3)
                ),
        /* Pads  96 ... 111 : PORT96_ETM_TRACE_D0 |
        PORT97_SAI0_MCLK |
        PORT98_FXIO_D6 |
        PORT99_FXIO_D7 |
        PORT101_MII_TXD3 |
        PORT102_MII_TXD2 |
        PORT103_MII_RMII_TXD_1 |
        PORT104_FXIO_D1 |
        PORT105_MII_RXD2 |
        PORT106_MII_RX_CLK |
        PORT107_MII_RMII_TX_CLK |
        PORT108_MII_RMII_TX_EN |
        PORT109_ENET_TMR1 |
        PORT110_ENET_TMR0 |
        PORT111_ENET_TMR2 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 112 ... 127 : PORT112_CMP0_RRT */
        (uint16)( SHL_PAD_U16(0)
                ),
        /* Pads 128 ... 143 : PORT128_LPSPI1_SOUT |
        PORT129_LPSPI1_PCS0 |
        PORT132_CAN0_RX |
        PORT133_CAN0_TX |
        PORT136_MII_RMII_MDC |
        PORT137_ENET_TMR3 |
        PORT143_FTM4_FLT1 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 144 ... 159 : PORT144_FTM4_FLT0 */
        (uint16)( SHL_PAD_U16(0)
                )
    }
    ,
    /*  Mode PORT_ALT6_FUNC_MODE: */
    {
        /* Pads   0 ...  15 : PORT0_LPUART0_CTS |
        PORT1_LPUART0_RTS |
        PORT2_LPUART0_RX |
        PORT3_LPUART0_TX |
        PORT6_LPUART1_CTS |
        PORT7_LPUART1_RTS |
        PORT8_FTM4_FLT1 |
        PORT9_FTM1_FLT3 |
        PORT11_SAI0_SYNC |
        PORT12_FTM2_QD_PHB |
        PORT13_FTM2_QD_PHA |
        PORT14_FTM1_FLT0 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14)
                ),
        /* Pads 16 ... 31 */
        (uint16)0x0000,
        /* Pads  32 ...  47 : PORT32_FTM4_CH6 |
        PORT33_FTM4_CH5 |
        PORT34_TRGMUX_IN3 |
        PORT35_TRGMUX_IN2 |
        PORT36_TRGMUX_IN1 |
        PORT37_TRGMUX_IN0 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5)
                ),
        /* Pads 48 ... 63 */
        (uint16)0x0000,
        /* Pads  64 ...  79 : PORT64_FTM1_CH6 |
        PORT65_FTM1_CH7 |
        PORT66_ETM_TRACE_CLKOUT |
        PORT67_QSPI_A_CS |
        PORT68_FTM1_QD_PHB |
        PORT69_FTM2_QD_PHB |
        PORT70_FTM1_QD_PHB |
        PORT71_FTM1_QD_PHA |
        PORT72_LPUART0_CTS |
        PORT73_LPUART0_RTS |
        PORT74_TRGMUX_IN11 |
        PORT75_TRGMUX_IN10 |
        PORT78_TRGMUX_IN9 |
        PORT79_TRGMUX_IN8 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(14) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 80 ... 95 */
        (uint16)0x0000,
        /* Pads  96 ... 111 : PORT96_FXIO_D0 |
        PORT97_FXIO_D1 |
        PORT98_TRGMUX_IN5 |
        PORT99_TRGMUX_IN4 |
        PORT101_TRGMUX_IN7 |
        PORT103_ETM_TRACE_D0 |
        PORT104_FTM1_CH4 |
        PORT105_FTM1_CH5 |
        PORT106_CLKOUT |
        PORT107_LPUART2_CTS |
        PORT108_LPUART2_RTS */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12)
                ),
        /* Pads 112 ... 127 : PORT112_ETM_TRACE_CLKOUT */
        (uint16)( SHL_PAD_U16(0)
                ),
        /* Pads 128 ... 143 : PORT128_FTM1_FLT2 |
        PORT129_FTM1_FLT1 |
        PORT130_LPUART1_CTS |
        PORT131_TRGMUX_IN6 |
        PORT132_FXIO_D6 |
        PORT133_FXIO_D7 |
        PORT134_LPUART1_RTS |
        PORT138_FXIO_D4 |
        PORT139_FXIO_D5 |
        PORT143_FXIO_D2 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 144 ... 159 : PORT144_FXIO_D3 */
        (uint16)( SHL_PAD_U16(0)
                )
    }
    ,
    /*  Mode PORT_ALT7_FUNC_MODE: */
    {
        /* Pads   0 ...  15 : PORT0_TRGMUX_OUT3 |
        PORT1_TRGMUX_OUT0 |
        PORT4_JTAG_TMS_SWD_DIO |
        PORT5_RESET_B |
        PORT9_FTM4_FLT0 |
        PORT10_JTAG_TDO_NOETM_TRACE_SWO |
        PORT12_SAI0_BCLK |
        PORT13_SAI0_D0 |
        PORT14_SAI0_D3 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14)
                ),
        /* Pads 16 ... 31 */
        (uint16)0x0000,
        /* Pads  32 ...  47 : PORT36_QSPI_B_IO0 |
        PORT37_MII_RMII_MDC */
        (uint16)( SHL_PAD_U16(4) |
                  SHL_PAD_U16(5)
                ),
        /* Pads 48 ... 63 */
        (uint16)0x0000,
        /* Pads  64 ...  79 : PORT64_QSPI_B_RWDS |
        PORT65_QSPI_B_SCK |
        PORT66_QSPI_A_IO3 |
        PORT67_QSPI_B_IO3 |
        PORT68_JTAG_TCLK_SWD_CLK |
        PORT69_JTAG_TDI |
        PORT79_QSPI_B_CS */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(15)
                ),
        /* Pads  80 ...  95 : PORT80_QSPI_B_IO7 |
        PORT81_QSPI_B_IO6 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1)
                ),
        /* Pads  96 ... 111 : PORT96_TRGMUX_OUT1 |
        PORT97_TRGMUX_OUT2 |
        PORT99_NMI_B |
        PORT101_QSPI_B_IO2 |
        PORT102_QSPI_B_IO1 |
        PORT103_QSPI_A_IO1 |
        PORT104_QSPI_B_IO5 |
        PORT105_QSPI_B_IO4 |
        PORT106_QSPI_A_SCK |
        PORT107_QSPI_A_IO0 |
        PORT108_QSPI_A_IO2 |
        PORT109_RTC_CLKOUT |
        PORT110_CLKOUT */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(6) |
                  SHL_PAD_U16(7) |
                  SHL_PAD_U16(8) |
                  SHL_PAD_U16(9) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(12) |
                  SHL_PAD_U16(13) |
                  SHL_PAD_U16(14)
                ),
        /* Pads 112 ... 127 */
        (uint16)0x0000,
        /* Pads 128 ... 143 : PORT128_SAI0_D2 |
        PORT129_SAI0_D1 |
        PORT130_SAI1_SYNC |
        PORT131_CMP0_OUT |
        PORT132_EWM_OUT_B |
        PORT133_EWM_IN |
        PORT138_TRGMUX_OUT4 |
        PORT139_TRGMUX_OUT5 |
        PORT143_TRGMUX_OUT6 */
        (uint16)( SHL_PAD_U16(0) |
                  SHL_PAD_U16(1) |
                  SHL_PAD_U16(2) |
                  SHL_PAD_U16(3) |
                  SHL_PAD_U16(4) |
                  SHL_PAD_U16(5) |
                  SHL_PAD_U16(10) |
                  SHL_PAD_U16(11) |
                  SHL_PAD_U16(15)
                ),
        /* Pads 144 ... 159 : PORT144_TRGMUX_OUT7 */
        (uint16)( SHL_PAD_U16(0)
                )
    }

};
#endif

#define PORT_STOP_SEC_CONST_16
#include "Port_MemMap.h"
/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/

/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/

/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/

/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */
