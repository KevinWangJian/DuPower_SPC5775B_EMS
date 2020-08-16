/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
//#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif /* NOT_READY_FOR_TESTING_OR_DEPLOYMENT */



#ifndef ETHTRCV_CFG_TIME_H_
# define ETHTRCV_CFG_TIME_H_

#include "ComStack_Types.h"
#include "Std_Types.h"


/* For TJA1100 define the time how low for undervoltdetection should be wait */
#define ETHTRCV_TJA1100_UNDERVOLTDETECTION_TIMEOUT_US 1000

/* Expected interface */
/* void Eth_Cfg_TimerElapsend( uint16 l_TimeSpanInUsec_u16) */
/* Return only after the timespan is expired */
#define EthTrcv_Cfg_TimerElapsed(ts)  do{((ts)--);}while((ts)>0) /*
                                                                  *  map this to an OS Function,
                                                                  *  that provides a given delay
                                                                  *  OsTime_IsUsecTimerElapsed(ETH_TIMESPAN)
                                                                  */

#endif  //ETHTRCV_CFG_TIME_H_

/*<>
 **********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</>*/
