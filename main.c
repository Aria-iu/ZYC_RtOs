//
// Created by zyc on 25-2-23.
//

#include <stdint.h>
#include "serial.h"

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

	while(1){
		dw8250_uart4_init();
		putchar('z');
		putchar('y');
		putchar('c');
		ARM_SLEEP;
	}
}
/* }}} */

/* vim:foldmethod=marker
 */
