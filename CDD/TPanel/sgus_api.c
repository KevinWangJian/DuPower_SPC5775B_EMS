
#include "sgus_api.h"

sgus_txqueue_t SGUS_TXQueue;

uint8_t SGUS_CRCHangFlag = FALSE;

void SGUS_SetTxQueue(uint8_t indextype, uint8_t indexvalue, uint8_t length)
{
    SGUS_TXQueue.type[SGUS_TXQueue.head] = indextype;
    SGUS_TXQueue.queues[SGUS_TXQueue.head] = indexvalue;
    SGUS_TXQueue.length[SGUS_TXQueue.head] = length;

    if(++SGUS_TXQueue.head >= QUEUE_SIZE)
    {
        SGUS_TXQueue.head = 0;
    }
    SGUS_TXQueue.count++;
}


void SGUS_GetTxQueue(uint8_t *indextype, uint8_t *indexvalue, uint8_t *length, uint8_t *valid)
{
    if(0 != SGUS_TXQueue.count)
    {
        *indextype = SGUS_TXQueue.type[SGUS_TXQueue.tail];
        *indexvalue = SGUS_TXQueue.queues[SGUS_TXQueue.tail];
        *length = SGUS_TXQueue.length[SGUS_TXQueue.tail];

        if(++SGUS_TXQueue.tail >= QUEUE_SIZE)
        {
            SGUS_TXQueue.tail = 0;
        }
        SGUS_TXQueue.count--;
        *valid = TRUE;
    }
    else
    {
        SGUS_TXQueue.head = 0;
        SGUS_TXQueue.tail = 0;
        *valid = FALSE;
    }
}

uint8_t SGUS_EnableCRC(void)
{
    uint8_t tmp;
    sgus_regdata_t * regdata;

    if(TRUE == SGUS_CRCHangFlag)
    {
        return 1;
    }
    if(FALSE == SGUS_EnableCRCFlag)
    {
        regdata = SGUS_GetRxRegData();
        tmp = regdata->tfconfig_r2;
        regdata = SGUS_GetTxRegData();
    
        tmp |= 0x10;
        regdata->tfconfig_r2 = tmp;
        SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_TFConfig_R2, 1);
        tmp = 0xA5;
        regdata->tfconfigenable = tmp;
        SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_TFConfigEnable, 1);
        SGUS_CRCHangFlag = TRUE;
    }

    return 0;
}

uint8_t SGUS_DisableCRC(void)
{
    uint8_t tmp;
    sgus_regdata_t * regdata;

    if(TRUE == SGUS_CRCHangFlag)
    {
        return 1;
    }
    
    if(FALSE == SGUS_EnableCRCFlag)
    {
        regdata = SGUS_GetRxRegData();
        tmp = regdata->tfconfig_r2;
        regdata = SGUS_GetTxRegData();
    
        tmp &= 0xEF;
        regdata->tfconfig_r2 = tmp;
        SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_TFConfig_R2, 1);
        tmp = 0xA5;
        regdata->tfconfigenable = tmp;
        SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_TFConfigEnable, 1);
        SGUS_CRCHangFlag = TRUE;
    }

    return 0;
}

uint8_t SGUS_GetCRCState(void)
{
    return SGUS_EnableCRCFlag;
}



uint8_t SGUS_GetVersion(sgus_version_t * version)
{
    sgus_regdata_t * regdata = SGUS_GetRxRegData();
    
    *version = (sgus_version_t)regdata->version;

    return 0;
}


uint8_t SGUS_SetBacklight(uint8_t lightvalue)
{
    sgus_regdata_t * regdata = SGUS_GetTxRegData();

    if(0x3F < lightvalue)
    {
        lightvalue  = 0x3F;
    }


    regdata->ledlm = lightvalue;
    SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_LedLm, 1);

    return 0;
}

uint8_t SGUS_GetBacklight(uint8_t *lightvalue)
{
    sgus_regdata_t * regdata = SGUS_GetTxRegData();

    *lightvalue = regdata->ledlmnow;

    return 0;
}


uint8_t SGUS_SetBeepTime(uint16_t beeptime_ms)
{
    uint8_t beeptimetmp;
    sgus_regdata_t * regdata = SGUS_GetTxRegData();

    if(2550 < beeptime_ms)
    {
        beeptime_ms = 2550;
    }

    beeptimetmp = (beeptime_ms+5)/10;

    regdata->bztime = beeptimetmp;
    SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_BzTime, 1);
    return 0;
}

uint8_t SGUS_SetCurrentPage(sgus_pageindex_t pageindex)
{
    uint8_t pageaddr[2];
    uint16_t pageaddr_tmp;

    const sgus_pageinfo_t * pageinfo = SGUS_GetPageInfo();
    sgus_regdata_t * regdata = SGUS_GetTxRegData();

    pageaddr_tmp = pageinfo[pageindex].pageaddr + SGUS_PAGE_OFFSET*SGUS_LangEnum;

    pageaddr[0] = (pageaddr_tmp >> 8) & 0xFF;
    pageaddr[1] = pageaddr_tmp & 0xFF;


    regdata->picindex[0] = pageaddr[0];
    regdata->picindex[1] = pageaddr[1];

    SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_PicIndex, 2);

    return 0;
}

uint8_t SGUS_GetCurrentPage(sgus_pageindex_t * pageindex)
{
    uint16_t pageaddr;
    const sgus_pageinfo_t * pageinfo = SGUS_GetPageInfo();
    sgus_regdata_t * regdata = SGUS_GetRxRegData();

    uint8_t i;

    pageaddr = (regdata->picindex[0]<<8) | regdata->picindex[1];
    pageaddr -= SGUS_PAGE_OFFSET*SGUS_LangEnum;

    for(i = 0; i < NumofPageIndex; i++)
    {
        if(pageaddr == pageinfo[i].pageaddr)
        {
            *pageindex = pageinfo[i].pageindex;
            break;
        }
    }

    return 0;
}

uint8_t SGUS_GetRunTime(uint32_t * runtime)
{
    sgus_regdata_t * regdata = SGUS_GetRxRegData();

    *runtime = regdata->runtime[0] << 24 | regdata->runtime[1]<< 16 |\
              regdata->runtime[2] << 8  | regdata->runtime[3];

    return 0 ;
}
uint8_t SGUS_SetRTC(sgus_rtc_t * rtcvalue)
{
    sgus_regdata_t * regdata = SGUS_GetTxRegData();

    regdata->rtccomadj[0] = 0x5A;
    regdata->rtccomadj[1] = rtcvalue->year;
    regdata->rtccomadj[2] = rtcvalue->month;
    regdata->rtccomadj[3] = rtcvalue->day;
    regdata->rtccomadj[4] = 0x00;  //Week set to 0, and SGUS will auto calc the value;
    regdata->rtccomadj[5] = rtcvalue->hour;
    regdata->rtccomadj[6] = rtcvalue->minute;
    regdata->rtccomadj[7] = rtcvalue->second;

    SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_RtcComAdj, 8);

    return 0;
}

uint8_t SGUS_GetRTC(sgus_rtc_t * rtcvalue)
{
    sgus_regdata_t * regdata = SGUS_GetRxRegData();

    rtcvalue->year   = regdata->rtcnow[0];
    rtcvalue->month  = regdata->rtcnow[1];
    rtcvalue->day    = regdata->rtcnow[2];
    rtcvalue->week   = regdata->rtcnow[3];
    rtcvalue->hour   = regdata->rtcnow[4];
    rtcvalue->minute = regdata->rtcnow[5];
    rtcvalue->second = regdata->rtcnow[6];

    return 0;
}

