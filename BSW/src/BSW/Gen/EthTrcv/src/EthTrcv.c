


/*
 ***************************************************************************************************
 * \moduledescription
 *                      Public source file for ETHTRCV
 *
 * \scope               API
 ***************************************************************************************************
 */


/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "EthTrcv_Prv.h"
#include "EthTrcv_Cfg_Time.h"
#include "EthTrcv_PBcfg.h"

#ifdef ETHTRCV_CONFIGURED

#include "Eth.h"
#include "EthTrcv_Cfg_SchM.h"
#include "EthIf.h"
#include "EthIf_Cbk.h"

#if (ETHTRCV_CFG_DET_ENABLE == STD_ON)
# include "Det.h"
#endif
#if (ETHTRCV_CFG_DEM_ENABLE == STD_ON)
# include "Dem.h"
#endif

/**
***************************************************************************************************
*               Version Check
****************************************************************************************************
*/
#if(ETHTRCV_EXPECTED_GEN_MAJOR_VERSION != ETHTRCV_GEN_MAJOR_VERSION)
# error "Generator version does not fit to software version"
#endif
#if(ETHTRCV_EXPECTED_GEN_MINOR_VERSION != ETHTRCV_GEN_MINOR_VERSION)
# error "Generator version does not fit to software version"
#endif

#if (!defined(ETH_AR_RELEASE_MAJOR_VERSION) || (ETH_AR_RELEASE_MAJOR_VERSION < 4))
# error "ETH AUTOSAR major version undefined or mismatched."
#endif
#if (!defined(ETH_AR_RELEASE_MAJOR_VERSION) || (ETH_AR_RELEASE_MAJOR_VERSION > 4))
# error "ETH AUTOSAR major version undefined or mismatched."
#endif
#if (ETHTRCV_CFG_DET_ENABLE == STD_ON)
# if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION < 3))
#  error "DET AUTOSAR major version undefined or mismatched."
# endif
# if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION > 4))
#  error "DET AUTOSAR major version undefined or mismatched."
# endif
#endif
#if (ETHTRCV_CFG_DEM_ENABLE == STD_ON)
# if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION < 3))
#  error "DEM AUTOSAR major version undefined or mismatched."
# endif
# if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION > 4))
#  error "DEM AUTOSAR major version undefined or mismatched."
# endif
#endif

/**
 ***************************************************************************************************
*               Defines
****************************************************************************************************
*/
#if(ETHTRCV_CFG_CONFIG_VARIANT == ETHTRCV_POSTBUILD)
# define ETHTRCV_NUMBER_OF_ETHTRCV (EthTrcv_Config.NumberOfEthTrcv)
# define ETHTRCV_NUMBER_OF_CONFSET (EthTrcv_Config.NumberOfConfSets_u8)
# define ETHTRCV_NUMBER_OF_CFGDATA (EthTrcv_Config.NumberOfCfgData_u16)
#endif
#if(ETHTRCV_CFG_CONFIG_VARIANT == ETHTRCV_LINKTIME)
# define ETHTRCV_NUMBER_OF_ETHTRCV (EthTrcv_Config.NumberOfEthTrcv)
#endif
#if(ETHTRCV_CFG_CONFIG_VARIANT == ETHTRCV_PRECOMPILE)
# define ETHTRCV_NUMBER_OF_ETHTRCV ETHTRCV_CFG_NUMBER_OF_ETHTRCV
# define ETHTRCV_NUMBER_OF_CONFSET (EthTrcv_Config.NumberOfConfSets_u8)
# define ETHTRCV_NUMBER_OF_CFGDATA (EthTrcv_Config.NumberOfCfgData_u16)
#endif


/**
 ***************************************************************************************************
*               Global variables
****************************************************************************************************
*/
#define ETHTRCV_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EthTrcv_MemMap.h"

#define ETHTRCV_CFG_TIMEOUT_COUNTER_MAX 10

VAR(boolean,                ETHTRCV_VAR)    EthTrcv_Prv_MiiCommunicationFlag_b;   /* Made True before MDIO communication is started; Made to FALSE once MDIO communication is over */
VAR(EthTrcv_StateType,      ETHTRCV_VAR)    EthTrcv_Prv_State_e[ETHTRCV_MAX_TRCVS_SUPPORTED];       /* State of each Trcv */
VAR(EthTrcv_WupReasonType,  ETHTRCV_VAR)    EthTrcv_Prv_WupReason_e[ETHTRCV_MAX_TRCVS_SUPPORTED];   /* Wup Reason for each Trcv (only for TJA1100) */
VAR(EthTrcv_InitStateType,  ETHTRCV_VAR)    EthTrcv_Prv_InitState_e[ETHTRCV_MAX_TRCVS_SUPPORTED];   /* Local init state for each Trcv (see  EthTrcv_Cfg_CfgData_ast) */
VAR(EthTrcv_ModeType,       ETHTRCV_VAR)    EthTrcv_Prv_CurrentMode[ETHTRCV_MAX_TRCVS_SUPPORTED];   /* Holds the current mode of EthTrcv */
VAR(EthTrcv_ModeType,       ETHTRCV_VAR)    EthTrcv_Prv_RequestedMode[ETHTRCV_MAX_TRCVS_SUPPORTED]; /* Requested Mode, The mode change is executed in main function until then requested mode is stored here */
VAR(EthTrcv_LinkStateType,  ETHTRCV_VAR)    EthTrcv_Prv_LinkState[ETHTRCV_MAX_TRCVS_SUPPORTED];     /* Link state is updaed in every main-function */
VAR(EthTrcv_BaudRateType,   ETHTRCV_VAR)    EthTrcv_Prv_BaudRate[ETHTRCV_MAX_TRCVS_SUPPORTED];      /* Baud rate is updated in main-function. Not for all the Phys */
VAR(EthTrcv_DuplexModeType, ETHTRCV_VAR)    EthTrcv_Prv_DuplexMode[ETHTRCV_MAX_TRCVS_SUPPORTED];    /* Duplex Mode is updated in main-function. Not for all the Phys */
VAR(boolean,                ETHTRCV_VAR)    EthTrcv_Prv_ModeIndicationFlag[ETHTRCV_MAX_TRCVS_SUPPORTED];    /* Global Flag to decide whether mode indication is required */
VAR(boolean,                ETHTRCV_VAR)    EthTrcv_Prv_AutoNegotiationReq[ETHTRCV_MAX_TRCVS_SUPPORTED];    /* Auto negotiation has to be started in main function */

#if defined(ETHTRCV_TJA1100_USED)
 #if (ETHTRCV_TJA1100_USED == STD_ON)
static VAR(EthTrcv_PhyTestModeType,             ETHTRCV_VAR)    EthTrcv_Prv_RequestedPhyTestMode[ETHTRCV_MAX_TRCVS_SUPPORTED];      /* Requested Test mode for EthTrcv */
static VAR(EthTrcv_PhyTestModeType,             ETHTRCV_VAR)    EthTrcv_Prv_CurrentPhyTestMode[ETHTRCV_MAX_TRCVS_SUPPORTED];        /* Current Test mode of EthTrcv */
static VAR(boolean,                             ETHTRCV_VAR)    EthTrcv_Prv_CableDiagRequested[ETHTRCV_MAX_TRCVS_SUPPORTED];        /* Indicates whether the cable test is requested */
static VAR(EthTrcv_CableDiagResultType,         ETHTRCV_VAR)    EthTrcv_Prv_CableDiagResult[ETHTRCV_MAX_TRCVS_SUPPORTED];           /* Result of the cable test */
static VAR(uint8,                               ETHTRCV_VAR)    EthTrcv_Prv_CableSignalQuality_u8[ETHTRCV_MAX_TRCVS_SUPPORTED];     /* Result of the signal quality of the cable */
static VAR(EthTrcv_PhyLoopbackModeType,         ETHTRCV_VAR)    EthTrcv_Prv_RequestedPhyLoopbackMode[ETHTRCV_MAX_TRCVS_SUPPORTED];  /* Requested Loopback mode for EthTrcv */
static VAR(EthTrcv_PhyLoopbackModeType,         ETHTRCV_VAR)    EthTrcv_Prv_CurrentPhyLoopbackMode[ETHTRCV_MAX_TRCVS_SUPPORTED];    /* Current Loopback mode of EthTrcv */
static VAR(EthTrcv_PhyIdentificationType_tst,   ETHTRCV_VAR)    EthTrcv_Prv_PhyIdentifier_au32[ETHTRCV_MAX_TRCVS_SUPPORTED];        /* Phy Identifier for each EthTrcv */
static VAR(EthTrcv_PhyAccessStatusType,         ETHTRCV_VAR)    EthTrcv_Prv_PhyAccessStatus_e[ETHTRCV_MAX_TRCVS_SUPPORTED];         /* Contains the information about Phy access */
static VAR(EthTrcv_LinkStatisticsType,          ETHTRCV_VAR)    EthTrcv_Prv_LinkStatistics_ast[ETHTRCV_MAX_TRCVS_SUPPORTED];        /* Contains the link statistics information */
 #endif
#endif

VAR(uint16,ETHTRCV_VAR) EthTrcv_Prv_MiiCommunicationPos; /* Position to point the current MDIO command in EthTrcv_Cfg_CfgData_ast */
VAR(uint16,ETHTRCV_VAR) EthTrcv_Prv_Buff0;               /* The read value from Phy is always copied to EthTrcv_Prv_Buff0 */
VAR(uint16,ETHTRCV_VAR) EthTrcv_Prv_Buff1;               /* Var used to write desired value into Phy register */
VAR(uint16,ETHTRCV_VAR) EthTrcv_Prv_TimeoutCount;        /* Number of main functions for which the MDIO communication is running */

/* The config variant given in EthTrcv_TransceiverInit
   for faster access some pointers are stored in RAM */
static P2CONST(EthTrcv_Cfg_TrcvInit_tst, AUTOMATIC, ETHTRCV_CONFIG_DATA)  EthTrcv_Cfg_TrcvInit_po;
static P2CONST(EthTrcv_Cfg_CfgInit_tst, AUTOMATIC, ETHTRCV_APPL_DATA)     EthTrcv_Cfg_CfgInit_po;

#if defined(ETHTRCV_TJA1100_USED)
 #if (ETHTRCV_TJA1100_USED == STD_ON)
static P2CONST(EthTrcv_ConfigType, AUTOMATIC, ETHTRCV_CONFIG_DATA)        EthTrcv_CurrentConfig_pco;
/* global pointer to Phy Identification structure */
static P2CONST(EthTrcv_PhyIdentificationType_tst, AUTOMATIC, ETHTRCV_APPL_DATA)     EthTrcv_CurrentCfg_PhyIdentification_pco;
 #endif
#endif

#define ETHTRCV_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EthTrcv_MemMap.h"

#define ETHTRCV_START_SEC_VAR_NO_INIT_16
#include "EthTrcv_MemMap.h"
/* Configuration Index of each Trcv (Set in EthTrcv_TransceiverInit) */
static VAR(uint16,ETHTRCV_VAR)              EthTrcv_InitCfgNo_au16[ETHTRCV_MAX_TRCVS_SUPPORTED];
#define ETHTRCV_STOP_SEC_VAR_NO_INIT_16
#include "EthTrcv_MemMap.h"


/**
****************************************************************************************************
*
*
*               AUTOSAR ETH TRANSCEIVER DRIVER SPECIFIC FUNCTIONS
*
*
****************************************************************************************************
*/
#define ETHTRCV_START_SEC_CODE
#include "EthTrcv_MemMap.h"
/**
 ***************************************************************************************************
 * \moduledescription
 * Init Function for EthTransceiver module
 *
 * \arg     CfgPtr = global configuration pointer
 * \return  void
 * \see
 * \note    Initialization of global variables
 ***************************************************************************************************
 */
