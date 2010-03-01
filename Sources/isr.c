//----------------------------------------------------------------------------
//
//                  Robokid
//
//----------------------------------------------------------------------------
// isr.c    first level interrupt handling routines
// =====
//
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           31/07/2008
//                    11/08/08        Added handler for IRQ interrupt    
//----------------------------------------------------------------------------

#include "global.h"

//----------------------------------------------------------------------------
// Vrti   first level interrupt handler for RTI interrupt.
// ====
// 
// 1. Acknowledge RTI interrupt.
// 2. Call interrupt service routine
//----------------------------------------------------------------------------

interrupt VectorNumber_Vrti void Vrti1(void){

    SRTISC_RTIACK = 1;                   /* Reset real-time interrupt request flag */
    rti_isr();
}

//----------------------------------------------------------------------------
// Virq   first level interrupt handler for external IRQ interrupt.
// ====
// 
// 1. Acknowledge IRQ interrupt.
// 2. Call interrupt service routine
//----------------------------------------------------------------------------

interrupt VectorNumber_Virq void Virq1(void)
{

    IRQ_ACK;                   /* Reset real-time interrupt request flag */
    irq_isr();
}

//----------------------------------------------------------------------------
// Vkbi   first level interrupt handler for keyboard interrupts.
// ====
// 
// 1. Acknowledge IRQ interrupt.
// 2. Call interrupt service routine
//----------------------------------------------------------------------------

interrupt VectorNumber_Vkeyboard1  void Vkbi1(void)
{

    KBI_ACK;                   /* Reset real-time interrupt request flag */
    kbi_isr();
}