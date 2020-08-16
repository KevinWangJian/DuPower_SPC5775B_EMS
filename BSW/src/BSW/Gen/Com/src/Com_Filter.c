

/*********************************************************************************************************************
* Preprocessor includes
*********************************************************************************************************************/
#include "Com_Priv.h"

/*********************************************************************************************************************
* Global functions (declared in header files )
*********************************************************************************************************************/

/*********************************************************************************************************************
 Function name    : Com_Filter
 Syntax           : boolean Com_Filter(uint32 NewVal,uint8 Algorithm,Com_FilterType FilterIndex,boolean CallContext_b)
 Description      : Service used for filtering the signal depending on the conditions
 Parameter        : Algorithm -> Filter type
                  : NewVal  -> New value for filtering
                  : FilterIndex -> Filter Index
                  : CallContext_b -> Whether to increment occurrence for ONE_EVERYN filters
 Return value     : COM_TRUE/COM_FALSE
*********************************************************************************************************************/

#if (defined(COM_TxFilters) || defined(COM_RxFilters))
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean, COM_CODE) Com_Filter( VAR(uint32, AUTOMATIC) NewVal, VAR(uint8, AUTOMATIC) Algorithm,
                                    VAR(Com_FilterType, AUTOMATIC) FilterIndex, VAR(boolean,AUTOMATIC) CallContext_b )
{
    VAR(boolean, AUTOMATIC) State;
    State = COM_FALSE;

#ifndef COM_F_ONEEVERYN
    (void)CallContext_b;
#endif
    switch(Algorithm)
    {
        case COM_ALWAYS:
            State = COM_TRUE;
            break;
        case COM_NEVER:
            /* State = COM_FALSE; */
            break;

#ifdef COM_F_MASKEDNEWEQUALSX
        case COM_MASKED_NEW_EQUALS_X:
            if((NewVal & COM_GET_MASK_X(FilterIndex).Mask)
                         == COM_GET_MASK_X(FilterIndex).X_Val)
            {
                State = COM_TRUE;
            }
            break;

#endif /* #ifdef COM_F_MASKEDNEWEQUALSX */

#ifdef COM_F_MASKEDNEWDIFFERSX
        case COM_MASKED_NEW_DIFFERS_X:
            if((NewVal & COM_GET_MASK_X(FilterIndex).Mask)
                 != COM_GET_MASK_X(FilterIndex).X_Val)
            {
                State = COM_TRUE;
            }
            break;
#endif /* #ifdef COM_F_MASKEDNEWDIFFERSX */

#ifdef COM_F_MASKEDNEWDIFFERSOLD
        case COM_MASKED_NEW_DIFFERS_MASKED_OLD:
            if((NewVal & COM_GET_MASK(FilterIndex)) !=
                        (COM_GET_F_OLDVALUE(FilterIndex) & COM_GET_MASK(FilterIndex)))
            {
                State = COM_TRUE;
            }
            break;
#endif /* COM_F_MASKEDNEWDIFFERSOLD */

#ifdef COM_F_NEWISWITHIN_POS
        case COM_NEW_IS_WITHIN_POS:
            if((COM_GET_POSMINMAX(FilterIndex).Min <= NewVal) &&
                    (NewVal <= COM_GET_POSMINMAX(FilterIndex).Max))
            {
                State = COM_TRUE;
            }
            break;
#endif /* #ifdef COM_F_NEWISWITHIN_POS */

#ifdef COM_F_NEWISWITHIN_NEG
        case COM_NEW_IS_WITHIN_NEG:
            if((COM_GET_NEGMINMAX(FilterIndex).Min <= (sint32)NewVal) &&
                    ((sint32)NewVal <= COM_GET_NEGMINMAX(FilterIndex).Max))
            {
                State = COM_TRUE;
            }
            break;
#endif /* #ifdef COM_F_NEWISWITHIN_NEG */

#ifdef COM_F_NEWISOUTSIDE_POS
        case COM_NEW_IS_OUTSIDE_POS:
            if((NewVal < COM_GET_POSMINMAX(FilterIndex).Min) ||
                (NewVal > COM_GET_POSMINMAX(FilterIndex).Max))
            {
                State = COM_TRUE;
            }
            break;
#endif /* #ifdef COM_F_NEWISOUTSIDE_POS */

#ifdef COM_F_NEWISOUTSIDE_NEG
        case COM_NEW_IS_OUTSIDE_NEG:
            if(((sint32)NewVal < COM_GET_NEGMINMAX(FilterIndex).Min) ||
                ((sint32)NewVal > COM_GET_NEGMINMAX(FilterIndex).Max))
            {
                State = COM_TRUE;
            }
            break;
#endif /* #ifdef COM_F_NEWISOUTSIDE_NEG */

#ifdef COM_F_ONEEVERYN
        case COM_ONE_EVERY_N:
            if(COM_GET_ONEEVERYN(FilterIndex).Occurrence == COM_GET_ONEEVERYN(FilterIndex).Offset)
            {
                State = COM_TRUE;
            }
            /* NOTE on CallContext_b:
             * 1.Currently the values for the parameter CallContext_b are COM_TRUE/COM_FALSE
             * 2.It is used only for filter ONE_EVERYN */
            if(CallContext_b != COM_FALSE)
            {
                /* Increment Occurrence */
                COM_GET_ONEEVERYN(FilterIndex).Occurrence++;
            }

            if(COM_GET_ONEEVERYN(FilterIndex).Occurrence == COM_GET_ONEEVERYN(FilterIndex).Period)
            {
                /*Reset the Occurrence to 0x00*/
                COM_GET_ONEEVERYN(FilterIndex).Occurrence = 0;
            }
            break;
#endif /* #ifdef COM_F_ONEEVERYN */
        default:
            /**
             * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined filterAlgorithm(s)
             * are allowed to be configured, hence default case is intentionally left empty.
             */
            break;
    }

#ifdef COM_F_MASKEDNEWDIFFERSOLD
    if((State != COM_FALSE) && (Algorithm == COM_MASKED_NEW_DIFFERS_MASKED_OLD))
    {
        /* If Filter evaluates to TRUE then the New_value is placed into Old_Value */
        COM_GET_F_OLDVALUE(FilterIndex) = NewVal;
    }
#endif /* #ifdef COM_F_MASKEDNEWDIFFERSOLD */

    return (State);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #if (defined(COM_TxFilters) || defined(COM_RxFilters)) */

