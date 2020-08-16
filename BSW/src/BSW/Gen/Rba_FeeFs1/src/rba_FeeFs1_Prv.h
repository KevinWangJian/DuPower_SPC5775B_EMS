

#ifndef RBA_FEEFS1_PRV_H
#define RBA_FEEFS1_PRV_H

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR FEE
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */


/*
**********************************************************************************************************************
* Defines/Macros
**********************************************************************************************************************
*/
/* General defines */
#define FEE_MAXUINT32               (0xFFFFFFFFuL)
#define FEE_MAXUINT16               (0xFFFFu)
#define FEE_NULL                    (0u)

#define FEE_MARKER_PATTERN          0xCAFEu                 /* Pattern to identify a marker */
#define FEE_NUM_MARKER_IN_HEADER    (FEE_NUM_MARKER_E - 1)  /* A sector has at least 4 states:
                                                               ERASED -> USED -> FULL -> ERASE_REQ
                                                               Value is also in used in Fee_Process.pm */
#define FEE_NO_SEC_IDX_FOUND        0xFFu                   /* No active sector / matching flash bank found */

#define FEE_MARKER_SIZE             8u                      /* Each marker has a size of 8 Bytes (fix value is used in Fee_Process.pm) */
#define FEE_MARKER_CS_SIZE          2u                      /* Size of CRC16 */
#define FEE_LL_DATABUFFSIZE         256u                    /* Size of the internal data buffer used for writing */
                                                            /* (The page buffer size is auto generated) */
#define FEE_LL_CRC_CALC_RESTRICTION FEE_LL_DATABUFFSIZE     /* Restriction for the Crc calculation */

#define FEE_FREE_PAGES_FOR_ERASED_ST    1u                  /* Number of pages containing the erased value */
#define FEE_SIZE_OF_BLOCK_CS            4                   /* Size of block checksum */

/* Special values for sector change counter within the RAM array */
#define FEE_SEC_CHANGE_CNT_RESET_REQ  0xFFFFFFFFuL
#define FEE_SEC_CHANGE_CNT_UNDEF      FEE_SEC_CHANGE_CNT_RESET_REQ
#define FEE_SEC_CHANGE_CNT_ERASED     (FEE_SEC_CHANGE_CNT_RESET_REQ - 1u)

/* Mask for accessing block flags in the configuration and in the block header */
#define FEE_FLAG_SEC_LEVEL_MSK      0x0001u
#define FEE_FLAG_SEC_LEVEL_BP       0u       /* Security level setting is bit 0 within the block flags */
#define FEE_BLK_INT_DOUBLE_STORAGE  1u       /* Internal double block storage definition */

#define FEE_FLAG_DATAFILTERTYPE_ATTR_MSK      0x0006u
#define FEE_FLAG_DATAFILTERTYPE_ATTR_BP       1u

#define FEE_FLAG_INVALID_MSK        0x08u
#define FEE_FLAG_INVALID_BP         3u

#define FEE_FLAG_SURV_ATTR_MSK      0x0010u
#define FEE_FLAG_SURV_ATTR_BP       4u

#define FEE_FLAG_ROBUST_ATTR_MSK    0x0020
#define FEE_FLAG_ROBUST_ATTR_BP     5

#define FEE_FLAG_NOFALLBACK_MSK     0x0040u
#define FEE_FLAG_NOFALLBACK_BP      6u

#define FEE_MASK_BIT7               (uint8)0x80

/* Mask for accessing block flags (upper byte only) */
#define FEE_FLAG_JOBTYPE_MSK        0x0300u
#define FEE_FLAG_JOBTYPE_BP         8u

#define FEE_FLAG_JOBPRIO_MSK        0x0400u
#define FEE_FLAG_JOBPRIO_BP         10u


/* Macros for the conversion of the Sec Level settings:
 * Internal storage level:      Sec Level 1  --> 0 / Sec Level 2 --> 1
 * User Config storage level:   Sec Level 1  --> 1 / Sec Level 2 --> 2 */
#define FEE_INT_TO_USER_STORAGE_TYPE(SEC_LEVEL) ((SEC_LEVEL) + 1u)   /* Convert the Sec Level setting from
                                                                       header/properties == internal to user config format */
#define FEE_CNT_FIRST_COPY          0u       /* Internal counter value for first copy */

/* Erase actions */
#define FEE_NO_SECTOR_TO_ERASE      0xFFu    /* No sector has to be erased */

/* Block header validation */
#define FEE_BLK_HEADER_PREAMBEL             0xA53C96uL                                  /* Pattern of preambel */
#define FEE_BLK_HEADER_PREAMBEL_BYTE_2      (FEE_BLK_HEADER_PREAMBEL & 0xFFu)           /* 0x96 */
#define FEE_BLK_HEADER_PREAMBEL_BYTE_1      ((FEE_BLK_HEADER_PREAMBEL >> 8u) & 0xFFu)   /* 0x3C */
#define FEE_BLK_HEADER_PREAMBEL_BYTE_0      ((FEE_BLK_HEADER_PREAMBEL >> 16u) & 0xFFu)  /* 0xA5 */
#define FEE_BLK_HEADER_SIZE                 14u                                         /* Size of block header in bytes */
#define FEE_BKL_HEADER_REDUCTION	        FEE_VIRTUAL_PAGE_SIZE

/* Calculation of free byte in current sector */
#define FEE_LL_SECTOR_USED_FOR_WRITING      Fee_RdWrOrder_st.xWrAddress
#define FEE_LL_SECTOR_USED_FOR_READING      Fee_RdWrOrder_st.xRdAddress
#define FEE_LL_SECTOR_USED_FOR_COMPARING    Fee_RdWrOrder_st.xCmpAddress
#define FEE_LL_SECTOR_USED_FOR_CRC_CALC     Fee_RdWrOrder_st.xCrcAddress

/* Cache usage*/
#define FEE_INVLD_BLOCK_PROP_IDX        0xFFFFFFFFuL    /* Invalid Fee Idx that can be passed to the block header search function
                                                           in order to ignore the cache during the init phase */
#define FEE_USE_CACHED_ACCESS               0x01u       /* Use the cache method for finding the next block header */
#define FEE_USE_MANUAL_ACCESS               0x00u       /* Search manually for headers */
#define FEE_UPDATE_CACHE_IN_INIT            0x01u       /* Update the cache for fast access in init */
#define FEE_NO_CACHE_UPDATE                 0x00u       /* Do not use the fast access method (only evaluated blocks are added to the cache) */
#define FEE_CACHE_UPD_NOT_COMP_FOR_SECT     0x00u       /* The respective sector was not completely checked */
#define FEE_CACHE_UPD_COMP_FOR_SECT         0x01u       /* The respective sector was checked completely */
#define FEE_CACHE_UPD_COMP_FOR_ALL_SECT     0x02u       /* All sectors have been checked completely */

#define Fee_LLInvalidateAddressInCache(FEEIDX) Fee_LLUpdateAddressInCache(FEEIDX, FEE_CACHE_INIT_VALUE)

/* Fee init defines */
#define FEE_PRV_ST_INIT_RUNNING             0x00u       /* Module is still uninitialized */
#define FEE_PRV_ST_INIT_DONE                0x01u       /* Module has been initialized */

/* Fee reorganization defines */
#define FEE_PRV_ST_REORG_IDLE               0x00u       /* No reorganization is running */
#define FEE_PRV_ST_REORG_STANDARD_RUNNING   0x01u       /* Standard reorganization is running */
#define FEE_PRV_ST_REORG_AFTERB_RUNNING     0x02u       /* "Afterburner" of the reorganization is runnning */

/* Amount of sectors used by the emulation  */
#define FEE_NUM_FLASH_BANKS         Fee_NumFlashBanksUsed_u8  /* Number of sectors which can be used by the Fee */

#if (FEE_RB_ADDONS_CCAS == TRUE)
#define FEE_RB_REQUEST_STOP_MODE            TRUE
#endif

#if(FEE_ROBUST_PROG_ACTIVE != FALSE)
#define FEE_ROBMARKER_BUFF_SIZE             96u
#endif

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u) 	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
#define FEE_FIRSTDATAPAGE_NOTPROGRAMMED 0x00u			/* First data pages in Fee_LlFls2FlsCopy is not yet programmed. */
#define FEE_FIRSTDATAPAGE_PROGRAMMED 	0x01u			/* First data pages in Fee_LlFls2FlsCopy is programmed. */
#endif

/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/

/* Order priority */
typedef enum
{
    FEE_NORMAL_PRIO_E = 0,      /* e.g. if FeeImmediateData is configured to no */
    FEE_HIGH_PRIO_E   = 1       /* e.g. if FeeImmediateData is configured to yes */
}Fee_HlPriority_ten;

/* This enumerator list contains the index inside the order queue.
 * Attention: The order in the enumerator is from Low (FEE_ADAPTER_JOB) to High (FEE_INTERNAL_JOB).
 *            Do not change this order!
 * */
typedef enum
{
    FEE_INTERNAL_JOB,           /* Internal job (reorganization or sector erase) */
    FEE_NVM_JOB,                /* Nvm job */
    FEE_ADAPTER_JOB,            /* Adapter job (e.g. Mx17 Eep) */
    FEE_QUEUE_SIZE              /* Size of the Fee internal queue (each job type has 1 entry) */
}Fee_HlJobType_ten;

typedef struct
{
    uint8*  DataBufferPtr_pu8;  /* Pointer to the read- or write-buffer */
    uint16  FeeIdx_u16;         /* FeeRbBlockPersistentId */
    uint16  BlockPropIdx_u16;   /* Respective block properties table index */
    uint16  Offset_u16;         /* Offset inside block (could be != 0 only for read-orders --> R4.0 Rev1) */
    uint16  Length_u16;         /* Block length, only required for element-read-jobs */
    Fee_HlMode_ten Mode_en;     /* Type of this order: Read, Write, Invalidate */
    Fee_HlPriority_ten Prio_en; /* Priority out of the configuration */
    uint8   SecLevel_u8;        /* Security level out of the configuration */
}Fee_OrderFifo_tst;


