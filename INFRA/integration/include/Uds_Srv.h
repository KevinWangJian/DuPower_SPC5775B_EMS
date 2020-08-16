/*
 * Uds_Srv.h
 *
 *  Created on: 2019Äê10ÔÂ16ÈÕ
 *      Author: admin
 */

#ifndef INFRA_INTEGRATION_INCLUDE_UDS_SRV_H_
#define INFRA_INTEGRATION_INCLUDE_UDS_SRV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Mcal.h"
#include "typedefs.h"
#include "Std_Types.h"


#define  UDS_UPDATE_ID		(0x18DBFFFAU)


void Uds_ReUpdate_Process(void);
extern void Uds_JumpToBootloader(void);
#ifdef __cplusplus
}
#endif
#endif /* INFRA_INTEGRATION_INCLUDE_UDS_SRV_H_ */
