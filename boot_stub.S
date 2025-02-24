/*
 *   Created by zyc on 25-2-23.
*/

#include "mem_addr.h"

.section ".boot"

.global _start
_start:
    // 清零BSS段
    adr	x0, bss_start
    adr	x1, bss_end
    cmp x0, x1
    // 若BSS段长度为0，直接去set_sp
    b.eq set_sp
meminit:
    str xzr, [x0], #8
    cmp x0, x1
    b.ne meminit

set_sp:
    // 链接脚本里面设置的栈，大小为0x1000
    adr x0 , stack_top
    mov sp , x0
    // 执行主函数
    bl inmate_main
    // 若主函数返回，直接无限制循环
    b dead_loop

dead_loop:
    b dead_loop
