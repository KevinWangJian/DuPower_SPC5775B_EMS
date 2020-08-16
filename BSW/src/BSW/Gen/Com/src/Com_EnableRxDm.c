

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
static INLINE FUNC (void,COM_CODE) Com_EnableRxDeadlineMonitoring_Inline(VAR(Com_IpduIdType, AUTOMATIC) IpduId,    VAR(boolean, AUTOMATIC) Initialize);

/***************************************************************************************************
 Function name    : Com_ReceptionDMControl
 Syntax           : void Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector)
 Description      : Service Enables deadline monitoring for the I-PDU groups within the given I-PDU group.
 Parameter        : ipduGroupVector -> contains the requested deadline monitoring state (disabled = 0/ enabled = 1) for all I-PDU groups.
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ReceptionDMControl(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector)
{
    /* Local pointer which holds the address of the array which stores the ipdu id */
    P2CONST(Com_IpduIdType, AUTOMATIC, COM_APPL_CONST) IPduRefPtr;
    /* Local pointer to hold the address of Ipdu group structure                   */
    Com_IPduGrpConstPtrType     IPduGrpConstPtr;
    /* Local pointer to hold the address of the Rx Ipdu status structure           */
    Com_RxIpduRamPtrType        RxIPduRamPtr;
    VAR(uint16, AUTOMATIC)      Index_u16;
    /* Variable to store the no. of ipdus belongs to a particular ipdu group       */
    VAR(uint16,AUTOMATIC)       NoofPdus_u16;
    VAR(uint16,AUTOMATIC)       ByteNo_u16;
    VAR(Com_IpduGroupIdType, AUTOMATIC) IpduGrpId_u16; /* To store the Ipdu Group Id      */
    VAR(uint8, AUTOMATIC)       ByteVal_u8;
    VAR(uint8,AUTOMATIC)        BitOffset_u8;
    VAR(boolean, AUTOMATIC)     PduGrp_Status_b;       /* Stores the status of Ipdu Group */

    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_ReceptionDMControl, COM_E_UNINIT)

    /* START: Clear Unused BitFields
     * If the Group vector is filled with non-zero in unconfigured bitfields,
     * it might cause an exception in the software. */
    ByteNo_u16 = ( uint16 )( COM_GET_NUM_TOTAL_IPDU_GRP / 8u );
    if ( ByteNo_u16 < COM_NUM_ARR_IPDUGRPVECT )
    {
        ipduGroupVector[ ByteNo_u16 ] &= ( ( uint8 )( 0xFF ) >> ( 8u - ( COM_GET_NUM_TOTAL_IPDU_GRP % 8u ) ) );
        ByteNo_u16++;

        while ( ByteNo_u16 < COM_NUM_ARR_IPDUGRPVECT )
        {
            ipduGroupVector[ ByteNo_u16 ] = ( uint8 )0;
            ByteNo_u16++;
        }
    }
    /* END: Clear Unused BitFields */

    if (Com_Uninit_Flag == COM_INIT)
    {
        for (Index_u16 = 0; Index_u16 < COM_NUM_ARR_IPDUGRPVECT; Index_u16++)
        {
            if (Com_IpduGrpVector_DM[Index_u16] != ipduGroupVector[Index_u16] )
            {
                /* Perform an XOR to find the Ipdu Groups which have changed the states */

                ByteVal_u8 = (uint8)((Com_IpduGrpVector_DM[Index_u16]) ^ (ipduGroupVector[Index_u16]));
                BitOffset_u8 = 0;

                /*If there are some Ipdu groups which have changed the status*/
                while(ByteVal_u8 > 0)
                {
                    /*Check for the status of the changed Ipdu groups and perform actions accordingly*/
                    /* Check if any of the IPdu Group is changed by performing right bit shift*/
                    if ( COM_RESET != ( ByteVal_u8 & ((uint8)1) ) )
                    {
                        /*Get the Ipdu group Id if the status is changed*/
                        IpduGrpId_u16 = (8 * Index_u16)+ BitOffset_u8 ;

                        /* Convert external HandleId to internal HandleId
                           IMP : ipduGroupVector will be set/reset based on the external ID.
                           It is required to convert the ID only when accessing the tables
                           For pre-compile , conversion is not required. Access Macro will return the same ID, which is passed to it */


                        IpduGrpId_u16 = COM_GET_IPDUGRP_ID(IpduGrpId_u16);

                        /* Get the latest status of the IPdu group */
                        PduGrp_Status_b = (((ipduGroupVector[Index_u16] >> BitOffset_u8) & ((uint8)(1))) != 0u);

                        IPduGrpConstPtr = COM_GET_IPDUGRP_CONSTDATA(IpduGrpId_u16);

                        IPduRefPtr = COM_GET_IPDUGRP_IPDUREF_CONSTDATA(IPduGrpConstPtr->FirstIpdu_Index);


                        NoofPdus_u16 = IPduGrpConstPtr ->NoOfPdus;

                        while(NoofPdus_u16 > 0 )
                        {
                            /* If RX IPdu */
                            if ((*IPduRefPtr) < COM_GET_NUM_RX_IPDU)
                            {
                                /*Check if the DM state of the Ipdu Group is changed and if it is an RX IPdu*/
                                if (PduGrp_Status_b)
                                {
                                    COM_GET_IPDUCOUNTER_DM(*IPduRefPtr) ++;
                                }

                                else
                                {
                                    COM_GET_IPDUCOUNTER_DM(*IPduRefPtr) --;
                                }
                            }
                            IPduRefPtr++;
                            NoofPdus_u16--;

                        }/* while(NoofPdus_u16 > 0 ) */

                    }/* if (ByteVal_u8 & ((uint8)1))*/
                    BitOffset_u8 ++;
                    ByteVal_u8 = ByteVal_u8 >> 1;
                }/* while(ByteVal_u8 > 0) */

                /* update the status of the IPdu group */
                Com_IpduGrpVector_DM[Index_u16] = ipduGroupVector[Index_u16] ;
            } /* if (Com_IpduGrpVector_DM[Index_u16] != ipduGroupVector[Index_u16] ) */

        } /* End of For loop */

        RxIPduRamPtr   = &COM_GET_RXPDURAM_S(0);
        for (Index_u16 = 0; Index_u16 < COM_GET_NUM_RX_IPDU; Index_u16++)
        {
            if (COM_GET_IPDUCOUNTER_DM(Index_u16) >0 )
            {
                /*If the state is changed from RESET to SET*/
                /*As the counters are already updated, no necessary actions are required the other way around */
                /* if(RxIPduRamPtr->RxFlags.Pdu_DMStatus == 0)  */
                if ((Com_GetRamValue(RXIPDU,_DMSTATUS,RxIPduRamPtr->RxFlags)) == COM_FALSE)
                {
                    Com_EnableRxDeadlineMonitoring_Inline((Com_IpduIdType)Index_u16,COM_TRUE);
                    /* (RxIPduRamPtr->RxFlags.Pdu_DMStatus = COM_SET)  */
                    Com_SetRamValue(RXIPDU,_DMSTATUS,RxIPduRamPtr->RxFlags, COM_TRUE);
                }
            }
            else
            {
                /* if(RxIPduRamPtr->RxFlags.Pdu_DMStatus)  */
                if (Com_GetRamValue(RXIPDU,_DMSTATUS,RxIPduRamPtr->RxFlags))
                {
                    /*Interrupt is locked due to the updation of IPdu Group DM Status. */
                    /* (RxIPduRamPtr->RxFlags.Pdu_DMStatus = COM_RESET)  */
                    Com_SetRamValue(RXIPDU,_DMSTATUS,RxIPduRamPtr->RxFlags, COM_FALSE);
                }

            }
            RxIPduRamPtr++;
        } /* End of Rx IPdu for loop */

    }/* if ((Com_Uninit_Flag == COM_INIT)) */
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_EnableRxDeadlineMonitoring_Inline
 Syntax           : void Com_EnableRxDeadlineMonitoring_Inline(Com_IpduIdType IpduId, boolean Initialize)
 Description      : Inline function to enable the Rx DeadlineMonitoring.
 Parameter        : IpduId -> Id of the Rx ipdu
                  : Initialize -> Decides whether to load first timeout factor or normal timeout factor
 Return value     : None
 ***************************************************************************************************/
