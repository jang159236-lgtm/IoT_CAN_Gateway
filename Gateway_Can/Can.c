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

/* ==================== CAN 协议定义（跟单片机对齐）==================== */
#define CAN_ID_SENSOR_REPORT 0x122u   /* 单片机 -> 开发板：温湿度上报，大端序  */
#define CAN_ID_LED_CONTROL   0x100u   /* 开发板 -> 单片机：LED 控制，data[0]=状态(0/1) 下发命令:{"led":0,"state":0} */
#define CAN_ID_SERVO_CONTROL 0x101u   /* 开发板 -> 单片机：舵机角度控制，data[0]=角度(0~180) 下发命令:{"angle":90}*/
/*==================== MQTT 主题定义 ==================== */
#define TOPIC_SENSOR_PUB   "device/igkboard/sensor"
#define TOPIC_LED_SUB      "device/igkboard/led/set"
#define TOPIC_SERVO_SUB    "device/igkboard/servo/set"
/* ==================== 全局变量 ==================== */
static int g_can_fd = -1;
static struct mosquitto *g_mosq = NULL;
static volatile int g_running = 1;

/* ---------------------------------------------------------------------
 * CAN 相关
 * ------------------------------------------------------------------- */

static int open_can_socket(const char *ifname)
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

static void send_servo_command(uint8_t angle)
{
	struct can_frame frame;

	if (angle > 180) angle = 180;

	memset(&frame, 0, sizeof(frame));
	frame.can_id = CAN_ID_SERVO_CONTROL;
	frame.can_dlc = 1;
	frame.data[0] = angle;

	if (write(g_can_fd, &frame, sizeof(frame)) != (ssize_t)sizeof(frame)) 
	{
		perror("CAN write");
		return;
	}

	printf("[CAN TX] Servo control: angle=%u\n", angle);
}

/* 发送LED控制帧到单片机。state: 0=灭 1=亮 */
/* led_index: 0=红 1=绿 2=蓝；state: 0=灭 1=亮 */
static void send_led_command(uint8_t led_index, uint8_t state)
{
	struct can_frame frame;

	memset(&frame, 0, sizeof(frame));
	frame.can_id = CAN_ID_LED_CONTROL;
	frame.can_dlc = 2;
	frame.data[0] = led_index;   /* 单片机用 data[0] 直接判断开关状态 */
	frame.data[1] = state ? 1 : 0;

	if (write(g_can_fd, &frame, sizeof(frame)) != (ssize_t)sizeof(frame)) 
	{
		perror("CAN write");
		return;
	}

	printf("[CAN TX] LED control: led=%u state=%s\n", led_index, state ? "ON" : "OFF");
}

/* ---------------------------------------------------------------------
 * 提取指令
 * ------------------------------------------------------------------- */
static int json_get_int(const char *json, const char *key, long *out)
{
	char pattern[64];
	const char *p;
	snprintf(pattern, sizeof(pattern), "\"%s\"", key);

	p = strstr(json, pattern);
	if (!p) {
		return -1;
	}
	p += strlen(pattern);

	/* 跳过冒号和空白 */
	while (*p == ' ' || *p == '\t' || *p == ':') {
		p++;
	}

	char *endptr;
	long val = strtol(p, &endptr, 10);
	if (endptr == p) {
		return -1;   /* 没解析出数字 */
	}

	*out = val;
	return 0;
}

/* ---------------------------------------------------------------------
 * MQTT 回调
 * ------------------------------------------------------------------- */

static void on_connect(struct mosquitto *mosq, void *userdata, int rc)
{
	(void)userdata;
	if (rc == 0) {
		printf("[MQTT] 连接成功\n");
		mosquitto_subscribe(mosq, NULL, TOPIC_LED_SUB, 0);
		mosquitto_subscribe(mosq, NULL, TOPIC_SERVO_SUB, 0);
		printf("[MQTT] 已订阅 %s\n", TOPIC_SERVO_SUB);
		printf("[MQTT] 已订阅 %s\n", TOPIC_LED_SUB);
	} else {
		fprintf(stderr, "[MQTT] 连接失败，返回码=%d (%s)\n", rc, mosquitto_connack_string(rc));
	}
}

static void on_disconnect(struct mosquitto *mosq, void *userdata, int rc)
{
	(void)mosq;
	(void)userdata;
	fprintf(stderr, "[MQTT] 连接断开，返回码=%d，库会自动尝试重连\n", rc);
}

