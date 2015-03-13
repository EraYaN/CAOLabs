#include "LPC13xx.h"
//SDA = GPIO0 5
//SCL = GPIO0 4
//LPC_I2C->CONSET = (1<<5);
//LPC_I2C->CONCLR = (1<<3);
//LPC_I2C->DATA_BUFFER receive
//LPC_I2C->DAT            send
/*while(LPC_I2C->CONSET & (1<<5))
{
}*/

//0.0625C per count

//0x49 read, 0x48 write
//12C=0000 1100 0000 -30C= 1110 0010 0000
//0010 1010 1001=42,5625C  1101 0100 1000=-43.5
//8 bits
