
#include "IpduM.h"
#include "IpduM_Priv.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : IpduM_CopyBuffer
 Syntax           : void IpduM_CopyBuffer(IpduM_SubPartType SubPartPtr, uint8 SrcPtr,uint8 DestPtr)
 Description      : This is the internal function for copying subparts.
 Parameter        : IpduM_SubPartType SubPartPtr : Configuration of subpart
					uint8 SrcPtr     			 : Pointer to input source location
					uint8 DestPtr      			 : Pointer to output destination location.

 Return value     : None.
 ***************************************************************************************************/

FUNC(void, IPDUM_CODE) IpduM_CopyBuffer(
	 CONST(boolean,IPDUM_CONST ) Endianess,
     P2CONST(IpduM_SubPartType, AUTOMATIC, IPDUM_APPL_DATA) SubPartPtr,
     P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcPtr,
     P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr)
{

	/* Local variables declaration */
	VAR(uint16, AUTOMATIC) segPos_ui;
	VAR(uint16, AUTOMATIC) bitlen_ui;

	VAR(PduLengthType, AUTOMATIC) ByteNo;
	VAR(uint16, AUTOMATIC) Bits_left;
    VAR(uint8, AUTOMATIC) BitOffsetInByte;
	VAR(uint16, AUTOMATIC) Total_BitsCopied;
    VAR(uint8, AUTOMATIC) Mask;

	segPos_ui = SubPartPtr->SegmentPos;								/* bitfield starts here */
	bitlen_ui = SubPartPtr->SegmentLen; 							/* length of bitfield */

	/*Finding the 1st Byte No*/
	ByteNo = (PduLengthType)(segPos_ui >> 3u);
    BitOffsetInByte = (uint8)(segPos_ui - (ByteNo * 8u));

	/*This Part will be executed if the Segment is placed in more than 1 byte */
	if((((ByteNo*8u)+8u) - segPos_ui)<= bitlen_ui)
	{
		/* This mask protects the other bits in the byte */
        Mask =(uint8)( ~(uint8)(0xFFu << BitOffsetInByte));
		Total_BitsCopied = (uint16)(((ByteNo*8u)+8u) - segPos_ui);
	}

	/*This Part will be executed if the Segment is placed within the same byte */
	else
	{
		/* This mask protects the other bits in the byte */
        Mask = (uint8) (~(uint8)(((uint8)(1u << bitlen_ui) - 1u) << BitOffsetInByte));
		Total_BitsCopied = bitlen_ui;
	}

	/* Update the destination pointer with the source pointer, masking the other bits in the Ipdu */
    *(DestPtr+ByteNo) = ((*(DestPtr+ByteNo)) & Mask)  | (*(SrcPtr+ByteNo) & ((uint8)(0xFFu << BitOffsetInByte) & (uint8)(~Mask)));

    /* Loop to run to copy the remaining bits */
	while (Total_BitsCopied < bitlen_ui)
	{
		Bits_left = bitlen_ui - Total_BitsCopied;

		if(Endianess != IPDUM_BIGENDIAN)
		{
			ByteNo++;
		}
		else
		{
			ByteNo--;
		}

		/* Copy the next complete byte into the destination */
		if(Bits_left >= 8u)
		{
			*(DestPtr+ByteNo) = *(SrcPtr+ByteNo);
			Total_BitsCopied = Total_BitsCopied + 8u;
		}
		/* Copy bit wise into the destination buffer */
		else
		{
			*(DestPtr+ByteNo) = ((*(DestPtr+ByteNo) & (uint8)((0xFFu << Bits_left))) | (*(SrcPtr+ByteNo) & (uint8)((0xFFu >> (uint8)(8u - Bits_left)))));
			Total_BitsCopied = Total_BitsCopied + Bits_left;
		}

	}

}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

