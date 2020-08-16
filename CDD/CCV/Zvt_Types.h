/*
 * Zvt_Types.h
 *
 *  Created on: 2020Äê3ÔÂ5ÈÕ
 *      Author: admin
 */

#ifndef CDD_ETHCOMM_ZVT_TYPES_H_
#define CDD_ETHCOMM_ZVT_TYPES_H_

#include "Platform_Types.h"
#include "fsm.h"
#include "ASW_RTE.h"
#include "Rte_Asw_Swc.h"

#define PT_CFG_MAX_TIMES		(3u)
#define PT_SID_LEN				(32U)
#define PT_UID_LEN				(10U)
#define CCV_DRAFT				(0u)
#define DEBUG_PHASE				TRUE
#define DEBUG_COPY_PHASE		TRUE
#define PAY_DEFAULT_ERRID       (0xEE)

typedef uint8 (*configprocess_t)(void);

extern uint8 ZVT_CarIDValue[10u];
extern uint8 ZVT_CarSIDValue[32u];

typedef enum
{
	German 	 = 0,
	English,
	French,
	Italian
}zvt_languagetype;

typedef enum
{
	CreditCard 	 = 1,
	RfidCard
}zvt_cardtype;

typedef enum
{
	PreAuthTxRmb_Start = 0,
	PreAuthTxRmb_Stop

}zvt_preauth_txdatatype;


typedef enum
{
	ReversalTxData_Start = 0,
	ReversalTxData_Stop

}zvt_reversal_txdatatype;

typedef enum
{
	StopPreAuth = 0,
	StartPreAuth
}zvt_preaut_flag;

typedef enum
{
	StopPartialReversal = 0,
	StartPartialReversal
}zvt_reversal_flag;

typedef enum
{
	Reversal_N_OK = 0,
	Reversal_OK
}zvt_reversal_result;

typedef enum
{
	IdleStateReversal = 0,
	RunStateReversal
}zvt_reversal_state;

typedef enum
{
	PreAuth_N_OK = 0,
	PreAuth_OK
}zvt_preaut_resultflag;


typedef enum
{
	ZVT_RET_OK 	 = 0,
	ZVT_RET_N_OK = 1
}zvt_retvalue;

typedef enum
{
	ResultCode_OK = 0u,
	ResultCode_N_OK
}zvt_erridflag;

typedef enum
{
	NonZvtFormat = 0xF,
	StdZvtFormat    = 0x01,
	ExtZvtFormat    = 0x02
}zvt_formattype;

typedef enum
{
	ZvtSniffer_Stop = 0u,
	ZvtSniffer_Start
}zvt_arpsniffer;

typedef enum
{
	PtParamInit_N_OK = 0u,
	PtParamInit_OK
}zvt_ptparaminit;

typedef enum
{
	zvtFsm_TcpIdle = 0u,
	zvtFsm_Error ,
	zvtFsm_TcpRun,
	zvtFsm_PtIdle ,
	zvtFsm_PT_Init_1_42,
	zvtFsm_PT_Init_NewIP,
	zvtFsm_PtRun,
	zvtFsm_PT_Config0813,
	zvtFsm_PT_StatusEnquiry0501,
	zvtFsm_PT_PreAuthorized0622,
	zvtFsm_PT_StopchargeReturnMoney0623,
	zvtFsm_PT_ChangeLanguage0830,
	zvtFsm_PT_PositiveAck8000,
	zvtFsm_PT_PositiveAck8400,

	zvtFsm_PT_Rfid

}zvt_func_state_machine;

typedef enum
{
	PtRespCmd0800_N_OK = 0u,
	PtRespCmd0800_OK
}zvt_pt0800ack;

typedef enum
{
	PtRespCmd8000_N_OK = 0u,
	PtRespCmd8000_OK
}zvt_pt8000ack;


typedef enum
{
	PtRespCmd8400_N_OK = 0u,
	PtRespCmd8400_OK
}zvt_pt8400ack;

typedef enum
{
	PT_wait_for_amount_confirmation0x00 = 0x00,
	Please_wait0x04 = 0x04,
	PT_send_post_booking0x06 = 0x06,
	Insert_card0x0a =0x0A,
	BeingProcessed_PleaseWait0x0e  = 0x0E,
	Please_wait0x17  = 0x17,
	PIN_try_limit_exceeded0x18 = 0x18,
	Service_Mode_0x1a = 0x1A,
	Approved_Please_fill_up0x1b =0x1B,
	PT_Detected_Customer_Card_Insertion0x68 = 0x68,
	Connecting_Dial_Up0xd2 = 0xD2,
	Dial_up_connection_made0xd3 = 0xD3,
	Np_propriate_ZVT_status_code_matches_the_status0xff = 0xFF
}zvt_cmd04ff_intermediate_status;



