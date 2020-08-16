
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
#if (XCP_CMD_USER_CMD_AVAILABLE == STD_ON)

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Function for user-defined command
\param[in]  XcpCmdPtr         Command pointer
\param[in]  CmdLength         Command Length
\param[out] XcpResPtr         Response pointer
\param[out] ResLength         Response Length
\param[in]  ProtocolLayerId   protocol layer id
\retval     XCP_NO_ERROR          success \n
\retval     XCP_ERR_CMD_UNKNOWN   Command not supported
\retval     XCP_ERR_CMD_SYNTAX    Command syntax invalid
\retval     XCP_ERR_OUT_OF_RANGE  Command parameter(s) out of range
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_UserCmd(const uint8* XcpCmdPtr, uint8 CmdLength, uint8* XcpResPtr ,uint8* ResLength, uint8 ProtocolLayerId)
{
    /*-----------------------------------------------------------------*/
    /* This function is project specific and shall be totally reworked */
    /*-----------------------------------------------------------------*/

    /* Local variables */
    Xcp_ErrorCode Error;

    /* Command syntax shall be validated by integrator, if not valid ERR_CMD_SYNTAX shall be assigned to Error */

    /* Example for Response data and length */
    /* MR12 RULE 11.5 VIOLATION: The calling layers ensure 4-Byte-Alignment. This cast allows easier (= safer) access to the data in the buffer */
    Xcp_ResUserCmd_t* ResPtr = (Xcp_ResUserCmd_t*) (void*) XcpResPtr;

    ResPtr->PacketId_u8 = 0xFF;
    *ResLength = 1;

    /* Remove when parameter used */
    XCP_PARAM_UNUSED(XcpCmdPtr);
    XCP_PARAM_UNUSED(CmdLength);
    XCP_PARAM_UNUSED(ProtocolLayerId);

    /* Initial values */
    Error = XCP_NO_ERROR;

    /* return Error Code */
    return(Error);
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

#endif


