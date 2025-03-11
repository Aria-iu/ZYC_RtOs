//
// Created by zyc on 25-3-10.
//

#ifndef LOG_H
#define LOG_H
#include "log_level.h"

void init_log(log_level_t log_level);
void ani_printk(const char *fmt, ...);
void println(const char *fmt, ...);
void log(log_level_t level, const char *format, ...);
void LOGD(const char *format,...);
void LOGI(const char *format,...);
void LOGW(const char *format,...);
void LOGE(const char *format,...);
void LOGF(const char *format,...);

#endif //LOG_H
