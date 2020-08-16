

#include "Dcm.h"

#include "DcmDspUds_Uds_Prot.h"

#include "ComM_Dcm.h"

#include "DcmDspUds_Rc_Prot.h"


#include "DcmDspUds_Rdtc_Priv.h"

#include "DcmDspUds_Er_Prot.h"



#include "DcmDspUds_Cdtcs_Prot.h"



#include "DcmAppl.h"




/**
 ***************************************************************************************************
            Session Control (DSC) Service
 ***************************************************************************************************
*/
/* Initialization of the parameters for the supported sessions */
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
CONST(Dcm_Dsp_Session_t, DCM_CONST) Dcm_Dsp_Session[DCM_CFG_DSP_NUMSESSIONS] =
{

   /* session configuration for DEFAULT_SESSION*/
   {
		50000,				/* P2 Max time in us */
		2000000,				/* P2* Max time in us */
		0x1,				/* Session ID */
		RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION, /* DcmDiagnosticSessionControl Mode  for the Session Level */
		DCM_NO_BOOT			/* Diagnostic session used for jump to Bootloader */
	},

   /* session configuration for PROGRAMMING_SESSION*/
   {
		50000,				/* P2 Max time in us */
		2000000,				/* P2* Max time in us */
		0x2,				/* Session ID */
		RTE_MODE_DcmDiagnosticSessionControl_PROGRAMMING_SESSION, /* DcmDiagnosticSessionControl Mode  for the Session Level */
		DCM_OEM_BOOT			/* Diagnostic session used for jump to Bootloader */
	},

   /* session configuration for EXTENDED_DIAGNOSTIC_SESSION*/
   {
		50000,				/* P2 Max time in us */
		2000000,				/* P2* Max time in us */
		0x3,				/* Session ID */
		RTE_MODE_DcmDiagnosticSessionControl_EXTENDED_DIAGNOSTIC_SESSION, /* DcmDiagnosticSessionControl Mode  for the Session Level */
		DCM_NO_BOOT			/* Diagnostic session used for jump to Bootloader */
	}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"



/**
 ***************************************************************************************************
            Security Access (SECA) Service
 ***************************************************************************************************
*/
/* Initialization of the parameters for the supported security */
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
CONST(Dcm_Dsp_Security_t, DCM_CONST) Dcm_Dsp_Security[DCM_CFG_DSP_NUMSECURITY] =
{
   /* security configuration for DCM_SEC_LEV_L1*/
   {
   
        0x00u,          /* Delay timer on Power On in DcmTaskTime Counts*/   

		1000,			/* Delay time after failed security access in DcmTaskTime Counts */

		/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
		(void*)	&DCM_SEC_LEV_L1_GetSeed, /* Function for the GetSeed Function */
		/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
		(void*)	&DCM_SEC_LEV_L1_CompareKey, /* Function for the Compare Key Function */
		0x1, 		/* Security Level */
		4,			/* Security Seed size */
		4,			/* Security Key size */
		3,			/* Number of failed security access after which delay time is active */
		0,			/* Number of failed security access after which security is locked */
		0,			/* Size of the Access Data Record in Seed Request */
		USE_ASYNCH_FNC			}
,
   /* security configuration for DCM_SEC_LEV_L2*/
   {
   
        0x00u,          /* Delay timer on Power On in DcmTaskTime Counts*/   

		1000,			/* Delay time after failed security access in DcmTaskTime Counts */

		/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
		(void*)	&DCM_SEC_LEV_L2_GetSeed, /* Function for the GetSeed Function */
		/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
		(void*)	&DCM_SEC_LEV_L2_CompareKey, /* Function for the Compare Key Function */
		0x2, 		/* Security Level */
		4,			/* Security Seed size */
		4,			/* Security Key size */
		3,			/* Number of failed security access after which delay time is active */
		0,			/* Number of failed security access after which security is locked */
		0,			/* Size of the Access Data Record in Seed Request */
		USE_ASYNCH_FNC			}

};
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"















/**
 ***************************************************************************************************
            Routine control (RC) service - start
 ***************************************************************************************************
 */

#if (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)




#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(sint16,DCM_VAR)              Dcm_RCSigOutN_as16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"




#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(sint32,DCM_VAR)              Dcm_RCSigOutN_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"



#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(sint8,DCM_VAR)               Dcm_RCSigOutN_as8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"




#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint32,DCM_VAR)              Dcm_RCSigOutN_au32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint16,DCM_VAR)              Dcm_RCSigOutN_au16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


typedef enum
{
    DcmDspRoutine_4AF0_DcmDspStartRoutineOutSignal_StrtOut,
    DCM_RC_SIGOUTUINT8MAX
} Dcm_DspRoutineSigOutUInt8Idx_ten;

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint8,DCM_VAR)               Dcm_RCSigOut_au8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,DCM_VAR)               Dcm_RCSigOutN_au8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"






#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(sint16,DCM_VAR)              Dcm_RCSigInN_as16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"