uint8_t SGUS_PlayMusic(uint8_t musicindex) //musicindex need to be enum?
{
    sgus_regdata_t * regdata = SGUS_GetTxRegData();

    regdata->playmusic[0] = 0x5A;
    regdata->playmusic[1] = musicindex;
    regdata->playmusic[2] = 1;

    SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_PlayMusic, 3);

    return 0;
}

uint8_t SGUS_SetTimer0(uint16_t time)
{
	sgus_regdata_t * regdata = SGUS_GetTxRegData();

	regdata->timer0[0] = time >> 8;
    regdata->timer0[1] = time & 0xFF;

	SGUS_SetTxQueue(QUEUE_TYPE_REG, SGUS_Reg_Timer0, 1);

	return 0;
}

uint8_t SGUS_GetTimer0(uint16_t * time)
{
	sgus_regdata_t * regdata = SGUS_GetRxRegData();

	*time = (regdata->timer0[0]<< 8) | regdata->timer0[1];

	return 0;
}












//Variable Part
//Global
//SerialNum
uint8_t SGUS_SetSerialNum(uint8_t * buffer)
{
    uint8_t len = 0;
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    uint8_t i;
    for(i = 0; i < SGUS_SERIALNUM_MAX; i++)
    {
        vardata->serialnum[i] = buffer[i];
        if('\0' == buffer[i])
        {
            len = i+1;
            break;
        }
    }

    if(SGUS_SERIALNUM_MAX <= len)
    {
        len = SGUS_SERIALNUM_MAX;
    }
    else
    {
        vardata->serialnum[len] = '\0';
    }

    vardata->serialnum[SGUS_SERIALNUM_MAX-1] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_SerialNum, len);

    return 0;
}

uint8_t SGUS_GetSerialNum(uint8_t * buffer)
{
   sgus_vardata_t * vartable = SGUS_GetRxVarData();

   uint8_t i;

   vartable->serialnum[SGUS_SERIALNUM_MAX-1] = '\0';
   for(i = 0; i < SGUS_SERIALNUM_MAX; i++)
    {
        buffer[i] = vartable->serialnum[i];
        if('\0' == vartable->serialnum[i])
        {
            break;
        }
    }

   return 0;
}

//NetworkState
uint8_t SGUS_SetNetworkState(sgus_networkstate_t state)
{
    sgus_vardata_t * artable = SGUS_GetTxVarData();
    artable->networkstate[0] = 0;
    artable->networkstate[1] = state;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_NetworkState, 2);

    return 0;
}

uint8_t SGUS_GetNetworkState(sgus_networkstate_t * state)
{
    sgus_vardata_t * artable = SGUS_GetRxVarData();
    *state = (sgus_networkstate_t)artable->networkstate[1];

    return 0;
}

//CurrentPlug
uint8_t SGUS_SetCurrentPlug(uint8_t plug)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->currentplug[0] = 0;
    vartable->currentplug[1] = plug;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_CurrentPlug, 2);

    return 0;
}

uint8_t SGUS_GetCurrentPlug(uint8_t *plug)
{
    sgus_vardata_t *vartable = SGUS_GetRxVarData();
    *plug = vartable->currentplug[1];

    return 0;
}

//TimeCountDown
uint8_t SGUS_SetTimOut(uint16_t value)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->timecountdown[0] = 0;
    vartable->timecountdown[1] = value;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_TimeCountDown, 2);

    return 0;
}

//ButtonBack
uint8_t SGUS_GetButtonBack(uint8_t *button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonback[1];

    
    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonback[0] = 0;
        vartable->buttonback[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonBack, 2);
    }
    return 0;
}

//ButtonConfirm
uint8_t SGUS_GetButtonConfirm(uint8_t *button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonconfirm[1];

    
    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonconfirm[0] = 0;
        vartable->buttonconfirm[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonConfirm, 2);
    }

    return 0;
}

//ButtonSysInfo
uint8_t SGUS_GetButtonSysInfo(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonsysinfo[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttontest[0] = 0;
        vartable->buttontest[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonSysInfo, 2);
    }

    return 0;
}

//ButtonHomepage
uint8_t SGUS_GetButtonHomePage(uint8_t *button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonhomepage[1];

    
    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonhomepage[0] = 0;
        vartable->buttonhomepage[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonHomePage, 2);
    }
    return 0;
}

//ButtonStopCharge
uint8_t SGUS_GetButtonStopCharge(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonstopcharge[1];

    
    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonstopcharge[0] = 0;
        vartable->buttonstopcharge[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonStopCharge, 2);
    }
    return 0;
}


//ButtonTest
uint8_t SGUS_GetButtonTest(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttontest[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttontest[0] = 0;
        vartable->buttontest[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonTest, 2);
    }

    return 0;
}






//Page Homepage
//ButtonStop_PlugA
uint8_t SGUS_GetButtonStop_PlugA(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonstop_pluga[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonstop_pluga[0] = 0;
        vartable->buttonstop_pluga[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonStop_PlugA, 2);
    }

    return 0;
}
//ButtonStop_PlugB
uint8_t SGUS_GetButtonStop_PlugB(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonstop_plugb[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonstop_plugb[0] = 0;
        vartable->buttonstop_plugb[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonStop_PlugB, 2);
    }

    return 0;
}

//ButtonBase_PlugA
uint8_t SGUS_GetButtonBase_PlugA(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonbase_pluga[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonbase_pluga[0] = 0;
        vartable->buttonbase_pluga[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonBase_PlugA, 2);
    }

    return 0;
}

//ButtonBase_PlugB
uint8_t SGUS_GetButtonBase_PlugB(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonbase_plugb[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonbase_plugb[0] = 0;
        vartable->buttonbase_plugb[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonBase_PlugB, 2);
    }

    return 0;
}

//ButtonLangSelect
uint8_t SGUS_GetButtonLangSelect(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonlangsel[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonlangsel[0] = 0;
        vartable->buttonlangsel[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonLangSelect, 2);
    }

    return 0;
}

//MarkedWord_PlugA
uint8_t SGUS_SetMarkedWord_PlugA(uint8_t markedword)
{
	sgus_vardata_t * vartable = SGUS_GetTxVarData();

	vartable->markedword_pluga[0] = 0;
	vartable->markedword_pluga[1] = markedword;

	SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_MarkedWords_PlugA, 2);

	    return 0;
}

uint8_t SGUS_GetMarkedWord_PlugA(uint8_t * markedword)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*markedword = vartable->markedword_pluga[1];
	return 0;
}

//MarkedWord_PlugB
uint8_t SGUS_SetMarkedWord_PlugB(uint8_t markedword)
{
	sgus_vardata_t * vartable = SGUS_GetTxVarData();

	vartable->markedword_plugb[0] = 0;
	vartable->markedword_plugb[1] = markedword;

	SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_MarkedWords_PlugB, 2);

	    return 0;
}

uint8_t SGUS_GetMarkedWord_PlugB(uint8_t * markedword)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*markedword = vartable->markedword_plugb[1];
	return 0;
}

//State_PlugA
uint8_t SGUS_SetPlugState_PlugA(sgus_plugstate_t state)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
/*
    vartable->dynstate_pluga[0] = 0;
    vartable->dynstate_pluga[1] = !state;
    vartable->dynstate_pluga[2] = 0;
    vartable->dynstate_pluga[3] = 0;
*/
    vartable->staticstate_pluga[0] = 0;
    vartable->staticstate_pluga[1] = state;


    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StaticState_PlugA, 2);

    return 0;
}

