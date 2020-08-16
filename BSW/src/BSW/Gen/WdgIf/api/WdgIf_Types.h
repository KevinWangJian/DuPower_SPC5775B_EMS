 

 #ifndef WDGIF_TYPES_H
 #define WDGIF_TYPES_H
 /*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#if 0
#include "Std_Types.h"
#if (!defined(STD_TYPES_AR_RELEASE_MAJOR_VERSION) || (STD_TYPES_AR_RELEASE_MAJOR_VERSION != 4))
#error 揂UTOSAR major version undefined or mismatched�
#endif
#if (!defined(STD_TYPES_AR_RELEASE_MINOR_VERSION) || (STD_TYPES_AR_RELEASE_MINOR_VERSION != 2))
#error 揂UTOSAR minor version undefined or mismatched�
#endif
#endif
 /*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

#define WDGIF_TYPES_AR_RELEASE_MAJOR_VERSION            (4)
#define WDGIF_TYPES_AR_RELEASE_MINOR_VERSION            (2)
#define WDGIF_TYPES_AR_RELEASE_REVISION_VERSION         (2)
#define WDGIF_TYPES_SW_MAJOR_VERSION                    (3)
#define WDGIF_TYPES_SW_MINOR_VERSION                    (0)
#define WDGIF_TYPES_SW_PATCH_VERSION                    (0)

 /*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */
/*TRACE[WDGIF010] All type definations in WdgIf_Types.h*/
 typedef enum
 {
        WDGIF_UNINIT,
        WDGIF_IDLE,
        WDGIF_BUSY
 }WdgIf_StatusType;

 /*TRACE[WDGIF016] Definations of WdgIf Mode Type*/
 typedef enum
 {
        WDGIF_OFF_MODE,
        WDGIF_SLOW_MODE,
        WDGIF_FAST_MODE
 }WdgIf_ModeType;

 /*Old :  WdgIf_RequestType_t usage will be depriciated and later discontinued.
  *New :  WdgIf_Rb_RequestType_tst will be used instead*/
 typedef struct
 {
     VAR(uint32,AUTOMATIC)  rb_responseTime;        /* current response time in microsec */
     VAR(uint32,AUTOMATIC)  rb_timeStampLastTrans;  /* timestamp of last SPI transmission in timer ticks */
     VAR(uint8,AUTOMATIC)   rb_currentRequestMm;    /* current request of monitoring module (0..16) */
     VAR(uint8,AUTOMATIC)   rb_errorCounter;        /* value of error counter (0..7) */
     VAR(uint8,AUTOMATIC)   rb_statusBitsMm;        /* status bits of the monitoring module (bit coded) */
 } WdgIf_RequestType_t;


  typedef struct
  {
      VAR(uint32,AUTOMATIC)  tiResp_u32;          /* current response time in microsec */
      VAR(uint32,AUTOMATIC)  tiStampLastTx_u32;   /* timestamp of last SPI transmission in timer ticks */
      VAR(uint8,AUTOMATIC)   xCurrReq_u8;         /* current request of monitoring module (0..16) */
      VAR(uint8,AUTOMATIC)   cntrErr_u8;          /* value of error counter (0..7) */
      VAR(uint8,AUTOMATIC)   stMm_u8;             /* status bits of the monitoring module (bit coded) */
  } WdgIf_Rb_RequestType_tst;

#endif  /* WDGIF_TYPES_H */
