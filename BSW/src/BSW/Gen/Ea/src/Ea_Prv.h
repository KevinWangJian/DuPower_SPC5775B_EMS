

#ifndef EA_PRV_H
#define EA_PRV_H

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 4.0.2
 * \scope    INTERN
 **********************************************************************************************************************
 */
#if (EA_PRESENT == 1)
/*
 ****************************************************************************************************
 * Includes
 ****************************************************************************************************
 */
#include "Eep.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

/* Ea init defines */
#define EA_RB_ST_INIT_NOT_DONE          0x00        /* Module is still uninitialized */
#define EA_RB_ST_INIT_DONE              0x01        /* Module has been initialized */
#define EA_RB_ST_INIT_RUNNING           0x02        /* Module is in initialization */

/* Ea cancel defines */
#define EA_RB_ST_CANCEL_NOT_REQUESTED   0x00	    /* No cancel requested currently active */
#define EA_RB_ST_CANCEL_REQUESTED		0x01	    /* Cancel request is currently active */

/* Ea mask defines */
#define EA_MARKER_PATTERN               0xCAFE      /* Start value of CRC  */
#define EA_BLK_HEADER_PREAMBEL          0xAFFE80    /* Pattern of preambel */

#define EA_BLK_HEADER_PREAMBEL_BYTE_0   0xAF        /* 0xAF */
#define EA_BLK_HEADER_PREAMBEL_BYTE_1   0xFE        /* 0xFE */
#define EA_BLK_HEADER_PREAMBEL_BYTE_2   0x80        /* 0x80 */

#define EA_CRC_XOR_VALUE32              ((uint32)0xFFFFFFFFuL)

/* Ea flag defines */
#define EA_SECURITY_LEVEL_FLAG          0x1uL         /* Set flag for security level 2, store block twice */
#define EA_INVALID_FLAG                 0x8uL         /* Set flag for invalid block */
#define EA_SURVIVAL_FLAG                0x10uL        /* Set flag for survival data, keep them undeleted even not configured */
#define EA_ROBUST_CRC_FLAG              0x20uL        /* Set flag for robustness checksum calculation */

/* Ea parameter defines */
#define EA_REPEAT_ORDER_MAX             3u           /* Number of repeat order if any errors */
#define EA_BLK_HEADER_SIZE              16u         /* Size of block header */
#define EA_INIT_BLK_ID                  0x0         /* Default initial value of persistent ID */
#define EA_BASE_MIGCLIP_ADDR_SIZE		6uL			/* Size of Base Clipboard Address */
#define EA_MIGCLIP_DETAILS_SIZE			8uL			/* Size of Entire Clip details Structure to be written into/read from EEPROM */

#define EA_MAXUINT16                    (0xFFFF)    /* UINT16 max */
#define EA_MAXUINT32                    (0xFFFFFFFFuL)
#define EA_INIT_BLK_VERSION             (0x1)       /* Block version initialization value */

#define EA_MIGRATION_MARKER_TEMP        (0xDEADBEEFuL)  /* Temporary migration marker during migraion running */
#define EA_RB_MIG_BUFFER_SIZE           (256uL)  	/* Ea Init length of scan buffer */
#define EA_RB_MIG_BUFFER_ALIGN_SIZE		(EA_RB_MIG_BUFFER_SIZE - EA_BLK_HEADER_SIZE)  	/* Ea Init length of scan buffer to align with last 16byes */
#define EA_BASE_CLIP_MARKER             (0xA5A5uL)    /* Base value of the MigClipDetails Marker present in Eeprom during Migration */


#if (EA_RB_ADDONS_CCAS != FALSE)
#define EA_RB_REQUEST_STOP_MODE         TRUE        /* Stop mode for CCAS add-on */
#endif

/* Ea Offset to write Migration Clipboard address */
#define EA_RB_MIGCLIP_ADDR_OFFSET			0x30uL		/* Offset Address in the Layout Header reserved location to store the Details of ClipBoard Start Address */

/* Mapping of read and write to EEP because of name conflict if EEP used */
#if (EEP_NAME_USED == 1)
#define EA_EEP_READ(EepromAddress, DataBufferPtr, Length)                   Eep_Rb_Read(EepromAddress, DataBufferPtr, Length)
#define EA_EEP_WRITE(EepromAddress, DataBufferPtr, Length)                  Eep_Rb_Write(EepromAddress, DataBufferPtr, Length)
#else
#define EA_EEP_READ(EepromAddress, DataBufferPtr, Length)                   Eep_Read(EepromAddress, DataBufferPtr, Length)
#define EA_EEP_WRITE(EepromAddress, DataBufferPtr, Length)                  Eep_Write(EepromAddress, DataBufferPtr, Length)
#endif

