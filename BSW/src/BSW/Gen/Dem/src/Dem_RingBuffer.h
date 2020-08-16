


#ifndef DEM_RINGBUFFER_LIB_H
#define DEM_RINGBUFFER_LIB_H

#include "Dem_Array.h"

typedef struct {
   uint16 end;             /* pointer to last buffer-place */
   uint16 lastEmptyLoc;    /* last empty buffer location */
   uint16 nextEmptyLoc;    /* next empty location */
   uint16 RingBuffLocIt;   /* location iterator shall not be used outside the ring buffer as there must be only one iterator at a time*/
} Dem_RingBuffer;

/* MR12 RULE 20.7 VIOLATION: the makro is expanded into several commans/lines, this cannot be encapsulated with braces */
#define DEM_DEFINE_RINGBUFFER(DATATYPE, NAME, SIZE)                       \
  static Dem_RingBuffer  NAME##_Handler; \
  static DEM_ARRAY_DEFINE(DATATYPE, NAME, SIZE+1u)


/*This remove function may be considered in future. */
/* #define  Dem_RingBuffer__REMOVE(NAME, REMOVED_DATA)                                      \
        ((boolean)Dem_RingBufferIndex__isEmpty (&(NAME##_Handler))) ?                       \
            (                                                                               \
                FALSE                                                                       \
            )                                                                               \
        :   (                                                                               \
                (NAME##_Handler).lastEmptyLoc = Dem_RingBuffer__next (&(NAME##_Handler), (NAME##_Handler).lastEmptyLoc),              \
                DEM_MEMCPY(&(REMOVED_DATA), &(NAME[(NAME##_Handler).lastEmptyLoc]), DEM_SIZEOF_VAR(REMOVED_DATA)) != NULL_PTR || TRUE     \
            )                                                                               \
        ;
*/
/*----------------------------------------------------------------------------*/

/**
 * initialize the ringbuffer
 * Parameters
 *   ringBufferMemory: RAM-Array for buffer elements
 *   buffersize: number of elements in buffer
 */
/* MR12 RULE 20.7 VIOLATION : Macro parameter may not be enclosed in (). */
#define Dem_RingBuffer__Init(NAME)                                      \
{                                                                       \
   NAME##_Handler.end = (uint16)(DEM_SIZEOF_VAR(NAME) / DEM_SIZEOF_VAR(NAME[0])); \
   NAME##_Handler.lastEmptyLoc = NAME##_Handler.end - 1;                \
}

/*----------------------------------------------------------------------------*/

/**
 * initialize the ringbuffer
 */

DEM_INLINE void Dem_RingBuffer__clear (Dem_RingBuffer* rb)
{
   rb->nextEmptyLoc = 0;
   rb->lastEmptyLoc = rb->end - 1;
}

/*----------------------------------------------------------------------------*/

/**
 * move position pointer to next position (if new position is larger than end, reset to begin)
 */

DEM_INLINE uint16 Dem_RingBuffer__next (const Dem_RingBuffer* rb, uint16 idx)
{
   uint16 result = idx + 1;
   if (result >= rb->end)
   {
      result = 0;
   }
   return result;
}

/*----------------------------------------------------------------------------*/

/**
 * returns whether the buffer is empty or not
 */

DEM_INLINE boolean Dem_RingBuffer__isEmpty (const Dem_RingBuffer* rb)
{
   return (Dem_RingBuffer__next (rb, rb->lastEmptyLoc) == rb->nextEmptyLoc);
}

/*----------------------------------------------------------------------------*/

/**
 * returns whether the buffer is full or not
 */

DEM_INLINE boolean Dem_RingBuffer__isFull (const Dem_RingBuffer* rb)
{
   return (rb->lastEmptyLoc == rb->nextEmptyLoc);
}


/*----------------------------------------------------------------------------*/

/**
 * insert element to ringbuffer (Queue behaviour: FIFO)
 * returns TRUE: if value was inserted
 *         FALSE: if buffer was full
 */

