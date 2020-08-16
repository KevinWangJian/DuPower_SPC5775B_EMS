

/*********************************************************************************************************************
* Preprocessor includes
*********************************************************************************************************************/
#include "Com_Priv.h"

/*********************************************************************************************************************
* Global functions (declared in header files )
*********************************************************************************************************************/
#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
static INLINE FUNC(Std_ReturnType, COM_CODE) Com_ReadSigGwReceiveQueue(PduIdType*             ComRxPduId,
                                                                       Com_RxGwQueueIndexType l_Com_RxGwQueueWrite_ux);


/*********************************************************************************************************************
 Function name    : Com_MainFunctionRouteSignals
 Syntax           : void Com_MainFunctionRouteSignals(void)
 Description      : Service that Calls the signal gateway part of the AUTOSAR COM module
                    to forward received signals to be routed.
 Parameter        : void
 Return value     : None
 *********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_MainFunctionRouteSignals( void )
{
    /* Start: Det */
    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_MainFunctionRouteSignals, COM_E_UNINIT)
    /* End: Det */

    if(Com_Uninit_Flag == COM_INIT)
    {
        Com_RxGwQueueIndexType  l_Com_RxGwQueueWrite_ux;
        Com_RxGwQueuePtrType    RxGwQueuePtr_l;

        RxGwQueuePtr_l = COM_GET_RXGWQUEUE_S;

        /* Take a local copy of theWrite pointer
         * Only the receptions which till this step are processed in the current call of Com_MainfunctionRouteSignals()*/
        l_Com_RxGwQueueWrite_ux = RxGwQueuePtr_l->Com_RxGwQueueWrite_ux;
        {
            PduIdType l_Ipduid;
            uint8 l_IpduSyncCounter;

            /* Run through the loop for all the new elements in the queue, and process each element in the queue */
            /* Read the queue here; The queue read pointer is moved to the next location in the below operation
             * Read is to be performed carefully, if called two time the read pointer is moved */
            while (Com_ReadSigGwReceiveQueue(&l_Ipduid,l_Com_RxGwQueueWrite_ux) == (Std_ReturnType)E_OK)
            {
                /* Start the counter with this value, as this the maximum times the Ipdu will be processed for
                 * synchronisation of Signals within Ipdu */
                l_IpduSyncCounter = 0;
                /* Report an error if the value added into the queue is not a Gw Pdu id */
                COM_REPORT_ERROR((l_Ipduid >= COM_GET_NUM_GWSRC_IPDUS), COMServiceId_MainFunctionRouteSignals, COM_E_PARAM)
                /* This below part of the code(do-while) is needed for Signal level data synchronisation within one Rx Ipdu
                 * Scenario:  If while processing this signal in the queue There was an update on the rx side,
                 * it is possible that one signal can have old value and other signals can have new value.
                 * Method : During the complete Gw routing operation if a new update on the Ipdu was recieved,
                 * then all the signals are updated to new values  */
                do
                {
                    Com_RxIpduConstPtrType RxIPduConstPtr;

                    SchM_Enter_Com_RxSigGwQueueProtArea();
                    /* Here the Ipdu entry is popped out of the queue, this flag is reset to capture the changes in
                     * Com_RxIndication. Set the Ipdu processed flag to TRUE, this is to capture any further updates
                     * during the processing */
                    Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,COM_GET_RXPDURAM_S(l_Ipduid).RxFlags,COM_FALSE);
                    SchM_Exit_Com_RxSigGwQueueProtArea();

                    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(l_Ipduid);

#ifdef COM_SIGNALGATEWAY
                    if(RxIPduConstPtr->numOfGwSrcSignals > 0)
                    {
                        Com_GwMapSigConfPtrType          ComGwMapSigConfPtr;
                        Com_GwMapSigIdConfPtrType        ComGwMapSigIdConfPtr;
                        Com_SignalIdType                 l_TxGwDestId;
                        VAR(Com_SignalIdType, AUTOMATIC) SigId_u32;
                        VAR(uint16_least, AUTOMATIC)     limit_ui;
                        VAR(uint16_least, AUTOMATIC)     loopIndex_ui;
                        Com_RxSigRamPtrType              RxSigRamPtr;
                        Com_RxSigConstPtrType            RxSigConstPtr;

                        limit_ui      = (uint32)RxIPduConstPtr->RxSigId_Index + (uint32)RxIPduConstPtr->numOfGwSrcSignals;
                        RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);

                        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

                        for(SigId_u32 = RxIPduConstPtr->RxSigId_Index; SigId_u32 < limit_ui; SigId_u32++)
                        {
                            /* The processing of the signals within one Rx Ipdu could be done with an earlier signal entry in the queue;
                             * This is to ensure that only new data updates are processed and not missed for other signals in the Ipdu
                             * This will also ensure Update bit handling for an Rx signal with set update bit
                             */
                            /* Process only the 1. Gw signals fill bit set  */
                            /* Report an error if the Signal to be routed is not a Gw signal id */
                            COM_REPORT_ERROR((SigId_u32 >= COM_GET_NUM_GWSRC_SIGNALS), COMServiceId_MainFunctionRouteSignals, COM_E_PARAM)

                            if(Com_GetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields) != COM_FALSE)
                            {
                                ComGwMapSigConfPtr = COM_GET_GWSIG_CONSTDATA(SigId_u32);
                                ComGwMapSigIdConfPtr = COM_GET_GWSIGIDMAP_CONSTDATA(ComGwMapSigConfPtr->indexGwMapSigDestIdArray);

                                /* Loop for 1:N signal gatewaying, this packs the signal data into all the configured destination Ipdu buffer */
                                for(loopIndex_ui = 0; loopIndex_ui < ComGwMapSigConfPtr->destCount; loopIndex_ui++)
                                {
                                    l_TxGwDestId = ComGwMapSigIdConfPtr->GwMap_DestId;

                                    /* Report an error if the Signal to be routed is not a Gw signal id */
                                    COM_REPORT_ERROR((l_TxGwDestId == COM_GET_NUM_TX_SIGNALS), COMServiceId_MainFunctionRouteSignals, COM_E_PARAM)

                                    Com_PackRxSignalGwBufferData(RxSigConstPtr,l_TxGwDestId);

                                    ComGwMapSigIdConfPtr++;
                                }
                                /* Set the Signal data update flag to FALSE, After processing this Rx signal */
                                Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields,COM_FALSE);
                            }
                            RxSigRamPtr++;
                            RxSigConstPtr++;
                        }
                    }
