#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "can_bridge.h"

int g_can_fd = -1;

int open_can_socket(const char *ifname)
{
	int fd;
	struct sockaddr_can addr;
	struct ifreq ifr;

	fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (fd < 0) {
		perror("socket");
		return -1;
	}

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
	if (ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
		perror("ioctl(SIOCGIFINDEX)");
		close(fd);
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		close(fd);
		return -1;
	}

	return fd;
}

void send_servo_command(uint8_t angle)
{
	struct can_frame frame;

	if (angle > 180) angle = 180;

	memset(&frame, 0, sizeof(frame));
	frame.can_id = CAN_ID_SERVO_CONTROL;
	frame.can_dlc = 1;
	frame.data[0] = angle;

	if (write(g_can_fd, &frame, sizeof(frame)) != (ssize_t)sizeof(frame)) {
		perror("CAN write");
		return;
	}

	printf("[CAN TX] Servo control: angle=%u\n", angle);
}

void send_led_command(uint8_t led_index, uint8_t state)
{
	struct can_frame frame;

	memset(&frame, 0, sizeof(frame));
	frame.can_id = CAN_ID_LED_CONTROL;
	frame.can_dlc = 2;
	frame.data[0] = led_index;
	frame.data[1] = state ? 1 : 0;

	if (write(g_can_fd, &frame, sizeof(frame)) != (ssize_t)sizeof(frame)) {
		perror("CAN write");
		return;
	}

	printf("[CAN TX] LED control: led=%u state=%s\n", led_index, state ? "ON" : "OFF");
}

void handle_can_frame(const struct can_frame *frame)
{
	if (frame->can_id != CAN_ID_SENSOR_REPORT) {
		return;
	}

	if (frame->can_dlc < 4) {
		fprintf(stderr, "[WARN] Sensor frame length insufficient, dlc=%d\n", frame->can_dlc);
		return;
	}

	uint16_t raw_temp = (uint16_t)((frame->data[0] << 8) | frame->data[1]);
	uint16_t raw_humi = (uint16_t)((frame->data[2] << 8) | frame->data[3]);

	double temperature = raw_temp / 100.0;
	double humidity    = raw_humi / 100.0;

	char payload[128];
	int n = snprintf(payload, sizeof(payload),
			"{\"temperature\":%.2f,\"humidity\":%.2f}",
			temperature, humidity);

	int rc = mosquitto_publish(g_mosq, NULL, TOPIC_SENSOR_PUB, n, payload, 0, false);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "[MQTT] Publish failed: %s\n", mosquitto_strerror(rc));
	} else {
		printf("[MQTT TX] topic=%s payload=%s\n", TOPIC_SENSOR_PUB, payload);
	}
}