FUNC (void, ETHTRCV_CODE) EthTrcv_Init(const EthTrcv_ConfigType* CfgPtr)
{
    uint8   lTrcvIdx_u8;
    // set local pointer to configdata according ConfigurationVariant. Used to have common, fast access
#if (ETHTRCV_CFG_CONFIG_VARIANT == ETHTRCV_POSTBUILD)
    ETHTRCV_CHECKDETTRUE_RETURN_NO_VAL((CfgPtr != NULL_PTR),0,ETHTRCV_SID_INIT, ETHTRCV_E_INV_POINTER);

    EthTrcv_Cfg_TrcvInit_po                     = CfgPtr->EthTrcv_Cfg_TrcvInit_ast;
    EthTrcv_Cfg_CfgInit_po                      = CfgPtr->EthTrcv_Cfg_CfgInit_ast;
 #if defined(ETHTRCV_TJA1100_USED)
  #if (ETHTRCV_TJA1100_USED == STD_ON)
    EthTrcv_CurrentCfg_PhyIdentification_pco    = CfgPtr->EthTrcv_Cfg_PhyIdentification_pco;
  #endif
 #endif
#else
    /* Only pre-compile is supported and the passed CfgPtr must be a null pointer else DET will be reported */
    ETHTRCV_CHECKDETTRUE_RETURN_NO_VAL((CfgPtr == NULL_PTR),0,ETHTRCV_SID_INIT, ETHTRCV_E_INV_POINTER);
    EthTrcv_Cfg_TrcvInit_po                     = EthTrcv_Cfg_TrcvInit_ast;
    EthTrcv_Cfg_CfgInit_po                      = EthTrcv_Cfg_CfgInit_ast;
 #if defined(ETHTRCV_TJA1100_USED)
  #if (ETHTRCV_TJA1100_USED == STD_ON)
    EthTrcv_CurrentConfig_pco                   = &EthTrcv_Config;
    EthTrcv_CurrentCfg_PhyIdentification_pco    = EthTrcv_PhyIdentification_ast;
  #endif
 #endif

    /* Pointer is made as void since it is unused*/
    (void)CfgPtr;
#endif

    /* Initialise state variables for all trcv */
    for(lTrcvIdx_u8=0; lTrcvIdx_u8<ETHTRCV_NUMBER_OF_ETHTRCV; lTrcvIdx_u8++ )
    {
        EthTrcv_Prv_State_e[lTrcvIdx_u8]              = ETHTRCV_STATE_INIT;
        EthTrcv_Prv_WupReason_e[lTrcvIdx_u8]          = ETHTRCV_WUP_NOT_SUPPORTED;
        EthTrcv_Prv_InitState_e[lTrcvIdx_u8]          = ETHTRCV_INITSTATE_UNINIT;
        EthTrcv_Prv_CurrentMode[lTrcvIdx_u8]          = ETHTRCV_MODE_DOWN;
        EthTrcv_Prv_RequestedMode[lTrcvIdx_u8]        = ETHTRCV_MODE_DOWN;
        EthTrcv_Prv_LinkState[lTrcvIdx_u8]            = ETHTRCV_LINK_STATE_UNDEF;
        EthTrcv_Prv_BaudRate[lTrcvIdx_u8]             = ETHTRCV_BAUD_RATE_UNDEF;
        EthTrcv_Prv_DuplexMode[lTrcvIdx_u8]           = ETHTRCV_DUPLEX_MODE_UNDEF;
        EthTrcv_Prv_ModeIndicationFlag[lTrcvIdx_u8]   = FALSE;
#if defined(ETHTRCV_TJA1100_USED)
 #if (ETHTRCV_TJA1100_USED == STD_ON)
        EthTrcv_Prv_RequestedPhyTestMode[lTrcvIdx_u8]     = ETHTRCV_PHYTESTMODE_NONE;
        EthTrcv_Prv_CurrentPhyTestMode[lTrcvIdx_u8]       = ETHTRCV_PHYTESTMODE_NONE;
        EthTrcv_Prv_CableDiagResult[lTrcvIdx_u8]          = ETHTRCV_CABLEDIAG_OK;
        EthTrcv_Prv_CableDiagRequested[lTrcvIdx_u8]       = FALSE;
        EthTrcv_Prv_CableSignalQuality_u8[lTrcvIdx_u8]    = ETHTRCV_PRV_LINKQUALITY_PERCENT_0;
        EthTrcv_Prv_RequestedPhyLoopbackMode[lTrcvIdx_u8] = ETHTRCV_PHYLOOPBACK_NONE;
        EthTrcv_Prv_CurrentPhyLoopbackMode[lTrcvIdx_u8]   = ETHTRCV_PHYLOOPBACK_NONE;
        /* Initially the Phy access is made as ETHTRCV_PHYACCESS_NOT_AVAILABLE. After the Phy is successfully identified,
         * then this global variable will be made as ETHTRCV_PHYACCESS_AVAILABLE
         */
        EthTrcv_Prv_PhyAccessStatus_e[lTrcvIdx_u8]        = ETHTRCV_PHYACCESS_NOT_AVAILABLE;
 #endif
#endif
    }
}
/**
 ***************************************************************************************************
 * \moduledescription
 * This function configures the transceiver
 *
 * \arg     TrcvIdx                     identifies Transceiver to which the API has to be applied
 * \arg     CfgIdx                      Not used in current implementation
 * \return     E_OK:                    The state request was successful (no DET error occured)
 *             E_NOT_OK:                The state request could not be executed because of DET
 * \see
 * \note
 ***************************************************************************************************
 */
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_TransceiverInit(uint8 TrcvIdx, uint8 CfgIdx)
{
    Std_ReturnType RetVal_o = E_OK;
    uint16 CfgNo;
    boolean access = FALSE;

    /* DET checks */
    /* Check if TrcvIdx passed is within the maximum range */
    ETHTRCV_CHECKDETTRUE_RETURN((TrcvIdx < ETHTRCV_NUMBER_OF_ETHTRCV), TrcvIdx, ETHTRCV_SID_TRANSCEIVERINIT, ETHTRCV_E_INV_TRCV_IDX);
    /* Check if EthTrcv_Init wasn't called previously -> ETHTRCV_STATE_INIT */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx],ETHTRCV_STATE_INIT,TrcvIdx,ETHTRCV_SID_TRANSCEIVERINIT);
    /* Check if the CfgIdx passed is withing the maximum range */
    ETHTRCV_CHECKDETTRUE_RETURN((CfgIdx <= EthTrcv_Cfg_TrcvInit_po[TrcvIdx].CfgNoEnd ), CfgIdx, ETHTRCV_SID_TRANSCEIVERINIT, ETHTRCV_E_INVALID_INDEX);

    CfgNo = EthTrcv_Cfg_TrcvInit_po[TrcvIdx].CfgNoStart + CfgIdx; // No into EthTrcv_Cfg_CfgInit_ast
    EthTrcv_InitCfgNo_au16[TrcvIdx] = CfgNo;

    /* Start Initialization of Phy */
    /* Check if communication is already running. If yes, only set a flag and start init later */
    SchM_Enter_EthTrcv_MiiCommunication();
    if(EthTrcv_Prv_MiiCommunicationFlag_b == FALSE)
    {
        EthTrcv_Prv_MiiCommunicationFlag_b = TRUE;
        access = TRUE;
    }
    else
    {
        EthTrcv_Prv_InitState_e[TrcvIdx] = ETHTRCV_INITSTATE_INITREQ;
    }
    SchM_Exit_EthTrcv_MiiCommunication();

    // Start communication. This code is outside upper if--condition because of interrupt-lock
    if (access == TRUE)
    {
        EthTrcv_Prv_InitState_e[TrcvIdx] = ETHTRCV_INITSTATE_INITRUN;
        EthTrcv_Prv_MiiCommunicationPos  = EthTrcv_Cfg_CfgInit_po[CfgNo].AdrNoInit;

        EthTrcv_WriteMiiIndication(EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvCtrlIdx,                    /* CtrlIdx */
                                   EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvMiiIdx,                     /* MiiIdx */
                                   EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].adr);   /* RegIdx */

        /* Check for Phy Access. If Phy access is available then transceiver Init is done, return E_OK else transceiver
         * Init is not done successfully and hence return E_NOT_ok
         */
        #if (ETHTRCV_TJA1100_USED == STD_ON)
           if(EthTrcv_Prv_PhyAccessStatus_e[TrcvIdx] == ETHTRCV_PHYACCESS_AVAILABLE )
           {
               /* Transceiver Init is done */
               EthTrcv_Prv_State_e[TrcvIdx] = ETHTRCV_STATE_ACTIVE;         // [ETHTRCV036]
               /* Phy Access is Available */
               RetVal_o = E_OK;
           }
           else
           {
               /* Transceiver Init cannot be done since Phy access is not available */
               EthTrcv_Prv_State_e[TrcvIdx] = ETHTRCV_STATE_INIT;         // [ETHTRCV036]
               /* Phy Access is Not Available */
               RetVal_o = E_NOT_OK;
           }
        #else
           /* Error handling(Phy access check) is not supported for other Transceivers and hence Init is assumed to be done */
           EthTrcv_Prv_State_e[TrcvIdx] = ETHTRCV_STATE_ACTIVE;         // [ETHTRCV036]
           /* Phy Access is Available */
           RetVal_o = E_OK;
        #endif
    }

    return RetVal_o;
}
/**
 ***************************************************************************************************
 * \moduledescription
 * FOR TJA1100 set EN Pin and WAKE Pin
 *
 * \arg        -
 * \return     -
 *
 * \see
 * \note
 ***************************************************************************************************
 */
#if (ETHTRCV_TJA1100_USED == STD_ON)
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_InitFct1(void)
{
    uint8 TrcvIdx = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    Dio_WriteChannel(EthTrcv_Cfg_TJA1100_ast[TrcvIdx].EnablePin, STD_HIGH);

    // To ensure wakeup after Undervoltage -> sleep: create a falling edge on wake-pin
    if(EthTrcv_Cfg_TJA1100_ast[TrcvIdx].WakePin != (Dio_ChannelType)EthTrcv_NO_DIO)
    {
        Dio_WriteChannel(EthTrcv_Cfg_TJA1100_ast[TrcvIdx].WakePin, STD_HIGH);
        Dio_WriteChannel(EthTrcv_Cfg_TJA1100_ast[TrcvIdx].WakePin, STD_LOW);
    }
}

/**
 ***************************************************************************************************
 * \moduledescription
 * For TJA1100: Wait until a registervalue can be read. (Read Reg21 bit3 = undervolt detection)
 * Read Interrupt Status Register and store PWON
 *
 * \arg        -
 * \return     -
 *
 * \see
 * \note   This function will be changed in future. It is used for SampleA of TJA1100.
 *         For this silizium EthTrcv_Prv_InitFct3 is used. After finial silizium this function has to be adapted.
 ***************************************************************************************************
 */
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_InitFct2(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint8  TrcvIdx;

    if( (EthTrcv_Prv_Buff0 & EthTrcv_Cfg_CfgData_ast[pos].data) != 0)   // Reg 21 Bit3 = UV_ERR 0=no undervolt
    {                                               // if still undervolt detected,
        EthTrcv_Prv_MiiCommunicationPos --;         // the same command shall be executed
        EthTrcv_Prv_Buff1++;                        // counter for timeout increased
        if (EthTrcv_Prv_Buff1 >= (ETHTRCV_TJA1100_UNDERVOLTDETECTION_TIMEOUT_US / 23)) // Divided by 20 because each
        {                                                                              // transmission takes about 23usec This timing is not exact!!!
            EthTrcv_Prv_MiiCommunicationPos++;                                         // continue
            ETHTRCV_CHECKDETTRUE_NORETURN( ETHTRCV_FALSE_B, (uint8)pos, ETHTRCV_SID_PRV_PRV_INITFCT2, ETHTRCV_E_MII_TIMEOUT_READ);
        }
    }
    else
    {
        // Store Wakeup reason (also stored in reg21)
        // Get current TrcvIdx
        TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;
        if((EthTrcv_Prv_Buff0 & 0x8000uL) != 0uL)
        {
            EthTrcv_Prv_WupReason_e[TrcvIdx] = ETHTRCV_WUP_POWON;
        }
        else
        {
            EthTrcv_Prv_WupReason_e[TrcvIdx] = ETHTRCV_WUP_NOT_SUPPORTED;
        }
    }
    return;
}
#endif
/**
 ***************************************************************************************************
 * \moduledescription
 * This function sets the mode of the requested transceiver. It only stores the request. The request is executed in main-function
 *
 * \arg     TrcvIdx             identifies Transceiver to which the API has to be applied
 * \arg     CtrlMode            Requested state of the transceiver
 * \return     E_OK:            The state can be evaluated
 *             E_NOT_OK:        The state could not be evaluated, either because of transceiver error
 *                              or wrong parameters
 * \see
 * \note    possible values are: ETHTRCV_MODE_DOWN, ETHTRCV_MODE_ACTIVE
 ***************************************************************************************************
 */
#if ( ETHTRCV_CFG_SET_TRANSCEIVERMODE_API == STD_ON)
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetTransceiverMode(uint8 TrcvIdx, EthTrcv_ModeType CtrlMode)
{
    Std_ReturnType RetVal_o = E_OK;

    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_SETTRANSCEIVERMODE);
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_SETTRANSCEIVERMODE);

    EthTrcv_Prv_RequestedMode[TrcvIdx] = CtrlMode;

    return RetVal_o;
}
#endif
/**
 ***************************************************************************************************
 * \moduledescription
 * This function returns the stored current mode a the requested transceiver. Mode is read out in main-function
 *
 * \arg     TrcvIdx                 identifies Transceiver to which the API has to be applied
 * \arg     TrcvModePtr             Evaluated mode
 * \return     E_OK:                The wakeup reason can be evaluated
 *             E_NOT_OK:            The wakeup reason could not be evaluated, either because of transceiver error
 *                                  or wrong parameters
 * \see
 * \note    possible values are: ETHTRCV_MODE_DOWN, ETHTRCV_MODE_ACTIVE
 ***************************************************************************************************
 */
#if ( ETHTRCV_CFG_GET_TRANSCEIVERMODE_API == STD_ON)
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetTransceiverMode(uint8 TrcvIdx, EthTrcv_ModeType* TrcvModePtr)
{
    Std_ReturnType RetVal_o = E_OK;

    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_GETTRANSCEIVERMODE);
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_GETTRANSCEIVERMODE);
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, TrcvModePtr, ETHTRCV_SID_GETTRANSCEIVERMODE);

    *TrcvModePtr = EthTrcv_Prv_CurrentMode[TrcvIdx];

    return RetVal_o;
}
#endif
/**
 ***************************************************************************************************
 * \moduledescription
 * restart the automatic negotiation of the transmission parameters. It only stores a flag. Request is executed in main function
 *
 * \arg     TrcvIdx         identifies Transceiver to which the API has to be applied
 * \return  E_OK:           The wakeup reason can be changed
 *          E_NOT_OK:       Error orrcured
 * \see
 * \note    The  function  is  not  required  or  called  by  an  upper  layer  BSW  software component
 ***************************************************************************************************
 */
