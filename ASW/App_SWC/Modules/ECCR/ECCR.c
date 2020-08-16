/*
 * File: ECCR.c
 *
 * Code generated for Simulink model 'ECCR'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 08 15:47:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ECCR.h"
#include "ECCR_private.h"

/* Block signals (auto storage) */
B_ECCR_T ECCR_B;

/* Real-time model */
RT_MODEL_ECCR_T ECCR_M_;
RT_MODEL_ECCR_T *const ECCR_M = &ECCR_M_;

/* Forward declaration for local functions */
static int32_T safe_cast_to_Enum_ECCRCCU1State(int32_T input);
static int32_T safe_cast_to_Enum_ECCRCCU2State(int32_T input);

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU1_MsgUpdateClear_10ms_at_outport_1' */
void ECCR_CCU1_MsgUpdateClear_10ms(void)
{
  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_n) {
    if (CbECCR_CCU1BCL1817FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BCL1817FAF2hUpdate_flg(CcECCR_CCU1BCL1817FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BCL1817FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_oc) {
    if (CbECCR_CCU1BCP1812FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BCP1812FAF2hUpdate_flg(CcECCR_CCU1BCP1812FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BCP1812FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_e) {
    if (CbECCR_CCU1BCP1813FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BCP1813FAF2hUpdate_flg(CcECCR_CCU1BCP1813FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BCP1813FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_oz) {
    if (CbECCR_CCU1BCS1818FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BCS1818FAF2hUpdate_flg(CcECCR_CCU1BCS1818FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BCS1818FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_fj) {
    if (CbECCR_CCU1BHM1811FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BHM1811FAF2hUpdate_flg(CcECCR_CCU1BHM1811FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BHM1811FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_g) {
    if (CbECCR_CCU1BRM1814FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BRM1814FAF2hUpdate_flg(CcECCR_CCU1BRM1814FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BRM1814FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_dv) {
    if (CbECCR_CCU1BRM1815FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BRM1815FAF2hUpdate_flg(CcECCR_CCU1BRM1815FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BRM1815FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_l) {
    if (CbECCR_CCU1BSM181AFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BSM181AFAF2hUpdate_flg(CcECCR_CCU1BSM181AFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BSM181AFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_j3) {
    if (CbECCR_CCU1BSD181BFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BSD181BFAF2hUpdate_flg(CcECCR_CCU1BSD181BFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BSD181BFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_jp) {
    if (CbECCR_CCU1BST181CFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1BST181CFAF2hUpdate_flg(CcECCR_CCU1BST181CFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1BST181CFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_a) {
    if (CbECCR_CCU1CCS1819FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1CCS1819FAF2hUpdate_flg(CcECCR_CCU1CCS1819FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1CCS1819FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_mv) {
    if (CbECCR_CCU1CST181DFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1CST181DFAF2hUpdate_flg(CcECCR_CCU1CST181DFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1CST181DFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_ol) {
    if (CbECCR_CCU1DTC18AAFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1DTC18AAFAF2hUpdate_flg(CcECCR_CCU1DTC18AAFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1DTC18AAFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_my) {
    if (CbECCR_CCU1HV1802FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1HV1802FAF2hUpdate_flg(CcECCR_CCU1HV1802FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1HV1802FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_lp) {
    if (CbECCR_CCU1ISO1820FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1ISO1820FAF2hUpdate_flg(CcECCR_CCU1ISO1820FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1ISO1820FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_lq) {
    if (CbECCR_CCU1Sample1803FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1Sample1803FAF2hUpdate_flg
        (CcECCR_CCU1Sample1803FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1Sample1803FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN1_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_hx) {
    if (CbECCR_CCU1VIN1816FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU1VIN1816FAF2hUpdate_flg(CcECCR_CCU1VIN1816FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU1VIN1816FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU2_MsgUpdateClear_10ms_at_outport_1' */
void ECCR_CCU2_MsgUpdateClear_10ms(void)
{
  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion) {
    if (CbECCR_CCU2BCL1817FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BCL1817FAF2hUpdate_flg(CcECCR_CCU2BCL1817FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BCL1817FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_h) {
    if (CbECCR_CCU2BCP1812FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BCP1812FAF2hUpdate_flg(CcECCR_CCU2BCP1812FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BCP1812FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_i) {
    if (CbECCR_CCU2BCP1813FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BCP1813FAF2hUpdate_flg(CcECCR_CCU2BCP1813FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BCP1813FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_c) {
    if (CbECCR_CCU2BCS1818FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BCS1818FAF2hUpdate_flg(CcECCR_CCU2BCS1818FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BCS1818FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_m) {
    if (CbECCR_CCU2BHM1811FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BHM1811FAF2hUpdate_flg(CcECCR_CCU2BHM1811FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BHM1811FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_ih) {
    if (CbECCR_CCU2BRM1814FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BRM1814FAF2hUpdate_flg(CcECCR_CCU2BRM1814FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BRM1814FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_f) {
    if (CbECCR_CCU2BRM1815FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BRM1815FAF2hUpdate_flg(CcECCR_CCU2BRM1815FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BRM1815FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_cd) {
    if (CbECCR_CCU2BSM181AFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BSM181AFAF2hUpdate_flg(CcECCR_CCU2BSM181AFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BSM181AFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_i2) {
    if (CbECCR_CCU2BSD181BFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BSD181BFAF2hUpdate_flg(CcECCR_CCU2BSD181BFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BSD181BFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_p) {
    if (CbECCR_CCU2BST181CFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2BST181CFAF2hUpdate_flg(CcECCR_CCU2BST181CFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2BST181CFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_o) {
    if (CbECCR_CCU2CCS1819FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2CCS1819FAF2hUpdate_flg(CcECCR_CCU2CCS1819FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2CCS1819FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_j) {
    if (CbECCR_CCU2CST181DFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2CST181DFAF2hUpdate_flg(CcECCR_CCU2CST181DFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2CST181DFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_d) {
    if (CbECCR_CCU2DTC18AAFAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2DTC18AAFAF2hUpdate_flg(CcECCR_CCU2DTC18AAFAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2DTC18AAFAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_do) {
    if (CbECCR_CCU2HV1802FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2HV1802FAF2hUpdate_flg(CcECCR_CCU2HV1802FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2HV1802FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_k) {
    if (CbECCR_CCU2ISO1820FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2ISO1820FAF2hUpdate_flg(CcECCR_CCU2ISO1820FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2ISO1820FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_jl) {
    if (CbECCR_CCU2Sample1803FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2Sample1803FAF2hUpdate_flg
        (CcECCR_CCU2Sample1803FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2Sample1803FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GeCAN3_CCUCC1STATE_enum() != ECCR_ConstB.DataTypeConversion_doa) {
    if (CbECCR_CCU2VIN1816FAF2hUpdateOvrSwt_flg) {
      set_ECCR_CCU2VIN1816FAF2hUpdate_flg(CcECCR_CCU2VIN1816FAF2hUpdateOvr_flg);
    } else {
      set_ECCR_CCU2VIN1816FAF2hUpdate_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_BST_181CFAF2h_50ms_at_outport_1' */
void ECCR_CCU_BST_181CFAF2h_50ms(void)
{
  uint8_T rtb_Merge_kf;
  uint8_T rtb_Merge1_j2;
  uint8_T rtb_Merge2_gu;
  uint8_T rtb_Merge3_b1;
  uint8_T rtb_Merge4_av;
  uint8_T rtb_Merge5_o;
  uint8_T rtb_Merge6_f;
  uint8_T rtb_Merge7_f;
  uint8_T rtb_Merge8_bn;
  uint8_T rtb_Merge9_f;
  uint8_T rtb_Merge10_pk;
  uint8_T rtb_Merge11_c;
  uint8_T rtb_Merge12_k;
  uint8_T rtb_Merge13_nk;
  uint8_T rtb_Merge14_e;
  uint8_T rtb_Merge15_a;
  uint8_T rtb_Merge16_f;
  uint8_T rtb_Merge17_m;
  uint8_T rtb_Merge18_g;
  uint8_T rtb_Merge19_g;
  uint8_T rtb_Merge20_n;
  uint8_T rtb_Merge21_i;
  if (get_ECCR_CCU1BST181CFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_kf = get_GcCAN1_BSTSPN3511StopReasonSOC_enum();
    rtb_Merge1_j2 = get_GcCAN1_BSTSPN3511StopReasonU_enum();
    rtb_Merge2_gu = get_GcCAN1_BSTSPN3511StopReasonUcell_enum();
    rtb_Merge3_b1 = get_GcCAN1_BSTSPN3511StopReasonCHGStop_enum();
    rtb_Merge4_av = get_GcCAN1_BSTSPN3512StopFaultIso_enum();
    rtb_Merge5_o = get_GcCAN1_BSTSPN3512StopFaultOutCnnt_enum();
    rtb_Merge6_f = get_GcCAN1_BSTSPN3512StopFaultBCUcompo_enum();
    rtb_Merge7_f = get_GcCAN1_BSTSPN3512StopFaultChgCnnt_enum();
    rtb_Merge8_bn = get_GcCAN1_BSTSPN3512StopFaultT_enum();
    rtb_Merge9_f = get_GcCAN1_BSTSPN3512StopFaultHVRelay_enum();
    rtb_Merge10_pk = get_GcCAN1_BSTSPN3512StopFaultCC2_enum();
    rtb_Merge11_c = get_GcCAN1_BSTSPN3512StopFaultOther_enum();
    rtb_Merge12_k = get_GcCAN1_BSTSPN3513StopFaultI_enum();
    rtb_Merge13_nk = get_GcCAN1_BSTSPN3513StopFaultU_enum();
    rtb_Merge14_e = get_GcCAN1_BEMSPN3901TimeoutSPN25600x00_enum();
    rtb_Merge15_a = get_GcCAN1_BEMSPN3902TimeoutSPN25600xAA_enum();
    rtb_Merge16_f = get_GcCAN1_BEMSPN3903TimeoutCTSCML_enum();
    rtb_Merge17_m = get_GcCAN1_BEMSPN3904TimeoutCRO_enum();
    rtb_Merge18_g = get_GcCAN1_BEMSPN3905TimeoutCCS_enum();
    rtb_Merge19_g = get_GcCAN1_BEMSPN3906TimeoutCST_enum();
    rtb_Merge20_n = get_GcCAN1_BEMSPN3907TimeoutCSD_enum();
    rtb_Merge21_i = get_GcCAN1_BEMother_enum();
  } else {
    rtb_Merge_kf = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_j2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_gu = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_b1 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4_av = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_o = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge6_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge7_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge8_bn = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge9_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge10_pk = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge11_c = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge12_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge13_nk = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge14_e = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge15_a = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge16_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge17_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge18_g = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge19_g = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge20_n = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge21_i = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BEMSPN3901TimeoutSPN25600x00OvrSwt_flg) {
    set_GcECCR_CCU1BEMSPN3901TimeoutSPN25600x00_enum
      (CcECCR_CCU1BEMSPN3901TimeoutSPN25600x00Ovr_enum);
  } else {
    set_GcECCR_CCU1BEMSPN3901TimeoutSPN25600x00_enum(rtb_Merge14_e);
  }

  if (CbECCR_CCU1BEMSPN3902TimeoutSPN25600xAAOvrSwt_flg) {
    set_GcECCR_CCU1BEMSPN3902TimeoutSPN25600xAA_enum
      (CcECCR_CCU1BEMSPN3902TimeoutSPN25600xAAOvr_enum);
  } else {
    set_GcECCR_CCU1BEMSPN3902TimeoutSPN25600xAA_enum(rtb_Merge15_a);
  }

  if (CbECCR_CCU1BEMSPN3903TimeoutCTSCMLOvrSwt_flg) {
    set_GcECCR_CCU1BEMSPN3903TimeoutCTSCML_enum
      (CcECCR_CCU1BEMSPN3903TimeoutCTSCMLOvr_enum);
  } else {
    set_GcECCR_CCU1BEMSPN3903TimeoutCTSCML_enum(rtb_Merge16_f);
  }

  if (CbECCR_CCU1BEMSPN3904TimeoutCROOvrSwt_flg) {
    set_GcECCR_CCU1BEMSPN3904TimeoutCRO_enum
      (CcECCR_CCU1BEMSPN3904TimeoutCROOvr_enum);
  } else {
    set_GcECCR_CCU1BEMSPN3904TimeoutCRO_enum(rtb_Merge17_m);
  }

  if (CbECCR_CCU1BEMSPN3905TimeoutCCSOvrSwt_flg) {
    set_GcECCR_CCU1BEMSPN3905TimeoutCCS_enum
      (CcECCR_CCU1BEMSPN3905TimeoutCCSOvr_enum);
  } else {
    set_GcECCR_CCU1BEMSPN3905TimeoutCCS_enum(rtb_Merge18_g);
  }

  if (CbECCR_CCU1BEMSPN3906TimeoutCSTOvrSwt_flg) {
    set_GcECCR_CCU1BEMSPN3906TimeoutCST_enum
      (CcECCR_CCU1BEMSPN3906TimeoutCSTOvr_enum);
  } else {
    set_GcECCR_CCU1BEMSPN3906TimeoutCST_enum(rtb_Merge19_g);
  }

  if (CbECCR_CCU1BEMSPN3907TimeoutCSDOvrSwt_flg) {
    set_GcECCR_CCU1BEMSPN3907TimeoutCSD_enum
      (CcECCR_CCU1BEMSPN3907TimeoutCSDOvr_enum);
  } else {
    set_GcECCR_CCU1BEMSPN3907TimeoutCSD_enum(rtb_Merge20_n);
  }

  if (CbECCR_CCU1BEMotherOvrSwt_flg) {
    set_GcECCR_CCU1BEMother_enum(CcECCR_CCU1BEMotherOvr_enum);
  } else {
    set_GcECCR_CCU1BEMother_enum(rtb_Merge21_i);
  }

  if (CbECCR_CCU1BSTSPN3511StopReasonCHGStopOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3511StopReasonCHGStop_enum
      (CcECCR_CCU1BSTSPN3511StopReasonCHGStopOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3511StopReasonCHGStop_enum(rtb_Merge3_b1);
  }

  if (CbECCR_CCU1BSTSPN3511StopReasonSOCOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3511StopReasonSOC_enum
      (CcECCR_CCU1BSTSPN3511StopReasonSOCOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3511StopReasonSOC_enum(rtb_Merge_kf);
  }

  if (CbECCR_CCU1BSTSPN3511StopReasonUOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3511StopReasonU_enum
      (CcECCR_CCU1BSTSPN3511StopReasonUOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3511StopReasonU_enum(rtb_Merge1_j2);
  }

  if (CbECCR_CCU1BSTSPN3511StopReasonUcellOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3511StopReasonUcell_enum
      (CcECCR_CCU1BSTSPN3511StopReasonUcellOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3511StopReasonUcell_enum(rtb_Merge2_gu);
  }

  if (CbECCR_CCU1BSTSPN3512StopFaultBCUcompoOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3512StopFaultBCUcompo_enum
      (CcECCR_CCU1BSTSPN3512StopFaultBCUcompoOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3512StopFaultBCUcompo_enum(rtb_Merge6_f);
  }

  if (CbECCR_CCU1BSTSPN3512StopFaultCC2OvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3512StopFaultCC2_enum
      (CcECCR_CCU1BSTSPN3512StopFaultCC2Ovr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3512StopFaultCC2_enum(rtb_Merge10_pk);
  }

  if (CbECCR_CCU1BSTSPN3512StopFaultChgCnntOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3512StopFaultChgCnnt_enum
      (CcECCR_CCU1BSTSPN3512StopFaultChgCnntOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3512StopFaultChgCnnt_enum(rtb_Merge7_f);
  }

  if (CbECCR_CCU1BSTSPN3512StopFaultHVRelayOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3512StopFaultHVRelay_enum
      (CcECCR_CCU1BSTSPN3512StopFaultHVRelayOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3512StopFaultHVRelay_enum(rtb_Merge9_f);
  }

  if (CbECCR_CCU1BSTSPN3512StopFaultIsoOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3512StopFaultIso_enum
      (CcECCR_CCU1BSTSPN3512StopFaultIsoOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3512StopFaultIso_enum(rtb_Merge4_av);
  }

  if (CbECCR_CCU1BSTSPN3512StopFaultOtherOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3512StopFaultOther_enum
      (CcECCR_CCU1BSTSPN3512StopFaultOtherOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3512StopFaultOther_enum(rtb_Merge11_c);
  }

  if (CbECCR_CCU1BSTSPN3512StopFaultOutCnntOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3512StopFaultOutCnnt_enum
      (CcECCR_CCU1BSTSPN3512StopFaultOutCnntOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3512StopFaultOutCnnt_enum(rtb_Merge5_o);
  }

  if (CbECCR_CCU1BSTSPN3512StopFaultTOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3512StopFaultT_enum
      (CcECCR_CCU1BSTSPN3512StopFaultTOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3512StopFaultT_enum(rtb_Merge8_bn);
  }

  if (CbECCR_CCU1BSTSPN3513StopFaultIOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3513StopFaultI_enum
      (CcECCR_CCU1BSTSPN3513StopFaultIOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3513StopFaultI_enum(rtb_Merge12_k);
  }

  if (CbECCR_CCU1BSTSPN3513StopFaultUOvrSwt_flg) {
    set_GcECCR_CCU1BSTSPN3513StopFaultU_enum
      (CcECCR_CCU1BSTSPN3513StopFaultUOvr_enum);
  } else {
    set_GcECCR_CCU1BSTSPN3513StopFaultU_enum(rtb_Merge13_nk);
  }

  if (get_ECCR_CCU2BST181CFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_kf = get_GcCAN3_BSTSPN3511StopReasonSOC_enum();
    rtb_Merge1_j2 = get_GcCAN3_BSTSPN3511StopReasonU_enum();
    rtb_Merge2_gu = get_GcCAN3_BSTSPN3511StopReasonUcell_enum();
    rtb_Merge3_b1 = get_GcCAN3_BSTSPN3511StopReasonCHGStop_enum();
    rtb_Merge4_av = get_GcCAN3_BSTSPN3512StopFaultIso_enum();
    rtb_Merge5_o = get_GcCAN3_BSTSPN3512StopFaultOutCnnt_enum();
    rtb_Merge6_f = get_GcCAN3_BSTSPN3512StopFaultBCUcompo_enum();
    rtb_Merge7_f = get_GcCAN3_BSTSPN3512StopFaultChgCnnt_enum();
    rtb_Merge8_bn = get_GcCAN3_BSTSPN3512StopFaultT_enum();
    rtb_Merge9_f = get_GcCAN3_BSTSPN3512StopFaultHVRelay_enum();
    rtb_Merge10_pk = get_GcCAN3_BSTSPN3512StopFaultCC2_enum();
    rtb_Merge11_c = get_GcCAN3_BSTSPN3512StopFaultOther_enum();
    rtb_Merge12_k = get_GcCAN3_BSTSPN3513StopFaultI_enum();
    rtb_Merge13_nk = get_GcCAN3_BSTSPN3513StopFaultU_enum();
    rtb_Merge14_e = get_GcCAN3_BEMSPN3901TimeoutSPN25600x00_enum();
    rtb_Merge15_a = get_GcCAN3_BEMSPN3902TimeoutSPN25600xAA_enum();
    rtb_Merge16_f = get_GcCAN3_BEMSPN3903TimeoutCTSCML_enum();
    rtb_Merge17_m = get_GcCAN3_BEMSPN3904TimeoutCRO_enum();
    rtb_Merge18_g = get_GcCAN3_BEMSPN3905TimeoutCCS_enum();
    rtb_Merge19_g = get_GcCAN3_BEMSPN3906TimeoutCST_enum();
    rtb_Merge20_n = get_GcCAN3_BEMSPN3907TimeoutCSD_enum();
    rtb_Merge21_i = get_GcCAN3_BEMother_enum();
  } else {
    rtb_Merge_kf = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_j2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_gu = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_b1 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4_av = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_o = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge6_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge7_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge8_bn = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge9_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge10_pk = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge11_c = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge12_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge13_nk = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge14_e = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge15_a = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge16_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge17_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge18_g = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge19_g = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge20_n = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge21_i = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BEMSPN3901TimeoutSPN25600x00OvrSwt_flg) {
    set_GcECCR_CCU2BEMSPN3901TimeoutSPN25600x00_enum
      (CcECCR_CCU2BEMSPN3901TimeoutSPN25600x00Ovr_enum);
  } else {
    set_GcECCR_CCU2BEMSPN3901TimeoutSPN25600x00_enum(rtb_Merge14_e);
  }

  if (CbECCR_CCU2BEMSPN3902TimeoutSPN25600xAAOvrSwt_flg) {
    set_GcECCR_CCU2BEMSPN3902TimeoutSPN25600xAA_enum
      (CcECCR_CCU2BEMSPN3902TimeoutSPN25600xAAOvr_enum);
  } else {
    set_GcECCR_CCU2BEMSPN3902TimeoutSPN25600xAA_enum(rtb_Merge15_a);
  }

  if (CbECCR_CCU2BEMSPN3903TimeoutCTSCMLOvrSwt_flg) {
    set_GcECCR_CCU2BEMSPN3903TimeoutCTSCML_enum
      (CcECCR_CCU2BEMSPN3903TimeoutCTSCMLOvr_enum);
  } else {
    set_GcECCR_CCU2BEMSPN3903TimeoutCTSCML_enum(rtb_Merge16_f);
  }

  if (CbECCR_CCU2BEMSPN3904TimeoutCROOvrSwt_flg) {
    set_GcECCR_CCU2BEMSPN3904TimeoutCRO_enum
      (CcECCR_CCU2BEMSPN3904TimeoutCROOvr_enum);
  } else {
    set_GcECCR_CCU2BEMSPN3904TimeoutCRO_enum(rtb_Merge17_m);
  }

  if (CbECCR_CCU2BEMSPN3905TimeoutCCSOvrSwt_flg) {
    set_GcECCR_CCU2BEMSPN3905TimeoutCCS_enum
      (CcECCR_CCU2BEMSPN3905TimeoutCCSOvr_enum);
  } else {
    set_GcECCR_CCU2BEMSPN3905TimeoutCCS_enum(rtb_Merge18_g);
  }

  if (CbECCR_CCU2BEMSPN3906TimeoutCSTOvrSwt_flg) {
    set_GcECCR_CCU2BEMSPN3906TimeoutCST_enum
      (CcECCR_CCU2BEMSPN3906TimeoutCSTOvr_enum);
  } else {
    set_GcECCR_CCU2BEMSPN3906TimeoutCST_enum(rtb_Merge19_g);
  }

  if (CbECCR_CCU2BEMSPN3907TimeoutCSDOvrSwt_flg) {
    set_GcECCR_CCU2BEMSPN3907TimeoutCSD_enum
      (CcECCR_CCU2BEMSPN3907TimeoutCSDOvr_enum);
  } else {
    set_GcECCR_CCU2BEMSPN3907TimeoutCSD_enum(rtb_Merge20_n);
  }

  if (CbECCR_CCU2BEMotherOvrSwt_flg) {
    set_GcECCR_CCU2BEMother_enum(CcECCR_CCU2BEMotherOvr_enum);
  } else {
    set_GcECCR_CCU2BEMother_enum(rtb_Merge21_i);
  }

  if (CbECCR_CCU2BSTSPN3511StopReasonCHGStopOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3511StopReasonCHGStop_enum
      (CcECCR_CCU2BSTSPN3511StopReasonCHGStopOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3511StopReasonCHGStop_enum(rtb_Merge3_b1);
  }

  if (CbECCR_CCU2BSTSPN3511StopReasonSOCOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3511StopReasonSOC_enum
      (CcECCR_CCU2BSTSPN3511StopReasonSOCOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3511StopReasonSOC_enum(rtb_Merge_kf);
  }

  if (CbECCR_CCU2BSTSPN3511StopReasonUOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3511StopReasonU_enum
      (CcECCR_CCU2BSTSPN3511StopReasonUOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3511StopReasonU_enum(rtb_Merge1_j2);
  }

  if (CbECCR_CCU2BSTSPN3511StopReasonUcellOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3511StopReasonUcell_enum
      (CcECCR_CCU2BSTSPN3511StopReasonUcellOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3511StopReasonUcell_enum(rtb_Merge2_gu);
  }

  if (CbECCR_CCU2BSTSPN3512StopFaultBCUcompoOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3512StopFaultBCUcompo_enum
      (CcECCR_CCU2BSTSPN3512StopFaultBCUcompoOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3512StopFaultBCUcompo_enum(rtb_Merge6_f);
  }

  if (CbECCR_CCU2BSTSPN3512StopFaultCC2OvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3512StopFaultCC2_enum
      (CcECCR_CCU2BSTSPN3512StopFaultCC2Ovr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3512StopFaultCC2_enum(rtb_Merge10_pk);
  }

  if (CbECCR_CCU2BSTSPN3512StopFaultChgCnntOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3512StopFaultChgCnnt_enum
      (CcECCR_CCU2BSTSPN3512StopFaultChgCnntOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3512StopFaultChgCnnt_enum(rtb_Merge7_f);
  }

  if (CbECCR_CCU2BSTSPN3512StopFaultHVRelayOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3512StopFaultHVRelay_enum
      (CcECCR_CCU2BSTSPN3512StopFaultHVRelayOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3512StopFaultHVRelay_enum(rtb_Merge9_f);
  }

  if (CbECCR_CCU2BSTSPN3512StopFaultIsoOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3512StopFaultIso_enum
      (CcECCR_CCU2BSTSPN3512StopFaultIsoOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3512StopFaultIso_enum(rtb_Merge4_av);
  }

  if (CbECCR_CCU2BSTSPN3512StopFaultOtherOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3512StopFaultOther_enum
      (CcECCR_CCU2BSTSPN3512StopFaultOtherOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3512StopFaultOther_enum(rtb_Merge11_c);
  }

  if (CbECCR_CCU2BSTSPN3512StopFaultOutCnntOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3512StopFaultOutCnnt_enum
      (CcECCR_CCU2BSTSPN3512StopFaultOutCnntOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3512StopFaultOutCnnt_enum(rtb_Merge5_o);
  }

  if (CbECCR_CCU2BSTSPN3512StopFaultTOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3512StopFaultT_enum
      (CcECCR_CCU2BSTSPN3512StopFaultTOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3512StopFaultT_enum(rtb_Merge8_bn);
  }

  if (CbECCR_CCU2BSTSPN3513StopFaultIOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3513StopFaultI_enum
      (CcECCR_CCU2BSTSPN3513StopFaultIOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3513StopFaultI_enum(rtb_Merge12_k);
  }

  if (CbECCR_CCU2BSTSPN3513StopFaultUOvrSwt_flg) {
    set_GcECCR_CCU2BSTSPN3513StopFaultU_enum
      (CcECCR_CCU2BSTSPN3513StopFaultUOvr_enum);
  } else {
    set_GcECCR_CCU2BSTSPN3513StopFaultU_enum(rtb_Merge13_nk);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_CCS_1819FAF2h_50ms_at_outport_1' */
void ECCR_CCU_CCS_1819FAF2h_50ms(void)
{
  real32_T rtb_Merge_gj;
  real32_T rtb_Merge1_lv;
  uint16_T rtb_Merge2_o;
  if (get_ECCR_CCU1CCS1819FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_gj = (real32_T)get_GcCAN1_CCSSPN3081UOut_V() * 0.1F;
    rtb_Merge1_lv = (real32_T)get_GcCAN1_CCSSPN3082IOut_A() * 0.1F - 400.0F;
    rtb_Merge2_o = get_GcCAN1_CCSSPN3083TimeCharged_min();
  } else {
    rtb_Merge_gj = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_lv = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_o = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1CCSSPN3081UOutOvrSwt_flg) {
    set_GcECCR_CCU1CCSSPN3081UOut_V(CcECCR_CCU1CCSSPN3081UOutOvr_V);
  } else {
    set_GcECCR_CCU1CCSSPN3081UOut_V(rtb_Merge_gj);
  }

  if (CbECCR_CCU1CCSSPN3082IOutOvrSwt_flg) {
    set_GcECCR_CCU1CCSSPN3082IOut_A(CcECCR_CCU1CCSSPN3082IOutOvr_A);
  } else {
    set_GcECCR_CCU1CCSSPN3082IOut_A(rtb_Merge1_lv);
  }

  if (CbECCR_CCU1CCSSPN3083TimeChargedOvrSwt_flg) {
    set_GcECCR_CCU1CCSSPN3083TimeCharged_Min
      (CcECCR_CCU1CCSSPN3083TimeChargedOvr_Min);
  } else {
    set_GcECCR_CCU1CCSSPN3083TimeCharged_Min(rtb_Merge2_o);
  }

  if (get_ECCR_CCU2CCS1819FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_gj = (real32_T)get_GcCAN3_CCSSPN3081UOut_V() * 0.1F;
    rtb_Merge1_lv = (real32_T)get_GcCAN3_CCSSPN3082IOut_A() * 0.1F - 400.0F;
    rtb_Merge2_o = get_GcCAN3_CCSSPN3083TimeCharged_min();
  } else {
    rtb_Merge_gj = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_lv = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_o = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2CCSSPN3081UOutOvrSwt_flg) {
    set_GcECCR_CCU2CCSSPN3081UOut_V(CcECCR_CCU2CCSSPN3081UOutOvr_V);
  } else {
    set_GcECCR_CCU2CCSSPN3081UOut_V(rtb_Merge_gj);
  }

  if (CbECCR_CCU2CCSSPN3082IOutOvrSwt_flg) {
    set_GcECCR_CCU2CCSSPN3082IOut_A(CcECCR_CCU2CCSSPN3082IOutOvr_A);
  } else {
    set_GcECCR_CCU2CCSSPN3082IOut_A(rtb_Merge1_lv);
  }

  if (CbECCR_CCU2CCSSPN3083TimeChargedOvrSwt_flg) {
    set_GcECCR_CCU2CCSSPN3083TimeCharged_Min
      (CcECCR_CCU2CCSSPN3083TimeChargedOvr_Min);
  } else {
    set_GcECCR_CCU2CCSSPN3083TimeCharged_Min(rtb_Merge2_o);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_CCS_1821FAF2h_50ms_at_outport_1' */
void ECCR_CCU_CCS_1821FAF2h_50ms(void)
{
  if (CbECCR_CCU1DirectPosStateOvrSwt_flg) {
    set_GcECCR_CCU1DirectPosState_enum(CcECCR_CCU1DirectPosStateOvr_enum);
  } else {
    set_GcECCR_CCU1DirectPosState_enum(get_GcCAN1_CCU1DirectPosState_enum());
  }

  if (CbECCR_CCU1DirectNegStateOvrSwt_flg) {
    set_GcECCR_CCU1DirectNegState_enum(CcECCR_CCU1DirectNegStateOvr_enum);
  } else {
    set_GcECCR_CCU1DirectNegState_enum(get_GcCAN1_CCU1DirectNegState_enum());
  }

  if (CbECCR_CCU1CrossPosStateOvrSwt_flg) {
    set_GcECCR_CCU1CrossPosState_enum(CcECCR_CCU1CrossPosStateOvr_enum);
  } else {
    set_GcECCR_CCU1CrossPosState_enum(get_GcCAN1_CCU1CrossPosState_enum());
  }

  if (CbECCR_CCU1CrossNegStateOvrSwt_flg) {
    set_GcECCR_CCU1CrossNegState_enum(CcECCR_CCU1CrossNegStateOvr_enum);
  } else {
    set_GcECCR_CCU1CrossNegState_enum(get_GcCAN1_CCU1CrossNegState_enum());
  }

  if (CbECCR_CCU2DirectPosStateOvrSwt_flg) {
    set_GcECCR_CCU2DirectPosState_enum(CcECCR_CCU2DirectPosStateOvr_enum);
  } else {
    set_GcECCR_CCU2DirectPosState_enum(get_GcCAN3_CCU2DirectPosState_enum());
  }

  if (CbECCR_CCU2DirectNegStateOvrSwt_flg) {
    set_GcECCR_CCU2DirectNegState_enum(CcECCR_CCU2DirectNegStateOvr_enum);
  } else {
    set_GcECCR_CCU2DirectNegState_enum(get_GcCAN3_CCU2DirectNegState_enum());
  }

  if (CbECCR_CCU2CrossPosStateOvrSwt_flg) {
    set_GcECCR_CCU2CrossPosState_enum(CcECCR_CCU2CrossPosStateOvr_enum);
  } else {
    set_GcECCR_CCU2CrossPosState_enum(get_GcCAN3_CCU2CrossPosState_enum());
  }

  if (CbECCR_CCU2CrossNegStateOvrSwt_flg) {
    set_GcECCR_CCU2CrossNegState_enum(CcECCR_CCU2CrossNegStateOvr_enum);
  } else {
    set_GcECCR_CCU2CrossNegState_enum(get_GcCAN3_CCU2CrossNegState_enum());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_CST_181DFAF2_50ms_at_outport_1' */
void ECCR_CCU_CST_181DFAF2_50ms(void)
{
  uint8_T rtb_Merge_c;
  uint8_T rtb_Merge1_m;
  uint8_T rtb_Merge2_mu;
  uint8_T rtb_Merge3_kt;
  uint8_T rtb_Merge4_e;
  uint8_T rtb_Merge5_m;
  uint8_T rtb_Merge6_l;
  uint8_T rtb_Merge7_ef;
  uint8_T rtb_Merge8_fi;
  uint8_T rtb_Merge9_hw;
  uint8_T rtb_Merge10_j;
  uint8_T rtb_Merge11_i;
  uint8_T rtb_Merge12_k;
  uint8_T rtb_Merge13_d;
  uint8_T rtb_Merge14_d;
  uint8_T rtb_Merge15_d;
  uint8_T rtb_Merge16_k;
  uint8_T rtb_Merge17_h;
  uint8_T rtb_Merge18_f;
  uint8_T rtb_Merge19_n;
  if (get_ECCR_CCU1CST181DFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_c = get_GeCAN1_CSTSPN3521StopReasonAuto_enum();
    rtb_Merge1_m = get_GeCAN1_CSTSPN3521StopReasonManual_enum();
    rtb_Merge2_mu = get_GeCAN1_CSTSPN3521StopReasonFault_enum();
    rtb_Merge3_kt = get_GeCAN1_CSTSPN3521StopReasonBMSStop_enum();
    rtb_Merge4_e = get_GeCAN1_CSTSPN3522StopFaultTCHG_enum();
    rtb_Merge5_m = get_GeCAN1_CSTSPN3522StopFaultCHGCnnt_enum();
    rtb_Merge6_l = get_GeCAN1_CSTSPN3522StopFaultTInter_enum();
    rtb_Merge7_ef = get_GeCAN1_CSTSPN3522StopFaultDeliver_enum();
    rtb_Merge8_fi = get_GeCAN1_CSTSPN3522StopFaultEmerStop_enum();
    rtb_Merge9_hw = get_GeCAN1_CSTSPN3522StopFaultOther_enum();
    rtb_Merge10_j = get_GeCAN1_CSTSPN3523StopFaultMismatch_enum();
    rtb_Merge11_i = get_GeCAN1_CSTSPN3523StopFaultU_enum();
    rtb_Merge12_k = get_GeCAN1_CEMSPN3921TimeoutBRM_enum();
    rtb_Merge13_d = get_GeCAN1_CEMSPN3922TimeoutBCP_enum();
    rtb_Merge14_d = get_GeCAN1_CEMSPN3923TimeoutBRO_enum();
    rtb_Merge15_d = get_GeCAN1_CEMSPN3924TimeoutBCS_enum();
    rtb_Merge16_k = get_GeCAN1_CEMSPN3925TimeoutBCL_enum();
    rtb_Merge17_h = get_GeCAN1_CEMSPN3926TimeoutBST_enum();
    rtb_Merge18_f = get_GeCAN1_CEMSPN3927TimeoutBSD_enum();
    rtb_Merge19_n = get_GeCAN1_CEMother_enum();
  } else {
    rtb_Merge_c = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_mu = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_kt = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4_e = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge6_l = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge7_ef = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge8_fi = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge9_hw = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge10_j = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge11_i = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge12_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge13_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge14_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge15_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge16_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge17_h = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge18_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge19_n = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1CEMOtherOvrSwt_flg) {
    set_GeECCR_CCU1CEMOther_enum(CeECCR_CCU1CEMOtherOvr_enum);
  } else {
    set_GeECCR_CCU1CEMOther_enum(rtb_Merge19_n);
  }

  if (CbECCR_CCU1CEMSPN3921TimeoutBRMOvrSwt_flg) {
    set_GeECCR_CCU1CEMSPN3921TimeoutBRM_enum
      (CeECCR_CCU1CEMSPN3921TimeoutBRMOvr_enum);
  } else {
    set_GeECCR_CCU1CEMSPN3921TimeoutBRM_enum(rtb_Merge12_k);
  }

  if (CbECCR_CCU1CEMSPN3922TimeoutBCPOvrSwt_flg) {
    set_GeECCR_CCU1CEMSPN3922TimeoutBCP_enum
      (CeECCR_CCU1CEMSPN3922TimeoutBCPOvr_enum);
  } else {
    set_GeECCR_CCU1CEMSPN3922TimeoutBCP_enum(rtb_Merge13_d);
  }

  if (CbECCR_CCU1CEMSPN3923TimeoutBROOvrSwt_flg) {
    set_GeECCR_CCU1CEMSPN3923TimeoutBRO_enum
      (CeECCR_CCU1CEMSPN3923TimeoutBROOvr_enum);
  } else {
    set_GeECCR_CCU1CEMSPN3923TimeoutBRO_enum(rtb_Merge14_d);
  }

  if (CbECCR_CCU1CEMSPN3924TimeoutBCSOvrSwt_flg) {
    set_GeECCR_CCU1CEMSPN3924TimeoutBCS_enum
      (CeECCR_CCU1CEMSPN3924TimeoutBCSOvr_enum);
  } else {
    set_GeECCR_CCU1CEMSPN3924TimeoutBCS_enum(rtb_Merge15_d);
  }

  if (CbECCR_CCU1CEMSPN3925TimeoutBCLOvrSwt_flg) {
    set_GeECCR_CCU1CEMSPN3925TimeoutBCL_enum
      (CeECCR_CCU1CEMSPN3925TimeoutBCLOvr_enum);
  } else {
    set_GeECCR_CCU1CEMSPN3925TimeoutBCL_enum(rtb_Merge16_k);
  }

  if (CbECCR_CCU1CEMSPN3926TimeoutBSTOvrSwt_flg) {
    set_GeECCR_CCU1CEMSPN3926TimeoutBST_enum
      (CeECCR_CCU1CEMSPN3926TimeoutBSTOvr_enum);
  } else {
    set_GeECCR_CCU1CEMSPN3926TimeoutBST_enum(rtb_Merge17_h);
  }

  if (CbECCR_CCU1CEMSPN3927TimeoutBSDOvrSwt_flg) {
    set_GeECCR_CCU1CEMSPN3927TimeoutBSD_enum
      (CeECCR_CCU1CEMSPN3927TimeoutBSDOvr_enum);
  } else {
    set_GeECCR_CCU1CEMSPN3927TimeoutBSD_enum(rtb_Merge18_f);
  }

  if (CbECCR_CCU1CSTSPN3521StopReasonAutoOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3521StopReasonAuto_enum
      (CeECCR_CCU1CSTSPN3521StopReasonAutoOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3521StopReasonAuto_enum(rtb_Merge_c);
  }

  if (CbECCR_CCU1CSTSPN3521StopReasonBMSStopOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3521StopReasonBMSStop_enum
      (CeECCR_CCU1CSTSPN3521StopReasonBMSStopOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3521StopReasonBMSStop_enum(rtb_Merge3_kt);
  }

  if (CbECCR_CCU1CSTSPN3521StopReasonFaultOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3521StopReasonFault_enum
      (CeECCR_CCU1CSTSPN3521StopReasonFaultOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3521StopReasonFault_enum(rtb_Merge2_mu);
  }

  if (CbECCR_CCU1CSTSPN3521StopReasonManualOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3521StopReasonManual_enum
      (CeECCR_CCU1CSTSPN3521StopReasonManualOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3521StopReasonManual_enum(rtb_Merge1_m);
  }

  if (CbECCR_CCU1CSTSPN3522StopFaultCHGCnntOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3522StopFaultCHGCnnt_enum
      (CeECCR_CCU1CSTSPN3522StopFaultCHGCnntOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3522StopFaultCHGCnnt_enum(rtb_Merge5_m);
  }

  if (CbECCR_CCU1CSTSPN3522StopFaultDeliverOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3522StopFaultDeliver_enum
      (CeECCR_CCU1CSTSPN3522StopFaultDeliverOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3522StopFaultDeliver_enum(rtb_Merge7_ef);
  }

  if (CbECCR_CCU1CSTSPN3522StopFaultEmerStopOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3522StopFaultEmerStop_enum
      (CeECCR_CCU1CSTSPN3522StopFaultEmerStopOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3522StopFaultEmerStop_enum(rtb_Merge8_fi);
  }

  if (CbECCR_CCU1CSTSPN3522StopFaultOtherOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3522StopFaultOther_enum
      (CeECCR_CCU1CSTSPN3522StopFaultOtherOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3522StopFaultOther_enum(rtb_Merge9_hw);
  }

  if (CbECCR_CCU1CSTSPN3522StopFaultTCHGOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3522StopFaultTCHG_enum
      (CeECCR_CCU1CSTSPN3522StopFaultTCHGOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3522StopFaultTCHG_enum(rtb_Merge4_e);
  }

  if (CbECCR_CCU1CSTSPN3522StopFaultTInterOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3522StopFaultTInter_enum
      (CeECCR_CCU1CSTSPN3522StopFaultTInterOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3522StopFaultTInter_enum(rtb_Merge6_l);
  }

  if (CbECCR_CCU1CSTSPN3523StopFaultMismatchOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3523StopFaultMismatch_enum
      (CeECCR_CCU1CSTSPN3523StopFaultMismatchOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3523StopFaultMismatch_enum(rtb_Merge10_j);
  }

  if (CbECCR_CCU1CSTSPN3523StopFaultUOvrSwt_flg) {
    set_GeECCR_CCU1CSTSPN3523StopFaultU_enum
      (CeECCR_CCU1CSTSPN3523StopFaultUOvr_enum);
  } else {
    set_GeECCR_CCU1CSTSPN3523StopFaultU_enum(rtb_Merge11_i);
  }

  if (get_ECCR_CCU2CST181DFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_c = get_GeCAN3_CSTSPN3521StopReasonAuto_enum();
    rtb_Merge1_m = get_GeCAN3_CSTSPN3521StopReaManual_enum();
    rtb_Merge2_mu = get_GeCAN3_CSTSPN3521StopReasonFault_enum();
    rtb_Merge3_kt = get_GeCAN3_CSTSPN3521StopReaBMSStop_enum();
    rtb_Merge4_e = get_GeCAN3_CSTSPN3522StopFaultTCHG_enum();
    rtb_Merge5_m = get_GeCAN3_CSTSPN3522StopFaultCHGCnnt_enum();
    rtb_Merge6_l = get_GeCAN3_CSTSPN3522StopFaultTInter_enum();
    rtb_Merge7_ef = get_GeCAN3_CSTSPN3522StopFaultDeliver_enum();
    rtb_Merge8_fi = get_GeCAN3_CST3522StopFaultEmerStop_enum();
    rtb_Merge9_hw = get_GeCAN3_CSTSPN3522StopFaultOther_enum();
    rtb_Merge10_j = get_GeCAN3_CST3523StopFaultMismatch_enum();
    rtb_Merge11_i = get_GeCAN3_CSTSPN3523StopFaultU_enum();
    rtb_Merge12_k = get_GeCAN3_CEMSPN3921TimeoutBRM_enum();
    rtb_Merge13_d = get_GeCAN3_CEMSPN3922TimeoutBCP_enum();
    rtb_Merge14_d = get_GeCAN3_CEMSPN3923TimeoutBRO_enum();
    rtb_Merge15_d = get_GeCAN3_CEMSPN3924TimeoutBCS_enum();
    rtb_Merge16_k = get_GeCAN3_CEMSPN3925TimeoutBCL_enum();
    rtb_Merge17_h = get_GeCAN3_CEMSPN3926TimeoutBST_enum();
    rtb_Merge18_f = get_GeCAN3_CEMSPN3927TimeoutBSD_enum();
    rtb_Merge19_n = get_GeCAN3_CEMother_enum();
  } else {
    rtb_Merge_c = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_mu = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_kt = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4_e = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge6_l = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge7_ef = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge8_fi = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge9_hw = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge10_j = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge11_i = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge12_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge13_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge14_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge15_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge16_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge17_h = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge18_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge19_n = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2CEMOtherOvrSwt_flg) {
    set_GeECCR_CCU2CEMOther_enum(CeECCR_CCU2CEMOtherOvr_enum);
  } else {
    set_GeECCR_CCU2CEMOther_enum(rtb_Merge19_n);
  }

  if (CbECCR_CCU2CEMSPN3921TimeoutBRMOvrSwt_flg) {
    set_GeECCR_CCU2CEMSPN3921TimeoutBRM_enum
      (CeECCR_CCU2CEMSPN3921TimeoutBRMOvr_enum);
  } else {
    set_GeECCR_CCU2CEMSPN3921TimeoutBRM_enum(rtb_Merge12_k);
  }

  if (CbECCR_CCU2CEMSPN3922TimeoutBCPOvrSwt_flg) {
    set_GeECCR_CCU2CEMSPN3922TimeoutBCP_enum
      (CeECCR_CCU2CEMSPN3922TimeoutBCPOvr_enum);
  } else {
    set_GeECCR_CCU2CEMSPN3922TimeoutBCP_enum(rtb_Merge13_d);
  }

  if (CbECCR_CCU2CEMSPN3923TimeoutBROOvrSwt_flg) {
    set_GeECCR_CCU2CEMSPN3923TimeoutBRO_enum
      (CeECCR_CCU2CEMSPN3923TimeoutBROOvr_enum);
  } else {
    set_GeECCR_CCU2CEMSPN3923TimeoutBRO_enum(rtb_Merge14_d);
  }

  if (CbECCR_CCU2CEMSPN3924TimeoutBCSOvrSwt_flg) {
    set_GeECCR_CCU2CEMSPN3924TimeoutBCS_enum
      (CeECCR_CCU2CEMSPN3924TimeoutBCSOvr_enum);
  } else {
    set_GeECCR_CCU2CEMSPN3924TimeoutBCS_enum(rtb_Merge15_d);
  }

  if (CbECCR_CCU2CEMSPN3925TimeoutBCLOvrSwt_flg) {
    set_GeECCR_CCU2CEMSPN3925TimeoutBCL_enum
      (CeECCR_CCU2CEMSPN3925TimeoutBCLOvr_enum);
  } else {
    set_GeECCR_CCU2CEMSPN3925TimeoutBCL_enum(rtb_Merge16_k);
  }

  if (CbECCR_CCU2CEMSPN3926TimeoutBSTOvrSwt_flg) {
    set_GeECCR_CCU2CEMSPN3926TimeoutBST_enum
      (CeECCR_CCU2CEMSPN3926TimeoutBSTOvr_enum);
  } else {
    set_GeECCR_CCU2CEMSPN3926TimeoutBST_enum(rtb_Merge17_h);
  }

  if (CbECCR_CCU2CEMSPN3927TimeoutBSDOvrSwt_flg) {
    set_GeECCR_CCU2CEMSPN3927TimeoutBSD_enum
      (CeECCR_CCU2CEMSPN3927TimeoutBSDOvr_enum);
  } else {
    set_GeECCR_CCU2CEMSPN3927TimeoutBSD_enum(rtb_Merge18_f);
  }

  if (CbECCR_CCU2CSTSPN3521StopReasonAutoOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3521StopReasonAuto_enum
      (CeECCR_CCU2CSTSPN3521StopReasonAutoOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3521StopReasonAuto_enum(rtb_Merge_c);
  }

  if (CbECCR_CCU2CSTSPN3521StopReasonBMSStopOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3521StopReasonBMSStop_enum
      (CeECCR_CCU2CSTSPN3521StopReasonBMSStopOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3521StopReasonBMSStop_enum(rtb_Merge3_kt);
  }

  if (CbECCR_CCU2CSTSPN3521StopReasonFaultOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3521StopReasonFault_enum
      (CeECCR_CCU2CSTSPN3521StopReasonFaultOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3521StopReasonFault_enum(rtb_Merge2_mu);
  }

  if (CbECCR_CCU2CSTSPN3521StopReasonManualOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3521StopReasonManual_enum
      (CeECCR_CCU2CSTSPN3521StopReasonManualOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3521StopReasonManual_enum(rtb_Merge1_m);
  }

  if (CbECCR_CCU2CSTSPN3522StopFaultCHGCnntOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3522StopFaultCHGCnnt_enum
      (CeECCR_CCU2CSTSPN3522StopFaultCHGCnntOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3522StopFaultCHGCnnt_enum(rtb_Merge5_m);
  }

  if (CbECCR_CCU2CSTSPN3522StopFaultDeliverOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3522StopFaultDeliver_enum
      (CeECCR_CCU2CSTSPN3522StopFaultDeliverOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3522StopFaultDeliver_enum(rtb_Merge7_ef);
  }

  if (CbECCR_CCU2CSTSPN3522StopFaultEmerStopOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3522StopFaultEmerStop_enum
      (CeECCR_CCU2CSTSPN3522StopFaultEmerStopOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3522StopFaultEmerStop_enum(rtb_Merge8_fi);
  }

  if (CbECCR_CCU2CSTSPN3522StopFaultOtherOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3522StopFaultOther_enum
      (CeECCR_CCU2CSTSPN3522StopFaultOtherOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3522StopFaultOther_enum(rtb_Merge9_hw);
  }

  if (CbECCR_CCU2CSTSPN3522StopFaultTCHGOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3522StopFaultTCHG_enum
      (CeECCR_CCU2CSTSPN3522StopFaultTCHGOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3522StopFaultTCHG_enum(rtb_Merge4_e);
  }

  if (CbECCR_CCU2CSTSPN3522StopFaultTInterOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3522StopFaultTInter_enum
      (CeECCR_CCU2CSTSPN3522StopFaultTInterOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3522StopFaultTInter_enum(rtb_Merge6_l);
  }

  if (CbECCR_CCU2CSTSPN3523StopFaultMismatchOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3523StopFaultMismatch_enum
      (CeECCR_CCU2CSTSPN3523StopFaultMismatchOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3523StopFaultMismatch_enum(rtb_Merge10_j);
  }

  if (CbECCR_CCU2CSTSPN3523StopFaultUOvrSwt_flg) {
    set_GeECCR_CCU2CSTSPN3523StopFaultU_enum
      (CeECCR_CCU2CSTSPN3523StopFaultUOvr_enum);
  } else {
    set_GeECCR_CCU2CSTSPN3523StopFaultU_enum(rtb_Merge11_i);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_DTC_18AAFAF2h_200ms_at_outport_1' */
void ECCR_CCU_DTC_18AAFAF2h_200ms(void)
{
  uint8_T rtb_Merge_ao;
  uint8_T rtb_Merge1_e4;
  uint8_T rtb_Merge2_o;
  if (get_ECCR_CCU1DTC18AAFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_ao = get_GcCAN1_CCUDTCHighByte_numb();
    rtb_Merge1_e4 = get_GcCAN1_CCUDTCLowByte_numb();
    rtb_Merge2_o = get_GcCAN1_CCUDTCFailureTypeByte_numb();
  } else {
    rtb_Merge_ao = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_e4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_o = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1CCUDTCFailureTypeByteOvrSwt_flg) {
    set_GcECCR_CCU1CCUDTCFailureTypeByte_numb
      (CcECCR_CCU1CCUDTCFailureTypeByteOvr_numb);
  } else {
    set_GcECCR_CCU1CCUDTCFailureTypeByte_numb(rtb_Merge2_o);
  }

  if (CbECCR_CCU1CCUDTCHighByteOvrSwt_flg) {
    set_GcECCR_CCU1CCUDTCHighByte_numb(CcECCR_CCU1CCUDTCHighByteOvr_numb);
  } else {
    set_GcECCR_CCU1CCUDTCHighByte_numb(rtb_Merge_ao);
  }

  if (CbECCR_CCU1CCUDTCLowByteOvrSwt_flg) {
    set_GcECCR_CCU1CCUDTCLowByte_numb(CcECCR_CCU1CCUDTCLowByteOvr_numb);
  } else {
    set_GcECCR_CCU1CCUDTCLowByte_numb(rtb_Merge1_e4);
  }

  if (get_ECCR_CCU2DTC18AAFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_ao = get_GcCAN3_CCUDTCHighByte_numb();
    rtb_Merge1_e4 = get_GcCAN3_CCUDTCLowByte_numb();
    rtb_Merge2_o = get_GcCAN3_CCUDTCFailureTypeByte_numb();
  } else {
    rtb_Merge_ao = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_e4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_o = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2CCUDTCFailureTypeByteOvrSwt_flg) {
    set_GcECCR_CCU2CCUDTCFailureTypeByte_numb
      (CcECCR_CCU2CCUDTCFailureTypeByteOvr_numb);
  } else {
    set_GcECCR_CCU2CCUDTCFailureTypeByte_numb(rtb_Merge2_o);
  }

  if (CbECCR_CCU2CCUDTCHighByteOvrSwt_flg) {
    set_GcECCR_CCU2CCUDTCHighByte_numb(CcECCR_CCU2CCUDTCHighByteOvr_numb);
  } else {
    set_GcECCR_CCU2CCUDTCHighByte_numb(rtb_Merge_ao);
  }

  if (CbECCR_CCU2CCUDTCLowByteOvrSwt_flg) {
    set_GcECCR_CCU2CCUDTCLowByte_numb(CcECCR_CCU2CCUDTCLowByteOvr_numb);
  } else {
    set_GcECCR_CCU2CCUDTCLowByte_numb(rtb_Merge1_e4);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_HV_1802FAF2h_100ms_at_outport_1' */
void ECCR_CCU_HV_1802FAF2h_100ms(void)
{
  real32_T rtb_Merge_n;
  real32_T rtb_Merge1_g;
  real32_T rtb_Merge2_m;
  real32_T rtb_Merge3_m4;
  if (get_ECCR_CCU1HV1802FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_n = (real32_T)get_GcCAN1_CCUHVRelayOutVLTG_V() * 0.1F;
    rtb_Merge1_g = (real32_T)get_GcCAN1_CCUHVRelayintVLTG_V() * 0.1F;
    rtb_Merge2_m = (real32_T)get_GcCAN1_CCUHVFuseVLTG_V() * 0.1F;
    rtb_Merge3_m4 = (real32_T)get_GcCAN1_CCUShuntCurrent_A() * 0.1F - 400.0F;
  } else {
    rtb_Merge_n = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_g = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_m4 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1CCUHVFuseVLTGOvrSwt_flg) {
    set_GcECCR_CCU1CCUHVFuseVLTG_V(CcECCR_CCU1CCUHVFuseVLTGOvr_V);
  } else {
    set_GcECCR_CCU1CCUHVFuseVLTG_V(rtb_Merge2_m);
  }

  if (CbECCR_CCU1CCUHVRelayOutVLTGOvrSwt_flg) {
    set_GcECCR_CCU1CCUHVRelayOutVLTG_V(CcECCR_CCU1CCUHVRelayOutVLTGOvr_V);
  } else {
    set_GcECCR_CCU1CCUHVRelayOutVLTG_V(rtb_Merge_n);
  }

  if (CbECCR_CCU1CCUHVRelayintVLTGOvrSwt_flg) {
    set_GcECCR_CCU1CCUHVRelayintVLTG_V(CcECCR_CCU1CCUHVRelayintVLTGOvr_V);
  } else {
    set_GcECCR_CCU1CCUHVRelayintVLTG_V(rtb_Merge1_g);
  }

  if (CbECCR_CCU1CCUShuntCurrentOvrSwt_flg) {
    set_GcECCR_CCU1CCUShuntCurrent_A(CcECCR_CCU1CCUShuntCurrentOvr_A);
  } else {
    set_GcECCR_CCU1CCUShuntCurrent_A(rtb_Merge3_m4);
  }

  if (get_ECCR_CCU2HV1802FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_n = (real32_T)get_GcCAN3_CCUHVRelayOutVLTG_V() * 0.1F;
    rtb_Merge1_g = (real32_T)get_GcCAN3_CCUHVRelayintVLTG_V() * 0.1F;
    rtb_Merge2_m = (real32_T)get_GcCAN3_CCUHVFuseVLTG_V() * 0.1F;
    rtb_Merge3_m4 = (real32_T)get_GcCAN3_CCUShuntCurrent_A() * 0.1F - 400.0F;
  } else {
    rtb_Merge_n = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_g = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_m4 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2CCUHVFuseVLTGOvrSwt_flg) {
    set_GcECCR_CCU2CCUHVFuseVLTG_V(CcECCR_CCU2CCUHVFuseVLTGOvr_V);
  } else {
    set_GcECCR_CCU2CCUHVFuseVLTG_V(rtb_Merge2_m);
  }

  if (CbECCR_CCU2CCUHVRelayOutVLTGOvrSwt_flg) {
    set_GcECCR_CCU2CCUHVRelayOutVLTG_V(CcECCR_CCU2CCUHVRelayOutVLTGOvr_V);
  } else {
    set_GcECCR_CCU2CCUHVRelayOutVLTG_V(rtb_Merge_n);
  }

  if (CbECCR_CCU2CCUHVRelayintVLTGOvrSwt_flg) {
    set_GcECCR_CCU2CCUHVRelayintVLTG_V(CcECCR_CCU2CCUHVRelayintVLTGOvr_V);
  } else {
    set_GcECCR_CCU2CCUHVRelayintVLTG_V(rtb_Merge1_g);
  }

  if (CbECCR_CCU2CCUShuntCurrentOvrSwt_flg) {
    set_GcECCR_CCU2CCUShuntCurrent_A(CcECCR_CCU2CCUShuntCurrentOvr_A);
  } else {
    set_GcECCR_CCU2CCUShuntCurrent_A(rtb_Merge3_m4);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_HV_1820FAF2h_100ms_at_outport_1' */
void ECCR_CCU_HV_1820FAF2h_100ms(void)
{
  real32_T rtb_Merge_mp;
  real32_T rtb_Merge1_ok;
  uint16_T rtb_Merge2_li;
  uint16_T rtb_Merge3_bv;
  if (get_ECCR_CCU1ISO1820FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_mp = (real32_T)get_GcCAN1_CCUISOPosVolt_V() * 0.1F;
    rtb_Merge1_ok = (real32_T)get_GcCAN1_CCUISONegVolt_V() * 0.1F;
    rtb_Merge2_li = get_GcCAN1_CCUISOPosRes_Kohm();
    rtb_Merge3_bv = get_GcCAN1_CCUISONegRes_Kohm();
  } else {
    rtb_Merge_mp = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_ok = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_li = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_bv = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1CCUISONegVoltOvrSwt_flg) {
    set_GcECCR_CCU1CCUISONegVolt_Kohm(CcECCR_CCU1CCUISONegVoltOvr_Kohm);
    set_GcECCR_CCU1CCUISONegVolt_V(CcECCR_CCU1CCUISONegVoltOvr_V);
  } else {
    set_GcECCR_CCU1CCUISONegVolt_Kohm(rtb_Merge3_bv);
    set_GcECCR_CCU1CCUISONegVolt_V(rtb_Merge1_ok);
  }

  if (CbECCR_CCU1CCUISOPosVoltOvrSwt_flg) {
    set_GcECCR_CCU1CCUISOPosVolt_Kohm(CcECCR_CCU1CCUISOPosVoltOvr_Kohm);
    set_GcECCR_CCU1CCUISOPosVolt_V(CcECCR_CCU1CCUISOPosVoltOvr_V);
  } else {
    set_GcECCR_CCU1CCUISOPosVolt_Kohm(rtb_Merge2_li);
    set_GcECCR_CCU1CCUISOPosVolt_V(rtb_Merge_mp);
  }

  if (get_ECCR_CCU2ISO1820FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_mp = (real32_T)get_GcCAN3_CCUISOPosVolt_V() * 0.1F;
    rtb_Merge1_ok = (real32_T)get_GcCAN3_CCUISONegVolt_V() * 0.1F;
    rtb_Merge2_li = get_GcCAN3_CCUISOPosRes_Kohm();
    rtb_Merge3_bv = get_GcCAN3_CCUISONegRes_Kohm();
  } else {
    rtb_Merge_mp = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_ok = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_li = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_bv = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2CCUISONegVoltOvrSwt_flg) {
    set_GcECCR_CCU2CCUISONegVolt_Kohm(CcECCR_CCU2CCUISONegVoltOvr_Kohm);
    set_GcECCR_CCU2CCUISONegVolt_V(CcECCR_CCU2CCUISONegVoltOvr_V);
  } else {
    set_GcECCR_CCU2CCUISONegVolt_Kohm(rtb_Merge3_bv);
    set_GcECCR_CCU2CCUISONegVolt_V(rtb_Merge1_ok);
  }

  if (CbECCR_CCU2CCUISOPosVoltOvrSwt_flg) {
    set_GcECCR_CCU2CCUISOPosVolt_Kohm(CcECCR_CCU2CCUISOPosVoltOvr_Kohm);
    set_GcECCR_CCU2CCUISOPosVolt_V(CcECCR_CCU2CCUISOPosVoltOvr_V);
  } else {
    set_GcECCR_CCU2CCUISOPosVolt_Kohm(rtb_Merge2_li);
    set_GcECCR_CCU2CCUISOPosVolt_V(rtb_Merge_mp);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_Sample_1803FAF2h_1000ms_at_outport_1' */
void ECCR_CCU_Sample_1803FAF2h_1000ms(void)
{
  uint16_T rtb_Merge_bd;
  int32_T rtb_Merge1_np;
  int32_T rtb_Merge2_b;
  if (get_ECCR_CCU1Sample1803FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_bd = get_GcCAN1_CCUISO_Kohm();
    rtb_Merge1_np = get_GcCAN1_CCUTEMP1_C() - 50;
    rtb_Merge2_b = get_GcCAN1_CCUTEMP2_C() - 50;
  } else {
    rtb_Merge_bd = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_np = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_b = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1CCUISOOvrSwt_flg) {
    set_GcECCR_CCU1CCUISO_Kohm(CcECCR_CCU1CCUISOOvr_Kohm);
  } else {
    set_GcECCR_CCU1CCUISO_Kohm(rtb_Merge_bd);
  }

  if (CbECCR_CCU1CCUTEMP1OvrSwt_flg) {
    set_GcECCR_CCU1CCUTEMP1_C(CcECCR_CCU1CCUTEMP1Ovr_C);
  } else {
    set_GcECCR_CCU1CCUTEMP1_C((real32_T)rtb_Merge1_np);
  }

  if (CbECCR_CCU1CCUTEMP2OvrSwt_flg) {
    set_GcECCR_CCU1CCUTEMP2_C(CcECCR_CCU1CCUTEMP2Ovr_C);
  } else {
    set_GcECCR_CCU1CCUTEMP2_C((real32_T)rtb_Merge2_b);
  }

  if (get_ECCR_CCU2Sample1803FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_bd = get_GcCAN3_CCUISO_Kohm();
    rtb_Merge1_np = get_GcCAN3_CCUTEMP1_C() - 50;
    rtb_Merge2_b = get_GcCAN3_CCUTEMP2_C() - 50;
  } else {
    rtb_Merge_bd = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_np = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_b = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2CCUISOOvrSwt_flg) {
    set_GcECCR_CCU2CCUISO_Kohm(CcECCR_CCU2CCUISOOvr_Kohm);
  } else {
    set_GcECCR_CCU2CCUISO_Kohm(rtb_Merge_bd);
  }

  if (CbECCR_CCU2CCUTEMP1OvrSwt_flg) {
    set_GcECCR_CCU2CCUTEMP1_C(CcECCR_CCU2CCUTEMP1Ovr_C);
  } else {
    set_GcECCR_CCU2CCUTEMP1_C((real32_T)rtb_Merge1_np);
  }

  if (CbECCR_CCU2CCUTEMP2OvrSwt_flg) {
    set_GcECCR_CCU2CCUTEMP2_C(CcECCR_CCU2CCUTEMP2Ovr_C);
  } else {
    set_GcECCR_CCU2CCUTEMP2_C((real32_T)rtb_Merge2_b);
  }
}

static int32_T safe_cast_to_Enum_ECCRCCU1State(int32_T input)
{
  int32_T output;

  /* Initialize output value to default value for Enum_ECCRCCU1State (Enum_ECCRCCU1State_NotReady) */
  output = 0;
  if ((input >= 0) && (input <= 7)) {
    /* Set output value to input value if it is a member of Enum_ECCRCCU1State */
    output = input;
  }

  return output;
}

static int32_T safe_cast_to_Enum_ECCRCCU2State(int32_T input)
{
  int32_T output;

  /* Initialize output value to default value for Enum_ECCRCCU2State (Enum_ECCRCCU2State_NotReady) */
  output = 0;
  if ((input >= 0) && (input <= 7)) {
    /* Set output value to input value if it is a member of Enum_ECCRCCU2State */
    output = input;
  }

  return output;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_SystStat_1801FAF2h_10ms_at_outport_1' */
void ECCR_CCU_SystStat_1801FAF2h_10ms(void)
{
  boolean_T rtb_LogicalOperator1_pr;
  if (CbECCR_CCU1CCUSTATEOvrSwt_flg) {
    set_GeECCR_CCU1CCUSTATE_enum(CeECCR_CCU1CCUSTATEOvr_enum);
  } else {
    set_GeECCR_CCU1CCUSTATE_enum(get_GeCAN1_CCUSTATE_enum());
  }

  if (CbECCR_CCU2CCUSTATEOvrSwt_flg) {
    set_GeECCR_CCU2CCUSTATE_enum(CeECCR_CCU2CCUSTATEOvr_enum);
  } else {
    set_GeECCR_CCU2CCUSTATE_enum(get_GeCAN3_CCUSTATE_enum());
  }

  rtb_LogicalOperator1_pr = ((safe_cast_to_Enum_ECCRCCU1State
    (get_GeCAN1_CCUSTATE_enum()) == (int32_T)Enum_ECCRCCU1State_ISOdetect) ||
    (safe_cast_to_Enum_ECCRCCU1State(get_GeCAN1_CCUSTATE_enum()) == (int32_T)
     Enum_ECCRCCU1State_PreChg) || (safe_cast_to_Enum_ECCRCCU1State
    (get_GeCAN1_CCUSTATE_enum()) == (int32_T)Enum_ECCRCCU1State_Chging) ||
    (safe_cast_to_Enum_ECCRCCU1State(get_GeCAN1_CCUSTATE_enum()) == (int32_T)
     Enum_ECCRCCU1State_Standby));
  if ((get_GcCAN1_BHMSPN2601UbatMaxPermit_V() > 0) && rtb_LogicalOperator1_pr) {
    ECCR_B.Merge = ((boolean_T)ASWTYPE_TRUE);
  }

  if ((safe_cast_to_Enum_ECCRCCU1State(get_GeCAN1_CCUSTATE_enum()) == (int32_T)
       Enum_ECCRCCU1State_NotReady) || (safe_cast_to_Enum_ECCRCCU1State
       (get_GeCAN1_CCUSTATE_enum()) == (int32_T)Enum_ECCRCCU1State_StopChg) ||
      (safe_cast_to_Enum_ECCRCCU1State(get_GeCAN1_CCUSTATE_enum()) == (int32_T)
       Enum_ECCRCCU1State_ChgFault) || (safe_cast_to_Enum_ECCRCCU1State
       (get_GeCAN1_CCUSTATE_enum()) == (int32_T)Enum_ECCRCCU1State_Powerdown)) {
    ECCR_B.Merge = ((boolean_T)ASWTYPE_FALSE);
    ECCR_B.Merge1 = ((boolean_T)ASWTYPE_FALSE);
    ECCR_B.Merge2 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (safe_cast_to_Enum_ECCRCCU1State(get_GeCAN1_CCUSTATE_enum()) == (int32_T)
      Enum_ECCRCCU1State_StopChg) {
    ECCR_B.Merge6 = ((boolean_T)ASWTYPE_TRUE);
  }

  if (safe_cast_to_Enum_ECCRCCU1State(get_GeCAN1_CCUSTATE_enum()) != (int32_T)
      Enum_ECCRCCU1State_StopChg) {
    ECCR_B.Merge6 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (rtb_LogicalOperator1_pr && (get_GcCAN1_BCPSPN2822U_V() > 0)) {
    ECCR_B.Merge1 = ((boolean_T)ASWTYPE_TRUE);
  }

  if (rtb_LogicalOperator1_pr && (get_GcCAN1_BCLSPN3072UReq_V() > 0)) {
    ECCR_B.Merge2 = ((boolean_T)ASWTYPE_TRUE);
  }

  if (CbECCR_CCU1ChgBHMOvrSwt_flg) {
    set_GbECCR_CCU1ChgBHM_flg(CbECCR_CCU1ChgBHMOvr_flg);
  } else {
    set_GbECCR_CCU1ChgBHM_flg((uint8_T)ECCR_B.Merge);
  }

  if (CbECCR_CCU1ChgBCPOvrSwt_flg) {
    set_GbECCR_CCU1ChgBCP_flg(CbECCR_CCU1ChgBCPOvr_flg);
  } else {
    set_GbECCR_CCU1ChgBCP_flg((uint8_T)ECCR_B.Merge1);
  }

  if (CbECCR_CCU1ChgBCLOvrSwt_flg) {
    set_GbECCR_CCU1ChgBCL_flg(CbECCR_CCU1ChgBCLOvr_flg);
  } else {
    set_GbECCR_CCU1ChgBCL_flg((uint8_T)ECCR_B.Merge2);
  }

  if (CbECCR_CCU1ChgBSTOvrSwt_flg) {
    set_GbECCR_CCU1ChgBST_flg(CbECCR_CCU1ChgBSTOvr_flg);
  } else {
    set_GbECCR_CCU1ChgBST_flg((uint8_T)ECCR_B.Merge6);
  }

  rtb_LogicalOperator1_pr = ((safe_cast_to_Enum_ECCRCCU2State
    (get_GeCAN3_CCUSTATE_enum()) == (int32_T)Enum_ECCRCCU2State_ISOdetect) ||
    (safe_cast_to_Enum_ECCRCCU2State(get_GeCAN3_CCUSTATE_enum()) == (int32_T)
     Enum_ECCRCCU2State_PreChg) || (safe_cast_to_Enum_ECCRCCU2State
    (get_GeCAN3_CCUSTATE_enum()) == (int32_T)Enum_ECCRCCU2State_Chging) ||
    (safe_cast_to_Enum_ECCRCCU2State(get_GeCAN3_CCUSTATE_enum()) == (int32_T)
     Enum_ECCRCCU2State_Standby));
  if (rtb_LogicalOperator1_pr && (get_GcCAN3_BHMSPN2601UbatMaxPermit_V() > 0)) {
    ECCR_B.Merge3 = ((boolean_T)ASWTYPE_TRUE);
  }

  if ((safe_cast_to_Enum_ECCRCCU2State(get_GeCAN3_CCUSTATE_enum()) == (int32_T)
       Enum_ECCRCCU2State_NotReady) || (safe_cast_to_Enum_ECCRCCU2State
       (get_GeCAN3_CCUSTATE_enum()) == (int32_T)Enum_ECCRCCU2State_StopChg) ||
      (safe_cast_to_Enum_ECCRCCU2State(get_GeCAN3_CCUSTATE_enum()) == (int32_T)
       Enum_ECCRCCU2State_ChgFault) || (safe_cast_to_Enum_ECCRCCU2State
       (get_GeCAN3_CCUSTATE_enum()) == (int32_T)Enum_ECCRCCU2State_Powerdown)) {
    ECCR_B.Merge3 = ((boolean_T)ASWTYPE_FALSE);
    ECCR_B.Merge4 = ((boolean_T)ASWTYPE_FALSE);
    ECCR_B.Merge5 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (rtb_LogicalOperator1_pr && (get_GcCAN3_BCPSPN2822U_V() > 0)) {
    ECCR_B.Merge4 = ((boolean_T)ASWTYPE_TRUE);
  }

  if (rtb_LogicalOperator1_pr && (get_GcCAN3_BCLSPN3072UReq_V() > 0)) {
    ECCR_B.Merge5 = ((boolean_T)ASWTYPE_TRUE);
  }

  if (safe_cast_to_Enum_ECCRCCU2State(get_GeCAN3_CCUSTATE_enum()) == (int32_T)
      Enum_ECCRCCU2State_StopChg) {
    ECCR_B.Merge7 = ((boolean_T)ASWTYPE_TRUE);
  }

  if (safe_cast_to_Enum_ECCRCCU2State(get_GeCAN3_CCUSTATE_enum()) != (int32_T)
      Enum_ECCRCCU2State_StopChg) {
    ECCR_B.Merge7 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2ChgBHMOvrSwt_flg) {
    set_GbECCR_CCU2ChgBHM_flg(CbECCR_CCU2ChgBHMOvr_flg);
  } else {
    set_GbECCR_CCU2ChgBHM_flg((uint8_T)ECCR_B.Merge3);
  }

  if (CbECCR_CCU2ChgBCPOvrSwt_flg) {
    set_GbECCR_CCU2ChgBCP_flg(CbECCR_CCU2ChgBCPOvr_flg);
  } else {
    set_GbECCR_CCU2ChgBCP_flg((uint8_T)ECCR_B.Merge4);
  }

  if (CbECCR_CCU2ChgBCLOvrSwt_flg) {
    set_GbECCR_CCU2ChgBCL_flg(CbECCR_CCU2ChgBCLOvr_flg);
  } else {
    set_GbECCR_CCU2ChgBCL_flg((uint8_T)ECCR_B.Merge5);
  }

  if (CbECCR_CCU2ChgBSTOvrSwt_flg) {
    set_GbECCR_CCU2ChgBST_flg(CbECCR_CCU2ChgBSTOvr_flg);
  } else {
    set_GbECCR_CCU2ChgBST_flg((uint8_T)ECCR_B.Merge7);
  }

  if (CbECCR_CCU1CCUSysStatAliveCounterOvrSwt_flg) {
    set_GcECCR_CCU1CCUSysStatAliveCounter_numb
      (CcECCR_CCU1CCUSysStatAliveCounterOvr_numb);
  } else {
    set_GcECCR_CCU1CCUSysStatAliveCounter_numb
      (get_GcCAN1_CCUSysStatAliveCounter_numb());
  }

  if (CbECCR_CCU1CCUPyroswitchCMDOvrSwt_flg) {
    set_GeECCR_CCU1CCUPyroswitchCMD_enum(CeECCR_CCU1CCUPyroswitchCMDOvr_enum);
  } else {
    set_GeECCR_CCU1CCUPyroswitchCMD_enum(get_GeCAN1_CCUPyroswitchCMD_enum());
  }

  if (CbECCR_CCU1CCUGUNpositionOvrSwt_flg) {
    set_GeECCR_CCU1CCUGUNposition_enum(CeECCR_CCU1CCUGUNpositionOvr_enum);
  } else {
    set_GeECCR_CCU1CCUGUNposition_enum(get_GeCAN1_CCUGUNposition_enum());
  }

  if (CbECCR_CCU1FUSE1STATEOvrSwt_flg) {
    set_GeECCR_CCU1FUSE1STATE_enum(CeECCR_CCU1FUSE1STATEOvr_enum);
  } else {
    set_GeECCR_CCU1FUSE1STATE_enum(get_GeCAN1_CCUFUSE1STATE_enum());
  }

  if (CbECCR_CCU1CCUISOSTATEOvrSwt_flg) {
    set_GeECCR_CCU1CCUISOSTATE_enum(CeECCR_CCU1CCUISOSTATEOvr_enum);
  } else {
    set_GeECCR_CCU1CCUISOSTATE_enum(get_GeCAN1_CCUISOSTATE_enum());
  }

  if (CbECCR_CCU1CCUGUNTEMP2STATEOvrSwt_flg) {
    set_GcECCR_CCU1CCUGUNTEMP2STATE_enum(CcECCR_CCU1CCUGUNTEMP2STATEOvr_enum);
  } else {
    set_GcECCR_CCU1CCUGUNTEMP2STATE_enum(get_GcCAN1_CCUGUNTEMP2STATE_enum());
  }

  if (CbECCR_CCU1CCUGUNTEMP1STATEOvrSwt_flg) {
    set_GcECCR_CCU1CCUGUNTEMP1STATE_enum(CcECCR_CCU1CCUGUNTEMP1STATEOvr_enum);
  } else {
    set_GcECCR_CCU1CCUGUNTEMP1STATE_enum(get_GcCAN1_CCUGUNTEMP1STATE_enum());
  }

  if (CbECCR_CCU1CCUCC1STATEOvrSwt_flg) {
    set_GeECCR_CCU1CCUCC1STATE_enum(CeECCR_CCU1CCUCC1STATEOvr_enum);
  } else {
    set_GeECCR_CCU1CCUCC1STATE_enum(get_GeCAN1_CCUCC1STATE_enum());
  }

  if (CbECCR_CCU1CCUK1K3STATEOvrSwt_flg) {
    set_GeECCR_CCU1CCUK1K3STATE_enum(CeECCR_CCU1CCUK1K3STATEOvr_enum);
  } else {
    set_GeECCR_CCU1CCUK1K3STATE_enum(get_GeCAN1_CCUK1K3STATE_enum());
  }

  if (CbECCR_CCU1CCUK2K4STATEOvrSwt_flg) {
    set_GeECCR_CCU1CCUK2K4STATE_enum(CeECCR_CCU1CCUK2K4STATEOvr_enum);
  } else {
    set_GeECCR_CCU1CCUK2K4STATE_enum(get_GeCAN1_CCUK2K4STATE_enum());
  }

  if (CbECCR_CCU1ELOCKSTATEOvrSwt_flg) {
    set_GcECCR_CCU1ELOCKSTATE_enum(CcECCR_CCU1ELOCKSTATEOvr_enum);
  } else {
    set_GcECCR_CCU1ELOCKSTATE_enum(get_GcCAN1_CCUELOCKSTATE_enum());
  }

  if (CbECCR_CCU1CCUCARCONNECTSTATEOvrSwt_flg) {
    set_GeECCR_CCU1CCUCARCONNECTSTATE_enum(CeECCR_CCU1CCUCARCONNECTSTATEOvr_enum);
  } else {
    set_GeECCR_CCU1CCUCARCONNECTSTATE_enum(get_GeCAN1_CCUCARCONNECTSTATE_enum());
  }

  if (CbECCR_CCU1FaultSevtyStatOvrSwt_flg) {
    set_GeECCR_CCU1FaultSevtyStat_enum(CeECCR_CCU1FaultSevtyStatOvr_enum);
  } else {
    set_GeECCR_CCU1FaultSevtyStat_enum(get_GeCAN1_CCUFaultSevtyStat_enum());
  }

  if (CbECCR_CCU1CCU12VSTATEOvrSwt_flg) {
    set_GeECCR_CCU1CCU12VSTATE_enum(CeECCR_CCU1CCU12VSTATEOvr_enum);
  } else {
    set_GeECCR_CCU1CCU12VSTATE_enum(get_GeCAN1_CCU12VSTATE_enum());
  }

  if (CbECCR_CCU1CCU24VSTATEOvrSwt_flg) {
    set_GeECCR_CCU1CCU24VSTATE_enum(CeECCR_CCU1CCU24VSTATEOvr_enum);
  } else {
    set_GeECCR_CCU1CCU24VSTATE_enum(get_GeCAN1_CCU24VSTATE_enum());
  }

  if (CbECCR_CCU1CCUIndexOvrSwt_flg) {
    set_GeECCR_CCU1CCUIndex_enum(CeECCR_CCU1CCUIndexOvr_enum);
  } else {
    set_GeECCR_CCU1CCUIndex_enum(get_GeCAN1_CCUIndex_enum());
  }

  if (CbECCR_CCU1CCUISOCheckFinishOvrSwt_flg) {
    set_GbECCR_CCU1CCUISOCheckFinish_flg(CbECCR_CCU1CCUISOCheckFinishOvr_flg);
  } else {
    set_GbECCR_CCU1CCUISOCheckFinish_flg(get_GbCAN1_CCUISOCheckFinishflg_flg());
  }

  if (CbECCR_CCU1CCUSwVersionOvrSwt_flg) {
    set_GbECCR_CCU1CCUSwVersion_numb(CbECCR_CCU1CCUSwVersionOvr_numb);
  } else {
    set_GbECCR_CCU1CCUSwVersion_numb(get_GcCAN1_CCUSwVersion_numb());
  }

  if (CbECCR_CCU1CCUHwVersionOvrSwt_flg) {
    set_GbECCR_CCU1CCUHwVersion_numb(CbECCR_CCU1CCUHwVersionOvr_numb);
  } else {
    set_GbECCR_CCU1CCUHwVersion_numb(get_GcCAN1_CCUHwVersion_numb());
  }

  if (CbECCR_CCU1CCUSysStatCheckSumOvrSwt_flg) {
    set_GbECCR_CCU1CCUSysStatCheckSum_numb(CbECCR_CCU1CCUSysStatCheckSumOvr_numb);
  } else {
    set_GbECCR_CCU1CCUSysStatCheckSum_numb(get_GcCAN1_CCUSysStatCheckSum_numb());
  }

  if (CbECCR_CCU2CCUSysStatAliveCounterOvrSwt_flg) {
    set_GcECCR_CCU2CCUSysStatAliveCounter_numb
      (CcECCR_CCU2CCUSysStatAliveCounterOvr_numb);
  } else {
    set_GcECCR_CCU2CCUSysStatAliveCounter_numb
      (get_GcCAN3_CCUSysStatAliveCounter_numb());
  }

  if (CbECCR_CCU2CCUPyroswitchCMDOvrSwt_flg) {
    set_GeECCR_CCU2CCUPyroswitchCMD_enum(CeECCR_CCU2CCUPyroswitchCMDOvr_enum);
  } else {
    set_GeECCR_CCU2CCUPyroswitchCMD_enum(get_GeCAN3_CCUPyroswitchCMD_enum());
  }

  if (CbECCR_CCU2CCUGUNpositionOvrSwt_flg) {
    set_GeECCR_CCU2CCUGUNposition_enum(CeECCR_CCU2CCUGUNpositionOvr_enum);
  } else {
    set_GeECCR_CCU2CCUGUNposition_enum(get_GeCAN3_CCUGUNposition_enum());
  }

  if (CbECCR_CCU2FUSE1STATEOvrSwt_flg) {
    set_GeECCR_CCU2FUSE1STATE_enum(CeECCR_CCU2FUSE1STATEOvr_enum);
  } else {
    set_GeECCR_CCU2FUSE1STATE_enum(get_GeCAN3_CCUFUSE1STATE_enum());
  }

  if (CbECCR_CCU2CCUISOSTATEOvrSwt_flg) {
    set_GeECCR_CCU2CCUISOSTATE_enum(CeECCR_CCU2CCUISOSTATEOvr_enum);
  } else {
    set_GeECCR_CCU2CCUISOSTATE_enum(get_GeCAN3_CCUISOSTATE_enum());
  }

  if (CbECCR_CCU2CCUGUNTEMP2STATEOvrSwt_flg) {
    set_GcECCR_CCU2CCUGUNTEMP2STATE_enum(CcECCR_CCU2CCUGUNTEMP2STATEOvr_enum);
  } else {
    set_GcECCR_CCU2CCUGUNTEMP2STATE_enum(get_GcCAN3_CCUGUNTEMP2STATE_enum());
  }

  if (CbECCR_CCU2CCUGUNTEMP1STATEOvrSwt_flg) {
    set_GcECCR_CCU2CCUGUNTEMP1STATE_enum(CcECCR_CCU2CCUGUNTEMP1STATEOvr_enum);
  } else {
    set_GcECCR_CCU2CCUGUNTEMP1STATE_enum(get_GcCAN3_CCUGUNTEMP1STATE_enum());
  }

  if (CbECCR_CCU2CCUCC1STATEOvrSwt_flg) {
    set_GeECCR_CCU2CCUCC1STATE_enum(CeECCR_CCU2CCUCC1STATEOvr_enum);
  } else {
    set_GeECCR_CCU2CCUCC1STATE_enum(get_GeCAN3_CCUCC1STATE_enum());
  }

  if (CbECCR_CCU2CCUK1K3STATEOvrSwt_flg) {
    set_GeECCR_CCU2CCUK1K3STATE_enum(CeECCR_CCU2CCUK1K3STATEOvr_enum);
  } else {
    set_GeECCR_CCU2CCUK1K3STATE_enum(get_GeCAN3_CCUK1K3STATE_enum());
  }

  if (CbECCR_CCU2CCUK2K4STATEOvrSwt_flg) {
    set_GeECCR_CCU2CCUK2K4STATE_enum(CeECCR_CCU2CCUK2K4STATEOvr_enum);
  } else {
    set_GeECCR_CCU2CCUK2K4STATE_enum(get_GeCAN3_CCUK2K4STATE_enum());
  }

  if (CbECCR_CCU2ELOCKSTATEOvrSwt_flg) {
    set_GcECCR_CCU2ELOCKSTATE_enum(CcECCR_CCU2ELOCKSTATEOvr_enum);
  } else {
    set_GcECCR_CCU2ELOCKSTATE_enum(get_GcCAN3_CCUELOCKSTATE_enum());
  }

  if (CbECCR_CCU2CCUCARCONNECTSTATEOvrSwt_flg) {
    set_GeECCR_CCU2CCUCARCONNECTSTATE_enum(CeECCR_CCU2CCUCARCONNECTSTATEOvr_enum);
  } else {
    set_GeECCR_CCU2CCUCARCONNECTSTATE_enum(get_GeCAN3_CCUCARCONNECTSTATE_enum());
  }

  if (CbECCR_CCU2FaultSevtyStatOvrSwt_flg) {
    set_GeECCR_CCU2FaultSevtyStat_enum(CeECCR_CCU2FaultSevtyStatOvr_enum);
  } else {
    set_GeECCR_CCU2FaultSevtyStat_enum(get_GeCAN3_CCUFaultSevtyStat_enum());
  }

  if (CbECCR_CCU2CCU22VSTATEOvrSwt_flg) {
    set_GeECCR_CCU2CCU22VSTATE_enum(CeECCR_CCU2CCU22VSTATEOvr_enum);
  } else {
    set_GeECCR_CCU2CCU22VSTATE_enum(get_GeCAN3_CCU22VSTATE_enum());
  }

  if (CbECCR_CCU2CCU24VSTATEOvrSwt_flg) {
    set_GeECCR_CCU2CCU24VSTATE_enum(CeECCR_CCU2CCU24VSTATEOvr_enum);
  } else {
    set_GeECCR_CCU2CCU24VSTATE_enum(get_GeCAN3_CCU24VSTATE_enum());
  }

  if (CbECCR_CCU2CCUIndexOvrSwt_flg) {
    set_GeECCR_CCU2CCUIndex_enum(CeECCR_CCU2CCUIndexOvr_enum);
  } else {
    set_GeECCR_CCU2CCUIndex_enum(get_GeCAN3_CCUIndex_enum());
  }

  if (CbECCR_CCU2CCUISOCheckFinishOvrSwt_flg) {
    set_GbECCR_CCU2CCUISOCheckFinish_flg(CbECCR_CCU2CCUISOCheckFinishOvr_flg);
  } else {
    set_GbECCR_CCU2CCUISOCheckFinish_flg(get_GbCAN3_CCUISOCheckFinishflg_flg());
  }

  if (CbECCR_CCU2CCUSwVersionOvrSwt_flg) {
    set_GbECCR_CCU2CCUSwVersion_numb(CbECCR_CCU2CCUSwVersionOvr_numb);
  } else {
    set_GbECCR_CCU2CCUSwVersion_numb(get_GbCAN3_CCUSwVersion_numb());
  }

  if (CbECCR_CCU2CCUHwVersionOvrSwt_flg) {
    set_GbECCR_CCU2CCUHwVersion_numb(CbECCR_CCU2CCUHwVersionOvr_numb);
  } else {
    set_GbECCR_CCU2CCUHwVersion_numb(get_GbCAN3_CCUHwVersion_numb());
  }

  if (CbECCR_CCU2CCUSysStatCheckSumOvrSwt_flg) {
    set_GbECCR_CCU2CCUSysStatCheckSum_numb(CbECCR_CCU2CCUSysStatCheckSumOvr_numb);
  } else {
    set_GbECCR_CCU2CCUSysStatCheckSum_numb(get_GbCAN3_CCUSysStatCheckSum_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VIN_1816FAF2h_250ms_at_outport_1' */
void ECCR_CCU_VIN_1816FAF2h_250ms(void)
{
  uint8_T rtb_Merge_i;
  uint8_T rtb_Merge1_bo;
  uint8_T rtb_Merge2_hc;
  uint8_T rtb_Merge3_p4;
  uint8_T rtb_Merge4_l;
  uint8_T rtb_Merge5_h0;
  uint8_T rtb_Merge6_kn;
  uint8_T rtb_Merge7_k;
  if (get_ECCR_CCU1VIN1816FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_i = get_GcCAN1_VINNumIndex_numb();
    rtb_Merge1_bo = get_GcCAN1_VINNum1_numb();
    rtb_Merge2_hc = get_GcCAN1_VINNum2_numb();
    rtb_Merge3_p4 = get_GcCAN1_VINNum3_numb();
    rtb_Merge4_l = get_GcCAN1_VINNum4_numb();
    rtb_Merge5_h0 = get_GcCAN1_VINNum5_numb();
    rtb_Merge6_kn = get_GcCAN1_VINNum6_numb();
    rtb_Merge7_k = get_GcCAN1_VINNum7_numb();
  } else {
    rtb_Merge_i = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_bo = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_hc = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_p4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4_l = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_h0 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge6_kn = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge7_k = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1VINNum1OvrSwt_flg) {
    set_GcECCR_CCU1VINNum1_numb(CcECCR_CCU1VINNum1Ovr_numb);
  } else {
    set_GcECCR_CCU1VINNum1_numb(rtb_Merge1_bo);
  }

  if (CbECCR_CCU1VINNum2OvrSwt_flg) {
    set_GcECCR_CCU1VINNum2_numb(CcECCR_CCU1VINNum2Ovr_numb);
  } else {
    set_GcECCR_CCU1VINNum2_numb(rtb_Merge2_hc);
  }

  if (CbECCR_CCU1VINNum3OvrSwt_flg) {
    set_GcECCR_CCU1VINNum3_numb(CcECCR_CCU1VINNum3Ovr_numb);
  } else {
    set_GcECCR_CCU1VINNum3_numb(rtb_Merge3_p4);
  }

  if (CbECCR_CCU1VINNum4OvrSwt_flg) {
    set_GcECCR_CCU1VINNum4_numb(CcECCR_CCU1VINNum4Ovr_numb);
  } else {
    set_GcECCR_CCU1VINNum4_numb(rtb_Merge4_l);
  }

  if (CbECCR_CCU1VINNum5OvrSwt_flg) {
    set_GcECCR_CCU1VINNum5_numb(CcECCR_CCU1VINNum5Ovr_numb);
  } else {
    set_GcECCR_CCU1VINNum5_numb(rtb_Merge5_h0);
  }

  if (CbECCR_CCU1VINNum6OvrSwt_flg) {
    set_GcECCR_CCU1VINNum6_numb(CcECCR_CCU1VINNum6Ovr_numb);
  } else {
    set_GcECCR_CCU1VINNum6_numb(rtb_Merge6_kn);
  }

  if (CbECCR_CCU1VINNum7OvrSwt_flg) {
    set_GcECCR_CCU1VINNum7_numb(CcECCR_CCU1VINNum7Ovr_numb);
  } else {
    set_GcECCR_CCU1VINNum7_numb(rtb_Merge7_k);
  }

  if (CbECCR_CCU1VINNumIndexOvrSwt_flg) {
    set_GcECCR_CCU1VINNumIndex_numb(CcECCR_CCU1VINNumIndexOvr_numb);
  } else {
    set_GcECCR_CCU1VINNumIndex_numb(rtb_Merge_i);
  }

  if (get_ECCR_CCU2VIN1816FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_i = get_GcCAN3_VINNumIndex_numb();
    rtb_Merge1_bo = get_GcCAN3_VINNum1_numb();
    rtb_Merge2_hc = get_GcCAN3_VINNum2_numb();
    rtb_Merge3_p4 = get_GcCAN3_VINNum3_numb();
    rtb_Merge4_l = get_GcCAN3_VINNum4_numb();
    rtb_Merge5_h0 = get_GcCAN3_VINNum5_numb();
    rtb_Merge6_kn = get_GcCAN3_VINNum6_numb();
    rtb_Merge7_k = get_GcCAN3_VINNum7_numb();
  } else {
    rtb_Merge_i = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_bo = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_hc = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_p4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4_l = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_h0 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge6_kn = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge7_k = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2VINNum1OvrSwt_flg) {
    set_GcECCR_CCU2VINNum1_numb(CcECCR_CCU2VINNum1Ovr_numb);
  } else {
    set_GcECCR_CCU2VINNum1_numb(rtb_Merge1_bo);
  }

  if (CbECCR_CCU2VINNum2OvrSwt_flg) {
    set_GcECCR_CCU2VINNum2_numb(CcECCR_CCU2VINNum2Ovr_numb);
  } else {
    set_GcECCR_CCU2VINNum2_numb(rtb_Merge2_hc);
  }

  if (CbECCR_CCU2VINNum3OvrSwt_flg) {
    set_GcECCR_CCU2VINNum3_numb(CcECCR_CCU2VINNum3Ovr_numb);
  } else {
    set_GcECCR_CCU2VINNum3_numb(rtb_Merge3_p4);
  }

  if (CbECCR_CCU2VINNum4OvrSwt_flg) {
    set_GcECCR_CCU2VINNum4_numb(CcECCR_CCU2VINNum4Ovr_numb);
  } else {
    set_GcECCR_CCU2VINNum4_numb(rtb_Merge4_l);
  }

  if (CbECCR_CCU2VINNum5OvrSwt_flg) {
    set_GcECCR_CCU2VINNum5_numb(CcECCR_CCU2VINNum5Ovr_numb);
  } else {
    set_GcECCR_CCU2VINNum5_numb(rtb_Merge5_h0);
  }

  if (CbECCR_CCU2VINNum6OvrSwt_flg) {
    set_GcECCR_CCU2VINNum6_numb(CcECCR_CCU2VINNum6Ovr_numb);
  } else {
    set_GcECCR_CCU2VINNum6_numb(rtb_Merge6_kn);
  }

  if (CbECCR_CCU2VINNum7OvrSwt_flg) {
    set_GcECCR_CCU2VINNum7_numb(CcECCR_CCU2VINNum7Ovr_numb);
  } else {
    set_GcECCR_CCU2VINNum7_numb(rtb_Merge7_k);
  }

  if (CbECCR_CCU2VINNumIndexOvrSwt_flg) {
    set_GcECCR_CCU2VINNumIndex_numb(CcECCR_CCU2VINNumIndexOvr_numb);
  } else {
    set_GcECCR_CCU2VINNumIndex_numb(rtb_Merge_i);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBCL_1817FAF2h_50ms_at_outport_1' */
void ECCR_CCU_VechBCL_1817FAF2h_50ms(void)
{
  real32_T rtb_Merge_p;
  real32_T rtb_Merge1_h;
  uint8_T rtb_Merge2_i;
  if (get_ECCR_CCU1BCL1817FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_p = (real32_T)get_GcCAN1_BCLSPN3072UReq_V() * 0.1F;
    rtb_Merge1_h = (real32_T)fabs((real32_T)get_GcCAN1_BCLSPN3073IReq_A() * 0.1F
      - 400.0F);
    rtb_Merge2_i = get_GcCAN1_BCLSPN3074ChgMode_enum();
  } else {
    rtb_Merge_p = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_h = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_i = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BCLSPN3072UReqOvrSwt_flg) {
    set_GcECCR_CCU1BCLSPN3072UReq_V(CcECCR_CCU1BCLSPN3072UReqOvr_V);
  } else {
    set_GcECCR_CCU1BCLSPN3072UReq_V(rtb_Merge_p);
  }

  if (CbECCR_CCU1BCLSPN3073IReqOvrSwt_flg) {
    set_GcECCR_CCU1BCLSPN3073IReq_A(CcECCR_CCU1BCLSPN3073IReqOvr_A);
  } else {
    set_GcECCR_CCU1BCLSPN3073IReq_A(rtb_Merge1_h);
  }

  if (CbECCR_CCU1BCLSPN3074ChgModeOvrSwt_flg) {
    set_GcECCR_CCU1BCLSPN3074ChgMode_enum(CcECCR_CCU1BCLSPN3074ChgModeOvr_enum);
  } else {
    set_GcECCR_CCU1BCLSPN3074ChgMode_enum(rtb_Merge2_i);
  }

  if (get_ECCR_CCU2BCL1817FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_p = (real32_T)get_GcCAN3_BCLSPN3072UReq_V() * 0.1F;
    rtb_Merge1_h = (real32_T)fabs((real32_T)get_GcCAN3_BCLSPN3073IReq_A() * 0.1F
      - 400.0F);
    rtb_Merge2_i = get_GcCAN3_BCLSPN3074ChgMode_enum();
  } else {
    rtb_Merge_p = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_h = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_i = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BCLSPN3072UReqOvrSwt_flg) {
    set_GcECCR_CCU2BCLSPN3072UReq_V(CcECCR_CCU2BCLSPN3072UReqOvr_V);
  } else {
    set_GcECCR_CCU2BCLSPN3072UReq_V(rtb_Merge_p);
  }

  if (CbECCR_CCU2BCLSPN3073IReqOvrSwt_flg) {
    set_GcECCR_CCU2BCLSPN3073IReq_A(CcECCR_CCU2BCLSPN3073IReqOvr_A);
  } else {
    set_GcECCR_CCU2BCLSPN3073IReq_A(rtb_Merge1_h);
  }

  if (CbECCR_CCU2BCLSPN3074ChgModeOvrSwt_flg) {
    set_GcECCR_CCU2BCLSPN3074ChgMode_enum(CcECCR_CCU2BCLSPN3074ChgModeOvr_enum);
  } else {
    set_GcECCR_CCU2BCLSPN3074ChgMode_enum(rtb_Merge2_i);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBCP1_1812FAF2h_500ms_at_outport_1' */
void ECCR_CCU_VechBCP1_1812FAF2h_500ms(void)
{
  uint16_T rtb_Merge_c4;
  real32_T rtb_Merge9_op;
  real32_T rtb_Merge1_j;
  real32_T rtb_Merge3_ps;
  real32_T rtb_Merge2_g;
  if (get_ECCR_CCU1BCP1812FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_c4 = get_GcCAN1_BCPSPN2816UcellMaxPermit_V();
    rtb_Merge9_op = (real32_T)fabs((real32_T)(((real32_T)
      get_GcCAN1_BCPSPN2817IMaxPermit_A() * 0.1F - 400.0F) * ((real32_T)
      get_GcCAN1_BCPSPN2819UMaxPermit_V() * 0.1F) * 0.001));
    rtb_Merge1_j = (real32_T)get_GcCAN1_BCPSPN2817IMaxPermit_A() * 0.1F - 400.0F;
    rtb_Merge3_ps = (real32_T)get_GcCAN1_BCPSPN2819UMaxPermit_V() * 0.1F;
    rtb_Merge2_g = (real32_T)get_GcCAN1_BCPSPN2818kWhNom_Kwh() * 0.1F;
  } else {
    rtb_Merge_c4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_j = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_g = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_ps = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge9_op = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BCPSPN2816UcellMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU1BCPSPN2816UcellMaxPermit_V
      (CcECCR_CCU1BCPSPN2816UcellMaxPermitOvr_V);
  } else {
    set_GcECCR_CCU1BCPSPN2816UcellMaxPermit_V(rtb_Merge_c4);
  }

  if (CbECCR_CCU1BCPSPN2817IMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU1BCPSPN2817IMaxPermit_A(CcECCR_CCU1BCPSPN2817IMaxPermitOvr_A);
  } else {
    set_GcECCR_CCU1BCPSPN2817IMaxPermit_A(rtb_Merge1_j);
  }

  if (CbECCR_CCU1BCPSPN2818kWhNomOvrSwt_flg) {
    set_GcECCR_CCU1BCPSPN2818kWhNom_Kwh(CcECCR_CCU1BCPSPN2818kWhNomOvr_Kwh);
  } else {
    set_GcECCR_CCU1BCPSPN2818kWhNom_Kwh(rtb_Merge2_g);
  }

  if (CbECCR_CCU1BCPSPN2819UMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU1BCPSPN2819UMaxPermit_V(CcECCR_CCU1BCPSPN2819UMaxPermitOvr_V);
  } else {
    set_GcECCR_CCU1BCPSPN2819UMaxPermit_V(rtb_Merge3_ps);
  }

  if (CbECCR_GunAMaxPwrOvrSwt_flg) {
    set_GcECCR_GunAMaxPwr_kw(CcECCR_GunAMaxPwrOvr_kw);
  } else {
    set_GcECCR_GunAMaxPwr_kw(rtb_Merge9_op);
  }

  if (get_ECCR_CCU2BCP1812FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_c4 = get_GcCAN3_BCPSPN2816UcellMaxPermit_V();
    rtb_Merge9_op = (real32_T)fabs((real32_T)(((real32_T)
      get_GcCAN3_BCPSPN2817IMaxPermit_A() * 0.1F - 400.0F) * ((real32_T)
      get_GcCAN3_BCPSPN2819UMaxPermit_V() * 0.1F) * 0.001));
    rtb_Merge1_j = (real32_T)get_GcCAN3_BCPSPN2817IMaxPermit_A() * 0.1F - 400.0F;
    rtb_Merge3_ps = (real32_T)get_GcCAN3_BCPSPN2819UMaxPermit_V() * 0.1F;
    rtb_Merge2_g = (real32_T)get_GcCAN3_BCPSPN2818kWhNom_Kwh() * 0.1F;
  } else {
    rtb_Merge_c4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_j = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_g = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_ps = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge9_op = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BCPSPN2816UcellMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU2BCPSPN2816UcellMaxPermit_V
      (CcECCR_CCU2BCPSPN2816UcellMaxPermitOvr_V);
  } else {
    set_GcECCR_CCU2BCPSPN2816UcellMaxPermit_V(rtb_Merge_c4);
  }

  if (CbECCR_CCU2BCPSPN2817IMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU2BCPSPN2817IMaxPermit_A(CcECCR_CCU2BCPSPN2817IMaxPermitOvr_A);
  } else {
    set_GcECCR_CCU2BCPSPN2817IMaxPermit_A(rtb_Merge1_j);
  }

  if (CbECCR_CCU2BCPSPN2818kWhNomOvrSwt_flg) {
    set_GcECCR_CCU2BCPSPN2818kWhNom_Kwh(CcECCR_CCU2BCPSPN2818kWhNomOvr_Kwh);
  } else {
    set_GcECCR_CCU2BCPSPN2818kWhNom_Kwh(rtb_Merge2_g);
  }

  if (CbECCR_CCU2BCPSPN2819UMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU2BCPSPN2819UMaxPermit_V(CcECCR_CCU2BCPSPN2819UMaxPermitOvr_V);
  } else {
    set_GcECCR_CCU2BCPSPN2819UMaxPermit_V(rtb_Merge3_ps);
  }

  if (GbECCR_GunBMaxPwrOvrSwt_flg) {
    set_GcECCR_GunBMaxPwr_kw(GcECCR_GunBMaxPwrOvr_kw);
  } else {
    set_GcECCR_GunBMaxPwr_kw(rtb_Merge9_op);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBCP2_1813FAF2h_500ms_at_outport_1' */
void ECCR_CCU_VechBCP2_1813FAF2h_500ms(void)
{
  int32_T rtb_Merge_a4;
  real32_T rtb_Merge1_i;
  real32_T rtb_Merge2_f;
  if (get_ECCR_CCU1BCP1813FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_a4 = get_GcCAN1_BCPSPN2820TMaxPermit_C() - 50;
    rtb_Merge1_i = (real32_T)get_GcCAN1_BCPSPN2821SOC_Pct() * 0.1F;
    rtb_Merge2_f = (real32_T)get_GcCAN1_BCPSPN2822U_V() * 0.1F;
  } else {
    rtb_Merge_a4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_i = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_f = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BCPSPN2820TMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU1BCPSPN2820TMaxPermit_C(CcECCR_CCU1BCPSPN2820TMaxPermitOvr_C);
  } else {
    set_GcECCR_CCU1BCPSPN2820TMaxPermit_C((real32_T)rtb_Merge_a4);
  }

  if (CbECCR_CCU1BCPSPN2821SOCOvrSwt_flg) {
    set_GcECCR_CCU1BCPSPN2821SOC_Pct(CcECCR_CCU1BCPSPN2821SOCOvr_Pct);
  } else {
    set_GcECCR_CCU1BCPSPN2821SOC_Pct(rtb_Merge1_i);
  }

  if (CbECCR_CCU1BCPSPN2822UOvrSwt_flg) {
    set_GcECCR_CCU1BCPSPN2822U_V(CcECCR_CCU1BCPSPN2822UOvr_V);
  } else {
    set_GcECCR_CCU1BCPSPN2822U_V(rtb_Merge2_f);
  }

  if (get_ECCR_CCU2BCP1813FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge_a4 = get_GcCAN3_BCPSPN2820TMaxPermit_C() - 50;
    rtb_Merge1_i = (real32_T)get_GcCAN3_BCPSPN2821SOC_Pct() * 0.1F;
    rtb_Merge2_f = (real32_T)get_GcCAN3_BCPSPN2822U_V() * 0.1F;
  } else {
    rtb_Merge_a4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_i = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_f = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BCPSPN2820TMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU2BCPSPN2820TMaxPermit_C(CcECCR_CCU2BCPSPN2820TMaxPermitOvr_C);
  } else {
    set_GcECCR_CCU2BCPSPN2820TMaxPermit_C((real32_T)rtb_Merge_a4);
  }

  if (CbECCR_CCU2BCPSPN2821SOCOvrSwt_flg) {
    set_GcECCR_CCU2BCPSPN2821SOC_Pct(CcECCR_CCU2BCPSPN2821SOCOvr_Pct);
  } else {
    set_GcECCR_CCU2BCPSPN2821SOC_Pct(rtb_Merge1_i);
  }

  if (CbECCR_CCU2BCPSPN2822UOvrSwt_flg) {
    set_GcECCR_CCU2BCPSPN2822U_V(CcECCR_CCU2BCPSPN2822UOvr_V);
  } else {
    set_GcECCR_CCU2BCPSPN2822U_V(rtb_Merge2_f);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBCS_1818FAF2h_250ms_at_outport_1' */
void ECCR_CCU_VechBCS_1818FAF2h_250ms(void)
{
  real32_T rtb_Merge;
  real32_T rtb_Merge1_o;
  uint16_T rtb_Merge2_j;
  uint8_T rtb_Merge3_d;
  uint8_T rtb_Merge4_m;
  uint16_T rtb_Merge5_f;
  if (get_ECCR_CCU1BCS1818FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = (real32_T)get_GcCAN1_BCSSPN3075UMea_V() * 0.1F;
    rtb_Merge1_o = (real32_T)get_GcCAN1_BCSSPN3076IMea_A() * 0.1F - 400.0F;
    rtb_Merge2_j = get_GcCAN1_BCSSPN3077UcellMax_V();
    rtb_Merge3_d = get_GeCAN1_BCSSPN3077UcellMaxGrp_enum();
    rtb_Merge4_m = get_GcCAN1_BCSSPN3078SOC_Pct();
    rtb_Merge5_f = get_GcCAN1_BCSSPN3079TimeRemain_min();
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_o = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_j = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_f = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BCSSPN3075UMeaOvrSwt_flg) {
    set_GcECCR_CCU1BCSSPN3075UMea_V(CcECCR_CCU1BCSSPN3075UMeaOvr_V);
  } else {
    set_GcECCR_CCU1BCSSPN3075UMea_V(rtb_Merge);
  }

  if (CbECCR_CCU1BCSSPN3076IMeaOvrSwt_flg) {
    set_GcECCR_CCU1BCSSPN3076IMea_A(CcECCR_CCU1BCSSPN3076IMeaOvr_A);
  } else {
    set_GcECCR_CCU1BCSSPN3076IMea_A(rtb_Merge1_o);
  }

  if (CbECCR_CCU1BCSSPN3077UcellMaxOvrSwt_flg) {
    set_GcECCR_CCU1BCSSPN3077UcellMax_V(CcECCR_CCU1BCSSPN3077UcellMaxOvr_V);
  } else {
    set_GcECCR_CCU1BCSSPN3077UcellMax_V(rtb_Merge2_j);
  }

  if (CbECCR_CCU1BCSSPN3078SOCOvrSwt_flg) {
    set_GcECCR_CCU1BCSSPN3078SOC_Pct(CcECCR_CCU1BCSSPN3078SOCOvr_Pct);
  } else {
    set_GcECCR_CCU1BCSSPN3078SOC_Pct(rtb_Merge4_m);
  }

  if (CbECCR_CCU1BCSSPN3079TimeRemainOvrSwt_flg) {
    set_GcECCR_CCU1BCSSPN3079TimeRemain_min
      (CcECCR_CCU1BCSSPN3079TimeRemainOvr_min);
  } else {
    set_GcECCR_CCU1BCSSPN3079TimeRemain_min(rtb_Merge5_f);
  }

  if (CbECCR_CCU1BCSSPN3077UcellMaxGrpOvrSwt_flg) {
    set_GeECCR_CCU1BCSSPN3077UcellMaxGrp_enum
      (CeECCR_CCU1BCSSPN3077UcellMaxGrpOvr_enum);
  } else {
    set_GeECCR_CCU1BCSSPN3077UcellMaxGrp_enum(rtb_Merge3_d);
  }

  if (get_ECCR_CCU2BCS1818FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = (real32_T)get_GcCAN3_BCSSPN3075UMea_V() * 0.1F;
    rtb_Merge1_o = (real32_T)get_GcCAN3_BCSSPN3076IMea_A() * 0.1F - 400.0F;
    rtb_Merge2_j = get_GcCAN3_BCSSPN3077UcellMax_V();
    rtb_Merge3_d = get_GeCAN3_BCSSPN3077UcellMaxGrp_enum();
    rtb_Merge4_m = get_GcCAN3_BCSSPN3078SOC_Pct();
    rtb_Merge5_f = get_GcCAN3_BCSSPN3079TimeRemain_min();
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_o = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2_j = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4_m = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_f = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BCSSPN3075UMeaOvrSwt_flg) {
    set_GcECCR_CCU2BCSSPN3075UMea_V(CcECCR_CCU2BCSSPN3075UMeaOvr_V);
  } else {
    set_GcECCR_CCU2BCSSPN3075UMea_V(rtb_Merge);
  }

  if (CbECCR_CCU2BCSSPN3076IMeaOvrSwt_flg) {
    set_GcECCR_CCU2BCSSPN3076IMea_A(CcECCR_CCU2BCSSPN3076IMeaOvr_A);
  } else {
    set_GcECCR_CCU2BCSSPN3076IMea_A(rtb_Merge1_o);
  }

  if (CbECCR_CCU2BCSSPN3077UcellMaxOvrSwt_flg) {
    set_GcECCR_CCU2BCSSPN3077UcellMax_V(CcECCR_CCU2BCSSPN3077UcellMaxOvr_V);
  } else {
    set_GcECCR_CCU2BCSSPN3077UcellMax_V(rtb_Merge2_j);
  }

  if (CbECCR_CCU2BCSSPN3078SOCOvrSwt_flg) {
    set_GcECCR_CCU2BCSSPN3078SOC_Pct(CcECCR_CCU2BCSSPN3078SOCOvr_Pct);
  } else {
    set_GcECCR_CCU2BCSSPN3078SOC_Pct(rtb_Merge4_m);
  }

  if (CbECCR_CCU2BCSSPN3079TimeRemainOvrSwt_flg) {
    set_GcECCR_CCU2BCSSPN3079TimeRemain_min
      (CcECCR_CCU2BCSSPN3079TimeRemainOvr_min);
  } else {
    set_GcECCR_CCU2BCSSPN3079TimeRemain_min(rtb_Merge5_f);
  }

  if (CbECCR_CCU2BCSSPN3077UcellMaxGrpOvrSwt_flg) {
    set_GeECCR_CCU2BCSSPN3077UcellMaxGrp_enum
      (CeECCR_CCU2BCSSPN3077UcellMaxGrpOvr_enum);
  } else {
    set_GeECCR_CCU2BCSSPN3077UcellMaxGrp_enum(rtb_Merge3_d);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBHM_1811FAF2h_250ms_at_outport_1' */
void ECCR_CCU_VechBHM_1811FAF2h_250ms(void)
{
  uint32_T rtb_Merge;
  real32_T rtb_Merge1_p;
  if (get_ECCR_CCU1BHM1811FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GcCAN1_CHMSPN2600CommVer_numb();
    rtb_Merge1_p = (real32_T)get_GcCAN1_BHMSPN2601UbatMaxPermit_V() * 0.1F;
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_p = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BHMSPN2601UbatMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU1BHMSPN2601UbatMaxPermit_V
      (CcECCR_CCU1BHMSPN2601UbatMaxPermitOvr_V);
  } else {
    set_GcECCR_CCU1BHMSPN2601UbatMaxPermit_V(rtb_Merge1_p);
  }

  if (CbECCR_CCU1CHMSPN2600CommVerOvrSwt_flg) {
    set_GcECCR_CCU1CHMSPN2600CommVer_numb(CcECCR_CCU1CHMSPN2600CommVerOvr_numb);
  } else {
    set_GcECCR_CCU1CHMSPN2600CommVer_numb(rtb_Merge);
  }

  if (get_ECCR_CCU2BHM1811FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GcCAN3_CHMSPN2600CommVer_numb();
    rtb_Merge1_p = (real32_T)get_GcCAN3_BHMSPN2601UbatMaxPermit_V() * 0.1F;
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_p = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BHMSPN2601UbatMaxPermitOvrSwt_flg) {
    set_GcECCR_CCU2BHMSPN2601UbatMaxPermit_V
      (CcECCR_CCU2BHMSPN2601UbatMaxPermitOvr_V);
  } else {
    set_GcECCR_CCU2BHMSPN2601UbatMaxPermit_V(rtb_Merge1_p);
  }

  if (CbECCR_CCU2CHMSPN2600CommVerOvrSwt_flg) {
    set_GcECCR_CCU2CHMSPN2600CommVer_numb(CcECCR_CCU2CHMSPN2600CommVerOvr_numb);
  } else {
    set_GcECCR_CCU2CHMSPN2600CommVer_numb(rtb_Merge);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBRM1_1814FAF2h_250ms_at_outport_1' */
void ECCR_CCU_VechBRM1_1814FAF2h_250ms(void)
{
  uint8_T rtb_Merge;
  real32_T rtb_Merge1_d;
  real32_T rtb_Merge2;
  uint32_T rtb_Merge3_d5;
  if (get_ECCR_CCU1BRM1814FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GeCAN1_BRMSPN2566BatType_enum();
    rtb_Merge1_d = (real32_T)get_GcCAN1_BRMSPN2567CapNom_Ah() * 0.1F;
    rtb_Merge2 = (real32_T)get_GcCAN1_BRMSPN2568UNom_V() * 0.1F;
    rtb_Merge3_d5 = get_GcCAN1_BRMSPN2565CommVer_numb();
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_d5 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BRMSPN2565CommVerOvrSwt_flg) {
    set_GcECCR_CCU1BRMSPN2565CommVer_numb(CcECCR_CCU1BRMSPN2565CommVerOvr_numb);
  } else {
    set_GcECCR_CCU1BRMSPN2565CommVer_numb(rtb_Merge3_d5);
  }

  if (CbECCR_CCU1BRMSPN2567CapNomOvrSwt_flg) {
    set_GcECCR_CCU1BRMSPN2567CapNom_Ah(CcECCR_CCU1BRMSPN2567CapNomOvr_Ah);
  } else {
    set_GcECCR_CCU1BRMSPN2567CapNom_Ah(rtb_Merge1_d);
  }

  if (CbECCR_CCU1BRMSPN2568UNomOvrSwt_flg) {
    set_GcECCR_CCU1BRMSPN2568UNom_V(CcECCR_CCU1BRMSPN2568UNomOvr_V);
  } else {
    set_GcECCR_CCU1BRMSPN2568UNom_V(rtb_Merge2);
  }

  if (CbECCR_CCU1BRMSPN2566BatTypeOvrSwt_flg) {
    set_GeECCR_CCU1BRMSPN2566BatType_enum(CeECCR_CCU1BRMSPN2566BatTypeOvr_enum);
  } else {
    set_GeECCR_CCU1BRMSPN2566BatType_enum(rtb_Merge);
  }

  if (get_ECCR_CCU2BRM1814FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GeCAN3_BRMSPN2566BatType_enum();
    rtb_Merge1_d = (real32_T)get_GcCAN3_BRMSPN2567CapNom_Ah() * 0.1F;
    rtb_Merge2 = (real32_T)get_GcCAN3_BRMSPN2568UNom_V() * 0.1F;
    rtb_Merge3_d5 = get_GcCAN3_BRMSPN2565CommVer_numb();
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_d5 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BRMSPN2565CommVerOvrSwt_flg) {
    set_GcECCR_CCU2BRMSPN2565CommVer_numb(CcECCR_CCU2BRMSPN2565CommVerOvr_numb);
  } else {
    set_GcECCR_CCU2BRMSPN2565CommVer_numb(rtb_Merge3_d5);
  }

  if (CbECCR_CCU2BRMSPN2567CapNomOvrSwt_flg) {
    set_GcECCR_CCU2BRMSPN2567CapNom_Ah(CcECCR_CCU2BRMSPN2567CapNomOvr_Ah);
  } else {
    set_GcECCR_CCU2BRMSPN2567CapNom_Ah(rtb_Merge1_d);
  }

  if (CbECCR_CCU2BRMSPN2568UNomOvrSwt_flg) {
    set_GcECCR_CCU2BRMSPN2568UNom_V(CcECCR_CCU2BRMSPN2568UNomOvr_V);
  } else {
    set_GcECCR_CCU2BRMSPN2568UNom_V(rtb_Merge2);
  }

  if (CbECCR_CCU2BRMSPN2566BatTypeOvrSwt_flg) {
    set_GeECCR_CCU2BRMSPN2566BatType_enum(CeECCR_CCU2BRMSPN2566BatTypeOvr_enum);
  } else {
    set_GeECCR_CCU2BRMSPN2566BatType_enum(rtb_Merge);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBRM2_1815FAF2h_250ms_at_outport_1' */
void ECCR_CCU_VechBRM2_1815FAF2h_250ms(void)
{
  uint32_T rtb_Merge;
  uint32_T rtb_Merge1_k;
  if (get_ECCR_CCU1BRM1815FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GcCAN1_BRMSPN2569BatFactory_numb();
    rtb_Merge1_k = get_GcCAN1_BRMSPN2570PackSN_numb();
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_k = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BRMSPN2569BatFactoryOvrSwt_flg) {
    set_GcECCR_CCU1BRMSPN2569BatFactory_numb
      (CcECCR_CCU1BRMSPN2569BatFactoryOvr_numb);
  } else {
    set_GcECCR_CCU1BRMSPN2569BatFactory_numb(rtb_Merge);
  }

  if (CbECCR_CCU1BRMSPN2570PackSNOvrSwt_flg) {
    set_GcECCR_CCU1BRMSPN2570PackSN_numb(CcECCR_CCU1BRMSPN2570PackSNOvr_numb);
  } else {
    set_GcECCR_CCU1BRMSPN2570PackSN_numb(rtb_Merge1_k);
  }

  if (get_ECCR_CCU2BRM1815FAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GcCAN3_BRMSPN2569BatFactory_numb();
    rtb_Merge1_k = get_GcCAN3_BRMSPN2570PackSN_numb();
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_k = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BRMSPN2569BatFactoryOvrSwt_flg) {
    set_GcECCR_CCU2BRMSPN2569BatFactory_numb
      (CcECCR_CCU2BRMSPN2569BatFactoryOvr_numb);
  } else {
    set_GcECCR_CCU2BRMSPN2569BatFactory_numb(rtb_Merge);
  }

  if (CbECCR_CCU2BRMSPN2570PackSNOvrSwt_flg) {
    set_GcECCR_CCU2BRMSPN2570PackSN_numb(CcECCR_CCU2BRMSPN2570PackSNOvr_numb);
  } else {
    set_GcECCR_CCU2BRMSPN2570PackSN_numb(rtb_Merge1_k);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBSD_181BFAF2h_250ms_at_outport_1' */
void ECCR_CCU_VechBSD_181BFAF2h_250ms(void)
{
  uint8_T rtb_Merge;
  uint16_T rtb_Merge1_e;
  uint16_T rtb_Merge2;
  int32_T rtb_Merge3_k;
  int32_T rtb_Merge4;
  if (get_ECCR_CCU1BSD181BFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GcCAN1_BSDSPN3601SOCFinal_Pct();
    rtb_Merge1_e = get_GcCAN1_BSDSPN3602UcellMin_V();
    rtb_Merge2 = get_GcCAN1_BSDSPN3603UcellMax_V();
    rtb_Merge3_k = get_GcCAN1_BSDSPN3604TMin_C() - 50;
    rtb_Merge4 = get_GcCAN1_BSDSPN3605TMax_C() - 50;
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_e = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BSDSPN3601SOCFinalOvrSwt_flg) {
    set_GcECCR_CCU1BSDSPN3601SOCFinal_Pct(CcECCR_CCU1BSDSPN3601SOCFinalOvr_Pct);
  } else {
    set_GcECCR_CCU1BSDSPN3601SOCFinal_Pct(rtb_Merge);
  }

  if (CbECCR_CCU1BSDSPN3602UcellMinOvrSwt_flg) {
    set_GcECCR_CCU1BSDSPN3602UcellMin_V(CcECCR_CCU1BSDSPN3602UcellMinOvr_V);
  } else {
    set_GcECCR_CCU1BSDSPN3602UcellMin_V(rtb_Merge1_e);
  }

  if (CbECCR_CCU1BSDSPN3603UcellMaxOvrSwt_flg) {
    set_GcECCR_CCU1BSDSPN3603UcellMax_V(CcECCR_CCU1BSDSPN3603UcellMaxOvr_V);
  } else {
    set_GcECCR_CCU1BSDSPN3603UcellMax_V(rtb_Merge2);
  }

  if (CbECCR_CCU1BSDSPN3604TMinOvrSwt_flg) {
    set_GcECCR_CCU1BSDSPN3604TMin_C(CcECCR_CCU1BSDSPN3604TMinOvr_C);
  } else {
    set_GcECCR_CCU1BSDSPN3604TMin_C((real32_T)rtb_Merge3_k);
  }

  if (CbECCR_CCU1BSDSPN3605TMaxOvrSwt_flg) {
    set_GcECCR_CCU1BSDSPN3605TMax_C(CcECCR_CCU1BSDSPN3605TMaxOvr_C);
  } else {
    set_GcECCR_CCU1BSDSPN3605TMax_C((real32_T)rtb_Merge4);
  }

  if (get_ECCR_CCU2BSD181BFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GcCAN3_BSDSPN3601SOCFinal_Pct();
    rtb_Merge1_e = get_GcCAN3_BSDSPN3602UcellMin_V();
    rtb_Merge2 = get_GcCAN3_BSDSPN3603UcellMax_V();
    rtb_Merge3_k = get_GcCAN3_BSDSPN3604TMin_C() - 50;
    rtb_Merge4 = get_GcCAN3_BSDSPN3605TMax_C() - 50;
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1_e = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BSDSPN3601SOCFinalOvrSwt_flg) {
    set_GcECCR_CCU2BSDSPN3601SOCFinal_Pct(CcECCR_CCU2BSDSPN3601SOCFinalOvr_Pct);
  } else {
    set_GcECCR_CCU2BSDSPN3601SOCFinal_Pct(rtb_Merge);
  }

  if (CbECCR_CCU2BSDSPN3602UcellMinOvrSwt_flg) {
    set_GcECCR_CCU2BSDSPN3602UcellMin_V(CcECCR_CCU2BSDSPN3602UcellMinOvr_V);
  } else {
    set_GcECCR_CCU2BSDSPN3602UcellMin_V(rtb_Merge1_e);
  }

  if (CbECCR_CCU2BSDSPN3603UcellMaxOvrSwt_flg) {
    set_GcECCR_CCU2BSDSPN3603UcellMax_V(CcECCR_CCU2BSDSPN3603UcellMaxOvr_V);
  } else {
    set_GcECCR_CCU2BSDSPN3603UcellMax_V(rtb_Merge2);
  }

  if (CbECCR_CCU2BSDSPN3604TMinOvrSwt_flg) {
    set_GcECCR_CCU2BSDSPN3604TMin_C(CcECCR_CCU2BSDSPN3604TMinOvr_C);
  } else {
    set_GcECCR_CCU2BSDSPN3604TMin_C((real32_T)rtb_Merge3_k);
  }

  if (CbECCR_CCU2BSDSPN3605TMaxOvrSwt_flg) {
    set_GcECCR_CCU2BSDSPN3605TMax_C(CcECCR_CCU2BSDSPN3605TMaxOvr_C);
  } else {
    set_GcECCR_CCU2BSDSPN3605TMax_C((real32_T)rtb_Merge4);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCR_CCU_VechBSM_181AFAF2h_250ms_at_outport_1' */
void ECCR_CCU_VechBSM_181AFAF2h_250ms(void)
{
  uint8_T rtb_Merge;
  int32_T rtb_Merge1;
  uint8_T rtb_Merge2;
  int32_T rtb_Merge3;
  uint8_T rtb_Merge4;
  uint8_T rtb_Merge5_nj;
  uint8_T rtb_Merge6_d;
  uint8_T rtb_Merge7_n;
  uint8_T rtb_Merge8_j;
  uint8_T rtb_Merge9_i;
  uint8_T rtb_Merge10;
  uint8_T rtb_Merge11_o;
  if (get_ECCR_CCU1BSM181AFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GeCAN1_BSMSPN3085UcellMaxIndex_enum();
    rtb_Merge1 = get_GcCAN1_BSMSPN3086TMax_C() - 50;
    rtb_Merge2 = get_GeCAN1_BSMSPN3087TMaxIndex_enum();
    rtb_Merge3 = get_GcCAN1_BSMSPN3088TMin_C() - 50;
    rtb_Merge4 = get_GcCAN1_BSMSPN3089TMinIndex_enum();
    rtb_Merge5_nj = get_GeCAN1_BSMSPN3090UcellWarn_enum();
    rtb_Merge6_d = get_GeCAN1_BSMSPN3091SOCWarn_enum();
    rtb_Merge7_n = get_GeCAN1_BSMSPN3092IWarn_enum();
    rtb_Merge8_j = get_GeCAN1_BSMSPN3093TWarn_enum();
    rtb_Merge9_i = get_GeCAN1_BSMSPN3094IsoState_enum();
    rtb_Merge10 = get_GeCAN1_BSMSPN3095OutConnectorState_enum();
    rtb_Merge11_o = get_GeCAN1_BSMSPN3096ChgEnable_enum();
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_nj = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge6_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge7_n = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge8_j = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge9_i = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge10 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge11_o = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU1BSMSPN3086TMaxOvrSwt_flg) {
    set_GcECCR_CCU1BSMSPN3086TMax_C(CcECCR_CCU1BSMSPN3086TMaxOvr_C);
  } else {
    set_GcECCR_CCU1BSMSPN3086TMax_C((real32_T)rtb_Merge1);
  }

  if (CbECCR_CCU1BSMSPN3088TMinOvrSwt_flg) {
    set_GcECCR_CCU1BSMSPN3088TMin_C(CcECCR_CCU1BSMSPN3088TMinOvr_C);
  } else {
    set_GcECCR_CCU1BSMSPN3088TMin_C((real32_T)rtb_Merge3);
  }

  if (CbECCR_CCU1BSMSPN3089TMinIndexOvrSwt_flg) {
    set_GcECCR_CCU1BSMSPN3089TMinIndex_enum
      (CcECCR_CCU1BSMSPN3089TMinIndexOvr_enum);
  } else {
    set_GcECCR_CCU1BSMSPN3089TMinIndex_enum(rtb_Merge4);
  }

  if (CbECCR_CCU1BSMSPN3085UcellMaxIndexOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3085UcellMaxIndex_enum
      (CeECCR_CCU1BSMSPN3085UcellMaxIndexOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3085UcellMaxIndex_enum(rtb_Merge);
  }

  if (CbECCR_CCU1BSMSPN3087TMaxIndexOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3087TMaxIndex_enum
      (CeECCR_CCU1BSMSPN3087TMaxIndexOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3087TMaxIndex_enum(rtb_Merge2);
  }

  if (CbECCR_CCU1BSMSPN3090UcellWarnOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3090UcellWarn_enum
      (CeECCR_CCU1BSMSPN3090UcellWarnOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3090UcellWarn_enum(rtb_Merge5_nj);
  }

  if (CbECCR_CCU1BSMSPN3091SOCWarnOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3091SOCWarn_enum(CeECCR_CCU1BSMSPN3091SOCWarnOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3091SOCWarn_enum(rtb_Merge6_d);
  }

  if (CbECCR_CCU1BSMSPN3092IWarnOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3092IWarn_enum(CeECCR_CCU1BSMSPN3092IWarnOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3092IWarn_enum(rtb_Merge7_n);
  }

  if (CbECCR_CCU1BSMSPN3093TWarnOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3093TWarn_enum(CeECCR_CCU1BSMSPN3093TWarnOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3093TWarn_enum(rtb_Merge8_j);
  }

  if (CbECCR_CCU1BSMSPN3094IsoStateOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3094IsoState_enum(CeECCR_CCU1BSMSPN3094IsoStateOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3094IsoState_enum(rtb_Merge9_i);
  }

  if (CbECCR_CCU1BSMSPN3095OutConnectorStateOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3095OutConnectorState_enum
      (CeECCR_CCU1BSMSPN3095OutConnectorStateOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3095OutConnectorState_enum(rtb_Merge10);
  }

  if (CbECCR_CCU1BSMSPN3096ChgEnableOvrSwt_flg) {
    set_GeECCR_CCU1BSMSPN3096ChgEnable_enum
      (CeECCR_CCU1BSMSPN3096ChgEnableOvr_enum);
  } else {
    set_GeECCR_CCU1BSMSPN3096ChgEnable_enum(rtb_Merge11_o);
  }

  if (get_ECCR_CCU2BSM181AFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_Merge = get_GeCAN3_BSMSPN3085UcellMaxIndex_enum();
    rtb_Merge1 = get_GcCAN3_BSMSPN3086TMax_C() - 50;
    rtb_Merge2 = get_GeCAN3_BSMSPN3087TMaxIndex_enum();
    rtb_Merge3 = get_GcCAN3_BSMSPN3088TMin_C() - 50;
    rtb_Merge4 = get_GcCAN3_BSMSPN3089TMinIndex_enum();
    rtb_Merge5_nj = get_GeCAN3_BSMSPN3090UcellWarn_enum();
    rtb_Merge6_d = get_GeCAN3_BSMSPN3091SOCWarn_enum();
    rtb_Merge7_n = get_GeCAN3_BSMSPN3092IWarn_enum();
    rtb_Merge8_j = get_GeCAN3_BSMSPN3093TWarn_enum();
    rtb_Merge9_i = get_GeCAN3_BSMSPN3094IsoState_enum();
    rtb_Merge10 = get_GeCAN3_BSMSPN3095OutConnectorState_enum();
    rtb_Merge11_o = get_GeCAN3_BSMSPN3096ChgEnable_enum();
  } else {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge1 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge3 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge4 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge5_nj = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge6_d = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge7_n = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge8_j = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge9_i = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge10 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Merge11_o = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECCR_CCU2BSMSPN3086TMaxOvrSwt_flg) {
    set_GcECCR_CCU2BSMSPN3086TMax_C(CcECCR_CCU2BSMSPN3086TMaxOvr_C);
  } else {
    set_GcECCR_CCU2BSMSPN3086TMax_C((real32_T)rtb_Merge1);
  }

  if (CbECCR_CCU2BSMSPN3088TMinOvrSwt_flg) {
    set_GcECCR_CCU2BSMSPN3088TMin_C(CcECCR_CCU2BSMSPN3088TMinOvr_C);
  } else {
    set_GcECCR_CCU2BSMSPN3088TMin_C((real32_T)rtb_Merge3);
  }

  if (CbECCR_CCU2BSMSPN3089TMinIndexOvrSwt_flg) {
    set_GcECCR_CCU2BSMSPN3089TMinIndex_enum
      (CcECCR_CCU2BSMSPN3089TMinIndexOvr_enum);
  } else {
    set_GcECCR_CCU2BSMSPN3089TMinIndex_enum(rtb_Merge4);
  }

  if (CbECCR_CCU2BSMSPN3085UcellMaxIndexOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3085UcellMaxIndex_enum
      (CeECCR_CCU2BSMSPN3085UcellMaxIndexOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3085UcellMaxIndex_enum(rtb_Merge);
  }

  if (CbECCR_CCU2BSMSPN3087TMaxIndexOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3087TMaxIndex_enum
      (CeECCR_CCU2BSMSPN3087TMaxIndexOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3087TMaxIndex_enum(rtb_Merge2);
  }

  if (CbECCR_CCU2BSMSPN3090UcellWarnOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3090UcellWarn_enum
      (CeECCR_CCU2BSMSPN3090UcellWarnOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3090UcellWarn_enum(rtb_Merge5_nj);
  }

  if (CbECCR_CCU2BSMSPN3091SOCWarnOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3091SOCWarn_enum(CeECCR_CCU2BSMSPN3091SOCWarnOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3091SOCWarn_enum(rtb_Merge6_d);
  }

  if (CbECCR_CCU2BSMSPN3092IWarnOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3092IWarn_enum(CeECCR_CCU2BSMSPN3092IWarnOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3092IWarn_enum(rtb_Merge7_n);
  }

  if (CbECCR_CCU2BSMSPN3093TWarnOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3093TWarn_enum(CeECCR_CCU2BSMSPN3093TWarnOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3093TWarn_enum(rtb_Merge8_j);
  }

  if (CbECCR_CCU2BSMSPN3094IsoStateOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3094IsoState_enum(CeECCR_CCU2BSMSPN3094IsoStateOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3094IsoState_enum(rtb_Merge9_i);
  }

  if (CbECCR_CCU2BSMSPN3095OutConnectorStateOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3095OutConnectorState_enum
      (CeECCR_CCU2BSMSPN3095OutConnectorStateOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3095OutConnectorState_enum(rtb_Merge10);
  }

  if (CbECCR_CCU2BSMSPN3096ChgEnableOvrSwt_flg) {
    set_GeECCR_CCU2BSMSPN3096ChgEnable_enum
      (CeECCR_CCU2BSMSPN3096ChgEnableOvr_enum);
  } else {
    set_GeECCR_CCU2BSMSPN3096ChgEnable_enum(rtb_Merge11_o);
  }
}

/* Model initialize function */
void ECCR_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
