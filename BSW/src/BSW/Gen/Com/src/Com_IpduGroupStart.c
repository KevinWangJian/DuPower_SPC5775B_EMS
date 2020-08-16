

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

static INLINE FUNC(void, COM_CODE) Com_RxIPduStart(VAR(Com_IpduIdType, AUTOMATIC) IpduId,VAR(boolean, AUTOMATIC) Initialize);

static INLINE FUNC(void, COM_CODE) Com_TxIPduStart(VAR(Com_IpduIdType, AUTOMATIC) IpduId,VAR(boolean, AUTOMATIC) Initialize);

/***************************************************************************************************
 Function name    : Com_IpduGroupControl
 Syntax           : void FUNC(void, COM_CODE) Com_IpduGroupControl( VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector, VAR(boolean, AUTOMATIC) initialize )
 Description      : Service for controlling the Ipdu groups
 Parameter        : Com_IpduGroupVector -> I-PDU group vector containing the activation state (stopped = 0/ started = 1) for all I-PDU groups.
                  : Initialize -> flag to request initialization of the I-PDUs which are newly started
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_IpduGroupControl( VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector, VAR(boolean, AUTOMATIC) initialize )
{

    P2CONST(Com_IpduIdType, AUTOMATIC, COM_APPL_CONST) IPduRefPtr;
    Com_IPduGrpConstPtrType     IPduGrpConstPtr;    /* Local pointer to Ipdu Group static configuration */
    Com_TxIpduRamPtrType        TxIPduRamPtr;       /* Local pointer to Tx Ipdu dynamic configuration   */
    Com_RxIpduRamPtrType        RxIPduRamPtr;       /* Local pointer to Rx Ipdu dynamic configuration   */
    VAR(uint16, AUTOMATIC)      Index_u16;
    VAR(Com_IpduGroupIdType, AUTOMATIC) IpduGrpId_u16;
    VAR(uint16,AUTOMATIC)       NoofPdus_u16;
    VAR(uint8, AUTOMATIC)       ByteVal_u8;
    VAR(uint8,AUTOMATIC)        BitOffset_u8;
    VAR(boolean, AUTOMATIC)     PduGrp_Status_b;

    /* Start: Det */

    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_IpduGroupControl,  COM_E_UNINIT)

    COM_REPORT_ERROR(((initialize!=COM_TRUE)&&(initialize!=COM_FALSE)),COMServiceId_IpduGroupControl,COM_E_PARAM)

    /* End: Det */

    /* A call to the API Com_ReceptionDMControl is made to set the DM vector with the same value
     * as that of the IPduGroupVector */
    Com_ReceptionDMControl(ipduGroupVector);

    if (Com_Uninit_Flag == COM_INIT)
    {

        /* It needs to be checked if a DET check is required for the size of the array passed by the application */
        for (Index_u16 = 0; Index_u16 < COM_NUM_ARR_IPDUGRPVECT; Index_u16++)
        {
            if (Com_IpduGrpVector[Index_u16] != ipduGroupVector[Index_u16] )
            {
                /* Perform an XOR to find the Ipdu Groups which have changed the states */
                /* Does this action require interrupt protection*/

                ByteVal_u8 = (uint8)((Com_IpduGrpVector[Index_u16]) ^ (ipduGroupVector[Index_u16]));
                BitOffset_u8 = 0;

                /*If there are some Ipdu groups which have changed the status*/
                while(ByteVal_u8 > 0)
                {
                    /*Check for the status of the changed Ipdu groups and perform actions accordingly*/
                    /* Check if any of the IPdu Group is changed by performing right bit shift*/

                    if ( COM_RESET != ( ByteVal_u8 & ((uint8)1) ) )
                    {

                        /*Get the Ipdu group Id if the status is changed*/
                        IpduGrpId_u16 = (8 *Index_u16)+ BitOffset_u8;

                        /* Convert external HandleId to internal HandleId
                           IMP : ipduGroupVector will be set/reset based on the external ID.
                           It is required to convert the ID only when accessing the tables
                           For pre-compile , conversion is not required. Access Macro will return the same ID, which is passed to it */
                        IpduGrpId_u16 = COM_GET_IPDUGRP_ID(IpduGrpId_u16);

                        /* Handling a boolean variable needs to be checked here if it is correct*/

                        /* Get the latest status of the IPdu group */
                        PduGrp_Status_b = (((ipduGroupVector[Index_u16] >> BitOffset_u8) & ((uint8)(1))) != 0u);

                        IPduGrpConstPtr = COM_GET_IPDUGRP_CONSTDATA(IpduGrpId_u16);
                        IPduRefPtr = COM_GET_IPDUGRP_IPDUREF_CONSTDATA(IPduGrpConstPtr->FirstIpdu_Index);

                        NoofPdus_u16 = IPduGrpConstPtr ->NoOfPdus;

                        while(NoofPdus_u16 > 0 )
                        {
                            /* If the latest state is 'Activate' increment the counter*/
                            if (PduGrp_Status_b)
                            {
                                COM_GET_IPDUCOUNTER_S(*IPduRefPtr) ++;
                            }
                            /* If the latest state is 'De-Activate' decrement the counter*/
                            else
                            {
                                COM_GET_IPDUCOUNTER_S(*IPduRefPtr) --;

                            }


                            IPduRefPtr++;
                            NoofPdus_u16--;
                        }/* while(NoofPdus_u16 > 0 ) */

                    } /* if (ByteVal_u8 & ((uint8)1)) */
                    BitOffset_u8 ++;
                    ByteVal_u8 = ByteVal_u8 >> 1u;
                } /* while(ByteVal_u8 > 0) */

                /* update the status of the IPdu group */
                Com_IpduGrpVector[Index_u16] = ipduGroupVector[Index_u16] ;
            } /* if (Com_IpduGrpVector[Index_u16] != ipduGroupVector[Index_u16] ) */

        } /* End of For loop */
        RxIPduRamPtr   = &COM_GET_RXPDURAM_S(0);
        for (Index_u16 = 0; Index_u16 < COM_GET_NUM_RX_IPDU; Index_u16++)
        {
            /* If any of the Ipdu Group containing the IPdu is active */
            if (COM_GET_IPDUCOUNTER_S(Index_u16) >0 )
            {
                /*If the state is changed from RESET to SET*/
                /*if (RxIPduRamPtr->RxFlags.PduStatus == 0)   */
                if (Com_GetRamValue(RXIPDU,_PDUSTATUS,RxIPduRamPtr->RxFlags) == COM_STOP)
                {
                    Com_RxIPduStart((Com_IpduIdType)Index_u16,initialize);
                    /* RxIPduRamPtr->RxFlags.PduStatus = COM_START  */
                    Com_SetRamValue(RXIPDU,_PDUSTATUS,RxIPduRamPtr->RxFlags,COM_START);

                }
            }
            else
            {
                /*If the state is changed from SET to RESET*/
                /*if (RxIPduRamPtr->RxFlags.PduStatus != 0)   */
                if (Com_GetRamValue(RXIPDU,_PDUSTATUS,RxIPduRamPtr->RxFlags))
                {
                    /* RxIPduRamPtr ->RxFlags.RxIndicationFlag = COM_RESET */
                    Com_SetRamValue(RXIPDU,_INDICATION,RxIPduRamPtr->RxFlags,COM_FALSE);
                    /* RxIPduRamPtr->RxFlags.PduStatus = COM_STOP  */
                    Com_SetRamValue(RXIPDU,_PDUSTATUS,RxIPduRamPtr->RxFlags,COM_STOP);
                    /*Large Pdu Rx status is reset, No further calls for this reception are processed*/
                    Com_SetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr->RxFlags,COM_FALSE);
                }

            }

            RxIPduRamPtr++;
        } /*End of RxIpdu for loop */

        TxIPduRamPtr   = &COM_GET_TXPDURAM_S(0);
        for (Index_u16 = 0; Index_u16 < COM_GET_NUM_TX_IPDU; Index_u16++)
        {
            if (COM_GET_IPDUCOUNTER_S(Index_u16 + COM_GET_NUM_RX_IPDU) >0 )
            {
                /*If the state is changed from RESET to SET*/
                /*if (TxIPduRamPtr->RxFlags.PduStatus == 0)   */
                if (Com_GetRamValue(TXIPDU,_PDUSTATUS,TxIPduRamPtr ->Com_TxFlags) == COM_STOP)
                {
                    /* NOTE: This below order is to be maintained, to avoid any interrupt related race conditions.
                     * REASON: If the below function call is interrupted, by any other API,as the _PDUSTATUS is set after the function returns,
                     * the interrupting API returns without any effect */
                    Com_TxIPduStart((Com_IpduIdType)Index_u16,initialize);
                    /* TxIPduRamPtr->RxFlags.PduStatus = COM_START  */
                    Com_SetRamValue(TXIPDU,_PDUSTATUS,TxIPduRamPtr ->Com_TxFlags,COM_START);
                    /* By default release the large Ipdu buffer lock, which is acquired in Com_SendIpdu */
                    Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIPduRamPtr ->Com_TxFlags,COM_FALSE);
                }
            }
            else
            {
                /*If the state is changed from SET to RESET*/
                /*if (TxIPduRamPtr->RxFlags.PduStatus != 0)   */
                if (Com_GetRamValue(TXIPDU,_PDUSTATUS,TxIPduRamPtr ->Com_TxFlags))
                {
                    /* NOTE     : This below order is to be maintained, to avoid any interrupt related race conditions.
                     * REASON: If the below function call is interrupted, by any other API,as the _PDUSTATUS is set before the function call,
                     * the interrupting API returns without any effect */
                    /* TxIPduRamPtr->RxFlags.PduStatus = COM_STOP  */
                    Com_SetRamValue(TXIPDU,_PDUSTATUS,TxIPduRamPtr ->Com_TxFlags,COM_STOP);
                    Com_TxIPduStop((Com_IpduIdType)Index_u16);
                }

            }
            TxIPduRamPtr++;
        } /*  End of TxIpdu for loop  */
    }/* if ((Com_Uninit_Flag == COM_INIT)) */
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_ClearIpduGroupVector
 Syntax           : void Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector)
 Description      : Service to clear Ipdu group vector
 Parameter        : Com_IpduGroupVector -> I-PDU group vector containing the activation state (stopped = 0/ started = 1) for all I-PDU groups.
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ClearIpduGroupVector(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector)
{
    VAR(uint16, AUTOMATIC) Index_u16;

    for (Index_u16 = 0; Index_u16 < COM_NUM_ARR_IPDUGRPVECT; Index_u16++)
    {
        ipduGroupVector[Index_u16] = (uint8)0;
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/***************************************************************************************************
 Function name    : Com_SetIpduGroup
 Syntax           : void Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType IpduGroupId, boolean bitval)
 Description      : Service to set bit of the given Ipdu group vector that corresponds to the given I-PDU group.
 Parameter        : Com_IpduGroupVector -> I-PDU group vector containing the activation state (stopped = 0/ started = 1) for all I-PDU groups.
                  : IpduGroupId -> Id of the IpduGroup
                  : bitval --> New value of the corresponding bit
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_SetIpduGroup(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector, VAR(Com_IpduGroupIdType, AUTOMATIC) IpduGroupId, VAR(boolean, AUTOMATIC) bitval )
{
    VAR(uint16, AUTOMATIC) Index_u16;
    VAR (uint8,AUTOMATIC) BitOffset_u8;

    Index_u16 = IpduGroupId >> 3u;
    BitOffset_u8 = (uint8)(IpduGroupId - (uint16)(Index_u16 << 3u)) ;

    if (bitval)
    {
        ipduGroupVector[Index_u16] = ipduGroupVector[Index_u16] | (uint8)(1u << BitOffset_u8);
    }
    else
    {
        ipduGroupVector[Index_u16] = ipduGroupVector[Index_u16] & (uint8)(~((uint8)(1u << BitOffset_u8)));
    }

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_TxIPduStart
 Syntax           : void Com_TxIPduStart(Com_IpduIdType IpduId, boolean Initialize)
 Description      : Service to start the Tx ipdu
 Parameter        : IpduId -> Id of the ipdu
                  : Initialize -> flag to request initialization of the I-PDUs which are newly started
 Return value     : None
 ***************************************************************************************************/

static INLINE FUNC(void, COM_CODE) Com_TxIPduStart(VAR(Com_IpduIdType, AUTOMATIC) IpduId,VAR(boolean, AUTOMATIC) Initialize)
 {
    Com_TxSigConstPtrType   TxSigConstPtr;  /* Local pointer to Tx Signal static configuration */
    Com_TxIpduConstPtrType  TxIPduConstPtr; /* Local pointer to Tx ipdu static configuration */
    Com_TxIpduRamPtrType TxIpduRamPtr;        /* Local pointer to Tx ipdu dynamic configuration */
    VAR(uint16_least, AUTOMATIC) Index_Sig_ui;
    VAR(uint8, AUTOMATIC) LatestTransMode_u8;
#ifdef COM_TX_SIGNALGROUP
    Com_TxSigGrpConstPtrType TxSigGrpConstPtr;    /* Local pointer to Tx SignalGroup static configuration */
    VAR(uint16_least, AUTOMATIC) Index_SigGrp_ui;
#endif

#if defined (COM_TX_SIGNALGROUP) && defined(COM_TxFilters) && defined (COM_F_ONEEVERYN)
    Com_TxGrpSigConstPtrType TxGrpSigConstPtr;  /* Local pointer to Tx GroupSignal static configuration */
#endif



#if defined (COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)
    VAR(PduLengthType, AUTOMATIC) ByteNo_u8;
    VAR(uint8, AUTOMATIC) ConstByteValue_u8;
#endif

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(IpduId);

    /*The below Initialize check should be only after Com_LatestTransMode is calculated */
    if(Initialize != COM_FALSE)
    {

        TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);

        for(Index_Sig_ui = TxIPduConstPtr->No_Of_Sig_Ref;Index_Sig_ui != 0u;Index_Sig_ui--)
        {

#ifdef COM_TxSigUpdateBit
            /* Only the first byte of txIPduFields is needed */
            ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;
            /*    if(TxIPduConstPtr->txIPduFields.ClearUpdBit != (uint8)COM_CLRUPDATEBIT_NONE)*/
            if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) != (uint16)COM_CLRUPDATEBIT_NONE)
            {

                /* Clear Update bits*/
                /* if(TxSigConstPtr->General.UpdBitConf != COM_FALSE) */
                if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
                {
                    /*Find the Byte No, where the Update bit lies */
                    ByteNo_u8 = (PduLengthType)((TxSigConstPtr->Update_Bit_Pos)>>3u);
                    /* This macro clears the update bit value at the Update bit position */
                    Com_ClearUpdateBitValue(TxIPduConstPtr,TxSigConstPtr->Update_Bit_Pos,ByteNo_u8)

                }
            }
#endif/*COM_TxSigUpdateBit*/

            /* OCCURRENCE shall be set to zero by Com_IpduGroupStart*/
#ifdef COM_TxFilters
#ifdef COM_F_ONEEVERYN
            /*     if(TxSigConstPtr->txSignalFields.FilterAlgorithm == (uint8)COM_ONE_EVERY_N) */
            if(Com_GetValue(TXSIG,_FILTRALG,TxSigConstPtr->txSignalFields) == (uint8)COM_ONE_EVERY_N)
            {
                COM_GET_ONEEVERYN(TxSigConstPtr->Filter_Index).Occurrence = 0;
            }

#endif
#endif

            TxSigConstPtr++;
        }

#ifdef COM_TX_SIGNALGROUP

        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);

        for(Index_SigGrp_ui=(uint16_least)TxIPduConstPtr ->No_Of_SigGrp_Ref;Index_SigGrp_ui != 0u;Index_SigGrp_ui--)
        {


#if defined(COM_TxFilters) && defined (COM_F_ONEEVERYN)

            TxGrpSigConstPtr= COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr ->FirstGrpSig_Index);

            for(Index_Sig_ui = TxSigGrpConstPtr ->No_Of_GrpSig;Index_Sig_ui !=0u;Index_Sig_ui--)
            {

                /* OCCURRENCE shall be set to zero by Com_IpduGroupStart*/

                if( TxGrpSigConstPtr->Filter_Algo == (uint8)COM_ONE_EVERY_N)
                {
                    COM_GET_ONEEVERYN(TxGrpSigConstPtr->Filter_Index).Occurrence = 0;
                }
                TxGrpSigConstPtr++;
            }
