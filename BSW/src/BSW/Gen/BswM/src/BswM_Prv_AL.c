

/*---------------------------------------------------------------------------------------*/
/*- Include files                                                                       -*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_Prv.h"
#include "BswM_PBcfg.h"

/*****************************************************************************************
* Function name :   FUNC(void, BSWM_CODE) BswM_Prv_Evaluate_ActionList(P2CONST(BswM_Cfg_ActionListType_tst, AUTOMATIC , BSWM_APPL_CONST) dataActionList_pst)
* Description   :   This function is called by BswM_Prv_Arbitrate_Rule to execute the true/false Actionlist.
* Parameter dataActionList_st   :   This parameter pointer to structure that holds all the information needed for executing Actionlist.
* Return value  :   None
* Remarks       :
*****************************************************************************************/
#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

FUNC(void, BSWM_CODE) BswM_Prv_Evaluate_ActionList
(
    P2CONST(BswM_Cfg_ActionListType_tst, AUTOMATIC ,BSWM_APPL_CONST) dataActionList_pst
)
{
/* Check if any Rule is configured in the Project? */
#ifdef BSWM_MAX_NO_OF_RULES

    VAR(boolean, AUTOMATIC)    isExitOnAbortFlag_b = FALSE;
    VAR(uint16, AUTOMATIC)    hasIndex_u16 = 0;
    VAR(Std_ReturnType, AUTOMATIC)    isActionRet_u8 = E_NOT_OK;
    P2CONST(BswM_Cfg_ActionListItemType_tst, AUTOMATIC ,BSWM_APPL_CONST)    dataActionListItem_pst = NULL_PTR ;

    /* Loop through all the members of ActionList */
    for (hasIndex_u16 = 0; hasIndex_u16 < dataActionList_pst->nrActionListItems_u8; hasIndex_u16++)
    {
         dataActionListItem_pst = &dataActionList_pst->adrActionListItem_pst[hasIndex_u16];

         /* Check if the member of ActionList is refrence to another ACIONLIST */
         if (dataActionListItem_pst->dataActionListItemType_en == BSWM_ACTIONLIST)
         {
#if (defined(BSWM_TOTAL_NO_OF_ACTIONLIST) && (BSWM_TOTAL_NO_OF_ACTIONLIST > 0))
             if (FALSE == BswM_isMultipleActionListTriggered_ab[dataActionList_pst->idxActionListnum])
             {
                 BswM_Prv_Evaluate_ActionList((const BswM_Cfg_ActionListType_tst *)(dataActionListItem_pst->adrActionListItemRef_pv));
                 BswM_isMultipleActionListTriggered_ab[dataActionList_pst->idxActionListnum] = TRUE;
             }
             else
             {
               /* Do nothing */
             }
#endif
         }
         /* Check if the member of ActionList is refrence to any ACION */
         else
         {
              isActionRet_u8 = BswM_Prv_Evaluate_Action(dataActionListItem_pst->adrActionListItemRef_pv, dataActionListItem_pst->dataActionListItemType_en);
              /* Check if the action returns E_NOT_OK and is configured for AbortOnFail as TRUE */
              if ((dataActionListItem_pst->isActionListAbortOnFail_b) && (isActionRet_u8 == E_NOT_OK))
              {
                   isExitOnAbortFlag_b = TRUE;
              }

              if (dataActionList_pst->nrActionListItems_u8 == (hasIndex_u16 + 1))
              {
#if (defined(BSWM_TOTAL_NO_OF_ACTIONLIST) && (BSWM_TOTAL_NO_OF_ACTIONLIST > 0))
                  BswM_isMultipleActionListTriggered_ab[dataActionList_pst->idxActionListnum] = TRUE;
#endif
              }
              else
              {
                  /* Do nothing */
              }

         }
        /* Check if break from looping to next member of ActionList*/
        if(isExitOnAbortFlag_b)
        {
             break;
        }
    }


#else
    (void)dataActionList_pst;
#endif
    return;
}
#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"
/**********************************************************************************************************************
 *
 **********************************************************************************************************************/