/* Hint:
 * For calculation of the sector order (old -> new -> erased -> undef) the sector change counter is a valid criteria.
 * The lowest valid value points to the eldest data, the most current value to the most current data.
 * These following defines are used for an implicit sorting:
 *
 *  +------+------+------+------+------+------+------+------+
 *  |MarkerPattern|Ident | marker content     |marker CRC16 |
 *  +------+------+------+------+------+------+------+------+
 *
 *  Sector headers: 12 times available as default
 *
 *      +------+------+------+------+
 *    0 |Erased| Used | Full |Erase |
 *      +------+------+------+------+
 *    4 |      |      |      |      |
 *      +------+------+------+------+
 *    8 |      |      |      |      |
 *      +------+------+------+------+
 *      |<---->|
 *        Page
 *
 * Erased:  Sector was erased successfully. This marker also contains the sector erase counter
 * Used:    Sector contains user data. This marker will be written first before data is written into a sector.
 *          This marker also contains the sector change counter.
 * Full:    Sector is completely full and must not be considered for searching for the first empty page.
 *          This marker also contains the sector change counter.
 * Erase:   Sector contains no valid data anymore and can be erased in the background task.
 *
 */
enum
{
    FEE_ERASED_MARKER_ID_E = 0x01u, /* Sector was erased successfully */
    FEE_USED_MARKER_ID_E,           /* Sector was used to store data */
    FEE_FULL_MARKER_ID_E,           /* Sector is full */
    FEE_ERASE_REQUEST_ID_E,         /* Sector should be erased */
    FEE_START_MARKER_ID_E,			/* Double storage of USED marker, contains address of first blockheader */
    FEE_CLONE_START_MARKER_ID_E,    /* Marker to indicate that cloning of a defect sector has startet in this sector --> Ifx robust programming */
    FEE_RESERVED_MARKER_ID1_E,      /* Reserved range marker space in the sector header, currently not used! */
    FEE_RESERVED_MARKER_ID2_E,      /*    "       "     "      "   "    "      "         "      "    "   */
    FEE_RESERVED_MARKER_ID3_E,      /*    "       "     "      "   "    "      "         "      "    "   */
    FEE_RESERVED_MARKER_ID4_E,      /*    "       "     "      "   "    "      "         "      "    "   */
    FEE_RESERVED_MARKER_ID5_E,      /*    "       "     "      "   "    "      "         "      "    "   */
    FEE_RESERVED_MARKER_ID6_E,      /*    "       "     "      "   "    "      "         "      "    "   */
    FEE_NUM_MARKER_E                /* Amount of required markers in the sector header + 1 */
};

/* Sector marker structure */
typedef struct
{
    uint16  xPattern;               /* Static marker pattern: 0xCAFE */
    uint8   xIdent;                 /* Ident to identify the marker: 0x01 Erased-Marker, 0x02 Used-Marker, 0x03 Full-Marker, 0x04 Erase-Request */
    uint8   xContent[3];            /* Sector change counter */
    uint16  xChecksum;              /* Crc16 checksum, calculation over Patter, Ident and content */
}Fee_MarkerProp_t;

/* Sector detection type */
typedef struct
{
    uint32  SecChngCnt_u32;         /* Sector change counter */
    uint8   ctErasedMarker_u8;      /* Number of found ERASED markers */
    uint8   ctUsedMarker_u8;        /* Number of found USED markers */
    uint8   ctFullMarker_u8;        /* Number of found FULL markers */
    uint8   ctEraseReq_u8;          /* Number of found ERASE requests */
    uint32  xStartAddr_u32;         /* Address of first blockheader in the sector */
    uint8   ctCloneMarker_u8;       /* Cloning of data has started (only Ifx robust programming algorithm */
}Fee_stSecDet_tst;

/* Sector states */
typedef enum
{
    FEE_SECTOR_STATE_UNDEF_E        = 0,                      /* undefined sector-state --> no marker found */
    FEE_SECTOR_ERASED_E             = FEE_ERASED_MARKER_ID_E, /* sector was erased */
    FEE_SECTOR_USED_E               = FEE_USED_MARKER_ID_E,   /* sector was used to write data */
    FEE_SECTOR_FULL_E               = FEE_FULL_MARKER_ID_E,   /* sector is full */
    FEE_SECTOR_REQUEST2ERASE_E      = FEE_ERASE_REQUEST_ID_E, /* sector could be erased */
    FEE_SECTOR_CONSIDERED_E         = FEE_NUM_MARKER_E        /* sector was considered in function Fee_LLDetectActiveSector */
}Fee_SectorState_ten;

/* Sector order after sort sequence */
typedef struct
{
    uint32 SecChngCnt_u32;                  /* Sector change counter */
    Fee_SectorState_ten SecState_en;        /* Sector state */
    uint8 xPhySecIdx_u8;                    /* Sector index (physical sector) */
}Fee_LLSectorOrder_tst;

/* Fee internal return types */
typedef enum
{
    FEE_ORDER_PENDING_E,            /* The order is still pending*/
    FEE_ORDER_FINISHED_E,           /* The order was finished without error */
    FEE_BLOCK_INVALIDATED_E,        /* The block was invalidated in the block status */
    FEE_ERROR_E,                    /* An error occured, maybe data in flash was not valid */
    FEE_SECTORCHANGE_E,             /* A sector change has to be done */
    FEE_SECTORFULL_E,               /* The sector is full */
    FEE_ABORTED_E,                  /* An order was aborted*/
    FEE_ERASE_SECTOR_E,             /* The sector must be erased */
    FEE_SEARCH_ABORTED_E,           /* Searching was aborted */
    FEE_NUM_RET_VAL_E               /* Number of return values */
}Fee_stRetVal_ten;


/* Flash properties */
typedef struct
{
    uint32  Fee_PhysStartAddress_u32;       /* Physical sector: start address */
    uint32  Fee_PhysEndAddress_u32;         /* physical sector: end address */
    uint32  Fee_LogStartAddress_u32;        /* logical sector: start address */
    uint32  Fee_LogEndAddress_u32;          /* logical sector: end address */
}Fee_FlashProp_tst;

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
 * |     |     |     |     |     |Prio-| Job type  |     |     | Rob |Surv.|(Inv)| DataFilter| Sec-|
 * |     |     |     |     |     |rity |           |     |     |Attr.|Attr.|     |    Type   | lvl |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *
 *
 *  0  ... SecurityLevel      => 0...SingleStorage, 1...DoubleStorage
 * 1+2 ... Data Filter Type   => 0...Dynamic:         Anybody can erase this block (e.g. during migration)
 *                               1...Static:          Only certain users (e.g. repair shops) can erase this block
 *                               2...Permanent:       Only very certain users (e.g. OEM) can erase this block
 *                               3...Super Permanent: Block can never be erased
 *  3 .... Invalid            => 0...Block OK, 1...Block is invalid  --> can be changed by function Fee_InvalidateBlock
 *  4 .... Survival Attribute => 0...No survival, 1... Survival (even without being part of the layout)
 *  5 .... Robustness Attribute (Robustness against data modification during write execution)
 *                            => 0...Deactivated:     No additional checksum is used
 *                            => 1...Activated:       Additional checksum is used
 * 8+9 ... TypeOfBlock        => 0...InternalJob, 1...NvmJob, 2...AdapterJob (e.g. Mx17 Eep adapter)
 *  A .... Priority           => Job priority:        0...FEE_NORMAL_PRIO_E --> FeeImmediateData = No
 *                                                    1...FEE_HIGH_PRIO_E   --> FeeImmediateData = Yes
 */
typedef struct
{
    uint16 BlockPersistentId_u16;
    uint16 Flags_u16;
    uint16 Length_u16;
    void (* const JobEndNotification_pfn) (void);      /* callback function, will be called if a job was successfully finished */
    void (* const JobErrorNotification_pfn) (void);    /* callback function, will be called if a job was finished with an error */
}Fee_BlockPropertiesType_tst;

/* Job types corresponding to the queue index */
enum
{
    FEE_JOB_TYPE_INTERNAL_E = 0,            /* Internal job index */
    FEE_JOB_TYPE_NVM_E      = 1,            /* NvM job index  */
    FEE_JOB_TYPE_ADAPTER_E  = 2             /* Adapter job index */
};

/* State machine types for the function Fee_LLWriteMarker */
typedef enum
{
    FEE_LL_MARKER_INIT_E,                   /* Init state                                    */
    FEE_LL_MARKER_BLK_CHK_E,                /* Perform a blank check over one page           */
    FEE_LL_MARKER_BLK_CHK_WAIT_E,           /* Wait for the blank check order to be finished */
    FEE_LL_MARKER_BLK_CHK_ERROR_E,          /* Differences detected                          */
    FEE_LL_MARKER_BLK_CHK_FINISHED_E,       /* Start write order of the marker               */
    FEE_LL_MARKER_WRITE_WAIT_E,             /* Wait for the write order to be finished       */
    FEE_LL_MARKER_WRITE_ERROR_E,            /* Read or write error                           */
    FEE_LL_MARKER_VERIFY_E,                 /* Verify written marker                         */
    FEE_LL_MARKER_VERIFY_WAIT_E,            /* Wait for verify marker                        */
    FEE_LL_MARKER_VERIFY_FINISHED_E         /* Verify marker finished                        */
}Fee_LLWrMarkerType_ten;

