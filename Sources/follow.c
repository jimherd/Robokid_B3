//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// follow.c : code to run follow modes
// ========
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd          14/02/09      
//----------------------------------------------------------------------------

#include "global.h"

//----------------------------------------------------------------------------
// run_follow_mode : run one of a set of follow activities
// ===============
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch C = exit to main slection level
//          switch D = step through selections
//
uint8_t run_follow_mode(void) {

uint8_t     activity;

    F_MODE_LEDS;
    activity = FIRST_FOLLOW_MODE;
    show_dual_chars('F', ('0'+ activity), (A_TO_FLASH | 10));
//
// main loop
//       
    FOREVER {
//
//  check and act on the switches
//
        if (switch_D == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_D);
            SOUND_NEXT_SELECTION;
            activity++;
            if (activity > LAST_FOLLOW_MODE) {
                activity = FIRST_FOLLOW_MODE;
            }
            show_dual_chars('F', ('0'+ activity), (A_TO_FLASH | 10));
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
// run a follow activity
// 
        show_dual_chars('F', ('0'+ activity), 0); 
        push_LED_display();      
        switch (activity) {
                case LINE_FOLLOW_MODE :                          // in progress
                    run_follow_line_mode();
                    break;
                case LIGHT_FOLLOW_MODE :                         // in progress
                    run_follow_light_mode();
                    break;
                default :
                    break;
        }
        pop_LED_display();
        show_dual_chars('F', ('0'+ activity), (A_TO_FLASH | 10));
        F_MODE_LEDS;            
    } 
}


//----------------------------------------------------------------------------
// run_follow_line_mode : run vehicle mode with 2 line follow sensors
// ====================
//
// Description
//      Vehicle uses the two floor sensors that straddle a 19mm black tape line.
//      These sensors are measured and converted to disgital values.  The sensors give a value between o
//      and 255
//                0 = BLACK (complete IR absorption)   
//              255 = WHITE (complete IR reflection)
//      The values never reach these extremes due to non-ideal absoption/reflection
//      characteristics of floor and tape materials.
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch B = change setting by reading POT_1, POT_2 and POT_3
//          switch C = exit mode
//
//      Active pots
//          POT_1 : speed setting   0->60%
//          POT_2 : right wheel slow down factor 0->100% of speed
//          POT_3 : sample rate  10mS->500mS (units of 10mS)
//

uint8_t run_follow_line_mode(void) {

uint8_t       line_L, line_R, ad_value, drag_speed;
uint16_t      sample_time, temp16;
mode_state_t  state;

    state = MODE_INIT;
    left_speed = DEFAULT_LINE_FOLLOW_SPEED;
    right_speed = left_speed - pwm_differential + DIFFERENTIAL_NULL;
    drag_speed = 0;
    sample_time = DEFAULT_SAMPLE_TIME;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);    
//
// main loop
//       
    FOREVER {
//
//  run simple state machine to define operating modes
//  There are two states : MODE_INIT and MODE_RUNNING
//
// read pots to set system characteristics
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;  

            ad_value = get_adc(POT_1);
            temp16 =  ((ad_value >> 2) & 0x3F);                   // convert to 0->63
            temp16 = (temp16 * DEFAULT_LINE_FOLLOW_SPEED) / 0x3F; // convert to 0-> DEFAULT_LINE_FOLLOW_SPEED
            temp16 = temp16 + 20;                                 // convert to 20 -> DEFAULT_LINE_FOLLOW_SPEED + 20
            left_speed = (uint8_t)temp16;
            
            ad_value = get_adc(POT_2);
            temp16 =  ((ad_value >> 3) & 0x1F);                   // convert to 0->31
            temp16 = (temp16 * left_speed) / 0x1F;                // convert to 0->left_speed
            drag_speed = left_speed - (uint8_t)temp16;            // convert to left_speed->0

            ad_value = get_adc(POT_3);
            temp16 =  ((ad_value >> 3) & 0x1F);                   // convert to 0->31
            temp16 = (temp16 * 20) / 0x1F;                        // convert to 0->50
            sample_time = (uint8_t)temp16 * 10;                   // convert to 0->500mS
            if (sample_time == 0) {              // ensure that sample time is not 0
                sample_time = 10;
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
        line_L = READ_TAPE_SENSOR(LINE_SENSOR_L); 
        line_R = READ_TAPE_SENSOR(LINE_SENSOR_R); 
//
// process 4 possible options for 2 line sensors 
//
// tape detected by both sensors
//      -> go into spin mode
//        
        if ((line_L == BLACK) && (line_R == BLACK)) {
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
            set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);          
        }
//
// tape detected by left sensor
//      -> stop left motor
//
        if ((line_L == BLACK) && (line_R == WHITE)) {
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, drag_speed);
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);     
        }
