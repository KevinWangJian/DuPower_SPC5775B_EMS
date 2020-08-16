
/*<VersionHead>
 ***************************************************************************************************
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: IpduM / AR42.4.0.0                 Module Package Version
 * $Editor_____: 2.3.0.4                 Tool Version
 * $Model______: 9.0                 ECU Parameter Definition Version
 ***************************************************************************************************
 </VersionHead>*/

#include "IpduM.h"
#include "IpduM_Priv.h"
#include "PduR_IpduM.h"
#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != IPDUM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != IPDUM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "IpduM_Cfg.h"



/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"
CONST(IpduM_RxUpPduType, IPDUM_CONST)   IpduM_RxUpPduTable[IPDUM_NUM_RX_IPDUS] =
{
    /*  Base addr   ,               IPdu    ,            IPdu  ,   RxHandleId,      Num of,          Selector   */
    /*  of SubPart                 Buffer               Length                     SubParts           Value   */
    /*AFC2_EOLTester_Confirm_MUX1*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer0[0],      8,                        2        ,                   8,             0x1,
    },    /*AFC2_EOLTester_Confirm_MUX10*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer1[0],      8,                        0        ,                   8,             0xA,
    },    /*AFC2_EOLTester_Confirm_MUX11*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer2[0],      8,                        1        ,                   8,             0xB,
    },    /*AFC2_EOLTester_Confirm_MUX2*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer3[0],      8,                        3        ,                   8,             0x2,
    },    /*AFC2_EOLTester_Confirm_MUX3*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer4[0],      8,                        4        ,                   8,             0x3,
    },    /*AFC2_EOLTester_Confirm_MUX4*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer5[0],      8,                        5        ,                   8,             0x4,
    },    /*AFC2_EOLTester_Confirm_MUX5*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer6[0],      8,                        6        ,                   8,             0x5,
    },    /*AFC2_EOLTester_Confirm_MUX6*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer7[0],      8,                        7        ,                   8,             0x6,
    },    /*AFC2_EOLTester_Confirm_MUX8*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer8[0],      8,                        8        ,                   8,             0x8,
    },    /*AFC2_EOLTester_Confirm_MUX9*/
    {
        &IpduM_RxSubParts[2],        &IpduM_RxBuffer9[0],      8,                        9        ,                   8,             0x9,
    }
    ,
    /*AFC_EOLTester_Confirm_MUX1*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer10[0],      8,                        12        ,                   8,             0x1,
    },    /*AFC_EOLTester_Confirm_MUX10*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer11[0],      8,                        10        ,                   8,             0xA,
    },    /*AFC_EOLTester_Confirm_MUX11*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer12[0],      8,                        11        ,                   8,             0xB,
    },    /*AFC_EOLTester_Confirm_MUX2*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer13[0],      8,                        13        ,                   8,             0x2,
    },    /*AFC_EOLTester_Confirm_MUX3*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer14[0],      8,                        14        ,                   8,             0x3,
    },    /*AFC_EOLTester_Confirm_MUX4*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer15[0],      8,                        15        ,                   8,             0x4,
    },    /*AFC_EOLTester_Confirm_MUX5*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer16[0],      8,                        16        ,                   8,             0x5,
    },    /*AFC_EOLTester_Confirm_MUX6*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer17[0],      8,                        17        ,                   8,             0x6,
    },    /*AFC_EOLTester_Confirm_MUX8*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer18[0],      8,                        18        ,                   8,             0x8,
    },    /*AFC_EOLTester_Confirm_MUX9*/
    {
        &IpduM_RxSubParts[0],        &IpduM_RxBuffer19[0],      8,                        19        ,                   8,             0x9,
    }
    ,
    /*Tester2_18FFFA01h_MUX1*/
    {
        &IpduM_RxSubParts[3],        &IpduM_RxBuffer20[0],      8,                        20        ,                   11,             0x1,
    }
    ,
    /*Tester_18FFFA01h_MUX1*/
    {
        &IpduM_RxSubParts[1],        &IpduM_RxBuffer21[0],      8,                        21        ,                   11,             0x1,
    }
};
/* ------------------------------------------------------------------------ */
/* End section for constants */

#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"
CONST(IpduM_RxMPduType, IPDUM_CONST)    IpduM_RxMPduTable[IPDUM_NUM_RX_MPDUS] =
{
    /* Pointer to ,  	  MPdu Length,  TotalNumOfIPdus,     Selector ,      Selector   , Byte Order     */
    /* RxUpPduTable         	                            Startbyte          Mask                      */
    
    {
        &IpduM_RxUpPduTable[0],  	8,  	10,        			0,          	0xFF,           IPDUM_LITTLEENDIAN

    },
    {
        &IpduM_RxUpPduTable[10],  	8,  	10,        			0,          	0xFF,           IPDUM_LITTLEENDIAN

    },
    {
        &IpduM_RxUpPduTable[20],  	8,  	1,        			0,          	0xFF,           IPDUM_LITTLEENDIAN

    },
    {
        &IpduM_RxUpPduTable[21],  	8,  	1,        			0,          	0xFF,           IPDUM_LITTLEENDIAN

    }
    
};
/* ------------------------------------------------------------------------ */
/* End section for constants */

