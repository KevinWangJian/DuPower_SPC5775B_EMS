/**HEADER********************************************************************
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: ee_demo.c$
* $Version : 1.12$
* $Date    : Dec-19-2014$
*
* Comments:
*
*   
*
*END************************************************************************/
#include "block_mpc57xx.h"

#if DCACHE_AVAILABLE
#include "ssd_types.h"
#ifdef __ghs__
    #include <ppc_ghs.h>
    #define E200CORE_SYNC()             __MSYNC() /* Memory synchronize  */
    #define E200CORE_ISYNC()            __ISYNC() /* Instruction synchronize */
    #define E200CORE_SPR_GET(lhs, reg)  {lhs = __MFSPR(reg);} /* read from special register*/
    #define E200CORE_SPR_SET(reg, val)  __MTSPR(reg, val) /* write to special register*/
#elif (defined __CWCC__)
    #define E200CORE_SYNC()            asm(" msync") /* Memory synchronize  */
    #define E200CORE_ISYNC()           asm ("isync") /* Instruction synchronize */
    #define E200CORE_SPR_GET(lhs, reg) {register _t; asm{ mfspr _t, reg } lhs = _t; } /* read from special register*/
    #define E200CORE_SPR_SET(reg, val) {register _t = val; asm{ mtspr reg, _t } } /* write to special register*/
#elif (defined __DCC__)
    #include <diab/asm.h>
    #define E200CORE_SYNC()             __msync() /* Memory synchronize  */
    #define E200CORE_ISYNC()            __isync() /* Instruction synchronize */
    #define E200CORE_SPR_GET(lhs, reg)  {lhs = __mfspr(reg);} /* read from special register*/
    #define E200CORE_SPR_SET(reg, val)  __mtspr(reg, val) /* write to special register*/
#else
    //#error "This compiler is not supported"
#endif
#define E200CORE_L1CSR0         1010 /* L1 Cache Control and Status Register 0 */
#define E200CORE_L1CSR0_CE      0x00000001 /* Data cache enable */
#define E200CORE_L1CSR0_CWM     0x00100000 /* Data cache Write mode */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : dcache_enable
* Returned Value   : none
* Comments         :
*   This function enables the data cache
*
*END*----------------------------------------------------------------------*/

void dcache_enable
   (
        void
   )
{ /* Body */
#if 0
   register UINT32 i;
   /* Read L1CSR0 */
   E200CORE_SPR_GET(i,E200CORE_L1CSR0); 
   /* enable copy-back mode,enable cache */
   i |= E200CORE_L1CSR0_CE | E200CORE_L1CSR0_CWM;
   /* Memory Synchronize */
   E200CORE_SYNC();
   /* Instruction Synchronize */
   E200CORE_ISYNC();
   /* Write to L1CSR0 */
   E200CORE_SPR_SET(E200CORE_L1CSR0,i);      
   /* Instruction Synchronize */
   E200CORE_ISYNC();
#endif
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : dcache_disable
* Returned Value   : none
* Comments         :
*   This function disables the data cache (if possible)
*
*END*----------------------------------------------------------------------*/

void dcache_disable
   (
      void
   )
{ /* Body */
#if 0
	register UINT32 val;
   
   E200CORE_SPR_GET(val,E200CORE_L1CSR0); /* L1CSR0 */
   val &= ~E200CORE_L1CSR0_CE;
   /* Memory Synchronize */
   E200CORE_SYNC();
   /* Instruction Synchronize */
   E200CORE_ISYNC();
   E200CORE_SPR_SET(E200CORE_L1CSR0,val);
   /* Instruction Synchronize */
   E200CORE_ISYNC();
#endif

} /* Endbody */
#endif
/* EOF */
