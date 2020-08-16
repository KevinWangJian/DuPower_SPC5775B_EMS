
/**
 *********************************************************************
 * \moduledescription
 *
 *
 * \scope           [INTERN]
 *********************************************************************
 */

/**
 * \defgroup IPDUM_PRIV_H    IpduM_Priv - Private Function of IpduM
 * \n
 */

#ifndef IPDUM_PRIV_H
#define IPDUM_PRIV_H

/*
 *********************************************************************
 * Includes
 *********************************************************************
 */

#include "IpduM_Types.h"
#include "IpduM.h"
#include "IpduM_Cfg_SchM.h"
#include "rba_BswSrv.h"

/*
 *********************************************************************
 * Defines
 *********************************************************************
 */

/**
 * @ingroup IPDUM_PRIV_H
 *
 * Invalid Selector value \n
 */
#define IPDUM_INVALID_SELECTOR        0xFFFFu
/**
 * @ingroup IPDUM_PRIV_H
 *
 *  Endianes type: Little endian
 */
#define IPDUM_LITTLEENDIAN          TRUE
/**
 * @ingroup IPDUM_PRIV_H
 *
 *  Endianes type: Big Endian
 */
#define IPDUM_BIGENDIAN             FALSE
/**
 *  @ingroup IPDUM_PRIV_H
 *
 * Length of Unint 8 variable
 *
 * . \n
 */
#define    IPDUM_UINT8_LENGTH            8
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Length of Unint 32 variable \n
 */
#define    IPDUM_UINT32_LENGTH            32
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Header = Id (24 bits) + Dlc(8 bits)\n
 */
#define    IPDUM_CREATE_SHORT_HEADER(ID, DLC)   (uint32)((((ID) << 8u) | (DLC)))
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Get the current container instance Pdu length\n
 */
#define    IPDUM_CUR_CNTNR_SDU_LEN(BaseAddr, PduLen)   *((BaseAddr) + (PduLen))
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Get the container length[instances in q + container length]\n
 */
#define    IPDUM_TOTAL_CNTNR_LEN(TxContainerLen, InstancesInQueue)   (((TxContainerLen)*(InstancesInQueue)) + (InstancesInQueue))

#if ((defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)) || (defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF)))

/*Returns the Id value from that specified container location*/
LOCAL_INLINE FUNC(uint32, IpduM_Code) IpduM_ReadIdFromHeader(
        VAR(uint8, AUTOMATIC) ContainerHeaderSize,
        P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) ContainerAddr)
{
    uint8 index_u8;
    uint32 pduHeaderId;
    pduHeaderId = 0u;

#if(IPDUM_HEADER_BYTEORDER == IPDUM_LITTLEENDIAN)
    {
        if(ContainerHeaderSize != IPDUM_HEADERTYPE_SHORT_SIZE)
        {
            ContainerAddr+=IPDUM_FOUR_BYTES;
        }
        /*Read byte by byte data from the starting address of the container address*/
        for(index_u8 = IPDUM_FOUR_BYTES ; index_u8 != 0u; index_u8--)
        {
            pduHeaderId <<= 8u;
            pduHeaderId |= *(ContainerAddr+(index_u8-1u));
        }

    }
#else
    {
        /*Read byte by byte data from the starting address of the container address*/
        for(index_u8 = 0u ; index_u8 < IPDUM_FOUR_BYTES; index_u8++)
        {
            pduHeaderId <<= 8u;
            pduHeaderId |= *(ContainerAddr+index_u8);
        }
    }
#endif /* #if(IPDUM_HEADER_BYTEORDER == IPDUM_LITTLEENDIAN) */
    if(ContainerHeaderSize == IPDUM_HEADERTYPE_SHORT_SIZE)
    {
        /*Read the First 3 bytes which gives you the Id info */
        pduHeaderId >>= 8u;
    }

    return pduHeaderId;
}