/* State machine types for the function Fee_HLWriteBlock and Fee_HLReadBlock */
typedef enum
{
    FEE_HL_RDWR_BLK_INIT_E,                 /* Init state */
    FEE_HL_SEARCH_BLK_HDR_E,                /* Search block header */
    FEE_HL_READ_BLK_HDR_WAIT_E,                  /* Read block header for redundant blocks */
    FEE_HL_CHECK_BLK_HDR_E,                 /* Check block header for redundant blocks */
    FEE_HL_CALC_BLK_CS_E,                   /* Calculate the user checksum */
    FEE_HL_CHECK_BLK_CS_E,                  /* Verify the block checksum */
    FEE_HL_RD_DATA_FROM_BLK_E,              /* Read the block data */
    FEE_HL_COMP_BLK_E,                      /* Compare the complete block data */

    /* Workaround Overstamp invalid header to reduce init time */
    #if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
    FEE_HL_RD_WAIT_FOR_FLS_E,               /* Wait for the Fls to overstamp an invalid header */
    #endif
    /* END Workaround Overstamp invalid header to reduce init time */

    FEE_HL_WR_BLK_E                         /* Write the block */
}Fee_HLRdWrBlockType_ten;

/* State machine types for the function Fee_LLWriteBlock */
typedef enum
{
    FEE_LL_WR_BLK_INIT_E,                   /* Init state */
    FEE_LL_WR_WRITEHEADER_E,                /* Write the header (and first data bytes) */
    FEE_LL_WR_SIZECHECK_HSR_E,              /* check for space until HSR */
    #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
    FEE_LL_WR_BLANKCHECK_NOFB_WR_E,
    FEE_LL_WR_BLANKCHECK_NOFB_WR_WAIT_E,
    FEE_LL_WR_WRITE_NOFB_MARKER_E,          /* Write the NoFallback marker */
    FEE_LL_WR_WRITE_NOFB_MARKER_WAIT_E,     /* Wait until the programming of the NoFallback marker is finished */
    FEE_LL_WR_FILL_SECTOR_END_E,            /* Changes the active sector and fills the empty pages if necessary */
    FEE_LL_WR_FILL_SECTOR_END_WAIT_E,       /* Wait until the write order to fill the empty pages is finished */
    FEE_LL_WR_FILL_SECTOR_END_ERROR_E,      /* Errors during write occured */
    FEE_LL_WR_WRITE_NOFB_MARKER_ERROR_E,    /* Errors during write occured */
    #endif
    FEE_LL_WR_WRITEHEADER_WAIT_E,           /* Wait until the write order is finished */
    FEE_LL_WR_VERIFYHEADER_E,               /* Verify the header */
    FEE_LL_WR_VERIFYHEADER_WAIT_E,          /* Wait for the verification to end */
    FEE_LL_WR_VERIFYHEADER_ERROR_E,         /* Verify error */
    FEE_LL_WR_WRITEDATA_SEC_A_E,            /* Write the data */
    FEE_LL_WR_WAIT_WRITEDATA_SEC_A_E,       /* Wait until the write order is finished */
    FEE_LL_WR_WRITE_ERROR_E,                /* Error during write (header or data page writes) */

    FEE_LL_WR_WRITE_FULL_MARKER_E,          /* Write the FULL marker */
    FEE_LL_WR_ERASE_SECTOR_E,               /* Erase a sector and write the ERASED marker */
    FEE_LL_WR_WRITE_USED_MARKER_E,          /* Write the USED marker */
    FEE_LL_WR_WRITE_START_MARKER_E,         /* Write the START marker */

    /* Workaround Overstamp invalid header to reduce init time */
    #if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
    FEE_LL_WR_WAIT_FOR_FLS_OVERPROGRAMMING_E,   /* Wait for the Fls to overstamp an invalid header */
    #endif
    /* END Workaround Overstamp invalid header to reduce init time */

    #if(FEE_ROBUST_PROG_ACTIVE != FALSE)
    FEE_LL_WR_WRITEDATA_IFX_HANDLING_E,     /* robust Ifx handling in case of wordline fails */
    #endif
    FEE_LL_WR_VERIFY_BLK_E                  /* Verify the complete data including the block header */

    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    #if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)
    ,FEE_LL_WR_WRITEHDRPG2_E,                /* Write the 2nd header page. */
    FEE_LL_WR_WAIT_WRITEHDRPG2_E            /* Wait until 2nd header page write is completed. */
    #endif
}Fee_LLWrBlockType_ten;

/* State machine types for the function Fee_LLCompBlkInFlash */
typedef enum
{
    FEE_LL_CMP_BLK_INIT_E,                  /* Init state */
    FEE_LL_CMP_HEADER_E,                    /* Compare the complete block header */
    FEE_LL_CMP_WAIT_HEADER_E,               /* Wait for the compare to finish */
    FEE_LL_CMP_CHECK_OVERLAP_E,             /* Check for an overlap */
    FEE_LL_CMP_DATA_SEC_A_E,                /* Check the header compare result and compare the data */
    FEE_LL_CMP_WAIT_DATA_SEC_A_E,           /* Wait for the compare to be finished */
    FEE_LL_CMP_FINISHED_E                   /* Verify the data compare result and reset the state machine */
}Fee_LLCmpBlkType_ten;

/* State machine types for the function Fee_LLCopyData2Buffer */
typedef enum
{
    FEE_LL_CPY_BLK_INIT_E,                  /* Init state */
    FEE_LL_CPY_BLOCK_START_E,               /* Read out the data */
    FEE_LL_CPY_BLOCK_WAIT_E,                /* Wait for the read order to be finished */
    FEE_LL_CPY_BLOCK_ERROR_E,               /* Error in the read function */
    FEE_LL_CPY_BLOCK_FINISHED_E             /* Finish the function or the data transfer */
}Fee_LLCpyBlkType_ten;

/* State machine types for the function Fee_LLCalcBlkCrcInFlash */
typedef enum
{
    FEE_LL_CRC_BLK_INIT_E,                  /* Init state */
    FEE_LL_CRC_RD_HD_PAGE_E,                /* Read the header page */
    FEE_LL_CRC_RD_PAGE_E,                   /* Calculate the block checksums */
    FEE_LL_CRC_CHECK_OVERLAP_E,             /* Check for an overlap */
    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
    FEE_LL_CRC_RD_ROB_PAGE_E,               /* Retry with the robustness checksum */
    FEE_LL_CRC_CHECK_OVERLAP_ROB_E,         /* Check for an overlap */
    FEE_LL_CRC_RD_ROB_PAGE_WAIT_E,          /* Wait until the read access is finished */
    #endif
    FEE_LL_CRC_RD_PAGE_WAIT_E,              /* Wait until the read access is finished */
    FEE_LL_CRC_RD_ERROR_E                   /* Read error case */
}Fee_LLCalcCrcBlkType_ten;

/* State machine types for reading */
typedef enum
{
    FEE_LL_INIT_READ_E                      /* Init state */
    ,FEE_LL_BLANK_CHECK_E					/* Perform a blank check */
    ,FEE_LL_BLANK_CHECK_WAIT_E				/* Wait for the blank check to be finished */
    ,FEE_LL_READ_PAGE_E                     /* Read pages */
    ,FEE_LL_WAIT_READ_PAGE_E                /* Wait for the read order to be finished */
    ,FEE_LL_READ_ERROR_E                    /* Error reaction for read error */
    ,FEE_LL_READ_FINISHED_E                 /* Finish state machine */
    #if (FEE_HEADER_RECHECK_ACTIVE != FALSE)
    #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
    ,FEE_LL_NOFALLBACK_MARKER_CHECK_E
    ,FEE_LL_NOFALLBACK_MARKER_CHECK_WAIT_E
    ,FEE_LL_NOFALLBACK_MARKER_CHECK_FAILED_E
    #endif
    ,FEE_LL_RECHECK_HEADER_E
    ,FEE_LL_RECHECK_HEADER_WAIT_E
    ,FEE_LL_RECHECK_HEADER_FAILED_E
    ,FEE_LL_RECHECK_HEADER_FINISHED_E
    #endif
} Fee_LLRdStateType_ten;

/* States for function Fee_LLCheckErasePattern */
typedef enum
{
    FEE_LL_INIT_BLANK_CHECK_E,              /* Init state */
    FEE_LL_PERFORM_BLANK_CHECK_E,           /* Perform a blank check */
    FEE_LL_WAIT_PERFORM_BLANK_CHECK_E,      /* Wait for the blank check order to be finished */
    FEE_LL_BLANK_CHECK_ERROR_E,             /* Differences detected */
    FEE_LL_BLANK_CHECK_FINISHED_E           /* Finish state machine with success */
} Fee_LLBlankCheckType_ten;

/* State of function Fee_Prv_LLFindEmptyPage */
typedef enum
{
    #if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
    FEE_LL_FINDEMPTYPGE_INIT_E,             /* Initalize find empty page state machine  */
    FEE_LL_FINDEMPTYPGE_CHECK_E,            /* Begin a blank check                      */
    FEE_LL_FINDEMPTYPGE_WAIT_E,             /* Wait until the blank check finished      */
    FEE_LL_FINDEMPTYPGE_RESULT_BLANK_E,     /* Checked chunk was completely blank       */
    FEE_LL_FINDEMPTYPGE_RESULT_NOT_BLANK_E  /* Checked chunk was not completely blank   */
    #else
    FEE_LL_FIND_CURRENT_SECTOR_E,           /* Evaluate the sector with most current values */
    FEE_LL_FIND_LAST_HEADER_E,              /* Search the last block header in the active sector */
    FEE_LL_FINISHED_E                       /* Function finished */
    #endif
}Fee_LLFndEmptyPgeType_ten;

/* State of the function Fee_LLSearchSpecifiedBlkHeader */
typedef enum
{
    FEE_LL_SEARCHBLK_INIT_E,                /* Init state */
    FEE_LL_SEARCHBLK_BLK_HEADER_E           /* Search for the next block header*/
}Fee_LLSearchBlkHdrType_ten;

