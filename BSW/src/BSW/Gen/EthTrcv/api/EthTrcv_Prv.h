


#ifndef ETHTRCV_PRV_H_
# define ETHTRCV_PRV_H_
/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/
#include "EthTrcv.h"

// only use file if EthTrcv is required
#ifdef ETHTRCV_CONFIGURED

/*
***************************************************************************************************
* defines
***************************************************************************************************
*/
#define ETHTRCV_PRV_BCM89810        0
#define ETHTRCV_PRV_DP83848YB       1
#define ETHTRCV_PRV_MARVELL88E1116R 2
#define ETHTRCV_PRV_CDD             3
#define ETHTRCV_PRV_NO_PHY          4
#define ETHTRCV_PRV_TJA1100         5
#define ETHTRCV_PRV_LAN8700         6
#define ETHTRCV_PRV_DP83822         7
#define ETHTRCV_PRV_BCM89811        8
#define ETHTRCV_PRV_RTL9000AA       9

/* Size of Phy Identifier */
#define ETHTRCV_PHY_IDENTIFIER_SIZE             (2U)
#define ETHTRVC_PRV_REG2_OUI_POS                (6U)
#define ETHTRVC_PRV_REG3_OUI_POS                (10U)
#define ETHTRCV_PRV_REG3_MODEL_NUMBER_POS       (4U)
#define ETHTRCV_PRV_REG3_OUI_MASK               (0xFC00U)
#define ETHTRCV_PRV_REG3_MODEL_NUMBER_MASK      (0x03F0U)
#define ETHTRCV_PRV_REG3_REVISION_NUMBER_MASK   (0x000FU)

/* Phy Identifiers for TJA1100 */
#define ETHTRCV_PRV_TJA1100_OUI_NUMBER          (0x00006037U)
#define ETHTRCV_PRV_TJA1100_MODEL_NUMBER        (0x04U)
#define ETHTRCV_PRV_TJA1100_REVISION_NUMBER     (0x0U)

