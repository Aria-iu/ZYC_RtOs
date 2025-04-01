//
// Created by zyc on 25-3-10.
//

#include "log.h"
#include <stdarg.h>
#include <inmate.h>
#include <uart.h>

log_level_t g_log_level;

/**
 * @param[in]  log_level    需要设置的系统日志级别
 */
void log_init(log_level_t log_level){
    console_init();
    g_log_level = log_level;
}

void ani_printk(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    __vprintk(fmt, ap);
    va_end(ap);
}

void println(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    __vprintf(fmt, ap);
    va_end(ap);
    ani_printk("\n");
}

/**
* @param[in]  log_level    日志级别
* @param[in]  format       字符串
*/
void log(log_level_t level, const char *format, ...){
    if (level < g_log_level) return;
    va_list ap;
    va_start(ap, format);
    switch (level) {
      case LOG_DEBUG:
        ani_printk("[ZYC_RtOs : DEBUG] : ");
        break;
      case LOG_INFO:
        ani_printk("[ZYC_RtOs : INFO] : ");
        break;
      case LOG_WARNING:
        ani_printk("[ZYC_RtOs : WARNING] : ");
        break;
      case LOG_ERROR:
        ani_printk("[ZYC_RtOs : ERROR] : ");
        break;
      case LOG_FATAL:
        ani_printk("[ZYC_RtOs : FATAL] : ");
        break;
      default:
        ani_printk("[ZYC_RtOs !!!!] : unknown log level : %d\n", level);
        break;
    }
    __vprintk(format, ap);
    va_end(ap);
}

void LOGD(const char *format,...){
    if (LOG_DEBUG < g_log_level) return;
    ani_printk("[ZYC_RtOs : DEBUG] : ");
    va_list ap;
    va_start(ap, format);
    __vprintk(format, ap);
    va_end(ap);
}

void LOGI(const char *format,...){
    if (LOG_INFO < g_log_level) return;
    ani_printk("[ZYC_RtOs : INFO] : ");
    va_list ap;
    va_start(ap, format);
    __vprintk(format, ap);
    va_end(ap);
}

void LOGW(const char *format,...){
    if (LOG_WARNING < g_log_level) return;
    ani_printk("[ZYC_RtOs : WARNING] : ");
    va_list ap;
    va_start(ap, format);
    __vprintk(format, ap);
    va_end(ap);
}

void LOGE(const char *format,...){
    if (LOG_ERROR < g_log_level) return;
    ani_printk("[ZYC_RtOs : ERROR] : ");
    va_list ap;
    va_start(ap, format);
    __vprintk(format, ap);
    va_end(ap);
}

void LOGF(const char *format,...){
    if (LOG_FATAL < g_log_level) return;
    ani_printk("[ZYC_RtOs : FATAL] : ");
    va_list ap;
    va_start(ap, format);
    __vprintk(format, ap);
    va_end(ap);
}
