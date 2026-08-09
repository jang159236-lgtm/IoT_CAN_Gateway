/*
 * miscdev.h
 *
 *  Created on: May 11, 2025
 *      Author: 11812
 */

#include "stm32l4xx_hal.h"
#include <stdio.h>

#ifndef SRC_BOARD_MISCDEV_H_
#define SRC_BOARD_MISCDEV_H_


/**********************************************************************
*   Copyright: (C)2024 LingYun IoT System Studio
*      Author: GuoWenxue<guowenxue@gmail.com>
* Description: ISKBoard Hardware Abstract Layer driver
*
*   ChangeLog:
*        Version    Date       Author            Description
*        V1.0.0  2024.08.29    GuoWenxue      Release initial version
***********************************************************************/


/* 定义ON/OFF两个宏，这样在代码中使用比 1/0 更具有可读性 */
#define OFF    0
#define ON     1
#define time_after(a,b)	( (int32_t)(b) - (int32_t)(a)<0)
#define time_before(a,b)	time_after(b,a)
#define time_after_eq(a,b)( (int32_t)(a) - (int32_t)(b)>= 0)
#define time_before_eq(a,b)time_after_eq(b,a)
/* 定义一个gpio的结构体，用来描述这个引脚的相关信息 */
typedef struct gpio_s
{
    const char         *name;
    GPIO_TypeDef       *group;
    uint16_t            pin;
    uint8_t             status;
} gpio_t;

/*
 *+----------------------+
 *|    GPIO Relay API    |
 *+----------------------+
 */

typedef enum
{
    Relay1,
    RelayMax,
} relaynum_t;


/* Initial relays GPIO port */
extern int init_relay(void);

/* Turn $which r to $status(ON/OFF) */
extern void turn_relay(int which, int status);

/* Get $which relay current status */
extern int status_relay(int which);

/*
 *+----------------------+
 *|     GPIO Led API     |
 *+----------------------+
 */

/* 定义了一个枚举，分别表示RGB三个灯的索引：
 * 枚举的第1个成员,如果没赋值则其值为0，后面的成员值永远是前面成员的值加1.
 */
typedef enum
{
    Led_R, /* 其值为0 */
    Led_G, /* 其值为1 */
    Led_B, /* 其值为2 */
    LedMax,/* 其值为3，刚好是Led的总数 */
} lednum_t;

#define BITMASK_ALLLED  ((1<<LedMax)-1)


/* Initial leds GPIO port */
extern int init_led(void);

/* Turn $which led to $status(ON/OFF) */
extern void turn_led(int which, int status);

/* Toggle $which led status */
extern void toggle_led(int which);

/* Blink $which led */
extern void blink_led(int which, uint32_t interval);

/* Get $which led current status */
extern int status_led(int which);

/*
 *+----------------------------+
 *| ADC noisy & lux sensor API |
 *+----------------------------+
 */

enum
{
    ADCCHN_NOISY,
    ADCCHN_LUX,
    ADCCHN_MAX,
};

extern int adc_sample_lux_noisy(uint32_t *lux, uint32_t *noisy);


/*
 *+-----------------------------+
 *|  Timer delay API            |
 *+-----------------------------+
 */

/* Max to 60000 us */
extern void udelay(uint16_t us);
/* Turn buzzer on for $times */
extern void beep_start(uint16_t times, uint16_t interval);
#endif /* SRC_BOARD_MISCDEV_H_ */
