#include "mqtt_client.h"
#include "can_dev.h"
#include "json_util.h"

static void on_connect(struct mosquitto *mosq, void *userdata, int rc)
{
    (void)userdata;
    if (rc == 0) {
        printf("[MQTT] Connected successfully\n");
        mosquitto_subscribe(mosq, NULL, TOPIC_LED_SUB, 0);
        mosquitto_subscribe(mosq, NULL, TOPIC_SERVO_SUB, 0);
        printf("[MQTT] Subscribed to %s\n", TOPIC_SERVO_SUB);
        printf("[MQTT] Subscribed to %s\n", TOPIC_LED_SUB);
    } else {
        fprintf(stderr, "[MQTT] Connection failed, rc=%d (%s)\n", rc, mosquitto_connack_string(rc));
    }
}

static void on_disconnect(struct mosquitto *mosq, void *userdata, int rc)
{
    (void)mosq;
    (void)userdata;
    fprintf(stderr, "[MQTT] Disconnected, rc=%d, auto reconnection will be attempted\n", rc);
}

static void on_message(struct mosquitto *mosq, void *userdata,
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

    cJSON *root = cJSON_Parse(buf);
    if (root == NULL) {
        const char *err = cJSON_GetErrorPtr();
        fprintf(stderr, "[WARN] JSON parse failed, skip message: %s\n", err ? err : "unknown error");
        return;
    }

    if (strcmp(msg->topic, TOPIC_LED_SUB) == 0) {
        long led = 0, state = 0;
        int has_led   = (json_get_int(root, "led", &led) == 0);
        int has_state = (json_get_int(root, "state", &state) == 0);

        if (!has_state) {
            fprintf(stderr, "[WARN] LED command missing state field, skip: %s\n", buf);
            cJSON_Delete(root);
            return;
        }
        if (!has_led) {
            led = 0;
        }

        send_led_command((uint8_t)led, (uint8_t)state);
    }
    else if (strcmp(msg->topic, TOPIC_SERVO_SUB) == 0)
    {
        long angle = 0;
        if (json_get_int(root, "angle", &angle) != 0)
        {
            fprintf(stderr, "[WARN] Servo command missing angle field, skip: %s\n", buf);
            cJSON_Delete(root);
            return;
        }
        send_servo_command((uint8_t)angle);
    }

    cJSON_Delete(root);
}

void mqtt_set_all_callbacks(struct mosquitto *mosq)
{
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    mosquitto_message_callback_set(mosq, on_message);
}
