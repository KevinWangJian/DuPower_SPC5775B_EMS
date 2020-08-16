/*
 * Xcp_Integration.h
 *
 *  Created on: May 24, 2018
 *      Author: CIX2SGH
 */

#ifndef XCP_OVERLAYMEM_H
#define XCP_OVERLAYMEM_H

/*******************************************************************************
* Include Files
*******************************************************************************/
#include "Platform_Types.h"

/*******************************************************************************
* Macro Definitions
*******************************************************************************/
#define SIZE_KB(size)       ((uint32)(size * 1024UL))

/* CAL */
#define XCP_MEMACCESS_CAL_ADDR    0x40000000UL
#define XCP_MEMACCESS_CAL_SIZE    SIZE_KB(64)

/* System RAM - Exclude RAM for CAL */
#define XCP_MEMACCESS_RAM0_ADDR   0x40000000UL
#define XCP_MEMACCESS_RAM0_SIZE   SIZE_KB(194)

/* Code */
#define XCP_MEMACCESS_CODE_ADDR   0x01000000UL
#define XCP_MEMACCESS_CODE_SIZE   SIZE_KB(1984)

/*******************************************************************************
* Function Declarations
*******************************************************************************/
extern void Xcp_UpdateTimeStamp(void);
extern uint32 Xcp_GetTimeStamp(void);

#endif /* XCP_OVERLAYMEM_H */
