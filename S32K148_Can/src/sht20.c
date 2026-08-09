#include "CDD_I2c.h"
#include "Std_Types.h"
#include "sht20.h"
#include "CDD.h"
#include <stdio.h>

extern void delay(volatile uint32_t count);

/* 向SHT2x写1字节命令（触发一次测量） */
static Std_ReturnType SHT2x_SendCommand(uint8 cmd)
{
    I2c_RequestType req;
    uint8 cmdBuf[1] = { cmd };
    Std_ReturnType ret = E_NOT_OK;

    printf("  [Debug] Sending Cmd: 0x%02X to Addr: 0x40...\r\n", cmd);

    req.SlaveAddress          = 0x40U;
    req.BitsSlaveAddressSize  = FALSE;
    req.ExpectNack            = FALSE;
    req.RepeatedStart         = FALSE;
    req.BufferSize            = 1U;
    req.DataDirection         = I2C_SEND_DATA;
    req.DataBuffer            = cmdBuf;


    ret = I2c_SyncTransmit(I2cConf_I2cChannel_I2cChannel_0, &req);


    printf("  [Debug] I2c_SyncTransmit Result = 0x%02X (%s)\r\n",
           ret, (ret == E_OK) ? "SUCCESS" : "FAILED");

    return ret;
}


/* 从SHT2x读回2字节原始数据 */
static Std_ReturnType SHT2x_ReadData(uint8 *outBuf2Bytes)
{
    I2c_RequestType req;

    req.SlaveAddress          = SHT2X_I2C_ADDR;
    req.BitsSlaveAddressSize  = FALSE;
    req.ExpectNack            = FALSE;
    req.RepeatedStart         = FALSE;
    req.BufferSize            = 2U;         /* 只读高低字节，跳过第3字节CRC */
    req.DataDirection         = I2C_RECEIVE_DATA;
    req.DataBuffer            = outBuf2Bytes;

    return I2c_SyncTransmit(I2cConf_I2cChannel_I2cChannel_0, &req);
}

/* 读一次温度，成功返回TRUE，结果通过outTemp传出 */
boolean SHT2x_ReadTemperature(float *outTemp)
{
    uint8 raw[2];
    uint16 rawVal;
    printf("---> Inside SHT2x_ReadTemperatureFunc!\r\n");

    if (E_OK != SHT2x_SendCommand(SHT2X_CMD_TEMP_NOHOLD))
    {
        return FALSE;
    }

    /* No Hold模式下，温度测量典型耗时约66~85ms*/
    delay(4000000U);

    if (E_OK != SHT2x_ReadData(raw))
    {
        return FALSE;
    }

    rawVal = ((uint16)raw[0] << 8) | raw[1];
    rawVal &= 0xFFFCU;   /* 低2位是状态位，清零 */

    *outTemp = -46.85f + 175.72f * ((float)rawVal / 65536.0f);
    return TRUE;
}

/* 读一次湿度，成功返回TRUE，结果通过outHumi传出 */
boolean SHT2x_ReadHumidity(float *outHumi)
{
    uint8 raw[2];
    uint16 rawVal;

    if (E_OK != SHT2x_SendCommand(SHT2X_CMD_HUMI_NOHOLD))
    {
    	printf("Fail at SendCommand!\r\n");
        return FALSE;
    }

    /* No Hold模式下，湿度测量典型耗时约22~29ms */
    delay(2000000U);

    if (E_OK != SHT2x_ReadData(raw))
    {
    	printf("Fail at ReadData!\r\n");
        return FALSE;
    }

    rawVal = ((uint16)raw[0] << 8) | raw[1];
    rawVal &= 0xFFFCU;

    *outHumi = -6.0f + 125.0f * ((float)rawVal / 65536.0f);
    return TRUE;
}

void App_SendSensorReport(float temp, float humi)
{
    uint16_t temp_int = (uint16_t)(temp * 100.0f);
    uint16_t humi_int = (uint16_t)(humi * 100.0f);
    uint8 buf[4];

    buf[0] = (uint8)(temp_int >> 8);
    buf[1] = (uint8)(temp_int & 0xFF);
    buf[2] = (uint8)(humi_int >> 8);
    buf[3] = (uint8)(humi_int & 0xFF);

    CDD_CanTransmit(CanIfTxPduCfg_2 , buf, 8);
}
