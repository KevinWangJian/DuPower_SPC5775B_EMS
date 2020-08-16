

/**
 **************************************************************************************************
 * FiM_Utils.h
 * utilities header for Function Inhibition Manager
 * Design specification: AUTOSAR_SWS_FunctionInhibitionManager.pdf Version 4.0 Rev0002
 **************************************************************************************************
 */

#ifndef FIM_UTILS_H
#define FIM_UTILS_H

#include "FiM_Cfg.h"
#include "FiM_Priv_Data.h"
#include "rba_DiagLib_MemUtils.h"

/* Abstraction to the MemSet, MemCompare and MemCopy Library function */
#define FIM_MEMSET(xDest_pv,xPattern_u32,numBytes_u32)    RBA_DIAGLIB_MEMSET((xDest_pv),(xPattern_u32),(numBytes_u32))

/**
 **************************************************************************************************
 * macro to suppress QAC warnings for unused parameters
 **************************************************************************************************
 */
#define FIM_USE_VAR(P)   ((void)(P))

/**
 **************************************************************************************************
 * macro for MINand MAX
 **************************************************************************************************
 */

#define FIM_PRIV_MIN(a, b)  ( ((a) < (b)) ? (a) : (b) )

#define FIM_PRIV_MAX(a, b)  ( ((a) > (b)) ? (a) : (b) )

/**
 **************************************************************************************************
 * macros for inhibition mask checks acc. to chapter 10.2.7
 **************************************************************************************************
 */
#define FIM_LAST_FAILED_MASK        0x01u    /* TF */
#define FIM_LAST_FAILED_VALUE       0x01u    /* TF */
#define FIM_NOT_TESTED_MASK         0x40u    /* TNCTOC */
#define FIM_NOT_TESTED_VALUE        0x40u    /* TNCTOC */
#define FIM_TESTED_MASK             0x40u    /* TNCTOC */
#define FIM_TESTED_VALUE            0x00u    /* !TNCTOC */
#define FIM_TESTED_AND_FAILED_MASK  0x41u    /* TNCTOC&TF */
#define FIM_TESTED_AND_FAILED_VALUE 0x01u    /* !TNCTOC&TF */

#define FIM_INHIBITION_BITS_MASK    0x41u /* (LAST_FAILED_MASK|NOT_TESTED_MASK|TESTED_MASK|TESTED_AND_FAILED_MASK) */

#define FIM_PENDING_BITS_MASK       0x04u
#define FIM_PENDING_BITS_VALUE      0x04u

/**
 **************************************************************************************************
 * macros for critical sections
 **************************************************************************************************
 */

#define FIM_PRIV_ENTERLOCK_MONITOR()            SchM_Enter_FiM_Monitor_NoNest()
#define FIM_PRIV_EXITLOCK_MONITOR()             SchM_Exit_FiM_Monitor_NoNest()

#define FIM_PRIV_ENTERLOCK_STATUS()             SchM_Enter_FiM_Status_NoNest()
#define FIM_PRIV_EXITLOCK_STATUS()              SchM_Exit_FiM_Status_NoNest()

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"
/**
 **************************************************************************************************
 * prototypes for utility functions
 **************************************************************************************************
 */

/**
 **************************************************************************************************
 * definition of inline utility functions
 **************************************************************************************************
 */

/**
 **************************************************************************************************
 * This function checks if an inhibition situation exists.
 *
 * param[in]	eventStatus_u8  The DTC status byte of the Event
 * param[in]	maskType_uo     The mask that is configured for the Event/FId inhibition relation
 * return		TRUE/FALSE:      Do we have an inhibit situation?
 * see [AR402:FIM096_Conf]
 **************************************************************************************************
 */
LOCAL_INLINE boolean FiM_Priv_IsInhibitionSet(uint8 statusByte_u8, FiM_InhibitionMaskType maskType_uo)
{
    boolean retVal_b = FALSE;

    switch (maskType_uo)
    {
        case FIM_CFG_LAST_FAILED:
            if ((statusByte_u8 & FIM_LAST_FAILED_MASK) == FIM_LAST_FAILED_VALUE)
            {
                retVal_b = TRUE;
            }
            break;

        case FIM_CFG_NOT_TESTED:
            if ((statusByte_u8 & FIM_NOT_TESTED_MASK) == FIM_NOT_TESTED_VALUE)
            {
                retVal_b = TRUE;
            }
            break;

        case FIM_CFG_TESTED:
            if ((statusByte_u8 & FIM_TESTED_MASK) == FIM_TESTED_VALUE)
            {
                retVal_b = TRUE;
            }
            break;

        case FIM_CFG_TESTED_AND_FAILED:
            if ((statusByte_u8 & FIM_TESTED_AND_FAILED_MASK) == FIM_TESTED_AND_FAILED_VALUE)
            {
                retVal_b = TRUE;
            }
            break;

        case FIM_CFG_FAILED_OR_NOT_TESTED:
            if (((statusByte_u8 & FIM_NOT_TESTED_MASK) == FIM_NOT_TESTED_VALUE)
                    || ((statusByte_u8 & FIM_LAST_FAILED_MASK) == FIM_LAST_FAILED_VALUE))
            {
                retVal_b = TRUE;
            }
            break;

        default: /* superfluous default, but necessary according to coding guidelines */
            retVal_b = FALSE;
            break;
    }

    return retVal_b;
}

/**
 *******************************************************************************************************************
 * This function checks if relevant bits are set, so that a further check for the inhibition situation makes sense
 *
 * param[in]	statusByteNew_u8    The DTC status byte of the new event
 * param[in]	statusByteOld_u8    The DTC status byte of the old event
 * param[in]    maskType_uo         The mask that is configured for the Event/FId inhibition relation
 * param[out]   inhStatusNew_b      Do we have an inhibit situation for the new status?
 * return		TRUE/FALSE          Did the inhibit situation change?
 * see [AR402:FIM096_Conf]
 *******************************************************************************************************************
 */
LOCAL_INLINE boolean FiM_Priv_IsInhibitionChanged(uint8 statusByteNew_u8, uint8 statusByteOld_u8,
        FiM_InhibitionMaskType maskType_uo, boolean* inhStatusNew_b)
{
    boolean inhStatusOld_b = FiM_Priv_IsInhibitionSet(statusByteOld_u8, maskType_uo);
    *inhStatusNew_b = FiM_Priv_IsInhibitionSet(statusByteNew_u8, maskType_uo);

    return (*inhStatusNew_b != inhStatusOld_b);
}

/**
 *******************************************************************************************************************
 * This function checks if a configured mask is relevant for service$07
 *
 * param[in]    maskType_uo         The mask that is configured for the Event/FId inhibition relation
 * return       TRUE/FALSE          Is the InhMask relevant for service$07?
 * see [AR402:FIM096_Conf]
 *******************************************************************************************************************
 */
LOCAL_INLINE boolean FiM_Priv_IsInhMaskServ07Relevant(FiM_InhibitionMaskType maskType_uo)
{
    return ((maskType_uo == FIM_CFG_LAST_FAILED) || (maskType_uo == FIM_CFG_TESTED_AND_FAILED)
            || (maskType_uo == FIM_CFG_FAILED_OR_NOT_TESTED));
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif /* include protection */