uint8_t SGUS_GetPlugState_PlugA(sgus_plugstate_t * state)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *state = (sgus_plugstate_t)vartable->staticstate_pluga[1];

    return 0;
}


//State_PlugB
uint8_t SGUS_SetPlugState_PlugB(sgus_plugstate_t state)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();

    /*
    vartable->dynstate_plugb[0] = 0;
    vartable->dynstate_plugb[1] = !state;
    vartable->dynstate_plugb[2] = 0;
    vartable->dynstate_plugb[3] = 0;
*/
    vartable->staticstate_plugb[0] = 0;
    vartable->staticstate_plugb[1] = state;


    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StaticState_PlugB, 2);

    return 0;
}


uint8_t SGUS_GetPlugState_PlugB(sgus_plugstate_t *state)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *state = (sgus_plugstate_t)vartable->staticstate_plugb[1];

    return 0;
}

//RemainingTime_PlugA
uint8_t SGUS_SetRemainingTime_PlugA(uint16_t     lefttime)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->remainingtime_pluga[0] = lefttime>>8;
    vartable->remainingtime_pluga[1] = lefttime&0xFF;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_RemainingTime_PlugA, 2);

    return 0;
}

uint8_t SGUS_GetRemainingTime_PlugA(uint16_t   * lefttime)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *lefttime = (vartable->remainingtime_pluga[0]<<8) | vartable->remainingtime_pluga[1];

    return 0;
}


//RemainingTime_PlugB
uint8_t SGUS_SetRemainingTime_PlugB(uint16_t     lefttime)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->remainingtime_plugb[0] = lefttime>>8;
    vartable->remainingtime_plugb[1] = lefttime&0xFF;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_RemainingTime_PlugB, 2);

    return 0;
}

uint8_t SGUS_GetRemainingTime_PlugB(uint16_t     *  lefttime)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *lefttime = (vartable->remainingtime_plugb[0]<<8) | vartable->remainingtime_plugb[1];

    return 0;
}


//SOCGreen_PlugA
uint8_t SGUS_SetSOCGreen_PlugA(uint8_t   soc)
{
    uint8_t tmpbuf[4] = {0x20, 0x20, 0x20, 0x20};
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    if(100 < soc)
    {

    }
    else if(100 == soc)
    {
        tmpbuf[1] = 0x31;
        tmpbuf[2] = 0x30;
        tmpbuf[3] = 0x30;
    }
    else if(0 < soc/10)
    {
        tmpbuf[2] = soc/10 + 0x30;
        tmpbuf[3] = soc%10 + 0x30;
    }
    else
    {
        tmpbuf[3] = soc + 0x30;
    }
    vartable->socgreen_pluga[0] = tmpbuf[0];
    vartable->socgreen_pluga[1] = tmpbuf[1];
    vartable->socgreen_pluga[2] = tmpbuf[2];
    vartable->socgreen_pluga[3] = tmpbuf[3];

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoSOCGreen_PlugA, 4);

    return 0;
}


uint8_t SGUS_GetSOCGreen_PlugA(uint8_t * soc)
{
    uint8_t tmpbuf[4];
    sgus_vardata_t * vartable = SGUS_GetRxVarData();

    tmpbuf[1] = (vartable->socgreen_pluga[1] >= 0x30) ? (vartable->socgreen_pluga[1] - 0x30) : 0;
    tmpbuf[2] = (vartable->socgreen_pluga[2] >= 0x30) ? (vartable->socgreen_pluga[2] - 0x30) : 0;
    tmpbuf[3] = (vartable->socgreen_pluga[3] >= 0x30) ? (vartable->socgreen_pluga[3] - 0x30) : 200;

    *soc = tmpbuf[1]*100 | tmpbuf[2]*10 | tmpbuf[3];

    return 0;
}

//SOCGreen_PlugB
uint8_t SGUS_SetSOCGreen_PlugB(uint8_t   soc)
{
    uint8_t tmpbuf[4] = {0x20, 0x20, 0x20, 0x20};
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    if(100 < soc)
    {
        
    }
    else if(100 == soc)
    {
        tmpbuf[1] = 0x31;
        tmpbuf[2] = 0x30;
        tmpbuf[3] = 0x30;
    }
    else if(0 < soc/10)
    {
        tmpbuf[2] = soc/10 + 0x30;
        tmpbuf[3] = soc%10 + 0x30;
    }
    else
    {
        tmpbuf[3] = soc + 0x30;
    }
    vartable->socgreen_plugb[0] = tmpbuf[0];
    vartable->socgreen_plugb[1] = tmpbuf[1];
    vartable->socgreen_plugb[2] = tmpbuf[2];
    vartable->socgreen_plugb[3] = tmpbuf[3];

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoSOCGreen_PlugB, 4);

    return 0;
}


uint8_t SGUS_GetSOCGreen_PlugB(uint8_t * soc)
{
    uint8_t tmpbuf[4];
    sgus_vardata_t * vartable = SGUS_GetRxVarData();

    tmpbuf[1] = (vartable->socgreen_plugb[1] >= 0x30) ? (vartable->socgreen_plugb[1] - 0x30) : 0;
    tmpbuf[2] = (vartable->socgreen_plugb[2] >= 0x30) ? (vartable->socgreen_plugb[2] - 0x30) : 0;
    tmpbuf[3] = (vartable->socgreen_plugb[3] >= 0x30) ? (vartable->socgreen_plugb[3] - 0x30) : 200;

    *soc = tmpbuf[1]*100 | tmpbuf[2]*10 | tmpbuf[3];

    return 0;
}


//SOCRed_PlugA
uint8_t SGUS_SetSOCRed_PlugA(uint8_t   soc)
{
    uint8_t tmpbuf[4] = {0x20, 0x20, 0x20, 0x20};
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    if(100 < soc)
    {

    }
    else if(100 == soc)
    {
        tmpbuf[1] = 0x31;
        tmpbuf[2] = 0x30;
        tmpbuf[3] = 0x30;
    }
    else if(0 < soc/10)
    {
        tmpbuf[2] = soc/10 + 0x30;
        tmpbuf[3] = soc%10 + 0x30;
    }
    else
    {
        tmpbuf[3] = soc + 0x30;
    }
    vartable->socred_pluga[0] = tmpbuf[0];
    vartable->socred_pluga[1] = tmpbuf[1];
    vartable->socred_pluga[2] = tmpbuf[2];
    vartable->socred_pluga[3] = tmpbuf[3];

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoSOCRed_PlugA, 4);

    return 0;
}


uint8_t SGUS_GetSOCRed_PlugA(uint8_t * soc)
{
    uint8_t tmpbuf[4];
    sgus_vardata_t * vartable = SGUS_GetRxVarData();

    tmpbuf[1] = (vartable->socred_pluga[1] >= 0x30) ? (vartable->socred_pluga[1] - 0x30) : 0;
    tmpbuf[2] = (vartable->socred_pluga[2] >= 0x30) ? (vartable->socred_pluga[2] - 0x30) : 0;
    tmpbuf[3] = (vartable->socred_pluga[3] >= 0x30) ? (vartable->socred_pluga[3] - 0x30) : 200;

    *soc = tmpbuf[1]*100 | tmpbuf[2]*10 | tmpbuf[3];

    return 0;
}