/*
 ***************************************************************************************************
 * Type definition and enums
 ***************************************************************************************************
 */
/* Internal Ea order enumerator */
typedef enum
{
    EA_RB_NO_ORDER_E                = 0,        /* No order currently placed */
    EA_RB_STOPMODE_E                = 1,        /* Stop mode from CCAS add on */
    EA_RB_READ_ORDER_E              = 2,        /* Read order */
    EA_RB_WRITE_ORDER_E             = 3,        /* Write order */
    EA_RB_SEARCH_ORDER_E            = 4,        /* Search survival block order */
    EA_RB_READ_HEADER_E             = 5,        /* Reading header order */
    EA_RB_CHECK_DATA_VALID_E        = 6,        /* Start data valid check */
    EA_RB_CHECK_DATA_VALID_WAIT_E   = 7,        /* Wait status for data valid check */
    EA_RB_START_WRITE_ORDER_E       = 8,        /* Start to write, block header at first */
    EA_RB_COMPARE_HEADER_ORDER_E    = 9,        /* Compare the written header */
    EA_RB_WRITE_DATA_ORDER_E        = 10,       /* Write data order */
    EA_RB_COMPARE_DATA_ORDER_E      = 11,       /* After writing, compare the new data block with write buffer */
    EA_RB_ERASE_ORDER_E             = 12,       /* Erase order */
    EA_RB_END_ERASE_ORDER_E         = 13,       /* Erase end order */
    EA_RB_END_READ_ORDER_E          = 14,       /* Read end order */
    EA_RB_END_WRITE_ORDER_E         = 15,       /* Write end order */
    EA_RB_MAINTAIN_ORDER_E          = 16,       /* Maintain start order */
    EA_RB_MAINTAIN_MOVING_WAIT_E    = 17,       /* Maintain wait order for block copying */
	EA_RB_WRITE_ORDER_WAIT_E		= 18		/* Waits for Handling of Survival Blocks to be completed before placing the write request to Driver layer */
}Ea_Rb_OrderType_ten;

/* Internal Ea migration order enumerator */
typedef enum
{
    EA_RB_NO_MIGRATION_E            	= 0,        /* No migration placed */
    EA_RB_MIG_CHECKMARKER_E         	= 1,        /* Check migration marker */
    EA_RB_MIG_LOAD_BLKHDR_E         	= 2,        /* Search all valid block in layout */
    EA_RB_MIG_CHECK_DATA_E          	= 3,        /* Check data valid */
    EA_RB_MIG_WRITE_BLKHDR_E        	= 4,        /* Write block header only if necessary */
    EA_RB_MIG_WRITE_MIGHDR_TEMP_E   	= 5,        /* Write migration header temporary before migration started */
    EA_RB_MIG_DELETING_E            	= 6,        /* Deleting block */
    EA_RB_MIG_RUNNING_E             	= 7,        /* Running migration */
    EA_RB_MIG_START_HDR_E           	= 8,        /* Write block header only if no data available */
    EA_RB_MIG_MOVING_READ_E         	= 9,        /* First step of moving: read */
    EA_RB_MIG_MOVING_WRITE_E        	= 10,       /* Second step of moving: write */
    EA_RB_MIG_MOVING_COMPARE_E      	= 11,       /* Third step of moving: compare */
    EA_RB_MIG_MOVING_DELETE_E       	= 12,       /* Fourth step of moving: delete old layout */
    EA_RB_MIG_MOVING_WAIT_E         	= 13,       /* Wait for moving finished */
 #if(EA_NUM_SURVIVAL_BLOCKS > 0)
    EA_RB_MIG_FINISH_CHECK_1_E      	= 14,       /* First step of migration end: read reserved block if survival block used */
    EA_RB_MIG_FINISH_CHECK_2_E      	= 15,       /* Second step of migration end: check and write survival block offsets */
 #endif
    EA_RB_MIG_FINISH_CHECK_3_E      	= 16,       /* Third step of migration end: wait for writing end */
    EA_RB_MIG_WRITE_MIGHDR_E        	= 17,       /* Write migration header with correct new layout end */
    EA_RB_MIG_NOT_POSSIBLE_E        	= 18,       /* Migration not possible because of no free space */
    EA_RB_MIG_ERROR_E               	= 19,       /* Error occurs during migration */
    EA_RB_END_MIGRATION_E           	= 20,       /* Migration finished successfully */
	EA_RB_MIG_CHECKVALID_COPY_E     	= 21,		/* Check the valid block b/w first and second appearence of same ID */
	EA_RB_MIG_BASECLIP_WRITE_WAIT_E		= 22,		/* Writing of Base ClipBoard Address, if updated, before start of migration operation */
	EA_RB_MIG_BASECLIP_READ_E			= 23,		/* Reading of ClipBoard Address after every Power On during Migration */
	EA_RB_MIG_BASECLIP_READ_WAIT_E		= 24,		/* Checking whether CRC of Clipdetails is correct */
	EA_RB_MIG_DELETE_BASECLIP_E         = 25,       /* Erase the Clipdetails area to avoid any confusion when Boot to Application mode jump occurs */
 #if(EA_NUM_SURVIVAL_BLOCKS > 0)
	EA_RB_MIG_SURVBLK_HANDLING_INIT_E	= 26,		/* Searches for all new survival blocks and those Survival blocks whose property has been changed */
	EA_RB_MIG_SURVBLK_HANDLING_E		= 27,		/* Handling of Survival Blocks will be done here */
	EA_RB_MIG_SURVBLK_HANDLING_ERROR_E  = 28,       /* Error while handling of Survival Blocks */
 #endif
	EA_RB_MIG_ORDER_DEFAULT_E           = 0xFF      /* Added as last value of MigOrderType enum, add new enum literals above this one */
}Ea_Rb_MigOrderType_ten;

