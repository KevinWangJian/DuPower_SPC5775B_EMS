

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/

/************************** START CONST UNSPECIFIED ***********************************/
/* MAP CONST UNSPECIFIED VAR  */
#define XCP_START_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"

/** Table containing all commands and the functions that handle them */
static const Xcp_CmdTable_t  Xcp_CmdActiveTable_as[] =
{
  /* FF */  {XCP_CMD_CONNECT_PFCT                 , XCP_RESOURCE_NONE,    XCP_CMD_CONNECT_LENGTH                },
  /* FE */  {XCP_CMD_DISCONNECT_PFCT              , XCP_RESOURCE_NONE,    XCP_CMD_DISCONNECT_LENGTH             },
  /* FD */  {XCP_CMD_GET_STATUS_PFCT              , XCP_RESOURCE_NONE,    XCP_CMD_GET_STATUS_LENGTH             },
  /* FC */  {XCP_CMD_SYNCH_PFCT                   , XCP_RESOURCE_NONE,    XCP_CMD_SYNCH_LENGTH                  },
  /* FB */  {XCP_CMD_GET_COMM_MODE_INFO_PFCT      , XCP_RESOURCE_NONE,    XCP_CMD_GET_COMM_MODE_INFO_LENGTH     },
  /* FA */  {XCP_CMD_GET_ID_PFCT                  , XCP_RESOURCE_NONE,    XCP_CMD_GET_ID_LENGTH                 },
  /* F9 */  {XCP_CMD_SET_REQUEST_PFCT             , XCP_RESOURCE_NONE,    XCP_CMD_SET_REQUEST_LENGTH            },
  /* F8 */  {XCP_CMD_GET_SEED_PFCT                , XCP_RESOURCE_NONE,    XCP_CMD_GET_SEED_LENGTH               },
  /* F7 */  {XCP_CMD_UNLOCK_PFCT                  , XCP_RESOURCE_NONE,    XCP_CMD_UNLOCK_LENGTH_MIN             },
  /* F6 */  {XCP_CMD_SET_MTA_PFCT                 , XCP_RESOURCE_NONE,    XCP_CMD_SET_MTA_LENGTH                },
  /* F5 */  {XCP_CMD_UPLOAD_PFCT                  , XCP_RESOURCE_NONE,    XCP_CMD_UPLOAD_LENGTH                 },
  /* F4 */  {XCP_CMD_SHORT_UPLOAD_PFCT            , XCP_RESOURCE_NONE,    XCP_CMD_SHORT_UPLOAD_LENGTH           },
  /* F3 */  {XCP_CMD_BUILD_CHECKSUM_PFCT          , XCP_RESOURCE_NONE,    XCP_CMD_BUILD_CHECKSUM_LENGTH         },
  /* F2 */  {XCP_CMD_TRANSPORT_LAYER_CMD_PFCT     , XCP_RESOURCE_NONE,    XCP_CMD_TRANSPORT_LAYER_CMD_LENGTH_MIN},
  /* F1 */  {XCP_CMD_USER_CMD_PFCT                , XCP_RESOURCE_NONE,    XCP_CMD_USER_CMD_LENGTH_MIN           },
  /* F0 */  {XCP_CMD_DOWNLOAD_PFCT                , XCP_RESOURCE_CALPAG,  XCP_CMD_DOWNLOAD_LENGTH_MIN           },
  /* EF */  {XCP_CMD_DOWNLOAD_NEXT_PFCT           , XCP_RESOURCE_CALPAG,  XCP_CMD_DOWNLOAD_NEXT_LENGTH_MIN      },
  /* EE */  {XCP_CMD_DOWNLOAD_MAX_PFCT            , XCP_RESOURCE_CALPAG,  XCP_CMD_DOWNLOAD_MAX_LENGTH_MIN       },
  /* ED */  {XCP_CMD_SHORT_DOWNLOAD_PFCT          , XCP_RESOURCE_CALPAG,  XCP_CMD_SHORT_DOWNLOAD_LENGTH_MIN     },
  /* EC */  {XCP_CMD_MODIFY_BITS_PFCT             , XCP_RESOURCE_CALPAG,  XCP_CMD_MODIFY_BITS_LENGTH            },
  /* EB */  {XCP_CMD_SET_CAL_PAGE_PFCT            , XCP_RESOURCE_CALPAG,  XCP_CMD_SET_CAL_PAGE_LENGTH           },
  /* EA */  {XCP_CMD_GET_CAL_PAGE_PFCT            , XCP_RESOURCE_CALPAG,  XCP_CMD_GET_CAL_PAGE_LENGTH           },
  /* E9 */  {XCP_CMD_GET_PAG_PROCESSOR_INFO_PFCT  , XCP_RESOURCE_CALPAG,  XCP_CMD_GET_PAG_PROCESSOR_INFO_LENGTH },
  /* E8 */  {XCP_CMD_GET_SEGMENT_INFO_PFCT        , XCP_RESOURCE_CALPAG,  XCP_CMD_GET_SEGMENT_INFO_LENGTH       },
  /* E7 */  {XCP_CMD_GET_PAGE_INFO_PFCT           , XCP_RESOURCE_CALPAG,  XCP_CMD_GET_PAGE_INFO_LENGTH          },
  /* E6 */  {XCP_CMD_SET_SEGMENT_MODE_PFCT        , XCP_RESOURCE_CALPAG,  XCP_CMD_SET_SEGMENT_MODE_LENGTH       },
  /* E5 */  {XCP_CMD_GET_SEGMENT_MODE_PFCT        , XCP_RESOURCE_CALPAG,  XCP_CMD_GET_SEGMENT_MODE_LENGTH       },
  /* E4 */  {XCP_CMD_COPY_CAL_PAGE_PFCT           , XCP_RESOURCE_CALPAG,  XCP_CMD_COPY_CAL_PAGE_LENGTH          },
  /* E3 */  {XCP_CMD_CLEAR_DAQ_LIST_PFCT          , XCP_RESOURCE_DAQ,     XCP_CMD_CLEAR_DAQ_LIST_LENGTH         },
  /* E2 */  {XCP_CMD_SET_DAQ_PTR_PFCT             , XCP_RESOURCE_DAQ,     XCP_CMD_SET_DAQ_PTR_LENGTH            },
  /* E1 */  {XCP_CMD_WRITE_DAQ_PFCT               , XCP_RESOURCE_DAQ,     XCP_CMD_WRITE_DAQ_LENGTH              },
  /* E0 */  {XCP_CMD_SET_DAQ_LIST_MODE_PFCT       , XCP_RESOURCE_DAQ,     XCP_CMD_SET_DAQ_LIST_MODE_LENGTH      },
  /* DF */  {XCP_CMD_GET_DAQ_LIST_MODE_PFCT       , XCP_RESOURCE_DAQ,     XCP_CMD_GET_DAQ_LIST_MODE_LENGTH      },
  /* DE */  {XCP_CMD_START_STOP_DAQ_LIST_PFCT     , XCP_RESOURCE_DAQ,     XCP_CMD_START_STOP_DAQ_LIST_LENGTH    },
  /* DD */  {XCP_CMD_START_STOP_SYNCH_PFCT        , XCP_RESOURCE_DAQ,     XCP_CMD_START_STOP_SYNCH_LENGTH       },
  /* DC */  {XCP_CMD_GET_DAQ_CLOCK_PFCT           , XCP_RESOURCE_DAQ,     XCP_CMD_GET_DAQ_CLOCK_LENGTH          },
  /* DB */  {XCP_CMD_READ_DAQ_PFCT                , XCP_RESOURCE_DAQ,     XCP_CMD_READ_DAQ_LENGTH               },
  /* DA */  {XCP_CMD_GET_DAQ_PROCESSOR_INFO_PFCT  , XCP_RESOURCE_DAQ,     XCP_CMD_GET_DAQ_PROCESSOR_INFO_LENGTH },
  /* D9 */  {XCP_CMD_GET_DAQ_RESOLUTION_INFO_PFCT , XCP_RESOURCE_DAQ,     XCP_CMD_GET_DAQ_RESOLUTION_INFO_LENGTH},
  /* D8 */  {XCP_CMD_GET_DAQ_LIST_INFO_PFCT       , XCP_RESOURCE_DAQ,     XCP_CMD_GET_DAQ_LIST_INFO_LENGTH      },
  /* D7 */  {XCP_CMD_GET_DAQ_EVENT_INFO_PFCT      , XCP_RESOURCE_DAQ,     XCP_CMD_GET_DAQ_EVENT_INFO_LENGTH     },
  /* D6 */  {XCP_CMD_FREE_DAQ_PFCT                , XCP_RESOURCE_DAQ,     XCP_CMD_FREE_DAQ_LENGTH               },
  /* D5 */  {XCP_CMD_ALLOC_DAQ_PFCT               , XCP_RESOURCE_DAQ,     XCP_CMD_ALLOC_DAQ_LENGTH              },
  /* D4 */  {XCP_CMD_ALLOC_ODT_PFCT               , XCP_RESOURCE_DAQ,     XCP_CMD_ALLOC_ODT_LENGTH              },
  /* D3 */  {XCP_CMD_ALLOC_ODT_ENTRY_PFCT         , XCP_RESOURCE_DAQ,     XCP_CMD_ALLOC_ODT_ENTRY_LENGTH        },
/* Programming commands */
  /* D2 */  {XCP_CMD_PROGRAM_START_PFCT           , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_START_LENGTH          },
  /* D1 */  {XCP_CMD_PROGRAM_CLEAR_PFCT           , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_CLEAR_LENGTH          },
  /* D0 */  {XCP_CMD_PROGRAM_PFCT                 , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_LENGTH_MIN            },
  /* CF */  {XCP_CMD_PROGRAM_RESET_PFCT           , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_RESET_LENGTH          },
  /* CE */  {XCP_CMD_GET_PGM_PROCESSOR_INFO_PFCT  , XCP_RESOURCE_PGM,     XCP_CMD_PGM_PROCESSOR_INFO_LENGTH     },
  /* CD */  {XCP_CMD_GET_SECTOR_INFO_PFCT         , XCP_RESOURCE_PGM,     XCP_CMD_GET_SECTOR_INFO_LENGTH        },
  /* CC */  {XCP_CMD_PROGRAM_PREPARE_PFCT         , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_PREPARE_LENGTH        },
  /* CB */  {XCP_CMD_PROGRAM_FORMAT_PFCT          , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_FORMAT_LENGTH         },
  /* CA */  {XCP_CMD_PROGRAM_NEXT_PFCT            , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_NEXT_LENGTH_MIN       },
  /* C9 */  {XCP_CMD_PROGRAM_MAX_PFCT             , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_MAX_LENGTH_MIN        },
  /* C8 */  {XCP_CMD_PROGRAM_VERIFY_PFCT          , XCP_RESOURCE_PGM,     XCP_CMD_PROGRAM_VERIFY_LENGTH         },
  /* C7 */  {XCP_CMD_WRITE_DAQ_MULTIPLE_PFCT      , XCP_RESOURCE_DAQ,     XCP_CMD_WRITE_DAQ_MULTIPLE_LENGTH_MIN },
/* Empty commands */
  /* C6 */  {(Xcp_CmdFunctionPtr)(NULL_PTR)       , XCP_RESOURCE_NONE,    0                                     },
  /* C5 */  {(Xcp_CmdFunctionPtr)(NULL_PTR)       , XCP_RESOURCE_NONE,    0                                     },
  /* C4 */  {(Xcp_CmdFunctionPtr)(NULL_PTR)       , XCP_RESOURCE_NONE,    0                                     },
  /* C3 */  {(Xcp_CmdFunctionPtr)(NULL_PTR)       , XCP_RESOURCE_NONE,    0                                     },
  /* C2 */  {(Xcp_CmdFunctionPtr)(NULL_PTR)       , XCP_RESOURCE_NONE,    0                                     },
  /* C1 */  {(Xcp_CmdFunctionPtr)(NULL_PTR)       , XCP_RESOURCE_NONE,    0                                     },
  /* C0 */  {(Xcp_CmdFunctionPtr)(NULL_PTR)       , XCP_RESOURCE_NONE,    0                                     },
};