#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(sint32,DCM_VAR)              Dcm_RCSigInN_as32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(sint8,DCM_VAR)               Dcm_RCSigInN_as8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_VAR_CLEARED_32/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint32,DCM_VAR)              Dcm_RCSigInN_au32[1];
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint16,DCM_VAR)              Dcm_RCSigInN_au16[1];
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


typedef enum
{
    DcmDspRoutine_4AF0_DcmDspStartRoutineInSignal_StrtIn,
    DCM_RC_SIGINUINT8MAX
} Dcm_DspRoutineSigInUInt8Idx_ten;

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint8,DCM_VAR)               Dcm_RCSigIn_au8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,DCM_VAR)               Dcm_RCSigInN_au8[1];
#define DCM_STOP_SEC_VAR_CLEARED_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

FUNC(uint32,DCM_CODE) Dcm_RCGetSigVal_u32 ( VAR(uint8,AUTOMATIC) dataSigType_en, VAR(uint16,AUTOMATIC) idxSignalIndex_u16 )
{
    VAR(uint32,AUTOMATIC)       dataSigVal_u32;

    dataSigVal_u32 = 0;
   
    switch (dataSigType_en)
    {
    case DCM_UINT8:
        dataSigVal_u32 = (uint32)Dcm_RCSigOut_au8[idxSignalIndex_u16];
        break;
/*MR12 RULE 16.6 VIOLATION: This 'switch' statement contains only a single path - it is redundant. MISRA C:2012 Rule-16.6*/
    default:
        (void)idxSignalIndex_u16;
        break;
    }
    return (dataSigVal_u32);
}