/*Returns the DLC from that specified container location*/
LOCAL_INLINE FUNC(uint32, IpduM_Code) IpduM_ReadDlcFromHeader(
        VAR(uint8, AUTOMATIC) ContainerHeaderSize,
        P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) ContainerAddr)
{
    uint8 index_u8;
    uint32 dlc;
    dlc = 0u;
#if(IPDUM_HEADER_BYTEORDER == IPDUM_LITTLEENDIAN)
    {
        /*Read byte by byte data from the starting address of the container address*/
        for(index_u8 = IPDUM_FOUR_BYTES ; index_u8 != 0u; index_u8--)
        {
            dlc <<= 8u;
            dlc |= *(ContainerAddr+(index_u8-1u));
        }
    }
#else
    {
        /* Read byte by byte data after offsetting by four bytes, as PduHeaderID will be placed in the starting address of the container */
        if(ContainerHeaderSize != IPDUM_HEADERTYPE_SHORT_SIZE)
        {
            ContainerAddr+=IPDUM_FOUR_BYTES;
        }
        for(index_u8 = 0 ; index_u8 < IPDUM_FOUR_BYTES; index_u8++)
        {
            dlc <<= 8u;
            dlc |= *(ContainerAddr+index_u8);
        }
    }
#endif /* #if(IPDUM_HEADER_BYTEORDER == IPDUM_LITTLEENDIAN) */

    if(ContainerHeaderSize == IPDUM_HEADERTYPE_SHORT_SIZE)
    {
        /*Read the 4th byte which gives you the Dlc info */
        dlc &= (0x000000ffu);
    }

    return dlc;

}

#endif /*((defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)) || (defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF)))*/

/*Copy the buffer into the container */
LOCAL_INLINE void IpduM_ByteCopyBuffer(
        P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcPtr,
        P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr,
        uint32 Len
)
{
    uint8_least Index_ui;

    for(Index_ui = 0; Index_ui < Len; Index_ui++)
    {
        *DestPtr = *SrcPtr;
        SrcPtr++;
        DestPtr++;
    }
}

/**
 * @ingroup IPDUM_PRIV_H    IpduM - IPDUM_RXDIRECT_COMINVOCATION \n
 * It shall be allowed to optimize the RX- and TX-Confirmation path from the IpduM module \n
 * via the PDU-Router module to the COM layer to call the COM API directly from the IpduM module without including the PDU-Router.\n
 * This shall be indicated by setting the published parameter IpduMRxDirectComInvocation to TRUE
 * \n
 */

#if IPDUM_RXDIRECT_COMINVOCATION
/**
 * @ingroup IPDUM_PRIV_H
 *
 *  If IPDUM_RXDIRECT_COMINVOCATION is set to true then Com call backs(Com_TxConfirmation) will be called \n
 */
#define IPDUM_UPL_TXCONFIRMATION     Com_TxConfirmation
/**
 * @ingroup IPDUM_PRIV_H
 *
 *  If IPDUM_RXDIRECT_COMINVOCATION is set to true then Com call backs(Com_RxIndication) will be called \n
 */
#define IPDUM_UPL_RXINDICATION         Com_RxIndication

/**
 * @ingroup IPDUM_PRIV_H
 *
 *  If IPDUM_RXDIRECT_COMINVOCATION is set to true then Com call backs(Com_TriggerTransmit) will be called \n
 */
#define IPDUM_UPL_TRIGGERTRANSMIT     Com_TriggerTransmit

#else
/**
 * @ingroup IPDUM_PRIV_H
 *
 * If IPDUM_RXDIRECT_COMINVOCATION is set to false then PduR call backs(PduR_IpduMTxConfirmation) will be called \n
 */
#define IPDUM_UPL_TXCONFIRMATION     PduR_IpduMTxConfirmation
/**
 * @ingroup IPDUM_PRIV_H
 *
 * If IPDUM_RXDIRECT_COMINVOCATION is set to false then PduR call backs(PduR_IpduMRxIndication) will be called \n
 */
#define IPDUM_UPL_RXINDICATION         PduR_IpduMRxIndication
/**
 * @ingroup IPDUM_PRIV_H
 *
 * If IPDUM_RXDIRECT_COMINVOCATION is set to false then PduR call backs(PduR_IpduMTxConfirmation) will be called \n
 */
#define IPDUM_UPL_TRIGGERTRANSMIT     PduR_IpduMTriggerTransmit

#endif

/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */

/**
 * @ingroup IPDUM_PRIV_H
 * typedef struct
 * {\n
 *   IpduM_StateType TxState;\n
 *   uint32          TxConfirmTimer;\n
 *   PduIdType       StaticPartPduId;     0xFF => invalid Pdu \n
 *   PduIdType       DynPartPduId;       passed in Ipdum_Transmit; index of PduR_ipdumLoTxToUp table \n
 *  } IpduM_TxRamType;
 */
typedef struct
{
    IpduM_StateType TxState;
    uint32             TxConfirmTimer;
    PduIdType        StaticPartPduId;
    PduIdType         DynPartPduId;
    PduIdType         PrevDynPartPduId;

} IpduM_TxRamType;


