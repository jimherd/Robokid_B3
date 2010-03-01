//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// joystick.c : joystick activities
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
// run_joystick_mode : run one of a set of joystick activities
// =================
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch C = exit to main slection level
//          switch D = step through selections
//
uint8_t run_joystick_mode(void) {

uint8_t    activity;

    J_MODE_LEDS;
    activity = FIRST_JOYSTICK_MODE;
    show_dual_chars('j', ('0'+ activity), (A_TO_FLASH | 10));
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
            if (activity > LAST_JOYSTICK_MODE) {
                activity = FIRST_JOYSTICK_MODE;
            }
            show_dual_chars('j', ('0'+ activity), (A_TO_FLASH | 10));
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
// run a joystick activity
// 
        show_dual_chars('j', ('0'+ activity), 0);
        push_LED_display();       
        switch (activity) {
                case JOYSTICK_MODE_1 :                           // done
                    run_joystick_mode_1();
                    break;
                case JOYSTICK_MODE_2 :                           // done
                    run_joystick_mode_2();
                    break;                         
                case JOYSTICK_MODE_3 :                           // done
                    run_joystick_mode_3();
                    break;
                default :
                    break;
        }
        pop_LED_display();
        show_dual_chars('j', ('0'+ activity), (A_TO_FLASH | 10));
        J_MODE_LEDS;      
    } 
}


//----------------------------------------------------------------------------
// run_joystick_mode_1 : run vehicle mode with external simple joystick
// ===================
//
// Notes
//      Joysticks switches operate as follows
//          left joystick switch  = drive left motor - forward/off/backward
//          right joystick switch = drive right motor  - forward/off/backward
//
//      Active switches are 
//          switch A = exit button
//          switch B = change speed by reading POT_1_IN
//          switch C = exit to main slection level
//
//      Active pots
//          pot 1 = selected speed (30% to 95%)
//          pot 2 = differential between motors
//
void run_joystick_mode_1(void) {

uint8_t     ad_value;

    left_speed = DEFAULT_SPEED;
    right_speed = left_speed - pwm_differential + DIFFERENTIAL_NULL;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);    
//
// main loop
//    
    FOREVER {
//
//  hold command
//
        if (switch_A == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_A);
            push_LED_display();
            set_LED(LED_A, FLASH_ON);
            vehicle_stop();
            SOUND_NEXT_SELECTION;
            WAIT_SWITCH_PRESSED(switch_A);
            WAIT_SWITCH_RELEASED(switch_A);
            pop_LED_display();
        }
// 
// read pot to set system speed
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;
            ad_value = get_adc(POT_1);
            straight_line_speed = motor_speeds[(ad_value >> 4) & 0x0F];   // get speed setting
            ad_value = get_adc(POT_2);
            pwm_differential = speed_delta[(ad_value >> 4) & 0x0F];;
            left_speed = straight_line_speed;
            right_speed = straight_line_speed - pwm_differential + DIFFERENTIAL_NULL;
            WAIT_SWITCH_RELEASED(switch_B);
        }
//
//  check for exit
//
        if (switch_C == PRESSED) {            //  back to main 
            vehicle_stop();
            straight_line_speed = DEFAULT_SPEED;
            SOUND_EXIT_SELECTION;
            WAIT_SWITCH_RELEASED(switch_C);
            return;
        }  
//
// read and process left input switch
//
        ad_value = get_adc(PAD_SWL);
        if (ad_value < (BACKWARD_VALUE + DEADBAND)) {    
            set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);     // backward
        } else if (ad_value > (STOP_VALUE - DEADBAND)) {
            set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);                 // stop
        } else {                                 
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);      // forward
        }   
//
// read and process right input switch
//
        ad_value = get_adc(PAD_SWR);
        if (ad_value < (BACKWARD_VALUE + DEADBAND)) {    
            set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);   // backward              
        } else if (ad_value > (STOP_VALUE - DEADBAND)) {        
            set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);                // stop
        } else {                                 
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);    // forward
        } 
    }  /* end of infinite loop */
}

//----------------------------------------------------------------------------
// run_joystick_mode_2 : run cornering experiment mode
// ===================
//
// Notes
//
//      Joysticks switches operate as follows
//          left joystick switch  = drive left motor - off/slow_forward/fast_forward
//          right joystick switch = drive right motor  - off/slow_forward/fast_forward
//      Active switches are 
//          switch A = exit button
//          switch B = change setting by reading POT_1_IN, POT_2_IN  and POT_3_IN
//          switch C = exit mode
//
//      Active pots
//          pot 1 = selected speed (30% to 95%)
//          pot 2 = amount of reversing
//          pot 3 = amount of spin
//
void run_joystick_mode_2(void) {

uint8_t     ad_value;

    left_speed = DEFAULT_SPEED;
    right_speed = left_speed - pwm_differential + DIFFERENTIAL_NULL;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);  
// main loop
//       
    FOREVER {
//
//  hold command
//
        if (switch_A == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_A);
            push_LED_display();
            set_LED(LED_A, FLASH_ON);
            vehicle_stop();
            SOUND_NEXT_SELECTION;
            WAIT_SWITCH_PRESSED(switch_A);
            WAIT_SWITCH_RELEASED(switch_A);
            pop_LED_display();
        }
// 
// read pots to set system speed if required
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;
            ad_value = get_adc(POT_1);        
            straight_line_speed = motor_speeds[(ad_value >> 4) & 0x0F];   // get speed setting
            ad_value = get_adc(POT_2);   
            pwm_differential = speed_delta[(ad_value >> 4) & 0x0F];;
            left_speed = straight_line_speed;
            right_speed = straight_line_speed - pwm_differential + DIFFERENTIAL_NULL;
            WAIT_SWITCH_RELEASED(switch_B);
        }