#if ( ETHTRCV_CFG_START_AUTONEGOTIATION_API == STD_ON)
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_StartAutoNegotiation(uint8 TrcvIdx)
{
    Std_ReturnType RetVal_o = E_OK;
    uint16  CfgNo;

    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_STARTAUTONEGOTIATION);
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_STARTAUTONEGOTIATION);

    CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvIdx];
    // Check, if autoneg is allowed per configuration
    if(EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvAutoNegotiationEnabled == ETHTRCV_AUTONEGOTIATIONENABLED )
    {
        EthTrcv_Prv_AutoNegotiationReq[TrcvIdx] = TRUE;
    }
    else
    {
        ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, TrcvIdx, ETHTRCV_SID_STARTAUTONEGOTIATION, ETHTRCV_E_INV_CONFIG_INV_PARAM);
        RetVal_o = E_NOT_OK;
    }

    return RetVal_o;
}
#endif
/**
 ***************************************************************************************************
 * \moduledescription
 * This function reads the current transceiver link state. It gives back a stored value. The value is updated in main function
 *
 * \arg     TrcvIdx             identifies Transceiver to which the API has to be applied
 * \return     E_OK:            The wakeup occured
 *             E_NOT_OK:        The wakeup not occured
 * \see
 * \note    possible values are: ETHTRCV_LINK_STATE_DOWN, ETHTRCV_LINK_STATE_ACTIVE
 ***************************************************************************************************
 */
#if ( ETHTRCV_CFG_GET_LINKSTATE_API == STD_ON)
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetLinkState(uint8 TrcvIdx,EthTrcv_LinkStateType* LinkStatePtr)
{
    Std_ReturnType RetVal_o = E_OK;

    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_GETLINKSTATE);
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_GETLINKSTATE);
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, LinkStatePtr, ETHTRCV_SID_GETLINKSTATE);

    if( EthTrcv_Prv_LinkState[TrcvIdx] != ETHTRCV_LINK_STATE_UNDEF)
    {
        *LinkStatePtr = EthTrcv_Prv_LinkState[TrcvIdx];
    }
    else
    {
        RetVal_o = E_NOT_OK;
    }

    return RetVal_o;
}
#endif
/**
 ***************************************************************************************************
 * \moduledescription
 * This function reads the current transceiver baud rate. It gives back a stored value. Value is written in main function
 *
 * \arg     TrcvIdx                 identifies Transceiver to which the API has to be applied
 * \arg     BaudRatePtr             identifies Transceiver to which the API has to be applied
 * \return     E_OK:                The wakeup occured
 *             E_NOT_OK:            The wakeup not occured
 * \see
 * \note    The function is not required or called by an upper layer BSW software component.
 *          possible values are: ETHTRCV_BAUD_RATE_10MBIT, ETHTRCV_BAUD_RATE_100MBIT
 ***************************************************************************************************
 */
#if ( ETHTRCV_CFG_GET_BAUDRATE_API == STD_ON)
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetBaudRate(uint8 TrcvIdx, EthTrcv_BaudRateType *BaudRatePtr)
{
    Std_ReturnType RetVal_o = E_OK;

    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_GETBAUDRATE);
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_GETBAUDRATE);
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, BaudRatePtr, ETHTRCV_SID_GETBAUDRATE);

    if( EthTrcv_Prv_BaudRate[TrcvIdx] != ETHTRCV_BAUD_RATE_UNDEF)
    {
        *BaudRatePtr = EthTrcv_Prv_BaudRate[TrcvIdx];
    }
    else
    {
        RetVal_o = E_NOT_OK;
    }

    return RetVal_o;
}
#endif
/**
 ***************************************************************************************************
 * \moduledescription
 * This function reads the current transceiver duplex mode. It gives back a stored value. The value is updated in main function
 *
 * \arg     TrcvIdx                 identifies Transceiver to which the API has to be applied
 * \arg     DuplexModePtr           gives back the current duplex mode
 * \return     E_OK:                The wakeup occured
 *             E_NOT_OK:            The wakeup not occured
 * \see
 * \note    The function is not required or called by an upper layer BSW software component.
 *          possible values are: ETHTRCV_DUPLEX_MODE_HALF,  ETHTRCV_DUPLEX_MODE_FULL
 ***************************************************************************************************
 */
#if ( ETHTRCV_CFG_GET_DUPLEXMODE_API == STD_ON)
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetDuplexMode(uint8 TrcvIdx, EthTrcv_DuplexModeType *DuplexModePtr)
{
    Std_ReturnType RetVal_o = E_OK;

    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_GETDUPLEXMODE);
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_GETDUPLEXMODE);
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, DuplexModePtr, ETHTRCV_SID_GETDUPLEXMODE);

    if( EthTrcv_Prv_DuplexMode[TrcvIdx] != ETHTRCV_DUPLEX_MODE_UNDEF)
    {
        *DuplexModePtr = EthTrcv_Prv_DuplexMode[TrcvIdx];
    }
    else
    {
        RetVal_o = E_NOT_OK;
    }

    return RetVal_o;
}
#endif

#if defined(ETHTRCV_TJA1100_USED)
 #if (ETHTRCV_TJA1100_USED == STD_ON)
/**
*******************************************************************************************************
* Function name:  EthTrcv_SetPhyTestMode
* Description:    This function sets the test mode for the requested transceiver.
*
*
* \arg        TrcvIdx          Identifies Transceiver to which the API has to be applied
* \arg        Mode             Requested test mode for the transceiver
* \return     E_OK:            The request has been accepted
*             E_NOT_OK:        The request has not been accepted.
*
* \note       possible values are:     ETHTRCV_PHYTESTMODE_NONE,
                                       ETHTRCV_PHYTESTMODE_1,
                                       ETHTRCV_PHYTESTMODE_2,
                                       ETHTRCV_PHYTESTMODE_3,
                                       ETHTRCV_PHYTESTMODE_4,
                                       ETHTRCV_PHYTESTMODE_5
*******************************************************************************************************
*/
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetPhyTestMode(    VAR( uint8, AUTOMATIC )     TrcvIdx,
                                                              VAR( EthTrcv_PhyTestModeType, AUTOMATIC )         Mode )

{
    Std_ReturnType  Result_o;
    uint16          CfgNo;

    Result_o = E_NOT_OK;
    /* DET checks */
    /* check if TrcvIdx is within the maximum range */
    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_SETPHYTESTMODE);
    /* This check is required since the global structure initialization is required for running the test mode */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_SETPHYTESTMODE);
    /* AR does not specify a return from the function, but it seems to be reasonable */
    /* As per IEEE standards, supported test modes are only TestMode 1 to TestMode 5. Any other value is illegal */
    ETHTRCV_CHECKDETTRUE_RETURN(( Mode <= ETHTRCV_PHYTESTMODE_5), TrcvIdx, ETHTRCV_SID_SETPHYTESTMODE,ETHTRCV_E_NOT_SUPPORTED);

    /* The requested mode is updated into the global variable */
    EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx] = Mode;

    CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvIdx];

    /* Request is accepted only if the Requested test mode is other than the current test mode */
    if(EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx] != EthTrcv_Prv_CurrentPhyTestMode[TrcvIdx])
    {
        if(EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx] != ETHTRCV_PHYTESTMODE_NONE)
        {
            /* command position for enabling the Test modes */
            EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].AdrNoEnTestMode;
        }
        else
        {
            /* Command position for disabling the Test modes and entering into normal operation*/
            EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].AdrNoDisTestMode;

        }

        /* Enable the MDIO communication */
        EthTrcv_Prv_MiiCommunicationFlag_b = TRUE;

        /* Currently Sync support is given only */
        EthTrcv_WriteMiiIndication(EthTrcv_Cfg_CfgInit_po[TrcvIdx].EthTrcvCtrlIdx,
                                   EthTrcv_Cfg_CfgInit_po[TrcvIdx].EthTrcvMiiIdx, 0);

        /* If Current mode is same as Requested mode, then return E_OK else E_NOT_OK is returned */
        if (EthTrcv_Prv_CurrentPhyTestMode[TrcvIdx] == EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx])
        {
            Result_o = E_OK;
        }
    }
    else
    {
        /* Current PhyTestMode is already same as Requested PhyTestMode */
        Result_o = E_OK;
    }

    return Result_o;
}


/**
*******************************************************************************************************
* Function name:  EthTrcv_SetPhyLoopbackMode
* Description:    This function sets the loopback mode for the requested transceiver.
*
*
* \arg        TrcvIdx          Identifies Transceiver to which the API has to be applied
* \arg        Mode             Requested loopback mode for the transceiver
* \return     E_OK:            The request has been accepted
*             E_NOT_OK:        The request has not been accepted.
*
* \note       possible values are:     ETHTRCV_PHYLOOPBACK_NONE,
                                       ETHTRCV_PHYLOOPBACK_INTERNAL,
                                       ETHTRCV_PHYLOOPBACK_EXTERNAL,
                                       ETHTRCV_PHYLOOPBACK_REMOTE
*******************************************************************************************************
*/
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetPhyLoopbackMode(    VAR( uint8,                       AUTOMATIC ) TrcvIdx,
                                                                  VAR( EthTrcv_PhyLoopbackModeType, AUTOMATIC ) Mode )

{
    Std_ReturnType  Result_o;
    uint16          CfgNo;

    Result_o = E_NOT_OK;
    /* DET checks */
    /* check if TrcvIdx is within the maximum range */
    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_SETPHYLOOPBACKMODE);
    /* This check is required since the global structure initialization is required for running the loopback mode */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_SETPHYLOOPBACKMODE);
    /* AR does not specify a return from the function, but it seems to be reasonable */
    /* As per IEEE standards, supported loopback modes are only internal, external and remote. Any other value is illegal */
    ETHTRCV_CHECKDETTRUE_RETURN(( Mode <= ETHTRCV_PHYLOOPBACK_REMOTE), TrcvIdx, ETHTRCV_SID_SETPHYLOOPBACKMODE,ETHTRCV_E_NOT_SUPPORTED);

    /* The requested loopback mode is updated into the global variable */
    EthTrcv_Prv_RequestedPhyLoopbackMode[TrcvIdx] = Mode;

    CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvIdx];

    /* Request is accepted only if the Requested loopback mode is other than the current loopback mode */
    if (EthTrcv_Prv_RequestedPhyLoopbackMode[TrcvIdx] != EthTrcv_Prv_CurrentPhyLoopbackMode[TrcvIdx])
    {
        if (EthTrcv_Prv_RequestedPhyLoopbackMode[TrcvIdx] != ETHTRCV_PHYLOOPBACK_NONE)
        {
            /* command position for enabling the Phy loopback modes */
            EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].CommandPosEnPhyLoopbackMode;
        }
        else
        {
            /* Command position for disabling the Phy loopback modes and entering into normal operation*/
            EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].CommandPosDisPhyLoopbackMode;
        }

        /* Enable the MDIO communication */
        EthTrcv_Prv_MiiCommunicationFlag_b = TRUE;

        /* Currently Sync support is given only */
        EthTrcv_WriteMiiIndication(EthTrcv_Cfg_CfgInit_po[TrcvIdx].EthTrcvCtrlIdx,
                EthTrcv_Cfg_CfgInit_po[TrcvIdx].EthTrcvMiiIdx, 0);

        /* If Current mode is same as Requested mode, then return E_OK else E_NOT_OK is returned */
        if (EthTrcv_Prv_CurrentPhyLoopbackMode[TrcvIdx] == EthTrcv_Prv_RequestedPhyLoopbackMode[TrcvIdx])
        {
            Result_o = E_OK;
        }
    }
    else
    {
        /* Current LoopbackMode is already same as Requested Loopback mode */
        Result_o = E_OK;
    }

    return Result_o;
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_GetCableDiagnosticsResult
* Description:    This function retrieves the cable diagnostics result of a given transceiver.
*
* Parameter In:
* \param     TrcvIdx          Index of the transceiver within the context of the Ethernet Transceiver Driver
*
*
* Parameter Out:
* \param     RegValPtr_pu16   Pointer to the location where the cable diagnostics result shall be stored
*
*\return     E_OK:            The request has been accepted
*            E_NOT_OK:        The request has not been accepted.
*
* \note      possible values are:      ETHTRCV_CABLEDIAG_OK,
                                       ETHTRCV_CABLEDIAG_ERROR,
                                       ETHTRCV_CABLEDIAG_SHORT,
                                       ETHTRCV_CABLEDIAG_OPEN
* Steps:
* 1: Read Register 18 to determine whether the Phy is in managed/autonomous operation
* 2: If phy is in autonomous operation,
*      2.1 Enable Configuration register access by writing 1 to bit 3 in Reg 17
*      2.2 Write 0 to Bit 14 of Reg 18 to enable the managed operation
*      2.3 Disable Configuration register access by writing 0 to bit 3 in Reg 17 - to be checked
* 3: If phy is in managed operation, no updates required for Reg 18
* 4. Disable Link Control bit 15 of Reg 17 for running cable test
* 5. Enable cable test by writing 1 to bit 5 of Reg 17
* 6. wait for cable test to get finished
* 7. Read cable test result from Reg 25
*
*******************************************************************************************************
*/

FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetCableDiagnosticsResult( uint8 TrcvIdx, EthTrcv_CableDiagResultType* ResultPtr )
{
    Std_ReturnType  Result_o;
    uint16          CfgNo;

    /* DET checks */
    /* check if TrcvIdx is within the maximum range */
    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_GETCABLEDIAGNOSTICSRESULT);
    /* This check is required since the global structure initialization is required for running the test mode */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_GETCABLEDIAGNOSTICSRESULT);
    /* check if provided pointer is a NULL pointer*/
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, ResultPtr, ETHTRCV_SID_GETCABLEDIAGNOSTICSRESULT);

    CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvIdx];

    /* command position for Cable test*/
    EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].AdrNoCableTest;

    /* Enable the MDIO communication */
    EthTrcv_Prv_MiiCommunicationFlag_b = TRUE;

    /* Cable diagnostic test is requested for the given TrcvIdx */
    EthTrcv_Prv_CableDiagRequested[TrcvIdx] = TRUE;

    /* Currently, only Sync support is given  */
    EthTrcv_WriteMiiIndication(EthTrcv_Cfg_CfgInit_po[TrcvIdx].EthTrcvCtrlIdx,
                               EthTrcv_Cfg_CfgInit_po[TrcvIdx].EthTrcvMiiIdx, 0);

    *ResultPtr = EthTrcv_Prv_CableDiagResult[TrcvIdx];

    Result_o = E_OK;

    return Result_o;

}

/**
*******************************************************************************************************
* Function name:  EthTrcv_GetPhySignalQuality
* Description:    This function retrieves the cable signal quality for a given transceiver.
*
* Parameter In:
* \param     TrcvIdx          Index of the transceiver within the context of the Ethernet Transceiver Driver
*
*
* Parameter Out:
* \param     RegValPtr_pu16   Pointer to the memory where the signal quality in percent shall be stored.
*
*\return     E_OK:            The request has been accepted
*            E_NOT_OK:        The request has not been accepted.
*

* Steps:
* 1: Read Register 23 to determine the phy signal quality for TJA1100 EthTrcv
*
*******************************************************************************************************
*/
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetPhySignalQuality( uint8 TrcvIdx, uint8* SignalQualityPtr )
{
    Std_ReturnType  Result_o = E_NOT_OK;
    uint16          CfgNo;

    /* DET checks */
    /* check if TrcvIdx is within the maximum range */
    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_GETPHYSIGNALQUALITY);
    /* This check is required since the global structure initialization is required for running the test mode */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_GETPHYSIGNALQUALITY);
    /* check if provided pointer is a NULL pointer*/
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, SignalQualityPtr, ETHTRCV_SID_GETPHYSIGNALQUALITY);

    CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvIdx];

    /* Command position for getting the signal quality */
    EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].AdrNoPhySignalQuality;

    /* Enable the MDIO communication */
    EthTrcv_Prv_MiiCommunicationFlag_b = TRUE;

    /* Currently, only Sync support is given  */
    EthTrcv_WriteMiiIndication(EthTrcv_Cfg_CfgInit_po[TrcvIdx].EthTrcvCtrlIdx,
                               EthTrcv_Cfg_CfgInit_po[TrcvIdx].EthTrcvMiiIdx, 0);

    *SignalQualityPtr = EthTrcv_Prv_CableSignalQuality_u8[TrcvIdx];

    Result_o = E_OK;

    return Result_o;

}

/**
*******************************************************************************************************
* Function name:  EthTrcv_GetPhyIdentifier
* Description:    This function retrieves the OrguniqueId, Model Number and Revision Number for a given transceiver.
*
* Parameter In:
* \param     TrcvIdx          Index of the transceiver within the context of the Ethernet Transceiver Driver
*
*
* Parameter Out:
* \param     OrgUniqueIdPtr   Pointer to the memory where the Organizationally Unique Identifier shall be stored.
* \param     ModelNrPtr       Pointer to the memory where the Manufacturer's Model Number shall be stored.
* \param     RevisionNrPtr    Pointer to the memory where the Revision Number shall be stored.
*
*\return     E_OK:            The request has been accepted
*            E_NOT_OK:        The request has not been accepted.
*

* Steps:
* 1: Read Register 2 and 3 to extract the OrguniqueId, Model Number and Revision Number for a given transceiver
*
*******************************************************************************************************
*/
FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetPhyIdentifier(uint8 TrcvIdx, uint32* OrgUniqueIdPtr, uint8* ModelNrPtr, uint8* RevisionNrPtr)
{
    Std_ReturnType  Result_o = E_NOT_OK;

    /* DET checks */
    /* check if TrcvIdx is within the maximum range */
    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx, ETHTRCV_SID_GETPHYIDENTIFIER);
    /* This check is required since the global structure initialization is required for running the test mode */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx], ETHTRCV_STATE_ACTIVE, TrcvIdx, ETHTRCV_SID_GETPHYIDENTIFIER);
    /* check if provided pointer is a NULL pointer*/
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, OrgUniqueIdPtr, ETHTRCV_SID_GETPHYIDENTIFIER);
    /* check if provided pointer is a NULL pointer*/
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, ModelNrPtr, ETHTRCV_SID_GETPHYIDENTIFIER);
    /* check if provided pointer is a NULL pointer*/
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx, RevisionNrPtr, ETHTRCV_SID_GETPHYIDENTIFIER);

    /* Updating the pointers with the identifier values stored in global variables during Initialization*/
    *OrgUniqueIdPtr = EthTrcv_Prv_PhyIdentifier_au32[TrcvIdx].Phy_OrgUniqueId_u32;
    *ModelNrPtr     = EthTrcv_Prv_PhyIdentifier_au32[TrcvIdx].Phy_ModelNumber_u8;
    *RevisionNrPtr  = EthTrcv_Prv_PhyIdentifier_au32[TrcvIdx].Phy_RevisionNumber_u8;

    Result_o = E_OK;

    return Result_o;

}
/**
***********************************************************************************************************************
* Function name:  EthTrcv_WritePhyRegister
* Description:    Writes the indexed transceiver register with the input value; uses Eth_WriteMii api provided by Eth
* \par Service ID 0x54, Synchronous, Non Reentrant
*
* Parameter In:
* \param CtrlIdx_u8        Index of the controller within the context of the Ethernet Driver
* \param TrcvIdx_u8        Index of the transceiver on the MII
* \param RegIdx_u8         Index of the transceiver register on the MII
* \param RegVal_u16        Value to be written into the indexed register
*
* Parameter Out:           none
*
*
* \return Std_ReturnType       E_OK: MII register written
*                              E_NOT_OK: MII register write failure
*
* Remarks: The MII behaviour of the Eth driver must be Sync. Once these apis are used to update registers of the
*          transceiver, the Phy state cannot be determined by the EthTrcv driver and hence a re-initialization
*          would be requried.
*
***********************************************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) EthTrcv_WritePhyRegister( VAR(uint8, AUTOMATIC)               CtrlIdx_u8,
                                                         VAR(uint8, AUTOMATIC)               TrcvIdx_u8,
                                                         VAR(uint8, AUTOMATIC)               RegIdx_u8,
                                                         VAR(uint16, AUTOMATIC)              RegVal_u16 )
{
    Std_ReturnType Result_o;

    /* DET checks */
    /* check if TrcvIdx is within the maximum range */
    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx_u8, ETHTRCV_SID_WRITEPHYREGISTER);
    /* This check is required since the global structure initialization is required for running the test mode */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx_u8], ETHTRCV_STATE_ACTIVE, TrcvIdx_u8, ETHTRCV_SID_WRITEPHYREGISTER);

    /* Call Eth_WriteMii api for reading out the register value through MDIO communication */
    Result_o = Eth_WriteMii(CtrlIdx_u8, TrcvIdx_u8, RegIdx_u8, RegVal_u16);

    return Result_o;

}

/**
*******************************************************************************************************
* Function name:  EthTrcv_ReadPhyRegister
* Description:    Reads the indexed transceiver register value; uses Eth_ReadMii api provided by Eth
* \par Service ID 0x53, Synchronous, Non Reentrant
*
* Parameter In:
* \param CtrlIdx_u8        Index of the controller within the context of the Ethernet Driver
* \param TrcvIdx_u8        Index of the transceiver on the MII
* \param RegIdx_u8         Index of the transceiver register on the MII
*
* Parameter Out:
* \param RegValPtr_pu16    Filled with the register content of the indexed register
*
* \return Std_ReturnType       E_OK: MII register written
*                              E_NOT_OK: MII register write failure
*
* Remarks: The MII behaviour shall be Sync.
*
*******************************************************************************************************
*/

FUNC(Std_ReturnType, ETH_CODE) EthTrcv_ReadPhyRegister( VAR(uint8, AUTOMATIC)               CtrlIdx_u8,
                                                        VAR(uint8, AUTOMATIC)               TrcvIdx_u8,
                                                        VAR(uint8, AUTOMATIC)               RegIdx_u8,
                                                        P2VAR(uint16, AUTOMATIC, AUTOMATIC) RegValPtr_pu16 )
{
    Std_ReturnType Result_o;
    /* DET checks */
    /* check if TrcvIdx is within the maximum range */
    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx_u8, ETHTRCV_SID_READPHYREGISTER);
    /* This check is required since the global structure initialization is required for running the test mode */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx_u8], ETHTRCV_STATE_ACTIVE, TrcvIdx_u8, ETHTRCV_SID_READPHYREGISTER);
    /* check if provided pointer is a NULL pointer*/
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx_u8, RegValPtr_pu16, ETHTRCV_SID_READPHYREGISTER);

    /* Call Eth_ReadMii api for reading out the register value through MDIO communication */
    Result_o = Eth_ReadMii(CtrlIdx_u8, TrcvIdx_u8, RegIdx_u8, RegValPtr_pu16);

    return Result_o;

}


/**
*******************************************************************************************************
* Function name:  EthTrcv_GetLinkStatistics
* Description:    Extracts the link statistics from the indexed transceiver
* \par Service ID 0x55, Synchronous, Non Reentrant
*
* Parameter In:
* \param TrcvIdx_u8        Index of the transceiver on the MII
*
* Parameter Out:
* \param LinkStats_pst    Filled with the Link statistics values for the indexed register
*
* \return Std_ReturnType       E_OK: Success
*                              E_NOT_OK: link statistics could not be obtained
*
* Remarks: The MII behaviour shall be Sync.
*
*******************************************************************************************************
*/
FUNC(Std_ReturnType, ETH_CODE) EthTrcv_GetLinkStatistics( VAR  (uint8,                                 AUTOMATIC) TrcvIdx_u8,
                                                          P2VAR(EthTrcv_LinkStatisticsType, AUTOMATIC, AUTOMATIC) LinkStats_pst)
{
    Std_ReturnType  Result_o;
    uint16          CfgNo;


    /* DET checks */
    /* check if TrcvIdx is within the maximum range */
    ETHTRCV_CHECKDETTRCVIDX_RETURN(TrcvIdx_u8, ETHTRCV_SID_GETLINKSTATISTICS);
    /* This check is required since the global structure initialization is required for running the test mode */
    ETHTRCV_CHECKDETINIT_RETURN(EthTrcv_Prv_State_e[TrcvIdx_u8], ETHTRCV_STATE_ACTIVE, TrcvIdx_u8, ETHTRCV_SID_GETLINKSTATISTICS);
    /* check if provided pointer is a NULL pointer*/
    ETHTRCV_CHECKDETNULLPTR_RETURN(TrcvIdx_u8, LinkStats_pst, ETHTRCV_SID_GETLINKSTATISTICS);

    SchM_Enter_EthTrcv_MiiCommunication();
    /* Get the Config Index for the indexed transceiver */
    CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvIdx_u8];
    /* command position for Cable test*/
    EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].CommandPosGetLinkStatistics;
    /* Enable the MDIO communication */
    EthTrcv_Prv_MiiCommunicationFlag_b = TRUE;
    SchM_Exit_EthTrcv_MiiCommunication();

    /* Currently, only Sync support is given  */
    EthTrcv_WriteMiiIndication(EthTrcv_Cfg_CfgInit_po[TrcvIdx_u8].EthTrcvCtrlIdx,
                               EthTrcv_Cfg_CfgInit_po[TrcvIdx_u8].EthTrcvMiiIdx, 0);

    SchM_Enter_EthTrcv_MiiCommunication();
    /* Getting the link statistics */
    LinkStats_pst->etherStatslinklosses_u8     = EthTrcv_Prv_LinkStatistics_ast[TrcvIdx_u8].etherStatslinklosses_u8;
    LinkStats_pst->etherStatsSymbolFailure_u16 = EthTrcv_Prv_LinkStatistics_ast[TrcvIdx_u8].etherStatsSymbolFailure_u16;
    SchM_Exit_EthTrcv_MiiCommunication();

    Result_o = E_OK;

    return Result_o;
}
 #endif
#endif


