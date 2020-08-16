#ifndef SPIIF_H_
#define SPIIF_H_

#include "Std_Types.h"

extern uint8 afe_RxData[75];  //5*14+5=75
extern uint8 RxIdxIn=0;
//Hv
Std_ReturnType SpiIf_TransmitHv(uint16 txData, uint16 *rxData);

//SBC FS65XX
//Std_ReturnType SpiIf_TransmitSbc(uint8 txData, uint8 *rxData);
Std_ReturnType SpiIf_TransmitSbc(uint16 txData, uint32 *rxData);

//EEdata
Std_ReturnType SpiIf_TransmitEepReadData(uint8 *ins, uint32 insLen, uint8 *data, uint32 dataLen);
Std_ReturnType SpiIf_TransmitEepWriteData(uint8 *ins, uint32 insLen, uint8 *data, uint32 dataLen);
Std_ReturnType SpiIf_TransmitEepRegister(uint8 *txData, uint8 *rxData, uint32 len);

//RTC
Std_ReturnType SpiIf_TransmitRtc(uint8 *txData, uint8 *rxData, uint32 len);

//AFE MC33771
Std_ReturnType SpiIf_TransmitAfe(uint8 *txData, uint32 txLen, uint8 *rxData, uint32 rxLen);

//Tja1145
Std_ReturnType SpiIf_TransmitTJA1145(uint8 *txData, uint8 *rxData, uint32 len);

#endif /* SPIIF_H_ */
