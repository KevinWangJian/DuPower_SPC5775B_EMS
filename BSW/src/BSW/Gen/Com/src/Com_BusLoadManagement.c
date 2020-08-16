

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

/**************************************************************************************************/
/* Global variables                                                                               */
/**************************************************************************************************/

#if (COM_COMMON_TX_PERIOD == STD_ON)
#define COM_START_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"
VAR(uint16,COM_VAR) Com_ReducedPeriod_u16;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_ReduceBusload
 Syntax           : void Com_ReduceBusload(uint16 CommonPeriod)
 Description      :
   The below function is used to change the Periodicity of all the Tx frames (periodic mode IPDUs and periodic part
   of mixed mode IPDUs)to a new value irrespective of their
   current cycle time. This can be used in the scenario where the Bus load has to be reduced while the tester is
   flashing other ECU.
   Input period is expected in resolution of Com_MainFunctionTx() raster time.(for ex: If Com_MainFunctionTx()
   is configured in 10ms raster then for 30 seconds  Cycletime = 3000)
   All message period is not changed to new period immediately.If there are message scheduled to be transmitted ,
   then they will be transmitted with old period once. After this the period will be changed to new period.
NOTE :
    Event triggered transmission is not affected by this functionality.
 Parameter        : CommonPeriod - New period (interms of multiples of Com_mainFunctionTx() raster time)
 Return value     : void
****************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ReduceBusload(VAR(uint16, AUTOMATIC) CommonPeriod)
{
  /* Check if COM module is initialised */
  if(Com_Uninit_Flag != COM_UNINIT)
  {
      Com_ReducedPeriod_u16 = CommonPeriod;
  }

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_RestoreBusload
 Syntax           : void Com_ReduceBusload(void)
 Description      :
   The below function is used to change the period of all the Tx frames to a old period from common TX period, set by
   function Com_ReduceBusload().
   After the call of the Com_ReduceBusload(), the configured period is applied immediately (ie the timer is loaded and
   started but the IPDU is not transmitted immediately).The periodic part of the IPDU is transmitted at
   the end of the configured period, respecting MDT.
 Parameter        : CycleTime - New period (interms of multiples of Com_mainFunctionTx() raster time)
 Return value     : void
****************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_RestoreBusload (void)
{
    Com_TxIpduRamPtrType TxIpduRamPtr;
    VAR( uint32_least, AUTOMATIC )   BufIdx;


    /* Check if COM module is initialised & common TX period is active */
    if((Com_Uninit_Flag != COM_UNINIT) && (Com_ReducedPeriod_u16 != 0))
    {
        Com_ReducedPeriod_u16 = 0;
        /* Loop through all TX IPDUs */

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(0);
        for (BufIdx = 0; BufIdx < COM_GET_NUM_TX_IPDU; BufIdx++)
        {
            /* Reload the configured period for PERIODIC and MIXED mode IPDUs.
               These IPDUs will be transmitted with configured period , after this function call */
            /* The CurrentTxModePtr points to the structure information of the current TxModeState */
            if((TxIpduRamPtr->CurrentTxModePtr->Mode == (uint8)COM_TXMODE_PERIODIC)
                || (TxIpduRamPtr->CurrentTxModePtr->Mode == (uint8)COM_TXMODE_MIXED))
            {
                TxIpduRamPtr ->Com_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->TimePeriodFact;
            }

            TxIpduRamPtr++;
        }/* END for loop */
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* COM_COMMON_TX_PERIOD */

