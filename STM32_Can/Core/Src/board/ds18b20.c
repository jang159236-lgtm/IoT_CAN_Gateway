#include "main.h"
#include "miscdev.h" /* 微秒级延时函数 udelay() 在该头文件中声明 */

/* 使用 HAL_Delay() 定义一个新的毫秒级的延时宏 mdelay(), 与Linux内核风格保持一致 */
#define mdelay(ms) HAL_Delay(ms)

/* 定义一个 GPIO 口的结构体类型，它有两个成员 */
typedef struct w1_gpio_s
{
    GPIO_TypeDef        *group; /* 这个GPIO口在哪个组 */
    uint16_t             pin;   /* 这个GPIO口的引脚号 */
} w1_gpio_t;

/* DS18B20 上的数据通信口 DQ 连到了 CPU 的 PA12 引脚上 */
static w1_gpio_t   W1Dat =
{
    .group = GPIOA,
    .pin   = GPIO_PIN_12,
};

/* 下面定义了一些DS18B20通信DQ引脚的操作宏，这里之所以用宏而不是函数是
 * 减少函数调用的CPU开销。在下面宏中最后面出现的 \ 为断行符，如果不清楚
 * 的话，可以自行 Deepseek 搜索学习：宏定义 断行符
 */

/* 这里定义了一个宏，用来初始化DQ引脚：设置为输入模式，并使能内部上拉 */
#define W1DQ_Input()        \
{   \
    GPIO_InitTypeDef GPIO_InitStruct = {0}; \
    GPIO_InitStruct.Pin = W1Dat.pin; \
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; \
    GPIO_InitStruct.Pull = GPIO_PULLUP; \
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
    HAL_GPIO_Init(W1Dat.group, &GPIO_InitStruct); \
}

/* 这里定义了一个宏，用来把 DQ 引脚设置为推挽输出模式 */
#define W1DQ_Output()       \
{   \
    GPIO_InitTypeDef GPIO_InitStruct = {0}; \
    GPIO_InitStruct.Pin = W1Dat.pin; \
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; \
    GPIO_InitStruct.Pull = GPIO_NOPULL; \
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
    HAL_GPIO_Init(W1Dat.group, &GPIO_InitStruct); \
}

/* 这里定义了一个宏，用来写控制 DQ 引脚时输出高电平还是低电平 */
#define W1DQ_Write(x)   HAL_GPIO_WritePin(W1Dat.group, W1Dat.pin, \
                        (x==1)?GPIO_PIN_SET:GPIO_PIN_RESET)

/* 这里定义了一个宏，用来读 DQ 引脚，当前时高电平还是低电平 */
#define W1DQ_Read()     HAL_GPIO_ReadPin(W1Dat.group,  W1Dat.pin)

/* 这里定义了一个枚举，用来定义低电平和高电平 */
enum {
    LOW,  /* 低电平：LOW=0 */
    HIGH, /* 高电平: LOW=1 */
};

/* 单总线上的所有通信都是以初始化序列开始，Master发出初始化信号后等待从设备的应答信号，以确定从设备是否存在并能正常工作。 */
static int ds18b20_reset(void)
{
    int time = 0;
    int present = 0; /* 设置默认值没有探测到 DS18B20 */

    /* 设置 DQ 引脚为输出模式 */
    W1DQ_Output();

    /* 主机(CPU)输出低电平，并保持低电平时间至少 480us，以产生复位脉冲。 */
    W1DQ_Write(LOW);
    udelay(480);

    /* 接着主机(CPU)释放总线， 4.7K 的上拉电阻将单总线拉高，延时 15～60 us，并进入接收模式(Rx) */
    W1DQ_Write(HIGH); // 这里先拉高是避免模式切换瞬间可能出现的不确定状态。
    udelay(60);
    W1DQ_Input();

    /* DS18B20芯片在收到主机发送过来的这个复位脉冲后，将会拉低总线 60~240 us，以产生低电平应答脉冲 */
    while( W1DQ_Read() && time<240) {
        time++;
        udelay(1);
    }

    /* 如果 time<240 则说明上面的while()循环是因为W1DQ_Read()读到了低电平(0) 跳出的，而不是超时
     * 跳出。这也就意味着CPU在这段期间读到了低电平，探测到DS18B20芯片了。
    */
    if( time < 240 )
        present = 1;

    /* 释放总线并维持至少480us */
    W1DQ_Output();
    udelay(480-time);

    return present;
}

