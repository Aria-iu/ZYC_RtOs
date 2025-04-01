/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) ARM Limited, 2014
 *
 * Authors:
 *  Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */


#include <inmate.h>
#include "log.h"
#include "mem.h"
#include "fsc_mem.h"

struct foo{
	int a;
	int b;
};

void inmate_main(void)
{
    log_init(LOG_INFO);
    mem_detect();
    mem_init();
    LOGI("mem init end\n");


    LOGI("fsc : g_fscMemBitMap is 0x%x\n",g_fscMemBitMap);
    LOGI("fsc : g_memTotalSize is 0x%x\n",g_memTotalSize);
    LOGI("fsc : g_memUsage is 0x%x\n",g_memUsage);
    LOGI("fsc : g_memPeakUsage is 0x%x\n",g_memPeakUsage);
    LOGI("fsc : g_memStartAddr is 0x%x\n",g_memStartAddr);
    
    int size = sizeof(struct foo);
    LOGI("sizeof foo is %d\n",size);

    struct foo * foo_ptr;
    foo_ptr = (struct foo *)PRT_MemAlloc(OS_MID_SYS,OS_MEM_DEFAULT_PT0,size);
    if (foo_ptr == 0){
    	 LOGE("fsc: alloc error\n");
    }else{
    	LOGI("fsc: alloc success , var foo_ptr 's address is 0x%x",foo_ptr);
    }
    
    LOGI("fsc : g_fscMemBitMap is 0x%x\n",g_fscMemBitMap);
    LOGI("fsc : g_memTotalSize is 0x%x\n",g_memTotalSize);
    LOGI("fsc : g_memUsage is 0x%x\n",g_memUsage);
    LOGI("fsc : g_memPeakUsage is 0x%x\n",g_memPeakUsage);
    LOGI("fsc : g_memStartAddr is 0x%x\n",g_memStartAddr);

	foo_ptr -> a = 10;
    foo_ptr -> b = 20;
LOGI("fsc: foo_ptr->a = %d\n", foo_ptr->a);
        LOGI("fsc: foo_ptr->b = %d\n", foo_ptr->b);

   


	  LOGI("fsc : g_fscMemBitMap is 0x%x\n",g_fscMemBitMap);
	      LOGI("fsc : g_memTotalSize is 0x%x\n",g_memTotalSize);
	          LOGI("fsc : g_memUsage is 0x%x\n",g_memUsage);
		      LOGI("fsc : g_memPeakUsage is 0x%x\n",g_memPeakUsage);
		          LOGI("fsc : g_memStartAddr is 0x%x\n",g_memStartAddr);


}


