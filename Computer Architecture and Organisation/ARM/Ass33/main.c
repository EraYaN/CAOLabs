#include "LPC13xx.h"
#include "leddriver.h"

#define TMP102_READ_ADDR 0x49
#define TMP102_WRITE_ADDR 0x48
#define TMP102_DATLEN 2


static void init()
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);
    LPC_SYSCON->PRESETCTRL |= (1<<1);

    //LPC_GPIO0->DIR |= 1<<4;
    //LPC_GPIO0->DIR |= 1<<5;

    LPC_IOCON->PIO0_4 |= 1;
    LPC_IOCON->PIO0_5 |= 1;

    LPC_I2C->SCLH = SystemCoreClock/200000;
    LPC_I2C->SCLL = SystemCoreClock/200000;

    LPC_I2C->CONSET |= (1<<6);
}

static void i2cstart()
{
    LPC_I2C->CONSET |= (1<<5);
}

static void i2cstartclr()
{
    LPC_I2C->CONCLR |= (1<<5);
}

static void i2cstop()
{
    LPC_I2C->CONSET |= (1<<4);
}

static void i2creset()
{
    LPC_I2C->CONCLR |= (1<<2);
    LPC_I2C->CONCLR |= (1<<3);
    LPC_I2C->CONCLR |= (1<<5);
}

static void i2cack()
{
    LPC_I2C->CONSET |= (1<<2);
}

static void i2cackclr()
{
    LPC_I2C->CONCLR |= (1<<2);
}

static void i2csiclr()
{
    LPC_I2C->CONCLR |= (1<<3);
}

static uint8_t i2creadbyte()
{
    return LPC_I2C->DATA_BUFFER;
}


static void i2cwritebyte(uint8_t d)
{
    LPC_I2C->DAT = d;
}

static void setpointerregister()
{
    i2cstart();
    set_leds(1);
    while((LPC_I2C->CONSET & (1<<3)) != (1<<3))
    {
        set_leds(LPC_I2C->CONSET);
    }
    set_leds(2);
    i2cwritebyte(TMP102_WRITE_ADDR);
    while((LPC_I2C->CONSET & (1<<3)) != (1<<3))
    {
    }
    set_leds(4);
    i2cstartclr();
    i2cwritebyte(0);
    while((LPC_I2C->CONSET & (1<<3)) != (1<<3))
    {
    }
    set_leds(8);
    i2cstop();
}

static uint8_t datacount = 0;
static uint8_t led_data = 0;
static uint8_t data[TMP102_DATLEN];

int main (void)
{
    init_leds();
    init();
    setpointerregister();
    i2cstart();
    while (1)
    {
        led_data = 4;
        set_leds(led_data);
        //process i2c events
        if(LPC_I2C->CONSET & (1<<3))
        {
            switch(LPC_I2C->STAT)
            {
            case 0x08:
                i2cwritebyte(TMP102_READ_ADDR);
                break;
            case 0x10:
                i2cwritebyte(TMP102_READ_ADDR);
                break;
            case 0x38:
                i2cstart();
                break;
            case 0x40:
                i2cstartclr();
                if(datacount == TMP102_DATLEN)
                {
                    i2cackclr();
                }
                else
                {
                    i2cack();
                }
                break;
            case 0x48:
                i2cstop();
                i2cstart();
                break;
            case 0x50:
                data[datacount] = i2creadbyte();
                datacount++;
                break;
            case 0x58:
                //last byte
                data[datacount] = i2creadbyte();
                datacount = 0;
                //map data to leds LS four bits of first received bye and MS four bits of second received byte
                led_data = ((data[0]&0xF)<<4)|(data[1]&0xF0);
                //ask for temp again
                i2cstart();
                break;
            }
            //clear interrupt
            i2csiclr();

        }
    }
}
