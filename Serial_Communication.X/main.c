#include "mcc_generated_files/system.h"
#define ULONG  unsigned long
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/attribs.h>
#define  CORE_COUNT 2000000

void UART1_Initialize(void);
void UART1_Write(uint8_t txData);
uint8_t UART1_Read1();
uint8_t UART1_Read(int D1,int D2);
int MYASCII(int data_value);
void digit(int num,int num1, int num2);
void delay (ULONG milisec);
void UART1_Write(uint8_t txData);
bool UART1_IsRxReady(void);

// Variables Declaration
volatile int first_digit = 8;// First digit of the 7-Segment
volatile int second_digit=22;// Second digit of the 7-Segment
volatile int purity = 21;
volatile int zero = 0;
volatile int one = 1;
volatile bool state = true;
volatile uint8_t check = 0;
char Raw_data[63];//create a string to store the recieved data
uint8_t myData;// A variable for storing recieved data
uint8_t myInfo;// A variable for storing the processed recieved data
int i=0; 
    
void __attribute__((vector(_UART1_RX_VECTOR), interrupt(IPL5SOFT))) UART_ISR(void){
    myData = UART1_Read1();
        if (myData!=141) {
            myInfo = myData-128;
            Raw_data[i]=myInfo; // storing the values in a string
            i++;
            IFS0bits.U1RXIF = 0; // clear the UART flag  
            check =0;
        }
        else {         
            first_digit = MYASCII(Raw_data[59]);
            second_digit= MYASCII(Raw_data[60]);
            i = 0;
            purity = first_digit*10+second_digit;          
            IFS0bits.U1RXIF = 0;//clear the UART flag
            check = 0;
        }       
}
void __attribute__((vector(_CORE_TIMER_VECTOR), interrupt(IPL6SOFT))) CoreTimerISR(void) { 
    state = !state;
    check ++;
    if (check>2){
       first_digit = 23;
       second_digit= 23;
    }
    //LATBbits.LATB13 = ~LATBbits.LATB13;
    IFS0bits.CTIF = 0;//clear the interrupt flag
    _CP0_SET_COUNT(0);
    _CP0_SET_COMPARE(CORE_COUNT);  
}

uint8_t UART1_Read(int D1,int D2) {
    while(!(U1STAbits.URXDA == 1)) {  
            digit(D1,zero,one);
            delay(1);
            digit(D2,one,zero);
            delay(1);     
    }
    if ((U1STAbits.OERR == 1)){
        U1STACLR = _U1STA_OERR_MASK;
    }
    return U1RXREG;
}
uint8_t UART1_Read1()
{
    while(!(U1STAbits.URXDA == 1));
    if ((U1STAbits.OERR == 1)){
        U1STACLR = _U1STA_OERR_MASK;
    }
    return U1RXREG;
}
int main(void) {
   
    SYSTEM_Initialize();
    UART1_Initialize(); // Configuring UART settings
    
    TRISBbits.TRISB13=0;
    ANSELBbits.ANSB13=0; 
    
    __builtin_disable_interrupts();
    _CP0_SET_COMPARE(CORE_COUNT); // configure the device to generate an interrupt when the count is 2000000
    IPC0bits.CTIP=6;//set priority at level and this must match the priority set in the ISR
    IPC0bits.CTIS=0;// set sub_priority
    IFS0bits.CTIF=0;// clear the interrupt flag
    IEC0bits.CTIE=1;// enable the interrupt
    
    
    IPC5bits.U1RXIP = 5;//set priority
    IPC5bits.SPI1RXIS = 0;
    IFS0bits.U1RXIF = 0;//clear flag
    IEC0bits.U1RXIE= 1;//enable interrupt
     __builtin_enable_interrupts();
    _CP0_SET_COUNT(0);   
   LATBbits.LATB9 = 1;
   LATBbits.LATB8 = 1;
    while (1) {
        if ((purity < 82)&& (state==false)) {
            LATBbits.LATB9 = 1;
            LATBbits.LATB8 = 1;
        }
        else {
            digit(first_digit,zero,one);
            delay(1);
            digit(second_digit,one,zero);
            delay(1);
        }   
    }
     return 1; 
}
int MYASCII(int data_value){
    switch(data_value){
        case 48: return (0); break;
        case 49: return (1); break;
        case 50: return (2); break;
        case 51: return (3); break;
        case 52: return (4); break;
        case 53: return (5); break;
        case 54: return (6); break;
        case 55: return (7); break;
        case 56: return (8); break;
        case 57: return (9); break;
        default: /*return ();*/ break;
    }          
}
void digit(int num,int num1, int num2){
    LATBbits.LATB9 = num1;
    LATBbits.LATB8 = num2;    
    switch (num){
        case 0:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 0;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 0;
            LATBbits.LATB6 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB10= 1;       
            break;
        case 1:
            LATBbits.LATB2 = 1;
            LATBbits.LATB3 = 0;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 1;
            LATBbits.LATB6 = 1;
            LATBbits.LATB7 = 1;
            LATBbits.LATB10= 1;
            break;
        case 2:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 0;
            LATAbits.LATA2 = 1;
            LATBbits.LATB5 = 0;
            LATBbits.LATB6 = 0;
            LATBbits.LATB7 = 1;
            LATBbits.LATB10= 0;
            break;
        case 3:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 0;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 0;
            LATBbits.LATB6 = 1;
            LATBbits.LATB7 = 1;
            LATBbits.LATB10= 0;
            break;
        case 4:
            LATBbits.LATB2 = 1;
            LATBbits.LATB3 = 0;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 1;
            LATBbits.LATB6 = 1;
            LATBbits.LATB7 = 0;
            LATBbits.LATB10= 0;
            break;
        case 5:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 1;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 0;
            LATBbits.LATB6 = 1;
            LATBbits.LATB7 = 0;
            LATBbits.LATB10= 0;
            break;
        case 6:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 1;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 0;
            LATBbits.LATB6 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB10= 0;
            break;
        case 7:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 0;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 1;
            LATBbits.LATB6 = 1;
            LATBbits.LATB7 = 1;
            LATBbits.LATB10= 1;
            break;
        case 8:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 0;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 0;
            LATBbits.LATB6 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB10= 0;
            break;
        case 9:
            LATBbits.LATB2 = 0;
            LATBbits.LATB3 = 0;
            LATAbits.LATA2 = 0;
            LATBbits.LATB5 = 0;
            LATBbits.LATB6 = 1;
            LATBbits.LATB7 = 0;
            LATBbits.LATB10= 0;
            break;
        default:
            LATBbits.LATB2 = 1;
            LATBbits.LATB3 = 1;
            LATAbits.LATA2 = 1;
            LATBbits.LATB5 = 1;
            LATBbits.LATB6 = 1;
            LATBbits.LATB7 = 1;
            LATBbits.LATB10= 1;
            break;
    }
   
}
void delay (ULONG milisec) {  
    ULONG  newtime;
    newtime = milisec *512;
    T1CON = 0x8010;  
    TMR1 = 0x00; 
   T1CONbits.ON;
    ULONG  i = 0;  
    PR1 = 0x40;  
    while(i != newtime) {  
        while(TMR1) {  
        }  
        i++;  
        TMR1 = 0x00;  
    }  
    T1CON = 0x00;  
    return;  
}
