/*
 * File: EETM.c
 *
 * Code generated for Simulink model 'EETM'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 23 17:19:25 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EETM.h"
#include "EETM_private.h"

/* Named constants for Chart: '<S3>/EETM_10ms' */
#define EETM_IN_COLD                   ((uint8_T)1U)
#define EETM_IN_HEAT                   ((uint8_T)2U)
#define EETM_IN_OFFLINE                ((uint8_T)3U)
#define EETM_IN_SELF_CIRCULATION       ((uint8_T)4U)
#define EETM_IN_STANDBY                ((uint8_T)5U)

/* Block signals (auto storage) */
B_EETM_T EETM_B;

/* Block states (auto storage) */
DW_EETM_T EETM_DW;

/* Real-time model */
RT_MODEL_EETM_T EETM_M_;
RT_MODEL_EETM_T *const EETM_M = &EETM_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EETM_10ms_at_outport_1' */
void EETM_10ms(void)
{
  real32_T rtb_MinBatTmp;
  real32_T rtb_MaxBatTmp;
  real32_T rtb_MaxWaterTmp;
  if ((get_GcEBCR_BMSAMinBatTmp_C() <= get_GcEBCR_BMSBMinBatTmp_C()) || rtIsNaNF
      (get_GcEBCR_BMSBMinBatTmp_C())) {
    rtb_MinBatTmp = get_GcEBCR_BMSAMinBatTmp_C();
  } else {
    rtb_MinBatTmp = get_GcEBCR_BMSBMinBatTmp_C();
  }

  if ((get_GcEBCR_BMSAMaxBatTmp_C() >= get_GcEBCR_BMSBMaxBatTmp_C()) || rtIsNaNF
      (get_GcEBCR_BMSBMaxBatTmp_C())) {
    rtb_MaxBatTmp = get_GcEBCR_BMSAMaxBatTmp_C();
  } else {
    rtb_MaxBatTmp = get_GcEBCR_BMSBMaxBatTmp_C();
  }

  if ((get_GcEBSW_ACDCAOutWaterTemp_C() >= get_GcEBSW_DCDCAOutWaterTemp_C()) ||
      rtIsNaNF(get_GcEBSW_DCDCAOutWaterTemp_C())) {
    rtb_MaxWaterTmp = get_GcEBSW_ACDCAOutWaterTemp_C();
  } else {
    rtb_MaxWaterTmp = get_GcEBSW_DCDCAOutWaterTemp_C();
  }

  if (!((rtb_MaxWaterTmp >= get_GcEBSW_ACDCBOutWaterTemp_C()) || rtIsNaNF
        (get_GcEBSW_ACDCBOutWaterTemp_C()))) {
    rtb_MaxWaterTmp = get_GcEBSW_ACDCBOutWaterTemp_C();
  }

  if (!((rtb_MaxWaterTmp >= get_GcEBSW_DCDCBOutWaterTemp_C()) || rtIsNaNF
        (get_GcEBSW_DCDCBOutWaterTemp_C()))) {
    rtb_MaxWaterTmp = get_GcEBSW_DCDCBOutWaterTemp_C();
  }

  if (EETM_DW.is_active_c1_EETM == 0U) {
    EETM_DW.is_active_c1_EETM = 1U;
    EETM_DW.is_c1_EETM = EETM_IN_OFFLINE;
    EETM_B.oGeEETM_HeatMode_enum = (uint8_T)Enum_EETMHeatMode_OffLine;
    EETM_B.oGcEETM_SetTemp_C = 215.0F;
  } else {
    switch (EETM_DW.is_c1_EETM) {
     case EETM_IN_COLD:
      if (get_GbEDEC_ETMFbid_flg() || ((21.0F >= rtb_MaxBatTmp) && (32.0F >=
            rtb_MaxWaterTmp))) {
        EETM_B.oGcEETM_SetTemp_C = 215.0F;
        EETM_DW.is_c1_EETM = EETM_IN_STANDBY;
        EETM_B.oGeEETM_HeatMode_enum = (uint8_T)Enum_EETMHeatMode_Standby;
      }
      break;

     case EETM_IN_HEAT:
      if (get_GbEDEC_ETMFbid_flg() || (9.0F <= rtb_MinBatTmp)) {
        EETM_B.oGcEETM_SetTemp_C = 215.0F;
        EETM_DW.is_c1_EETM = EETM_IN_STANDBY;
        EETM_B.oGeEETM_HeatMode_enum = (uint8_T)Enum_EETMHeatMode_Standby;
      }
      break;

     case EETM_IN_OFFLINE:
      if ((!get_GbEBSW_HCUTimeOut_flg()) && get_GbEMSM_24VSelfCheckSuccess_flg())
      {
        EETM_B.oGcEETM_SetTemp_C = 215.0F;
        EETM_DW.is_c1_EETM = EETM_IN_STANDBY;
        EETM_B.oGeEETM_HeatMode_enum = (uint8_T)Enum_EETMHeatMode_Standby;
      }
      break;

     case EETM_IN_SELF_CIRCULATION:
      if (get_GbEDEC_ETMFbid_flg() || ((-20.0F <= rtb_MinBatTmp) && (6.0F >=
            rtb_MinBatTmp)) || (24.0F < rtb_MaxBatTmp) || (35.0F <=
           rtb_MaxWaterTmp)) {
        EETM_B.oGcEETM_SetTemp_C = 215.0F;
        EETM_DW.is_c1_EETM = EETM_IN_STANDBY;
        EETM_B.oGeEETM_HeatMode_enum = (uint8_T)Enum_EETMHeatMode_Standby;
      }
      break;

     default:
      if (get_GbEBSW_HCUTimeOut_flg()) {
        EETM_DW.is_c1_EETM = EETM_IN_OFFLINE;
        EETM_B.oGeEETM_HeatMode_enum = (uint8_T)Enum_EETMHeatMode_OffLine;
        EETM_B.oGcEETM_SetTemp_C = 215.0F;
      } else if ((!get_GbEDEC_ETMFbid_flg()) && ((-20.0F <= rtb_MinBatTmp) &&
                  (6.0F >= rtb_MinBatTmp))) {
        EETM_B.oGcEETM_SetTemp_C = 30.0F;
        EETM_DW.is_c1_EETM = EETM_IN_HEAT;
        EETM_B.oGeEETM_HeatMode_enum = (uint8_T)Enum_EETMHeatMode_Heat;
      } else if ((!get_GbEDEC_ETMFbid_flg()) && ((24.0F < rtb_MaxBatTmp) ||
                  (35.0F <= rtb_MaxWaterTmp))) {
        EETM_B.oGcEETM_SetTemp_C = 15.0F;
        EETM_DW.is_c1_EETM = EETM_IN_COLD;
        EETM_B.oGeEETM_HeatMode_enum = (uint8_T)Enum_EETMHeatMode_Cold;
      } else {
        if ((!get_GbEDEC_ETMFbid_flg()) && (6.0F < rtb_MinBatTmp) && (24.0F >=
             rtb_MaxBatTmp) && (35.0F > rtb_MaxWaterTmp)) {
          EETM_B.oGcEETM_SetTemp_C = 215.0F;
          EETM_DW.is_c1_EETM = EETM_IN_SELF_CIRCULATION;
          EETM_B.oGeEETM_HeatMode_enum = (uint8_T)
            Enum_EETMHeatMode_SelfCirculation;
        }
      }
      break;
    }
  }

  if (CbEETM_HeatModeOvrSwt_flg) {
    set_GeEETM_HeatMode_enum(CeEETM_HeatModeOvr_enum);
  } else {
    set_GeEETM_HeatMode_enum(EETM_B.oGeEETM_HeatMode_enum);
  }

  if (CbEETM_SetTempOvrSwt_flg) {
    set_GcEETM_SetTemp_C(CcEETM_SetTempOvr_C);
  } else {
    set_GcEETM_SetTemp_C(EETM_B.oGcEETM_SetTemp_C);
  }
}

/* Model initialize function */
void EETM_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
