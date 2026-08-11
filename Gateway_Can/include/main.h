#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <stdint.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <mosquitto.h>
#include "cJSON.h"

/* CAN ID definitions, align with MCU firmware */
#define CAN_ID_SENSOR_REPORT 0x122u  /* MCU -> Bridge: temperature & humidity (big-endian) */
#define CAN_ID_LED_CONTROL   0x100u  /* Bridge -> MCU: LED control */
#define CAN_ID_SERVO_CONTROL 0x101u  /* Bridge -> MCU: servo angle control */

/* MQTT topic definitions */
#define TOPIC_SENSOR_PUB   "device/igkboard/sensor"
#define TOPIC_LED_SUB      "device/igkboard/led/set"
#define TOPIC_SERVO_SUB    "device/igkboard/servo/set"

/* Global variables */
extern int g_can_fd;
extern struct mosquitto *g_mosq;
extern volatile int g_running;

#endif