static INLINE FUNC (void, COM_CODE) Com_EnableRxDeadlineMonitoring_Inline(VAR(Com_IpduIdType, AUTOMATIC) IpduId,
        VAR(boolean, AUTOMATIC) Initialize)
{

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
    /* Pointer to Configuration Data */
    Com_RxIpduConstPtrType RxIPduConstPtr;
#endif /* #if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout) */
#ifdef COM_RxSigUpdateTimeout
    /* Pointer to RAM data */
    Com_RxSigRamPtrType RxSigRamPtr;
#endif /* #ifdef COM_RxSigUpdateTimeout */
    Com_RxIpduRamPtrType RxIPduRamPtr;

#if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))
    /* Pointer to Configuration Data */
    P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST) SigTimeOutConfigPtr;
    P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) SigTimeOutTicksPtr;
    VAR(uint16_least, AUTOMATIC) Idx_Sig_ui;
    VAR(uint16_least, AUTOMATIC) numOfSigOrGrpSig;
#endif /* #if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)) */

#ifdef COM_RxSigUpdateTimeout
    VAR(uint16_least, AUTOMATIC) RxSigId_Index_ui;
#endif /* #ifdef COM_RxSigUpdateTimeout */
#if ((!defined(COM_RxIPduTimeout)) && (!defined(COM_RxSigUpdateTimeout) && (!defined(COM_RxSigGrpUpdateTimeout))))
    (void)Initialize;
