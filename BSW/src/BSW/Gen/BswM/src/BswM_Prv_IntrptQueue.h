
#ifndef BSWM_PRV_INTRPT_QUEUE_H
#define BSWM_PRV_INTRPT_QUEUE_H

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/

typedef struct
{
    BswM_Cfg_MRPType_ten dataMRPType_en;
    uint16 idChannel_u16;
    uint16 idxMRPChnl_u16;
    uint16 dataReqMode_u16;
}BswM_Prv_IntrptQueueType_tst;

typedef struct
{
    uint8 idxHead_u8;
    uint8 idxTail_u8;
    uint8 dataSize_u8;
}BswM_Prv_IntrptQueueInfoType_tst;
/*
 **********************************************************************************************************************
 * Function definitions
 **********************************************************************************************************************
*/
#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

FUNC(void, BSWM_CODE) BswM_Prv_IntrptQueueIn(VAR(BswM_Cfg_MRPType_ten, AUTOMATIC) dataMRPType_en, VAR(uint16, AUTOMATIC) idChannel_u16, VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16);
FUNC(Std_ReturnType, BSWM_CODE) BswM_Prv_IntrptQueueOut(P2VAR(BswM_Cfg_MRPType_ten, AUTOMATIC, BSWM_VAR) dataMRPType_pen, P2VAR(uint16, AUTOMATIC, BSWM_VAR) idChannel_pu16, P2VAR(uint16, AUTOMATIC, BSWM_VAR) idxMRPChnl_pu16, P2VAR(uint16, AUTOMATIC, BSWM_VAR) dataReqMode_pu16);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_VAR_INIT_UNSPECIFIED
#include "BswM_Cfg_MemMap.h"

extern VAR(BswM_Prv_IntrptQueueInfoType_tst, BSWM_VAR) BswM_Prv_IntrptQueueInfo_st;

#define BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_PRV_INTRPT_QUEUE_H */
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
