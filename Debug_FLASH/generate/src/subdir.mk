################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../generate/src/CDD_Uart_PBcfg.c \
../generate/src/CanIf_Cfg.c \
../generate/src/CanIf_PBcfg.c \
../generate/src/Can_43_FLEXCAN_Ipw_PBcfg.c \
../generate/src/Can_43_FLEXCAN_PBcfg.c \
../generate/src/Clock_Ip_Cfg.c \
../generate/src/Clock_Ip_PBcfg.c \
../generate/src/Dio_Cfg.c \
../generate/src/FlexCAN_Ip_PBcfg.c \
../generate/src/Flexio_Uart_Ip_PBcfg.c \
../generate/src/IntCtrl_Ip_Cfg.c \
../generate/src/Lpuart_Uart_Ip_PBcfg.c \
../generate/src/Mcu_Cfg.c \
../generate/src/Mcu_PBcfg.c \
../generate/src/Mpu_Ip_Cfg.c \
../generate/src/OsIf_Cfg.c \
../generate/src/Platform_Cfg.c \
../generate/src/Platform_Ipw_Cfg.c \
../generate/src/Port_Cfg.c \
../generate/src/Port_Ci_Port_Ip_PBcfg.c \
../generate/src/Port_PBcfg.c \
../generate/src/Power_Ip_Cfg.c \
../generate/src/Power_Ip_PBcfg.c \
../generate/src/Ram_Ip_Cfg.c \
../generate/src/Ram_Ip_PBcfg.c \
../generate/src/Uart_Ipw_PBcfg.c 

OBJS += \
./generate/src/CDD_Uart_PBcfg.o \
./generate/src/CanIf_Cfg.o \
./generate/src/CanIf_PBcfg.o \
./generate/src/Can_43_FLEXCAN_Ipw_PBcfg.o \
./generate/src/Can_43_FLEXCAN_PBcfg.o \
./generate/src/Clock_Ip_Cfg.o \
./generate/src/Clock_Ip_PBcfg.o \
./generate/src/Dio_Cfg.o \
./generate/src/FlexCAN_Ip_PBcfg.o \
./generate/src/Flexio_Uart_Ip_PBcfg.o \
./generate/src/IntCtrl_Ip_Cfg.o \
./generate/src/Lpuart_Uart_Ip_PBcfg.o \
./generate/src/Mcu_Cfg.o \
./generate/src/Mcu_PBcfg.o \
./generate/src/Mpu_Ip_Cfg.o \
./generate/src/OsIf_Cfg.o \
./generate/src/Platform_Cfg.o \
./generate/src/Platform_Ipw_Cfg.o \
./generate/src/Port_Cfg.o \
./generate/src/Port_Ci_Port_Ip_PBcfg.o \
./generate/src/Port_PBcfg.o \
./generate/src/Power_Ip_Cfg.o \
./generate/src/Power_Ip_PBcfg.o \
./generate/src/Ram_Ip_Cfg.o \
./generate/src/Ram_Ip_PBcfg.o \
./generate/src/Uart_Ipw_PBcfg.o 

C_DEPS += \
./generate/src/CDD_Uart_PBcfg.d \
./generate/src/CanIf_Cfg.d \
./generate/src/CanIf_PBcfg.d \
./generate/src/Can_43_FLEXCAN_Ipw_PBcfg.d \
./generate/src/Can_43_FLEXCAN_PBcfg.d \
./generate/src/Clock_Ip_Cfg.d \
./generate/src/Clock_Ip_PBcfg.d \
./generate/src/Dio_Cfg.d \
./generate/src/FlexCAN_Ip_PBcfg.d \
./generate/src/Flexio_Uart_Ip_PBcfg.d \
./generate/src/IntCtrl_Ip_Cfg.d \
./generate/src/Lpuart_Uart_Ip_PBcfg.d \
./generate/src/Mcu_Cfg.d \
./generate/src/Mcu_PBcfg.d \
./generate/src/Mpu_Ip_Cfg.d \
./generate/src/OsIf_Cfg.d \
./generate/src/Platform_Cfg.d \
./generate/src/Platform_Ipw_Cfg.d \
./generate/src/Port_Cfg.d \
./generate/src/Port_Ci_Port_Ip_PBcfg.d \
./generate/src/Port_PBcfg.d \
./generate/src/Power_Ip_Cfg.d \
./generate/src/Power_Ip_PBcfg.d \
./generate/src/Ram_Ip_Cfg.d \
./generate/src/Ram_Ip_PBcfg.d \
./generate/src/Uart_Ipw_PBcfg.d 


# Each subdirectory must supply rules for building sources it contributes
generate/src/%.o: ../generate/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@generate/src/CDD_Uart_PBcfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


