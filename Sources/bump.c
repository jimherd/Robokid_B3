//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// bump.c : code to run bump modes
// ======
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd          14/02/09      
//----------------------------------------------------------------------------

#include "global.h"

//----------------------------------------------------------------------------
// run_bump_mode : run one of a set of bump activities
// =============
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch C = exit to main selection level
//          switch D = step through selections
//
uint8_t run_bump_mode(void) {

uint8_t       activity;

    B_MODE_LEDS;
    activity = FIRST_BUMP_MODE;
    show_dual_chars('b', ('0'+ activity), (A_TO_FLASH | 10));
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
            if (activity > LAST_BUMP_MODE) {
                activity = FIRST_BUMP_MODE;
            }
            show_dual_chars('b', ('0'+ activity), (A_TO_FLASH | 10));
        }
        if (switch_C == PRESSED) {            //  back to main 
            WAIT_SWITCH_RELEASED(switch_C);
            SOUND_EXIT_SELECTION;
            return 0;
        }        
        if (switch_A == PRESSED) {              
            set_LED(LED_A, FLASH_ON); 
            set_LED(LED_D, FLASH_ON);
            WAIT_SWITCH_RELEASED(switch_A); 
        } else {
            continue;       // back to checking switches
        }
//
// run a bump activity
// 
        show_dual_chars('b', ('0'+ activity), 0);
        push_LED_display();        
        switch (activity) {
            case LINE_BUMP_MODE :    
                run_line_bump_mode();
                break;
            case LINE_BUG_BUMP_MODE :     
                run_line_bug_bump_mode();
                break;
            case WALL_BUMP_MODE : 
                run_wall_bump_mode();
                break;                
            default :
                break;                    
        }
        pop_LED_display();
        show_dual_chars('b', ('0'+ activity), (A_TO_FLASH | 10));
        B_MODE_LEDS;           
    } 
}

//----------------------------------------------------------------------------
// run_wall_bump_mode : run bump mode with with detection of walls with switches
// ==================
//
// Notes
//
//      Active switches are 
//          switch A = go/halt
//          switch B = read POT_1, POT_2  and POT_3
//          switch C = exit mode
//
//      Active pots
//          pot 1 = selected speed (30% to 95%)
//          pot 2 = amount of reversing
//          pot 3 = amount of spin
//
uint8_t run_wall_bump_mode(void) {

uint8_t       ad_value, bump_L, bump_C, bump_R, bump, time_reverse, time_spin; 
mode_state_t  state;
int8_t        speed_differential;
uint16_t      time; 

    state = MODE_INIT;
    left_speed = DEFAULT_SPEED;
    right_speed = left_speed - pwm_differential + DIFFERENTIAL_NULL;
    time_reverse = DEFAULT_REVERSE_TIME;
    time_spin = DEFAULT_SPIN_TIME;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);

