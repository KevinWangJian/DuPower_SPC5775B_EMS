/*
 * This is Os_DisableInterrupts.h, auto-generated for:
 *   Project: RTAOS
 *   Target:  PPCe200WR
 *   Variant: MPC5777C
 *   Version: 5.1.14
 */
/*
 * Include this header in order to allow any configured INTC interrupt to be
 * disabled or enabled
 */
#ifndef OS_DISABLEINTERRUPTS_H
#define OS_DISABLEINTERRUPTS_H

/* These macros can be used to disable and enable individual interrupts by
 * vector name or configuration name
 * [$TargetHT 144] [$TargetGHS 256] [$TargetWR 239]
*/
#define Os_IntChannel_eQADC_A_CMD_FIFO_0_Fill (104U)
#define Os_Disable_eQADC_A_CMD_FIFO_0_Fill()  ((volatile uint8 *)&OS_INTC_PSR0)[104U] = 0U
#define Os_Enable_eQADC_A_CMD_FIFO_0_Fill()   ((volatile uint8 *)&OS_INTC_PSR0)[104U] = 0x000AU
#define Os_IntChannel_Adc_Eqadc_EqadcACFifo0Empty (104U)
#define Os_Disable_Adc_Eqadc_EqadcACFifo0Empty()  Os_Disable_eQADC_A_CMD_FIFO_0_Fill()
#define Os_Enable_Adc_Eqadc_EqadcACFifo0Empty()   Os_Enable_eQADC_A_CMD_FIFO_0_Fill()

#define Os_IntChannel_eQADC_A_Rx_FIFO_0_Drain (105U)
#define Os_Disable_eQADC_A_Rx_FIFO_0_Drain()  ((volatile uint8 *)&OS_INTC_PSR0)[105U] = 0U
#define Os_Enable_eQADC_A_Rx_FIFO_0_Drain()   ((volatile uint8 *)&OS_INTC_PSR0)[105U] = 0x000AU
#define Os_IntChannel_Adc_Eqadc_EqadcARFifo0Full (105U)
#define Os_Disable_Adc_Eqadc_EqadcARFifo0Full()  Os_Disable_eQADC_A_Rx_FIFO_0_Drain()
#define Os_Enable_Adc_Eqadc_EqadcARFifo0Full()   Os_Enable_eQADC_A_Rx_FIFO_0_Drain()

#define Os_IntChannel_eMIOS_0_Channel_16 (202U)
#define Os_Disable_eMIOS_0_Channel_16()  ((volatile uint8 *)&OS_INTC_PSR0)[202U] = 0U
#define Os_Enable_eMIOS_0_Channel_16()   ((volatile uint8 *)&OS_INTC_PSR0)[202U] = 0x000BU
#define Os_IntChannel_EMIOS_0_CH_16_ISR (202U)
#define Os_Disable_EMIOS_0_CH_16_ISR()  Os_Disable_eMIOS_0_Channel_16()
#define Os_Enable_EMIOS_0_CH_16_ISR()   Os_Enable_eMIOS_0_Channel_16()

#define Os_IntChannel_eMIOS_0_Channel_18 (204U)
#define Os_Disable_eMIOS_0_Channel_18()  ((volatile uint8 *)&OS_INTC_PSR0)[204U] = 0U
#define Os_Enable_eMIOS_0_Channel_18()   ((volatile uint8 *)&OS_INTC_PSR0)[204U] = 0x000BU
#define Os_IntChannel_EMIOS_0_CH_18_ISR (204U)
#define Os_Disable_EMIOS_0_CH_18_ISR()  Os_Disable_eMIOS_0_Channel_18()
#define Os_Enable_EMIOS_0_CH_18_ISR()   Os_Enable_eMIOS_0_Channel_18()

#define Os_IntChannel_eMIOS_0_Channel_19 (205U)
#define Os_Disable_eMIOS_0_Channel_19()  ((volatile uint8 *)&OS_INTC_PSR0)[205U] = 0U
#define Os_Enable_eMIOS_0_Channel_19()   ((volatile uint8 *)&OS_INTC_PSR0)[205U] = 0x000BU
#define Os_IntChannel_EMIOS_0_CH_19_ISR (205U)
#define Os_Disable_EMIOS_0_CH_19_ISR()  Os_Disable_eMIOS_0_Channel_19()
#define Os_Enable_EMIOS_0_CH_19_ISR()   Os_Enable_eMIOS_0_Channel_19()

#define Os_IntChannel_eMIOS_0_Channel_20 (206U)
#define Os_Disable_eMIOS_0_Channel_20()  ((volatile uint8 *)&OS_INTC_PSR0)[206U] = 0U
#define Os_Enable_eMIOS_0_Channel_20()   ((volatile uint8 *)&OS_INTC_PSR0)[206U] = 0x000BU
#define Os_IntChannel_EMIOS_0_CH_20_ISR (206U)
#define Os_Disable_EMIOS_0_CH_20_ISR()  Os_Disable_eMIOS_0_Channel_20()
#define Os_Enable_EMIOS_0_CH_20_ISR()   Os_Enable_eMIOS_0_Channel_20()

#define Os_IntChannel_eMIOS_0_Channel_21 (207U)
#define Os_Disable_eMIOS_0_Channel_21()  ((volatile uint8 *)&OS_INTC_PSR0)[207U] = 0U
#define Os_Enable_eMIOS_0_Channel_21()   ((volatile uint8 *)&OS_INTC_PSR0)[207U] = 0x000BU
#define Os_IntChannel_EMIOS_0_CH_21_ISR (207U)
#define Os_Disable_EMIOS_0_CH_21_ISR()  Os_Disable_eMIOS_0_Channel_21()
#define Os_Enable_EMIOS_0_CH_21_ISR()   Os_Enable_eMIOS_0_Channel_21()

#define Os_IntChannel_FLEXCAN_B_Bus_Off (280U)
#define Os_Disable_FLEXCAN_B_Bus_Off()  ((volatile uint8 *)&OS_INTC_PSR0)[280U] = 0U
#define Os_Enable_FLEXCAN_B_Bus_Off()   ((volatile uint8 *)&OS_INTC_PSR0)[280U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_BO (280U)
#define Os_Disable_Can_IsrFCB_BO()  Os_Disable_FLEXCAN_B_Bus_Off()
#define Os_Enable_Can_IsrFCB_BO()   Os_Enable_FLEXCAN_B_Bus_Off()

#define Os_IntChannel_FLEXCAN_B_Error (281U)
#define Os_Disable_FLEXCAN_B_Error()  ((volatile uint8 *)&OS_INTC_PSR0)[281U] = 0U
#define Os_Enable_FLEXCAN_B_Error()   ((volatile uint8 *)&OS_INTC_PSR0)[281U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_ERR (281U)
#define Os_Disable_Can_IsrFCB_ERR()  Os_Disable_FLEXCAN_B_Error()
#define Os_Enable_Can_IsrFCB_ERR()   Os_Enable_FLEXCAN_B_Error()

#define Os_IntChannel_FLEXCAN_B_Buffer_0 (283U)
#define Os_Disable_FLEXCAN_B_Buffer_0()  ((volatile uint8 *)&OS_INTC_PSR0)[283U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_0()   ((volatile uint8 *)&OS_INTC_PSR0)[283U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_00 (283U)
#define Os_Disable_Can_IsrFCB_MB_00()  Os_Disable_FLEXCAN_B_Buffer_0()
#define Os_Enable_Can_IsrFCB_MB_00()   Os_Enable_FLEXCAN_B_Buffer_0()

#define Os_IntChannel_FLEXCAN_B_Buffer_1 (284U)
#define Os_Disable_FLEXCAN_B_Buffer_1()  ((volatile uint8 *)&OS_INTC_PSR0)[284U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_1()   ((volatile uint8 *)&OS_INTC_PSR0)[284U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_01 (284U)
#define Os_Disable_Can_IsrFCB_MB_01()  Os_Disable_FLEXCAN_B_Buffer_1()
#define Os_Enable_Can_IsrFCB_MB_01()   Os_Enable_FLEXCAN_B_Buffer_1()

#define Os_IntChannel_FLEXCAN_B_Buffer_2 (285U)
#define Os_Disable_FLEXCAN_B_Buffer_2()  ((volatile uint8 *)&OS_INTC_PSR0)[285U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_2()   ((volatile uint8 *)&OS_INTC_PSR0)[285U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_02 (285U)
#define Os_Disable_Can_IsrFCB_MB_02()  Os_Disable_FLEXCAN_B_Buffer_2()
#define Os_Enable_Can_IsrFCB_MB_02()   Os_Enable_FLEXCAN_B_Buffer_2()