/* Internal Ea return type */
typedef enum
{
    EA_RB_ST_INIT_E                 = 0,        /* Status initialization */
    EA_RB_ST_OK_E                   = 1,        /* Status OK */
    EA_RB_ST_ERROR_E                = 2,        /* A general error occurred */
    EA_RB_ST_INVALIDATED_E          = 3,        /* The processing block is invalidated */
    EA_RB_ST_PENDING_E              = 4,        /* The order is in processing */
    EA_RB_ST_NODATA_E               = 5,        /* The processing block has no data (never been written) */
    EA_RB_ST_WRONG_ID_E             = 6
}Ea_Rb_stReturn_ten;

/* Internal Ea order type */
typedef enum
{
    EA_RB_NO_REQUEST_E              = 0,
    EA_RB_READ_E                    = 1,        /* Read order */
    EA_RB_WRITE_E                   = 2,        /* Write order */
    EA_RB_MAINTAIN_E                = 3,        /* Maintain redundant block order */
    EA_RB_MIGRATION_E               = 4
}Ea_Rb_Request_ten;

/* Type of request order */
typedef enum
{
    EA_RB_FLAG_NO_CHANGE_E          = 0,        /* No flag changes */
    EA_RB_FLAG_SL1_TO_SL2_E         = 1,        /* SL1 --> SL2 */
    EA_RB_FLAG_SL2_TO_SL1_E         = 2,        /* SL2 --> SL1 */
    EA_RB_FLAG_TO_SURVIVAL_E        = 3,        /* No-Survival to Survival */
    EA_RB_FLAG_TO_NO_SURVIVAL_E     = 4,        /* Survival to No-Survival */
	EA_RB_FLAG_NEW_SURVBLK_E		= 5			/* New Survival Block Detected */
}Ea_Rb_MigFlagChanges_ten;

#if(EA_NUM_SURVIVAL_BLOCKS > 0)
/* Internal Order while Handling of Survival Blocks */
typedef enum
{
    EA_RB_SURVBLK_INIT_E                = 0,    /* Init State which loads the Eep Cache to the local structure */
    EA_RB_SURVBLK_READ_DATA_E			= 1,	/* Read order to read Data will be placed to driver layer */
	EA_RB_SURVBLK_WRITE_DATA_E			= 2,	/* Write Order to write Data will be placed to driver layer */
	EA_RB_SURVBLK_READ_HEADER_E			= 3,	/* Read order to read Header will be placed to driver layer */
	EA_RB_SURVBLK_WRITE_HEADER_E		= 4,	/* Write Order to write Header will be placed to driver layer */
	EA_RB_SURVBLK_WRITE_HEADER_COPY_E	= 5,	/* Write Order to write second copy of Header if any will be placed to driver layer */
	EA_RB_SURVBLK_READ_HEADER_COPY_E    = 6,    /* Read Order to read second copy of Header if any will be placed in the driver layer */
	EA_RB_SURVBLK_ERASE_COPY_E          = 7     /* Erase Order to erase the Second copy of a block when there is a change from SL->SL1 */
}Ea_Rb_SurvBlkHandlingOrderType_ten;

#endif

/* Internal State's of Ea_Rb_BlockMaintenance Order */
typedef enum
{
    EA_RB_MAINTAIN_READ_E        = 0,        /* Reads the block Data from valid copy */
    EA_RB_MAINTAIN_WRITE_E       = 1,        /* Write the block Data into corrupted location */
    EA_RB_MAINTAIN_COMPARE_E     = 2,        /* Compare the write request buffer content with Eeprom content */
    EA_RB_MAINTAIN_FINISH_E      = 3        /* Block Maintain movement completed successfully */
}Ea_Rb_BlockMaintenance_ten;

