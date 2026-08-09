/*
 * sht20.h
 *
 *  Created on: 2026年8月6日
 *      Author: 11812
 */

#ifndef SHT20_H_
#define SHT20_H_

#include "Std_Types.h"
#include "CDD_I2c.h"

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* SHT2x 固定7位从机地址 */
#define SHT2X_I2C_ADDR          ((I2c_AddressType)0x40U)

/* SHT2x 命令字节（不保持总线模式 No Hold Master） */
#define SHT2X_CMD_TEMP_NOHOLD   ((uint8)0xF3U)
#define SHT2X_CMD_HUMI_NOHOLD   ((uint8)0xF5U)
#define SHT2X_CMD_SOFT_RESET    ((uint8)0xFEU)

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

/**
 * @brief  读取一次 SHT2x 温度值 (°C)
 * @param  outTemp: 测量到的温度结果输出指针
 * @return boolean: TRUE  - 读取成功
 *                  FALSE - 读取失败（I2C通信错误）
 */
boolean SHT2x_ReadTemperature(float *outTemp);

/**
 * @brief  读取一次 SHT2x 相对湿度值 (%RH)
 * @param  outHumi: 测量到的湿度结果输出指针
 * @return boolean: TRUE  - 读取成功
 *                  FALSE - 读取失败（I2C通信错误）
 */
boolean SHT2x_ReadHumidity(float *outHumi);


/* 将数据放大100倍、大端打包并发送 CAN 报文的函数声明 */
void App_SendSensorReport(float temp, float humi);


#endif /* SHT20_H_ */
