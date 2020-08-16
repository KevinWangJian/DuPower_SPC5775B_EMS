#include "sbc_65xx.h"
#include "FS65xx_driver.h"


uint8_t can_wkup_state;
uint8_t rtc_wkup_state;
uint8_t io0_wkup_state;
uint8_t io4_wkup_state;
uint8_t io5_wkup_state;

uint8_t lastpwr_status;
uint8_t sbc_init_status;

static void wk_source_get(void);

void sbc_65xx_fresh_watchdog(void);

void sbc_65xx_init(void)
{
	  FS65_Init();  //Init FS65xx and watchdog init

	  sbc_init_status = FS65_Error;

	  FS65_Config_NonInit(); //can enter normal module

	  sbc_65xx_fresh_watchdog();

	  FS65_ReleaseFS0andFS1out();

	  wk_source_get();  //get wk source

	  //sbc_65xx_can_wkup(1);				//disable CAN wake up
}

void sbc_65xx_enter_lpoff_mode(void)
{
	FS65_UpdateRegisterContent(MODE_ADR);
	FS65_UpdateRegisterContent(DIAG_SF_ERR_ADR);
	FS65_UpdateRegisterContent(DIAG_SF_ERR_ADR);
	FS65_UpdateRegisterContent(RELEASE_FSxB_ADR);

	FS65_SetLPOFFmode();
}

void sbc_65xx_fresh_watchdog(void)
{
	FS65_FreshWatchdog();
}

void sbc_65xx_reset(void)
{
	FS65_SetLPOFFmode_autoWU(); //entern lpoff model 1ms, then all registers set default value
}

static void wk_source_get(void)
{

	can_wkup_state = (uint8_t)(reset_source >> 0 & 0x01);  //can or lin wu
	//FS65_UpdateRegisterContent(CAN_LIN_MODE_ADR);
	//can_wkup_state = (uint8_t)(INTstruct.CAN_LIN_MODE.R >> 1 & 0x01);  //can_wu
	rtc_wkup_state = (uint8_t)(reset_source >> 1 & 0x01);  //ldt
	io0_wkup_state = (uint8_t)(reset_source >> 3 & 0x01);  //io0
	//io2_wkup_state = (uint8_t)(reset_source >> 4 & 0x01);  //io4
	//io3_wkup_state = (uint8_t)(reset_source >> 5 & 0x01);  //io5
	io4_wkup_state = (uint8_t)(reset_source >> 6 & 0x01);  //io4
	io5_wkup_state = (uint8_t)(reset_source >> 7 & 0x01);  //io5

	//ldt
	if(rtc_wkup_state){
		lastpwr_status = 3;
		return;
	}
	//sleep
	FS65_UpdateRegisterContent(MODE_ADR);
	if(1 == (INTstruct.MODE.R>>0 & 0x01)){
		lastpwr_status = 2;
		return ;
	}
	//the last one
	lastpwr_status = 0;
}



void sbc_65xx_can_wkup(uint8_t status) //enable or disable
{
	if(status){
		FS65_SetCANmode(CAN_SLEEP_WU);          //sleep and wakeup
	}else{
		FS65_SetCANmode(CAN_SLEEP);             //sleep buf no wakeup
	}
}



uint8_t sbc_65xx_get_vpre_ov_uv_flg(uint8_t *ov, uint8_t *uv)
{
	uint8_t ret = 0;

	ret = FS65_UpdateRegisterContent(DIAG_VPRE_ADR);

	*ov = (uint8_t)(INTstruct.DIAG_VPRE.R>>3 & 0x01);
	*uv = (uint8_t)(INTstruct.DIAG_VPRE.R>>2 & 0x01);

	return ret;
}

uint8_t sbc_65xx_get_vcore_ov_uv_flg(uint8_t *ov, uint8_t *uv)
{
	uint8_t ret = 0;

	ret = FS65_UpdateRegisterContent(DIAG_VCORE_ADR);

	*ov = (uint8_t)(INTstruct.DIAG_VCORE.R>>3 & 0x01);
	*uv = (uint8_t)(INTstruct.DIAG_VCORE.R>>2 & 0x01);

	return ret;
}

uint8_t sbc_65xx_get_vcca_ov_uv_flg(uint8_t *ov, uint8_t *uv)
{
	uint8_t ret = 0;

	ret = FS65_UpdateRegisterContent(DIAG_VCCA_ADR);

	*ov = (uint8_t)(INTstruct.DIAG_VCCA.R>>3 & 0x01);
	*uv = (uint8_t)(INTstruct.DIAG_VCCA.R>>2 & 0x01);

	return ret;
}

uint8_t sbc_65xx_get_vaux_ov_uv_flg(uint8_t *ov, uint8_t *uv)
{
	uint8_t ret = 0;

	ret = FS65_UpdateRegisterContent(DIAG_VAUX_ADR);

	*ov = (uint8_t)(INTstruct.DIAG_VAUX.R>>3 & 0x01);
	*uv = (uint8_t)(INTstruct.DIAG_VAUX.R>>2 & 0x01);

	return ret;
}

uint8_t sbc_65xx_get_vcan_ov_uv_flg(uint8_t *ov, uint8_t *uv)
{
	uint8_t ret = 0;

	ret = FS65_UpdateRegisterContent(DIAG_VSUP_VCAN_ADR);

	*ov = (uint8_t)(INTstruct.DIAG_VSUP_VCAN.R>>3 & 0x01);
	*uv = (uint8_t)(INTstruct.DIAG_VSUP_VCAN.R>>2 & 0x01);

	return ret;
}

uint8_t sbc_65xx_get_can_status(uint8_t *status)
{
	uint8_t ret  = 0;
	uint8_t data = 0;

	ret = FS65_UpdateRegisterContent(DEVICE_ID_ADR);

	data = (uint8_t)(INTstruct.DEVICE_ID.R>>13 & 0x01); //can_G
	if(0 == data){
		*status = 1;
	}else{
		*status = 0;
	}

	return ret;
}

uint8_t sbc_65xx_get_rstpin_status(uint8_t *status)
{
	uint8_t ret = 0;

	ret = FS65_UpdateRegisterContent(RELEASE_FSxB_ADR);
	//bit0 = RSTB_SNS
	*status = (uint8_t)(INTstruct.RELEASE_FSxB.R>>0 & 0x01); //status=1, pin is high, status=0, pin is low

	return ret;
}




