//
// Created by zyc on 25-3-13.
//
#ifndef TASK_H
#define TASK_H

#include "ZYC_error.h"
#include "ZYC_types.h"
#include "ZYC_module.h"
#include "task.h"

/*
 * 任务名的最大长度。
 *
 * 任务名的最大长度，包括结尾符'\0'。
 */
#define OS_TSK_NAME_LEN 16

/*
 * 任务错误码：申请内存失败。
 *
 * 值: 0x02000301
 *
 * 解决方案: 分配更大的私有FSC内存分区
 *
 */
#define OS_ERRNO_TSK_NO_MEMORY OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x01)

/*
 * 任务错误码：指针参数为空。
 *
 * 值: 0x02000302
 *
 * 解决方案: 检查参数指针是否为NUL。
 */
#define OS_ERRNO_TSK_PTR_NULL OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x02)

/*
 * 任务错误码：任务栈大小未按16字节大小对齐。
 *
 * 值: 0x02000303
 *
 * 解决方案: 检查入参任务栈大小是否按16字节对齐。
 */
#define OS_ERRNO_TSK_STKSZ_NOT_ALIGN OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x03)

/*
 * 任务错误码：任务优先级非法。
 *
 * 值: 0x02000304
 *
 * 解决方案: 检查入参任务优先级不能大于63，其他平台不能大于31。
 */
#define OS_ERRNO_TSK_PRIOR_ERROR OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x04)

/*
 * 任务错误码：任务入口函数为空。
 *
 * 值: 0x02000305
 *
 * 解决方案: 检查入参任务入口函数是否为NULL。
 */
#define OS_ERRNO_TSK_ENTRY_NULL OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x05)

/*
 * 任务错误码：任务名的指针为空或任务名为空字符串。
 *
 * 值: 0x02000306
 *
 * 解决方案: 检查任务名指针和任务名。
 */
#define OS_ERRNO_TSK_NAME_EMPTY OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x06)

/*
 * 任务错误码：指定的任务栈空间太小。
 *
 * 值: 0x02000307
 *
 * 解决方案: 检查任务栈是否小于OS_TSK_MIN_STACK_SIZE。
 */
#define OS_ERRNO_TSK_STKSZ_TOO_SMALL OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x07)

/*
 * 任务错误码：任务ID非法。
 *
 * 值: 0x02000308
 *
 * 解决方案: 检查当前运行任务的PID是否超过任务最大数或检查用户入参任务PID是否合法。
 */
#define OS_ERRNO_TSK_ID_INVALID OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x08)

/*
 * 任务错误码：任务已被挂起。
 *
 * 值: 0x02000309
 *
 * 解决方案: 检查所挂起任务是否为已挂起任务。
 */
#define OS_ERRNO_TSK_ALREADY_SUSPENDED OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x09)

/*
 * 任务错误码：任务未被挂起。
 *
 * 值: 0x0200030a
 *
 * 解决方案: 检查所恢复任务是否未挂起。
 */
#define OS_ERRNO_TSK_NOT_SUSPENDED OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x0a)

/*
 * 任务错误码：任务未创建。
 *
 * 值: 0x0200030b
 *
 * 解决方案: 检查任务是否创建。
 */
#define OS_ERRNO_TSK_NOT_CREATED OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x0b)

/*
 * 任务错误码：在锁任务的状态下删除当前任务。
 *
 * 值: 0x0300030c
 *
 * 解决方案: 用户确保删除任务时，将任务解锁。
 *
 */
#define OS_ERRNO_TSK_DELETE_LOCKED OS_ERRNO_BUILD_FATAL(OS_MID_TSK, 0x0c)

/*
 * 任务错误码：在硬中断的处理中进行延时操作。
 *
 * 值: 0x0300030d
 *
 * 解决方案: 此操作禁止在中断中进行调度。
 *
 */
#define OS_ERRNO_TSK_DELAY_IN_INT OS_ERRNO_BUILD_FATAL(OS_MID_TSK, 0x0d)

