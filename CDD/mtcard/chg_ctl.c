#include "chg_ctl.h"
#include "mt_card.h"
#include "eSCI.h"
#include "Rte_Asw_Swc.h"
#include "Rte_IoHwAb.h"

#define TIME_TEST 2000
//内部变量
static uint32_t TIME_FIND_COUNT = 0;
static uint16_t TIME_VALID = TIME_TEST;  //
static uint16_t TIME_PIN = TIME_TEST;  //用户输入pin超时时间
static uint16_t TIME_PRETREATMENT = TIME_TEST;  //用户输入pin超时时间
static uint16_t TIME_CHARGE = TIME_TEST;  //加电命令确认时间
static uint16_t TIME_STOP = TIME_TEST;  //退电命令确认时间
static uint32_t TIME_MONEY = TIME_TEST;  //输入消费金额确认时间
static uint16_t TIME_ADD = TIME_TEST;  //补充交易确认时间
static uint16_t TIME_ANT = TIME_TEST;  //关闭射频确认时间

//外部写
static uint8_t IS_PIN = 1;  //是否已完成输入PIN码
static uint32_t PIN_INPUT = 0x123456;  //用户输入PIN码
static uint32_t MONEY_INPUT = 0;  //消费金额,在结束充电时必须赋值

uint8_t cardnum[8];

//外部读
typedef enum ERROR_CODE_ENU
{
	DEFAULT,  //初始状态
	CARD_TYPE_ERROR,  //寻卡时返回非系统卡
	CARD_EXIST_ERROR,  //寻卡时无卡超时
	VALID_ERROR,
	PIN_TIMEOUT,
	PIN_BCD_ERROR,
	CARD_USER_ERROR,
	PRETREATMENT_ERROR,
	PRETREATMENT_TIMEOUT,
	CHARGE_FAIL,
	CHARGE_TIMEOUT,
	STOP_CHECK_FAIL,
	STOP_CHECK_TIMEOUT,
	STOP_MONEY_FAIL,
	STOP_FAIL,
	STOP_TIMEOUT,
	ADD_FAIL,
	ADD_TIMEOUT,
	ANT_FAIL,
	ANT_TIMEOUT


}ERROR_TYPE;
static ERROR_TYPE ERROR_CODE = DEFAULT;

typedef enum step_typ
{
    IDLE,
	FAIL,  //错误值，不动作
	TIMEOUT,  //超时
	FIND,  //开始，发送一个寻卡命令，并判断卡片状态
	FIND_REC,
	CHECK_VALID,
	CHECK_VALID_REC,
	PIN,
	PRETREATMENT,  //预处理
	PRETREATMENT_REC,

	START_CHARGE,  //开始加电
	START_CHARGE_REC,
	STOP_CHARGE_CHECK,
	STOP_CHARGE,   //结束加电
	STOP_CHARGE_REC,
	ADD_TRAD,     //补充交易
	ADD_TRAD_REC,

	POP,           //弹卡
	POS_SELECT,   //卡位置选择
	CLOSE_ANT,     //关闭天线
	CLOSE_ANT_REC,
	END


}STEP_ENU;
static STEP_ENU STEP = IDLE;

uint8_t CHECK_BCD(uint32_t bcd_input);