typedef enum
{
	EA_RB_MIG_BLOCK_VERSION_COMPARE_E	= 0,  /* Compare block versions b/w first and second appearence of same ID */
	EA_RB_MIG_READ_DATA_TO_VALIDATE_E   = 1   /* Read the data to validate the block with CRC32 */
}Ea_Rb_Mig_SecondBlkValid_ten;

/* Ea_Rb_BlockMaintenance handling Structure */
typedef struct
{
	Eep_AddressType ReadAddr_uo;                 	/* Read address for current order */
	Eep_AddressType WriteAddr_uo;                 	/* Write address for current order */
	Ea_Rb_BlockMaintenance_ten MaintainOrder_en;	/* Maintain Order Internal Processing state's */
	uint32 numBytes_u32;                        	/* Number of bytes for current order: uint16 block length. Max length possible is 0xFFFF + Header Info Size  */
	uint32 numBytesTemp_u32;						/* Temporary variable */
}Ea_Rb_BlockMaintenance_tst;

typedef struct
{
    Eep_AddressType adStart_uo;                 /* Start address for current order */
    Eep_LengthType BlockLenAligned_uo;          /* Aligned block length + block header */
    uint16 numBytes_u16;                        /* Number of bytes for current order: uint16 block length */
    uint16 stCurBlockVersion_u16;               /* Current Block version */
    uint16 numID_u16;                           /* Current block Persistent ID */
    union
    {
        uint8* Read_pu8;                        /* Read pointer to data buffer is needed for */
                                                /* writing data to read buffer */
        const uint8* Write_pcu8;                /* Write pointer (constant) to data buffer */
    } Buffer_un;
    Ea_Rb_OrderType_ten OrderType_en;           /* Type of current order (status) */
    Ea_Rb_Request_ten RequestOrder_en;          /* Type of request order */
    uint8 numRepOrder_u8;                       /* Number of repeated order */
    boolean isWriteHeaderOnly_b;                /* TRUE: write the block header only */
    boolean isDataNotEqual_b;                   /* TRUE: the compared data are not equal; FALSE: data equal */
    boolean isSecLevelCurr_b;                   /* FALSE: no need to check the second copy; TRUE: the second copy check is possible */
    boolean isActivBlkCurr_b;                   /* FALSE: first block is the newer one; TRUE: second copy of block is newer */
    boolean isSurvivalBlk_b;                    /* TRUE: current block is a survival block */
    boolean isCheckAfterWrite_b;                /* Marker for block valid check after writing */
}Ea_Rb_Order_tst;

typedef struct
{
    Eep_AddressType adReadStart_uo;             /* Start read address for current order */
    Eep_AddressType adWriteStart_uo;            /* Start write address for current order */
    uint32 BlockData_CS_u32;                    /* block data CRC32 */
    Eep_LengthType numBytes_uo;                 /* Number of bytes for current order */
    Eep_LengthType numTrsBytes_uo;              /* Number of bytes for current Spi transfer */
    Eep_LengthType numAlignedBytes_uo;          /* Aligned number of bytes for current order */
    uint16 numID_u16;                           /* Current block Persistent ID */
    uint16 stCurBlockVersion_u16;               /* Current Block version */
    union
    {
        uint8* Read_pu8;                        /* Read pointer to data buffer is needed for */
                                                /* writing data to read buffer */
        const uint8* Write_pcu8;                /* Write pointer (constant) to data buffer */
    } Buffer_un;
    Ea_Rb_MigOrderType_ten MigOrderType_en;     /* Type of current order */
    boolean isMoveToEepEnd_b;                   /* FALSE: write order; TRUE: read order */
    boolean isToBeErase_b;                      /* TRUE: old block is to be erased */
    boolean isSecLevelCurr_b;                   /* TRUE: the second copy check is possible; FALSE: no need to check the second copy */
    boolean isCopyWritten_b;                    /* TRUE: for redundant blocks, the second copy has been written */
    boolean isFlagChanged_b;
}Ea_Rb_MigOrder_tst;

/* Block header descriptor */
typedef struct
{
    uint8  BlockPattern_u8[3];                  /* Block pattern, should be 0xAFFE80 */
    uint8  BlockFlags_u8;                       /* Block flags */
    uint16 BlockID_u16;                         /* Block persistent ID */
    uint16 BlockLen_u16;                        /* Block length */
    uint16 BlockVersion_u16;                    /* Block version */
    uint16 BlockHeader_CS_u16;                  /* Block header checksum CRC16 */
    uint32 BlockData_CS_u32;                    /* Block data checksum CRC16 */
}Ea_Rb_BlockHeader_tst;

