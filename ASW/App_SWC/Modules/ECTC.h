/*
 * File: ECTC.h
 *
 * Code generated for Simulink model 'ECTC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 20 17:33:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ECTC_h_
#define RTW_HEADER_ECTC_h_
#include <math.h>
#include <stddef.h>
#ifndef ECTC_COMMON_INCLUDES_
# define ECTC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ECTC_COMMON_INCLUDES_ */

#include "ECTC_types.h"

/* Includes for objects with custom storage classes. */
#include "ECTC_Const.h"
#include "ECTC_Cal.h"
#include "ECTC_Var.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S25>/DebounceStartZero' */
typedef struct {
  boolean_T Switch;                    /* '<S27>/Switch' */
} B_DebounceStartZero_ECTC_T;

/* Block states (auto storage) for system '<S25>/DebounceStartZero' */
typedef struct {
  uint32_T StateName;                  /* '<S30>/Unit Delay' */
  uint32_T StateName_f;                /* '<S31>/Unit Delay1' */
  boolean_T StateName_h;               /* '<S27>/Unit Delay' */
  boolean_T StateName_e;               /* '<S30>/Unit Delay1' */
  boolean_T StateName_m;               /* '<S31>/Unit Delay2' */
} DW_DebounceStartZero_ECTC_T;

/* Block signals for system '<S61>/DebounceStartZero' */
typedef struct {
  real32_T Switch;                     /* '<S67>/Switch' */
} B_DebounceStartZero_ECTC_m_T;

/* Block states (auto storage) for system '<S61>/DebounceStartZero' */
typedef struct {
  real32_T StateName;                  /* '<S67>/Unit Delay' */
  uint32_T StateName_e;                /* '<S69>/Unit Delay' */
  uint32_T StateName_c;                /* '<S70>/Unit Delay1' */
  boolean_T StateName_g;               /* '<S69>/Unit Delay1' */
  boolean_T StateName_h;               /* '<S70>/Unit Delay2' */
} DW_DebounceStartZero_ECTC_n_T;

/* Block signals for system '<S112>/DebounceStartZero1' */
typedef struct {
  boolean_T Switch;                    /* '<S114>/Switch' */
} B_DebounceStartZero1_ECTC_T;

/* Block states (auto storage) for system '<S112>/DebounceStartZero1' */
typedef struct {
  uint32_T StateName;                  /* '<S116>/Unit Delay' */
  uint32_T StateName_h;                /* '<S117>/Unit Delay1' */
  boolean_T StateName_l;               /* '<S114>/Unit Delay' */
  boolean_T StateName_i;               /* '<S116>/Unit Delay1' */
  boolean_T StateName_n;               /* '<S117>/Unit Delay2' */
} DW_DebounceStartZero1_ECTC_T;

