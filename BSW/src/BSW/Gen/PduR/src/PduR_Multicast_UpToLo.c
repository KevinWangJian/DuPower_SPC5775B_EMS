

#include "PduR_Prv.h"
#include "PduR_Mc.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
/**
 **************************************************************************************************
 * PduR_MF_UpToLo
 *      Support function to handle multicast from upper layers to lower layers
 *
 * \param           PduR_MT_UpToLo upToLoTable: Multicast routing table
 *                  PduIdType mcId            :ID of I-PDU to be transmitted.
 *                  P2VAR( P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), TYPEDEF, PDUR_APPL_DATA ) ptr:Pointer to pointer to PduInfoStructure containing SDU data pointer and
 *                                             SDU length of a transmit buffer.
 *
 * \retval          E_OK, E_NOT_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_UpToLo(P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) upToLoTable,
                                                 VAR(PduIdType, AUTOMATIC) mcId,
                                                 P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) tablePtr = upToLoTable;
    VAR(Std_ReturnType, AUTOMATIC) rtn = E_NOT_OK;
    VAR(uint8, AUTOMATIC) cnt_Not_Ok = 0;

    #if(PDUR_MULTICAST_TO_IF_SUPPORT == 1)
    boolean flg = FALSE;
    #endif

    /* check for tablePtr */
    if(upToLoTable != NULL_PTR)
    {
           /*Table ptr is incremented till indexes to the expected Mc_GwToLo table entry*/
            while(tablePtr->upId < mcId)
            {
                tablePtr++;
            }

            while (tablePtr->upId == mcId)
            {
                #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

                   /* Below check is to perform routing if it is configured and enabled. */
                if ((tablePtr->routingCntrl_Idx == PDUR_RPGID_NULL)   ||  /* Routing control is not required.*/
                    ((PDUR_RPG_ENROUTING_INFO(tablePtr->routingCntrl_Idx)) != FALSE ))   /* Routing is enabled or not */
                #endif
                {
                    #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                    rtn = PDUR_BASE_RPTBL(loTxTablePtr)[tablePtr->upToLo.loTransmitID].PduR_loTransmitFunc (tablePtr->upToLo.loId, info);
                    #else
                    rtn = PduR_loTransmitTable[tablePtr->upToLo.loTransmitID].PduR_loTransmitFunc (tablePtr->upToLo.loId, info);
                    #endif
                    if (rtn != E_OK)
                    {
                        cnt_Not_Ok++;
                    }
                    #if(PDUR_MULTICAST_TO_IF_SUPPORT == 1)
                    else
                    {
                        flg = TRUE;
                    }
                    #endif
                }
                tablePtr++;  /* Iterate for next table entry. */
            }  /* while loop ends */
#if(PDUR_MULTICAST_TO_IF_SUPPORT == 1)
            if(flg == TRUE)
            {
                tablePtr--;  /* Iterate for next table entry. */
                PduR_MC_SetTxConfirmationFlag(tablePtr->upLayerSymName ,tablePtr->upSrcLayerName);
            }
#endif
            if (cnt_Not_Ok > 0)
            {
                rtn = E_NOT_OK;
            }
    }
    return rtn;
}

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
 * PduR_MF_CancelTransmit_UpToLo
 *      Support function to handle Cancel Transmission request for multicast routes
 *
 * \param           PduR_MT_UpToLo upToLoTable: Multicast routing table
 *                  PduIdType mcId            :ID of I-PDU to be transmitted.
 *
 * \retval          E_OK, E_NOT_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_CancelTransmit_UpToLo(P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) upToLoTable,
                                                 VAR(PduIdType, AUTOMATIC) mcId)
{
    P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST) tablePtr = upToLoTable;
    VAR(Std_ReturnType, AUTOMATIC) rtn = E_NOT_OK;
    VAR(uint8, AUTOMATIC) cnt_Not_Ok = 0;

    /* check for tablePtr */
    if(upToLoTable != NULL_PTR)
    {
           /*Table ptr is incremented till indexes to the expected Mc_GwToLo table entry*/
            while(tablePtr->upId < mcId)
            {
                tablePtr++;
            }
            while (tablePtr->upId == mcId)
            {
                #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)

                   /* Below check is to perform routing if it is configured and enabled. */
                if ((tablePtr->routingCntrl_Idx == PDUR_RPGID_NULL)   ||  /* Routing control is not required.*/
                    ((PDUR_RPG_ENROUTING_INFO(tablePtr->routingCntrl_Idx)) != FALSE ))   /* Routing is enabled or not */
                #endif
                {
                    #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                    rtn = PDUR_BASE_RPTBL(loCnclTxTablePtr)[tablePtr->upToLo.loCancelTransmitID].PduR_loCancelTransmitFunc(tablePtr->upToLo.loId);
                    #else
                    rtn = PduR_loCancelTransmitTable[tablePtr->upToLo.loCancelTransmitID].PduR_loCancelTransmitFunc(tablePtr->upToLo.loId);
                    #endif
                    if (rtn != E_OK)
                    {
                        cnt_Not_Ok++;
                    }
                }
                tablePtr++;  /* Iterate for next table entry. */
            }  /* while loop ends */

            if (cnt_Not_Ok > 0)
            {
                rtn = E_NOT_OK;
            }
    }
    return rtn;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

