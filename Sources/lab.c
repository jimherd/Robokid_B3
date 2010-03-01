//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// lab.c : run unit as lab helper unit
// =====
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd          04/09/09      
//----------------------------------------------------------------------------

#include "global.h"

//----------------------------------------------------------------------------
// run_lab_mode : run robot as a a lab support unit
// ============
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch C = exit to main slection level
//          switch D = step through selections
//
uint8_t run_lab_mode(void) 
{
uint8_t   activity;

    L_MODE_LEDS;
    activity = FIRST_SKETCH_MODE;
    show_dual_chars(LAB_MODE_CODE, ('0'+ activity), (A_TO_FLASH | 10));
//
// main loop
//       
    FOREVER {
//
//  check and act on the switches
//
        if (switch_D == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_D);
            activity++;
            SOUND_NEXT_SELECTION;
            if (activity > LAST_PROGRAM_MODE) {
                activity = FIRST_PROGRAM_MODE;
            }
            show_dual_chars(LAB_MODE_CODE, ('0'+ activity), (A_TO_FLASH | 10));
        }
        if (switch_C == PRESSED) {            //  back to main
            SOUND_EXIT_SELECTION; 
            WAIT_SWITCH_RELEASED(switch_C);
            return 0;
        }        
        if (switch_A == PRESSED) {              
            set_LED(LED_A, FLASH_ON); 
            set_LED(LED_D, FLASH_ON);
            WAIT_SWITCH_RELEASED(switch_A); 
        } else {
            continue;
        }
//
// run a joystick activity
// 
        show_dual_chars(LAB_MODE_CODE, ('0'+ activity), 0);
        push_LED_display();       
        switch (activity) {
                case LAB_MODE_0 :                          // in progress
                    run_lab_mode_0();
                    break;
                case LAB_MODE_1 :                          // in progress
                    run_lab_mode_1();
                    break;
                case LAB_MODE_2 :                          // in progress
                    run_lab_mode_2();
                    break;                                        
                default :
                    break;
        }
        show_dual_chars(LAB_MODE_CODE, ('0'+ activity), (A_TO_FLASH | 10));
        pop_LED_display();       
    } 
}

//----------------------------------------------------------------------------
// run_lab_mode_0 : use unit as a stopwatch
// ==============
//
// Description
//      The front left and right sensor inputs act as counter start/stop signals.
//      
//
// Notes
//
//      Active switches are 
//          switch A = arm/disarm count mode
//          switch B = reset count
//          switch C = exit mode
//          switch D = 
//
//      Active pots
//          pot 1 = 
//          pot 2 = 
//          pot 3 = 
//
//      Other inputs
//          front left sensor  = start timing
//          front right sensor = stop timing
//

enum { COUNTING_OFF, COUNTING_ON };
    

uint8_t run_lab_mode_0(void) 
{
mode_state_t  state;
uint8_t       count_100mS, count_mode; 
uint16_t      t_count, count_seconds; 
uint32_t      count_mS;

    state = MODE_INIT;
    set_LED(LED_A, FLASH_ON);
    clr_LED(LED_B);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);
    count_mode = COUNTING_OFF;

//
// main loop
//       
    FOREVER {
// 
// read pots - none at this time
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;
        
            WAIT_SWITCH_RELEASED(switch_B);
        }
//
//  check for exit
//
        if (switch_C == PRESSED) {            //  exit mode
            vehicle_stop();
            SOUND_EXIT_SELECTION;
            WAIT_SWITCH_RELEASED(switch_C);
            return 0;
        }  
//
//  run simple state machine to define operating modes
//  There are two states : MODE_INIT and MODE_RUNNING
//
//        if (state == MODE_INIT) {
//            if (switch_A == PRESSED) {           
//                state = MODE_RUNNING;             // go to RUN state    
//                WAIT_SWITCH_RELEASED(switch_A); 
//            } else {
//                continue;                         // back to begining of FOREVER loop
//            }
//        }
//        if (state == MODE_RUNNING) {
//            if (switch_A == PRESSED) {            // halt bump activity
//                state = MODE_INIT;
//                WAIT_SWITCH_RELEASED(switch_A);
//                continue;
//            }
//        }
//
// check for count START signal : clear timer, show cycling display and sound beeps
// 
        if ((count_mode == COUNTING_OFF) && (get_adc(FRONT_SENSOR_L) < SENSE_LOW)) {       // start count
            CLR_TIMER16;
            play_tune(&snd_beeps_1);
            display_string("_-^-_", 0);
            count_mode = COUNTING_ON;       
        }
//
// check for count STOP signal; read count and convert to x.y seconds value
//     
        if ((count_mode == COUNTING_ON) && (get_adc(FRONT_SENSOR_R) < SENSE_LOW)) {       // start count
            GET_TIMER16(t_count);
            count_mode = COUNTING_OFF;       
            stop_tune();
            //
            // convert count of 8mS units units of 1 second and units of 0.1 second
            //
            count_mS = t_count * 8;   
            count_seconds = count_mS / 1000;
            count_mS = count_mS - (count_seconds * 1000);
            count_100mS = count_mS / 100;
            count_mS = count_mS - (count_100mS * 100);
            if (count_mS >= 50 ) {                     // round to nearest 0.1 second
                count_100mS++;
            }
            //
            // print to display
            //
            sprintf(tempstring, " %u_%u SECS", count_seconds, count_100mS);
            display_string(tempstring, 0);
        }  
    }
}

//----------------------------------------------------------------------------
// run_lab_mode_1 : 
// ==============
//
// Description
//      xxxxx
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch B = 
//          switch C = exit
//          switch D = 
//
//      Active pots
//          pot 1 = 
//          pot 2 = 
//          pot 3 = 
//

uint8_t run_lab_mode_1(void) 
{
mode_state_t    state; 

    state = MODE_INIT;
    set_LED(LED_A, FLASH_ON);
    clr_LED(LED_B);
    set_LED(LED_B, FLASH_ON);
    clr_LED(LED_D);
//
// main loop
//       
    FOREVER {
// 
// read pots - 
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;            
            WAIT_SWITCH_RELEASED(switch_B);
        }
//
//  check for exit
//
        if (switch_C == PRESSED) {            //  exit mode
            SOUND_EXIT_SELECTION;
            WAIT_SWITCH_RELEASED(switch_C);
            return 0;
        }  
//
//  run simple state machine to define operating modes
//  There are two states : MODE_INIT and MODE_RUNNING
//
        if (state == MODE_INIT) {
            if (switch_A == PRESSED) {            //  go to RUN state              
                state = MODE_RUNNING;
                CLR_TIMER16;                      // reset timeout timer
                WAIT_SWITCH_RELEASED(switch_A); 
            } else {
                continue;                         // back to begining of FOREVER loop
            }
        }
        if (state == MODE_RUNNING) {
            if (switch_A == PRESSED) {            // halt bump activity
                state = MODE_INIT;
                vehicle_stop();
                WAIT_SWITCH_RELEASED(switch_A);
                continue;
            }
        }
//
//  zzzzzzz
//
     return 0;
    }
}



//----------------------------------------------------------------------------
// run_lab_mode_2 : 
// ==============
//
// Description
//      xxxxxxxx
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch B = no effect
//          switch C = exit
//          switch D = start/stop scanning operation
//
//      Active pots
//

uint8_t run_lab_mode_2(void) 
{
    run_sequence(program_a);
    return 0;
}

