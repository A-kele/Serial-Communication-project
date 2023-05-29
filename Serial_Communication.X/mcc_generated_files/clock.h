
#ifndef CLOCK_H
#define	CLOCK_H


#include <stdbool.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ  8000000UL
#endif

#define CLOCK_SystemFrequencyGet()        (8000000UL)

#define CLOCK_PeripheralFrequencyGet()    (CLOCK_SystemFrequencyGet())

#define CLOCK_InstructionFrequencyGet()   (CLOCK_SystemFrequencyGet())

void CLOCK_Initialize(void);


#endif	