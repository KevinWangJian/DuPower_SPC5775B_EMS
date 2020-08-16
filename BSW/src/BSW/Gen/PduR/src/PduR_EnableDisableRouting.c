
#include "PduR_Prv.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */


/**
 **************************************************************************************************
 * PduR_DisableRouting : Control function to disable routing of PDUs from one src to one or more
 *                       than one dest layers.
 *
 * \param           PduR_RoutingPathGroupIdType id: RoutingPathGroupId
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"


FUNC( void, PDUR_CODE ) PduR_DisableRouting( VAR(PduR_RoutingPathGroupIdType, AUTOMATIC) id)
{
/* checking for mode dependent routing is enabled or not during Pre-compile time */
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
    /* Checking for Routing path id */
    if ((id != 0) && (id <= PDUR_GET_RPGID_MAX))
    {
        /* Enter Critical Section */
        SchM_Enter_PduR_LockDisableRoutingNoNest();
        if((PDUR_RPG_ENROUTING_INFO(id)) == TRUE)
        {
            /* Disable routing for this RPG */
            (PDUR_RPG_ENROUTING_INFO(id)) = FALSE;
            /* Checking for data*/
            if (PDUR_RPG_CONFIG_INFO[id].targetInfo != NULL_PTR)
            {
                PduR_FifoDynIfPtr       dyn_If;
                PduR_TpSessDynPtr       dyn_Tp;
                P2VAR(PduR_BuffLockType, AUTOMATIC, PDUR_VAR)  buffPtr;
                P2CONST( PduR_TargetInfoType, AUTOMATIC, PDUR_CONST ) targetInfo;
                VAR(uint8, AUTOMATIC)   cntDest;
                VAR(uint8, AUTOMATIC)   index;

                targetInfo = PDUR_RPG_CONFIG_INFO[id].targetInfo;
                cntDest = PDUR_RPG_CONFIG_INFO[id].cntDest;

                for(index=0;index < cntDest;index++)
                {

                    switch(targetInfo->pathType)
                    {
                        case PDUR_FIFO_IF:

                                        /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
                                         * Hence Supressed.*/
                                        dyn_If = (PduR_FifoDynIfPtr)targetInfo->destInfo;
                                        dyn_If->used           = 0;
                                        dyn_If->txConfPending  = 0;            /* Reset txConfPending to ignore TtxConfirmation. */
                                        dyn_If->writePtr       = dyn_If->readPtr; /* Remove all elements from the FIFO */

                            break;

                        case PDUR_UCSEB_TP:
                                        /* Buffer Lock needs to be locked */
                                        /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
                                         * Hence Supressed.*/
                                        buffPtr = (P2VAR(PduR_BuffLockType, AUTOMATIC, PDUR_VAR))targetInfo->destInfo;
                                        buffPtr->bufferLock = 0;
                            break;

                        case PDUR_MCSEB_TP:
                                        /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
                                         * Hence Supressed.*/
                                        buffPtr = (P2VAR(PduR_BuffLockType, AUTOMATIC, PDUR_VAR))targetInfo->destInfo;
                                        /* Decrement the lower Layer */
                                        buffPtr->lowerLayers = buffPtr->lowerLayers - 1;

                            break;

                        case PDUR_UCFIFO_TP:
                                        /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
                                         * Hence Supressed.*/
                                        dyn_Tp = (PduR_TpSessDynPtr)targetInfo->destInfo;
                                        /*Reset the FIFO TP buffer*/
                                        dyn_Tp->writePtr =  dyn_Tp->readPtr;
                                        dyn_Tp->numRxLength = 0;
                                        dyn_Tp->numTxLength = 0;
                                        dyn_Tp->SduLength = 0;
                            break;

                        default:
                            break;


                    }
                    targetInfo++;

                }

            }/*End of if (PDUR_RPG_CONFIG_INFO[id].targetInfo != NULL_PTR)*/
        }/*End of if((PDUR_RPG_ENROUTING_INFO)[(PDUR_RPG_CONFIG_INFO[id].rpg_Idx)] == TRUE)*/
        SchM_Exit_PduR_LockDisableRoutingNoNest();
        /* Exit Critical section */
    }
    else
    {
        /* Routing path table id does not exist and the PduRDevErrorDetect is enabled */
        PDUR_REPORT_ERROR(PDUR_SID_DISABLEROUTING, PDUR_E_ROUTING_TABLE_ID_INVALID);
    }

   #else
        (void)id;
   #endif
}

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"