//SOCRed_PlugB
uint8_t SGUS_SetSOCRed_PlugB(uint8_t   soc)
{
    uint8_t tmpbuf[4] = {0x20, 0x20, 0x20, 0x20};
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    if(100 < soc)
    {

    }
    else if(100 == soc)
    {
        tmpbuf[1] = 0x31;
        tmpbuf[2] = 0x30;
        tmpbuf[3] = 0x30;
    }
    else if(0 < soc/10)
    {
        tmpbuf[2] = soc/10 + 0x30;
        tmpbuf[3] = soc%10 + 0x30;
    }
    else
    {
        tmpbuf[3] = soc + 0x30;
    }
    vartable->socred_plugb[0] = tmpbuf[0];
    vartable->socred_plugb[1] = tmpbuf[1];
    vartable->socred_plugb[2] = tmpbuf[2];
    vartable->socred_plugb[3] = tmpbuf[3];

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoSOCRed_PlugB, 4);

    return 0;
}


uint8_t SGUS_GetSOCRed_PlugB(uint8_t * soc)
{
    uint8_t tmpbuf[4];
    sgus_vardata_t * vartable = SGUS_GetRxVarData();

    tmpbuf[1] = (vartable->socred_plugb[1] >= 0x30) ? (vartable->socred_plugb[1] - 0x30) : 0;
    tmpbuf[2] = (vartable->socred_plugb[2] >= 0x30) ? (vartable->socred_plugb[2] - 0x30) : 0;
    tmpbuf[3] = (vartable->socred_plugb[3] >= 0x30) ? (vartable->socred_plugb[3] - 0x30) : 200;

    *soc = tmpbuf[1]*100 | tmpbuf[2]*10 | tmpbuf[3];

    return 0;
}


//ChargePrice
uint8_t SGUS_SetChargePrice(uint32_t price)
{
	sgus_vardata_t * vartable = SGUS_GetTxVarData();
	vartable->chargeprice[0] = (price>>24) & 0xFF;
	vartable->chargeprice[1] = (price>>16) & 0xFF;
	vartable->chargeprice[2] = (price>>8) & 0xFF;
	vartable->chargeprice[3] = (price>>0) & 0xFF;

	SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ChargePrice, 4);

	return 0;

}

uint8_t SGUS_GetChargePrice(uint32_t * price)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();

	*price = (vartable->chargeprice[0]<<24) |\
			(vartable->chargeprice[1]<<16) |\
			(vartable->chargeprice[2]<<8) |\
			(vartable->chargeprice[3]<<0);

	return 0;
}




//Page LangSelect
uint8_t SGUS_GetButtonLangEnum(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();

	*button = vartable->buttonlang_enum[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonlang_enum[0] = 0;
		vartable->buttonlang_enum[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonLanguageEnum, 2);
	}
	return 0;
}

uint8_t SGUS_SetLangEnum(uint8_t value)
{
	SGUS_LangEnum = value;
	return 0;
}

uint8_t SGUS_GetLangEnum(void)
{
	return SGUS_LangEnum;
}

//Page User Login
//UserName
uint8_t SGUS_SetLoginUserName(uint8_t *buffer)
{
    uint8_t len = 0;
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    uint8_t i;
    for(i = 0; i < 32; i++)
    {
        vardata->loginusername[i] = buffer[i];
        if('\0' == buffer[i])
        {
            len = i+1;
            break;
        }
    }

    if(32 <= len)
    {
        len = 32;
    }
    else
    {
        vardata->loginusername[len] = '\0';
    }

    vardata->loginusername[32-1] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_LoginUserName, len);

    return 0;
}


uint8_t SGUS_GetLoginUserName(uint8_t * buffer)
{
   sgus_vardata_t * vartable = SGUS_GetRxVarData();

   uint8_t i;

   vartable->loginusername[32-1] = '\0';

   for(i = 0; i < 32; i++)
    {
        buffer[i] = vartable->loginusername[i];
        if('\0' == vartable->loginusername[i])
        {
            break;
        }
    }
   

   return 0;
}

//Password
uint8_t SGUS_SetLoginPassWord(uint8_t *buffer)
{
    uint8_t len = 0;
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    uint8_t i;
    for(i = 0; i < 32; i++)
    {
        vardata->loginpassword[i] = buffer[i];
        if('\0' == buffer[i])
        {
            len = i+1;
            break;
        }
    }

    if(32 <= len)
    {
        len = 32;
    }
    else
    {
        vardata->loginpassword[len] = '\0';
    }

    vardata->loginpassword[32-1] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_LoginPassWord, len);

    return 0;
}


uint8_t SGUS_GetLoginPassWord(uint8_t * buffer)
{
   sgus_vardata_t * vartable = SGUS_GetRxVarData();

   uint8_t i;

   vartable->loginpassword[32-1] = '\0';

   for(i = 0; i < 32; i++)
    {
        buffer[i] = vartable->loginpassword[i];
        if('\0' == vartable->loginpassword[i])
        {
            break;
        }
    }

   return 0;
}

//Page Payment Method
//Button Payment QRCode
uint8_t SGUS_GetButtonPaymentMethod(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->payment_method[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->payment_method[0] = 0;
        vartable->payment_method[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_Payment_Method, 2);
    }

    return 0;
}


//Page Payment QRCode
uint8_t SGUS_SetQRCode(uint8_t * data)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    uint16_t i;
    for(i = 0; i < 480; i++)
    {
        vartable->qrcode[i] = data[i];
        if('\0' == data[i])
        {
            break;
        }
    }
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_QRCode, (i+2)*2/2);

    return 0;
}

//Page Mode Select
//Button AutoFull
uint8_t SGUS_GetButtonAutoFull(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonmodautofull[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonmodautofull[0] = 0;
        vartable->buttonmodautofull[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ChargeModAutoFull, 2);
    }

    return 0;
}

//Button Money
uint8_t SGUS_GetButtonMoney(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonmodmoney[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonmodmoney[0] = 0;
        vartable->buttonmodmoney[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ChargeModMoney, 2);
    }

    return 0;
}

//Button Time
uint8_t SGUS_GetButtonTime(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonmodtime[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonmodtime[0] = 0;
        vartable->buttonmodtime[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ChargeModTime, 2);
    }

    return 0;
}

//Button Energy
uint8_t SGUS_GetButtonEnergy(uint8_t * button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonmodenergy[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonmodenergy[0] = 0;
        vartable->buttonmodenergy[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ChargeModEnergy, 2);
    }

    return 0;
}

//Page Mode Moeny
//MoneyValue
uint8_t SGUS_SetChargeMoneyValue(uint16_t value)
{
	sgus_vardata_t * vartable = SGUS_GetTxVarData();
	vartable->valuemodmoney[0] = (value>>8) & 0xFF;
	vartable->valuemodmoney[1] = value & 0xFF;

	SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ChargeMoneyValue, 2);
	return 0;
}

uint8_t SGUS_GetChargeMoneyValue(uint16_t *value)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();

	*value = (vartable->valuemodmoney[0]<<8) |\
			 vartable->valuemodmoney[1];

	return 0;
}

//TimeValue
uint8_t SGUS_SetChargeTimeValue(uint16_t value)
{
	sgus_vardata_t * vartable = SGUS_GetTxVarData();
	vartable->valuemodtime[0] = (value>>8) & 0xFF;
	vartable->valuemodtime[1] = value & 0xFF;

	SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ChargeTimeValue, 2);
	return 0;
}

uint8_t SGUS_GetChargeTimeValue(uint16_t *value)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();

	*value = (vartable->valuemodtime[0]<<8) |\
			 vartable->valuemodtime[1];

	return 0;
}

