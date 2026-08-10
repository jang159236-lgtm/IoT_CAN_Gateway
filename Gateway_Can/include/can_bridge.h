#ifndef CAN_BRIDGE_H
#define CAN_BRIDGE_H

#include <stdint.h>
#include <linux/can.h>
#include <mosquitto.h>
#include "cJSON.h"

/* ==================== CAN Protocol Definitions ==================== */
#define CAN_ID_SENSOR_REPORT 0x122u   /* MCU -> Board: Temperature/Humidity Report (Big-endian) */
#define CAN_ID_LED_CONTROL   0x100u   /* Board -> MCU: LED Control, data[0]=state(0/1) */
#define CAN_ID_SERVO_CONTROL 0x101u   /* Board -> MCU: Servo Angle Control, data[0]=angle(0~180) */

/* ==================== MQTT Topic Definitions ==================== */
#define TOPIC_SENSOR_PUB   "device/igkboard/sensor"
#define TOPIC_LED_SUB      "device/igkboard/led/set"
#define TOPIC_SERVO_SUB    "device/igkboard/servo/set"

/* ==================== Global Variables ==================== */
extern int g_can_fd;
extern struct mosquitto *g_mosq;
extern volatile int g_running;

/* ==================== Function Declarations ==================== */

/* CAN Socket Functions */
int open_can_socket(const char *ifname);
void send_led_command(uint8_t led_index, uint8_t state);
void send_servo_command(uint8_t angle);
void handle_can_frame(const struct can_frame *frame);

/* JSON Parser Functions (using cJSON library) */
int json_get_int(const char *json_str, const char *key, long *out);
cJSON *json_parse(const char *json_str);
void json_delete(cJSON *json);

/* MQTT Callback Functions */
void on_connect(struct mosquitto *mosq, void *userdata, int rc);
void on_disconnect(struct mosquitto *mosq, void *userdata, int rc);
void on_message(struct mosquitto *mosq, void *userdata,
		const struct mosquitto_message *msg);

#endif /* CAN_BRIDGE_H */