static void on_message(struct mosquitto *mosq, void *userdata,
		const struct mosquitto_message *msg)
{
	(void)mosq;
	(void)userdata;

	if (msg->payloadlen <= 0 || msg->payload == NULL) {
		return;
	}

	/* payload 不保证以 \0 结尾，复制一份加上结束符再解析 */
	char buf[256];
	int len = msg->payloadlen;
	if (len >= (int)sizeof(buf)) {
		len = sizeof(buf) - 1;
	}
	memcpy(buf, msg->payload, len);
	buf[len] = '\0';

	printf("[MQTT RX] topic=%s payload=%s\n", msg->topic, buf);

	if (strcmp(msg->topic, TOPIC_LED_SUB) == 0) {
		long led = 0, state = 0;
		int has_led   = (json_get_int(buf, "led", &led) == 0);
		int has_state = (json_get_int(buf, "state", &state) == 0);

		if (!has_state) {
			fprintf(stderr, "[WARN] LED控制消息缺少 state 字段，忽略: %s\n", buf);
			return;
		}
		if (!has_led) {
			led = 0;   /* 缺省LED编号为0 */
		}

		send_led_command((uint8_t)led, (uint8_t)state);
	}
	else if (strcmp(msg->topic, TOPIC_SERVO_SUB) == 0) 
	{
		long angle = 0;
		if (json_get_int(buf, "angle", &angle) != 0) 
		{
			fprintf(stderr, "[WARN] 舵机控制消息缺少 angle 字段，忽略: %s\n", buf);
			return;
		}
		send_servo_command((uint8_t)angle);
	}
}

/* ---------------------------------------------------------------------
 * 处理CAN收到的传感器帧，转发到MQTT
 * ------------------------------------------------------------------- */
static void handle_can_frame(const struct can_frame *frame)
{
	if (frame->can_id != CAN_ID_SENSOR_REPORT) {
		return; 
	}

	if (frame->can_dlc < 4) {
		fprintf(stderr, "[WARN] 传感器帧长度不足, dlc=%d\n", frame->can_dlc);
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
		fprintf(stderr, "[MQTT] 发布失败: %s\n", mosquitto_strerror(rc));
	} else {
		printf("[MQTT TX] topic=%s payload=%s\n", TOPIC_SENSOR_PUB, payload);
	}
}

/* ---------------------------------------------------------------------
 * main
 * ------------------------------------------------------------------- */

static void print_usage(const char *progname)
{
	printf("Usage: %s -i <can_interface> --host <broker> [options]\n", progname);
	printf("Options:\n");
	printf("  -i, --interface <if>   CAN 接口 (例如 can1)\n");
	printf("      --host <host>      MQTT Broker 地址\n");
	printf("      --port <port>      MQTT Broker 端口 (默认 1883)\n");
	printf("      --user <user>      MQTT 用户名\n");
	printf("      --pass <pass>      MQTT 密码\n");
	printf("  -h, --help              显示帮助\n");
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
		fprintf(stderr, "错误: 必须指定 -i 和 --host\n\n");
		print_usage(argv[0]);
		return 1;
	}

	/* ---- 打开 CAN ---- */
	g_can_fd = open_can_socket(ifname);
	if (g_can_fd < 0) {
		return 1;
	}
	printf("CAN 接口 %s 已打开\n", ifname);

	/* ---- 初始化 MQTT ---- */
	mosquitto_lib_init();

	g_mosq = mosquitto_new(NULL, true, NULL);
	if (!g_mosq) {
		fprintf(stderr, "mosquitto_new 失败\n");
		return 1;
	}

	if (user != NULL) {
		if (mosquitto_username_pw_set(g_mosq, user, pass) != MOSQ_ERR_SUCCESS) {
			fprintf(stderr, "设置用户名密码失败\n");
			return 1;
		}
	}

	mosquitto_connect_callback_set(g_mosq, on_connect);
	mosquitto_disconnect_callback_set(g_mosq, on_disconnect);
	mosquitto_message_callback_set(g_mosq, on_message);

	printf("正在连接 MQTT Broker %s:%d ...\n", host, port);
	int rc = mosquitto_connect(g_mosq, host, port, 60 /* keepalive秒 */);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "mosquitto_connect 失败: %s\n", mosquitto_strerror(rc));
		return 1;
	}

	/* 用后台线程处理MQTT网络I/O（收发、自动重连都在这个线程里） */
	rc = mosquitto_loop_start(g_mosq);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "mosquitto_loop_start 失败: %s\n", mosquitto_strerror(rc));
		return 1;
	}

	printf("桥接程序已启动，等待CAN数据 / MQTT消息...\n");

	/* ---- 主循环：阻塞读CAN，收到就转发到MQTT ---- */
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
			fprintf(stderr, "[WARN] 读到不完整的CAN帧\n");
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
