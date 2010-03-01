//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// drawing.c : code to run drawing modes
// =========
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd          31/08/09      
//----------------------------------------------------------------------------

#include "global.h"

//----------------------------------------------------------------------------
// run_drawing_mode : run one of a set of drawing activities
// ================
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch C = exit to main slection level
//          switch D = step through selections
//
uint8_t run_drawing_mode(void) 
{
uint8_t   activity;

    D_MODE_LEDS;
    activity = FIRST_DRAWING_MODE;
    show_dual_chars('d', ('0'+ activity), (A_TO_FLASH | 10));
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
            show_dual_chars('d', ('0'+ activity), (A_TO_FLASH | 10));
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
        show_dual_chars('d', ('0'+ activity), 0);
        push_LED_display();       
        switch (activity) {
                case DRAWING_MODE_0 :                          // in progress
                    run_drawing_mode_0();
                    break;
                case DRAWING_MODE_1 :                          // in progress
                    run_drawing_mode_1();
                    break;
                case DRAWING_MODE_2 :                          // in progress
                    run_drawing_mode_2();
                    break;                                        
                default :
                    break;
        }
        show_dual_chars('d', ('0'+ activity), (A_TO_FLASH | 10));
        pop_LED_display();       
    } 
}

//----------------------------------------------------------------------------
// run_drawing_mode_0 : draw a spiral pattern
// ==================
//
// Description
//      Draw a spiral pattern.  
//
// Notes
//
//      Active switches are 
//          switch A = run spiral pattern
//          switch B = read POTs
//          switch C = exit 
//          switch D = ------
//
//      Active pots
//          pot 1 = spiral update time
//          pot 2 = 
//          pot 3 = 
//

uint8_t run_drawing_mode_0(void) 
{
uint8_t       ad_value, spiral_mode, i; 
mode_state_t  state;
uint16_t      time, spiral_update_time; 

    state = MODE_INIT;
    spiral_update_time = DEFAULT_SPIRAL_UPDATE_TIME;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    clr_LED(LED_C);
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
            if (time > DRAWING_MODE_0_TIME_OUT ) {
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
            spiral_update_time = ((uint16_t)ad_value * 3) + 50;;   // convert to range 50 -> 1000 (units of mS)             
            
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
// randomly decide on left or right spiral
//        
        if (get_random_bit() == 1) {
            spiral_mode = LEFT_SPIRAL;
             set_motor(LEFT_MOTOR, MOTOR_BACKWARD, MAX_SPIRAL_SPEED);
             set_motor(RIGHT_MOTOR, MOTOR_FORWARD, MAX_SPIRAL_SPEED);        
        } else {
            spiral_mode = RIGHT_SPIRAL;
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, MAX_SPIRAL_SPEED);
            set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, MAX_SPIRAL_SPEED);
        }
//
// run spiral code
//
        for (i = MAX_SPIRAL_SPEED ; i > STOP_SPEED ; i--) {
            if (spiral_mode == LEFT_SPIRAL) {
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, i);
            } else {
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, i);
            }
            DelayMs(spiral_update_time);
            if (get_adc(FRONT_SENSOR_C) < SENSE_LOW ) {       // check for bump
                vehicle_stop ();
                return 0;
            }
        }        
        for (i = STOP_SPEED ; i <=MAX_SPIRAL_SPEED ; i++) {
            if (spiral_mode == LEFT_SPIRAL) {
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, i);
            } else {
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, i);
            }
            DelayMs(spiral_update_time);
            if (get_adc(FRONT_SENSOR_C) < SENSE_LOW ) {        // check for bump
                vehicle_stop ();
                return 0;
            } 
        }
        vehicle_stop ();
        return 0;
    }
}

//----------------------------------------------------------------------------
// run_drawing_mode_1 : generate spirograph pattern
// ==================
//
// Description
//      Produces flower-like spirograh patterns.
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch B = read POTs
//          switch C = exit
//          switch D = 
//
//      Active pots
//          pot 1 = size of pattern
//          pot 2 = angle of turn at the points
//          pot 3 = speed differential
//

#define   DRAWING_MODE_1_TIME_OUT      (30 * TICKS_IN_ONE_SECOND) 
#define   NOS_PATTTERN_LINES           20
#define   SPIROGRAPH_SPEED             60
#define   DEFAULT_LINE_DRAW_TIME       15
#define   DEFAULT_TURN_TIME            15

uint8_t run_drawing_mode_1(void) 
{
uint8_t         ad_value, line_draw_time, turn_time, i;
int8_t          speed_differential;
mode_state_t    state; 

    state = MODE_INIT;
    line_draw_time = DEFAULT_LINE_DRAW_TIME;
    turn_time = DEFAULT_TURN_TIME;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    clr_LED(LED_D);

//
// main loop
//       
    FOREVER {
// 
// read pots to set system characteristics
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;
        
            ad_value = get_adc(POT_1); 
            line_draw_time = ((ad_value >> 4 ) & 0x0F) + 15;   // convert to range 15 -> 31 (units of 0.05s)             

            ad_value = get_adc(POT_2);               
            turn_time = ((ad_value >> 4 ) & 0x07) + 15;       // convert to range 15 -> 31 (units of 0.05s)
            
            ad_value = ((get_adc(POT_3) >> 2) & 0x3F);
            speed_differential = (ad_value - 31);        // convert to range -31% -> +31% 
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
//  produce pattern as sequence of line draws and turns
//
    for (i = 0; i <= NOS_PATTTERN_LINES ; i++ ) {
        set_motor(LEFT_MOTOR, MOTOR_FORWARD, SPIROGRAPH_SPEED);
        set_motor(RIGHT_MOTOR, MOTOR_FORWARD, SPIROGRAPH_SPEED);
        DelayMs(line_draw_time * 50);
        vehicle_stop();
        DelayMs(10);
        set_motor(LEFT_MOTOR, MOTOR_FORWARD, SPIROGRAPH_SPEED);
        set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, SPIROGRAPH_SPEED);
        DelayMs(turn_time * 25);
        vehicle_stop();
        DelayMs(10); 
    }
     return 0;
    }
}

//----------------------------------------------------------------------------
// run_drawing_mode_2 : 
// ==================
//
// Description
//      xxxxxxxxxxxxx
//
// Notes
//
//      Active switches are 
//          switch A = 
//          switch B = 
//          switch C = 
//          switch D = 
//
//      Active pots
//

uint8_t run_drawing_mode_2(void) 
{
    return 0;
}

