

#include "DcmDspUds_Uds_Inf.h"

#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,DCM_VAR) Dcm_VInData_au8[DCM_VIN_DATALEN] = {0};  /*Buffer to store VIN data*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR( boolean, DCM_VAR )Dcm_VinReceived_b = FALSE; /*Flag to indicate VIN data is received successfully or not */
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 **********************************************************************************************************************
 * Dcm_GetVin :
 *  This function is called by DOIP for reading the VIN DID.
 *
 * \param           : *Data - pointer to the target buffer(17 bytes) provided by DOIP
 * \return          : Std_ReturnType
 * \retval          : E_OK - if the VIN DID is read successfully
 * 					  E_NOT_OK - if the VIN DID is not read successfully
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */

FUNC (Std_ReturnType,DCM_CODE) Dcm_GetVin (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data)
{
	VAR (uint32,AUTOMATIC) dataSessionMask_u32;   /* Variable to hold the configured sessions value */
	VAR (uint32,AUTOMATIC) dataSecurityMask_u32;  /* Variable to hold the configured security value */
	P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst; /* Pointer to extended configuration */
	VAR(Dcm_DIDIndexType_tst,AUTOMATIC) idxVinDidIndexType_st;  		/* structure for DID index */
	VAR(uint16, AUTOMATIC) idxVinDidSignal_u16;						/* Signal index for the VIN DID */
	VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8; /* Return value of Condition check API */
	VAR (Std_ReturnType,   AUTOMATIC) dataModeChkRetval_u8; /*Return value of mode rule check API*/
	VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegRespCode_u8; 	/* variable for Negative response value */
	VAR(uint8, AUTOMATIC) dataStatusReturn_u8;							/* variable to hold the return value */
	VAR (boolean,   AUTOMATIC) flgModeRetVal_b; /*Return value of mode rule check API*/
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrControlSigConfig;

	/* Initialization of the variables */
	dataNegRespCode_u8=0;
	dataStatusReturn_u8=E_OK;
	idxVinDidSignal_u16=0;
	dataCondChkRetVal_u8 = E_OK;  /* Initialize to E_OK */
	/*Initialize the flag for mode return value to TRUE*/
	flgModeRetVal_b = TRUE;
	/* Call the API to get the index of the requested VIN DID */
	dataStatusReturn_u8 = Dcm_GetIndexOfDID(DCM_CFG_VIN_DID,&idxVinDidIndexType_st);
	ptrDidConfig = &Dcm_DIDConfig[idxVinDidIndexType_st.idxIndex_u16];
	ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxVinDidSignal_u16].idxDcmDspDatainfo_u16];
	ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
	/* Check if the DID is supported in current variant */
	/*If data range of Did is a range did or not and supported in the current variant*/
	if((idxVinDidIndexType_st.dataRange_b ==FALSE) && (*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR))
	{
		if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))(DCM_CFG_VIN_DID)!=E_OK)
		{
			dataStatusReturn_u8 = E_NOT_OK;
		}
	}
