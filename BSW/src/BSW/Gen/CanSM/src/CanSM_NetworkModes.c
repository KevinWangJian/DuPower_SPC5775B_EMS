
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"
/**
***************************************************************************************************
** Function Name        : CanSM_NetworkModeTrans
**
** Description          : This function Controls the Network Mode state Machine. Whenever a valid Network Mode Transition
**                        is requested, this function Valiadates the request and calls the corresponding function for
**                        actual Network Mode Transition.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant (only for different network handles)
**
** Input Parameters     : network: Handle of destined communication network for request
**                        ComM_Mode : Requested communication mode
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_NetworkModeTrans( VAR(NetworkHandleType, AUTOMATIC) network,VAR(ComM_ModeType, AUTOMATIC) ComM_Mode )
{

    /*Local variabe to hold the BSWM mode*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
	
    /*To keep a track of current network mode*/
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;

    /*Make a local copy of current network mode */
    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

    /*If Current Network State in CANSM_BSM_S_PRE_FULLCOM and Requested state is FULL_COM*/
    if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (ComM_Mode == COMM_FULL_COMMUNICATION ))
        {
        if(CanSM_PreFullCom_Substates_en[network]== CANSM_PRE_FULLCOM_DEFAULT)
        {
            CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_TRCV_NORMAL;
        }
            CanSM_NO2FULL_COM(network);
        }
    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_FULLCOM) && ((ComM_Mode == COMM_SILENT_COMMUNICATION )))
        {
            /* Function Call for FULL COM to SILENT COM Transition*/
            CanSM_FULL2SILENT_COM(network);

        }

    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_SILENTCOM) && ((ComM_Mode == COMM_FULL_COMMUNICATION )) )
        {
            if(CanSM_PreFullCom_Substates_en[network]== CANSM_PRE_FULLCOM_DEFAULT)
            {
                CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_TRCV_NORMAL;
            }
            /* Function Call for SILENT COM to FULL COM Transition*/
            CanSM_SILENT2FULL_COM(network);

        }
    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_FULLCOM) && ((ComM_Mode == COMM_NO_COMMUNICATION )))
        {
            CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_PRE_NOCOM;

            /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION*/
            CanSM_BswM_Mode_en=CANSM_BSWM_NO_COMMUNICATION;
            /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
            BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);
            /*When transceiver is configured, also check if PN is supported*/
            if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
             {
               #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
               if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].TrcvPnConfig_b == TRUE) /*Pn checking includes that transceiver is also configured */
                 {
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                   {
                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                   }
                   CanSM_DeInitPnSupported(network);
                 }
               else
                 {
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                       {
                           CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                       }
                   CanSM_DeInitPnNotSupported(network);
                 }
               #else
               if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                   {
                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                   }
               CanSM_DeInitPnNotSupported(network);
               #endif
             }
           else
             {
               if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                   {
                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                   }
               CanSM_DeInitPnNotSupported(network);
             }

        }

    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_SILENTCOM) && ((ComM_Mode == COMM_NO_COMMUNICATION )) )
        {
            CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_PRE_NOCOM;

            /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION*/
            CanSM_BswM_Mode_en=CANSM_BSWM_NO_COMMUNICATION;
            /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
            BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);
            /*When transceiver is configured, also check if PN is supported*/
            if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
             {
               #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
               if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].TrcvPnConfig_b == TRUE) /*Pn checking includes that transceiver is also configured */
                 {
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                   {
                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                   }
                   CanSM_DeInitPnSupported(network);
                 }
               else
                 {
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                       {
                           CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                       }
                   CanSM_DeInitPnNotSupported(network);
                 }
               #else
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                       {
                           CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                       }
                   CanSM_DeInitPnNotSupported(network);
               #endif
             }
           else
             {
               if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
               {
                   CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
               }
               CanSM_DeInitPnNotSupported(network);
             }

        }

    else if ((CanSM_CurrNw_Mode_en[network] == CANSM_BSM_S_PRE_NOCOM)&&(ComM_Mode == COMM_NO_COMMUNICATION))
    {
     /*When transceiver is configured, also check if PN is supported*/
     if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
      {
        #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
        if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].TrcvPnConfig_b == TRUE) /*Pn checking includes that transceiver is also configured */
          {
            if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
            {
                CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
            }
            CanSM_DeInitPnSupported(network);
          }
        else
          {
            if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
            {
                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
            }
            CanSM_DeInitPnNotSupported(network);
          }
        #else
        if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
        {
            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
        }
        CanSM_DeInitPnNotSupported(network);
        #endif
      }
    else
      {
        if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
        {
            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
        }
        CanSM_DeInitPnNotSupported(network);
      }
    }
    else
    {
        /* Not a Valid Transition*/
    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_GetNetworkMode_Substate
**
** Service ID           : 0x11u
**
** Description          : This API provides the current Network Mode Substate of the given CAN Network
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant(only for other networks
**
** Input Parameters     : network - index of the Network Configuration structure
**                        NetworkMode_SubstatePtr - Data pointer to store the Current Network Mode Substate.
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : E_OK/E_NOT_OK

***************************************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetNetworkMode_Substate(VAR(NetworkHandleType, AUTOMATIC) network,
        P2VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC, CANSM_APPL_DATA) NetworkMode_SubstatePtr
        )
{
    /*To keep a track of Return value*/
    VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;

    CanSM_FuncVal_uo = E_NOT_OK;

    /* Get the CanSM Network Index value corresponding to the ComM channel Id received */
    network = CanSM_GetHandle(network);

    /* Report DET : Development Error Handling for CANSM is Uninitialized */
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_GETNETWORKMODESUBSTATE_SID),
                           ((uint8)CANSM_E_UNINIT))

    /* Report DET : Development Error for Invalid Network Handle */
    CANSM_REPORT_ERROR_NOK(((uint8)network >= (uint8)CANSM_NUM_CAN_NETWORKS),
                           ((uint8)CANSM_GETNETWORKMODESUBSTATE_SID),
                           ((uint8)CANSM_E_INVALID_NETWORK_HANDLE))

    /* Report DET : Development Error for Invalid data pointer */
    CANSM_REPORT_ERROR_NOK((NetworkMode_SubstatePtr == NULL_PTR),
                           ((uint8)CANSM_GETNETWORKMODESUBSTATE_SID),
                           ((uint8)CANSM_E_PARAM_POINTER))

    *NetworkMode_SubstatePtr = CanSM_CurrNw_Mode_en[network];

    CanSM_FuncVal_uo = E_OK;

    return (CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
