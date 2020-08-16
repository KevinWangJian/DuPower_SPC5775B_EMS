/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2012-2014           *
*                         All Rights Reserved                           *
*************************************************************************
*************************************************************************
*                                                                       *
*                   Standard Software Driver for C55                    *
*                                                                       *
* FILE NAME     :  demo.c                                               *
* DATE          :  09.19.2014                                           *
*                                                                       *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
************************************************************************/

/******************************* CHANGES ********************************
 1.0.0    12.29.2011      FPT Team       Initial Version for RTM version
 ***********************************************************************/


#include    "flash_ee.h"


void ErrorTrap(UINT32 returnCode);

SSD_CONFIG ssdConfig =
{
    C55_REG_BASE,         /* C55 control register base */
    MAIN_ARRAY_BASE,      /* base of main array */
    { 0, 0, 0 },          /* blocks info of low address space */
    { 0, 0, 0 },          /* blocks info of mid address space */
    { 0, 0, 0 },          /* blocks info of high address space */
    0,                    /* number of blocks in 256K address space */
    UTEST_ARRAY_BASE,     /* base of UTEST array */
    TRUE,                 /* interface flag indicate main or alternate interface */
    C55_PROGRAMMABLE_SIZE,/* programmable size */
    FALSE                 /* debug mode selection */
};

CONTEXT_DATA dummyCtxData;
CONTEXT_DATA pgmCtxData;
CONTEXT_DATA bcCtxData;
CONTEXT_DATA pvCtxData;
CONTEXT_DATA csCtxData;
CONTEXT_DATA exPgmCtxData;

/* Source flash_ee_cache_arr for program and verify */
UINT32  flash_ee_cache_arr[FLASH_EE_CACHE_SIZE / C55_WORD_SIZE]={0};
MEM_REGION_INFO memRegionInfo;


UINT32 FLASH_EE_Init(void)
{
    register UINT32 returnCode;           /* Return code from each SSD function. */
    register UINT32 demoResult;

//    register UINT32 dest;                 /* destination address */
//    UINT32 size;                 /* size applicable */
//    UINT32 source;               /* source address for program and verify */

//    UINT32 failedAddress;          /* save the failed address in flash */
//    UINT32 failedData;             /* save the failed data in flash */
//    UINT32 failedSource;           /* Save the failed source for verification */

    UINT32 blkLockState;         /* block lock status to be retrieved */

    UINT32 sum;                  /* check sum result */
    UINT32 i;                    /* Index */

//    UINT32 lowBlockSelect;
//    UINT32 midBlockSelect;
//    UINT32 highBlockSelect;
//    UINT32 pflash_pfcr0, pflash_pfcr1, pflash_pfcr2, pflash_pfcr3;
//    N256K_BLOCK_SEL n256KBlockSelect;


    /* set up function pointers in context data */
    pgmCtxData.pReqCompletionFn = pFlashProgram;
    bcCtxData.pReqCompletionFn = pBlankCheck;
    pvCtxData.pReqCompletionFn = pProgramVerify;
    csCtxData.pReqCompletionFn = pCheckSum;
    exPgmCtxData.pReqCompletionFn = pFlashExpressProgram;
    /* If user wants to run this demo for alternate interface, please assign */
    /* ssdConfig.mainInterfaceFlag = FALSE and ssdConfig.programmablesize = 32 here */
    /* then all below codes can be applied for alternate interface */

    /* Initialize for express program */
    //InitMemRegionInfo(&memRegionInfo);

    /**************************************************************************/
    /* Initialize Flash                                                       */
    /**************************************************************************/
    ssdConfig.c55RegBase = C55_REG_BASE;
    ssdConfig.mainArrayBase = MAIN_ARRAY_BASE;
    ssdConfig.uTestArrayBase = UTEST_ARRAY_BASE;
    ssdConfig.mainInterfaceFlag = TRUE;
    ssdConfig.programmableSize = C55_PROGRAMMABLE_SIZE;
    ssdConfig.BDMEnable = FALSE;


    /* Flash Init */
    returnCode = pFlashInit(&ssdConfig);

    if (C55_OK != returnCode)
    {
        ErrorTrap(returnCode);
    }


    /**************************************************************************/
    /* Lock to Protect UTest Address Space                                    */
    /**************************************************************************/
    returnCode = pGetLock(&ssdConfig, C55_BLOCK_UTEST, &blkLockState);
//    if (C55_OK != returnCode)
//    {
//        ErrorTrap(returnCode);
//    }

    if (!(blkLockState & 0x00000001))
    {
        returnCode = pSetLock(&ssdConfig, C55_BLOCK_UTEST, 0x1);
//        if (C55_OK != returnCode)
//        {
//            ErrorTrap(returnCode);
//        }
    }

    /**************************************************************************/
    /* Unlock all blocks in low address space                                 */
    /**************************************************************************/
    returnCode = pSetLock(&ssdConfig, C55_BLOCK_LOW, UNLOCK_LOW_BLOCKS);
//    if (C55_OK != returnCode)
//    {
//        ErrorTrap(returnCode);
//    }


#if 0
    /**************************************************************************
    Call FlashErase, BlankCheck, FlashProgram, ProgramVerify, CheckSum
    for each individual block.
    **************************************************************************/
    /* Enable software watchdog to demonstrate that user can reset watchdog
       in demo code if it is enabled */

            lowBlockSelect = 1;
            midBlockSelect = 0;
            highBlockSelect = 0;
            n256KBlockSelect.first256KBlockSelect = 0;
            n256KBlockSelect.second256KBlockSelect = 0;

            /* erase block individually */
            demoResult = App_FlashErase(&ssdConfig,
                                         C55_ERASE_MAIN,
                                         lowBlockSelect,
                                         midBlockSelect,
                                         highBlockSelect,
                                         n256KBlockSelect);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }


            /* blank check */
            dest = 0x00800000;
            size = 0x4000;
            demoResult = App_BlankCheck(&ssdConfig,
                                         dest,
                                         size,
                                        &failedAddress,
                                        &failedData,
                                        &bcCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }

            /* program to the beginning of block */
            dest = 0x00800000;
            size = FLASH_EE_CACHE_SIZE;
            source = (UINT32)flash_ee_cache_arr;
            demoResult = App_FlashProgram(&ssdConfig,
                                           FALSE,
                                           dest,
                                           size,
                                           source,
                                          &pgmCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }

            /* Program verify */
            demoResult = App_ProgramVerify(&ssdConfig,
                                            dest,
                                            size,
                                            source,
                                           &failedAddress,
                                           &failedData,
                                           &failedSource,
                                           &pvCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }

            /* Check sum */
            demoResult = App_CheckSum(&ssdConfig,
                                       dest,
                                       size,
                                      &sum,
                                      &csCtxData);
            if (demoResult == DEMO_FAIL)
            {
                ErrorTrap(demoResult);
            }

    /* DEMO FINISHED */
    while(1)
    {
        /* do nothing */
    }