typedef enum
{
	no_error = 0x00,

	PtCfg_Factory0813Err = 0x10,
	PtCfg_User0813Err = 0x11,
	PtCfg_User0693Err = 0x12,
	PtCfg_User0670EmvErr = 0x13,


	card_not_readable_0x64 = 0x64u,
	card_data_not_present_0x65,
	processing_error_0x66,
	function_not_permitted_for_ec_and_Maestro_cards_0x67,
	function_not_permitted_for_credit_and_tank_cards_0x68,
	turnover_file_full_0x6A = 0x6A,
	function_deactivated_PT_not_registered_0x6B,
	abort_via_timeout_or_abort_key_0x6C,
	card_in_blocked_list_0x6E = 0x6Eu,
	wrong_currency_0x6F,
	credit_not_sufficient_0x71 = 0x71u,
	chip_error_0x72,
	card_data_incorrect_0x73,
	DUKPT_engine_exhausted_0x74,
	text_not_authentic_0x75,
	PAN_not_in_white_list_0x76,
	end_of_day_batch_not_possible_0x77,
	card_expired_0x78,
	card_not_yet_valid_0x79,
	card_unknown_0x7A,
	fallback_to_magnetic_stripe_for_girocard_not_possible_0x7B,
	fallback_to_magnetic_stripe_not_possible_0x7C,
	communication_error_0x7D,
	fallback_to_magnetic_stripe_not_possible_debit_advice_possible_0x7E,
	function_not_possible_0x83 = 0x83u,
	key_missing0x85 = 0x85u,
	PIN_pad_defective0x89 = 0x89u,
	ZVT_protocol_error_0x9A = 0x9Au,
	error_from_dial_up_communication_fault_0x9B,
	please_wait_0x9C,
	receiver_not_ready = 0xA0u,
	remote_station_does_not_respond_0xA1,
	no_connection_0xA3 = 0xA3u,
	submission_of_Geldkarte_not_possible_0xA4,
	function_not_allowed_due_to_PCI_DSS_P2PE_rules_0xA5,
	memory_full_0xB1 = 0xB1u,
	merchant_journal_full_0xB2,
	already_reversed_0xB4 = 0xB4u,
	reversal_not_possible_0xB5,
	pre_authorisation_incorrect_or_amount_wrong_0xB7 = 0xB7u,
	error_pre_authorisation_0xB8,
	voltage_supply_to_low_0xBF = 0xBFu,
	card_locking_mechanism_defective_0xC0 = 0xC0u,
	merchant_card_locked_0xC1,
	diagnosis_required_0xC2,
	maximum_amount_exceeded_0xC3,
	card_profile_invalid_0xC4,
	payment_method_not_supported_0xC5,
	currency_not_applicable_0xC6,
	amount_too_small = 0xC8u,
	max_transaction_amount_too_small_0xC9,
	function_only_allowed_in_EURO_0xCB = 0xCBu,
	printer_not_ready_0xCC,
	Cashback_not_possible_0xCD,
	function_not_permitted_for_service_cards_bank_customer_cards_0xD2 = 0xD2u,
	card_inserted_0xDC = 0xDCu,
	error_during_card_eject_0xDD,
	error_during_card_insertion_0xDE,
	remote_maintenance_activated_0xE0 = 0xE0u,
	card_reader_does_not_answer_card_reader_defective_0xE2 = 0xE2u,
	shutter_closed_0xE3,
	Terminal_activation_required_0xE4,
	min_one_goods_group_not_found_0xE7 = 0xE7u,
	no_goods_groups_table_loaded_0xE8,
	restriction_code_not_permitted_0xE9,
	card_code_not_permitted_0xEA,
	function_not_executable_0xEB,
	PIN_processing_not_possible_0xEC,
	PIN_pad_defective_0xED,
	open_end_of_day_batch_present_0xF0 = 0xF0u,
	ec_cash_Maestro_offline_error_0xF1,
	OPT_error_0xF5 = 0xF5u,
	OPT_data_not_available_0xF6,
	error_transmitting_offline_transactions_0xFA = 0xFAu,
	turnover_data_set_defective_0xFB,
	necessary_device_not_present_or_defective_0xFC,
	baudrate_not_supported_0xFD,
	register_unknown_0xFE,
	system_error_0xFF,
	Default_NullCode = 0xEE
}zvt_apdu_err_id;

