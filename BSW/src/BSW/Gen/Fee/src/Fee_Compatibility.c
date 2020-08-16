

/*
 * The Compatibility unit contains variables that were published by the Fee 1.0
 * However those variables are deprecated or not used any more.
 * Still they are filled with life to be compatible, but they are Fee internally not used as before.
*/

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "Fee.h"

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
Fee_Rb_WorkingStateType_ten Fee_Rb_WorkingState_en  = FEE_RB_IDLE_E;        /* Now: Fee_Prv_DriverState_en                  */
Fee_stMainType              Fee_stMain              = FEE_POLLING_MODE_E;   /* Now: Fee_Prv_Medium_st.sync_b                */
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_32
#include "Fee_MemMap.h"
uint32                      Fee_SecChngCnt_u32      = 0;                    /* Now: Fee_Prv_Fs2SectorAll_st.maxCounter_u32  */
#define FEE_STOP_SEC_VAR_INIT_32
#include "Fee_MemMap.h"
/*
 **********************************************************************************************************************
 * Implementation
 **********************************************************************************************************************
*/

/**
 * \brief   Get the maximum sector counter
 *
 * \return  Maximum sector change counter
*/
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
uint32 Fee_Rb_GetSectChngCnt(void)
{
    return(Fee_SecChngCnt_u32);
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/