/*
 * 任务错误码：在锁任务的状态下进行延时操作。
 *
 * 值: 0x0200030e
 *
 * 解决方案: 检查是否锁任务。
 */
#define OS_ERRNO_TSK_DELAY_IN_LOCK OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x0e)

/*
 * 任务错误码：任务ID不在Yield操作指定的优先级队列中。
 *
 * 值: 0x0200030f
 *
 * 解决方案: 检查操作的任务的优先级。
 */
#define OS_ERRNO_TSK_YIELD_INVALID_TASK OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x0f)

/*
 * 任务错误码：Yield操作指定的优先级队列中，就绪任务数小于2。
 *
 * 值: 0x02000310
 *
 * 解决方案: 检查指定优先级就绪任务，确保就绪任务数大于1。
 */
#define OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x10)

/*
 * 任务错误码：没有可用的任务控制块资源或配置项中任务裁剪关闭。
 *
 * 值: 0x02000311
 *
 * 解决方案: 打开配置项中任务裁剪开关，并配置足够大的任务资源数。
 */
#define OS_ERRNO_TSK_TCB_UNAVAILABLE OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x11)

/*
 * 任务错误码：操作IDLE任务。
 *
 * 值: 0x02000312
 *
 * 解决方案: 检查是否操作IDLE任务。
 */
#define OS_ERRNO_TSK_OPERATE_IDLE OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x12)

/*
 * 任务错误码：在锁任务的状态下挂起当前任务。
 *
 * 值: 0x03000313
 *
 * 解决方案: 确保任务挂起的时候，任务已经解锁。
 *
 */
#define OS_ERRNO_TSK_SUSPEND_LOCKED OS_ERRNO_BUILD_FATAL(OS_MID_TSK, 0x13)

/*
 * 任务错误码：系统初始化任务激活失败。
 *
 * 值: 0x02000314
 *
 * 解决方案: 查看任务栈是否配置错误。
 *
 */
#define OS_ERRNO_TSK_ACTIVE_FAILED OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x14)

/*
 * 任务错误码：配置的任务数量太多，配置的最大任务个数不能大于254，
 * 总任务个数不包括Idle任务且不能为0。
 *
 * 值: 0x02000315
 *
 * 解决方案: 在任务配置项中将最大任务数改为小于等于254且大于0。
 */
#define OS_ERRNO_TSK_MAX_NUM_NOT_SUITED OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x15)

/*
 * 任务错误码：获取任务信息时，用户实际欲获取任务数为0。
 *
 * 值: 0x02000316
 *
 * 解决方案: 获取任务信息时，用户实际输入的欲获取任务数不为0。
 */
#define OS_ERRNO_TSK_INPUT_NUM_ERROR OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x16)

/*
 * 任务错误码：用户配置的任务栈首地址未16字节对齐。
 *
 * 值: 0x02000317
 *
 * 解决方案: 配置进来任务栈首地址需16字节对齐。
 */
#define OS_ERRNO_TSK_STACKADDR_NOT_ALIGN OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x17)

/*
 * 任务错误码：任务正在操作队列。
 *
 * 值: 0x02000318
 *
 * 解决方案: 让被删除的任务得到调度读取完队列数据，即可删除。
 */
#define OS_ERRNO_TSK_QUEUE_DOING OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x18)

/*
 * 任务错误码：任务退出时没有完全释放资源。
 *
 * 值: 0x03000319
 *
 * 解决方案: 任务退出前确保完全释放其占有的资源(如消息，互斥信号量等)。
 *
 */
#define OS_ERRNO_TSK_EXIT_WITH_RESOURCE OS_ERRNO_BUILD_FATAL(OS_MID_TSK, 0x19)

/*
 * 任务错误码：解锁任务之前并未上锁。
 *
 * 值: 0x0200031a
 *
 * 解决方案: 任务上锁解锁必须配对使用，不能不加锁，直接解锁，可能导致误解锁。
 */
#define OS_ERRNO_TSK_UNLOCK_NO_LOCK OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x1a)

/*
 * 任务错误码：指定的任务栈地址太大导致任务栈初始化的时候整形溢出。
 *
 * 值: 0x0200031b
 *
 * 解决方案: 限制任务栈地址大小，确保任务栈初始化地址不大于0xFFFFFFFF。
 */