#endif /* #ifdef COM_SIGNALGATEWAY */
#if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) && defined (COM_TX_SIGNALGROUP))
                    if(RxIPduConstPtr->numOfGwSrcSignalGrps > 0)
                    {
                        Com_RxSigGrpConstPtrType RxSigGrpConstPtr;
                        Com_RxSigGrpRamPtrType RxSigGrpRamPtr;
                        Com_RxGrpSigConstPtrType RxGrpSigConstPtr;
                        VAR(uint16_least, AUTOMATIC)    Idx_GrpSig_ui;
                        VAR(uint16_least, AUTOMATIC) limit_grpsig_ui;
                        Com_GwMapGrpSigConfPtrType GwMapGrpSigConfigPtr;
                        Com_GwMapGrpSigIdConfPtrType GwMapGrpSigIdConfigPtr;
                        Com_TxIntGrpSignalIdType l_TxGwDestId;
                        VAR(Com_TxIntGrpSignalIdType, AUTOMATIC) SigId_u32;
                        VAR(uint16_least, AUTOMATIC) limit_ui;
                        VAR(uint16_least, AUTOMATIC) loopIndex_ui;

                        RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);

                        RxSigGrpRamPtr =  &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);
                        limit_ui       = (uint32)RxIPduConstPtr->FirstRxSigGrp_Index + (uint32)RxIPduConstPtr->numOfGwSrcSignalGrps;

                        for(SigId_u32 = RxIPduConstPtr->FirstRxSigGrp_Index; SigId_u32 < limit_ui; SigId_u32++)
                        {
                            /* The processing of the signal groups within one Rx Ipdu could be done with an earlier signal entry in the queue;
                             * This is to ensure that only new data updates are processed and not missed for other signal groups in the Ipdu
                             * This will also ensure Update bit handling for an Rx signal group with set update bit
                             */
                            /* Process only the 1. Gw signal group fill bit set  */
                            /* Report an error if the GrpSignal to be routed is not a Gw signal id */
                            if(Com_GetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr ->rxSigGrpRAMFields) != COM_FALSE)
                            {

                                RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

                                limit_grpsig_ui = RxSigGrpConstPtr->FirstGrpSig_Index + RxSigGrpConstPtr->numOfGwSrcGrpSignals;
                                for(Idx_GrpSig_ui = (uint32)RxSigGrpConstPtr->FirstGrpSig_Index; Idx_GrpSig_ui < limit_grpsig_ui;Idx_GrpSig_ui++)
                                {
                                    /* Report the error, if the Group signal id is not a Gw signal id  */
                                    COM_REPORT_ERROR(((Idx_GrpSig_ui < COM_GET_NUM_GRPSIG_NOGW) || (Idx_GrpSig_ui >= (COM_GET_NUM_GRPSIG_NOGW+COM_GET_NUM_GWSRC_GRPSIGNALS)))
                                            , COMServiceId_MainFunctionRouteSignals, COM_E_PARAM)

                                    GwMapGrpSigConfigPtr = COM_GET_GWGRPSIG_CONSTDATA((Idx_GrpSig_ui - COM_GET_NUM_GRPSIG_NOGW));
                                    GwMapGrpSigIdConfigPtr = COM_GET_GWGRPSIGIDMAP_CONSTDATA(GwMapGrpSigConfigPtr->indexGwMapGrpSigDestIdArray);

                                    for(loopIndex_ui = 0; loopIndex_ui < GwMapGrpSigConfigPtr->destCount; loopIndex_ui++)
                                    {
                                        l_TxGwDestId = GwMapGrpSigIdConfigPtr->GwMap_DestGrpSigId;
                                        /* Report an error if the Signal to be routed is not a Gw signal id */
                                        COM_REPORT_ERROR((l_TxGwDestId == COM_GET_NUM_TX_GRPSIGNALS), COMServiceId_MainFunctionRouteSignals, COM_E_PARAM)
                                        /* Refer to Com_Cfg_SchM file; this is a multi-core lock */
                                        SchM_Enter_Com_RxSigGwMcLockProtArea();
                                        Com_PackRxSignalGrpGwBufferData(RxGrpSigConstPtr,l_TxGwDestId);
                                        SchM_Exit_Com_RxSigGwMcLockProtArea();
                                        GwMapGrpSigIdConfigPtr++;
                                    }
                                    RxGrpSigConstPtr++;
                                }
                                /* Set the Signal data update flag to TRUE, this is to capture any further updates during the processing */
                                Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr ->rxSigGrpRAMFields,COM_FALSE);
                            }
                            RxSigGrpConstPtr++;
                            RxSigGrpRamPtr++;
                        }
                    }