//
// main loop
//       
    FOREVER {
//
//  check for timeout if in RUNNING state
//
        if (state == MODE_RUNNING) {   
            GET_TIMER16(time);
            if (time > LINE_BUMP_TIME_OUT ) {
                state = MODE_INIT;
                vehicle_stop();
                continue;
                }
        }
// 
// read pots to set system characteristics
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;
        
            ad_value = get_adc(POT_1); 
            time_reverse = ((ad_value >> 5 ) & 0x07);   // convert to range 0 -> 7 (units of 0.05s)             

            ad_value = get_adc(POT_2);               
            time_spin = ((ad_value >> 5 ) & 0x07);      // convert to range 0 -> 7 (units of 0.05s)
            
            ad_value = ((get_adc(POT_3) >> 2) & 0x3F);
            speed_differential = (ad_value - 31); // convert to range -31% -> +31% 
            if (speed_differential > 0) {
                left_speed = DEFAULT_LINE_BUMP_SPEED;
                right_speed = DEFAULT_LINE_BUMP_SPEED - speed_differential;
            } else {
                speed_differential = -speed_differential;
                left_speed = DEFAULT_LINE_BUMP_SPEED - speed_differential; 
                right_speed = DEFAULT_LINE_BUMP_SPEED;
            }
            
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
// read bump sensors
//
        bump_L = get_adc(FRONT_SENSOR_L);           
        bump_C = get_adc(FRONT_SENSOR_C);           
        bump_R = get_adc(FRONT_SENSOR_R);   
//
// process bump sensor readings into digital values and combine into a single 
// 3-bit line value
//
        bump = 0b111;
        if (bump_L < (YES_BUMP + DEADBAND)){
            bump &= 0b011;
            vehicle_stop();
            beep(NOTE_C, 1);
        }
        if (bump_C < (YES_BUMP + DEADBAND)){
            bump &= 0b101;
            vehicle_stop();
            beep(NOTE_C, 2);
        }
        if (bump_R < (YES_BUMP + DEADBAND)){
            bump &= 0b110;
            vehicle_stop();
            beep(NOTE_C, 3);
        }
//
// now react to bump information. Deal with 8 possibilities.
//
        switch (bump) {
            case LCR : //  000 - L = yes , C = yes , R = yes => reverse + random spin
                vehicle_stop();
                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_reverse * 100);
                if (get_random_bit() == 0) {   // spin in a random direction                  
                    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                }else {
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                }
                DelayMs(time_spin * 100);                
                break;
            case LCx : //  001 - L = yes , C = yes , R =  no => reverse + spin right
                vehicle_stop();
                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_reverse * 100);
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_spin * 100);                
                break;
            case LxR : //  010 - L = yes , C =  no , R = yes => reverse + random spin
                vehicle_stop();
                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_reverse * 100);
                if (get_random_bit() == 0) {   // spin in a random direction                  
                    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                }else {
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                }
                DelayMs(time_spin * 100);              
                break;
            case Lxx : //  011 - L = yes , C =  no , R =  no => spin right
                vehicle_stop();
                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_OFF, 0);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_spin * 100);                
                break;
            case xCR : //  100 - L =  no , C = yes , R = yes => reverse + spin left
                vehicle_stop();
                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_reverse * 100);
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                DelayMs(time_spin * 100);                
                break;
            case xCx : //  101 - L =  no , C = yes , R =  no => reverse + spin
                vehicle_stop();
                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_reverse * 100);
                if (get_random_bit() == 0) {   // spin in a random direction                  
                    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                }else {
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                }
                DelayMs(time_spin * 100);              
                break;
            case xxR : //  110 - L =  no , C =  no , R = yes => reverse + spin
                vehicle_stop();
                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_OFF, 0);
                DelayMs(time_spin * 100);                
                break;
            case xxx : //  111 - L =  no , C =  no , R =  no => forward action
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);               
                break;
        }
    }
}

//----------------------------------------------------------------------------
// run_line_bump_mode : run bump mode with with detection of black tape 
// ==================
//
// Notes
//
//      Active switches are 
//          switch A = exit button
//          switch B = change setting by reading POT_1_IN, POT_2_IN  and POT_3_IN
//          switch C = exit mode
//
//      Active pots
//          pot 1 = amount of reversing
//          pot 2 = amount of spin
//          pot 1 = difference between wheel speeds
//
uint8_t run_line_bump_mode(void) {

uint8_t       ad_value, line_L, line_R, line, time_reverse, time_spin;
int8_t        speed_differential;
uint16_t      time; 
mode_state_t  state;

    state = MODE_INIT;
    left_speed = DEFAULT_LINE_BUMP_SPEED;
    right_speed = DEFAULT_LINE_BUMP_SPEED;
    time_reverse = DEFAULT_REVERSE_TIME;
    time_spin = DEFAULT_SPIN_TIME;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);
    CLR_TIMER16;