/* EEPROM Layout migration header descriptor */
typedef struct
{
    uint32 MigMarker_u32;                       /* Migration marker, generated */
    Eep_AddressType MigPerStartAddr_u32;        /* Start address of permanent area */
    Eep_AddressType MigEndAddr_u32;             /* Layout end address. By migration break it will be set to EEP_TOTAL_SIZE */
    uint16 MigStartOff_u16;                     /* Start address of Layout */
    uint16 MigHeader_CS_u16;                    /* Migration header checksum */
}Ea_Rb_MigHeader_tst;

typedef struct {
    Eep_AddressType BlkStartAddr;               /* Start address of current block */
    Eep_AddressType BlkEndAddr;                 /* End address of current block */
    Eep_LengthType  BlkRealLen;                 /* Real length of current block including block header and alignment*/
    uint16 NvMIdx;                              /* Persistent ID of current block */
    uint16 Length;                              /* Data length of current block  */
    uint8  Flags;                               /* Flags of current block  */
}Ea_BlockPropertiesType;

/* Survival block offset descriptor:
Pay attention: the length of this structure is needed in BCT script running
               By any changes of this structure length different from 8 Bytes
			   Please change the length in script variable $lenOfOffsetStr_s */
typedef struct
{
    Eep_AddressType BlockOffset_uo;             /* Block offset for survival block */
    uint16 SurvivalBlockID_u16;                 /* Survival block persistent ID */
}Ea_Rb_SurvivalBlockOffset_tst;

typedef struct
{
    void (*Ea_Rb_ErrorHandling_CallBack_pfct)(uint8 ErrorId);   /* Pointer to error handling callback function */
} Ea_Prv_Common_tst;

typedef struct
{
	Eep_AddressType MigClipBaseAddr_uo;			/* Back of the Base Clipboard start address after first time inititalisation*/
	uint16 MigClipMarker_u16;                   /* Marker to indicate start of Clip details in Reserved area */
    uint16 MigClipBaseAddr_CS_u16;					/* Base ClipBoard Address Checksum */
}Ea_Rb_MigClipDetails_tst;

#if(EA_NUM_SURVIVAL_BLOCKS > 0)

typedef struct
{
    Eep_AddressType ReadStartAdr_u32;                                               /* Read start address of the Survival Block in the old layout */
    Eep_AddressType WriteStartAdr_u32;                                              /* Write Start Address of the Survival Block in the new layout */
    Ea_Rb_SurvBlkHandlingOrderType_ten Ea_Rb_SurvBlkHandlingOrderType_en;           /* Type of order being executed currently during handling of Survival Blocks */
    Ea_Rb_MigFlagChanges_ten Ea_Rb_MigFlagChanges_aen[EA_NUM_SURVIVAL_BLOCKS];      /* Reason for the Survival Block to be handled */
    uint16 BlkLength_u16;                                                           /* Length of the Survival Block being processed */
    uint16 TransmitLen_u16;                                                         /* Number of Bytes transmitted for the operation */
    uint16 SurvBlksToBeHandled[EA_NUM_SURVIVAL_BLOCKS];								/* Array that maintains the list of Survival Blocks to be handled */
	boolean isNextSurvBlkHandlingPossible_b;								        /* TRUE: Next Survival Block can be handled */
	boolean isSurvBlksHandlingOver_b;										        /* TRUE: Handling of Survival Blocks is completed */
	boolean isSurvBlksHandlingError_b;										        /* TRUE: An Error occured while handling of Survival Blocks */
}Ea_Rb_SurvBlksHandling_tst;

#endif

/* Second found block validation structure */
typedef struct {
	Eep_AddressType adStart_uo;                 /* Start address for current order */
	Ea_Rb_Mig_SecondBlkValid_ten OrderType_en;  /* Type of current order (status) */
    uint16 numBytes_u16;                        /* Number of bytes for current order: uint16 block length */
	uint16 BlockID_u16;                         /* Holds Persistent ID of first copy of Second found block. Only for redundent block */
    uint16 BlockLen_u16;                        /* Holds length of first copy of Second found block. Only for redundent block */
} Ea_Rb_MigSecondBlkValid_tst;
/*
 ***************************************************************************************************
 * Externals
 ***************************************************************************************************
 */

