#include "Uart.h"
#include "CDD_Uart.h"
#include "Std_Types.h"


/*
 * printf字符发送
 */
int __io_putchar(int ch)
{
    uint8 c = (uint8)ch;

    (void)Uart_SyncSend(
            0,      // Uart Channel ID
            &c,
            1,
            1000
    );

    return ch;
}


/*
 * printf重定向
 */
int _write(int file, char *ptr, int len)
{
    (void)file;

    for(int i = 0; i < len; i++)
    {
        __io_putchar((int)ptr[i]);
    }

    return len;
}