FUNC(void,DCM_CODE) Dcm_RCSetSigVal ( VAR(uint8,AUTOMATIC) dataSigType_en, VAR(uint16,AUTOMATIC) idxSignalIndex_u16, VAR(uint32,AUTOMATIC) dataSigVal_u32)
{

    switch (dataSigType_en)
    {
    case DCM_UINT8:
        Dcm_RCSigIn_au8[idxSignalIndex_u16]=(uint8)dataSigVal_u32;
        break;
/*MR12 RULE 16.6 VIOLATION: This 'switch' statement contains only a single path - it is redundant. MISRA C:2012 Rule-16.6*/
    default:
        (void)dataSigVal_u32;
        (void)idxSignalIndex_u16;
        break;
    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST) DcmDspRc_DcmDspRoutine_4AF0_StrtInSig[]=
{
     {
        0,            /* Start bit position of the signal */
        8,               /* length of the signal */
        DcmDspRoutine_4AF0_DcmDspStartRoutineInSignal_StrtIn,            /* Index of the signal */
        DCM_BIG_ENDIAN,       /* Signal Endianness is BIG_ENDIAN*/
        DCM_UINT8  /* Data Type is UINT8 */             
    }
};



static CONST(Dcm_DspRoutineSignalInfo_tst, DCM_CONST) DcmDspRc_DcmDspRoutine_4AF0_StrtOutSig[]=
{
   {
        0,             /* Start bit position of the signal */
        8,               /* length of the signal */
	    DcmDspRoutine_4AF0_DcmDspStartRoutineOutSignal_StrtOut,           /* Index of the signal */
	    DCM_BIG_ENDIAN,       /* Signal Endianness is BIG_ENDIAN*/
	   DCM_UINT8  /* Data Type is UINT8 */      
    }
};






static CONST(Dcm_DspRoutineInfoType_tst, DCM_CONST) DcmDspRc_DcmDspRoutine_4AF0=
{
    /* Allowed Security Row Bit Mask for start routine*/
  0xFFFF,
  /* Allowed Security Row Bit Mask Stop Routine */
  0xFFFF,
  /* Allowed Security Row Bit Mask  Request Routine Results*/
  0xFFFF,

    /* Allowed Session Row Bit Mask for start routine */
  0xFFFF,
   /* Allowed Session Row Bit Mask  for stop routine */
  0xFFFF,
   /* Allowed Session Row Bit Mask request routine results */
  0xFFFF,
     NULL_PTR,       /*  No User defined Mode rule Function configured  */
    /* Reference to In Signal from StartRoutine */
    DcmDspRc_DcmDspRoutine_4AF0_StrtInSig,
    /* Reference to In Signal from StopRoutine */
    NULL_PTR,
/* Reference to In Signal from RequestResultRoutine */
    NULL_PTR,
    /* Reference to Out Signal from StartRoutine */
    DcmDspRc_DcmDspRoutine_4AF0_StrtOutSig,
    /* Reference to Out Signal from StopRoutine */
    NULL_PTR,
    /* Reference to Out Signal from RequestResultsRoutine */
    NULL_PTR,
    /* (Maximum) Size of Control Option Record i.e. Optional Bytes in Request for Start Routine */
    1,
    /* (Maximum) Size of Control Option Record i.e. Optional Bytes in Request for Stop Routine */
    0,
/* (Maximum) Size of Control Option Record i.e. Optional Bytes in Request for RequestResults Routine */
    0,
    /* (Maximum) Size of Status Option Record i.e. Optional Bytes in Response for Request Start Routine */
    1,
    /* (Maximum) Size of Status Option Record i.e. Optional Bytes in Response for Request Stop Routine */
    0,
    /* (Maximum) Size of Status Option Record i.e. Optional Bytes in Response for RequestResults Routine */
    0,
    /* Minimum Size of Control Option Record i.e. Optional Bytes in Request for Start Routine */
    1,

    /* Minimum Size of Control Option Record i.e. Optional Bytes in Request for Stop Routine */
    0,
    /* Minimum Size of Control Option Record i.e. Optional Bytes in Request for RequestResult Routine */
    0,
    /* Minimum Size of Status Option Record i.e. Optional Bytes in Response for Request Start Routine */
    1,
    /* Minimum Size of Status Option Record i.e. Optional Bytes in Response for Request Stop Routine */
    0,
    /* Minimum Size of Status Option Record i.e. Optional Bytes in Response for Request RequestResults Routine */
    0,
    /* Number of In Signals configured for StartRoutine */
    1,
    /* Number of In Signals configured for StopRoutine */
    0,
/* Number of In Signals configured for ReqResultsRoutine */
    0,
    /* Number of Out Signals configured for StartRoutine */
    1,
    /* Number of Out Signals configured for StopRoutine */
    0,
    /* Number of Out Signals configured for RequestResultsRoutine */
    0
};


#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_RC_DcmDspRoutine_4AF0_Func ( VAR(uint8, AUTOMATIC) dataSubFunc_u8 )
{
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    dataRetVal_u8 = E_NOT_OK;

    switch (dataSubFunc_u8)
    {
    case 1u:
        dataRetVal_u8 = DcmDspStartRoutine_4AF0
                (
Dcm_RCSigIn_au8[DcmDspRoutine_4AF0_DcmDspStartRoutineInSignal_StrtIn],
                    Dcm_RCOpStatus_u8,
                    &(Dcm_RCSigOut_au8[DcmDspRoutine_4AF0_DcmDspStartRoutineOutSignal_StrtOut]),
                    &(Dcm_RCNegResCode_u8)
                  );

        break;



    default:
        Dcm_RCNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        break;
    }

    return (dataRetVal_u8);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/* Array with function pointers configured for RIDs to check if they are supported in the current variant */

CONST(Dcm_DspRoutineType_tst, DCM_CONST) Dcm_DspRoutine_cast[DCM_CFG_RC_NUMRIDS]=
{

    /* DcmDspRoutine_4AF0 */
    {
        0x4af0,        /* Routine Identifier */
        TRUE,      /* Fixed length */
        FALSE,      /* UsePort is set to FALSE, call will be to Configured call-back */
        &DcmDspRc_DcmDspRoutine_4AF0,      /* Reference to Routine Info */
        &Dcm_Dsp_RC_DcmDspRoutine_4AF0_Func,        /* Reference to Call-out function */

        TRUE,       /* Is Start Routine supported ? */

        FALSE,      /* Is Stop Routine supported ? */
        FALSE,       /* Stop this routine if active on Session change */
        TRUE,       /* Is RequestSequnceError supported for RequestResults subfunction for Routine which is not started ? */
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),      /*Configuration mask indicating the availability of routine in different DCMConfigsets*/
#endif
        FALSE,      /* Is Request Results Routine supported ? */
    }
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Array for storing current status of each RID*/
VAR(Dcm_DspRoutineStatusType_ten, DCM_VAR) Dcm_RoutineStatus_aen[DCM_CFG_RC_NUMRIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

/**
 ***************************************************************************************************
            Routine control (RC) service - end
 ***************************************************************************************************
 */












 

 

/*Handling of  Sender receiver supported IOCBI DIDs*/
 








/**
 **********************************************************************************************************************
           DID Signal Substructure Configuration for IOCBI
 **********************************************************************************************************************
**/
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
CONST(Dcm_SignalDIDIocbiConfig_tst, DCM_CONST) Dcm_DspIOControlInfo[12]=
{
    {
            NULL_PTR,
            NULL_PTR,
            NULL_PTR,
            NULL_PTR    
    },
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_0101_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_0101_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_0101_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_0101_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D107_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D107_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D107_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D107_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D108_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D108_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D108_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D108_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D109_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D109_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D109_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D109_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D111_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D111_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D111_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D111_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D113_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D113_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D113_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D113_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D115_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D115_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D115_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D115_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D116_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D116_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D116_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D116_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D121_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D121_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D121_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D121_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D122_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D122_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D122_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D122_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
, 
    {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D123_ReturnControlToEcu_Fnc,            /* Return Control To Ecu Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D123_ResetToDefault_Fnc,         /* Reset To Default Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void*)&DcmDspData_D123_FreezeCurrentState_Fnc,            /* Freeze Current State Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
             (void*)&DcmDspData_D123_ShortTermAdjustment_Fnc            /* Short Term Adjustment Function */
                
    }
};
  
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **********************************************************************************************************************
           DID Signal Substructure Configuration for condition check for read and write and read datalength function
 **********************************************************************************************************************
**/
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
CONST(Dcm_SignalDIDSubStructConfig_tst, DCM_CONST) Dcm_DspDid_ControlInfo_st[34]=
{
    {
        NULL_PTR,
        NULL_PTR
,
        NULL_PTR
          
,
        0
    },



    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                1    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C001,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C002,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C003,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C004,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C005,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C006,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C007,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C008,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C009,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C010,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C011,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_C012,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                2    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                3    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                4    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                5    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                6    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                7    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                8    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                9    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                10    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            NULL_PTR,           /* Write Data Function */
                11    /*Index to DcmDspControlInfoStructure*/   /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F187,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F18B,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F18C,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F190,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F191,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F1A2,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F1A3,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F1A4,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F1A5,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }
, 
    {

            NULL_PTR,          /* Condition Check Read Function */
            NULL_PTR,          /* Read Data Length Function */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	    (void*)&DcmDspDataWriteFnc_F1A6,         /* Write Data Function */
            0                                                /*IOCBI Sub structure address*/
    }

};


#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 ***************************************************************************************************
           DID Signal Configuration
 ***************************************************************************************************
**/

#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
CONST(Dcm_DataInfoConfig_tst, DCM_CONST) Dcm_DspDataInfo_st [55]=
{
    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_0101,            /* Read Data Function */
    
    
           32,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           1,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C001,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           2,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C002,            /* Read Data Function */
    
    
           192,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           3,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C003,            /* Read Data Function */
    
    
           240,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           4,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C004,            /* Read Data Function */
    
    
           64,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           5,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C005,            /* Read Data Function */
    
    
           48,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           6,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C006,            /* Read Data Function */
    
    
           48,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           7,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C007,            /* Read Data Function */
    
    
           72,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           8,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C008,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           9,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C009,            /* Read Data Function */
    
    
           8,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           10,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C010,            /* Read Data Function */
    
    
           160,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           11,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C011,            /* Read Data Function */
    
    
           256,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           12,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_C012,            /* Read Data Function */
    
    
           32,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           13,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D101,            /* Read Data Function */
    
    
           160,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D102,            /* Read Data Function */
    
    
           96,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D103,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D104,            /* Read Data Function */
    
    
           48,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D105,            /* Read Data Function */
    
    
           8,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D106,            /* Read Data Function */
    
    
           32,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D107,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           14,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D108,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           15,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D109,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           16,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D110,            /* Read Data Function */
    
    
           128,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D111,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           17,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D112,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D113,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           18,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D114,            /* Read Data Function */
    
    
           192,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D115,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           19,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D116,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           20,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D117,            /* Read Data Function */
    
    
           24,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D118,            /* Read Data Function */
    
    
           272,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D119,            /* Read Data Function */
    
    
           128,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D120,            /* Read Data Function */
    
    
           8,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D121,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           21,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D122,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           22,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_D123,            /* Read Data Function */
    
    
           16,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           23,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_E100,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_E101,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_E102,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_E103,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_E104,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F183,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F186,            /* Read Data Function */
    
    
           8,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F187,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           24,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F18B,            /* Read Data Function */
    
    
           24,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           25,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F18C,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           26,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F190,            /* Read Data Function */
    
    
           144,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           27,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F191,            /* Read Data Function */
    
    
           96,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           28,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F194,            /* Read Data Function */
    
    
           96,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F1A1,            /* Read Data Function */
    
    
           48,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           0,                         /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F1A2,            /* Read Data Function */
    
    
           256,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           29,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F1A3,            /* Read Data Function */
    
    
           24,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           30,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F1A4,            /* Read Data Function */
    
    
           80,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           31,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F1A5,            /* Read Data Function */
    
    
           112,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           32,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
,    
     {   
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	        (void*)&DcmDspDataReadFnc_F1A6,            /* Read Data Function */
    
    
           152,                                                 /*Signal Data Size */
           DCM_INVALID_NVDBLOCK,                               /*NVM block id for USE_BLOCK_ID*/
           33,    /*Index to DcmDspControlInfoStructure*/
           DCM_UINT8,                                          /* Data Type is UINT8 */
	       USE_DATA_SYNCH_FNC,      /*DataUsePort is USE_DATA_SYNCH_FNC*/
           DCM_BIG_ENDIAN,                 /*Signal endianness is BIG_ENDIAN*/
     
           TRUE,       /*Signal's fixedLength type**/
     
     
    }
    
    
};



#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"



/**
 ***************************************************************************************************
           DID Signal Configuration
 ***************************************************************************************************
**/
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


/* DID DcmDspDid_0101 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_101_SigConf[1]=
{
 /* Signal DcmDspDidSignal_0 */
    {
        0,    /* Signal Bit Position */
        0
    }
};

/* DID DcmDspDid_F183 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F183_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        41
    }
};

/* DID DcmDspDid_F187 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F187_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        43
    }
};

/* DID DcmDspDid_F190 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F190_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        46
    }
};

/* DID DcmDspDid_F18B signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F18B_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        44
    }
};

/* DID DcmDspDid_F18C signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F18C_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        45
    }
};

/* DID DcmDspDid_F191 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F191_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        47
    }
};

/* DID DcmDspDid_F194 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F194_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        48
    }
};

/* DID DcmDspDid_F1A1 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F1A1_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        49
    }
};

/* DID DcmDspDid_F1A2 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F1A2_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        50
    }
};

/* DID DcmDspDid_F1A3 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F1A3_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        51
    }
};

/* DID DcmDspDid_F1A4 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F1A4_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        52
    }
};

/* DID DcmDspDid_F1A5 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F1A5_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        53
    }
};

/* DID DcmDspDid_F1A6 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F1A6_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        54
    }
};

/* DID DcmDspDid_C001 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C001_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        1
    }
};

/* DID DcmDspDid_C002 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C002_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        2
    }
};

/* DID DcmDspDid_C003 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C003_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        3
    }
};

/* DID DcmDspDid_C004 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C004_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        4
    }
};

/* DID DcmDspDid_C005 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C005_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        5
    }
};

/* DID DcmDspDid_C006 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C006_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        6
    }
};

/* DID DcmDspDid_C007 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C007_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        7
    }
};

/* DID DcmDspDid_C008 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C008_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        8
    }
};

/* DID DcmDspDid_C009 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C009_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        9
    }
};

/* DID DcmDspDid_C010 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C010_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        10
    }
};

/* DID DcmDspDid_C011 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C011_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        11
    }
};

/* DID DcmDspDid_C012 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_C012_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        12
    }
};

/* DID DcmDspDid_D101 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D101_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        13
    }
};

/* DID DcmDspDid_D102 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D102_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        14
    }
};

/* DID DcmDspDid_D103 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D103_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        15
    }
};

/* DID DcmDspDid_D104 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D104_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        16
    }
};

/* DID DcmDspDid_D105 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D105_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        17
    }
};

/* DID DcmDspDid_D106 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D106_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        18
    }
};

/* DID DcmDspDid_D107 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D107_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        19
    }
};

/* DID DcmDspDid_D108 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D108_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        20
    }
};

/* DID DcmDspDid_D109 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D109_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        21
    }
};

/* DID DcmDspDid_D110 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D110_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        22
    }
};

/* DID DcmDspDid_D111 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D111_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        23
    }
};

/* DID DcmDspDid_D112 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D112_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        24
    }
};

/* DID DcmDspDid_D113 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D113_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        25
    }
};

/* DID DcmDspDid_D114 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D114_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        26
    }
};

/* DID DcmDspDid_D115 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D115_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        27
    }
};

/* DID DcmDspDid_D116 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D116_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        28
    }
};

/* DID DcmDspDid_D117 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D117_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        29
    }
};

/* DID DcmDspDid_D118 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D118_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        30
    }
};

/* DID DcmDspDid_D119 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D119_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        31
    }
};

/* DID DcmDspDid_D120 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D120_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        32
    }
};

/* DID DcmDspDid_D121 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D121_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        33
    }
};

/* DID DcmDspDid_D122 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D122_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        34
    }
};

/* DID DcmDspDid_D123 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_D123_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        35
    }
};

/* DID DcmDspDid_E100 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_E100_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        36
    }
};

/* DID DcmDspDid_E101 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_E101_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        37
    }
};

/* DID DcmDspDid_E102 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_E102_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        38
    }
};

/* DID DcmDspDid_E103 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_E103_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        39
    }
};

/* DID DcmDspDid_E104 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_E104_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        42
    }
};

/* DID DcmDspDid_F186 signal configuration */
static CONST(Dcm_SignalDIDConfig_tst, DCM_CONST) DcmDspDid_F186_SigConf[1]=
{
 /* Signal DcmDspDidSignal */
    {
        0,    /* Signal Bit Position */
        40
    }
};


#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"



/**
 ***************************************************************************************************
           DID Extended Configuration
 ***************************************************************************************************
*/
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_0101=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F183=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F187=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F190=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F18B=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F18C=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F191=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F194=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F1A1=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F1A2=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F1A3=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F1A4=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F1A5=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F1A6=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C001=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C002=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C003=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C004=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C005=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C006=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C007=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C008=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C009=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C010=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C011=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_C012=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed Write Session levels */
        0x2uL,     /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D101=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D102=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D103=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D104=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D105=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D106=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D107=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D108=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D109=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D110=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D111=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D112=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D113=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D114=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D115=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D116=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D117=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D118=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D119=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D120=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D121=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D122=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_D123=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x4uL,     /* Allowed IO control Session levels */
        0x2uL,     /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_NO,                                         /*Control mask is not relvant*/
        0x0,                                         /*Control mask size in bytes*/
        TRUE,            /* If Enabled allows the IOcontrol(IOCBI DIDS) to be reset on session/security change */
    
        0xF
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_E100=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_E101=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_E102=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_E103=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_E104=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};
static CONST(Dcm_ExtendedDIDConfig_tst, DCM_CONST) Did_extendedConfig_DcmDspDidInfo_F186=
{
    
        0x5uL,     /* Allowed Read Session levels */
        0xffffffffuL, /* Allowed Read Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed Write Session levels */
        0x0uL,           /* Allowed Write Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        0x0uL,          /* Allowed IO control Session levels */
        0x0uL,          /* Allowed IO control Security levels */
        NULL_PTR,       /*  No User defined Mode rule Function configured  */
        DCM_CONTROLMASK_INTERNAL,                                         /*Default value of Control mask*/
        0x0,                                         /*Control mask size in bytes*/
        FALSE,          /* If disabled does not the IOcontrol(IOCBI DIDS) to be reset on session/security change */
        0x00u
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


/**
 ***************************************************************************************************
           DID Configuration Structure
 ***************************************************************************************************
*/
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
CONST (Dcm_DIDConfig_tst, DCM_CONST) Dcm_DIDConfig []=
{

    {
        0x101,                        /*DID*/
        1,                          /*No of Signals*/
        4,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_101_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_0101   /*ExtendedConfiguration*/
    }


,
    {
        0xC001,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C001_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C001   /*ExtendedConfiguration*/
    }


,
    {
        0xC002,                        /*DID*/
        1,                          /*No of Signals*/
        24,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C002_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C002   /*ExtendedConfiguration*/
    }


,
    {
        0xC003,                        /*DID*/
        1,                          /*No of Signals*/
        30,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C003_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C003   /*ExtendedConfiguration*/
    }


,
    {
        0xC004,                        /*DID*/
        1,                          /*No of Signals*/
        8,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C004_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C004   /*ExtendedConfiguration*/
    }


,
    {
        0xC005,                        /*DID*/
        1,                          /*No of Signals*/
        6,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C005_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C005   /*ExtendedConfiguration*/
    }


,
    {
        0xC006,                        /*DID*/
        1,                          /*No of Signals*/
        6,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C006_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C006   /*ExtendedConfiguration*/
    }


,
    {
        0xC007,                        /*DID*/
        1,                          /*No of Signals*/
        9,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C007_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C007   /*ExtendedConfiguration*/
    }


,
    {
        0xC008,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C008_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C008   /*ExtendedConfiguration*/
    }


,
    {
        0xC009,                        /*DID*/
        1,                          /*No of Signals*/
        1,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C009_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C009   /*ExtendedConfiguration*/
    }


,
    {
        0xC010,                        /*DID*/
        1,                          /*No of Signals*/
        20,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C010_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C010   /*ExtendedConfiguration*/
    }


,
    {
        0xC011,                        /*DID*/
        1,                          /*No of Signals*/
        32,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C011_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C011   /*ExtendedConfiguration*/
    }


,
    {
        0xC012,                        /*DID*/
        1,                          /*No of Signals*/
        4,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_C012_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_C012   /*ExtendedConfiguration*/
    }


,
    {
        0xD101,                        /*DID*/
        1,                          /*No of Signals*/
        20,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D101_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D101   /*ExtendedConfiguration*/
    }


,
    {
        0xD102,                        /*DID*/
        1,                          /*No of Signals*/
        12,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D102_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D102   /*ExtendedConfiguration*/
    }


,
    {
        0xD103,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D103_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D103   /*ExtendedConfiguration*/
    }


,
    {
        0xD104,                        /*DID*/
        1,                          /*No of Signals*/
        6,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D104_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D104   /*ExtendedConfiguration*/
    }


,
    {
        0xD105,                        /*DID*/
        1,                          /*No of Signals*/
        1,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D105_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D105   /*ExtendedConfiguration*/
    }


,
    {
        0xD106,                        /*DID*/
        1,                          /*No of Signals*/
        4,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D106_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D106   /*ExtendedConfiguration*/
    }


,
    {
        0xD107,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D107_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D107   /*ExtendedConfiguration*/
    }


,
    {
        0xD108,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D108_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D108   /*ExtendedConfiguration*/
    }


,
    {
        0xD109,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D109_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D109   /*ExtendedConfiguration*/
    }


,
    {
        0xD110,                        /*DID*/
        1,                          /*No of Signals*/
        16,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D110_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D110   /*ExtendedConfiguration*/
    }


,
    {
        0xD111,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D111_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D111   /*ExtendedConfiguration*/
    }


,
    {
        0xD112,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D112_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D112   /*ExtendedConfiguration*/
    }


,
    {
        0xD113,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D113_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D113   /*ExtendedConfiguration*/
    }


,
    {
        0xD114,                        /*DID*/
        1,                          /*No of Signals*/
        24,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D114_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D114   /*ExtendedConfiguration*/
    }


,
    {
        0xD115,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D115_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D115   /*ExtendedConfiguration*/
    }


,
    {
        0xD116,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D116_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D116   /*ExtendedConfiguration*/
    }


,
    {
        0xD117,                        /*DID*/
        1,                          /*No of Signals*/
        3,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D117_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D117   /*ExtendedConfiguration*/
    }


,
    {
        0xD118,                        /*DID*/
        1,                          /*No of Signals*/
        34,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D118_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D118   /*ExtendedConfiguration*/
    }


,
    {
        0xD119,                        /*DID*/
        1,                          /*No of Signals*/
        16,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D119_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D119   /*ExtendedConfiguration*/
    }


,
    {
        0xD120,                        /*DID*/
        1,                          /*No of Signals*/
        1,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D120_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D120   /*ExtendedConfiguration*/
    }


,
    {
        0xD121,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D121_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D121   /*ExtendedConfiguration*/
    }


,
    {
        0xD122,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D122_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D122   /*ExtendedConfiguration*/
    }


,
    {
        0xD123,                        /*DID*/
        1,                          /*No of Signals*/
        2,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_D123_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_D123   /*ExtendedConfiguration*/
    }


,
    {
        0xE100,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_E100_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_E100   /*ExtendedConfiguration*/
    }


,
    {
        0xE101,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_E101_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_E101   /*ExtendedConfiguration*/
    }


,
    {
        0xE102,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_E102_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_E102   /*ExtendedConfiguration*/
    }


,
    {
        0xE103,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_E103_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_E103   /*ExtendedConfiguration*/
    }


,
    {
        0xE104,                        /*DID*/
        1,                          /*No of Signals*/
        1,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_E104_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_E104   /*ExtendedConfiguration*/
    }


,
    {
        0xF183,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F183_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F183   /*ExtendedConfiguration*/
    }


,
    {
        0xF186,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F186_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F186   /*ExtendedConfiguration*/
    }


,
    {
        0xF187,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F187_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F187   /*ExtendedConfiguration*/
    }


,
    {
        0xF18B,                        /*DID*/
        1,                          /*No of Signals*/
        3,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F18B_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F18B   /*ExtendedConfiguration*/
    }


,
    {
        0xF18C,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F18C_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F18C   /*ExtendedConfiguration*/
    }


,
    {
        0xF190,                        /*DID*/
        1,                          /*No of Signals*/
        18,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F190_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F190   /*ExtendedConfiguration*/
    }


,
    {
        0xF191,                        /*DID*/
        1,                          /*No of Signals*/
        12,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F191_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F191   /*ExtendedConfiguration*/
    }


,
    {
        0xF194,                        /*DID*/
        1,                          /*No of Signals*/
        12,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F194_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F194   /*ExtendedConfiguration*/
    }


,
    {
        0xF1A1,                        /*DID*/
        1,                          /*No of Signals*/
        6,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F1A1_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F1A1   /*ExtendedConfiguration*/
    }


,
    {
        0xF1A2,                        /*DID*/
        1,                          /*No of Signals*/
        32,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F1A2_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F1A2   /*ExtendedConfiguration*/
    }


,
    {
        0xF1A3,                        /*DID*/
        1,                          /*No of Signals*/
        3,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F1A3_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F1A3   /*ExtendedConfiguration*/
    }


,
    {
        0xF1A4,                        /*DID*/
        1,                          /*No of Signals*/
        10,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F1A4_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F1A4   /*ExtendedConfiguration*/
    }


,
    {
        0xF1A5,                        /*DID*/
        1,                          /*No of Signals*/
        14,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F1A5_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F1A5   /*ExtendedConfiguration*/
    }


,
    {
        0xF1A6,                        /*DID*/
        1,                          /*No of Signals*/
        19,                            /*TotalSize*/
        TRUE,                      /*FixedLength*/
        FALSE,                      /*DynamicallyDefined*/
        DcmDspDid_F1A6_SigConf,        /*DidSignalRef*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
        ((DCM_CFG_CONFIGSET1)|(DCM_CFG_CONFIGSET2)|(DCM_CFG_CONFIGSET3)|(DCM_CFG_CONFIGSET4)|
         (DCM_CFG_CONFIGSET5)|(DCM_CFG_CONFIGSET6)|(DCM_CFG_CONFIGSET7)|(DCM_CFG_CONFIGSET8)),                          /*DidConfigurationMask indicating availability of DID in different configuration sets*/
#endif
        &Did_extendedConfig_DcmDspDidInfo_F1A6   /*ExtendedConfiguration*/
    }



};
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
FUNC(uint16,DCM_CODE) Dcm_DIDcalculateTableSize_u16(void)
{
  return ((uint16)(sizeof(Dcm_DIDConfig))/(uint16)(sizeof(Dcm_DIDConfig_tst)));
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"







#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
boolean Dcm_ControlDtcSettingModecheck_b(
/* MR12 RULE 8.13 VIOLATION:The object addressed by the pointer parameter 'NegRespCode_u8' is not modified and so the pointer could be of type 'pointer to const' - Prototype is suggested by Autosar */
P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) NegRespCode_u8)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    VAR(boolean,AUTOMATIC) retVal_b;

    /* Call the DcmAppl API to check if the DTC Setting needs to be re-enabled */
    retVal_u8 =DcmAppl_UserDTCSettingEnableModeRuleService();

    if(retVal_u8!=E_OK)
    {
        (void)NegRespCode_u8;
        retVal_b = FALSE;
    }
    else
    {
        (void)NegRespCode_u8;
        retVal_b = TRUE;
    }
    return (retVal_b);

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"




/**
 ***************************************************************************************************
            Ecu Reset (ER) Service
 ***************************************************************************************************
*/
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Initialization of the parameters for the supported Reset Types */
CONST(Dcm_DspEcuReset_tst, DCM_CONST) Dcm_DspEcuResetType_cast[DCM_CFG_DSP_NUMRESETTYPE] =
{

    {
        RTE_MODE_DcmEcuReset_HARD,         /* DcmEcuReset Mode  for the ResetType */
        0x1,                              /* ResetType */
        DCM_RESET_NO_BOOT

    },

    {
        RTE_MODE_DcmEcuReset_SOFT,         /* DcmEcuReset Mode  for the ResetType */
        0x3,                              /* ResetType */
        DCM_RESET_NO_BOOT

    }
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"





/**
 ***************************************************************************************************
        Communication Control Service
 ***************************************************************************************************
*/
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
P2FUNC(Std_ReturnType,DCM_APPL_CODE,Dcm_ComMUserReEnableModeRuleRef)(void) = &DcmAppl_UserCommCtrlReEnableModeRuleService;
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static FUNC(boolean,DCM_CODE) Dcm_ComMChannel_Can_Network_2_Channel_IsModeDefault ( void )
{
	VAR(boolean,AUTOMATIC)	dataRetValue_b;

	if ( SchM_Mode_Dcm_R_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel() != RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_ENABLE_RX_TX_NORM_NM )
	{
		dataRetValue_b = FALSE;
	}
	else
	{
		dataRetValue_b = TRUE;
	}
	return (dataRetValue_b);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/* Function to map Dcm_CommunicationModeType to Rte_Communication Mode type for ComMChannel_Can_Network_2_Channel */
static FUNC(Std_ReturnType,DCM_CODE) Dcm_ComMChannel_Can_Network_2_Channel_SwitchIndication ( VAR(Dcm_CommunicationModeType,AUTOMATIC) Mode )
{
	VAR(Std_ReturnType,AUTOMATIC)	dataRetValue_u8;
	switch (Mode)
	{
		case DCM_ENABLE_RX_TX_NORM: dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel( RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_ENABLE_RX_TX_NORM);
			break;
		case DCM_ENABLE_RX_DISABLE_TX_NORM:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_ENABLE_RX_DISABLE_TX_NORM);
			break;
		case DCM_DISABLE_RX_ENABLE_TX_NORM: dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_DISABLE_RX_ENABLE_TX_NORM);
			break;
		case DCM_DISABLE_RX_TX_NORMAL:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_DISABLE_RX_TX_NORM);
			break;
		case DCM_ENABLE_RX_TX_NM:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_ENABLE_RX_TX_NM);
			break;
		case DCM_ENABLE_RX_DISABLE_TX_NM: dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel( RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_ENABLE_RX_DISABLE_TX_NM);
			break;
		case DCM_DISABLE_RX_ENABLE_TX_NM:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_DISABLE_RX_ENABLE_TX_NM);
			break;
		case DCM_DISABLE_RX_TX_NM:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_DISABLE_RX_TX_NM);
			break;
		case DCM_ENABLE_RX_TX_NORM_NM:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_ENABLE_RX_TX_NORM_NM);
			break;
		case DCM_ENABLE_RX_DISABLE_TX_NORM_NM:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_ENABLE_RX_DISABLE_TX_NORM_NM);
			break;
		case DCM_DISABLE_RX_ENABLE_TX_NORM_NM:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_DISABLE_RX_ENABLE_TX_NORM_NM);
			break;
		case DCM_DISABLE_RX_TX_NORM_NM:  dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_DISABLE_RX_TX_NORM_NM);
			break;
		default: dataRetValue_u8 = SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(RTE_MODE_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_DCM_ENABLE_RX_TX_NORM);
			break;
	}
	return (dataRetValue_u8);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Array for storing Special Subnet IDs supported and their corresponding ComM channels */