#endif

#if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout)
        RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(IpduId);
#endif /* #if defined (COM_RxIPduTimeout) || defined (COM_RxSigUpdateTimeout) || defined (COM_RxSigGrpUpdateTimeout) */

    RxIPduRamPtr = &COM_GET_RXPDURAM_S(IpduId);
#if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))
    SigTimeOutConfigPtr = NULL_PTR;
    SigTimeOutTicksPtr = NULL_PTR;
#endif /* #if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)) */


#ifdef COM_RxIPduTimeout
    if (Initialize != COM_FALSE)
    {
        /* Initialize parameter is TRUE
         * Reset the Reception deadline monitoring timer to COM_FIRST_TIMEOUT_FACTOR
         * Start the First timeout
         * If First timeout is not configured , load the timer with specific value ie 0xFFFF.
         * If First timeout is configured then load the actual value
         */
        RxIPduRamPtr->RxTicks_u16 = (RxIPduConstPtr->FirstTimeout_Factor == 0)? COM_RXTIMER_MAX :
        RxIPduConstPtr->FirstTimeout_Factor;
    }
    else
    {
        VAR(uint16, AUTOMATIC) rxTimeOutFact_u16;
        /* FC_VariationPoint_START */
#ifdef COM_RXPDU_TIMEOUT_VIA_CALIBRATION
        rxTimeOutFact_u16 = Com_GetRxIPduTimeoutCalibration(IpduId);
#else
        /* FC_VariationPoint_END */
        rxTimeOutFact_u16 = RxIPduConstPtr->Timeout_Fact;
        /* FC_VariationPoint_START */
#endif /* #ifdef COM_RXPDU_TIMEOUT_VIA_CALIBRATION */
        /* FC_VariationPoint_END */
        /* Initialize parameter is FALSE
         * Reset the Reception deadline monitoring timer to COM_TIMEOUT_FACTOR
         * Start the regular timeout
         * If First timeout is not configured , load the timer with specific value ie 0xFFFF.
         * If First timeout is configured then load the actual value
         */
        RxIPduRamPtr->RxTicks_u16 = (rxTimeOutFact_u16 == 0)? COM_RXTIMER_MAX : rxTimeOutFact_u16;
    }
#endif /* #ifdef COM_RxIPduTimeout */

    /* Reset to the required values all variables used for Rx Deadline monitoring */
    /* RxIPduRamPtr ->RxFlags.RxIndicationFlag = COM_RESET */
    Com_SetRamValue(RXIPDU,_INDICATION,RxIPduRamPtr ->RxFlags, COM_FALSE);


