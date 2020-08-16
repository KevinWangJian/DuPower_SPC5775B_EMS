/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/



/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "Crc.h"

/**
 **********************************************************************************************************************
 * Crc_calculateCRC32P4
 *
 * \brief Calculates the remainder of a polynomial division: input is divided by the CRC32P4 polynomial
 *
 * Crc_CalculateCRC32P4 calculates the remainder of a polynomial divided by the crc polynomial with Hex-value
 * 0x1F4ACFB13.
 * Crc calculation starts with an initial value, Crc_StartValue32.
 * The Crc remainder is calculated over a reflected data stream *Crc_DataPtr of length Crc_Length.
 * Note, 0xC8DF352F is the reflected data stream of 0xF4ACFB13. 0xF4ACFB13 describes the truncated crc polynomial .
 * Thus, 0xC8DF352F is the reflected data stream of the truncated crc polynomial.
 * The result data are reflected, too.
 * At the end the remainder is manipulated by a XOR operation using the value CRC_XOR_VALUE32.
 *
 * \param    Crc_DataPtr,      Pointer to start address of data block
 * \param    Crc_Length,       Length of data block to be calculated in bytes
 * \param    Crc_StartValue32  Start value when the algorithm starts
 * \return                     Remainder after polynomial division *const Crc_DataPtr / CRC32P4
 **********************************************************************************************************************
 */
/*
 **********************************************************************************************************************
 * TABLE Version, Revision_2
 **********************************************************************************************************************
*/