typedef enum
{
	PtRegistration_Tdle = 0u,
	PtRegistration_Run,
	PtRegistrationSendData_Stop,
	PtRegistrationSendData_Start
}zvt_ptregistration_state;

typedef enum
{
	PtConfigFactory0813_Tdle = 0u,
	PtConfigFactory0813_Run,
	PtConfigFactory0813SendData_Stop,
	PtConfigFactory0813SendData_Start
}zvt_ptconfig0813_state;

typedef enum
{
	PtConfigUser0813_Tdle = 0u,
	PtConfigUser0813_Run,
	PtConfigUser0813SendData_Stop,
	PtConfigUser0813SendData_Start
}zvt_ptconfiguser0813_state;

typedef enum
{
	PtInit0693_Tdle = 0u,
	PtInit0693_Run,
	PtInit0693SendData_Stop,
	PtInit0693SendData_Start
}zvt_ptinit0693_state;

typedef enum
{
	PtExtDiag_Tdle = 0u,
	PtExtDiag_Run,
	PtExtDiagSendData_Stop,
	PtExtDiagSendData_Start
}zvt_ptextdiag_state;

typedef enum
{
	PtConfigDiag_Tdle = 0u,
	PtConfigDiag_Run,
	PtConfigDiagSendData_Stop,
	PtConfigDiagSendData_Start
}zvt_ptconfigdiag_state;

typedef enum
{
	PtEmvDiag_Tdle = 0u,
	PtEmvDiag_Run,
	PtEmvDiagSendData_Stop,
	PtEmvDiagSendData_Start
}zvt_ptemvdiag_state;

typedef enum
{
	PtInit_Stop = 0u,
	PtInit_Start,
	PtInit_1_42_N_OK,
	PtInit_1_42_OK,
	PtInit_UserIP_N_OK,
	PtInit_UserIP_OK

}zvt_ptinit_switch;

typedef enum
{
	WaitforCmd040f_OK = 0u,
	WaitforCmd040f_N_OK
}zvt_preauth_waitfor040f;

typedef enum
{
	Cmd040fArrived_OK = 0u,
	Cmd040fArrived_N_OK
}zvt_preauth_cmd040farrived;

typedef enum
{
	Cmd060fArrived_OK = 0u,
	Cmd060fArrived_N_OK
}zvt_config0813_cmd060farrived;

typedef enum
{
	SendFactory0813 = 0u,
	DelayFactory0813,
	CheckCennection,
    WaitforTID,


}zvt_configfactory0813_step;


typedef enum
{
	Send0622Sid_N_OK = 1u,
	Send0622Sid_OK,
	Waitfor_0622SID,
	PreAuthorize_OK,
	PreAuthorize_Over,
	PreAuthorize_OverTime

}ccv_preauthstep_t;

typedef enum
{
	UserSend06C0_RfidUID = 1u,
	Waitfor_RfidUID,
	Check_RfidUID,
	Waitfor_UserSID,
	Arrived_UserSID,
	Check_UserSID,
	Waitfor_UserSend0623,
	UserSend0623_N_OK,
	UserSend0623_OK,
	UserStop_Over

}ccv_userstopstep_t;

typedef enum
{
	MifareSend06C0_N_OK = 1u,
    MifareSend06C0_Wait,
	MifareSend06C0_OK,
	MifareStep_Over,
	MifareStep_TimeOut

}zvt_mifarestep_t;


typedef enum
{
	ReversalSend0623_N_OK = 1u,
	ReversalSend0623_OK,
	ReversalStep_Over

}ccv_reversalstep_t;


typedef enum
{
	Factory0600,
	User0600,
	Factory0813,
	User0813,
	User0693,
	User0670emv,
	PtConfig_OK,
	PtConfig_TimeOut

}ccv_configstep_t;

typedef enum
{
	SendCmd0501,
	WaitAckFor0501,
	CheckTcpConnnectionOver

}ccv_tcpconnectstep_t;