#ifdef COM_RxSigUpdateTimeout
    /* If this IPDU has signals with update-bits , initialise the pointers
     * Separate deadline monitoring should be performed for signals with update-bit
     */
    numOfSigOrGrpSig = RxIPduConstPtr->No_Of_Sig_Ref;
    if (RxIPduConstPtr->SignalTimeout_Ref != NULL_PTR)
    {
        SigTimeOutConfigPtr = RxIPduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref;
        SigTimeOutTicksPtr = RxIPduConstPtr->SignalTimeout_Ref->TimeoutTicks_p;
    }
    RxSigRamPtr = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
    RxSigId_Index_ui = (uint32)RxIPduConstPtr->RxSigId_Index + numOfSigOrGrpSig;
    SchM_Enter_Com_RxSigToTicks();

    for(Idx_Sig_ui = RxIPduConstPtr->RxSigId_Index; Idx_Sig_ui < RxSigId_Index_ui; Idx_Sig_ui++)
    {
        /* Check if the signal contained within this IPDU has update-bit configured & timeout
         * monitoring is enabled for the signal
         */
        if ((SigTimeOutConfigPtr != NULL_PTR) &&
                (Idx_Sig_ui == (uint32)SigTimeOutConfigPtr->SigId))
        {
            if (Initialize != COM_FALSE)
            {
                /* Initialize parameter is TRUE
                 * Initialise timer for signal with COM_FIRST_TIMEOUT_FACTOR value
                 * If FirstTimeOutFactor is disabled then load timer with COM_RXTIMER_MAX(0xFFFF)
                 * If FirstTimeOutFactor is enabled then load the configured value
                 */
                (*SigTimeOutTicksPtr) = (SigTimeOutConfigPtr->First_Timeout == 0) ? COM_RXTIMER_MAX :
                SigTimeOutConfigPtr->First_Timeout;
            }
            else
            {
                /* Initialize parameter is FALSE
                 * Initialise timer for signal with COM_TIMEOUT_FACTOR value
                 * If COM_TIMEOUT_FACTOR is disabled then the corresponding entry will not be present in
                 * Com_SignalTimeoutInfo array.
                 * Hence no need to check if COM_TIMEOUT_FACTOR is disabled.
                 */
                (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout;
            }

            /* Increment pointers to refer next signal with update-bit(within this IPDU)
             * If no next signal with update-bit is present in the IPDU, then the if() check fails and
             * the code inside if() block is not executed.
             */
            SigTimeOutTicksPtr++;
            SigTimeOutConfigPtr++;
        }
        RxSigRamPtr ++ ;
    }/*End of for loop*/
    SchM_Exit_Com_RxSigToTicks();
#endif /* #ifdef COM_RxSigUpdateTimeout */
#ifdef COM_RX_SIGNALGROUP

#ifdef COM_RxSigGrpUpdateTimeout
    /* If this IPDU has signal groups with update-bits , initialise the pointers
     * Separate deadline monitoring should be performed for signals with update-bit
     */
    if (RxIPduConstPtr->SignalGrpTimeout_Ref != NULL_PTR)
    {
        SigTimeOutConfigPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref;
        SigTimeOutTicksPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p;
    }
    numOfSigOrGrpSig = (uint32)RxIPduConstPtr->FirstRxSigGrp_Index + (uint32)RxIPduConstPtr->No_Of_SigGrp_Ref;
    SchM_Enter_Com_RxSigGrpToTicks();

    for(Idx_Sig_ui = (uint32)RxIPduConstPtr->FirstRxSigGrp_Index; Idx_Sig_ui < numOfSigOrGrpSig; Idx_Sig_ui++)
    {
        /* Check if the signal group contained within this IPDU has update-bit configured & timeout
         * monitoring is enabled for the signal group
         */
        if ((SigTimeOutConfigPtr != NULL_PTR) &&
                (Idx_Sig_ui == SigTimeOutConfigPtr->SigId))
        {
            if (Initialize != COM_FALSE)
            {
                /* Initialize parameter is TRUE
                 * Initialise timer for signal grou with COM_FIRST_TIMEOUT_FACTOR value
                 * If FirstTimeOutFactor is disabled then load timer with COM_RXTIMER_MAX(0xFFFF)
                 * If FirstTimeOutFactor is enabled then load the configured value
                 */
                (*SigTimeOutTicksPtr) = (SigTimeOutConfigPtr->First_Timeout == 0) ? COM_RXTIMER_MAX :
                SigTimeOutConfigPtr->First_Timeout;
            }
            else
            {
                /* Initialize parameter is FALSE
                 * Initialise timer for signal group with COM_TIMEOUT_FACTOR value
                 * If COM_TIMEOUT_FACTOR is disabled then the corresponding entry will not be present in
                 * Com_SignalTimeoutInfo array.
                 * Hence no need to check if COM_TIMEOUT_FACTOR is disabled.
                 */
                (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout;
            }
            /* Increment pointers to refer next signal group with update-bit(within this IPDU)
             * If no next signal group with update-bit is present in the IPDU, then the if() check fails and
             * the code inside if() block is not executed.
             */
            SigTimeOutTicksPtr++;
            SigTimeOutConfigPtr++;

        }

    }/*End of for loop*/
    SchM_Exit_Com_RxSigGrpToTicks();
#endif /* #ifdef COM_RxSigGrpUpdateTimeout */
#endif /* #ifdef COM_RX_SIGNALGROUP */

}

