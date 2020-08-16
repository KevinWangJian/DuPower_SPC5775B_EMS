################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/src/BSW/Gen/NvM/src/NvM.c \
../BSW/src/BSW/Gen/NvM/src/NvM_BlockData.c \
../BSW/src/BSW/Gen/NvM/src/NvM_CancelWriteAll.c \
../BSW/src/BSW/Gen/NvM/src/NvM_EraseNvBlock.c \
../BSW/src/BSW/Gen/NvM/src/NvM_ErrorDetection.c \
../BSW/src/BSW/Gen/NvM/src/NvM_GetDataIndex.c \
../BSW/src/BSW/Gen/NvM/src/NvM_GetErrorStatus.c \
../BSW/src/BSW/Gen/NvM/src/NvM_GetVersionInfo.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Init.c \
../BSW/src/BSW/Gen/NvM/src/NvM_InvalidateNvBlock.c \
../BSW/src/BSW/Gen/NvM/src/NvM_MainFunction.c \
../BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionArbitrate.c \
../BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionJobStart.c \
../BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionPollResult.c \
../BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionResultEval.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Queue.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetDataIndex.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetErrorStatus.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetMigrationResult.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxInvalidateNvBlock.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxReadBlock.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxSetDataIndex.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxWriteBlock.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_FirstInitAll.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetActiveService.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetBlockId.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetBlockIdCausingLastDetError.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetMigrationResult.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetNvBlockLength.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetRequestType.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetStatus.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_SetWriteAllTrigger.c \
../BSW/src/BSW/Gen/NvM/src/NvM_Rb_WriteMon.c \
../BSW/src/BSW/Gen/NvM/src/NvM_ReadAll.c \
../BSW/src/BSW/Gen/NvM/src/NvM_ReadBlock.c \
../BSW/src/BSW/Gen/NvM/src/NvM_RestoreBlockDefaults.c \
../BSW/src/BSW/Gen/NvM/src/NvM_SetBlockLockStatus.c \
../BSW/src/BSW/Gen/NvM/src/NvM_SetBlockProtection.c \
../BSW/src/BSW/Gen/NvM/src/NvM_SetDataIndex.c \
../BSW/src/BSW/Gen/NvM/src/NvM_SetRamBlockStatus.c \
../BSW/src/BSW/Gen/NvM/src/NvM_ValidateAll.c \
../BSW/src/BSW/Gen/NvM/src/NvM_WriteAll.c \
../BSW/src/BSW/Gen/NvM/src/NvM_WriteBlock.c 

OBJS += \
./BSW/src/BSW/Gen/NvM/src/NvM.o \
./BSW/src/BSW/Gen/NvM/src/NvM_BlockData.o \
./BSW/src/BSW/Gen/NvM/src/NvM_CancelWriteAll.o \
./BSW/src/BSW/Gen/NvM/src/NvM_EraseNvBlock.o \
./BSW/src/BSW/Gen/NvM/src/NvM_ErrorDetection.o \
./BSW/src/BSW/Gen/NvM/src/NvM_GetDataIndex.o \
./BSW/src/BSW/Gen/NvM/src/NvM_GetErrorStatus.o \
./BSW/src/BSW/Gen/NvM/src/NvM_GetVersionInfo.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Init.o \
./BSW/src/BSW/Gen/NvM/src/NvM_InvalidateNvBlock.o \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunction.o \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionArbitrate.o \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionJobStart.o \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionPollResult.o \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionResultEval.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Queue.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetDataIndex.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetErrorStatus.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetMigrationResult.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxInvalidateNvBlock.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxReadBlock.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxSetDataIndex.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxWriteBlock.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_FirstInitAll.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetActiveService.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetBlockId.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetBlockIdCausingLastDetError.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetMigrationResult.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetNvBlockLength.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetRequestType.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetStatus.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_SetWriteAllTrigger.o \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_WriteMon.o \
./BSW/src/BSW/Gen/NvM/src/NvM_ReadAll.o \
./BSW/src/BSW/Gen/NvM/src/NvM_ReadBlock.o \
./BSW/src/BSW/Gen/NvM/src/NvM_RestoreBlockDefaults.o \
./BSW/src/BSW/Gen/NvM/src/NvM_SetBlockLockStatus.o \
./BSW/src/BSW/Gen/NvM/src/NvM_SetBlockProtection.o \
./BSW/src/BSW/Gen/NvM/src/NvM_SetDataIndex.o \
./BSW/src/BSW/Gen/NvM/src/NvM_SetRamBlockStatus.o \
./BSW/src/BSW/Gen/NvM/src/NvM_ValidateAll.o \
./BSW/src/BSW/Gen/NvM/src/NvM_WriteAll.o \
./BSW/src/BSW/Gen/NvM/src/NvM_WriteBlock.o 

