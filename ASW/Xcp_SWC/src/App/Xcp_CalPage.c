
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"
#include "Xcp_Integration.h"

typedef enum
{
    CalPage_Working = 0,
    CalPage_Reference
} CalPage_T;

/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

#if (XCP_CMD_SET_CAL_PAGE_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function sets active calibration page
\param[in]  Mode              mode given from the command (ECU, XCP, All)
\param[in]  SegNum            segment number
\param[in]  PageNum           calibration data page
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR                sucess
\retval     XCP_ERR_PAGE_NOT_VALID      Page not valid
\retval     XCP_ERR_SEGMENT_NOT_VALID   Segment not valid
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_SetCalPage(uint8 Mode, uint8 SegNum, uint8 PageNum, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(Mode);
  XCP_PARAM_UNUSED(SegNum);
  XCP_PARAM_UNUSED(PageNum);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Initial values */
  Error = XCP_NO_ERROR;

  /* return Error Code */
  return(Error);
}
#endif


#if (XCP_CMD_GET_CAL_PAGE_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function gets active calibration page
\param[in]  Mode              mode given from the command (ECU, XCP, All)
\param[in]  SegNum            segment number
\param[out] PageNum           calibration data page
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR                sucess
\retval     XCP_ERR_SEGMENT_NOT_VALID   Segment not valid
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_GetCalPage(uint8 Mode, uint8 SegNum, uint8* PageNum, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(Mode);
  XCP_PARAM_UNUSED(SegNum);
  //XCP_PARAM_UNUSED(PageNum);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Initial values */
  Error = XCP_NO_ERROR;

  /* Get calibration page here... */
  *PageNum = CalPage_Working;

  /* Return currently active calibration page  */
  return(Error);
}
#endif


#if (XCP_CMD_COPY_CAL_PAGE_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function copies calibration page
\param[in]  SegNumSrc         Source Segment
\param[in]  PageNumSrc        Source Page
\param[in]  SegNumDst         Destination Segment
\param[in]  PageNumDst        Destination Page
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR                sucess
\retval     XCP_ERR_PAGE_NOT_VALID      Page not valid
\retval     XCP_ERR_SEGMENT_NOT_VALID   Segment not valid
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_CopyCalPage(uint8 SegNumSrc, uint8 PageNumSrc, uint8 SegNumDst, uint8 PageNumDst, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(SegNumSrc);
  XCP_PARAM_UNUSED(PageNumSrc);
  XCP_PARAM_UNUSED(SegNumDst);
  XCP_PARAM_UNUSED(PageNumDst);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Initial values */
  Error = XCP_NO_ERROR;

  /* Copy calibration page here... */

  /* return Error Code */
  return(Error);
}
#endif


# if (XCP_CMD_GET_PAG_PROCESSOR_INFO_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function to get the MAX_SEGMENT number as general information on paging.
\param[in]  ProtocolLayerId   Protocol Layer Id
\param[out] MaxSegment        Maximum segment number
\retval     XCP_NO_ERROR                sucess
\retval     XCP_ERR_CMD_UNKNOWN         Command not supported
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_GetPagProcessorInfo(uint8* MaxSegment, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(MaxSegment);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Initial values */
  Error = XCP_NO_ERROR;

  /* Set MaxSegment here... */

  /* return Error Code */
  return(Error);
}
#endif