/**
 * @ingroup IPDUM_PRIV_H
 *typedef struct
 *{
 *P2VAR(uint8, TYPEDEF, IPDUM_VAR)    WritePtr;
 *P2VAR(uint8, TYPEDEF, IPDUM_VAR)    ReadPtr;
 *P2VAR(uint8, TYPEDEF, IPDUM_VAR)    TxConfPtr; \n  Pointer to current container queue Buffer
 *uint16    TxSendTimeOutTicks;    \n used to moniter Time out to transmit Pdu
 *uint16    TxConfRAMTicks;           \n Used to moniter Tx confirmation Time out
 *uint8     CurrentQueueInstance;      \n Queue instance during run time.
 *boolean   RetransmissionRequired;  \n this flag shall be set if PduR_IpduMTransmit returns E_NOT_OK, then this Pdu shall be retransmitted in the next mainfunction.
 *}IpduM_TxContainerPduDynamicType;
 * * */
typedef struct
{
    P2VAR(uint8, TYPEDEF, IPDUM_VAR)    WritePtr;
    P2VAR(uint8, TYPEDEF, IPDUM_VAR)    ReadPtr;
    P2VAR(uint8, TYPEDEF, IPDUM_VAR)    TxConfPtr;
    uint16    TxSendTimeOutTicks;
    uint16    TxConfRAMTicks;
    uint8     CurrentQueueInstance;
    boolean   RetransmissionRequired;
}IpduM_TxContainerPduDynamicType;


/**
 * @ingroup IPDUM_PRIV_H
 * typedef struct
 * {
 *     P2VAR(uint8, TYPEDEF, IPDUM_VAR)    WritePtr;
       P2VAR(uint8, TYPEDEF, IPDUM_VAR)    ReadPtr;
 *     uint8           CurrentQueueInstance;    \n Used to identify current instance of container Pdu
 *     }IpduM_RxContainerPduDynamicType;
 * */
typedef struct
{
    P2VAR(uint8, TYPEDEF, IPDUM_VAR)    WritePtr;
    P2VAR(uint8, TYPEDEF, IPDUM_VAR)    ReadPtr;
    uint8           CurrentQueueInstance;
}IpduM_RxContainerPduDynamicType;

/**
 * @ingroup IPDUM_PRIV_H
 * typedef struct
 *  {\n
 *   uint32          SwFRTimer; \n
 *   uint32          tiPrevTicks; \n
 *
 *  } IpduM_TimerType;
 */
typedef struct
{
    uint32            SwFRTimer;
    uint32            tiPrevTicks;

} IpduM_TimerType;

/* Access MACROS */



/* Start: DET Checking macro */
#if(IPDUM_DEV_ERROR_DETECT == STD_ON)
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Macro For functions with return type as 'Void' \n
 */

    #define IPDUM_REPORT_ERROR(CONDITION, API, ERROR)                                                             \
                                           if((CONDITION))                                                          \
                                           {                                                                      \
                                               (void) Det_ReportError(IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (API), (ERROR)); \
                                                return;                                                           \
                                           }
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Macro For functions with return type as 'Std_ReturnType' \n
 */
    #define IPDUM_REPORT_ERROR1(CONDITION, API, ERROR)                                                            \
                                           if((CONDITION))                                                          \
                                           {                                                                      \
                                               (void) Det_ReportError(IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, (API), (ERROR)); \
                                                return E_NOT_OK;                                                  \
                                           }

#else

    #define IPDUM_REPORT_ERROR(CONDITION, API, ERROR)

    #define IPDUM_REPORT_ERROR1(CONDITION, API, ERROR)

#endif

/*
 *********************************************************************
 * Prototypes
 *********************************************************************
 */
/**
 * @ingroup IPDUM_PRIV_H    IpduM - Internal Functions of IpduM
 *  This is the internal function for copying subparts <b>IpduM_CopyBuffer</b>
 * @param [in]         SubPartPtr - configuration of subpart\n
 * @param [in]         SrcPtr - pointer to input source location.\n
 * @param [in]         DestPtr - pointer to output destination location.
 * \n
 * @return None \n
 */
/* Begin of code section
*/
#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"
extern FUNC(void, IPDUM_CODE) IpduM_CopyBuffer(
											   CONST(boolean,IPDUM_CONST ) Endianess,
                                               P2CONST(IpduM_SubPartType, AUTOMATIC, IPDUM_APPL_DATA)   SubPartPtr,
                                               P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA)   SrcPtr,
                                               P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr
                                              );

extern FUNC(PduLengthType, IPDUM_CODE) IpduM_CreateHeaderForTypeShort(
                                                                      PduLengthType Id,
                                                                      PduLengthType Dlc);

