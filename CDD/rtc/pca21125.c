/************************************************************************************
 *
 * Copyright (c) DU-POWER New Energy Technical Co., Ltd - All rights reserved 
 *
 * file name:    pca21125.c
 *
 * description:  
 *  pca21125.
 * 
 *
 * revision history:
 *
 * Date        Author           Description
 * 2018/6/8	   Psm             initial version
 *
*************************************************************************************/

#include "pca21125.h"
#include "SpiIf.h"




typedef union  {   
  uint8_t R;

  struct {
	  uint8_t RW   :1;         //0-write data 1-read data
	  uint8_t SA   :3;         //subaddress 001
      uint8_t ADDR :4;         //addr
  } B;
} Command_tag;

//second;  //02h
typedef union  {   
  uint8_t R;

  struct {
	  uint8_t RF    :1;       //
	  uint8_t ten   :3;       //
      uint8_t unit  :4;       //	
  } B;
} Second_tag;
//minute;  //03h
typedef union  {   
  uint8_t R;

  struct {
	  uint8_t      :1;       //
	  uint8_t ten  :3;       //
      uint8_t unit :4;       //
  } B;
} Minute_tag;
//hour;	 //04h
typedef union  {   
  uint8_t R;

  struct {
	  uint8_t      :2;       //
	  uint8_t ten  :2;       //24 hours mode
      uint8_t unit :4;       //
  } B;
} Hour_tag;
//day;     //05h
typedef union  {   
  uint8_t R;

  struct {
	  uint8_t      :2;       //
	  uint8_t ten  :2;       //
      uint8_t unit :4;       //	
  } B;
} Day_tag;
//weekday; //06h
typedef union  {   
  uint8_t R;

  struct {
	  uint8_t           :5;   //
      uint8_t WEEKDAYS  :3;   //
  } B;
} Weekday_tag;
//month;   //07h
typedef union  {   
  uint8_t R;

  struct {
	  uint8_t       :3;       //
	  uint8_t ten   :1;       //
      uint8_t unit  :4;       //
  } B;
} Month_tag;
//year;    //08h
typedef union  {   
  uint8_t R;

  struct {  
	  uint8_t ten   :4;       //   
      uint8_t unit  :4;       //
  } B;
} Year_tag;


static void pca21125_countdown_interrupt_enable(void);


void pca21125_init(void)
{
    //spi init
	pca21125_countdown_interrupt_enable();

	pca21125_timercount_disable(); //1min countdown timer disable, stop to reload the T value
}



static void pca21125_countdown_interrupt_enable(void)
{
	uint8_t txbuf[2] = {0};
	uint8_t rxbuf[2] = {0};
	Reg_Control_2_tag regcontrol; 
	Command_tag command;                 

	command.R = 0;
	command.B.ADDR = Control_2; //01h Control_2 register
	command.B.SA   = 001;   
	command.B.RW   = W_Data;  //write

	txbuf[0] = (uint8_t)command.R;

	regcontrol.R = 0;
	regcontrol.B.TIE   = 1;
	regcontrol.B.TI_TP = 1;     //generator a plus
	regcontrol.B.TF    = 0;     //status,clear the TF interrupt flag, write 0

	txbuf[1] = regcontrol.R;
	
	SpiIf_TransmitRtc(&txbuf[0], &rxbuf[0], 2);
}


void pca21125_timercount_enable(uint8_t count) //1min
{
	uint8_t txbuf[3] = {0};
	uint8_t rxbuf[3] = {0};
	Command_tag command;         
	Timer_control_tag timercount;

	command.R = 0;
	command.B.ADDR = Timer_control; //0Eh Timer_control register
	command.B.SA   = 001;     
	command.B.RW   = W_Data;  //write

	timercount.R     = 0;
	timercount.B.TE  = 1;           //TE 0=disable 1=enable
	timercount.B.CTD = F_1_60HZ;    //
	
	txbuf[0] = (uint8_t)command.R;
	txbuf[1] = (uint8_t)timercount.R;
	//countdown timer,the next register
	txbuf[2] = count;  //countdown_timer register  //0Fh
	
	SpiIf_TransmitRtc(&txbuf[0], &rxbuf[0], 3);
}