#endif /* #if defined(COM_TxFilters) && defined (COM_F_ONEEVERYN) */



            /* Clear Update bits*/
#ifdef COM_TxSigGrpUpdateBit
            /* Only the first byte of txIPduFields is needed */
            ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;
            /*    if(TxIPduConstPtr->txIPduFields.ClearUpdBit != (uint8)COM_CLRUPDATEBIT_NONE)*/
            if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) != (uint16)COM_CLRUPDATEBIT_NONE)
            {

                /* Clear Update bits*/
                /* if(TxSigGrpConstPtr->txSignalGrpFields.UpdBitConf != COM_FALSE) */
                if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
                {
                    /*Find the Byte No, where the Update bit lies */
                    ByteNo_u8 = (PduLengthType)((TxSigGrpConstPtr ->Update_Bit_Pos)>>3u);
                    /* This macro clears the update bit value at the Update bit position */
                    Com_ClearUpdateBitValue(TxIPduConstPtr,TxSigGrpConstPtr ->Update_Bit_Pos,ByteNo_u8)
                }
            }
#endif  /*COM_TxSigGrpUpdateBit*/

            TxSigGrpConstPtr++;
        }
#endif

        /* Call Com_TxChangeMode( )
                    To calculate the Com_LatestTransMode[i] */
        Com_TxChangeMode(IpduId);
        /*Note: Even though if the Com_Tick_Tx is updated in Com_TxChangeMode(),
                                       it is once again updated in Ipdu Group Start i.e below*/
        /* LatestTransMode_u8 = TxIpduRamPtr->Com_TransMode.LatestTransMode */
        LatestTransMode_u8 = Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode);

        /* Reset the global TMS status flag on the start of IPduGroup */
        Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

        /* time period and offset attributes of IPDUs in
                           Periodic or Mixed Transmission Mode */
        /* The CurrentTxModePtr points to the structure information of the current TxModeState */
        if( COM_RESET != ( LatestTransMode_u8 & COM_TXMODE_MIXED ) )
        {
            /*I.e first timeout factor*/
            TxIpduRamPtr->Com_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->TimeOffsetFact;
        }
        /* the minimum delay time attribute of IPDUs in
                       Direct/N-Times or Mixed Transmission Mode */
        /*Reset it to Zero i.e No Min delay check as soon as IpduGroup is started */
        TxIpduRamPtr->Com_MinDelayTick = 0;

        /*RESET all the Tx Confirmation and Tx timeout variables*/
        /*Reset it to Stop, Note: This Flag has to be set
                           to START only in SendIpdu() i,e just before Sending the IPDU*/
        /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_STOP */
        Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);
        /*Reset it to RESET*/

        /* The AUTOSAR COM module shall start the transmission deadline monitoring timer
         ** for this I-PDU upon the start of the I-PDU group to which the I-PDU belongs to*/
