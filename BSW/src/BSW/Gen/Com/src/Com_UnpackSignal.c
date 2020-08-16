

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_UnpackSignal
 Syntax           : Com_SigMaxType Com_UnpackSignal(uint8 Endianess,Com_BitpositionType Bit_Pos,
                                                    Com_BitsizeType Bitsize, uint8 *Src_Buf)
 Description      : Internal function used for unpacking the signal from Ipdu Buffer
 Parameter        : Endianess,Bit_Pos,Bitsize,*Src_Buf
 Return value     : Com_SigMaxType
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(Com_SigMaxType, COM_CODE) Com_UnpackSignal( VAR(uint8, AUTOMATIC)                    Endianess,
                                                 VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos,
                                                 VAR(Com_BitsizeType, AUTOMATIC)          Bitsize,
                                                 P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src_Buf )
{
    /* Bfx - AR specific service library is not used, for the signal unpacking operations for below reasons
     *  1. There is a function Bfx_PutBits takes a variable of type of data (uint8/16/32) as source variable and
     *      a Input data pointer of same respective type (uint8/16/32/64),
     *  2. It takes bit string from a source variable and puts them in destination data ptr.
     *  On the similar lines,If this api is used in Com, there will still be many bit type operations which
     *  have to be performed in the Com code, Hence there is no much help, as bit operations (significant in number)
     *  are done both in Com and SrvLib
     */

    VAR(Com_SigMaxType, AUTOMATIC)  a_data;
    VAR(PduLengthType, AUTOMATIC)    ByteNo;
    VAR(uint16_least, AUTOMATIC)     Bits_left;
    VAR(uint16_least, AUTOMATIC)     Total_BitsCopied;
    VAR(uint8_least, AUTOMATIC)      BitOffsetInByte;

    /* Finding the 1st Byte No */
    ByteNo          = (PduLengthType)(Bit_Pos >> 3u);
    BitOffsetInByte = (uint8_least)(Bit_Pos % 8u);

    a_data = (Com_SigMaxType)(*(Src_Buf + ByteNo) >> BitOffsetInByte);

    if (Bitsize >= (8u - BitOffsetInByte))
    {
        /* This Part will be executed if the Signal is placed in more than 1 byte */
        Total_BitsCopied = (uint16_least)(8u - BitOffsetInByte);
    }
    else
    {
        /* This Part will be executed if the Signal is placed within the same byte
         * Once data is copied, ensure the remaining bits are zero */
        a_data = a_data & (uint8)(~(uint8)(0xFFu << Bitsize));
        Total_BitsCopied = Bitsize;
    }

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

        if(Bits_left >= 8u)
        {
            /* The data has been typecasted to Com_SigMaxType, to ensure data is not lost after the shifting. */
            a_data = (((Com_SigMaxType)(*(Src_Buf + ByteNo))) << Total_BitsCopied) | a_data;

            Total_BitsCopied = Total_BitsCopied + 8u;
        }
        else
        {
            /* The data has been typecasted to Com_SigMaxType, to ensure data is not lost after the shifting. */
            a_data = ((Com_SigMaxType)(*(Src_Buf + ByteNo) & ((uint8)(0xFFu >> (8u - Bits_left)))) << Total_BitsCopied) | a_data;

            Total_BitsCopied = Total_BitsCopied + Bits_left;
        }
    }

    /*Return the Unpacked data*/
    return(a_data);

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"