#define Os_IntChannel_FLEXCAN_B_Buffer_3 (286U)
#define Os_Disable_FLEXCAN_B_Buffer_3()  ((volatile uint8 *)&OS_INTC_PSR0)[286U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_3()   ((volatile uint8 *)&OS_INTC_PSR0)[286U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_03 (286U)
#define Os_Disable_Can_IsrFCB_MB_03()  Os_Disable_FLEXCAN_B_Buffer_3()
#define Os_Enable_Can_IsrFCB_MB_03()   Os_Enable_FLEXCAN_B_Buffer_3()

#define Os_IntChannel_FLEXCAN_B_Buffer_4 (287U)
#define Os_Disable_FLEXCAN_B_Buffer_4()  ((volatile uint8 *)&OS_INTC_PSR0)[287U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_4()   ((volatile uint8 *)&OS_INTC_PSR0)[287U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_04 (287U)
#define Os_Disable_Can_IsrFCB_MB_04()  Os_Disable_FLEXCAN_B_Buffer_4()
#define Os_Enable_Can_IsrFCB_MB_04()   Os_Enable_FLEXCAN_B_Buffer_4()

#define Os_IntChannel_FLEXCAN_B_Buffer_5 (288U)
#define Os_Disable_FLEXCAN_B_Buffer_5()  ((volatile uint8 *)&OS_INTC_PSR0)[288U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_5()   ((volatile uint8 *)&OS_INTC_PSR0)[288U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_05 (288U)
#define Os_Disable_Can_IsrFCB_MB_05()  Os_Disable_FLEXCAN_B_Buffer_5()
#define Os_Enable_Can_IsrFCB_MB_05()   Os_Enable_FLEXCAN_B_Buffer_5()

#define Os_IntChannel_FLEXCAN_B_Buffer_6 (289U)
#define Os_Disable_FLEXCAN_B_Buffer_6()  ((volatile uint8 *)&OS_INTC_PSR0)[289U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_6()   ((volatile uint8 *)&OS_INTC_PSR0)[289U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_06 (289U)
#define Os_Disable_Can_IsrFCB_MB_06()  Os_Disable_FLEXCAN_B_Buffer_6()
#define Os_Enable_Can_IsrFCB_MB_06()   Os_Enable_FLEXCAN_B_Buffer_6()

#define Os_IntChannel_FLEXCAN_B_Buffer_7 (290U)
#define Os_Disable_FLEXCAN_B_Buffer_7()  ((volatile uint8 *)&OS_INTC_PSR0)[290U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_7()   ((volatile uint8 *)&OS_INTC_PSR0)[290U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_07 (290U)
#define Os_Disable_Can_IsrFCB_MB_07()  Os_Disable_FLEXCAN_B_Buffer_7()
#define Os_Enable_Can_IsrFCB_MB_07()   Os_Enable_FLEXCAN_B_Buffer_7()

#define Os_IntChannel_FLEXCAN_B_Buffer_8 (291U)
#define Os_Disable_FLEXCAN_B_Buffer_8()  ((volatile uint8 *)&OS_INTC_PSR0)[291U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_8()   ((volatile uint8 *)&OS_INTC_PSR0)[291U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_08 (291U)
#define Os_Disable_Can_IsrFCB_MB_08()  Os_Disable_FLEXCAN_B_Buffer_8()
#define Os_Enable_Can_IsrFCB_MB_08()   Os_Enable_FLEXCAN_B_Buffer_8()

#define Os_IntChannel_FLEXCAN_B_Buffer_9 (292U)
#define Os_Disable_FLEXCAN_B_Buffer_9()  ((volatile uint8 *)&OS_INTC_PSR0)[292U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_9()   ((volatile uint8 *)&OS_INTC_PSR0)[292U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_09 (292U)
#define Os_Disable_Can_IsrFCB_MB_09()  Os_Disable_FLEXCAN_B_Buffer_9()
#define Os_Enable_Can_IsrFCB_MB_09()   Os_Enable_FLEXCAN_B_Buffer_9()

#define Os_IntChannel_FLEXCAN_B_Buffer_10 (293U)
#define Os_Disable_FLEXCAN_B_Buffer_10()  ((volatile uint8 *)&OS_INTC_PSR0)[293U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_10()   ((volatile uint8 *)&OS_INTC_PSR0)[293U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_10 (293U)
#define Os_Disable_Can_IsrFCB_MB_10()  Os_Disable_FLEXCAN_B_Buffer_10()
#define Os_Enable_Can_IsrFCB_MB_10()   Os_Enable_FLEXCAN_B_Buffer_10()

#define Os_IntChannel_FLEXCAN_B_Buffer_11 (294U)
#define Os_Disable_FLEXCAN_B_Buffer_11()  ((volatile uint8 *)&OS_INTC_PSR0)[294U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_11()   ((volatile uint8 *)&OS_INTC_PSR0)[294U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_11 (294U)
#define Os_Disable_Can_IsrFCB_MB_11()  Os_Disable_FLEXCAN_B_Buffer_11()
#define Os_Enable_Can_IsrFCB_MB_11()   Os_Enable_FLEXCAN_B_Buffer_11()

#define Os_IntChannel_FLEXCAN_B_Buffer_12 (295U)
#define Os_Disable_FLEXCAN_B_Buffer_12()  ((volatile uint8 *)&OS_INTC_PSR0)[295U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_12()   ((volatile uint8 *)&OS_INTC_PSR0)[295U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_12 (295U)
#define Os_Disable_Can_IsrFCB_MB_12()  Os_Disable_FLEXCAN_B_Buffer_12()
#define Os_Enable_Can_IsrFCB_MB_12()   Os_Enable_FLEXCAN_B_Buffer_12()

#define Os_IntChannel_FLEXCAN_B_Buffer_13 (296U)
#define Os_Disable_FLEXCAN_B_Buffer_13()  ((volatile uint8 *)&OS_INTC_PSR0)[296U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_13()   ((volatile uint8 *)&OS_INTC_PSR0)[296U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_13 (296U)
#define Os_Disable_Can_IsrFCB_MB_13()  Os_Disable_FLEXCAN_B_Buffer_13()
#define Os_Enable_Can_IsrFCB_MB_13()   Os_Enable_FLEXCAN_B_Buffer_13()

#define Os_IntChannel_FLEXCAN_B_Buffer_14 (297U)
#define Os_Disable_FLEXCAN_B_Buffer_14()  ((volatile uint8 *)&OS_INTC_PSR0)[297U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_14()   ((volatile uint8 *)&OS_INTC_PSR0)[297U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_14 (297U)
#define Os_Disable_Can_IsrFCB_MB_14()  Os_Disable_FLEXCAN_B_Buffer_14()
#define Os_Enable_Can_IsrFCB_MB_14()   Os_Enable_FLEXCAN_B_Buffer_14()

#define Os_IntChannel_FLEXCAN_B_Buffer_15 (298U)
#define Os_Disable_FLEXCAN_B_Buffer_15()  ((volatile uint8 *)&OS_INTC_PSR0)[298U] = 0U
#define Os_Enable_FLEXCAN_B_Buffer_15()   ((volatile uint8 *)&OS_INTC_PSR0)[298U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_15 (298U)
#define Os_Disable_Can_IsrFCB_MB_15()  Os_Disable_FLEXCAN_B_Buffer_15()
#define Os_Enable_Can_IsrFCB_MB_15()   Os_Enable_FLEXCAN_B_Buffer_15()

#define Os_IntChannel_FLEXCAN_B_Buffers_16_31 (299U)
#define Os_Disable_FLEXCAN_B_Buffers_16_31()  ((volatile uint8 *)&OS_INTC_PSR0)[299U] = 0U
#define Os_Enable_FLEXCAN_B_Buffers_16_31()   ((volatile uint8 *)&OS_INTC_PSR0)[299U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_16_31 (299U)
#define Os_Disable_Can_IsrFCB_MB_16_31()  Os_Disable_FLEXCAN_B_Buffers_16_31()
#define Os_Enable_Can_IsrFCB_MB_16_31()   Os_Enable_FLEXCAN_B_Buffers_16_31()

#define Os_IntChannel_FLEXCAN_B_Buffers_32_63 (300U)
#define Os_Disable_FLEXCAN_B_Buffers_32_63()  ((volatile uint8 *)&OS_INTC_PSR0)[300U] = 0U
#define Os_Enable_FLEXCAN_B_Buffers_32_63()   ((volatile uint8 *)&OS_INTC_PSR0)[300U] = 0x000CU
#define Os_IntChannel_Can_IsrFCB_MB_32_63 (300U)
#define Os_Disable_Can_IsrFCB_MB_32_63()  Os_Disable_FLEXCAN_B_Buffers_32_63()
#define Os_Enable_Can_IsrFCB_MB_32_63()   Os_Enable_FLEXCAN_B_Buffers_32_63()