/* Block signals (auto storage) */
typedef struct {
  uint8_T GeECTC_ReChrgCtrBMode_enum;  /* '<S488>/ReChrgCtrBMode' */
  uint8_T GeECTC_ReChrgCtrAMode_enum;  /* '<S419>/ReChrgCtrAMode' */
  uint8_T GeECTC_CChrgCtrBMode_enum;   /* '<S314>/CChrgCtrBMode' */
  uint8_T GeECTC_CChrgCtrAMode_enum;   /* '<S245>/CChrgCtrAMode' */
  uint8_T GeECTC_BCChrgCtrBMode_enum;  /* '<S127>/BCChrgCtrBMode' */
  uint8_T GeECTC_BCChrgCtrAMode_enum;  /* '<S9>/BCChrgCtrAMode' */
  boolean_T Constant3;                 /* '<S554>/Constant3' */
  boolean_T Switch;                    /* '<S530>/Switch' */
  boolean_T Switch_h;                  /* '<S531>/Switch' */
  boolean_T Switch_c;                  /* '<S492>/Switch' */
  boolean_T Switch_b;                  /* '<S462>/Switch' */
  boolean_T Constant3_f;               /* '<S380>/Constant3' */
  boolean_T Switch_o;                  /* '<S354>/Switch' */
  boolean_T Switch_p;                  /* '<S355>/Switch' */
  boolean_T Switch_g;                  /* '<S317>/Switch' */
  boolean_T Constant3_c;               /* '<S311>/Constant3' */
  boolean_T Switch_i;                  /* '<S285>/Switch' */
  boolean_T Switch_e;                  /* '<S286>/Switch' */
  boolean_T Switch_en;                 /* '<S248>/Switch' */
  boolean_T Constant3_l;               /* '<S230>/Constant3' */
  boolean_T Switch_f;                  /* '<S134>/Switch' */
  boolean_T Switch_j;                  /* '<S138>/Switch' */
  boolean_T Switch_hy;                 /* '<S139>/Switch' */
  boolean_T Switch_a;                  /* '<S140>/Switch' */
  boolean_T Switch_af;                 /* '<S141>/Switch' */
  boolean_T Switch_k;                  /* '<S128>/Switch' */
  boolean_T Constant3_j;               /* '<S112>/Constant3' */
  boolean_T Switch_ex;                 /* '<S16>/Switch' */
  boolean_T LbECTC_BCChrgAPreChrgTimeOutFlt;/* '<S62>/Switch' */
  boolean_T Switch_fc;                 /* '<S64>/Switch' */
  boolean_T Switch_n;                  /* '<S10>/Switch' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_g4;/* '<S531>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_pkl;/* '<S530>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_c;/* '<S504>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_px;/* '<S503>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_h;/* '<S462>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_k1;/* '<S461>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_b;/* '<S435>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_mk;/* '<S434>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_kb;/* '<S355>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_on;/* '<S354>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_i;/* '<S330>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_pk;/* '<S329>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_m;/* '<S286>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_d;/* '<S285>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_k;/* '<S261>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_ln;/* '<S260>/DebounceStartZero' */
  B_DebounceStartZero1_ECTC_T DebounceStartZero1_g;/* '<S230>/DebounceStartZero1' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_a;/* '<S195>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero1_h;/* '<S194>/DebounceStartZero1' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_p3;/* '<S194>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_f4;/* '<S141>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_l;/* '<S140>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_n;/* '<S139>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_pv;/* '<S138>/DebounceStartZero' */
  B_DebounceStartZero1_ECTC_T DebounceStartZero1_a;/* '<S112>/DebounceStartZero1' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_e;/* '<S64>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_g;/* '<S63>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_p;/* '<S62>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_m_T DebounceStartZero_f;/* '<S61>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero_o;/* '<S26>/DebounceStartZero' */
  B_DebounceStartZero_ECTC_T DebounceStartZero1;/* '<S25>/DebounceStartZero1' */
  B_DebounceStartZero_ECTC_T DebounceStartZero;/* '<S25>/DebounceStartZero' */
} B_ECTC_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T FixPtUnitDelay1_DSTATE;     /* '<S556>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_f;   /* '<S500>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_g;   /* '<S487>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_b;   /* '<S431>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_m;   /* '<S382>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_p;   /* '<S326>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_l;   /* '<S313>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_h;   /* '<S257>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_c;   /* '<S244>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_i;   /* '<S191>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_d;   /* '<S126>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_fc;  /* '<S22>/FixPt Unit Delay1' */
  uint8_T StateName;                   /* '<S488>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S556>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_o;    /* '<S500>/FixPt Unit Delay2' */
  uint8_T StateName_i;                 /* '<S419>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_h;    /* '<S487>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_ov;   /* '<S431>/FixPt Unit Delay2' */
  uint8_T StateName_c;                 /* '<S314>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_j;    /* '<S382>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_hu;   /* '<S326>/FixPt Unit Delay2' */
  uint8_T StateName_d;                 /* '<S245>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_k;    /* '<S313>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_m;    /* '<S257>/FixPt Unit Delay2' */
  uint8_T StateName_k;                 /* '<S127>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_mk;   /* '<S244>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_e;    /* '<S191>/FixPt Unit Delay2' */
  uint8_T StateName_i2;                /* '<S9>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_ek;   /* '<S126>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_n;    /* '<S22>/FixPt Unit Delay2' */
  boolean_T StateName_p;               /* '<S527>/Unit Delay' */
  boolean_T StateName_g;               /* '<S502>/Unit Delay' */
  boolean_T Delay_DSTATE;              /* '<S492>/Delay' */
  boolean_T StateName_f;               /* '<S458>/Unit Delay' */
  boolean_T StateName_j;               /* '<S433>/Unit Delay' */
  boolean_T StateName_a;               /* '<S423>/Unit Delay' */
  boolean_T StateName_cv;              /* '<S354>/Unit Delay' */
  boolean_T StateName_h;               /* '<S353>/Unit Delay' */
  boolean_T StateName_f2;              /* '<S328>/Unit Delay' */
  boolean_T Delay_DSTATE_a;            /* '<S317>/Delay' */
  boolean_T StateName_iz;              /* '<S285>/Unit Delay' */
  boolean_T StateName_m;               /* '<S284>/Unit Delay' */
  boolean_T StateName_fy;              /* '<S259>/Unit Delay' */
  boolean_T Delay_DSTATE_h;            /* '<S248>/Delay' */
  boolean_T Delay_DSTATE_an;           /* '<S134>/Delay' */
  boolean_T StateName_o;               /* '<S193>/Unit Delay1' */
  boolean_T StateName_mi;              /* '<S193>/Unit Delay' */
  boolean_T StateName_ha;              /* '<S137>/Unit Delay' */
  boolean_T StateName_l;               /* '<S138>/Unit Delay' */
  boolean_T StateName_jm;              /* '<S140>/Unit Delay' */
  boolean_T StateName_n;               /* '<S137>/Unit Delay1' */
  boolean_T Delay_DSTATE_p;            /* '<S128>/Delay' */
  boolean_T Delay_DSTATE_av;           /* '<S16>/Delay' */
  boolean_T StateName_ib;              /* '<S60>/Unit Delay' */
  boolean_T StateName_ax;              /* '<S61>/Unit Delay' */
  boolean_T StateName_jt;              /* '<S63>/Unit Delay' */
  boolean_T StateName_nc;              /* '<S60>/Unit Delay1' */
  boolean_T StateName_b;               /* '<S24>/Unit Delay1' */
  boolean_T StateName_aj;              /* '<S24>/Unit Delay' */
  boolean_T Delay_DSTATE_o;            /* '<S10>/Delay' */
  uint8_T is_active_c4_ECTC;           /* '<S488>/ReChrgCtrBMode' */
  uint8_T is_c4_ECTC;                  /* '<S488>/ReChrgCtrBMode' */
  uint8_T is_active_c2_ECTC;           /* '<S419>/ReChrgCtrAMode' */
  uint8_T is_c2_ECTC;                  /* '<S419>/ReChrgCtrAMode' */
  uint8_T is_active_c5_ECTC;           /* '<S314>/CChrgCtrBMode' */
  uint8_T is_c5_ECTC;                  /* '<S314>/CChrgCtrBMode' */
  uint8_T is_active_c1_ECTC;           /* '<S245>/CChrgCtrAMode' */
  uint8_T is_c1_ECTC;                  /* '<S245>/CChrgCtrAMode' */
  uint8_T is_active_c6_ECTC;           /* '<S127>/BCChrgCtrBMode' */
  uint8_T is_c6_ECTC;                  /* '<S127>/BCChrgCtrBMode' */
  uint8_T is_active_c3_ECTC;           /* '<S9>/BCChrgCtrAMode' */
  uint8_T is_c3_ECTC;                  /* '<S9>/BCChrgCtrAMode' */
  boolean_T OnlineWork_MODE;           /* '<S493>/OnlineWork' */
  boolean_T PreshutWork_MODE;          /* '<S494>/PreshutWork' */
  boolean_T ShutdownWork_MODE;         /* '<S496>/ShutdownWork' */
  boolean_T PrechrgWork_MODE;          /* '<S495>/PrechrgWork' */
  boolean_T OfflineWork_MODE;          /* '<S491>/OfflineWork' */
  boolean_T OnlineWork_MODE_o;         /* '<S424>/OnlineWork' */
  boolean_T PreshutWork_MODE_i;        /* '<S425>/PreshutWork' */
  boolean_T ShutdownWork_MODE_h;       /* '<S427>/ShutdownWork' */
  boolean_T PrechrgWork_MODE_p;        /* '<S426>/PrechrgWork' */
  boolean_T OfflineWork_MODE_n;        /* '<S422>/OfflineWork' */
  boolean_T OnlineWork_MODE_b;         /* '<S318>/OnlineWork' */
  boolean_T PreshutWork_MODE_l;        /* '<S319>/PreshutWork' */
  boolean_T ShutdownWork_MODE_g;       /* '<S321>/ShutdownWork' */
  boolean_T PrechrgWork_MODE_g;        /* '<S320>/PrechrgWork' */
  boolean_T OfflineWork_MODE_e;        /* '<S316>/OfflineWork' */
  boolean_T OnlineWork_MODE_c;         /* '<S249>/OnlineWork' */
  boolean_T PreshutWork_MODE_n;        /* '<S250>/PreshutWork' */
  boolean_T ShutdownWork_MODE_b;       /* '<S252>/ShutdownWork' */
  boolean_T PrechrgWork_MODE_i;        /* '<S251>/PrechrgWork' */
  boolean_T OfflineWork_MODE_c;        /* '<S247>/OfflineWork' */
  boolean_T ShutdownWork_MODE_bd;      /* '<S135>/ShutdownWork' */
  boolean_T OnlineWork_MODE_d;         /* '<S132>/OnlineWork' */
  boolean_T PreshutWork_MODE_j;        /* '<S133>/PreshutWork' */
  boolean_T OfflineWork_MODE_b;        /* '<S131>/OfflineWork' */
  boolean_T PrechrgWork_MODE_o;        /* '<S129>/PrechrgWork' */
  boolean_T ShutdownWork_MODE_bv;      /* '<S17>/ShutdownWork' */
  boolean_T OnlineWork_MODE_k;         /* '<S13>/OnlineWork' */
  boolean_T PreshutWork_MODE_h;        /* '<S14>/PreshutWork' */
  boolean_T PrechrgWork_MODE_pf;       /* '<S15>/PrechrgWork' */
  boolean_T OfflineWork_MODE_h;        /* '<S12>/OfflineWork' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_g4;/* '<S531>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_pkl;/* '<S530>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_c;/* '<S504>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_px;/* '<S503>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_h;/* '<S462>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_k1;/* '<S461>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_b;/* '<S435>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_mk;/* '<S434>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_kb;/* '<S355>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_on;/* '<S354>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_i;/* '<S330>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_pk;/* '<S329>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_m;/* '<S286>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_d;/* '<S285>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_k;/* '<S261>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_ln;/* '<S260>/DebounceStartZero' */
  DW_DebounceStartZero1_ECTC_T DebounceStartZero1_g;/* '<S230>/DebounceStartZero1' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_a;/* '<S195>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero1_h;/* '<S194>/DebounceStartZero1' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_p3;/* '<S194>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_f4;/* '<S141>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_l;/* '<S140>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_n;/* '<S139>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_pv;/* '<S138>/DebounceStartZero' */
  DW_DebounceStartZero1_ECTC_T DebounceStartZero1_a;/* '<S112>/DebounceStartZero1' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_e;/* '<S64>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_g;/* '<S63>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_p;/* '<S62>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_n_T DebounceStartZero_f;/* '<S61>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero_o;/* '<S26>/DebounceStartZero' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero1;/* '<S25>/DebounceStartZero1' */
  DW_DebounceStartZero_ECTC_T DebounceStartZero;/* '<S25>/DebounceStartZero' */
} DW_ECTC_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S493>/Data Type Conversion' */
  const uint8_T DataTypeConversion_l;  /* '<S494>/Data Type Conversion' */
  const uint8_T DataTypeConversion_n;  /* '<S496>/Data Type Conversion' */
  const uint8_T DataTypeConversion_b;  /* '<S495>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S528>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_p; /* '<S501>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_c;  /* '<S492>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_c; /* '<S492>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_a;  /* '<S491>/Data Type Conversion' */
  const uint8_T DataTypeConversion_ai; /* '<S498>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_pe;/* '<S498>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S498>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S498>/Data Type Conversion3' */
  const uint8_T DataTypeConversion_h;  /* '<S424>/Data Type Conversion' */
  const uint8_T DataTypeConversion_c2; /* '<S425>/Data Type Conversion' */
  const uint8_T DataTypeConversion_g;  /* '<S427>/Data Type Conversion' */
  const uint8_T DataTypeConversion_f;  /* '<S426>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_d; /* '<S459>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_c2;/* '<S432>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_d;  /* '<S423>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_m; /* '<S423>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_e;  /* '<S422>/Data Type Conversion' */
  const uint8_T DataTypeConversion_o;  /* '<S429>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_e; /* '<S429>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_i; /* '<S429>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_f; /* '<S429>/Data Type Conversion3' */
  const uint8_T DataTypeConversion_cf; /* '<S318>/Data Type Conversion' */
  const uint8_T DataTypeConversion_c4; /* '<S319>/Data Type Conversion' */
  const uint8_T DataTypeConversion_lw; /* '<S321>/Data Type Conversion' */
  const uint8_T DataTypeConversion_dy; /* '<S320>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_b; /* '<S356>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_a; /* '<S327>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_g5; /* '<S317>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_f; /* '<S317>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_k;  /* '<S316>/Data Type Conversion' */
  const uint8_T DataTypeConversion_cd; /* '<S324>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_i; /* '<S324>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_m; /* '<S324>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_o; /* '<S324>/Data Type Conversion3' */
  const uint8_T DataTypeConversion_ov; /* '<S249>/Data Type Conversion' */
  const uint8_T DataTypeConversion_ep; /* '<S250>/Data Type Conversion' */
  const uint8_T DataTypeConversion_i;  /* '<S252>/Data Type Conversion' */
  const uint8_T DataTypeConversion_iv; /* '<S251>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_cc;/* '<S287>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_cl;/* '<S258>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_au; /* '<S248>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_pa;/* '<S248>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_co; /* '<S247>/Data Type Conversion' */
  const uint8_T DataTypeConversion_ke; /* '<S255>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_mh;/* '<S255>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_d; /* '<S255>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_g; /* '<S255>/Data Type Conversion3' */
  const uint8_T DataTypeConversion_hk; /* '<S135>/Data Type Conversion' */
  const uint8_T DataTypeConversion_os; /* '<S132>/Data Type Conversion' */
  const uint8_T DataTypeConversion_bz; /* '<S133>/Data Type Conversion' */
  const uint8_T DataTypeConversion_oh; /* '<S134>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_ay;/* '<S134>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_dm;/* '<S192>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_fd; /* '<S131>/Data Type Conversion' */
  const uint8_T DataTypeConversion_ou; /* '<S189>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_g; /* '<S189>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_a; /* '<S189>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_a; /* '<S189>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S189>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5;   /* '<S189>/Data Type Conversion5' */
  const uint8_T DataTypeConversion_ko; /* '<S129>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_n; /* '<S142>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_p;  /* '<S128>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_di;/* '<S128>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_gj; /* '<S17>/Data Type Conversion' */
  const uint8_T DataTypeConversion_as; /* '<S13>/Data Type Conversion' */
  const uint8_T DataTypeConversion_az; /* '<S14>/Data Type Conversion' */
  const uint8_T DataTypeConversion_j;  /* '<S16>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_j; /* '<S16>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_oo; /* '<S15>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_h; /* '<S65>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_c4;/* '<S23>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_cx; /* '<S12>/Data Type Conversion' */
  const uint8_T DataTypeConversion_oj; /* '<S20>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_k; /* '<S20>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_l; /* '<S20>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_i; /* '<S20>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_n; /* '<S20>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_e; /* '<S20>/Data Type Conversion5' */
  const uint8_T DataTypeConversion_jc; /* '<S10>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_bj;/* '<S10>/Data Type Conversion1' */
} ConstB_ECTC_T;