/*
* 写 0 时序：主机输出低电平，延时 60us，然后释放总线，延时 2us；
* 写 1 时序：主机输出低电平，延时 2us，然后释放总线，延时 60us；
*/
void ds18b20_write_byte(uint8_t byte)
{
    uint8_t            i = 0;

    /* 设置 DS18B20的DQ引脚为输出模式 */
    W1DQ_Output();

    /* 1个字节包含8个位，DS18B20数据发送是LSB(低位先发送) */
    for(i=0; i<8; i++) {

        /* DS18B20的写0逻辑是将 DQ 拉低>=60us 后拉高,写1逻辑是拉低<=15us后拉高 */

        /* 这里先将 DS18B20 的 DQ 线线拉低 10us(<15us) */
        W1DQ_Write(LOW);
        udelay(10);

        /* 判断当前位是1还是0 */
        if( byte & 0x1 )
            W1DQ_Write(HIGH); /* 如果当前位是1，则现在就拉成高电平，这样低电平维持时间 10us */
        else
            W1DQ_Write(LOW); /* 如果当前位是0，则继续维持低电平，这样低电平维持时间位 10+下面的60us */

        /* 无论是写0还是写1，DQ的写时序都要大于15+15+30=60us */
        udelay(60);

        /* 发送0/1数据位完成后，拉高总线并延时 2us */
        W1DQ_Write(HIGH);
        udelay(2);

        /* 该字节数据右移1位，即再发下一位数据 */
        byte >>= 1;
    }
}

/* 当总线控制器把数据线从高电平拉到低电平时，读时序开始，数据线必须至少保持1us，然后总线被释放。
 * DS18B20 通过拉高或拉低总线上来传输”1”或”0”。
 */
uint8_t ds18b20_read_byte(void)
{
    uint8_t            i = 0;
    uint8_t            byte = 0;

    /* 1个字节包含8个位，DS18B20数据发送是LSB(低位先发送)，所以读也是LSB */
    for(i=0; i<8; i++) {
        /* 当CPU把数据线DQ拉低至少1us后，读时序开始。*/
        W1DQ_Output();
        W1DQ_Write(LOW);
        udelay(2);

        /* CPU拉高DQ释放总线 */
        W1DQ_Write(HIGH);
        udelay(2);

        /* CPU设置DQ为输入模式，等待DS18B20发数据过来，注意此时需要靠上拉电阻将总线拉成高电平 */
        W1DQ_Input();

        /* DS18B20开始以 LSB (lower bit first) 模式发送数据 */
        if( W1DQ_Read() ) {
            byte |= 1<<i; /* 如果接收到该位是高电平，则将相应位设置为1，否则为0 */
        }

        /* 读时序至少维持15+45=60us */
        udelay(60);

        /* CPU拉高DQ并释放总线 */
        W1DQ_Output();
        W1DQ_Write(HIGH);
        udelay(2);
    }

    return byte;
}

/* 该函数用来给 DS18B20 传感器发送开始采样温度命令 */
static inline int ds18b20_convert(void)
{
    /* 发送复位信号，看DS18B20模块是否在位，如果模块不在或坏了就返回错误值(-1)。 */
    if( !ds18b20_reset() )
        return -1;

    /* 这里我们不关心ROM中的16位产品序列号，就发送 Skip ROM 命令跳过SN的读取 */
    ds18b20_write_byte(0xCC);

    /* 发送 Convert T 命令，通知DS18B20开始温度采样 */
    ds18b20_write_byte(0x44);

    return 0;
}

