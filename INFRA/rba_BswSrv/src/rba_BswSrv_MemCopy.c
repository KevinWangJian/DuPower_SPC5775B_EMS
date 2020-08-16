/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#include "rba_BswSrv.h"

/*
 *********************************************************************
 * Defines
 *********************************************************************
 */

/*
 *********************************************************************
 * Variables
 *********************************************************************
 */

/*
 *********************************************************************
 * Functions
 *********************************************************************
 */

#define RBA_BSWSRV_START_SEC_CODE
#include "rba_BswSrv_MemMap.h"
/**
 ***********************************************************************************************************************
 * \brief Memcopy with the same parameters as C90-memcpy
 *
 * This function implements Memcopy with the same parameters as C90-memcpy
 * It copies 32 bit data, if possible. So it is save to copy structures which require consistent 32 bit data.
 *
 * \param[in]       void* xDest_pv, const void* xSrc_pcv, uint32 numBytes_u32
 * \return          void*
 ***********************************************************************************************************************
 */
 
void* rba_BswSrv_MemCopy(void* xDest_pv, const void* xSrc_pcv, uint32 numBytes_u32)
{
    uint32* xDest_pu32       = (uint32*)xDest_pv;
    const uint32* xSrc_pcu32 = (const uint32*)xSrc_pcv;
    uint16* xDest_pu16;
    const uint16* xSrc_pcu16;
    uint8* xDest_pu8;
    const uint8* xSrc_pcu8;
    uint32 ctLoop_u32;

    /* 32 bit aligned copy */
    /* MISRA RULE 11.3 VIOLATION: cast cannot be avoided here */
    if ((numBytes_u32 >= 4) && ((((uint32)xDest_pu32 | (uint32)xSrc_pcu32) & 0x03) == 0))
    {
        ctLoop_u32 = numBytes_u32 / 4;
        numBytes_u32 &= 0x03;
        do
        {
            *xDest_pu32 = *xSrc_pcu32;
            xDest_pu32++;
            xSrc_pcu32++;
            ctLoop_u32--;
        } while(ctLoop_u32 > 0);
    }
    /* MISRA RULE 11.4 VIOLATION: cast cannot be avoided here */
    xDest_pu16 = (uint16*)xDest_pu32;
    xSrc_pcu16 = (const uint16*)xSrc_pcu32;

    /* 16 bit aligned copy */
    /* MISRA RULE 11.3 VIOLATION: cast cannot be avoided here */
    if ((numBytes_u32 >= 2) && ((((uint32)xDest_pu16 | (uint32)xSrc_pcu16) & 0x01) == 0))
    {
        ctLoop_u32 = numBytes_u32 / 2;
        numBytes_u32 &= 0x01;
        do
        {
            *xDest_pu16 = *xSrc_pcu16;
            xDest_pu16++;
            xSrc_pcu16++;
            ctLoop_u32--;
        } while(ctLoop_u32 > 0);
    }
    /* MISRA RULE 11.4 VIOLATION: cast cannot be avoided here */
    xDest_pu8 = (uint8*)xDest_pu16;
    xSrc_pcu8 = (const uint8*)xSrc_pcu16;

    /* 8 bit copy for remaining data */
    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        *xDest_pu8 = *xSrc_pcu8;
        xDest_pu8++;
        xSrc_pcu8++;
    }
    return xDest_pv;
}

#define RBA_BSWSRV_STOP_SEC_CODE
#include "rba_BswSrv_MemMap.h"

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
