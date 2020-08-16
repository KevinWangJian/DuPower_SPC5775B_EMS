################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSW/src/BSW/Gen/PduR/src/PduR_BufferPool.c \
../BSW/src/BSW/Gen/PduR/src/PduR_EnableDisableRouting.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_Com.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTransmit_FiFo.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTxConf_FiFo.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTxConf_NoBuf.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_IfRxInd.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_IpduM.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTransmit_Buf.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTransmit_FiFo.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTrigTx_Buf.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTrigTx_FiFo.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTxConf_Buf.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTxConf_FiFo.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpDcmTx.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpRx.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpTx.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpTxConf.c \
../BSW/src/BSW/Gen/PduR/src/PduR_GetBuffer.c \
../BSW/src/BSW/Gen/PduR/src/PduR_GetConfigurationId.c \
../BSW/src/BSW/Gen/PduR/src/PduR_GetVersionInfo.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Globals.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Init.c \
../BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_If.c \
../BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_Tp.c \
../BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_UpTx.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Multicast_LoTpTxToUp.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Multicast_Tp.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Multicast_UpToLo.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Multicast_UpTx.c \
../BSW/src/BSW/Gen/PduR/src/PduR_NullFunc_TrigTx.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Null_Com.c \
../BSW/src/BSW/Gen/PduR/src/PduR_Null_IpduM.c 

OBJS += \
./BSW/src/BSW/Gen/PduR/src/PduR_BufferPool.o \
./BSW/src/BSW/Gen/PduR/src/PduR_EnableDisableRouting.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_Com.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTransmit_FiFo.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTxConf_FiFo.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTxConf_NoBuf.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_IfRxInd.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_IpduM.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTransmit_Buf.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTransmit_FiFo.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTrigTx_Buf.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTrigTx_FiFo.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTxConf_Buf.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTxConf_FiFo.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpDcmTx.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpRx.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpTx.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpTxConf.o \
./BSW/src/BSW/Gen/PduR/src/PduR_GetBuffer.o \
./BSW/src/BSW/Gen/PduR/src/PduR_GetConfigurationId.o \
./BSW/src/BSW/Gen/PduR/src/PduR_GetVersionInfo.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Globals.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Init.o \
./BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_If.o \
./BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_Tp.o \
./BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_UpTx.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Multicast_LoTpTxToUp.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Multicast_Tp.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Multicast_UpToLo.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Multicast_UpTx.o \
./BSW/src/BSW/Gen/PduR/src/PduR_NullFunc_TrigTx.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Null_Com.o \
./BSW/src/BSW/Gen/PduR/src/PduR_Null_IpduM.o 

C_DEPS += \
./BSW/src/BSW/Gen/PduR/src/PduR_BufferPool.d \
./BSW/src/BSW/Gen/PduR/src/PduR_EnableDisableRouting.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_Com.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTransmit_FiFo.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTxConf_FiFo.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_DDIfTxConf_NoBuf.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_IfRxInd.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_IpduM.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTransmit_Buf.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTransmit_FiFo.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTrigTx_Buf.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTrigTx_FiFo.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTxConf_Buf.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TTIfTxConf_FiFo.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpDcmTx.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpRx.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpTx.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Gateway_TpTxConf.d \
./BSW/src/BSW/Gen/PduR/src/PduR_GetBuffer.d \
./BSW/src/BSW/Gen/PduR/src/PduR_GetConfigurationId.d \
./BSW/src/BSW/Gen/PduR/src/PduR_GetVersionInfo.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Globals.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Init.d \
./BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_If.d \
./BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_Tp.d \
./BSW/src/BSW/Gen/PduR/src/PduR_InvalidId_UpTx.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Multicast_LoTpTxToUp.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Multicast_Tp.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Multicast_UpToLo.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Multicast_UpTx.d \
./BSW/src/BSW/Gen/PduR/src/PduR_NullFunc_TrigTx.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Null_Com.d \
./BSW/src/BSW/Gen/PduR/src/PduR_Null_IpduM.d 


