
#include "xc.h"
#include "stdint.h"
#include "clock.h"
#include "system.h"

void CLOCK_Initialize(void)
{
    SYSTEM_RegUnlock();
    // TUN Center frequency; 
    OSCTUN = 0x00;
    // PLLODIV 1:4; PLLMULT 12x; PLLICLK FRC; 
    SPLLCON = 0x2050080;
    // SBOREN disabled; VREGS disabled; RETEN disabled; 
    PWRCON = 0x00;
    //CF No Clock Failure has been detected;; FRCDIV FRC/1; SLPEN Device will enter Idle mode when a WAIT instruction is issued; NOSC FRCDIV; SOSCEN enabled; CLKLOCK Clock and PLL selections are not locked and may be modified; OSWEN Switch is Complete; 
    OSCCON = (0x02);
    SYSTEM_RegLock();
    // ON disabled; DIVSWEN disabled; RSLP disabled; ROSEL SYSCLK; OE disabled; SIDL disabled; RODIV 0; 
    REFO1CON = 0x00;
    // ROTRIM 0; 
    REFO1TRIM = 0x00;
}
