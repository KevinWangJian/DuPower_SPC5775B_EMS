/************************************************************************************
 *
 * Copyright (c) DU-POWER New Energy Technical Co., Ltd - All rights reserved
 *
 * file name:    mt_card.c
 *
 * description:
 *  mt_card protocol analysis
 *
 *
 * revision history:
 *
 * Date           Author            Description
 * 2018/7/12	   PSM              initial version
 *
*************************************************************************************/

#include "mt_card.h"
#include "string.h"
#include "eSCI.h"

#include "pca21125.h"





#define RETRY_TIMES             ( 3 )
//115200bps  1ms-11.52bytes
//[49]=50bytes/11.52=4.34ms=5ms
//5+5=10ms ->20ms
#define PERIOD                  ( 10 )  //20ms callback
#define TIMEOUT                 ( 1000/PERIOD )

#define BUFF_SIZE               ( 50 )





uint32_t card_status = 0xff;  	      //0-卡机内无卡, 1 卡机内有卡   find_card
uint32_t card_sys_type;       //0-非系统卡,   1 系统卡       find_card
uint32_t card_type;    	      //ic type, 用户卡或或员工卡
uint8_t  status_byte;         //buff[5] 返回状态字
uint8_t  card_lock_status;    //灰锁状态
uint8_t  IC1_8[8];            //卡 ID 号,
uint32_t card_remain_money;   //剩余金额
uint16_t offline_count;       //脱机交易次数
uint16_t online_count;        //联机交易次数
uint32_t radom_num;           //伪随机数
uint16_t online_index;        //联机交易序号
uint16_t offline_index;       //脱机交易序号
uint32_t now_used_money;      //本次交易金额
uint8_t  trap_type_index;     //交易类型标示
uint8_t  eterm[6];            //桩体号
uint8_t  release_lock_time[7];   //解扣时间
uint32_t jmac3;               //mac3
uint32_t close_ant;
uint32_t pos_select;
uint32_t pop_card;     	     //0-弹卡失败, 1-弹卡成功




static card_state_t card_state, card_recv_state;

static uint8_t timeout;
static uint8_t rec_buff[BUFF_SIZE];  //default 50
static uint32_t monetary;
static uint32_t PIN_ID;

//冗余计数
static uint8_t start_charge_count;
static uint8_t stop_charge_count;
static uint8_t add_trap_count;

static uint8_t pop_count;
static uint8_t pos_sel_count;
static uint8_t pos_index;
static uint8_t close_ant_count;



//异或加密接口
static uint8_t xor_check(uint8_t*, uint8_t);

//控制流程接口
static void mt_card_find_send(void);
static void mt_card_check_valid_send(void);
static void mt_card_pretreatment_send(void);
static void mt_card_startch_send(void);
static void mt_card_stopch_send(void);
static void mt_card_addtrap_send(void);

//弹卡，位置选择，关闭天线
static void mt_card_pop_send(void);
static void mt_card_pos_select_send(void);
static void mt_card_close_ant_send(void);

//接收发送函数
static uint8_t mt_card_send(uint8_t*, uint8_t);
static uint8_t mt_card_recv(uint8_t*);
void mt_card_recv_process(void);




static uint8_t xor_check(uint8_t* pbuff, uint8_t len)
{
	uint8_t i;
	uint8_t data = 0;

	if (0 == len)
	{
		return 0;
	}

	data = pbuff[0];
	for (i = 1; i < len; ++i)  //start from 1
	{
		data ^= pbuff[i];
	}

	return data;
}


//寻卡
static void mt_card_find_send(void)
{
	uint8_t buff[7] = { 0 };

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x02; //LENGTH
	buff[3] = 0x51; //0x51
	buff[4] = 0x37; //FIND
	buff[5] = 0x03; //ETX

	buff[6] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_FIND;
	timeout = 0;
}

static void mt_card_check_valid_send(void)
{
	uint8_t buff[7] = { 0 };

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x02; //LENGTH
	buff[3] = 0x51; //0x51
	buff[4] = 0x56; //CHECK_VALID
	buff[5] = 0x03; //ETX

	buff[6] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_CHECK_VALID;
	timeout = 0;
}

