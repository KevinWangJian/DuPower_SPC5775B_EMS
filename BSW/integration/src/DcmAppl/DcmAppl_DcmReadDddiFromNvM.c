/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmCore_DslDsd_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmReadDddiFromNvM :-\n
 * This API is called for each DDDID that is configured. Application has to read and update the DDDID definition if the requested DDDID is already stored in NvM .
 * In case application returns E_NOT_OK or any value other than E_OK,Dcm will not try to restore the same again and it is the responsibility of application to ensure the DDDI is restored successfully.
 * This API is called from Dcm_Init function.
 *
 * Note: An example code is given with this application function which the projects can refer to for restoring the DDDID definitions
 *
 * @param[in]     dataDddId_u16           : value of DDDID for which this Read API is called
 * @param[out]    dataDefinitionOfDDDI    : pointer to the definition of the DDDID which the application has to update after reading from non volatile memory.
 *
 * @retval        DCM_DDDI_READ_OK : In case the read is successful
 * @retval        DCM_DDDI_READ_NOT_OK : In case there is no access or error while reading(In this case, Dcm shall log the DET error)
 * @retval        DCM_DDDI_READ_NOTAVAILABLE : In case the configured DDDID (dataDddId_u16) is not available in NVRAM
 *
 */
FUNC(Dcm_RestoreDddiReturn_ten,DCM_APPL_CODE) DcmAppl_DcmReadDddiFromNvM (P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) dataDefinitionOfDDDI,
                                                                          VAR (uint16,AUTOMATIC) dataDddId_u16)
{
    /*TESTCODE-START
    uint16 idxLoop_u16;
    uint16 idxLoopRecord_u16;
    TESTCODE-END*/
    VAR (Dcm_RestoreDddiReturn_ten,AUTOMATIC) returnValue = DCM_DDDI_READ_OK;
    (void)dataDefinitionOfDDDI;
    (void)dataDddId_u16;
    /*TESTCODE-START

    // for reading the requested DDDID from NvM
    // first read all the information that is stored in NvM in the structure "dataToStoreInNvM_pst"
    // loop through the requested DDDID, and load the information in the out parameter "*dataDefinitionOfDDDI"

    for(idxLoop_u16 = 0;idxLoop_u16 < indexOfDDDIToStoreinNvM;idxLoop_u16++)
    {
        if(dataDddId_u16 == dataToStoreInNvM_pst[idxLoop_u16].dataDddId_u16)
        {
            break;
        }
    }

    if(idxLoop_u16 < indexOfDDDIToStoreinNvM)
    {
        dataDefinitionOfDDDI->dataDDDIRecordContext_pst->nrCurrentlyDefinedRecords_u16 = dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.nrCurrentlyDefinedRecords_u16;
        dataDefinitionOfDDDI->dataDDDIRecordContext_pst->posnCurrentPosInDataBuffer_u16 = dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.posnCurrentPosInDataBuffer_u16;
        dataDefinitionOfDDDI->dataDDDIRecordContext_pst->idxCurrentRecord_u16 = dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.idxCurrentRecord_u16;

        dataDefinitionOfDDDI->dataPDIRecordContext_pst->nrCurrentlyDefinedRecords_u16 = dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.nrCurrentlyDefinedRecords_u16;
        dataDefinitionOfDDDI->dataPDIRecordContext_pst->posnCurrentPosInDataBuffer_u16 = dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.posnCurrentPosInDataBuffer_u16;
        dataDefinitionOfDDDI->dataPDIRecordContext_pst->idxCurrentRecord_u16 = dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.idxCurrentRecord_u16;

        for(idxLoopRecord_u16=0;idxLoopRecord_u16<dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.nrCurrentlyDefinedRecords_u16;idxLoopRecord_u16++)
        {
            dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDefinitionType_u8 = dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDefinitionType_u8;
            if(dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDefinitionType_u8 == DCM_STORE_DEFINITION_BY_ID)
            {
                dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.dataSrcDid_u16 =
                                                                dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.dataSrcDid_u16;
                dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.idxOfDid_u16 =
                                                                dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.idxOfDid_u16;
                dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.posnInSourceDataRecord_u8 =
                                                                dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.posnInSourceDataRecord_u8;
                dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.dataMemorySize_u8 =
                                                                dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.dataMemorySize_u8;
                dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.stCurrentDidRangeStatus_b =
                                                                dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.stCurrentDidRangeStatus_b;
            }
            else if(dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDefinitionType_u8 == DCM_STORE_DEFINITION_BY_MEMORYADDRESS)
            {
                dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32 =
                                                                dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32;
                dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32 =
                                                                dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32;
            }
            else
            {
                // dummy else
            }
        }

    }
    else
    {
        returnValue = DCM_DDDI_READ_NOTAVAILABLE;
    }

    TESTCODE-END*/

    /*TESTCODE-START
    returnValue = DcmTest_DcmAppl_DcmReadDddiFromNvM(dataDefinitionOfDDDI, dataDddId_u16);
    TESTCODE-END*/
    return returnValue;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* #if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)) */
