
#ifndef _DCM_CFG_DSPUDS_H
#define _DCM_CFG_DSPUDS_H

/*
 ***************************************************************************************************
 *    DCM Defines generated from configuration
 ***************************************************************************************************
*/
#define DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED        DCM_CFG_ON  /* Session control service enabled */
#define DCM_CFG_DSP_ECURESET_ENABLED                        DCM_CFG_ON  /* ECU Reset service enabled */
#define DCM_CFG_DSP_SECURITYACCESS_ENABLED                  DCM_CFG_ON  /* Security Access service enabled */
#define DCM_CFG_DSP_TESTERPRESENT_ENABLED                   DCM_CFG_ON  /* Tester Present service enabled */
#define DCM_CFG_DSP_TESTERPRESENTSB_ENABLED                 DCM_CFG_OFF  /* SB Tester Present service disabled */
#define DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED               DCM_CFG_ON  /* CDTC Setting service enabled */
#define DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED      DCM_CFG_ON  /* CDI service enabled */
#define DCM_CFG_DSP_ROUTINECONTROL_ENABLED                  DCM_CFG_ON  /* Routine control service enabled */
#define DCM_CFG_DSP_IOCBI_ENABLED                           DCM_CFG_ON  /* IOCBI service is enabled */

#define RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED             DCM_CFG_OFF /* Plant mode activation Enabled or Disabled? */

#define DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED            DCM_CFG_ON  /* RDBI service is enabled */

/* WDBI Service Configurtion */
#define DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED           DCM_CFG_ON  /* WDBI service is enabled */

/* TransferData Service Configurtion */
#define DCM_CFG_DSP_TRANSFERDATA_ENABLED           DCM_CFG_OFF /* TransferData service is disabled */

/* Flag Definition for Asynchronous Server Call point handling */
/* Flag to check whether Asynchronous ServerCallPoint handling is selected for any of the DID data */

#define DCM_CFG_DSP_DATA_ASYNCHCS_ENABLED  DCM_CFG_OFF     


/* Flag to check whether Asynchronous Servercallpoint handling is selected for any of the DidControlData */ 
#define DCM_CFG_DSP_IOCBI_ASP_ENABLED       DCM_CFG_OFF  /* The signal of the DID in IOCBI Service does not have useport configured as USE_DATA_ASYNCH_CLIENT_SERVER */
/* Flag to check whether Asynchronous Servercallpoint handling is selected for any of the DidRead Data */ 
#define DCM_CFG_DSP_READ_ASP_ENABLED       DCM_CFG_OFF  /* The signal of the DID in RDBI Service does not have useport configured as USE_DATA_ASYNCH_CLIENT_SERVER */

/* Flag to check whether Asynchronous Servercallpoint handling is selected for any of the DidWrite Data */ 
#define DCM_CFG_DSP_WRITE_ASP_ENABLED       DCM_CFG_OFF  /* The signal of the DID in WDBI Service does not have useport configured as USE_DATA_ASYNCH_CLIENT_SERVER */

#define DCM_CFG_DSP_WRITE_SYNCH_FNC_ENABLED      DCM_CFG_ON  /* The signal of the DID in WDBI Service has useport configured as USE_DATA_SYNCH_FNC */
#define DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED       DCM_CFG_OFF  /* The signal of the DID in WDBI Service does not have useport configured as USE_DATA_ASYNCH_FNC */
#define DCM_CFG_DSP_WRITE_SYNCH_CS_ENABLED       DCM_CFG_OFF  /* The signal of the DID in WDBI Service does not have useport configured as USE_DATA_SYNCH_CLIENT_SERVER */
#define DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED       DCM_CFG_OFF  /* The signal of the DID in WDBI Service does not have useport configured as USE_DATA_ASYNCH_CLIENT_SERVER */
#define DCM_CFG_DSP_WRITE_SR_ENABLED       DCM_CFG_OFF  /* The signal of the DID in WDBI Service does not have useport configured as USE_DATA_SENDER_RECEIVER */
#define DCM_CFG_DSP_WRITE_FIXED_LENGTH       DCM_CFG_ON  /* The data belonging to a DID in WDBI Service is configured has Fixed length*/
#define DCM_CFG_DSP_WRITE_VARIABLE_LENGTH       DCM_CFG_OFF  /* The data belonging to a DID in WDBI Service is not configured has Variable length */
#define DCM_CFG_DSP_WRITE_BOOLEAN_SR_ENABLED       DCM_CFG_OFF  /* The data type of Data belonging to a DID is not configured as BOOLEAN */
#define DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED       DCM_CFG_OFF  /* The data type of Data belonging to a DID is not configured as UINT8 */
#define DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED       DCM_CFG_OFF  /* The data type of Data belonging to a DID is not configured as UINT16 */
#define DCM_CFG_DSP_WRITE_UINT32_SR_ENABLED       DCM_CFG_OFF  /* The data type of Data belonging to a DID is not configured as UINT32 */
#define DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED       DCM_CFG_OFF  /* The data type of Data belonging to a DID is not configured as SINT8 */
#define DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED       DCM_CFG_OFF  /* The data type of Data belonging to a DID is not configured as SINT16 */
#define DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED       DCM_CFG_OFF  /* The data type of Data belonging to a DID is not configured as SINT32 */
/* WDBI Service Configuration ends */

