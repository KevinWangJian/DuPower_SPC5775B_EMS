#ifndef __SBC_65XX_H
#define __SbC_65XX_H


#include "typedefs.h"


#define	INT_CEIL_PRIORITY	12	///ceil priority has to be equal to the highest priority of interrupts sharing DSPI to communicate with FS65xx


extern uint32_t reset_source;        //report the reset source
extern uint8_t lastpwr_status;
extern uint8_t sbc_init_status;

extern uint8_t can_wkup_state;
extern uint8_t rtc_wkup_state;
extern uint8_t io0_wkup_state;
extern uint8_t io4_wkup_state;
extern uint8_t io5_wkup_state;


void sbc_65xx_init(void);
void sbc_65xx_enter_lpoff_mode(void);
void sbc_65xx_fresh_watchdog(void);
void sbc_65xx_reset(void);


void sbc_65xx_can_wkup(uint8_t status); //enable or disable

uint8_t sbc_65xx_get_vpre_ov_uv_flg( uint8_t *ov,  uint8_t *uv);
uint8_t sbc_65xx_get_vcore_ov_uv_flg(uint8_t *ov,  uint8_t *uv);
uint8_t sbc_65xx_get_vcca_ov_uv_flg( uint8_t *ov,  uint8_t *uv);
uint8_t sbc_65xx_get_vaux_ov_uv_flg( uint8_t *ov,  uint8_t *uv);
uint8_t sbc_65xx_get_vcan_ov_uv_flg( uint8_t *ov,  uint8_t *uv);

uint8_t sbc_65xx_get_can_status(uint8_t *status);
uint8_t sbc_65xx_get_rstpin_status(uint8_t *status);



#endif /* __SBC_65XX_H */