typedef struct
{
	uint8 Cfg0813Factory_Times;
	uint8 Cfg0813User_Times;
	uint8 Cfg0693_Times;
	uint8 Cfg0670Emv_Times;

	uint8 Cfg0693_RecordErrID[PT_CFG_MAX_TIMES];
	uint8 Cfg0670Emv_RecordErrID[PT_CFG_MAX_TIMES];

	ccv_configstep_t ConfigStep;

}ccv_configdata_t;



typedef struct
{
	ccv_preauthstep_t 		PreAuthStep;

	uint8  ErrCode;
	uint8  getSID;
	uint8  getReceiptNo;
	uint8  SID_0x1F14_32B[32u];
	uint8  getCmd040fReceiptNumber0x87[2u];

	uint8  Bitmap06Get141F_Backup[800u];
	uint16 Bitmap06Length;

	uint32 CounterStep1;
	uint32 CounterStep2;
	uint32 CounterStep3;
	uint32 CounterStep4;

}zvt_preauthdata_t;


typedef struct
{
	ccv_reversalstep_t 	ReversalStep;

	uint8  ErrCode;
	uint8  getSID;
	uint8 SID_0x1F14_32B[32u];


	uint8 rxCmd040fReceiptNumber0x87[2u];
	uint8 txCmd0623ReversalMoney0x04[4u];
	uint8 txCmd0623ReceiptNumber0x87[2u];

	uint8  Bitmap06Get141F_Backup[800u];
	uint16 Bitmap06Length;

	uint32 TimeOutCounter;
	uint32 TimeOutDefaultCounter;
	uint32 TimeOutWaitAckCounter;


}zvt_partialreversaldata_t;

typedef struct
{
	ccv_userstopstep_t 	UserStopStep;

	uint8  ErrCode;
	uint8  getSID;
	uint8 SID_0x1F14_32B[32u];

	uint8 rxCmd040fReceiptNumber0x87[2u];
	uint8 txCmd0623ReversalMoney0x04[4u];
	uint8 txCmd0623ReceiptNumber0x87[2u];

	uint8  Bitmap06Get141F_Backup[800u];
	uint16 Bitmap06Length;

	uint32 TimeOutWaitUidCounter;
	uint32 TimeOutArrivedUidCounter;
	uint32 TimeOutCounter;
	uint32 TimeOutDefaultCounter;
	uint32 TimeOutWaitAckCounter;
	uint32 TimeOutArrivedAckCounter;
	uint32 WaitforTx0623Counter;
	uint32 WaitforTx0623DefaultCounter;
	uint32 UserSend0623Counter;

}zvt_credituserstopdata_t;


typedef struct
{
	zvt_mifarestep_t 	MifareCardStep;

	uint8 ErrCode;
	uint8 getUID;
	uint8 UID_0x4C0A_10B[10u];
	uint8 UID_0x4C0A_10B_temp[10u];

	uint8  Bitmap06Get4C0A_Backup[800u];
	uint16 Bitmap06Length;

	uint32 TimeOutCounter;
	uint32 TimeOutDefaultCounter;
	uint32 WaitforTx06C0Counter;
	uint32 WaitforTx06C0DefaultCounter;
	uint32 Send06C0Counter;

}zvt_mifaredata_t;

typedef struct
{

	uint8 debugFlag1;
	uint8 debugFlag2;
	uint8 debugFlag3;
	uint8 debugFlag4;
	uint8 debugFlag5;
	uint8 debugFlag6;
	uint8 debugFlag7;
	uint8 debugFlag8;
	uint8 debugFlag9;
	uint8 debugFlag10;
	uint8 debugFlag11;
	uint8 debugFlag12;
	uint8 debugFlag13;
	uint8 debugFlag14;
	uint8 debugFlag15;
	uint8 debugFlag16;
	uint8 debugFlag17;
	uint8 debugFlag18;
	uint8 debugFlag19;
	uint8 debugFlag20;



	uint8 debugFlag_Ethernet_TcpIp_ReceiveLong;

	uint32 counter1;
	uint32 counter2;
	uint32 counter3;
	uint32 counter4;
	uint32 counter5;
	uint32 counter6;
	uint32 counter7;
	uint32 counter8;
	uint32 counter9;
	uint32 counter10;

}zvt_debugflag_t;

typedef struct
{
	uint32 ui32_Counter1;
	uint32 ui32_Counter2;
	uint32 ui32_Counter3;
	uint32 ui32_Counter4;

}zvt_debugcounter_t;


