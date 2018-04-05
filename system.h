/* 
 * File:   system.h
 * Author: Ibrahim
 *
 * Created on 26 mars 2018, 14:26
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

/*#ifdef	__cplusplus
extern "C" {
#endif*/
#include <plib/usart.h>

#define TRUE             1
#define FALSE            0
#define SYS_FREQ         8000000L  
#define FCY              SYS_FREQ/4
#define Timer1High       0xFF 
#define Timer1Low        0xDE 
#define BAUD_RATE        9600
#define SlaveAddress     2 
#define writeEnable      LATDbits.LATD7    //RE    //this is RO/RE
#define writeEnConf      TRISDbits.TRISD7       //to config RO/RE as output
#define readEnable       LATDbits.LATD3    //DE
#define readEbConf       TRISDbits.TRISD3
#define busyUsart        Busy2USART()
#define TransmitBuffer   TXREG2 
#define ReceiveBuffer    RCREG2 
#define ReceiveFlag1     PIR3bits.RC2IF  
#define TransmitFlag1    PIR3bits.TX2IF
#define Timer1Flag       PIR1bits.TMR1IF

void InitUSART(void);
void ClsUSART(void);
void InitTimer1(void);
void ConfigInterrupts(void);

/*#ifdef	__cplusplus
}
#endif*/

#endif	/* SYSTEM_H */