/**
 ***************************************************************************************************
 * \moduledescription
 * This service returns the version information of this module.
 *
 * \arg     versioninfo                  maps to Buffer of version information
 * \return  void
 * \see
 * \note
 ***************************************************************************************************
 */
#if (ETHTRCV_GET_VERSION_INFO == STD_ON)
# if(ETHTRCV_VERSION_INFO_API_MACRO == STD_OFF)
FUNC (void, ETHTRCV_CODE) EthTrcv_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr)
{
    ETHTRCV_CHECKDETNULLPTR_RETURN_NO_VAL(0,VersionInfoPtr,ETHTRCV_SID_GETVERSIONINFO);

    if(VersionInfoPtr != NULL_PTR)
    {
        VersionInfoPtr->vendorID         = ETHTRCV_VENDOR_ID;
        VersionInfoPtr->moduleID         = ETHTRCV_MODULE_ID;
        VersionInfoPtr->sw_major_version = ETHTRCV_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = ETHTRCV_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = ETHTRCV_SW_PATCH_VERSION;
    }
}
# endif
#endif

/**
*******************************************************************************************************
* Function name:  EthTrcv_ReadMiiIndication
* Description:    Called when information has been read out via MII interface. Triggered by
*                 previous Eth_ReadMii call. Can directly be called within Eth_ReadMii.
* \arg          - CtrlIdx   Index of the controller within the context of the Ethernet Driver
* \arg          - TrcvIdx   Index of the transceiver on the MII
* \arg          - RegIdx    Index of the transceiver register on the MII
* \arg          - RegVal    Value contained in the indexed register
* Returns:      -
* Reentrancy:   - Non Reentrant for the same CtrlIdx, (reentrant for different)
* Remarks:      Could call Eth_ReadMii Eth_WriteMii. If called out of Eth_ReadMii could lead to increased stack consumption
*               As all trcv (even for multi controller) are handled sequentiell, reentrancy is not requried
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_ReadMiiIndication( uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal)
{
    uint8   TrcvNo;
    uint16  pos;        // position through EthTrcv_Cfg_CfgData_ast.
    uint16  CfgNo;
    EthTrcv_Prv_Cmd_ten cmd;
    uint8   CtrlNo;
    uint8   MiiIdx;
    uint16  timeout = 0;    // count how many Read/WriteMii can be returned with NOT_OK

    pos     = EthTrcv_Prv_MiiCommunicationPos;
    if(EthTrcv_Prv_MiiCommunicationFlag_b == FALSE)
    {
        ETHTRCV_CHECKDETTRUE_NORETURN((ETHTRCV_FALSE_B), (uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_INV_CONFIG_COMM_NOT_RUNNING);
    }
    ETHTRCV_CHECKDETTRUE_RETURN_NO_VAL((pos < ETHTRCV_NUMBER_OF_CFGDATA), (uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_POS);

    CfgNo  =  EthTrcv_InitCfgNo_au16[EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx];
    
    ETHTRCV_CHECKDETTRUE_RETURN_NO_VAL((
        (CtrlIdx == EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvCtrlIdx) &&
        (TrcvIdx == EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvMiiIdx)  &&
        (RegIdx  == EthTrcv_Cfg_CfgData_ast[pos].adr)) ,(uint8)pos,ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_PARAM);

    (void)CtrlIdx;  // not required if no DET
    (void)TrcvIdx;  // not required if no DET
    (void)RegIdx;   // not required if no DET
    //******************  store current read value ***************************************
    EthTrcv_Prv_Buff0 = RegVal;

    /************************** Check for next command *****************************************************/
    EthTrcv_Prv_CheckForNextCommand();

    pos     = EthTrcv_Prv_MiiCommunicationPos;
    cmd     = EthTrcv_Cfg_CfgData_ast[pos].cmd;

    TrcvNo =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;
    CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvNo];
    CtrlNo = EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvCtrlIdx;
    MiiIdx = EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvMiiIdx;

    switch(cmd)
    {
        case ETHTRCV_PRV_MII_COMMAND_WRITE_BUF1:
        {
#if (ETHTRCV_MII_REQUIRED == STD_ON)
            timeout = 0;
            while (E_OK != Eth_WriteMii(
                CtrlNo,
                MiiIdx,     // Index of the transceiver on the MII
                EthTrcv_Cfg_CfgData_ast[pos].adr,               // Adr
                EthTrcv_Prv_Buff1))                             // Value
            {
                if (timeout > 100)
                {
                    ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, (uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_MII_TIMEOUT_WRITE);
                    EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;   // no need to lock interrupts
                    break;
                }
                timeout++;
            };
#else
            ETHTRCV_CHECKDET_NORETURN((uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_PARAM);
#endif
        }
        break;
        case ETHTRCV_PRV_MII_COMMAND_WRITE_DIRECT:
        {
#if (ETHTRCV_MII_REQUIRED == STD_ON)
            timeout = 0;
            while (E_OK != Eth_WriteMii(
                    CtrlNo,
                    MiiIdx,     // Index of the transceiver on the MII
                    EthTrcv_Cfg_CfgData_ast[pos].adr,               // Adr
                    EthTrcv_Cfg_CfgData_ast[pos].data))             // Value
            {
                if (timeout > 100)
                {
                    ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, (uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_MII_TIMEOUT_WRITE);
                    EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;   // no need to lock interrupts
                    break;
                }
                timeout++;
            };
#else
            ETHTRCV_CHECKDET_NORETURN((uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_PARAM);
#endif
        }
        break;
        case ETHTRCV_PRV_MII_COMMAND_READ:
        {
#if (ETHTRCV_MII_REQUIRED == STD_ON)
            timeout = 0;
            while (E_OK != Eth_ReadMii( CtrlNo, MiiIdx,
                    EthTrcv_Cfg_CfgData_ast[pos].adr,       // EthTrcv_SetTransceiverMode Adr0
                    &RegVal))                                // Driver sets it to 0. Variable not used. Sync
            {                                               // never calls this function
                if (timeout > 100)
                {
                    ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, (uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_MII_TIMEOUT_READ);
                    EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;   // no need to lock interrrupts
                    break;
                }
                timeout++;
            };
#else
            ETHTRCV_CHECKDET_NORETURN((uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_PARAM);
#endif
        }
        break;
        default:    //  ETHTRCV_PRV_MII_COMMAND_END:
        {
            EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;
        }
        break;
    }
#if (ETHTRCV_MII_REQUIRED != STD_ON)
    // ETHTRCV_MII_REQUIRED == STD_OFF
    (void) CtrlNo;     //  ETHTRCV_PRV_PARAM_UNUSED
    (void) MiiIdx;     //  ETHTRCV_PRV_PARAM_UNUSED
    (void) timeout;    //  ETHTRCV_PRV_PARAM_UNUSED
#endif
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_WriteMiiIndication
* Description:    Called when information has been written via MII interface. Triggered by previous Eth_WriteMii call.
*                 Can directly be called within Eth_WriteMii.
* Arguments:    - CtrlIdx   Index of the controller within the context of the Ethernet Driver
*               - TrcvIdx   Index of the transceiver on the MII
*               - RegIdx    Index of the transceiver register on the MII
*               - RegVal    Value contained in the indexed register
* Returns:      -
* Reentrancy:   - Non Reentrant for the same CtrlIdx, reentrant for different
* Remarks:      Could call Eth_ReadMii Eth_WriteMii. If called out of Eth_WriteMii could lead to increased stack consumption
*               As all trcv (even for multi controller) are handled sequentiell, reentrancy is not requried
*               If driver is sync, all register access are handled here without leaving message
*               If driver is async, one register access is handled here and function is left. It will be called after next interrupt from driver
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_WriteMiiIndication( uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx )
{
    uint16  pos;        /* position through EthTrcv_Cfg_CfgData_ast..   */
    uint16  CfgNo;
    uint8   MiiIdx;
    uint8   TrcvNo;
    uint8   CtrlNo;
    EthTrcv_Prv_Cmd_ten  cmd;
    uint16  RegVal = 0;     // variable set to 0 in ASYNC-ReadMii and returns the value if dirver is sync
    EthTrcv_Prv_DrvMiiMode_ten   SyncLoop;
    uint16  timeout = 0;

    pos     = EthTrcv_Prv_MiiCommunicationPos;
    
    ETHTRCV_CHECKDETTRUE_RETURN_NO_VAL((EthTrcv_Prv_MiiCommunicationFlag_b == TRUE), (uint8)pos, ETHTRCV_SID_WRITEMIIINDICATION, ETHTRCV_E_INV_CONFIG_COMM_NOT_RUNNING);
    ETHTRCV_CHECKDETTRUE_RETURN_NO_VAL((pos < ETHTRCV_NUMBER_OF_CFGDATA)         , (uint8)pos, ETHTRCV_SID_WRITEMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_POS);

    TrcvNo =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;
    CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvNo];

    if ((CtrlIdx == EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvCtrlIdx)
            && (TrcvIdx == EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvMiiIdx) && (RegIdx == EthTrcv_Cfg_CfgData_ast[pos].adr))
    {
    }
    else
    {
        ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, (uint8 )pos, ETHTRCV_SID_WRITEMIIINDICATION,
                        ETHTRCV_E_INV_CONFIG_INV_PARAM);
    }


    (void)(RegIdx);     // not required if no DET
    (void)(TrcvIdx);    // not required if no DET
    (void)(CtrlIdx);    // not required if no DET
    /************************** Loop if sync-Driver  ****************************************************/
    /*                          if async Driver, loop goes through once                                 */
    do
    {
        /******************  store current read value ***************************************/
        // only required if driver is sync. Then this function loops internal and a read can occur
        if( EthTrcv_Cfg_CfgData_ast[pos].cmd == ETHTRCV_PRV_MII_COMMAND_READ)
        {
            EthTrcv_Prv_Buff0 = RegVal;
        }

        /************************** Check for next command *****************************************************/
        EthTrcv_Prv_CheckForNextCommand();

        pos    = EthTrcv_Prv_MiiCommunicationPos;
        cmd    = EthTrcv_Cfg_CfgData_ast[pos].cmd;
        TrcvNo =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;
        CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvNo];
        CtrlNo = EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvCtrlIdx;
        MiiIdx = EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvMiiIdx;

        SyncLoop = EthTrcv_Cfg_CfgData_ast[pos].SyncFlag;

        switch(cmd)
        {
            case ETHTRCV_PRV_MII_COMMAND_WRITE_BUF1:
            {
#if (ETHTRCV_MII_REQUIRED == STD_ON)
                timeout = 0;

                while (E_OK != Eth_WriteMii(
                    CtrlNo,
                    MiiIdx,     // TrcvIdx = Index of the transceiver on the MII
                    EthTrcv_Cfg_CfgData_ast[pos].adr,              // Adr
                    EthTrcv_Prv_Buff1))                            // Value
                {
                    if (timeout > 100)
                    {
                        ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, (uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_MII_TIMEOUT_WRITE);
                        EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;
                        SyncLoop = ETHTRCV_DRV_ASYNC;
                        break;
                    }
                    timeout++;
                };
#else
                ETHTRCV_CHECKDET_NORETURN((uint8)pos, ETHTRCV_SID_WRITEMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_PARAM);
#endif
            }
            break;
            case ETHTRCV_PRV_MII_COMMAND_WRITE_DIRECT:
            {
#if (ETHTRCV_MII_REQUIRED == STD_ON)
                timeout = 0;

                while (E_OK != Eth_WriteMii(
                    CtrlNo,
                    MiiIdx,     // TrcvIdxIndex of the transceiver on the MII
                    EthTrcv_Cfg_CfgData_ast[pos].adr,              // Adr
                    EthTrcv_Cfg_CfgData_ast[pos].data))         // Value
                {
                    if (timeout > 100)
                    {
                        ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, (uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_MII_TIMEOUT_WRITE);
                        EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;
                        SyncLoop = ETHTRCV_DRV_ASYNC;
                        break;
                    }
                    timeout++;
                };
#else
                ETHTRCV_CHECKDET_NORETURN((uint8)pos, ETHTRCV_SID_WRITEMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_PARAM);
#endif

            }
            break;
            case ETHTRCV_PRV_MII_COMMAND_READ:
            {
#if (ETHTRCV_MII_REQUIRED == STD_ON)
                timeout = 0;
                while (E_OK != Eth_ReadMii( CtrlNo, MiiIdx,  // MiiIdx = Index of the transceiver on the MII
                        EthTrcv_Cfg_CfgData_ast[pos].adr,    // EthTrcv_SetTransceiverMode Adr0
                        &RegVal))                         // Driver sets it to 0. Variable not used
                {
                    if (timeout > 100)
                    {
                        ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, (uint8)pos, ETHTRCV_SID_READMIIINDICATION, ETHTRCV_E_MII_TIMEOUT_READ);
                        EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;
                        SyncLoop = ETHTRCV_DRV_ASYNC;
                        break;
                    }
                    timeout++;
                };
#else
                ETHTRCV_CHECKDET_NORETURN((uint8)pos, ETHTRCV_SID_WRITEMIIINDICATION, ETHTRCV_E_INV_CONFIG_INV_PARAM);
#endif
            }
            break;
            default:    //  ETHTRCV_PRV_MII_COMMAND_END:
            {
                EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;
                SyncLoop = ETHTRCV_DRV_ASYNC;
            }
            break;
        }
    }while( SyncLoop == ETHTRCV_DRV_SYNC);
