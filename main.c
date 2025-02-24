//
// Created by zyc on 25-2-23.
//

#include <stdint.h>



/* {{{1 Defines */
#define TIMER_IRQ 27
#define BEATS_PER_SEC configTICK_RATE_HZ
#define ARM_SLEEP asm volatile("wfi" : : : "memory")
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

#define UART_BUFSIZE 72

#define UART_LOCK xSemaphoreTake(uart_mutex, portMAX_DELAY)
#define UART_UNLOCK xSemaphoreGive(uart_mutex)
#define UART_OUTPUT(args...) do { if(pdPASS == UART_LOCK) { printf(args); UART_UNLOCK;} } while(0)


#define USE_CACHE_MMU 1


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
		ARM_SLEEP;
	}
}
/* }}} */

/* vim:foldmethod=marker
 */
