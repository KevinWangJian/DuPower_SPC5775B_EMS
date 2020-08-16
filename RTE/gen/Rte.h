/** @file         Rte.h
  *
  * @brief        RTE header file
  *
  * @copyright    Copyright 2007-2008 ETAS Engineering Tools Application and Services Ltd.
  *               Copyright 2008-2016 ETAS GmbH.
  *
  * @note         PLATFORM DEPENDENT [yes/no]: no
  *
  * @note         TO BE CHANGED BY USER [yes/no]: no
  *
  * Template:     Id: Rte_h.template 58851 2016-11-17 17:54:50Z DIX9YOK
  */


#ifndef RTE_H
#define RTE_H

#include "Rte_UserCfg.h"

#if defined(RTE_LIBC_MEMCPY)
#include <string.h>    /* for memcpy */
#endif /* defined(RTE_LIBC_MEMCPY) */

#include <Std_Types.h>                                    /* [$Satisfies $SWS 1164] */
/* rte_srd_req 96 end */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------------------------------------*/
/* Prototype for RTE Tick function that is generated in Rte.c only if there are
 * Alarms used.
 */

void Rte_Tick_Timeouts(void);

/*---------------------------------------------------------------------------*/
/* Target concurrency control */

#define RTE_ATOMIC(op)          ( Rte_SuspendOSInterrupts(), (op), Rte_ResumeOSInterrupts() )

#ifndef RTE_8BIT_NONATOMIC
#define RTE_8BIT_ATOMIC
#endif

#ifndef RTE_8BIT_ATOMIC
#define RTE_ATOMIC8(x)          RTE_ATOMIC(x)
#else
#define RTE_ATOMIC8(x)          (x)
#endif

#ifndef RTE_16BIT_ATOMIC
#define RTE_ATOMIC16(x)         RTE_ATOMIC(x)
#else
#define RTE_ATOMIC16(x)         (x)
#endif

#ifndef RTE_32BIT_ATOMIC
#define RTE_ATOMIC32(x)         RTE_ATOMIC(x)
#else
#define RTE_ATOMIC32(x)         (x)
#endif

#ifndef RTE_64BIT_ATOMIC
#define RTE_ATOMIC64(x)         RTE_ATOMIC(x)
#else
#define RTE_ATOMIC64(x)         (x)
#endif

#ifndef RTE_BOOLEAN_ATOMIC
#define RTE_ATOMICBOOLEAN(x)    RTE_ATOMIC(x)
#else
#define RTE_ATOMICBOOLEAN(x)    (x)
#endif

#ifndef RTE_FLOAT32_ATOMIC
#define RTE_ATOMICFLOAT32(x)    RTE_ATOMIC(x)
#else
#define RTE_ATOMICFLOAT32(x)    (x)
#endif

#ifndef RTE_FLOAT64_ATOMIC
#define RTE_ATOMICFLOAT64(x)    RTE_ATOMIC(x)
#else
#define RTE_ATOMICFLOAT64(x)    (x)
#endif

/*---------------------------------------------------------------------------*/
/* [$Satisfies $SWS 1269] Standard Error Codes */

#define RTE_E_OK               ((Std_ReturnType)0u)    /* [$Satisfies $SWS 1058] */
#define RTE_E_INVALID          ((Std_ReturnType)1u)    /* [$Satisfies $SWS 2594] */

/* [$Satisfies $SWS 1318] */
#define RTE_E_LOST_DATA        ((Std_ReturnType)64u)   /* [$Satisfies $SWS 2571] */
#define RTE_E_MAX_AGE_EXCEEDED ((Std_ReturnType)64u)   /* [$Satisfies $SWS 2702] */

