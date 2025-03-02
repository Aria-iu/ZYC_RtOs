//
// Created by zyc on 25-3-2.
//
#define UART_BASE2_ADDR  0xfe660000ULL

void uart_poll_send(unsigned char ch)
{
    /* 暂不使用uart，先直接写串口寄存器地址 */
    // serial_putc((char)ch);
    volatile int time = 5000;
    *(unsigned int *)UART_BASE2_ADDR = ch;
    while (time--);
}

void TestPutc(unsigned char ch)
{
    uart_poll_send(ch);
    if (ch == '\n') {
        uart_poll_send('\r');
    }
}