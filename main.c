//
// Created by zyc on 25-2-23.
//

#include <stdint.h>
#include "uart/serial.h"
#include "uart/uart_core.h"
#include "uart/uart_dev.h"
#include "test.h"

#define TIMER_IRQ 27
#define BEATS_PER_SEC configTICK_RATE_HZ
#define ARM_SLEEP asm volatile("wfi" : : : "memory")
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#define UART_BUFSIZE 72
#define UART_LOCK xSemaphoreTake(uart_mutex, portMAX_DELAY)
#define UART_UNLOCK xSemaphoreGive(uart_mutex)
#define UART_OUTPUT(args...) do { if(pdPASS == UART_LOCK) { printf(args); UART_UNLOCK;} } while(0)
#define USE_CACHE_MMU 1

// ------------------------------------------------------------ gpio-led --------------------------------------
/*
* 		gpio0@fdd60000 {
			compatible = "rockchip,gpio-bank";
			reg = <0x00 0xfdd60000 0x00 0x100>;
			interrupts = <0x00 0x21 0x04>;
			clocks = <0x33 0x2e 0x33 0x0c>;
			gpio-controller;
			#gpio-cells = <0x02>;
			interrupt-controller;
			#interrupt-cells = <0x02>;
			phandle = <0x38>;
		};
 *
 * */
// #define PIO_R6_REG (0xfdd60000)
// #define PIO_R5_REG (0xfdd60000)
// --------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------uart ------------------------------------------


//---------------------------------------------------------------------------------------------------------------

static void prvSetupHardware(void)
{

}
/* }}} */


/* {{{1 main */
void inmate_main(void)
{
  // unsigned i;
  	prvSetupHardware();
	serial_init(&g_uart_cfg, &g_uart_ops);
	while(1){
//		 serial_putc('Z');
//		 serial_putc('Y');
//		 serial_putc('C');
//                TestPutc('t');
//                TestPutc('h');
//                TestPutc('i');
//                TestPutc('s');
//                TestPutc('i');
//                TestPutc('s');
//                TestPutc('t');
//                TestPutc('e');
//                TestPutc('s');
//                TestPutc('t');
	}
}
/* }}} */

/* vim:foldmethod=marker
 */
