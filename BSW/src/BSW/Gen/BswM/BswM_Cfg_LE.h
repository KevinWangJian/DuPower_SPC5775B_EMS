#ifndef BSWM_CFG_LE_H
#define BSWM_CFG_LE_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "Std_Types.h"

#include "Rte_Main.h"

#include "CanSM.h"

#include "CanIf.h"

#include "ComM.h"

#include "Com.h"

#include "PduR.h"

#include "EcuM.h"

#include "Integration.h"

#include "IpduM.h"

#include "Xcp.h"

#include "WdgM.h"

#include "McuFunc.h"

#include "Fee.h"

#include "NvM.h"

#include "Dcm.h"

#include "Dem.h"

#include "FiM.h"

#include "CanTp.h"

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */

/******************************     BswM Logical Expression    *****************************************/

#define BSWMLOGEXP_BSWM_LE_DCM_DISABLE_RX_TX_NORMAL  \
                    ( DCM_DISABLE_RX_TX_NORMAL  ==  BswM_Cfg_DcmComModeRequestModeInfo_ast[BSWM_IDX_BSWM_MRP_DCM_COM].dataMode_u8 )

#define BSWMLOGEXP_BSWM_LE_DCM_ENABLE_RX_DISABLE_TX_NORMAL  \
                    ( DCM_ENABLE_RX_DISABLE_TX_NORM  ==  BswM_Cfg_DcmComModeRequestModeInfo_ast[BSWM_IDX_BSWM_MRP_DCM_COM].dataMode_u8 )

#define BSWMLOGEXP_BSWM_LE_DCM_ENABLE_RX_TX_NORMAL  \
                    ( DCM_ENABLE_RX_TX_NORM  ==  BswM_Cfg_DcmComModeRequestModeInfo_ast[BSWM_IDX_BSWM_MRP_DCM_COM].dataMode_u8 )

#define BSWMLOGEXP_BSWM_LE_POSTRUN  \
                    ( RTE_MODE_MDG_ECUM_STATE_ECUM_STATE_POST_RUN  ==  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_SWCMODEREQUEST].dataMode_u16 )

#define BSWMLOGEXP_BSWM_LE_PREPSHUTDOWN  \
                     ( ( RTE_MODE_MDG_ECUM_STATE_ECUM_STATE_PREP_SHUTDOWN  ==  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].dataMode_u16 )  \
                     && ( COMM_NO_COMMUNICATION  ==  BswM_Cfg_ComMIndicationModeInfo_ast[BSWM_IDX_BSWM_MRP_COMM_CAN1].dataMode_u8 ) )

#define BSWMLOGEXP_BSWM_LE_RUN  \
                    ( RTE_MODE_MDG_ECUM_STATE_ECUM_STATE_RUN  ==  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].dataMode_u16 )

#define BSWMLOGEXP_BSWM_LE_SHUTDOWN  \
                     ( ( RTE_MODE_MDG_ECUM_STATE_ECUM_STATE_SHUTDOWN  ==  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].dataMode_u16 )  \
                     && ( NVM_REQ_PENDING  !=  BswM_Cfg_NvMJobModeInfo_ast[BSWM_IDX_BSWM_MRP_NVMWRITEALLCOMPLETE].dataMode_en ) )

#define BSWMLOGEXP_BSWM_LE_STARTUPONE  \
                    ( RTE_MODE_MDG_ECUM_STATE_ECUM_STATE_STARTUP_ONE  ==  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].dataMode_u16 )

#define BSWMLOGEXP_BSWM_LE_STARTUPTWO  \
                     ( ( RTE_MODE_MDG_ECUM_STATE_ECUM_STATE_STARTUP_TWO  ==  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].dataMode_u16 )  \
                     && ( NVM_REQ_PENDING  !=  BswM_Cfg_NvMJobModeInfo_ast[BSWM_IDX_BSWM_MRP_NVMREADALLCOMPLETE].dataMode_en ) )

/******************   Macros for checking whether the ModeValues are defined   ******************************/

#define BSWMMODEVALUE_BSWM_LE_DCM_DISABLE_RX_TX_NORMAL  \
        ( FALSE  !=  BswM_Cfg_DcmComModeRequestModeInfo_ast[BSWM_IDX_BSWM_MRP_DCM_COM].isValidModePresent_b )

#define BSWMMODEVALUE_BSWM_LE_DCM_ENABLE_RX_DISABLE_TX_NORMAL  \
        ( FALSE  !=  BswM_Cfg_DcmComModeRequestModeInfo_ast[BSWM_IDX_BSWM_MRP_DCM_COM].isValidModePresent_b )

#define BSWMMODEVALUE_BSWM_LE_DCM_ENABLE_RX_TX_NORMAL  \
        ( FALSE  !=  BswM_Cfg_DcmComModeRequestModeInfo_ast[BSWM_IDX_BSWM_MRP_DCM_COM].isValidModePresent_b )

#define BSWMMODEVALUE_BSWM_LE_POSTRUN  \
        ( FALSE  !=  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_SWCMODEREQUEST].isValidModePresent_b )

#define BSWMMODEVALUE_BSWM_LE_PREPSHUTDOWN  \
        ( ( FALSE  !=  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].isValidModePresent_b )  \
         && ( FALSE  !=  BswM_Cfg_ComMIndicationModeInfo_ast[BSWM_IDX_BSWM_MRP_COMM_CAN1].isValidModePresent_b ) )

#define BSWMMODEVALUE_BSWM_LE_RUN  \
        ( FALSE  !=  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].isValidModePresent_b )

#define BSWMMODEVALUE_BSWM_LE_SHUTDOWN  \
        ( ( FALSE  !=  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].isValidModePresent_b )  \
         && ( FALSE  !=  BswM_Cfg_NvMJobModeInfo_ast[BSWM_IDX_BSWM_MRP_NVMWRITEALLCOMPLETE].isValidModePresent_b ) )

#define BSWMMODEVALUE_BSWM_LE_STARTUPONE  \
        ( FALSE  !=  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].isValidModePresent_b )

#define BSWMMODEVALUE_BSWM_LE_STARTUPTWO  \
        ( ( FALSE  !=  BswM_Cfg_GenericReqModeInfo_ast[BSWM_IDX_BSWM_MRP_BSWM_MDG].isValidModePresent_b )  \
         && ( FALSE  !=  BswM_Cfg_NvMJobModeInfo_ast[BSWM_IDX_BSWM_MRP_NVMREADALLCOMPLETE].isValidModePresent_b ) )

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
 */

/********************************  LogicalExpressionEvaluateFunctions  ***************************************/
#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_DCM_DISABLE_RX_TX_NORMAL (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);
extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_DCM_ENABLE_RX_DISABLE_TX_NORMAL (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);
extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_DCM_ENABLE_RX_TX_NORMAL (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);
extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_PostRun (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);
extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_PrepShutdown (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);
extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_Run (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);
extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_Shutdown (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);
extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_StartupOne (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);
extern FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_StartupTwo (P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb, P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif  /* BSWM_CFG_LE_H */
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