#define OS_ERRNO_TSK_STACKADDR_TOO_BIG OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x1b)

#define OS_ERRNO_TSK_OPERATION_BUSY OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x1c)

#define OS_ERRNO_TSK_BIND_CORE_INVALID OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x1d)

#define OS_ERRNO_TSK_BIND_IN_HWI OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x1e)

#define OS_ERRNO_TSK_BIND_SELF_WITH_TASKLOCK OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x1f)

#define OS_ERRNO_TSK_GET_CURRENT_COREID_INVALID OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x21)

#define OS_ERRNO_TSK_DESTCORE_NOT_RUNNING OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x22)

#define OS_ERRNO_BUILD_ID_INVALID   OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x23)

/*
 * 任务错误码：任务继承优先级中
 *
 * 值: 0x02000324
 *
 * 解决方案: 等待任务恢复原本优先级后再设置任务的优先级
 */
#define OS_ERRNO_TSK_PRIORITY_INHERIT OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x24)

/*
 * 任务错误码：任务阻塞在互斥信号量上
 *
 * 值: 0x02000325
 *
 * 解决方案: 等待任务恢复调度后再设置任务的优先级
 */
#define OS_ERRNO_TSK_PEND_MUTEX OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x25)

/*
 * 任务错误码：任务阻塞在优先级信号量上
 *
 * 值: 0x02000326
 *
 * 解决方案: 等待任务恢复调度后再设置任务的优先级
 */
#define OS_ERRNO_TSK_PEND_PRIOR OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x26)

/*
 * 任务错误码：重设优先级时低于阻塞在目标任务持有的互斥信号量的任务的优先级
 *
 * 值: 0x02000327
 *
 * 解决方案: 等待目标任务释放互斥信号量后再设置优先级
 */
#define OS_ERRNO_TSK_PRIOR_LOWER_THAN_PENDTSK OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x27)

/*
 * 任务错误码：删除任务时，任务持有互斥信号量
 *
 * 值: 0x02000328
 *
 * 解决方案: 删除任务前应该将其持有的互斥信号量释放
 */
#define OS_ERRNO_TSK_HAVE_MUTEX_SEM OS_ERRNO_BUILD_ERROR(OS_MID_TSK, 0x28)



/*
 * 任务或任务控制块状态标志。
 *
 * 任务控制块未被使用。
 */
#define OS_TSK_UNUSED 0x0000

/*
 * 任务或任务控制块状态标志。
 *
 * 任务控制块被使用,任务被创建。
 */
#define OS_TSK_INUSE 0x0001

/*
 * 任务或任务控制块状态标志。
 *
 * 任务被阻塞（等待信号）。
 */
#define OS_TSK_WAIT_SIGNAL 0x0002

/*
 * 任务或任务控制块状态标志。
 *
 * 任务被挂起。
 */
#define OS_TSK_SUSPEND 0x0004

/*
 * 任务或任务控制块状态标志。
 *
 * 任务被阻塞（等待信号量）。
 */
#define OS_TSK_PEND 0x0008

/*
 * 任务或任务控制块状态标志。
 *
 * 任务在等待信号量或者事件的标志。
 */
#define OS_TSK_TIMEOUT 0x0010

/*
 * 任务或任务控制块状态标志。
 *
 * 任务被延时。
 */
#define OS_TSK_DELAY 0x0020

/*
 * 任务或任务控制块状态标志。
 *
 * 任务已就绪，已加入就绪队列。
 */
#define OS_TSK_READY 0x0040

/*
 * 任务或任务控制块状态标志。
 *
 * 任务正运行，仍在就绪队列。
 */
#define OS_TSK_RUNNING 0x0080


/*
 * 任务ID的类型定义。
 */
typedef U32 TskHandle;

/*
 * 任务优先级的类型定义。
 */
typedef U16 TskPrior;

/*
 * 任务状态的类型定义。
 */
typedef U16 TskStatus;

/*
 * 任务信息结构体
 */