void pca21125_timercount_disable(void)
{
	uint8_t txbuf[3] = {0};
	uint8_t rxbuf[3] = {0};
	Command_tag command;
	Timer_control_tag timercount;
	
	command.R = 0;
	command.B.ADDR = Timer_control; //0Eh Timer_control register
	command.B.SA   = 001;     //
	command.B.RW   = W_Data;  //write
	
	timercount.R = 0;
	timercount.B.TE = 0;        // countdown timer
	timercount.B.CTD = F_1_60HZ;//F_1_60HZ
	
	txbuf[0] = (uint8_t)command.R;
	txbuf[1] = (uint8_t)timercount.R;
	txbuf[2] = 0;  //countdown_timer register
	
	SpiIf_TransmitRtc(&txbuf[0], &rxbuf[0], 3);
	
}


void pca21125_set_time(time_tag *buffer)    
{
	uint8_t txbuf[8] = {0};
	uint8_t rxbuf[8] = {0};
	Command_tag command;
	Second_tag  second;
	Minute_tag  minute;
	Hour_tag    hour;
	Day_tag     day;
	Weekday_tag weekday;
	Month_tag   month;
	Year_tag    year;

	command.R = 0;
	command.B.ADDR = Seconds; //02h Seconds register
	command.B.SA   = 001;     //
	command.B.RW   = W_Data;  //write
	
	
	txbuf[0] = (uint8_t)command.R;   //command type

	second.R = 0;
	second.B.unit = buffer->second%10;  //
	second.B.ten  = buffer->second/10;  //
	second.B.RF   = 1;                  //default = 1
	txbuf[1] = second.R;
	
	minute.R = 0;
	minute.B.unit = buffer->minute%10;
	minute.B.ten  = buffer->minute/10;
	txbuf[2] = minute.R;
	
	hour.R = 0;
	hour.B.unit = buffer->hour%10;
	hour.B.ten  = buffer->hour/10;
	txbuf[3] = hour.R;
	
	day.R = 0;
	day.B.unit = buffer->day%10;
	day.B.ten  = buffer->day/10;
	txbuf[4] = day.R;
	
	weekday.R = 0;
	weekday.B.WEEKDAYS = buffer->weekday;
	txbuf[5] = weekday.R;
	
	month.R = 0;
	month.B.unit = buffer->month%10;
	month.B.ten  = buffer->month/10;
	txbuf[6] = month.R;
	
	year.R = 0;
	year.B.unit = (buffer->year)%10;
	year.B.ten  = (buffer->year)/10;
	txbuf[7] = year.R;
	
	SpiIf_TransmitRtc(&txbuf[0], &rxbuf[0], 8);
}


//02h~0ch
void pca21125_get_time(time_tag *buffer)
{	
	uint8_t data = 0;
	uint8_t pack[8] = {0};
	Command_tag command;
	
	command.R = 0;
	command.B.ADDR = Seconds; //02h Seconds register
	command.B.SA   = 001;     //
	command.B.RW   = R_Data;  //read	
	

	data = (uint8_t)command.R;
	
	buffer->FltInfo = SpiIf_TransmitRtc(&data, &pack[0], 8);

	//BCD2DEC 
	//pack[0] = 0; ignor
	buffer->second  = (uint8_t)( (pack[1]>>4) & 0x7)*10 + (pack[1] & 0xF);
	buffer->minute  = (uint8_t)( (pack[2]>>4) & 0x7)*10 + (pack[2] & 0xF);
	buffer->hour    = (uint8_t)( (pack[3]>>4) & 0x3)*10 + (pack[3] & 0xF);
	buffer->day     = (uint8_t)( (pack[4]>>4) & 0x3)*10 + (pack[4] & 0xF);
	buffer->weekday = (uint8_t)(  pack[5] & 0x7);
	buffer->month   = (uint8_t)( (pack[6]>>4) & 0x1)*10 + (pack[6] & 0xF);
	buffer->year    = (uint8_t)( (pack[7]>>4) & 0x1)*10 + (pack[7] & 0xF);  //+2000
}
