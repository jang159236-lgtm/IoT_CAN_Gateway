/* Copyright 2019, 2023, 2025 NXP */
/* License: BSD 3-clause
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * main implementation: use this 'C' sample to create your own application
 *
// */
#include "S32K148.h"
#include "Dio_Cfg.h"
#include "Clock_Ip.h"
#include "Port_Cfg.h"
#include "Port_Ci_Port_Ip.h"
#include "Gpio_Dio_Ip.h"
#include "Dio.h"
#include "CanIf_Cfg.h"
#include "Port.h"
#include <stdio.h>
#include "Mcu.h"
#include "CanIf.h"
#include "Can_43_FLEXCAN.h"
#include "Platform.h"
#include "CDD.h"
#include "Lpuart_Uart_Ip.h"
#include "Lpuart_Uart_Ip_PBcfg.h"
#include "Uart.h"
#include "CDD_I2c.h"
#include "sht20.h"


extern Port_Ci_Port_Ip_PinSettingsConfig g_pin_mux_InitConfigArr_PortContainer_0_BOARD_InitPeripherals[];
extern uint32 NUM_OF_CONFIGURED_PINS_PortContainer_0_BOARD_InitPeripherals;
extern const Port_ConfigType Port_Config;
extern const Can_43_FLEXCAN_ConfigType Can_43_FLEXCAN_Config;
extern void UartInit(void);
extern void Printf(const char *fmt, ...);

#if defined (__ghs__)
    #define __INTERRUPT_SVC  __interrupt
    #define __NO_RETURN _Pragma("ghs nowarning 111")
#elif defined (__ICCARM__)
    #define __INTERRUPT_SVC  __svc
    #define __NO_RETURN _Pragma("diag_suppress=Pe111")
#elif defined (__GNUC__)
    #define __INTERRUPT_SVC  __attribute__ ((interrupt ("SVC")))
    #define __NO_RETURN
#else
    #define __INTERRUPT_SVC
    #define __NO_RETURN
#endif

int counter = 0;
int accumulator = 0;
volatile int exit_code = 0;
uint8 CAN0_msg[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint8 CAN1_msg[8] = {0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18};
extern volatile uint8 g_rx_flag_can1;
extern volatile uint8 g_led_rx_flag;

float temp = 0.0f, humi = 0.0f;

volatile uint8 g_tx_confirm_count = 0;

void Can_43_FLEXCAN_MainFunction_Write(void);

void delay(volatile uint32_t count)
{
    while (count--);
}


int main(void)
{

	OsIf_Init( NULL_PTR );
	Mcu_Init( NULL_PTR );
	Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_0);

	while (MCU_PLL_LOCKED != Mcu_GetPllStatus())
	{
	        //do nothing
	}
	Mcu_DistributePllClock();
    Mcu_SetMode(McuConf_McuModeSettingConf_McuModeSettingConf_0);

    Platform_Init(NULL_PTR);
    Port_Init(NULL_PTR);
    IntCtrl_Ip_Init(&intCtrlConfig);

    Uart_Init(NULL_PTR);
    printf("UART debug ready\r\n");

    Can_43_FLEXCAN_Init(&Can_43_FLEXCAN_Config);
    CanIf_Init(NULL_PTR);

    Can_43_FLEXCAN_SetControllerMode(Can_43_FLEXCANConf_CanController_CanController_0, CAN_CS_STARTED);
    I2c_Init(&I2c_Config);

    Can_ControllerStateType state;
    do
    {
    	Can_43_FLEXCAN_GetControllerMode(Can_43_FLEXCANConf_CanController_CanController_0, &state);
    }
    while (state != CAN_CS_STARTED);

   PduInfoType PduInfoCAN0 =
    {
        .SduDataPtr = CAN0_msg,
        .SduLength = 8
    };

    for(;;)
    {
    	CDD_CanTransmit(CanIfTxPduCfg_0, CAN0_msg, 8);
		if (g_led_rx_flag == 1U) {
			g_led_rx_flag = 0U;
		}
		if (SHT2x_ReadTemperature(&temp) && SHT2x_ReadHumidity(&humi)) {
			App_SendSensorReport(temp, humi);
		}
    	Can_43_FLEXCAN_MainFunction_Write();
    	delay(500000);
    	printf("UART debug OK\r\n");
     }
    return exit_code;

}




#if defined (__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

__INTERRUPT_SVC void SVC_Handler() {
    accumulator += counter;
    printf("counter is 0x%08x, accumulator is 0x%08x\n", counter, accumulator);
}

#if defined (__GNUC__)
#pragma GCC diagnostic pop
#endif
