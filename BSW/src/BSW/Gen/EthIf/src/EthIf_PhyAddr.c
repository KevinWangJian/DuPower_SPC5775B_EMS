
#include "EthIf.h"

#ifdef ETHIF_CONFIGURED

#include "Eth.h"
#include "EthIf_Prv.h"
#include "rba_BswSrv.h"


 #if( ETHIF_UPDATE_PHYS_ADDR_FILTER_SUPPORT == STD_ON )

 /**
 ***************************************************************************************************
  * This array is the virtual address filter
  * Design Decisions:
  *	1. This is a global static array because it is not desirable to allow direct access to it outside the file
  * 2. In order to save memory, there is only one Array which is shared among the configured HW Eth controllers
  * 3. Its size is configurable and MUST NOT be greater than capacity of physical address filters
  */

#define ETHIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthIf_MemMap.h"
 static EthIf_PhysAddrFilterRefCounterType EthIf_Prv_PhysAddrFilterRefCounters[ETHIF_SIZE_OF_CONFIGURED_FILTERS] = {0};
#define ETHIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"

 /**
 *****************************************************************************************************************************************************************************
  * EthIf_Prv_FindAndUpdatePhysAddrFilterReference: This static function manages the reference counter of the existing filters as follows:
  *			Increments the reference counter each time upper layers call the EthIf_UpdatePhysAddrFilter and the MAC filter is already set for the provided physical ctrl index,
  *			Decrements the reference counters each time UL call the EthIf_UpdatePhysAddrFilter and the MAC filter is already set for the provided physical ctrl index,
  *
  *  What it does:
  *  1. Iterates over the EthIf_Prv_PhysAddrFilterRefCounters` elements and tries to find a valid filter element for the supplied MAC address and Eth physical controller index.
  *     A valid element can be found only if all of the following conditions are met:
  *			- element.HardwareControllerIndex_u8 ==  PhysCtrlIdx_u8   AND
  *			- element.ReferenceCounter_u32 > 0 (that is: the filter is valid and added in the driver`s filter) AND
  *			- element.PhysicalAddress_u8 matches the provided as argument physical address (PhysAddrPtr_pcu8)
  *
  *  1.1 IF such element has NOT been found, then RETURNS E_NOT_OK because the filter is not present in the eth driver`s addresses filter
  *  1.2 IF such element has been found, then continues with step 2
  *
  *	 2. Checks the desied ACTION (which can be ADD or REMOVE)
  *  2.1 IF the required action is ADD to filter, then increments the reference counter
  *	 2.2 ELSE IF the required action is REMOVE from filter, then decrements the reference counter
  *  3. updates the output parameter `NewReferenceCounter_u32` which represents the reference counter for the current MAC filter reference
  *
  * Design Decisions:
  * 1. This function is static because it is not necessary to expose it outside this unit/file.
  * 2. Critical sections are not required because the virtual addr filters are not called for various ETH controllers at the same time.
  *
  * Parameter In:
  *	/PhysCtrlIdx_u8: Index of the Ethernet controller within the context of the Ethernet Driver
  * /PhysAddrPtr_pcu8: Physical source address (MAC address) in network byte order. Please refer to [16] for the physical source address specification.
  * /ActionType_st: Add or remove the address from the filter.
  *
  * Parameter Out: NewReferenceCounter_u32: Current reference counter of the modified entry within the virtual filter
  *
  * \return  E_OK:     The pair: {PhysCtrlIdx_u8, PhysAddrPtr_pcu8} could be found in the virtual address filter and the pair is valid (has the reference counter greater than 0)
  *                    E_OK is also returned when ActionType_st is invalid.
  *          E_NOT_OK: The pair: {PhysCtrlIdx_u8, PhysAddrPtr_pcu8} could NOT be found in the virtual address filter. In this case it must be allocated. This is not a DET error.
  *
  *****************************************************************************************************************************************************************************
  **/
static FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_FindAndUpdatePhysAddrFilterReference( VAR( uint8, AUTOMATIC ) PhysCtrlIdx_u8,
																							P2CONST( uint8, AUTOMATIC, AUTOMATIC ) PhysAddrPtr_pcu8,
																							P2VAR( uint32, AUTOMATIC, AUTOMATIC ) NewReferenceCounter_u32,
																							VAR( Eth_FilterActionType, AUTOMATIC ) ActionType_st
																							)
{
	Std_ReturnType  result = E_OK;
	uint8* 			localPhysAddrPointer_pu8 = NULL_PTR;
	uint8			localCtrlIdx_pu8 = 0U;
	uint32 			localReferenceCounter_u32 = 0U;
	uint32          index_u32 = 0U;
	EthIf_PhysAddrFilterRefCounterType* localPhysAddrFilterRefCounter_pst =  NULL_PTR;

	/* Iterates over the EthIf_Prv_PhysAddrFilterRefCounters` elements and tries to find a valid filter element for the supplied MAC address and Eth physical controller index. */
	for (index_u32 = 0U; index_u32 < ETHIF_SIZE_OF_CONFIGURED_FILTERS; index_u32++)
	{
		localPhysAddrPointer_pu8  = (uint8*) (EthIf_Prv_PhysAddrFilterRefCounters[index_u32].PhysicalAddress_u8);
		localCtrlIdx_pu8 = EthIf_Prv_PhysAddrFilterRefCounters[index_u32].HardwareControllerIndex_u8;
		localReferenceCounter_u32 = EthIf_Prv_PhysAddrFilterRefCounters[index_u32].ReferenceCounter_u32;

		/*  A valid entry can be found only if the following pair {PhysCtrlIdx_u8, PhysAddrPtr_pcu8} exists in the virtual filter and its reference counter is greater than 0 */
		if ( (localCtrlIdx_pu8 == PhysCtrlIdx_u8) && (localReferenceCounter_u32 > 0U) )
		{
			if (rba_BswSrv_MemCompare8(localPhysAddrPointer_pu8 , PhysAddrPtr_pcu8, 6U) == 0U)
			{
				localPhysAddrFilterRefCounter_pst = &(EthIf_Prv_PhysAddrFilterRefCounters[index_u32]);
				break;
			}
			else { /* do nothing */ }
		}
		else { /* do nothing */ }
	}

	/* a valid entry could be found in the virtual address filter */
	if (localPhysAddrFilterRefCounter_pst != NULL_PTR)
	{
		/* increments the reference counter because this entry already exists in the virtual address filter */
		if (ETH_ADD_TO_FILTER == ActionType_st)
		{
			localPhysAddrFilterRefCounter_pst-> ReferenceCounter_u32 ++;
		}
		/* decrements the reference counter  */
		else if (ETH_REMOVE_FROM_FILTER == ActionType_st)
		{
			localPhysAddrFilterRefCounter_pst-> ReferenceCounter_u32 --;
		}
		else { /* do nothing */ }

		/* Store the current reference counter of the modified entry into out parameter: NewReferenceCounter_u32 */
		(*NewReferenceCounter_u32) = localPhysAddrFilterRefCounter_pst->ReferenceCounter_u32;
	}
	/* a valid entry could not be found in the virtual address filter */
	else
	{
		result = E_NOT_OK;
	}

	return result;
}

/**
 *****************************************************************************************************************************************
  * EthIf_AllocateNewPhysAddrFilterReference: allocates filters in the EthIf_Prv_PhysAddrFilterRefCounters array.
  *	   This function is called by the EthIf_UpdatePhysAddrFilter, only if the requested action is ADD to filter an the provided MAC
  *			addres could not be found in the Physical address filter.
  *
  *	What it does:
  *
  *  1. Iterates over the EthIf_Prv_PhysAddrFilterRefCounters` elements and tries to find an empty/not used element.
  *      Note: An empty/not used element is any element having the ReferenceCounter_u32 set to 0
  *
  *	 1.1. IF such element could not be found, returns E_NOT_OK because the filter is full.
  *	 1.2 ELSE continues with step 2
  *  2. Sets the the following fields:
  *		- element.ReferenceCounter_u32 to 1
  *		- element.HardwareControllerIndex_u8 to  PhysCtrlIdx_u8
  *		- copies the provided physical address (PhysAddrPtr_pcu8)  into element.PhysicalAddress_u8
  *
  *
  * Design Decisions:
  * 1. This function is static because it is not necessary to expose it outside this unit/file.
  * 2. Critical sections are not required because the virtual addr filters are not called for various ETH controllers at the same time.
  *
  * Parameter In:
  *	/PhysCtrlIdx_u8: Index of the Ethernet controller within the context of the Ethernet Driver
  * /PhysAddrPtr_pcu8: Physical source address (MAC address) in network byte order. Please refer to [16] for the physical source address specification.
  *
  * Parameter Out: None
  *
  * \return  E_OK:     an empty filter could be found, and the provided PhysAddrPtr_pcu8 is stored
  *          E_NOT_OK: the virtual filter is full, therefore the provided PhysAddrPtr_pcu8 could not be stored
  *
  ******************************************************************************************************************************************
  **/
static FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_AllocateNewPhysAddrFilterReference(VAR( uint8, AUTOMATIC ) PhysCtrlIdx_u8,
																					 P2CONST( uint8, AUTOMATIC, AUTOMATIC ) PhysAddrPtr_pcu8)
{
	Std_ReturnType		result = E_OK;

	uint32				index_u32 = 0U;
	EthIf_PhysAddrFilterRefCounterType* localPhysAddrFilterRefCounter_pst =  NULL_PTR;

	/* Iterates over the EthIf_Prv_PhysAddrFilterRefCounters` elements and tries to find an empty/not used entry. An empty/not used entry is any element having the ReferenceCounter_u32 set to 0 */
	for (index_u32 = 0U; index_u32 < ETHIF_SIZE_OF_CONFIGURED_FILTERS; index_u32 ++)
	{
		localPhysAddrFilterRefCounter_pst = &(EthIf_Prv_PhysAddrFilterRefCounters[index_u32]);
		/* If an empty/not used entry could be found, then: */
		if (localPhysAddrFilterRefCounter_pst->ReferenceCounter_u32 == 0U)
		{
			/* marks the current entry as valid by setting the reference counter to 1*/
			localPhysAddrFilterRefCounter_pst->ReferenceCounter_u32 = 1U;
			/* stores the physical Eth Controller index into the current entry */
			localPhysAddrFilterRefCounter_pst->HardwareControllerIndex_u8 = PhysCtrlIdx_u8;
			/* copies the provided physical address into the current entry */
			rba_BswSrv_MemCopy8(localPhysAddrFilterRefCounter_pst->PhysicalAddress_u8, PhysAddrPtr_pcu8, 6U);

			break;
		}
	}
	/* an invalid/empty slot could not be found */
	if (index_u32 == ETHIF_SIZE_OF_CONFIGURED_FILTERS)
	{
		result = E_NOT_OK;
	}
	return result;
}


/**
 ******************************************************************************************************************************************
 * This function must be called by the EthIf_Prv_SetControllerMode function, before setting the eth controller to ETHCTRL_MODE_ACTIVE.
 *
 * What it does:
 *	It clears the physical address filters for the specified physical eth controller index.
 *
 * Design Decisions:
 * 1. Critical sections are not required because the virtual addr filters are not called for various ETH controllers at the same time.
 *
 * Parameter In:
 *	/PhysCtrlIdx_u8: Index of the Ethernet controller within the context of the Ethernet Driver
 *
 * Parameter Out: None
 *
 * \return  None
 *
 ******************************************************************************************************************************************
 **/
FUNC (void, RBA_ETHIF_CODE) EthIf_Prv_ResetPhysAddrFilterReferencesForEthHwCtrlIdx(VAR( uint8, AUTOMATIC ) PhysCtrlIdx_u8)
{
	uint32 index_u32 = 0U;

	/* Interates over the virtual filter entries and deallocates all the physical addresses for the specified physical controller index(PhysCtrlIdx_u8) */
	for (index_u32 = 0; index_u32 < ETHIF_SIZE_OF_CONFIGURED_FILTERS; index_u32++)
	{
		if (EthIf_Prv_PhysAddrFilterRefCounters[index_u32].HardwareControllerIndex_u8 == PhysCtrlIdx_u8)
		{
			/* Deallocates the current entry by setting the ReferenceCounter_u32 to 0 */
			EthIf_Prv_PhysAddrFilterRefCounters[index_u32].ReferenceCounter_u32 = 0;
		}
	}
}

/**
 ******************************************************************************************************************************************
 * This function must be called by the EthIf_Init.
 *
 * What it does:
 *	It clears the physical address filters for all configured physical controllers.
 *
 * Design Decisions:
 * 1. Critical sections are not required because the virtual addr filters are not called for various ETH controllers at the same time.
 *
 * Parameter In: None
 *
 * Parameter Out: None
 *
 * \return  None
 *
 ******************************************************************************************************************************************
 **/
