#ifndef BSWM_CFG_GENERAL_H
#define BSWM_CFG_GENERAL_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */

/* Autosar version information */

#define BSWM_AR_RELEASE_MAJOR_VERSION   ( 4 )

#define BSWM_AR_RELEASE_MINOR_VERSION   ( 2 )

#define BSWM_AR_RELEASE_REVISION_VERSION    ( 2 )

/* Software version information */

#define BSWM_SW_MAJOR_VERSION   ( 2 )

#define BSWM_SW_MINOR_VERSION   ( 0 )

#define BSWM_SW_PATCH_VERSION   ( 0 )

#define BSWM_RTE_IN_USE               (TRUE)

#define BSWM_CANSM_ENABLED              (TRUE)

#define BSWM_COMM_ENABLED               (TRUE)

#define BSWM_DCM_ENABLED                (TRUE)

#define BSWM_ECUM_ENABLED               (TRUE)

#define BSWM_ETHIF_ENABLED              (TRUE)

#define BSWM_ETHSM_ENABLED              (TRUE)

#define BSWM_FRSM_ENABLED               (FALSE)

#define BSWM_GENERIC_REQUEST_ENABLED    (TRUE)

#define BSWM_J1939DCM_ENABLED    		(FALSE)

#define BSWM_J1939NM_ENABLED    		(FALSE)

#define BSWM_LINSM_ENABLED              (FALSE)

#define BSWM_LINTP_ENABLED              (FALSE)

#define BSWM_NM_ENABLED                (FALSE)

#define BSWM_NVM_ENABLED                (TRUE)

#define BSWM_SCHM_ENABLED                (TRUE)

#define BSWM_SD_ENABLED                 (FALSE)

#define BSWM_RB_COMMPNC_ENABLED         (TRUE)

#define BSWM_RB_INTRPTQUEUE_MAXSIZE     (5)

#define BSWM_DEBUG                      (FALSE)

#define BSWM_DEV_ERROR_DETECT           (TRUE)

#define BSWM_VERSIONINFO_API            (TRUE)

#ifdef CONFIG
#define BSWM_CFG_MULTICORE_ENABLED       2
#else
#define BSWM_CFG_MULTICORE_ENABLED      (FALSE)
#endif

#ifdef CONFIG
#define BSWM_PRV_DMCNTRL_USED           (TRUE)   /* DeadlineMonitoringControl action is configured */
#else
#define BSWM_PRV_DMCNTRL_USED           (FALSE)  /* DeadlineMonitoringControl action is not configured */
#endif

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
 */

/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/

#endif /* BSWM_CFG_GENERAL_H  */ 
