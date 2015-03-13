#include "LPC13xx.h"
//Current with sleep mode: 18.93 mA
static void init()
{
    LPC_GPIO1->DIR |= 1<<6;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
    LPC_TMR32B0->MR3 = (720000); //720000
    LPC_TMR32B0->MR0 = (576000); //576000
    LPC_TMR32B0->PR = 0;
    LPC_TMR32B0->MCR |= (1<<10);
    LPC_TMR32B0->MCR |= (1<<9);
    LPC_TMR32B0->MCR |= (1<<0);
    LPC_TMR32B0->TCR |= 1<<1;
    LPC_TMR32B0->TCR &= ~(1<<1);
    LPC_TMR32B0->TCR |= 1<<0;
    //LPC_SYSCON->PDRUNCFG &= ~(1<<4);
    NVIC_EnableIRQ(TIMER_32_0_IRQn);

}
#include "LPC13xx.h"

static void init()
{
    LPC_GPIO1->DIR |= 1<<6;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
    LPC_TMR32B0->MR3 = (720000); //720000
    LPC_TMR32B0->MR0 = (576000); //576000
    LPC_TMR32B0->PR = 0;
    LPC_TMR32B0->MCR |= (1<<10);
    LPC_TMR32B0->MCR |= (1<<9);
    LPC_TMR32B0->MCR |= (1<<0);
    LPC_TMR32B0->TCR |= 1<<1;
    LPC_TMR32B0->TCR &= ~(1<<1);
    LPC_TMR32B0->TCR |= 1<<0;
    //LPC_SYSCON->PDRUNCFG &= ~(1<<4);
    NVIC_EnableIRQ(TIMER_32_0_IRQn);

}

static void pin_high()
{
    LPC_GPIO1->DATA |= 1<<6;
}

static void pin_low()
{
    LPC_GPIO1->DATA &= ~(1<<6);
}

void TIMER_32_0_Handler()
{
    if((LPC_TMR32B0->IR & (1 << 3)))
    {
        pin_high();
        LPC_TMR32B0->IR = 1<<3;
    }
    else if ((LPC_TMR32B0->IR & (1 << 0)))
    {
        pin_low();
        LPC_TMR32B0->IR = 1<<0;
    }
}

int main (void)
{
    init();
    pin_high();

    while (1)
    {

    }
}

static void pin_high()
{
    LPC_GPIO1->DATA |= 1<<6;
}

static void pin_low()
{
    LPC_GPIO1->DATA &= ~(1<<6);
}

void TIMER_32_0_Handler()
{
    if((LPC_TMR32B0->IR & (1 << 3)))
    {
        pin_high();
        LPC_TMR32B0->IR = 1<<3;
    }
    else if ((LPC_TMR32B0->IR & (1 << 0)))
    {
        pin_low();
        LPC_TMR32B0->IR = 1<<0;
    }
}

int main (void)
{
    init();
    pin_high();

    while (1)
    {
        __WFI();
    }
}