typedef struct
{
	uint8 Fsmflag;
	uint32 FsmCounter1;
	uint32 FsmCounter2;

}zvt_switch_fsm;

typedef struct
{
	zvt_pt8400ack   PtResp8400Flag;
	zvt_pt0800ack   PtResp8000Flag;

}zvt_pt_cmdflag_t;

typedef struct
{
	zvt_apdu_err_id   PtCmd040fErrCode;
	zvt_apdu_err_id   PtCmd060fErrCode;
	zvt_apdu_err_id   PtCmd061eErrCode;
	zvt_apdu_err_id   PtCmd06d3ErrCode;
	zvt_apdu_err_id   PtCmd8000ErrCode;
	zvt_apdu_err_id   PtCmd8400ErrCode;

}zvt_pt_errcode_t;

typedef struct
{
	uint16   PtCmd040fReceipt87No;
	uint16   PtCmd060fReceipt87No;
	uint16   PtCmd061eReceipt87No;
	uint16   PtCmd06d3Receipt87No;

}zvt_pt_receiptnumber_t;

typedef struct
{

	uint16 		Counter_PtRegistration0600;
	uint16 		DefaultCounter_PtRegistration0600;
	zvt_ptregistration_state 	PtRegistration0600;
	zvt_ptregistration_state 	PtRegistration0600_TxDataFlag;

}zvt_ptconfig_factory0600_t;


typedef struct
{
	uint16 		Counter_PtRegistration0600;
	uint16 		DefaultCounter_PtRegistration0600;
	zvt_ptregistration_state 	PtRegistration0600;
	zvt_ptregistration_state 	PtRegistration0600_TxDataFlag;

}zvt_ptconfig_user0600_t;


typedef struct
{
	zvt_config0813_cmd060farrived 	Factory0813_Waitfor060f;
	zvt_ptconfig0813_state 		PtConfig0813;
	zvt_ptconfig0813_state 		PtConfig0813_TxDataFlag;

	uint8 		Factory0813_getCmd060fTID[4u];

	uint16 		Counter_PtConfig0813;
	uint16 		DefaultCounter_PtConfig0813;

}zvt_ptconfig_factory0813_t;

typedef struct
{

	zvt_configfactory0813_step	Factory0813Step;
	uint8 	Factory0813_getCmd060fTID[4u];
	uint16  Factory0813_Counter;
	uint16  Factory0813_DefaultCounter;
	uint16  Factory0813CheckTID_Counter;
	uint16  Factory0813CheckTID_DefaultCounter;
	uint16  Factory0813CheckIP_Counter;
	uint16  Factory0813CheckIP_DefaultCounter;

}ccv_ptconfig_factory0813_t;

typedef struct
{
	zvt_config0813_cmd060farrived 	User0813_Waitfor060f;
	zvt_ptconfiguser0813_state 		PtConfig0813;
	uint8 User0813_getCmd060fTID[4u];

	uint16 		Counter_PtConfig0813;
	uint16 		DefaultCounter_PtConfig0813;
	zvt_ptconfig0813_state 		PtConfig0813_TxDataFlag;

}zvt_ptconfig_user0813_t;

typedef struct
{
    uint8	User0813Step;
	uint8 	User0813_getCmd060fTID[4u];
	uint16  User0813_Counter;
	uint16  User0813_DefaultCounter;
	uint16  User0813CheckTID_Counter;
	uint16  User0813CheckTID_DefaultCounter;

}ccv_ptconfig_user0813_t;

typedef struct
{
	uint16 		Counter_PtInitialisation0693;
	uint16 		DefaultCounter_PtInitialisation0693;
	zvt_ptinit0693_state 		PtInitialisation0693;
	zvt_ptinit0693_state 		PtInitialisation0693_TxDataFlag;

}zvt_ptconfig_user0693_t;

typedef struct
{
    uint8	Init0693Step;
	uint16 	PtInitialisation0693_Counter;
	uint16 	PtInitialisation0693_DefaultCounter;


	zvt_apdu_err_id   Init0693Get061eErrCode;



}ccv_ptconfig_0693_t;

typedef struct
{
	uint16 		Counter_PtEmvDiag0670_4;
	uint16 		DefaultCounter_PtEmvDiag0670_4;
	zvt_ptemvdiag_state 		PtEmvDiag0670_4;
	zvt_ptemvdiag_state 		PtEmvDiag0670_4_TxDataFlag;

}zvt_ptconfig_user0670emv_t;

