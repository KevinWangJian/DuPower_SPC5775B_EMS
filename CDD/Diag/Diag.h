/*
 * Diag.h
 *
 *  Created on: 2019Äê10ÔÂ11ÈÕ
 *      Author: admin
 */

#ifndef CDD_DIAG_DIAG_H_
#define CDD_DIAG_DIAG_H_

#include "Platform_Types.h"



#define ACDCINVOLT_OVER_LIMIT 437u   //437=1.15*380
#define ACDCINVOLT_UNDER_LIMIT 323u   //323=0.85*380

extern unsigned char Fault_Result_Return(void);

extern void CloseRelayDevice_mainfun(void);
extern void Volt_Diag_mainfun(void);



extern unsigned char get_GbCQC_ACDCOverVolt_flg(void);
extern unsigned char get_GbCQC_ACDCUnderVolt_flg(void);
extern unsigned char get_GbCQC_APSOverVolt_flg(void);
extern unsigned char get_GbCQC_HVISO_flg(void);
extern unsigned char get_GbCQC_APSOverVolt_flg(void);
extern unsigned char get_GbCQC_APSUnderVolt_flg(void);
extern unsigned char get_GbCQC_DCDCTimeout_flg(void);
extern unsigned char get_GbCQC_ACDCTimeout_flg(void);
#endif /* CDD_DIAG_DIAG_H_ */