#define CRC_START_SEC_CONST_32
#include "Crc_MemMap.h"
const uint32  CRC_32P4_POLYNOMIAL_Tbl[((uint16)CRC_32P4_TABLESIZE)] =
{
    /*  0:*/ 0x00000000uL, 0x30850FF5uL, 0x610A1FEAuL, 0x518F101FuL,
    /*  4:*/ 0xC2143FD4uL, 0xF2913021uL, 0xA31E203EuL, 0x939B2FCBuL,
    /*  8:*/ 0x159615F7uL, 0x25131A02uL, 0x749C0A1DuL, 0x441905E8uL,
    /*  8:*/ 0xD7822A23uL, 0xE70725D6uL, 0xB68835C9uL, 0x860D3A3CuL,
    /* 16:*/ 0x2B2C2BEEuL, 0x1BA9241BuL, 0x4A263404uL, 0x7AA33BF1uL,
    /* 20:*/ 0xE938143AuL, 0xD9BD1BCFuL, 0x88320BD0uL, 0xB8B70425uL,
    /* 24:*/ 0x3EBA3E19uL, 0x0E3F31ECuL, 0x5FB021F3uL, 0x6F352E06uL,
    /* 28:*/ 0xFCAE01CDuL, 0xCC2B0E38uL, 0x9DA41E27uL, 0xAD2111D2uL,
    /* 32:*/ 0x565857DCuL, 0x66DD5829uL, 0x37524836uL, 0x07D747C3uL,
    /* 36:*/ 0x944C6808uL, 0xA4C967FDuL, 0xF54677E2uL, 0xC5C37817uL,
    /* 40:*/ 0x43CE422BuL, 0x734B4DDEuL, 0x22C45DC1uL, 0x12415234uL,
    /* 44:*/ 0x81DA7DFFuL, 0xB15F720AuL, 0xE0D06215uL, 0xD0556DE0uL,
    /* 48:*/ 0x7D747C32uL, 0x4DF173C7uL, 0x1C7E63D8uL, 0x2CFB6C2DuL,
    /* 52:*/ 0xBF6043E6uL, 0x8FE54C13uL, 0xDE6A5C0CuL, 0xEEEF53F9uL,
    /* 56:*/ 0x68E269C5uL, 0x58676630uL, 0x09E8762FuL, 0x396D79DAuL,
    /* 60:*/ 0xAAF65611uL, 0x9A7359E4uL, 0xCBFC49FBuL, 0xFB79460EuL,
    /* 64:*/ 0xACB0AFB8uL, 0x9C35A04DuL, 0xCDBAB052uL, 0xFD3FBFA7uL,
    /* 68:*/ 0x6EA4906CuL, 0x5E219F99uL, 0x0FAE8F86uL, 0x3F2B8073uL,
    /* 72:*/ 0xB926BA4FuL, 0x89A3B5BAuL, 0xD82CA5A5uL, 0xE8A9AA50uL,
    /* 76:*/ 0x7B32859BuL, 0x4BB78A6EuL, 0x1A389A71uL, 0x2ABD9584uL,
    /* 80:*/ 0x879C8456uL, 0xB7198BA3uL, 0xE6969BBCuL, 0xD6139449uL,
    /* 84:*/ 0x4588BB82uL, 0x750DB477uL, 0x2482A468uL, 0x1407AB9DuL,
    /* 88:*/ 0x920A91A1uL, 0xA28F9E54uL, 0xF3008E4BuL, 0xC38581BEuL,
    /* 92:*/ 0x501EAE75uL, 0x609BA180uL, 0x3114B19FuL, 0x0191BE6AuL,
    /* 96:*/ 0xFAE8F864uL, 0xCA6DF791uL, 0x9BE2E78EuL, 0xAB67E87BuL,
    /*100:*/ 0x38FCC7B0uL, 0x0879C845uL, 0x59F6D85AuL, 0x6973D7AFuL,
    /*104:*/ 0xEF7EED93uL, 0xDFFBE266uL, 0x8E74F279uL, 0xBEF1FD8CuL,
    /*108:*/ 0x2D6AD247uL, 0x1DEFDDB2uL, 0x4C60CDADuL, 0x7CE5C258uL,
    /*112:*/ 0xD1C4D38AuL, 0xE141DC7FuL, 0xB0CECC60uL, 0x804BC395uL,
    /*116:*/ 0x13D0EC5EuL, 0x2355E3ABuL, 0x72DAF3B4uL, 0x425FFC41uL,
    /*120:*/ 0xC452C67DuL, 0xF4D7C988uL, 0xA558D997uL, 0x95DDD662uL,
    /*124:*/ 0x0646F9A9uL, 0x36C3F65CuL, 0x674CE643uL, 0x57C9E9B6uL,
    /*128:*/ 0xC8DF352FuL, 0xF85A3ADAuL, 0xA9D52AC5uL, 0x99502530uL,
    /*132:*/ 0x0ACB0AFBuL, 0x3A4E050EuL, 0x6BC11511uL, 0x5B441AE4uL,
    /*136:*/ 0xDD4920D8uL, 0xEDCC2F2DuL, 0xBC433F32uL, 0x8CC630C7uL,
    /*140:*/ 0x1F5D1F0CuL, 0x2FD810F9uL, 0x7E5700E6uL, 0x4ED20F13uL,
    /*144:*/ 0xE3F31EC1uL, 0xD3761134uL, 0x82F9012BuL, 0xB27C0EDEuL,
    /*148:*/ 0x21E72115uL, 0x11622EE0uL, 0x40ED3EFFuL, 0x7068310AuL,
    /*152:*/ 0xF6650B36uL, 0xC6E004C3uL, 0x976F14DCuL, 0xA7EA1B29uL,
    /*156:*/ 0x347134E2uL, 0x04F43B17uL, 0x557B2B08uL, 0x65FE24FDuL,
    /*160:*/ 0x9E8762F3uL, 0xAE026D06uL, 0xFF8D7D19uL, 0xCF0872ECuL,
    /*164:*/ 0x5C935D27uL, 0x6C1652D2uL, 0x3D9942CDuL, 0x0D1C4D38uL,
    /*168:*/ 0x8B117704uL, 0xBB9478F1uL, 0xEA1B68EEuL, 0xDA9E671BuL,
    /*172:*/ 0x490548D0uL, 0x79804725uL, 0x280F573AuL, 0x188A58CFuL,
    /*176:*/ 0xB5AB491DuL, 0x852E46E8uL, 0xD4A156F7uL, 0xE4245902uL,
    /*180:*/ 0x77BF76C9uL, 0x473A793CuL, 0x16B56923uL, 0x263066D6uL,
    /*184:*/ 0xA03D5CEAuL, 0x90B8531FuL, 0xC1374300uL, 0xF1B24CF5uL,
    /*188:*/ 0x6229633EuL, 0x52AC6CCBuL, 0x03237CD4uL, 0x33A67321uL,
    /*192:*/ 0x646F9A97uL, 0x54EA9562uL, 0x0565857DuL, 0x35E08A88uL,
    /*196:*/ 0xA67BA543uL, 0x96FEAAB6uL, 0xC771BAA9uL, 0xF7F4B55CuL,
    /*200:*/ 0x71F98F60uL, 0x417C8095uL, 0x10F3908AuL, 0x20769F7FuL,
    /*204:*/ 0xB3EDB0B4uL, 0x8368BF41uL, 0xD2E7AF5EuL, 0xE262A0ABuL,
    /*208:*/ 0x4F43B179uL, 0x7FC6BE8CuL, 0x2E49AE93uL, 0x1ECCA166uL,
    /*212:*/ 0x8D578EADuL, 0xBDD28158uL, 0xEC5D9147uL, 0xDCD89EB2uL,
    /*216:*/ 0x5AD5A48EuL, 0x6A50AB7BuL, 0x3BDFBB64uL, 0x0B5AB491uL,
    /*220:*/ 0x98C19B5AuL, 0xA84494AFuL, 0xF9CB84B0uL, 0xC94E8B45uL,
    /*224:*/ 0x3237CD4BuL, 0x02B2C2BEuL, 0x533DD2A1uL, 0x63B8DD54uL,
    /*228:*/ 0xF023F29FuL, 0xC0A6FD6AuL, 0x9129ED75uL, 0xA1ACE280uL,
    /*232:*/ 0x27A1D8BCuL, 0x1724D749uL, 0x46ABC756uL, 0x762EC8A3uL,
    /*236:*/ 0xE5B5E768uL, 0xD530E89DuL, 0x84BFF882uL, 0xB43AF777uL,
    /*240:*/ 0x191BE6A5uL, 0x299EE950uL, 0x7811F94FuL, 0x4894F6BAuL,
    /*244:*/ 0xDB0FD971uL, 0xEB8AD684uL, 0xBA05C69BuL, 0x8A80C96EuL,
    /*248:*/ 0x0C8DF352uL, 0x3C08FCA7uL, 0x6D87ECB8uL, 0x5D02E34DuL,
    /*252:*/ 0xCE99CC86uL, 0xFE1CC373uL, 0xAF93D36CuL, 0x9F16DC99uL
};
#define CRC_STOP_SEC_CONST_32
#include "Crc_MemMap.h"

#define CRC_START_SEC_CODE
#include "Crc_MemMap.h"


uint32 Crc_CalculateCRC32P4(const uint8* Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32,
                            boolean Crc_IsFirstCall)
{
    uint32_least  index;
    uint32        crcTemp;
    uint32        result;


    if (Crc_IsFirstCall != FALSE)
    {
        crcTemp = CRC_INITIAL_VALUE32P4;
    }
    else
    {
        crcTemp = Crc_StartValue32 ^ CRC_XOR_VALUE32P4;
    }

    for (index = 0U; index < Crc_Length; ++index)
    {
        /* Impact of temporary rest on next crc rest */
        crcTemp ^= Crc_DataPtr[index];

        crcTemp = (crcTemp >> ((uint8)CRC_32P4_CHUNK)) ^
                   CRC_32P4_POLYNOMIAL_Tbl[crcTemp & ((uint8)CRC_32P4_TABLEMASK)];
    }
    result = crcTemp ^ CRC_XOR_VALUE32P4;

    return (result);
}

#define CRC_STOP_SEC_CODE
#include "Crc_MemMap.h"