# if (XCP_CMD_GET_SEGMENT_INFO_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function prepares response packet based on Mode for command GET_SEGMENT_INFO
\param[in]  XcpCmdPtr         Command pointer
\param[out] XcpResPtr         Response pointer
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR                sucess
\retval     XCP_ERR_CMD_UNKNOWN         Command not supported
\retval     XCP_ERR_OUT_OF_RANGE        Mode or SegmentInfo or MappingIndex are out of range
\retval     XCP_ERR_SEGMENT_NOT_VALID   Segment not valid
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_GetSegmentInfo(const uint8* XcpCmdPtr, uint8* XcpResPtr, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be reworked         */
  /*-----------------------------------------------------------------*/

  /* MR12 RULE 11.5 VIOLATION: The calling layers ensure 4-Byte-Alignment. This cast allows easier (= safer) access to the data in the buffer */
  const Xcp_CmdGetSegmentInfo_t* const CmdPtr = (const Xcp_CmdGetSegmentInfo_t*) (const void*) XcpCmdPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* CmdPtr shall be used to know the SegmentNum_u8, SegmentInfo_u8, MappingIndex_u8 requested by master */

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Initial values */
  Error = XCP_NO_ERROR;

  /* SegmentNum_u8 shall be validate here by integrator, if it is invalid XCP_ERR_SEGMENT_NOT_VALID shall be assigned to Error */

  if (Error == XCP_NO_ERROR)
  {
    switch (CmdPtr->Mode_u8)
    {
      case 0u:
      {
        /* MR12 RULE 11.5 VIOLATION: The calling layers ensure 4-Byte-Alignment. This cast allows easier (= safer) access to the data in the buffer */
        Xcp_ResGetSegmentInfo_Mode0_t* Mode0_ResPtr = (Xcp_ResGetSegmentInfo_Mode0_t*) (void*) XcpResPtr;

        /* Prepare response packet for MODE0 */
        Mode0_ResPtr->PacketId_u8           = XCP_PACKET_ID_RES;
        Mode0_ResPtr->Reserved_u8           = 0u;
        Mode0_ResPtr->Reserved_u16          = 0u;
        /* BasicInfo_u32 shall be updated below based on SegmentInfo by integrator */
        Mode0_ResPtr->BasicInfo_u32         = 0u;
        break;
      }

      case 1u:
      {
        /* MR12 RULE 11.5 VIOLATION: The calling layers ensure 4-Byte-Alignment. This cast allows easier (= safer) access to the data in the buffer */
        Xcp_ResGetSegmentInfo_Mode1_t* Mode1_ResPtr = (Xcp_ResGetSegmentInfo_Mode1_t*) (void*) XcpResPtr;

        /* Prepare response packet for MODE1 */
        Mode1_ResPtr->PacketId_u8           = XCP_PACKET_ID_RES;
        /* MaxPages_u8, Address AddrExtension_u8, Max MaxMapping_u8, CompressionMethod_u8 Method, EncryptionMethod_u8 Method shall be updated below by integrator */
        Mode1_ResPtr->MaxPages_u8           = 0u;
        Mode1_ResPtr->AddrExtension_u8      = 0u;
        Mode1_ResPtr->MaxMapping_u8         = 0u;
        Mode1_ResPtr->CompressionMethod_u8  = 0u;
        Mode1_ResPtr->EncryptionMethod_u8   = 0u;
        break;
      }

      case 2u:
      {
        /* MR12 RULE 11.5 VIOLATION: The calling layers ensure 4-Byte-Alignment. This cast allows easier (= safer) access to the data in the buffer */
        Xcp_ResGetSegmentInfo_Mode2_t* Mode2_ResPtr = (Xcp_ResGetSegmentInfo_Mode2_t*) (void*) XcpResPtr;

        /* Prepare response packet for MODE2*/
        Mode2_ResPtr->PacketId_u8           = XCP_PACKET_ID_RES;
        Mode2_ResPtr->Reserved_u8           = 0u;
        Mode2_ResPtr->Reserved_u16          = 0u;
        /* MappingInfo_u32 shall be updated below based on MapIndex by integrator */
        Mode2_ResPtr->MappingInfo_u32       = 0u;
        break;
      }

      default:
      {
        /* Mode is out or range */
        Error = XCP_ERR_OUT_OF_RANGE;
        break;
      }
    }
  }
  return (Error);
}
#endif


#if (XCP_CMD_GET_PAGE_INFO_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function returns page information
\param[in]  SegmentNumber     Segment Number
\param[in]  PageNumber        Page Number
\param[out] PageProperties    Page Properties
\param[out] InitSegment       Init Segment
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR                success
\retval     XCP_ERR_PAGE_NOT_VALID      Page not valid
\retval     XCP_ERR_SEGMENT_NOT_VALID   Segment not valid
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_GetPageInfo(uint8 SegmentNumber, uint8 PageNumber, uint8* PageProperties, uint8* InitSegment, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(SegmentNumber);
  XCP_PARAM_UNUSED(PageNumber);
  XCP_PARAM_UNUSED(PageProperties);
  XCP_PARAM_UNUSED(InitSegment);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Initial values */
  Error = XCP_NO_ERROR;

  /* Set PageProperties and InitSegment here... */

  /* return Error Code */
  return(Error);
}
#endif


/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"