struct TskInfo{
    /* 任务切换时的SP */
    uintptr_t sp;
    /* 任务切换时的PC */
    uintptr_t pc;
    /* 任务状态 */
    TskStatus taskStatus;
    /* 任务优先级 */
    TskPrior taskPrio;
    /* 任务栈的大小 */
    U32 stackSize;
    /* 任务栈的栈顶 */
    uintptr_t topOfStack;
    /* 任务名 */
    char name[OS_TSK_NAME_LEN];
    /* 任务当前核 */
    U32 core;
    /* 任务入口函数 */
    void *entry;
    /* 任务控制块地址 */
    void *tcbAddr;
    /* 栈底 */
    uintptr_t bottom;
    /* 栈当前使用的大小 */
    U32 currUsed;
    /* 栈使用的历史峰值 */
    U32 peakUsed;
    /* 栈是否溢出 */
    // bool ovf;
    /* 任务上下文 */
//    struct TskContext context;
};

/*
 * 任务模块配置信息的结构体定义。
 *
 * 保存任务模块的配置项信息。
 */
struct TskModInfo {
    /* 最大支持的任务数 */
    U32 maxNum;
    /* 缺省的任务栈大小 */
    U32 defaultSize;
    /* Idle任务的任务栈大小 */
    U32 idleStackSize;
    /* 任务栈初始化魔术字 */
    U32 magicWord;
    /* 时间片调度，时间片粒度，单位ms */
    U32 timeSliceMs;
};

/*
 * @brief 任务入口函数类型定义。
 *
 * @par 描述
 * 用户通过任务入口函数类型定义任务入口函数，在任务创建触发之后调用该函数进行任务执行。
 * @attention 无。
 *
 * @param param1 [IN]  类型#uintptr_t，传递给任务处理函数的第一个参数。
 * @param param2 [IN]  类型#uintptr_t，传递给任务处理函数的第二个参数。
 * @param param3 [IN]  类型#uintptr_t，传递给任务处理函数的第三个参数。
 * @param param4 [IN]  类型#uintptr_t，传递给任务处理函数的第四个参数。
 *
 * @retval 无。
 * @par 依赖
 * <ul><li>prt_task.h：该接口声明所在的头文件。</li></ul>
 * @see 无。
 */
typedef void (*TskEntryFunc)(uintptr_t param1, uintptr_t param2, uintptr_t param3, uintptr_t param4);

/*
 * @brief 任务创建钩子函数类型定义。
 *
 * @par 描述
 * 用户通过任务创建钩子函数类型定义任务创建钩子，在系统创建任务时，调用该钩子。
 * @attention 无。
 *
 * @param taskPid [IN]  类型#TskHandle，新创建任务的PID。
 *
 * @retval 无。
 * @par 依赖
 * <ul><li>prt_task.h：该接口声明所在的头文件。</li></ul>
 * @see 无。
 */
typedef U32(*TskCreateHook)(TskHandle taskPid);

/*
 * @brief 任务删除钩子函数类型定义。
 *
 * @par 描述
 * 用户通过任务删除钩子函数类型定义任务删除钩子，在系统对任务进行删除时，调用该钩子。
 * @attention 无。
 *
 * @param taskPid [IN]  类型#TskHandle，删除任务的PID。
 *
 * @retval 无。
 * @par 依赖
 * <ul><li>prt_task.h：该接口声明所在的头文件。</li></ul>
 * @see 无。
 */
typedef U32(*TskDeleteHook)(TskHandle taskPid);

/*
 * @brief 任务切换钩子函数类型定义。
 *
 * @par 描述
 * 用户通过任务切换钩子函数类型定义任务切换钩子，在系统对任务进行切换时，调用该钩子。
 * @attention 无。
 *
 * @param lastTaskPid [IN]  类型#TskHandle，上一个任务的PID。
 * @param nextTaskPid [IN]  类型#TskHandle，下一个任务的PID。
 *
 * @retval 无。
 * @par 依赖
 * <ul><li>prt_task.h：该接口声明所在的头文件。</li></ul>
 * @see 无。
 */
