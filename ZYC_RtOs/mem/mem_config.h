//
// Created by zyc on 25-3-10.
//

#ifndef MEM_CONFIG_H
#define MEM_CONFIG_H

// 内存基地址
#define OS_MEM_FSC_PT_ADDR                              (uintptr_t)&g_memRegion00[0]
// 内存大小，单位为 byte
#define OS_MEM_FSC_PT_SIZE                              0x10000
// 用户可以创建的最大分区数，取值范围[0,253]
#define OS_MEM_MAX_PT_NUM                               200

#endif //MEM_CONFIG_H
