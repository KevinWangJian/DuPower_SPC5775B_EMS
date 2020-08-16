

/*---------------------------------------------------------------------------------------*/
/*- Include files                                                                       -*/
/*---------------------------------------------------------------------------------------*/

#include "BswM.h"
#include "BswM_Prv.h"

/*---------------------------------------------------------------------------------------*/
/*- Definition of Global Functions                                                      -*/
/*---------------------------------------------------------------------------------------*/
#define BSWM_START_SEC_VAR_INIT_UNSPECIFIED
#include "BswM_Cfg_MemMap.h"

VAR(BswM_Prv_IntrptQueueInfoType_tst, BSWM_VAR) BswM_Prv_IntrptQueueInfo_st = {0, 0, 0};
static VAR(BswM_Prv_IntrptQueueType_tst, BSWM_VAR) BswM_Prv_IntrptQueue_ast[BSWM_RB_INTRPTQUEUE_MAXSIZE];

#define BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"


/************************************************************************************************
*Function name  : BswM_Prv_IntrptQueueIn (BswM_Cfg_MRPType_ten dataMRPType_en, uint16 idChannel_u16,
                            uint16 idxMRPChnl_u16, uint16 dataReqMode_u16)
*Description  : This function inserts mode request information into the interrupt queue.
*Parameters(in) :
*   dataMRPType_en- The type or source of the mode request (CamSMIndication, ComMIndication, etc)
*   idChannel_u16 - The ChannelId of the respective mode requester.
*   idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*   dataReqMode_u16 - The mode currently requested.
*Parameters(out): None
*Return value   : Std_ReturnType
*                 E_OK : The request has been successfully queued.
*                 E_NOT_OK : The queue is already full and new requests cannot be queued.
************************************************************************************************/

FUNC(void, BSWM_CODE) BswM_Prv_IntrptQueueIn
(
    VAR(BswM_Cfg_MRPType_ten, AUTOMATIC) dataMRPType_en,
    VAR(uint16, AUTOMATIC) idChannel_u16,
    VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
    VAR(uint16, AUTOMATIC) dataReqMode_u16
)
{
    /* Variable declaration*/
    VAR(uint8, AUTOMATIC) tailIndex_u8= 0;

    if(BSWM_RB_INTRPTQUEUE_MAXSIZE == BswM_Prv_IntrptQueueInfo_st.dataSize_u8)
    {

        

    }
    else
    {
        tailIndex_u8 = BswM_Prv_IntrptQueueInfo_st.idxTail_u8;

        /* Queue in the passed information*/
        BswM_Prv_IntrptQueue_ast[tailIndex_u8].dataMRPType_en = dataMRPType_en;
        BswM_Prv_IntrptQueue_ast[tailIndex_u8].idChannel_u16 = idChannel_u16;
        BswM_Prv_IntrptQueue_ast[tailIndex_u8].idxMRPChnl_u16 = idxMRPChnl_u16;
        BswM_Prv_IntrptQueue_ast[tailIndex_u8].dataReqMode_u16 = dataReqMode_u16;

        /* Increment the tail index and the size of the queue*/
        BswM_Prv_IntrptQueueInfo_st.idxTail_u8++;
        BswM_Prv_IntrptQueueInfo_st.dataSize_u8++;
        BswM_Prv_isReqstDelayed_b = TRUE;

        /* Has the final index of the queue been reached?*/
        if (BSWM_RB_INTRPTQUEUE_MAXSIZE == BswM_Prv_IntrptQueueInfo_st.idxTail_u8)
        {
            /*Reset the tail index to indicate the first index of the queue*/
            BswM_Prv_IntrptQueueInfo_st.idxTail_u8 = 0;
        }
    }
    return;
}

/************************************************************************************************
*Function name  : BswM_Prv_IntrptQueueOut (BswM_Cfg_MRPType_ten* dataMRPType_pen, uint16 * idChannel_pu16,
*                    uint16 * idxMRPChnl_pu16, uint16* dataReqMode_pu16)
*Description    : This function retrieves information about the queued mode request from the interrupt queue.
*Parameters(in) : None
*Parameters(out):
*   dataMRPType_pen - Pointer to the type or source of the mode request (CamSMIndication, ComMIndication, etc)
*   idChannel_pu16 -  Pointer to the ChannelId of the respective mode requester.
*   idxMRPChnl_pu16 - Pointer to the index (in the PBstruct and RAM buffer) occupied by this channel.
*   dataReqMode_pu16 - Pointer to the mode currently requested
*Return value   : Std_ReturnType
*                 E_OK : The queue is not empty and a value is returned.
*                 E_NOT_OK : The queue is empty, no values are returned.
************************************************************************************************/

FUNC(Std_ReturnType, BSWM_CODE) BswM_Prv_IntrptQueueOut
(
    P2VAR(BswM_Cfg_MRPType_ten, AUTOMATIC, BSWM_VAR) dataMRPType_pen,
    P2VAR(uint16, AUTOMATIC, BSWM_VAR) idChannel_pu16,
    P2VAR(uint16, AUTOMATIC, BSWM_VAR) idxMRPChnl_pu16,
    P2VAR(uint16, AUTOMATIC, BSWM_VAR) dataReqMode_pu16
)
{
    /* Variable declaration*/
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;
    VAR(uint8, AUTOMATIC) headIndex_u8= 0;

    if(0 == BswM_Prv_IntrptQueueInfo_st.dataSize_u8)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        headIndex_u8 = BswM_Prv_IntrptQueueInfo_st.idxHead_u8;

        /* Dequeue the information stored at head index*/
        *dataMRPType_pen = BswM_Prv_IntrptQueue_ast[headIndex_u8].dataMRPType_en;
        *idChannel_pu16 = BswM_Prv_IntrptQueue_ast[headIndex_u8].idChannel_u16;
        *idxMRPChnl_pu16 = BswM_Prv_IntrptQueue_ast[headIndex_u8].idxMRPChnl_u16;
        *dataReqMode_pu16 = BswM_Prv_IntrptQueue_ast[headIndex_u8].dataReqMode_u16;

        /*Clear the values at head index*/
        BswM_Prv_IntrptQueue_ast[headIndex_u8].dataMRPType_en = BSWM_MRP_DEFAULT;
        BswM_Prv_IntrptQueue_ast[headIndex_u8].idChannel_u16 = 0xFF;
        BswM_Prv_IntrptQueue_ast[headIndex_u8].idxMRPChnl_u16 = 0xFF;
        BswM_Prv_IntrptQueue_ast[headIndex_u8].dataReqMode_u16 = 0xFF;

        /* Increment the head index and decrement the size of the queue*/
        BswM_Prv_IntrptQueueInfo_st.idxHead_u8++;
        BswM_Prv_IntrptQueueInfo_st.dataSize_u8--;

        /*Is the queue empty?*/
        if(0 == BswM_Prv_IntrptQueueInfo_st.dataSize_u8)
        {
            /* Reset head and tail indexes of the queue*/
            BswM_Prv_IntrptQueueInfo_st.idxHead_u8 = 0;
            BswM_Prv_IntrptQueueInfo_st.idxTail_u8 = 0;
            BswM_Prv_isReqstDelayed_b = FALSE;
        }
        else
        {
            /* Has the final index of the queue been reached?*/
            if (BSWM_RB_INTRPTQUEUE_MAXSIZE == BswM_Prv_IntrptQueueInfo_st.idxHead_u8)
            {
                /*Reset the head index to indicate the first index of the queue*/
                BswM_Prv_IntrptQueueInfo_st.idxHead_u8 = 0;
            }

        }
    }
    return retVal;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/

