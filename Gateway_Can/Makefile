CC=/opt/buildroot/cortexA7/bin/arm-linux-gcc
APP_NAME=spi_test

all:clean
	@${CC} ${APP_NAME}.c -o ${APP_NAME}
	${CC} ttyS_test.c -o ttyS_test -lpthread
	${CC} can_test.c -o can_test
	${CC} lcd_test.c -o lcd_test
	${CC} can_gs.c -o can_gs
	${CC} Can_mqtt.c -o Can_mqtt -lmosquitto -lpthread
	${CC} Can_V2.c cJSON.c -o Can_V2 -lmosquitto -lpthread
	${CC} Can.c cJSON.c -o Can -lmosquitto -lpthread

clean:
	@rm -f ${APP_NAME}
	@rm -f ttyS_test
	@rm -f can_test
	@rm -f lcd_test
	@rm -f can_gs
	@rm -f Can_mqtt
	@rm -f Can_V2
	@rm -f Can

install:
	cp ${APP_NAME} ~/linux/tftp/