#if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
/* State of the function Fee_BuildUpCache */
typedef enum
{
    FEE_LL_BLD_UP_CACHE_INIT_E,             /* Init state */
    FEE_LL_BLD_UP_CACHE_READ_E              /* Read out data directly if possible */
}Fee_LLBuildUpCache_ten;

/* State of the function Fee_BuildUpCacheForAllSect */
typedef enum
{
    FEE_LL_BLD_UP_CACHE_ALL_SECT_INIT_E,/* Init case */
    FEE_LL_BLD_UP_CACHE_ALL_SECT_DO_E   /* Build up the cache */
}Fee_LLBuildUpCacheAllSect_ten;
/* FEE_FAST_CACHE_INIT_ACTIVE != FALSE */
#endif

#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
#if (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0)
/* Unknown blcok sector reorganiation without cache: State of the function Fee_LLSearchUnknBlkHeader */
typedef enum
{
    FEE_LL_SEARCHUNKNBLK_INIT_E,            /* Init state */
    FEE_LL_SEARCHUNKNBLK_UNKN_BLK_HEADER_E, /* Search the next unknown block header */
    FEE_LL_SEARCHUNKNBLK_SPEC_BLK_HEADER_E  /* Search the next specific block header */
}Fee_LLSearchUnknBlkHdrType_ten;
#else
/* Unknown block sector reorganiation with cache: states of cache build up function Fee_BuildUpCacheUnknownBlk */
typedef enum
{
    FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_INIT_E,             /* Init state */
    FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_READ_E,             /* Read out data directly if possible */
    FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_VALIDATEDATA_E      /* Validate the data CRC of the uknown block */
}Fee_LLBuildUpUnknownBlkCache_ten;
#endif /* End of (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0) */
#endif /* End of ((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE)) */

/* States for the function Fee_LLSectorReorganization */
typedef enum
{
    FEE_LL_REORG_INIT_E,                    /* Init state */
    FEE_LL_REORG_PREP_SEARCH_BLK_E,         /* Prepare the next block search */
    FEE_LL_REORG_SEARCH_BLK_E,              /* Search for a specific block */
    FEE_LL_REORG_CHECK_BLOCK_CS_E,          /* Evaluate the block checksum */
    FEE_LL_REORG_REDUNDANT_BLK_CHK_E,       /* Check if redundant copy is not lost during sector reorg. */
    FEE_LL_REORG_WRITE_BLOCK_E,             /* Write a block into the latest sector */
#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
    FEE_LL_REORG_SEARCH_UNK_BLK_E,          /* Search for an unknown block */
 #if(FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0) /* Unknown blcok sector reorganiation with cache */
    FEE_LL_REORG_CACHEBUILDUP_UNK_BLK_E,    /* Building of cache for unknown block */
    FEE_LL_REORG_SEARCH_UNK_HDRBLK_WAIT_E,			/* Wait till reading of unknown block header is finished. */
    FEE_LL_REORG_SEARCH_UNK_HDRBLK_READ_ERROR_E,	/* Failure during read of unknown block header. */
    FEE_LL_REORG_SEARCH_UNK_HDRBLK_READ_FINISHED_E,	/* Unknown block header read successful. */
 #endif /* End of (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0) */
#endif /* End of ((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE)) */

    /* Workaround Overstamp invalid header to reduce init time */
    #if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
    FEE_LL_REORG_WAIT_FOR_FLS_E,            /* Wait for the Fls to overstamp an invalid header */
    #endif
    /* END Workaround Overstamp invalid header to reduce init time */

    FEE_LL_REORG_FINISHED_E                 /* Function finished */
}Fee_LLSecReorgType_ten;

/* States for the function Fee_LLRedundantCpyChk */
typedef enum
{
    FEE_LL_REDUNDANT_CPY_CHK_INIT_E,            /* Init state */
    FEE_LL_REDUNDANT_CPY_CHK_SEARCH_HDR_E,      /* Search header of redundant copy */
    FEE_LL_REDUNDANT_CPY_CHK_BLK_CS_E           /* Validate data CRC of redundant copy */
}Fee_LLRedundantCpyChk_ten;

/* States for the function Fee_LLCpyBlkFromFls2Fls */
typedef enum
{
    FEE_LL_CPY_FLS2FLS_INIT_E,                      /* Init state */

    #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
    FEE_LL_CPY_FLS2FLS_WRITE_NOFB_MARKER_E,
    FEE_LL_CPY_FLS2FLS_WAIT_WRITE_NOFB_MARKER_E,
    FEE_LL_CPY_FLS2FLS_WRITE_NOFB_MARKER_ERROR_E,
    FEE_LL_CPY_FLS2FLS_WAIT_FILL_SECTOR_END_E,
    FEE_LL_CPY_FLS2FLS_FILL_SECTOR_END_ERROR_E,
    #endif

    FEE_LL_CPY_FLS2FLS_READ_E,                      /* Read out the complete block (header and data) and finish the function if possible */
    FEE_LL_CPY_FLS2FLS_WAIT_READ_E,                 /* Wait for the read order to be finished */
    FEE_LL_CPY_FLS2FLS_READ_ERROR_E,                /* Read error state */

    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    #if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)
    FEE_LL_CPY_FLS2FLS_HDRPG1_WRITE_E,              /* Write the header page 1 into the new sector */
    FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_WRITE_E,         /* Wait for the header page 1 write order to be finished */
    FEE_LL_CPY_FLS2FLS_HDRPG1_WRITE_ERROR_E,        /* Write error state for header page 1 */
    FEE_LL_CPY_FLS2FLS_HDRPG1_VERIFY_E,             /* Compare the header page 1 write */
    FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_VERIFY_E,        /* Wait for the header page 1 verification to finish */
    FEE_LL_CPY_FLS2FLS_HDRPG1_VERIFY_ERROR_E,       /* Verification error for header page 1 */
    #endif

    FEE_LL_CPY_FLS2FLS_WRITE_E,                     /* Write the data into the new sector */
    FEE_LL_CPY_FLS2FLS_WAIT_WRITE_E,                /* Wait for the write order to be finished */
    FEE_LL_CPY_FLS2FLS_WRITE_ERROR_E,               /* Write error state */
    FEE_LL_CPY_FLS2FLS_VERIFY_E,        			/* Compare the programmed data */
    FEE_LL_CPY_FLS2FLS_WAIT_VERIFY_E,               /* Wait for the verification to finish */
    FEE_LL_CPY_FLS2FLS_VERIFY_ERROR_E,          	/* Verification error */

    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    #if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)
    FEE_LL_CPY_FLS2FLS_HDRPG2_WRITE_E,              /* Write the header page 2 into the new sector */
    FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_WRITE_E,         /* Wait for the header page 2 write order to be finished */
    FEE_LL_CPY_FLS2FLS_HDRPG2_WRITE_ERROR_E,        /* Write error state for header page 2 */
    FEE_LL_CPY_FLS2FLS_HDRPG2_VERIFY_E,             /* Compare the header page 2 write */
    FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_VERIFY_E,        /* Wait for the header page 2 verification to finish */
    FEE_LL_CPY_FLS2FLS_HDRPG2_VERIFY_ERROR_E,       /* Verification error for header page 2 */
    #endif

    FEE_LL_CPY_FLS2FLS_CHECK_ADR_OVERFLOW_E,		/* Data transfer is finished, check a possible address overflow */
    FEE_LL_CPY_FLS2FLS_WRITE_FULL_MARKER_E,         /* Write the FULL marker to the "old" sector */
    FEE_LL_CPY_FLS2FLS_ERASE_SECTOR_E,              /* Erase the sector that will be used as a new USED sector */
    FEE_LL_CPY_FLS2FLS_WRITE_USED_MARKER_E,         /* Write the USED marker to new sector */

    #if(FEE_ROBUST_PROG_ACTIVE != FALSE)
    FEE_LL_CPY_FLS2FLS_ROBUST_IFX_HANDLING_E,       /* robust Ifx handling in case of wordline fails */
    #endif

    #if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
    FEE_LL_CPY_FLS2FLS_ROBUST_SECT_OVERFLOW_E,      /* Robust sector reorganisation when sector overflow occurs during sector reorg. */
    #endif

    FEE_LL_CPY_FLS2FLS_WRITE_START_MARKER_E 		/* Write the START marker to the new sector */
}Fee_LLCpyBlkFls2Fls_ten;

/* States for the function Fee_LlRobustSectorOverflow */
#if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
typedef enum
{
    FEE_LL_ROBUST_SECTOR_OVERFLOW_INIT_E,           /* Init state. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_WR_CM_E,          /* Write Clone marker in the latest sector. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_PREPARE_E,        /* Compute the address and number of bytes for the operation. */

    #if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
    FEE_LL_ROBUST_SECTOR_OVERFLOW_BLANK_CHK_E,      /* Check if the page is blank, transfer only programmed pages. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_BLANK_CHK_WAIT_E, /* Wait for Blank check operation to complete. */
    #endif /* #if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) ) */

    FEE_LL_ROBUST_SECTOR_OVERFLOW_READ_PAGE_E,      /* Read out the programmed page in an internal buffer. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_READ_PAGE_WAIT_E, /* Wait for Read operation to complete. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_E,      /* Copy data to new sector. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_WAIT_E, /* Wait for Write operation to complete. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_DATA_E,    /* Verify the copied data. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_DATA_WAIT_E,/* Wait for Verify operation to complete. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_SUCCESS_E, /* Check if more bytes are left to be programmed. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_WR_UM_E,          /* Write Used marker in the latest sector. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_SORT_SECT_E,      /* Sort sectors */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_ERROR_E,          /* Error state for all kinds of error in this state machine. */
    FEE_LL_ROBUST_SECTOR_OVERFLOW_ERASE_E           /* Re-erase the older sector, this state is reached for error handling. */
}Fee_LLRobustSectOverflow_ten;
#endif /* #if defined (FEE_PRV_ROBUST_SECT_OVERFLOW) */