//EnergyValue
uint8_t SGUS_SetChargeEnergyValue(uint16_t value)
{
	sgus_vardata_t * vartable = SGUS_GetTxVarData();
	vartable->valuemodenergy[0] = (value>>8) & 0xFF;
	vartable->valuemodenergy[1] = value & 0xFF;

	SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ChargeEnergyValue, 2);
	return 0;
}

uint8_t SGUS_GetChargeEnergyValue(uint16_t *value)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();

	*value = (vartable->valuemodenergy[0]<<8) |\
			 vartable->valuemodenergy[1];

	return 0;
}

//PageCardInfoCheckFailueCode
uint8_t SGUS_SetAuthCheckFailCode(uint8_t * failcode)
{
//TODO SGUS_SetAuthCheckFailCode
	return 0;
}

//PageCardInfoCheckSucceed
//RFID Card Num
uint8_t SGUS_SetRFIDCardNum(uint8_t *buffer)
{
    uint8_t len = 0;
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    uint8_t i;
    for(i = 0; i < SGUS_SERIALNUM_MAX; i++)
    {
        vardata->rfidcardnum[i] = buffer[i];
        if('\0' == buffer[i])
        {
            len = i+1;
            break;
        }
    }

    if(SGUS_SERIALNUM_MAX <= len)
    {
        len = SGUS_SERIALNUM_MAX;
    }
    else
    {
        vardata->rfidcardnum[len] = '\0';
    }

    vardata->rfidcardnum[SGUS_SERIALNUM_MAX-1] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_RFIDCardNum, len);

    return 0;
}

uint8_t SGUS_SetRFIDCardBalance(uint32_t balance)
{
//TODO SGUS_SetRFIDCardBalance
	return 0;
}

uint8_t SGUS_SetRFIDCardPoint(uint32_t point)
{
//TODO SGUS_SetRFIDCardPoint
	return 0;
}

uint8_t SGUS_SetChargeFailCode(uint8_t *buffer)
{
//TODO SGUS_SetChargeFailCode
	return 0;
}

//Page Auth by Card
uint8_t SGUS_SetCardTypeIcon(uint8_t icon)
{
	 sgus_vardata_t * vardata = SGUS_GetTxVarData();
	 vardata->cardicon[0] = 0;
	 vardata->cardicon[1] = icon;
	 SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_CardIcon, 2);
	 return 0;
}

uint8_t SGUS_GetCardTypeIcon(uint8_t * icon)
{
	sgus_vardata_t * vardata = SGUS_GetRxVarData();
	*icon = vardata->cardicon[1];
	return 0;
}



//WorkInfo
uint8_t SGUS_SetWorkInfoCurrent(uint32_t data)
{
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    vardata->workinfocurrent[0] = (data >> 24) & 0xFF;
    vardata->workinfocurrent[1] = (data >> 16) & 0xFF;
    vardata->workinfocurrent[2] = (data >> 8) & 0xFF;
    vardata->workinfocurrent[3] = data & 0xFF;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoCurrent, 4);
    return 0;
}

uint8_t SGUS_GetWorkInfoCurrent(uint32_t *data)
{
    sgus_vardata_t * vardata = SGUS_GetRxVarData();
    *data = (vardata->workinfocurrent[0]<< 24) |\
    		(vardata->workinfocurrent[1]<< 16) |\
			(vardata->workinfocurrent[2]<< 8) |\
			vardata->workinfocurrent[3];
    return 0;
}

uint8_t SGUS_SetWorkInfoVoltage(uint32_t data)
{
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    vardata->workinfovoltate[0] = (data >> 24) & 0xFF;
    vardata->workinfovoltate[1] = (data >> 16) & 0xFF;
    vardata->workinfovoltate[2] = (data >> 8) & 0xFF;
    vardata->workinfovoltate[3] = data & 0xFF;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoVoltage, 4);
    return 0;
}

uint8_t SGUS_GetWorkInfoVoltage(uint32_t *data)
{
    sgus_vardata_t * vardata = SGUS_GetRxVarData();

    *data = (vardata->workinfovoltate[0] << 24) |\
    		(vardata->workinfovoltate[1] << 16) |\
			(vardata->workinfovoltate[2] << 8) |\
			vardata->workinfovoltate[3];

    return 0;
}

uint8_t SGUS_SetWorkInfoEnergy(uint32_t data)
{
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    vardata->workinfoenergy[0] = (data >> 24) & 0xFF;
    vardata->workinfoenergy[1] = (data >> 16) & 0xFF;
    vardata->workinfoenergy[2] = (data >> 8) & 0xFF;
    vardata->workinfoenergy[3] = data & 0xFF;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoEnergy, 4);
    return 0;
}

uint8_t SGUS_GetWorkInfoEnergy(uint32_t *data)
{
    sgus_vardata_t * vardata = SGUS_GetRxVarData();

    *data = (vardata->workinfoenergy[0]<<24) |\
    		(vardata->workinfoenergy[1]<<16) |\
			(vardata->workinfoenergy[2]<<8) |\
			vardata->workinfoenergy[3];

    return 0;
}


uint8_t SGUS_SetWorkInfoChargingTime(uint32_t data)
{
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    vardata->workinfochargingtime[0] = (data >> 24) & 0xFF;
    vardata->workinfochargingtime[1] = (data >> 16) & 0xFF;
    vardata->workinfochargingtime[2] = (data >> 8) & 0xFF;
    vardata->workinfochargingtime[3] = data & 0xFF;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoChargingTime, 4);
    return 0;
}

uint8_t SGUS_GetWorkInfoChargingTime(uint32_t *data)
{
    sgus_vardata_t * vardata = SGUS_GetRxVarData();

    *data = (vardata->workinfochargingtime[0] << 24) |\
    		(vardata->workinfochargingtime[1] << 16) |\
			(vardata->workinfochargingtime[2] << 8) |\
			vardata->workinfochargingtime[3];


    return 0;
}


uint8_t SGUS_SetWorkInfoRemainingTime(uint32_t data)
{
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    vardata->workinforemainingtime[0] = (data >> 24) & 0xFF;
    vardata->workinforemainingtime[1] = (data >> 16) & 0xFF;
    vardata->workinforemainingtime[2] = (data >> 8) & 0xFF;
    vardata->workinforemainingtime[3] = data & 0xFF;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoRemainingTime, 4);
    return 0;
}

uint8_t SGUS_GetWorkInfoRemainingTime(uint32_t *data)
{
    sgus_vardata_t * vardata = SGUS_GetRxVarData();

    *data = (vardata->workinforemainingtime[0] << 24) |\
    		(vardata->workinforemainingtime[1] << 16) |\
			(vardata->workinforemainingtime[2] << 8) |\
			vardata->workinforemainingtime[3];

    return 0;
}

uint8_t SGUS_SetWorkInfoCost(uint32_t data)
{
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    vardata->workinfocost[0] = (data >> 24) & 0xFF;
    vardata->workinfocost[1] = (data >> 16) & 0xFF;
    vardata->workinfocost[2] = (data >> 8) & 0xFF;
    vardata->workinfocost[3] = data & 0xFF;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoCost, 4);
    return 0;
}

uint8_t SGUS_GetWorkInfoCost(uint32_t *data)
{
    sgus_vardata_t * vardata = SGUS_GetRxVarData();
    *data  = (vardata->workinfocost[0] << 24) |\
    		(vardata->workinfocost[1] << 16) |\
			(vardata->workinfocost[2] << 8) |\
			vardata->workinfocost[3];

    return 0;
}


