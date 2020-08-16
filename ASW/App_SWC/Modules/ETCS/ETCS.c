/*
 * File: ETCS.c
 *
 * Code generated for Simulink model 'ETCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 13 19:52:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ETCS.h"
#include "ETCS_private.h"

/* Named constants for Chart: '<S19>/hold3tick' */
#define ETCS_IN_DISABLE                ((uint8_T)1U)
#define ETCS_IN_ENABLE                 ((uint8_T)2U)

/* Named constants for Chart: '<S7>/HoldEnable3tick' */
#define ETCS_IN_DISABLE_o              ((uint8_T)1U)
#define ETCS_IN_ENABLE_h               ((uint8_T)2U)

/* Block signals (auto storage) */
B_ETCS_T ETCS_B;

/* Block states (auto storage) */
DW_ETCS_T ETCS_DW;

/* Real-time model */
RT_MODEL_ETCS_T ETCS_M_;
RT_MODEL_ETCS_T *const ETCS_M = &ETCS_M_;

/*
 * Output and update for atomic system:
 *    '<S19>/hold3tick'
 *    '<S33>/hold3tick'
 */
void ETCS_hold3tick(boolean_T rtu_ipt, B_hold3tick_ETCS_T *localB,
                    DW_hold3tick_ETCS_T *localDW)
{
  if (localDW->temporalCounter_i1 < 7U) {
    localDW->temporalCounter_i1++;
  }

  localDW->ipt_prev = localDW->ipt_start;
  localDW->ipt_start = rtu_ipt;
  if (localDW->is_active_c2_ETCS == 0U) {
    localDW->ipt_prev = rtu_ipt;
    localDW->is_active_c2_ETCS = 1U;
    localDW->is_c2_ETCS = ETCS_IN_DISABLE;
    localB->out = false;
  } else if (localDW->is_c2_ETCS == ETCS_IN_DISABLE) {
    if ((localDW->ipt_prev != localDW->ipt_start) && localDW->ipt_start) {
      localDW->is_c2_ETCS = ETCS_IN_ENABLE;
      localDW->temporalCounter_i1 = 0U;
      localB->out = true;
    }
  } else {
    if (localDW->temporalCounter_i1 >= 3) {
      localDW->is_c2_ETCS = ETCS_IN_DISABLE;
      localB->out = false;
    }
  }
}

/*
 * Output and update for atomic system:
 *    '<S7>/HoldEnable3tick'
 *    '<S8>/hold3tick'
 */
