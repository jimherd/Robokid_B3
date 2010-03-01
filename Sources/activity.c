//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// activity.c : general activity routines
// ==========
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd    12/02/09      iitial design
//----------------------------------------------------------------------------

#include "global.h"

//----------------------------------------------------------------------------
// run_activity_mode : run one of a set of single activities
// ================
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch C = exit to main slection level
//          switch D = step through selections
//
uint8_t run_activity_mode(void) {

uint8_t     activity;
uint16_t    forward_time;

    forward_time = 2000;
    A_MODE_LEDS;
    activity = FIRST_ACTIVITY_MODE;
    show_dual_chars('A', ('0'+ activity), (A_TO_FLASH | 10));
//
// main loop
//       
    FOREVER {
//
//  run simple state machine to define operating modes
//  There are two states : MODE_INIT and MODE_RUNNING
//
//
//  check and act on the switches
//
        if (switch_D == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_D);
            activity++;
            SOUND_NEXT_SELECTION;
            if (activity > LAST_ACTIVITY_MODE) {
                activity = FIRST_ACTIVITY_MODE;
            }
            show_dual_chars('A', ('0'+ activity), (A_TO_FLASH | 10));
        }
        if (switch_C == PRESSED) {            //  back to main 
            WAIT_SWITCH_RELEASED(switch_C);
            SOUND_EXIT_SELECTION;
            return 0;
        }
        if (switch_A == PRESSED) {            //  go to RUN state              
            set_LED(LED_A, FLASH_ON); 
            set_LED(LED_D, FLASH_ON);
            WAIT_SWITCH_RELEASED(switch_A); 
        } else {
            continue;
        }
//
// run an activity
// 
        show_dual_chars('A', ('0'+ activity), 0);
        push_LED_display();          
        switch (activity) {
            case RUN_FORWARD :
                do_move(FORWARD);
                break;
            case RUN_BACKWARD :
                do_move(BACKWARD);                             
                break;
            case RUN_SPIN_RIGHT :
                do_move(SPIN_RIGHT);
                break;                                                                                  
            case RUN_SPIN_LEFT :
                do_move(SPIN_LEFT);
                break;      
            case RUN_TEST :
                run_test();
                break;
            case DEMO_MODE :                                 // to be done
                play_sequence();
                break;                                                                                          
             default :
                break;
        }
        pop_LED_display();
        show_dual_chars('A', ('0'+ activity), (A_TO_FLASH | 10));
        A_MODE_LEDS;      
    } 
}


//----------------------------------------------------------------------------
// do_move : implement a simple robot move
// =======
//
// Notes
//
//      Active switches are 
//          switch A = go button
//          switch B = change setting by reading POT_1_IN, POT_2_IN and POT_3_IN
//          switch C = exit mode
//
//      Active pots
//          pot 1 = selected speed (30% to 95%)
//          pot 2 = differential between motors
//          pot 3 = time of travel :: 1 sec to 7.2 sec
//

#define   DEFAULT_FORWARD_TIME     2000

uint8_t do_move(uint8_t direction) {

uint16_t   forward_time, temp16;
uint8_t    ad_value, speed;
int8_t     speed_differential;

    set_LED(LED_A, FLASH_ON); 
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON); 
    clr_LED(LED_D);    
    forward_time = DEFAULT_FORWARD_TIME;
    left_speed = DEFAULT_SPEED;
    right_speed = DEFAULT_SPEED;
    speed = DEFAULT_SPEED;
    speed_differential = 0;

    FOREVER {
//
// run for a set period of time
//            
        if (switch_A == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_A);
            DelayMs(1000);
            play_tune(&snd_beeps_1);
            
            switch (direction) {
                case FORWARD :
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                    break; 
                case BACKWARD :
                    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed); 
                    break; 
                case SPIN_RIGHT :
                    set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed); 
                    break; 
                case SPIN_LEFT :
                    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed); 
                    break; 
            }

            DelayMs(forward_time);
                          
            vehicle_stop();
            stop_tune();                  
        }
//
// read pots to set system speed, differential bias, and run time
//        
        if (switch_B == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_B);
            SOUND_READ_POTS;
            vehicle_stop();
            
            ad_value = get_adc(POT_1);
            speed = motor_speeds[(ad_value >> 4) & 0x0F];   // get speed setting

            ad_value = ((get_adc(POT_2) >> 3) & 0x1F);      // convert to 0->31
            temp16 = (ad_value * 26)/31;                    // convert from 0->31 to 0->26         
            speed_differential = (temp16 - 13);             // convert to range -13% -> +13% 
            if (speed_differential > 0) {
                left_speed = speed;
                right_speed = speed - speed_differential;
            } else {
                speed_differential = -speed_differential;
                left_speed = speed - speed_differential; 
                right_speed = speed;
            }
          
            ad_value = ((get_adc(POT_3)) >> 2) & 0x3F;      // convert to range 0->65
            forward_time = (ad_value + 10)  * 100;          // convert to range 1 sec to 7.2 secs 
        }
