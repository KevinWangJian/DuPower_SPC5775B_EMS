

#include "Eep.h"
#include "Ea.h"
#include "Ea_Prv.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/


/*
 **********************************************************************************************************************
 * Constants
 **********************************************************************************************************************
*/

#define EA_START_SEC_CONST_UNSPECIFIED
#include "Ea_MemMap.h"

/* Callback function defines for error handling */
Ea_Prv_Common_tst const Ea_Prv_Common_cst = {NULL_PTR};

/* Version information define */
#if (EA_VERSION_INFO_API == TRUE)
Std_VersionInfoType const Ea_VersionInfo = {
                                                EA_VENDOR_ID,
                                                EA_MODULE_ID,
                                                EA_SW_MAJOR_VERSION,
                                                EA_SW_MINOR_VERSION,
                                                EA_SW_PATCH_VERSION
                                            };
#endif

/*********************************************************************************************************************/
/* block properties for all Ea blocks
 *
 * Status Flags:
 * Block flags will help to specify more detailed block configuration. These block flags are also stored
 * in the EEPROM (status-byte inside block header). This information can be used to read-/write the layout
 * without configuration (PAV, CB).
 *
 *
 * |<----------- stored in BlkHdr, too ----------->|
 * |  7     6     5     4     3     2     1     0  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |(Rob)|(Sur)|(Inv)|  Update-  | Sec-|
 * |     |     |     |     |     | attribute | lvl |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *
 *  0  ... SecurityLevel    => 0...SingleStorage, 1...DoubleStorage
 * 1+2 ... Update-Attribute => 0...Dynamic
 *                             1...Static
 *                             2...Permanent
 *                             3...Super Permanent
 *  3 .... Invalid          => 0...Block is valid
 *                             1...Block is invalid --> can be changed by function call Ea_InvalidateBlock
 *  4 .... Survival Attribute => 0...No survival, 1... Survival (even without being part of the layout)
 *  5 .... Robustness Attribute (Robustness against data modification during write execution)
 *                            => 0...Deactivated:     No additional checksum is used
 *                            => 1...Activated:       Additional checksum is used
 *  6..7 .... Reserved
 */
Ea_BlockPropertiesType const Ea_BlockProperties[EA_NUM_BLOCKS]= {
	 /*		    BlkStartAddress  BlkEndAddress  BlkRealLength   BlkPersistentId  BlkLength  StatusFlags                                       	 */
	 /*   0 */{   0x00000040,      0x0000044F,       0x0410,       0x0002,       0x0400,       0x00} /* NVDataBlock1                             */,
	 /*   1 */{   0x00000450,      0x0000065F,       0x0210,       0x0003,       0x0200,       0x00} /* DiagDataBlock1                           */,
	 /*   2 */{   0x00000660,      0x00000E6F,       0x0810,       0x007B,       0x0800,       0x00} /* EOLDataBlock                             */,
	 /*   3 */{   0x00000E70,      0x00000F23,       0x00B4,       0x11AF,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory4 */,
	 /*   4 */{   0x00000F24,      0x00000FD7,       0x00B4,       0x1597,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory5 */,
	 /*   5 */{   0x00000FD8,      0x0000108B,       0x00B4,       0x197F,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory6 */,
	 /*   6 */{   0x0000108C,      0x0000113F,       0x00B4,       0x1D67,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory7 */,
	 /*   7 */{   0x00001140,      0x000011F3,       0x00B4,       0x214F,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory8 */,
	 /*   8 */{   0x000011F4,      0x00001213,       0x0020,       0x2200,       0x0010,       0x00} /* NvMBlockDescriptor_Dem_GenericNvData     */,
	 /*   9 */{   0x00001214,      0x000012C7,       0x00B4,       0x2537,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory9 */,
	 /*  10 */{   0x000012C8,      0x0000137B,       0x00B4,       0x4602,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory1 */,
	 /*  11 */{   0x0000137C,      0x0000145B,       0x00E0,       0x4FBB,       0x00D0,       0x00} /* NvMBlockDescriptor_Dem_AllEventsStatusByte */,
	 /*  12 */{   0x0000145C,      0x0000150F,       0x00B4,       0x578B,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory0 */,
	 /*  13 */{   0x00001510,      0x000015C3,       0x00B4,       0x6510,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory3 */,
	 /*  14 */{   0x000015C4,      0x00001677,       0x00B4,       0x7499,       0x00A4,       0x00} /* NvMBlockDescriptor_Dem_EvMemEventMemory2 */,
	 /*  15 */{   0x00001678,      0x0000168F,       0x0018,       0xF2FB,       0x0008,       0x00} /* ECUM_CFG_NVM_BLOCK                       */,
};

#define EA_STOP_SEC_CONST_UNSPECIFIED
#include "Ea_MemMap.h"
/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/

