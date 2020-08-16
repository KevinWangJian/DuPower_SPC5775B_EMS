


#include "DcmDspUds_Wmba_Inf.h"
#include "DcmDspUds_Rmba_Inf.h"
#include "DcmDspUds_RequestUpload_Inf.h"
#include "DcmDspUds_RequestDownload_Inf.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Wmba_Priv.h"
#endif
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Rmba_Priv.h"
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_RequestUpload_Priv.h"
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_RequestDownload_Priv.h"
#endif

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)   ||    \
													   (DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)  ||    \
                                                       (DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)       ||    \
                                                       (DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *********************************************************************************************************************
 * Dcm_GetMemoryInfo : This function is used to calculate the memory address received from
 * 							the tester
 *
 * \param				: dataSize_u8: Size of the memory address or length extracted from addressAndLengthFormatIdentifier
 * 								received from the tester
 * 						  adrReqBuf_pcu8 : 		Pointer to the memoryAddress or memory length in the Dcm Request buffer
 * 						  adrMemAddrLength_pu32 :  pointer to the variable to store the memory address or memory length requested
 * 						  			    by the tester*
 *
 * \retval          None
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_GetMemoryInfo(VAR   (uint8,AUTOMATIC) dataSize_u8,
									  P2CONST (uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pcu8,
									  P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA) adrMemAddrLength_pu32)
{
	VAR(uint8,             AUTOMATIC) idxIndex_u8=0;
	VAR(uint32,             AUTOMATIC) tempResult_u32=0;
	VAR(uint32,             AUTOMATIC) dataMemAlFid_u32=0;
	do{
        tempResult_u32 = (uint32)(adrReqBuf_pcu8[idxIndex_u8]);
        tempResult_u32 <<= (uint32)((dataSize_u8-1)*8u);
        dataMemAlFid_u32 |= (uint32)(tempResult_u32);/*Address Length Format Identifier --- ALFID*/
		dataSize_u8--;
		idxIndex_u8++;
	}while(dataSize_u8!=0);
	*adrMemAddrLength_pu32 = dataMemAlFid_u32; /*Store the calculated memory address in to the global variable*/

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)|| \
                                                     (DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 ******************************************************************************************************************************
 * Dcm_UpdateTransferRequestCount : Function to update the number of Transfer data calls expected before RequestTransferExit
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 *******************************************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_UpdateTransferRequestCount(void)
{
    /* Check is upload is active */
    /*Check whether Data upload or download is active*/
    if((Dcm_DataTransfer_st.isUploadStarted_b!=FALSE)||(Dcm_DataTransfer_st.isDownloadStarted_b!=FALSE))
    {
        /* Calcualte the total number of TransferData requests to complete the upload process */

        if((Dcm_DataTransfer_st.dataMemorySize_u32 % (Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u)) != 0x00u)
        {
            Dcm_DataTransfer_st.nrMaxBlockSequenceNum_u32 = (Dcm_DataTransfer_st.dataMemorySize_u32 / (Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u)) +1u;
        }
        else
        {
            Dcm_DataTransfer_st.nrMaxBlockSequenceNum_u32 = (Dcm_DataTransfer_st.dataMemorySize_u32 / (Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u));
        }
    }
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