#endif
	/* If the return value is E_OK */
	if(dataStatusReturn_u8 == E_OK)
	{

		adrExtendedConfig_pcst = ptrDidConfig->adrExtendedConfig_pcst;
		/* initialize the session and security masks */
		dataSessionMask_u32  = 0x0;
		dataSecurityMask_u32 = 0x0;

#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
		/* Copy the session and security levels for read configured */
		dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessRead_u32;
		dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecRead_u32;
#endif


		/* Session check */
		/* Check if the DID is allowed to be read/written in the active session and in current active configuration set*/
		if ((Dcm_DsldGetActiveSessionMask_u32 () & dataSessionMask_u32) != 0x0uL)
		{
			/*  Security level check */
			if ((Dcm_DsldGetActiveSecurityMask_u32 () & dataSecurityMask_u32) != 0x0uL)
			{
			    /*Initialize to TRUE*/
				dataModeChkRetval_u8= E_OK;

#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
				/* Call the Dcm Appl API in case to check for the VIN DID Read permissions */
				dataModeChkRetval_u8 = DcmAppl_UserDIDModeRuleService(&dataNegRespCode_u8,DCM_CFG_VIN_DID,DCM_SUPPORT_READ);
				/* Ignore the NRC if set in case the DcmAppl API returns TRUE */
				if(dataModeChkRetval_u8!= E_OK)
				{
					/*Reset the flag for mode return value to FALSE*/
					flgModeRetVal_b =FALSE;
				}
				else
				{
				    dataNegRespCode_u8 = 0;
				}
#if(DCM_CFG_DSP_MODERULEFORDIDREAD !=DCM_CFG_OFF)
				/*Check if the flag for mode return value is set to TRUE and is supported for Extended Configuration */
				if((flgModeRetVal_b!=FALSE) && (NULL_PTR != adrExtendedConfig_pcst->adrRdbiModeRuleChkFnc_pfct))
				{
					/* Mode Rule Check */
					flgModeRetVal_b = (*(adrExtendedConfig_pcst->adrRdbiModeRuleChkFnc_pfct))(&dataNegRespCode_u8);
				}
#endif
				/*Check if flag for mode return value is set to TRUE*/
				if(FALSE != flgModeRetVal_b)
				{
					/* Loop through each signal of the DID and check for ConditionRead support */
				    for(idxVinDidSignal_u16=0;((idxVinDidSignal_u16<ptrDidConfig->nrSig_u16)&&(dataNegRespCode_u8==0x0)&&(dataCondChkRetVal_u8==E_OK));idxVinDidSignal_u16++)
					{
					    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxVinDidSignal_u16].idxDcmDspDatainfo_u16];
					    ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
					    /* Check if the read function for the DID signal is available*/
						if((ptrSigConfig->adrReadFnc_cpv)!= NULL_PTR)
						{
							/* If the ConditionCheckRead function is configured */
							if(ptrControlSigConfig->adrCondChkRdFnc_cpv!= NULL_PTR)
							{
								/* Call function to check if conditions are fulfilled to read the DID */
								/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
									dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(&dataNegRespCode_u8);
							}
						}
						else
						{
							/* If the read function for the requested DID is not configured */
							dataCondChkRetVal_u8 = E_NOT_OK;
						}
					}
				}
				else
				{
					/* ModeRuleCheck failed */
					dataStatusReturn_u8 = E_NOT_OK;
				}
#endif
			}
			else
			{
				/* Reading the VIN DID is not supported in the active security level */
				dataStatusReturn_u8 = E_NOT_OK;
			}
		}
		else
		{
			/* Reading the VIN DID is not supported in the active session */
			dataStatusReturn_u8 = E_NOT_OK;
		}
		if((dataStatusReturn_u8==E_OK)&&(dataCondChkRetVal_u8==E_OK))
		{
		/* If the Conditions for reading the the VIN DID are correct and NRC is zero */
			/* Call the Dcm_ReadVinBuffer() API to read the VIN DID from VIN buffer */
			dataStatusReturn_u8=Dcm_ReadVinBuffer(Data);
			idxVinDidIndexType_st.nrNumofSignalsRead_u16=0x0;	 /*Reset the number of signals read variable to zero for E_OK and E_NOT_OK case*/
			idxVinDidIndexType_st.dataSignalLengthInfo_u32=0x0; /*Reset the number of signals length information to zero*/
			dataNegRespCode_u8=0x00;
			if(dataStatusReturn_u8 !=E_OK)
			{
				/* The DID was not read successfully */
				dataStatusReturn_u8= E_NOT_OK;
			}
		}
		else
		{
			/* If the condition check read is not through or NRC is set */
			dataStatusReturn_u8= E_NOT_OK;
		}
	}
	else
	{
		dataStatusReturn_u8= E_NOT_OK;
	}

	return dataStatusReturn_u8;
}


/**
 **********************************************************************************************************************
 * Dcm_VinBuffer_Init :
 *  This function is called by Dcm_MainFunction for reading the VIN DID data during start up .
 *  if VIN DID data is read successfully , it is stored in Dcm_VInData_au8[]
 *

 * \return          : Std_ReturnType
 * \retval          : E_OK - if the VIN DID is read successfully
 *                    E_NOT_OK - if the VIN DID is not read successfully
 *                    DCM_E_PENDING - More time is required to read the data\n
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */
FUNC(Std_ReturnType ,DCM_CODE)  Dcm_VinBuffer_Init(void){

    VAR(Std_ReturnType, AUTOMATIC) dataStatusReturn_u8 = E_NOT_OK;                           /* variable to hold the return value */
    VAR(Dcm_DIDIndexType_tst,AUTOMATIC) idxVinDidIndexType_st;                              /* structure for DID index */

    /* Call the API to get the index of the requested VIN DID */
    if (E_OK ==  Dcm_GetIndexOfDID(DCM_CFG_VIN_DID,&idxVinDidIndexType_st))
    /* Call the Dcm_GetDIDData() API to read the VIN DID */
    {
       dataStatusReturn_u8=Dcm_GetDIDData(&idxVinDidIndexType_st,&Dcm_VInData_au8[0]);
       if(dataStatusReturn_u8 == E_OK)
       {
           /*Set flag is true as VIN data is read successfully*/
           Dcm_VinReceived_b = TRUE;
       }

    }

    return dataStatusReturn_u8;
}


/**
 **********************************************************************************************************************
 * Dcm_ReadVinBuffer :
 *  This function is called by Dcm_GetVin for copying VIN DID into application buffer .
 *

 * \return          : Std_ReturnType
 * \retval          : E_OK - if the VIN DID is available
 *                    E_NOT_OK - if the VIN DID is  not available
 *
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */
FUNC(Std_ReturnType ,DCM_CODE) Dcm_ReadVinBuffer(P2VAR(uint8, AUTOMATIC, DCM_VAR) Data){

   VAR(Std_ReturnType, AUTOMATIC) dataStatusReturn_u8 = E_NOT_OK;
   VAR(uint8, AUTOMATIC) indexVinBuff = 0;
   /* Check if VIN data is available or Application buffer is available */
    if((Dcm_VinReceived_b != FALSE) && (Data != NULL_PTR))
    {

        /* Store VIN DID in application Buffer  */
       for(indexVinBuff = 0;indexVinBuff < DCM_VIN_DATALEN ;indexVinBuff++)
       {
          *(Data) = Dcm_VInData_au8[indexVinBuff];
		  Data++;
       }

       if(indexVinBuff == DCM_VIN_DATALEN)
       {
         /*17 bytes data is copied into Application buffer*/
           dataStatusReturn_u8 = E_OK;
       }
    }
    return dataStatusReturn_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif  /* ((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)) */