#endif
}



//==================================================================================
// Function    :
// Description :
// Parameters  :
// Return      : none
//==================================================================================
#if 0
void ee_FlashEraseBlock(UINT32 low_block_sel, UINT32 mid_block_sel)
{
	N256K_BLOCK_SEL n256KBlockSelect;
	n256KBlockSelect.first256KBlockSelect = 0;
	n256KBlockSelect.second256KBlockSelect = 0;

	App_FlashErase(&ssdConfig,C55_ERASE_MAIN,low_block_sel,mid_block_sel,0,n256KBlockSelect);
}
#endif

void ee_FlashEraseBlock(UINT32 low_block_sel)
{
	N256K_BLOCK_SEL n256KBlockSelect;
	n256KBlockSelect.first256KBlockSelect = 0;
	n256KBlockSelect.second256KBlockSelect = 0;

	App_FlashErase(&ssdConfig,C55_ERASE_MAIN,low_block_sel,0,0,n256KBlockSelect);
}


//==================================================================================
// Function    :
// Description :
// Parameters  :
// Return      : none
//==================================================================================
void ee_FlashBlankCheck(UINT32 star_addr, UINT32 size)
{
	UINT32 failedAddress,failedData,bcCtxData;

    App_BlankCheck(&ssdConfig,star_addr, size,
                   &failedAddress,
                   &failedData,
                   &bcCtxData);
}

//==================================================================================
// Function    :
// Description :
// Parameters  :
// Return      : none
//==================================================================================
void ee_FlashProgram(UINT32 addr, UINT32 size, UINT32 source)
{
    App_FlashProgram(&ssdConfig,FALSE,addr,size,source,&pgmCtxData);
}

//==================================================================================
// Function    :
// Description :
// Parameters  :
// Return      : none
//==================================================================================
void ee_FlashProgramVerify(UINT32 addr, UINT32 size, UINT32 source)
{
	UINT32 failedAddress,failedData,failedSource;
    App_ProgramVerify(&ssdConfig,addr,size,source,
                      &failedAddress,
                      &failedData,
                      &failedSource,
                      &pvCtxData);

}


