void MAINPROCESS()
{
    uint8_t i;

    uint8_t cardreadreq = 0;
    static uint8_t cardreadreqpre = 0; 
	static uint8_t faultcnt = 0;
    static uint8_t recvtimeout = 0;
    
	switch(STEP)
	{
		case IDLE :
			//Do nothin or some hook Func;
			Rte_Read_TouchPanel_ReadID_flg(&cardreadreq);
            if(TRUE == cardreadreq && FALSE ==  cardreadreqpre)
            {
                STEP = FIND;
			    faultcnt = 0;
                Rte_Write_MtCard_CarPass_flg(0);
            }
            cardreadreqpre = cardreadreq;
			break;
		case FIND :
			mt_card_find(); //读卡
    		STEP = FIND_REC;
            card_sys_type = 0; 
            card_type = 0;
            recvtimeout = 250;
			break;
		case FIND_REC :
			if(CARD_IDLE == mt_get_card_state())//if Find end, card state become IDLE)
			{
                if (1 == card_sys_type && 1 == card_type)  //Card Exit and is user card;
    			{
                    card_sys_type = 0;
                    card_type = 0;
                    STEP = PRETREATMENT;
    			}
				else
				{
                    STEP = FIND;
                }
                faultcnt = 0;
                recvtimeout = 250;
			}
			
		    if(0 == --recvtimeout)//If Timeout, refind
		    {
				STEP = FIND;
				faultcnt++;
			}
			//if faultcnt > 3 can't get info with cardreader
			if(3 < faultcnt)
			{
//				STEP = FAIL;
			}

            Rte_Read_TouchPanel_ReadID_flg(&cardreadreq);//Get Read Card Request
			if(FALSE == cardreadreq)//If False
			{
				STEP = IDLE;
			}
			break;
        case PRETREATMENT :
            mt_card_down_pin(PIN_INPUT);
            mt_card_pretreatment();  //预处理
		    STEP = PRETREATMENT_REC;
            break;
        case PRETREATMENT_REC:
            if(CARD_IDLE == mt_get_card_state())
            {
                if(1 == card_type)
                {
                    for(i = 0; i < 8; i++)
                    {
                        cardnum[i] = IC1_8[i];
                    }
                    Rte_Write_MtCard_CarID_Value(cardnum);
                    Rte_Write_MtCard_CarPass_flg(1);//Set info to rte;
                    STEP = IDLE;
                }
                else
                {
                    STEP = FIND;
                }
            }

            if(0 == --recvtimeout)//If Timeout, refind
		    {
				STEP = FIND;
				faultcnt++;
			}
            //if faultcnt > 3 can't get info with cardreader
			if(3 < faultcnt)
			{
//				STEP = FAIL;
			}
            break;
		case FAIL :
			STEP = IDLE;
			break;
		default :
			break;
			
	}
}

