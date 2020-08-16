


#ifndef DEM_ISO14229BYTE_H
#define DEM_ISO14229BYTE_H

#include "Dem_Types.h"
#include "rba_DiagLib_Bits8.h"


/* Refer to Dem_UdsStatusByteType */


#define DEM_ISO14229_TESTFAILED             0u
#define DEM_ISO14229_TESTFAILED_TOC         1u
#define DEM_ISO14229_TESTFAILED_SLC         5u
#define DEM_ISO14229_TESTNOTCOMPLETE_TOC    6u
#define DEM_ISO14229_TESTNOTCOMPLETE_SLC    4u
#define DEM_ISO14229_PENDINGDTC             2u
#define DEM_ISO14229_CONFIRMEDDTC           3u
#define DEM_ISO14229_WARNINGINDICATOR       7u

#define DEM_ISO14229_BM_TESTFAILED             (1u<<DEM_ISO14229_TESTFAILED)
#define DEM_ISO14229_BM_TESTFAILED_TOC         (1u<<DEM_ISO14229_TESTFAILED_TOC)
#define DEM_ISO14229_BM_TESTFAILED_SLC         (1u<<DEM_ISO14229_TESTFAILED_SLC)
#define DEM_ISO14229_BM_TESTNOTCOMPLETE_TOC    (1u<<DEM_ISO14229_TESTNOTCOMPLETE_TOC)
#define DEM_ISO14229_BM_TESTNOTCOMPLETE_SLC    (1u<<DEM_ISO14229_TESTNOTCOMPLETE_SLC)
#define DEM_ISO14229_BM_PENDINGDTC             (1u<<DEM_ISO14229_PENDINGDTC)
#define DEM_ISO14229_BM_CONFIRMEDDTC           (1u<<DEM_ISO14229_CONFIRMEDDTC)
#define DEM_ISO14229_BM_WARNINGINDICATOR       (1u<<DEM_ISO14229_WARNINGINDICATOR)

#if (DEM_ISO14229_BM_TESTFAILED           !=  DEM_UDS_STATUS_TF)
#error Bit definition error
#endif

#if (DEM_ISO14229_BM_TESTFAILED_TOC       !=  DEM_UDS_STATUS_TFTOC)
#error Bit definition error
#endif

#if (DEM_ISO14229_BM_TESTFAILED_SLC       !=  DEM_UDS_STATUS_TFSLC)
#error Bit definition error
#endif

#if (DEM_ISO14229_BM_TESTNOTCOMPLETE_TOC  !=  DEM_UDS_STATUS_TNCTOC)
#error Bit definition error
#endif

#if (DEM_ISO14229_BM_TESTNOTCOMPLETE_SLC  !=  DEM_UDS_STATUS_TNCSLC)
#error Bit definition error
#endif

#if (DEM_ISO14229_BM_PENDINGDTC           !=  DEM_UDS_STATUS_PDTC)
#error Bit definition error
#endif

#if (DEM_ISO14229_BM_CONFIRMEDDTC         !=  DEM_UDS_STATUS_CDTC)
#error Bit definition error
#endif

#if (DEM_ISO14229_BM_WARNINGINDICATOR     !=  DEM_UDS_STATUS_WIR)
#error Bit definition error
#endif



#define DEM_ISO14229BYTE_INITVALUE            		( (DEM_ISO14229_BM_TESTNOTCOMPLETE_TOC)|(DEM_ISO14229_BM_TESTNOTCOMPLETE_SLC) )
#define DEM_ISO14229BYTE_MASK_PENDING_CONFIRMED     ( DEM_ISO14229_BM_PENDINGDTC | DEM_ISO14229_BM_CONFIRMEDDTC )
/*#define DEM_ISO14229BYTE_MASK_FAILED_COMPLETE_WIR   ( DEM_ISO14229_BM_TESTFAILED | DEM_ISO14229_BM_TESTFAILED_TOC \
                                                      | DEM_ISO14229_BM_TESTFAILED_SLC | DEM_ISO14229_BM_WARNINGINDICATOR \
                                                      | DEM_ISO14229_BM_TESTNOTCOMPLETE_TOC | DEM_ISO14229_BM_TESTNOTCOMPLETE_SLC)
 */

#define DEM_ISO14229BYTE_MASK_INDICATOR_OFF			(DEM_ISO14229_BM_CONFIRMEDDTC | DEM_ISO14229_BM_TESTFAILED \
                                                      | DEM_ISO14229_BM_TESTFAILED_TOC)

#define DEM_ISO14229BYTE_MASK_TESTFAILEDSINCELASTCLEAR     ( DEM_ISO14229_BM_TESTFAILED_SLC )

