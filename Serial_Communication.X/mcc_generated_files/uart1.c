#include <xc.h>
#include "uart1.h"

/**
  Section: UART1 APIs
*/

void UART1_Initialize(void)
{
    // Set the UART1 module to the options selected in the user interface.

    // STSEL 1; PDSEL 8N; RTSMD disabled; OVFDIS disabled; ACTIVE disabled; RXINV disabled; WAKE disabled; BRGH enabled; IREN disabled; ON enabled; SLPEN disabled; SIDL disabled; ABAUD disabled; LPBACK disabled; UEN TX_RX; CLKSEL PBCLK; 
    // Data Bits = 8; Parity = None; Stop Bits = 1;
    U1MODE = (0x8008 & ~(1<<15));  // disabling UARTEN bit
    // UTXISEL TX_ONE_CHAR; UTXINV disabled; ADDR 0; MASK 0; URXEN disabled; OERR disabled; URXISEL RX_ONE_CHAR; UTXBRK disabled; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x00;
    // BaudRate = 9600; Frequency = 8000000 Hz; BRG 207; 
    U1BRG = 0xCF;
    
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U1STASET = _U1STA_UTXEN_MASK;
    U1MODESET = _U1MODE_ON_MASK;   // enabling UART ON bit
    U1STASET = _U1STA_URXEN_MASK;
}



void UART1_Write(uint8_t txData)
{
    while(U1STAbits.UTXBF == 1)
    {
        
    }

    U1TXREG = txData;    // Write the data byte to the USART.
}

bool UART1_IsRxReady(void)
{
    return U1STAbits.URXDA;
}

bool UART1_IsTxReady(void)
{
    return ((!U1STAbits.UTXBF) && U1STAbits.UTXEN );
}

bool UART1_IsTxDone(void)
{
    return U1STAbits.TRMT;
}


uint32_t __attribute__((deprecated)) UART1_StatusGet (void)
{
    return U1STA;
}

void __attribute__((deprecated)) UART1_Enable(void)
{
    U1STASET = _U1STA_UTXEN_MASK;
    U1STASET = _U1STA_URXEN_MASK;
    U1MODESET = _U1MODE_ON_MASK;
}

void __attribute__((deprecated)) UART1_Disable(void)
{
    U1STACLR = _U1STA_UTXEN_MASK;
    U1STACLR = _U1STA_URXEN_MASK;
    U1MODECLR = _U1MODE_ON_MASK;
}