extern FUNC( void, IPDUM_CODE ) IpduM_GetCurInstanceBaseAddress(
        PduIdType TxCrPduId);

extern FUNC(void, IPDUM_CODE) IpduM_CopyBufferToContainer(
        PduIdType TxCdPduId,
        PduLengthType ContainedPduLength,
        P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcPtr,
        P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr);

extern FUNC(boolean, IPDUM_CODE) IpduM_HandlingLastIsBestSemantics(PduIdType TxCdPduId,
        P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);

extern FUNC(Std_ReturnType, IPDUM_CODE) IpduM_PreparePduRTransmit(
        PduIdType TxCntnrPduId);

extern FUNC(void, IPDUM_CODE) IpduM_UpdateTxSendTimeOutTimer(PduIdType TxCdPduId,
        VAR(uint32, AUTOMATIC) CurPduLength);

extern FUNC(void, IPDUM_CODE) IpduM_ProcessRxContainerPdu(
        VAR(PduIdType, AUTOMATIC) PdumRxPduId,
        P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr,
        P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContainerPduConstPtr_pst
     );

extern FUNC( void, IPDUM_CODE ) IpduM_GetRxCurInstanceBaseAddress(
        P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxCrPtr_pst,
        P2VAR(IpduM_RxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_VAR) RxCrDynptr_pst
        );


/* End of code section
*/
#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

/* Begin of  variable section */
#define IPDUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "IpduM_MemMap.h"
/**
 * @ingroup IPDUM_PRIV_H
 *
 * IpduM module status flag. \n
 */
extern VAR(IpduM_StatusType,IPDUM_VAR) IpduM_Uninit_Flag;

/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of RAM data required for MPdus \n
 */
extern VAR(IpduM_TxRamType, IPDUM_VAR) IpduM_TxRamData[];

/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table for handling Rx container Pdu RAM variables \n
 */
extern VAR(IpduM_RxContainerPduDynamicType, IPDUM_VAR) IpduM_RxContainerPduDynData[];

/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table for handling Tx container Pdu RAM variables \n
 */
extern VAR(IpduM_TxContainerPduDynamicType, IPDUM_VAR) IpduM_TxContainerPduDynData[];

/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of SW timer required for MPdus \n
 */
extern VAR(IpduM_TimerType, IPDUM_VAR) IpduM_SwTimer;

/* End of variable section */
#define IPDUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "IpduM_MemMap.h"

/* Begin of  Constant section */
#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of all PDUs to be multiplexed \n
 */
extern    CONST(IpduM_TxRequestType, IPDUM_CONST) IpduM_TxReqTable[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of all PDUs to be de-multiplexed \n
 */
extern    CONST(IpduM_RxUpPduType, IPDUM_CONST)   IpduM_RxUpPduTable[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table for Multiplexed PDUs that are transmitted \n
 */
extern    CONST(IpduM_TxMPduType, IPDUM_CONST)    IpduM_TxMPduTable[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table for Multiplexed PDUs that are received \n
 */
extern    CONST(IpduM_RxMPduType, IPDUM_CONST)    IpduM_RxMPduTable[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of all subparts of each TX IPDU in a multiplexed PDU \n
 */
extern    CONST(IpduM_SubPartType, IPDUM_CONST)   IpduM_TxSubParts[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of all subparts of each RX IPDU in a multiplexed PDU \n
 */
extern    CONST(IpduM_SubPartType, IPDUM_CONST)   IpduM_RxSubParts[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of all Rx containers Pdu \n
 */
extern    CONST(IpduM_RxContainerPduType, IPDUM_CONST)   IpduM_RxContainerPdu[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of all Rx contained PDU's \n
 */
extern    CONST(IpduM_RxContainedPduType, IPDUM_CONST)   IpduM_RxContainedPdu[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of all Tx containers Pdu \n
 */
extern    CONST(IpduM_TxContainerPduType, IPDUM_CONST)   IpduM_TxContainerPdu[];
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table of all Tx contained PDU's \n
 */
extern    CONST(IpduM_TxContainedPduType, IPDUM_CONST)   IpduM_TxContainedPdu[];


/* End of Constant section */
#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"

/* Begin of  variable section */
#define IPDUM_START_SEC_VAR_INIT_8
#include "IpduM_MemMap.h"
/**
 * @ingroup IPDUM_PRIV_H
 *
 * Table for Com Handle Id's \n
 */
extern VAR(uint8, IPDUM_VAR) IpduM_TxConfTable[];

/* End of variable section */
#define IPDUM_STOP_SEC_VAR_INIT_8
#include "IpduM_MemMap.h"

#endif /* IPDUM_PRIV_H */