/* [$Satisfies $SWS 2593] */
#define RTE_E_COM_STOPPED      ((Std_ReturnType)128u)  /* [$Satisfies $SWS 1060] */
#define RTE_E_TIMEOUT          ((Std_ReturnType)129u)  /* [$Satisfies $SWS 1064] */
#define RTE_E_LIMIT            ((Std_ReturnType)130u)  /* [$Satisfies $SWS 1317] */
#define RTE_E_NO_DATA          ((Std_ReturnType)131u)  /* [$Satisfies $SWS 1061] [$Satisfies $SWS 6012] */
#define RTE_E_TRANSMIT_ACK     ((Std_ReturnType)132u)  /* [$Satisfies $SWS 1065] */
#define RTE_E_NEVER_RECEIVED    ((Std_ReturnType)133u) /* [$Satisfies $SWS40 7384] */
#define RTE_E_UNCONNECTED       ((Std_ReturnType)134u) /* [$Satisfies $SWS40 7655] */
#define RTE_E_IN_EXCLUSIVE_AREA ((Std_ReturnType)135u) /* [$Satisfies $SWS40 2739] */
#define RTE_E_SEG_FAULT         ((Std_ReturnType)136u) /* [$Satisfies $SWS40 2757] */

/* [$Satisfies $rte_xfrm 079] */
#define RTE_E_HARD_TRANSFORMER_ERROR ((Std_ReturnType)138u)
#define RTE_E_SOFT_TRANSFORMER_ERROR ((Std_ReturnType)140u)

/* [$Satisfies $SWS40 7291] */
#define SCHM_E_OK                ((Std_ReturnType)0u)    /* [$Satisfies $SWS40 7289] */
#define SCHM_E_LIMIT             ((Std_ReturnType)130u)  /* [$Satisfies $SWS40 7290] */
#define SCHM_E_NO_DATA           ((Std_ReturnType)131u)  /* [$Satisfies $SWS40 7562] */
#define SCHM_E_TRANSMIT_ACK      ((Std_ReturnType)132u)  /* [$Satisfies $SWS40 7563] */
#define SCHM_E_IN_EXCLUSIVE_AREA ((Std_ReturnType)135u)  /* [$Satisfies $SWS40 2747] */

/*---------------------------------------------------------------------------*/
/* RTE DataTransformers */

/* [$Satisfies $rte_xfrm 129] */
typedef uint8 Rte_TransformerErrorCode;
typedef uint8 Rte_TransformerClass;

#define RTE_TRANSFORMER_UNSPECIFIED ((Rte_TransformerClass)0u)
#define RTE_TRANSFORMER_SERIALIZER ((Rte_TransformerClass)1u)
#define RTE_TRANSFORMER_SAFETY ((Rte_TransformerClass)2u)
#define RTE_TRANSFORMER_SECURITY ((Rte_TransformerClass)3u)
#define RTE_TRANSFORMER_CUSTOM ((Rte_TransformerClass)255u)

typedef struct Rte_TransformerError {
   Rte_TransformerErrorCode errorCode;
   Rte_TransformerClass transformerClass;
} Rte_TransformerError;

/*---------------------------------------------------------------------------*/
/* RTE Types */

#if !defined(RTE_LIBC_MEMCPY)
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern FUNC(void, RTE_CODE) Rte_memcpy(P2VAR(void, AUTOMATIC, RTE_DATA) dst,
                                          P2CONST(void, AUTOMATIC, RTE_APPL_DATA) src,
                                          uint16 length);
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
#else
#define Rte_memcpy(dst,src,length) memcpy(dst,src,length)
#endif


#ifdef RTE_CHAR_TYPE
typedef RTE_CHAR_TYPE      Rte_Char;
typedef RTE_CHAR_TYPE *    Rte_String;
#else
typedef sint8              Rte_Char;
typedef sint8*             Rte_String;
#endif

typedef struct {
   P2VAR(void, AUTOMATIC, RTE_DATA)   in;           /* [$Satisfies $SWS 2522] */
   P2VAR(void, AUTOMATIC, RTE_DATA)   out;          /* [$Satisfies $SWS 2522] */
   uint16                             used;         /* [$Satisfies $SWS 2523] */
   Std_ReturnType                     lost_data;    /* [$Satisfies $SWS 2523] [$Satisfies $SWS 2572] */
} Rte_QDynType;