C_DEPS += \
./BSW/src/BSW/Gen/NvM/src/NvM.d \
./BSW/src/BSW/Gen/NvM/src/NvM_BlockData.d \
./BSW/src/BSW/Gen/NvM/src/NvM_CancelWriteAll.d \
./BSW/src/BSW/Gen/NvM/src/NvM_EraseNvBlock.d \
./BSW/src/BSW/Gen/NvM/src/NvM_ErrorDetection.d \
./BSW/src/BSW/Gen/NvM/src/NvM_GetDataIndex.d \
./BSW/src/BSW/Gen/NvM/src/NvM_GetErrorStatus.d \
./BSW/src/BSW/Gen/NvM/src/NvM_GetVersionInfo.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Init.d \
./BSW/src/BSW/Gen/NvM/src/NvM_InvalidateNvBlock.d \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunction.d \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionArbitrate.d \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionJobStart.d \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionPollResult.d \
./BSW/src/BSW/Gen/NvM/src/NvM_MainFunctionResultEval.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Queue.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetDataIndex.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetErrorStatus.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxGetMigrationResult.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxInvalidateNvBlock.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxReadBlock.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxSetDataIndex.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_AuxWriteBlock.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_FirstInitAll.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetActiveService.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetBlockId.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetBlockIdCausingLastDetError.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetMigrationResult.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetNvBlockLength.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetRequestType.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_GetStatus.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_SetWriteAllTrigger.d \
./BSW/src/BSW/Gen/NvM/src/NvM_Rb_WriteMon.d \
./BSW/src/BSW/Gen/NvM/src/NvM_ReadAll.d \
./BSW/src/BSW/Gen/NvM/src/NvM_ReadBlock.d \
./BSW/src/BSW/Gen/NvM/src/NvM_RestoreBlockDefaults.d \
./BSW/src/BSW/Gen/NvM/src/NvM_SetBlockLockStatus.d \
./BSW/src/BSW/Gen/NvM/src/NvM_SetBlockProtection.d \
./BSW/src/BSW/Gen/NvM/src/NvM_SetDataIndex.d \
./BSW/src/BSW/Gen/NvM/src/NvM_SetRamBlockStatus.d \
./BSW/src/BSW/Gen/NvM/src/NvM_ValidateAll.d \
./BSW/src/BSW/Gen/NvM/src/NvM_WriteAll.d \
./BSW/src/BSW/Gen/NvM/src/NvM_WriteBlock.d 


