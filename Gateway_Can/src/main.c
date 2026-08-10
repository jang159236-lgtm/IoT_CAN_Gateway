#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <mosquitto.h>
#include <linux/can.h>

#include "can_bridge.h"

volatile int g_running = 1;

static void print_usage(const char *progname)
{
	printf("Usage: %s -i <can_interface> --host <broker> [options]\n", progname);
	printf("Options:\n");
	printf("  -i, --interface <if>   CAN interface (e.g. can1)\n");
	printf("      --host <host>      MQTT Broker address\n");
	printf("      --port <port>      MQTT Broker port (default 1883)\n");
	printf("      --user <user>      MQTT username\n");
	printf("      --pass <pass>      MQTT password\n");
	printf("  -h, --help              Show this help message\n");
}

int main(int argc, char **argv)
{
	const char *ifname = NULL;
	const char *host = NULL;
	int port = 1883;
	const char *user = NULL;
	const char *pass = NULL;

	static struct option long_options[] = {
		{"interface", required_argument, 0, 'i'},
		{"host",      required_argument, 0, 1001},
		{"port",      required_argument, 0, 1002},
		{"user",      required_argument, 0, 1003},
		{"pass",      required_argument, 0, 1004},
		{"help",      no_argument,       0, 'h'},
		{0, 0, 0, 0}
	};

	int opt;
	while ((opt = getopt_long(argc, argv, "i:h", long_options, NULL)) != -1) {
		switch (opt) {
			case 'i': ifname = optarg; break;
			case 1001: host = optarg; break;
			case 1002: port = atoi(optarg); break;
			case 1003: user = optarg; break;
			case 1004: pass = optarg; break;
			case 'h': print_usage(argv[0]); return 0;
			default: print_usage(argv[0]); return 1;
		}
	}

	if (ifname == NULL || host == NULL) {
		fprintf(stderr, "Error: Must specify -i and --host\n\n");
		print_usage(argv[0]);
		return 1;
	}

	g_can_fd = open_can_socket(ifname);
	if (g_can_fd < 0) {
		return 1;
	}
	printf("CAN interface %s opened\n", ifname);

	mosquitto_lib_init();

	g_mosq = mosquitto_new(NULL, true, NULL);
	if (!g_mosq) {
		fprintf(stderr, "mosquitto_new failed\n");
		return 1;
	}

	if (user != NULL) {
		if (mosquitto_username_pw_set(g_mosq, user, pass) != MOSQ_ERR_SUCCESS) {
			fprintf(stderr, "Failed to set username and password\n");
			return 1;
		}
	}

	mosquitto_connect_callback_set(g_mosq, on_connect);
	mosquitto_disconnect_callback_set(g_mosq, on_disconnect);
	mosquitto_message_callback_set(g_mosq, on_message);

	printf("Connecting to MQTT Broker %s:%d ...\n", host, port);
	int rc = mosquitto_connect(g_mosq, host, port, 60);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "mosquitto_connect failed: %s\n", mosquitto_strerror(rc));
		return 1;
	}

	rc = mosquitto_loop_start(g_mosq);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "mosquitto_loop_start failed: %s\n", mosquitto_strerror(rc));
		return 1;
	}

	printf("Bridge program started, waiting for CAN data / MQTT messages...\n");

	struct can_frame frame;
	while (g_running) {
		ssize_t nbytes = read(g_can_fd, &frame, sizeof(frame));
		if (nbytes < 0) {
			if (errno == EINTR) {
				continue;
			}
			perror("CAN read");
			break;
		}
		if (nbytes < (ssize_t)sizeof(frame)) {
			fprintf(stderr, "[WARN] Incomplete CAN frame received\n");
			continue;
		}

		handle_can_frame(&frame);
	}

	mosquitto_loop_stop(g_mosq, true);
	mosquitto_destroy(g_mosq);
	mosquitto_lib_cleanup();
	close(g_can_fd);

	return 0;
}