#define XCP_STOP_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"
/************************** END CONST UNSPECIFIED ***********************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles the several command requests
\param[in]  XcpPacketPtr  pointer to the received XcpPacket
\param[in]  protLayerId   protocol layer id
\return     
***************************************************************************************************/
void Xcp_ReceiveCommand(const PduInfoType* XcpPacketPtr, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint8 commandIndex_u8;

  commandIndex_u8 = (uint8) (0xFFu - XcpPacketPtr->SduDataPtr[0]); /* PID was checked to be >= 0xC0 in the function calling this function */

  /* Connected state is ensured in Xcp_Receive */
  /* Check if function pointer is set and required resource is enabled */
  if (  ( Xcp_CmdActiveTable_as[commandIndex_u8].Command_pfct == NULL_PTR )
     || ((Xcp_CmdActiveTable_as[commandIndex_u8].ResourceMask_u8 & (uint8) (~Xcp_GlobalNoInit.EnabledResources_u8)) != 0)
     )
  {
    /* Error packet code: 0x20 */
    Xcp_SendErrRes(XCP_ERR_CMD_UNKNOWN, protLayerId);
  }
#if(XCP_SEED_AND_KEY == STD_ON)
  else if ((Xcp_CmdActiveTable_as[commandIndex_u8].ResourceMask_u8 & Xcp_NoInit[protLayerId].Session.ResourceProtStatus_u8) != 0)
  {
    /* Command is locked */
    /* Send Error packet code 0x25 */
    Xcp_SendErrRes(XCP_ERR_ACCESS_LOCKED, protLayerId);
  }
#endif
  else if (XcpPacketPtr->SduLength < Xcp_CmdActiveTable_as[commandIndex_u8].CmdMinLength_u8)     /* Check packet length */
  {
    /* Send Command Syntax error */
    Xcp_SendErrRes(XCP_ERR_CMD_SYNTAX, protLayerId);
  }
  else /* all checks have been passed */
  {
#if (XCP_RESUME_MODE == STD_ON)
    /* If the slave is in RESUME mode it should only accept the CONNECT command */
    if ( (Xcp_NoInit[protLayerId].Session.XcpState_en != XCP_STATE_RESUME)
      || ((Xcp_NoInit[protLayerId].Session.XcpState_en == XCP_STATE_RESUME) && (XcpPacketPtr->SduDataPtr[0] == XCP_CMD_CONNECT_ID)) )
#endif
    {
      /* Call the command */
      Xcp_CmdActiveTable_as[commandIndex_u8].Command_pfct(XcpPacketPtr, protLayerId);
    }
  }

#if (XCP_CMD_RECEIVED_NOTIFICATION == STD_ON)
  /* Notification for every received command */
  XcpAppl_CmdReceived(XcpPacketPtr->SduDataPtr, (uint8)XCP_MIN(XcpPacketPtr->SduLength,255u), protLayerId);
#endif

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



