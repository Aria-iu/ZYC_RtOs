//
// Created by zyc on 25-3-10.
//

#include <inmate.h>
#include "log.h"

void inmate_main(void)
{
	unsigned int i = 0, j;
	/*
	 * The cell config can set up a mapping to access UARTx instead of UART0
	 */
	log_init(LOG_INFO);
	while(++i) {
		for (j = 0; j < 100000000; j++);
		LOGI("Hello %d from cell!\n", i);
	}

	/* lr should be 0, so a return will go back to the reset vector */
}
