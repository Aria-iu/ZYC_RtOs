# 日志系统
ZYC_RtOs 基于串口驱动提供消息打印，在此基础上实现日志输出（记录）。

## 日志模块
```c
ZYC_RtOs
---ZYC_RtOs
------log
---------log.c
---------log.h
---------log_level.h
```

## 日志机制
提供系统级别日志设置 g_log_level。用户可以在任何时刻设置日志级别，日志级别如下：
```c
enum LogLevel {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
}
```

## 日志 API
日志模块提供的API如下：
```c
void init_log(log_level_t log_level);
void ani_printk(const char *fmt, ...);
void println(const char *fmt, ...);
void log(log_level_t level, const char *format, ...);
void LOGD(const char *format,...);
void LOGI(const char *format,...);
void LOGW(const char *format,...);
void LOGE(const char *format,...);
void LOGF(const char *format,...);
```
log输出日志时会指定消息的级别，只有指定的级别大于设置的 g_log_level 才会进行输出。

## 使用建议
默认设置为 LOG_INFO。