static void mt_card_pretreatment_send(void)
{
	uint8_t buff[17] = { 0 };
	uint16_t year = 0;
	uint8_t  mon = 0;
	uint8_t  day = 0;
	uint8_t  hour = 0;
	uint8_t  min = 0;
	uint8_t  sen = 0;

	time_tag time_tmp;

	//pca21125_get_time(&time_tmp);
	//year = time_tmp->year+2000;
	//mon  = time_tmp->month;
	//day  = time_tmp->day;
	//hour = time_tmp->hour;
	//min  = time_tmp->minute;
	//sen  = time_tmp->second;

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x0C; //LENGTH
	buff[3] = 0x51; //0x51
	buff[4] = 0x36; //PRETREATMENT

	buff[5] = (uint8_t)(year >> 8 & 0xFF); //year
	buff[6] = (uint8_t)(year >> 0 & 0xFF); //year
	buff[7] = mon;
	buff[8] = day;
	buff[9] = hour;
	buff[10] = min;
	buff[11] = sen;
	buff[12] = (uint8_t)(PIN_ID >> 16 & 0xFF);
	buff[13] = (uint8_t)(PIN_ID >> 8 & 0xFF);
	buff[14] = (uint8_t)(PIN_ID >> 0 & 0xFF);

	buff[15] = 0x03; //ETX
	buff[16] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_PRETREATMENT;
	timeout = 0;
}

static void mt_card_startch_send(void)
{
	uint8_t buff[14] = { 0 };
	uint16_t year = 0;
	uint8_t  mon = 0;
	uint8_t  day = 0;
	uint8_t  hour = 0;
	uint8_t  min = 0;
	uint8_t  sen = 0;
	time_tag time_tmp;

	//pca21125_get_time(&time_tmp);
	//year = time_tmp->year+2000;
	//mon  = time_tmp->month;
	//day  = time_tmp->day;
	//hour = time_tmp->hour;
	//min  = time_tmp->minute;
	//sen  = time_tmp->second;

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x09; //LENGTH
	buff[3] = 0x51; //0x51
	buff[4] = 0x30; //START CHARGE
	buff[5] = (uint8_t)(year >> 8 & 0xFF);
	buff[6] = (uint8_t)(year >> 0 & 0xFF);
	buff[7] = mon;
	buff[8] = day;
	buff[9] = hour;
	buff[10] = min;
	buff[11] = sen;
	buff[12] = 0x03; //ETX

	buff[13] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_START_CHARGE;
	timeout = 0;
}

static void mt_card_stopch_send(void)
{
	uint8_t buff[18] = { 0 };
	uint16_t year = 0;
	uint8_t  mon = 0;
	uint8_t  day = 0;
	uint8_t  hour = 0;
	uint8_t  min = 0;
	uint8_t  sen = 0;
	time_tag time_tmp;

	//pca21125_get_time(&time_tmp);
	//year = time_tmp->year+2000;
	//mon  = time_tmp->month;
	//day  = time_tmp->day;
	//hour = time_tmp->hour;
	//min  = time_tmp->minute;
	//sen  = time_tmp->second;

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x0D; //LENGTH
	buff[3] = 0x51; //0x51
	buff[4] = 0x34; //STOP CHARGE
	buff[5] = (uint8_t)(monetary >> 24 & 0xFF);
	buff[6] = (uint8_t)(monetary >> 16 & 0xFF);
	buff[7] = (uint8_t)(monetary >> 8 & 0xFF);
	buff[8] = (uint8_t)(monetary >> 0 & 0xFF);
	buff[9] = (uint8_t)(year >> 8 & 0xFF);
	buff[10] = (uint8_t)(year >> 0 & 0xFF);
	buff[11] = mon;
	buff[12] = day;
	buff[13] = hour;
	buff[14] = min;
	buff[15] = sen;
	buff[16] = 0x03; //ETX

	buff[17] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_STOP_CHARGE;
	timeout = 0;
}

static void mt_card_addtrap_send(void)
{
	uint8_t buff[7] = { 0 };

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x02; //LENGTH
	buff[3] = 0x51; //0x51
	buff[4] = 0x35; //ADD TRAP
	buff[5] = 0x03; //ETX

	buff[6] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_ADD_TRAD;
	timeout = 0;
}


