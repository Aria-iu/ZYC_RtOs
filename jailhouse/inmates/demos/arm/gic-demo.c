//
// Created by zyc on 25-3-10.
//

#include <inmate.h>
#include <gic.h>

#define BEATS_PER_SEC		10

static u64 ticks_per_beat;
static volatile u64 expected_ticks;

/*
 * Enables blinking LED
 * Banana Pi:           register 0x1c2090c, pin 24
 * Orange Pi Zero:      register 0x1c20810, pin 17
 */
static void *led_reg;
static unsigned int led_pin;

static void handle_IRQ(unsigned int irqn)
{
	static u64 min_delta = ~0ULL, max_delta = 0;
	u64 delta;

	if (irqn != TIMER_IRQ)
		return;

	delta = timer_get_ticks() - expected_ticks;
	if (delta < min_delta)
		min_delta = delta;
	if (delta > max_delta)
		max_delta = delta;

	printk("Timer fired, jitter: %6ld ns, min: %6ld ns, max: %6ld ns\n",
	       (long)timer_ticks_to_ns(delta),
	       (long)timer_ticks_to_ns(min_delta),
	       (long)timer_ticks_to_ns(max_delta));

	if (led_reg)
		mmio_write32(led_reg, mmio_read32(led_reg) ^ (1 << led_pin));

	expected_ticks = timer_get_ticks() + ticks_per_beat;
	timer_start(ticks_per_beat);
}

void inmate_main(void)
{
	printk("Initializing the GIC...\n");
	irq_init(handle_IRQ);
	irq_enable(TIMER_IRQ);

	printk("Initializing the timer...\n");
    // 每 1 秒 BEATS_PER_SEC 次 beat ， 每个 beat 有 ticks_per_beat 个 tick
	ticks_per_beat = timer_get_frequency() / BEATS_PER_SEC;
	expected_ticks = timer_get_ticks() + ticks_per_beat;
	timer_start(ticks_per_beat);

	led_reg = (void *)(unsigned long)cmdline_parse_int("led-reg", 0);
	led_pin = cmdline_parse_int("led-pin", 0);

	halt();
}
