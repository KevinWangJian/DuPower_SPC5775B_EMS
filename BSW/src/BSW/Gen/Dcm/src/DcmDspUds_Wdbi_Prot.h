

#ifndef DCMDSPUDS_WDBI_PROT_H
#define DCMDSPUDS_WDBI_PROT_H


/**
 ***************************************************************************************************
            Write Data By Identifier (WDBI) service
 ***************************************************************************************************
 */

#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)


/* Type definitions for the WDBI functions */

/* When UsePort is configured TRUE i.e. RTE is enabled */
typedef   P2FUNC(Std_ReturnType,TYPEDEF,WriteFncRange1_pfct)( VAR(uint16,AUTOMATIC) DID,
		  P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
		  VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
		  VAR(uint16,AUTOMATIC) DataLength,
		  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
		);

/* When UsePort is configured FALSE i.e. RTE is disabled */
typedef   P2FUNC(Std_ReturnType,TYPEDEF,WriteFncRange2_pfct)( VAR(uint16,AUTOMATIC) DID,
        P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
		  VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
		  VAR(uint16,AUTOMATIC) DataLength,
		  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
		);
/* When UsePort is USE_DATA_SYNC_CLIENT_SERVER and Data Length is variable */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc1_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    VAR(uint16,AUTOMATIC) DataLength,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_SYNC_CLIENT_SERVER and Data Length is fixed */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc2_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_SYNC_FNC and Data Length is variable */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc18_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    VAR(uint16,AUTOMATIC) DataLength,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_SYNCH_FNC  and Data Length is fixed */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc19_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_ASYNC_FNC and Data Length is variable */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc3_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    VAR(uint16,AUTOMATIC) DataLength,
                                    VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_ASYNC_FNC and Data Length is fixed */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc4_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_ASYNC_CLIENT_SERVER and Data Length is variable */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc20_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    VAR(uint16,AUTOMATIC) DataLength,
                                    VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_ASYNC_CLIENT_SERVER and Data Length is fixed */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc21_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When Asynchronous Server Call Point handling is requested */
#if(DCM_CFG_DSP_WRITE_ASP_ENABLED != DCM_CFG_OFF)

/* When Data Length is variable */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc22_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
/* When  Data Length is fixed */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc23_pfct)
                                   (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                    VAR(uint16,AUTOMATIC) DataLength,
                                    VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);

typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc24_pfct)
                                   (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

/* When UsePort is USE_SENDER_RECEIVER */
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc5_pfct) (VAR(boolean,AUTOMATIC) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc6_pfct) (VAR(uint8,  AUTOMATIC) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc7_pfct) (VAR(uint16, AUTOMATIC) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc8_pfct) (VAR(uint32, AUTOMATIC) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc9_pfct) (VAR(sint8,  AUTOMATIC) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc10_pfct)(VAR(sint16, AUTOMATIC) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc11_pfct)(VAR(sint32, AUTOMATIC) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc12_pfct)(P2CONST(uint8, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc13_pfct)(P2CONST(uint16,AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc14_pfct)(P2CONST(uint32,AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc15_pfct)(P2CONST(sint8, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc16_pfct)(P2CONST(sint16,AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,WdbiFnc17_pfct)(P2CONST(sint32,AUTOMATIC,DCM_INTERN_DATA) Data);


#endif
#endif   /* _DCMDSPUDS_WDBI_PROT_H */

