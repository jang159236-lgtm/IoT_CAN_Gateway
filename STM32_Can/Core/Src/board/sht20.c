/*
 * sht20.c
 *
 *  Created on: Jun 10, 2026
 *      Author: 11812
 */

#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "sht20.h"

#define CONFIG_DEBUG_SHT2X /* Enable SHT20 debug */

#define SHT2X_CHIPADDR          0x40      /* SHT20 7-Bits Chip address */


#ifdef CONFIG_DEBUG_SHT2X
#define sht2x_print(format,args...) printf(format, ##args)
#else
#define sht2x_print(format,args...) do{} while(0);
#endif

#ifdef CONFIG_DEBUG_SHT2X
static inline void dump_buf(uint8_t *buf, uint32_t size)
{
    int      i;

    if(!buf)
        return ;

    for(i=0; i<size; i++)
        printf("%02x ", buf[i]);

    printf("\r\n");
}
#endif


enum
{
    TRIG_T_MEASUREMENT_HM    = 0xE3, // command trig. temp meas. hold master
    TRIG_RH_MEASUREMENT_HM   = 0xE5, // command trig. humidity meas. hold master
    TRIG_T_MEASUREMENT_POLL  = 0xF3, // command trig. temp meas. no hold master
    TRIG_RH_MEASUREMENT_POLL = 0xF5, // command trig. humidity meas. no hold master
    USER_REG_W               = 0xE6, // command writing user register
    USER_REG_R               = 0xE7, // command reading user register
    SOFT_RESET               = 0xFE  // command soft reset
};

static int sht2x_measure_value(uint8_t command, uint16_t *val);
static int sht2x_softreset(void);

int sht20_sample_TrH(float *temperature, float *humdity)
{
    uint16_t        raw_temp, raw_rh;
    float           temp, rh;
    int             rv;

    if( sht2x_softreset() < 0 )
    {
        sht2x_print("SHT20 soft reset failed.\r\n");
        goto OUT;
    }

    sht2x_print("Start to measurement temperature...\r\n");
    rv=sht2x_measure_value(TRIG_T_MEASUREMENT_POLL, &raw_temp);
    if( rv < 0 )
    {
        sht2x_print("I2C measurement temperature failed, rv=%d\r\n", rv);
        goto OUT;
    }

    temp = -46.85f + 175.72f * (float)raw_temp / 65536.0f;
    sht2x_print("Measure temperature: %.2f\r\n", temp);
    if( temperature )
        *temperature=temp;

    sht2x_print("Start to measurement relative humidity...\r\n");
    rv = sht2x_measure_value(TRIG_RH_MEASUREMENT_POLL, &raw_rh);
    if( rv < 0 )
    {
        sht2x_print("I2C measurement humidity failed, rv=%d\r\n", rv);
        goto OUT;
    }

    rh = -6.0f + 125.0f * (float)raw_rh / 65536.0f;
    sht2x_print("Measure relative humidity: %.1f%%\r\n", rh);
    if( humdity )
        *humdity=rh;

OUT:
    return rv;
}

int sht2x_softreset(void)
{
    uint8_t           command = SOFT_RESET;
    int               rv = 0;

    sht2x_print("Start soft reset sht2x\r\n");

    rv=HAL_I2C_Master_Transmit(&hi2c1, SHT2X_CHIPADDR<<1, &command, 1, 0xFFFFFFFF);
    if( rv != HAL_OK )
    {
        sht2x_print("SHT2X send soft reset command 0x%0x failure: rv=0x%02x\r\n", command, rv);
        return -rv;
    }

    HAL_Delay(15);
    return 0;
}

static int sht2x_checkcrc(uint8_t *data, uint8_t bytes, uint8_t checksum)
{
  uint8_t crc = 0;
  uint8_t i;
  uint8_t bit;

  //calculates 8-Bit checksum with given polynomial
  for (i=0; i<bytes; ++i)
  {
    crc ^= (data[i]);
    for (bit=8; bit>0; --bit)
    {
      if (crc & 0x80)
        crc = (crc << 1) ^ 0x0131; //POLYNOMIAL;
      else
        crc = (crc << 1);
    }
  }

  if (crc != checksum)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

static int sht2x_measure_value(uint8_t command, uint16_t *val)
{
    uint8_t        buf[3];    /* I2C receive buffer */
    int            count=4;    /* I2C read retry times */

    if( !val )
    {
        sht2x_print("SHT2X invalid input arguments\r\n");
        return -1;
    }

    if(TRIG_T_MEASUREMENT_POLL!=command && TRIG_RH_MEASUREMENT_POLL !=command )
    {
        sht2x_print("SHT2X unsupport command: 0x%0x\r\n", command);
        return -2;
    }

    if( HAL_I2C_Master_Transmit(&hi2c1, SHT2X_CHIPADDR<<1, &command, 1, 0xFFFFFFFF) != HAL_OK )
    {
        sht2x_print("SHT2X send measure command 0x%0x failure\r\n", command);
        return -3;
    }

    if(TRIG_T_MEASUREMENT_POLL == command)
        HAL_Delay(85);
    else
        HAL_Delay(29);

    while(count--)
    {
        memset(buf, 0, 3);

        if( HAL_OK == HAL_I2C_Master_Receive(&hi2c1, SHT2X_CHIPADDR<<1|1, buf, 3, 0xFFFFFFFF) )
        {
            break;
        }
        HAL_Delay(5);
    }

    if( sht2x_checkcrc(buf, 2, buf[2])< 0 )
    {
#ifdef CONFIG_DEBUG_SHT2X
        sht2x_print("Measurement data checksum failure:\r\n");
        dump_buf(buf, 3);
#endif
        return -4;
    }

    if(TRIG_T_MEASUREMENT_POLL == command)
        *val = buf[0]<<8|(buf[1]&0xFC); //14bits(1111 1100)
    else
        *val = buf[0]<<8|(buf[1]&0xF0); //12bits(1111 0000)

    sht2x_print("Measurement temperature value: 0x%04x\r\n", *val);

  return 0;
}
