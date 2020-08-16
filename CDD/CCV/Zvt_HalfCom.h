#ifndef CCV_STATE_H_
#define CCV_STATE_H_

//#include <stdio.h>
//#include <stdlib.h>
#include "Platform_Types.h"
#include "string.h"
#include "Zvt_Types.h"
#include "Zvt_Driver.h"
//#include <stdint.h>
//#include "ccv_types.h"

#include "fsm.h"

typedef parser_t ccv_parser_t;

typedef sigupdatefunc_t ccv_sigupdatefunc_t;

typedef enum
{
    CCV_SIG_ENTRY = FSM_SIG_ENTRY,
	CCV_SIG_EXIT = FSM_SIG_EXIT,

	CCV_SIG_BACK,

	CCV_SIG_CREDIT,
	CCV_SIG_MIFARE,

    CCV_SIG_USERSTOP,
    CCV_SIG_CREDIT_REVERSAL,

	CCV_SIG_CONFIG,

    CCV_SIG_DEFAULT
}ccv_signal_t;


typedef enum
{
    SGUS_STA_IDLE,
    SGUS_STA_CREDIT,
    SGUS_STA_MIFARE,
    SGUS_STA_USERSTOP,
    SGUS_STA_CREDITREVERSAL,
	SGUS_STA_PTCONFIG
}ccv_state_t;

extern uint8 CompareSimilarIpData(const uint8* ZvtIpData, const uint32* EthIpData);
extern void StateTask(void);


#endif // CCV_STATE_H_
