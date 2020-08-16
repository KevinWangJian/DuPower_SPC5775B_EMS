


/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * Generator__: ComM / AR42.4.0.0                Module Package Version
 * Editor_____: 9.0                Tool Version
 * Model______: 2.3.0.4             ECU Parameter Definition Version
 *
 </VersionHead>*/



#ifndef  COMM_CFG_H
#define  COMM_CFG_H


/***********************************************************************************/
/*                                        INCLUDES                                 */
/***********************************************************************************/
#include "ComM_Types.h"
#include "Rte_ComM_Type.h"




/*
 ***************************************************************************************************
 * Version Information Defines
 ***************************************************************************************************
 */
/* ComM module id(according to AUTOSAR BSW module list)  */
#define COMM_MODULE_ID                 12u
/* ComM module id(according to AUTOSAR BSW module list)    */
#define COMM_VENDOR_ID                 6u
/* Version of AUTOSAR ComM specification */
/* Major Version of AUTOSAR ComM specification    */
#define COMM_AR_RELEASE_MAJOR_VERSION             4u
/* Minor Version of AUTOSAR ComM specification  */
#define COMM_AR_RELEASE_MINOR_VERSION             2u
/* Revision Version of AUTOSAR ComM specification  */
#define COMM_AR_RELEASE_REVISION_VERSION          2u
/* Version of AUTOSAR ComM implementation */
#define COMM_SW_MAJOR_VERSION          4u
/* Minor Version of AUTOSAR ComM implementation  */
#define COMM_SW_MINOR_VERSION          0u
/* Patch Version of AUTOSAR ComM implementation  */
#define COMM_SW_PATCH_VERSION          0u



/***********************************************************************************/
/*                                        DEFINES                                  */
/***********************************************************************************/

/* Define for configuration variant of ComM */

/* Macros for different config variants */

#define COMM_VARIANT_PRECOMPILE                                         0x00

#define COMM_VARIANT_POSTBUILD_LOADABLE                                 0x01

#define COMM_CONFIGURATION_VARIANT                                      COMM_VARIANT_PRECOMPILE

#define COMM_ECUC_RB_RTE_IN_USE                                         STD_ON


/*************************************************************************************/
/*                              Channel Symbolic Names                               */
/*************************************************************************************/

#define         ComMConf_ComMChannel_ComMChannel_Can_Network_1_Channel       ((NetworkHandleType)0)

#define         ComMConf_ComMChannel_ComMChannel_Can_Network_2_Channel       ((NetworkHandleType)1)

#define         ComMConf_ComMChannel_ComMChannel_Can_Network_3_Channel       ((NetworkHandleType)2)

#define         ComMConf_ComMChannel_ComMChannel_Can_Network_4_Channel       ((NetworkHandleType)3)

#define         ComMConf_ComMChannel_ComMChannel_Can_Network_5_Channel       ((NetworkHandleType)4)

#define         ComMConf_ComMChannel_ComMChannel_Can_Network_6_Channel       ((NetworkHandleType)5)

#define         ComMConf_ComMChannel_ComMChannel_Eth_Network_Channel       ((NetworkHandleType)6)

/*************************************************************************************/
/*                              User Symbolic Names                               */
/*************************************************************************************/

#define     ComMConf_ComMUser_ComMUser_Can_Network_1_Channel        ((ComM_UserHandleType)(0))

#define     ComMConf_ComMUser_ComMUser_Can_Network_2_Channel        ((ComM_UserHandleType)(1))

#define     ComMConf_ComMUser_ComMUser_Can_Network_3_Channel        ((ComM_UserHandleType)(2))

#define     ComMConf_ComMUser_ComMUser_Can_Network_4_Channel        ((ComM_UserHandleType)(3))

#define     ComMConf_ComMUser_ComMUser_Can_Network_5_Channel        ((ComM_UserHandleType)(4))

#define     ComMConf_ComMUser_ComMUser_Can_Network_6_Channel        ((ComM_UserHandleType)(5))

#define     ComMConf_ComMUser_ComMUser_Eth_Network_Channel        ((ComM_UserHandleType)(6))

/*************************************************************************************/
/*                              Pnc Symbolic Names                                   */
/*************************************************************************************/




#endif  /* #ifndef  COMM_CFG_H  */
