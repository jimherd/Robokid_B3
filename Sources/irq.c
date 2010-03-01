//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// irq.c    handle IRQ interrupt
// =====
//
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           11/08/2008    
//----------------------------------------------------------------------------

#include "global.h"

extern uint16_t  left_wheel_count, right_wheel_count;

//----------------------------------------------------------------------------
// irq_isr : handle irq interrupt
// =======
//
// Description
//      irq interrupt is linked to the left wheel rotation sensor through
//      pin 2 (signal IRQ).  Basic requirement is to increment the rotation
//      counter.
//
// Notes
//         
//----------------------------------------------------------------------------
void irq_isr(void)
{
    left_wheel_count++;
}