/* 根据DS18B20的 CRC 校验公式(CRC = X^8 + X^5 + X^4 + 1) 来检测收到的数据是否出错 */
static int ds18b20_checkcrc(uint8_t *data, uint8_t length, uint8_t checksum)
{
    uint8_t     i, j, byte;
    uint8_t     mix = 0;
    uint8_t     crc = 0;

    for ( i=0; i<length; i++ ) {
        byte = data[i];

        for( j=0; j<8; j++ ) {
            mix = ( crc ^ byte ) & 0x01;
            crc >>= 1;
            if ( mix )
                crc ^= 0x8C; //POLYNOMIAL;
            byte >>= 1;
        }
    }

    return crc==checksum ? 1 : 0;
}

/* 读取 DS18B20 的采样温度值 */
static inline int ds18b20_read(uint8_t *out, int bytes)
{
    uint8_t     buf[9];
    uint8_t     i = 0;

    /* CPU给DS18B02发送复位信号并探测芯片是否存在 */
    if( !ds18b20_reset() )
        return -1;

    /* 这里我们不关心ROM中的16位产品序列号，就发送 Skip ROM 命令跳过SN的读取 */
    ds18b20_write_byte(0xCC);

    /* 发送 Read Scratchpad 命令开始读取DS18B20的采样温度值 */
    ds18b20_write_byte(0xBE);

    buf[i++] = ds18b20_read_byte(); /* 第1个字节是温度值的低字节(LSB) */
    buf[i++] = ds18b20_read_byte(); /* 第2个字节是温度值的高字节(MSB) */
    buf[i++] = ds18b20_read_byte(); /* 第3个字节不关心 */
    buf[i++] = ds18b20_read_byte(); /* 第4个字节不关心 */
    buf[i++] = ds18b20_read_byte(); /* 第5个字节是用户配置寄存器，也不关系 */
    buf[i++] = ds18b20_read_byte(); /* 第6个字节保留(0xFF) */
    buf[i++] = ds18b20_read_byte(); /* 第7个字节保留 */
    buf[i++] = ds18b20_read_byte(); /* 第8个字节保留(0x10) */
    buf[i++] = ds18b20_read_byte(); /* 第9个字节是CRC校验和 */

    /* 将读取到的前8个字节数据按照CRC公司计算校验和，与第9个字节做对比看是否匹配 */
    if( !ds18b20_checkcrc(buf, 8, buf[8]) ) {
        return -2; /* CRC校验失败就返回错误值 */
    }

    /* CRC校验通过就输出读到的2字节温度采样原始数据 */
    out[0]=buf[0];
    out[1]=buf[1];

    return 0;
}

int ds18b20_sample(float *temperature)
{
    uint8_t               byte[2];
    uint8_t               sign;
    uint16_t              temp;
    static uint8_t        firstin = 1;

    if( !temperature )
        return -1;

    /* 发送开始采样的命令 */
    if( ds18b20_convert()<0 )
        return -2;

    /* 芯片datasheet说明第一次启动采样最大需要750ms完成，否则将会在100ms内完成采样 */
    if( firstin ) {
        mdelay(750);
        firstin = 0;
    }
    else {
        mdelay(100);
    }

    /* 开始从DS18B20传感器读取2字节的原始数据 */
    if( ds18b20_read(byte, 2)<0 )
        return -3;

    /* 采样温度值两个字节，共16位。其中byte[0]为低字节、byte[1]为高字节：
     * LSB: Bits[0:3]为小数位 2^(-4) ~ 2^(-1) Bits[4:7]为整数位:2^0~2^3
     * MSB: Bits[0:2]为为整数位:2^4~2^6   Bits[3:7]为符号位: 全1表示温度为负值
     */

    /* 高字节的低3位为温度整数值，高8位为符号位。*/
    if( byte[1]> 0x7 ) { /* 如果>7(低三位最大为111=7)，说明为负值 */
        temp = ~(byte[1]<<8|byte[0]) + 1;
        sign=0;
    }
    else {
        temp = byte[1]<<8 | byte[0];
        sign=1;
    }

   /* DS18b20默认工作精度为12位，高8位是整数部分，低4位为小数部分。小数部分刻度为0.0625(1/16) */
    *temperature = (temp>>4) + (temp&0xF)*0.0625 ;
    if( !sign ) {
        *temperature = -*temperature;
    }

    return 0;
}
