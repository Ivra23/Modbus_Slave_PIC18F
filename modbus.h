/* 
 * File:   modbus.h
 * Author: Ibrahim
 *
 * Created on 26 mars 2018, 14:26
 */

#ifndef MODBUS_H
#define	MODBUS_H

#ifdef	__cplusplus
extern "C" {
#endif

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/
unsigned char checkCRC(void);
void clearResponse(void);
void readReg(void);         /* I/O and Peripheral Initialization */
void readInputReg(void);
void writeReg(void);
void readCoil(void);
void readInputCoil(void);
void writeCoil(void);
void modbusDelay(void);              /* Writes to Timer0 for 1.04ms delay*/
void decodeIt(void);
unsigned int generateCRC(unsigned char);


#ifdef	__cplusplus
}
#endif

#endif	/* MODBUS_H */

