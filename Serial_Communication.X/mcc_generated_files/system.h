
#ifndef _XTAL_FREQ
#define _XTAL_FREQ  8000000UL
#endif
#define WDT_CLR_KEY 0x5743

#include "xc.h"
#include "stdint.h"

#ifndef SYSTEM_H
#define	SYSTEM_H

inline static void SYSTEM_RegUnlock(void)
{
    SYSKEY = 0x0; //write invalid key to force lock
    SYSKEY = 0xAA996655; //write Key1 to SYSKEY
    SYSKEY = 0x556699AA; //write Key2 to SYSKEY
}

inline static void SYSTEM_RegLock(void)
{
   SYSKEY = 0x00000000; 
}


void SYSTEM_Initialize(void);
#endif	