#ifdef COM_TxIPduTimeOut
        /* if(TxIPduConstPtr->txIPduFields.NoneModeTimeOut != (uint8)COM_FALSE) */
        if(Com_GetValue(TXIPDU,_NONETOSTATUS,TxIPduConstPtr->txIPduFields))
        {
            /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_START */
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
            TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
        }
        else
#endif/* #ifdef COM_TxIPduTimeOut */
        {
            /*Reset the timer to Zero */
#ifdef COM_TxIPduTimeOut
            TxIpduRamPtr->Com_TickTxTimeout = 0;
#endif/* #ifdef COM_TxIPduTimeOut */
            /* TxIpduRamPtr->Com_TxFlags.TxConfirFlag = COM_RESET */
            Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }


    }/*End of If(INITIALIZE)*/
    else
    {
        /* Check if IPDU group is TX group
         * Cyclic IPDU's will be sent out cyclically after the call of this API
         */

        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);

#ifdef COM_TxIPduTimeOut
        TxIpduRamPtr = &COM_GET_TXPDURAM_S(IpduId);
#endif
        /* Call Com_TxChangeMode( )
                        To calculate the Com_LatestTransMode[i] */
        Com_TxChangeMode((Com_IpduIdType)IpduId);
        /*Note: Eventhough if the Com_Tick_Tx is updated in Com_TxChangeMode(),
                                it is once again updated in Ipdu Group Start i.e below*/

        /* The AUTOSAR COM module shall start the transmission deadline monitoring timer
         ** for this I-PDU upon the start of the I-PDU group to which the I-PDU belongs to*/
