/*
 * M95640.h
 *
 *  Created on: Jun 29, 2018
 *      Author: CIX2SGH
 */

#ifndef M95640_H
#define M95640_H

#include "typedefs.h"
#include "Platform_Types.h"

#define OK					0x00
#define ERROR				0xFF

#define WAIT_T	    		200

#define PageByte    		32          //Page Size
#define EEPM95640_SIZE		8192        //M95640 total size 8KB

#define EEPCHECK_ADDR      	0x1FFF  	//EEPROM check address

#define Eepm95640BeginAddress	0x0000	//EEPROM start address

//Write-Protected Block Size
#define SPM_NONE	       	0x00    	//Software Protected (none)
#define SPM_UPPER_QUARTER  	0x04    	//Software Protected (Upper quarter  1800h - 1FFFh(M95640))
#define SPM_UPPER_HALF     	0x08    	//Software Protected (Upper half     1000h - 1FFFh(M95640))
#define SPM_WHOLE_MEMORY   	0x0C    	//Software Protected (Whole memory   0000h - 1FFFh(M95640))

#define HPM_NONE	       	0x80   	 	//Hardware Protected (none)
#define HPM_UPPER_QUARTER  	0x84    	//Hardware Protected (Upper quarter  1800h - 1FFFh(M95640))
#define HPM_UPPER_HALF     	0x88    	//Hardware Protected (Upper half     1000h - 1FFFh(M95640))
#define HPM_WHOLE_MEMORY   	0x8C    	//Hardware Protected (Whole memory   0000h - 1FFFh(M95640))

extern uint8 WriteEepm95640Flag;

extern void Eepm95640_Init(void);
extern void Eepm95640_MainFunction(void);

Std_ReturnType Eepm95640_Erase(uint16_t address, uint16_t size);
Std_ReturnType Eepm95640_Write(uint16_t WriteAddr, uint8 *pBuffer, uint16_t NumToWrite, uint16_t *written);
Std_ReturnType Eepm95640_Read(uint16_t ReadAddr, uint8 *pBuffer, uint16_t NumToRead);
Std_ReturnType Eepm95640_Compare (uint16_t SourceAddress, uint8 *pTargetAddressPtr, uint16_t Length);
boolean        Eepm95640_IsInWriting(void);

#endif /* M95640_H */
