

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_PackSignal
 Syntax           : void Com_PackSignal(uint8 Endianess,Com_BitpositionType Bit_Pos, Com_BitsizeType Bitsize,
                                        Com_SigMaxType Src_Buf,P2VAR(uint8, AUTOMATIC, COM_CODE) Dest_Buf)
 Description      : Internal function used for packing the signal into Ipdubuffer
 Parameter        : Endianess -> Little Endian/Big Endian
                  : Bit_Pos ->   Position of the signal in the ipdu
                  : Bitsize ->   Size of the signal
                  : Src_Buf ->   Buffer where signal data is available
                  : Dest_Buf ->  ponter to buffer where the signal data needs to be packed
 Return value     : None
***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_PackSignal( VAR(uint8, AUTOMATIC)                  Endianess,
                                     VAR(Com_BitpositionType, AUTOMATIC)    Bit_Pos,
                                     VAR(Com_BitsizeType, AUTOMATIC)        Bitsize,
                                     VAR(Com_SigMaxType, AUTOMATIC)         Src_Buf,
                                     P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) Dest_Buf )
{

    /* Bfx - AR specific service library is not used, for the signal packing operations for below reasons
     * 1. There is a function Bfx_GetBits which takes a variable of type (uint8/16/32/64), extracts bits from it,
     * returns the data in the same respective type(uint8/16/32/64).
     * If this api is used in Com, there will still be many bit operations(Bitshift etc..)
     * which have to be performed in the Com code,hence there is no much help,
     * as bit operations (significant in number) are done both in Com and SrvLib.
     */

    VAR(PduLengthType, AUTOMATIC) ByteNo;
    VAR(uint16_least, AUTOMATIC)  Total_BitsCopied;
    VAR(uint16_least, AUTOMATIC)  Bits_left;
    VAR(uint8_least, AUTOMATIC)   BitOffsetInByte;
    VAR(uint8_least, AUTOMATIC)   a_data;
    VAR(uint8, AUTOMATIC)         Mask;

    /* Clear unused bits in the source buffer */
    if(Bitsize != COM_SIG_MAX_NO_OF_BITS)
    {
        Src_Buf = Src_Buf & (~(COM_SIG_MAX_DATA << Bitsize));
    }

    ByteNo          = (PduLengthType)(Bit_Pos >> 3u);
    BitOffsetInByte = (uint8_least)(Bit_Pos % 8u);

    a_data = (uint8_least)(Src_Buf << BitOffsetInByte);

    if(Bitsize >= (8u - BitOffsetInByte))
    {
        /* This Part will be executed if the Signal is placed in more than 1 byte */
        Mask = (uint8)(~((uint8)(0xFFu << BitOffsetInByte)));
        Total_BitsCopied = (8u - BitOffsetInByte);
    }
    else
    {
        /* This Part will be executed if the Signal is placed within the same byte. i.e. Bitsize <= 7 */
        Mask = (uint8)(~(((1u << Bitsize) - 1u) << BitOffsetInByte));
        Total_BitsCopied = Bitsize;
    }

    *(Dest_Buf+ByteNo) = ((*(Dest_Buf+ByteNo)) & Mask) | (uint8)a_data;

    while (Total_BitsCopied < Bitsize)
    {
        Bits_left = Bitsize - Total_BitsCopied;

        if(Endianess != COM_BIGENDIAN)
        {
            ByteNo++;
        }
        else
        {
            ByteNo--;
        }

        a_data = (uint8_least)(Src_Buf >> Total_BitsCopied);

        if(Bits_left >= 8u)
        {
            *(Dest_Buf+ByteNo) = (uint8)a_data;
            Total_BitsCopied = Total_BitsCopied + 8u;
        }
        else
        {
            Mask = (uint8)(0xFFu << Bits_left);
            *(Dest_Buf+ByteNo) = *(Dest_Buf+ByteNo) & Mask;
            *(Dest_Buf+ByteNo) = *(Dest_Buf+ByteNo) | (uint8)a_data;

            Total_BitsCopied = Total_BitsCopied + Bits_left;
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/* FC_VariationPoint_START */
#if (defined(COM_TXSIG_FLOAT64SUPP) || defined(COM_TXGRPSIG_FLOAT64SUPP) ||\
    (defined(COM_RX_SIGNALGROUP_ARRAY) && defined(COM_RXGRPSIG_FLOAT64SUPP)))
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_PackFloatSignal
 Syntax           : void Com_PackFloatSignal(uint8 Endianess,Com_BitpositionType Bit_Pos,
                    floa64 Src,P2VAR(uint8, AUTOMATIC, COM_CODE) Dest_Buf)
 Description      : Internal function used for packing the signal into Ipdubuffer
 Parameter        : Endianess -> Little Endian/Big Endian
                  : Bit_Pos ->   Position of the signal in the ipdu
                  : Src ->   Buffer where signal data is available
                  : Dest_Buf ->  ponter to buffer where the signal data needs to be packed
 Operation           : This function only packs Float64 signals into Tx Ipdu buffer.
 There can be two possibilities in packing a float signal
 1. Signal lies in the byte boundary:
  If signal lies in byte boundary, then all the 8 bytes of float data (64 bits) is copied into the uint8 destination buffer using memcpy function

 2. Signal does not lie in the byte boundary:
  If the signal bit position is not in the byte boundary, then the first and last bytes are displaced from the byte boundary
  and need a bit copy of corresponding displaced bits. Where as the other 7 bytes of data can be copied with memcpy function
  i.e : If the Bit position of the signal is 21,
        1. first three bits are packed in 3rd byte of IPdu buffer with LSB being bit number 21.
        2. Next 7 bytes of float data is copied into the next 7 bytes of IPdu buffer
        3. The 11th byte of Ipdu buffer is then packed with remaining 5 bits of data.
 Return value     : None
***************************************************************************************************/
FUNC(void, COM_CODE) Com_PackFloatSignal(VAR(uint8, AUTOMATIC) Endianess, VAR(Com_BitpositionType, AUTOMATIC) Bit_Pos,
                VAR(float64,AUTOMATIC) Src, P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) Dest_Buf)
{

    VAR(PduLengthType, AUTOMATIC) ByteNo;
    VAR(PduLengthType, AUTOMATIC) NoofBytes;
    VAR(uint8_least, AUTOMATIC) BitOffsetInByte;

    /* Float64 data type has 8 bytes */
    NoofBytes = 8u;
    ByteNo = Bit_Pos >> 3u;
    BitOffsetInByte = (uint8)(Bit_Pos - (ByteNo * 8u));

    if(BitOffsetInByte == 0u )
    {
        if(Endianess == COM_LITTLEENDIAN)
        {
            /* MR12 DIR 1.1 VIOLATION: Explicit cast is provided in line with rba_BswSrv_MemCopy() definition.
               But the void pointer is always deferenced to a type based on the pointers address alignment.
               Hence the alignment warning can safely be ignored. */
            (void)rba_BswSrv_MemCopy((void *)(Dest_Buf+ByteNo),(const void *)&Src,NoofBytes);

        }
        else
        {
            uint8 index_u8;
            uint8 convdata_u8[8];

            /* This step is needed to perform bit operations on the Src data
             * bit operations cannot be performed on Float data type */
            /* MR12 DIR 1.1 VIOLATION: Explicit cast is provided in line with rba_BswSrv_MemCopy() definition.
               But the void pointer is always deferenced to a type based on the pointers address alignment.
               Hence the alignment warning can safely be ignored. */
            (void)rba_BswSrv_MemCopy((void *)convdata_u8, (const void *)&Src, NoofBytes);

            for(index_u8 = 0; index_u8 < NoofBytes; index_u8++)
            {
                *(Dest_Buf+ByteNo) = convdata_u8[index_u8];
                ByteNo--; /* Decrement the byte number to point to the next byte */
            }
        }
    }
    else
    {
        uint16_least index_u16;
        uint8        Mask;
        uint8        convdata_u8[8];

        /* This step is needed to perform bit operations on the Src data
         * bit operations cannot be performed on Float data type */
        /* MR12 DIR 1.1 VIOLATION: Explicit cast is provided in line with rba_BswSrv_MemCopy() definition.
           But the void pointer is always deferenced to a type based on the pointers address alignment.
           Hence the alignment warning can safely be ignored. */
        (void)rba_BswSrv_MemCopy( (void *)convdata_u8, (const void *)&Src, NoofBytes );

        Mask = (uint8) (~((uint8)(0xFFu << BitOffsetInByte)));
        /* Copy the first byte into the Ipdu buffer */
        *(Dest_Buf+ByteNo) = (uint8)((uint8)((uint8)(*(Dest_Buf+ByteNo)) & Mask) |
                                     (uint8)(convdata_u8[0] << BitOffsetInByte));

        if(Endianess == COM_LITTLEENDIAN)
        {
            /* Increment the byte number to point to the next byte */
            ByteNo++;

            /* The last byte is copied outside the loop, hence run the loop for (NoofBytes-1) times */
            for(index_u16 = 0; index_u16 < (NoofBytes-1u); index_u16++)
            {
                /* Below Function is to be masked for protection ? */
                /* Copy the left over part of first byte and additional part of next byte into the Ipdu buffer */
                *(Dest_Buf+ByteNo) = (uint8)((uint8)(convdata_u8[index_u16] >> (8u-BitOffsetInByte)) |
                                             (uint8)(convdata_u8[index_u16 + 1u] << BitOffsetInByte));

                ByteNo++; /* Increment the byte number to point to the next byte */
            }
            /* Copy the last byte into the Ipdu buffer */
            *(Dest_Buf+ByteNo) = (uint8)((*(Dest_Buf+ByteNo)) & ((uint8)(~Mask))) |
                                 (uint8)(convdata_u8[7] >> (8u-BitOffsetInByte));
        }
        else
        {
            /* Decrement the byte number to point to the next byte */
            ByteNo--;

            for(index_u16 = 0; index_u16 < (NoofBytes-1u); index_u16++)
            {
                /* Below Function is to be masked for protection */
                /* Copy the left over part of first byte and additional part of next byte into the Ipdu buffer */
                *(Dest_Buf+ByteNo) = (uint8)((uint8)(convdata_u8[index_u16] >> (8u-BitOffsetInByte)) |
                                             (uint8)((convdata_u8[index_u16 + 1u] << BitOffsetInByte)));

                ByteNo--; /* Decrement the byte number to point to the next byte */
            }
            /* Copy the last byte into the Ipdu buffer */
            *(Dest_Buf+ByteNo) = (uint8)((*(Dest_Buf+ByteNo)) & ((uint8)(~Mask))) |
                                 (uint8)(convdata_u8[7] >> (8u-BitOffsetInByte));
        }
    }

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif
/* FC_VariationPoint_END */