CONST (Dcm_Dsld_SpecificSubnetInfo, DCM_CONST) Dcm_specific_subnet_table[DCM_CFG_NUM_SPECIFIC_SUBNETS]=
{
	{
		&Dcm_ComMChannel_Can_Network_2_Channel_SwitchIndication,		/* Auto generated Dcm function to be called for invoking SchM Switch Indication */
		&Dcm_ComMChannel_Can_Network_2_Channel_IsModeDefault,		/* Auto generated Dcm function to be called for checking if Active Mode is Default */
		1,
		ComMConf_ComMChannel_ComMChannel_Can_Network_2_Channel
	}

};
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/*Array  stores the channelID info which is to be informed about the communication mode change if the subnet ID is 0  */
CONST(Dcm_Dsld_AllChannelsInfoType, DCM_CONST) Dcm_AllChannels_ForModeInfo[DCM_CFG_NUM_ALLCHANNELS_MODE_INFO]=
{
	{
		&Dcm_ComMChannel_Can_Network_2_Channel_SwitchIndication,  	/* Auto generated Dcm function to be called for invoking SchM Switch Indication */
		&Dcm_ComMChannel_Can_Network_2_Channel_IsModeDefault,		/* Auto generated Dcm function to be called for checking if Active Mode is Default */
 		ComMConf_ComMChannel_ComMChannel_Can_Network_2_Channel
	}
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"




/**
 ***************************************************************************************************
        Clear Diagnostic Information Service (0x14)
 ***************************************************************************************************
*/











