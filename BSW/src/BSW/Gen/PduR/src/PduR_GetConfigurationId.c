
/* PDU Router Configuratio ID  */

#include "PduR_Prv.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( uint16, PDUR_CODE ) PduR_GetConfigurationId( void )
{
    uint16 return_val;
#if defined(PDUR_ZERO_COST_OPERATION) && (PDUR_ZERO_COST_OPERATION!= STD_OFF)
    return_val = (uint16)0;
#elif defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
    return_val=  PduR_dGetConfigurationId();
#else
    return_val= PduR_iGetConfigurationId();
#endif /* PDUR_ZERO_COST_OPERATION */
    return return_val;
}

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
FUNC( uint16, PDUR_CODE ) PduR_dGetConfigurationId( void )
{
    PDUR_CHECK_STATE_RET( PDUR_SID_GETCFGID, 0 )
    return PduR_iGetConfigurationId();
}
#endif /*#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)*/
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_iGetConfigurationId
 *        This function returns the unique identifier of the post-build time configuration of the PDU Router
 *
 * \param           None
 * \retval          unique identifier of the post-build time configuration
 *
 * \seealso         PDUR242, PDUR280
 * \usedresources
 **************************************************************************************************
 */
FUNC( uint16, PDUR_CODE ) PduR_iGetConfigurationId( void )
{
    uint16 return_val;
#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
    return_val = PduR_Base->configId; /* configuration id */
#else
    return_val = PDUR_CONFIGURATION_ID;
#endif

    return return_val;
}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