//MT610专用
static void mt_card_pop_send(void)
{
	uint8_t buff[7] = { 0 };

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x02; //LENGTH
	buff[3] = 0x32; //0x32
	buff[4] = 0x40; //POP
	buff[5] = 0x03; //ETX

	buff[6] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_POP;
	timeout = 0;
}

static void mt_card_pos_select_send(void)
{
	uint8_t buff[8] = { 0 };

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x03; //LENGTH
	buff[3] = 0x32; //0x32
	buff[4] = 0x41; //POS_SELECT
	buff[5] = pos_index; //SIM卡位置选择
	buff[6] = 0x03; //ETX

	buff[7] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_POS_SELECT;
	timeout = 0;
}

static void mt_card_close_ant_send(void)
{
	uint8_t buff[7] = { 0 };

	buff[0] = 0x02; //STX
	buff[1] = 0x00; //LENGTH
	buff[2] = 0x02; //LENGTH
	buff[3] = 0x34; //0x32
	buff[4] = 0x42; //CLOSE_ANT
	buff[5] = 0x03; //ETX

	buff[6] = xor_check(buff, sizeof(buff) - 1);

	mt_card_send(buff, sizeof(buff));

	card_state = CARD_RECV;
	card_recv_state = CARD_CLOSE_ANT;
	timeout = 0;
}