/* Read / write order type */
typedef struct
{
    uint32                              xRdAddress;                     /* Address for reading (Fee_LLReadBlock) */
    uint32                              xWrAddress;                     /* Address for writing (Fee_LLWriteBlock) */
    uint32                              xCmpAddress;                    /* Address for comparing (Fee_LLCompBlkInFlash) */
    uint32                              xCrcAddress;                    /* Address for the CRC (Fee_LLCompBlkInFlash) */
    uint32                              xCpyAddress;                    /* Address for copying (Fee_LLCompBlkInFlash) */
    uint32                              AdrHdSearchStart_u32;           /* Start address for the header search after reloads */
    uint32                              xStartAddrNextSector_u32;		/* Payload of START-Marker, contains the expected address of the 1. blockheader */

/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)
    uint32                              xHdPg2Address;                   /* Address for writing the header 2nd page. */
#endif

#if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
    uint32                              LastProgrammedAddress_u32;        /* Last programmed page during cache build up. */
    uint32                              LastValidHdrAddress_u32;          /* Last valid header found during cache build up. */
#endif

    Fee_LLSecReorgType_ten              Fee_LLSecReorg_en;                /* State machine for the sector reorganization */
    Fee_LLRedundantCpyChk_ten           Fee_LLRedundantCpyChk_en;         /* State machine for checking redundant copy */
    Fee_LLCpyBlkFls2Fls_ten             Fee_LLCpyBlkFls2Fls_en;           /* State machine for copying one block from one sector to another one */

#if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
    Fee_LLRobustSectOverflow_ten        Fee_LLRobustSectOverflow_en;      /* LL state machine for Robust sector overflow */
#endif

    Fee_HLRdWrBlockType_ten             Fee_HLWrBlock_en;                  /* HL state machine for writing a block */

#if(FEE_RB_MAINTAIN != FALSE)
    Fee_HLRdWrBlockType_ten             Fee_HLMtBlock_en;                  /* HL state machine for maintaining a block */
 #endif

    Fee_LLWrBlockType_ten               Fee_LLWrBlock_en;                  /* LL State machine for writing a block */
    Fee_HLRdWrBlockType_ten             Fee_HLRdBlock;                     /* state machine for reading a block High Level */
    Fee_LLWrBlockType_ten               Fee_LLNextUsedWrBlock_en;          /* LL state for saving the next write state if a USED marker is necessary in between */
    Fee_LLWrBlockType_ten               Fee_LLNextEraseWrBlock_en;         /* LL state for saving the next write state if an erase operation is necessary in between */
    Fee_LLCmpBlkType_ten                Fee_LLCompBlk;                     /* LL state machine for comparing data */
    Fee_LLCpyBlkType_ten                Fee_LLCopyBlk_en;                  /* LL state machine for copying data from the flash to the user buffer */
    Fee_LLCalcCrcBlkType_ten            Fee_LLCalcCrcBlk_en;               /* LL state machine for calculating the checksum of a block inside the flash */
    Fee_LLWrMarkerType_ten              Fee_LLWrMarker_en;                 /* LL state machine for writing a sector marker */
    Fee_LLRdStateType_ten               Fee_LLRdState_en;                  /* LL state machine to read a specified address in the sector */
    Fee_LLBlankCheckType_ten            Fee_LLBlankCheckState_en;          /* LL State machine to perform a blank check */
    Fee_LLFndEmptyPgeType_ten           Fee_LLFindEmptyPageState_en;       /* LL state machine to find an empty page within one sector */
    Fee_LLSearchBlkHdrType_ten          Fee_LLSearchBlkHdr_en;             /* LL state machine to find a specified block header */

#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
 #if(FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0) /* Unknown block sector reorganiation without cache */
    Fee_LLSearchUnknBlkHdrType_ten      Fee_LLSearchUnknBlkHdr_en;          /* LL state machine to find an unknown block header */
 #else /* Unknown blcok sector reorganiation with cache */
    uint32                              Fee_UnknownBlkCacheAdd_u32;         /* Address till where the cache for unknown block is scanned */
    uint16                              Fee_UnknownBlkCacheIdx_u16;         /* Index till which the cache for unknown block is built */
    Fee_LLBuildUpUnknownBlkCache_ten    Fee_LLBuildUpCacheUnknownBlk_en;    /* LL state machine to build up the cache for unknown blocks */
 #endif
#endif

#if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
    Fee_LLBuildUpCache_ten              Fee_LLBuildUpCache_en;              /* LL state machine to build up the cache */
    Fee_LLBuildUpCacheAllSect_ten       Fee_LLBuildUpCacheAllSect_en;       /* LL state machine to build up the cache for all sectors */
#endif
} Fee_RdWrOrder_tst;

/* Block header info type */
typedef struct
{
    uint32 AdrBlkHeader_u32;    /* Read address for for the function Fee_LLReadBlock and Fee_LLCpyBlkFromFls2Fls */
    uint32 BlkCrc32_u32;        /* Block data checksum */
    uint16 HdrCrc16_u16;        /* Block header checksum (start value for block data checksum) */
    uint16 BlkLength_u16;       /* Extracted block length from the block header */
    uint16 FeeIndex_u16;        /* Fee Index */
    uint8  BlkStatus_u8;        /* Block status */
}Fee_GlobInfoLastRdHeader_tst;

/* Block write type */
typedef struct
{
    uint16  BytesAlrdyConsid_u16;   /* Write offset in user data */
    uint16  BytesAlrdyCompared_u16;    /* Number of bytes already compared */
    uint16  Bytes2Read_u16;          /* Number of bytes to read */
    uint8   CompareResult_u8;       /* Result of last Fls_Compare */
    uint8   cntWriteRetry_u8;       /* Count number of write retries */
    uint8   cntCopies_u8;           /* Count number of written copies */
}Fee_GlobInfoWrBlock_tst;

/* Sector reorganization type */
typedef struct
{
    uint32 xRdAddress_u32;
    uint16 xNumBytesAlrdyCopied_u16;
    uint16 xNumBytesLeftToRdWr_u16;
    uint8  xCntCopies_u8;
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    uint8  xFirstDataPgPgm_u8;
#endif
}Fee_LLSecReorgStruct_tst;

/* Erase sector types */
typedef enum
{
    FEE_ERASESEC_IDLE_E = 0,        /* Idle state */
    FEE_ERASESEC_CHECK_CACHE_E,     /* Check of cache */
    FEE_ERASESEC_START_E,           /* Erase sequence started */
    FEE_ERASESEC_DO_E,              /* Wait until erasing was finished */
    FEE_ERASESEC_WRITE_MARKER_E,    /* Write the sector ERASED marker */
    FEE_ERASESEC_ERROR_E            /* Error state */
}Fee_LLEraseStateType_ten;

/* Erase Order type */
typedef struct
{
    Fee_LLEraseStateType_ten EraseState_en; /* State machine state */
    uint8   xPhySectorIdx_u8;               /* Idx of sector that should get erased  */
}Fee_LLEraseOrderType_tst;

/* Block header structure */
typedef struct
{
    uint8   Preamble_au8[3];    /* Preambel (0xA53C96) */
    uint8   BlkStatus_u8;       /* Block status, contains information like security level, etc. */
    uint16  FeeIndex_u16;       /* FeeIndex */
    uint16  BlkLength_u16;      /* Block length without header and block checksum */
    uint16  HdrCrc16_u16;       /* Header checksum, start value is 0xCAFE */
    uint32  BlkCrc32_u32;       /* Block data checksum */
}Fee_BlkHeader_tst;

/* Linked function structure */
typedef struct
{
    void(* Fee_ResetUsedSectors_pfn)(void);     /* Function for resetting the amount of used sectors */
}Fee_LinkedFunctions_tst;

#if (FEE_PRV_DEBUG_MONITOR != FALSE)
#define FEE_DBM_ERROR_ENTRIES   15

typedef enum
{
    FEE_DBM_ERROR_ERASE_FCT_E,        /* Used in function Fee_LLEraseSector */
    FEE_DBM_ERROR_LLMARKER_FCT_E,     /* USed in function Fee_LLWriteMarker */
    FEE_DBM_ERROR_XX_E                /* not used yet....                   */
} Fee_DebugMonitoringFct_ten;

typedef struct
{
    uint32                       xSecChngCntVal;             /* value of sector change counter while error occurs */
    uint16                       FeeBlkIdx;                  /* if the error couldn't be assigned to a NvmBlock, this is 0xFFFF */
    Fee_DebugMonitoringFct_ten   xError;                     /* error number */
    uint8                        xErrorInfo;                 /* error info, if necessary */
} FeeDBMErrInfo_tst;

typedef struct
{
    FeeDBMErrInfo_tst  xErrorEntry[FEE_DBM_ERROR_ENTRIES];  /* array of a structure with detail info to the errors */
    uint8   idxNewEntry;                /* index points on the next free entry in the xErrorEntry buffer */
    uint8   ctBuffOverflow;             /* counter countrs how often the FEE_DBM_ERROR_ENTRIES error overflow. Startvalue is 1, used for ProtRAM validation! */
} Fee_DebugMonitoring_tst;

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
extern Fee_DebugMonitoring_tst Fee_DebugMonitoring;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
#endif

#if(FEE_ROBUST_PROG_ACTIVE != FALSE)
/* Ifx robust programming */
typedef enum
{
    FEE_ROB_IFX_INIT,
    FEE_ROB_IFX_MARK_SECTOR,
    FEE_ROB_IFX_STORE_BUFFER,
    FEE_ROB_IFX_STORE_BUFFER_WAIT,
    FEE_ROB_IFX_COPY_DATA,
    FEE_ROB_IFX_STORE_COPY_WAIT,
    FEE_ROB_IFX_ERASE_SECTOR,
    FEE_ROB_IFX_WRITE_USED_MARK_SECTOR,
    FEE_ROB_SORT_SECTOR,
    FEE_ROB_IFX_FINISHED
}Fee_RobIfxHdl_e;