#endif /* #if defined COM_SIGNALGROUPGATEWAY && (defined (COM_RX_SIGNALGROUP) || defined (COM_TX_SIGNALGROUP)) */

                    /* This part will control the loop to run 2 times after the main processing in case there was a new Reception of Ipdu */
                    if(Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,COM_GET_RXPDURAM_S(l_Ipduid).RxFlags) == COM_TRUE)
                    {
                        l_IpduSyncCounter = (l_IpduSyncCounter+1) % (COM_MAXIMUM_GWSYNC_REPITIONS+1);
                    }
                    else
                    {
                        l_IpduSyncCounter = 0;
                    }
                }while (l_IpduSyncCounter != 0);
            }
        }
        {
            Com_TxIpduConstPtrType       TxIPduConstPtr; /* Local pointer to the Tx ipdu static configuration */
            Com_TxIpduRamPtrType         TxIpduRamPtr;   /* Local pointer to the Tx ipdu RAM structure        */
            VAR(uint16_least, AUTOMATIC) Index_ui;

            TxIpduRamPtr   = &COM_GET_TXPDURAM_S(0);

            TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(0);

            for(Index_ui = 0; Index_ui < COM_GET_NUM_TX_IPDU; Index_ui++)
            {
                /* Check if IPdu group is started */
                /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
                 * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
                 * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
                 * Hence the warning is suppressed. */
                if(COM_CheckTxIPduStatus(Index_ui))
                {
                    if(Com_GetValue(TXIPDU,_ISGWPDU,TxIPduConstPtr->txIPduFields) != COM_FALSE)
                    {
#if defined (COM_SIGNALGROUPGATEWAY) && defined (COM_TX_SIGNALGROUP)
                        Com_TxSigGrpRamPtrType       TxSigGrpRamPtr;   /* Local pointer to Tx SignalGroup status structure     */
                        VAR(uint16_least, AUTOMATIC) Idx_SigGrp_ui;
                        VAR(uint16_least, AUTOMATIC) limit_siggrp_ui;

                        limit_siggrp_ui  = (uint32)TxIPduConstPtr->FirstTxSigGrp_Index +
                                           (uint32)TxIPduConstPtr->No_Of_SigGrp_Ref;

                        TxSigGrpRamPtr   = &COM_GET_TXSIGGRPFLAG(TxIPduConstPtr->FirstTxSigGrp_Index);

                        for( Idx_SigGrp_ui = (uint32)TxIPduConstPtr->FirstTxSigGrp_Index;
                             Idx_SigGrp_ui < limit_siggrp_ui;
                             Idx_SigGrp_ui++)
                        {
                            /* TxSigGrpRamPtr ->txSigGrpRAMFields.IsGwUpdated = COM_TRUE */
                            if(Com_GetRamValue(TXSIGGRP,_ISGWUPDTD,TxSigGrpRamPtr ->txSigGrpRAMFields) == COM_TRUE)
                            {
                                /* TxSigGrpRamPtr ->txSigGrpRAMFields.IsGwUpdated = COM_FALSE */
                                Com_SetRamValue(TXSIGGRP,_ISGWUPDTD,TxSigGrpRamPtr ->txSigGrpRAMFields,COM_FALSE);

                                /* 1. Set the UpdateBit
                                 * 2. Update TxIPdu buffer with the latest Tx-GroupSignal data
                                 * 3. Evaluate TMC of GroupSignals
                                 * 4. Evaluate TMS of TxIPdu
                                 * Return value is based on IPduGroup status that can be ignored here,
                                 * as it is checked later in Com_MainFunctionRouteSignals()
                                 */
                                (void)Com_InternalSendSignalGroup( (Com_SignalGroupIdType)Idx_SigGrp_ui );
                            }
                            TxSigGrpRamPtr++;
                        }
#endif /* #if defined (COM_SIGNALGROUPGATEWAY) && defined (COM_TX_SIGNALGROUP) */

                        /* Process Tx-IPdu transmission */
                        /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status.
                         * Evaluation(or no evaluation) of the 2nd or 3rd operands does not impact the system behaviour,
                         * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
                         * Hence the warning is suppressed. */
                        if (((Com_GetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags) != COM_FALSE) &&
                             (Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) <= COM_TXMODE_MIXED))
#ifdef COM_TxFilters
                            || (Com_GetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags) != COM_FALSE)
#endif
                            )
                        {
                            /* All unused flags are reset here */
                            Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                            /* For the direct part of the Mixed TM, Signal Transfer property is set directly from
                             * _ISGWTRIGGRD flag. In all the other cases, it is ignored. */
                            sendIpduFlag_u16.sigTransProp =
                             COM_BOOL_TO_UNSIGNED(Com_GetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags));

                            /* Reset the global flag that stores if any triggered Signal/SignalGroup is updated */
                            Com_SetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

#ifdef COM_TxFilters
                            sendIpduFlag_u16.isModeChangd =
                             COM_BOOL_TO_UNSIGNED(Com_GetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags));

                            /* Reset the global flag that stores the IPdu TMS Change after the last transmission */
                            Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#endif

                            /* this flag will be set, as call happens from Com_MainFunctionRouteSignals */
                            sendIpduFlag_u16.isEventTrig      = COM_SET;

                            sendIpduFlag_u16.isGwIpduSend     = COM_SET;

