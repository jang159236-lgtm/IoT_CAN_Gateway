#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H
#include "main.h"

/**
 * Register all MQTT event callbacks
 * @param mosq mosquitto client instance pointer
 */
void mqtt_set_all_callbacks(struct mosquitto *mosq);

#endif