typedef struct
{
    uint8	Diag0670EmvStep;
	uint16 	Diag0670Emv_Counter;
	uint16 	Diag0670Emv_DefaultCounter;


	zvt_apdu_err_id   Diag0670EmvGet061eErrCode;


}ccv_ptconfig_0670emv_t;

typedef struct
{
	uint8 		CheckTcpConnectionTimes;
	uint16 		Counter_PtInit142Connect;
	uint16 		Counter_PtInitReConnect;

	uint16 		DefaultCounter_PtInit142Connect;
	uint16 		DefaultCounter_PtInitReConnect;

	zvt_pt0800ack               PtResp0800Flag;
	zvt_ptinit_switch			PtInitSwitch;
	zvt_ptinit_switch           PtInit142Connect;
	zvt_ptinit_switch           PtInitReConnect;
	ccv_tcpconnectstep_t 		CheckTcpConnectionStep;


}zvt_pt_init_statemachine_t;

typedef struct
{
	uint8 TxReversalDataFlag;
	zvt_preauth_txdatatype State_PreAuth;

}zvt_preauth_fsm;

typedef struct
{
	uint8 waitCmd04FF_PleaseFillUp0x1b_flag;
	uint8 waitCmd040F_Receipt0x87_flag;
	uint8 waitCmd04FF_ConnectDialUp0xd2_flag;

}zvt_preauth_wait;

typedef struct
{
	uint32 ZvtCom_Write_switch;

	uint8 PT_ConfigResult_flg;           /*fail = 0,  success = 1u*/
	zvt_apdu_err_id SetCCVFault_enum_Watch;


	uint8 CCU1_Set0622PreAut_flg;
	uint8 CCU1_Set0623SettleAccount_flg;
	zvt_apdu_err_id CCU1_SetCCVFault_enum;
	uint8 CCU1_Set06C0CardSID_flg;
	uint8 CCU1_SetCCVCreditCardReceipt_numb[2u];
	uint8 CCU1_SetCCVCreditCardSID_numb[32u];

	uint8 CCU2_Set0622PreAut_flg;
	uint8 CCU2_Set0623SettleAccount_flg;
	zvt_apdu_err_id CCU2_SetCCVFault_enum;
	uint8 CCU2_Set06C0CardSID_flg;
	uint8 CCU2_SetCCVCreditCardReceipt_numb[2u];
	uint8 CCU2_SetCCVCreditCardSID_numb[32u];

	uint8 CCU1_Set06C0CardUID_flg;
	uint8 CCU1_SetCCVRFIDCardUID_numb[10u];

	uint8 CCU2_Set06C0CardUID_flg;
	uint8 CCU2_SetCCVRFIDCardUID_numb[10u];

}zvt_wrcomtest_t;


typedef struct
{
	uint32 ZvtCom_Read_switch;

	uint8 PT_ConfigSwitch_flg;           /*off = 0,  on = 1u*/

	zvt_cardtype CCU1_CardType_enum;
	zvt_cardtype CCU2_CardType_enum;

	uint8 CCU1_ZVT0622PreAut_flg;
	uint8 CCU2_ZVT0622PreAut_flg;
	uint8 CCU1_ZVT06C0CardSID_flg;
	uint8 CCU2_ZVT06C0CardSID_flg;
	uint8 CCU1_ZVT0623SettleAccount_flg;
	uint8 CCU2_ZVT0623SettleAccount_flg;
	uint8 LeftCheckSuccess_flg;
	uint8 RightCheckSuccess_flg;
	uint8 CCU1_PreMoney_rmb[2u];
	uint8 CCU2_PreMoney_rmb[2u];
	uint8 CCU1_RemainMoney_rmb[2u];
	uint8 CCU2_RemainMoney_rmb[2u];
	uint8 LeftStartCreditCardSID_numb[32u];
	uint8 LeftEndCreditCardSID_numb[32u];
	uint8 RightStartCreditCardSID_numb[32u];
	uint8 RightEndCreditCardSID_numb[32u];

	uint8 LeftCreditCardReceipt_numb[2u];
	uint8 RightCreditCardReceipt_numb[2u];

	uint8 CCU1_ZVT06C0CardUID_flg;
	uint8 CCU2_ZVT06C0CardUID_flg;
	uint8 LeftRFIDCardUID_numb[10u];
	uint8 RightRFIDCardUID_numb[10u];

	uint8  PtCfg_TidNo[4u];
	uint8  PtCfg_IpAddr[4u];
	uint8  PtCfg_IpNetmask[4u];
	uint8  PtCfg_IpGateway[4u];

	uint8  ChgUsr_IpAddr[4u];
	uint8  ChgUsr_IpGateway[4u];

}zvt_rdcomtest_t;


