//
// Created by zyc on 25-3-10.
//

#ifndef ZYC_ERROR_H
#define ZYC_ERROR_H

#include "ZYC_types.h"

/*
 * OS错误码标记位，0x00表示OS
 *
 */
#define ERRNO_OS_ID    (0x00U << 16)

/*
 * 定义错误的等级:提示级别
 *
 */
#define ERRTYPE_NORMAL (0x00U << 24)

/*
 * 定义错误的等级:告警级别
 *
 */
#define ERRTYPE_WARN   (0x01U << 24)

/*
 * 定义错误的等级:严重级别
 *
 */
#define ERRTYPE_ERROR  (0x02U << 24)

/*
 * 定义错误的等级:致命级别
 *
 */
#define ERRTYPE_FATAL  (0x03U << 24)

/*
 * @brief 定义OS致命错误。
 *
 * @par 描述
 * 宏定义，定义OS致命错误。
 *
 * @attention 无
 *
 * @param  mid   [IN] 模块ID编号。
 * @param  errno [IN] 错误码编号。
 *
 * @retval 无
 * @par 依赖
 * <li>prt_errno.h：该宏定义所在的头文件。</li>
 * @see OS_ERRNO_BUILD_ERROR | OS_ERRNO_BUILD_WARN | OS_ERRNO_BUILD_NORMAL
 */
#define OS_ERRNO_BUILD_FATAL(mid, errno) (ERRTYPE_FATAL | ERRNO_OS_ID | ((U32)(mid) << 8) | (errno))

/*
 * @brief 定义OS严重错误
 *
 * @par 描述
 * 宏定义，定义OS严重错误
 *
 * @attention 无
 * @param  mid   [IN] 模块ID编号。
 * @param  errno [IN] 错误码编号。
 *
 * @retval 无
 * @par 依赖
 * <li>prt_errno.h：该宏定义所在的头文件。</li>
 * @see OS_ERRNO_BUILD_FATAL | OS_ERRNO_BUILD_WARN | OS_ERRNO_BUILD_NORMAL
 */
#define OS_ERRNO_BUILD_ERROR(mid, errno) (ERRTYPE_ERROR | ERRNO_OS_ID | ((U32)(mid) << 8) | (errno))


#define OS_REPORT_ERROR(errNo)                                       \
do {                                                             \
   OsErrHandle("os_file", 0, (errNo), 0, NULL); \
} while (0)

extern void OsAsmIll(void);

#define OS_GOTO_SYS_ERROR() \
do {                    \
   OsAsmIll();         \
} while (0)



#endif //ZYC_ERROR_H
