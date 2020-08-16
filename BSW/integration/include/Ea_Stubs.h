/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */

#ifndef EA_STUBS_H
#define EA_STUBS_H

#include "Eep.h"

#define EEP_BASE_ADDRESS			0
#define EEP_ERASE_VALUE				0xFF

/* Define EEP_TOTAL_SIZE to be EEP_SIZE. EEP_SIZE is defined in AUTOSAR specification*/
#define EEP_TOTAL_SIZE             EEP_SIZE

/* EEP_LAYOUT_HEADER_SIZE is used as the data length to be read to/written from Ea_Rb_MigHeader_st
 * Set it to 16 so that it is equal to the size of Ea_Rb_MigHeader_tst structure.
 * This macro definition should not be changed.
 */
#define EEP_LAYOUT_HEADER_SIZE     16U

extern Eep_LengthType Eep_Rb_RealSize_u32;
extern MemIf_ModeType Eep_Mode;

void Spi_MainFunction_Handling(void);

#endif
