

#ifndef FIM_STATUS_H
#define FIM_STATUS_H

#include "FiM_Priv_Data.h"
#include "FiM_Utils.h"
#include "FiM_Det.h"
#include "FiM_Cfg_SchM.h"
/**
 **************************************************************************************************
 * macros and definitions
 **************************************************************************************************
 */
#define FIM_PRIV_ZERO 	(0x00)
/**
 **************************************************************************************************
 * status data structure
 **************************************************************************************************
 */
#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
extern uint8 FiM_FIdStatusBitArray_au8[2][(FIM_CFG_NUMBEROFFIDS + 1 + 7) / 8];
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
/* Bit array for Service 07 visible entry */
extern uint8 FiM_FIdStatusServ07BitArray_au8[2][(FIM_CFG_NUMBEROFFIDS + 1 + 7) / 8];
#endif
#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

#define FIM_START_SEC_RAM_INIT
#include "FiM_MemMap.h"
extern uint8 FiM_LastIdx;
extern uint8 FiM_CurrentIdx;
#define FIM_STOP_SEC_RAM_INIT
#include "FiM_MemMap.h"

#else

#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
extern FiM_FIdStatusCounterType FiM_FIdStatusCounter_auo[FIM_CFG_NUMBEROFFIDS+1];
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
extern FiM_FIdStatusCounterType FiM_FIdServ07StatusCounter_auo[FIM_CFG_NUMBEROFFIDS+1];
#endif
#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

#endif
/**
 **************************************************************************************************
 * prototypes for private functions of FiM_Status.h
 **************************************************************************************************
 */
#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"
void FiM_Priv_StatusInit(void);

/**
 **************************************************************************************************
 * private inline functions of FiM_Status.h
 **************************************************************************************************
 */
#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)
/* private function to return the inhibit counter of an FId */
LOCAL_INLINE FiM_FIdStatusCounterType FiM_Priv_FIdGetInhibitCounter(FiM_FunctionIdType FId)
{
    return (FiM_FIdStatusCounter_auo[FId]);
}
#endif

/* private function to evaluate the permission status of an FId */
LOCAL_INLINE boolean FiM_Priv_FIdGetPermission(FiM_FunctionIdType FId)
{
    boolean FiM_PermissionStatus = FALSE;

#if(FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
    FIM_PRIV_ENTERLOCK_MONITOR();
    FiM_PermissionStatus = (((FiM_FIdStatusBitArray_au8[FiM_LastIdx][(FId / 8)]) & ((uint8) (1u << (uint8) (FId % 8))))
            == 0);
    FIM_PRIV_EXITLOCK_MONITOR();
#else
    FIM_PRIV_ENTERLOCK_STATUS();
    FiM_PermissionStatus = ((FiM_FIdStatusCounter_auo[FId])==0);
    FIM_PRIV_EXITLOCK_STATUS();
#endif
    return FiM_PermissionStatus;
}

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)
/* private function to increment the inhibit counter of an FId */

LOCAL_INLINE void FiM_Priv_FIdCountInc(FiM_FunctionIdType FId)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    if (FiM_FIdStatusCounter_auo[FId] < FIM_CFG_STATUSCOUNTERMAX )
    {
        FiM_FIdStatusCounter_auo[FId]++;
    }

    FIM_PRIV_EXITLOCK_STATUS();
}

/* private function to decrement the inhibit counter of an FId */
LOCAL_INLINE void FiM_Priv_FIdCountDec(FiM_FunctionIdType FId)
{
#if (FIM_CFG_DEV_ERROR_DETECT == FIM_CFG_ON)
    boolean FiM_DetErrorFlag = FALSE;
#endif

    FIM_PRIV_ENTERLOCK_STATUS();

    if( FiM_FIdStatusCounter_auo[FId] > 0 )
    {
        FiM_FIdStatusCounter_auo[FId]--;
    }
#if (FIM_CFG_DEV_ERROR_DETECT == FIM_CFG_ON)
    else
    {
        /* Set the Error flag to TRUE */
        FiM_DetErrorFlag = TRUE;
    }
#endif

    FIM_PRIV_EXITLOCK_STATUS();

#if (FIM_CFG_DEV_ERROR_DETECT == FIM_CFG_ON)
    /* Invoke Det only if the error flag is set */
    if(FiM_DetErrorFlag == TRUE)
    {
        FIM_PRIV_DET_ERROR(FIM_PRIV_FIDCOUNTDEC_ID,FIM_E_FID_COUNTERNEGATIVE);
    }
#endif
}

/* private function to reset the inhibit counter of an FId */
LOCAL_INLINE void FiM_Priv_FIdCountReset(FiM_FunctionIdType FId)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    FiM_FIdStatusCounter_auo[FId] = 0;

    FIM_PRIV_EXITLOCK_STATUS();
}

/* private function to set the inhibit counter of an FId to a dedicated value */
LOCAL_INLINE void FiM_Priv_FIdCountSet(FiM_FunctionIdType FId, const FiM_FIdStatusCounterType value)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    FiM_FIdStatusCounter_auo[FId] |= (FiM_FIdStatusCounterType)FIM_PRIV_MIN(value,FIM_CFG_STATUSCOUNTERMAX);

    FIM_PRIV_EXITLOCK_STATUS();
}

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
/* private function to increment the service$07 visibility counter of an FId */
LOCAL_INLINE void FiM_Priv_FIdServ07CountInc(FiM_FunctionIdType FId)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    if (FiM_FIdServ07StatusCounter_auo[FId] < FIM_CFG_STATUSCOUNTERMAX )
    {
        FiM_FIdServ07StatusCounter_auo[FId]++;
    }

    FIM_PRIV_EXITLOCK_STATUS();
}

/* private function to decrement the service$07 visibility counter of an FId */
LOCAL_INLINE void FiM_Priv_FIdServ07CountDec(FiM_FunctionIdType FId)
{
    FIM_PRIV_ENTERLOCK_STATUS();

    if( FiM_FIdServ07StatusCounter_auo[FId] > 0 )
    {
        FiM_FIdServ07StatusCounter_auo[FId]--;
    }

    FIM_PRIV_EXITLOCK_STATUS();
}
#endif

#endif

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
/* private function to set the current monitoring inhibit bit */
LOCAL_INLINE void FiM_Priv_SetInhStatus(FiM_FunctionIdType FId_uo)
{
    /* Set the inhibition status of that particular Fid */
    FiM_FIdStatusBitArray_au8[FiM_CurrentIdx][(FId_uo / 8)] |= ((uint8) (1u << (FId_uo % 8)));
}

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
/* private function to set the current service$07 visible entry bit */
LOCAL_INLINE void FiM_Priv_SetServ07InhStatus(FiM_FunctionIdType FId_uo)
{
    /* Set the inhibition status of that particular Fid */
    FiM_FIdStatusServ07BitArray_au8[FiM_CurrentIdx][(FId_uo / 8)] |= ((uint8) (1u << (FId_uo % 8)));
}
#endif
#endif

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif /* include protection */