#define Os_IntChannel_M_CAN_Combined (348U)
#define Os_Disable_M_CAN_Combined()  ((volatile uint8 *)&OS_INTC_PSR0)[348U] = 0U
#define Os_Enable_M_CAN_Combined()   ((volatile uint8 *)&OS_INTC_PSR0)[348U] = 0x000DU
#define Os_IntChannel_Can_IsrCombined_IL0_IL1 (348U)
#define Os_Disable_Can_IsrCombined_IL0_IL1()  Os_Disable_M_CAN_Combined()
#define Os_Enable_Can_IsrCombined_IL0_IL1()   Os_Enable_M_CAN_Combined()

#define Os_IntChannel_FLEXCAN_A_Bus_Off (152U)
#define Os_Disable_FLEXCAN_A_Bus_Off()  ((volatile uint8 *)&OS_INTC_PSR0)[152U] = 0U
#define Os_Enable_FLEXCAN_A_Bus_Off()   ((volatile uint8 *)&OS_INTC_PSR0)[152U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_BO (152U)
#define Os_Disable_Can_IsrFCA_BO()  Os_Disable_FLEXCAN_A_Bus_Off()
#define Os_Enable_Can_IsrFCA_BO()   Os_Enable_FLEXCAN_A_Bus_Off()

#define Os_IntChannel_FLEXCAN_A_Error (153U)
#define Os_Disable_FLEXCAN_A_Error()  ((volatile uint8 *)&OS_INTC_PSR0)[153U] = 0U
#define Os_Enable_FLEXCAN_A_Error()   ((volatile uint8 *)&OS_INTC_PSR0)[153U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_ERR (153U)
#define Os_Disable_Can_IsrFCA_ERR()  Os_Disable_FLEXCAN_A_Error()
#define Os_Enable_Can_IsrFCA_ERR()   Os_Enable_FLEXCAN_A_Error()

#define Os_IntChannel_FLEXCAN_A_Buffer_0 (155U)
#define Os_Disable_FLEXCAN_A_Buffer_0()  ((volatile uint8 *)&OS_INTC_PSR0)[155U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_0()   ((volatile uint8 *)&OS_INTC_PSR0)[155U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_00 (155U)
#define Os_Disable_Can_IsrFCA_MB_00()  Os_Disable_FLEXCAN_A_Buffer_0()
#define Os_Enable_Can_IsrFCA_MB_00()   Os_Enable_FLEXCAN_A_Buffer_0()

#define Os_IntChannel_FLEXCAN_A_Buffer_1 (156U)
#define Os_Disable_FLEXCAN_A_Buffer_1()  ((volatile uint8 *)&OS_INTC_PSR0)[156U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_1()   ((volatile uint8 *)&OS_INTC_PSR0)[156U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_01 (156U)
#define Os_Disable_Can_IsrFCA_MB_01()  Os_Disable_FLEXCAN_A_Buffer_1()
#define Os_Enable_Can_IsrFCA_MB_01()   Os_Enable_FLEXCAN_A_Buffer_1()

#define Os_IntChannel_FLEXCAN_A_Buffer_2 (157U)
#define Os_Disable_FLEXCAN_A_Buffer_2()  ((volatile uint8 *)&OS_INTC_PSR0)[157U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_2()   ((volatile uint8 *)&OS_INTC_PSR0)[157U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_02 (157U)
#define Os_Disable_Can_IsrFCA_MB_02()  Os_Disable_FLEXCAN_A_Buffer_2()
#define Os_Enable_Can_IsrFCA_MB_02()   Os_Enable_FLEXCAN_A_Buffer_2()

#define Os_IntChannel_FLEXCAN_A_Buffer_3 (158U)
#define Os_Disable_FLEXCAN_A_Buffer_3()  ((volatile uint8 *)&OS_INTC_PSR0)[158U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_3()   ((volatile uint8 *)&OS_INTC_PSR0)[158U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_03 (158U)
#define Os_Disable_Can_IsrFCA_MB_03()  Os_Disable_FLEXCAN_A_Buffer_3()
#define Os_Enable_Can_IsrFCA_MB_03()   Os_Enable_FLEXCAN_A_Buffer_3()

#define Os_IntChannel_FLEXCAN_A_Buffer_4 (159U)
#define Os_Disable_FLEXCAN_A_Buffer_4()  ((volatile uint8 *)&OS_INTC_PSR0)[159U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_4()   ((volatile uint8 *)&OS_INTC_PSR0)[159U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_04 (159U)
#define Os_Disable_Can_IsrFCA_MB_04()  Os_Disable_FLEXCAN_A_Buffer_4()
#define Os_Enable_Can_IsrFCA_MB_04()   Os_Enable_FLEXCAN_A_Buffer_4()

#define Os_IntChannel_FLEXCAN_A_Buffer_5 (160U)
#define Os_Disable_FLEXCAN_A_Buffer_5()  ((volatile uint8 *)&OS_INTC_PSR0)[160U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_5()   ((volatile uint8 *)&OS_INTC_PSR0)[160U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_05 (160U)
#define Os_Disable_Can_IsrFCA_MB_05()  Os_Disable_FLEXCAN_A_Buffer_5()
#define Os_Enable_Can_IsrFCA_MB_05()   Os_Enable_FLEXCAN_A_Buffer_5()

#define Os_IntChannel_FLEXCAN_A_Buffer_6 (161U)
#define Os_Disable_FLEXCAN_A_Buffer_6()  ((volatile uint8 *)&OS_INTC_PSR0)[161U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_6()   ((volatile uint8 *)&OS_INTC_PSR0)[161U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_06 (161U)
#define Os_Disable_Can_IsrFCA_MB_06()  Os_Disable_FLEXCAN_A_Buffer_6()
#define Os_Enable_Can_IsrFCA_MB_06()   Os_Enable_FLEXCAN_A_Buffer_6()

#define Os_IntChannel_FLEXCAN_A_Buffer_7 (162U)
#define Os_Disable_FLEXCAN_A_Buffer_7()  ((volatile uint8 *)&OS_INTC_PSR0)[162U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_7()   ((volatile uint8 *)&OS_INTC_PSR0)[162U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_07 (162U)
#define Os_Disable_Can_IsrFCA_MB_07()  Os_Disable_FLEXCAN_A_Buffer_7()
#define Os_Enable_Can_IsrFCA_MB_07()   Os_Enable_FLEXCAN_A_Buffer_7()

#define Os_IntChannel_FLEXCAN_A_Buffer_8 (163U)
#define Os_Disable_FLEXCAN_A_Buffer_8()  ((volatile uint8 *)&OS_INTC_PSR0)[163U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_8()   ((volatile uint8 *)&OS_INTC_PSR0)[163U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_08 (163U)
#define Os_Disable_Can_IsrFCA_MB_08()  Os_Disable_FLEXCAN_A_Buffer_8()
#define Os_Enable_Can_IsrFCA_MB_08()   Os_Enable_FLEXCAN_A_Buffer_8()

#define Os_IntChannel_FLEXCAN_A_Buffer_9 (164U)
#define Os_Disable_FLEXCAN_A_Buffer_9()  ((volatile uint8 *)&OS_INTC_PSR0)[164U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_9()   ((volatile uint8 *)&OS_INTC_PSR0)[164U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_09 (164U)
#define Os_Disable_Can_IsrFCA_MB_09()  Os_Disable_FLEXCAN_A_Buffer_9()
#define Os_Enable_Can_IsrFCA_MB_09()   Os_Enable_FLEXCAN_A_Buffer_9()

#define Os_IntChannel_FLEXCAN_A_Buffer_10 (165U)
#define Os_Disable_FLEXCAN_A_Buffer_10()  ((volatile uint8 *)&OS_INTC_PSR0)[165U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_10()   ((volatile uint8 *)&OS_INTC_PSR0)[165U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_10 (165U)
#define Os_Disable_Can_IsrFCA_MB_10()  Os_Disable_FLEXCAN_A_Buffer_10()
#define Os_Enable_Can_IsrFCA_MB_10()   Os_Enable_FLEXCAN_A_Buffer_10()

#define Os_IntChannel_FLEXCAN_A_Buffer_11 (166U)
#define Os_Disable_FLEXCAN_A_Buffer_11()  ((volatile uint8 *)&OS_INTC_PSR0)[166U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_11()   ((volatile uint8 *)&OS_INTC_PSR0)[166U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_11 (166U)
#define Os_Disable_Can_IsrFCA_MB_11()  Os_Disable_FLEXCAN_A_Buffer_11()
#define Os_Enable_Can_IsrFCA_MB_11()   Os_Enable_FLEXCAN_A_Buffer_11()

