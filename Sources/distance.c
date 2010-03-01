//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// distance.c : run modes that use the distance encoders
// ==========
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd          08/09/09      
//----------------------------------------------------------------------------

#include "global.h"

//----------------------------------------------------------------------------
// run_distance_mode :  Run modes that use the wheel encoder sensors
// =================
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch C = exit to main slection level
//          switch D = step through selections
//
uint8_t run_distance_mode(void) 
{
uint8_t   activity;

    D_MODE_LEDS;
    activity = FIRST_DISTANCE_MODE;
    show_dual_chars(DISTANCE_MODE_CODE, ('0'+ activity), (A_TO_FLASH | 10));
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
            show_dual_chars(DISTANCE_MODE_CODE, ('0'+ activity), (A_TO_FLASH | 10));
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
// run a distance activity
// 
        show_dual_chars(DISTANCE_MODE_CODE, ('0'+ activity), 0);
        push_LED_display();       
        switch (activity) {
                case DISTANCE_MODE_0 :                          // in progress
                    run_distance_mode_0();
                    break;
                case DISTANCE_MODE_1 :                          // in progress
                    run_distance_mode_1();
                    break;
                case DISTANCE_MODE_2 :                          // in progress
                    run_distance_mode_2();
                    break;                                        
                default :
                    break;
        }
        show_dual_chars(DISTANCE_MODE_CODE, ('0'+ activity), (A_TO_FLASH | 10));
        pop_LED_display();       
    } 
}

//----------------------------------------------------------------------------
// run_distance_mode_0 : 
// ===================
//
// Description
//      Draw a shape
//
// Notes
//
//      Active switches are 
//          switch A = go/stop button
//          switch B = read POTs
//          switch C = exit
//          switch D = ---
//
//      Active pots
//

uint8_t run_distance_mode_0(void) 
{
mode_state_t    state; 

    state = MODE_INIT;
    set_LED(LED_A, FLASH_ON);
    clr_LED(LED_B);
    set_LED(LED_C, FLASH_ON);
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
            if (switch_A == PRESSED) {            
                state = MODE_INIT;
                vehicle_stop();
                WAIT_SWITCH_RELEASED(switch_A);
                continue;
            }
        }
        move_distance(40, LEFT_MOTOR, WHEEL_SENSOR_CALIBRATE_SPEED, WHEEL_SENSOR_CALIBRATE_SPEED);
        DelayMs(1000);
        move_distance(20, LEFT_MOTOR, WHEEL_SENSOR_CALIBRATE_SPEED, -WHEEL_SENSOR_CALIBRATE_SPEED);    
        return 0;    
    }
}


//----------------------------------------------------------------------------
// run_distance_mode_1 : 
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

uint8_t run_distance_mode_1(void) 
{
mode_state_t    state; 

    state = MODE_INIT;
    set_LED(LED_A, FLASH_ON);
    clr_LED(LED_B);
    set_LED(LED_C, FLASH_ON);
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
    CLEAR_AD_WHEEL_COUNTERS;
//
    set_motor(LEFT_MOTOR, MOTOR_FORWARD, WHEEL_SENSOR_CALIBRATE_SPEED);
    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, WHEEL_SENSOR_CALIBRATE_SPEED);
    DelayMs(2000);
    vehicle_stop();
    sprintf(tempstring, "Left=%u   Right=%u\r\n", left_wheel_count, right_wheel_count);
    send_msg(tempstring);    
    
    return 0;
    }
}