/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_UnpackOpaqueSignal
 Syntax           : void Com_UnpackOpaqueSignal(Com_BitpositionType Bit_Pos, Com_BitsizeType SignalLength,
                    uint8 *Src_Buf)
 Description      : Internal function used for unpacking a UINT8_N opaque signal from Ipdu Buffer
 Parameter        : Bit_Pos,SignalLength,*Src_Buf
 Return value     : uint32
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint32, COM_CODE) Com_UnpackOpaqueSignal(VAR(Com_BitpositionType, AUTOMATIC)      Bit_Pos,
                                              VAR(Com_BitsizeType, AUTOMATIC)          SignalLength,
                                              P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src_Buf)
{
    VAR(uint16_least, AUTOMATIC) ByteNo;
    VAR(uint32, AUTOMATIC) a_data;

    a_data = 0x00;

    /*Find the First Byte of the signal: Bit_Pos >> 8  */
    ByteNo = (Bit_Pos >> 3u);

    while (SignalLength > 0)
    {
        a_data = (uint32)( a_data << 8u) | (uint32)(*(Src_Buf + ByteNo));
        ByteNo ++;
        SignalLength--;
    }

    /*Return the Unpacked data*/
    return(a_data);

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_START */

#if defined (COM_RXSIG_FLOAT64SUPP ) || defined(COM_RXGRPSIG_FLOAT64SUPP)
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_UnPackFloatSignal
 Syntax           : float64 Com_UnPackFloatSignal(uint8 Endianess,Com_BitpositionType Bit_Pos, uint8* Src_Buf)
 Description      : Internal function used for packing the signal into Ipdubuffer
 Parameter        : Endianess -> Little Endian/Big Endian
                  : Bit_Pos ->   Position of the signal in the ipdu
                  : Src_Buf ->   Buffer where signal data is available
 Return value     : The function returns the unpacked Float64 value
 Operation        : This function only packs Float64 signals/ group signals into Tx Ipdu buffer.
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
FUNC(float64, COM_CODE) Com_UnPackFloatSignal(VAR(uint8, AUTOMATIC) Endianess, VAR(Com_BitpositionType, AUTOMATIC) Bit_Pos,
                P2CONST(uint8,AUTOMATIC,COM_APPL_DATA) Src_Buf)
{

    VAR(PduLengthType, AUTOMATIC) ByteNo;
    VAR(PduLengthType, AUTOMATIC) NoofBytes;
    VAR(uint8_least, AUTOMATIC) BitOffsetInByte;
    VAR(float64, AUTOMATIC) Dest_Buf_f64;
    VAR(uint8, AUTOMATIC) destdata_u8[8] = {0,0,0,0,0,0,0,0};

    /* Float64 data type has 8 bytes */
    NoofBytes = 8;
    ByteNo = Bit_Pos >> 3u;
    BitOffsetInByte = (uint8)(Bit_Pos % 8u);

    if(BitOffsetInByte ==  (uint8_least)0)
    {
        if(Endianess == COM_LITTLEENDIAN)
        {
            /* MR12 DIR 1.1 VIOLATION: Explicit cast is provided in line with rba_BswSrv_MemCopy() definition.
               But the void pointer is always deferenced to a type based on the pointers address alignment.
               Hence the alignment warning can safely be ignored. */
            (void)rba_BswSrv_MemCopy( (void *)destdata_u8, (const void *)Src_Buf, NoofBytes );

        }
        else
        {
            uint8 index_u8;
            for(index_u8 = 0 ; index_u8 < NoofBytes; index_u8++)
            {
                destdata_u8[index_u8] = *(Src_Buf+ByteNo);
                ByteNo--;
            }
        }
    }
    else
    {
        uint16_least index_u16;
        if(Endianess == COM_LITTLEENDIAN)
        {
            /* Run the loop for NoofBytes times with an offset to Ipdu buffer */
            for(index_u16 = 0; index_u16 < NoofBytes; index_u16++)
            {
                /* Below Function is to be masked for protection ? */
                /* Copy the left over part of first byte and additional part of next byte into the Ipdu buffer */
                destdata_u8[index_u16] = (uint8)((uint8)(*(Src_Buf+ByteNo)) >> BitOffsetInByte) | (uint8)((*(Src_Buf+(ByteNo + 1u))) << (8u-BitOffsetInByte));

                ByteNo++;
            }
        }
        else
        {
            /* Decrement the byte number to point to the next byte */
            for(index_u16 = 0; index_u16 < NoofBytes; index_u16++)
            {
                /* Below Function is to be masked for protection ? */
                /* Copy the left over part of first byte and additional part of next byte into the Ipdu buffer */
                destdata_u8[index_u16] = (uint8)((*(Src_Buf+ByteNo)) >> BitOffsetInByte) | (uint8)((*(Src_Buf+(ByteNo -1u))) << (8u-BitOffsetInByte));

                ByteNo--;
            }
        }
    }
    /* Convert the data into float64 type */
    /* MR12 DIR 1.1 VIOLATION: Explicit cast is provided in line with rba_BswSrv_MemCopy() definition.
       But the void pointer is always deferenced to a type based on the pointers address alignment.
       Hence the alignment warning can safely be ignored. */
    (void)rba_BswSrv_MemCopy( (void *)&Dest_Buf_f64, (const void *)destdata_u8, NoofBytes );

    return(Dest_Buf_f64);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif
/* FC_VariationPoint_END */