#define DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED     DCM_CFG_OFF /* DDDI service is disabled */
#define DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED            DCM_CFG_ON  /* CC service is enabled */
#define DCM_CFG_DSP_REQUESTUPLOAD_ENABLED                   DCM_CFG_OFF /* RequestUpload service is disabled */
#define DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED                   DCM_CFG_OFF /* RequestDownload service is disabled */
#define DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED             DCM_CFG_OFF /* RequestTransferExit service is disabled */
#define DCM_CFG_DSP_RESPONSEONEVENT_ENABLED                 DCM_CFG_OFF /* ROE service is disabled */
#define DCM_CFG_DSP_ROEEVENT_ENABLED                 DCM_CFG_OFF /* ROE Event is Configured */
#define DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED             DCM_CFG_OFF /* RMBA service is disabled */
#define DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED            DCM_CFG_OFF /* WMBA service is disabled */
#define DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED    DCM_CFG_OFF /* RDPI service is disabled */

/* RDTC Service Configuration */
#define DCM_CFG_DSP_READDTCINFORMATION_ENABLED              DCM_CFG_ON  /* RDTC Service enabled */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED                DCM_CFG_ON  /* RDTC Subfunction 0x01 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED                DCM_CFG_ON  /* RDTC Subfunction 0x02 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x03 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED                DCM_CFG_ON  /* RDTC Subfunction 0x04 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x05 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED                DCM_CFG_ON  /* RDTC Subfunction 0x06 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x07 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x08 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x09 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED                DCM_CFG_ON  /* RDTC Subfunction 0x0A Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x0B Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x0C Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x0D Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x0E Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x0F Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x10 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x11 Enabled or Disabled? */

#define DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x12 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x13 Enabled or Disabled? */

#define DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x14 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x15 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x17 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x18 Enabled or Disabled? */
#define DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED                DCM_CFG_OFF  /* RDTC Subfunction 0x19 Enabled or Disabled? */


#define DCM_CFG_NUMRDTCSUBFUNC         5u           /* Number of subfunctions configured for Read DTC Info service */
#define DCM_CFG_RDTC_MAXNUMDTCREAD     1u           /* Maximum number of DTC's that can be read at a time */
#define DCM_CFG_RDTC_MAXNUMRECREAD     1u           /* Maximum number of records that can be read at a time */

#define DCM_CFG_CANFD_ENABLED DCM_CFG_OFF

/* RDTC Service Configuration ends */
/* Clear Diagnostic Information Service configuration */
#define DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED    DCM_CFG_OFF  /* ConditionCheck for CDI service is disabled */
/* DSC Service configuration */
#define DCM_CFG_DSP_NUMSESSIONS        3u          /* Number of sessions configured in DSC service */
#define DCM_CFG_DSP_DSC_SESRECINRESP   DCM_CFG_ON  /* Session Parameter Record exists in Response */
/* DSC Service configuration ends */

/* SECA Service configuration */
/* Flag to check whether Asynhronous server point handling is selected for any of the SecurityRows */
#define DCM_CFG_DSP_SECA_ASP_ENABLED       DCM_CFG_OFF  /* Asynchronous server point handling is not selected for any of the security rows */

