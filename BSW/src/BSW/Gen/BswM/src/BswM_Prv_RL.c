

/*---------------------------------------------------------------------------------------*/
/*- Include files                                                                       -*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_PBcfg.h"
#include "BswM_Prv.h"

/*---------------------------------------------------------------------------------------*/
/*- Definition of Global Variables                                                      -*/
/*---------------------------------------------------------------------------------------*/

/*****************************************************************************************
 * Function name :FUNC(void, BSWM_CODE) BswM_Prv_Evaluate_Rule (P2CONST(BswM_Cfg_RuleType_tst, AUTOMATIC,BSWM_APPL_CONST) dataRule_pst,VAR(uint16, AUTOMATIC) idxRule_u16)
 * Description   :This function is called by BswM_Prv_Arbitrate_Rule to evaluate the rule based on logical conditions binding the modeconditions.
 * Parameter dataRule_st : Pointer to Rule structure associated with rule index .
 * Parameter dataRuleIndex_u16 : Rule Index.
 * Return value  :None
 * Remarks       :
 *****************************************************************************************/
#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

FUNC(void, BSWM_CODE) BswM_Prv_Evaluate_Rule
(
    P2CONST(BswM_Cfg_RuleType_tst, AUTOMATIC,BSWM_APPL_CONST) dataRule_pst,
    VAR(uint16, AUTOMATIC) idxRule_u16
)
{

/* Check if any Rule is configured in the Project? */
#ifdef BSWM_MAX_NO_OF_RULES
    VAR(boolean, AUTOMATIC) isValidMode_b = FALSE;
    VAR(boolean, AUTOMATIC) isEvalResult_b = FALSE;
    /* Check if refrence to logical Expression is not pointing to NULL_PTR */
        /* Evaluate Logical Expression */
        (void) dataRule_pst->adrlogExp_pfct(&isValidMode_b, &isEvalResult_b);
        /* Check if the mode conditions are valid */
        if (isValidMode_b)
        {
            /* Check if the logical expression is evaluated to TRUE */
            if (isEvalResult_b)
            {
                /* Evaluate True ActionList when Pointer to True action list is not invalid*/
                if(dataRule_pst->adrTrueAL_pst != NULL_PTR)
                {
                    if((dataRule_pst->adrTrueAL_pst->dataActionListExecutionType_en == BSWM_CONDITION)   ||
                    ((dataRule_pst->adrTrueAL_pst->dataActionListExecutionType_en == BSWM_TRIGGER)    &&
                    (BswM_Prv_RuleState_aen[idxRule_u16] != BSWM_TRUE)))
                    {
                        /*Call Evaulate True actionlist if rule is evaluated to true */
                        BswM_Prv_Evaluate_ActionList(dataRule_pst->adrTrueAL_pst);
                    }
                }
                /* Update RuleInitState Flag to TRUE*/
                BswM_Prv_RuleState_aen[idxRule_u16] = BSWM_TRUE;
            }
            /* Check if the logical expression is evaluated to FALSE */
            else
            {
                /* Evaluate False ActionList when Pointer to False action list is not invalid*/
                if (dataRule_pst->adrFalseAL_pst != NULL_PTR)
                {
                    if((dataRule_pst->adrFalseAL_pst->dataActionListExecutionType_en == BSWM_CONDITION)  ||
                    ((dataRule_pst->adrFalseAL_pst->dataActionListExecutionType_en == BSWM_TRIGGER)   &&
                    (BswM_Prv_RuleState_aen[idxRule_u16] != BSWM_FALSE)))
                    {
                        /*Call Evaulate FALSE actionlist if rule is evaluated to false */
                        BswM_Prv_Evaluate_ActionList(dataRule_pst->adrFalseAL_pst);
                    }
                }
                /* Update RuleInitState Flag to FALSE */
                BswM_Prv_RuleState_aen[idxRule_u16] = BSWM_FALSE;
            }
        }
        else
        {
            /* Mode Conditions are not defined, dont do anything and return */
        }


#else /* If no rule is configured in the project and If variables are not used*/
    (void)dataRule_pst;
    (void)idxRule_u16;
#endif
    return;
}


/*****************************************************************************************
 * Function name : FUNC(void, BSWM_CODE) BswM_Prv_Arbitrate_Rule(VAR(uint16, AUTOMATIC) nrOfAssociatedRules_u16,P2CONST(uint16, AUTOMATIC, BSWM_APPL_CONST) ruleRef_pu16)
 * Description   :Function is called by ModeRequest API for evaluating the rules associated with particular MRPType and MRPId
 * Parameter nrOfAssociatedRules_u16 : Number of rules associated with the particular MRPType and MRPId.
 * Parameter ruleRef_pu16 : The pointer to the array of Rule Index.
 * Return value  :None
 * Remarks       :
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Prv_Arbitrate_Rule
(
    VAR(uint16, AUTOMATIC) nrOfAssociatedRules_u16,
    P2CONST(uint16, BSWM_VAR, BSWM_APPL_CONST) ruleRef_pu16
)
{
/* Check if any Rule is configured in the Project? */
#ifdef BSWM_MAX_NO_OF_RULES


    P2CONST(BswM_Cfg_RuleType_tst, AUTOMATIC ,BSWM_APPL_CONST) dataRule_pst = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.adrArbitrationRule_pst;
    VAR(uint16, AUTOMATIC ) idxRule_u16;
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    /*Check if ref to array of rule index is Configured is valid*/
    if(NULL_PTR !=ruleRef_pu16)
    {
        /*Check if Any Rule is Configured for passed config structure */
        if (NULL_PTR != dataRule_pst)
        {
            /*Execute ActionList for DIFERRED context*/
            for (idx_u16 = 0; idx_u16 < BSWM_TOTAL_NO_OF_ACTIONLIST; idx_u16++)
            {
#if (defined(BSWM_TOTAL_NO_OF_ACTIONLIST) && (BSWM_TOTAL_NO_OF_ACTIONLIST > 0))
                BswM_isMultipleActionListTriggered_ab[idx_u16] = FALSE;
#endif
            }

            /*Loop till all the no of associated rule with a particular MRPType and MRPId is evaluated */
            for (idx_u16 = 0; idx_u16 < nrOfAssociatedRules_u16; idx_u16++)
            {
                /* Get the index of rule from the array of RuleIndex */
                idxRule_u16 = ruleRef_pu16[idx_u16];
                /* Call Evaulate rule to evaluate each rule with that index */
                BswM_Prv_Evaluate_Rule( &dataRule_pst[idxRule_u16], idxRule_u16);
            }
        }
    }
    else
    {
        /*  Do Nothing */
    }

#else /* If no rule is configured in the project and If variables are not used*/
    (void)nrOfAssociatedRules_u16;
    (void)ruleRef_pu16;
#endif
    return;
}
#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/**********************************************************************************************************************
 *
 **********************************************************************************************************************/
/*******************************EOD*******************************************************************/