/**
 **************************************************************************************************
 * PduR_EnableRouting : Control function to enable routing of PDUs from one src to one or more than
 *                      one dest layers.
 *
 * \param           PduR_RoutingPathGroupIdType id: RoutingPathGroupId
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */


#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_EnableRouting( VAR(PduR_RoutingPathGroupIdType, AUTOMATIC) id)
{
/* check for mode dependent routing is enabled or not during Pre-compile time */
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

     /* Checking for Routing path id */
     if ((id != 0) && (id <= PDUR_GET_RPGID_MAX))
     {
         /* Enter Critical Section */
         SchM_Enter_PduR_LockEnableRoutingNoNest();

         /* Enable routing for this RPG */
         if ((PDUR_RPG_ENROUTING_INFO(id)) == FALSE)
         {
             (PDUR_RPG_ENROUTING_INFO(id)) = TRUE;

            /* Decrement the lower layers if the Routing path is Multicast SEB */
            if (PDUR_RPG_CONFIG_INFO[id].targetInfo != NULL_PTR)
            {
                PduR_TpSessDynPtr       dyn_Tp;
                P2VAR(PduR_BuffLockType, AUTOMATIC, PDUR_VAR) buffPtr;
                const PduR_TargetInfoType     *targetInfo;
                VAR(uint8, AUTOMATIC)   cntDest;
                VAR(uint8, AUTOMATIC)   index;

                targetInfo = PDUR_RPG_CONFIG_INFO[id].targetInfo;
                cntDest = PDUR_RPG_CONFIG_INFO[id].cntDest;
                for(index=0;index < cntDest;index++)
                {
                    switch(targetInfo->pathType)
                    {
                            case PDUR_MCSEB_TP:
                                        /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
                                        * Hence Supressed.*/
                                        buffPtr = (PduR_BuffLockType*)targetInfo->destInfo;
                                        /* Increment the lower Layer */
                                        buffPtr->lowerLayers = buffPtr->lowerLayers + 1;

                                 break;
                            case PDUR_UCSEB_TP:
                                        /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
                                        * Hence Supressed.*/
                                        buffPtr = (PduR_BuffLockType*)targetInfo->destInfo;
                                        /* Increment the lower Layer */
                                        buffPtr->lowerLayers = 1;
                                        buffPtr->bufferLock = 0;

                                 break;
                            case PDUR_UCFIFO_TP:
                                        /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
                                         * Hence Supressed.*/
                                        dyn_Tp = (PduR_TpSessDynPtr)targetInfo->destInfo;
                                        /*Reset the FIFO TP buffer*/
                                        dyn_Tp->writePtr =  dyn_Tp->readPtr;
                                        dyn_Tp->numRxLength = 0;
                                        dyn_Tp->numTxLength = 0;
                                        dyn_Tp->SduLength = 0;
                                 break;
                            default:
                                 break;

                    }

                    targetInfo++;

                }

            }
         }


         SchM_Exit_PduR_LockEnableRoutingNoNest();
         /* Exit Critical Section */
     }
     else
     {
        /* Routing path group id does not exist and the PduRDevErrorDetect is enabled */
        PDUR_REPORT_ERROR(PDUR_SID_ENABLEROUTING, PDUR_E_ROUTING_TABLE_ID_INVALID);
     }

   #else
      (void)id;
   #endif
}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