//
//  check for exit
//
        if (switch_C == PRESSED) {            //  back to main 
            vehicle_stop();
            straight_line_speed = DEFAULT_SPEED;
            SOUND_EXIT_SELECTION;
            WAIT_SWITCH_RELEASED(switch_C);
            return;
        }  
//
// read and process left input switch
//
        ad_value = get_adc(PAD_SWL);   
        if (ad_value < (CORNER_MODE_STOP_VALUE + DEADBAND)) {    
            set_motor(LEFT_MOTOR, MOTOR_OFF, 0);                              // stop
        } else if (ad_value > (CORNER_MODE_HALF_SPEED_VALUE - DEADBAND)) {
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, (left_speed - 20));          // half speed
        } else {
            set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);                 // full speed
        }   
//
// read and process right input switch
//
        ad_value = get_adc(PAD_SWR);   
        if (ad_value < (CORNER_MODE_STOP_VALUE + DEADBAND)) {    
            set_motor(RIGHT_MOTOR, MOTOR_OFF, 0);                             // stop
        } else if (ad_value > (CORNER_MODE_HALF_SPEED_VALUE - DEADBAND)) {
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, (right_speed - 20));        // half speed      
        } else {
            set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);               // full speed
        } 
    }
}


//----------------------------------------------------------------------------
// run_joystick_mode_3 : run vehicle mode with external simple joystick
// ===================
//
// Notes
//      Joysticks switches operate as follows
//          left joystick switch  = forward/backward drive
//          right joystick switch = left/right drive
//
//      Active switches are 
//          switch A = halt/restart button
//          switch B = change speed by POT_1 and differential setting with POT_2
//          switch C = exit button
//
//      Active pots
//          pot 1 = selected speed (30% to 95%)
//          pot 2 = differential adjustment
//
void run_joystick_mode_3(void) {

uint8_t     ad_value_L, ad_value_R, ad_value, fb_mode, lr_mode;
uint8_t     joystick_mode, last_joystick_mode;

    left_speed = DEFAULT_SPEED;
    right_speed = left_speed - pwm_differential + DIFFERENTIAL_NULL;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    set_LED(LED_C, FLASH_ON);
    clr_LED(LED_D);     
    last_joystick_mode = 5;
//
// main loop
//       
    FOREVER {
//
//  hold command
//
        if (switch_A == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_A);
            push_LED_display();
            set_LED(LED_A, FLASH_ON);
            vehicle_stop();
            SOUND_NEXT_SELECTION;
            WAIT_SWITCH_PRESSED(switch_A);
            WAIT_SWITCH_RELEASED(switch_A);
            pop_LED_display();
        }
// 
// read pots to set system speed and differential bias between the motors
//
        if (switch_B == PRESSED) {
            SOUND_READ_POTS;
            ad_value = get_adc(POT_1);
            straight_line_speed = motor_speeds[(ad_value >> 4) & 0x0F];   // get speed setting
            ad_value = get_adc(POT_2);
            pwm_differential = speed_delta[(ad_value >> 4) & 0x0F];;
            left_speed = straight_line_speed;
            right_speed = straight_line_speed - pwm_differential + DIFFERENTIAL_NULL;
            WAIT_SWITCH_RELEASED(switch_B);
        }
//
//  check for exit
//
        if (switch_C == PRESSED) {            //  back to main 
            vehicle_stop();
            straight_line_speed = DEFAULT_SPEED;
            SOUND_EXIT_SELECTION;
            WAIT_SWITCH_RELEASED(switch_C);
            return;
        }        
//
// read joystick values
//
        ad_value_L = get_adc(PAD_SWL);
        ad_value_R = get_adc(PAD_SWR);        
//
//  process joystick values
//                
        if (ad_value_R < (JOYSTICK_BACKWARD_VALUE + DEADBAND)) {
            fb_mode = 2;        // backward
        } else if (ad_value_R > (JOYSTICK_STOP_VALUE - DEADBAND)) {
            fb_mode = 1;        // off
        } else {
            fb_mode = 0;        // forward
        }
        if (ad_value_L < (JOYSTICK_RIGHT_VALUE + DEADBAND)) {
            lr_mode = 2;        // right
        } else if (ad_value_L > (JOYSTICK_STOP_VALUE - DEADBAND)) {
            lr_mode = 1;        // off
        } else {
            lr_mode = 0;        // left
        } 
//
// only change motors if joystick has changed
//
        joystick_mode = (lr_mode + (fb_mode << 2)) & 0x0F;
        if (joystick_mode == last_joystick_mode) {
            continue;                               // skip motor setting code
        }
        last_joystick_mode = joystick_mode;
        set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
        set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);      
//
//  Now convert joystick values into motor commands
//
        switch (joystick_mode) {
            case 0 :  // veer to right
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
                break;
            case 1 :  // move forward
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                break;        
            case 2 :  // veer to left
                set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                break;         
            case 4 :  // spin right
                set_motor(LEFT_MOTOR, MOTOR_FORWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                break;            
            case 5 :  // stop
                set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
                set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
                break;           
            case 6 :  // spin left
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_FORWARD, right_speed);
                break;           
            case 8 :  // reverse to right
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_OFF, 0);
                break;     
            case 9 :  // reverse
                set_motor(LEFT_MOTOR, MOTOR_BACKWARD, left_speed);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                break;      
            case 10 :  // reverse to left
                set_motor(LEFT_MOTOR, MOTOR_BRAKE, 0);
                set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, right_speed);
                break; 
        }                                
    }
}
