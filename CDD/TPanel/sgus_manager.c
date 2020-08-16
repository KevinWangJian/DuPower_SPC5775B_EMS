#include "sgus_api.h"

#include "sgus_io.h"
#include "Rte_Asw_Swc.h"
#include "Rte_IoHwAb.h"
#include "Pwm.h"
#include "eep.h"

/* SGUS_ALIVE_TASK Defines and variables*/
#define SGUS_ALIVE_TEST_LIMIT    10 //run in 500ms peroid, so 5000ms is enough
static uint8_t SGUS_AliveFlag = TRUE;

SGUS_StationInputCtl_eeprom readdata;
uint8_t SGUS_Init(uint8_t recoverflg)
{
    static uint8_t initstep = 0;
    static uint8_t initonce = 1;
    uint8_t initresult;

    if(1 == initonce)
    {

        SGUS_IO_Read_InputControl((uint8_t*)&readdata);
        if(0 != memcmp(&readdata.flgname[0],"Inputflg",8))
        {
        	memcpy(&readdata.flgname[0],"Inputflg",8);
        	readdata.value = 0;
        	SGUS_IO_Store_InputControl((uint8_t*)&readdata);
        }
        Rte_Write_TouchPanel_StationInputCtl_enum(readdata.value);
        initonce = 0;
    }
    
    if(1 == recoverflg)
    {
        initstep = 0;
    }
    
    if(0 == initstep)
    {
        initresult = SGUS_ApiInit(recoverflg);
        if(0 == initresult)
        {
            initresult = 0xFF;
            initstep++;
        }
    }
    else
    {
        SGUS_StateInit();
        initresult = 0;
        initstep = 0;
    }
    return initresult;
}


void SGUS_IOUpdate_Task(void) //Input/Output Data/Flag Update 10ms, Data or Flag in this Func is interactive with outside of SGUS
{
    
}



void SGUS_AliveTest_Task(void) //TASK PEROID 100ms
{
    uint32_t runtimecur = 0;
    static uint32_t runtimepre = 0;
    static uint8_t testcnt = 0;

    SGUS_GetRunTime(&runtimecur);

    if(runtimepre == runtimecur)
    {
        testcnt++;
    }
    else
    {
        
        testcnt = 0;
    }

    runtimepre = runtimecur;

    if(testcnt >= SGUS_ALIVE_TEST_LIMIT)
    {
        testcnt = SGUS_ALIVE_TEST_LIMIT;
        SGUS_AliveFlag = FALSE;
    }
    else
    {
        SGUS_AliveFlag = TRUE;
    }
}

uint8_t SGUS_GetAliveFlag(void)
{
    return SGUS_AliveFlag;
}


void SGUS_Manager_Task(void) //State Machine in this Func 100ms Peroid
{
    static uint8_t SGUS_WorkState = SGUS_INIT;  //Initial Value
    static uint8_t inittimecnt = 0; //Init Timeout Count; if can't init within 20S, goto FAULT;
    static uint8_t recoverflag = 0; //Recover Flag; if ReInit From FAULT; Set this Flag to true
    static uint8_t buserrorcnt = 0; //Bus Error Count; If Bus Error More than 10S, goto FAULT;
    
    uint8_t initresult;
    
    switch(SGUS_WorkState)
    {
        case SGUS_INIT :
            initresult  = SGUS_Init(recoverflag);
            recoverflag = 0;
            if(0 == initresult)
            {
                
                SGUS_WorkState = SGUS_WORK;
            }
            else
            {
                inittimecnt++;
                if(inittimecnt > 80)
                {
                    SGUS_WorkState = SGUS_FAULT;
                }
            }
            break;
        case SGUS_WORK :
            SGUS_State_Task();
            if(FALSE == SGUS_GetAliveFlag())
            {
                SGUS_WorkState = SGUS_BUSERR;
            }
            break;
        case SGUS_BUSERR :
            buserrorcnt++;
            if(buserrorcnt > 40)
            {
                SGUS_WorkState = SGUS_FAULT;
            }
            if(TRUE == SGUS_GetAliveFlag())
            {
                SGUS_WorkState = SGUS_WORK;
                buserrorcnt = 0;
            }
            break;
        case SGUS_FAULT :
            if(TRUE == SGUS_GetAliveFlag())
            {
                inittimecnt = 0;
                buserrorcnt = 0;
                recoverflag = 1;
                SGUS_WorkState = SGUS_INIT;
            }
            break;
        default :
            break;
    }
    
    SGUS_AliveTest_Task();
    
    Rte_Write_TouchPanel_TPSTATE_enum(SGUS_WorkState);
}

void SGUS_Task_10ms(void)
{
    static uint8_t managerperiod = 10;

    if(++managerperiod >= 50)
    {
        SGUS_Manager_Task();
        managerperiod = 0;
    }

    SGUS_Recieve_Task();
    if(managerperiod%2)
    {
    	SGUS_Transmit_Task();
    }

    SGUS_IOUpdate_Task();
}