typedef U32(*TskSwitchHook)(TskHandle lastTaskPid, TskHandle nextTaskPid);

typedef U32 (*TaskNameAddFunc)(U32 taskId, const char *name);

/*
 * 任务栈信息的结构体定义。
 *
 * 保存任务栈的信息。
 */
struct TskStackInfo {
    /* 栈顶 */
    uintptr_t top;
    /* 栈底 */
    uintptr_t bottom;
    /* 栈当前SP指针值 */
    uintptr_t sp;
    /* 栈当前使用的大小 */
    U32 currUsed;
    /* 栈使用的历史峰值 */
    U32 peakUsed;
    /* 栈是否溢出 */
    // bool ovf;
};

/*
 * 任务创建参数的结构体定义。
 *
 * 传递任务创建时指定的参数信息。
 */
struct TskInitParam {
    /* 任务入口函数 */
    TskEntryFunc taskEntry;
    /* 任务优先级 */
    TskPrior taskPrio;
    U16 reserved;
    /* 任务参数，最多4个 */
    uintptr_t args[4];
    /* 任务栈的大小 */
    U32 stackSize;
    /* 任务名 */
    char *name;
    /*
     * 本任务的任务栈独立配置起始地址，用户必须对该成员进行初始化，
     * 若配置为0表示从系统内部空间分配，否则用户指定栈起始地址
     */
    uintptr_t stackAddr;
    /* 任务调度策略 */
    U16 policy;
};

/*
 * @brief 创建任务，但不激活任务。
 *
 * @par 描述
 * 创建一个任务。该任务不加入就绪队列，只处于挂起状态，用户需要激活该任务需要通过调用PRT_TaskResume函数将其激活。
 *
 * @attention
 * <ul>
 * <li>任务创建时，会对之前自删除任务的任务控制块和任务栈进行回收，用户独立配置的任务栈除外。</li>
 * <li>任务名的最大长度为16字节，含结束符。</li>
 * <li>同一核内任务名不允许重复。</li>
 * <li>若指定的任务栈大小为0，则使用配置项#OS_TSK_DEFAULT_STACK_SIZE指定的默认的任务栈大小。</li>
 * <li>任务栈的大小必须按16字节大小对齐。确定任务栈大小的原则是，够用就行：多了浪费，少了任务栈溢出。</li>
 * <li>具体多少取决于需要消耗多少的栈内存，视情况而定：函数调用层次越深，栈内存开销越大，</li>
 * <li>局部数组越大，局部变量越多，栈内存开销也越大。</li>
 * <li>用户配置的任务栈首地址需16字节对齐。</li>
 * <li>用户配置的任务栈空间需由用户保证其合法性，即对可cache空间的地址用户需要保证其任务栈首地址及栈大小cache</li>
 * <li>line对齐，系统不做对齐处理，并在使用后需由用户进行释放。</li>
 * <li>任务创建时，任务创建参数中的任务栈大小配置建议不要使用最小任务栈大小OS_TSK_MIN_STACK_SIZE，</li>
 * <li>该项只是包含任务上下文预留的栈空间，任务调度时额外的任务开销需要由用户自行保证足够的任务栈空间配置。</li>
 * </ul>
 *
 * @param taskPid   [OUT] 类型#TskHandle *，保存任务PID。
 * @param initParam [IN]  类型#struct TskInitParam *，任务创建参数，
 * 其结构体中的成员参数stackAddr传入时必须进行初始化，若不采用用户配置的独立任务栈进行栈空间分配，
 * 该成员必须初始化为0。
 *
 * @retval #OS_OK  0x00000000，任务创建成功。
 * @retval #其它值，创建失败。
 * @par 依赖
 * <ul><li>prt_task.h：该接口声明所在的头文件。</li></ul>
 * @see PRT_TaskDelete | PRT_TaskCreateHookAdd | PRT_TaskCreate
 */
extern U32 PRT_TaskCreate(TskHandle *taskPid, struct TskInitParam *initParam);
void TskExit(int Tskid);
void load_current_context(struct TskContext* context);
#endif