#define Os_IntChannel_FLEXCAN_A_Buffer_12 (167U)
#define Os_Disable_FLEXCAN_A_Buffer_12()  ((volatile uint8 *)&OS_INTC_PSR0)[167U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_12()   ((volatile uint8 *)&OS_INTC_PSR0)[167U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_12 (167U)
#define Os_Disable_Can_IsrFCA_MB_12()  Os_Disable_FLEXCAN_A_Buffer_12()
#define Os_Enable_Can_IsrFCA_MB_12()   Os_Enable_FLEXCAN_A_Buffer_12()

#define Os_IntChannel_FLEXCAN_A_Buffer_13 (168U)
#define Os_Disable_FLEXCAN_A_Buffer_13()  ((volatile uint8 *)&OS_INTC_PSR0)[168U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_13()   ((volatile uint8 *)&OS_INTC_PSR0)[168U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_13 (168U)
#define Os_Disable_Can_IsrFCA_MB_13()  Os_Disable_FLEXCAN_A_Buffer_13()
#define Os_Enable_Can_IsrFCA_MB_13()   Os_Enable_FLEXCAN_A_Buffer_13()

#define Os_IntChannel_FLEXCAN_A_Buffer_14 (169U)
#define Os_Disable_FLEXCAN_A_Buffer_14()  ((volatile uint8 *)&OS_INTC_PSR0)[169U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_14()   ((volatile uint8 *)&OS_INTC_PSR0)[169U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_14 (169U)
#define Os_Disable_Can_IsrFCA_MB_14()  Os_Disable_FLEXCAN_A_Buffer_14()
#define Os_Enable_Can_IsrFCA_MB_14()   Os_Enable_FLEXCAN_A_Buffer_14()

#define Os_IntChannel_FLEXCAN_A_Buffer_15 (170U)
#define Os_Disable_FLEXCAN_A_Buffer_15()  ((volatile uint8 *)&OS_INTC_PSR0)[170U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_15()   ((volatile uint8 *)&OS_INTC_PSR0)[170U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_15 (170U)
#define Os_Disable_Can_IsrFCA_MB_15()  Os_Disable_FLEXCAN_A_Buffer_15()
#define Os_Enable_Can_IsrFCA_MB_15()   Os_Enable_FLEXCAN_A_Buffer_15()

#define Os_IntChannel_FLEXCAN_A_Buffer_16_31 (171U)
#define Os_Disable_FLEXCAN_A_Buffer_16_31()  ((volatile uint8 *)&OS_INTC_PSR0)[171U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_16_31()   ((volatile uint8 *)&OS_INTC_PSR0)[171U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_16_31 (171U)
#define Os_Disable_Can_IsrFCA_MB_16_31()  Os_Disable_FLEXCAN_A_Buffer_16_31()
#define Os_Enable_Can_IsrFCA_MB_16_31()   Os_Enable_FLEXCAN_A_Buffer_16_31()

#define Os_IntChannel_FLEXCAN_A_Buffer_32_63 (172U)
#define Os_Disable_FLEXCAN_A_Buffer_32_63()  ((volatile uint8 *)&OS_INTC_PSR0)[172U] = 0U
#define Os_Enable_FLEXCAN_A_Buffer_32_63()   ((volatile uint8 *)&OS_INTC_PSR0)[172U] = 0x000DU
#define Os_IntChannel_Can_IsrFCA_MB_32_63 (172U)
#define Os_Disable_Can_IsrFCA_MB_32_63()  Os_Disable_FLEXCAN_A_Buffer_32_63()
#define Os_Enable_Can_IsrFCA_MB_32_63()   Os_Enable_FLEXCAN_A_Buffer_32_63()

#define Os_IntChannel_FLEXCAN_C_Bus_Off (173U)
#define Os_Disable_FLEXCAN_C_Bus_Off()  ((volatile uint8 *)&OS_INTC_PSR0)[173U] = 0U
#define Os_Enable_FLEXCAN_C_Bus_Off()   ((volatile uint8 *)&OS_INTC_PSR0)[173U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_BO (173U)
#define Os_Disable_Can_IsrFCC_BO()  Os_Disable_FLEXCAN_C_Bus_Off()
#define Os_Enable_Can_IsrFCC_BO()   Os_Enable_FLEXCAN_C_Bus_Off()

#define Os_IntChannel_FLEXCAN_C_Error (174U)
#define Os_Disable_FLEXCAN_C_Error()  ((volatile uint8 *)&OS_INTC_PSR0)[174U] = 0U
#define Os_Enable_FLEXCAN_C_Error()   ((volatile uint8 *)&OS_INTC_PSR0)[174U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_ERR (174U)
#define Os_Disable_Can_IsrFCC_ERR()  Os_Disable_FLEXCAN_C_Error()
#define Os_Enable_Can_IsrFCC_ERR()   Os_Enable_FLEXCAN_C_Error()

#define Os_IntChannel_FLEXCAN_C_Buffer_0 (176U)
#define Os_Disable_FLEXCAN_C_Buffer_0()  ((volatile uint8 *)&OS_INTC_PSR0)[176U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_0()   ((volatile uint8 *)&OS_INTC_PSR0)[176U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_00 (176U)
#define Os_Disable_Can_IsrFCC_MB_00()  Os_Disable_FLEXCAN_C_Buffer_0()
#define Os_Enable_Can_IsrFCC_MB_00()   Os_Enable_FLEXCAN_C_Buffer_0()

#define Os_IntChannel_FLEXCAN_C_Buffer_1 (177U)
#define Os_Disable_FLEXCAN_C_Buffer_1()  ((volatile uint8 *)&OS_INTC_PSR0)[177U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_1()   ((volatile uint8 *)&OS_INTC_PSR0)[177U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_01 (177U)
#define Os_Disable_Can_IsrFCC_MB_01()  Os_Disable_FLEXCAN_C_Buffer_1()
#define Os_Enable_Can_IsrFCC_MB_01()   Os_Enable_FLEXCAN_C_Buffer_1()

#define Os_IntChannel_FLEXCAN_C_Buffer_2 (178U)
#define Os_Disable_FLEXCAN_C_Buffer_2()  ((volatile uint8 *)&OS_INTC_PSR0)[178U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_2()   ((volatile uint8 *)&OS_INTC_PSR0)[178U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_02 (178U)
#define Os_Disable_Can_IsrFCC_MB_02()  Os_Disable_FLEXCAN_C_Buffer_2()
#define Os_Enable_Can_IsrFCC_MB_02()   Os_Enable_FLEXCAN_C_Buffer_2()

#define Os_IntChannel_FLEXCAN_C_Buffer_3 (179U)
#define Os_Disable_FLEXCAN_C_Buffer_3()  ((volatile uint8 *)&OS_INTC_PSR0)[179U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_3()   ((volatile uint8 *)&OS_INTC_PSR0)[179U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_03 (179U)
#define Os_Disable_Can_IsrFCC_MB_03()  Os_Disable_FLEXCAN_C_Buffer_3()
#define Os_Enable_Can_IsrFCC_MB_03()   Os_Enable_FLEXCAN_C_Buffer_3()

#define Os_IntChannel_FLEXCAN_C_Buffer_4 (180U)
#define Os_Disable_FLEXCAN_C_Buffer_4()  ((volatile uint8 *)&OS_INTC_PSR0)[180U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_4()   ((volatile uint8 *)&OS_INTC_PSR0)[180U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_04 (180U)
#define Os_Disable_Can_IsrFCC_MB_04()  Os_Disable_FLEXCAN_C_Buffer_4()
#define Os_Enable_Can_IsrFCC_MB_04()   Os_Enable_FLEXCAN_C_Buffer_4()

#define Os_IntChannel_FLEXCAN_C_Buffer_5 (181U)
#define Os_Disable_FLEXCAN_C_Buffer_5()  ((volatile uint8 *)&OS_INTC_PSR0)[181U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_5()   ((volatile uint8 *)&OS_INTC_PSR0)[181U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_05 (181U)
#define Os_Disable_Can_IsrFCC_MB_05()  Os_Disable_FLEXCAN_C_Buffer_5()
#define Os_Enable_Can_IsrFCC_MB_05()   Os_Enable_FLEXCAN_C_Buffer_5()