#if (ETHTRCV_MII_REQUIRED != STD_ON)
    // ETHTRCV_MII_REQUIRED == STD_OFF
    (void) CtrlNo;     //  ETHTRCV_PRV_PARAM_UNUSED
    (void) MiiIdx;     //  ETHTRCV_PRV_PARAM_UNUSED
    (void) timeout;    //  ETHTRCV_PRV_PARAM_UNUSED
#endif
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_CheckForNextCommand
* Description:    Check for next command in EthTrcv_Cfg_CfgData_ast. It calls internal functions and loops until next MII command required
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_CheckForNextCommand(void)
{
    EthTrcv_Prv_MiiCommunicationPos++;  // Set index to next line in EthTrcv_Cfg_CfgData_ast
    while((EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].fct != NULL_PTR) ||                        // Check if internal function should be called before next MiiCommand
          (EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].cmd == ETHTRCV_PRV_MII_COMMAND_IGNORE)) // always skip line if dummy line with NULL_PTR and COMMAND_IGNORE
    {
        if(EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].fct != NULL_PTR)
        {
            EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].fct();
        }
        // Check if next command should be executed imediatelly
        if((EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].cmd != ETHTRCV_PRV_MII_COMMAND_IGNORE) )
        {
            break;  // if not, execute this command
        }
        EthTrcv_Prv_MiiCommunicationPos++; // execute next line in EthTrcv_Cfg_CfgData_ast
    }
    return ;
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_CheckForNextInit
* Description:    Called if trcv is initialized. Checks, if another trcv should be initialized
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_CheckForNextInit(void)
{
    uint8     TrcvNo;
    uint16    CfgIdx;
    uint16    pos = EthTrcv_Prv_MiiCommunicationPos;

    // Get current TrcvIdx
    TrcvNo =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;
    CfgIdx =  EthTrcv_InitCfgNo_au16[TrcvNo];

	if(EthTrcv_Prv_InitState_e[TrcvNo] != ETHTRCV_INITSTATE_INITRUN)
	{
	    // Set Current Trcv to state init
	    ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B,
            (uint8)EthTrcv_Prv_MiiCommunicationPos, ETHTRCV_SID_PRV_CHECKFORNEXTINIT, ETHTRCV_E_MII_COMMUNICATION);

	}

    EthTrcv_Prv_InitState_e[TrcvNo] = ETHTRCV_INITSTATE_INITFINISH;

    // Check, if another Trcv should be init
    for( TrcvNo = 0; TrcvNo < ETHTRCV_NUMBER_OF_ETHTRCV; TrcvNo++)
    {
        if ( EthTrcv_Prv_InitState_e[TrcvNo] == ETHTRCV_INITSTATE_INITREQ )
        {
            // move CommunicationPos to next init-start
            CfgIdx = EthTrcv_InitCfgNo_au16[TrcvNo];
            EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgIdx].AdrNoInit;
            EthTrcv_Prv_InitState_e[TrcvNo] = ETHTRCV_INITSTATE_INITRUN;
            break;  // found next Trcv to be initialised
        }
    }
    // if no other Trcv is found, Command ETHTRCV_PRV_MII_COMMAND_END is executed or
    //   cyclic communication is started
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_CheckExec
* Description:    Called if trcv is initialized. Checks, if another trcv should be initialized
*                   it is called in main function before cycl commands are executed
*                   Checks, if current Trcv is active and commands should be executed.
*                   otherwise next command for next trcv is searched
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_CheckExec(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint16 CfgNo;
    uint8  TrcvIdx;

    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;    // Get current TrcvIdx out of EthTrcv_Cfg_CfgData_ast

    if(EthTrcv_Prv_InitState_e[TrcvIdx] != ETHTRCV_INITSTATE_INITFINISH)
    {
        TrcvIdx ++;
        if(TrcvIdx < ETHTRCV_NUMBER_OF_ETHTRCV)
        {
            CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvIdx];
            // change pointer to next trcv (new check is done there)
            EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].AdrNoMain;
        }
    }
    else
    {
        EthTrcv_Prv_MiiCommunicationPos++;  // Execute current trcv (step over this line with ETHTRCV_PRV_MII_COMMAND_END)
    }
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_ModeDown
* Description:    Check if trcv should be switched off. If yes, execute next lines, otherwise jump over next lines
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_ModeDown(void)
{
    /* Check if Mode should be changed, otherwise jump over conf data */
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint8  TrcvIdx;
    // Get current TrcvIdx
    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;

    // If no Req == down or mode already down: Jump over command
    if(( EthTrcv_Prv_RequestedMode[TrcvIdx] != ETHTRCV_MODE_DOWN ) ||
       ( EthTrcv_Prv_CurrentMode[TrcvIdx]   == ETHTRCV_MODE_DOWN))
    {
            EthTrcv_Prv_MiiCommunicationPos += EthTrcv_Cfg_CfgData_ast[pos].adr;
    }
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_ModeActive
* Description:    Check if trcv should be switched on. If yes, execute next lines, otherwise jump over next lines
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_ModeActive(void)
{
    /* Check if Mode should be changed, otherwise jump over conf data */
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint8  TrcvIdx;
    // Get current TrcvIdx
    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;

    if((EthTrcv_Prv_RequestedMode[TrcvIdx] != ETHTRCV_MODE_ACTIVE ) ||
       (EthTrcv_Prv_CurrentMode[TrcvIdx]   == ETHTRCV_MODE_ACTIVE))
    {
            EthTrcv_Prv_MiiCommunicationPos += EthTrcv_Cfg_CfgData_ast[pos].adr;
    }
}

#if ( ETHTRCV_CFG_START_AUTONEGOTIATION_API == STD_ON)
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_StartAutoNeg
* Description:    Check if autoneg should be startet. If yes, execute next lines, otherwise jump over next lines
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_StartAutoNeg(void)
{
    /* Check if Autonegotiation should be started, otherwise jump over conf data */
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint8  TrcvIdx;
    // Get current TrcvIdx
    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;

    if(EthTrcv_Prv_AutoNegotiationReq[TrcvIdx] != TRUE )
    {
        // if there is no request, skip next commands
        EthTrcv_Prv_MiiCommunicationPos += EthTrcv_Cfg_CfgData_ast[pos].adr;
    }
    else
    {
        // Execute next commands and clear request
        EthTrcv_Prv_AutoNegotiationReq[TrcvIdx] = FALSE;
    }
}
#endif
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_Or
* Description:    internal function to logical OR EthTrcv_Prv_Buff0 with EthTrcv_Prv_Buff1 and store in EthTrcv_Prv_Buff1
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_Or(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    EthTrcv_Prv_Buff1  |=   EthTrcv_Prv_Buff0 | EthTrcv_Cfg_CfgData_ast[pos].data;
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_And
* Description:    internal function to logical AND EthTrcv_Prv_Buff0 with Configured data and store in EthTrcv_Prv_Buff1
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_And(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    EthTrcv_Prv_Buff1  |=   EthTrcv_Prv_Buff0 & EthTrcv_Cfg_CfgData_ast[pos].data;
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_Clr0
* Description:    internal function to clear EthTrcv_Prv_Buff0
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_Clr0(void)
{
    EthTrcv_Prv_Buff0 = 0;
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_Clr1
* Description:    internal function to clear EthTrcv_Prv_Buff1
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_Clr1(void)
{
    EthTrcv_Prv_Buff1 = 0;
}
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_GetMode
* Description:    Check previously read registervalues compare wiht configured data. As result set the Mode of trcv in internal variable
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetMode(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint8  TrcvIdx;
    // Get current TrcvIdx
    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;

    if( (EthTrcv_Prv_Buff0 & EthTrcv_Cfg_CfgData_ast[pos].data) == 0)    // Detect HW as active
    {
        if(EthTrcv_Prv_CurrentMode[TrcvIdx] == ETHTRCV_MODE_DOWN)       // Check if indication should be sent
        {
            EthTrcv_Prv_ModeIndicationFlag[TrcvIdx] = TRUE;
        }
        EthTrcv_Prv_CurrentMode[TrcvIdx] = ETHTRCV_MODE_ACTIVE;
    }
    else
    {
        if(EthTrcv_Prv_CurrentMode[TrcvIdx] == ETHTRCV_MODE_ACTIVE)    // Detect HW as down
        {
            EthTrcv_Prv_ModeIndicationFlag[TrcvIdx] = TRUE;         // Check if indication should be sent
        }
        EthTrcv_Prv_CurrentMode[TrcvIdx] = ETHTRCV_MODE_DOWN;
    }
}

# if (ETHTRCV_NO_PHY_USED == STD_ON)
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_GetModeNoPhy
* Description:    Set the mode according requested mode.
*                 Set Link-state according requested mode
*
* Arguments:    -
* Returns:      -
* Remarks:      This function is called cyclicly out of main function so link-state is also set cyclicly
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetModeNoPhy(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint8  TrcvIdx;

    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;    // Get current TrcvIdx

    if (EthTrcv_Prv_RequestedMode[TrcvIdx] != EthTrcv_Prv_CurrentMode[TrcvIdx])
    {
        EthTrcv_Prv_ModeIndicationFlag[TrcvIdx] = TRUE;
        EthTrcv_Prv_CurrentMode[TrcvIdx] = EthTrcv_Prv_RequestedMode[TrcvIdx];
    }

    // Set Link-State according Mode (No extra function required)
    if( EthTrcv_Prv_CurrentMode[TrcvIdx] == ETHTRCV_MODE_ACTIVE)
    {
        EthTrcv_Prv_LinkState[TrcvIdx] = ETHTRCV_LINK_STATE_ACTIVE;
    }
    else
    {
        EthTrcv_Prv_LinkState[TrcvIdx] = ETHTRCV_LINK_STATE_DOWN;
    }
}
#endif
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_GetLink
* Description:    Evaluates out out previous read registervalues the link-state
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetLink(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint8  TrcvIdx;

    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;    // Get current TrcvIdx

    if( (EthTrcv_Prv_Buff0 & EthTrcv_Cfg_CfgData_ast[pos].data) == 0) // usually Bit2
    {
        EthTrcv_Prv_LinkState[TrcvIdx] = ETHTRCV_LINK_STATE_DOWN;
    }
    else
    {
        EthTrcv_Prv_LinkState[TrcvIdx] = ETHTRCV_LINK_STATE_ACTIVE;
    }
}

# if (ETHTRCV_DP83822_USED == STD_ON)
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_GetBaud2
* Description:    Evaluates out out previous read registervalues the baud rate
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetBaud2(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint8  TrcvIdx;

    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;    // Get current TrcvIdx

    if( (EthTrcv_Prv_Buff0 & EthTrcv_Cfg_CfgData_ast[pos].data) == 0) // usually Bit2
    {
        EthTrcv_Prv_BaudRate[TrcvIdx] = ETHTRCV_BAUD_RATE_100MBIT;
    }
    else
    {
        EthTrcv_Prv_BaudRate[TrcvIdx] = ETHTRCV_BAUD_RATE_10MBIT;
    }
}
#endif

# if (ETHTRCV_DP83822_USED == STD_ON)
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_GetDuplexMode2
* Description:    Evaluates out of previous read register values the duplex mode
*
* Arguments:    -
* Returns:      -
* Remarks:
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetDuplexMode2(void)
{
    uint16 pos = EthTrcv_Prv_MiiCommunicationPos;
    uint16 RegVal;
    uint8  TrcvIdx;

    // Get current TrcvIdx
    TrcvIdx =  EthTrcv_Cfg_CfgData_ast[pos].TrcvIdx;

    RegVal = EthTrcv_Prv_Buff0;
    if((RegVal & EthTrcv_Cfg_CfgData_ast[pos].data) == 0)
    {
        EthTrcv_Prv_DuplexMode[TrcvIdx] = ETHTRCV_DUPLEX_MODE_HALF;
    }
    else
    {
        EthTrcv_Prv_DuplexMode[TrcvIdx] = ETHTRCV_DUPLEX_MODE_FULL;
    }
}
#endif

#if defined(ETHTRCV_TJA1100_USED)
 #if (ETHTRCV_TJA1100_USED == STD_ON)
/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_UpdatePhyOperationType
* Description:    This internal api configures the Phy to managed operation only if test mode is requested and phy is
*                 in autonomous operation and disables the managed operation only if it was enabled in the previuos call
*                 and if normal mode is requested.
*                 If phy is configured for managed operation during initialization, then api will skip the next command.
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_UpdatePhyOperationType(void)
{
    uint8                               TrcvIdx; /* Index of the trasnceiver within the context of the Ethernet Trcv */
    static boolean EnManagedOperation_b = FALSE; /* local var to store information about the phy operation type*/

    TrcvIdx = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    /* For running test mode or cable test, managed operation is required */
    if((EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx] != ETHTRCV_PHYTESTMODE_NONE) ||
       (EthTrcv_Prv_CableDiagRequested[TrcvIdx] != FALSE) ||
       (EthTrcv_Prv_RequestedPhyLoopbackMode[TrcvIdx] != ETHTRCV_PHYLOOPBACK_NONE))
    {
        /* Check if Phy is in autonomous operation */
        if(0U != (EthTrcv_Prv_Buff0 & ETHTRCV_PRV_REG18_AUTO_OP_AUTONOMOUS))
        {
            /* Phy is Autonomous operation; Enable managed operation */
            EthTrcv_Prv_Buff1 = (EthTrcv_Prv_Buff0 & ETHTRCV_PRV_REG18_EN_AUTO_OP_MANAGED);
            EnManagedOperation_b = TRUE;
        }
        else
        {
            /* Already in managed operation; Hence skipping the command for configuring managed operation */
            EthTrcv_Prv_MiiCommunicationPos++;
        }
    }
    else
    {
        if(EnManagedOperation_b == TRUE)
        {
            /* For running test mode or cable test, managed operation was enabled. Disable Managed operation for normal operation */
            EthTrcv_Prv_Buff1 = (EthTrcv_Prv_Buff0 | ETHTRCV_PRV_REG18_AUTO_OP_AUTONOMOUS);
            EnManagedOperation_b = FALSE;
        }
        else
        {
            /* No configuration was done for test mode or cable test. Hence no configuration needs to be made for normal operation*/
            EthTrcv_Prv_MiiCommunicationPos++;
        }
    }
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_UpdateBuff1WithReqMode
* Description:    The internal api does the below functionalities
*                 - It updates the EthTrcv_Prv_Buff1 with the requested test mode.
*                 - Disbles the Link control and conf reg access control when requested mode is test mode
*                 - Enables the Link control and conf reg access control when requested mode is normal mode
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_UpdateBuff1WithReqMode(void)
{
    uint8   TrcvIdx; /* Index of the trasnceiver within the context of the Ethernet Trcv */

    TrcvIdx = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    if(EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx] != ETHTRCV_PHYTESTMODE_NONE)
    {
        /* Test mode activation is requested */
        /* Get the requested mode */
        EthTrcv_Prv_Buff1 = (((uint16)EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx]) << ETHTRCV_PRV_REG17_TESTMODE_POS);

        /* Disable the configuration register access */
        EthTrcv_Prv_Buff0 &= ETHTRCV_PRV_REG17_DIS_CONF_REG_ACCESS;

        /* Disable Link Control to run a test mode */
        EthTrcv_Prv_Buff0 &= ETHTRCV_PRV_REG17_DIS_LINK_CONTROL;

        /* Reset the Test Mode field */
        EthTrcv_Prv_Buff0 &= ETHTRCV_PRV_REG17_RESET_TESTMODE_FIELD;

        /* Update the Test mode */
        EthTrcv_Prv_Buff1 |= EthTrcv_Prv_Buff0;
    }
    else
    {
        /* Normal mode activation is requested */
        /* Enable the configuration register access */
        EthTrcv_Prv_Buff0 |= ETHTRCV_PRV_REG17_EN_CONF_REG_ACCESS;

        /* Disabling the test mode */
        EthTrcv_Prv_Buff0 &= ETHTRCV_PRV_REG17_RESET_TESTMODE_FIELD;

        /* Update it into Extended control register */
        EthTrcv_Prv_Buff1 |= EthTrcv_Prv_Buff0;
    }
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_TestModeCheck
* Description:    the api is internally used to check the result of the phy test mode
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_PhyTestModeCheck(void)
{
    uint8  TrcvIdx_u8;          /* Index of the trasnceiver within the context of the Ethernet Trcv */
    uint16 PhyState_ChkVal_u16; /* local variable to store the checkvalue depending on the requested mode */

    TrcvIdx_u8 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    if(EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx_u8] != ETHTRCV_PHYTESTMODE_NONE)
    {
        /* Check value when the requested test mode is other than Normal mode */
        PhyState_ChkVal_u16 = ETHTRCV_PRV_REG23_PHYSTATE_TESTMODE;
    }
    else
    {
        /* Check value when the requested test mode is Normal mode */
        PhyState_ChkVal_u16 = ETHTRCV_PRV_REG23_PHYSTATE_ACTIVE;
    }

    if(PhyState_ChkVal_u16 == (EthTrcv_Prv_Buff0 &  PhyState_ChkVal_u16))
    {
        /* Requested Phy test mode is enabled */
        EthTrcv_Prv_CurrentPhyTestMode[TrcvIdx_u8] = EthTrcv_Prv_RequestedPhyTestMode[TrcvIdx_u8];
    }
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_CableDiagnosticCheck
* Description:    the api is internally used to check the result of the cable diagnostic
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_CableDiagnosticCheck(void)
{
    uint8 TrcvIdx_u8;
    uint16 CheckValue_u16;

    TrcvIdx_u8 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    /* Get the check value for cable diagnostic result */
    CheckValue_u16 = EthTrcv_Prv_Buff0 & ETHTRCV_PRV_REG25_OPEN_SHORT_CIRCUIT;

   if(ETHTRCV_PRV_REG25_SHORT_CIRCUIT == CheckValue_u16)
   {
       /* Short circuit is detected */
       EthTrcv_Prv_CableDiagResult[TrcvIdx_u8] = ETHTRCV_CABLEDIAG_SHORT;
   }
   else if(ETHTRCV_PRV_REG25_OPEN_CIRCUIT == CheckValue_u16 )
   {
       /* Open circuit is detected */
       EthTrcv_Prv_CableDiagResult[TrcvIdx_u8] = ETHTRCV_CABLEDIAG_OPEN;
   }
   else
   {
       /* In all other cases the cable is fine. Both open and short circuit bits become HIGH when the cable is
        * terminated properly.
        * Note for TJA1100 : When cable test is started by a device that is configured as Master and the link partner
        * is also configured as Master there can be an ambiguity in the cable tests results. If the line is properly
        * terminated, then for this particular case both Open and Short flags will be indicated.
        * But, in all theses cases, the cable test result is given as CABLEDIAG_OK
        */
       EthTrcv_Prv_CableDiagResult[TrcvIdx_u8] = ETHTRCV_CABLEDIAG_OK;
   }

    /* Cable diagnostic is finished */
    EthTrcv_Prv_CableDiagRequested[TrcvIdx_u8] = FALSE;
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_GetCableSignalQuality
* Description:    the api is internally used to determine the cabel signal quality. This api is valid only
*                 TJA1100 ethernet transceiver
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_GetCableSignalQuality(void)
{
    uint8 lLinkQua_u8;              /* local variable for SQI value */
    uint8 lTrcvIdx_u8;              /* local variable for index of Trcv */
    uint8 lSignalQuality_u8 = 0;    /* local variable to hold the signal quality in percent */

    lTrcvIdx_u8 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    /* Before calling this api, the status register 23 of TJA1100 shall be read.
     * The Read Value is present in EthTrcv_Prv_Buff0 */
    lLinkQua_u8 = (uint8) ((EthTrcv_Prv_Buff0 & ETHTRCV_PRV_LINKQUALITY_FIELD) >> 5)/*0x00E0*/;

    switch (lLinkQua_u8)
    {
        case ETHTRCV_PRV_LINKQUALITY_SQI_7:
        {
            /* When the SQI value is 7  : class G SQI (very good link)*/
            lSignalQuality_u8 = ETHTRCV_PRV_LINKQUALITY_PERCENT_100;
        }
        break;

        case ETHTRCV_PRV_LINKQUALITY_SQI_6:
        {
            /* When the SQI value is 6  : class F SQI (very good link)*/
            lSignalQuality_u8 = ETHTRCV_PRV_LINKQUALITY_PERCENT_80;
        }
        break;

        case ETHTRCV_PRV_LINKQUALITY_SQI_5:
        {
            /* When the SQI value is 5  : class E SQI (good link)*/
            lSignalQuality_u8 = ETHTRCV_PRV_LINKQUALITY_PERCENT_60;
        }
        break;

        case ETHTRCV_PRV_LINKQUALITY_SQI_4:
        case ETHTRCV_PRV_LINKQUALITY_SQI_3:
        {
            /* When the SQI value is 4  : class D SQI (good link)*/
            /* When the SQI value is 3  : class C SQI (good link)*/
            lSignalQuality_u8 = ETHTRCV_PRV_LINKQUALITY_PERCENT_40;
        }
        break;

        case ETHTRCV_PRV_LINKQUALITY_SQI_2:
        case ETHTRCV_PRV_LINKQUALITY_SQI_1:
        {
            /* When the SQI value is 2  : class B SQI (unstable link)*/
            /* When the SQI value is 1  : class A SQI (unstable link)*/
            lSignalQuality_u8 = ETHTRCV_PRV_LINKQUALITY_PERCENT_20;
        }
        break;

        default:
        {
            /* When the SQI value is 0 : worse than class A SQI (unstable link)*/
            lSignalQuality_u8 = ETHTRCV_PRV_LINKQUALITY_PERCENT_0;
        }
        break;
    }

    /* Updating the global signal quality variable */
    EthTrcv_Prv_CableSignalQuality_u8[lTrcvIdx_u8] = lSignalQuality_u8;

}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_UpdateBuff1WithReqLoopBackMode
* Description:    The internal api does the below functionalities
*                 - It updates the EthTrcv_Prv_Buff1 with the requested loopback mode when the requested
*                 loopback mode is other than ETHTRCV_PHYLOOPBACK_INTERNAL
*                 This api will not be called when the requested loopback mode is None
*
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_UpdateBuff1WithReqLoopBackMode(void)
{
    uint8  TrcvIdx_u8;          /* Index of the trasnceiver within the context of the Ethernet Trcv */

    TrcvIdx_u8 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    if(EthTrcv_Prv_RequestedPhyLoopbackMode[TrcvIdx_u8] != ETHTRCV_PHYLOOPBACK_INTERNAL)
    {
        EthTrcv_Prv_Buff1 |= ((uint16)EthTrcv_Prv_RequestedPhyLoopbackMode[TrcvIdx_u8]) << 3;
    }
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_PhyLoopBackModeCheck
* Description:    the api is internally used to check the result of the phy loopback mode
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_PhyLoopBackModeCheck(void)
{
    uint8  lTrcvIdx_u8;
    uint16 lPhyLoopbackMode_ChkVal_u16 = 0; /* local variable to store the checkvalue depending on the requested mode */

    lTrcvIdx_u8 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    switch (EthTrcv_Prv_RequestedPhyLoopbackMode[lTrcvIdx_u8])
    {
        case ETHTRCV_PHYLOOPBACK_NONE:
        {
            /* Check value when the requested loopback mode is none */
            lPhyLoopbackMode_ChkVal_u16 = ETHTRCV_PRV_CHKVALUE_LOOPBACK_NONE;
        }
        break;
        case ETHTRCV_PHYLOOPBACK_INTERNAL:
        {
            /* Check value when the requested loopback mode is internal */
            lPhyLoopbackMode_ChkVal_u16 = ETHTRCV_PRV_CHKVALUE_LOOPBACK_INTERNAL;
        }
        break;
        case ETHTRCV_PHYLOOPBACK_EXTERNAL:
        {
            /* Check value when the requested loopback mode is external */
            lPhyLoopbackMode_ChkVal_u16 = ETHTRCV_PRV_CHKVALUE_LOOPBACK_EXTERNAL;
        }
        break;
        case ETHTRCV_PHYLOOPBACK_REMOTE:
        {
            /* Check value when the requested loopback mode is remote */
            lPhyLoopbackMode_ChkVal_u16 = ETHTRCV_PRV_CHKVALUE_LOOPBACK_REMOTE;
        }
        break;
        default:
        {
            /* Required as per the coding guidelines */
        }
        break;
    }

    if(lPhyLoopbackMode_ChkVal_u16 == (EthTrcv_Prv_Buff0 &  lPhyLoopbackMode_ChkVal_u16))
    {
        /* Requested Phy loopback mode is enabled */
        EthTrcv_Prv_CurrentPhyLoopbackMode[lTrcvIdx_u8] = EthTrcv_Prv_RequestedPhyLoopbackMode[lTrcvIdx_u8];
    }

}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_ExtractPhyIdentifier
* Description:    the api is internally used to obtain the OrgUniqueId, ModelId and RevisionId of the indexed Phy
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_ExtractPhyIdentifier(void)
{
    static uint8 lIdentifierIndex_u8 = 0U;
    uint8        lTrcvIdx_u8;

    lTrcvIdx_u8 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    if(0U == lIdentifierIndex_u8)
    {
        /* Extracting Bits 3 to 18 of the Organizationally Unique IDentifier. Bits 1 and 2 are always 0 */
        EthTrcv_Prv_PhyIdentifier_au32[lTrcvIdx_u8].Phy_OrgUniqueId_u32 = ((uint32)EthTrcv_Prv_Buff0) << ETHTRVC_PRV_REG2_OUI_POS;
        /* Setting the local static variable to 1 so that in the next call the else part is executed */
        lIdentifierIndex_u8 = 1U;
    }
    else
    {
        /* Extracting Bits 19 to 24 of the Organizationally Unique IDentifier */
        EthTrcv_Prv_PhyIdentifier_au32[lTrcvIdx_u8].Phy_OrgUniqueId_u32   |= (uint32)((EthTrcv_Prv_Buff0 & ETHTRCV_PRV_REG3_OUI_MASK) >> ETHTRVC_PRV_REG3_OUI_POS);
        /* Extracting Bits 19 to 24 of the Manufacturer's model or type number */
        EthTrcv_Prv_PhyIdentifier_au32[lTrcvIdx_u8].Phy_ModelNumber_u8    =  (uint8) ((EthTrcv_Prv_Buff0 & ETHTRCV_PRV_REG3_MODEL_NUMBER_MASK) >> ETHTRCV_PRV_REG3_MODEL_NUMBER_POS);
        /* Extracting Bits 19 to 24 of the Manufacturer's revision number */
        EthTrcv_Prv_PhyIdentifier_au32[lTrcvIdx_u8].Phy_RevisionNumber_u8 =  (uint8) (EthTrcv_Prv_Buff0 & ETHTRCV_PRV_REG3_REVISION_NUMBER_MASK);
        /* Setting the local variable to its initail value*/
        lIdentifierIndex_u8 = 0U;
    }
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_CheckForPhyAccess
* Description:    the api is internally used to check whether access Phy is available or not
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_CheckForPhyAccess(void)
{
    uint8                   lTrcvIdx_u8;   /* local variable to hold the current transceiver index*/
#if defined(ETHTRCV_CFG_DEM_ENABLE)
 #if (ETHTRCV_CFG_DEM_ENABLE == STD_ON)
    uint16                  lCfgIdx_u16;   /* local variable to hold the current config index */
    Dem_EventStatusType     lDemStatus_b = DEM_EVENT_STATUS_FAILED;
 #endif
#endif

    /* Get the transceiver index for the current MII command */
    lTrcvIdx_u8 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;
#if defined(ETHTRCV_CFG_DEM_ENABLE)
 #if (ETHTRCV_CFG_DEM_ENABLE == STD_ON)
    lCfgIdx_u16                      =  EthTrcv_InitCfgNo_au16[lTrcvIdx_u8];
 #endif
#endif


    /* check for trcv access by reading the identification registers */
    /* if no phy access, raise DET or DEM and then skip the init commands*/
    if((EthTrcv_Prv_PhyIdentifier_au32[lTrcvIdx_u8].Phy_OrgUniqueId_u32 == EthTrcv_CurrentCfg_PhyIdentification_pco[lTrcvIdx_u8].Phy_OrgUniqueId_u32) &&
           (EthTrcv_Prv_PhyIdentifier_au32[lTrcvIdx_u8].Phy_ModelNumber_u8 == EthTrcv_CurrentCfg_PhyIdentification_pco[lTrcvIdx_u8].Phy_ModelNumber_u8))
    {
/* Access to Ethernet Phy is available */
#if defined(ETHTRCV_CFG_DEM_ENABLE)
 #if (ETHTRCV_CFG_DEM_ENABLE == STD_ON)
        lDemStatus_b = DEM_EVENT_STATUS_PASSED;
 #endif
#endif
        EthTrcv_Prv_PhyAccessStatus_e[lTrcvIdx_u8] = ETHTRCV_PHYACCESS_AVAILABLE;
    }
    else
    {
        /* No access to Ethernet Phy. Report error and stop the initialization */
#if defined(ETHTRCV_CFG_DEM_ENABLE)
 #if (ETHTRCV_CFG_DEM_ENABLE == STD_OFF)
        ETHTRCV_CHECKDETTRUE_NORETURN(ETHTRCV_FALSE_B, (uint8)EthTrcv_Prv_MiiCommunicationPos, ETHTRCV_SID_TRANSCEIVERINIT, ETHTRCV_E_MII_TIMEOUT_READ);
 #endif
#endif
        /* Access to Ethernet Phy is NOT available */
        EthTrcv_Prv_PhyAccessStatus_e[lTrcvIdx_u8] = ETHTRCV_PHYACCESS_NOT_AVAILABLE;
        /* Skip the Init commands since no access Eth Phy */
        EthTrcv_Prv_MiiCommunicationPos  = EthTrcv_CurrentConfig_pco->NumberOfCfgData_u16;
    }
#if defined(ETHTRCV_CFG_DEM_ENABLE)
 #if (ETHTRCV_CFG_DEM_ENABLE == STD_ON)
        EthTrcv_DemReportErrorStatus(EthTrcv_Cfg_CfgInit_po[lCfgIdx_u16].EventId, lDemStatus_b );
 #endif
#endif
}


/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_ExtractLinkStatistics
* Description:    the api is internally used to obtain the link statistics information
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_ExtractLinkStatistics(void)
{
    static uint8 lLinkStatsIndex_u8 = 0U;
    uint8        lTrcvIdx_u8;

    lTrcvIdx_u8 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].TrcvIdx;

    switch(lLinkStatsIndex_u8)
    {
        case 0U:
        {
            SchM_Enter_EthTrcv_MiiCommunication();
            /* Extracting Link Fail Count i.e,. Bits 3 to 7 of General status register which is Register 24 */
            EthTrcv_Prv_LinkStatistics_ast[lTrcvIdx_u8].etherStatslinklosses_u8 = (uint8) ((EthTrcv_Prv_Buff0
                    & ETHTRCV_TJA1100_REG24_LINKFAIL_CNT_MASKVALUE) >> ETHTRCV_TJA1100_REG24_LINKFAIL_CNT_POS);
            SchM_Exit_EthTrcv_MiiCommunication();

            /* Setting the local static variable to 1 so that in the next call the else part is executed */
            lLinkStatsIndex_u8 = 1U;

        }
        break;
        case 1U:
        {
            SchM_Enter_EthTrcv_MiiCommunication();
            /* Extracting Symbol error counter register i.e,. Register 20*/
            EthTrcv_Prv_LinkStatistics_ast[lTrcvIdx_u8].etherStatsSymbolFailure_u16 = EthTrcv_Prv_Buff0;
            SchM_Exit_EthTrcv_MiiCommunication();

            /* Re-Setting the local static variable to initial value */
            lLinkStatsIndex_u8 = 0U;

        }
        break;
        default:
        {
            lLinkStatsIndex_u8 = 0U;
        }
        break;
    }
}
 #endif
#endif /* End for ETHTRCV_TJA1100_USED*/

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_Fct_Wait_uS
* Description:    the api is internally used to provide a wait time in micro second. It uses an api provided by the OS.
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_Fct_Wait_uS(void)
{
    uint16 lTimeoutCnt_u16;

    /* Get the wait time in micro second */
    lTimeoutCnt_u16 = EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].data;

    /* wait for the timeout period in micro second*/
    EthTrcv_Cfg_TimerElapsed(lTimeoutCnt_u16);
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_CheckForResetToFinish
* Description:    the api is internally used to check if Reset of RTL9000AA is finished
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
# if (ETHTRCV_RTL9000AA_USED == STD_ON)
void EthTrcv_Prv_CheckForResetToFinish(void)
{
   if(ETHTRCV_PRV_RESET_CHECKVALUE == (EthTrcv_Prv_Buff0 & ETHTRCV_PRV_RESET_MASKVALUE))
   {
       /*Reset is successfull*/
   }
   else
   {
       /* Reset is not successful. Read register value again
        change EthTrcv_Prv_MiiCommunicationPos to back */
       EthTrcv_Prv_MiiCommunicationPos--;
   }
}

/**
*******************************************************************************************************
* Function name:  EthTrcv_Prv_CheckForPhyReady
* Description:    the api is internally used to check if RTL9000AA phy is ready
*
*
*
* \arg        none
* \arg        none
* \return
*
*
* \note
*******************************************************************************************************
*/
void EthTrcv_Prv_CheckForPhyReady(void)
{
    if(ETHTRCV_PRV_PHYREADYSTATE_CHECKVALUE == (EthTrcv_Prv_Buff0 & ETHTRCV_PRV_PHYREADYSTATE_MASKVALUE))
    {
        /*Phy is in Ready State */
    }
    else
    {
        /* Phy is not ready. Read register value again
         change EthTrcv_Prv_MiiCommunicationPos to back */
        EthTrcv_Prv_MiiCommunicationPos--;
    }
}
#endif

/**
*******************************************************************************************************
* Function name:  EthTrcv_MainFunction
* Description:    Is called cyclicly. Checks for init, starts trcv communication and calles indication functions,
*
* Arguments:    -
* Returns:      -
* Remarks:      - The schedule depends on time to get link-state and execution time to set a mode.
*                 All read states are delayed for main-function-cycle time
*******************************************************************************************************
*/
FUNC (void, ETHTRCV_CODE) EthTrcv_MainFunction( void )
{
    uint8  TrcvNo;
    uint16 CfgNo;
    boolean access = FALSE;

    // Check, if communication is still running
    SchM_Enter_EthTrcv_MiiCommunication();    // Access to EthTrcv_Prv_MiiCommunicationFlag_b under Interruptproctection
    if(EthTrcv_Prv_MiiCommunicationFlag_b == FALSE)
    {
        EthTrcv_Prv_MiiCommunicationFlag_b = TRUE;
        EthTrcv_Prv_TimeoutCount = 0u;
    }
    else
    {
        // Communication is already running. To check not ending communication (something is wrong) timeoutcounter is increased
        EthTrcv_Prv_TimeoutCount ++;    // Check for overflow of counter outside loop (interrupt-lock)
        access = TRUE;
    }
    SchM_Exit_EthTrcv_MiiCommunication();

    // Check if for long time communication is not finished.
    // This loop is outside of upper else condition because of short Interrupt-lock (DET-Function call not inside interrupt-lock)
    if( EthTrcv_Prv_TimeoutCount > ETHTRCV_CFG_TIMEOUT_COUNTER_MAX)
    {
        ETHTRCV_CHECKDETTRUE_NORETURN((ETHTRCV_FALSE_B), 1, ETHTRCV_SID_MAINFUNCTION, ETHTRCV_E_MII_COMMUNICATION);
        // Restart Communication because of some errors to allow communication again. This should never happen.
        EthTrcv_Prv_TimeoutCount = 0;
        EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;
    }

    // If no Mii-Communication is running, a new init or the normal operation can be started
    if(access == FALSE)
    {
        // Check for need to send initdata
        for(TrcvNo = 0u; TrcvNo < ETHTRCV_NUMBER_OF_ETHTRCV; TrcvNo++)
        {
            if(EthTrcv_Prv_InitState_e[TrcvNo] == ETHTRCV_INITSTATE_INITREQ)
            {
                // If a Trcv is newly init, one main-cycle is postponed and init is executed
                CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvNo];
                EthTrcv_Prv_InitState_e[TrcvNo] = ETHTRCV_INITSTATE_INITRUN;
                EthTrcv_Prv_MiiCommunicationPos  = EthTrcv_Cfg_CfgInit_po[CfgNo].AdrNoInit;

                EthTrcv_WriteMiiIndication(EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvCtrlIdx,   // CtrlIdx
                        EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvMiiIdx,                       // MiiIdx
                        EthTrcv_Cfg_CfgData_ast[EthTrcv_Prv_MiiCommunicationPos].adr);      // RegIdx
                access = TRUE;
            }
        }
        // If communication was not running and nothing has to be newly initialized then
        // Find out first initiated trcv and start main-Mii-chain with it
        if(access == FALSE)
        {
            for(TrcvNo = 0; TrcvNo < ETHTRCV_NUMBER_OF_ETHTRCV; TrcvNo++)
            {
#if defined(ETHTRCV_TJA1100_USED)
 #if (ETHTRCV_TJA1100_USED == STD_ON)
                /* If Phy Test modes are enabled then normal communication is stopped */
                if((EthTrcv_Prv_CurrentPhyTestMode[TrcvNo] == ETHTRCV_PHYTESTMODE_NONE) &&
                        (EthTrcv_Prv_CurrentPhyLoopbackMode[TrcvNo] == ETHTRCV_PHYLOOPBACK_NONE))
                {
 #endif
#endif
                    if(EthTrcv_Prv_State_e[TrcvNo] == ETHTRCV_STATE_ACTIVE)
                    {
                        access = TRUE;
                        CfgNo  =  EthTrcv_InitCfgNo_au16[TrcvNo];
                        EthTrcv_Prv_MiiCommunicationPos = EthTrcv_Cfg_CfgInit_po[CfgNo].AdrNoMain;
                        EthTrcv_WriteMiiIndication(EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvCtrlIdx,
                                                   EthTrcv_Cfg_CfgInit_po[CfgNo].EthTrcvMiiIdx, 0);
                        break;
                    }
#if defined(ETHTRCV_TJA1100_USED)
  #if (ETHTRCV_TJA1100_USED == STD_ON)
                }
 #endif
#endif
            }
        }
        // Check, if communication is required, otherwise release flag
        if((EthTrcv_Prv_MiiCommunicationFlag_b == TRUE) && (access == FALSE))
        {
            EthTrcv_Prv_MiiCommunicationFlag_b = FALSE;
        }
    }

    // Check for need to call mode indication functions
    for(TrcvNo = 0; TrcvNo < ETHTRCV_NUMBER_OF_ETHTRCV; TrcvNo++)
    {
        if(EthTrcv_Prv_ModeIndicationFlag[TrcvNo] == TRUE)
        {
            EthIf_TrcvModeIndication(TrcvNo, EthTrcv_Prv_CurrentMode[TrcvNo]);
            EthTrcv_Prv_ModeIndicationFlag[TrcvNo] = FALSE;
        }
    }
}

#endif // ETHTRCV_CONFIGURED

#define ETHTRCV_STOP_SEC_CODE
#include "EthTrcv_MemMap.h"

/*<>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</>*/



