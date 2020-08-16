

/*---------------------------------------------------------------------------------------*/
/*- Include files																		-*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_J1939Nm.h"
#include "BswM_Prv.h"

#ifdef BSWM_J1939NM_ENABLED
#if ( BSWM_J1939NM_ENABLED == TRUE )

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
* Function name : BswM_J1939Nm_StateChangeNotification( NetworkHandleType Network, uint8 Node, Nm_StateType NmState )
* Description   : The J1939Nm provides a state indication with this
* Parameters(in): Network: Identification of the J1939 channel
*                 Node: Identification of the J1939 node
*                 NmState:Current (new) state of the J1939 node
*
* Return value  : None
* Remarks       : The corresponding configuration container for this API is BswMJ1939NmIndication
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_J1939Nm_StateChangeNotification
(
        VAR(NetworkHandleType, AUTOMATIC) Network,
        VAR(uint8, AUTOMATIC) Node,
        VAR(Nm_StateType, AUTOMATIC) NmState
)
{
#if ( BSWM_NO_OF_J1939NM_CHANNELS > 0 )

    /* Local variables defined for this function. */
    VAR(uint16, AUTOMATIC) idxJ1939NmNodeChn_u16 = 0;
    VAR(boolean, AUTOMATIC) flgJ1939NmNodeChnIdVld_b = FALSE;
    VAR(BswM_Cfg_MRPJ1939NmType_tst, AUTOMATIC) dataJ1939NmMRP_st;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_J1939NM, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed Network Channel-Id is valid and get corresponding index */
        flgJ1939NmNodeChnIdVld_b = BswM_Prv_GetJ1939NmNodeChnIndex_b(Network, Node, &idxJ1939NmNodeChn_u16);

            /* Proceed if it valid index */
            if (FALSE != flgJ1939NmNodeChnIdVld_b)
            {

                /* Check if no other request is in progress */
                if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_J1939_NM_IND, idxJ1939NmNodeChn_u16, idxJ1939NmNodeChn_u16, (uint16)NmState))
                {
                    /* Process any requests that were delayed before this request */
                    if (FALSE != BswM_Prv_isReqstDelayed_b)
                    {
                        BswM_Prv_ProcessDelayedReqst();
                    }

                    /* J1939Nm Request MRP RAM Buffer updated at required index */
                    BswM_Cfg_J1939NmStateChangeNotificationInfo_ast[idxJ1939NmNodeChn_u16].isValidModePresent_b = TRUE;
                    BswM_Cfg_J1939NmStateChangeNotificationInfo_ast[idxJ1939NmNodeChn_u16].dataMode_en = NmState;

                    dataJ1939NmMRP_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Nm_ast[idxJ1939NmNodeChn_u16];

                    /* Rules of the request will be stored if it is Deferred/ evaluated if it is Immediate */
                    BswM_Prv_RuleEval(dataJ1939NmMRP_st.dataReqProcessing_en, BSWM_MRP_J1939_NM_IND, idxJ1939NmNodeChn_u16, dataJ1939NmMRP_st.adrRulesRef_pu16,dataJ1939NmMRP_st.nrAssociatedRules_u16);

                    /* Check Whether deferred request processing was delayed */
                    if( FALSE != BswM_Prv_flgDelayDeferredReqst_b )
                    {
                        /* Call the deferred request processing function */
                        BswM_Prv_ProcessDeferredReqst();
                    }

                    /* Reset request in progress flag */
                    BswM_Prv_flgNewReqstProgress_b = FALSE;

                }
            }
        }

#if ( BSWM_DEBUG == TRUE )
    BswM_Prv_InterruptHandler(BSWM_API_ID_J1939NM);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /* To avoid compiler warnings if no J1939Nm channel is configured */
        (void)Network;
        (void)Node;
        (void)NmState;
#endif  /* ( BSWM_NO_OF_J1939NM_CHANNELS > 0 ) */

     return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_J1939NM_ENABLED == TRUE ) */
#endif /* BSWM_J1939NM_ENABLED */

/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
