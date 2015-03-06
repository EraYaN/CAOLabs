#include "LPC13xx.h"
#include "stdbool.h"
#include "delay.h"

//BUTTON1 PIO29
//BUTTON2 PIO14

static void init_button(void)
{
    LPC_GPIO3->DIR |= 1<<0;
    LPC_GPIO3->DIR |= 1<<1;
    LPC_GPIO2->DIR &= ~(1<<9);
}
static bool but1_pressed(void)
{
    if((LPC_GPIO2->DATA & (1 << 9))==0)
        return true;
    else
        return false;
}

static void led_toggle(void)
{
    LPC_GPIO3->DATA ^= 1 << 0;
}

int main (void)
{
    init_button();
	while (1)
    {
        if(but1_pressed()==true)
        {
            delay_ms(25);
            led_toggle();
            while(but1_pressed())
            {

            }
        }
        delay_ms(25);
    }
}