#define Os_IntChannel_FLEXCAN_C_Buffer_6 (182U)
#define Os_Disable_FLEXCAN_C_Buffer_6()  ((volatile uint8 *)&OS_INTC_PSR0)[182U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_6()   ((volatile uint8 *)&OS_INTC_PSR0)[182U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_06 (182U)
#define Os_Disable_Can_IsrFCC_MB_06()  Os_Disable_FLEXCAN_C_Buffer_6()
#define Os_Enable_Can_IsrFCC_MB_06()   Os_Enable_FLEXCAN_C_Buffer_6()

#define Os_IntChannel_FLEXCAN_C_Buffer_7 (183U)
#define Os_Disable_FLEXCAN_C_Buffer_7()  ((volatile uint8 *)&OS_INTC_PSR0)[183U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_7()   ((volatile uint8 *)&OS_INTC_PSR0)[183U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_07 (183U)
#define Os_Disable_Can_IsrFCC_MB_07()  Os_Disable_FLEXCAN_C_Buffer_7()
#define Os_Enable_Can_IsrFCC_MB_07()   Os_Enable_FLEXCAN_C_Buffer_7()

#define Os_IntChannel_FLEXCAN_C_Buffer_8 (184U)
#define Os_Disable_FLEXCAN_C_Buffer_8()  ((volatile uint8 *)&OS_INTC_PSR0)[184U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_8()   ((volatile uint8 *)&OS_INTC_PSR0)[184U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_08 (184U)
#define Os_Disable_Can_IsrFCC_MB_08()  Os_Disable_FLEXCAN_C_Buffer_8()
#define Os_Enable_Can_IsrFCC_MB_08()   Os_Enable_FLEXCAN_C_Buffer_8()

#define Os_IntChannel_FLEXCAN_C_Buffer_9 (185U)
#define Os_Disable_FLEXCAN_C_Buffer_9()  ((volatile uint8 *)&OS_INTC_PSR0)[185U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_9()   ((volatile uint8 *)&OS_INTC_PSR0)[185U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_09 (185U)
#define Os_Disable_Can_IsrFCC_MB_09()  Os_Disable_FLEXCAN_C_Buffer_9()
#define Os_Enable_Can_IsrFCC_MB_09()   Os_Enable_FLEXCAN_C_Buffer_9()

#define Os_IntChannel_FLEXCAN_C_Buffer_10 (186U)
#define Os_Disable_FLEXCAN_C_Buffer_10()  ((volatile uint8 *)&OS_INTC_PSR0)[186U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_10()   ((volatile uint8 *)&OS_INTC_PSR0)[186U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_10 (186U)
#define Os_Disable_Can_IsrFCC_MB_10()  Os_Disable_FLEXCAN_C_Buffer_10()
#define Os_Enable_Can_IsrFCC_MB_10()   Os_Enable_FLEXCAN_C_Buffer_10()

#define Os_IntChannel_FLEXCAN_C_Buffer_11 (187U)
#define Os_Disable_FLEXCAN_C_Buffer_11()  ((volatile uint8 *)&OS_INTC_PSR0)[187U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_11()   ((volatile uint8 *)&OS_INTC_PSR0)[187U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_11 (187U)
#define Os_Disable_Can_IsrFCC_MB_11()  Os_Disable_FLEXCAN_C_Buffer_11()
#define Os_Enable_Can_IsrFCC_MB_11()   Os_Enable_FLEXCAN_C_Buffer_11()

#define Os_IntChannel_FLEXCAN_C_Buffer_12 (188U)
#define Os_Disable_FLEXCAN_C_Buffer_12()  ((volatile uint8 *)&OS_INTC_PSR0)[188U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_12()   ((volatile uint8 *)&OS_INTC_PSR0)[188U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_12 (188U)
#define Os_Disable_Can_IsrFCC_MB_12()  Os_Disable_FLEXCAN_C_Buffer_12()
#define Os_Enable_Can_IsrFCC_MB_12()   Os_Enable_FLEXCAN_C_Buffer_12()

#define Os_IntChannel_FLEXCAN_C_Buffer_13 (189U)
#define Os_Disable_FLEXCAN_C_Buffer_13()  ((volatile uint8 *)&OS_INTC_PSR0)[189U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_13()   ((volatile uint8 *)&OS_INTC_PSR0)[189U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_13 (189U)
#define Os_Disable_Can_IsrFCC_MB_13()  Os_Disable_FLEXCAN_C_Buffer_13()
#define Os_Enable_Can_IsrFCC_MB_13()   Os_Enable_FLEXCAN_C_Buffer_13()

#define Os_IntChannel_FLEXCAN_C_Buffer_14 (190U)
#define Os_Disable_FLEXCAN_C_Buffer_14()  ((volatile uint8 *)&OS_INTC_PSR0)[190U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_14()   ((volatile uint8 *)&OS_INTC_PSR0)[190U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_14 (190U)
#define Os_Disable_Can_IsrFCC_MB_14()  Os_Disable_FLEXCAN_C_Buffer_14()
#define Os_Enable_Can_IsrFCC_MB_14()   Os_Enable_FLEXCAN_C_Buffer_14()

#define Os_IntChannel_FLEXCAN_C_Buffer_15 (191U)
#define Os_Disable_FLEXCAN_C_Buffer_15()  ((volatile uint8 *)&OS_INTC_PSR0)[191U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_15()   ((volatile uint8 *)&OS_INTC_PSR0)[191U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_15 (191U)
#define Os_Disable_Can_IsrFCC_MB_15()  Os_Disable_FLEXCAN_C_Buffer_15()
#define Os_Enable_Can_IsrFCC_MB_15()   Os_Enable_FLEXCAN_C_Buffer_15()

#define Os_IntChannel_FLEXCAN_C_Buffer_16_31 (192U)
#define Os_Disable_FLEXCAN_C_Buffer_16_31()  ((volatile uint8 *)&OS_INTC_PSR0)[192U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_16_31()   ((volatile uint8 *)&OS_INTC_PSR0)[192U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_16_31 (192U)
#define Os_Disable_Can_IsrFCC_MB_16_31()  Os_Disable_FLEXCAN_C_Buffer_16_31()
#define Os_Enable_Can_IsrFCC_MB_16_31()   Os_Enable_FLEXCAN_C_Buffer_16_31()

#define Os_IntChannel_FLEXCAN_C_Buffer_32_63 (193U)
#define Os_Disable_FLEXCAN_C_Buffer_32_63()  ((volatile uint8 *)&OS_INTC_PSR0)[193U] = 0U
#define Os_Enable_FLEXCAN_C_Buffer_32_63()   ((volatile uint8 *)&OS_INTC_PSR0)[193U] = 0x000DU
#define Os_IntChannel_Can_IsrFCC_MB_32_63 (193U)
#define Os_Disable_Can_IsrFCC_MB_32_63()  Os_Disable_FLEXCAN_C_Buffer_32_63()
#define Os_Enable_Can_IsrFCC_MB_32_63()   Os_Enable_FLEXCAN_C_Buffer_32_63()

#define Os_IntChannel_FLEXCAN_D_Bus_Off (308U)
#define Os_Disable_FLEXCAN_D_Bus_Off()  ((volatile uint8 *)&OS_INTC_PSR0)[308U] = 0U
#define Os_Enable_FLEXCAN_D_Bus_Off()   ((volatile uint8 *)&OS_INTC_PSR0)[308U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_BO (308U)
#define Os_Disable_Can_IsrFCD_BO()  Os_Disable_FLEXCAN_D_Bus_Off()
#define Os_Enable_Can_IsrFCD_BO()   Os_Enable_FLEXCAN_D_Bus_Off()

#define Os_IntChannel_FLEXCAN_D_Error (309U)
#define Os_Disable_FLEXCAN_D_Error()  ((volatile uint8 *)&OS_INTC_PSR0)[309U] = 0U
#define Os_Enable_FLEXCAN_D_Error()   ((volatile uint8 *)&OS_INTC_PSR0)[309U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_ERR (309U)
#define Os_Disable_Can_IsrFCD_ERR()  Os_Disable_FLEXCAN_D_Error()
#define Os_Enable_Can_IsrFCD_ERR()   Os_Enable_FLEXCAN_D_Error()

#define Os_IntChannel_FLEXCAN_D_Buffer_0 (311U)
#define Os_Disable_FLEXCAN_D_Buffer_0()  ((volatile uint8 *)&OS_INTC_PSR0)[311U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_0()   ((volatile uint8 *)&OS_INTC_PSR0)[311U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_00 (311U)
#define Os_Disable_Can_IsrFCD_MB_00()  Os_Disable_FLEXCAN_D_Buffer_0()
#define Os_Enable_Can_IsrFCD_MB_00()   Os_Enable_FLEXCAN_D_Buffer_0()

