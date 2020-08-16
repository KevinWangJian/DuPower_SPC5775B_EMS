

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /*
***********************************************************************************************************
*  Dcm_SetSecurityLevel: To set the new security level value in DCM
*  \param    dataSecurityLevel_u8:  New security level value
*  \retval
*  \seealso
***********************************************************************************************************/

FUNC(void,DCM_CODE) Dcm_SetSecurityLevel (VAR(Dcm_SecLevelType, AUTOMATIC) dataSecurityLevel_u8)
{
    VAR(uint8_least,AUTOMATIC) idxIndex_qu8;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
    VAR(uint32,AUTOMATIC) dataSecurityMask_u32;							/*Active security Mask*/
#endif
	
    /* pointer to security look up table array */
    P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) adrSecurityLookupTable_pcu8;

    /* get the look up table from configuration */
    adrSecurityLookupTable_pcu8 = Dcm_Dsld_Conf_cs.security_lookup_table_pcau8;

    /* get the index of the requested security level in security look up table */
    for(idxIndex_qu8 = 0x0; idxIndex_qu8 < DCM_CFG_NUM_SECURITY_LEVEL ; idxIndex_qu8++)
    {
        if(adrSecurityLookupTable_pcu8[idxIndex_qu8]== dataSecurityLevel_u8)
        {
            /* requested security level found */
            break;
        }
    }

    if(idxIndex_qu8< DCM_CFG_NUM_SECURITY_LEVEL)
    {
        /* set security level index */
        Dcm_DsldGlobal_st.idxActiveSecurity_u8 = (uint8)idxIndex_qu8;
	
    #if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
        /**The code which would loop through all the IOCBI DIDs and call all the returncontrol to ECU functions to reset all the IOctrls which are not active in the current security level
        ***supported in the current security level or not*/
        dataSecurityMask_u32 = Dcm_DsldGetActiveSecurityMask_u32();
        /*Session MASK is sent as 0xFFFFFFFF because during security transition, session mask is not affected
         * there is no need to do session check, Hence 0xFFFFFFFF is sent which will always result in true,on security
         * transition there is no need to check for session mask, Hence FALSE is passed which will result in session check being disabled*/
    Dcm_ResetActiveIoCtrl(0xFFFFFFFFu,dataSecurityMask_u32,FALSE);
    #endif
    }
    else
    {
        /* Report development error "DCM_E_SECURITYLEVEL_NOT_CONFIGURED " to DET module if the DET module is enabled */
        DCM_DET_ERROR(DCM_SETSECURITYLEVEL , DCM_E_SECURITYLEVEL_OUTOFBOUNDS )
    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

