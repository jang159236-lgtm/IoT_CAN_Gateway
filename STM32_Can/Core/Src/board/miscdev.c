/*
 * miscdev.c
 *
 *  Created on: May 11, 2025
 *      Author: 11812
 */

//#ifndef SRC_BOARD_MISCDEV_C_
//#define SRC_BOARD_MISCDEV_C_



//#endif /* SRC_BOARD_MISCDEV_C_ */
/**********************************************************************
*   Copyright: (C)2024 LingYun IoT System Studio
*      Author: GuoWenxue<guowenxue@gmail.com>
* Description: ISKBoard Hardware Abstract Layer driver
*
*   ChangeLog:
*        Version    Date       Author            Description
*        V1.0.0  2024.08.29    GuoWenxue      Release initial version
***********************************************************************/

#include "miscdev.h"
#include "main.h" /* KEY1_pin, KEY2_Pin, KEY3_Pin 定义在该头文件下 */
//#include "usart.h"  /* 全局变量huart1定义在 usart.c中，并在sart.h头文件中声明 */

/*
 *+----------------------+
 *|    GPIO Relay API    |
 *+----------------------+
 */

gpio_t     relays[RelayMax] =
{
    { "Relay1",   GPIOD, GPIO_PIN_2, OFF },
};

int init_relay(void)
{
    int                 which;

    /* Turn all relays off */
    for(which=0; which<RelayMax; which++)
    {
        HAL_GPIO_WritePin(relays[which].group, relays[which].pin, GPIO_PIN_RESET);
    }

    return 0;
}

/* Turn $which relay to ON/OFF */
void turn_relay(int which, int status)
{
    GPIO_PinState       level;

    if( which >= RelayMax )
        return ;

    level = status==OFF ? GPIO_PIN_RESET : GPIO_PIN_SET;

    HAL_GPIO_WritePin(relays[which].group, relays[which].pin, level);

    relays[which].status = status;
}

/* Get $which relay current status */
int status_relay(int which)
{
    if( which >= RelayMax )
        return 0;

    return relays[which].status;
}

/*
 *+----------------------+
 *|     GPIO Led API     |
 *+----------------------+
 */

gpio_t     leds[LedMax] =
{
    { "RedLed",   GPIOC, GPIO_PIN_9, OFF },
    { "GreenLed", GPIOC, GPIO_PIN_6, OFF },
    { "BlueLed",  GPIOB, GPIO_PIN_2, OFF },
};


int init_led(void)
{
    int                 which;

    /* Turn all Leds off */
    for(which=0; which<LedMax; which++)
    {
        HAL_GPIO_WritePin(leds[which].group, leds[which].pin, GPIO_PIN_SET);
    }

    return 0;
}

/* Turn $which led to ON/OFF */
void turn_led(int which, int status)
{
    GPIO_PinState       level;

    if( which >= LedMax )
        return ;

    level = status==OFF ? GPIO_PIN_SET : GPIO_PIN_RESET;

    HAL_GPIO_WritePin(leds[which].group, leds[which].pin, level);

    leds[which].status = status;
}

/* Toggle $which led status */
void toggle_led(int which)
{

    if( which >= LedMax )
        return ;

    HAL_GPIO_TogglePin(leds[which].group, leds[which].pin);

    leds[which].status = !leds[which].status;
}

/* Blink $which led */
void blink_led(int which, uint32_t interval)
{
    turn_led(which, ON);
    HAL_Delay(interval);

    turn_led(which, OFF);
    HAL_Delay(interval);
}

/* Get $which led current status */
int status_led(int which)
{
    if( which >= LedMax )
        return 0;

    return leds[which].status;
}
/*
 *+----------------------+
 *|     GPIO Key API     |
 *+----------------------+
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
/*	static uint8_t relay1_status = OFF;

	    if( KEY1_Pin == GPIO_Pin )
	    {
	        relay1_status  ^= 1;
	        turn_relay(Relay1, relay1_status);
	    }
*/

   if( KEY1_Pin == GPIO_Pin )
    {
        blink_led( Led_R, 500 );
    }
    else if( KEY2_Pin == GPIO_Pin )
    {
        blink_led( Led_G, 500 );
    }
    else if( KEY3_Pin == GPIO_Pin )
    {
        blink_led( Led_B, 500 );
    }
}

/*
 *+----------------------+
 *|      printf API      |
 *+----------------------+
 */
#include "usart.h"  /* 全局变量huart1定义在 usart.c中，并在sart.h头文件中声明 */

/* gcc 编译器中的 printf 函数将会调用 __io_putchar() 函数，实现最终的字符打印
 * keil编译器中的 printf 函数将会调用 fputc() 函数，实现最终的字符打印
 * 这里我们定义一个宏 PUTCHAR_PROTOTYPE 来兼容这两个编译器所需要的函数原型；
 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/*
 * STM32CubeIDE使用的是 gcc 编译器，它会内建 __GNUC__ 宏定义，所以下面PUTCHAR_PROTOTYPE将会扩展为:
 *  int __io_putchar(int ch)
 */
PUTCHAR_PROTOTYPE
{
    /* 调用STM32 HAL库的串口发送函数，将printf要打印的这个字符通过串口发送出去 */
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
/*
 *+----------------------------+
 *| ADC noisy & lux sensor API |
 *+----------------------------+
 */

#include "adc.h"
int adc_sample_lux_noisy(uint32_t *lux, uint32_t *noisy)
{
    uint8_t            i;
    uint32_t           timeout = 0xffffff;

    for(i=0; i<ADCCHN_MAX; i++)
    {
            HAL_ADC_Start(&hadc1);

            HAL_ADC_PollForConversion(&hadc1, timeout);

            if( ADCCHN_NOISY == i )
            {
                *noisy = HAL_ADC_GetValue(&hadc1);
            }
            else if( ADCCHN_LUX == i )
            {
                *lux = HAL_ADC_GetValue(&hadc1);
            }

            HAL_Delay(10);
    }

    HAL_ADC_Stop(&hadc1);

    return 0;
}

/*
 *+----------------------------+
 *|      Timer delay API       |
 *+----------------------------+
 */
#include "tim.h"

/* Max to 60000 us */
void udelay(uint16_t us)
{
    uint16_t differ = 60000-us;

    HAL_TIM_Base_Start(&htim6);

    __HAL_TIM_SET_COUNTER(&htim6, differ);

    while( differ < 60000 )
    {
        differ=__HAL_TIM_GET_COUNTER(&htim6);
    }

    HAL_TIM_Base_Stop(&htim6);
}
void beep_start(uint16_t times, uint16_t interval)
{
    while( times-- )
    {
        /* Start buzzer */
        if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4) != HAL_OK)
        {
            /* Starting Error */
            Error_Handler();
        }

        HAL_Delay(interval);

        /* Stop buzzer */
        if (HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4) != HAL_OK)
        {
            /* Starting Error */
            Error_Handler();
        }

        HAL_Delay(interval);
    }
}