void mt_card_recv_process(void)
{
	uint8_t len = 0;

	len = mt_card_recv(rec_buff);

	switch (card_recv_state)
	{
	case CARD_FIND:

		if (10 == len) {

			status_byte = rec_buff[5];
			if (rec_buff[9] == xor_check(rec_buff, len - 1) && 0x59 == rec_buff[5]) {

				card_status = (rec_buff[6] == 0x30) ? 1 : 0;    //0x30卡机内有卡,0x31卡机内无卡
				card_sys_type = (rec_buff[7] == 0x30) ? 1 : 0;	//0x30系统卡,    0x31非系统卡	

				card_state = CARD_CHECK_VALID;
			}
			else {
				card_state = CARD_IDLE;
			}
		}

		break;
	case CARD_CHECK_VALID:

			if (17 == len) {
				status_byte = rec_buff[5];
				if (rec_buff[16] == xor_check(rec_buff, len - 1) && 0x59 == rec_buff[5]) {

					card_type = rec_buff[6];//卡片类型，0x01=用户卡
					card_state = CARD_IDLE;
				}
				else {
					card_state = CARD_IDLE;
				}
			}
			else {
				if (timeout++ >= TIMEOUT) //timeout 2S
				{
					card_state = CARD_IDLE;
				}
			}

		break;
		case CARD_PRETREATMENT:

			if (28 == len) {

				status_byte = rec_buff[5];
				if (rec_buff[27] == xor_check(rec_buff, len - 1) && 0x59 == rec_buff[5]) {

					card_type = rec_buff[6];
					card_lock_status = rec_buff[7];
					IC1_8[0] = rec_buff[8];
					IC1_8[1] = rec_buff[9];
					IC1_8[2] = rec_buff[10];
					IC1_8[3] = rec_buff[11];
					IC1_8[4] = rec_buff[12];
					IC1_8[5] = rec_buff[13];
					IC1_8[6] = rec_buff[14];
					IC1_8[7] = rec_buff[15];
					card_remain_money = (uint32_t)(rec_buff[16] << 24 | rec_buff[17] << 16 | rec_buff[18] << 8 | rec_buff[19]);
					offline_count = (uint16_t)(rec_buff[20] << 8 | rec_buff[21]);
					online_count = (uint16_t)(rec_buff[22] << 8 | rec_buff[23]);

					card_state = CARD_IDLE;
				}
				else {
					card_state = CARD_IDLE;
				}
			}
			else {
				if (timeout++ >= TIMEOUT) //timeout 2S
				{
					card_state = CARD_IDLE;
				}
			}

			break;
		case CARD_START_CHARGE:

			if (12 == len) {
				status_byte = rec_buff[5];
				if (rec_buff[11] == xor_check(rec_buff, len - 1) && 0x59 == rec_buff[5]) {

					card_remain_money = (uint32_t)(rec_buff[6] << 24 | rec_buff[7] << 16 | rec_buff[8] << 8 | rec_buff[9]);
				}
				else {
					if (start_charge_count++ >= RETRY_TIMES) { //三次冗余机会
						card_state = CARD_IDLE;
					}
					else {
						card_state = CARD_START_CHARGE;
					}
				}
			}
			else {
				if (timeout++ >= TIMEOUT) //timeout 2S
				{
					card_state = CARD_IDLE;
				}
			}

			break;
		case CARD_STOP_CHARGE:

			if (12 == len) {
				status_byte = rec_buff[5];
				if (rec_buff[11] == xor_check(rec_buff, len - 1) && 0x59 == rec_buff[5]) {

					card_remain_money = (uint32_t)(rec_buff[6] << 24 | rec_buff[7] << 16 | rec_buff[8] << 8 | rec_buff[9]);
				}
				else {
					if (stop_charge_count++ >= RETRY_TIMES) { //三次冗余机会
						card_state = CARD_IDLE;
					}
					else {
						card_state = CARD_STOP_CHARGE;
					}
				}
			}
			else {
				if (timeout++ >= TIMEOUT) //timeout 2S
				{
					card_state = CARD_IDLE;
				}
			}

			break;
		case CARD_ADD_TRAD:

			if (50 == len) {
				status_byte = rec_buff[5];
				if (rec_buff[49] == xor_check(rec_buff, len - 1) && 0x59 == rec_buff[5]) {

					IC1_8[0] = rec_buff[6];
					IC1_8[1] = rec_buff[7];
					IC1_8[2] = rec_buff[8];
					IC1_8[3] = rec_buff[9];
					IC1_8[4] = rec_buff[10];
					IC1_8[5] = rec_buff[11];
					IC1_8[6] = rec_buff[12];
					IC1_8[7] = rec_buff[13];
					radom_num = (uint32_t)(rec_buff[14] << 24 | rec_buff[15] << 16 | rec_buff[16] << 8 | rec_buff[17]);
					online_index = (uint16_t)(rec_buff[18] << 8 | rec_buff[19]);
					card_remain_money = (uint32_t)(rec_buff[20] << 24 | rec_buff[21] << 16 | rec_buff[22] << 8 | rec_buff[23]);
					now_used_money = (uint32_t)(rec_buff[24] << 24 | rec_buff[25] << 16 | rec_buff[26] << 8 | rec_buff[27]);
					trap_type_index = rec_buff[28];
					eterm[0] = rec_buff[29];
					eterm[1] = rec_buff[30];
					eterm[2] = rec_buff[31];
					eterm[3] = rec_buff[32];
					eterm[4] = rec_buff[33];
					eterm[5] = rec_buff[34];
					release_lock_time[0] = rec_buff[35];
					release_lock_time[1] = rec_buff[36];
					release_lock_time[2] = rec_buff[37];
					release_lock_time[3] = rec_buff[38];
					release_lock_time[4] = rec_buff[39];
					release_lock_time[5] = rec_buff[40];
					release_lock_time[6] = rec_buff[41];
					offline_index = (uint16_t)(rec_buff[42] << 8 | rec_buff[43]);
					jmac3 = (uint32_t)(rec_buff[44] << 24 | rec_buff[45] << 16 | rec_buff[46] << 8 | rec_buff[47]);
				}
				else {
					if (add_trap_count++ >= RETRY_TIMES) { //三次冗余机会
						card_state = CARD_IDLE;
					}
					else {
						card_state = CARD_ADD_TRAD;
					}
				}
			}
			else {
				if (timeout++ >= TIMEOUT) //timeout 2S
				{
					card_state = CARD_IDLE;
				}
			}

			break;
		case CARD_POP:

			if (0 != len) {
				status_byte = rec_buff[5];
				if (rec_buff[7] == xor_check(rec_buff, len - 1)) {

					pop_card = (rec_buff[5] == 0x30) ? 1 : 0;

					card_state = CARD_IDLE;
				}
				else {
					if (pop_count++ >= RETRY_TIMES) {
						pop_card = 0;
						card_state = CARD_IDLE;
					}
					else {
						pop_card = 0;
						card_state = CARD_POP;
					}
				}
			}
			else {
				if (timeout++ >= TIMEOUT) //timeout 2S
				{
					card_state = CARD_IDLE;
				}
			}

			break;
		case CARD_POS_SELECT:

			if (0 != len) {
				status_byte = rec_buff[5];
				if (rec_buff[7] == xor_check(rec_buff, len - 1)) {

					pos_select = (rec_buff[5] == 0x59) ? 1 : 0;

					card_state = CARD_IDLE;
				}
				else {
					if (pos_sel_count++ >= RETRY_TIMES) {
						pos_select = 0;
						card_state = CARD_IDLE;
					}
					else {
						pos_select = 0;
						card_state = CARD_POS_SELECT;
					}
				}
			}
			else {
				if (timeout++ >= TIMEOUT) //timeout 2S
				{
					card_state = CARD_IDLE;
				}
			}

			break;
		case CARD_CLOSE_ANT:

			if (0 != len) {
				status_byte = rec_buff[5];
				if (rec_buff[7] == xor_check(rec_buff, len - 1)) {

					close_ant = (rec_buff[5] == 0x59) ? 1 : 0;

					card_state = CARD_IDLE;
				}
				else {
					if (close_ant_count++ >= RETRY_TIMES) {
						close_ant = 0;
						card_state = CARD_IDLE;
					}
					else {
						close_ant = 0;
						card_state = CARD_CLOSE_ANT;
					}
				}
			}
			else {
				if (timeout++ >= TIMEOUT) //timeout 2S
				{
					card_state = CARD_IDLE;
				}
			}

			break;
	}

	memset(rec_buff, 0, len);

	//return 0;
}

