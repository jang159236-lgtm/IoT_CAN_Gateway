/*
 * servo.c
 *
 *  Created on: 2026年8月7日
 *      Author: 11812
 */

#include "servo.h"
#include "Pwm.h"

/* Convert a target angle (0~180) into the Pwm driver duty-cycle value */
static uint16_t Servo_AngleToDuty(uint8_t angleDeg)
{
    uint32_t pulse_us;
    uint32_t duty;

    if (angleDeg > 180U)
    {
        angleDeg = 180U;
    }

    /* Linear interpolation between min/max pulse width */
    pulse_us = SERVO_PULSE_MIN_US +
               ((uint32_t)(SERVO_PULSE_MAX_US - SERVO_PULSE_MIN_US) * angleDeg) / 180U;

    duty = (pulse_us * PWM_DUTY_FULL_SCALE) / SERVO_PWM_PERIOD_US;

    return (uint16_t)duty;
}

void Servo_SetAngle(uint8_t angleDeg)
{
    uint16_t duty = Servo_AngleToDuty(angleDeg);
    Pwm_SetDutyCycle(PwmConf_PwmChannel_PwmChannel_0, duty);
}