//
//  check for exit
//
        if (switch_C == PRESSED) {            //  back to main 
            vehicle_stop();
            straight_line_speed = DEFAULT_SPEED;
            SOUND_EXIT_SELECTION;
            WAIT_SWITCH_RELEASED(switch_C);
            return 0;
        }  
    }
}

//----------------------------------------------------------------------------
// run_test : run basic system tests
// ========
//
// Notes
//
//  This test routine is used to verify that the robots motors have been correctly wired.
//  It can also verify that the line and wheel sensors are correctly working.
//
//  1. Robot is carefully placed on an A4 sheet of paper which has a number of black target areas
//  2. The robot is then run in a special test mode.
//  3. The possible reults are as follows
//
//      a. runs forward and stops at front target
//      b. runs backward and stops at back target
//      c. spins about a point between the two motors (left or right)
//      d. arcs to the left or right 
//      e. does not move
//
//  Table of results from test
//
// Code  Time out  L sensor  R sensor  L count  R count          Result
// ====  ========  ========  ========  =======  =======          ======
//  r0      -         X    or   X        low      low      Robot OK
//  r1      X         -         -         0        0       both motors not running
//  r2      X         -         -        >0       >0       line sensors faulty
//  r3      -         X    or   X       high     high      both motors need to be reversed
//  r4      -         X         -      medium   medium     left motor needs to be reversed
//  r5      -         -         X      medium   medium     right motor needs to be reversed
//  r6      -         X         -         0       >0       left motor not running
//  r7      -         -         X        >0        0       right motor not running
//
//      Active switches are 
//          switch A = go button
//          switch B = change setting by reading POT_1_IN, POT_2_IN and POT_3_IN
//          switch C = exit mode
//
//      Active pots
//          pot 1 = selected speed (30% to 95%)
//          pot 2 = differential between motors
//
uint8_t run_test(void) {

uint8_t     line_L, line_R, test_result, ad_value;
uint16_t    left_count, right_count, start_time, now_time;

    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_A, FLASH_ON);
    clr_LED(LED_B);    
    test_result = 0;
//
// main loop
//       
    FOREVER {
//
// read pots to set system speed, differential bias, and run time
//        
        if (switch_B == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_B);
            SOUND_READ_POTS;
            vehicle_stop();
            ad_value = get_adc(POT_1);
            straight_line_speed = motor_speeds[(ad_value >> 4) & 0x0F];   // get speed setting
            ad_value = get_adc(POT_2);
            pwm_differential = speed_delta[(ad_value >> 4) & 0x0F];;
            left_speed = straight_line_speed;
            right_speed = straight_line_speed - pwm_differential + DIFFERENTIAL_NULL;
        }
//
//  check for exit
//
        if (switch_C == PRESSED) {            //  back to main 
            vehicle_stop();
            straight_line_speed = DEFAULT_SPEED;
            SOUND_EXIT_SELECTION;
            WAIT_SWITCH_RELEASED(switch_C);
            return 0;
        }
//
// Switch A to run the test.
//          
        if (switch_A == PRESSED) {
            clr_LED(LED_A);
            clr_LED(LED_B);
            play_tune(&snd_beeps_1);
            WAIT_SWITCH_RELEASED(switch_A);
//
// enable left and right wheel counters and initialise count
//
            left_count = 0;
            right_count = 0;
            enable_wheel_count();           
//
// get start time for for time-out calculation
//
            start_time = tick_count_16;            
//
// start both motors
//            
            DelayMs(1000);  
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
//
// stop motors on the following conditions
//  a. either line sensor detects black
//  b. time-out occurs
//
            now_time = tick_count_16;
            if ((now_time - start_time) > MOTOR_TEST_TIME_OUT) {
                set_motor(LEFT_MOTOR, MOTOR_BRAKE, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BRAKE, right_speed);
                sys_error = TIME_OUT; 
                break;
            }
//
// read line sensors
//
            line_L = get_adc(LINE_SENSOR_L);  
            line_R = get_adc(LINE_SENSOR_R);
//
// check for line detection
//
            if ((line_L > BLACK_WHITE_THRESHOLD) || (line_L > BLACK_WHITE_THRESHOLD)){
                set_motor(LEFT_MOTOR, MOTOR_BRAKE, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BRAKE, right_speed); 
                break;
            }                     
        }   
    }  // end of FOREVER loop
//
// using data from the line and wheel sensors we can detect possible motor wiring errors.
//
// convert line sensor analogue reading to two state values.
//
    line_L = READ_TAPE_SENSOR(LINE_SENSOR_L); 
    line_R = READ_TAPE_SENSOR(LINE_SENSOR_R);
//
// get wheel counts
//    
    left_count =  left_wheel_count;
    right_count = right_wheel_count;       
//
// option 1 : check for timeout
//
    if (sys_error == TIME_OUT) {
        return TIME_OUT;
    }
//
// option 2 : correct operation
//
//    if (left_count >     
//    return 0;
}