void mt_card_process(void)
{

	switch (card_state)
	{
	case CARD_FIND:           //寻卡
			
		mt_card_find_send();
		break;
	case CARD_CHECK_VALID:    //验证卡片合法性

		mt_card_check_valid_send();
		break;
	case CARD_PRETREATMENT:   //预处理

		mt_card_pretreatment_send();
		break;
	case CARD_START_CHARGE:   //开始加电

		mt_card_startch_send();
		break;
	case CARD_STOP_CHARGE:    //结束加电

		mt_card_stopch_send();
		break;
	case CARD_ADD_TRAD:      //补充交易

		mt_card_addtrap_send();
		break;
	case CARD_POP:			 //弹卡

		mt_card_pop_send();
		break;
	case CARD_POS_SELECT:   //SIM卡位置选择

		mt_card_pos_select_send();
		break;
	case CARD_CLOSE_ANT:   //关闭天线

		mt_card_close_ant_send();
		break;


		//处理接收协议	
	case CARD_RECV:

		mt_card_recv_process();	//处理接收协议	
		break;

	case CARD_IDLE:
		//for delay 
		break;
	default:
		card_state = CARD_IDLE;
		break;
	}
}



void mt_card_find(void)
{
	card_state = CARD_FIND;
}

void mt_card_pretreatment(void)
{
	card_state = CARD_PRETREATMENT;
}

void mt_card_pop(void)
{
	card_state = CARD_POP;  	   //弹卡
	pop_count = 0;
}

void mt_card_pos_select(uint8_t index)
{
	card_state = CARD_POS_SELECT;  //SIM卡位置选择
	pos_sel_count = 0;
	pos_index = index;
}

void mt_card_close_ant(void)
{
	card_state = CARD_CLOSE_ANT;   //关闭天线
	close_ant_count = 0;
}

void mt_card_down_pin(uint32_t pin)
{
	PIN_ID = pin;
}

void mt_card_start_charge(void)
{
	card_state = CARD_START_CHARGE;   //开始加电
	start_charge_count = 0;
}

void mt_card_stop_charge(uint32_t money)
{
	card_state = CARD_STOP_CHARGE;   //结束加电
	stop_charge_count = 0;
	monetary = money;
}

void mt_card_add_trap(void)
{
	card_state = CARD_ADD_TRAD;   //补充交易
	add_trap_count = 0;
}

card_state_t mt_get_card_state(void)
{
    return card_state;
}

static uint8_t mt_card_send(uint8_t* buff, uint8_t len)
{
	//
	return ESCIComm_SendDataBuff(ESCI_F, buff, len);
}

static uint8_t mt_card_recv(uint8_t* buff)
{
	static uint8_t offset = 0;
	uint16_t value = 0;
	ESCIComm_ReceiveDataBuff(ESCI_F, buff+offset, &value);
	offset += value;
	if(offset > 0 && 0 == value)
	{
		value = offset;
		offset = 0;
	}
	else
	{
		value = 0;
	}
	return value;
}
