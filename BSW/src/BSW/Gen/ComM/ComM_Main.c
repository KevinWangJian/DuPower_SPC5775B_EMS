

/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * Generator__: ComM / AR42.4.0.0                Module Package Version
 * Editor_____: 9.0                Tool Version
 * Model______: 2.3.0.4             ECU Parameter Definition Version
 *
 </VersionHead>*/



/* ---------------------------------------------------------------------*/
/* Inlcude section                                                      */
/* ---------------------------------------------------------------------*/
#include "ComM_Priv.h"



#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/*
 *  Name : ComM_MainFunction_ComMChannel_Can_Network_1_Channel
 *  Description : Main function for Bus Type COMM_BUS_TYPE_CAN channel ComMChannel_Can_Network_1_Channel
 *
 */
FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Can_Network_1_Channel(void)
{
    ComM_LChannelMainFunction(0) ;
}

/*
 *  Name : ComM_MainFunction_ComMChannel_Can_Network_2_Channel
 *  Description : Main function for Bus Type COMM_BUS_TYPE_CAN channel ComMChannel_Can_Network_2_Channel
 *
 */
FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Can_Network_2_Channel(void)
{
    ComM_LChannelMainFunction(1) ;
}

/*
 *  Name : ComM_MainFunction_ComMChannel_Can_Network_3_Channel
 *  Description : Main function for Bus Type COMM_BUS_TYPE_CAN channel ComMChannel_Can_Network_3_Channel
 *
 */
FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Can_Network_3_Channel(void)
{
    ComM_LChannelMainFunction(2) ;
}

/*
 *  Name : ComM_MainFunction_ComMChannel_Can_Network_4_Channel
 *  Description : Main function for Bus Type COMM_BUS_TYPE_CAN channel ComMChannel_Can_Network_4_Channel
 *
 */
FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Can_Network_4_Channel(void)
{
    ComM_LChannelMainFunction(3) ;
}

/*
 *  Name : ComM_MainFunction_ComMChannel_Can_Network_5_Channel
 *  Description : Main function for Bus Type COMM_BUS_TYPE_CAN channel ComMChannel_Can_Network_5_Channel
 *
 */
FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Can_Network_5_Channel(void)
{
    ComM_LChannelMainFunction(4) ;
}

/*
 *  Name : ComM_MainFunction_ComMChannel_Can_Network_6_Channel
 *  Description : Main function for Bus Type COMM_BUS_TYPE_CAN channel ComMChannel_Can_Network_6_Channel
 *
 */
FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Can_Network_6_Channel(void)
{
    ComM_LChannelMainFunction(5) ;
}

FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Eth_Network_Channel(void)
{
    ComM_LChannelMainFunction(6) ;
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"


#if (COMM_PNC_GW_ENABLED == STD_ON)



#endif /*  #if (COMM_PNC_GW_ENABLED == STD_ON)  */

#if (COMM_PNC_ENABLED == STD_ON)


/* EIRA call backs are generated for all possible bus types, depending on the bus types configred in
   ComMChannel container. This is to ensure that call backs are always available in Post-build configuration.
   Precompile : same approach is followed to keep the code same. */
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/*
 *  Name : ComM_EIRACallBack_COMM_BUS_TYPE_CAN
 *  Description : EIRA callback for bus type COMM_BUS_TYPE_CAN
 *                  This function will be called whenever EIRA signal for this bus type changes
 */
 
extern FUNC(void,COMM_CODE) ComM_EIRACallBack_COMM_BUS_TYPE_CAN(void);

FUNC(void,COMM_CODE) ComM_EIRACallBack_COMM_BUS_TYPE_CAN(void)
{
    ComM_EIRA_CallBack(0);
}

extern FUNC(void,COMM_CODE) ComM_EIRACallBack_COMM_BUS_TYPE_ETH(void);
FUNC(void,COMM_CODE) ComM_EIRACallBack_COMM_BUS_TYPE_ETH(void)
{
    ComM_EIRA_CallBack(1);
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"


#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */

/*----------------------------------------------------------------------*/

/************************************************************************/
