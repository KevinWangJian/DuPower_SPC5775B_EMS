

#ifndef PDUR_BUFFERPOOL_H_
#define PDUR_BUFFERPOOL_H_

#include "PduR_Cfg_Internal.h"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_Types.h"
#include "PduR_BufferPool_Cfg.h"

/* MR12 RULE 20.7 VIOLATION: The Type Conversion is Required */
#define PDUR_GLOBAL_BUFFERPOOL(s)                (PduR_Global_BufferPoolPtr->s)
#define PDUR_GW_TP_BASE_BUFFERPOOL_FIXED       PDUR_GLOBAL_BUFFERPOOL(bufferPoolConst)

/* Local typedefs for buffer pool */
typedef uint16 PduRBufferPoolLengthType;        /* Buffer pool length type */

/**
 * @ingroup PDUR_BUFFERPOOL_H_
 * This structure represents Buffer Pool referred by a TP Gateway routing path.\n
 * typedef struct \n
 *  { \n
 *  boolean                                poolBufferStatus;            Represents Status of buffer whether free or busy\n
 * } PduR_PoolBuffer_Dynamic;
 */
typedef struct
{
   boolean                                 poolBufferStatus;
} PduR_PoolBuffer_Dynamic;


typedef P2VAR( PduR_PoolBuffer_Dynamic, TYPEDEF, PDUR_VAR ) PduR_PoolBuffer_DynamicPtr;

/**
 * @ingroup PDUR_BUFFERPOOL_H_
 * This structure represents Buffer Pool referred by a TP Gateway routing path.\n
 * typedef struct \n
 *  { \n
 *  P2VAR( void, TYPEDEF, PDUR_VAR )     poolBufferPtr;     Pointer for Buffer\n
 *  PduRBufferPoolLengthType            poolBufferLength;    Represents Length of the buffer\n
 * } PduR_PoolBuffer_Fixed;
 */
typedef struct
{
   P2VAR( uint8, TYPEDEF, PDUR_VAR )     poolBufferPtr;
   PduRBufferPoolLengthType              poolBufferLength;
} PduR_PoolBuffer_Fixed;

typedef P2CONST( PduR_PoolBuffer_Fixed, TYPEDEF, PDUR_CONST ) PduR_PoolBuffer_FixedPtr;
/**
 * @ingroup PDUR_BUFFERPOOL_H_
 * This structure represents Buffer Pool referred by a TP Gateway routing path.\n
 * typedef struct \n
 *  { \n
 *  PduRBufferPoolLengthType            freeBuffersInPool;    Represents Total no. of free buffers in the Pool\n
 * } PduR_BufferPool_Dynamic;
 */
typedef struct
{
    PduRBufferPoolLengthType            freeBuffersInPool;
} PduR_BufferPool_Dynamic;

typedef P2VAR( PduR_BufferPool_Dynamic, TYPEDEF, PDUR_VAR ) PduR_BufferPool_DynamicPtr;

/**
 * @ingroup PDUR_BUFFERPOOL_H_
 * This structure represents Buffer Pool referred by a TP Gateway routing path.\n
 * typedef struct \n
 *  { \n
 *  P2VAR( PduR_BufferPool_Dynamic, TYPEDEF, PDUR_VAR )     bufferPoolDyn;           Pointer for Pool Manager dynamic structure\n
 *  P2CONST( PduR_PoolBuffer_Fixed, TYPEDEF, PDUR_CONST )     poolBufferConst;        Pointer to Const Buffer manager table\n
 *  P2VAR( PduR_PoolBuffer_Dynamic, TYPEDEF, PDUR_VAR )     poolBufferDyn;    Pointer to RAM Buffer manager table\n
 *  PduRBufferPoolLengthType                                 maxBufferSize;     Represents max size of buffer in the Pool\n
 *  PduRBufferPoolLengthType                                 totalBuffersInPool;    Represents Total no. of buffers in the Pool\n
 * } PduR_BufferPool_Fixed;
 */
typedef struct
{
   P2VAR( PduR_BufferPool_Dynamic, TYPEDEF, PDUR_VAR )      bufferPoolDyn;
   P2CONST( PduR_PoolBuffer_Fixed, TYPEDEF, PDUR_CONST )    poolBufferConst;
   P2VAR( PduR_PoolBuffer_Dynamic, TYPEDEF, PDUR_VAR )      poolBufferDyn;
   PduRBufferPoolLengthType                                 maxBufferSize;
   PduRBufferPoolLengthType                                 totalBuffersInPool;
} PduR_BufferPool_Fixed;

typedef P2CONST( PduR_BufferPool_Fixed, TYPEDEF, PDUR_CONST ) PduR_BufferPool_FixedPtr;

/**
 * @ingroup PDUR_BUFFERPOOL_H_
 * This structure represents Buffer Pool referred by a TP Gateway routing path.\n
 * typedef struct \n
 *  { \n
   P2CONST( PduR_BufferPool_Fixed, TYPEDEF, PDUR_VAR )     bufferPoolConst;        Pointer to Const Pool manager\n
 * } PduR_BufferPool_ConfigType;
 */
typedef struct
{
   P2CONST( PduR_BufferPool_Fixed, TYPEDEF, PDUR_CONST )     bufferPoolConst;

} PduR_BufferPool_ConfigType;

/*Extern declarations*/

/*Start: Functions*/
extern FUNC( void, PDUR_CODE ) PduR_BufferPoolInit(P2CONST( PduR_BufferPool_ConfigType, AUTOMATIC, PDUR_APPL_CONST ) BuffPoolConfigPtr);

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_BufferPoolRequest(  VAR(uint16, AUTOMATIC) BuffPoolId,
                                                               VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                               P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr,
                                                               P2VAR( uint8, TYPEDEF, PDUR_VAR ) *bufferPtr);

extern FUNC( void, PDUR_CODE ) PduR_BufferPoolRelease(VAR(uint16, AUTOMATIC) BuffPoolId, P2CONST( uint8, TYPEDEF, PDUR_VAR ) bufferPtr);
/*End: Functions*/

/*Start: Global variable */
extern P2CONST(PduR_BufferPool_ConfigType, PDUR_VAR, PDUR_APPL_CONST) PduR_Global_BufferPoolPtr;

extern CONST( PduR_BufferPool_ConfigType, PDUR_CONST )  PduR_BufferPool_Config;
/*End: Global variable */

#endif /* PDUR_BUFFERPOOL_SUPPORT */
#endif /* PDUR_BUFFERPOOL_H_ */

