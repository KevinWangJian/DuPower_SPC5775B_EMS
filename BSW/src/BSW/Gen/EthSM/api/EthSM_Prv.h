

#ifndef ETHSM_PRV_H_
#define ETHSM_PRV_H_

/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/
#if (ETHSM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (ETHSM_DEV_ERROR_DETECT == STD_ON) */

/*
****************************************************************************************************
*                                   Defines
****************************************************************************************************
*/

#define ETHSM_E_INVALID_NETWORK_MODE		0x1U	/* Invalid communication mode requested */
#define ETHSM_E_UNINIT						0x2U	/* Module was not initialized */
#define ETHSM_E_PARAM_POINTER				0x3U	/* Invalid pointer in parameter list */
#define ETHSM_E_INVALID_NETWORK_HANDLE		0x4U	/* Invalid parameter in parameter list */
#define ETHSM_E_INVALID_TCPIP_MODE          0x5U    /* Invalid parameter in parameter list */
													/* In SWS macro name is in mixed case( ETHSM_E_INVALID_TcpIpMode ) */
#define ETHSM_E_INVALID_TRCV_LINK_STATE     0x6U    /* Invalid parameter in parameter list */
#define ETHSM_E_PARAM_CONTROLLER            0x7U    /* Invalid parameter in parameter list */

#define ETHSM_SID_ETHSM_INIT				0x1U
#define ETHSM_SID_ETHSM_GETVERSIONINFO		0x2U
#define ETHSM_SID_ETHSM_REQUESTCOMMODE		0x3U
#define	ETHSM_SID_ETHSM_GETCURRENTCOMMODE	0x4U
#define ETHSM_SID_ETHSM_MAINFUNCTION		0x5U
#define ETHSM_SID_ETHSM_TRCVLINKSTATECHG	0x6U
#define ETHSM_SID_ETHSM_TCPIPMODEINDICATION	0x8U
#define ETHSM_SID_ETHSM_CTRLMODEINDICATION  0x9U


/*************************MACRO Definations for DET Error Handling*********************************/
#if (ETHSM_DEV_ERROR_DETECT  == STD_ON)

/* DET For functions with return type as 'void' */
#define ETHSM_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)                                                \
                               if(CONDITION)                                                              \
                               {                                                                          \
                                   (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, API, ERROR); \
                                   return;                                                                \
                               }

/* DET For functions with return type as 'Std_ReturnType' */
#define ETHSM_REPORT_ERROR_RET_VALUE(CONDITION, API, ERROR, RETVAL)                                       \
                               if(CONDITION)                                                              \
                                {                                                                         \
                                   (void)Det_ReportError(ETHSM_MODULE_ID, ETHSM_INSTANCE_ID, API, ERROR); \
                                   return ( RETVAL );                                                     \
                                }
#else

/* No DET Code Expansion if Development Detection Error is OFF */

#define ETHSM_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)

#define ETHSM_REPORT_ERROR_RET_VALUE(CONDITION, API, ERROR, RETVAL)

#endif

/*************************MACRO Definations for DET Error Handling*********************************/


#endif /* ETHSM_PRV_H_ */