#define DCM_CFG_DSP_NUMSECURITY        2u          /* Number of security levels configured in SECA service */
#define DCM_CFG_DSP_USE_ASYNCH_FNC              DCM_CFG_ON  /* Security levels in the project has useport configured as USE_ASYNCH_FNC */
#define DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER    DCM_CFG_OFF /* Security levels in the project does not have useport configured as USE_ASYNCH_CLIENT_SERVER */
#ifndef DCM_SEC_LEV_L1
#define DCM_SEC_LEV_L1        0x1          /* Symbolic values for Security */
#endif
#ifndef DCM_SEC_LEV_L2
#define DCM_SEC_LEV_L2        0x2          /* Symbolic values for Security */
#endif

#define DCM_CFG_DSP_SECA_ATTEMPT_COUNTER            DCM_CFG_OFF  /*External handling of the security attempt counter is not enabled*/
#define DCM_CFG_DSP_SECA_STORESEED     DCM_CFG_OFF /* Definition to store the seed calculated for Seed Request */
#define DCM_CFG_DSP_DELAYTIMERMONITORING      DCM_PRV_REQUEST_SEED  /* DelayTimer is monitored for Seed Request */
#define DCM_CFG_DSP_NRC0x36MAXDELAYCOUNT      DCM_CFG_ON    /* Return NRC 36 in case of Failed Attempts exceeds
                                                            the configured Number Of Attempts for Delay.
                                                            NRC 36 will be returned if Lock Count is exceeded */








/* SECA Service configuration ends */

/* Ecu Reset Service configuration */
/***********DcmModeRapidPowerShutDown configuration enabled or disabled*********/
#define DCM_CFG_RAPIDPOWERSHUTDOWNRESET DCM_CFG_OFF     /* EcuReset sub function EnableRapidPowerShutDown(0x04) and  DisableRapidPowerShutDown(0x05) is configured */
#define DCM_CFG_DSP_NUMRESETTYPE    2u  /* Number of Reset Types configured */
#define DCM_CFG_DSP_POWER_DOWN_TIME  255u   /* Power Down Time before Ecu reset */
/* Ecu Reset Service configuration ends */

/* CDTCS Service configuration */
#define DCM_CFG_DSP_SUPPORTCDTCRECORD  DCM_CFG_OFF /*CDTC Control Option record is not  supported*/
/* CDTCS Service configuration ends */

/* RoutineControl Service configuration */
#define DCM_CFG_RC_NUMRIDS  1u          /* Number of Routine Identifiers Configured */

#define DCM_CFG_DSP_NUMISRIDAVAIL          0   /* Number of  Functions  configured to check if RID is available in the current variant */

#define DCM_CFG_DSP_MODERULEFORROUTINES       DCM_CFG_OFF  /* Mode rules are not referred for Routines */
/* RoutineControl Service configuration ends */

/* RDBI/WDBI/IOCBI/DDDI Service configuration */
#define DCM_CFG_DSP_NVRAM_ENABLED                           DCM_CFG_OFF /* DID with NVRAM read and write block Enabled or Disabled?*/

#define DCM_CFG_DSP_NUMISDIDAVAIL                         0u /* Number of function configured to check if DID is available in the current variant */

/* RDBI USE DATA PORT CONFIGURATION */
#define DCM_CFG_DSP_READ_SYNCH_FNC_ENABLED                           DCM_CFG_ON  /* DID with signals of use port type USE_DATA_SYNCH_FNC or USE_DATA_SYNCH_CLIENT_SERVER is Enabled or Disabled?*/

#define DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_ADATA_SYNCH_FNC or USE_DATA_ASYNCH_CLIENT_SERVER is Enabled or Disabled?*/

#define DCM_CFG_DSP_READ_SR_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_DATA_SENDER_RECEIVER is Enabled or Disabled?*/


#define DCM_CFG_DSP_READ_BOOLEAN_SR_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_DATA_SENDER_RECEIVER with boolean data type is Enabled or Disabled?*/

#define DCM_CFG_DSP_READ_UINT8_SR_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_DATA_SENDER_RECEIVER with UINT8 data type is Enabled or Disabled?*/