typedef struct
{
    Fls_AddressType xStartAddress;
    uint8* DataBuffer;
    Fls_LengthType numBytes;
    uint16 offInBuf_u16;
}Fee_IfxRobustProgramming_t;

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
extern Fee_IfxRobustProgramming_t Fee_IfxRobustProgramming_s;
extern Fee_RobIfxHdl_e Fee_RobIfxHdl;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_RobIfxHandling(uint8 xActLogWrSect_u8);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#endif

#if ((FEE_RB_MAINTAIN != FALSE) && (FEE_NO_FALLBACK_ACTIVE != FALSE))
/* Additional MainFunction write states in case NoFallback is activated */
typedef enum
{
    FEE_WRITE_NOFB_IDLE_E = 0,      /* Idle state */
    FEE_WRITE_NOFB_MAINTAIN_E,      /* Maintain a NoFallback block */
    FEE_WRITE_NOFB_BLOCK_E          /* Write a NoFallback block */
}Fee_WriteStateNoFb_ten;
#endif

typedef struct
{
    uint32 Fee_Totalfree_bytes;    /* Total number of free bytes  */
    uint32 Fee_hardThreshold;      /* Hard Threshold configures */
    uint32 Fee_softThershold;      /* Soft therosold configured*/

}Fee_FreeByte_thrshold_t;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/
/* Structures and variables */
#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
extern CONST(Fee_FlashProp_tst, FEE_CONST)          Fee_FlashProp_st[FEE_NUM_FLASH_BANKS_AVAILABLE];
extern CONST (MemIf_JobResultType, AUTOMATIC)       Fee_JobTypeMapping[FEE_NUM_RET_VAL_E];
extern CONST (Fee_LinkedFunctions_tst, FEE_CONST)   Fee_LinkedFunctions_cst;
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
extern P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)       Fee_PageBytePtr_cpu8;
extern VAR(Fee_RdWrOrder_tst, AUTOMATIC)            Fee_RdWrOrder_st;
extern VAR(Fee_LLSectorOrder_tst, AUTOMATIC)        Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS_AVAILABLE];
extern VAR(Fee_LLEraseOrderType_tst, AUTOMATIC)     Fee_LLEraseOrder_st;
extern VAR(Fee_OrderFifo_tst, AUTOMATIC)            Fee_OrderFifo_st[FEE_QUEUE_SIZE];
extern VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC) Fee_GlobInfoLastRdHeader_st;
extern VAR(Fee_GlobInfoWrBlock_tst, FEE_VAR)        Fee_GlobInfoWrBlock_st;
extern VAR(Fee_LLSecReorgStruct_tst, FEE_VAR)       Fee_LLSecReorgStruct_st;
extern VAR(MemIf_JobResultType, AUTOMATIC)          Fee_JobResult[FEE_QUEUE_SIZE];
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
extern CONSTP2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)  Fee_MarkerBufBytePtr_cpu8;
extern CONSTP2VAR(uint8, AUTOMATIC, FEE_APPL_DATA)  Fee_DataBytePtr_cpu8;
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
extern VAR(uint8, FEE_VAR)                          Fee_Prv_stInit_u8;
extern VAR(uint8, FEE_VAR)                          Fee_Prv_stReorg_u8;
extern VAR(uint8, FEE_VAR)                          Fee_NumFlashBanksUsed_u8;
extern VAR(uint8, AUTOMATIC)                        Fee_idxActQueueBackUp;

/* Buffer to hold 2nd header page contents. */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
extern VAR(uint8, AUTOMATIC) Fee_hdr2Buffer_au8[FEE_PAGE_LEN];
#endif

/* Workaround Overstamp invalid header to reduce init time */
#if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
extern VAR(uint8, AUTOMATIC)                        Fee_hdrBuffer_au8[FEE_PAGE_LEN];
#endif
/* END Workaround Overstamp invalid header to reduce init time */

#define FEE_STOP_SEC_VAR_INIT_8
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
extern VAR(MemIf_StatusType, FEE_VAR)               Fee_GlobModuleState_st;
extern VAR(Fee_Rb_WorkingStateType_ten, AUTOMATIC)  Fee_Rb_WorkingStateBackUp_en;
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
extern VAR(uint8, AUTOMATIC)                        Fee_idxLLSectorOrder_au8[FEE_NUM_FLASH_BANKS_AVAILABLE];
extern VAR(uint8, FEE_VAR)                          Fee_idxActQueue_u8;
extern VAR(uint8, FEE_CONST)                        Fee_CacheUpdCompForSect_au8[FEE_NUM_FLASH_BANKS_AVAILABLE];
extern VAR(uint8, AUTOMATIC)                        Fee_RdWrRetries_u8;

#if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
extern VAR(boolean, AUTOMATIC) Fee_Prv_stSuspendActiv_b;
extern VAR(boolean, AUTOMATIC) Fee_Prv_stHardReOrgErase_b;
#endif

#if (FEE_RB_ADDONS_CCAS == TRUE)
extern VAR(boolean, AUTOMATIC) Fee_Rb_stRequestStopMode_b;
#endif

#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"
extern VAR(uint32, AUTOMATIC)                       Fee_llMarkerPageBuf_au32[FEE_SEC_HEADER_SIZE / 4u];
extern VAR(uint32, FEE_CONST)                       Fee_Cache_au32[FEE_NUM_BLOCKS];

#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
extern VAR(uint32, AUTOMATIC)                       Fee_DataByteStartCrc_u32;
#endif

#define FEE_STOP_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_32_SECURED
#include "Fee_MemMap.h"
extern VAR(uint32, AUTOMATIC)                       Fee_llPageBuf_au32[(FEE_LL_PAGEBUFFSIZE / 4u) + 2u];
extern VAR(uint32, AUTOMATIC)                       Fee_llDataBuf_au32[FEE_LL_DATABUFFSIZE / 4u];
#define FEE_STOP_SEC_VAR_CLEARED_32_SECURED
#include "Fee_MemMap.h"

#ifdef FEE_PRV_USE_ROM_TABLE
#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
extern CONST(Fee_BlockPropertiesType_tst, FEE_CONST)  Fee_BlockProperties_st[FEE_NUM_BLOCKS];
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
#else
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
extern VAR(Fee_BlockPropertiesType_tst, AUTOMATIC)  Fee_BlockProperties_st[FEE_NUM_BLOCKS];
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
#endif

#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
extern Fee_WriteStateNoFb_ten Fee_WriteStateNoFb_en;
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"
extern VAR(uint32, AUTOMATIC)   Fee_Rb_NoFallback_RemAdr_u32;
#define FEE_STOP_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
extern VAR(boolean, AUTOMATIC)  Fee_Rb_NoFallback_LastBlockCfg_b;
extern VAR(boolean, AUTOMATIC)  Fee_Rb_InvalidateOldCopy_b;
extern VAR(boolean, AUTOMATIC)  Fee_Rb_MaintainRun_b;
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"

#define FEE_START_SEC_CONST_8
#include "Fee_MemMap.h"
extern const uint8 Fee_NoFallbackMarkerPattern[FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN];
#define FEE_STOP_SEC_CONST_8
#include "Fee_MemMap.h"
#endif

#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) && (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0))
/* Unknown blcok sector reorganiation with cache */
#define FEE_START_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"
extern VAR(uint32, AUTOMATIC) Fee_UnknownBlkCache_Addr_au32[FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE];   /* Address of unknown block. */
#define FEE_STOP_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_16
#include "Fee_MemMap.h"
extern VAR(uint16, AUTOMATIC) Fee_UnknownBlkCache_FeeIndex_u16[FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE]; /* Index of unknown block. */
#define FEE_STOP_SEC_VAR_CLEARED_16
#include "Fee_MemMap.h"
#endif

/* Lower Layer functions of the Fee */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern FUNC(uint32, FEE_CODE) Fee_CalculateNumOfFreeBytesInCurSector(VAR(uint32, FEE_VAR) DataEndAdr_u32);
extern FUNC(void, FEE_CODE)   Fee_InitVarAndState(void);
extern FUNC(void, FEE_CODE)   Fee_InitCache(void);
extern FUNC(void, FEE_CODE)   Fee_InitOrderFifoBuffer(void);

/* Active sector detection */
extern FUNC(void ,FEE_CODE)   Fee_LLSearchSectors(P2VAR(Fee_stSecDet_tst, AUTOMATIC, FEE_APPL_DATA) Fee_stSecDet_ps);
extern FUNC(uint8, FEE_CODE)  Fee_LLDetectActiveSector(void);
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLFindEmptyPage(uint8 PhySectIdxUsedSect_u8);
extern FUNC(uint8, FEE_CODE)  Fee_GetMostCurrentSectorIdx(void);
extern FUNC(void, FEE_CODE)   Fee_CheckErasedSectorEmpty(void);
extern FUNC(uint8, FEE_CODE)  Fee_GetPhysSectorByAddress(VAR(uint32, AUTOMATIC) Address_u32);

/* Marker handling */
extern FUNC(Fee_stRetVal_ten,FEE_CODE)  Fee_LLWriteMarker(VAR(uint8, AUTOMATIC) PhySectIdx_u8,
                                                          VAR(uint8, AUTOMATIC) MarkerID_u8);

/* Erase functions */
extern FUNC(Fee_stRetVal_ten,FEE_CODE)  Fee_LLEraseSector(void);
extern FUNC(void,FEE_CODE)              Fee_LLSetEraseSector(VAR(uint8, AUTOMATIC) EraseLogIdx);

