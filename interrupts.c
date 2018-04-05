/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <p18cxxx.h>    /* C18 General Include File */
#include "modbus.h"
#include "system.h"

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/
volatile char endOfMessage,newMessage = 1;
volatile char timerCount,messageLength,modbusMessage,z = 0;
volatile unsigned char response[125]; //Enough to return all holding-r's
volatile unsigned char received[125]; //Enough to write all holding-r's 

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

void interrupt ISR(void)
{  
  if(ReceiveFlag1){ // USART receive interrupt flag has been set
    if((!endOfMessage)&&(!newMessage)){
      if(TransmitFlag1){     // check if the TXREG is empty
        received[z] = ReceiveBuffer;
        z++;
        timerCount = 0;
      }
    }
    if(newMessage){
      InitTimer1();
      if(TransmitFlag1){     // check if the TXREG is empty
        received[z] = ReceiveBuffer;
        z++;
        newMessage = 0;
        endOfMessage = 0;
        messageLength = 0;
        modbusMessage = 0;
        timerCount = 0;
        return;
      }
    }
  }else if(Timer1Flag){ //TMR0 interrupt flag
    modbusDelay();  //Resets timer for 1.04ms
    timerCount++;
    if(timerCount > 4){
      endOfMessage = 1;
      newMessage = 1;
      messageLength = z;
      modbusMessage = 1;
      for(z=(messageLength);z!=125;z++){ //Clear rest of message
        received[z] = 0;
      }
      z=0;
      T1CONbits.TMR1ON  = 0; //Close timer0
      timerCount = 0;
    }
   Timer1Flag = 0;  // Clear flag
  }
   /* if(PIR1bits.TMR1IF && PIE1bits.TMR1IE)
    {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xFF;  // Write high byte to Timer1
        TMR1L = 0xDE;  // Write low byte to Timer1
        TRISBbits.TRISB2 = !TRISBbits.TRISB2; // interrupt has occured.
    }*/
    /*if(PIR3bits.TX2IF)
    {
        PIR3bits.TX2IF = 0;
        Send_Data();      
    }*/
 }