#ifndef CAN_DEV_H
#define CAN_DEV_H
#include "main.h"

/**
 * Open CAN raw socket and bind to specified interface
 * @param ifname CAN interface name, e.g. "can1"
 * @return socket fd on success, -1 on failure
 */
int open_can_socket(const char *ifname);

/**
 * Send servo angle control frame to MCU
 * @param angle target angle 0~180
 */
void send_servo_command(uint8_t angle);

/**
 * Send LED control frame to MCU
 * @param led_index led index: 0=red,1=green,2=blue
 * @param state 0=off,1=on
 */
void send_led_command(uint8_t led_index, uint8_t state);

/**
 * Process incoming CAN frame, forward sensor data to MQTT
 * @param frame received CAN frame pointer
 */
void handle_can_frame(const struct can_frame *frame);

#endif
