
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "CanSM_Priv.h"

/*
 ***************************************************************************************************
 * Global Variables/Arrays
 ***************************************************************************************************
 */

/*Timer Configuration*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_TimerConfig_tst, CANSM_VAR)  CanSM_TimerConfig_ast[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*CanSM initialization indication flag*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_Init_ab;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/* Current Network Mode State */
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_NetworkModeStateType_ten, CANSM_VAR) CanSM_CurrNw_Mode_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/* Current BOR State */
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_BusOffRecoveryStateType_ten, CANSM_VAR) CanSM_currBOR_State_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*Busoff counter*/
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
VAR(uint8, CANSM_VAR) CanSM_BusOff_Cntr_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

/*Bus-Off State Machine Mode - Enable Recovery or Disable Recovery*/
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
VAR(uint8, CANSM_VAR) CanSM_BORMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

/*To track Bus Off Indications for the network*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_BusOff_Indicated_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"


/* Mutex Support for CanSM*/
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
VAR(uint8, CANSM_VAR) CanSM_MutexMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

/*Requested ComM Mode */

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(ComM_ModeType, CANSM_VAR) CanSM_ReqComM_Mode_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*Requested Ecum Mode */
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_Wuvalidation_Start_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/* Pending BusOff Recovery ISR*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_BusOffISRPend_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

#if (CANSM_CHANGE_BAUDRATE_API == STD_ON)
/*To hold the recent baudrate of the network*/
#define CANSM_START_SEC_VAR_CLEARED_32
#include "CanSM_MemMap.h"
VAR(uint32, CANSM_VAR) CanSM_ChangeBaudRate_Value_au32[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_32
#include "CanSM_MemMap.h"

/*To keep track of the status returned by CanSM_CheckBaudrate(), for each network*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_CheckBR_Status_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
#endif


#if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
/*To keep track of the substates in Change Baudrate, for each network*/
VAR(CanSM_ChangeBR_Substates_ten, CANSM_VAR) CanSM_ChangeBR_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#endif

/*To keep track of the the Baudrate Config Id for each network*/
#if(CANSM_SET_BAUDRATE_API == STD_ON)
/*To hold the BaudrateConfigID*/
#define CANSM_START_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"
VAR(uint16, CANSM_VAR) CanSM_BaudRateConfigID_Value_au16[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"

#endif

/*To keep track of unsuccessful attempts for mode change request received for each network ie T_REPEAT_MAX counter*/
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
VAR(uint8, CANSM_VAR) CanSM_Num_Unsuccessful_ModeReq_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

/*To keep track of Transceiver mode indication received*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_Trcv_ModeInd_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/*To keep track of Controller mode indication received*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_Ctrl_ModeInd_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/*To keep track of the substates in Prepare to NOCOM for each network*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_PreNoCom_Substates_ten, CANSM_VAR) CanSM_PreNoCom_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*To keep track of the call backs checkwakeupflag() and clearwakeupflag() have happened or not . Nothing to do with any PN indications*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_PN_Substate_Ind_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/*Array to hold the last value notified to ComM_BusSM_ModeIndication()*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(ComM_ModeType, CANSM_VAR) CanSM_BusSMMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*To keep track of the substates in Prepare to FULL COM for each network*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_PreFullCom_Substates_ten, CANSM_VAR) CanSM_PreFullCom_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*To keep track of the substates in Wake Up Validation for each network*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_WakeUpValidation_Substates_ten, CANSM_VAR) CanSM_WakeUpValidation_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*To keep track of the substates in Tx Timeout exception, for each network*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_TxTimeoutException_Substates_ten, CANSM_VAR) CanSM_TxTimeoutexception_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/* Specifies in which time duration the CanSM module shall repeat mode change requests by using the API of the CanIf module*/
#define CANSM_START_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"
VAR(uint16, CANSM_VAR)  CanSM_ModeRepeatReq_Time_u16;
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"

/* Holds Maximal amount of mode request repetitions without a respective mode indication */
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
VAR(uint8, CANSM_VAR)   CanSM_ModeRepeatReq_Max_u8;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_CANControllerStateType_ten, CANSM_VAR)CanSM_ControllerState_en[CANSM_NUM_CAN_CONTROLLERS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*CanSM initialization indication flag*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_Network_Init_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/*CAN ontrollers mode indications*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_ControllerIndications_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
VAR(CanSM_BOR_Controller_Stopped_stateType_ten, CANSM_VAR)CanSM_BOR_Controller_Stopped_state_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*Pointer to the Active network configuration*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
P2CONST(CanSM_NetworkConf_tst, CANSM_VAR, CANSM_APPL_CONST) CanSM_Network_pcst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*Pointer to the active config set*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
P2CONST(CanSM_ConfigType, CANSM_VAR, CANSM_APPL_CONST) CanSM_ConfigSet_pcst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/* FC_VariationPoint_START */
/*Pointer to the DSM Configuration*/
#if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
P2VAR(CanSM_NetworkConf_DEM_tst, CANSM_VAR, CANSM_APPL_DATA) CanSM_NetworkDem_pst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif
/* FC_VariationPoint_END */

#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
/*Variable to hold the value of input parameter*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean , AUTOMATIC) CanSM_Passive_b;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
#endif

/* FC_VariationPoint_START */
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_Rb_DisableBusOffRecovery_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
/* FC_VariationPoint_END */

#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
VAR(uint8, CANSM_VAR) CanSM_GetBusOffDelay_Value_u8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
VAR(boolean, CANSM_VAR) CanSM_BOR_SilentCom_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
/**
***************************************************************************************************
** Function Name        : CanSM_Init
**
** Service ID           : 0x00
**
** Description          : This function initializes internal and external
**                        interfaces and variables of the CANSM Module for further processing.
**                        This service initializes the CanSM module.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : ConfigPtr: Pointer to init structure for the post build parameters of the CanSM
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_Init(const CanSM_ConfigType* ConfigPtr)
{
    /* Local variable to hold network index */
    VAR(uint8, AUTOMATIC) CanSM_NetworkIdx_u8;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;

    #if(CANSM_VARIANT_INFO == CANSM_VARIANT_PRE_COMPILE)
    /* Assign the configuration pointer(default variant) to global pointer and ignore the pointer passed by ECUM*/
    CanSM_ConfigSet_pcst = &CanSM_ConfigSet[0];
    (void)ConfigPtr;
    #else
    /*Report to DET if NULL pointer is passed in case of PBS*/
    CANSM_REPORT_ERROR((ConfigPtr==NULL_PTR),(uint8)CANSM_INIT_SID,(uint8)CANSM_E_INIT_FAILED)
    /* Assign the configuration pointer to global pointer */
    CanSM_ConfigSet_pcst = ConfigPtr;
    #endif

    /*Assign the current network configuration*/
    CanSM_Network_pcst = CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst;

    #if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
    /*Assign the current network configuration for DSM*/
    CanSM_NetworkDem_pst = CanSM_ConfigSet_pcst->CanSMNetworkConfDEM_pst;
    #endif
    /*T_REPEAT_MAX value*/
    CanSM_ModeRepeatReq_Max_u8   = CanSM_ConfigSet_pcst->CanSMModeRequestRepetitionMax_u8;
    /*Timeout value*/
    CanSM_ModeRepeatReq_Time_u16 = CanSM_ConfigSet_pcst->CanSMModeRequestRepetitionTime_u16;

    /* Initialise all the networks of the PBS or PC variant */
    for(CanSM_NetworkIdx_u8 =0; CanSM_NetworkIdx_u8 < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; CanSM_NetworkIdx_u8++)
    {
        /*Initialize the global arrays*/
        CanSM_CurrNw_Mode_en[CanSM_NetworkIdx_u8]                      = CANSM_BSM_S_NOT_INITIALIZED;                   /*The present state of the network [after Power On] */
        CanSM_currBOR_State_en[CanSM_NetworkIdx_u8]                    = CANSM_BOR_IDLE;                                /*BOR state is IDLE*/
        CanSM_BusOff_Cntr_au8[CanSM_NetworkIdx_u8]                     = CANSM_ZERO;                                    /*Bus Off counter is reset*/
        CanSM_BORMode_au8[CanSM_NetworkIdx_u8]                         = CANSM_RECOVERY_DISABLED;                       /*BOR mode is Disabled*/
        CanSM_ReqComM_Mode_en[CanSM_NetworkIdx_u8]                     = COMM_NO_COMMUNICATION ;                        /*Requested ComM mode is NO COM*/
        CanSM_BusOffISRPend_ab[CanSM_NetworkIdx_u8]                    = FALSE;                                         /*No bus off event is pending*/
        CanSM_Ctrl_ModeInd_ab[CanSM_NetworkIdx_u8]                     = FALSE;                                         /*Set Controller mode indication to FALSE. This would be set to TRUE in CanSM_ControllerModeIndication()*/
        CanSM_Network_Init_ab[CanSM_NetworkIdx_u8]                     = FALSE;                                         /*Holds the status of network if it is initialised or not*/
        CanSM_MutexMode_au8[CanSM_NetworkIdx_u8]                       = CANSM_MUTEX_FREE;                              /*Lock is free is use*/
        CanSM_Init_ab                                                  = (boolean)CANSM_UNINITED;                       /*Holds the status of CanSM module if it is initialised or not*/
        CanSM_Wuvalidation_Start_ab[CanSM_NetworkIdx_u8]                = FALSE;                                         /*Holds the Wake Up Validation start  trigger */
        CanSM_PreNoCom_Substates_en[CanSM_NetworkIdx_u8]               = CANSM_DEFAULT;                                 /*The PreNoCom_Substate is set to CANSM_DEFAULT*/
        CanSM_PreFullCom_Substates_en[CanSM_NetworkIdx_u8]             = CANSM_PRE_FULLCOM_DEFAULT;                     /*No substates to be traversed in Prepare to FULLCOM*/
        CanSM_WakeUpValidation_Substates_en[CanSM_NetworkIdx_u8]       = CANSM_WAKEUP_VALIDATION_DEFAULT;               /*No substates to be traversed in Wake Up Validation*/
        #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
        CanSM_ChangeBR_Substates_en[CanSM_NetworkIdx_u8]               = CANSM_BR_DEFAULT;                              /*No substates to be traversed in Change Baudrate main state*/
        #endif
        CanSM_TxTimeoutexception_Substates_en[CanSM_NetworkIdx_u8]     = CANSM_TxTimeoutException_DEFAULT;              /*No substates to be traversed in Tx Timeout Exception during initialization*/
        CanSM_Num_Unsuccessful_ModeReq_au8[CanSM_NetworkIdx_u8]        = CANSM_ZERO;                                    /*Initialise T_REPEAT_MAX counter to 0*/
        CanSM_BusOff_Indicated_ab[CanSM_NetworkIdx_u8]                  = FALSE;                                         /*No bus off indication for the Network*/
        CanSM_InitTimer(CanSM_NetworkIdx_u8);                                                                           /*Initilaise the free running timer for Time track*/
        CanSM_BOR_Controller_Stopped_state_en[CanSM_NetworkIdx_u8]    = CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED;/*No request to stop controllers in BOR mode*/
        #if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
        CanSM_Passive_b                                                = FALSE;                                         /*ECU passive request is FALSE*/
        #endif
        /* FC_VariationPoint_START */
        CanSM_Rb_DisableBusOffRecovery_ab[CanSM_NetworkIdx_u8]         = FALSE;                                         /*To disable bus off recovery*/
        /* FC_VariationPoint_END */
        CanSM_GetBusOffDelay_Value_u8[CanSM_NetworkIdx_u8]             = CANSM_ZERO;                                    /*No bus off delay */
        CanSM_BOR_SilentCom_ab[CanSM_NetworkIdx_u8]                     = FALSE;                                        /*No bus off occuring  in Silent COM*/
        /*Hold the address of the configured network*/
        CanSM_NetworkConf_ps = &CanSM_Network_pcst[CanSM_NetworkIdx_u8];

        #if (CANSM_CHANGE_BAUDRATE_API == STD_ON)
        /* Initilalize CanSM_ChangeBaudRate_Value_au32 with an invalid value */
        CanSM_ChangeBaudRate_Value_au32[CanSM_NetworkIdx_u8] =0xFFFFFFFFu;
        /*Initialise the status to FALSE*/
        CanSM_CheckBR_Status_ab[CanSM_NetworkIdx_u8]=FALSE;
        #endif


        #if(CANSM_SET_BAUDRATE_API == STD_ON)
        /*Initilalize CanSM_BaudRateConfigID_Value_au16 with a default/invalid value*/
        CanSM_BaudRateConfigID_Value_au16[CanSM_NetworkIdx_u8] = 0xFFFFu;
        #endif

        /*The present state of the network [during initialisation]*/
        CanSM_CurrNw_Mode_en[CanSM_NetworkIdx_u8] = CANSM_BSM_S_PRE_NOCOM;

        /*When transceiver is configured, also check if PN is supported*/
        if(CanSM_Network_pcst[CanSM_NetworkIdx_u8].Trcv_hndle_u8 != 255u)
            {
                CanSM_Trcv_ModeInd_ab[CanSM_NetworkIdx_u8] = FALSE;
                #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
                /*Pn checking includes that transceiver is also configured */
                if(CanSM_Network_pcst[CanSM_NetworkIdx_u8].TrcvPnConfig_b == TRUE)
                    {
                        /*Initiate the substate machine for De-initilization with PN support*/
                        CanSM_PN_Substate_Ind_ab[CanSM_NetworkIdx_u8] = FALSE;
                    }
                #endif
            }
        else
            {
                CanSM_Trcv_ModeInd_ab[CanSM_NetworkIdx_u8] = TRUE;
            }

            /* Loop for all the Controllers in the network and Set them to UNINIT Mode*/
        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
            {
                /*Store the CAN controller ID belonging to the network*/
                CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                /*Put all the CAN conrollers to uninitialised state*/
                CanSM_ControllerState_en[CanSM_ControllerId_u8] = CANSM_ControllerState_UNINIT ;
                /*Update the CAN Controller Mode Indications to FALSE*/
                CanSM_ControllerIndications_ab[CanSM_ControllerId_u8] = FALSE;
            }

        /*Notify DEM that there is no busoff*/
        Dem_ReportErrorStatus(CanSM_Network_pcst[CanSM_NetworkIdx_u8].BusOffEventId_uo,DEM_EVENT_STATUS_PASSED);

        /* FC_VariationPoint_START */
        /*Update the intended network variable with latest DEM event status to be used to provide status to DEM module on request*/
        #if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
        CanSM_NetworkDem_pst[CanSM_NetworkIdx_u8].CanSM_DEM_Eventstatus_u8 = DEM_EVENT_STATUS_PASSED;
        #endif
        /* FC_VariationPoint_END */
    }
        /* The module is initialised */
        CanSM_Init_ab = (boolean)CANSM_INITED;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_DeInitPnNotSupported
**
** Service ID           : None
**
** Description          : This function Deinitialises the CanSM network without PN support
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non Reentrant
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_DeInitPnNotSupported(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*To keep the track of CanSM_PreNoCom_Substates*/
    VAR(CanSM_PreNoCom_Substates_ten, CANSM_VAR) CanSM_PreNoCom_Substates;

    /*Local variabe to hold the BSWM mode*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;

    /*Temporary pointer to CanSM_Network_pcst[]*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_APPL_DATA ) NetworkConf_ps;
    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;
    /*Hold the address of the passed network*/
    NetworkConf_ps = &CanSM_Network_pcst[network];

    /*Make local copy CanSM_PreNoCom_Substates_en[network]*/
    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

    /*If T_REPEAT_MAX counter has not exceeded*/
    if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
    {
        switch(CanSM_PreNoCom_Substates)
        {
            case CANSM_S_CC_STOPPED_WAIT:
            {
                /*Check if a controller indication was received that all the CAN controllers are stopped*/
                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the controller mode indication flag for the network*/
                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    /*Move to next substate of the CANSM_S_CC_SLEEP */
                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_SLEEP;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*Reset the T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

               }

                /*Check if timeout has occurred and so proceed accordingly*/
                else
                {
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate ie S_CC_STOPPED*/
                        CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
                    }
                }
            }
            break;

            case CANSM_S_CC_SLEEP_WAIT:
            {
                /*Check if a controller indication was received...*/
                if(CanSM_Ctrl_ModeInd_ab[network]==TRUE)
                {
                    /*Reset the controller mode indication flag for the network*/
                    CanSM_Ctrl_ModeInd_ab[network]=FALSE;

                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*move to next state CANSM_S_TRCV_NORMAL*/
                    CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*Reset the T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                /*check if timeout has occurred and proceed accordingly.*/
                else
                {
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate ie S_CC_SLEEP*/
                        CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }

            }
            break;

            case CANSM_S_TRCV_NORMAL_WAIT:
            {
                /*Check if a transceiver indication was received...*/
                if(CanSM_Trcv_ModeInd_ab[network]==TRUE)
                {
                    /*Check if the transceiver is configured*/
                    if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
                        {
                            /*Reset the transceiver mode indication flag to FALSE only if transceiver is configured */
                            CanSM_Trcv_ModeInd_ab[network] = FALSE;
                        }

                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*move to next state*/
                    CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY;

                    /*Reset the T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                }
                else
                {
                    /*check if timeout has occurred and proceed accordingly.*/
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate ie CANSM_S_TRCV_NORMAL*/
                        CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
                    }
                }
            }
            break;

            case CANSM_S_TRCV_STANDBY_WAIT:
            {
                /*Check if a transceiver indication was received...*/
                if(CanSM_Trcv_ModeInd_ab[network]==TRUE)
                {
                    /*Check if the transceiver is configured*/
                    if(NetworkConf_ps->Trcv_hndle_u8 != 255)
                        {
                            /*Reset the transceiver mode indication flag to FALSE only if transceiver is configured */
                            CanSM_Trcv_ModeInd_ab[network] = FALSE;
                        }
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the E_NOT_OK counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

                    /*Update the Pre no com state Default*/
                    CanSM_PreNoCom_Substates_en[network] = CANSM_DEFAULT;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*The network is now initialized*/
                    CanSM_Network_Init_ab[network] = TRUE;

                    /*Update the state of Network for BswM*/
                    CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;

                    /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                    BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

                    /* Loop for All the Controllers in the Network and put the pdu mode to OFFLINE*/
                    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                    {
                        CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                        /* set PDU to OFFLINE Mode */
                        /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                        (void)(CanIf_SetPduMode((uint8)CanSM_ControllerId_u8,CANIF_SET_OFFLINE));

                    }
                    /*The state machine can move to NOCOM or WUVALIDATION depending upon the trigger */
                    /* updated in CanSM_StartWakeUpSource() api called by Ecum */
                    if(CanSM_Wuvalidation_Start_ab[network] == TRUE)
                        {
                            /*Update the current network mode to CANSM_BSM_WUVALIDATION*/
                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_WUVALIDATION;
                            /*Update the array state to CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL */
                            CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

                        }
                    else
                        {
                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_S_NOCOM;
                        }
                }

                /*check if timeout has occurred and proceed accordingly.*/
                else
                {
                   if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate ie CANSM_S_TRCV_STANDBY*/
                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_TRCV_STANDBY;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;

            default:
                /*do nothing*/
            break;

        }/*switch ends*/
    }
    else
    {
        /*Start prepare to NOCOM again*/
        CanSM_PreNoCom_Substates_en[network]=CANSM_S_CC_STOPPED;

        /*keep a copy of the current substate */
        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

        /*Reset the T_REPEAT_MAX counter*/
        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

        /*Report to DET that T_REPEAT_MAX counter has exceeded CANSM_MODEREQ_MAX*/
        CANSM_REPORT_ERROR( CanSM_PreNoCom_Substates_en[network]==CANSM_S_CC_STOPPED,((uint8)CANSM_MAINFUNCTION_SID),(uint8)(CANSM_E_MODE_REQUEST_TIMEOUT))

    }/*else(near switch) ends*/

    /*Check the first substate of PRE_NOCOM is CANSM_S_CC_STOPPED*/
    if(CanSM_PreNoCom_Substates == CANSM_S_CC_STOPPED)
        {
            /*Stop the CAN controllers*/
            /*Depending on the mode indication received / not received, the next substate can be CANSM_S_SLEEP / CANSM_S_CC_STOPPED_WAIT*/
            CanSM_StopCtrl(network);
            /*keep a copy of the current substate */
            CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
        }

    /*mode indication for CANSM_S_CC_STOPPED received, hence current substate - CANSM_S_CC_SLEEP*/
    if(CanSM_PreNoCom_Substates == CANSM_S_CC_SLEEP)
        {
            /*Put all the CAN controllers to sleep mode */
            /*Depending on the mode indication received / not received, the next substate can be CANSM_S_TRCV_NORMAL / CANSM_S_CC_SLEEP_WAIT*/
            CanSM_SleepCtrl(network);
            /*keep a copy of the current substate */
            CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
        }

    /*mode indication for CANSM_S_CC_SLEEP received, hence current substate - CANSM_S_TRCV_NORMAL*/
    if(CanSM_PreNoCom_Substates == CANSM_S_TRCV_NORMAL)
        {
            if(CanSM_Network_pcst[network].Trcv_hndle_u8 == 255)
            {
                /*Tranceiver mode indication is considered to be received*/
                CanSM_Trcv_ModeInd_ab[network] = TRUE;
                /*If no CanSMTransceiverId is configured for a CAN Network, then the CanSM module shall bypass all specified
                CanIf_SetTrcvMode  calls for the CAN Network and proceed in the different state transitions as if it has got the supposed
                CanSM_TransceiverModeIndication already*/
                CanSM_PreNoCom_Substates_en[network] = CANSM_S_TRCV_STANDBY;
                /*keep a copy of the current substate */
                CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
            }
            else
            {
                /*Put the transceiver to Normal mode*/
                /*Depending on the mode indication received / not received, the next substate can be CANSM_S_TRCV_STANDBY / CANSM_S_TRCV_NORMAL_WAIT*/
                CanSM_NormalTrcv(network);
                /*keep a copy of the current substate */
                CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
            }
        }

    /*mode indication for CANSM_S_TRCV_NORMAL received, hence current substate - CANSM_S_TRCV_STANDBY*/
    if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_STANDBY)
        {
            if(CanSM_Network_pcst[network].Trcv_hndle_u8 == 255u)
            {
                /*Tranceiver mode indication is considered to be received*/
                CanSM_Trcv_ModeInd_ab[network] = TRUE;
                /*If no CanSMTransceiverId is configured for a CAN Network, then the CanSM module shall bypass all specified
                CanIf_SetTrcvMode  calls for the CAN Network and proceed in the different state transitions as if it has got the supposed
                CanSM_TransceiverModeIndication already*/
                CanSM_PreNoCom_Substates_en[network] = CANSM_DEFAULT;

                /*The network is initialised now*/
                CanSM_Network_Init_ab[network] = TRUE;
                /*keep a copy of the current substate */
                CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                /*Update the state of Network for BswM*/
                CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;
                /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);

                /* Loop for All the Controllers in the Network and put the pdu mode to OFFLINE*/
                for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                {
                    CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                    /* set PDU to OFFLINE Mode */
                    /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                    (void)(CanIf_SetPduMode((uint8)CanSM_ControllerId_u8,CANIF_SET_OFFLINE));

                }

                /*The state machine can move to NOCOM or WUVALIDATION depending upon the trigger */
                if(CanSM_Wuvalidation_Start_ab[network] == TRUE) /* updated in CanSM_StartWakeUpSource() api called by Ecum*/
                    {
                        /*Update the current network mode to CANSM_BSM_WUVALIDATION*/
                        CanSM_CurrNw_Mode_en[network]= CANSM_BSM_WUVALIDATION;
                        /*Update the array state to CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL */
                        CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;
                    }
                else
                    {
                        CanSM_CurrNw_Mode_en[network]= CANSM_BSM_S_NOCOM;
                    }
            }
            else
            {
                /*Put the CAN transceivers to STANDBY mode*/
                /*Depending on the mode indication received / not received, the next substate can be CANSM_DEFAULT / CANSM_S_TRCV_STANDBY_WAIT */
                CanSM_StandbyTrcv(network);
                /*keep a copy of the current substate */
                CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
            }

        }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_DeInitPnSupported
**
** Service ID           : None
**
** Description          : This function Deinitialises the CanSM network with PN support
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non Reentrant
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_DeInitPnSupported(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*To keep the track fo of prenocom substates*/
    VAR(CanSM_PreNoCom_Substates_ten, CANSM_VAR) CanSM_PreNoCom_Substates;

    /*Local variabe to hold the BSWM mode*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;

    /*Temporary pointer to CanSM_Network_pcst[]*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_APPL_DATA ) NetworkConf_ps;

    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;

    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;

    /*Make local copy CanSM_PreNoCom_Substates_en[network]*/
    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

    /*Hold the address of the passed network*/
    NetworkConf_ps = &CanSM_Network_pcst[network];

    /*If T_REPEAT_MAX counter has not exceeded...*/
    if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
    {
        switch(CanSM_PreNoCom_Substates)
        {
            case CANSM_S_PN_CLEAR_WUF_WAIT:
            {
                /*Check if the PN-mode indication was received...*/
                if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the flag*/
                    CanSM_PN_Substate_Ind_ab[network] = FALSE;

                    /*Proceed to next substate, CANSM_PN_S_CC_STOPPED*/
                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CC_STOPPED;

                    /*Reset the T_REPEAT_MAX counter on successful transition to next substate*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                }
                /*If PN-mode indication was not received...*/
                else
                {
                    /*Check if timeout has occurred and proceed accordingly*/
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate, CANSM_PN_S_CLEAR_WUF*/
                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_PN_CLEAR_WUF;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;

            case CANSM_S_PN_CC_STOPPED_WAIT:
            {
                /*Check if the controller-mode indication was received...*/
                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the controller mode indication flag*/
                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    /*Proceed to next substate, CANSM_S_TRCV_NORMAL*/
                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_TRCV_NORMAL;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*Reset the T_REPEAT_MAX counter on successful transition to next substate*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                /*If controller-mode indication was not received...*/
                else
                {
                    /*Check if timeout has occurred and proceed accordingly*/
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate, CANSM_PN_S_CC_STOPPED*/
                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_PN_CC_STOPPED;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;

            case CANSM_S_PN_TRCV_NORMAL_WAIT:
            {
                /*Check if the transceiver-mode indication was received...*/
                if(CanSM_Trcv_ModeInd_ab[network] == TRUE)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the flag*/
                    CanSM_Trcv_ModeInd_ab[network] = FALSE;

                    /*Proceed to next substate, CANSM_S_TRCV_STANDBY*/
                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_TRCV_STANDBY;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*Reset the T_REPEAT_MAX counter on successful transition to next substate*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                /*If transceiver-mode indication was not received...*/
                else
                {
                    /*Check if timeout has occurred and proceed accordingly*/
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate, CANSM_S_TRCV_NORMAL*/
                        CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_TRCV_NORMAL;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;


            case CANSM_S_PN_TRCV_STANDBY_WAIT:
            {
                /*Check if the transceiver-mode indication was received...*/
                if(CanSM_Trcv_ModeInd_ab[network] == TRUE)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the flag*/
                    CanSM_Trcv_ModeInd_ab[network] = FALSE;

                    /*Proceed to next substate, CANSM_S_CC_SLEEP*/
                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CC_SLEEP;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*Reset the T_REPEAT_MAX counter on successful transition to next substate*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                /*If transceiver-mode indication was not received...*/
                else
                {
                    /*Check if timeout has occurred and proceed accordingly*/
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate, CANSM_S_PN_TRCV_STANDBY*/
                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_PN_TRCV_STANDBY;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
                }
            }
            break;

            /*This substate is a bit different wrt to other wait states*/
            case CANSM_S_PN_CC_SLEEP_WAIT:
            {
                /*Check if the controller-mode indication was received...*/
                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the flag*/
                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    /*Proceed to next substate, CANSM_S_CHECK_WFLAG_IN_CC_SLEEP*/
                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CHECK_WFLAG_IN_CC_SLEEP;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*Reset the T_REPEAT_MAX counter on successful transition to next substate*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                /*If controller-mode indication was not received...*/
                else
                {
                   /*Check if timeout has occurred and proceed accordingly*/
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to NEXT substate, CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP*/
                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }
               }
            }
            break;

            case CANSM_S_CHECK_WFLAG_IN_CC_SLEEP_WAIT:
            {
                /*Check if the PN-mode indication was received...*/
                if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
                {

                    /*Reset all the mode indication flags*/
                    CanSM_PN_Substate_Ind_ab[network]   = FALSE;
                    CanSM_Ctrl_ModeInd_ab[network]      = FALSE;
                    CanSM_Trcv_ModeInd_ab[network]      = FALSE;
                    /*Update the PRE_NOCOM substate to Default*/
                    CanSM_PreNoCom_Substates_en[network] = CANSM_DEFAULT;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                    /*The network is now initialized*/
                    CanSM_Network_Init_ab[network] = TRUE;

                    /* Loop for All the Controllers in the Network and put the pdu mode to OFFLINE*/
                    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                    {
                        CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                        /* set PDU to OFFLINE Mode */
                        /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_OFFLINE));

                    }
                    /*Update the state of Network for BswM*/
                    CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;

                    /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                    BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

                    /*The state machine can move to NOCOM or WUVALIDATION depending upon the trigger */
                    if(CanSM_Wuvalidation_Start_ab[network] == TRUE) /* updated in CanSM_StartWakeUpSource() api called by Ecum*/
                        {
                            /*Update the current network mode to CANSM_BSM_WUVALIDATION*/
                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_WUVALIDATION;
                            /*Update the array state to CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL */
                            CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

                        }
                    else
                        {
                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_S_NOCOM;
                        }
                }
                /*If PN-mode indication was not received*/
                else
                {
                    /*Check if timeout has occurred and proceed accordingly*/
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate, CANSM_S_CHECK_WFLAG_IN_CC_SLEEP*/
                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_CHECK_WFLAG_IN_CC_SLEEP;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
                    }
                }
            }
            break;

            case CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP_WAIT:
            {
                /*Check if the PN-mode indication was received...*/
                if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
                {

                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset all mode indication flags*/
                    CanSM_PN_Substate_Ind_ab[network]   = FALSE;
                    CanSM_Ctrl_ModeInd_ab[network]      = FALSE;
                    CanSM_Trcv_ModeInd_ab[network]      = FALSE;

                    /*Restart the state machine. Go back to the first substate, CANSM_S_PN_CLEAR_WUF*/
                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;

                    /*keep a copy of the current substate */
                    CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    /*Reset T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                }

                /*If PN-mode indication was not received...*/
                else
                {
                    /*Check if timeout has occurred and proceed accordingly*/
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate, CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP*/
                        CanSM_PreNoCom_Substates_en[network]=CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP;

                        /*keep a copy of the current substate */
                        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

                    }

                }
            }
            break;

            default:
            /* Intentionally Empty */
            break;
        }
    }
    else
        {
            /*Reset T_REPEAT_MAX counter for the network*/
            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

            /*Set to the starting of the state machine substate*/
            CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;

            /*keep a copy of the current substate */
            CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];

            /*Report to DET that T_REPEAT_MAX counter has exceeded CANSM_MODEREQ_MAX*/
            CANSM_REPORT_ERROR(CanSM_PreNoCom_Substates_en[network]==CANSM_S_PN_CLEAR_WUF,((uint8)CANSM_MAINFUNCTION_SID),(CANSM_E_MODE_REQUEST_TIMEOUT))

        }
    /* Check if PreNoCom Substate is equal to CANSM_S_PN_CLEAR_WUF */
    if(CanSM_PreNoCom_Substates == CANSM_S_PN_CLEAR_WUF)
    {
        /* Clear WUF flag */
        CanSM_PN_ClearWufTrcv(network);
        /*keep a copy of the current substate */
        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    /* Check if PreNoCom Substate is equal to S_PN_CC_STOPPED */
    if(CanSM_PreNoCom_Substates == CANSM_S_PN_CC_STOPPED)
    {
        /* Put all the CAN controllers of the intended network to stop mode */
        CanSM_StopCtrl(network);
        /*keep a copy of the current substate */
        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    /* Check if PreNoCom Substate is equal to CANSM_S_PN_TRCV_NORMAL */
    if(CanSM_PreNoCom_Substates == CANSM_S_PN_TRCV_NORMAL)
    {
       /* Put the transceiver to normal mode */
        CanSM_NormalTrcv(network);
        /*keep a copy of the current substate */
        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    /* Check if PreNoCom Substate is equal to CANSM_S_PN_TRCV_STANDBY */
    if(CanSM_PreNoCom_Substates == CANSM_S_PN_TRCV_STANDBY)
    {
        /* Put the transceiver to standby mode */
        CanSM_StandbyTrcv(network);
        /*keep a copy of the current substate */
        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    /* Check if PreNoCom Substate is equal to CANSM_S_PN_CC_SLEEP */
    if(CanSM_PreNoCom_Substates == CANSM_S_PN_CC_SLEEP)
    {
        /* Put all the CAN controllers of the intended network to sleep mode */
        CanSM_SleepCtrl(network);
        /*keep a copy of the current substate */
        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

        /* Check if PreNoCom Substate is equal to CANSM_S_CHECK_WFLAG_IN_CC_SLEEP */
    if(CanSM_PreNoCom_Substates == CANSM_S_CHECK_WFLAG_IN_CC_SLEEP)
    {
        /* Check the wake up flag in sleep */
        CanSM_CheckWakeUpFlagInSleep(network);
        /*keep a copy of the current substate */
        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

    /* Check if PreNoCom Substate is equal to CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP */
    if(CanSM_PreNoCom_Substates == CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP)
    {
        /* Check wake up flag when not in sleep */
        CanSM_CheckWakeUpFlagNotInSleep(network);
        /*keep a copy of the current substate */
        CanSM_PreNoCom_Substates = CanSM_PreNoCom_Substates_en[network];
    }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