//
// tape detected by right sensor
//      -> stop right motor
//
        if ((line_L == WHITE) && (line_R == BLACK)) {
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, drag_speed);     
        }
//
// no line detected 
//      -> continue to drive forward
//
        if ((line_L == WHITE) && (line_R == WHITE)) {
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);                    
        }
        DelayMs(sample_time);
    }  // end of FOREVER loop
}

//----------------------------------------------------------------------------
// run_follow_light_mode : 
// =====================
//
// Description
//      Vehicle uses two LDR sensors to detect incident light.  As the light
//      intensity increases, the value read from the sensor decreases.
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch B = change setting by reading POT_1, POT_2 and POT_3
//          switch C = exit mode
//
//      Active pots
//          POT_1 : ambient light setting   0->63
//          POT_2 : drag speed setting   (if switch B is pressed for less than 2 seconds)
//          POT_2 : deadband 0->15       (if switch B is pressed for more than 2 seconds)
//          POT_3 : sample rate   -  0->200mS
//
uint8_t run_follow_light_mode(void) {

uint8_t       ad_value, light_L, light_R, ambient_L, ambient_R, ambient_diff, larger_reading, light_diff;
uint8_t       light_deadband, light_average, sample_time, drag_speed, ambient;
int16_t       temp16, ticks;
mode_state_t  state;

    state = MODE_INIT;
    left_speed = SLOW_SPEED;
    right_speed = SLOW_SPEED;
    drag_speed = 0;
    sample_time = DEFAULT_SAMPLE_TIME;
    
    light_deadband = DEFAULT_DEADBAND;
    ambient = DEFAULT_AMBIENT;

    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);
//
// read sensors to get ambient light values and comput the difference
//
    ambient_L = get_adc(FRONT_SENSOR_L);  
    ambient_R = get_adc(FRONT_SENSOR_R);
    if (ambient_L > ambient_R) {
        ambient_diff = ambient_L - ambient_R;
    } else {
        ambient_diff = ambient_R - ambient_L;
    }
//
// main loop
//       
    FOREVER {
//
// read pots to set system characteristics
//    
        if (switch_B == PRESSED) {
            CLR_TIMER16;
            SOUND_READ_POTS;
            WAIT_SWITCH_RELEASED(switch_B);     // wait until button returns to quiescent state 
            GET_TIMER16(ticks);                 // read 16-bit 8mS tick counter
            
            ad_value = get_adc(POT_1);                     
            if (ticks > (2 * TICKS_IN_ONE_SECOND)) {          // button press time > 2 seconds
                light_deadband =  ((ad_value >> 4) & 0x0F);       // convert to 0->15 
            } else {
                ambient =  ((ad_value >> 2) & 0x3F);              // convert to 0->63 
            }            
            ad_value = get_adc(POT_2);
            temp16 =  ((ad_value >> 3) & 0x1F);                   // convert to 0->31
            temp16 = (temp16 * left_speed) / 0x1F;                // convert to 0->left_speed
            drag_speed = left_speed - (uint8_t)temp16;            // convert to left_speed->0

            ad_value = get_adc(POT_3);
            temp16 =  ((ad_value >> 3) & 0x1F);                   // convert to 0->31
            temp16 = (temp16 * 20) / 0x1F;                        // convert to 0->20
            sample_time = (uint8_t)temp16 * 10;                   // convert to 0->200mS
            if (sample_time == 0) {              // ensure that sample time is not 0
                sample_time = 10;
            }
            //
            // recalculate ambient
            //
            ambient_L = get_adc(FRONT_SENSOR_L);  
            ambient_R = get_adc(FRONT_SENSOR_R);
            if (ambient_L > ambient_R) {
                ambient_diff = ambient_L - ambient_R;
            } else {
                ambient_diff = ambient_R - ambient_L;
            }
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
// read light sensors and correct for ambient.  Add 20 to keep value away from zero.
//
        light_L = (ambient_L + 20) - (get_adc(FRONT_SENSOR_L));  
        light_R = (ambient_R + 20) - (get_adc(FRONT_SENSOR_R));
        light_average = (light_R / 2) + (light_L /2); 
        if (light_L > light_R) {
            light_diff = light_L - light_R;
            larger_reading = FRONT_SENSOR_L;
        } else {
            light_diff = light_R - light_L;
            larger_reading = FRONT_SENSOR_R;
        }
//
// check and act on different light values.
//
// 1. If average light level is too low then stop
// 2. If within deadband move forward
//
        if (light_average < ambient) {
            vehicle_stop();
        } else {
            if (light_diff > light_deadband) {
                if (larger_reading == FRONT_SENSOR_L) {
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, drag_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                } else {
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, drag_speed);
                } 
            } else {
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed); 
            } 
        }
        DelayMs(sample_time);            
    }        // end of FOREVER loop
}
