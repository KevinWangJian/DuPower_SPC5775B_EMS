

#include "Fee.h"
#include "Fee_Prv.h"



/* Properties of flash sectors */
#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
CONST (Fee_FlashProp_tst, FEE_CONST) Fee_FlashProp_st[FEE_NUM_FLASH_BANKS_AVAILABLE] = {
	{ FEE_PHYS_SEC_START0, FEE_PHYS_SEC_END0, FEE_LOG_SEC_START0, FEE_LOG_SEC_END0 }, /* sector 0 */
	{ FEE_PHYS_SEC_START1, FEE_PHYS_SEC_END1, FEE_LOG_SEC_START1, FEE_LOG_SEC_END1 }, /* sector 1 */
};
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"

/* Linked functions of the Fee */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
CONST (Fee_LinkedFunctions_tst, FEE_CONST) Fee_LinkedFunctions_cst = 
{
    NULL_PTR
};
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/* Block properties for all Fee blocks
 *
 * Status Flags:
 * Block flags will help to specify a more detailed block configuration. The low Byte of these block flags is also stored
 * in the flash (status byte inside the block header). This information (in Flash) can be used to read/write the layout
 * without configuration (PAV, CB).
 *
 *
 *                                                 |<----- Block Status Byte in Block Header ----->|
 * |<---------------------------------------- Block Flags ---------------------------------------->|
 *    F     E     D     C     B     A     9     8  |  7     6     5     4     3     2     1     0  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |Prio-| Job type  |Ign. |No F.| Rob |Surv.|(Inv)| DataFilter| Sec-|
 * |     |     |     |     |     |rity |           |Blk  |back |Attr.|Attr.|     |    Type   | lvl |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *
 *  0  ... SecurityLevel      => 0...SingleStorage, 1...DoubleStorage
 * 1+2 ... Data Filter Type   => 0...Dynamic:         Anybody can erase this block (e.g. during migration)
 *                               1...Static:          Only certain users (e.g. repair shops) can erase this block
 *                               2...Permanent:       Only very certain users (e.g. OEM) can erase this block
 *                               3...Super Permanent: Block can never be erased
 *  3  ... Invalid            => 0...Block OK, 1...Block is invalid  --> can be changed by function Fee_InvalidateBlock
 *  4  ... Survival Attribute => 0...No survival, 1... Survival (even without being part of the layout)
 *  5  ... Robustness Attribute (Robustness against data modification during write execution)
 *                            => 0...Deactivated:     No additional checksum is used
 *                            => 1...Activated:       Additional checksum is used
 *  6  ... NoFallback         => 0...Deactivated:     A fallback to old copies is allowed
 *                            => 1...Activated:       A fallback to old copies is not allowed
 *  7  ... Ignore Block       => 0...Deactivated:     Block is considered
 *                            => 1...Activated:       Block is ignored
 * 8+9 ... TypeOfBlock        => 0...InternalJob, 1...NvmJob, 2...AdapterJob (e.g. Mx17 Eep adapter)
 *  A  ... Priority           => Job priority:        0...FEE_NORMAL_PRIO_E --> FeeImmediateData = No
 *                                                    1...FEE_HIGH_PRIO_E   --> FeeImmediateData = Yes
 */
#ifdef FEE_PRV_USE_ROM_TABLE
#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
const Fee_BlockPropertiesType_tst Fee_BlockProperties_st[FEE_NUM_BLOCKS] = {
#else
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
Fee_BlockPropertiesType_tst Fee_BlockProperties_st[FEE_NUM_BLOCKS] = {
#endif

	         /* FeeRbBlockPersistentId,  StatusFlags,  BlkLength ,  FeeRbCallbackEnd    ,  FeeRbCallbackError  */
	 /*   0 */{         0x0002         ,   0x0101   ,   0x0800   ,NULL_PTR              ,NULL_PTR               } /* NVDataBlock1                             */,
	 /*   1 */{         0x0003         ,   0x0100   ,   0x0200   ,NULL_PTR              ,NULL_PTR               } /* DiagDataBlock1                           */,
	 /*   2 */{         0x007B         ,   0x0100   ,   0x0800   ,NULL_PTR              ,NULL_PTR               } /* EOLDataBlock                             */,
	 /*   3 */{         0x11AF         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory4 */,
	 /*   4 */{         0x1597         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory5 */,
	 /*   5 */{         0x197F         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory6 */,
	 /*   6 */{         0x1D67         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory7 */,
	 /*   7 */{         0x214F         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory8 */,
	 /*   8 */{         0x2200         ,   0x0100   ,   0x0010   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_GenericNvData     */,
	 /*   9 */{         0x2537         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory9 */,
	 /*  10 */{         0x4602         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory1 */,
	 /*  11 */{         0x4FBB         ,   0x0100   ,   0x0085   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_AllEventsStatusByte */,
	 /*  12 */{         0x578B         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory0 */,
	 /*  13 */{         0x6510         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory3 */,
	 /*  14 */{         0x7499         ,   0x0100   ,   0x0074   ,NULL_PTR              ,NULL_PTR               } /* NvMBlockDescriptor_Dem_EvMemEventMemory2 */,
	 /*  15 */{         0xF2FB         ,   0x0100   ,   0x0008   ,NULL_PTR              ,NULL_PTR               } /* ECUM_CFG_NVM_BLOCK                       */,
};

#ifdef FEE_PRV_USE_ROM_TABLE
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
#else
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
#endif

 /* This section is applicable only for FEE 2.0, ignore or dont configure this section for FEE 1.0 */