#define Os_IntChannel_FLEXCAN_D_Buffer_1 (312U)
#define Os_Disable_FLEXCAN_D_Buffer_1()  ((volatile uint8 *)&OS_INTC_PSR0)[312U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_1()   ((volatile uint8 *)&OS_INTC_PSR0)[312U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_01 (312U)
#define Os_Disable_Can_IsrFCD_MB_01()  Os_Disable_FLEXCAN_D_Buffer_1()
#define Os_Enable_Can_IsrFCD_MB_01()   Os_Enable_FLEXCAN_D_Buffer_1()

#define Os_IntChannel_FLEXCAN_D_Buffer_2 (313U)
#define Os_Disable_FLEXCAN_D_Buffer_2()  ((volatile uint8 *)&OS_INTC_PSR0)[313U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_2()   ((volatile uint8 *)&OS_INTC_PSR0)[313U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_02 (313U)
#define Os_Disable_Can_IsrFCD_MB_02()  Os_Disable_FLEXCAN_D_Buffer_2()
#define Os_Enable_Can_IsrFCD_MB_02()   Os_Enable_FLEXCAN_D_Buffer_2()

#define Os_IntChannel_FLEXCAN_D_Buffer_3 (314U)
#define Os_Disable_FLEXCAN_D_Buffer_3()  ((volatile uint8 *)&OS_INTC_PSR0)[314U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_3()   ((volatile uint8 *)&OS_INTC_PSR0)[314U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_03 (314U)
#define Os_Disable_Can_IsrFCD_MB_03()  Os_Disable_FLEXCAN_D_Buffer_3()
#define Os_Enable_Can_IsrFCD_MB_03()   Os_Enable_FLEXCAN_D_Buffer_3()

#define Os_IntChannel_FLEXCAN_D_Buffer_4 (315U)
#define Os_Disable_FLEXCAN_D_Buffer_4()  ((volatile uint8 *)&OS_INTC_PSR0)[315U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_4()   ((volatile uint8 *)&OS_INTC_PSR0)[315U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_04 (315U)
#define Os_Disable_Can_IsrFCD_MB_04()  Os_Disable_FLEXCAN_D_Buffer_4()
#define Os_Enable_Can_IsrFCD_MB_04()   Os_Enable_FLEXCAN_D_Buffer_4()

#define Os_IntChannel_FLEXCAN_D_Buffer_5 (316U)
#define Os_Disable_FLEXCAN_D_Buffer_5()  ((volatile uint8 *)&OS_INTC_PSR0)[316U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_5()   ((volatile uint8 *)&OS_INTC_PSR0)[316U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_05 (316U)
#define Os_Disable_Can_IsrFCD_MB_05()  Os_Disable_FLEXCAN_D_Buffer_5()
#define Os_Enable_Can_IsrFCD_MB_05()   Os_Enable_FLEXCAN_D_Buffer_5()

#define Os_IntChannel_FLEXCAN_D_Buffer_6 (317U)
#define Os_Disable_FLEXCAN_D_Buffer_6()  ((volatile uint8 *)&OS_INTC_PSR0)[317U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_6()   ((volatile uint8 *)&OS_INTC_PSR0)[317U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_06 (317U)
#define Os_Disable_Can_IsrFCD_MB_06()  Os_Disable_FLEXCAN_D_Buffer_6()
#define Os_Enable_Can_IsrFCD_MB_06()   Os_Enable_FLEXCAN_D_Buffer_6()

#define Os_IntChannel_FLEXCAN_D_Buffer_7 (318U)
#define Os_Disable_FLEXCAN_D_Buffer_7()  ((volatile uint8 *)&OS_INTC_PSR0)[318U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_7()   ((volatile uint8 *)&OS_INTC_PSR0)[318U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_07 (318U)
#define Os_Disable_Can_IsrFCD_MB_07()  Os_Disable_FLEXCAN_D_Buffer_7()
#define Os_Enable_Can_IsrFCD_MB_07()   Os_Enable_FLEXCAN_D_Buffer_7()

#define Os_IntChannel_FLEXCAN_D_Buffer_8 (319U)
#define Os_Disable_FLEXCAN_D_Buffer_8()  ((volatile uint8 *)&OS_INTC_PSR0)[319U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_8()   ((volatile uint8 *)&OS_INTC_PSR0)[319U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_08 (319U)
#define Os_Disable_Can_IsrFCD_MB_08()  Os_Disable_FLEXCAN_D_Buffer_8()
#define Os_Enable_Can_IsrFCD_MB_08()   Os_Enable_FLEXCAN_D_Buffer_8()

#define Os_IntChannel_FLEXCAN_D_Buffer_9 (320U)
#define Os_Disable_FLEXCAN_D_Buffer_9()  ((volatile uint8 *)&OS_INTC_PSR0)[320U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_9()   ((volatile uint8 *)&OS_INTC_PSR0)[320U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_09 (320U)
#define Os_Disable_Can_IsrFCD_MB_09()  Os_Disable_FLEXCAN_D_Buffer_9()
#define Os_Enable_Can_IsrFCD_MB_09()   Os_Enable_FLEXCAN_D_Buffer_9()

#define Os_IntChannel_FLEXCAN_D_Buffer_10 (321U)
#define Os_Disable_FLEXCAN_D_Buffer_10()  ((volatile uint8 *)&OS_INTC_PSR0)[321U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_10()   ((volatile uint8 *)&OS_INTC_PSR0)[321U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_10 (321U)
#define Os_Disable_Can_IsrFCD_MB_10()  Os_Disable_FLEXCAN_D_Buffer_10()
#define Os_Enable_Can_IsrFCD_MB_10()   Os_Enable_FLEXCAN_D_Buffer_10()

#define Os_IntChannel_FLEXCAN_D_Buffer_11 (322U)
#define Os_Disable_FLEXCAN_D_Buffer_11()  ((volatile uint8 *)&OS_INTC_PSR0)[322U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_11()   ((volatile uint8 *)&OS_INTC_PSR0)[322U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_11 (322U)
#define Os_Disable_Can_IsrFCD_MB_11()  Os_Disable_FLEXCAN_D_Buffer_11()
#define Os_Enable_Can_IsrFCD_MB_11()   Os_Enable_FLEXCAN_D_Buffer_11()

#define Os_IntChannel_FLEXCAN_D_Buffer_12 (323U)
#define Os_Disable_FLEXCAN_D_Buffer_12()  ((volatile uint8 *)&OS_INTC_PSR0)[323U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_12()   ((volatile uint8 *)&OS_INTC_PSR0)[323U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_12 (323U)
#define Os_Disable_Can_IsrFCD_MB_12()  Os_Disable_FLEXCAN_D_Buffer_12()
#define Os_Enable_Can_IsrFCD_MB_12()   Os_Enable_FLEXCAN_D_Buffer_12()

#define Os_IntChannel_FLEXCAN_D_Buffer_13 (324U)
#define Os_Disable_FLEXCAN_D_Buffer_13()  ((volatile uint8 *)&OS_INTC_PSR0)[324U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_13()   ((volatile uint8 *)&OS_INTC_PSR0)[324U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_13 (324U)
#define Os_Disable_Can_IsrFCD_MB_13()  Os_Disable_FLEXCAN_D_Buffer_13()
#define Os_Enable_Can_IsrFCD_MB_13()   Os_Enable_FLEXCAN_D_Buffer_13()

#define Os_IntChannel_FLEXCAN_D_Buffer_14 (325U)
#define Os_Disable_FLEXCAN_D_Buffer_14()  ((volatile uint8 *)&OS_INTC_PSR0)[325U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_14()   ((volatile uint8 *)&OS_INTC_PSR0)[325U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_14 (325U)
#define Os_Disable_Can_IsrFCD_MB_14()  Os_Disable_FLEXCAN_D_Buffer_14()
#define Os_Enable_Can_IsrFCD_MB_14()   Os_Enable_FLEXCAN_D_Buffer_14()

#define Os_IntChannel_FLEXCAN_D_Buffer_15 (326U)
#define Os_Disable_FLEXCAN_D_Buffer_15()  ((volatile uint8 *)&OS_INTC_PSR0)[326U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_15()   ((volatile uint8 *)&OS_INTC_PSR0)[326U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_15 (326U)
#define Os_Disable_Can_IsrFCD_MB_15()  Os_Disable_FLEXCAN_D_Buffer_15()
#define Os_Enable_Can_IsrFCD_MB_15()   Os_Enable_FLEXCAN_D_Buffer_15()

