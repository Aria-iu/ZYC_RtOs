//
// Created by zyc on 25-3-10.
//

#include <inmate.h>
#include "log.h"
#include "mem.h"

void inmate_main(void)
{
    log_init(LOG_INFO);
    LOGI("This is a test for mem boarder\n");
    LOGI("Hello from cell!\n");
    bool r = mem_test(mem_conf_size-0x4);
    if (r) {
      LOGI("TEST PASS\n");
    }else{
      LOGI("TEST FAIL\n");
    }
}