DEM_INLINE boolean Dem_RingBuffer__insert (Dem_RingBuffer* rb, uint16* insertionIndex)
{
   if (Dem_RingBuffer__isFull (rb)) return FALSE;

   *insertionIndex = rb->nextEmptyLoc;
   rb->nextEmptyLoc = Dem_RingBuffer__next (rb, rb->nextEmptyLoc);

   return TRUE;
}

/*----------------------------------------------------------------------------*/

/**
 * index of element which will be removed next with function remove
 * returns TRUE: if value was returned
 *         FALSE: if buffer was empty
 */

DEM_INLINE boolean Dem_RingBuffer__nextRemoval (const Dem_RingBuffer* rb, uint16* nextIndex)
{
   if (Dem_RingBuffer__isEmpty (rb)) return FALSE;

   *nextIndex = Dem_RingBuffer__next (rb, rb->lastEmptyLoc);

   return TRUE;
}

/*----------------------------------------------------------------------------*/

/**
 * remove element from ringbuffer (Queue behaviour: FIFO)
 * returns TRUE: if value was returned
 *         FALSE: if buffer was empty
 */

DEM_INLINE boolean Dem_RingBuffer__remove (Dem_RingBuffer* rb, uint16* removedIndex)
{
   if (Dem_RingBuffer__isEmpty (rb)) return FALSE;

   rb->lastEmptyLoc = Dem_RingBuffer__next (rb, rb->lastEmptyLoc);
   *removedIndex = rb->lastEmptyLoc;

   return TRUE;
}

/*----------------------------------------------------------------------------*/
/* Iterator Functions for fetching and validating the ring buffer indices */

DEM_INLINE void Dem_RingBuffer__NewIterator (Dem_RingBuffer* rb)
{
    rb->RingBuffLocIt = Dem_RingBuffer__next (rb, rb->lastEmptyLoc);
}
DEM_INLINE boolean Dem_RingBuffer__IteratorIsValid (const Dem_RingBuffer* rb)
{
    return (rb->RingBuffLocIt != rb->nextEmptyLoc);
}
DEM_INLINE void Dem_RingBuffer__IteratorNext (Dem_RingBuffer* rb)
{
    rb->RingBuffLocIt = Dem_RingBuffer__next(rb, rb->RingBuffLocIt);
}

/** PARAMETERS: BUFFERNAME=name of the buffer,
 *              COMPAREFUNCTION=function to perform the check,
 *              COMAREVALUE=value to search, will be passed to COMPAREFUNCTION
 *              ISINBUFFER=boolean var returning whether element was found
 *              LOC=location which stores the value (only valid if ISINBUFFER is true)
 * Prototype for COMPAREFUNCTION:  inline boolean compareF (DATATYPE *bufferElement, ANYTYPE compareValue)
 */
/* MR12 RULE 20.7 VIOLATION: the makro is expanded into several commans/lines, this cannot be encapsulated with braces */
#define Dem_RingBufferIndex__ISINBUFFER(BUFFERNAME, COMPAREFUNCTION, COMPAREVALUE, ISINBUFFER, LOC)             \
    ISINBUFFER = FALSE;                                                                                         \
    for (Dem_RingBuffer__NewIterator (&(BUFFERNAME##_Handler)); Dem_RingBuffer__IteratorIsValid (&(BUFFERNAME##_Handler));    \
    Dem_RingBuffer__IteratorNext (&(BUFFERNAME##_Handler)))                                                     \
    {                                                                                                           \
        if(COMPAREFUNCTION (&(BUFFERNAME[(BUFFERNAME##_Handler).RingBuffLocIt]), COMPAREVALUE))                 \
        {                                                                                                       \
            LOC = (BUFFERNAME##_Handler).RingBuffLocIt;                                                         \
            ISINBUFFER = TRUE;                                                                                  \
            break;                                                                                              \
        }                                                                                                       \
    }


#endif