uint8_t SGUS_SetPlugState(sgus_plugstate_t state)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();

    vartable->workinfoplugdynstate[0] = 0;
    vartable->workinfoplugdynstate[1] = !state;
    vartable->workinfoplugdynstate[2] = 0;
    vartable->workinfoplugdynstate[3] = 0;

    vartable->workinfoplugstaticstate[0] = 0;
    vartable->workinfoplugstaticstate[1] = state;


    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoPlugDynState, 6);

    return 0;
}

uint8_t SGUS_GetPlugState(sgus_plugstate_t * state)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *state = (sgus_plugstate_t)vartable->workinfoplugstaticstate[1];

    return 0;
}

uint8_t SGUS_SetChargingGIF(uint8_t state)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->workinfocharginggif[0] = 0;
    vartable->workinfocharginggif[1] = state;

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoChargingGIF, 2);

    return 0;
}

uint8_t SGUS_GetChargingGIF(uint8_t * state)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *state = vartable->workinfocharginggif[1];

    return 0;
}

uint8_t SGUS_SetSOCGreen(uint8_t   soc)
{
    uint8_t tmpbuf[4] = {0x20, 0x20, 0x20, 0x20};
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    if(100 < soc)
    {

    }
    else if(100 == soc)
    {
        tmpbuf[1] = 0x31;
        tmpbuf[2] = 0x30;
        tmpbuf[3] = 0x30;
    }
    else if(0 < soc/10)
    {
        tmpbuf[2] = soc/10 + 0x30;
        tmpbuf[3] = soc%10 + 0x30;
    }
    else
    {
        tmpbuf[3] = soc + 0x30;
    }
    vartable->workinfosocgreen[0] = tmpbuf[0];
    vartable->workinfosocgreen[1] = tmpbuf[1];
    vartable->workinfosocgreen[2] = tmpbuf[2];
    vartable->workinfosocgreen[3] = tmpbuf[3];

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoSOCGreen, 4);

    return 0;
}


uint8_t SGUS_GetSOCGreen(uint8_t * soc)
{
    uint8_t tmpbuf[4];
    sgus_vardata_t * vartable = SGUS_GetRxVarData();

    tmpbuf[1] = (vartable->workinfosocgreen[1] >= 0x30) ? (vartable->workinfosocgreen[1] - 0x30) : 0;
    tmpbuf[2] = (vartable->workinfosocgreen[2] >= 0x30) ? (vartable->workinfosocgreen[2] - 0x30) : 0;
    tmpbuf[3] = (vartable->workinfosocgreen[3] >= 0x30) ? (vartable->workinfosocgreen[3] - 0x30) : 200;

    *soc = tmpbuf[1]*100 | tmpbuf[2]*10 | tmpbuf[3];

    return 0;
}


uint8_t SGUS_SetSOCRed(uint8_t   soc)
{
    uint8_t tmpbuf[4] = {0x20, 0x20, 0x20, 0x20};
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    if(100 < soc)
    {

    }
    else if(100 == soc)
    {
        tmpbuf[1] = 0x31;
        tmpbuf[2] = 0x30;
        tmpbuf[3] = 0x30;
    }
    else if(0 < soc/10)
    {
        tmpbuf[2] = soc/10 + 0x30;
        tmpbuf[3] = soc%10 + 0x30;
    }
    else
    {
        tmpbuf[3] = soc + 0x30;
    }
    vartable->workinfosocred[0] = tmpbuf[0];
    vartable->workinfosocred[1] = tmpbuf[1];
    vartable->workinfosocred[2] = tmpbuf[2];
    vartable->workinfosocred[3] = tmpbuf[3];

    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_WorkInfoSOCRed, 4);

    return 0;
}


uint8_t SGUS_GetSOCRed(uint8_t * soc)
{
    uint8_t tmpbuf[4];
    sgus_vardata_t * vartable = SGUS_GetRxVarData();

    tmpbuf[1] = (vartable->workinfosocred[1] >= 0x30) ? (vartable->workinfosocred[1] - 0x30) : 0;
    tmpbuf[2] = (vartable->workinfosocred[2] >= 0x30) ? (vartable->workinfosocred[2] - 0x30) : 0;
    tmpbuf[3] = (vartable->workinfosocred[3] >= 0x30) ? (vartable->workinfosocred[3] - 0x30) : 200;

    *soc = tmpbuf[1]*100 | tmpbuf[2]*10 | tmpbuf[3];

    return 0;
}

uint8_t SGUS_SetWorkInfoPower(uint32_t power)
{
	sgus_vardata_t * vartable = SGUS_GetTxVarData();
	vartable->workinfopower[0] = (power >> 24) & 0xFF;
	vartable->workinfopower[1] = (power >> 16) & 0xFF;
	vartable->workinfopower[2] = (power >> 8) & 0xFF;
	vartable->workinfopower[3] = power & 0xFF;
}

uint8_t SGUS_GetWorkInfoPower(uint32_t * power)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();

	*power =  (vartable->workinfopower[0] << 24) |\
				(vartable->workinfopower[1] << 16) |\
				(vartable->workinfopower[2] << 8) |\
				vartable->workinfopower[3];

	return 0;
}






uint8_t SGUS_SetLogoutPassWord(uint8_t *buffer)
{
    uint8_t len = 0;
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    uint8_t i;
    for(i = 0; i < 32; i++)
    {
        vardata->logoutpassword[i] = buffer[i];
        if('\0' == buffer[i])
        {
            len = i+1;
            break;
        }
    }

    if(32 <= len)
    {
        len = 32;
    }
    else
    {
        vardata->logoutpassword[len] = '\0';
    }

    vardata->logoutpassword[32-1] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_LogoutPassWord, len);

    return 0;
}


uint8_t SGUS_GetLogoutPassWord(uint8_t * buffer)
{
   sgus_vardata_t * vartable = SGUS_GetRxVarData();

   uint8_t i;

   vartable->logoutpassword[32-1] = '\0';

   for(i = 0; i < 32; i++)
    {
        buffer[i] = vartable->logoutpassword[i];
        if('\0' == vartable->logoutpassword[i])
        {
            break;
        }
    }

   return 0;
}