#define DCM_CFG_DSP_READ_SINT8_SR_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_DATA_SENDER_RECEIVER with SINT8 data type is Enabled or Disabled?*/

#define DCM_CFG_DSP_READ_UINT16_SR_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_DATA_SENDER_RECEIVER with UINT16 data type is Enabled or Disabled?*/

#define DCM_CFG_DSP_READ_SINT16_SR_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_DATA_SENDER_RECEIVER with SINT16 data type is Enabled or Disabled?*/

#define DCM_CFG_DSP_READ_UINT32_SR_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_DATA_SENDER_RECEIVER with UINT32 data type is Enabled or Disabled?*/

#define DCM_CFG_DSP_READ_SINT32_SR_ENABLED                           DCM_CFG_OFF /* DID with signals of use port type USE_DATA_SENDER_RECEIVER with SINT32 data type is Enabled or Disabled?*/


#define DCM_CFG_DSP_READ_VARIABLE_LENGTH       DCM_CFG_OFF  /* The data belonging to a DID in RDBI Service is not configured has Variable length */

#define DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH       DCM_CFG_OFF  /* The data belonging to a DID in IOCTRL Service is not configured has Variable length */

#define DCM_CFG_DSP_WRITE_FIXED_LENGTH       DCM_CFG_ON  /* The data belonging to a DID in WDBI Service is configured has Fixed length*/
#define DCM_CFG_DSP_WRITE_VARIABLE_LENGTH       DCM_CFG_OFF  /* The data belonging to a DID in WDBI Service is not configured has Variable length */

#define DCM_CFG_DSP_MODERULEFORDIDREAD       DCM_CFG_OFF  /* Mode rules are referred for DID Read */
#define DCM_CFG_DSP_MODERULEFORDIDWRITE      DCM_CFG_OFF  /* Mode rules are referred for DID Write */
#define DCM_CFG_DSP_MODERULEFORDIDCONTROL    DCM_CFG_OFF  /* Mode rules are referred for DID Control */
#define DCM_CFG_MAXDIDTOREAD           0           /* Max number of DID allowed to be requested in one request */
#define DCM_CFG_READDATALENGTH_BITS    DCM_CFG_OFF    /* DataLength returned by ReadDataLength operation is in bytes */
#define DCM_CFG_DSP_DIDBUFFER         DCM_RAM_BUFFER   /* Buffer used for storage of data while reading DDDI records */
/***********Macro to indicate whether DcmDspDidRange is configured or not*********/

#define DCM_CFG_DIDRANGE_EXTENSION  DCM_CFG_OFF
#define DCM_CFG_NUMOFDIDRANGES 0x0

/***********Macro to indicate whether DcmDspDid is configured or not*********/
#define DCM_CFG_DIDSUPPORT DCM_CFG_ON
/***********Macro to indicate whether ROE DID is configured or not*********/
#define DCM_CFG_DSP_ROEDID_ENABLED       DCM_CFG_OFF
/***********Macro to indicate whether DcmDspRoeOnDTCStatusChange is configured or not*********/
#define DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED       DCM_CFG_OFF
/***********A parameter which indicates the number of IOCBI DIDs configured*********/
#define DCM_CFG_NUM_IOCBI_DIDS          0xBu
/***********Control parameters enabled for IOCBI DIDs configured*********/
#define DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED    DCM_CFG_ON
#define DCM_CFG_DSP_RESETTODEFAULT_ENABLED        DCM_CFG_ON
#define DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED   DCM_CFG_ON
#define DCM_CFG_DSP_IOCBI_SR_ENABLED   DCM_CFG_OFF
#define DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED    DCM_CFG_OFF

/***********DataInterface Type (DataUseports) configured for IOCBI DIDs*********/
#define DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED     DCM_CFG_ON
#define DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED    DCM_CFG_OFF
/***********Whether at least one fixed length signal/variable legth signal is configured for IOCBI DIDs*********/
#define DCM_CFG_DSP_CONTROL_FIXED_LEN_ENABLED    DCM_CFG_ON
#define DCM_CFG_DSP_CONTROL_VAR_LEN_ENABLED    DCM_CFG_OFF


