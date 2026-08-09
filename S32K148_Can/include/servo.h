/*
 * servo.h
 *
 *  Created on: 2026年8月7日
 *      Author: 11812
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include "Std_Types.h"
#include "Pwm_Cfg.h"


#define SERVO_PWM_PERIOD_US      (20000U)   /* 20ms period, 50Hz */
#define SERVO_PULSE_MIN_US       (500U)     /* 0.5ms -> 0 degree */
#define SERVO_PULSE_MAX_US       (2500U)    /* 2.5ms -> 180 degree */
#define PWM_DUTY_FULL_SCALE      (0x8000U)  /* Pwm driver duty scale */


void Servo_SetAngle(uint8_t angleDeg);

#endif /* SERVO_H_ */