#define Os_IntChannel_FLEXCAN_D_Buffer_16_31 (327U)
#define Os_Disable_FLEXCAN_D_Buffer_16_31()  ((volatile uint8 *)&OS_INTC_PSR0)[327U] = 0U
#define Os_Enable_FLEXCAN_D_Buffer_16_31()   ((volatile uint8 *)&OS_INTC_PSR0)[327U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_16_31 (327U)
#define Os_Disable_Can_IsrFCD_MB_16_31()  Os_Disable_FLEXCAN_D_Buffer_16_31()
#define Os_Enable_Can_IsrFCD_MB_16_31()   Os_Enable_FLEXCAN_D_Buffer_16_31()

#define Os_IntChannel_FLEXCAN_D_Buffers_32_63 (328U)
#define Os_Disable_FLEXCAN_D_Buffers_32_63()  ((volatile uint8 *)&OS_INTC_PSR0)[328U] = 0U
#define Os_Enable_FLEXCAN_D_Buffers_32_63()   ((volatile uint8 *)&OS_INTC_PSR0)[328U] = 0x000DU
#define Os_IntChannel_Can_IsrFCD_MB_32_63 (328U)
#define Os_Disable_Can_IsrFCD_MB_32_63()  Os_Disable_FLEXCAN_D_Buffers_32_63()
#define Os_Enable_Can_IsrFCD_MB_32_63()   Os_Enable_FLEXCAN_D_Buffers_32_63()

#define Os_IntChannel_ESCI_B_Combined (149U)
#define Os_Disable_ESCI_B_Combined()  ((volatile uint8 *)&OS_INTC_PSR0)[149U] = 0U
#define Os_Enable_ESCI_B_Combined()   ((volatile uint8 *)&OS_INTC_PSR0)[149U] = 0x000DU
#define Os_IntChannel_ESCI_B1_ISR (149U)
#define Os_Disable_ESCI_B1_ISR()  Os_Disable_ESCI_B_Combined()
#define Os_Enable_ESCI_B1_ISR()   Os_Enable_ESCI_B_Combined()

#define Os_IntChannel_ESCI_A_Combined (146U)
#define Os_Disable_ESCI_A_Combined()  ((volatile uint8 *)&OS_INTC_PSR0)[146U] = 0U
#define Os_Enable_ESCI_A_Combined()   ((volatile uint8 *)&OS_INTC_PSR0)[146U] = 0x000EU
#define Os_IntChannel_ESCI_A0_ISR (146U)
#define Os_Disable_ESCI_A0_ISR()  Os_Disable_ESCI_A_Combined()
#define Os_Enable_ESCI_A0_ISR()   Os_Enable_ESCI_A_Combined()

#define Os_IntChannel_ESCI_C_Combined (473U)
#define Os_Disable_ESCI_C_Combined()  ((volatile uint8 *)&OS_INTC_PSR0)[473U] = 0U
#define Os_Enable_ESCI_C_Combined()   ((volatile uint8 *)&OS_INTC_PSR0)[473U] = 0x000EU
#define Os_IntChannel_ESCI_C2_ISR (473U)
#define Os_Disable_ESCI_C2_ISR()  Os_Disable_ESCI_C_Combined()
#define Os_Enable_ESCI_C2_ISR()   Os_Enable_ESCI_C_Combined()

#define Os_IntChannel_ESCI_F_Combined (505U)
#define Os_Disable_ESCI_F_Combined()  ((volatile uint8 *)&OS_INTC_PSR0)[505U] = 0U
#define Os_Enable_ESCI_F_Combined()   ((volatile uint8 *)&OS_INTC_PSR0)[505U] = 0x000EU
#define Os_IntChannel_ESCI_F5_ISR (505U)
#define Os_Disable_ESCI_F5_ISR()  Os_Disable_ESCI_F_Combined()
#define Os_Enable_ESCI_F5_ISR()   Os_Enable_ESCI_F_Combined()

#define Os_IntChannel_PIT0 (301U)
#define Os_Disable_PIT0()  ((volatile uint8 *)&OS_INTC_PSR0)[301U] = 0U
#define Os_Enable_PIT0()   ((volatile uint8 *)&OS_INTC_PSR0)[301U] = 0x000FU
#define Os_IntChannel_Gpt_PIT_0_TIMER_0_ISR (301U)
#define Os_Disable_Gpt_PIT_0_TIMER_0_ISR()  Os_Disable_PIT0()
#define Os_Enable_Gpt_PIT_0_TIMER_0_ISR()   Os_Enable_PIT0()

#define Os_IntChannel_PIT_RTI (305U)
#define Os_Disable_PIT_RTI()  ((volatile uint8 *)&OS_INTC_PSR0)[305U] = 0U
#define Os_Enable_PIT_RTI()   ((volatile uint8 *)&OS_INTC_PSR0)[305U] = 0x000FU
#define Os_IntChannel_Gpt_PIT_0_TIMER_RTI_ISR (305U)
#define Os_Disable_Gpt_PIT_0_TIMER_RTI_ISR()  Os_Disable_PIT_RTI()
#define Os_Enable_Gpt_PIT_0_TIMER_RTI_ISR()   Os_Enable_PIT_RTI()


/* These macros can be used to disable or enable all of the
 * configured interrupts
 * [$TargetHT 237] [$TargetHT 238] [$TargetWR 275] [$TargetWR 276] [$TargetGHS 311] [$TargetGHS 312]
*/
#define Os_DisableAllConfiguredInterrupts() Os_Disable_Adc_Eqadc_EqadcACFifo0Empty();\
 Os_Disable_Adc_Eqadc_EqadcARFifo0Full();\
 Os_Disable_EMIOS_0_CH_16_ISR();\
 Os_Disable_EMIOS_0_CH_18_ISR();\
 Os_Disable_EMIOS_0_CH_19_ISR();\
 Os_Disable_EMIOS_0_CH_20_ISR();\
 Os_Disable_EMIOS_0_CH_21_ISR();\
 Os_Disable_Can_IsrFCB_BO();\
 Os_Disable_Can_IsrFCB_ERR();\
 Os_Disable_Can_IsrFCB_MB_00();\
 Os_Disable_Can_IsrFCB_MB_01();\
 Os_Disable_Can_IsrFCB_MB_02();\
 Os_Disable_Can_IsrFCB_MB_03();\
 Os_Disable_Can_IsrFCB_MB_04();\
 Os_Disable_Can_IsrFCB_MB_05();\
 Os_Disable_Can_IsrFCB_MB_06();\
 Os_Disable_Can_IsrFCB_MB_07();\
 Os_Disable_Can_IsrFCB_MB_08();\
 Os_Disable_Can_IsrFCB_MB_09();\
 Os_Disable_Can_IsrFCB_MB_10();\
 Os_Disable_Can_IsrFCB_MB_11();\
 Os_Disable_Can_IsrFCB_MB_12();\
 Os_Disable_Can_IsrFCB_MB_13();\
 Os_Disable_Can_IsrFCB_MB_14();\
 Os_Disable_Can_IsrFCB_MB_15();\
 Os_Disable_Can_IsrFCB_MB_16_31();\
 Os_Disable_Can_IsrFCB_MB_32_63();\
 Os_Disable_Can_IsrCombined_IL0_IL1();\
 Os_Disable_Can_IsrFCA_BO();\
 Os_Disable_Can_IsrFCA_ERR();\
 Os_Disable_Can_IsrFCA_MB_00();\
 Os_Disable_Can_IsrFCA_MB_01();\
 Os_Disable_Can_IsrFCA_MB_02();\
 Os_Disable_Can_IsrFCA_MB_03();\
 Os_Disable_Can_IsrFCA_MB_04();\
 Os_Disable_Can_IsrFCA_MB_05();\
 Os_Disable_Can_IsrFCA_MB_06();\
 Os_Disable_Can_IsrFCA_MB_07();\
 Os_Disable_Can_IsrFCA_MB_08();\
 Os_Disable_Can_IsrFCA_MB_09();\
 Os_Disable_Can_IsrFCA_MB_10();\
 Os_Disable_Can_IsrFCA_MB_11();\
 Os_Disable_Can_IsrFCA_MB_12();\
 Os_Disable_Can_IsrFCA_MB_13();\
 Os_Disable_Can_IsrFCA_MB_14();\
 Os_Disable_Can_IsrFCA_MB_15();\
 Os_Disable_Can_IsrFCA_MB_16_31();\
 Os_Disable_Can_IsrFCA_MB_32_63();\
 Os_Disable_Can_IsrFCC_BO();\
 Os_Disable_Can_IsrFCC_ERR();\
 Os_Disable_Can_IsrFCC_MB_00();\
 Os_Disable_Can_IsrFCC_MB_01();\
 Os_Disable_Can_IsrFCC_MB_02();\
 Os_Disable_Can_IsrFCC_MB_03();\
 Os_Disable_Can_IsrFCC_MB_04();\
 Os_Disable_Can_IsrFCC_MB_05();\
 Os_Disable_Can_IsrFCC_MB_06();\
 Os_Disable_Can_IsrFCC_MB_07();\
 Os_Disable_Can_IsrFCC_MB_08();\
 Os_Disable_Can_IsrFCC_MB_09();\
 Os_Disable_Can_IsrFCC_MB_10();\
 Os_Disable_Can_IsrFCC_MB_11();\
 Os_Disable_Can_IsrFCC_MB_12();\
 Os_Disable_Can_IsrFCC_MB_13();\
 Os_Disable_Can_IsrFCC_MB_14();\
 Os_Disable_Can_IsrFCC_MB_15();\
 Os_Disable_Can_IsrFCC_MB_16_31();\
 Os_Disable_Can_IsrFCC_MB_32_63();\
 Os_Disable_Can_IsrFCD_BO();\
 Os_Disable_Can_IsrFCD_ERR();\
 Os_Disable_Can_IsrFCD_MB_00();\
 Os_Disable_Can_IsrFCD_MB_01();\
 Os_Disable_Can_IsrFCD_MB_02();\
 Os_Disable_Can_IsrFCD_MB_03();\
 Os_Disable_Can_IsrFCD_MB_04();\
 Os_Disable_Can_IsrFCD_MB_05();\
 Os_Disable_Can_IsrFCD_MB_06();\
 Os_Disable_Can_IsrFCD_MB_07();\
 Os_Disable_Can_IsrFCD_MB_08();\
 Os_Disable_Can_IsrFCD_MB_09();\
 Os_Disable_Can_IsrFCD_MB_10();\
 Os_Disable_Can_IsrFCD_MB_11();\
 Os_Disable_Can_IsrFCD_MB_12();\
 Os_Disable_Can_IsrFCD_MB_13();\
 Os_Disable_Can_IsrFCD_MB_14();\
 Os_Disable_Can_IsrFCD_MB_15();\
 Os_Disable_Can_IsrFCD_MB_16_31();\
 Os_Disable_Can_IsrFCD_MB_32_63();\
 Os_Disable_ESCI_B1_ISR();\
 Os_Disable_ESCI_A0_ISR();\
 Os_Disable_ESCI_C2_ISR();\
 Os_Disable_ESCI_F5_ISR();\
 Os_Disable_Gpt_PIT_0_TIMER_0_ISR();\
 Os_Disable_Gpt_PIT_0_TIMER_RTI_ISR()