/***********Macro to indicate if the RDBI cut postive response feature is enabled or not*********/
#define DCM_CFG_LIMITRDBIRESPTOBUFSIZE      DCM_CFG_OFF


/***********Macro to indicate if the page buffer support for RDBI sevice is enabled or not*********/
#define DCM_CFG_RDBIPAGEDBUFFERSUPPORT      DCM_CFG_OFF     /* Paged buffer support for RDBI service is disabled */

/***********Macro to indicate  the maximum number of ROE dids configured*********/




/***********Macro to indicate if the page buffer support for RDTC sevice is enabled or not*********/
#define DCM_CFG_RDTCPAGEDBUFFERSUPPORT      DCM_CFG_OFF     /* Paged buffer support for RDTC service is disabled */

/***********Buffer size to create a copy of the request buffer to store all the requested(only accepted) DIDs in the buffer*********/
#define DCM_CFG_RDBIREQUESTBUFFERSIZE       1024u
/***********ISO Version used by the projects, this macro is only relevant to RDPI service*********/
/***********ISO Version used by the projects, this macro is only relevant to RDPI service*********/

/* RDBI/WDBI/IOCBI/DDDI Service configuration ends */

/* RMBA/WMBA Service configuration */
#define DCM_CFG_DSP_MODERULEFORREADMEMORY       DCM_CFG_OFF  /* Mode rules are not referred for Memory configured for Read */
#define DCM_CFG_DSP_MODERULEFORWRITEMEMORY       DCM_CFG_OFF  /* Mode rules are not referred for Memory configured for Write */
/* RMBA/WMBA Service configuration ends */

/* RequestUpload Service configuration starts */

/* RequestDownload Service configuration starts */


/* RequestDownload/RequestUpload Service configuration starts */


/* Communication Control - Start */
#define DCM_CFG_NUM_SPECIFIC_SUBNETS                    1        /*Number of special subnet IDs configured*/

#define DCM_CFG_NUM_ALLCHANNELS_MODE_INFO                   1     /*Number of channels  configured for Dcm*/

#define DCM_CFG_DSP_MODERULEFORCC                   DCM_CFG_OFF   /* Mode rule re-enable check valid/configured for Communication Control */

#define DCM_CFG_DSP_BSWMDCM_ENABLED    DCM_CFG_ON     /* In the BswM module check if Dcm is enabled */
/* Communication Control - End */

/* Control DTC Setting Service Configuration Start */



#define DCM_CFG_DSP_CDTCMODECHECK       DCM_CFG_OFF /* Disable re-enabling of cdtc by mode rule check*/



/* Control DTC Setting Service Configuration End */

/* VIN DID configuration start */
#define DCM_CFG_VIN_SUPPORTED                           DCM_CFG_OFF  /* reading the VIN DID is not supported */
/* VIN DID configuration end */
/*Routine Control Subfunctions - Start */
#define DCM_CFG_STARTSUPPORTED                         DCM_CFG_ON       /*If start is configured for RID*/

#define DCM_CFG_STOPSUPPORTED                         DCM_CFG_ON        /* If stop is configured for RID */

#define DCM_CFG_REQRESULTSSUPPORTED                         DCM_CFG_ON          /* If requestResults is configured for RID */

#define DCM_CFG_ROUTINEVARLENGTH                         DCM_CFG_OFF            /*If atleast one fixed length signal is configured */

#define DCM_CFG_ROUTINEARRAY_INSIG                   DCM_CFG_OFF         /* If Array Data type is not configured for any of the IN Signals */

#define DCM_CFG_ROUTINEARRAY_OUTSIG                   DCM_CFG_OFF         /* If Array Data type is not configured for any of the OUT Signals */

/*Routine Control Subfunctions - End */


/* Mapping old macros to coding guideline compliant macros to ensure backward compatibility */
            /* Obsolete */
