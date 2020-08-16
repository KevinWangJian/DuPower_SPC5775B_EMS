/*
 * File: EBCR.h
 *
 * Code generated for Simulink model 'EBCR'.
 *
 * Company                        : DP
 * Author                         : Kris Lee
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 08 14:21:32 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EBCR_h_
#define RTW_HEADER_EBCR_h_
#include <stddef.h>
#ifndef EBCR_COMMON_INCLUDES_
# define EBCR_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EBCR_COMMON_INCLUDES_ */

#include "EBCR_types.h"

/* Includes for objects with custom storage classes. */
#include "EBCR_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T GcEBCR_PackBOutVolt_V;      /* '<Root>/GcEBCR_PackBOutVolt_V' */
} ExtY_EBCR_T;

/* Real-time Model Data Structure */
struct tag_RTM_EBCR_T {
  const char_T * volatile errorStatus;
};

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_EBCR_T EBCR_Y;

/* Model entry point functions */
extern void EBCR_initialize(void);

/* Exported entry point functions */
extern void EBCR_BMS_Cell_18042701_10ms(void);
extern void EBCR_BMS_ConntSts_18192701_10ms(void);
extern void EBCR_BMS_DTC_18AA2701_10ms(void);
extern void EBCR_BMS_DetCell_18042701_10ms(void);
extern void EBCR_BMS_DetTemp_18062701_10ms(void);
extern void EBCR_BMS_Fault_18072701_10ms(void);
extern void EBCR_BMS_HV2_18182071_10ms(void);
extern void EBCR_BMS_HV_18022701_10ms(void);
extern void EBCR_BMS_HV_Curr_18102071_10ms(void);
extern void EBCR_BMS_ISO_18162701_10ms(void);
extern void EBCR_BMS_Info_18082701_10ms(void);
extern void EBCR_BMS_LongSOP_18032701_10ms(void);
extern void EBCR_BMS_PackInfo_18142701_10ms(void);
extern void EBCR_BMS_PeakSOP_18172701_10ms(void);
extern void EBCR_BMS_SysPara_18012701_10ms(void);
extern void EBCR_BMS_SysStat_18122701_10ms(void);
extern void EBCR_BMS_Temp_18152701_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EBCR_T *const EBCR_M;

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
 * '<Root>' : 'EBCR'
 * '<S1>'   : 'EBCR/EBCR'
 * '<S2>'   : 'EBCR/EBCR/BMS_Cell_18042701_10ms'
 * '<S3>'   : 'EBCR/EBCR/BMS_ConntSts_18192701_10ms'
 * '<S4>'   : 'EBCR/EBCR/BMS_DTC_18AA2701'
 * '<S5>'   : 'EBCR/EBCR/BMS_DetCell_18042701'
 * '<S6>'   : 'EBCR/EBCR/BMS_DetTemp_18062701'
 * '<S7>'   : 'EBCR/EBCR/BMS_Fault_1807270'
 * '<S8>'   : 'EBCR/EBCR/BMS_HV2_18182071'
 * '<S9>'   : 'EBCR/EBCR/BMS_HV_18022701'
 * '<S10>'  : 'EBCR/EBCR/BMS_HV_Curr_18102071'
 * '<S11>'  : 'EBCR/EBCR/BMS_ISO_18162701'
 * '<S12>'  : 'EBCR/EBCR/BMS_Info_18082701'
 * '<S13>'  : 'EBCR/EBCR/BMS_LongSOP_18032701'
 * '<S14>'  : 'EBCR/EBCR/BMS_PackInfo_18142701'
 * '<S15>'  : 'EBCR/EBCR/BMS_PeakSOP_18172701'
 * '<S16>'  : 'EBCR/EBCR/BMS_SysPara_18012701'
 * '<S17>'  : 'EBCR/EBCR/BMS_SysStat_18122701'
 * '<S18>'  : 'EBCR/EBCR/BMS_Temp_18152701'
 * '<S19>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSA_Cell_18042701'
 * '<S20>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSB_Cell_18042701'
 * '<S21>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSA_Cell_18042701/OverWrite10'
 * '<S22>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSA_Cell_18042701/OverWrite11'
 * '<S23>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSA_Cell_18042701/OverWrite6'
 * '<S24>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSA_Cell_18042701/OverWrite7'
 * '<S25>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSA_Cell_18042701/OverWrite8'
 * '<S26>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSA_Cell_18042701/OverWrite9'
 * '<S27>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSB_Cell_18042701/OverWrite'
 * '<S28>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSB_Cell_18042701/OverWrite1'
 * '<S29>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSB_Cell_18042701/OverWrite2'
 * '<S30>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSB_Cell_18042701/OverWrite3'
 * '<S31>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSB_Cell_18042701/OverWrite4'
 * '<S32>'  : 'EBCR/EBCR/BMS_Cell_18042701_10ms/BMSB_Cell_18042701/OverWrite5'
 * '<S33>'  : 'EBCR/EBCR/BMS_ConntSts_18192701_10ms/BMSA_ConntSts_18192701'
 * '<S34>'  : 'EBCR/EBCR/BMS_ConntSts_18192701_10ms/BMSB_ConntSts_18192701'
 * '<S35>'  : 'EBCR/EBCR/BMS_ConntSts_18192701_10ms/BMSA_ConntSts_18192701/OverWrite'
 * '<S36>'  : 'EBCR/EBCR/BMS_ConntSts_18192701_10ms/BMSA_ConntSts_18192701/OverWrite1'
 * '<S37>'  : 'EBCR/EBCR/BMS_ConntSts_18192701_10ms/BMSB_ConntSts_18192701/OverWrite'
 * '<S38>'  : 'EBCR/EBCR/BMS_ConntSts_18192701_10ms/BMSB_ConntSts_18192701/OverWrite1'
 * '<S39>'  : 'EBCR/EBCR/BMS_DTC_18AA2701/BMSA_DTC_18AA2701'
 * '<S40>'  : 'EBCR/EBCR/BMS_DTC_18AA2701/BMSB_DTC_18AA2701'
 * '<S41>'  : 'EBCR/EBCR/BMS_DTC_18AA2701/BMSA_DTC_18AA2701/OverWrite1'
 * '<S42>'  : 'EBCR/EBCR/BMS_DTC_18AA2701/BMSA_DTC_18AA2701/OverWrite2'
 * '<S43>'  : 'EBCR/EBCR/BMS_DTC_18AA2701/BMSA_DTC_18AA2701/OverWrite7'
 * '<S44>'  : 'EBCR/EBCR/BMS_DTC_18AA2701/BMSB_DTC_18AA2701/OverWrite3'
 * '<S45>'  : 'EBCR/EBCR/BMS_DTC_18AA2701/BMSB_DTC_18AA2701/OverWrite4'
 * '<S46>'  : 'EBCR/EBCR/BMS_DTC_18AA2701/BMSB_DTC_18AA2701/OverWrite5'
 * '<S47>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701'
 * '<S48>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701'
 * '<S49>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701/OverWrite1'
 * '<S50>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701/OverWrite2'
 * '<S51>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701/OverWrite3'
 * '<S52>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701/OverWrite4'
 * '<S53>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701/OverWrite5'
 * '<S54>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701/OverWrite6'
 * '<S55>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701/OverWrite7'
 * '<S56>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSA_DetCell_18052701/OverWrite8'
 * '<S57>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701/OverWrite10'
 * '<S58>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701/OverWrite11'
 * '<S59>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701/OverWrite12'
 * '<S60>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701/OverWrite13'
 * '<S61>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701/OverWrite14'
 * '<S62>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701/OverWrite15'
 * '<S63>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701/OverWrite16'
 * '<S64>'  : 'EBCR/EBCR/BMS_DetCell_18042701/BMSB_DetCell_18052701/OverWrite9'
 * '<S65>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701'
 * '<S66>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701'
 * '<S67>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701/OverWrite1'
 * '<S68>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701/OverWrite2'
 * '<S69>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701/OverWrite3'
 * '<S70>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701/OverWrite4'
 * '<S71>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701/OverWrite5'
 * '<S72>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701/OverWrite6'
 * '<S73>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701/OverWrite7'
 * '<S74>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSA_DetTemp_18062701/OverWrite8'
 * '<S75>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701/OverWrite10'
 * '<S76>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701/OverWrite11'
 * '<S77>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701/OverWrite12'
 * '<S78>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701/OverWrite13'
 * '<S79>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701/OverWrite14'
 * '<S80>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701/OverWrite15'
 * '<S81>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701/OverWrite16'
 * '<S82>'  : 'EBCR/EBCR/BMS_DetTemp_18062701/BMSB_DetTemp_18062701/OverWrite9'
 * '<S83>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701'
 * '<S84>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701'
 * '<S85>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite1'
 * '<S86>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite10'
 * '<S87>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite11'
 * '<S88>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite12'
 * '<S89>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite13'
 * '<S90>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite14'
 * '<S91>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite15'
 * '<S92>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite16'
 * '<S93>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite17'
 * '<S94>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite18'
 * '<S95>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite19'
 * '<S96>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite2'
 * '<S97>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite20'
 * '<S98>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite21'
 * '<S99>'  : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite22'
 * '<S100>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite3'
 * '<S101>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite4'
 * '<S102>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite5'
 * '<S103>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite6'
 * '<S104>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite7'
 * '<S105>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite8'
 * '<S106>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSA_Fault_18072701/OverWrite9'
 * '<S107>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite23'
 * '<S108>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite24'
 * '<S109>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite25'
 * '<S110>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite26'
 * '<S111>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite27'
 * '<S112>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite28'
 * '<S113>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite29'
 * '<S114>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite30'
 * '<S115>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite31'
 * '<S116>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite32'
 * '<S117>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite33'
 * '<S118>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite34'
 * '<S119>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite35'
 * '<S120>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite36'
 * '<S121>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite37'
 * '<S122>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite38'
 * '<S123>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite39'
 * '<S124>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite40'
 * '<S125>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite41'
 * '<S126>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite42'
 * '<S127>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite43'
 * '<S128>' : 'EBCR/EBCR/BMS_Fault_1807270/BMSB_Fault_18072701/OverWrite44'
 * '<S129>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSA_HV2_18182071'
 * '<S130>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSB_HV2_18182071'
 * '<S131>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSA_HV2_18182071/OverWrite1'
 * '<S132>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSA_HV2_18182071/OverWrite2'
 * '<S133>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSA_HV2_18182071/OverWrite3'
 * '<S134>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSA_HV2_18182071/OverWrite5'
 * '<S135>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSB_HV2_18182071/OverWrite4'
 * '<S136>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSB_HV2_18182071/OverWrite6'
 * '<S137>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSB_HV2_18182071/OverWrite7'
 * '<S138>' : 'EBCR/EBCR/BMS_HV2_18182071/BMSB_HV2_18182071/OverWrite8'
 * '<S139>' : 'EBCR/EBCR/BMS_HV_18022701/BMSA_HV_18022701'
 * '<S140>' : 'EBCR/EBCR/BMS_HV_18022701/BMSB_HV_18022701'
 * '<S141>' : 'EBCR/EBCR/BMS_HV_18022701/BMSA_HV_18022701/OverWrite1'
 * '<S142>' : 'EBCR/EBCR/BMS_HV_18022701/BMSA_HV_18022701/OverWrite2'
 * '<S143>' : 'EBCR/EBCR/BMS_HV_18022701/BMSA_HV_18022701/OverWrite3'
 * '<S144>' : 'EBCR/EBCR/BMS_HV_18022701/BMSA_HV_18022701/OverWrite4'
 * '<S145>' : 'EBCR/EBCR/BMS_HV_18022701/BMSB_HV_18022701/OverWrite5'
 * '<S146>' : 'EBCR/EBCR/BMS_HV_18022701/BMSB_HV_18022701/OverWrite6'
 * '<S147>' : 'EBCR/EBCR/BMS_HV_18022701/BMSB_HV_18022701/OverWrite7'
 * '<S148>' : 'EBCR/EBCR/BMS_HV_18022701/BMSB_HV_18022701/OverWrite8'
 * '<S149>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSA_HV_Curr_18102071'
 * '<S150>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSB_HV_Curr_18102071'
 * '<S151>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSA_HV_Curr_18102071/OverWrite1'
 * '<S152>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSA_HV_Curr_18102071/OverWrite16'
 * '<S153>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSA_HV_Curr_18102071/OverWrite2'
 * '<S154>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSA_HV_Curr_18102071/OverWrite3'
 * '<S155>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSA_HV_Curr_18102071/OverWrite4'
 * '<S156>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSA_HV_Curr_18102071/OverWrite5'
 * '<S157>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSA_HV_Curr_18102071/OverWrite6'
 * '<S158>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSB_HV_Curr_18102071/OverWrite1'
 * '<S159>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSB_HV_Curr_18102071/OverWrite10'
 * '<S160>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSB_HV_Curr_18102071/OverWrite11'
 * '<S161>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSB_HV_Curr_18102071/OverWrite4'
 * '<S162>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSB_HV_Curr_18102071/OverWrite7'
 * '<S163>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSB_HV_Curr_18102071/OverWrite8'
 * '<S164>' : 'EBCR/EBCR/BMS_HV_Curr_18102071/BMSB_HV_Curr_18102071/OverWrite9'
 * '<S165>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSA_ISO_18162701'
 * '<S166>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSB_ISO_18162701'
 * '<S167>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSA_ISO_18162701/OverWrite1'
 * '<S168>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSA_ISO_18162701/OverWrite2'
 * '<S169>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSA_ISO_18162701/OverWrite3'
 * '<S170>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSA_ISO_18162701/OverWrite4'
 * '<S171>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSB_ISO_18162701/OverWrite5'
 * '<S172>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSB_ISO_18162701/OverWrite6'
 * '<S173>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSB_ISO_18162701/OverWrite7'
 * '<S174>' : 'EBCR/EBCR/BMS_ISO_18162701/BMSB_ISO_18162701/OverWrite8'
 * '<S175>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701'
 * '<S176>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701'
 * '<S177>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite1'
 * '<S178>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite16'
 * '<S179>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite2'
 * '<S180>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite3'
 * '<S181>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite4'
 * '<S182>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite5'
 * '<S183>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite6'
 * '<S184>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite7'
 * '<S185>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite8'
 * '<S186>' : 'EBCR/EBCR/BMS_Info_18082701/BMSA_Info_18082701/OverWrite9'
 * '<S187>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite10'
 * '<S188>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite11'
 * '<S189>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite12'
 * '<S190>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite13'
 * '<S191>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite14'
 * '<S192>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite15'
 * '<S193>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite17'
 * '<S194>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite18'
 * '<S195>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite19'
 * '<S196>' : 'EBCR/EBCR/BMS_Info_18082701/BMSB_Info_18082701/OverWrite20'
 * '<S197>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSA_LongSOP_18032701'
 * '<S198>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSB_LongSOP_18032701'
 * '<S199>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSA_LongSOP_18032701/OverWrite1'
 * '<S200>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSA_LongSOP_18032701/OverWrite16'
 * '<S201>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSA_LongSOP_18032701/OverWrite2'
 * '<S202>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSA_LongSOP_18032701/OverWrite3'
 * '<S203>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSA_LongSOP_18032701/OverWrite8'
 * '<S204>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSB_LongSOP_18032701/OverWrite4'
 * '<S205>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSB_LongSOP_18032701/OverWrite5'
 * '<S206>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSB_LongSOP_18032701/OverWrite6'
 * '<S207>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSB_LongSOP_18032701/OverWrite7'
 * '<S208>' : 'EBCR/EBCR/BMS_LongSOP_18032701/BMSB_LongSOP_18032701/OverWrite9'
 * '<S209>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSA_PackInfo_18142701'
 * '<S210>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSB_PackInfo_18142701'
 * '<S211>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSA_PackInfo_18142701/OverWrite1'
 * '<S212>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSA_PackInfo_18142701/OverWrite2'
 * '<S213>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSA_PackInfo_18142701/OverWrite3'
 * '<S214>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSA_PackInfo_18142701/OverWrite4'
 * '<S215>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSA_PackInfo_18142701/OverWrite5'
 * '<S216>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSA_PackInfo_18142701/OverWrite6'
 * '<S217>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSA_PackInfo_18142701/OverWrite7'
 * '<S218>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSB_PackInfo_18142701/OverWrite1'
 * '<S219>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSB_PackInfo_18142701/OverWrite2'
 * '<S220>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSB_PackInfo_18142701/OverWrite3'
 * '<S221>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSB_PackInfo_18142701/OverWrite4'
 * '<S222>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSB_PackInfo_18142701/OverWrite5'
 * '<S223>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSB_PackInfo_18142701/OverWrite6'
 * '<S224>' : 'EBCR/EBCR/BMS_PackInfo_18142701/BMSB_PackInfo_18142701/OverWrite7'
 * '<S225>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSA_PeakSOP_18172701'
 * '<S226>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSB_PeakSOP_18172701'
 * '<S227>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSA_PeakSOP_18172701/OverWrite1'
 * '<S228>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSA_PeakSOP_18172701/OverWrite16'
 * '<S229>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSA_PeakSOP_18172701/OverWrite2'
 * '<S230>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSA_PeakSOP_18172701/OverWrite3'
 * '<S231>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSB_PeakSOP_18172701/OverWrite4'
 * '<S232>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSB_PeakSOP_18172701/OverWrite5'
 * '<S233>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSB_PeakSOP_18172701/OverWrite6'
 * '<S234>' : 'EBCR/EBCR/BMS_PeakSOP_18172701/BMSB_PeakSOP_18172701/OverWrite7'
 * '<S235>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSA_SysPara_18012701'
 * '<S236>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSB_SysPara_18012701'
 * '<S237>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSA_SysPara_18012701/OverWrite1'
 * '<S238>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSA_SysPara_18012701/OverWrite2'
 * '<S239>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSA_SysPara_18012701/OverWrite3'
 * '<S240>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSA_SysPara_18012701/OverWrite4'
 * '<S241>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSA_SysPara_18012701/OverWrite5'
 * '<S242>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSA_SysPara_18012701/OverWrite6'
 * '<S243>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSA_SysPara_18012701/OverWrite7'
 * '<S244>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSB_SysPara_18012701/OverWrite10'
 * '<S245>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSB_SysPara_18012701/OverWrite11'
 * '<S246>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSB_SysPara_18012701/OverWrite12'
 * '<S247>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSB_SysPara_18012701/OverWrite13'
 * '<S248>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSB_SysPara_18012701/OverWrite14'
 * '<S249>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSB_SysPara_18012701/OverWrite8'
 * '<S250>' : 'EBCR/EBCR/BMS_SysPara_18012701/BMSB_SysPara_18012701/OverWrite9'
 * '<S251>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701'
 * '<S252>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701'
 * '<S253>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite1'
 * '<S254>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite10'
 * '<S255>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite11'
 * '<S256>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite12'
 * '<S257>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite13'
 * '<S258>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite14'
 * '<S259>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite15'
 * '<S260>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite16'
 * '<S261>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite17'
 * '<S262>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite2'
 * '<S263>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite3'
 * '<S264>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite4'
 * '<S265>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite6'
 * '<S266>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite7'
 * '<S267>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite8'
 * '<S268>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSA_SysStat_18122701/OverWrite9'
 * '<S269>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite18'
 * '<S270>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite19'
 * '<S271>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite20'
 * '<S272>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite21'
 * '<S273>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite22'
 * '<S274>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite23'
 * '<S275>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite24'
 * '<S276>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite25'
 * '<S277>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite26'
 * '<S278>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite27'
 * '<S279>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite28'
 * '<S280>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite29'
 * '<S281>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite30'
 * '<S282>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite31'
 * '<S283>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite32'
 * '<S284>' : 'EBCR/EBCR/BMS_SysStat_18122701/BMSB_SysStat_18122701/OverWrite5'
 * '<S285>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSA_Temp_18152701'
 * '<S286>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSB_Temp_18152701'
 * '<S287>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSA_Temp_18152701/OverWrite1'
 * '<S288>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSA_Temp_18152701/OverWrite2'
 * '<S289>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSA_Temp_18152701/OverWrite3'
 * '<S290>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSA_Temp_18152701/OverWrite4'
 * '<S291>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSA_Temp_18152701/OverWrite5'
 * '<S292>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSA_Temp_18152701/OverWrite6'
 * '<S293>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSA_Temp_18152701/OverWrite7'
 * '<S294>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSB_Temp_18152701/OverWrite10'
 * '<S295>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSB_Temp_18152701/OverWrite11'
 * '<S296>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSB_Temp_18152701/OverWrite12'
 * '<S297>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSB_Temp_18152701/OverWrite13'
 * '<S298>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSB_Temp_18152701/OverWrite14'
 * '<S299>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSB_Temp_18152701/OverWrite8'
 * '<S300>' : 'EBCR/EBCR/BMS_Temp_18152701/BMSB_Temp_18152701/OverWrite9'
 */

/*-
 * Requirements for '<Root>': EBCR
 */
#endif                                 /* RTW_HEADER_EBCR_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