typedef struct
{


	uint8 ReadCardSuccess_flg;
    uint8 HandleReversalSuccess_flg;
	uint8 SetCCVRFIDCardUID_numb[10u];
	uint8 SetCCVCreditCardSID_numb[32u];
	uint16 SetCCVCreditCardReceipt;

	uint32 Zvt_WriteRte_switch;
	zvt_apdu_err_id SetCCVFault_enum;
	uint8 PT_CfgResult_flg;           /*fail = 0,  success = 1u*/

}zvt_writerte_t;


typedef struct
{
	uint32 Zvt_ReadAsw_switch;

	uint8 PT_CfgSwitch_flg;           /*off = 0,  on = 1u*/

	zvt_cardtype CCU1_MCVCardType_enum;
	zvt_cardtype CCU2_MCVCardType_enum;

	zvt_cardtype CCU1_MCVCardType_enum_bak;
	zvt_cardtype CCU2_MCVCardType_enum_bak;

	uint8 AGunStart_flg;
	uint8 BGunStart_flg;
	uint8 AGunStop_flg;
	uint8 BGunStop_flg;
	uint8 CCU1_AutoFinish_flg;
	uint8 CCU2_AutoFinish_flg;

	float32 CCU1_PreMoney_rmb;
	float32 CCU2_PreMoney_rmb;
	float32 CCU1_RemainMoney_rmb;
	float32 CCU2_RemainMoney_rmb;

	uint8 CCU1_ZVT06C0CardUID_flg;
	uint8 CCU2_ZVT06C0CardUID_flg;

}zvt_readasw_t;



typedef struct
{
	uint8 class_ccrc;
	uint8 instr_aprc;
}zvt_apdu_controlfield_t;

typedef struct
{
	uint8 lo_byte;
	uint8 hi_byte;
}zvt_apdu_extlengthfield_t;

typedef struct
{
	zvt_apdu_controlfield_t control_field;
	uint8 					length_field;
	uint8* 					pData_block;
}zvt_apdu_stdformat_t;


typedef struct
{
	zvt_apdu_controlfield_t 	control_field;
	uint8  						ext_format_flag;
	zvt_apdu_extlengthfield_t 	extlength_field;
	uint8* 						pData_block;
}zvt_apdu_extformat_t;

typedef struct
{
	uint8  						cmd04ff_intermediate_status;
	uint8 						cmd04ff_timeout;
	uint8* 						pCmd04ff_TLV_Container;
}zvt_cmd04ff_stdformat_t;

typedef struct
{
	uint8  						cmd061e_Result_Code;
	uint8* 						pCmd061e_TLV_Container;
}zvt_cmd061e_stdformat_t;

typedef struct
{
	zvt_formattype formatStdExtFlag;
	uint8 Resultcode0x27_2B;
	uint8 TerminalID0x29_5B[4u];
	uint8 Amount0x04_7B[6u];
	uint8 Tracenumber0x0B_4B[3u];
	uint8 TimeBCD0x0c_4B[3u];
	uint8 DateBCD0x0d_3B[2u];
	uint8 ExpiryDateBCD0x0e_3B[2u];
	uint8 CardSequenceNumberBCD0x17_3B[2u];
	uint8 StatusBytePaymentTypeCardType0x19_2B[1u];
	uint8 VU_Number0x2a_16B[15u];
	uint8 ReceiptNumberReversal0x37_4B[3u];
	uint8 UID_0x4c_2_10B[10u];
	uint8 Receiptnumber0x87_3B[2u];
	uint8 CardType_Bin0x8a_2B;
	uint8 CardName_LL_Var0x8b_11B[20u];
	uint8 CardTypeID_Bin0x8c_2B;
	uint8 SID_0x1F14_32B[32u];


}zvt_extractdata_cmd_t;

typedef struct
{
	zvt_languagetype LanguageTpye0830;
	zvt_func_state_machine zvt2PtTxFuncSM;
	uint8 preAuthorizedAmount0622[6u];
	uint8 preAuthorizedRemainingMoney0623[6u];
	uint8 receiptNumber0x87_0623[2u];

}zvt_transmitdata2pt_t;

