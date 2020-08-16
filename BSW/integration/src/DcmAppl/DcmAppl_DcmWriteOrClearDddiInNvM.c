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

/*TESTCODE-START
// the size of the below array should be atleast the number of DDDIDs configured
Dcm_DddiStoreInNvMConfig_tst dataToStoreInNvM_pst[10];
uint16 indexOfDDDIToStoreinNvM;
TESTCODE-END*/

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmWriteOrClearDddiInNvM :-\n
 * This API is called with the DDDID definition from Dcm whenever a DDDID is defined or cleared so that the application can store/clear the DDDID definition in NvM.\n
 * This API is called from Dcm service context.
 *
 * Note: An example code is given with this application function which the projects can refer to for storing/clearing the DDDIDs\n
 *
 * @param[in]     *dataDefinitionOfDDDI    : pointer to the definition of the DDDID which the application has to store in non volatile memory. It is basically the structure which has the DDDID definition.\n
 *                                           In case, the API call is for clearing the DDDIDs, then this parameter shall be NULL_PTR.
 *
 * @param[in]     dataDddId_u16            : value of DDDID that is defined/cleared\n
 *
 * @param[in]     Dcm_StoreDDDiOpstatus_u8 : opstatus parameter\n
 *                                           Possible values : DCM_INITIAL\n
                                                               DCM_PENDING\n
                                                               DCM_CANCEL\n
 *
 *
 * @param[in]     Dcm_DddiWriteOrClear_en  : enum parameter to indicate whether the API call is for adding/clearing/clearing all the DDDIDs.\n
 *                                           possible values - DCM_DDDI_CLEAR - for clearing one specific DDDID definition\n
 *                                                             DCM_DDDI_CLEARALL - for clearing the all the defined DDDIDs\n
 *                                                             DCM_DDDI_WRITE - for writing the DDDID definition\n
 *
 * @retval         E_OK  : In case the NvM Store/Clear operation is successful\n
 * @retval         E_NOT_OK : In case the operation is not successful.
                   (In this case, Dcm shall log the DET error and just treat the DDDI request as a normal one no restoring is possible for this DDDI post reset.)\n
   @retval         E_PENDING : In case the operation takes more time.
                   In this case, the API shall be called again in the next main function cycle of Dcm.\n
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmWriteOrClearDddiInNvM (P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) dataDefinitionOfDDDI,
                                                                     VAR (uint16,AUTOMATIC) dataDddId_u16,
                                                                     VAR (Dcm_OpStatusType,AUTOMATIC) Dcm_StoreDDDiOpstatus_u8,
                                                                     VAR (Dcm_DddiWriteOrClear_ten,AUTOMATIC) Dcm_DddiWriteOrClear_en)
                                                                     {
    /*TESTCODE-START
    uint16 idxLoop_u16;
    uint16 idxLoopRecord_u16;
    TESTCODE-END*/
    VAR (Std_ReturnType,AUTOMATIC) returnValue = E_OK;
    (void)Dcm_StoreDDDiOpstatus_u8;
    (void)dataDefinitionOfDDDI;
    (void)dataDddId_u16;
    (void)Dcm_DddiWriteOrClear_en;
    /* Example Code
     if(Dcm_StoreDDDiOpstatus_u8 == DCM_INITIAL)
     {
        if(Dcm_DddiWriteOrClear_en == DCM_DDDI_WRITE)
        {
        // for writing the DDDID definition in NvM
        // first copy all the information to be stored in the structure "dataToStoreInNvM_pst" and write the same in NvM

            for(idxLoop_u16 = 0; idxLoop_u16< indexOfDDDIToStoreinNvM;idxLoop_u16++)
            {
                // check if the DDDID is stored already and this call is for updating the definition of the same DDDID
               if(dataToStoreInNvM_pst[idxLoop_u16].dataDddId_u16 == dataDddId_u16)
               {
                   break;
               }
            }

            dataToStoreInNvM_pst[idxLoop_u16].dataDddId_u16 = dataDddId_u16;

            dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.nrCurrentlyDefinedRecords_u16 = dataDefinitionOfDDDI->dataDDDIRecordContext_pst->nrCurrentlyDefinedRecords_u16;
            dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.posnCurrentPosInDataBuffer_u16 = dataDefinitionOfDDDI->dataDDDIRecordContext_pst->posnCurrentPosInDataBuffer_u16;
            dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.idxCurrentRecord_u16 = dataDefinitionOfDDDI->dataDDDIRecordContext_pst->idxCurrentRecord_u16;

            dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.nrCurrentlyDefinedRecords_u16 = dataDefinitionOfDDDI->dataPDIRecordContext_pst->nrCurrentlyDefinedRecords_u16;
            dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.posnCurrentPosInDataBuffer_u16 = dataDefinitionOfDDDI->dataPDIRecordContext_pst->posnCurrentPosInDataBuffer_u16;
            dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.idxCurrentRecord_u16 = dataDefinitionOfDDDI->dataPDIRecordContext_pst->idxCurrentRecord_u16;

            for(idxLoopRecord_u16 = 0; idxLoopRecord_u16< dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.nrCurrentlyDefinedRecords_u16;idxLoopRecord_u16++)
            {
                dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDefinitionType_u8 = dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDefinitionType_u8;

                if(dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDefinitionType_u8 == DCM_STORE_DEFINITION_BY_ID)
                {
                    dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.dataSrcDid_u16 =
                                                                                                             dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.dataSrcDid_u16;
                    dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.idxOfDid_u16 =
                                                                                                            dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.idxOfDid_u16;
                    dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.posnInSourceDataRecord_u8 =
                                                                                                            dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.posnInSourceDataRecord_u8;
                    dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.dataMemorySize_u8 =
                                                                                                            dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.dataMemorySize_u8;
                    dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.stCurrentDidRangeStatus_b =
                                                                                                            dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataIdAccess_st.stCurrentDidRangeStatus_b;
                }
                else if(dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDefinitionType_u8 == DCM_STORE_DEFINITION_BY_MEMORYADDRESS)
                {
                    dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32 = dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32;
                    dataToStoreInNvM_pst[idxLoop_u16].addrRecord_ast[idxLoopRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32 = dataDefinitionOfDDDI->addrRecord_pst[idxLoopRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32;
                }

            }

            indexOfDDDIToStoreinNvM++;
        }

        if(Dcm_DddiWriteOrClear_en == DCM_DDDI_CLEARALL)
        {
            // for clearing all the DDDID definition in NvM
            // first clear all the information to be stored in the structure "dataToStoreInNvM_pst" and clear the same in NvM

            for(idxLoop_u16 = 0;idxLoop_u16<indexOfDDDIToStoreinNvM;idxLoop_u16++)
            {
                dataToStoreInNvM_pst[idxLoop_u16].dataDddId_u16  = 0;

                dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.nrCurrentlyDefinedRecords_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.posnCurrentPosInDataBuffer_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.idxCurrentRecord_u16 = 0;

                dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.nrCurrentlyDefinedRecords_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.posnCurrentPosInDataBuffer_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.idxCurrentRecord_u16 = 0;
            }

            indexOfDDDIToStoreinNvM = 0;
         }

        if(Dcm_DddiWriteOrClear_en == DCM_DDDI_CLEAR)
        {
            // for clearing the requsted DDDID definition in NvM
            // first clear the requested DDDID definition in the structure "dataToStoreInNvM_pst" and clear the same in NvM

            for(idxLoop_u16 = 0;idxLoop_u16<indexOfDDDIToStoreinNvM;idxLoop_u16++)
            {
                if(dataDddId_u16 == dataToStoreInNvM_pst[idxLoop_u16].dataDddId_u16)
                {
                    break;
                }
            }

            if(idxLoop_u16 < indexOfDDDIToStoreinNvM)
            {
                dataToStoreInNvM_pst[idxLoop_u16].dataDddId_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.nrCurrentlyDefinedRecords_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.posnCurrentPosInDataBuffer_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataDDDIRecordContext_st.idxCurrentRecord_u16 = 0;

                dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.nrCurrentlyDefinedRecords_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.posnCurrentPosInDataBuffer_u16 = 0;
                dataToStoreInNvM_pst[idxLoop_u16].dataPDIRecordContext_st.idxCurrentRecord_u16 = 0;
            }

        }
    }
    */
/*TESTCODE-START
returnValue = DcmTest_DcmAppl_DcmWriteOrClearDddiInNvM(dataDefinitionOfDDDI,dataDddId_u16,Dcm_StoreDDDiOpstatus_u8,Dcm_DddiWriteOrClear_en);
TESTCODE-END*/

    return returnValue;
}


#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* #if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)) */
