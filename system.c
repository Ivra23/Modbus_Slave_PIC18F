/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "system.h"
#include <plib/usart.h>
#include <plib/pps.h>

void ClsUSART(void)
{
   RCSTA2 &= 0b01001111;  // Disable the receiver
   TXSTA2bits.TXEN = 0;   //  and transmitter
   PIE3 &= 0b11001111;   // Disable both interrupts
}

void InitUSART(void)
{
/******************************************************************************/
/* This just sets up the relevant parameters for the UART                     */
/******************************************************************************/
  //-----SPBRG needs to be changed depending upon oscillator frequency-------
  unsigned long spbrg = 0;

  OSCCON = 0b01110001;                // switch to 8MHz INTOSC clock source
     
  spbrg = SYS_FREQ/BAUD_RATE; // define these in system.h
  spbrg /= 4;
  spbrg -= 1;
  ClsUSART();    //Incase USART already opened
  writeEnConf = 0; //Set up TRIS register as output for write enable/disable
  writeEnable = 0;
  
  TXSTA2 = 0;           // Reset USART registers to POR state
  RCSTA2 = 0;
  
  //Remap USART2
  PPSUnLock();
  PPSOutput(PPS_RP23, PPS_TX2CK2);    // TX2 RP23/RD6
  PPSInput(PPS_RX2DT2, PPS_RP22);     // RX2 RP22/RD5
  PPSLock();

  //Set USART2 enabled
  TXSTA2bits.CSRC = TRUE;
  TXSTA2bits.TX9 = FALSE; // 8-bit mode
  TXSTA2bits.TXEN = TRUE;
  TXSTA2bits.SYNC = FALSE; // Async mode
  TXSTA2bits.SENDB = FALSE;// Sync break option (not sure)
  TXSTA2bits.BRGH = TRUE;  // High speed
  //TXSTA2bits.TRMT = ND
  TXSTA2bits.TX9D = FALSE;
 
  RCSTA2bits.SPEN = TRUE;
  RCSTA2bits.RX9 = FALSE; //8-bit reception
  RCSTA2bits.SREN = FALSE;
  RCSTA2bits.CREN = TRUE; //Continuous receive
  RCSTA2bits.ADDEN = FALSE;
  RCSTA2bits.FERR = FALSE;
  RCSTA2bits.OERR = FALSE;
  RCSTA2bits.RX9D = FALSE;
  BAUDCON2bits.ABDOVF = FALSE;
  BAUDCON2bits.RCIDL = TRUE;
  //BAUDCON2bits.RXDTP = ND
  BAUDCON2bits.TXCKP = FALSE;
  BAUDCON2bits.BRG16 = FALSE; // 8-bit Baud register*/
    
  PIE3bits.RC2IE = 1;   // Interrupt on receive
  PIE3bits.TX2IE = 0;   // Interrupt on transmit
  //IPR3bits.RC2IP = 0;
 
  // Baud Rate:
  SPBRG2 = spbrg; //0xCF; // Write baudrate to SPBRG1 spbrg
  
  baud2USART(BAUD_IDLE_TX_PIN_STATE_HIGH & BAUD_IDLE_RX_PIN_STATE_HIGH & BAUD_AUTO_OFF & BAUD_WAKEUP_OFF & BAUD_16_BIT_RATE & USART_RX_INT_ON);
}

void InitTimer1(void)
{   
    
    //IPR1bits.TMR1IP = 0;

    T1CONbits.TMR1ON  = 0;
    
    T1CONbits.TMR1CS1 = 1; 
    T1CONbits.TMR1CS0 = 0;
    T1CONbits.T1CKPS1 = 0;
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1OSCEN = 1;
    T1CONbits.nT1SYNC = 1;
    T1CONbits.RD16    = 1;
   
    TMR1H = 0xFF;  // Write high byte to Timer1 (for 1.04ms)) 0x7A , 0xE1
    TMR1L = 0xDE;  // Write low byte to Timer1
    
    T1CONbits.TMR1ON = 1;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
}

void ConfigInterrupts(void)
{
    RCONbits.IPEN   = 1; // disable interrupt priority
    //INTCONbits.GIEL  = 1; // enable interrupts
    //INTCONbits.GIEH = 1;
    INTCONbits.GIE  = 1; // enable interrupts 
    INTCONbits.PEIE = 1; // enable peripheral interrupts
}