FUNC (void, RBA_ETHIF_CODE) EthIf_Prv_ResetPhysAddrFilterReferences(void)
{
	uint32  index_u32 = 0U;

	/* Interates over the virtual filter entries and deallocates all physical addresses  */
	for (index_u32 = 0; index_u32 < ETHIF_SIZE_OF_CONFIGURED_FILTERS; index_u32++)
	{
		/* Deallocates the current entry by setting the ReferenceCounter_u32 to 0 */
		EthIf_Prv_PhysAddrFilterRefCounters[index_u32].ReferenceCounter_u32 = 0;
	}
}

#endif


/**
 ***************************************************************************************************
 * \module description
 * ETHIF061: Obtains the physical source address used by the indexed controller
 * \par Service ID 0x08, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx       Index of the Ethernet controller within the context of the Ethernet Interface
 *
 * Parameter Out:
 * \param PhysAddrPtr   Physical source address (MAC address) in network byte order.
 * Please refer to [16] for the physical source address specification.
 *
 * \return  None
 *
 ***************************************************************************************************
 */

 FUNC(void, RBA_ETHIF_CODE) EthIf_GetPhysAddr(   VAR( uint8,     AUTOMATIC )             CtrlIdx,
                                                P2VAR( uint8,   AUTOMATIC, AUTOMATIC )  PhysAddrPtr )
{
    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_GETPHYSADDR, ETHIF_E_NOT_INITIALIZED )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VOID( ( ( CtrlIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ),    \
                                   ETHIF_SID_ETHIF_GETPHYSADDR,                                                    \
                                   ETHIF_E_INV_CTRL_IDX )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VOID( (NULL_PTR == PhysAddrPtr ), ETHIF_SID_ETHIF_GETPHYSADDR, ETHIF_E_PARAM_POINTER )

    Eth_GetPhysAddr(    ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 ),
                        PhysAddrPtr );

    return;
}

/**
 ***************************************************************************************************
 * \module description
 * ETHIF139:Update the physical source address to/from the indexed controller filter.
 *          If the Ethernet Controller is not capable to do the filtering, the software has to do this.
 * \par Service ID 0x0c, Synchronous, Non Reentrant for the same CtrlIdx, reentrant for different
 *
 *
 * How it does:
 * I. If the requested action is ADD, then performs the following steps:
 *	1.  It tries to find and increment the retain count of an existing filter for the supplied physical controller index and MAC address by calling
 *				EthIf_Prv_FindAndUpdatePhysAddrFilterReference(..., ..., ETH_ADD_TO_FILTER)
 * 	1.1 IF such filter could be found, then returns E_OK because the filter already exists.
 *  1.2 ELSE IF such filter could not be found, then continues with step 2
 *	2. Calls the Eth_UpdatePhysAddrFilter function to insert the filter into the HW buffer
 *  2.1 IF this operation fails (HW filter full, or other error), then returns E_NOT_OK
 *	2.2 ELSE allocates an alement into the virtual filter  by calling EthIf_Prv_AllocateNewPhysAddrFilterReference
 * If the above mentioned function succeeds, then returns E_OK, else E_NOT_OK
 *
 * II. If the requested action is REMOVE, then performs the following steps:
 *	1.  It tries to find and decrement the retain count of an existing filter for the supplied physical controller index and MAC address by calling
 *				EthIf_Prv_FindAndUpdatePhysAddrFilterReference(..., ..., ETH_REMOVE_FROM_FILTER)
 *	1.1 IF such element could not be found (does not exist in the virtual and physical filter), reports DET error(ETHIF_E_INV_PARAM) then returns E_NOT_OK
 *  1.2 ELSE continues with step 2
 *  2. IF the updated reference counter equal 0, then the element must be removed from the HW filter. In order to do this,
 *			the Eth_UpdatePhysAddrFilter function is called. The return value is given by this function as follows:
 *							E_OK -  means that the filter could be removed from the HW registers
 *							E_NOT_OK - means that the filter could not be found in the HW filter. In this case DET error(ETHIF_E_INV_PARAM) must be reported.
 * 3. ELSE IF reference counter is not 0, returns E_OK because the refererence count was previously decremented by the EthIf_Prv_FindAndUpdatePhysAddrFilterReference
 *			function.
 *
 * Parameter In:
 * \param CtrlIdx      Index of the Ethernet controller within the context of the Ethernet Driver.
 * \param PhysAddrPtr  Pointer to memory containing the physical source address (MAC address) in network byte order.
 * \param Action       Add or remove the address from the Ethernet controllers filter.
 *
 * \return  E_OK:     filter was successfully changed
 *          E_NOT_OK: filter could not be changed
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_UpdatePhysAddrFilter(    VAR( uint8,                     AUTOMATIC )             CtrlIdx,
                                                                    P2CONST( uint8,                 AUTOMATIC, AUTOMATIC )  PhysAddrPtr,
                                                                    VAR( Eth_FilterActionType,      AUTOMATIC )             Action )
{
    /* Local variables declaration */
    Std_ReturnType     lResult_en;

