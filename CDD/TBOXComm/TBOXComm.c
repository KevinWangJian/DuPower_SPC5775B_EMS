
#include "typedefs.h"
#include "Rte_Asw_Swc.h"
#include "ASW_RTE.h"

#include "ETCS_Cal.h"
#include "ETCR_Cal.h"
uint8_t defaultID[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
void OCPPTestTempFix(void);
void OCPPTestInit(void)
{
	static uint8_t initonce = 1;

	if(1 == initonce)
	{
		Rte_Write_TBoxComm_OCPPPrePayment_rmb(25.0);
		Rte_Write_TBoxComm_OCPPChrgFee_rmb(2.5);
		Rte_Write_TBoxComm_OCPPDefaultUID_numb(&defaultID[0]);

		OCPPTestTempFix();
		initonce = 0;
	}
}

void OCPPTestTempFix(void)
{

}

void OCPPTestTask_100ms(void)
{
	uint8_t ccu1state, ccu2state;
	static uint8_t ccu1state_pre = 1, ccu2state_pre = 1;


	OCPPTestInit();

	ccu1state = get_GeECCR_CCU1CCUSTATE_enum();
	ccu2state = get_GeECCR_CCU2CCUSTATE_enum();

	if(4 == ccu1state_pre && 4 != ccu1state)
	{
		Rte_Write_TBoxComm_OCPPCCU1Cost_rmb(18.6);
		Rte_Write_TBoxComm_OCPPCCU1CostVld_flg(1);
	}
	if(1 == ccu1state_pre && 1 == ccu1state)
	{
		Rte_Write_TBoxComm_OCPPCCU1Cost_rmb(0);
		Rte_Write_TBoxComm_OCPPCCU1CostVld_flg(0);
	}

	if(4 == ccu2state_pre && 4 != ccu2state)
	{
		Rte_Write_TBoxComm_OCPPCCU2Cost_rmb(18.6);
		Rte_Write_TBoxComm_OCPPCCU2CostVld_flg(1);
	}
	if(1 == ccu2state_pre && 1 == ccu2state)
	{
		Rte_Write_TBoxComm_OCPPCCU2Cost_rmb(0);
		Rte_Write_TBoxComm_OCPPCCU2CostVld_flg(0);
	}

	ccu1state_pre = ccu1state;
	ccu2state_pre = ccu2state;

}