//
// main loop
//       
    FOREVER {
//
//  check for timeout if in RUNNING state
//
        if (state == MODE_RUNNING) {   
            GET_TIMER16(time);
            if (time > LINE_BUMP_TIME_OUT ) {
                state = MODE_INIT;
                vehicle_stop();
                continue;
                }
        }
// 
// read pots to set system characteristics
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;
        
            ad_value = get_adc(POT_1); 
            time_reverse = ((ad_value >> 5 ) & 0x07);   // convert to range 0->15 (units of 0.1s)
            time_reverse += 1;                          // ensure reverse time is greater than zero             
             
            ad_value = get_adc(POT_2);               
            time_spin = ((ad_value >> 5 ) & 0x07);      // convert to range 0->15 (units of 0.1s)
            
            ad_value = ((get_adc(POT_3) >> 2) & 0x3F);
            speed_differential = (ad_value - 31); // convert to range -31% -> +31% 
            if (speed_differential > 0) {
                left_speed = DEFAULT_LINE_BUMP_SPEED;
                right_speed = DEFAULT_LINE_BUMP_SPEED - speed_differential;
            } else {
                speed_differential = -speed_differential;
                left_speed = DEFAULT_LINE_BUMP_SPEED - speed_differential; 
                right_speed = DEFAULT_LINE_BUMP_SPEED;
            }
            
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
// read line sensors
//
        line_L = get_adc(LINE_SENSOR_L);   
        line_R = get_adc(LINE_SENSOR_R);           
//
// process line sensor readings into digital values and combine into a single 
// 2-bit line value and show on LEDS C and D.
//
        line = 0b00;
        if (line_L < (BLACK_WHITE_THRESHOLD)){
             line |= 0b10;
        } 
        if (line_R < (BLACK_WHITE_THRESHOLD)){
             line |= 0b01;
        }
//
// set LED_D on if line detected
//         
        if (line == 0b11){
            clr_LED(LED_D); 
        } else {
            set_LED(LED_D, FLASH_OFF); 
        }           
//
// process 4 possible options for 2 line sensors 
//
        switch (line) {
            case 0 : //  00 - line detected by both sensors :: reverse + random spin
                vehicle_stop();
//                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_reverse * 100);
                if (get_random_bit() == 0) {   // spin in a random direction                  
                    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                }else {
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                }
                DelayMs(time_spin * 100);     
                break;
            case 1 : //  01 - line detected by left sensor therefore turn right
                vehicle_stop();
//                SOUND_TAPE_BUMP;
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_reverse * 50);
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed); 
                DelayMs(time_spin * 100);          
                break;
            case 2 : //  10 - line detected by right sensor therfore turn left
                vehicle_stop();
//                SOUND_TAPE_BUMP; 
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                DelayMs(time_reverse * 100);                
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed); 
                DelayMs(time_spin * 100);           
                break;
            case 3 : //  11 - no line detected therfore drive straight forward
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);           
                break;
        } 
    }
}

//----------------------------------------------------------------------------
// run_line_bug_bump_mode : run random bump mode with with detection of black tape 
// ======================
//
// Notes
//
//      Active switches are 
//          switch A = exit button
//          switch B = change setting by reading POT_1_IN, POT_2_IN  and POT_3_IN
//          switch C = exit mode
//
//      Active pots
//          pot 1 = amount of reversing
//          pot 2 = amount of spin
//          pot 1 = difference between wheel speeds
//
uint8_t run_line_bug_bump_mode(void) {

uint8_t       ad_value, line_L, line_R, line, time_reverse, time_spin, time_stop, speed_value;
int8_t        speed_differential;
uint16_t      time; 
mode_state_t  state;

    state = MODE_INIT;
    left_speed = DEFAULT_LINE_BUMP_SPEED;
    right_speed = DEFAULT_LINE_BUMP_SPEED;
    time_reverse = DEFAULT_REVERSE_TIME;
    time_spin = DEFAULT_SPIN_TIME;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);
    CLR_TIMER16;
