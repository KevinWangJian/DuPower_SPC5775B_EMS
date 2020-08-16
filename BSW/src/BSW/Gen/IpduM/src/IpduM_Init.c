
#include "IpduM.h"
#include "IpduM_Priv.h"
#include "ComStack_Types.h"
#if (!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != IPDUM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != IPDUM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/* Begin of  variable section */
#define IPDUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "IpduM_MemMap.h"

VAR(IpduM_TimerType, IPDUM_VAR) IpduM_SwTimer;
VAR(IpduM_StatusType,IPDUM_VAR) IpduM_Uninit_Flag;

/* End of variable section */
#define IPDUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "IpduM_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : IpduM_Init
 Syntax           : void IpduM_Init(IpduM_ConfigType config)
 Description      : Initializes the I-PDU Multiplexer.
 Parameter        : IpduM_ConfigType config : Pointer to the selected configuration set
 Return value     : None.
 ***************************************************************************************************/

FUNC(void, IPDUM_CODE) IpduM_Init(
                   P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_APPL_DATA) config
                                 )
{
    /* pointer to SW Timer */
    P2VAR(IpduM_TimerType, AUTOMATIC, IPDUM_APPL_DATA)    TimerPtr;

    /*The variables will only be used if the IpduM TxPathways are configured*/
#if defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)

        /* Number of Tx MPDUS */
        VAR(uint8_least, AUTOMATIC) NumTxMpdus;
        /* Index to MPdu */
        VAR(uint8_least, AUTOMATIC) MpduIdx;

        /* pointer to Tx RAM data */
        P2VAR(IpduM_TxRamType, AUTOMATIC, IPDUM_APPL_DATA)    TxRamPtr;

#endif

    /**** End Of Declarations ****/

    /* Start: Det */
    /* Return Type: void */
    IPDUM_REPORT_ERROR((config != NULL_PTR), IPDUMServiceId_Init, IPDUM_E_PARAM_POINTER)
    /* End: Det */

    TimerPtr = &IpduM_SwTimer;

    (void)config;

    /* Initialize the free running timer */
    TimerPtr->SwFRTimer = 0;

#if defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)


        NumTxMpdus = (uint8_least)IPDUM_NUM_TX_MPDUS;

        for(MpduIdx = 0; MpduIdx < NumTxMpdus; MpduIdx++)
        {
            TxRamPtr = &IpduM_TxRamData[MpduIdx];
            TxRamPtr->StaticPartPduId = IPDUM_INVALID_INDEX;
            TxRamPtr->DynPartPduId = IPDUM_INVALID_INDEX;
            TxRamPtr->PrevDynPartPduId = IpduM_TxMPduTable[MpduIdx].InitialDynPduId;
            TxRamPtr->TxState = IPDUM_TX_READY;
        }
        /* CSCRM00379312*/
        /* calling the init value function in the ipdum_pbcfg.c file to initialise the buffers*/

        IpduM_InitValues();

#endif

#if defined (IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF)
        {
            /*Index to Container Rx Pdu*/
            VAR(uint16, AUTOMATIC) CrRxPduIdx;

            /* Pointer to Container(Cr) Rx table*/
            P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContainerPduConstPtr_pst;

            /*Pointer to Rx ContainerPduDynamicType table*/
            P2VAR(IpduM_RxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_DATA) RxContainerPduRAMPtr_pst;

            for (CrRxPduIdx = 0 ; CrRxPduIdx < IPDUM_NUM_CONTAINER_RX_PDUS ; CrRxPduIdx++)
            {
                /*Initailise the pointer with Rx container Pdu RAM variables */
                RxContainerPduRAMPtr_pst = &IpduM_RxContainerPduDynData[CrRxPduIdx];

                /*Initialise the pointer with Rx Container Pdu table*/
                RxContainerPduConstPtr_pst = &IpduM_RxContainerPdu[CrRxPduIdx];

                /*Initialise the read pointer to the base address of BufferPtr*/
                RxContainerPduRAMPtr_pst->ReadPtr = RxContainerPduConstPtr_pst->BufferPtr;

                /*Initialise the write pointer to the base address of BufferPtr*/
                RxContainerPduRAMPtr_pst->WritePtr = RxContainerPduConstPtr_pst->BufferPtr;

                /*Initialise the current queue Size to 0*/
                RxContainerPduRAMPtr_pst->CurrentQueueInstance = 0;

                /* Initialise the instance Pdu length to zero */
                IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->WritePtr,RxContainerPduConstPtr_pst->RxContainerPduLen) = 0;

            }
        }

#endif

#if defined (IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)
        {
            /*Index to Container Rx Pdu*/
            VAR(uint16, AUTOMATIC) CntnrTxPduIdx;

            /* Pointer to Container(Cr) Tx table*/
            P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxContainerConstPtr_pst;

            /*Pointer to Tx ContainerPduDynamicType table*/
            P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_DATA) TxContainerRAMDynptr_pst;
            for(CntnrTxPduIdx = 0 ; CntnrTxPduIdx < IPDUM_NUM_CONTAINER_TX_PDUS ; CntnrTxPduIdx++)
            {
                /*Initailise the pointer with Tx container Pdu RAM variables */
                TxContainerRAMDynptr_pst = &IpduM_TxContainerPduDynData[CntnrTxPduIdx];
                /*Initialise the pointer with Tx Container Pdu table*/
                TxContainerConstPtr_pst = &IpduM_TxContainerPdu[CntnrTxPduIdx];
                /*Initialise the read,Write and TxConfPtr to the base address of BufferPtr*/
                TxContainerRAMDynptr_pst->WritePtr = TxContainerConstPtr_pst->BufferPtr;
                TxContainerRAMDynptr_pst->ReadPtr = TxContainerConstPtr_pst->BufferPtr;
                TxContainerRAMDynptr_pst->TxConfPtr = NULL_PTR;
                IPDUM_CUR_CNTNR_SDU_LEN(TxContainerRAMDynptr_pst->WritePtr,TxContainerConstPtr_pst->TxContainerPduLen) = 0;
                TxContainerRAMDynptr_pst->CurrentQueueInstance = 0;
                TxContainerRAMDynptr_pst->TxConfRAMTicks = 0;
                TxContainerRAMDynptr_pst->TxSendTimeOutTicks = 0xFFFFu;
                TxContainerRAMDynptr_pst->RetransmissionRequired = FALSE;
            }
        }
#endif

    /* Reset the UNINIT flag */
    IpduM_Uninit_Flag = IPDUM_INIT;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