void ETCS_HoldEnable3tick(boolean_T rtu_iGbEMSM_24VSelfCheckSuccess,
  B_HoldEnable3tick_ETCS_T *localB, DW_HoldEnable3tick_ETCS_T *localDW)
{
  if (localDW->temporalCounter_i1 < 7U) {
    localDW->temporalCounter_i1++;
  }

  if (localDW->is_active_c5_ETCS == 0U) {
    localDW->is_active_c5_ETCS = 1U;
    localDW->is_c5_ETCS = ETCS_IN_DISABLE_o;
    localB->out = false;
  } else if (localDW->is_c5_ETCS == ETCS_IN_DISABLE_o) {
    if (rtu_iGbEMSM_24VSelfCheckSuccess) {
      localDW->is_c5_ETCS = ETCS_IN_ENABLE_h;
      localDW->temporalCounter_i1 = 0U;
      localB->out = true;
    }
  } else {
    if (localDW->temporalCounter_i1 >= 3) {
      localDW->is_c5_ETCS = ETCS_IN_DISABLE_o;
      localB->out = false;
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCS_180102F1Send1_500ms_at_outport_1' */
void ETCS_180102F1Send1_500ms(void)
{
  if (get_GbEMSM_24VSelfCheckSuccess_flg()) {
    if (CbETCS_TFDCCU1OcppReasonEnumOvrSwt_flg) {
      set_GeETCS_TFDCCU1OcppReasonEnum_enum(CeETCS_TFDCCU1OcppReasonEnumOvr_enum);
    } else {
      set_GeETCS_TFDCCU1OcppReasonEnum_enum
        (get_GcECCR_CCU1BSTSPN3511StopReasonCHGStop_enum());
    }

    if (CbETCS_TFDCCU2OcppReasonEnumOvrSwt_flg) {
      set_GeETCS_TFDCCU2OcppReasonEnum_enum(CeETCS_TFDCCU2OcppReasonEnumOvr_enum);
    } else {
      set_GeETCS_TFDCCU2OcppReasonEnum_enum
        (get_GcECCR_CCU2BSTSPN3511StopReasonCHGStop_enum());
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCS_180102F1Send2_500ms_at_outport_1' */
void ETCS_180102F1Send2_500ms(void)
{
  if (get_GbEMSM_24VSelfCheckSuccess_flg()) {
    if (CbETCS_TFDCCU1OpChrPointStatusEnumOvrSwt_flg) {
      set_GeETCS_TFDCCU1OpChrPointStatusEnum_enum
        (CeETCS_TFDCCU1OpChrPointStatusEnumOvr_enum);
    } else {
      set_GeETCS_TFDCCU1OpChrPointStatusEnum_enum(get_GeETIM_OCPPCCU1State_enum());
    }

    if (CbETCS_TFDCCU2OpChrPointStatusEnumOvrSwt_flg) {
      set_GeETCS_TFDCCU2OpChrPointStatusEnum_enum
        (CeETCS_TFDCCU2OpChrPointStatusEnumOvr_enum);
    } else {
      set_GeETCS_TFDCCU2OpChrPointStatusEnum_enum(get_GeETIM_OCPPCCU2State_enum());
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCS_180502F1Send3_1000ms_at_outport_1' */
void ETCS_180502F1Send3_1000ms(void)
{
  uint8_T rtb_Add1_p;
  uint8_T rtb_Add2_j;
  real32_T tmp;
  if (get_GbEMSM_24VSelfCheckSuccess_flg()) {
    rtb_Add1_p = (uint8_T)(1 - ETCS_DW.Memory_PreviousInput);
    rtb_Add2_j = (uint8_T)(rtb_Add1_p + 1U);
    if (CbETCS_TFDDCWhEnergeOvrSwt_flg) {
      set_GcETCS_TFDDCWhEnerge_Wh(CcETCS_TFDDCWhEnergeOvr_Wh);
    } else if (rtb_Add2_j > 1) {
      tmp = (real32_T)floor(get_GcEBSW_LeftDCWhCurrtEnerge_kwH() / 0.1F);
      if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
        tmp = 0.0F;
      } else {
        tmp = (real32_T)fmod(tmp, 4.2949673E+9F);
      }

      set_GcETCS_TFDDCWhEnerge_Wh(tmp < 0.0F ? (uint32_T)-(int32_T)(uint32_T)
        -tmp : (uint32_T)tmp);
    } else {
      tmp = (real32_T)floor(get_GcEBSW_RightDCWhCurrtEnerge_kwH() / 0.1F);
      if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
        tmp = 0.0F;
      } else {
        tmp = (real32_T)fmod(tmp, 4.2949673E+9F);
      }

      set_GcETCS_TFDDCWhEnerge_Wh(tmp < 0.0F ? (uint32_T)-(int32_T)(uint32_T)
        -tmp : (uint32_T)tmp);
    }

    if (CbETCS_TFDDCWhindexOvrSwt_flg) {
      set_GeETCS_TFDDCWhindex_enum(CeETCS_TFDDCWhindexOvr_enum);
    } else {
      set_GeETCS_TFDDCWhindex_enum(rtb_Add2_j);
    }

    ETCS_DW.Memory_PreviousInput = rtb_Add1_p;
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCS_181602F1Send1_1000ms_at_outport_1' */
void ETCS_181602F1Send1_1000ms(void)
{
  uint8_T rtb_Switch_a[8];
  int32_T i;
  if (get_GbEMSM_24VSelfCheckSuccess_flg()) {
    if (get_GbEACM_CCU1TFDAuthReq_flg()) {
      for (i = 0; i < 8; i++) {
        rtb_Switch_a[i] = get_GcEACM_LeftStaRFIDCardUID_numb( i );
      }
    } else if (get_GbEACM_CCU2TFDAuthReq_flg()) {
      rtb_Switch_a[0] = get_GcEACM_RightStaRFIDCardUID_numb( 0 );
      rtb_Switch_a[1] = get_GcEACM_RightStaRFIDCardUID_numb( 1 );
      rtb_Switch_a[2] = get_GcEACM_RightStaRFIDCardUID_numb( 2 );
      rtb_Switch_a[3] = get_GcEACM_RightStaRFIDCardUID_numb( 3 );
      rtb_Switch_a[4] = get_GcEACM_RightStaRFIDCardUID_numb( 4 );
      rtb_Switch_a[5] = get_GcEACM_RightStaRFIDCardUID_numb( 5 );
      rtb_Switch_a[6] = get_GcEACM_RightStaRFIDCardUID_numb( 6 );
      rtb_Switch_a[7] = get_GcEACM_RightStaRFIDCardUID_numb( 7 );
    } else {
      rtb_Switch_a[0] = 0U;
      rtb_Switch_a[1] = 0U;
      rtb_Switch_a[2] = 0U;
      rtb_Switch_a[3] = 0U;
      rtb_Switch_a[4] = 0U;
      rtb_Switch_a[5] = 0U;
      rtb_Switch_a[6] = 0U;
      rtb_Switch_a[7] = 0U;
    }

    ETCS_hold3tick(get_GbEACM_CCU1TFDAuthReq_flg() ||
                   get_GbEACM_CCU2TFDAuthReq_flg(), &ETCS_B.sf_hold3tick,
                   &ETCS_DW.sf_hold3tick);
    if (ETCS_B.sf_hold3tick.out) {
      if (CbETCS_TFDCardNum1OvrSwt_flg) {
        set_GcETCS_TFDCardNum1_numb(CcETCS_TFDCardNum1Ovr_numb);
      } else {
        set_GcETCS_TFDCardNum1_numb(rtb_Switch_a[0]);
      }

      if (CbETCS_TFDCardNum2OvrSwt_flg) {
        set_GcETCS_TFDCardNum2_numb(CcETCS_TFDCardNum2Ovr_numb);
      } else {
        set_GcETCS_TFDCardNum2_numb(rtb_Switch_a[1]);
      }

      if (CbETCS_TFDCardNum3OvrSwt_flg) {
        set_GcETCS_TFDCardNum3_numb(CcETCS_TFDCardNum3Ovr_numb);
      } else {
        set_GcETCS_TFDCardNum3_numb(rtb_Switch_a[2]);
      }

      if (CbETCS_TFDCardNum4OvrSwt_flg) {
        set_GcETCS_TFDCardNum4_numb(CcETCS_TFDCardNum4Ovr_numb);
      } else {
        set_GcETCS_TFDCardNum4_numb(rtb_Switch_a[3]);
      }

      if (CbETCS_TFDCardNum5OvrSwt_flg) {
        set_GcETCS_TFDCardNum5_numb(CcETCS_TFDCardNum5Ovr_numb);
      } else {
        set_GcETCS_TFDCardNum5_numb(rtb_Switch_a[4]);
      }

      if (CbETCS_TFDCardNum6OvrSwt_flg) {
        set_GcETCS_TFDCardNum6_numb(CcETCS_TFDCardNum6Ovr_numb);
      } else {
        set_GcETCS_TFDCardNum6_numb(rtb_Switch_a[5]);
      }

      if (CbETCS_TFDCardNum7OvrSwt_flg) {
        set_GcETCS_TFDCardNum7_numb(CcETCS_TFDCardNum7Ovr_numb);
      } else {
        set_GcETCS_TFDCardNum7_numb(rtb_Switch_a[6]);
      }

      if (CbETCS_TFDCardNum8OvrSwt_flg) {
        set_GcETCS_TFDCardNum8_numb(CcETCS_TFDCardNum8Ovr_numb);
      } else {
        set_GcETCS_TFDCardNum8_numb(rtb_Switch_a[7]);
      }

      if (CbETCS_TFDCardLengOvrSwt_flg) {
        set_GcETCS_TFDCardLeng_numb(CcETCS_TFDCardLengOvr_numb);
      } else {
        set_GcETCS_TFDCardLeng_numb(CcETCS_TFDCardLeng_numb);
      }

      if (CbETCS_TFDAuthRequestOvrSwt_flg) {
        set_GcETCS_TFDAuthRequest_numb(CcETCS_TFDAuthRequestOvr_numb);
      } else {
        set_GcETCS_TFDAuthRequest_numb(CcETCS_TFDAuthRequest_numb);
      }

      if (CbETCS_TFDCCUIndexOvrSwt_flg) {
        set_GcETCS_TFDCCUIndex_numb(CcETCS_TFDCCUIndexOvr_numb);
      } else if (get_GbEACM_CCU1TFDAuthReq_flg()) {
        set_GcETCS_TFDCCUIndex_numb(1U);
      } else if (get_GbEACM_CCU2TFDAuthReq_flg()) {
        set_GcETCS_TFDCCUIndex_numb(2U);
      } else {
        set_GcETCS_TFDCCUIndex_numb(0U);
      }
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCS_181602F1Send2_1000ms_at_outport_1' */
void ETCS_181602F1Send2_1000ms(void)
{
  boolean_T rtb_LogicalOperator;
  real32_T tmp;
  if (get_GbEMSM_24VSelfCheckSuccess_flg()) {
    rtb_LogicalOperator = (get_GbEACM_CCU1TFDAuthReq_flg() ||
      get_GbEACM_CCU2TFDAuthReq_flg());
    ETCS_hold3tick(rtb_LogicalOperator, &ETCS_B.sf_hold3tick_i,
                   &ETCS_DW.sf_hold3tick_i);
    if (ETCS_B.sf_hold3tick_i.out) {
      if (CbETCS_TFDCardbalanceOvrSwt_flg) {
        set_GcETCS_TFDCardbalance_rmb(CcETCS_TFDCardbalanceOvr_rmb);
      } else if (rtb_LogicalOperator) {
        tmp = (real32_T)floor(get_GcEACM_PrePayment_rmb() / 0.01F);
        if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
          tmp = 0.0F;
        } else {
          tmp = (real32_T)fmod(tmp, 4.2949673E+9F);
        }

        set_GcETCS_TFDCardbalance_rmb(tmp < 0.0F ? (uint32_T)-(int32_T)(uint32_T)
          -tmp : (uint32_T)tmp);
      } else {
        set_GcETCS_TFDCardbalance_rmb(0U);
      }

      if (CbETCS_TFDPasswordOvrSwt_flg) {
        set_GcETCS_TFDPassword_rmb(CcETCS_TFDPasswordOvr_rmb);
      } else if (rtb_LogicalOperator) {
        tmp = (real32_T)floor(get_GcEACM_ChrgFee_rmb() / 0.01F);
        if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
          tmp = 0.0F;
        } else {
          tmp = (real32_T)fmod(tmp, 4.2949673E+9F);
        }

        set_GcETCS_TFDPassword_rmb(tmp < 0.0F ? (uint32_T)-(int32_T)(uint32_T)
          -tmp : (uint32_T)tmp);
      } else {
        set_GcETCS_TFDPassword_rmb(0U);
      }
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCS_181902F1Send1_1000ms_at_outport_1' */
void ETCS_181902F1Send1_1000ms(void)
{
  ETCS_HoldEnable3tick(get_GbEMSM_24VSelfCheckSuccess_flg(),
                       &ETCS_B.sf_HoldEnable3tick, &ETCS_DW.sf_HoldEnable3tick);
  if (ETCS_B.sf_HoldEnable3tick.out) {
    if (CbETCS_TFDEACmeterSerialNumber2OvrSwt_flg) {
      set_GcETCS_TFDEACmeterSerialNumber2_numb
        (CcETCS_TFDEACmeterSerialNumber2Ovr_numb);
    } else {
      set_GcETCS_TFDEACmeterSerialNumber2_numb(((((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 4 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 5 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 6 ) << 8)) +
        get_GcEBSW_CCU1LEMMeterID_numb( 7 ));
    }

    if (CbETCS_TFDEACmeterSerialNumber3OvrSwt_flg) {
      set_GcETCS_TFDEACmeterSerialNumber3_numb
        (CcETCS_TFDEACmeterSerialNumber3Ovr_numb);
    } else {
      set_GcETCS_TFDEACmeterSerialNumber3_numb(((((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 8 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 9 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 10 ) << 8)) +
        get_GcEBSW_CCU1LEMMeterID_numb( 11 ));
    }

    if (CbETCS_TFDEACmeterSerialNumber5OvrSwt_flg) {
      set_GcETCS_TFDEACmeterSerialNumber5_numb
        (CcETCS_TFDEACmeterSerialNumber5Ovr_numb);
    } else {
      set_GcETCS_TFDEACmeterSerialNumber5_numb(((((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 16 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 17 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 18 ) << 8)) +
        get_GcEBSW_CCU1LEMMeterID_numb( 19 ));
    }

    if (CbETCS_TFDEACmeterSerialNumber4OvrSwt_flg) {
      set_GcETCS_TFDEACmeterSerialNumber4_numb
        (CcETCS_TFDEACmeterSerialNumber4Ovr_numb);
    } else {
      set_GcETCS_TFDEACmeterSerialNumber4_numb(((((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 12 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 13 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 14 ) << 8)) +
        get_GcEBSW_CCU1LEMMeterID_numb( 15 ));
    }

    if (CbETCS_TFDEACmeterSerialNumber1OvrSwt_flg) {
      set_GcETCS_TFDEACmeterSerialNumber1_numb
        (CcETCS_TFDEACmeterSerialNumber1Ovr_numb);
    } else {
      set_GcETCS_TFDEACmeterSerialNumber1_numb(((((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 0 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 1 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 2 ) << 8)) +
        get_GcEBSW_CCU1LEMMeterID_numb( 3 ));
    }

    if (CbETCS_TFDEACmeterSerialNumber6OvrSwt_flg) {
      set_GcETCS_TFDEACmeterSerialNumber6_numb
        (CcETCS_TFDEACmeterSerialNumber6Ovr_numb);
    } else {
      set_GcETCS_TFDEACmeterSerialNumber6_numb(((((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 20 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 21 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 22 ) << 8)) +
        get_GcEBSW_CCU1LEMMeterID_numb( 23 ));
    }

    if (CbETCS_TFDEACmeterSerialNumber7OvrSwt_flg) {
      set_GcETCS_TFDEACmeterSerialNumber7_numb
        (CcETCS_TFDEACmeterSerialNumber7Ovr_numb);
    } else {
      set_GcETCS_TFDEACmeterSerialNumber7_numb(((((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 24 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 25 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU1LEMMeterID_numb( 26 ) << 8)) +
        get_GcEBSW_CCU1LEMMeterID_numb( 27 ));
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCS_181902F1Send2_1000ms_at_outport_1' */
void ETCS_181902F1Send2_1000ms(void)
{
  ETCS_HoldEnable3tick(get_GbEMSM_24VSelfCheckSuccess_flg(),
                       &ETCS_B.sf_hold3tick_d, &ETCS_DW.sf_hold3tick_d);
  if (ETCS_B.sf_hold3tick_d.out) {
    if (CbETCS_TFDEDCmeterSerialNumber3OvrSwt_flg) {
      set_GcETCS_TFDEDCmeterSerialNumber3_numb
        (CcETCS_TFDEDCmeterSerialNumber3Ovr_numb);
    } else {
      set_GcETCS_TFDEDCmeterSerialNumber3_numb(((((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 8 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 9 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 10 ) << 8)) +
        get_GcEBSW_CCU2LEMMeterID_numb( 11 ));
    }

    if (CbETCS_TFDEDCmeterSerialNumber4OvrSwt_flg) {
      set_GcETCS_TFDEDCmeterSerialNumber4_numb
        (CcETCS_TFDEDCmeterSerialNumber4Ovr_numb);
    } else {
      set_GcETCS_TFDEDCmeterSerialNumber4_numb(((((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 12 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 13 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 14 ) << 8)) +
        get_GcEBSW_CCU2LEMMeterID_numb( 15 ));
    }

    if (CbETCS_TFDEDCmeterSerialNumber5OvrSwt_flg) {
      set_GcETCS_TFDEDCmeterSerialNumber5_numb
        (CcETCS_TFDEDCmeterSerialNumber5Ovr_numb);
    } else {
      set_GcETCS_TFDEDCmeterSerialNumber5_numb(((((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 16 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 17 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 18 ) << 8)) +
        get_GcEBSW_CCU2LEMMeterID_numb( 19 ));
    }

    if (CbETCS_TFDEDCmeterSerialNumber6OvrSwt_flg) {
      set_GcETCS_TFDEDCmeterSerialNumber6_numb
        (CcETCS_TFDEDCmeterSerialNumber6Ovr_numb);
    } else {
      set_GcETCS_TFDEDCmeterSerialNumber6_numb(((((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 20 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 21 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 22 ) << 8)) +
        get_GcEBSW_CCU2LEMMeterID_numb( 23 ));
    }

    if (CbETCS_TFDEDCmeterSerialNumber7OvrSwt_flg) {
      set_GcETCS_TFDEDCmeterSerialNumber7_numb
        (CcETCS_TFDEDCmeterSerialNumber7Ovr_numb);
    } else {
      set_GcETCS_TFDEDCmeterSerialNumber7_numb(((((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 24 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 25 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 26 ) << 8)) +
        get_GcEBSW_CCU2LEMMeterID_numb( 27 ));
    }

    if (CbETCS_TFDEDCmeterSerialNumber1OvrSwt_flg) {
      set_GcETCS_TFDEDCmeterSerialNumber1_numb
        (CcETCS_TFDEDCmeterSerialNumber1Ovr_numb);
    } else {
      set_GcETCS_TFDEDCmeterSerialNumber1_numb(((((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 0 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 1 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 2 ) << 8)) +
        get_GcEBSW_CCU2LEMMeterID_numb( 3 ));
    }

    if (CbETCS_TFDEDCmeterSerialNumber2OvrSwt_flg) {
      set_GcETCS_TFDEDCmeterSerialNumber2_numb
        (CcETCS_TFDEDCmeterSerialNumber2Ovr_numb);
    } else {
      set_GcETCS_TFDEDCmeterSerialNumber2_numb(((((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 4 ) << 24) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 5 ) << 16)) + ((uint32_T)
        get_GcEBSW_CCU2LEMMeterID_numb( 6 ) << 8)) +
        get_GcEBSW_CCU2LEMMeterID_numb( 7 ));
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCS_181A02F1Send_1000ms_at_outport_1' */
void ETCS_181A02F1Send_1000ms(void)
{
  if (get_GbEMSM_24VSelfCheckSuccess_flg()) {
    if (CbETCS_TFDEmeterType1OvrSwt_flg) {
      set_GcETCS_TFDEmeterType1_numb(CcETCS_TFDEmeterType1Ovr_numb);
    } else {
      set_GcETCS_TFDEmeterType1_numb(1279610207U);
    }

    if (CbETCS_TFDEmeterType2OvrSwt_flg) {
      set_GcETCS_TFDEmeterType2_numb(CcETCS_TFDEmeterType2Ovr_numb);
    } else {
      set_GcETCS_TFDEmeterType2_numb(1145258573U);
    }

    if (CbETCS_TFDEmeterType3OvrSwt_flg) {
      set_GcETCS_TFDEmeterType3_numb(CcETCS_TFDEmeterType3Ovr_numb);
    } else {
      set_GcETCS_TFDEmeterType3_numb(30257U);
    }
  }
}

/* Model initialize function */
void ETCS_initialize(void)
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
