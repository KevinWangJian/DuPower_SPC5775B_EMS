#pragma once
#include "typedefs.h"
#include "mt_card.h"

extern uint8_t cardnum[8];

extern void MAINPROCESS();

extern void Testfun();

void STARTFIND();

void SETPIN(uint32_t pin_par);

void SETMONEY(uint32_t money_par);

uint32_t GETSTEP();

uint32_t GETERROR_CODE();

extern void TimeTaskcard();