uint8_t SGUS_SetStopInfoEnergy(uint32_t energy)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->stopinfoenergy[0] = (energy>>24) & 0xFF;
    vartable->stopinfoenergy[1] = (energy>>16) & 0xFF;
    vartable->stopinfoenergy[2] = (energy>>8) & 0xFF;
    vartable->stopinfoenergy[3] = energy & 0xFF;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StopInfoEnergy, 4);
    return 0;
}
uint8_t SGUS_SetStopInfoMoney(uint32_t money)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->stopinfocost[0] = (money>>24) & 0xFF;
    vartable->stopinfocost[1] = (money>>16) & 0xFF;
    vartable->stopinfocost[2] = (money>>8) & 0xFF;
    vartable->stopinfocost[3] = money & 0xFF;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StopInfoCost, 4);
    return 0;
}
uint8_t SGUS_SetStopInfoChargedTime(uint32_t time)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->stopinfochargedtime[0] = (time>>24) & 0xFF;
    vartable->stopinfochargedtime[1] = (time>>16) & 0xFF;
    vartable->stopinfochargedtime[2] = (time>>8) & 0xFF;
    vartable->stopinfochargedtime[3] = time & 0xFF;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StopInfoChargedTime, 4);
    return 0;
}
uint8_t SGUS_SetStopInfoTransactionNum(uint8_t * number)
{
    uint8_t i;
    uint8_t len = 32;
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    for(i = 0; i < 32; i++)
    {
        vartable->stopInfotransactionnum[i] = number[i];
        if('\0' == number[i])
        {
            len = i;
            break;
        }
    }
    number[31] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StopInfoTransactionNum, len);
    return 0;
}
uint8_t SGUS_SetStopInfoStopReason(uint8_t * reson)
{
    uint8_t i;
    uint8_t len = 32;
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    for(i = 0; i < 32; i++)
    {
        vartable->stopinfostopreason[i] = reson[i];
        if('\0' == reson[i])
        {
            len = i;
            break;
        }
    }
    reson[31] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StopInfoTransactionNum, len);
    return 0;
}
uint8_t SGUS_SetStopInfoStartSOC(uint32_t soc)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->stopinfostartsoc[0] = (soc>>24) & 0xFF;
    vartable->stopinfostartsoc[1] = (soc>>16) & 0xFF;
    vartable->stopinfostartsoc[2] = (soc>>8) & 0xFF;
    vartable->stopinfostartsoc[3] = soc & 0xFF;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StopInfoStartSOC, 4);
    return 0;
}
uint8_t SGUS_SetStopInfoStopSOC(uint32_t soc)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    vartable->stopinfostopsoc[0] = (soc>>24) & 0xFF;
    vartable->stopinfostopsoc[1] = (soc>>16) & 0xFF;
    vartable->stopinfostopsoc[2] = (soc>>8) & 0xFF;
    vartable->stopinfostopsoc[3] = soc & 0xFF;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StopInfoStopSOC, 4);
    return 0;
}
uint8_t SGUS_SetStopInfoCardInfo(uint8_t * id)
{
    uint8_t i;
    uint8_t len = 32;
    sgus_vardata_t * vartable = SGUS_GetTxVarData();
    for(i = 0; i < 32; i++)
    {
        vartable->stopinfocardinfo[i] = id[i];
        if('\0' == id[i])
        {
            len = i;
            break;
        }
    }
    id[31] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StopInfoCardInfo, len);
    return 0;
}

uint8_t SGUS_SetStopInfoCardBalance(uint32_t balance)
{
//TODO SGUS_SetStopInfoCardBalance
	return 0;
}


uint8_t SGUS_SetSysConfigPassWord(uint8_t *buffer)
{
    uint8_t len = 0;
    sgus_vardata_t * vardata = SGUS_GetTxVarData();
    uint8_t i;
    for(i = 0; i < 32; i++)
    {
        vardata->sysconfigpassword[i] = buffer[i];
        if('\0' == buffer[i])
        {
            len = i+1;
            break;
        }
    }

    if(32 <= len)
    {
        len = 32;
    }
    else
    {
        vardata->sysconfigpassword[len] = '\0';
    }

    vardata->sysconfigpassword[32-1] = '\0';
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_SysLoginPassWord, len);

    return 0;
}


uint8_t SGUS_GetSysConfigPassWord(uint8_t * buffer)
{
   sgus_vardata_t * vartable = SGUS_GetRxVarData();

   uint8_t i;

   vartable->sysconfigpassword[32-1] = '\0';

   for(i = 0; i < 32; i++)
    {
        buffer[i] = vartable->sysconfigpassword[i];
        if('\0' == vartable->sysconfigpassword[i])
        {
            break;
        }
    }

   return 0;
}

uint8_t SGUS_GetButtonPageSysConfig(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpagesysconfig[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpagesysconfig[0] = 0;
		vartable->buttonpagesysconfig[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageSysConfig, 2);
	}
}

uint8_t SGUS_GetButtonPageInfoInquiry(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpageinfoinquiry[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpageinfoinquiry[0] = 0;
		vartable->buttonpageinfoinquiry[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageInfoInquiry, 2);
	}
}

uint8_t SGUS_GetButtonPageChargeRecord(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpagechargerecord[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpagechargerecord[0] = 0;
		vartable->buttonpagechargerecord[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageChargeRecord, 2);
	}
}

uint8_t SGUS_GetButtonPageFaultRecord(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpagefaultrecord[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpagefaultrecord[0] = 0;
		vartable->buttonpagefaultrecord[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageFaultRecord, 2);
	}
}

uint8_t SGUS_GetButtonPageInputControl(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpageinputcontrol[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpageinputcontrol[0] = 0;
		vartable->buttonpageinputcontrol[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPagerInputControl, 2);
	}
}

uint8_t SGUS_GetButtonPagePowerOffSelect(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpagepoweroffsel[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpagepoweroffsel[0] = 0;
		vartable->buttonpagepoweroffsel[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPagePowerOffSelect, 2);
	}
}

uint8_t SGUS_GetButtonPageElectricityMeterConfig(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpageelectricitymeterconfig[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpageelectricitymeterconfig[0] = 0;
		vartable->buttonpageelectricitymeterconfig[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageElectricityMeterConfig, 2);
	}
}

uint8_t SGUS_GetButtonPageAuxPowerConfig(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpageauxpowerconfig[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpageauxpowerconfig[0] = 0;
		vartable->buttonpageauxpowerconfig[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageAuxPowerConfig, 2);
	}
}

uint8_t SGUS_GetButtonPagePowerModuleConfig(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpagepowermoduleconfig[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpagepowermoduleconfig[0] = 0;
		vartable->buttonpagepowermoduleconfig[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPagePowerModuleConfig, 2);
	}
}

uint8_t SGUS_GetButtonPagePileTest(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpagepiletest[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpagepiletest[0] = 0;
		vartable->buttonpagepiletest[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPagePileTest, 2);
	}
}

uint8_t SGUS_GetButtonPageServerAddrConfig(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpageserveraddrconfig[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpageserveraddrconfig[0] = 0;
		vartable->buttonpageserveraddrconfig[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageServerAddrConfig, 2);
	}
}

uint8_t SGUS_GetButtonPageQRCodeConfig(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpageqrcodeconfig[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpageqrcodeconfig[0] = 0;
		vartable->buttonpageqrcodeconfig[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageQRCodeConfig, 2);
	}
}

uint8_t SGUS_GetButtonPageAreaSet(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpageareaset[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpageareaset[0] = 0;
		vartable->buttonpageareaset[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageAreaSet, 2);
	}
}

uint8_t SGUS_GetButtonPagePasswordReset(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonpagepasswordreset[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonpagepasswordreset[0] = 0;
		vartable->buttonpagepasswordreset[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPagePasswordRest, 2);
	}
}

uint8_t SGUS_SetHighVoltageState(uint8_t state)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();

    vartable->statehighvoltate[0] = 0;
    vartable->statehighvoltate[1] = state;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_StateHighVoltage, 2);

    return 0;
}

uint8_t SGUS_GetHighVoltageState(uint8_t *state)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();

    *state = vartable->statehighvoltate[1];

    return 0;
}


uint8_t SGUS_GetButtonSafePowerOff(uint8_t *button)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *button = vartable->buttonsafepoweroff[1];

    if(0 != *button)
    {
        //Reset Button state after read it
        vartable = SGUS_GetTxVarData();
        vartable->buttonsafepoweroff[0] = 0;
        vartable->buttonsafepoweroff[1] = 0;
        SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonSafePowerOff, 2);
    }

    return 0;
}


uint8_t SGUS_SetStationInput(uint8_t value)
{
    sgus_vardata_t * vartable = SGUS_GetTxVarData();

    vartable->inputcontrol[0] = 0;
    vartable->inputcontrol[1] = value;
    SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_InputControl, 2);

    return 0;
}