#if (DEM_UDS_STATUS_TF     != DEM_ISO14229_BM_TESTFAILED)
#error "WRONG BIT DEFINITION OF ISO14229BYTE"
#endif
#if (DEM_UDS_STATUS_TFTOC  != DEM_ISO14229_BM_TESTFAILED_TOC)
#error "WRONG BIT DEFINITION OF ISO14229BYTE"
#endif
#if (DEM_UDS_STATUS_PDTC   != DEM_ISO14229_BM_PENDINGDTC)
#error "WRONG BIT DEFINITION OF ISO14229BYTE"
#endif
#if (DEM_UDS_STATUS_CDTC   != DEM_ISO14229_BM_CONFIRMEDDTC)
#error "WRONG BIT DEFINITION OF ISO14229BYTE"
#endif
#if (DEM_UDS_STATUS_TNCSLC != DEM_ISO14229_BM_TESTNOTCOMPLETE_SLC)
#error "WRONG BIT DEFINITION OF ISO14229BYTE"
#endif
#if (DEM_UDS_STATUS_TFSLC  != DEM_ISO14229_BM_TESTFAILED_SLC)
#error "WRONG BIT DEFINITION OF ISO14229BYTE"
#endif
#if (DEM_UDS_STATUS_TNCTOC != DEM_ISO14229_BM_TESTNOTCOMPLETE_TOC)
#error "WRONG BIT DEFINITION OF ISO14229BYTE"
#endif
#if (DEM_UDS_STATUS_WIR    != DEM_ISO14229_BM_WARNINGINDICATOR)
#error "WRONG BIT DEFINITION OF ISO14229BYTE"
#endif






/*
 * concept idea for triggering storage to NVM for single status bytes
 */
#define DEM_ISO14229BYTE_NVMTRIGGER(STATUSBITSTORAGETESTFAILED, OPERATIONCYCLE_IS_PC) \
        (0|DEM_ISO14229_BM_TESTNOTCOMPLETE_SLC \
                |DEM_ISO14229_BM_TESTFAILED_SLC \
                |(DEM_ISO14229_BM_TESTFAILED*(STATUSBITSTORAGETESTFAILED)) \
                |(DEM_ISO14229_BM_TESTFAILED_TOC*(OPERATIONCYCLE_IS_PC)) \
                |(DEM_ISO14229_BM_TESTNOTCOMPLETE_TOC*(OPERATIONCYCLE_IS_PC)) \
        )


/* query functions */

DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsTestFailed (uint8 self)
{
    return rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_TESTFAILED);
}



DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsTestFailedTOC (uint8 self)
{
    return rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_TESTFAILED_TOC);
}



DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsTestFailedSLC (uint8 self)
{
    return rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_TESTFAILED_SLC);
}



DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsTestNotCompleteTOC (uint8 self)
{
    return rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_TESTNOTCOMPLETE_TOC);
}



DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsTestNotCompleteSLC (uint8 self)
{
    return rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_TESTNOTCOMPLETE_SLC);
}



DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsTestCompleteTOC (uint8 self)
{
    return !rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_TESTNOTCOMPLETE_TOC);
}



DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsTestCompleteSLC (uint8 self)
{
    return !rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_TESTNOTCOMPLETE_SLC);
}



DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsPendingDTC (uint8 self)
{
    return rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_PENDINGDTC);
}



DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsConfirmedDTC (uint8 self)
{
    return rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_CONFIRMEDDTC);
}


DEM_INLINE Dem_boolean_least Dem_ISO14229ByteIsWarningIndicatorRequested (uint8 self)
{
    return rba_DiagLib_Bit8IsBitSet (self, DEM_ISO14229_WARNINGINDICATOR);
}



/* set methods */

DEM_INLINE void Dem_ISO14229ByteSetTestFailed (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_TESTFAILED, setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetTestFailedTOC (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_TESTFAILED_TOC, setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetTestFailedSLC (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_TESTFAILED_SLC, setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetTestNotCompleteTOC (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_TESTNOTCOMPLETE_TOC, setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetTestNotCompleteSLC (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_TESTNOTCOMPLETE_SLC, setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetTestCompleteTOC (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_TESTNOTCOMPLETE_TOC, !setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetTestCompleteSLC (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_TESTNOTCOMPLETE_SLC, !setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetPendingDTC (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_PENDINGDTC, setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetConfirmedDTC (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_CONFIRMEDDTC, setOrReset);
}



DEM_INLINE void Dem_ISO14229ByteSetWarningIndicatorRequested (uint8 *self, Dem_boolean_least setOrReset)
{
    rba_DiagLib_Bit8OverwriteBit (self, DEM_ISO14229_WARNINGINDICATOR, setOrReset);
}

#endif

