//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// interrupt.c : code to handle ALL interrupts
// ===========
//
// Description
//      Routines handle the following interrupts
//
//          1. IRQ        : left wheel sensor
//          2. KBI (P4)   : right wheel sensor
//          3. RTI        : 8mS timer 
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           13/08/2008      brought together all interrupt code                    
//----------------------------------------------------------------------------

#include "global.h"
//
// background 8mS timers
//
uint16_t    tick_count_16;           // rolls over after 524.28 seconds (8.7 minutes)
uint8_t     tick_count_8;            // rolls over after 2.04 seconds
uint8_t     second_count;            // rolls over after 255 seconds
uint8_t     tick_for_second_count;
//
// switch data
//
uint8_t     switch_debounced_state, switch_states[SWITCH_SAMPLES];
uint8_t     sample_index, debounced_state;
uint8_t     switch_A, switch_B, switch_C, switch_D, switch_ABCD;
//
// display data
//
uint8_t     temp_flash_count, temp_LED_image, temp_display_image;
uint8_t     display_no;
//
// wheel count and speed data
//
uint16_t    left_wheel_count, right_wheel_count;
uint8_t     left_wheel_sensor_value, right_wheel_sensor_value;
uint8_t     left_speed_index, right_speed_index;
uint16_t    left_speed_array[64], right_speed_array[64];
//
// sound system data
//
uint8_t     note_pt, note_duration;



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// First level interrupt handlers.
// ==============================
//
//----------------------------------------------------------------------------
// Virq   first level interrupt handler for external IRQ interrupt.
// ====
// 
// 1. Acknowledge IRQ interrupt.
// 2. Call interrupt service routine
//----------------------------------------------------------------------------