#define Os_EnableAllConfiguredInterrupts() Os_Enable_Adc_Eqadc_EqadcACFifo0Empty();\
 Os_Enable_Adc_Eqadc_EqadcARFifo0Full();\
 Os_Enable_EMIOS_0_CH_16_ISR();\
 Os_Enable_EMIOS_0_CH_18_ISR();\
 Os_Enable_EMIOS_0_CH_19_ISR();\
 Os_Enable_EMIOS_0_CH_20_ISR();\
 Os_Enable_EMIOS_0_CH_21_ISR();\
 Os_Enable_Can_IsrFCB_BO();\
 Os_Enable_Can_IsrFCB_ERR();\
 Os_Enable_Can_IsrFCB_MB_00();\
 Os_Enable_Can_IsrFCB_MB_01();\
 Os_Enable_Can_IsrFCB_MB_02();\
 Os_Enable_Can_IsrFCB_MB_03();\
 Os_Enable_Can_IsrFCB_MB_04();\
 Os_Enable_Can_IsrFCB_MB_05();\
 Os_Enable_Can_IsrFCB_MB_06();\
 Os_Enable_Can_IsrFCB_MB_07();\
 Os_Enable_Can_IsrFCB_MB_08();\
 Os_Enable_Can_IsrFCB_MB_09();\
 Os_Enable_Can_IsrFCB_MB_10();\
 Os_Enable_Can_IsrFCB_MB_11();\
 Os_Enable_Can_IsrFCB_MB_12();\
 Os_Enable_Can_IsrFCB_MB_13();\
 Os_Enable_Can_IsrFCB_MB_14();\
 Os_Enable_Can_IsrFCB_MB_15();\
 Os_Enable_Can_IsrFCB_MB_16_31();\
 Os_Enable_Can_IsrFCB_MB_32_63();\
 Os_Enable_Can_IsrCombined_IL0_IL1();\
 Os_Enable_Can_IsrFCA_BO();\
 Os_Enable_Can_IsrFCA_ERR();\
 Os_Enable_Can_IsrFCA_MB_00();\
 Os_Enable_Can_IsrFCA_MB_01();\
 Os_Enable_Can_IsrFCA_MB_02();\
 Os_Enable_Can_IsrFCA_MB_03();\
 Os_Enable_Can_IsrFCA_MB_04();\
 Os_Enable_Can_IsrFCA_MB_05();\
 Os_Enable_Can_IsrFCA_MB_06();\
 Os_Enable_Can_IsrFCA_MB_07();\
 Os_Enable_Can_IsrFCA_MB_08();\
 Os_Enable_Can_IsrFCA_MB_09();\
 Os_Enable_Can_IsrFCA_MB_10();\
 Os_Enable_Can_IsrFCA_MB_11();\
 Os_Enable_Can_IsrFCA_MB_12();\
 Os_Enable_Can_IsrFCA_MB_13();\
 Os_Enable_Can_IsrFCA_MB_14();\
 Os_Enable_Can_IsrFCA_MB_15();\
 Os_Enable_Can_IsrFCA_MB_16_31();\
 Os_Enable_Can_IsrFCA_MB_32_63();\
 Os_Enable_Can_IsrFCC_BO();\
 Os_Enable_Can_IsrFCC_ERR();\
 Os_Enable_Can_IsrFCC_MB_00();\
 Os_Enable_Can_IsrFCC_MB_01();\
 Os_Enable_Can_IsrFCC_MB_02();\
 Os_Enable_Can_IsrFCC_MB_03();\
 Os_Enable_Can_IsrFCC_MB_04();\
 Os_Enable_Can_IsrFCC_MB_05();\
 Os_Enable_Can_IsrFCC_MB_06();\
 Os_Enable_Can_IsrFCC_MB_07();\
 Os_Enable_Can_IsrFCC_MB_08();\
 Os_Enable_Can_IsrFCC_MB_09();\
 Os_Enable_Can_IsrFCC_MB_10();\
 Os_Enable_Can_IsrFCC_MB_11();\
 Os_Enable_Can_IsrFCC_MB_12();\
 Os_Enable_Can_IsrFCC_MB_13();\
 Os_Enable_Can_IsrFCC_MB_14();\
 Os_Enable_Can_IsrFCC_MB_15();\
 Os_Enable_Can_IsrFCC_MB_16_31();\
 Os_Enable_Can_IsrFCC_MB_32_63();\
 Os_Enable_Can_IsrFCD_BO();\
 Os_Enable_Can_IsrFCD_ERR();\
 Os_Enable_Can_IsrFCD_MB_00();\
 Os_Enable_Can_IsrFCD_MB_01();\
 Os_Enable_Can_IsrFCD_MB_02();\
 Os_Enable_Can_IsrFCD_MB_03();\
 Os_Enable_Can_IsrFCD_MB_04();\
 Os_Enable_Can_IsrFCD_MB_05();\
 Os_Enable_Can_IsrFCD_MB_06();\
 Os_Enable_Can_IsrFCD_MB_07();\
 Os_Enable_Can_IsrFCD_MB_08();\
 Os_Enable_Can_IsrFCD_MB_09();\
 Os_Enable_Can_IsrFCD_MB_10();\
 Os_Enable_Can_IsrFCD_MB_11();\
 Os_Enable_Can_IsrFCD_MB_12();\
 Os_Enable_Can_IsrFCD_MB_13();\
 Os_Enable_Can_IsrFCD_MB_14();\
 Os_Enable_Can_IsrFCD_MB_15();\
 Os_Enable_Can_IsrFCD_MB_16_31();\
 Os_Enable_Can_IsrFCD_MB_32_63();\
 Os_Enable_ESCI_B1_ISR();\
 Os_Enable_ESCI_A0_ISR();\
 Os_Enable_ESCI_C2_ISR();\
 Os_Enable_ESCI_F5_ISR();\
 Os_Enable_Gpt_PIT_0_TIMER_0_ISR();\
 Os_Enable_Gpt_PIT_0_TIMER_RTI_ISR()
#endif /* OS_DISABLEINTERRUPTS_H */
