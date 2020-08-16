

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
/**
****************************************************************************************************
Function creates queue for the requested size
\param[in]  DaqListPtr  daqlist pointer
\param[in]  Size_u16    queue size
\return     -
***************************************************************************************************/
void Xcp_CreateQue(Xcp_DaqList_t* DaqListPtr, uint16 Size_u16)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* initialize first ODT to read */
  DaqListPtr->DaqListQuePos.ReadPos_OdtNum_u16 = DaqListPtr->OdtFirst_u16;
  /* Assign the size of the que */
  DaqListPtr->DaqListQuePos.QueSize_u16 = Size_u16;

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
Function initializes queue of given daq list, resetting all values for queue and stim buffers
\param[in]  daqListNo_u16   daq list number
\param[in]  protLayerId     protocol layer id
\return     -
***************************************************************************************************/
void Xcp_InitDaqQueue(uint16 daqListNo_u16, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  Xcp_DaqList_t* daqListPtr;

  daqListPtr = &(XCP_DAQ(daqListNo_u16, protLayerId));
  /* initialize the ReadPos and WritePos */
  daqListPtr->DaqListQuePos.ReadPos_u16  = 0;
  daqListPtr->DaqListQuePos.WritePos_u16 = 0;
  daqListPtr->DaqListQuePos.ReadPos_OdtNum_u16 = daqListPtr->OdtFirst_u16;

  #if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  /* enter lock to change buffers */
  SchM_Enter_Xcp_BufferAccessActiveNoNest();
  daqListPtr->BufferInfo.BufferNumReadActive_u8  = 0xFFu;
  daqListPtr->BufferInfo.BufferNumReadNext_u8    = 0xFFu;
  daqListPtr->BufferInfo.BufferNumWriteActive_u8 = 0xFFu;
  daqListPtr->BufferInfo.OdtReceiveCtr_u8        = 0x0u;
  daqListPtr->BufferInfo.CntStimReceived_u8      = 0x0u;
  /* set bit, that no complete data set has been received */
  daqListPtr->BufferInfo.Status_u8 = XCP_STATUSBIT_STIM_ERR_NO_DATA_AVAILABLE;
  /* exit lock around buffer access */
  SchM_Exit_Xcp_BufferAccessActiveNoNest();
  #endif

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


#endif /* (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) */

/**
****************************************************************************************************
Function clears all queues and response buffers of given protocol layer
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_QueClearAll(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* set spin lock to avoid problems by queue processing */
  SchM_Enter_Xcp_SendingLong();
  SchM_Enter_Xcp_SendingShort();

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  {
    /* Local variables */
    uint16 daqListNo_u16;

    /* empty DAQ queues */
    for (daqListNo_u16=0; daqListNo_u16 < (Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16); daqListNo_u16++)
    {
      Xcp_InitDaqQueue(daqListNo_u16, protLayerId);
    }
  }
#endif
  /* clear response buffer */
  XCP_RES_BUFFER_LENGTH(protLayerId) = 0;
  /* clear event buffer */
  XCP_EV_BUFFER_LENGTH(protLayerId)  = 0;

  /* reset transmission pending flag */
  Xcp_Cleared[protLayerId].TxPending_b = FALSE;

  /* release lock */
  SchM_Exit_Xcp_SendingShort();
  SchM_Exit_Xcp_SendingLong();

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)

#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Function increments index of the next available available queue
\param[in]  DaqListPtr  daqlist pointer
\return     -
***************************************************************************************************/
void Xcp_QueReadNext(Xcp_DaqList_t* DaqListPtr)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  Xcp_Que_t* DaqListQuePos;

  /* fetch QueuePos pointer for faster access */
  DaqListQuePos = &(DaqListPtr->DaqListQuePos);

  /* Check if was the end of the que */
  if (DaqListQuePos->ReadPos_u16 == (DaqListQuePos->QueSize_u16 - 1))
  {
    /* end of the Queue is reached */
    DaqListQuePos->ReadPos_u16 = 0;
  }
  else
  {
    /* increment index to the next available buffer */
    DaqListQuePos->ReadPos_u16++;
  }

  /* check if last ODT */
  if ( DaqListQuePos->ReadPos_OdtNum_u16 == ((DaqListPtr->OdtFirst_u16 + DaqListPtr->OdtCnt_u8) - 1) )
  {
    /* reset to first ODT */
    DaqListQuePos->ReadPos_OdtNum_u16 = DaqListPtr->OdtFirst_u16;
  }
  else
  {
    /* increment to next ODT */
    DaqListQuePos->ReadPos_OdtNum_u16++;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function set back the given daq queue, e.g. in case of an unsuccessful transmit
\param[in]  DaqListPtr  daqlist pointer
\return     -
***************************************************************************************************/
void Xcp_QueSetBack(Xcp_DaqList_t* DaqListPtr)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  Xcp_Que_t* DaqListQuePos;

  /* fetch QueuePos pointer for faster access */
  DaqListQuePos = &(DaqListPtr->DaqListQuePos);

  /* Check if it was the beginning of the que */
  if (DaqListQuePos->ReadPos_u16 != 0)
  {
    /* decrement index to the latest buffer */
    DaqListQuePos->ReadPos_u16--;
  }
  else
  {
    /* set to the end of queue */
    DaqListQuePos->ReadPos_u16 = DaqListQuePos->QueSize_u16 - 1;
  }

  /* check if first ODT */
  if ( DaqListQuePos->ReadPos_OdtNum_u16 == DaqListPtr->OdtFirst_u16 )
  {
    /* reset to last ODT */
    DaqListQuePos->ReadPos_OdtNum_u16 = (DaqListPtr->OdtFirst_u16 + DaqListPtr->OdtCnt_u8) - 1;
  }
  else
  {
    /* decrement to previous ODT */
    DaqListQuePos->ReadPos_OdtNum_u16--;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

#endif /* (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) */


