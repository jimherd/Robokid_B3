//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// kbi.c    handle keyboard interrupt
// =====
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           12/08/2008    
//----------------------------------------------------------------------------

#include "global.h"

extern uint16_t  left_wheel_count, right_wheel_count;

//----------------------------------------------------------------------------
// kbi_isr : handle KBI interrupt
// =======
//
// Description
//      keyboard interrupt is linked to the left wheel rotation sensor through
//      pin 49 (signal PTG4/KBI1P4).  Basic requirement is to increment the rotation
//      counter.
//
// Notes
//         
//----------------------------------------------------------------------------
void kbi_isr(void)
{
    right_wheel_count++;
}