//----------------------------------------------------------------------------
// run_distance_mode_2 : calibrate wheel sensors
// ===================
//
// Description
//      Calculate threshold values for wheel distance sensors and store
//      values in FLASH area.  The wheel IR replective sensors are connected
//      to both an analogue input and a digital/interrupt input.  The digital
//      input works if the wheel is correctly aligned however it may give 
//      problems over longer periods of time.
//      The analogue input can act as a variable threshold input.  This routine
//      estimates a value by taking an average value over at least one complete
//      revolution of a wheel.
//      This must be done at a slow speed to make sure that all the necessary 
//      data is captured.
//      Finally, the data is stored in a FLASH page area.
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
uint8_t run_distance_mode_2(void) 
{
mode_state_t    state;
uint16_t    i;
uint8_t     left_value, right_value, left_threshold, right_threshold;
uint8_t     max_left_value, min_left_value, max_right_value, min_right_value;

    state = MODE_INIT;
    set_LED(LED_A, FLASH_ON);
    set_LED(LED_B, FLASH_ON);
    clr_LED(LED_C);
    clr_LED(LED_D);
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
        if (state == MODE_INIT) {
            if (switch_A == PRESSED) {            //  go to RUN state              
                state = MODE_RUNNING;
                WAIT_SWITCH_RELEASED(switch_A); 
            } else {
                continue;                         // back to begining of FOREVER loop
            }
        }
        if (state == MODE_RUNNING) {
            if (switch_A == PRESSED) {            // 
                state = MODE_INIT;
                WAIT_SWITCH_RELEASED(switch_A);
                continue;
            }
        }
      //
      // Calibration procedure
      //   1. Run robot at a slow speed
      //   
        set_motor(LEFT_MOTOR, MOTOR_FORWARD, WHEEL_SENSOR_CALIBRATE_SPEED);
        set_motor(RIGHT_MOTOR, MOTOR_FORWARD, WHEEL_SENSOR_CALIBRATE_SPEED);
      //
      // 2. Read wheel sensor as a set of analogue values (range 0->255)
      //
        max_left_value  = V_MIN_VALUE;  
        min_left_value  = V_MAX_VALUE;
        max_right_value = V_MIN_VALUE;  
        min_right_value = V_MAX_VALUE;
        for(i = 0 ; i < NOS_WHEEL_SENSOR_CALIBRATE_READINGS ; i++) {
        
            left_value = get_adc(WHEEL_SENSOR_L);
            if (left_value > max_left_value) {
                max_left_value = left_value;
            }
            if (left_value < min_left_value) {
                min_left_value = left_value;
            }
            
            right_value = get_adc(WHEEL_SENSOR_R);
            if (right_value > max_right_value) {
                max_right_value = right_value;
            }
            if (right_value < min_right_value) {
                min_right_value = right_value;
            }              

            DelayMs(8);
        }
        vehicle_stop();
      //
      //   3. calculate threshold values as midpoint between max and min values
      //
        left_threshold = (max_left_value >> 1) + (min_left_value >> 1);
        right_threshold = (max_right_value >> 1) + (min_right_value >> 1);
      //
      //   4. store in FLASH area for later use   (Time for FLASH write to work?)
      //
        memcpy(&FLASH_data, &FLASH_data_image, sizeof(FLASH_data_t));
        FLASH_data_image.LEFT_WHEEL_THRESHOLD = left_threshold;
        FLASH_data_image.RIGHT_WHEEL_THRESHOLD = right_threshold;
        FlashErasePage((uint16_t)&FLASH_data.GUARD_BYTE);
        FlashProgramByte((uint16_t)&FLASH_data.LEFT_WHEEL_THRESHOLD, FLASH_data_image.LEFT_WHEEL_THRESHOLD);
        FlashProgramByte((uint16_t)&FLASH_data.RIGHT_WHEEL_THRESHOLD, FLASH_data_image.RIGHT_WHEEL_THRESHOLD);
      //
      //   5. Print values on serial channel
      //                                                                                
       sprintf(tempstring, "Left=%u   Right=%u\r\n", left_threshold, right_threshold);
       send_msg(tempstring);
       sprintf(tempstring, "Left:min=%u  max=%u\r\n", min_left_value, max_left_value);
       send_msg(tempstring);
       sprintf(tempstring, "Right:min=%u  max=%u\r\n", min_right_value, max_right_value);
       send_msg(tempstring);
       return 0;
    }
}

//----------------------------------------------------------------------------
// move_distance : run robot for a set number of wheel encoder counts
// =============
//
// Parameters
//      encoder_counts : number of wheel count
//      unit           : motor used for wheel encoder counts
//      l_speed        : speed of left motor (0 -> 100%)
//      r_speed        : speed of right motor (0 -> 100%)
//
// Description
//      Crude distance move routine.  Stops after specified count.
//      No speed profile at this time.
//      
// Notes
//
//
uint8_t move_distance(uint16_t encoder_counts, motor_t unit, int8_t l_speed, int8_t r_speed) 
{
   //
   // clear encoder wheel counter
   //
    CLEAR_AD_WHEEL_COUNTERS;
//
// set left motor; check if forward or backward move required
//    
    if (l_speed < 0) {
        set_motor(LEFT_MOTOR, MOTOR_BACKWARD, (uint8_t)(-l_speed));
    } else {
        set_motor(LEFT_MOTOR, MOTOR_FORWARD, (uint8_t)l_speed); 
    }
//
// set right motor; check if forward or backward move required
// 
    if (r_speed < 0) {
        set_motor(RIGHT_MOTOR, MOTOR_BACKWARD, (uint8_t)(-r_speed));
    } else {
        set_motor(RIGHT_MOTOR, MOTOR_FORWARD, (uint8_t)r_speed); 
    }
//
// check if left wheel count has reached, or exceeded specifies encoder count
//
    if (unit == LEFT_MOTOR) {
        while (left_wheel_count < encoder_counts) {   
            ;
        }
        vehicle_stop();
        return 0;
    }
//
// check if right wheel count has reached, or exceeded specifies encoder count
//    
    if (unit == RIGHT_MOTOR) {
        while (right_wheel_count < encoder_counts) {
            ;
        }
        vehicle_stop();
        return 0;        
    }
    
}


