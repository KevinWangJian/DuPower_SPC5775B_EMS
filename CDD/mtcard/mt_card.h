/************************************************************************************
 *
 * Copyright (c) DU-POWER New Energy Technical Co., Ltd - All rights reserved
 *
 * file name:    mt_card.h
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
#ifndef __MT_CARD_H
#define __MT_CARD_H

#include "typedefs.h"


typedef enum CARD_STATE {

	CARD_FIND          //寻卡
	, CARD_CHECK_VALID   //验证卡片合法性
	, CARD_PRETREATMENT  //预处理
	, CARD_START_CHARGE  //开始加电
	, CARD_STOP_CHARGE   //结束加电
	, CARD_ADD_TRAD      //补充交易

	, CARD_POP           //弹卡
	, CARD_POS_SELECT    //卡位置选择
	, CARD_CLOSE_ANT     //关闭天线

	, CARD_RECV

	, CARD_IDLE

}card_state_t;





#define SIM_1  ( 0x30 )
#define SIM_2  ( 0x31 )
#define SIM_3  ( 0x32 )
#define SIM_4  ( 0x33 )


extern uint32_t card_status;  	     //0-卡机内无卡, 1 卡机内有卡   find_card
extern uint32_t card_sys_type;       //0-非系统卡,   1 系统卡       find_card
extern uint32_t card_type;    	     //ic type, 用户卡或或员工卡
extern uint8_t  status_byte;         //buff[5] 返回状态字
extern uint8_t  card_lock_status;    //灰锁状态
extern uint8_t  IC1_8[8];            //卡 ID 号,
extern uint32_t card_remain_money;   //剩余金额
extern uint16_t offline_count;       //脱机交易次数
extern uint16_t online_count;        //联机交易次数
extern uint32_t radom_num;           //伪随机数
extern uint16_t online_index;        //联机交易序号
extern uint16_t offline_index;       //脱机交易序号
extern uint32_t now_used_money;      //本次交易金额
extern uint8_t  trap_type_index;     //交易类型标示
extern uint8_t  eterm[6];            //桩体号
extern uint8_t  release_lock_time[7];   //解扣时间
extern uint32_t jmac3;               //mac3

extern uint32_t pop_card;     	     //0-弹卡失败, 1-弹卡成功
extern uint32_t pos_select; 	     //0-SIM卡位置选择失败, 1-SIM卡位置选择成功
extern uint32_t close_ant; 		     //0-no close, 1-close


void mt_card_start_charge(void);     	 //开始加电
void mt_card_stop_charge(uint32_t money);//结束加电
void mt_card_add_trap(void);             //补充交易

void mt_card_pop(void);                  //弹卡
void mt_card_pos_select(uint8_t simx);   //SIM卡位置选择 SIM_1,SIM_2,SIM_3,SIM_4
void mt_card_close_ant(void);            //关闭天线


void mt_card_find(void);                 //控制器发起读卡动作

void mt_card_down_pin(uint32_t pin);     //下发PIN码,此动作要在预处理前完成
void mt_card_pretreatment(void);         //控制器发起预处理动作

void mt_card_process(void);              //周期性调用接口，后台通信处理状态机功能
void mt_card_recv_process(void);

card_state_t mt_get_card_state(void);




#endif /* __MT_CARD_H */

