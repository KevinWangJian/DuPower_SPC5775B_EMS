

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

static void Xcp_ConnectProtocolLayer(const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId);


/***************************************************************************************************
* Functions
***************************************************************************************************/
/**
****************************************************************************************************
This function processes the received XcpPacket and forwards it to a protcol layer
\param[in]  XcpPacketPtr          pointer to data and length of received packet
\param[in]  XcpTransportLayerId   id of transport layer which received data
\return     -
***************************************************************************************************/
void Xcp_Receive(const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint8 protLayerId;
  uint8 Pid_u8;

  XCP_DET_REPORT_ERROR((XcpTransportLayerId >= XCP_TL_IDS), XCP_RECEIVE_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID);
  XCP_DET_REPORT_ERROR((XcpPacketPtr->SduDataPtr == NULL_PTR), XCP_RECEIVE_SID, XCP_E_NULL_POINTER);

  /* check: XCP enabled */
  if ((Xcp_GlobalNoInit.EnabledResources_u8 != 0))
  {
    protLayerId = Xcp_GlobalNoInit.Tl2PlRef_au8[XcpTransportLayerId];
    Pid_u8 = XcpPacketPtr->SduDataPtr[0];

    /* check whether transport layer is already connected to a protocol layer / slave instance */
    if (protLayerId != XCP_INVALID_PROTLAYER_ID)
    {
      XCP_DET_REPORT_ERROR((protLayerId >= XCP_PL_IDS), XCP_RECEIVE_SID, XCP_E_INVALID_PROTOCOL_LAYER_ID);

      /* In order to accept new requests the XCP should not be in DISCONNECTING state */
      if (  (Xcp_NoInit[protLayerId].Session.XcpState_en != XCP_STATE_DISCONNECTING)
         && (XCP_ACTIVE_TL_ID(protLayerId) == XcpTransportLayerId)
         )
      {
        if(Pid_u8 >= XCP_PACKET_ID_CMD_MIN)
        {
          /* process the command */
          Xcp_ReceiveCommand(XcpPacketPtr, protLayerId);
        }
        else /* Frametype is a stim request */
        {
#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
          /* forward data to stim */
          Xcp_ReceiveStim(XcpPacketPtr, protLayerId);
#else
          XCP_DET_REPORT_ERROR_NO_RET(XCP_RECEIVE_SID, XCP_E_RX_STIM_DISABLED);
#endif
        }
      }
      else
      {
        /* XCP is still disconnecting. A new request can be handled only after the DISCONNECT is completely finished to avoid a trap due to invalid TL ID */
        XCP_DET_REPORT_ERROR((XCP_ACTIVE_TL_ID(protLayerId) != XcpTransportLayerId), XCP_RECEIVE_SID, XCP_E_INVALID_PROTOCOL_LAYER_ID);
      }
    }
    else
    { /* not connected to a protocol layer */
      if (   (Pid_u8 == XCP_CMD_CONNECT_ID) /* connect command ?*/
          && (XcpPacketPtr->SduLength >= XCP_CMD_CONNECT_LENGTH) /* packet has the min length */
         )
      {
#if (XCP_CONNECT_TRANSPORT_LAYER_CALLOUT == STD_ON)
        if (XcpAppl_ConnectTransportLayer(XcpTransportLayerId) != E_OK) /* allowed to connect this TransportLayer */
        { /* not allowed to connect */
          XCP_DET_REPORT_ERROR_NO_RET(XCP_RECEIVE_SID, XCP_E_CONNECT_FAILED);

          /* disconnect this Transport Layer */
          (void) Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].TLDisconnect_pfct(XcpTransportLayerId);
        }
        else
#endif
        {
          /* look for free protocol layer */
          Xcp_ConnectProtocolLayer(XcpPacketPtr, XcpTransportLayerId);
        }
      }
      else
      { /* not yet connected, but not correct connect command */
        XCP_DET_REPORT_ERROR_NO_RET(XCP_RECEIVE_SID, XCP_E_CONNECT_FAILED);

        /* disconnect this Transport Layer */
        (void) Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].TLDisconnect_pfct(XcpTransportLayerId);
      }
    }
  }
  else /* no resources enabled */
  {
    /* do not process anything, XCP disabled */
    XCP_DET_REPORT_ERROR_NO_RET(XCP_RECEIVE_SID, XCP_E_RESOURCE_DISABLED);

    /* disconnect this Transport Layer */
    Xcp_GlobalNoInit.Tl2PlRef_au8[XcpTransportLayerId] = XCP_INVALID_PROTLAYER_ID;
    (void) Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].TLDisconnect_pfct(XcpTransportLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/***************************************************************************************************
* Local functions
***************************************************************************************************/
/**
****************************************************************************************************
This function looks for a free protocol layer and calls the connect command
\param[in]  XcpPacketPtr          pointer to data and length of received packet
\param[in]  XcpTransportLayerId   id of transport layer which received data
\return     -
***************************************************************************************************/
static void Xcp_ConnectProtocolLayer(const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  uint8 protLayerId;

  /* Lock to make sure, other transportlayers do not connect at same time */
  SchM_Enter_Xcp_DaqRam();

  /* look for free protocol layer */
  for (protLayerId = 0; protLayerId < XCP_PL_IDS; protLayerId++)
  {
    if ( (  (XCP_ACTIVE_TL_ID(protLayerId) == 0xFF) /* free */
         || (XCP_ACTIVE_TL_ID(protLayerId) == XcpTransportLayerId) /* already connected to this TL */
       )
       && (Xcp_NoInit[protLayerId].Session.XcpState_en != XCP_STATE_DISCONNECTING) /* and XCP is not disconnecting currently */
       )
    {
      /* protocol layer found */
      /* save transport layer id in protocol layer */
      XCP_ACTIVE_TL_ID(protLayerId) = XcpTransportLayerId;
      /* save protocol layer id in lookup table */
      Xcp_GlobalNoInit.Tl2PlRef_au8[XcpTransportLayerId] = protLayerId;
      /* protocol layer is reserved, release lock now */
      SchM_Exit_Xcp_DaqRam();
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
      Xcp_InitDaqConfig(protLayerId);
#endif
      /* save TransportLayerId and transport layer specific parameters */
      Xcp_NoInit[protLayerId].Session.MaxCto_u8 = Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].MaxCto_u8;
      Xcp_NoInit[protLayerId].Session.MaxDto_u16 = Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].MaxDto_u16;
      Xcp_NoInit[protLayerId].Session.MaxDto4Aligned_u16 = XCP_4BYTE_ALIGN(Xcp_NoInit[protLayerId].Session.MaxDto_u16);
#if (XCP_IDFIELD_OTHER_THAN_ABSOLUTE == STD_ON)
      Xcp_NoInit[protLayerId].Session.IdFieldType_en = Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].IdFieldType_en;
#endif
      /* Call connect function */
      Xcp_CmdConnect(XcpPacketPtr, protLayerId);
      break;
    }
  }

  /* if end of for loop is reached without break */
  if (protLayerId >= XCP_PL_IDS)
  {
    /* no available protocol layer found */
    SchM_Exit_Xcp_DaqRam();
    XCP_DET_REPORT_ERROR_NO_RET(XCP_RECEIVE_SID, XCP_E_ALREADY_CONNECTED);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


