
#ifndef _UART1_H
#define _UART1_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif



void UART1_Initialize(void);

uint8_t UART1_Read(void);

void UART1_Write(uint8_t txData);

/**
  @Description
    Indicates of there is data available to read.

  @Returns
    true if byte can be read.
    false if byte can't be read right now.
*/
bool UART1_IsRxReady(void);

/**
  @Description
    Indicates if a byte can be written.
 
 @Returns
    true if byte can be written.
    false if byte can't be written right now.
*/
bool UART1_IsTxReady(void);

/**
  @Description
    Indicates if all bytes have been transferred.
 
 @Returns
    true if all bytes transfered.
    false if there is still data pending to transfer.
*/
bool UART1_IsTxDone(void);

/*******************************************************************************

  !!! Deprecated API and types !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/

/** UART1 Driver Hardware Flags

  @Summary
    Specifies the status of the hardware receive or transmit

  @Description
    This type specifies the status of the hardware receive or transmit.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/
typedef enum
{
    /* Indicates that Receive buffer has data, at least one more character can be read */
    UART1_RX_DATA_AVAILABLE = (1 << 0),
    /* Indicates that Receive buffer has overflowed */
    UART1_RX_OVERRUN_ERROR = (1 << 1),
    /* Indicates that Framing error has been detected for the current character */
    UART1_FRAMING_ERROR = (1 << 2),
    /* Indicates that Parity error has been detected for the current character */
    UART1_PARITY_ERROR = (1 << 3),
    /* Indicates that Receiver is Idle */
    UART1_RECEIVER_IDLE = (1 << 4),
    /* Indicates that the last transmission has completed */
    UART1_TX_COMPLETE = (1 << 8),
    /* Indicates that Transmit buffer is full */
    UART1_TX_FULL = (1 << 9) 
}UART1_STATUS;

/**
  @Summary
    Allows setting of a the enable bit for the UART1 mode

  @Description
    This routine is used to enable the UART1
  
  @Preconditions
    UART1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to UART1_Initialize(); for an example
*/

void __attribute__((deprecated)) UART1_Enable(void);

/**
  @Summary
    Allows setting of a the disable bit for the UART1 mode

  @Description
    This routine is used to disable the UART1
  
  @Preconditions
    UART1_Initialize() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to UART1_Initialize(); for an example
*/

void __attribute__((deprecated)) UART1_Disable(void);

/**
  @Summary
    Returns the transmitter and receiver status

  @Description
    This returns the transmitter and receiver status. The returned status may 
    contain a value with more than one of the bits
    specified in the UART1_STATUS enumeration set.  
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    UART1_Initialize function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    A UART1_STATUS value describing the current status 
    of the transfer.

  @Example
    <code>
        while(!(UART1_StatusGet & UART1_TX_COMPLETE ))
        {
           // Wait for the tranmission to complete
        }
    </code>
*/
uint32_t __attribute__((deprecated)) UART1_StatusGet (void );

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // _UART1_H
