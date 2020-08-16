#include "chg_ctl.h"
#include "mt_card.h"
#include "eSCI.h"
#include "Rte_Asw_Swc.h"
#include "Rte_IoHwAb.h"

#define TIME_TEST 2000
//�ڲ�����
static uint32_t TIME_FIND_COUNT = 0;
static uint16_t TIME_VALID = TIME_TEST;  //
static uint16_t TIME_PIN = TIME_TEST;  //�û�����pin��ʱʱ��
static uint16_t TIME_PRETREATMENT = TIME_TEST;  //�û�����pin��ʱʱ��
static uint16_t TIME_CHARGE = TIME_TEST;  //�ӵ�����ȷ��ʱ��
static uint16_t TIME_STOP = TIME_TEST;  //�˵�����ȷ��ʱ��
static uint32_t TIME_MONEY = TIME_TEST;  //�������ѽ��ȷ��ʱ��
static uint16_t TIME_ADD = TIME_TEST;  //���佻��ȷ��ʱ��
static uint16_t TIME_ANT = TIME_TEST;  //�ر���Ƶȷ��ʱ��

//�ⲿд
static uint8_t IS_PIN = 1;  //�Ƿ����������PIN��
static uint32_t PIN_INPUT = 0x123456;  //�û�����PIN��
static uint32_t MONEY_INPUT = 0;  //���ѽ��,�ڽ������ʱ���븳ֵ

uint8_t cardnum[8];

//�ⲿ��
typedef enum ERROR_CODE_ENU
{
	DEFAULT,  //��ʼ״̬
	CARD_TYPE_ERROR,  //Ѱ��ʱ���ط�ϵͳ��
	CARD_EXIST_ERROR,  //Ѱ��ʱ�޿���ʱ
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
	FAIL,  //����ֵ��������
	TIMEOUT,  //��ʱ
	FIND,  //��ʼ������һ��Ѱ��������жϿ�Ƭ״̬
	FIND_REC,
	CHECK_VALID,
	CHECK_VALID_REC,
	PIN,
	PRETREATMENT,  //Ԥ����
	PRETREATMENT_REC,

	START_CHARGE,  //��ʼ�ӵ�
	START_CHARGE_REC,
	STOP_CHARGE_CHECK,
	STOP_CHARGE,   //�����ӵ�
	STOP_CHARGE_REC,
	ADD_TRAD,     //���佻��
	ADD_TRAD_REC,

	POP,           //����
	POS_SELECT,   //��λ��ѡ��
	CLOSE_ANT,     //�ر�����
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
			mt_card_find(); //����
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
            mt_card_pretreatment();  //Ԥ����
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
void MAINPROCESS()  //������
{
	static uint16_t timeout_count = 0;  //��ʱ����
	static uint8_t add_count = 0;  //���佻�׼���
	switch (STEP)
	{
	case FIND:
		mt_card_find(); //����
		STEP = FIND_REC;
		ERROR_CODE = DEFAULT;
		break;

	case FIND_REC:  //Ϊ���mt_card.c������FIND���賬ʱ   --20190827-hw 
		if (card_status == 1)  //�����п�
		{
			if (card_sys_type == 1)  //ϵͳ��
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
		//��鿨Ƭ��Ч�Ա�����Ѱ���ɹ����Զ����ͣ�����Ҫ�ֶ�����
		break;
	case CHECK_VALID_REC:
		if (status_byte == 0x59)  //��Ч�Լ����ȷ����ʾ�û�����PIN��
		{
			STEP = PIN;
			timeout_count = 0;
			status_byte = 0;
		}
		else if ((status_byte == 0x4e)  //��Ч�Լ��ʧ��
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
				STEP = TIMEOUT;  //���볬ʱģʽ�����ֶ����и�λ
				ERROR_CODE = VALID_ERROR;
				timeout_count = 0;
			}
		}

		break;
	case PIN:  //�ȴ��û�����PIN��
		if (IS_PIN == 0)
		{
			if (timeout_count++ > TIME_PIN)  //����PIN�볬ʱ
			{
				STEP = TIMEOUT;  //���볬ʱģʽ�����ֶ����и�λ
				ERROR_CODE = PIN_TIMEOUT;
				timeout_count = 0;
				status_byte = 0;
			}
		}
		else
		{
			if (CHECK_BCD(PIN_INPUT) == 1)  //PIN��ΪBCD��
			{
				mt_card_down_pin(PIN_INPUT);
//				PIN_INPUT = 0;
				STEP = PRETREATMENT;
				timeout_count = 0;
			}
			else //PIN��Ϊ��BCD��
			{
				STEP = FAIL;
				ERROR_CODE = PIN_BCD_ERROR;
				timeout_count = 0;
			}
			IS_PIN = 0;
		}
		break;

	case PRETREATMENT:
		mt_card_pretreatment();  //Ԥ����
		STEP = PRETREATMENT_REC;
		break;

	case PRETREATMENT_REC:
		if(status_byte == 0x59) // Ԥ����ɹ�
		{
			if (card_type == 0x01)  //�û���
			{
				timeout_count = 0;
				status_byte = 0;
				if (card_lock_status == 0x30)  //������Ƭ������ӵ�
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
			else  //���û���
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
			STEP = FAIL;  //�������ģʽ����������Ѱ�������ֶ����б�־����
			ERROR_CODE = PRETREATMENT_ERROR;  //�������ԭ�򣬿ɲ鿴status_byte
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
			STEP = CLOSE_ANT;  //�ӵ�ɹ�������ر�����
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
	case STOP_CHARGE_CHECK:  //�жϵ�ǰ���Ƿ��ڱ�׮��ִ�й��ӵ�
		if (1)
		{
			STEP = STOP_CHARGE;
			timeout_count = 0;
		}
		else if (0)
		{
			;  //���ѿͻ�ȥӪҵ������
		}
		else
		{
			if (timeout_count++ > TIME_STOP)
			{
				STEP = FAIL;  //�������ģʽ����������Ѱ�������ֶ����б�־����
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
		if (status_byte == 0x59)  //���佻�׳ɹ�
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
				ERROR_CODE = ADD_FAIL;  //�����ִ˴���ʱ����Ҫ���ѿͻ�ȥ����������
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

//���Ժ������������ӿڱ�����ֵ���е��ԣ���ʽ�����н�ֹʹ��
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

//���⺯��

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


