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

void inmate_main(void)
{
    log_init(LOG_INFO);
    mem_detect();
    mem_init();
    LOGI("mem init end");
}

