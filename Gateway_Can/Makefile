#===================== 配置区 =====================
CC=/opt/buildroot/cortexA7/bin/arm-linux-gcc
TARGET := can_mqtt_bridge

# 头文件路径
# ./include：自己工程头文件
# ../mosquitto/include：mosquitto头文件
CFLAGS  := -Wall -g -I./include -I../mosquitto/include

# 链接库路径
# -L 指定so目录，-lmosquitto 链接mqtt库，-lm数学库
LDFLAGS := -L../mosquitto/lib -lmosquitto -lm

# 所有源文件
SRCS := src/main.c \
        src/can_dev.c \
        src/json_util.c \
        src/mqtt_client.c \
        src/cJSON.c

# 自动生成.o文件列表
OBJS := $(SRCS:.c=.o)
#==================================================

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 编译.c生成.o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
