CC = gcc
CFLAGS = -Wall -Wextra -I./include -std=c99
LDFLAGS = -lmosquitto -lm

TARGET = can_bridge
SRCS = src/main.c src/can_socket.c src/mqtt_handler.c src/json_parser.c src/cJSON.c
OBJS = $(SRCS:.c=.o)
HEADERS = include/can_bridge.h include/cJSON.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
