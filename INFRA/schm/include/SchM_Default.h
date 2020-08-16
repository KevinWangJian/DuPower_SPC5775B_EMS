/*
 * SchM_Default.h
 *
 *  Created on: Jun 6, 2018
 *      Author: CIX2SGH
 */

#ifndef SCHM_DEFAULT_H
#define SCHM_DEFAULT_H

#include "Os.h"

#define SCHM_ENTER_DEFAULT()   SuspendAllInterrupts()
#define SCHM_EXIT_DEFAULT()    ResumeAllInterrupts()

#endif /* SCHM_DEFAULT_H */