typedef enum {
   RTE_DRA,
   RTE_WOWP,
   RTE_TASK,
   RTE_ARE,
   RTE_EV,
   RTE_MSI
} Rte_NotificationType;

typedef struct Rte_QCmnType {
   P2VAR(Rte_QDynType, AUTOMATIC, RTE_DATA) dynamic;
   boolean                                  copy;
   uint16                                   queue_size;
   uint16                                   element_size;
   P2VAR(void, AUTOMATIC, RTE_DATA)         buffer_start;
   P2VAR(void, AUTOMATIC, RTE_DATA)         buffer_end;
   Rte_NotificationType                     notification_type;
} Rte_QCmnType;

/* The Rte_QCmnRefType needs to be visible to the components,
 * since the server's input queue element type contains a reference
 * to the client to which to reply */
typedef P2CONST(struct Rte_QCmnType, AUTOMATIC, RTE_CONST) Rte_QCmnRefType;

/* Type of each entry on Calibration reference table... since each
 * entry can be a pointer to a (different) structure we're forced to use
 * a void type and casts for type correctness. */
typedef P2CONST(void, AUTOMATIC, RTE_APPL_CONST) RteCalprmRefTabEntryType;

/* OS Resources :
 * The Rte_ResourceRefType needs to be visible to the components since
 * it can appear in the CDS. RTE SWS defines it as a void pointer */
#ifndef RTE_RESOURCEREFTYPE
#define RTE_RESOURCEREFTYPE            P2CONST(void, AUTOMATIC, RTE_OS_CDATA)
#endif /* RTE_RESOURCEREFTYPE */

typedef RTE_RESOURCEREFTYPE            Rte_ResourceRefType;

/* OS Alarms :
 * The Rte_AlarmRefType needs to be visible to the components since
 * it can appear in queue elements, and hence in Rte_Type.h */
#ifndef RTE_ALARMREFTYPE
#if defined(OSENV_RTAOSEK) || defined(OSENV_ERCOSEK) || defined(RTE_ALARMTYPE_IS_GLOBALCONST)
#define RTE_ALARMREFTYPE              P2CONST(void, AUTOMATIC, RTE_OS_CDATA)
#else
#define RTE_ALARMREFTYPE              unsigned int
#endif
#endif

typedef RTE_ALARMREFTYPE       Rte_AlarmRefType;

typedef uint16                 Rte_AlarmIndexType;

typedef uint16                 Rte_SeqCounterType_16;

/*---------------------------------------------------------------------------*/
/* BSW Scheduler support */

typedef void SchM_ConfigType;

/*---------------------------------------------------------------------------*/
/* Macro Support for Bit Fields
 * The arguments are ArrayName, Type and BitIndex.  The #ifndefs are there to
 * allow for optimization on targets having bit instructions.
 */
#ifndef RTE_BITSET
#define RTE_BITSET(A,T,X) (A[(X) / ( 8UL * sizeof( T ) )] |= ( ( T )( 1UL << ( (X)%(8UL * sizeof( T )) ) ) ))
#endif
#ifndef RTE_BITCLR
#define RTE_BITCLR(A,T,X) (A[(X) / ( 8UL * sizeof( T ) )] &= ~( ( T )( 1UL << ( (X)%(8UL * sizeof( T )) ) ) ))
#endif
#ifndef RTE_BITTST
#define RTE_BITTST(A,T,X) (A[(X) / ( 8UL * sizeof( T ) )] & ( ( T )( 1UL << ( (X)%(8UL * sizeof( T )) ) ) ))
#endif

/*---------------------------------------------------------------------------*/
/* Macro Support for Std_ReturnType analysis */

/* [$Satisfies $SWS40 7404] */
#define Rte_IsInfrastructureError(status)  ((status & 128U) != 0)

/* [$Satisfies $SWS40 7405] */
#define Rte_HasOverlayedError(status)      ((status & 64U) != 0)

/* [$Satisfies $SWS40 7406] */
#define Rte_ApplicationError(status)       (status & 63U)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RTE_H */

