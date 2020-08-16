

/**
 * \defgroup FIM_TYPES_H
 * The header types for the FiM.
 * @see AUTOSAR_SWS_FunctionInhibitionManager.pdf Version 4.0 Rev0002
 */

#ifndef FIM_TYPES_H
#define FIM_TYPES_H

#include "Std_Types.h"
#include "Rte_FiM_Type.h"

/**
 * @ingroup FIM_TYPES_H
 * Base type for Inhibition Mask.
 *
 */
typedef uint8 FiM_InhibitionMaskType;

/**
 * @ingroup FIM_TYPES_H
 * Base type for Event offsets
 *
 */
typedef uint32 FiM_NumOffsetEventType;

/**
 * @ingroup FIM_TYPES_H
 * Base type for Component offsets
 *
 */
typedef uint32 FiM_NumOffsetComponentType;

/**
 * @ingroup FIM_TYPES_H
 *  typedef struct \n
 *  {\n
 *      const FiM_NumOffsetEventType* FiM_Cfg_NumOffsetEventptr;    	  pointer to a constant array of type FiM_NumOffsetEventType \n
 *      const FiM_FunctionIdType* FiM_CfgInhibitSourceMatrixptr;     	  pointer to a constant array of type FiM_FunctionIdType\n
 *      const FiM_InhibitionMaskType* FiM_CfgInhibitMaskMatrixptr;  	  pointer to a constant array of type FiM_InhibitionMaskType\n
 *      const FiM_NumOffsetComponentType* FiM_Cfg_NumOffsetComponentptr;  pointer to a constant array of type FiM_NumOffsetComponentType \n
 *      const FiM_FunctionIdType* FiM_CfgInhibitSourceMatrixComponentptr; pointer to a constant array of type FiM_FunctionIdType for components\n
 *  }FiM_ConfigType;
 */

typedef struct
{
    const FiM_NumOffsetEventType* FiM_Cfg_NumOffsetEventptr;
    const FiM_FunctionIdType* FiM_CfgInhibitSourceMatrixptr;
    const FiM_InhibitionMaskType* FiM_CfgInhibitMaskMatrixptr;
    const FiM_NumOffsetComponentType* FiM_Cfg_NumOffsetComponentptr;
    const FiM_FunctionIdType* FiM_CfgInhibitSourceMatrixComponentptr;
} FiM_ConfigType;

#endif /* include protection */