# Each subdirectory must supply rules for building sources it contributes
BSW/src/BSW/Gen/NvM/src/%.o: ../BSW/src/BSW/Gen/NvM/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Diab C Compiler'
	dcc -c -tPPCE200Z425N3VES:simple -I../BSW/integration/include -I../BSW/src/BSW/Gen/Bfx -I../BSW/src/BSW/Gen/Bfx/api -I../BSW/src/BSW/Gen/Bfx/src -I../BSW/src/BSW/Gen/BswM -I../BSW/src/BSW/Gen/BswM/api -I../BSW/src/BSW/Gen/BswM/src -I../BSW/src/BSW/Gen/CanIf -I../BSW/src/BSW/Gen/CanIf/api -I../BSW/src/BSW/Gen/CanIf/src -I../BSW/src/BSW/Gen/CanSM -I../BSW/src/BSW/Gen/CanSM/api -I../BSW/src/BSW/Gen/CanSM/src -I../BSW/src/BSW/Gen/Com -I../BSW/src/BSW/Gen/Com/api -I../BSW/src/BSW/Gen/Com/src -I../BSW/src/BSW/Gen/ComStack -I../BSW/src/BSW/Gen/Crc -I../BSW/src/BSW/Gen/Crc/api -I../BSW/src/BSW/Gen/Crc/src -I../BSW/src/BSW/Gen/Det -I../BSW/src/BSW/Gen/Det/api -I../BSW/src/BSW/Gen/Det/src -I../BSW/src/BSW/Gen/ComM -I../BSW/src/BSW/Gen/ComM/api -I../BSW/src/BSW/Gen/ComM/src -I../BSW/src/BSW/Gen/EcuM -I../BSW/src/BSW/Gen/EcuM/api -I../BSW/src/BSW/Gen/EcuM/src -I../BSW/src/BSW/Gen/IpduM -I../BSW/src/BSW/Gen/IpduM/api -I../BSW/src/BSW/Gen/IpduM/src -I../BSW/src/BSW/Gen/MemIf -I../BSW/src/BSW/Gen/MemIf/api -I../BSW/src/BSW/Gen/MemIf/src -I../BSW/src/BSW/Gen/NvM -I../BSW/src/BSW/Gen/NvM/api -I../BSW/src/BSW/Gen/NvM/src -I../BSW/src/BSW/Gen/PduR -I../BSW/src/BSW/Gen/PduR/api -I../BSW/src/BSW/Gen/PduR/src -I../BSW/src/BSW/Gen/Rba_DiagLib -I../BSW/src/BSW/Gen/Rba_DiagLib/api -I../BSW/src/BSW/Gen/Rba_DiagLib/src -I../BSW/src/BSW/Gen/WdgIf -I../BSW/src/BSW/Gen/WdgIf/api -I../BSW/src/BSW/Gen/WdgIf/src -I../BSW/src/BSW/Gen/WdgM -I../BSW/src/BSW/Gen/WdgM/api -I../BSW/src/BSW/Gen/WdgM/src -I../BSW/src/BSW/Gen/Xcp -I../BSW/src/BSW/Gen/Xcp/api -I../BSW/src/BSW/Gen/Xcp/src -I../BSW/src/BSW/Gen/EthIf -I../BSW/src/BSW/Gen/EthIf/api -I../BSW/src/BSW/Gen/EthIf/src -I"../INFRA\integration\include" -I../INFRA/memmap -I../INFRA/rba_BswSrv/api -I../INFRA/schm/include -I../RTE/gen -I../RTE/include -I../CDD/Common -I../CDD/ComAb -I../CDD/IoAb -I../CDD/Afe -I../CDD/M95640 -I../CDD/rtc -I../CDD/sbc -I../ASW/App_SWC/ASW_RTE -I../ASW/App_SWC/Common -I../ASW/App_SWC/Modules -I../BSW/src/BSW/Gen/J1939Tp -I../BSW/src/BSW/Gen/J1939Tp/api -I../BSW/src/BSW/Gen/J1939Tp/src -I../Targets/SPC5775B/RTAOS/output/include -I../Targets/SPC5775B/MCAL/integration/include -I../Targets/SPC5775B/MCAL/Gen/include -I../Targets/SPC5775B/MCAL/modules/Adc/include -I../Targets/SPC5775B/MCAL/modules/Dio/include -I../Targets/SPC5775B/MCAL/modules/Gpt/include -I../Targets/SPC5775B/MCAL/modules/Mcu/include -I../Targets/SPC5775B/MCAL/modules/Port/include -I../Targets/SPC5775B/RTAOS/integration/include -I../Targets/SPC5775B/MCAL/modules/Rte/include -I../Targets/SPC5775B/MCAL/modules/Mcl/include -I../Targets/SPC5775B/MCAL/modules/Can/include -I../Targets/SPC5775B/MCAL/modules/Spi/include -I../Targets/SPC5775B/MCAL/modules/Esci/include -I../Targets/SPC5775B/MCAL/modules/Pwm/include -I../Targets/SPC5775B/MCAL/modules/Fls/include -I../Targets/SPC5775B/MCAL/modules/Mcan/include -I../Targets/SPC5775B/MCAL/modules/Eth/include -I../Targets/SPC5775B/MCAL/modules/EthIf/include -I../CDD/esci -I../CDD/mtcard -I../CDD/TPanel -I../CDD/PowerEnergyMeter -I../CDD/DCDC -I../CDD/Fls -I../CDD/McanComm -I../CDD/Diag -I../CDD/StateMachine -I../CDD/DP83822 -I../CDD/EthComm -I../CDD/SJA1105 -I../CDD/TJA1101 -I../BSW/src/BSW/Gen/EthSM -I../BSW/src/BSW/Gen/EthSM/api -I../BSW/src/BSW/Gen/EthSM/src -I../BSW/src/BSW/Gen/EthTrcv -I../BSW/src/BSW/Gen/EthTrcv/api -I../BSW/src/BSW/Gen/EthTrcv/src -I../BSW/src/BSW/Gen/Rba_EthArp -I../BSW/src/BSW/Gen/Rba_EthArp/api -I../BSW/src/BSW/Gen/Rba_EthArp/src -I../BSW/src/BSW/Gen/Rba_EthICMP -I../BSW/src/BSW/Gen/Rba_EthICMP/api -I../BSW/src/BSW/Gen/Rba_EthICMP/src -I../BSW/src/BSW/Gen/Rba_EthIPv4 -I../BSW/src/BSW/Gen/Rba_EthIPv4/api -I../BSW/src/BSW/Gen/Rba_EthIPv4/src -I../BSW/src/BSW/Gen/Rba_EthTcp -I../BSW/src/BSW/Gen/Rba_EthTcp/api -I../BSW/src/BSW/Gen/Rba_EthTcp/src -I../BSW/src/BSW/Gen/Rba_EthUdp -I../BSW/src/BSW/Gen/Rba_EthUdp/api -I../BSW/src/BSW/Gen/Rba_EthUdp/src -I../BSW/src/BSW/Gen/SoAd -I../BSW/src/BSW/Gen/SoAd/api -I../BSW/src/BSW/Gen/SoAd/src -I../BSW/src/BSW/Gen/TcpIp -I../BSW/src/BSW/Gen/TcpIp/api -I../BSW/src/BSW/Gen/TcpIp/src -I../BSW/src/BSW/Gen/CanTp -I../BSW/src/BSW/Gen/CanTp/api -I../BSW/src/BSW/Gen/CanTp/src -I../BSW/src/BSW/Gen/Dcm -I../BSW/src/BSW/Gen/Dcm/api -I../BSW/src/BSW/Gen/Dcm/src -I../BSW/src/BSW/Gen/Dem -I../BSW/src/BSW/Gen/Dem/api -I../BSW/src/BSW/Gen/Dem/src -I../BSW/src/BSW/Gen/FiM -I../BSW/src/BSW/Gen/FiM/api -I../BSW/src/BSW/Gen/FiM/src -I../BSW/integration/src/DcmAppl -I../BSW/src/BSW/Gen/Fee -I../BSW/src/BSW/Gen/Fee/api -I../BSW/src/BSW/Gen/Fee/src -I../BSW/src/BSW/Gen/Rba_FeeFs1/api -I../BSW/src/BSW/Gen/Rba_FeeFs1/src -I../ASW/NvM_SWC/api -I../ASW/Diag_SWC/api -I../CDD/CCV -I../CDD/TBOXComm -I../BSW/src/BSW/Gen/Ea -I../BSW/src/BSW/Gen/Ea/api -I../BSW/src/BSW/Gen/Ea/src -DDISABLE_MCAL_INTERMODULE_ASR_CHECK -g3 -Xlint=0x1100 -Xlink-time-lint -Xforce-prototypes -Xmismatch-warning=2 -Xsmall-const=0 -Xsmall-data=8 -Wa,-Xisa-vle -Xpass-source -Xlink-time-lint -Xdebug-local-cie -Xnested-interrupts -Xforce-declarations -Xaddr-sdata=0x11 -Xaddr-sconst=0x11 -Xsmall-data=0 -g3 -Xdebug-inline-on -Xmake-dependency=0x5 -o $@ $<
	@echo 'Finished building: $<'
	@echo ' '