#define EA_START_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"
extern boolean  Ea_Rb_MigInit_b;                /* TRUE: Migration initialization is running */
extern boolean  Ea_Rb_MigRunning_b;             /* TRUE: Migration is running */
extern boolean  Ea_Rb_RedundantActiv_b;         /* TRUE: Redundant block is active */
extern boolean  Ea_Rb_MigAndWrConflict_b;       /* TRUE: Write oder during migration of the same block */
#if (EA_RB_ADDONS_CCAS != FALSE)
extern boolean  Ea_Rb_stRequestStopMode_b;      /* TRUE: Stop mode has been requested by CCAS add on */
#endif
/* Check if migration header changed */
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
extern boolean Ea_Rb_isMigHeaderDiff_b;
#endif
extern boolean  Ea_Rb_MigChecked_b;                 /* TRUE: migration marker checked  */
extern boolean Ea_Rb_isDataCrcZero_b;			    /* TRUE: Data crc value for the block is zero */
extern boolean Ea_Rb_isData1CrcZero_b;			    /* TRUE: Data crc value for the redundent block copy1 is zero */
extern boolean Ea_Rb_isData2CrcZero_b;			    /* TRUE: Data crc value for the redundent block copy2 is zero */
extern boolean Ea_Rb_isLastDataValid_b;			    /* TRUE: Eeprom Data Valid. Applicable only for user write request */
extern boolean Ea_Rb_MigClipUpdate_b;			    /* TRUE: MigClipBaseAddr_uo value should be written in Eeprom */
extern boolean Ea_Rb_MigScanflag_b;				    /* TRUE: copy the header info from buffer to block header structure */
extern boolean Ea_Rb_MigVirginEepromFlag_b;		    /* TRUE: Virgin Eeprom Case */
extern boolean Ea_Rb_MigNotPossibleFlag_b;          /* TRUE: Either the Clip details have been corrupted or One complete cycle of Clipboard scanning is done */
extern boolean Ea_Rb_isNewSurvBlkToBeWritten_b;     /* TRUE: Write request for a new Survival block is given by user */
extern boolean Ea_Rb_SurvBlkHandlingAndWrConflict_b;/* TRUE: Write/Invalidate request is given for a block which is being handled(in survival block handling)*/
#define EA_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_8
#include "Ea_MemMap.h"
extern uint8    Ea_Rb_stInit_u8;                            /* Initialization state */
extern uint8    Ea_Rb_stCancel_u8;				            /* Status of cancel request  */
extern uint8    Ea_Rb_dDataBuf_u8[EA_DATA_BUFFER_SIZE];     /* Local data buffer */
extern uint8    Ea_Rb_dMigDataBuf_u8[EA_RB_MIG_BUFFER_SIZE];  /* Local data buffer only for migration */
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
extern uint8    Ea_Rb_MigrationStaus_u8;					/* Global variable to hold the Migration status */
#endif
#define EA_STOP_SEC_VAR_CLEARED_8
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"
extern uint16   Ea_Rb_MigCurNr_u16;             /* The current block number which should be placed to the right address */
extern uint16   Ea_Rb_MigFoundBlkNr_u16;        /* The found block number on old layout */
extern uint16   Ea_Rb_MigBlkNrToMove_u16;       /* Block number which has been moved in old layout */
extern uint16   Ea_Rb_MigNumBytesTmp_u16;       /* Number of bytes to be read during block validation in init */
extern uint16   Ea_Rb_numBytesTmp_u16;              /* Global number of bytes to be read */
extern uint16 Ea_Rb_MigBlkCnt_u16;
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
extern uint16   Ea_Rb_MigEraseBlkNr_u16;		/* Number of block headers to be erased in cyclic */
#endif
extern uint16   Ea_Rb_MigScanSize_u16;          /* Number of bytes already scanned */
#if(EA_NUM_SURVIVAL_BLOCKS > 0)
extern uint16 Ea_Rb_NewSurvBlkIndex_u16;        /* Index of the new survival block for which write/invalidate request has been given */
extern uint16 Ea_Rb_SurvBlksIndex_u16;
extern uint16 Ea_Rb_SurvBlksIndexBackUp_u16;
#endif
extern uint16 Ea_Rb_SurvBlkHandlingAndWrConflictIndex_u16;
extern uint16 Ea_Rb_SurvBlkHandled_u16;
#define EA_STOP_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_32
#include "Ea_MemMap.h"
extern uint32   Ea_Rb_BlockData_CS_u32;         /* Global checksum of current checked block */
extern uint32   Ea_Rb_MigLayoutEnd_u32;         /* End address of layout during migration */
extern uint32   Ea_Rb_BlockData1_CS_u32;
extern uint32   Ea_Rb_BlockData2_CS_u32;
extern uint32   Ea_Rb_MigBlockData_CS_u32;      /* Checksum for init time block validation */
#define EA_STOP_SEC_VAR_CLEARED_32
#include "Ea_MemMap.h"