#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"
CONST(IpduM_SubPartType, IPDUM_CONST)   IpduM_RxSubParts[IPDUM_NUM_RX_SUBPARTS] =
{
    /* SegmentPos,    SegmentLen */
    
    /*IpduMRxDynamicSegment_0 :: 0*/
    {
        16,      16
    },
    /*IpduMRxDynamicSegment_0 :: 1*/
    {
        32,      8
    },
    /*IpduMRxDynamicSegment_0 :: 2*/
    {
        16,      16
    },
    /*IpduMRxDynamicSegment_0 :: 3*/
    {
        32,      8
    },
    /*IpduMRxDynamicSegment_1 :: 4*/
    {
        32,      16
    },
    /*IpduMRxDynamicSegment_1 :: 5*/
    {
        48,      8
    },
    /*IpduMRxDynamicSegment_1 :: 6*/
    {
        32,      16
    },
    /*IpduMRxDynamicSegment_1 :: 7*/
    {
        48,      8
    },
    /*IpduMRxDynamicSegment_10 :: 8*/
    {
        30,      2
    },
    /*IpduMRxDynamicSegment_10 :: 9*/
    {
        30,      2
    },
    /*IpduMRxDynamicSegment_2 :: 10*/
    {
        48,      8
    },
    /*IpduMRxDynamicSegment_2 :: 11*/
    {
        0,      8
    },
    /*IpduMRxDynamicSegment_2 :: 12*/
    {
        48,      8
    },
    /*IpduMRxDynamicSegment_2 :: 13*/
    {
        0,      8
    },
    /*IpduMRxDynamicSegment_3 :: 14*/
    {
        0,      8
    },
    /*IpduMRxDynamicSegment_3 :: 15*/
    {
        8,      2
    },
    /*IpduMRxDynamicSegment_3 :: 16*/
    {
        0,      8
    },
    /*IpduMRxDynamicSegment_3 :: 17*/
    {
        8,      2
    },
    /*IpduMRxDynamicSegment_4 :: 18*/
    {
        8,      1
    },
    /*IpduMRxDynamicSegment_4 :: 19*/
    {
        24,      2
    },
    /*IpduMRxDynamicSegment_4 :: 20*/
    {
        8,      1
    },
    /*IpduMRxDynamicSegment_4 :: 21*/
    {
        24,      2
    },
    /*IpduMRxDynamicSegment_5 :: 22*/
    {
        24,      8
    },
    /*IpduMRxDynamicSegment_5 :: 23*/
    {
        40,      8
    },
    /*IpduMRxDynamicSegment_5 :: 24*/
    {
        24,      8
    },
    /*IpduMRxDynamicSegment_5 :: 25*/
    {
        40,      8
    },
    /*IpduMRxDynamicSegment_6 :: 26*/
    {
        40,      8
    },
    /*IpduMRxDynamicSegment_6 :: 27*/
    {
        56,      8
    },
    /*IpduMRxDynamicSegment_6 :: 28*/
    {
        40,      8
    },
    /*IpduMRxDynamicSegment_6 :: 29*/
    {
        56,      8
    },
    /*IpduMRxDynamicSegment_7 :: 30*/
    {
        56,      8
    },
    /*IpduMRxDynamicSegment_7 :: 31*/
    {
        10,      14
    },
    /*IpduMRxDynamicSegment_7 :: 32*/
    {
        56,      8
    },
    /*IpduMRxDynamicSegment_7 :: 33*/
    {
        10,      14
    },
    /*IpduMRxDynamicSegment_8 :: 34*/
    {
        26,      2
    },
    /*IpduMRxDynamicSegment_8 :: 35*/
    {
        26,      2
    },
    /*IpduMRxDynamicSegment_9 :: 36*/
    {
        28,      2
    },
    /*IpduMRxDynamicSegment_9 :: 37*/
    {
        28,      2
    }
    
};
/* ------------------------------------------------------------------------ */
/* End section for constants */

#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"


/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"
CONST(IpduM_ConfigType, IPDUM_APPL_CONST)   IpduMConfig =
{
    (P2CONST(IpduM_TxRequestType, TYPEDEF, IPDUM_APPL_CONST)) NULL_PTR,
    
    (P2CONST(IpduM_TxMPduType, TYPEDEF, IPDUM_APPL_CONST)) NULL_PTR,
    
    (P2CONST(IpduM_RxMPduType, TYPEDEF, IPDUM_APPL_CONST)) &IpduM_RxMPduTable[0],
    
    (P2CONST(IpduM_RxUpPduType, TYPEDEF, IPDUM_APPL_CONST)) &IpduM_RxUpPduTable[0],
    
    (P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST)) NULL_PTR,
    
    (P2CONST(IpduM_TxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST)) NULL_PTR,
    
    (P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST)) NULL_PTR,
    
    (P2CONST(IpduM_RxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST)) NULL_PTR
};
/* ------------------------------------------------------------------------ */
/* End section for constants */

#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"


/* IpduM RxIPdu Buffers */
/* ------------------------------------------------------------------------ */
/* Begin section for variables(Uint8) */

#define IPDUM_START_SEC_VAR_CLEARED_8
#include "IpduM_MemMap.h"
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer0[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer1[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer2[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer3[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer4[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer5[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer6[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer7[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer8[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer9[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer10[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer11[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer12[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer13[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer14[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer15[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer16[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer17[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer18[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer19[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer20[8];
VAR(uint8, IPDUM_VAR)   IpduM_RxBuffer21[8];
/* ------------------------------------------------------------------------ */
/* End section for variables(Uint8) */

#define IPDUM_STOP_SEC_VAR_CLEARED_8
#include "IpduM_MemMap.h"


/* ------------------------------------------------------------------------ */
/* Begin section for variables(Unspecified) */

#define IPDUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "IpduM_MemMap.h"
VAR(IpduM_TxRamType, IPDUM_VAR) IpduM_TxRamData[1];
/* ------------------------------------------------------------------------ */
/* End section for variables(Unspecified) */

#define IPDUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "IpduM_MemMap.h"



















