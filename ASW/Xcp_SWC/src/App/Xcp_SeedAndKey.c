
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/
#define XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

#if ((XCP_CMD_GET_SEED_AVAILABLE == STD_ON) || (XCP_CMD_UNLOCK_AVAILABLE == STD_ON))
/*-------------------------------------------------------------*/
/* This part is project specific and shall be totally reworked */
/*-------------------------------------------------------------*/

/* Application seed length - can be adjusted up to 255 */
#define XCP_APPL_SEED_LENGTH 4u

/* Application seed length - can be adjusted up to 255 */
#define XCP_APPL_KEY_LENGTH 4u

/* Structure for holding Seed and Resource type */
typedef struct
{
  uint8 Seed[XCP_APPL_SEED_LENGTH];
  uint8 ResourceType;
  uint8 Key[XCP_APPL_KEY_LENGTH];
  uint8 KeyLength;
}XcpAppl_SeedKeyData_t;

/* Table with internal data for SeedAndKey for every existing protocol layer */
static XcpAppl_SeedKeyData_t XcpAppl_SeedKeyData[XCP_PL_IDS];

#endif

#define XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

#if (XCP_CMD_GET_SEED_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Template of function which returns seed for unlock command
\param[out] SeedAdrPtr        Address of pointer to the Seed
\param[in]  ResourceType      Type of the resource to be unlocked
\param[in]  ProtocolLayerId   Id of protocol layer which is requesting SeedAndKey procedure
\return     Length of the Seed
***************************************************************************************************/
uint8 XcpAppl_GetSeed(Xcp_AdrPtr* SeedAdrPtr, uint8 ResourceType, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  uint8 i;

  /* Check if not null pointer */
  if (SeedAdrPtr != NULL_PTR)
  {
    /* Store resource Resource Type */
    XcpAppl_SeedKeyData[ProtocolLayerId].ResourceType = ResourceType;

    /* Set address of the pointer to the seed as return parameter */
    *SeedAdrPtr = XcpAppl_SeedKeyData[ProtocolLayerId].Seed;

    /* Fill the Seed */
    for (i = 0 ; i < XCP_APPL_SEED_LENGTH; i++)
    {
      /* Just an example seed */
      XcpAppl_SeedKeyData[ProtocolLayerId].Seed[i] = i;
    }
  }

  /* Reset received key length */
  XcpAppl_SeedKeyData[ProtocolLayerId].KeyLength = 0;

  /* Return seed length */
  return(XCP_APPL_SEED_LENGTH);
}
#endif


#if (XCP_CMD_UNLOCK_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Template of function which checks received key if is matching to calculated one
\param[in]  KeyPtr                Pointer to unlock Key
\param[in]  KeyPartLength         Length of actually received part of the Ke
\param[in]  RemainingKeyLength    Remaining length of the unlock Key
\param[out] UnlockedResource      Pointer to UnlockedResource
\param[in]  ProtocolLayerId       Id of protocol layer which is requesting SeedAndKey procedure
\retval     XCP_ERR_ACCESS_LOCKED if key is invalid
\retval     XCP_ERR_OUT_OF_RANGE  if key is too long
\retval     XCP_ERR_SEQUENCE      if key is too short
\retval     XCP_NO_ERROR          if the full key was not received UnlockedResource = 0 otherwise it will be:
                                  - XCP_RESOURCE_CALPAG
                                  - XCP_RESOURCE_DAQ
                                  - XCP_RESOURCE_STIM
                                  - XCP_RESOURCE_PGM
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_Unlock(Xcp_AdrPtrConst KeyPtr, uint8 KeyPartLength, uint8 RemainingKeyLength, uint8* UnlockedResource, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  uint8 CalculatedKey[XCP_APPL_KEY_LENGTH];
  uint8 i;
  uint8 ExpectedKeyLength;
  Xcp_ErrorCode Error;
  boolean KeyMatching;

  /* Initial values */
  *UnlockedResource = 0;

  /* Calculate expected full key length */
  ExpectedKeyLength = RemainingKeyLength + XcpAppl_SeedKeyData[ProtocolLayerId].KeyLength;

  /* Check if expected Key length is valid */
  if (ExpectedKeyLength == XCP_APPL_KEY_LENGTH)
  {
    /* Copy or concatenate Key to internal buffer reached */
    for (i = 0 ; i < KeyPartLength ; i++)
    {
      XcpAppl_SeedKeyData[ProtocolLayerId].Key[XcpAppl_SeedKeyData[ProtocolLayerId].KeyLength + i] = KeyPtr[i];
    }
    XcpAppl_SeedKeyData[ProtocolLayerId].KeyLength += KeyPartLength;

    /* Check if already full key received */
    if (XcpAppl_SeedKeyData[ProtocolLayerId].KeyLength == XCP_APPL_KEY_LENGTH)
    {
      /* Generate Key from seed */
      for (i = 0 ; i < XCP_APPL_KEY_LENGTH ; i++)
      {
        /* Simple key algorithm: Add ResourceType to every byte of seed */
        //CalculatedKey[i] = XcpAppl_SeedKeyData[ProtocolLayerId].Seed[i] + XcpAppl_SeedKeyData[ProtocolLayerId].ResourceType;
        CalculatedKey[i] = XcpAppl_SeedKeyData[ProtocolLayerId].Seed[i] + 1;
      }

      /* Init flag */
      KeyMatching = TRUE;

      /* Compare received and generated Key */
      for (i = 0 ; i < XCP_APPL_KEY_LENGTH ; i++)
      {
        /* Compare Key */
        if (CalculatedKey[i] != XcpAppl_SeedKeyData[ProtocolLayerId].Key[i])
        {
          KeyMatching = FALSE;

          /* Stop comparing */
          break;
        }
      }

      /* Check if Key is matching for requested resource */
      if (KeyMatching == TRUE)
      {
        /* Set return value as requested ResourceType */
        *UnlockedResource = XcpAppl_SeedKeyData[ProtocolLayerId].ResourceType;

        /* OK */
        Error = XCP_NO_ERROR;
      }
      else
      {
        /* Invalid Key */
        Error = XCP_ERR_ACCESS_LOCKED;
      }

      /* Reset received key length */
      XcpAppl_SeedKeyData[ProtocolLayerId].KeyLength = 0;
    }
    else
    {
      /* Mark that function has not received full key yet */
      *UnlockedResource = 0;
      Error = XCP_NO_ERROR;
    }
  }
  else if (ExpectedKeyLength < XCP_APPL_KEY_LENGTH)
  {
    /* Mark that function is expecting longer Key */
    Error = XCP_ERR_SEQUENCE;
  }
  else
  {
    /* Mark that key is too long and not supported */
    Error = XCP_ERR_OUT_OF_RANGE;
  }

  /* Return Error code */
  return (Error);
}
#endif

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"