/* Migration defines */
#define EA_START_SEC_VAR_INIT_32
#include "Ea_MemMap.h"
extern uint32   Ea_Rb_MigClipSrtAdr_u32;        	/* Start address of clip board during migration */
extern uint32	Ea_Rb_MigClipBaseSrtAdr_u32;		/* Backup of the initially calculated clip board address for future usage */
extern uint32	Ea_Rb_MigClipBackUpSrtAdr_u32;		/* Backup of the clip board start address before every migration operation to handle migration conflict use case */
#define EA_STOP_SEC_VAR_INIT_32
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
extern Eep_AddressType Ea_Rb_BlockOffset_uo;    /* Global block offset */
extern Eep_AddressType Ea_Rb_BlankStart_uo;     /* Blank area start address of survival blocks */
extern Eep_AddressType Ea_Rb_BlankLen_uo;       /* Blank area length of survival blocks */
extern Eep_AddressType Ea_Rb_MigScanAddr_uo;    /* Start address for current scanning in 256byte buffer */
extern Ea_Rb_Order_tst                  Ea_Rb_Order_st;                             /* EA order structure */
extern Ea_Rb_MigOrder_tst               Ea_Rb_MigOrder_st;                          /* EA migration order structure */
extern Ea_Rb_BlockHeader_tst            Ea_Rb_BlockHeader_st;                       /* EA block header structure */
extern Ea_Rb_BlockHeader_tst            Ea_Rb_MigBlockHeader_st;                    /* EA block header structure, used during migration */
extern Ea_Rb_MigSecondBlkValid_tst      Ea_Rb_MigSecondBlkValid_st;    				/* Temporary structure to validate the second found block */
extern Ea_BlockPropertiesType           Ea_BlockProperties_onEep[EA_NUM_BLOCKS];    /* Block properties on EEPROM layout */
extern Ea_Rb_MigClipDetails_tst			Ea_Rb_MigClipDetails_st;						/* Details of the initially calculated clip board start address*/
 #if(EA_NUM_SURVIVAL_BLOCKS > 0)
    extern Ea_Rb_SurvBlksHandling_tst       Ea_Rb_SurvBlksHandling_st;                  /* Details regarding the handling of Survival Blocks */
    extern Ea_Rb_SurvivalBlockOffset_tst    Ea_Rb_OffsetArr_st[EA_NUM_SURVIVAL_BLOCKS]; /* Offset array for all survival blocks */
 #endif
extern Ea_Rb_MigHeader_tst              Ea_Rb_MigHeader_st;                         /* Layout migration header information of all EEPROM */
extern Ea_Rb_BlockMaintenance_tst Ea_Rb_BlockMaintenance_st;						/* structure used for maintaining redundant block */
extern Ea_Rb_BlockHeader_tst			Ea_Rb_MigBlockHeaderTemp_st;				/* Temporary block header to compare the multiple instances of same ID */
extern Ea_Rb_MigOrder_tst               Ea_Rb_MigOrderMaintain_st;					/* Move structure used for maintaining redundant block */
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
extern Eep_AddressType Ea_Rb_MigEraseBuffer_uo[EA_RB_MIG_ERASE_BUFFER_SIZE];			/* This array will contain the addresses of old layout blocks which are not present in the new layout*/
#endif
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_INIT_UNSPECIFIED
#include "Ea_MemMap.h"
extern Ea_Rb_stReturn_ten               Ea_Rb_LastCheckResult_en;                   /* The result of last block check */
#define EA_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_CONST_UNSPECIFIED
#include "Ea_MemMap.h"
extern const Ea_Prv_Common_tst Ea_Prv_Common_cst;
extern const Std_VersionInfoType        Ea_VersionInfo;                             /* Version info structure */
extern const Ea_BlockPropertiesType     Ea_BlockProperties[EA_NUM_BLOCKS];          /* Block properties of current configuration */
#define EA_STOP_SEC_CONST_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
extern uint32 Ea_Rb_CalcAlignedLen(uint32 unalignedLen_u32);
extern void Ea_Rb_ResetStatus(void);
extern void Ea_Rb_JobFinished(Ea_Rb_stReturn_ten stRetEnd_en);
extern boolean Ea_Rb_HeaderCheck(const Ea_Rb_BlockHeader_tst* TargetHeader);
extern Ea_Rb_stReturn_ten Ea_Rb_CheckAnotherCopy(void);
extern void Ea_Rb_LoadHeaderToBuffer(const Ea_Rb_BlockHeader_tst* SourceHeader, uint8* TargetBuffer);
extern Ea_Rb_stReturn_ten Ea_Rb_StartToRead(uint32 CrcToBeChecked);
extern Ea_Rb_stReturn_ten Ea_Rb_StartToReadFromEep(Eep_AddressType EepromAddress, uint8* DataBufferPtr, Eep_LengthType Length);

