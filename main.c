/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>        /* XC8 General Include File */
#include <p18cxxx.h>   /* C18 General Include File */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "modbus.h"

/******************************************************************************/
/* Modbus Global Variable Declaration                                         */
/******************************************************************************/
volatile unsigned int  holdingReg[50] = {0};
volatile unsigned char coils[50]= {0};
extern volatile char modbusMessage;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

//SAM NOT RECEIVING ANYTHING FROM TONYS GADGET..

void main(void)
{
  InitUSART();
  ConfigInterrupts();

  while(1){
    if(modbusMessage){
      decodeIt();}
    }
    LATBbits.LATB2 = 1;                 // LED green output
    TRISBbits.TRISB2 = 0; 
    //LATD = holdingReg[0];
    //LATCbits.LATC1 = coils[0];
}