uint8_t SGUS_GetStationInput(uint8_t *value)
{
    sgus_vardata_t * vartable = SGUS_GetRxVarData();
    *value = vartable->inputcontrol[1];
}

uint8_t SGUS_GetButtonAux12V(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonaux12v[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonaux12v[0] = 0;
		vartable->buttonaux12v[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_VAR_ButtonAUX12V, 2);
	}

	return 0;
}

uint8_t SGUS_GetButtonAux24V(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonaux24v[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonaux24v[0] = 0;
		vartable->buttonaux24v[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_VAR_ButtonAUX24V, 2);
	}

	return 0;
}

uint8_t SGUS_GetButtonUserPowerOff(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*button = vartable->buttonuserpoweroff[1];

	if(0 != *button)
	{
		//Reset Button state after read it
		vartable = SGUS_GetTxVarData();
		vartable->buttonuserpoweroff[0] = 0;
		vartable->buttonuserpoweroff[1] = 0;
		SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonUserPowerOff, 2);
	}

	return 0;
}

uint8_t SGUS_SetUserPowerOffIcon(uint8_t icon)
{
	sgus_vardata_t * vartable = SGUS_GetTxVarData();
	vartable->iconuserpoweroff[0] = 0;
	vartable->iconuserpoweroff[1] = icon;

	SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_IconUserPowerOff, 2);

	return 0;
}

uint8_t SGUS_GetUserPowerOffIcon(uint8_t *icon)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
	*icon = vartable->iconuserpoweroff[1];

	return 0;
}

uint8_t SGUS_GetButtonPageSafePowerOff(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
		*button = vartable->buttonpagesafepoweroff[1];

		if(0 != *button)
		{
			//Reset Button state after read it
			vartable = SGUS_GetTxVarData();
			vartable->buttonpagesafepoweroff[0] = 0;
			vartable->buttonpagesafepoweroff[1] = 0;
			SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageSafePowerOff, 2);
		}

		return 0;
}

uint8_t SGUS_GetButtonPageUserPowerOff(uint8_t *button)
{
	sgus_vardata_t * vartable = SGUS_GetRxVarData();
		*button = vartable->buttonpageuserpoweroff[1];

		if(0 != *button)
		{
			//Reset Button state after read it
			vartable = SGUS_GetTxVarData();
			vartable->buttonpageuserpoweroff[0] = 0;
			vartable->buttonpageuserpoweroff[1] = 0;
			SGUS_SetTxQueue(QUEUE_TYPE_VAR, SGUS_Var_ButtonPageUserPowerOff, 2);
		}

		return 0;
}

uint8_t SGUS_ApiInit(uint8_t recoverflg)
{
    static uint8_t initstep = 0;
    static sgus_regindex_t regindex = 0;
    uint32_t runtime = 0;
    const sgus_reginfo_t  *reginfo;
    sgus_regdata_t *regdata;
    uint8_t rtn = 0xFF;

    if(1 == recoverflg)
    {
        regindex = 0;
        initstep = 0;    
    }

    //Init Queue
    switch(initstep)
    {
        case 0 :
            SGUS_TXQueue.count = 0;
            SGUS_TXQueue.head = 0;
            SGUS_TXQueue.tail = 0;
            
            regdata = SGUS_GetRxRegData();
            regdata->version = 0;

            SGUS_ReadRegRequest(SGUS_Reg_RunTime, 4);
            initstep++;
            break;
        case 1 :
            SGUS_GetRunTime(&runtime);
            if(0 != runtime)
            {
                SGUS_SetCurrentPage(SGUS_Page_Startup);
                initstep++;
            }
            else
            {
                SGUS_ReadRegRequest(SGUS_Reg_Version, 1);
            }
            break;
        case 2 :
            /*
            reginfo = SGUS_GetRegInfo();
            if(regindex < NumofRegIndex)
            {
                if(SGUS_REG_READABLE == (reginfo[regindex].regtype & SGUS_REG_READABLE))
                {
                    SGUS_ReadRegRequest(regindex, reginfo[regindex].regsize);
                }
                regindex++;
            }
            else
            {
                initstep++;
            }
            */
            initstep++;
            break;
        default :
        	initstep = 0;
        	regindex = 0;
            rtn = 0;
            break;
    }
    return rtn;
}



void SGUS_Transmit_Task(void) //10ms Task
{
	uint8_t indextype;
	uint8_t indexvalue;
	uint8_t indexlength;
	uint8_t indexvalid;
	uint8_t sendcnt;
    static uint8_t readstep = 0;

    sgus_pageindex_t  pageindex;
    const sgus_pageinfo_t * pageinfo;

    sgus_varindex_t   varindex_s;
    sgus_varindex_t   varindex_e;
    const sgus_varinfo_t *  varinfo;
    volatile uint8_t varsize = 0;

    uint8_t i;
    
	SGUS_GetTxQueue(&indextype, &indexvalue, &indexlength, &indexvalid);

	if(TRUE == indexvalid)//Write
	{
		sendcnt = 0;
		/*
        do
        {
        */
    		if(QUEUE_TYPE_REG == indextype)
    		{
    			SGUS_WriteReg(indexvalue, indexlength);
                if(SGUS_Reg_PicIndex == indexvalue)
                {
                    readstep = 0; //reset readstep when Pic have changed
                }
                if(SGUS_Reg_TFConfigEnable == indexvalue) //All Frame need enable/disable crc after this reg changed
                {
                	SGUS_EnableCRCFlag = !SGUS_EnableCRCFlag;
                    SGUS_CRCHangFlag = FALSE;
                }
    		}
    		else if(QUEUE_TYPE_VAR == indextype)
    		{
    			SGUS_WriteVar(indexvalue, indexlength);
    		}
/*
    		if(3 >= ++sendcnt)
    		{
    			SGUS_GetTxQueue(&indextype, &indexvalue, &indexlength, &indexvalid);
    		}
    		else
    		{
    			indexvalid = FALSE;
    		}
        }while(TRUE == indexvalid);
        */
	}
	else//Read Request
	{
        switch(readstep)
        {
            case 0 : //Step 0 Read Current Page and other Regs like timer0 request
                SGUS_ReadRegRequest(SGUS_Reg_PicIndex, 2);
                SGUS_ReadRegRequest(SGUS_Reg_RunTime, 4);
                readstep++;
                break;
            case 1 : //Step 1 Read Data request in current page in next peroid
                pageinfo = SGUS_GetPageInfo();
                varinfo  = SGUS_GetVarInfo(); 
                SGUS_GetCurrentPage(&pageindex);
                if(NumofPageIndex != pageindex)
                {
                    varindex_s = pageinfo[pageindex].varstartindex;
                    varindex_e = pageinfo[pageindex].varstopindex;
                    if(SGUS_Var_Null != varindex_s && SGUS_Var_Null != varindex_e)
                    {
                        varsize = 0;

                        for(i = varindex_s; i <= varindex_e; i++)
                        {
                            varsize += varinfo[i].varsize;
                        }
                        SGUS_ReadVarRequest(varindex_s, varsize);
                    }
                }
                readstep++;
                break;
            case 2 : //Step 2 Read Global Button request in another peroid
                varindex_s = SGUS_Var_ButtonBack;
                varindex_e = SGUS_Var_ButtonTest;
                varsize = 2*(varindex_e - varindex_s + 1);
                SGUS_ReadVarRequest(varindex_s, varsize);
                readstep++;
                break;
            default : //take a peroid break and go a new round
//            	SGUS_ReadRegRequest(SGUS_Reg_RunTime, 4);
                readstep = 0;
                break;
        }
	}
}