extern void Ea_Rb_Migration(void);
extern void Ea_Rb_WriteMigHeader(Ea_Rb_MigHeader_tst* SourceMigHeader);
extern void Ea_Rb_MigStartCheck(void);
extern void Ea_Rb_WriteBlockHeader(uint16 BlockNr, Ea_Rb_BlockHeader_tst* Target);
extern void Ea_Rb_MigrationInit(void);
/* Sub functions for order processing */
extern Ea_Rb_stReturn_ten Ea_Rb_CheckBlockValid(Eep_AddressType adStart, Ea_Rb_BlockHeader_tst* hdrFromOrder_st, Ea_Rb_Request_ten RequestOrder_en, boolean isFirstCall_b);
extern Ea_Rb_stReturn_ten Ea_Rb_MigMoveBlock(const Ea_Rb_MigOrder_tst * MigOrder_pst, boolean bFirstCall);
extern void Ea_Rb_MigCheckCurrBlkNr(void);
extern boolean Ea_Rb_MigCheckResult(void);
extern Eep_AddressType Ea_Rb_SearchBlock(Eep_AddressType adStart, uint16 numSearchID, boolean bFirstCall);
extern uint16 Ea_Prv_SearchBlockInProp(Ea_BlockPropertiesType const* stBlockProperties_apcst, uint16 persistentID_u16);
extern uint16 Ea_Rb_MigCheckFreeAdr(uint16 currBlk_u16);
extern boolean Ea_Rb_CheckBlkInRightAddr(uint16 numBlk_u16);
extern void Ea_Rb_LoadBlkProperties(uint16 tmpCnt1_u16, Ea_Rb_BlockHeader_tst const *tmpMigBlkHdr_st);
extern void Ea_Rb_LoadBlkHdrFromProperties(uint16 BlockNumber, Ea_Rb_BlockHeader_tst *tmpBlkHdr_st);
extern Ea_Rb_stReturn_ten Ea_Rb_BlockEvaluation(Ea_Rb_stReturn_ten   stRetLoc_en);
extern Ea_Rb_stReturn_ten Ea_Rb_RedundantBlockEvaluation(Ea_Rb_stReturn_ten stRetSub_en);
extern Ea_Rb_stReturn_ten Ea_Rb_SingleBlockEvaluation(void);
extern Ea_Rb_stReturn_ten Ea_Rb_StartToWrite(void);
extern uint16 Ea_Rb_FindPreambelInHdr(const uint8* SearchStart_Ptr, uint16 Len_u16);
extern Ea_Rb_stReturn_ten Ea_Rb_CheckRetryOrderNr(Ea_Rb_OrderType_ten RetryOrder_en);
extern void Ea_Rb_CheckFirstFoundBlk(uint16 PersistentID_u16);
extern void Ea_Rb_MigStop(void);
extern boolean Ea_Rb_MigClipAddrCheckSpace(uint16 CurrMigBlk_u16, uint16 NumBytes_u16);
extern void Ea_Rb_MigCheckSecondFoundBlkValid(void);

extern void Ea_Rb_MigBlockEvaluation(Ea_Rb_stReturn_ten stRetSub_en);
extern void Ea_Rb_MigCheckCurrBlkToBeMoved(void);
extern void Ea_Rb_MigStartToMoveBlock(void);

extern Std_ReturnType Ea_Rb_CheckInit(uint8 ApiId_u8);
extern Std_ReturnType Ea_Rb_CheckBlkNr(uint8 ApiId_u8, uint16 BlockNumber_u16);
extern void Ea_Rb_CheckMigrationErr(uint8 ApiId_u8, uint8 ErrTyp_u8);
/* Function to check whether current order requires last Executed Eep_JobResult status or Not */
extern boolean Ea_Rb_MainFunctionOrderCheck(void);
extern boolean Ea_Rb_MigrationOrderCheck(void);
extern boolean Ea_Rb_MigrationInitOrderCheck(void);
extern void Ea_Rb_CopyMigBlockHeader(void);
extern Ea_Rb_stReturn_ten Ea_Rb_MaintainMoveBlock(void);
#if(EA_NUM_SURVIVAL_BLOCKS > 0)
extern void Ea_Rb_MigSurvBlkHandlingInit(void);
extern void Ea_Rb_MigSurvBlkHandling(void);
#endif
#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"

/* EA_PRV_H */
#endif
/* #if (EA_PRESENT == 1) */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
**********************************************************************************************************************
* End of header file: $Name___:$
**********************************************************************************************************************
</BASDKey>*/

