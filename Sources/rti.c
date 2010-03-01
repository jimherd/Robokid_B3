//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// rti.c    handle RTI 8mS interrupt
// =====
//
// Description
//      RTI provides a simple regular 8mS interrupt that is used to execute
//      a series of actions that need to be handled on a regular basis.
//
//          Task 1 : count time units
//          Task 2 : sample set of switches and debounce
//          Task 3 : implement display flashing
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           31/07/2008    
//----------------------------------------------------------------------------

#include "global.h"

uint32_t    tick_count;         // 32-bit 8mS  counter
uint8_t     switch_debounced_state, switch_states[SWITCH_SAMPLES];
uint8_t     sample_index, debounced_state;
uint8_t     switch_A, switch_B, switch_C, switch_D;
uint8_t     temp_flash_count, temp_LED_image, temp_display_image;

extern uint8_t     LED_image, display_image, swap_image, LED_flash_map, display_flash_mode, flash_count;


//----------------------------------------------------------------------------
// rti_isr : handle rti interrupt
// =======
//
// Description
//
// Notes
//         
//----------------------------------------------------------------------------
void rti_isr(void) 
{
uint8_t   i, temp;
//
// Timer interrupt occurs every 8mS.
//
// Task 1 : count time units
// 
//      Can be used by any routines that needs background timing (e.g. timeouts)
//      32-bit value that goes back to 0 after about 397 days      
//
    tick_count++;
//
// Task 2 : sample set of switches and debounce
//          (Note : may not need to be done every 8mS)
//
    switch_states[sample_index] = PTCD; 
    ++sample_index; 
    switch_debounced_state = 0xff; 
    for(i=0; i<SWITCH_SAMPLES; i++) { 
        switch_debounced_state = switch_debounced_state & switch_states[i]; 
    }
    debounced_state = switch_debounced_state; 
    if(sample_index >= SWITCH_SAMPLES) {
        sample_index = 0; 
    }
    //
    // code to extract switch bits
    //
    switch_A = ((debounced_state & 0b00000100) >> 2 )  & 0b00000001;
    switch_B = ((debounced_state & 0b00001000) >> 3 )  & 0b00000001;
    switch_C = ((debounced_state & 0b00100000) >> 5 )  & 0b00000001;
    switch_D = ((debounced_state & 0b00010000) >> 4 )  & 0b00000001;
//
// Task 3 : implement display flashing
//
    temp_flash_count--;                    // decrements every 8mS
    if (temp_flash_count == 0) {
        temp_flash_count = flash_count;    // reload flash counter
    
        if (LED_flash_map != 0) {            
            LED_image = LED_image ^ LED_flash_map;
            PTGD = LED_image;
        }

        if (display_flash_mode == FLASH_ON) {           
            temp = display_image;
            display_image = swap_image;
            PTAD = display_image;
            swap_image = temp;
        }
    }
//
// Task 4 :
//      
}