/* Real-time Model Data Structure */
struct tag_RTM_ECTC_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_ECTC_T ECTC_B;

/* Block states (auto storage) */
extern DW_ECTC_T ECTC_DW;
extern const ConstB_ECTC_T ECTC_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void ECTC_initialize(void);

/* Exported entry point functions */
extern void ECTC_BCChrgA_20ms(void);
extern void ECTC_BCChrgB_20ms(void);
extern void ECTC_CChrgA_20ms(void);
extern void ECTC_CChrgB_20ms(void);
extern void ECTC_Fault_20ms(void);
extern void ECTC_ReChrgA_20ms(void);
extern void ECTC_ReChrgB_20ms(void);

/* Real-time Model object */
extern RT_MODEL_ECTC_T *const ECTC_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ECTC'
 * '<S1>'   : 'ECTC/ECTC_All'
 * '<S2>'   : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys'
 * '<S3>'   : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys'
 * '<S4>'   : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys'
 * '<S5>'   : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys'
 * '<S6>'   : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys'
 * '<S7>'   : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys'
 * '<S8>'   : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys'
 * '<S9>'   : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA'
 * '<S10>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgAPCtrCmd'
 * '<S11>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAMode'
 * '<S12>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAOffline'
 * '<S13>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAOnline'
 * '<S14>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut'
 * '<S15>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg'
 * '<S16>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgABCPCtrCmd'
 * '<S17>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown'
 * '<S18>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/ECTC_GeECTC_BatDisChg2State_enum'
 * '<S19>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAOffline/OfflineWork'
 * '<S20>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAOffline/OfflineWork/OfflineToPrechrg'
 * '<S21>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAOffline/OfflineWork/OfflineToPrechrg/Delay'
 * '<S22>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAOffline/OfflineWork/OfflineToPrechrg/Delay/Unit Delay Resettable'
 * '<S23>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAOnline/OnlineWork'
 * '<S24>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork'
 * '<S25>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt'
 * '<S26>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem'
 * '<S27>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero'
 * '<S28>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1'
 * '<S29>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S30>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S31>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S32>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S33>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S34>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S35>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S36>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S37>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S38>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S39>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/Compare To Zero'
 * '<S40>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/FaultProcess'
 * '<S41>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess'
 * '<S42>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/FaultProcess/Decrease'
 * '<S43>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/FaultProcess/Increase'
 * '<S44>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/FaultProcess/Decrease/Nomal'
 * '<S45>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess/Compare To Zero'
 * '<S46>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess/Decrease'
 * '<S47>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess/Increase'
 * '<S48>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess/Decrease/Nomal'
 * '<S49>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero'
 * '<S50>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/Compare To Zero'
 * '<S51>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/FaultProcess'
 * '<S52>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess'
 * '<S53>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/FaultProcess/Decrease'
 * '<S54>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/FaultProcess/Increase'
 * '<S55>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S56>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S57>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess/Decrease'
 * '<S58>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess/Increase'
 * '<S59>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S60>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork'
 * '<S61>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd'
 * '<S62>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt'
 * '<S63>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd'
 * '<S64>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt'
 * '<S65>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/PrechrgToOffline'
 * '<S66>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/PrechrgToOnline'
 * '<S67>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero'
 * '<S68>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/Compare To Zero'
 * '<S69>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess'
 * '<S70>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess'
 * '<S71>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S72>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S73>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S74>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S75>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S76>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Increase'
 * '<S77>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S78>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero'
 * '<S79>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S80>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S81>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S82>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S83>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S84>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S85>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S86>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S87>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S88>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/BCChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S89>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero'
 * '<S90>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/Compare To Zero'
 * '<S91>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/FaultProcess'
 * '<S92>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/HealProcess'
 * '<S93>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S94>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S95>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S96>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S97>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S98>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/HealProcess/Increase'
 * '<S99>'  : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S100>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero'
 * '<S101>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S102>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S103>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S104>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S105>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S106>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S107>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S108>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S109>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S110>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/BCChrgCtrAPrechrg/PrechrgWork/CChrgABCPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S111>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork'
 * '<S112>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem'
 * '<S113>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem1'
 * '<S114>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1'
 * '<S115>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/Compare To Zero'
 * '<S116>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/FaultProcess'
 * '<S117>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess'
 * '<S118>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/FaultProcess/Decrease'
 * '<S119>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/FaultProcess/Increase'
 * '<S120>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/FaultProcess/Decrease/Nomal'
 * '<S121>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess/Compare To Zero'
 * '<S122>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess/Decrease'
 * '<S123>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess/Increase'
 * '<S124>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess/Decrease/Nomal'
 * '<S125>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem1/Delay'
 * '<S126>' : 'ECTC/ECTC_All/ECTC_BCChrgA_20ms_Sys/ECTC_BCChrgA/CChrgCtrAShutdown/ShutdownWork/Subsystem1/Delay/Unit Delay Resettable'
 * '<S127>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB'
 * '<S128>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAOffline1'
 * '<S129>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg'
 * '<S130>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBMode'
 * '<S131>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBOffline'
 * '<S132>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBOnline'
 * '<S133>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut'
 * '<S134>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBBCOffline2'
 * '<S135>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown'
 * '<S136>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/ECTC_GeECTC_BatDisChg2State_enum'
 * '<S137>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork'
 * '<S138>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd'
 * '<S139>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt'
 * '<S140>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd'
 * '<S141>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt'
 * '<S142>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/PrechrgToOffline'
 * '<S143>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/PrechrgToOnline'
 * '<S144>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero'
 * '<S145>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/Compare To Zero'
 * '<S146>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess'
 * '<S147>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess'
 * '<S148>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S149>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S150>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S151>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S152>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S153>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Increase'
 * '<S154>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S155>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero'
 * '<S156>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S157>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S158>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S159>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S160>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S161>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S162>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S163>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S164>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S165>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/BCChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S166>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero'
 * '<S167>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/Compare To Zero'
 * '<S168>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/FaultProcess'
 * '<S169>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/HealProcess'
 * '<S170>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S171>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S172>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S173>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S174>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S175>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/HealProcess/Increase'
 * '<S176>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S177>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero'
 * '<S178>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S179>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S180>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S181>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S182>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S183>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S184>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S185>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S186>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S187>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrAPrechrg/PrechrgWork/CChrgBBCPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S188>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBOffline/OfflineWork'
 * '<S189>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBOffline/OfflineWork/OfflineToPrechrg'
 * '<S190>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBOffline/OfflineWork/OfflineToPrechrg/Delay'
 * '<S191>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBOffline/OfflineWork/OfflineToPrechrg/Delay/Unit Delay Resettable'
 * '<S192>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBOnline/OnlineWork'
 * '<S193>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork'
 * '<S194>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt'
 * '<S195>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem'
 * '<S196>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero'
 * '<S197>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1'
 * '<S198>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S199>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S200>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S201>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S202>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S203>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S204>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S205>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S206>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S207>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S208>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/Compare To Zero'
 * '<S209>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/FaultProcess'
 * '<S210>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess'
 * '<S211>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/FaultProcess/Decrease'
 * '<S212>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/FaultProcess/Increase'
 * '<S213>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/FaultProcess/Decrease/Nomal'
 * '<S214>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess/Compare To Zero'
 * '<S215>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess/Decrease'
 * '<S216>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess/Increase'
 * '<S217>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/BCChrgAOutCurrTimeOutFlt/DebounceStartZero1/HealProcess/Decrease/Nomal'
 * '<S218>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero'
 * '<S219>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/Compare To Zero'
 * '<S220>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/FaultProcess'
 * '<S221>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess'
 * '<S222>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/FaultProcess/Decrease'
 * '<S223>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/FaultProcess/Increase'
 * '<S224>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S225>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S226>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess/Decrease'
 * '<S227>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess/Increase'
 * '<S228>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/BCChrgCtrBPreShut/PreshutWork/Subsystem/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S229>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork'
 * '<S230>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem'
 * '<S231>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem1'
 * '<S232>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1'
 * '<S233>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/Compare To Zero'
 * '<S234>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/FaultProcess'
 * '<S235>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess'
 * '<S236>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/FaultProcess/Decrease'
 * '<S237>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/FaultProcess/Increase'
 * '<S238>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/FaultProcess/Decrease/Nomal'
 * '<S239>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess/Compare To Zero'
 * '<S240>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess/Decrease'
 * '<S241>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess/Increase'
 * '<S242>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem/DebounceStartZero1/HealProcess/Decrease/Nomal'
 * '<S243>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem1/Delay'
 * '<S244>' : 'ECTC/ECTC_All/ECTC_BCChrgB_20ms_Sys/ECTC_BCChrgB/CChrgCtrBShutdown/ShutdownWork/Subsystem1/Delay/Unit Delay Resettable'
 * '<S245>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA'
 * '<S246>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAMode'
 * '<S247>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAOffline'
 * '<S248>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAOffline1'
 * '<S249>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAOnline'
 * '<S250>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut'
 * '<S251>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg'
 * '<S252>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAShutdown'
 * '<S253>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/ECTC_GeECTC_BatDisChg2State_enum'
 * '<S254>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAOffline/OfflineWork'
 * '<S255>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAOffline/OfflineWork/OfflineToPrechrg'
 * '<S256>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAOffline/OfflineWork/OfflineToPrechrg/Delay'
 * '<S257>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAOffline/OfflineWork/OfflineToPrechrg/Delay/Unit Delay Resettable'
 * '<S258>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAOnline/OnlineWork'
 * '<S259>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork'
 * '<S260>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown'
 * '<S261>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt'
 * '<S262>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero'
 * '<S263>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/Compare To Zero'
 * '<S264>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/FaultProcess'
 * '<S265>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess'
 * '<S266>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/FaultProcess/Decrease'
 * '<S267>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/FaultProcess/Increase'
 * '<S268>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S269>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S270>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess/Decrease'
 * '<S271>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess/Increase'
 * '<S272>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/CChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S273>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero'
 * '<S274>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S275>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S276>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S277>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S278>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S279>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S280>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S281>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S282>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S283>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S284>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork'
 * '<S285>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd'
 * '<S286>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt'
 * '<S287>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/PrechrgToOffline'
 * '<S288>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/PrechrgToOnline'
 * '<S289>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero'
 * '<S290>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/Compare To Zero'
 * '<S291>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess'
 * '<S292>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess'
 * '<S293>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S294>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S295>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S296>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S297>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S298>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Increase'
 * '<S299>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S300>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero'
 * '<S301>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S302>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S303>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S304>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S305>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S306>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S307>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S308>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S309>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S310>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAPrechrg/PrechrgWork/CChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S311>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAShutdown/ShutdownWork'
 * '<S312>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAShutdown/ShutdownWork/Delay'
 * '<S313>' : 'ECTC/ECTC_All/ECTC_CChrgA_20ms_Sys/ECTC_CChrgA/CChrgCtrAShutdown/ShutdownWork/Delay/Unit Delay Resettable'
 * '<S314>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB'
 * '<S315>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBMode'
 * '<S316>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBOffline'
 * '<S317>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBOffline1'
 * '<S318>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBOnline'
 * '<S319>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut'
 * '<S320>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg'
 * '<S321>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBShutdown'
 * '<S322>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/ECTC_GeECTC_BatDisChg2State_enum'
 * '<S323>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBOffline/OfflineWork'
 * '<S324>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBOffline/OfflineWork/OfflineToPrechrg'
 * '<S325>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBOffline/OfflineWork/OfflineToPrechrg/Delay'
 * '<S326>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBOffline/OfflineWork/OfflineToPrechrg/Delay/Unit Delay Resettable'
 * '<S327>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBOnline/OnlineWork'
 * '<S328>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork'
 * '<S329>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown'
 * '<S330>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt'
 * '<S331>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero'
 * '<S332>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/Compare To Zero'
 * '<S333>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/FaultProcess'
 * '<S334>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess'
 * '<S335>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/FaultProcess/Decrease'
 * '<S336>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/FaultProcess/Increase'
 * '<S337>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S338>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S339>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess/Decrease'
 * '<S340>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess/Increase'
 * '<S341>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/CChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S342>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero'
 * '<S343>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S344>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S345>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S346>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S347>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S348>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S349>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S350>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S351>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S352>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S353>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork'
 * '<S354>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd'
 * '<S355>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt'
 * '<S356>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/PrechrgToOffline'
 * '<S357>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/PrechrgToOnline'
 * '<S358>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero'
 * '<S359>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/Compare To Zero'
 * '<S360>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess'
 * '<S361>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess'
 * '<S362>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S363>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S364>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S365>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S366>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S367>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Increase'
 * '<S368>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S369>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero'
 * '<S370>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S371>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S372>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S373>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S374>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S375>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S376>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S377>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S378>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S379>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBPrechrg/PrechrgWork/CChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S380>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBShutdown/ShutdownWork'
 * '<S381>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBShutdown/ShutdownWork/Delay'
 * '<S382>' : 'ECTC/ECTC_All/ECTC_CChrgB_20ms_Sys/ECTC_CChrgB/CChrgCtrBShutdown/ShutdownWork/Delay/Unit Delay Resettable'
 * '<S383>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt'
 * '<S384>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/TimeOutFlt'
 * '<S385>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt'
 * '<S386>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub'
 * '<S387>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem'
 * '<S388>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem2'
 * '<S389>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem3'
 * '<S390>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem4'
 * '<S391>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem5'
 * '<S392>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S393>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem2/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S394>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem3/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S395>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem4/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S396>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CircuitFlt/Subsystem5/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S397>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/BCChrgCmd'
 * '<S398>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/CChrgACmd'
 * '<S399>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/CChrgBCmd'
 * '<S400>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/ReChrgACmd'
 * '<S401>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/ReChrgBCmd'
 * '<S402>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/BCChrgCmd/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S403>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/BCChrgCmd/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S404>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/CChrgACmd/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S405>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/CChrgACmd/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S406>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/CChrgBCmd/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S407>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/CChrgBCmd/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S408>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/ReChrgACmd/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S409>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/ReChrgACmd/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S410>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/ReChrgBCmd/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S411>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/Cmd&Flt/CmdSub/ReChrgBCmd/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S412>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/TimeOutFlt/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S413>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/TimeOutFlt/ECTC_GeECTC_BatDisChg2State_enum2'
 * '<S414>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/TimeOutFlt/ECTC_GeECTC_BatDisChg2State_enum3'
 * '<S415>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/TimeOutFlt/ECTC_GeECTC_BatDisChg2State_enum4'
 * '<S416>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/TimeOutFlt/ECTC_GeECTC_BatDisChg2State_enum5'
 * '<S417>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/TimeOutFlt/ECTC_GeECTC_BatDisChg2State_enum6'
 * '<S418>' : 'ECTC/ECTC_All/ECTC_Fault_20ms_Sys/TimeOutFlt/ECTC_GeECTC_BatDisChg2State_enum7'
 * '<S419>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA'
 * '<S420>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S421>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAMode'
 * '<S422>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAOffline'
 * '<S423>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAOffline1'
 * '<S424>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAOnline'
 * '<S425>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut'
 * '<S426>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg'
 * '<S427>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAShutdown'
 * '<S428>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAOffline/OfflineWork'
 * '<S429>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAOffline/OfflineWork/OfflineToPrechrg'
 * '<S430>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAOffline/OfflineWork/OfflineToPrechrg/Delay'
 * '<S431>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAOffline/OfflineWork/OfflineToPrechrg/Delay/Unit Delay Resettable'
 * '<S432>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAOnline/OnlineWork'
 * '<S433>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork'
 * '<S434>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt'
 * '<S435>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown'
 * '<S436>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero'
 * '<S437>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S438>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S439>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S440>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S441>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S442>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S443>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S444>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S445>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S446>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgAOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S447>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero'
 * '<S448>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/Compare To Zero'
 * '<S449>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/FaultProcess'
 * '<S450>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess'
 * '<S451>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/FaultProcess/Decrease'
 * '<S452>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/FaultProcess/Increase'
 * '<S453>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S454>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S455>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess/Decrease'
 * '<S456>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess/Increase'
 * '<S457>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPreShut/PreshutWork/ReChrgCtrAPreShutToShutdown/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S458>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork'
 * '<S459>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/PrechrgToOffline'
 * '<S460>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/PrechrgToOnline'
 * '<S461>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd'
 * '<S462>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt'
 * '<S463>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero'
 * '<S464>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/Compare To Zero'
 * '<S465>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess'
 * '<S466>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess'
 * '<S467>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S468>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S469>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S470>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S471>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S472>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Increase'
 * '<S473>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S474>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero'
 * '<S475>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S476>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S477>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S478>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S479>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S480>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S481>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S482>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S483>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S484>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAPrechrg/PrechrgWork/ReChrgAPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S485>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAShutdown/ShutdownWork'
 * '<S486>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAShutdown/ShutdownWork/Delay'
 * '<S487>' : 'ECTC/ECTC_All/ECTC_ReChrgA_20ms_Sys/ECTC_ReChrgA/ReChrgCtrAShutdown/ShutdownWork/Delay/Unit Delay Resettable'
 * '<S488>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB'
 * '<S489>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S490>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBMode'
 * '<S491>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBOffline'
 * '<S492>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBOffline1'
 * '<S493>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBOnline'
 * '<S494>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut'
 * '<S495>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg'
 * '<S496>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBShutdown'
 * '<S497>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBOffline/OfflineWork'
 * '<S498>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBOffline/OfflineWork/OfflineToPrechrg'
 * '<S499>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBOffline/OfflineWork/OfflineToPrechrg/Delay'
 * '<S500>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBOffline/OfflineWork/OfflineToPrechrg/Delay/Unit Delay Resettable'
 * '<S501>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBOnline/OnlineWork'
 * '<S502>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork'
 * '<S503>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt'
 * '<S504>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown'
 * '<S505>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero'
 * '<S506>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S507>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S508>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S509>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S510>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S511>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S512>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S513>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S514>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S515>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgBOutCurrTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S516>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero'
 * '<S517>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/Compare To Zero'
 * '<S518>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/FaultProcess'
 * '<S519>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess'
 * '<S520>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/FaultProcess/Decrease'
 * '<S521>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/FaultProcess/Increase'
 * '<S522>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S523>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S524>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess/Decrease'
 * '<S525>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess/Increase'
 * '<S526>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPreShut/PreshutWork/ReChrgCtrBPreShutToShutdown/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S527>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork'
 * '<S528>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/PrechrgToOffline'
 * '<S529>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/PrechrgToOnline'
 * '<S530>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd'
 * '<S531>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt'
 * '<S532>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero'
 * '<S533>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/Compare To Zero'
 * '<S534>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess'
 * '<S535>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess'
 * '<S536>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S537>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S538>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S539>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S540>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S541>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Increase'
 * '<S542>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPos&NegCtrCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S543>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero'
 * '<S544>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/Compare To Zero'
 * '<S545>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess'
 * '<S546>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess'
 * '<S547>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease'
 * '<S548>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Increase'
 * '<S549>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S550>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S551>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease'
 * '<S552>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Increase'
 * '<S553>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBPrechrg/PrechrgWork/ReChrgBPreChrgTimeOutFlt/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S554>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBShutdown/ShutdownWork'
 * '<S555>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBShutdown/ShutdownWork/Delay'
 * '<S556>' : 'ECTC/ECTC_All/ECTC_ReChrgB_20ms_Sys/ECTC_ReChrgB/ReChrgCtrBShutdown/ShutdownWork/Delay/Unit Delay Resettable'
 */

/*-
 * Requirements for '<Root>': ECTC
 */
#endif                                 /* RTW_HEADER_ECTC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
