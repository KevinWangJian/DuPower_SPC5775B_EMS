/*
 * File: ECTD_Cal.c
 *
 * Code generated for Simulink model 'ECTD'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 21 10:58:24 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ECTD_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbECTD_BCChrgNCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_BCChrgNCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_BCChrgNCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_BCChrgNCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_BCChrgNCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_BCChrgNCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_BCChrgPCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_BCChrgPCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_BCChrgPCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_BCChrgPCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_BCChrgPCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_BCChrgPCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_CChrgANCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgANCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_CChrgANCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgANCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_CChrgANCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgANCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_CChrgAPCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgAPCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_CChrgAPCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgAPCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_CChrgAPCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgAPCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_CChrgBNCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgBNCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_CChrgBNCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_CChrgBNCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgBNCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_CChrgBPCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgBPCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_CChrgBPCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgBPCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_CChrgBPCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_CChrgBPCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgANCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgANCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgANCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgANCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgANCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgANCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgAPCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgAPCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgAPCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgAPCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgAPCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgAPCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgBNCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgBNCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgBNCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgBNCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgBNCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgBNCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgBPCtrCloseDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgBPCtrCloseDiagFltOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgBPCtrFilStaOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgBPCtrFilStaOvr_flg = 0;
volatile boolean_T CbECTD_ReChrgBPCtrOpenDiagFltOvrSwt_flg = 0;
volatile boolean_T CbECTD_ReChrgBPCtrOpenDiagFltOvr_flg = 0;
volatile boolean_T CbEECTD_CChrgBNCtrFilStaOvrSwt_flg = 0;
volatile uint16_T CcECTD_DebounceTime300ms_ms = 300U;
volatile uint16_T CcECTD_DebounceTime40ms_ms = 40U;
volatile uint16_T CcECTD_DebounceTime60ms_ms = 60U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