/* Block header access */
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLSearchNextBlkHeader(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Fee_GlobInfoLastRdHeader_ptr,
                                                                  VAR(uint8, AUTOMATIC) CachedAccess_u8,
                                                                  VAR(uint8, AUTOMATIC) FastCacheUpdate_u8,
                                                                  VAR(boolean, AUTOMATIC) xForcePageBufReload_b,
                                                                  VAR(uint32, AUTOMATIC) strAddrHdrSearch);

extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLSearchSpecifiedBlkHeader(VAR(uint16, AUTOMATIC) FeeIdx_u16,
                                                                       P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) LastHdrAddr_ptr,
                                                                       P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) GlobBlkHdr_ptr,
                                                                       VAR(boolean, AUTOMATIC) SearchRetry_b);

#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
/* Unknown blcok sector reorganiation without cache */
#if(FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0)
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLSearchUnknownBlkHeader(P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) StartHdrAddr_ptr,
                                                                     P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) LastHdrAddr_ptr,
                                                                     P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) GlobBlkHdr_ptr,
                                                                     P2VAR(boolean, AUTOMATIC, FEE_APPL_DATA) SearchRetry_ptr);
#else
/* Unknown blcok sector reorganiation with cache */
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_BuildUpCacheUnknownBlk(void);
#endif /* (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0) */
#endif /* ((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE)) */

extern FUNC(uint32, FEE_CODE) Fee_LLGetSecStartAddress(VAR(uint8, AUTOMATIC) xPhySectorIdx_u8);
extern FUNC(uint32, FEE_CODE) Fee_LLGetSecEndAddress(VAR(uint8, AUTOMATIC) xPhySectorIdx_u8);

/* Verification and handling of blocks */
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCompBlkInFlash(P2CONST(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) HeaderInfo_pcst,
                                                             P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) Data_pcu8);
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCalcBlkCrcInFlash(P2CONST(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) HeaderInfo_pcst);
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCpyBlkFromFls2Fls(P2CONST(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Fee_GlobInfoLastRdHeader_pcst, boolean Fee_WriteTwice_b);
#if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LlRobustSectorOverflow(void);
#endif
extern FUNC(void, FEE_CODE)             Fee_LLPrepMarkerBufWithMarkerData(P2CONST(Fee_MarkerProp_t, AUTOMATIC, FEE_APPL_DATA) Marker_pcst,
                                                                          P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) MarkerBuf_pu8);
extern FUNC(void, FEE_CODE)             Fee_LLCopyPageBuff2Marker(P2VAR(Fee_MarkerProp_t, AUTOMATIC, FEE_APPL_DATA) Marker_pst,
                                                                  P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8);
extern FUNC(void, FEE_CODE) 			Fee_LLPrepPageBufWithHdrDataStart(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) HeaderInfo_pst);
extern FUNC(void, FEE_CODE) 			Fee_LLPrepPageBufWithHdrDataEnd(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) HeaderInfo_pst,
                                                                               P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) Data_pcu8,
                                                                               VAR(uint32, AUTOMATIC) BlkCrc32_u32);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

LOCAL_INLINE FUNC(void, FEE_CODE)       Fee_LLCopyPageBuff2HeaderStart(P2VAR(Fee_BlkHeader_tst, AUTOMATIC, FEE_APPL_DATA) BlkHdr_pst,
                                                                       P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8);
#if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
LOCAL_INLINE FUNC(void, FEE_CODE)       Fee_LLCopyPageBuff2HeaderIdxAndCrc(P2VAR(Fee_BlkHeader_tst, AUTOMATIC, FEE_APPL_DATA) BlkHdr_pst,
                                                                           P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8);

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
#if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_SearchLastBlkHeader(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Fee_GlobInfoLastRdHeader_ptr);
#endif
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#endif

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"

extern FUNC(uint32, FEE_CODE)           Fee_SearchHighestCacheEntry(VAR(uint32,FEE_VAR) UpperBoundary_u32, VAR(uint8, FEE_VAR) SectIdx_u8);
extern FUNC(void, FEE_CODE)             Fee_InvalidateCacheByAddress(VAR(uint32,FEE_VAR) xAddress_u32);

extern FUNC(void, FEE_CODE)             Fee_LLCopyPageBuff2HeaderMid(P2VAR(Fee_BlkHeader_tst, AUTOMATIC, FEE_APPL_DATA) BlkHdr_pst,
                                                                     P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8);
extern FUNC(void, FEE_CODE)             Fee_LLCopyPageBuff2HeaderEnd(P2VAR(Fee_BlkHeader_tst, AUTOMATIC, FEE_APPL_DATA) BlkHdr_pst,
                                                                     P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8);
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCopyData2Buffer(P2CONST(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Fee_GlobInfoLastRdHeader_pcst,
                                                                  P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataPtr_pu8,
                                                                  VAR(uint16, FEE_VAR) DataOffset_u16,
                                                                  VAR(uint16, FEE_VAR) DataLength_u16);
extern FUNC(void, FEE_CODE)             Fee_IncAddressInsideSector(P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) Address_u32,
                                                                   VAR(uint16, FEE_VAR) numBytes_u16,
                                                                   VAR(boolean, FEE_VAR) EnsurePageAlign_b);

/* Sector reorganization */
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCheckReorganizationNeed(VAR(uint32, AUTOMATIC) Threshold_u32,
                                                                      VAR(uint16, AUTOMATIC) DataLength_u16);
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLSectorReorganization(P2VAR(boolean, AUTOMATIC, FEE_APPL_DATA) SectReorgInterSt_pb);

/* Block writes */
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_HLWriteBlock(void);
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLWriteBlock(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Info_ptr,
                                                         P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) Data_pcu8);

/* Block reading */
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_HLReadBlock(void);
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLReadBlock(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Info_ptr,
                                                        P2VAR(uint8,AUTOMATIC, FEE_APPL_DATA) Data_ptr);
 #if(FEE_RB_MAINTAIN != FALSE)
    /* Block maintaining*/
    extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_HLMaintainBlock(void);
 #endif

/* Order handling */
extern FUNC(Std_ReturnType, FEE_CODE)   Fee_HLPlaceOrder(VAR(uint16, AUTOMATIC) Blocknumber_u16,
                                                         VAR(uint16, AUTOMATIC) Offset_u16,
                                                         P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr_pu8,
                                                         VAR(uint16, AUTOMATIC) Length_16,
                                                         VAR(Fee_HlMode_ten, AUTOMATIC) Mode_en);


/* Cache handling */
extern FUNC(uint32, FEE_CODE) Fee_LLGetAddressFromCache(VAR(uint16, AUTOMATIC) FeeIdx_u16);
extern FUNC(boolean, FEE_CODE) Fee_LLCheckAddressInCache(VAR(uint32, AUTOMATIC) AdrInSector_u32);
extern FUNC(void, FEE_CODE)   Fee_LLUpdateAddressInCache(VAR(uint16, AUTOMATIC) FeeIdx_u16,
                                                         VAR(uint32, AUTOMATIC) Addr_u32);
extern FUNC(void, FEE_CODE)  Fee_LLUpdateCacheStForSect(VAR(uint8, AUTOMATIC) PhySecIdx_u8);
extern FUNC(void, FEE_CODE)  Fee_LLEraseCacheStForSect(VAR(uint8, AUTOMATIC) PhySecIdx_u8);
extern FUNC(uint8, FEE_CODE) Fee_LLGetCacheUpdateStForSect(VAR(uint8, AUTOMATIC) PhySecIdx_u8);
extern FUNC(uint8, FEE_CODE) Fee_LLGetCacheUpdateStForAllSect(void);
extern FUNC(boolean, FEE_CODE) Fee_SrvBinarySearchInBlockProp(VAR(uint16, AUTOMATIC) FeeIdx_u16,
                                                              P2VAR(uint16, AUTOMATIC, FEE_APPL_DATA) CacheIdx_pu16);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

#if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
LOCAL_INLINE FUNC(boolean, FEE_CODE) Fee_SrvBinarySearchInBlockPropFast(VAR(uint16, AUTOMATIC) FeeIdx_u16,
                                                                        P2VAR(uint16, AUTOMATIC, FEE_APPL_DATA) CacheIdx_pu16);

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_BuildUpCache(VAR(uint32, AUTOMATIC) StartAdr_u32,
                                                         VAR(uint32, AUTOMATIC) EndAdr_u32);
extern FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_BuildUpCacheForAllSect(void);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* FEE_FAST_CACHE_INIT_ACTIVE != FALSE */
#endif

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
/* Services */
extern FUNC(void, FEE_CODE)  Fee_SrvMemSet8(P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) xDest_pu8,
                                            VAR(uint32, FEE_VAR) xPattern_u32,
                                            VAR(uint32, FEE_VAR) numBytes_u32);
extern FUNC(void, FEE_CODE)  Fee_SrvMemCopy8(P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) xDest_pu8,
                                             P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) xSrc_pcu8,
                                             VAR(uint32, FEE_VAR) numBytes_u32);
extern FUNC(void, FEE_CODE)  Fee_SrvSetFifoMode(VAR(Fee_HlMode_ten, AUTOMATIC) Mode_en,
                                                VAR(uint16, AUTOMATIC) xJobType_u16);
extern FUNC(Fee_HlMode_ten, FEE_CODE) Fee_SrvGetFifoMode(VAR(uint16, AUTOMATIC) xJobType_u16);
extern FUNC(void, FEE_CODE)           Fee_LoadNextOrder(void);
extern FUNC(uint8, FEE_CODE)          Fee_SearchNextOrder(boolean isIntOrder_b);
extern FUNC(void, FEE_CODE)           Fee_UpdateStatus(void);
extern FUNC(void, FEE_CODE)           Fee_TriggerHardSectorReorg(VAR(Fee_Rb_WorkingStateType_ten, FEE_VAR) WorkingState_en);

