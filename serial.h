//
// Created by zyc on 25-2-26.
//

#ifndef SERIAL_H
#define SERIAL_H

// NOW we can not enable uart irq
// #define UART7_IRQ

typedef void * sio_fd_t;

sio_fd_t serial_open(void);
// void serial_irq_rx_enable(sio_fd_t fd);
void serial_putchar(sio_fd_t fd, uint32_t c);
void serial_printf(sio_fd_t fd, const char *ctrl1, ...);
// int serial_irq_getchar(sio_fd_t fd);

#endif //SERIAL_H
