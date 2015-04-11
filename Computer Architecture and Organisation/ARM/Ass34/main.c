#include "LPC13xx.h"
#include "leddriver.h"
#include "delay.h"
#include "states.h"
#include "stdbool.h"

#define TMP102_READ_ADDR 0x91
#define TMP102_WRITE_ADDR 0x90
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

    LPC_I2C->CONSET = (1<<6);
    NVIC_EnableIRQ(I2C_IRQn);
}

static void i2cstart()
{
    LPC_I2C->CONSET = (1<<5);
}

static void i2cstartclr()
{
    LPC_I2C->CONCLR = (1<<5);
}

static void i2cstop()
{
    LPC_I2C->CONSET = (1<<4);
}

static void i2creset()
{
    LPC_I2C->CONCLR = (1<<2);
    LPC_I2C->CONCLR = (1<<3);
    LPC_I2C->CONCLR = (1<<5);
}

static void i2cack()
{
    LPC_I2C->CONSET = (1<<2);
}

static void i2cackclr()
{
    LPC_I2C->CONCLR = (1<<2);
}

static void i2csiclr()
{
    LPC_I2C->CONCLR = (1<<3);
}

static uint8_t i2creadbyte()
{
    return LPC_I2C->DATA_BUFFER;
}


static void i2cwritebyte(uint8_t d)
{
    LPC_I2C->DAT = d;
}

static uint8_t datacount = 0;
static uint8_t led_data = 0;
static uint8_t data[TMP102_DATLEN];
static bool is_init = true;

void I2C_Handler()
{
    //set_leds(LPC_I2C->STAT);
    switch(LPC_I2C->STAT)
    {
    case StartRX:
        if(is_init){
            i2cwritebyte(TMP102_WRITE_ADDR);
        }else{
            i2cwritebyte(TMP102_READ_ADDR);
        }
        break;
    case RStartRX:
        i2cwritebyte(TMP102_READ_ADDR);
        break;
    case ARBLOST:
        i2cstart();
        break;
    case SLAWACK:
        i2cstartclr();
        i2cack();
        break;
    case SLAWNACK:
        i2cstop();
        //led_data=1;
        //set_leds(led_data);
        delay_ms(250);
        i2cstart();
        break;
    case SLARACK:
        i2cstartclr();
        i2cack();
        break;
    case SLARNACK:
        i2cstop();
        //led_data=1;
        //set_leds(led_data);
        delay_ms(250);
        i2cstart();
        break;
    case DATACKTX:
        i2cwritebyte(0);
        break;
    case DATNACKTX:
        is_init=false;
        i2cstart();
        break;
    case DATACKRX:
        data[datacount] = i2creadbyte();
        datacount++;
        if(datacount == TMP102_DATLEN)
        {
            i2cackclr();
        }
        else
        {
            i2cack();
        }
        break;
    case DATNACKRX:
        //last byte
        data[datacount] = i2creadbyte();
        datacount = 0;
        //map data to leds LS four bits of first received bye and MS four bits of second received byte
        //led_data = ((data[1]&0x0F)>>4)|((data[0]&0xF)<<4);
        led_data=data[0];
        set_leds(led_data);
        //ask for temp again
        i2cstop();
        //delay_ms(250);
        i2cstart();
        break;
    }
    //led_data=LPC_I2C->STAT;
    //clear interrupt
    i2csiclr();



}


int main (void)
{
    init_leds();
    init();
    i2cstart();
    while (1)
    {
    }
}