#if( ETHIF_UPDATE_PHYS_ADDR_FILTER_SUPPORT == STD_ON )

    uint8              lEthCtrlIdx_u8;
	uint32             newReferenceCounter_u32;

    lResult_en      = E_NOT_OK;
    lEthCtrlIdx_u8  = 0xFF;

	/* Report DET : Development Error: Module not initialised */
	ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_UPDATE_PHYSADDRFILTER,  \
								    ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

	/* Report DET : Development Error: CtrlIdx is not valid */
	ETHIF_REPORT_ERROR_RET_VALUE( ( ( CtrlIdx + 1 ) > ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ),     \
									ETHIF_SID_ETHIF_UPDATE_PHYSADDRFILTER,                                               \
									ETHIF_E_INV_CTRL_IDX, E_NOT_OK )

	/* Report DET : Development Error for Invalid Configuration Pointer */
	ETHIF_REPORT_ERROR_RET_VALUE( ( PhysAddrPtr == NULL_PTR ), ETHIF_SID_ETHIF_UPDATE_PHYSADDRFILTER, ETHIF_E_PARAM_POINTER, E_NOT_OK )

	/* Read out CtrlIdx from configuration */
	lEthCtrlIdx_u8  = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

	lResult_en = EthIf_Prv_FindAndUpdatePhysAddrFilterReference( lEthCtrlIdx_u8, PhysAddrPtr, &newReferenceCounter_u32, Action);

	/* The selected action is `ADD to filter` */
	if (ETH_ADD_TO_FILTER == Action)
	{
		/* The provided physical address is added into the Eth Driver only if the entry could not be found in the virtual filter */
		if (E_NOT_OK == lResult_en)
		{
			lResult_en = Eth_UpdatePhysAddrFilter( lEthCtrlIdx_u8, PhysAddrPtr, Action );
			if (E_OK == lResult_en)
			{
				lResult_en = EthIf_Prv_AllocateNewPhysAddrFilterReference(lEthCtrlIdx_u8, PhysAddrPtr);
			}
			else { /* Nothing to do because lResult_en has already been set to E_NOT_OK */  }

		}
		else { /* Nothing to do because the address already exists in the filter and the counter for the specified physical address is already incremented */ }
	}
	/* The selected action is `REMOVE from filter` */
	else if (ETH_REMOVE_FROM_FILTER == Action)
	{
		/* The actual removal from the HW filter takes place when the reference counter becomes 0 after several deallocation actions */
		if (E_OK == lResult_en)
		{
			if (newReferenceCounter_u32 == 0U)
			{
				lResult_en = Eth_UpdatePhysAddrFilter( lEthCtrlIdx_u8, PhysAddrPtr, Action );
			}
			else { /* Nothing to do because the reference counter was already decremented */ }
		}
		else { /* Nothing to do because lResult_en has already been set to E_NOT_OK */  }

		/* Report DET : Development Error as UL should NOT call this API for non existing addresses. */
		ETHIF_REPORT_ERROR_RET_VALUE( ( lResult_en == E_NOT_OK ), ETHIF_SID_ETHIF_UPDATE_PHYSADDRFILTER, ETHIF_E_INV_PARAM, E_NOT_OK )
	}
	else
	{
	    lResult_en = E_NOT_OK;
	}


#else
	(void)CtrlIdx;
	(void)PhysAddrPtr;
	(void)Action;
	lResult_en = E_NOT_OK;
#endif

    return ( lResult_en );
}

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"
#endif /* ETHIF_CONFIGURED */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
