
#ifndef SGUS_BASIC_H_
#define SGUS_BASIC_H_

#include "sgus_def.h"

extern volatile uint8_t SGUS_EnableCRCFlag;
extern volatile uint8_t SGUS_LangEnum;

sgus_error_t SGUS_WriteReg(sgus_regindex_t regindex, uint8_t length);
sgus_error_t SGUS_ReadRegRequest(sgus_regindex_t regindex, uint8_t length);
sgus_error_t SGUS_ReadReg_Async(uint8_t * data);
sgus_error_t SGUS_WriteVar(sgus_varindex_t varindex, uint8_t length);
sgus_error_t SGUS_ReadVarRequest(sgus_varindex_t varindex, uint8_t length);
sgus_error_t SGUS_ReadVar_Async(uint8_t *data);

void SGUS_Recieve_Task(void);

const sgus_reginfo_t * SGUS_GetRegInfo(void);
const sgus_varinfo_t * SGUS_GetVarInfo(void);
const sgus_pageinfo_t * SGUS_GetPageInfo(void);

sgus_regdata_t * SGUS_GetTxRegData(void);
sgus_regdata_t * SGUS_GetRxRegData(void);

sgus_vardata_t * SGUS_GetTxVarData(void);
sgus_vardata_t * SGUS_GetRxVarData(void);

#endif


