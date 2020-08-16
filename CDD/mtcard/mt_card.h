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

	CARD_FIND          //Ѱ��
	, CARD_CHECK_VALID   //��֤��Ƭ�Ϸ���
	, CARD_PRETREATMENT  //Ԥ����
	, CARD_START_CHARGE  //��ʼ�ӵ�
	, CARD_STOP_CHARGE   //�����ӵ�
	, CARD_ADD_TRAD      //���佻��

	, CARD_POP           //����
	, CARD_POS_SELECT    //��λ��ѡ��
	, CARD_CLOSE_ANT     //�ر�����

	, CARD_RECV

	, CARD_IDLE

}card_state_t;





#define SIM_1  ( 0x30 )
#define SIM_2  ( 0x31 )
#define SIM_3  ( 0x32 )
#define SIM_4  ( 0x33 )


extern uint32_t card_status;  	     //0-�������޿�, 1 �������п�   find_card
extern uint32_t card_sys_type;       //0-��ϵͳ��,   1 ϵͳ��       find_card
extern uint32_t card_type;    	     //ic type, �û������Ա����
extern uint8_t  status_byte;         //buff[5] ����״̬��
extern uint8_t  card_lock_status;    //����״̬
extern uint8_t  IC1_8[8];            //�� ID ��,
extern uint32_t card_remain_money;   //ʣ����
extern uint16_t offline_count;       //�ѻ����״���
extern uint16_t online_count;        //�������״���
extern uint32_t radom_num;           //α�����
extern uint16_t online_index;        //�����������
extern uint16_t offline_index;       //�ѻ��������
extern uint32_t now_used_money;      //���ν��׽��
extern uint8_t  trap_type_index;     //�������ͱ�ʾ
extern uint8_t  eterm[6];            //׮���
extern uint8_t  release_lock_time[7];   //���ʱ��
extern uint32_t jmac3;               //mac3

extern uint32_t pop_card;     	     //0-����ʧ��, 1-�����ɹ�
extern uint32_t pos_select; 	     //0-SIM��λ��ѡ��ʧ��, 1-SIM��λ��ѡ��ɹ�
extern uint32_t close_ant; 		     //0-no close, 1-close


void mt_card_start_charge(void);     	 //��ʼ�ӵ�
void mt_card_stop_charge(uint32_t money);//�����ӵ�
void mt_card_add_trap(void);             //���佻��

void mt_card_pop(void);                  //����
void mt_card_pos_select(uint8_t simx);   //SIM��λ��ѡ�� SIM_1,SIM_2,SIM_3,SIM_4
void mt_card_close_ant(void);            //�ر�����


void mt_card_find(void);                 //�����������������

void mt_card_down_pin(uint32_t pin);     //�·�PIN��,�˶���Ҫ��Ԥ����ǰ���
void mt_card_pretreatment(void);         //����������Ԥ������

void mt_card_process(void);              //�����Ե��ýӿڣ���̨ͨ�Ŵ���״̬������
void mt_card_recv_process(void);

card_state_t mt_get_card_state(void);




#endif /* __MT_CARD_H */