/* Link Quality definitions */
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_0       (0U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_10      (10U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_20      (20U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_30      (30U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_40      (40U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_50      (50U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_60      (60U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_70      (70U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_80      (80U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_90      (90U)
#define ETHTRCV_PRV_LINKQUALITY_PERCENT_100     (100U)

/* SQI values for Link quality */
#define ETHTRCV_PRV_LINKQUALITY_SQI_0           0x00U
#define ETHTRCV_PRV_LINKQUALITY_SQI_1           0x01U
#define ETHTRCV_PRV_LINKQUALITY_SQI_2           0x02U
#define ETHTRCV_PRV_LINKQUALITY_SQI_3           0x03U
#define ETHTRCV_PRV_LINKQUALITY_SQI_4           0x04U
#define ETHTRCV_PRV_LINKQUALITY_SQI_5           0x05U
#define ETHTRCV_PRV_LINKQUALITY_SQI_6           0x06U
#define ETHTRCV_PRV_LINKQUALITY_SQI_7           0x07U


/* TJA1100 specific macros */
#define ETHTRCV_PRV_REG17_DIS_LINK_CONTROL      (0x7FFFU)
#define ETHTRCV_PRV_REG17_EN_LINK_CONTROL       (0x8000U)
#define ETHTRCV_PRV_REG17_DIS_CONF_REG_ACCESS   (0xFFFBU)
#define ETHTRCV_PRV_REG17_EN_CONF_REG_ACCESS    (0x0004U)
#define ETHTRCV_PRV_REG17_RESET_TESTMODE_FIELD  (0xFE3FU)
#define ETHTRCV_PRV_REG17_TESTMODE_POS          (0x06U)

#define ETHTRCV_PRV_REG18_AUTO_OP_MANAGED           (0x0000U)
#define ETHTRCV_PRV_REG18_AUTO_OP_AUTONOMOUS        (0x4000U)

#define ETHTRCV_PRV_REG18_EN_AUTO_OP_MANAGED        (0xBFFFU)

#define ETHTRCV_PRV_REG23_PHYSTATE_IDLE             (0x0000U)
#define ETHTRCV_PRV_REG23_PHYSTATE_INITIALISING     (0x0001U)
#define ETHTRCV_PRV_REG23_PHYSTATE_CONFIGURED       (0x0002U)
#define ETHTRCV_PRV_REG23_PHYSTATE_OFFLINE          (0x0003U)
#define ETHTRCV_PRV_REG23_PHYSTATE_ACTIVE           (0x0004U)
#define ETHTRCV_PRV_REG23_PHYSTATE_ISOLATE          (0x0005U)
#define ETHTRCV_PRV_REG23_PHYSTATE_CABLETEST        (0x0006U)
#define ETHTRCV_PRV_REG23_PHYSTATE_TESTMODE         (0x0007U)

#define ETHTRCV_TJA1100_REG23_LINKQUALITY_FIELD     (0x00E0U)

#define ETHTRCV_TJA1100_REG17_CHKVALUE_LOOPBACK_NONE        (0x9800U)
#define ETHTRCV_TJA1100_REG17_CHKVALUE_LOOPBACK_INTERNAL    (0x9800U)
#define ETHTRCV_TJA1100_REG17_CHKVALUE_LOOPBACK_EXTERNAL    (0x9810U)
#define ETHTRCV_TJA1100_REG17_CHKVALUE_LOOPBACK_REMOTE      (0x9818U)

#define ETHTRCV_TJA1100_REG24_LINKFAIL_CNT_POS              (3U)
#define ETHTRCV_TJA1100_REG24_LINKFAIL_CNT_MASKVALUE        (0x00F8U)

#define ETHTRCV_PRV_REG25_SHORT_CIRCUIT             (0x0100U)
#define ETHTRCV_PRV_REG25_OPEN_CIRCUIT              (0x0080U)
#define ETHTRCV_PRV_REG25_OPEN_SHORT_CIRCUIT        (0x0180U)

/* RTL9000AA specific transceiver registers */
#define ETHTRCV_PRV_RTL9000AA_PHYIDENTIFIER_1     (0x001CU)
#define ETHTRCV_PRV_RTL9000AA_PHYIDENTIFIER_2     (0xCB00U)

#define ETHTRCV_PRV_RTL9000AA_RESET_MASKVALUE     (0x2100U)
#define ETHTRCV_PRV_RTL9000AA_RESET_CHECKVALUE    (0x2100U)

#define ETHTRCV_PRV_RTL9000AA_PHYREADYSTATE_MASKVALUE   (0x0007U)
#define ETHTRCV_PRV_RTL9000AA_PHYREADYSTATE_CHECKVALUE  (0x0003U)



// DET Macros
#if (ETHTRCV_CFG_DET_ENABLE == STD_ON)
# define ETHTRCV_CHECKDET_RETURN(Idx,FuncId,ErrId) \
               do{(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId, ErrId); return E_NOT_OK;}while(0)
# define ETHTRCV_CHECKDET_NORETURN(Idx,FuncId,ErrId) \
               do{(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId, ErrId); }while(0)
# define ETHTRCV_CHECKDETTRUE_RETURN(Cond,Idx,FuncId,ErrId)  do{if((Cond) == ETHTRCV_FALSE_B) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId, ErrId); return E_NOT_OK;}}while(0)
# define ETHTRCV_CHECKDETTRUE_RETURN_NO_VAL(Cond,Idx,FuncId,ErrId)  do{if((Cond) == ETHTRCV_FALSE_B) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId, ErrId); return;}}while(0)
# define ETHTRCV_CHECKDETTRUE_NORETURN(Cond,Idx,FuncId,ErrId)  do{(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId, ErrId); }while(0)
# define ETHTRCV_CHECKDETINIT_RETURN(CurrentState,ExpectedState,Idx,FuncId)  do{if((CurrentState) < (ExpectedState)) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId, ETHTRCV_E_NOT_INITIALIZED); return E_NOT_OK;}}while(0)
# define ETHTRCV_CHECKDETINIT_NORETURN(CurrentState,ExpectedState,Idx,FuncId)  do{if((CurrentState) < (ExpectedState)) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId, ETHTRCV_E_NOT_INITIALIZED);}}while(0)
# define ETHTRCV_CHECKDETTRCVIDX_RETURN(Idx,FuncId)  do{if((Idx) >= ETHTRCV_NUMBER_OF_ETHTRCV) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId,   ETHTRCV_E_INV_TRCV_IDX);return E_NOT_OK;}}while(0)
# define ETHTRCV_CHECKDETTRCVIDX_NORETURN(Idx,FuncId)  do{if((Idx) >= ETHTRCV_NUMBER_OF_ETHTRCV) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId,   ETHTRCV_E_INV_TRCV_IDX);}}while(0)
# define ETHTRCV_CHECKDETNULLPTR_RETURN(Idx,Ptr,FuncId)  do{if((Ptr) == NULL_PTR) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId,   ETHTRCV_E_INV_POINTER);return E_NOT_OK;}}while(0)
# define ETHTRCV_CHECKDETNULLPTR_RETURN_NO_VAL(Idx,Ptr,FuncId)  do{if((Ptr) == NULL_PTR) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId,   ETHTRCV_E_INV_POINTER);return;}}while(0)
# define ETHTRCV_CHECKDETNULLPTR_NORETURN(Idx,Ptr,FuncId)  do{if((Ptr) == NULL_PTR) \
                {(void)Det_ReportError(ETHTRCV_MODULE_ID,Idx,FuncId,   ETHTRCV_E_INV_POINTER);}}while(0)
#else
# define ETHTRCV_CHECKDET_RETURN(Idx,FuncId,ErrId)                              do{}while(0)
# define ETHTRCV_CHECKDET_NORETURN(Idx,FuncId,ErrId)                            do{}while(0)
# define ETHTRCV_CHECKDETTRUE_RETURN(Cond,Idx,FuncId,ErrId)                     do{}while(0)
# define ETHTRCV_CHECKDETTRUE_RETURN_NO_VAL(Cond,Idx,FuncId,ErrId)              do{}while(0)
# define ETHTRCV_CHECKDETTRUE_NORETURN(Cond,Idx,FuncId,ErrId)                   do{}while(0)
# define ETHTRCV_CHECKDETINIT_RETURN(CurrentState,ExpectedState,Idx,FuncId)     do{}while(0)
# define ETHTRCV_CHECKDETINIT_NORETURN(CurrentState,ExpectedState,Idx,FuncId)   do{}while(0)
# define ETHTRCV_CHECKDETTRCVIDX_RETURN(Idx,FuncId)                             do{}while(0)
# define ETHTRCV_CHECKDETTRCVIDX_NORETURN(Idx,FuncId)                           do{}while(0)
# define ETHTRCV_CHECKDETNULLPTR_RETURN(Idx,Ptr,FuncId)                         do{}while(0)
# define ETHTRCV_CHECKDETNULLPTR_RETURN_NO_VAL(Idx,Ptr,FuncId)                  do{}while(0)
# define ETHTRCV_CHECKDETNULLPTR_NORETURN(Idx,Ptr,FuncId)                       do{}while(0)
#endif


#if (ETHTRCV_CFG_DEM_ENABLE == STD_ON)
# define EthTrcv_DemReportErrorStatus(ERROR_CODE, EvId) do{if((ERROR_CODE)!=0) \
                                                            {(void)Dem_ReportErrorStatus((ERROR_CODE),(EvId));}}while(0)
#else
# define EthTrcv_DemReportErrorStatus(ERROR_CODE, EvId) do{}while(0)
#endif


/*
 ***************************************************************************************************
 * Internal Function Prototypes
 ***************************************************************************************************
*/
#define ETHTRCV_START_SEC_CODE
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"

FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_CheckForNextCommand(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_CheckForNextInit(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_ModeDown(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_ModeActive(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_StartAutoNeg(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_Or(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_And(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_Clr0(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_Clr1(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetMode(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetLink(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetBaud2(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetDuplexMode2(void);
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_CheckExec(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_Wait_uS(void);
# if (ETHTRCV_NO_PHY_USED == STD_ON)
FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_Fct_GetModeNoPhy(void);
#endif

/*
 ***************************************************************************************************
 * Configurable Internal Function Prototypes
 ***************************************************************************************************
*/
#if defined(ETHTRCV_TJA1100_USED)
 #if (ETHTRCV_TJA1100_USED == STD_ON)
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_UpdatePhyOperationType(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_UpdateBuff1WithReqMode(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_PhyTestModeCheck(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_CableDiagnosticCheck(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_GetCableSignalQuality(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_InitFct1(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_InitFct2(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_UpdateBuff1WithReqLoopBackMode(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_PhyLoopBackModeCheck(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_ExtractPhyIdentifier(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_CheckForPhyAccess(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_ExtractLinkStatistics(void);
#endif
#endif

# if (ETHTRCV_RTL9000AA_USED == STD_ON)
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_CheckForResetToFinish(void);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_Prv_CheckForPhyReady(void);
#endif
#define ETHTRCV_STOP_SEC_CODE
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"

/*
 ***************************************************************************************************
 * private const-variables
 ***************************************************************************************************
*/
#define ETHTRCV_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"
extern CONST(EthTrcv_Cfg_TrcvInit_tst,ETHTRCV_PB_CONST) EthTrcv_Cfg_TrcvInit_ast[];
extern CONST(EthTrcv_Cfg_CfgInit_tst,ETHTRCV_PB_CONST) EthTrcv_Cfg_CfgInit_ast[];
extern CONST (EthTrcv_Cfg_CfgData_tst, ETHTRCV_PB_CONST) EthTrcv_Cfg_CfgData_ast[];

#if ETHTRCV_TJA1100_USED == STD_ON
extern CONST(EthTrcv_Cfg_TJA1100_tst, ETHTRCV_PB_CONST) EthTrcv_Cfg_TJA1100_ast[];
extern CONST(EthTrcv_PhyIdentificationType_tst,ETHTRCV_CFG) EthTrcv_PhyIdentification_ast[];
#endif

#define ETHTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"


/*
 ***************************************************************************************************
 * private RAM-variables.
 ***************************************************************************************************
Defined as extern to have debugg access according Autosar
*/

#define ETHTRCV_START_SEC_VAR_NO_INIT_UNSPECIFIED
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"
extern VAR(boolean,                ETHTRCV_VAR)    EthTrcv_Prv_MiiCommunicationFlag_b;
extern VAR(EthTrcv_StateType,      ETHTRCV_VAR)    EthTrcv_Prv_State_e[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(EthTrcv_ModeType,       ETHTRCV_VAR)    EthTrcv_Prv_CtrlMode_e[];
extern VAR(EthTrcv_WupReasonType,  ETHTRCV_VAR)    EthTrcv_Prv_WupReason_e[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(EthTrcv_InitStateType,  ETHTRCV_VAR)    EthTrcv_Prv_InitState_e[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(EthTrcv_ModeType,       ETHTRCV_VAR)    EthTrcv_Prv_CurrentMode[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(EthTrcv_ModeType,       ETHTRCV_VAR)    EthTrcv_Prv_RequestedMode[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(EthTrcv_LinkStateType,  ETHTRCV_VAR)    EthTrcv_Prv_LinkState[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(EthTrcv_BaudRateType,   ETHTRCV_VAR)    EthTrcv_Prv_BaudRate[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(EthTrcv_DuplexModeType, ETHTRCV_VAR)    EthTrcv_Prv_DuplexMode[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(boolean,                ETHTRCV_VAR)    EthTrcv_Prv_ModeIndicationFlag[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(boolean,                ETHTRCV_VAR)    EthTrcv_Prv_AutoNegotiationReq[ETHTRCV_MAX_TRCVS_SUPPORTED];
extern VAR(uint16,                 ETHTRCV_VAR)    EthTrcv_Prv_MiiCommunicationPos;
extern VAR(uint16,                 ETHTRCV_VAR)    EthTrcv_Prv_Buff0;
extern VAR(uint16,                 ETHTRCV_VAR)    EthTrcv_Prv_Buff1;
extern VAR(uint16,                 ETHTRCV_VAR)    EthTrcv_Prv_TimeoutCount;
#define ETHTRCV_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"



#endif   // ETHTRCV_CFG_CONFIGURED
#endif  // ETHTRCV_PRV_H_

/*
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
*/