//
// main loop
//       
    FOREVER {
//
//  check for timeout if in RUNNING state
//
        if (state == MODE_RUNNING) {   
            GET_TIMER16(time);
            if (time > LINE_BUMP_TIME_OUT ) {
                state = MODE_INIT;
                vehicle_stop();
                continue;
                }
        }
// 
// read pots to set system characteristics
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;
        
            ad_value = get_adc(POT_1); 
            time_reverse = ((ad_value >> 4 ) & 0x0F);   // convert to range 0->15 (units of 0.1s)
            time_reverse += 1;                          // ensure reverse time is greater than zero             

            ad_value = get_adc(POT_2);               
            time_spin = ((ad_value >> 4 ) & 0x0F);      // convert to range 0->15 (units of 0.1s)
            
            ad_value = ((get_adc(POT_3) >> 2) & 0x3F);
            speed_differential = (ad_value - 31); // convert to range -31% -> +31% 
            if (speed_differential > 0) {
                left_speed = DEFAULT_LINE_BUMP_SPEED;
                right_speed = DEFAULT_LINE_BUMP_SPEED - speed_differential;
            } else {
                speed_differential = -speed_differential;
                left_speed = DEFAULT_LINE_BUMP_SPEED - speed_differential; 
                right_speed = DEFAULT_LINE_BUMP_SPEED;
            }
            
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
// read line sensors
//
        line_L = get_adc(LINE_SENSOR_L);   
        line_R = get_adc(LINE_SENSOR_R);           
//
// process line sensor readings into digital values and combine into a single 
// 2-bit line value and show on LEDS C and D.
//
        line = 0b00;
        if (line_L < (BLACK_WHITE_THRESHOLD)){
             line |= 0b10;
        } 
        if (line_R < (BLACK_WHITE_THRESHOLD)){
             line |= 0b01;
        }
//
// set LED_D on if line detected
//         
        if (line == 0b11){
            clr_LED(LED_D); 
        } else {
            set_LED(LED_D, FLASH_OFF); 
        }           
//
// process 4 possible options for 2 line sensors 
//
        switch (line) {
            case 0 : //  00 - line detected by both sensors :: reverse + random spin
            case 1 : //  01 - line detected by left sensor therefore turn right 
            case 2 : //  10 - line detected by right sensor therfore turn left                       
                
                vehicle_stop();
                SOUND_TAPE_BUMP;
                time_stop = (get_random_byte() & 0x0F);  // between 0 and 15 time units
                DelayMs(time_stop * 100);
                
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                
                time_reverse = (get_random_byte() & 0x07) + 3;  // between 3 and 11 time units
                DelayMs(time_reverse * 100);
                
                vehicle_stop();
                time_stop = (get_random_byte() & 0x0F);  // between 0 and 15 time units
                DelayMs(time_stop * 100);
                                
                if (get_random_bit() == 0) {   // spin in a random direction                  
                    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                }else {
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                }
                time_spin = (get_random_byte() & 0x07) + 1;  // between 1 and 8 time units
                DelayMs(time_spin * 100);
                
                vehicle_stop();
                time_stop = (get_random_byte() & 0x0F);  // between 0 and 15 time units
                DelayMs(time_stop * 100);
//
// set new wheel speed with a bit of randomness
//                
                speed_value = get_random_byte();
                if (speed_value < 85 ) {
                    left_speed = DEFAULT_LINE_BUMP_SPEED;
                    right_speed = DEFAULT_LINE_BUMP_SPEED;
                } else {
                    if (speed_value > 170 ) {
                    left_speed = DEFAULT_LINE_BUMP_SPEED - 20;
                    right_speed = DEFAULT_LINE_BUMP_SPEED;
                    } else {
                        left_speed = DEFAULT_LINE_BUMP_SPEED;
                        right_speed = DEFAULT_LINE_BUMP_SPEED - 20;
                    }
                }     
                break;
                
            case 3 : //  11 - no line detected therfore drive straight forward
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);           
                break;
        } 
    }
}

