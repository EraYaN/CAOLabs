#include "LPC13xx.h"
#include "leddriver.h"

#define TMP102_READ_ADDR 0x49
#define TMP102_WRITE_ADDR 0x48
#define TMP102_DATLEN 2


static void init()
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);
    LPC_SYSCON->PRESETCTRL |= (1<<1);

    LPC_GPIO0->DIR |= 1<<4;
    LPC_GPIO0->DIR |= 1<<5;

    LPC_I2C->SCLH = SystemCoreClock/200000;
    LPC_I2C->SCLL = SystemCoreClock/200000;

    LPC_I2C->CONSET |= (1<<6);
}
int main (void)
{
    init_leds();
    init();
	while (1) { }
}
