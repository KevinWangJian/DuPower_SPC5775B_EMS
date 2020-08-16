#===================================================================================================
#
#    @file        Vector_vle_mcal.s
#    @version     2.0.1
#
#    @brief       AUTOSAR - Sample_app Interrupt Vector Table..
#    @details     Interrupt Vector Table.
#
#    Project      : AUTOSAR 4.0 MCAL
#    Platform     : PA
#    Peripheral   : 
#    Dependencies : Base Det Dem Port Dio Mcu Rte Wdg WdgIf CanIf LinIf FrIf EcuM
#
#    Autosar Version       : 4.0.3
#    Autosar Revision      : ASR_REL_4_0_REV_0003
#    Autosar Conf. Variant :
#    Software Version      : 2.0.1
#    Build Version         : MPC57xxP_sMCAL_2_0_1_RTM_ASR_REL_4_0_REV_0003_20171020
#
#    (c) Copyright 2006-2017 NXP Semiconductor
#    All Rights Reserved.
#
#    This file contains sample code only. It is not part of the production code deliverables.
#
#===================================================================================================
##===================================================================================================
# Note: The user interrupt service routines must create entry and exit code
# (either with assembly code or with __interrupt keyword). If not the code
# will not exit interrupts properly.

     #Set the compiler using generated file by BEART
    .set COMPILER_GHS,  0
    .set COMPILER_DIAB, 1
    .set COMPILER_CW,   2

    .set COMPILER_USED, COMPILER_DIAB

#===================================================================================================
# Compiler selection
#===================================================================================================
    .if COMPILER_USED == COMPILER_GHS
        .set C_GHS,  1         # 0/1 - off/on
        .set C_DIAB, 0         # 0/1 - off/on
        .set C_CW,   0         # 0/1 - off/on
        .set ALIGN_SIZE,   2
    .else
    .if COMPILER_USED == COMPILER_DIAB
        .set C_GHS,  0         # 0/1 - off/on
        .set C_DIAB, 1         # 0/1 - off/on
        .set C_CW,   0         # 0/1 - off/on
        .set ALIGN_SIZE,   2
    .else
    .if COMPILER_USED == COMPILER_CW
        .set C_GHS,  0         # 0/1 - off/on
        .set C_DIAB, 0         # 0/1 - off/on
        .set C_CW,   1         # 0/1 - off/on
        .set ALIGN_SIZE,   16
    .endif
    .endif
    .endif

    # set reset configuration half word
    .set    RCW, 0x095a0000
    #.set    RCW, 0x015a0000
    #.set    RCW, 0x015a015a

    # put reset configuration halfword and application start address into .rcw
    # section
    .if C_CW == 1
         .extern __start
         .section .rcw,rodata
         .long RCW, __start
    .else
         .extern _start
         .section ".rcw","ax"
         .long RCW, _start
    .endif