#if 0
void MAINPROCESS()  //主流程
{
	static uint16_t timeout_count = 0;  //超时计数
	static uint8_t add_count = 0;  //补充交易计数
	switch (STEP)
	{
	case FIND:
		mt_card_find(); //读卡
		STEP = FIND_REC;
		ERROR_CODE = DEFAULT;
		break;

	case FIND_REC:  //为配合mt_card.c，接收FIND不设超时   --20190827-hw 
		if (card_status == 1)  //卡机有卡
		{
			if (card_sys_type == 1)  //系统卡
			{
				STEP = CHECK_VALID;
				status_byte = 0;
				TIME_FIND_COUNT = 0;
			}
			else
			{
				STEP = FAIL;
				ERROR_CODE = CARD_TYPE_ERROR;
				TIME_FIND_COUNT = 0;
			}
			timeout_count = 0;
		}
		else if (card_status == 0xff)
		{
		    TIME_FIND_COUNT++;
		}
		else
			{
			STEP = END;
			ERROR_CODE = CARD_EXIST_ERROR;
			TIME_FIND_COUNT = 0;
		    timeout_count = 0;
			}

		break;
	case CHECK_VALID:
		STEP = CHECK_VALID_REC;
		//检查卡片有效性报文在寻卡成功后自动发送，不需要手动发送
		break;
	case CHECK_VALID_REC:
		if (status_byte == 0x59)  //有效性检查正确，提示用户输入PIN码
		{
			STEP = PIN;
			timeout_count = 0;
			status_byte = 0;
		}
		else if ((status_byte == 0x4e)  //有效性检查失败
			|| (status_byte == 0x47)
			|| (status_byte == 0x48)
			|| (status_byte == 0x23)
			)
		{
			STEP = FAIL;
			ERROR_CODE = VALID_ERROR;
			timeout_count = 0;
		}
		else
		{
			if (timeout_count++ > TIME_VALID)
			{
				STEP = TIMEOUT;  //进入超时模式，需手动进行复位
				ERROR_CODE = VALID_ERROR;
				timeout_count = 0;
			}
		}

		break;
	case PIN:  //等待用户输入PIN码
		if (IS_PIN == 0)
		{
			if (timeout_count++ > TIME_PIN)  //输入PIN码超时
			{
				STEP = TIMEOUT;  //进入超时模式，需手动进行复位
				ERROR_CODE = PIN_TIMEOUT;
				timeout_count = 0;
				status_byte = 0;
			}
		}
		else
		{
			if (CHECK_BCD(PIN_INPUT) == 1)  //PIN码为BCD码
			{
				mt_card_down_pin(PIN_INPUT);
//				PIN_INPUT = 0;
				STEP = PRETREATMENT;
				timeout_count = 0;
			}
			else //PIN码为非BCD码
			{
				STEP = FAIL;
				ERROR_CODE = PIN_BCD_ERROR;
				timeout_count = 0;
			}
			IS_PIN = 0;
		}
		break;

	case PRETREATMENT:
		mt_card_pretreatment();  //预处理
		STEP = PRETREATMENT_REC;
		break;

	case PRETREATMENT_REC:
		if(status_byte == 0x59) // 预处理成功
		{
			if (card_type == 0x01)  //用户卡
			{
				timeout_count = 0;
				status_byte = 0;
				if (card_lock_status == 0x30)  //正常卡片，进入加电
				{
					STEP = START_CHARGE;
				}
				else if (card_lock_status == 0x31)
				{
					STEP = STOP_CHARGE_CHECK;
				}
				else if (card_lock_status == 0x32)
				{
					STEP = ADD_TRAD;
				}
				else
				{
				}				
			}
			else  //非用户卡
			{
				STEP = FAIL;
				ERROR_CODE = CARD_USER_ERROR;
			}
			timeout_count = 0;
		}
		else if((status_byte == 0x4e)
			|| (status_byte == 0x47)
			|| (status_byte == 0x48)
			|| (status_byte == 0x23)
			|| (status_byte == 0x45)
			|| (status_byte == 0x83)
			)
		{
			STEP = FAIL;  //进入错误模式，如需重新寻卡，需手动进行标志重置
			ERROR_CODE = PRETREATMENT_ERROR;  //具体错误原因，可查看status_byte
			timeout_count = 0;
		}
		else
		{
			if (timeout_count++ > TIME_PRETREATMENT)
			{
				STEP = TIMEOUT;
				ERROR_CODE = PRETREATMENT_TIMEOUT;
				timeout_count = 0;
			}
		}

		break;

	case START_CHARGE:
		mt_card_start_charge();
		STEP = START_CHARGE_REC;
		break;

	case START_CHARGE_REC:
		if (status_byte == 0x59)
		{			
			STEP = CLOSE_ANT;  //加电成功，进入关闭天线
			timeout_count = 0;
		}
		else if ((status_byte == 0x4e) || (status_byte == 0x45))
		{
			STEP = FAIL;
			ERROR_CODE = CHARGE_FAIL;
			timeout_count = 0;
		}
		else
		{
			if (timeout_count++ > TIME_CHARGE)
			{
				STEP = TIMEOUT;
				ERROR_CODE = CHARGE_TIMEOUT;
				timeout_count = 0;
			}
		}
		break;
	case STOP_CHARGE_CHECK:  //判断当前卡是否在本桩体执行过加电
		if (1)
		{
			STEP = STOP_CHARGE;
			timeout_count = 0;
		}
		else if (0)
		{
			;  //提醒客户去营业厅解锁
		}
		else
		{
			if (timeout_count++ > TIME_STOP)
			{
				STEP = FAIL;  //进入错误模式，如需重新寻卡，需手动进行标志重置
				ERROR_CODE = STOP_CHECK_TIMEOUT;
				timeout_count = 0;
			}
		}
		break;

	case STOP_CHARGE:
		if (MONEY_INPUT == 0)
		{
			if (timeout_count++ > TIME_MONEY)
			{
				STEP = FAIL;
				ERROR_CODE = STOP_MONEY_FAIL;
				timeout_count = 0;
			}
		}
		else
		{
			mt_card_stop_charge(MONEY_INPUT);
			MONEY_INPUT = 0;
			STEP = STOP_CHARGE_REC;
			timeout_count = 0;
		}
		break;

	case STOP_CHARGE_REC:
		if (status_byte == 0x59)
		{
			STEP = CLOSE_ANT;
			timeout_count = 0;
		}
		else if (status_byte == 0x43)
		{
			STEP = PRETREATMENT;
			timeout_count = 0;
		}
		else if ((status_byte == 0x4e)
			|| (status_byte == 0x45))
		{
			STEP = FAIL;
			ERROR_CODE = STOP_FAIL;
			timeout_count = 0;
		}
		else
		{
			if (timeout_count++ > TIME_CHARGE)
			{
				STEP = TIMEOUT;
				ERROR_CODE = STOP_TIMEOUT;
				timeout_count = 0;
			}
		}


		break;
	case ADD_TRAD:
		if (status_byte == 0x59)  //补充交易成功
		{
			STEP = CLOSE_ANT;
			timeout_count = 0;
			add_count = 0;
		}
		else if (status_byte == 0x4e)
		{
			if (add_count++ >= 3)
			{
				add_count = 0;
				STEP = FAIL;
				ERROR_CODE = ADD_FAIL;  //当出现此错误时，需要提醒客户去发卡方解锁
				timeout_count = 0;
			}
			else
			{
				STEP = PRETREATMENT;
				timeout_count = 0;

			}
		}
		else
		{
			if (timeout_count++ > TIME_CHARGE)
			{
				STEP = TIMEOUT;
				ERROR_CODE = ADD_TIMEOUT;
				timeout_count = 0;
				add_count = 0;
			}
		}
		break;
	case CLOSE_ANT:
		mt_card_close_ant();
		STEP = CLOSE_ANT_REC;
		break;
	case CLOSE_ANT_REC:
		if (status_byte == 0x59)
		{
			STEP = END;
		}
		else if (status_byte == 0x4e)
		{
			STEP = FAIL;
			ERROR_CODE = ANT_FAIL;
		}
		else
		{
			if (timeout_count++ > TIME_ANT)
			{
				STEP = TIMEOUT;
				ERROR_CODE = ADD_TIMEOUT;
				timeout_count = 0;
			}
		}
		break;
		case FAIL:
			break;

		case TIMEOUT:
			break;


	}	
}
#endif
uint8_t CHECK_BCD(uint32_t bcd_input)
{
	/*if (((bcd_input >> 16 & 0xFF) < 10)
		&& ((bcd_input >> 8 & 0xFF) < 10)
		&& ((bcd_input >> 0 & 0xFF) < 10)
		)
	{
		return 1;
	}
	else
	{
		return 0;
	}*/
	return 1;
}

//调试函数，用作给接口变量赋值进行调试，正式代码中禁止使用
/*
void Testfun()
{
	if (STEP == PIN)
	{
		IS_PIN = 1;	
		PIN_INPUT = 0x123456;
	}
	if (STEP == STOP_CHARGE)
	{
		MONEY_INPUT = 10;
	}
}
*/

//对外函数

void STARTFIND()
{
	STEP = FIND;
}

void SETPIN(uint32_t pin_par)
{
	PIN_INPUT = pin_par;
	IS_PIN = 1;
}

void SETMONEY(uint32_t money_par)
{
	MONEY_INPUT = money_par;
}

uint32_t GETSTEP()
{
	return STEP;
}

uint32_t GETERROR_CODE()
{
	return ERROR_CODE;
}

void TimeTaskcard()
{
    static int timecount = 0;

	if(timecount < 10)
	{
		timecount++;
	}
	else
	{
	    MAINPROCESS();
        mt_card_process();
//	    Testfun();
	}
}