#ifndef     DCM_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED
#define     DCM_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED    DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED
#endif
#ifndef     DCM_DSP_ECURESET_ENABLED
#define     DCM_DSP_ECURESET_ENABLED                    DCM_CFG_DSP_ECURESET_ENABLED
#endif
#ifndef     DCM_DSP_SECURITYACCESS_ENABLED
#define     DCM_DSP_SECURITYACCESS_ENABLED              DCM_CFG_DSP_SECURITYACCESS_ENABLED
#endif
#ifndef     DCM_DSP_TESTERPRESENT_ENABLED
#define     DCM_DSP_TESTERPRESENT_ENABLED               DCM_CFG_DSP_TESTERPRESENT_ENABLED
#endif
#ifndef     DCM_DSP_TESTERPRESENTSB_ENABLED
#define     DCM_DSP_TESTERPRESENTSB_ENABLED             DCM_CFG_DSP_TESTERPRESENTSB_ENABLED
#endif
#ifndef     DCM_DSP_CONTROLDTCSETTING_ENABLED
#define     DCM_DSP_CONTROLDTCSETTING_ENABLED           DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED
#endif
#ifndef     DCM_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED
#define     DCM_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED  DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED
#endif
#ifndef     DCM_DSP_ROUTINECONTROL_ENABLED
#define     DCM_DSP_ROUTINECONTROL_ENABLED              DCM_CFG_DSP_ROUTINECONTROL_ENABLED
#endif
#ifndef     DCM_DSP_IOCBI_ENABLED
#define     DCM_DSP_IOCBI_ENABLED                       DCM_CFG_DSP_IOCBI_ENABLED
#endif
#ifndef     DCM_DSP_READDATABYIDENTIFIER_ENABLED
#define     DCM_DSP_READDATABYIDENTIFIER_ENABLED        DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED
#endif
#ifndef     DCM_DSP_WRITEDATABYIDENTIFIER_ENABLED
#define     DCM_DSP_WRITEDATABYIDENTIFIER_ENABLED       DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED
#endif
#ifndef     DCM_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED
#define     DCM_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED   DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED
#endif
#ifndef     DCM_DSP_COMMUNICATIONCONTROL_ENABLED
#define     DCM_DSP_COMMUNICATIONCONTROL_ENABLED        DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED
#endif
#ifndef     DCM_DSP_RESPONSEONEVENT_ENABLED
#define     DCM_DSP_RESPONSEONEVENT_ENABLED             DCM_CFG_DSP_RESPONSEONEVENT_ENABLED
#endif
#ifndef     DCM_DSP_READMEMORYBYADDRESS_ENABLED
#define     DCM_DSP_READMEMORYBYADDRESS_ENABLED         DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED
#endif
#ifndef     DCM_DSP_WRITEMEMORYBYADDRESS_ENABLED
#define     DCM_DSP_WRITEMEMORYBYADDRESS_ENABLED        DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED
#endif
#ifndef     DCM_DSP_READDATABYPERIODICIDENTIFIER_ENABLED
#define     DCM_DSP_READDATABYPERIODICIDENTIFIER_ENABLED  DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED
#endif
#ifndef     DCM_DSP_READDTCINFORMATION_ENABLED
#define     DCM_DSP_READDTCINFORMATION_ENABLED          DCM_CFG_DSP_READDTCINFORMATION_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x01_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x01_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x02_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x02_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x03_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x03_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x04_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x04_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x06_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x06_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x07_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x07_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x08_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x08_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x09_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x09_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x0A_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x0A_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x0F_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x0F_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x10_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x10_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x11_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x11_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x12_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x12_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x13_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x13_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x14_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x14_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x15_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x15_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x17_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x17_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x18_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x18_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED
#endif
#ifndef     DCM_DSP_RDTCSUBFUNC_0x19_ENABLED
#define     DCM_DSP_RDTCSUBFUNC_0x19_ENABLED            DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED
#endif
#ifndef     DCM_NUMRDTCSUBFUNC
#define     DCM_NUMRDTCSUBFUNC                          DCM_CFG_NUMRDTCSUBFUNC
#endif
#ifndef     DCM_RDTC_MAXNUMDTCREAD
#define     DCM_RDTC_MAXNUMDTCREAD                      DCM_CFG_RDTC_MAXNUMDTCREAD
#endif
#ifndef     DCM_RDTC_MAXNUMRECREAD
#define     DCM_RDTC_MAXNUMRECREAD                      DCM_CFG_RDTC_MAXNUMRECREAD
#endif
#ifndef     DCM_DSP_NUMSESSIONS
#define     DCM_DSP_NUMSESSIONS                         DCM_CFG_DSP_NUMSESSIONS
#endif
#ifndef     DCM_DSP_DSC_SESRECINRESP
#define     DCM_DSP_DSC_SESRECINRESP                    DCM_CFG_DSP_DSC_SESRECINRESP
#endif
#ifndef     DCM_DSP_NUMSECURITY
#define     DCM_DSP_NUMSECURITY                         DCM_CFG_DSP_NUMSECURITY
#endif
#ifndef     DCM_SECA_MAXSEEDSIZE
#define     DCM_SECA_MAXSEEDSIZE                        DCM_CFG_SECA_MAXSEEDSIZE
#endif
#ifndef     DCM_DSP_SECA_STORESEED
#define     DCM_DSP_SECA_STORESEED                      DCM_CFG_DSP_SECA_STORESEED
#endif
#ifndef     DCM_DSP_DELAYTIMERMONITORING
#define     DCM_DSP_DELAYTIMERMONITORING                DCM_CFG_DSP_DELAYTIMERMONITORING
#endif
#ifndef     DCM_DSP_NRC0x36_MAXDELAYCOUNT
#define     DCM_DSP_NRC0x36_MAXDELAYCOUNT               DCM_CFG_DSP_NRC0x36MAXDELAYCOUNT
#endif
#ifndef     DCM_DSP_NUMRESETTYPE
#define     DCM_DSP_NUMRESETTYPE                        DCM_CFG_DSP_NUMRESETTYPE
#endif
#ifndef     DCM_DSP_POWER_DOWN_TIME
#define     DCM_DSP_POWER_DOWN_TIME                     DCM_CFG_DSP_POWER_DOWN_TIME
#endif
#ifndef     DCM_DSP_CDTCRECORD_LENGTH
#define     DCM_DSP_CDTCRECORD_LENGTH                   DCM_CFG_DSP_CDTCRECORDLENGTH
#endif
#ifndef     DCM_RC_NUM_RIDS
#define     DCM_RC_NUM_RIDS                             DCM_CFG_RC_NUMRIDS
#endif
#ifndef     DCM_DSP_NVRAM_ENABLED
#define     DCM_DSP_NVRAM_ENABLED                       DCM_CFG_DSP_NVRAM_ENABLED
#endif
#ifndef     DCM_MAXDIDTOREAD
#define     DCM_MAXDIDTOREAD                            DCM_CFG_MAXDIDTOREAD
#endif
#ifndef     DCM_LONGEST_SINGLE_DID
#define     DCM_LONGEST_SINGLE_DID                      DCM_CFG_LONGESTSINGLEDID
#endif
#ifndef     DCM_DSP_DID_BUFFER
#define     DCM_DSP_DID_BUFFER                          DCM_CFG_DSP_DIDBUFFER
#endif
#ifndef     DID_RANGE_EXTENSION
#define     DID_RANGE_EXTENSION                         DCM_CFG_DIDRANGE_EXTENSION
#endif
#ifndef     DCM_NO_OF_DIDRANGES
#define     DCM_NO_OF_DIDRANGES                         DCM_CFG_NUMOFDIDRANGES
#endif
#ifndef     DID_SUPPORT
#define     DID_SUPPORT                                 DCM_CFG_DIDSUPPORT
#endif
#ifndef     DCM_ROE_WINTIMEINREPEVENTSREQ
#define     DCM_ROE_WINTIMEINREPEVENTSREQ               DCM_CFG_ROE_WINTIMEINREPEVENTSREQ
#endif
#ifndef     DCM_NUM_SPECIFIC_SUBNETS
#define     DCM_NUM_SPECIFIC_SUBNETS                    DCM_CFG_NUM_SPECIFIC_SUBNETS
#endif
#ifndef     DCM_NUM_ALLCHANNELS_MODE_INFO
#define     DCM_NUM_ALLCHANNELS_MODE_INFO               DCM_CFG_NUM_ALLCHANNELS_MODE_INFO
#endif
#ifndef     DCM_DSP_CDTC_MODE_CHECK
#define     DCM_DSP_CDTC_MODE_CHECK                     DCM_CFG_DSP_CDTCMODECHECK
#endif



#endif /* _DCM_CFG_DSPUDS_H */

