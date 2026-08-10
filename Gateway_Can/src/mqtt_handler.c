#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include "cJSON.h"

#include "can_bridge.h"
#include "cJSON.h"

struct mosquitto *g_mosq = NULL;

void on_connect(struct mosquitto *mosq, void *userdata, int rc)
{
	(void)userdata;
	if (rc == 0) {
		printf("[MQTT] Connection successful\n");
		mosquitto_subscribe(mosq, NULL, TOPIC_LED_SUB, 0);
		mosquitto_subscribe(mosq, NULL, TOPIC_SERVO_SUB, 0);
		printf("[MQTT] Subscribed to %s\n", TOPIC_SERVO_SUB);
		printf("[MQTT] Subscribed to %s\n", TOPIC_LED_SUB);
	} else {
		fprintf(stderr, "[MQTT] Connection failed, return code=%d (%s)\n", rc, mosquitto_connack_string(rc));
	}
}

void on_disconnect(struct mosquitto *mosq, void *userdata, int rc)
{
	(void)mosq;
	(void)userdata;
	fprintf(stderr, "[MQTT] Disconnected, return code=%d, library will auto-reconnect\n", rc);
}

void on_message(struct mosquitto *mosq, void *userdata,
		const struct mosquitto_message *msg)
{
	(void)mosq;
	(void)userdata;

	if (msg->payloadlen <= 0 || msg->payload == NULL) {
		return;
	}

	char buf[256];
	int len = msg->payloadlen;
	if (len >= (int)sizeof(buf)) {
		len = sizeof(buf) - 1;
	}
	memcpy(buf, msg->payload, len);
	buf[len] = '\0';

	printf("[MQTT RX] topic=%s payload=%s\n", msg->topic, buf);

	if (strcmp(msg->topic, TOPIC_LED_SUB) == 0) {
		cJSON *json = cJSON_Parse(buf);
		if (!json) {
			fprintf(stderr, "[WARN] LED message JSON parse failed: %s\n", buf);
			return;
		}

		cJSON *led_item = cJSON_GetObjectItem(json, "led");
		cJSON *state_item = cJSON_GetObjectItem(json, "state");

		if (!state_item || !cJSON_IsNumber(state_item)) {
			fprintf(stderr, "[WARN] LED control message missing 'state' field\n");
			cJSON_Delete(json);
			return;
		}

		uint8_t led_index = 0;
		if (led_item && cJSON_IsNumber(led_item)) {
			led_index = (uint8_t)led_item->valuedouble;
		}

		send_led_command(led_index, (uint8_t)state_item->valuedouble);
		cJSON_Delete(json);
	}
	else if (strcmp(msg->topic, TOPIC_SERVO_SUB) == 0) {
		cJSON *json = cJSON_Parse(buf);
		if (!json) {
			fprintf(stderr, "[WARN] Servo message JSON parse failed: %s\n", buf);
			return;
		}

		cJSON *angle_item = cJSON_GetObjectItem(json, "angle");
		if (!angle_item || !cJSON_IsNumber(angle_item)) {
			fprintf(stderr, "[WARN] Servo control message missing 'angle' field\n");
			cJSON_Delete(json);
			return;
		}

		send_servo_command((uint8_t)angle_item->valuedouble);
		cJSON_Delete(json);
	}
}
