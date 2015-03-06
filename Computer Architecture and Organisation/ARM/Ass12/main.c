#include "LPC13xx.h"
#include "delay.h"

static void init(void)
{
    LPC_GPIO3->DIR|=1<<0;
    /* *(volatile uint32_t *)0x50038000UL|=1<<0;*/
}

static void led_on(void)
{
    LPC_GPIO3->DATA&=~(1<<0);
    /* *(volatile uint32_t *)0x50033FFCUL&=~(1<<0);*/
}
static void led_off(void)
{
    LPC_GPIO3->DATA|=1<<0;
    /* *(volatile uint32_t *)0x50033FFCUL|=1<<0; */
}

int main (void)
{
    init();

	while (1)
    {
        led_on();
        delay_ms(500);
        led_off();
        delay_ms(500);
	}
}