extern FUNC(Std_ReturnType, FEE_CODE) Fee_CheckBlockCfg(VAR(uint8, AUTOMATIC)  ApiId_u8,
                                                           VAR(uint16, AUTOMATIC) BlockNum_u16);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_CheckModuleSt(VAR(uint8, AUTOMATIC)  ApiId_u8);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_CheckAdrPtr(VAR(uint8, AUTOMATIC) ApiId_u8,
                                                      P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr_pcu8);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_CheckBlkOfs(VAR(uint8, AUTOMATIC) ApiId_u8,
                                                      VAR(uint16, AUTOMATIC) BlockNum_u16,
                                                      VAR(uint16, AUTOMATIC) BlockOfs_u16);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_CheckBlkLen(VAR(uint8, AUTOMATIC) ApiId_u8,
                                                      VAR(uint16, AUTOMATIC) BlockNum_u16,
                                                      VAR(uint16, AUTOMATIC) BlockOfs_u16,
                                                      VAR(uint16, AUTOMATIC) BlockLen_u16);

/* Miscellaneous */
extern FUNC(void, FEE_CODE)   Fee_CheckFlsJobResult(void);
extern void (* Fee_Prv_ResetUsedSectors_pfn)(void);

#if (FEE_PRV_DEBUG_MONITOR != FALSE)
extern FUNC(void ,FEE_CODE) Fee_DBM_RepError(VAR(uint16,FEE_VAR) FeeBlkIdx, VAR(Fee_DebugMonitoringFct_ten,FEE_VAR) xError, VAR(uint8,FEE_VAR) xErrorInfo);
#endif
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/*
**********************************************************************************************************************
* Inline functions (Necessary for fastening up the start up time)
**********************************************************************************************************************
*/
/**
 *********************************************************************
 * Fee_LLCopyPageBuff2HeaderStart(): Extract the start of the block header data
 *
 * This function extracts the preamble of the block header data out
 * of the page buffer (called every 8th byte of the flash).
 *
 * Hint: Block header structure:
 *       {
 *          uint8   Preamble_au8[3];
 *          uint8   BlkStatus_u8;
 *          uint16  FeeIndex_u16;
 *          uint16  BlkLength_u16;
 *          uint16  HdrCrc16_u16;
 *          uint32  BlkCrc32_u32;
 *       }Fee_BlkHeader_tst;
 *
 * \param    BlkHdr_pst:    Pointer to the block header that was
 *                          found in the flash.
 * \param    PageBuf_pu8:   Pointer to the page buffer
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
LOCAL_INLINE FUNC(void, FEE_CODE) Fee_LLCopyPageBuff2HeaderStart(P2VAR(Fee_BlkHeader_tst, AUTOMATIC, FEE_APPL_DATA) BlkHdr_pst,
                                                                 P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8)
{
    BlkHdr_pst->Preamble_au8[0] = PageBuf_pcu8[0];      /* 0xA53C96 <- [0]: A5, [1]: 3C, [2]: 96 */
    BlkHdr_pst->Preamble_au8[1] = PageBuf_pcu8[1];
    BlkHdr_pst->Preamble_au8[2] = PageBuf_pcu8[2];
}


#if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
/**
 *********************************************************************
 * Fee_LLCopyPageBuff2HeaderIdxAndCrc(): Extract the header checksum
 *  and the block index out of the block header data
 *
 * This function extracts the block header data out of the page buffer.
 *
 * Hint: Block header structure:
 *       {
 *          uint8   Preamble_au8[3];
 *          uint8   BlkStatus_u8;
 *          uint16  FeeIndex_u16;
 *          uint16  BlkLength_u16;
 *          uint16  HdrCrc16_u16;
 *          uint32  BlkCrc32_u32;
 *       }Fee_BlkHeader_tst;
 *
 * \param    BlkHdr_pst:    Pointer to the block header that was
 *                          found in the flash.
 * \param    PageBuf_pcu8:  Pointer to the page buffer
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
LOCAL_INLINE FUNC(void, FEE_CODE) Fee_LLCopyPageBuff2HeaderIdxAndCrc(P2VAR(Fee_BlkHeader_tst, AUTOMATIC, FEE_APPL_DATA) BlkHdr_pst,
                                                                     P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8)
{
    /* 0xD2E9 <- [4]: D2, [5]: E9 */
    BlkHdr_pst->FeeIndex_u16    = (uint16)((uint16)(((uint16)(PageBuf_pcu8[4])) << 8u)  | (uint16)(PageBuf_pcu8[5]));

    /* 0xABCD <- [8]: AB, [9]: CD */
    BlkHdr_pst->HdrCrc16_u16    = (uint16)((uint16)(((uint16)(PageBuf_pcu8[8])) << 8u)  | (uint16)(PageBuf_pcu8[9]));
}


/**
 *********************************************************************
 * Fee_SrvBinarySearchInBlockProp(): Get the respective index out of
 *                                   the block properties table
 *
 * This function searches for the respective block properties table
 * index. In case unknown blocks are searched, the function will
 * return with a negative response.
 *
 * \param    FeeIdx_u16:    Fee index (persistent ID)
 * \param    CacheIdx_pu16: Pointer for the result
 * \return   Success of the function
 * \retval   FALSE: Corresponding index was not found
 * \retval   TRUE:  Corresponding index was found
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */
LOCAL_INLINE FUNC(boolean, FEE_CODE) Fee_SrvBinarySearchInBlockPropFast(VAR(uint16, AUTOMATIC) FeeIdx_u16,
                                                                        P2VAR(uint16, AUTOMATIC, FEE_APPL_DATA) CacheIdx_pu16)
{
    VAR(boolean, AUTOMATIC)  xFuncRet_b = FALSE;    /* Function return value */
    VAR(uint16, AUTOMATIC)  xMid_u16;               /* Mid index for the search */
    VAR(uint16, AUTOMATIC)  xLeft_u16 = 0;          /* Left index for the search */
    VAR(uint16, AUTOMATIC)  xRight_u16 = FEE_NUM_BLOCKS - 1u; /* Right index for the search */

    /* Loop until the value is found */
    do
    {
        /* Divide search area by two */
        xMid_u16 = (uint16)(xLeft_u16 + ((xRight_u16 - xLeft_u16) / 2));

        /* Check the cache content */
        if(Fee_BlockProperties_st[xMid_u16].BlockPersistentId_u16 == FeeIdx_u16)
        {
            /* Index was found, set return value */
            *CacheIdx_pu16 = xMid_u16;

            /* Return positive response */
            xFuncRet_b = TRUE;

            /* Leave the loop */
            return xFuncRet_b;
        }

        /* Check the current array index */
        if(Fee_BlockProperties_st[xMid_u16].BlockPersistentId_u16 > FeeIdx_u16)
        {
            /* Check if the lowest array position is reached */
            if(xMid_u16 != 0)
            {
                /* Reduce the right limit to the left */
                xRight_u16 = (uint16)(xMid_u16 - 1u);
            }
            else
            {
                /* Leave the loop with a negative response */
                return xFuncRet_b;
            }
        }
        else
        {
            /* Reduce the left limit to the right (upper limit is
             * safe because of the loop condition) */
            xLeft_u16 = (uint16)(xMid_u16 + 1u);
        }
    }
    while(xRight_u16 >= xLeft_u16);

    return xFuncRet_b;
}
/* FEE_FAST_CACHE_INIT_ACTIVE != FALSE */
#endif


/**
 *********************************************************************
 * Fee_SrvRoundUp():
 *
 * This function takes the parameter value and rounds it up to the next
 * multiple of the stepsize.
 *
 *
 * \param    value_u32: value to be rounded up
 * \param    stepsize_u32: atomic steps to be made during the rounding
 * \return   value rounded up to a multiple of the stepsize
 *
 *********************************************************************
 */
LOCAL_INLINE uint32 Fee_SrvRoundUp(uint32 value_u32 , uint32 stepsize_u32)
{
    uint32 modValue_u32, retVal_u32;

    retVal_u32 = value_u32;

    modValue_u32 = value_u32 % stepsize_u32;

    if(modValue_u32 != 0u)
    {
        retVal_u32 += stepsize_u32 - modValue_u32;
    }

    return retVal_u32;
}

/**
 *********************************************************************
 * Fee_SrvCalcSpaceNeededForWrite():
 *
 * This function calculates the space required to perform a write operation based on a given block configuration
 *
 * \param    blockLen_u16:       data length to be writen
 * \param    securityLevel_b:    single or double stored block?
 * \param    noFallback_b: is the block configured as NoFallback?
 * \return   space needed to write the block
 *
 *********************************************************************
 */

LOCAL_INLINE uint32 Fee_SrvCalcSpaceNeededForWrite(uint16  blockLen_u16 , boolean securityLevel_b , boolean noFallback_b)
{
    uint32 neededSpace_u32;

    // for all block types: blkSize + HdrSize
    neededSpace_u32 = (uint32)FEE_BLOCK_OVERHEAD + (uint32)(blockLen_u16);



    // force a page alignment of header and data size
    neededSpace_u32 = Fee_SrvRoundUp(neededSpace_u32 , (uint32)FEE_PAGE_LEN);



    // for NoFallback blocks: add one page space for the NoFB header
    // If NoFallback is deactivated, the parameter shall be loaded with FALSE
    if (noFallback_b)
    {
        neededSpace_u32 += (uint32)FEE_PAGE_LEN;
    }


    // double security blocks: check for space writing both block copies
    if(securityLevel_b)
    {
        neededSpace_u32 *= 2u;
    }

    return neededSpace_u32;
}


/* RBA_FEEFS1_PRV_H */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
**********************************************************************************************************************
* End of header file: $Name___:$
**********************************************************************************************************************
</BASDKey>*/