#ifdef COM_TxIPduTimeOut
                            /* Set the timeout flag if the signal contributes for Timeout and
                             * the transmission mode is MIXED/DIRECT.
                             * For PERIODIC TM, it is handled from Com_MainFunctionTx().
                             */
                            if (Com_GetRamValue(TXIPDU,_ISTOENABLED,TxIpduRamPtr->Com_TxFlags)== COM_TRUE)
                            {
                                sendIpduFlag_u16.isTimeoutReq = COM_SET;
                                /* This flag is reset after starting Timeout monitoring*/
                                Com_SetRamValue(TXIPDU,_ISTOENABLED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                            }
#endif

                            Com_SendIpdu((PduIdType)Index_ui, sendIpduFlag_u16);
                        }
                    }
                } /* end of IPdu group started check */

                TxIPduConstPtr++ ;
                TxIpduRamPtr++;
            } /* end of for loop */
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_WriteSigGwReceiveQueue
 Syntax           : Std_ReturnType Com_WriteSigGwReceiveQueue(ComRxPduId)
 Description      : this function writes into the Rx Gw queue and updated the pointers accordingly
 To Be considered before using this function
 --------------------------------------------

 Parameter        : ComRxPduId
 Return value     : Std_ReturnType
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(Std_ReturnType, COM_CODE) Com_WriteSigGwReceiveQueue( PduIdType ComRxPduId)
{
    Com_RxGwQueuePtrType l_RxGwQueuePtr_struc;

    l_RxGwQueuePtr_struc = COM_GET_RXGWQUEUE_S;
    /* The write operation need not be conditional,
     * 1. As the length of the queue is fixed and queue need not be updated for any new updates on the signal */
    l_RxGwQueuePtr_struc->RxGwQueuePtr[l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux] = ComRxPduId;
    /* Perform a modulo to get to the next available location */
    l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux = ( Com_RxGwQueueIndexType )
                                                  ( ( l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux + 1 ) %
                                                    ( COM_GET_NUM_GWSRC_IPDUS + 1u ) );

    /* If the buffer is full and there is a request to write into the queue, It is taken care that no new request are recieved after that*/
    COM_REPORT_ERROR4((((l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux) % (COM_GET_NUM_GWSRC_IPDUS+1u)) == l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux)
                , COMServiceId_MainFunctionRouteSignals, COM_E_PARAM)
    return(E_OK);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_ReadSigGwReceiveQueue
 Syntax           : Std_ReturnType Com_ReadSigGwReceiveQueue( PduIdType*             ComRxPduId,
                                                              Com_RxGwQueueIndexType l_Com_RxGwQueueWrite_ux)
 Description      : this function reads from the Rx Gw queue and updated the pointers accordingly
 --------------------------------------------

 Parameter        : (IN/OUT)ComRxPduId
                    (IN)    l_Com_RxGwQueueWrite_ux
 Return value     : Std_ReturnType
 ***************************************************************************************************/
static INLINE FUNC(Std_ReturnType, COM_CODE) Com_ReadSigGwReceiveQueue( PduIdType*             ComRxPduId,
                                                                        Com_RxGwQueueIndexType l_Com_RxGwQueueWrite_ux)
{
    Com_RxGwQueuePtrType l_RxGwQueuePtr_struc;
    Std_ReturnType       retVal_uo;

    l_RxGwQueuePtr_struc = COM_GET_RXGWQUEUE_S;
    retVal_uo            = E_NOT_OK;

    /* This operation is performed before every read to confirm if the data is present in the queue */
    if(l_Com_RxGwQueueWrite_ux != l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux)
    {
        /* The Read operation need not be conditional,
         * 1. As the length of the queue is fixed and queue need not be updated for any new updates on the signal */
        *ComRxPduId = l_RxGwQueuePtr_struc->RxGwQueuePtr[l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux];
        /* Perform a modulo to get to the next available location */
        l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux = ( Com_RxGwQueueIndexType )
                                                     ( ( l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux + 1 ) %
                                                       ( COM_GET_NUM_GWSRC_IPDUS + 1u ) );
        retVal_uo = E_OK;
    }

    return(retVal_uo);
}

#endif /* #if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY) */