# Each subdirectory must supply rules for building sources it contributes
BSW/src/BSW/Gen/PduR/src/%.o: ../BSW/src/BSW/Gen/PduR/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Diab C Compiler'
	dcc -c -tPPCE200Z425N3VES:simple -I../BSW/integration/include -I../BSW/src/BSW/Gen/Bfx -I../BSW/src/BSW/Gen/Bfx/api -I../BSW/src/BSW/Gen/Bfx/src -I../BSW/src/BSW/Gen/BswM -I../BSW/src/BSW/Gen/BswM/api -I../BSW/src/BSW/Gen/BswM/src -I../BSW/src/BSW/Gen/CanIf -I../BSW/src/BSW/Gen/CanIf/api -I../BSW/src/BSW/Gen/CanIf/src -I../BSW/src/BSW/Gen/CanSM -I../BSW/src/BSW/Gen/CanSM/api -I../BSW/src/BSW/Gen/CanSM/src -I../BSW/src/BSW/Gen/Com -I../BSW/src/BSW/Gen/Com/api -I../BSW/src/BSW/Gen/Com/src -I../BSW/src/BSW/Gen/ComStack -I../BSW/src/BSW/Gen/Crc -I../BSW/src/BSW/Gen/Crc/api -I../BSW/src/BSW/Gen/Crc/src -I../BSW/src/BSW/Gen/Det -I../BSW/src/BSW/Gen/Det/api -I../BSW/src/BSW/Gen/Det/src -I../BSW/src/BSW/Gen/ComM -I../BSW/src/BSW/Gen/ComM/api -I../BSW/src/BSW/Gen/ComM/src -I../BSW/src/BSW/Gen/EcuM -I../BSW/src/BSW/Gen/EcuM/api -I../BSW/src/BSW/Gen/EcuM/src -I../BSW/src/BSW/Gen/IpduM -I../BSW/src/BSW/Gen/IpduM/api -I../BSW/src/BSW/Gen/IpduM/src -I../BSW/src/BSW/Gen/MemIf -I../BSW/src/BSW/Gen/MemIf/api -I../BSW/src/BSW/Gen/MemIf/src -I../BSW/src/BSW/Gen/NvM -I../BSW/src/BSW/Gen/NvM/api -I../BSW/src/BSW/Gen/NvM/src -I../BSW/src/BSW/Gen/PduR -I../BSW/src/BSW/Gen/PduR/api -I../BSW/src/BSW/Gen/PduR/src -I../BSW/src/BSW/Gen/Rba_DiagLib -I../BSW/src/BSW/Gen/Rba_DiagLib/api -I../BSW/src/BSW/Gen/Rba_DiagLib/src -I../BSW/src/BSW/Gen/WdgIf -I../BSW/src/BSW/Gen/WdgIf/api -I../BSW/src/BSW/Gen/WdgIf/src -I../BSW/src/BSW/Gen/WdgM -I../BSW/src/BSW/Gen/WdgM/api -I../BSW/src/BSW/Gen/WdgM/src -I../BSW/src/BSW/Gen/Xcp -I../BSW/src/BSW/Gen/Xcp/api -I../BSW/src/BSW/Gen/Xcp/src -I../BSW/src/BSW/Gen/EthIf -I../BSW/src/BSW/Gen/EthIf/api -I../BSW/src/BSW/Gen/EthIf/src -I"../INFRA\integration\include" -I../INFRA/memmap -I../INFRA/rba_BswSrv/api -I../INFRA/schm/include -I../RTE/gen -I../RTE/include -I../CDD/Common -I../CDD/ComAb -I../CDD/IoAb -I../CDD/Afe -I../CDD/M95640 -I../CDD/rtc -I../CDD/sbc -I../ASW/App_SWC/ASW_RTE -I../ASW/App_SWC/Common -I../ASW/App_SWC/Modules -I../BSW/src/BSW/Gen/J1939Tp -I../BSW/src/BSW/Gen/J1939Tp/api -I../BSW/src/BSW/Gen/J1939Tp/src -I../Targets/SPC5775B/RTAOS/output/include -I../Targets/SPC5775B/MCAL/integration/include -I../Targets/SPC5775B/MCAL/Gen/include -I../Targets/SPC5775B/MCAL/modules/Adc/include -I../Targets/SPC5775B/MCAL/modules/Dio/include -I../Targets/SPC5775B/MCAL/modules/Gpt/include -I../Targets/SPC5775B/MCAL/modules/Mcu/include -I../Targets/SPC5775B/MCAL/modules/Port/include -I../Targets/SPC5775B/RTAOS/integration/include -I../Targets/SPC5775B/MCAL/modules/Rte/include -I../Targets/SPC5775B/MCAL/modules/Mcl/include -I../Targets/SPC5775B/MCAL/modules/Can/include -I../Targets/SPC5775B/MCAL/modules/Spi/include -I../Targets/SPC5775B/MCAL/modules/Esci/include -I../Targets/SPC5775B/MCAL/modules/Pwm/include -I../Targets/SPC5775B/MCAL/modules/Fls/include -I../Targets/SPC5775B/MCAL/modules/Mcan/include -I../Targets/SPC5775B/MCAL/modules/Eth/include -I../Targets/SPC5775B/MCAL/modules/EthIf/include -I../CDD/esci -I../CDD/mtcard -I../CDD/TPanel -I../CDD/PowerEnergyMeter -I../CDD/DCDC -I../CDD/Fls -I../CDD/McanComm -I../CDD/Diag -I../CDD/StateMachine -I../CDD/DP83822 -I../CDD/EthComm -I../CDD/SJA1105 -I../CDD/TJA1101 -I../BSW/src/BSW/Gen/EthSM -I../BSW/src/BSW/Gen/EthSM/api -I../BSW/src/BSW/Gen/EthSM/src -I../BSW/src/BSW/Gen/EthTrcv -I../BSW/src/BSW/Gen/EthTrcv/api -I../BSW/src/BSW/Gen/EthTrcv/src -I../BSW/src/BSW/Gen/Rba_EthArp -I../BSW/src/BSW/Gen/Rba_EthArp/api -I../BSW/src/BSW/Gen/Rba_EthArp/src -I../BSW/src/BSW/Gen/Rba_EthICMP -I../BSW/src/BSW/Gen/Rba_EthICMP/api -I../BSW/src/BSW/Gen/Rba_EthICMP/src -I../BSW/src/BSW/Gen/Rba_EthIPv4 -I../BSW/src/BSW/Gen/Rba_EthIPv4/api -I../BSW/src/BSW/Gen/Rba_EthIPv4/src -I../BSW/src/BSW/Gen/Rba_EthTcp -I../BSW/src/BSW/Gen/Rba_EthTcp/api -I../BSW/src/BSW/Gen/Rba_EthTcp/src -I../BSW/src/BSW/Gen/Rba_EthUdp -I../BSW/src/BSW/Gen/Rba_EthUdp/api -I../BSW/src/BSW/Gen/Rba_EthUdp/src -I../BSW/src/BSW/Gen/SoAd -I../BSW/src/BSW/Gen/SoAd/api -I../BSW/src/BSW/Gen/SoAd/src -I../BSW/src/BSW/Gen/TcpIp -I../BSW/src/BSW/Gen/TcpIp/api -I../BSW/src/BSW/Gen/TcpIp/src -I../BSW/src/BSW/Gen/CanTp -I../BSW/src/BSW/Gen/CanTp/api -I../BSW/src/BSW/Gen/CanTp/src -I../BSW/src/BSW/Gen/Dcm -I../BSW/src/BSW/Gen/Dcm/api -I../BSW/src/BSW/Gen/Dcm/src -I../BSW/src/BSW/Gen/Dem -I../BSW/src/BSW/Gen/Dem/api -I../BSW/src/BSW/Gen/Dem/src -I../BSW/src/BSW/Gen/FiM -I../BSW/src/BSW/Gen/FiM/api -I../BSW/src/BSW/Gen/FiM/src -I../BSW/integration/src/DcmAppl -I../BSW/src/BSW/Gen/Fee -I../BSW/src/BSW/Gen/Fee/api -I../BSW/src/BSW/Gen/Fee/src -I../BSW/src/BSW/Gen/Rba_FeeFs1/api -I../BSW/src/BSW/Gen/Rba_FeeFs1/src -I../ASW/NvM_SWC/api -I../ASW/Diag_SWC/api -I../CDD/CCV -I../CDD/TBOXComm -I../BSW/src/BSW/Gen/Ea -I../BSW/src/BSW/Gen/Ea/api -I../BSW/src/BSW/Gen/Ea/src -DDISABLE_MCAL_INTERMODULE_ASR_CHECK -g3 -Xlint=0x1100 -Xlink-time-lint -Xforce-prototypes -Xmismatch-warning=2 -Xsmall-const=0 -Xsmall-data=8 -Wa,-Xisa-vle -Xpass-source -Xlink-time-lint -Xdebug-local-cie -Xnested-interrupts -Xforce-declarations -Xaddr-sdata=0x11 -Xaddr-sconst=0x11 -Xsmall-data=0 -g3 -Xdebug-inline-on -Xmake-dependency=0x5 -o $@ $<
	@echo 'Finished building: $<'
	@echo ' '