interrupt VectorNumber_Virq void Virq1(void) {

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

interrupt VectorNumber_Vkeyboard1  void Vkbi1(void) {

    KBI_ACK;                   /* Reset KBI interrupt request flag */
    kbi_isr();
}

//----------------------------------------------------------------------------
// Vrti   first level interrupt handler for RTI interrupt.
// ====
// 
// 1. Acknowledge RTI interrupt.
// 2. Call interrupt service routine
//----------------------------------------------------------------------------

interrupt VectorNumber_Vrti void Vrti1(void) {

    SRTISC_RTIACK = 1;                   /* Reset real-time interrupt request flag */
    rti_isr();
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Second level interrupt handlers.
// ================================
//
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
void irq_isr(void) {

    right_wheel_count++;
}

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
void kbi_isr(void) {

    left_wheel_count++;
}

//----------------------------------------------------------------------------
// rti_isr : handle rti interrupt
// =======
//
// Description
//      Background timer interrupt occurs every 8ms.
//      User to schedule a range of timed activities.
// Notes
//      rather goes against the idea of making interrupt routines
//      as small as possible. Not sure if this could be done in a more
//      efficient manner. 
//      (need to measure the time this routine takes to execute)
//        
//----------------------------------------------------------------------------
void rti_isr(void) {
uint8_t   i, tmp;
//
// Timer interrupt occurs every 8mS.
//
// Task 1 : count 8mS time units
// 
//      System has an 8-bit and 16-bit tick counters.
//      Can be used by any routines that needs background timing (e.g. timeouts)   
// 
    tick_count_16++ ; 
    tick_count_8++;
//
// Task 2 : sample set of switches and debounce
//          (Note : may not need to be done every 8mS)
//
    switch_states[sample_index] = PTCD; 
    ++sample_index; 
    switch_debounced_state = 0xff; 
    for(i=0; i < SWITCH_SAMPLES; i++) { 
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
    switch_ABCD = debounced_state & 0b00111100;
//
// Task 3 : implement flashing of LED displays
//
    temp_flash_count--;                    // decrements every 8mS
    if (temp_flash_count == 0) {
        temp_flash_count = flash_count;    // reload flash counter
    
        if (LED_flash_map != 0) {            
            LED_image = LED_image ^ LED_flash_map;
            PTGD = LED_image;
        }
    }
//
// Task 4 : shift to next characters for dual 7-segment displays
//
    if (robot_display.shift_rate != 0) {
        robot_display.shift_count--;
        if (robot_display.shift_count == 0) {
            robot_display.shift_count = robot_display.shift_rate;
            robot_display.char_ptr++;
            if (robot_display.char_ptr >= robot_display.char_count){
                robot_display.char_ptr = 0;
            } 
        }
    }
//
// Task 5 : Multiplex dual 7-segment displays : 8mS switching
//
    if (display_no == SEVEN_SEG_A){
        SEG_A_CTRL = 1; SEG_B_CTRL = 0;
        PTAD = robot_display.data_A[robot_display.char_ptr];
        display_no = SEVEN_SEG_B;
    } else {
        SEG_A_CTRL = 0; SEG_B_CTRL = 1;
        PTAD = robot_display.data_B[robot_display.char_ptr];
        display_no = SEVEN_SEG_A;
    }
//
// Task 6 : manage playing of current tune
//
    if (sound_file.mode == SOUND_ENABLE) { 
        if (note_duration == 0) {       // end of a note or about to start
            if (note_pt == 0) {         // start first note
                note_duration = sound_file.note[0][1];
                setReg16(TPM2MOD, tone_codes[sound_file.note[0][0]]);      // set period
                setReg16(TPM2C0V, (tone_codes[sound_file.note[0][0]]/2));
            }      
            if (note_pt >= sound_file.note_count) {     // no more notes so disable
                sound_file.mode = SOUND_DISABLE;
                note_pt = 0;
                note_duration = 0;
                setReg16(TPM2C0V, 0);
            } else {
                if (sound_file.note[note_pt][0] == SILENT_NOTE) {  // silent note
                    setReg16(TPM2C0V, 0);
                    note_duration = sound_file.note[note_pt][1]; 
                } else {                 //  configure new note
                    setReg16(TPM2MOD, tone_codes[sound_file.note[note_pt][0]]);      // set period
                    setReg16(TPM2C0V, (tone_codes[sound_file.note[note_pt][0]]/2));
                    note_duration = sound_file.note[note_pt][1]; 
                }
                note_pt++;
            }
        } else {
            note_duration--;
        }
    }
//
// Task 7 : Read and process wheel position encoders
//    
    tmp = interrupt_get_adc(WHEEL_SENSOR_L);
   //
   // threshold value
   //
    if (tmp < FLASH_data.LEFT_WHEEL_THRESHOLD) {
        tmp = BLACK; 
    } else {
        tmp = WHITE;
    }
   //
   // check for signal change
   //
    if (tmp != left_wheel_sensor_value) {
        left_wheel_count++;
        left_wheel_sensor_value = tmp;
    }
   //
   // repeat for right sensor
   // 
    tmp = interrupt_get_adc(WHEEL_SENSOR_R);
    if (tmp < FLASH_data.RIGHT_WHEEL_THRESHOLD) {
        tmp = BLACK; 
    } else {
        tmp = WHITE;
    }
    if (tmp != right_wheel_sensor_value) {
        right_wheel_count++;
        right_wheel_sensor_value = tmp;
    }   
//
// Task 8 : check for 1 second period and run 1 second tasks
// 
    if ((tick_for_second_count--) == 0) {
        tick_for_second_count = TICKS_IN_ONE_SECOND;
        //
        //  Task 8.1 : keep second count (rolls over after 255 seconds)
        //
        second_count++;
        //
        //  Task 8.2 : read wheel counter for speed and store in circular buffer
        //             buffer stores the last 64 values (last 64 seconds)
        //
//        left_speed_array[left_speed_index++] =  left_wheel_count;
//        left_speed_index &= (sizeof(left_speed_array)/sizeof(uint16_t));         // handle circular buffer pointer
//        right_speed_array[right_speed_index++] =  right_wheel_count;
//        right_speed_index &= (sizeof(right_speed_array)/sizeof(uint16_t));       // handle circular buffer pointer
    }
}