#ifdef COM_TxIPduTimeOut
        /* if(TxIPduConstPtr->txIPduFields.NoneModeTimeOut != (uint8)COM_FALSE) */
        if(Com_GetValue(TXIPDU,_NONETOSTATUS,TxIPduConstPtr->txIPduFields))
        {
            /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_START */
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
            TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
        }
#endif

    }
}
/***************************************************************************************************
 Function name    : Com_RxIPduStart
 Syntax           : void Com_RxIPduStart(Com_IpduIdType IpduId, boolean Initialize)
 Description      : Service to start the Rx ipdu
 Parameter        : IpduId -> Id of the ipdu
                  : Initialize -> flag to request initialization of the I-PDUs which are newly started
 Return value     : None
 ***************************************************************************************************/

static INLINE FUNC(void, COM_CODE) Com_RxIPduStart(VAR(Com_IpduIdType, AUTOMATIC) IpduId,VAR(boolean, AUTOMATIC) Initialize)
{
#if defined(COM_RX_SIGNALGROUP) || (defined(COM_RxFilters) && defined(COM_F_ONEEVERYN))
    VAR(uint16_least, AUTOMATIC) Index_Sig_ui;
# if defined(COM_RxFilters) && defined(COM_F_ONEEVERYN)
    Com_RxSigConstPtrType RxSigConstPtr;    /* Local pointer to Rx Signal static configuration */
# endif
    Com_RxIpduConstPtrType RxIPduConstPtr;  /* Local pointer to Rx Ipdu static configuration */
# ifdef COM_RX_SIGNALGROUP
    Com_RxSigGrpRamPtrType RxSigGrpRamPtr;  /* Local pointer to Rx SignalGroup dynamic configuration */
#  if defined(COM_RxFilters) && defined(COM_F_ONEEVERYN)
    Com_RxSigGrpConstPtrType      RxSigGrpConstPtr;
    Com_RxGrpSigConstPtrType      RxGrpSigConstPtr;
    VAR(uint16_least, AUTOMATIC)  index_ui;
#  endif
# endif /* #ifdef COM_RX_SIGNALGROUP */

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(IpduId);

# ifdef COM_RX_SIGNALGROUP

#  if defined(COM_RxFilters) && defined(COM_F_ONEEVERYN)
    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA( RxIPduConstPtr->FirstRxSigGrp_Index );
#endif

    RxSigGrpRamPtr = &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);

    for (Index_Sig_ui = RxIPduConstPtr->No_Of_SigGrp_Ref; Index_Sig_ui != 0u; Index_Sig_ui--)
    {
#  if defined(COM_RxFilters) && defined(COM_F_ONEEVERYN)

        RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA( RxSigGrpConstPtr->FirstGrpSig_Index );

        for ( index_ui = (uint16_least)RxSigGrpConstPtr->No_Of_GrpSig; index_ui != (uint16_least)0; index_ui-- )
        {
            if ( RxGrpSigConstPtr->Filter_Algo == (uint8)COM_ONE_EVERY_N )
            {
                COM_GET_ONEEVERYN(RxGrpSigConstPtr->Filter_Index).Occurrence = 0;
            }
            RxGrpSigConstPtr++;
        }
#  endif /* #  if defined(COM_RxFilters) && defined(COM_F_ONEEVERYN) */
        if (Initialize)
        {
            /* RxSigGrpRamPtr ->rxSigGrpRAMFields.SigGrpNotify_Flag = COM_TRUE */
            Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
        }
        RxSigGrpRamPtr++;
#  if defined(COM_RxFilters) && defined(COM_F_ONEEVERYN)
        RxSigGrpConstPtr++;
#  endif
    }
# else
    /*  Misra warning removal for unused parameter */
    (void)Initialize;
# endif /* #ifdef COM_RX_SIGNALGROUP */

# if defined(COM_RxFilters) && defined(COM_F_ONEEVERYN)

    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

    for(Index_Sig_ui = RxIPduConstPtr->No_Of_Sig_Ref; Index_Sig_ui != 0u;Index_Sig_ui--)
    {
        /*     if(RxSigConstPtr->rxSignalFields.FilterAlgorithm == (uint8)COM_ONE_EVERY_N) */
        if(Com_GetValue(RXSIG,_FILTRALG,RxSigConstPtr->rxSignalFields) == (uint8)COM_ONE_EVERY_N)
        {
            COM_GET_ONEEVERYN(RxSigConstPtr->Filter_Index).Occurrence = 0;
        }
        RxSigConstPtr++;
    }
# endif /* # if defined(COM_RxFilters) && defined(COM_F_ONEEVERYN) */

#else
    /*  Misra warning removal for unused parameter */
    (void)IpduId;
    (void)Initialize;
#endif/* #if defined(COM_RX_SIGNALGROUP) || (defined(COM_RxFilters) && defined(COM_F_ONEEVERYN)) */
}

