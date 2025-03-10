//
// Created by zyc on 25-3-10.
//

#ifndef PRINTK_H
#define PRINTK_H
#include <stdarg.h>

void console_init(void);
void __vprintk(const char *fmt, va_list ap);
void printk(const char *fmt, ...);

#endif //PRINTK_H
