
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/
#if (XCP_CMD_GET_ID_AVAILABLE == STD_ON)
static uint8 Xcp_SlaveIdType0_au8[] = {0x54,0x65,0x78,0x74}; /* Text */ /* Length = 4 */
static uint8 Xcp_SlaveIdType1_au8[] = {0x41,0x32,0x4C,0x5F,0x66,0x69,0x6C,0x65,0x6E,0x61,0x6D,0x65,0x5F,0x77,0x6F,0x5F,0x70,0x61,0x74,0x68}; /* A2L_filename_wo_path */ /* Length = 20 */
#endif /* (XCP_CMD_GET_ID_AVAILABLE == STD_ON) */


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

#if (XCP_CMD_GET_ID_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function is called when identification type 0 to 3, 128 to 255 is requested by master.
\param[in]  IdType            Identification Type from CMD [0..3, 128..255]
\param[out] Address           Address where identification shall be stored
\param[in]  ProtocolLayerId   Protocol layer id
\return     Length of identification
\retval     0  Id is not supported
***************************************************************************************************/
uint32 XcpAppl_GetIdSlave(uint8 IdType, Xcp_AdrPtr* Address, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /* As an example identification type 0 and 1 is implemented        */
  /*-----------------------------------------------------------------*/

  uint32 IdLength = 0;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Check if not null pointer */
  if(Address != NULL_PTR)
  {
    if(IdType == 0)
    {
      /* Set type0 address and length */
      *Address = Xcp_SlaveIdType0_au8;
      IdLength = sizeof(Xcp_SlaveIdType0_au8);
    }
    else if(IdType == 1u)
    {
      /* Set type1 address and length */
      *Address = Xcp_SlaveIdType1_au8;
      IdLength = sizeof(Xcp_SlaveIdType1_au8);
    }
    else
    {
      /* IdLength = 0 for not supported Ids already set */
    }
  }
  return IdLength;
}
#endif /* (XCP_CMD_GET_ID_AVAILABLE == STD_ON) */

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"