typedef struct
{
	uint8 ptTerminalID[8u];
	uint8 ptIpAddr[15u];
	uint8 ptNetmaskAddr[15u];
	uint8 ptGatewayAddr[15u];

}zvt_ptconfig_t;



typedef enum
{
	Bitmap04_AmounMinorCurrencyUnits_7B = 0x04u,
	Bitmap06_TLVContainer = 0x06u,
	Bitmap07_TextLines = 0x07u,
	Bitmap0B_TraceNumber_4B = 0x0Bu,
	Bitmap0C_TimeBCD_4B = 0x0c,
	Bitmap0D_DateBCD_3B = 0x0d,
	Bitmap0E_ExpiryDateBCD_3B = 0x0e,
	Bitmap17_CardSequenceNumberBCD_3B = 0x17,
	Bitmap19_StatusBytePaymentTypeCardType_Bin_2B = 0x19u,
	Bitmap22_LL_Var_PAN_EF_ID_BCD = 0x22,
	Bitmap23_LL_Var_Track_2_data = 0x23,
	Bitmap24_LLL_Var_Track_3_data = 0x24,
	Bitmap24_DisplayTexts = 0x24u,
	Bitmap2D_LL_Var_Track_1_data = 0x2D,
	Bitmap27_ResultCode_2B = 0x27u,
	Bitmap29_TID_5B = 0x29u,
	Bitmap2A_VU_Number_ASCII_16B = 0x2a,
	Bitmap2A_VUNumber = 0x2Au,
	Bitmap2E_LLL_Var_Synchronous_Chip_Data = 0x2E,
	Bitmap37_ReceiptNumberReversal_4B = 0x37u,
	Bitmap3C_LLL_Var_Additional_Data = 0x3Cu,
	Bitmap49_network_provider_card_type_ID_3B = 0x49u,
	Bitmap60_LLL_Var_Individual_totals = 0x60,
	Bitmap87_ReceiptNumber_3B = 0x87u,
	Bitmap8A_CardType_Bin_2B = 0x8a,
	Bitmap8B_CardName_LL_Var = 0x8b,
	Bitmap9A_GeldKarte_Payment_LLL_Var = 0x9a,				/**GeldKarte payments-/ failed-payment record/total record Geldkarte**/
	BitmapA7_Chip_Data_EF_ID_LL_Var = 0xA7,
	BitmapAF_EF_Info_LL_Var = 0xAF,
	BitmapD1_Card_Offset_PIN_Data_LL_Var = 0xD1

}zvt_bitmap;


typedef enum
{
	PrimitiveTag_UID_0x4c = 0x4c,
	PrimitiveTag_TopUpText_0x82 = 0x82


}zvt_tlvencoded_tag_t;


typedef enum
{
	PT_ready_pt_0x00 = 0x00u,
	Initialisation_required_pt_0x51 = 0x51u,
	Date_time_incorrect_pt_0x62 = 0x62u,
	Please_wait_pt_0x9C = 0x9Cu,
	Partial_issue_of_goods_pt_0x9D = 0x9Du,
	Memory_full_pt_0xB1 = 0xB1,
	Merchant_journal_full_pt_0xB2 = 0xB2,
	Voltage_supply_too_low_pt_0xBF = 0xBF,
	Card_ocking_mechanism_defect_pt_0xC0 = 0xC0,
	Merchant_card_locked_pt_0xC1 = 0xC1,
	Diagnosis_required_pt_0xC2 = 0xC2,
	Card_profile_invalid_New_card_profiles_must_be_loaded_pt_0xC4 = 0xC4,
	Printer_not_ready_pt_0xCC = 0xCC,
	Card_inserted_pt_0xDC = 0xDC,
	Out_of_order_pt_0xDC = 0xDF,
	Remote_maintenance_activated_pt_0xE0 = 0xE0,
	Card_not_completely_removed_pt_0xE1 = 0xE1,
	Card_reader_does_not_answer_card_reader_defective_pt_0xE2 = 0xE2,
	Shutter_closed_pt_0xE3 = 0xE3,
	Terminal_activation_required_pt_0xE4 = 0xE4,
	Reconciliation_required_pt_0xF0 = 0xF0,
	OPT_data_not_available_pt_0xF6 = 0xF6

}zvt_pt_err_id;


#endif /* CDD_ETHCOMM_ZVT_TYPES_H_ */
