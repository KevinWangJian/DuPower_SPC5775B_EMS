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
 * \brief MemSet with the same parameters as C90-memset
 *
 * This function implements MemSet with the same parameters as C90-memset
 * It Writes 32 bit data, if possible. So it is save to initialize structures which require consistent 32 bit data.
 *
 * \param[in]       void* xDest_pv, sint32 xPattern_u32, uint32 numBytes_u32
 * \return          void*
 ***********************************************************************************************************************
 */
 
void* rba_BswSrv_MemSet(void* xDest_pv, sint32 xPattern_u32, uint32 numBytes_u32)
{
    /* MISRA RULE 11.3 VIOLATION: cast cannot be avoided here */
    uint32  adDest_u32 = (uint32)xDest_pv;
    uint32* xDest_pu32;
    uint16* xDest_pu16;
    uint8* xDest_pu8;
    uint8  xPattern_u8  = (uint8)xPattern_u32;
    uint32 ctLoop_u32;

    /* only lower 8 bit are used for initialization */
    xPattern_u32 = xPattern_u8 + (xPattern_u8 << 8) + (xPattern_u8 << 16) + (xPattern_u8 << 24);
    
    /* 8 bit leading gap */
    if ((numBytes_u32 >= 1) && ((adDest_u32 & 0x01) != 0))
    {
        /* MISRA RULE 11.3 VIOLATION: cast cannot be avoided here */
        xDest_pu8 = (uint8*)adDest_u32;
        numBytes_u32 -= 1;
        *xDest_pu8 = (uint8)xPattern_u32;
        adDest_u32++;
    }

    /* 16 bit leading gap */
    if ((numBytes_u32 >= 2) && ((adDest_u32 & 0x02) != 0))
    {
        /* MISRA RULE 11.3 VIOLATION: cast cannot be avoided here */
        xDest_pu16 = (uint16*)adDest_u32;
        numBytes_u32 -= 2;
        *xDest_pu16 = (uint16)xPattern_u32;
        adDest_u32 += 2;
    }

    /* 32 bit set */
    /* MISRA RULE 11.3 VIOLATION: cast cannot be avoided here */
    xDest_pu32 = (uint32*)adDest_u32;
    if (numBytes_u32 >= 4)
    {
        ctLoop_u32 = numBytes_u32 / 4;
        numBytes_u32 &= 0x03;
        do
        {
            *xDest_pu32 = (uint32)xPattern_u32;
            xDest_pu32++;
            ctLoop_u32--;
        } while(ctLoop_u32 > 0);
    }

    /* 16 bit set */
    /* MISRA RULE 11.4 VIOLATION: cast cannot be avoided here */
    xDest_pu16 = (uint16*)xDest_pu32;
    if (numBytes_u32 >= 2)
    {
        numBytes_u32 -= 2;
        *xDest_pu16 = (uint16)xPattern_u32;
        xDest_pu16++;
    }

    /* 8 bit set */
    /* MISRA RULE 11.4 VIOLATION: cast cannot be avoided here */
    xDest_pu8 = (uint8*)xDest_pu16;
    if(numBytes_u32 > 0)
    {
        *xDest_pu8 = (uint8)xPattern_u32;
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
