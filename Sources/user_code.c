//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// user_code.c : code to run main functions of the vehicle
// ===========
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd    13/08/08      brought together all interrupt code 
//             26/08/08      included PID loop for line following 
//             13/12/08      copied project to new directory bot_B2                  
//----------------------------------------------------------------------------

#include "global.h"

#pragma  MESSAGE DISABLE C1420
   
//----------------------------------------------------------------------------
// Variables held in flash areas that can be re-flashed
//
// Segment : FLASH_CONST : store system constants
// 
#pragma   DATA_SEG    FLASH_CONST

FLASH_data_t    FLASH_data;

#pragma  DATA_SEG    DEFAULT
//
// Segment : FLASH_PRG1 : store program 1
// 
#pragma   DATA_SEG    FLASH_PRG1

union {
    uint16_t  uint16[256];
    uint8_t   uint8[512];
} FLASH_seq_0;

#pragma  DATA_SEG    DEFAULT
//----------------------------------------------------------------------------
//  definition of display strings for dual 7-segment display
//
#pragma INTO_ROM
seven_seg_display_t  hello = { 
    SEVEN_SEG_AB, 7, 0, 80, 0,
    CHAR_H, CHAR_E, CHAR_L, CHAR_L, CHAR_O, CHAR_CLR, CHAR_CLR, 0,0,0,0,0,0,0,0,0,
    CHAR_CLR, CHAR_H, CHAR_E, CHAR_L, CHAR_L, CHAR_O, CHAR_CLR, 0,0,0,0,0,0,0,0,0
};
#pragma INTO_ROM
seven_seg_display_t  robot = { 
    SEVEN_SEG_AB, 6, 0, 80, 0,
    CHAR_r, CHAR_o, CHAR_b, CHAR_o, CHAR_t, CHAR_CLR, 0, 0,0,0,0,0,0,0,0,0,
    CHAR_CLR, CHAR_r, CHAR_o, CHAR_b, CHAR_o, CHAR_t, 0, 0,0,0,0,0,0,0,0,0,
};
#pragma INTO_ROM
seven_seg_display_t  recharge = { 
    SEVEN_SEG_AB, 9, 0, 80, 0,
    CHAR_r, CHAR_E, CHAR_c, CHAR_h, CHAR_A, CHAR_r, CHAR_g, CHAR_E, CHAR_CLR, 0,0,0,0,0,0,0,
    CHAR_CLR, CHAR_r, CHAR_E, CHAR_c, CHAR_h, CHAR_A, CHAR_r, CHAR_g, CHAR_E,  0,0,0,0,0,0,0
};
#pragma INTO_ROM
seven_seg_display_t  bat_lo = {        // "bat_lo "
    SEVEN_SEG_AB, 7, 0, 80, 0,
    CHAR_b, CHAR_A, CHAR_t, CHAR__, CHAR_L, CHAR_o, CHAR_CLR, 0,0,0,0,0,0,0,0,0,
    CHAR_CLR, CHAR_b, CHAR_A, CHAR_t, CHAR__, CHAR_L, CHAR_o,  0,0,0,0,0,0,0,0,0
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// MODULE user_code 
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// user_init : initialisation of system variables
// =========
//
// Notes
//      Use routine to initialise variables.
//
void user_init(void) {

    disable_wheel_count();
    
    switch_A = RELEASED; switch_B = RELEASED; switch_C = RELEASED; switch_D = RELEASED;

    state_of_vehicle = STOPPED;
    left_motor_state = MOTOR_OFF;
    right_motor_state = MOTOR_OFF;
    
    left_speed  = DEFAULT_SPEED; 
    right_speed = DEFAULT_SPEED; 
    left_PWM    = DEFAULT_PWM; 
    right_PWM   = DEFAULT_PWM;
     
    current_left_speed = 0;
    current_right_speed = 0; 
    pwm_differential = DIFFERENTIAL_NULL;

    set_motor(RIGHT_MOTOR, MOTOR_OFF, 0);
    set_motor(LEFT_MOTOR , MOTOR_OFF, 0);
    
    tick_count_8 = 0;
    tick_count_16 = 0;
    second_count = 0;
    tick_for_second_count = TICKS_IN_ONE_SECOND;
//
// set wheel sensor initial conditions
//    
    left_wheel_count = 0;
    right_wheel_count = 0;
    
    left_wheel_sensor_value = get_adc(WHEEL_SENSOR_L);
    if (left_wheel_sensor_value < FLASH_data.LEFT_WHEEL_THRESHOLD) {
        left_wheel_sensor_value = BLACK; 
    } else {
        left_wheel_sensor_value = WHITE;
    }
    
    right_wheel_sensor_value = get_adc(WHEEL_SENSOR_R);
    if (right_wheel_sensor_value < FLASH_data.RIGHT_WHEEL_THRESHOLD) {
        right_wheel_sensor_value = BLACK; 
    } else {
        right_wheel_sensor_value = WHITE;
    }
          
    left_speed_index = 0;     // index to left speed circular buffer
    right_speed_index = 0;    // index to right speed circular buffer
    
    display_init();
//
// briefly show software version number
//
    show_dual_chars(MAJOR_VERSION, MINOR_VERSION, FLASH_OFF);
//
// Play start-up tune to indicate end of initialisation process
//
    sound_init();
    play_tune(&snd_start_up);
//
// enable system interrupts
//
    EnableInterrupts;       /* enable interrupts */
    
    DelayMs(1000);
//
// self test
//
    self_test();
}

//----------------------------------------------------------------------------
// get_random_bit : random bit generator
// ==============
//
// Notes
//      Uses background counter to generate some randomness
//
uint8_t get_random_bit(void) {

    return  (tick_count_8 & 0x01);
}

//----------------------------------------------------------------------------
// get_random_byte : get a random 8-bit value
// ===============
//
// Notes
//      Use low 8-bits of background 8mS tick counter
//
uint8_t get_random_byte(void) {

    return  tick_count_8;
}

//----------------------------------------------------------------------------
// disable_wheel_count : stop counting wheel rotation pulses
// ===================
//
// Parameters
//      None
//
//  Notes
//      Disable IRQ and KBI interrupts
//
void disable_wheel_count(void) {

    IRQSC_IRQIE = 0;
    KBI1SC_KBIE = 0;    
}

//----------------------------------------------------------------------------
// enable_wheel_count : start counting wheel rotation pulses
// ==================
//
// Parameters
//      None
//
//  Notes
//      Enable IRQ and KBI interrupts
//
void enable_wheel_count(void) {

    IRQSC_IRQIE = 1;
    KBI1SC_KBIE = 1;    
}

//----------------------------------------------------------------------------
// update_PID : compute controller output from PID parameters
// ==========
//
// Parameters
//      error : current calculated error
//      old_error : previous calculated error
//
// Notes
//      Care need to be taken
//  
//uint8_t  update_PID(int8_t error, int8_t old_error) {
//
// compute proportional term
//
//    P_term = P_gain * error;
//
// compute intergral term and check against limits
//
//    I_value = I_value + error;
//    if (I_value > I_MAX) {
//        I_value = I_max;
//    } else {
//        if (I_value < I_MIN) {
//            I_value = I_MIN;
//        } 
//    }
//    I_term = I_gain * I_value;
//
// compute derivative term
//
//    D_term = D_gain * (error - old_error);
//
// compute PID value
//
//    PID_value = P_term + I_term - D_term;
//   PID_value = PID_value / 100;
//        
//    return (uint8_t)PID_value;    
//}

//----------------------------------------------------------------------------
// set_vehicle_state : update state of vehicle
// =================
//
// Notes
//      Uses the state of each motor to define the state of the vehicle
//      -              STOPPED, MOVING_FORWARD, MOVING_BACKWARD, TURNING_LEFT, TURNING_RIGHT
//  7-seg didplay         0           1                 2              3            4
// 
void set_vehicle_state(void) {

    if ((left_motor_state == MOTOR_FORWARD) && (right_motor_state == MOTOR_FORWARD)) { 
        state_of_vehicle = MOVING_FORWARD;
        current_speed = straight_line_speed;
    } else if ((left_motor_state == MOTOR_BACKWARD) && (right_motor_state == MOTOR_BACKWARD)) {
        state_of_vehicle = MOVING_BACKWARD;
        current_speed = straight_line_speed;
    } else if ((left_motor_state == MOTOR_BACKWARD) && (right_motor_state == MOTOR_FORWARD)) {
        state_of_vehicle = TURNING_LEFT;
        current_speed = turn_speed;
    } else if ((left_motor_state == MOTOR_FORWARD) && (right_motor_state == MOTOR_BACKWARD)) {
        state_of_vehicle = TURNING_RIGHT;
        current_speed = turn_speed;        
    } else {
        state_of_vehicle = STOPPED;
        current_speed = 0;
    }
}

//----------------------------------------------------------------------------
// set_motor : configure a motor
// =========
//
// Notes
//      The motor speed is specified in the range of 0 to 100% which is
//      converted to the range 0 to 250 for use in the routine 'SetRatio8"
//
// Parameters
//      unit      : LEFT_MOTOR or RIGHT_MOTOR
//      state     : MOTOR_OFF, MOTOR_FORWARD, MOTOR_BACKWARD, or MOTOR_BRAKE
//      pwm_width : 0% to 100%
//
void  set_motor(motor_t unit, motor_state_t state, uint8_t pwm_width) {

uint16_t  pulse_count, period_count ;

    period_count = TPM1MOD;        // get current period count (e.g. 889 for 5kHz frequency)
    pulse_count = (period_count/100) * (100 - pwm_width);
    
    if (unit == LEFT_MOTOR) {
        switch (state) {
            case MOTOR_OFF :        // set FREEWHEEL condition
                setReg16(TPM1C0V, 0);     // set LOW on PWM1 and PWM2
                setReg16(TPM1C1V, 0);                
                left_motor_state = MOTOR_OFF;
                break;
            case MOTOR_FORWARD :    // set LOW on PWM2 and LM_PWM on LM_PWM1                                
                setReg16(TPM1C0V, pulse_count);       // set LOW on LM_PWM1
                setReg16(TPM1C1V, period_count);      // set pwm on LM_PWM2           
                left_motor_state = MOTOR_FORWARD;
                break;
            case MOTOR_BACKWARD :   // set LOW on PWM1 and PWM on PWM2
                setReg16(TPM1C0V, period_count);      // set pwm on LM_PWM1
                setReg16(TPM1C1V, pulse_count);       // set LOW on LM_PWM2    
                left_motor_state = MOTOR_BACKWARD;
                break;
            case MOTOR_BRAKE :      // set BRAKE condition
                setReg16(TPM1C0V, period_count);     // set HIGH on LM_PWM1 and LM_PWM2
                setReg16(TPM1C1V, period_count);
                left_motor_state = MOTOR_BRAKE;
                break;
        } 
    }
    
    if (unit == RIGHT_MOTOR) {
        switch (state) {
            case MOTOR_OFF :        // set FREEWHEEL condition
                setReg16(TPM1C2V, 0);     // set LOW on RM_PWM1 and RM_PWM2
                setReg16(TPM1C3V, 0);
                left_motor_state = MOTOR_OFF;
                break;
            case MOTOR_FORWARD :    // set LOW on RM_PWM2 and pwm on LM_PWM1
                setReg16(TPM1C2V, period_count);      // set pwm on RM_PWM1
                setReg16(TPM1C3V, pulse_count);       // set LOW on RM_PWM2
                left_motor_state = MOTOR_FORWARD;
                break;
            case MOTOR_BACKWARD :   // set LOW on RM_PWM1 and RM_PWM2
                setReg16(TPM1C2V, pulse_count);       // set LOW on RM_PWM1
                setReg16(TPM1C3V, period_count);      // set pwm on RM_PWM2
                left_motor_state = MOTOR_BACKWARD;
                break;
            case MOTOR_BRAKE :      // set BRAKE condition
                setReg16(TPM1C2V, period_count);     // set HIGH on RM_PWM1 and RM_PWM2
                setReg16(TPM1C3V, period_count);
                left_motor_state = MOTOR_BRAKE;
                break;
        }
    }
    setReg8(TPM1SC, (TPM_OVFL_INT_DIS | TPM_EDGE_ALIGN | TPM_BUSCLK | TPM_PRESCAL_DIV1));  
    set_vehicle_state(); 
}

//----------------------------------------------------------------------------
// vehicle_stop : set both motor to brake
// ============
//
void vehicle_stop(void) {

    set_motor(RIGHT_MOTOR, MOTOR_BRAKE, 0);
    set_motor(LEFT_MOTOR , MOTOR_BRAKE, 0);
}

//----------------------------------------------------------------------------
// abs16 : compute absolute value for a int16_t type value
// =====
//
int16_t abs16(int16_t  value) {
    
    if (value < 0){
        return -value;
    } else {
        return value;
    }
}

//----------------------------------------------------------------------------
// self_test : run some test code
// =========
//
void self_test(void) {
}

//----------------------------------------------------------------------------
// check_for_test : check for the power-up test mode and execute command if acivated
// ============
//
// Notes
//      The power-on test mode is initited by shorting the central bump and rear bump
//      sensor inputs during power on.
//      Test as follows
//          1. Flashing "test8" on display with any press to continue
//          2. test LEDs and switches.
//          3. Robot moves forward about 30 cm - press any switch to continue
//          4. Robot spins to right about 90 degrees _ press any switch to continue
//          5. set POTs to point to battery - press any switch to continue
//          6. 
//
void check_for_power_on_test(void) 
{
uint8_t   value_1, value_2;

    value_1 = get_adc(FRONT_SENSOR_C);
    value_2 = get_adc(REAR_SENSOR);
    
    if (( value_1 > 10) || (value_2 > 10)) {
        return;
    }     
//
// 1. show flashing "test8" message on seven segment display.
//
    display_string("test8 ", 0); 
    WAIT_ANY_SWITCH_PRESSED;
    WAIT_ALL_SWITCHES_RELEASED; 
//
// 2. set each LEDs in sequence and wait for appropriate switch press
//    

    set_LED(LED_A, FLASH_ON);
    WAIT_SWITCH_PRESSED(switch_A);
    WAIT_SWITCH_RELEASED(switch_A);
    clr_LED(LED_A);
//       
    set_LED(LED_B, FLASH_ON);
    WAIT_SWITCH_PRESSED(switch_B);
    WAIT_SWITCH_RELEASED(switch_B);
    clr_LED(LED_B);
//        
    set_LED(LED_C, FLASH_ON);
    WAIT_SWITCH_PRESSED(switch_C);
    WAIT_SWITCH_RELEASED(switch_C);
    clr_LED(LED_C);
//     
    set_LED(LED_D, FLASH_ON);
    WAIT_SWITCH_PRESSED(switch_D);
    WAIT_SWITCH_RELEASED(switch_D);
    clr_LED(LED_D);
//
// 3. Test robot moving forward for 5 seconds
//
    set_LED(LED_A, FLASH_ON);
    WAIT_SWITCH_PRESSED(switch_A);
    WAIT_SWITCH_RELEASED(switch_A);
    clr_LED(LED_A);
    set_motor(LEFT_MOTOR, MOTOR_FORWARD, 60);
    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, 60);
    DelayMs(5000);
    set_motor(LEFT_MOTOR, MOTOR_OFF, 0);
    set_motor(RIGHT_MOTOR, MOTOR_OFF, 0);
//
// 4. test robot turning to the left for 5 seconds
//
    PROMPT_SWITCH_A;
    set_motor(LEFT_MOTOR, MOTOR_BACKWARD, 60);
    set_motor(RIGHT_MOTOR, MOTOR_FORWARD, 60);
    DelayMs(3000);
    set_motor(LEFT_MOTOR, MOTOR_OFF, 0);
    set_motor(RIGHT_MOTOR, MOTOR_OFF, 0);
//
// 5. set POTs to mid positions 
//
    display_string("set pots ", 0);
    set_LED(LED_A, FLASH_ON);
    PROMPT_SWITCH_A;
    //
    // check that all three have an approx value of 128
    //
    value_1 = get_adc(POT_1);    
    if ((value_1 < 100) || (value_1 > 156)){
        display_string("err_pot_1 ",0);
        PROMPT_SWITCH_A;
    }
    value_1 = get_adc(POT_2);    
    if ((value_1 < 100) || (value_1 > 156)){
        display_string("err_pot_2 ",0);
        PROMPT_SWITCH_A;
    }    
    value_1 = get_adc(POT_3);    
    if ((value_1 < 100) || (value_1 > 156)){
        display_string("err_pot_3 ",0);
        PROMPT_SWITCH_A;
    }       
    display_string("test_end ",0);        
    HANG;

}

//----------------------------------------------------------------------------
// run_bot : code to execute robot operation.
// =======
//
// Description
//     Initialise system
//     check for entry to special test mode
//     output messages on serial channel
//     check battery level
//     hold until Switch A is pressed
//     Update display
//     implement selected programme
//
// Notes
//     On power-on the experiment mode is not available.  This prevents the pupils putting
//     the robot into special modes.  To get the system to include the experiment mode (r5)
//     in the 'r' options press the D switch for longer than 5 seconds. 
//       
void run_bot(void) {

static sys_modes_t  mode, last_mode;
uint8_t   ad_value;
uint16_t  ticks;

    user_init();
//
// output message on serial port
//    
    send_msg("RoboKid Vehicle V1.0B\r\n");
    send_msg("Unit active\r\n");
//
// print battery voltage value
//
    send_msg("Battery voltage reading = ");
    ad_value = get_adc(BATTERY_VOLTS);             
    send_msg(bcd(ad_value, tempstring));
    send_msg("\r\n");
//
// check for possible start-up test mode
//
    check_for_power_on_test();
//
// check battery levels and do one of the following
//
//  1. battery level very low -> show recharge message. and halt
//  2. battery level low -> show battery level message for several seconds then show "robot"
//  3. battery level OK -> continue as normal and show "robot" string
//    
    if (get_adc(BATTERY_VOLTS) < CRITICAL_BATTERY_THRESHOLD) {
        load_display(&recharge);
        play_tune(&snd_battery_recharge);
        HANG;                        //  insufficient power to run the motors reliably
    }
    if (get_adc(BATTERY_VOLTS) < LOW_BATTERY_THRESHOLD) {
        load_display(&bat_lo);
        play_tune(&snd_battery_low);
        DelayMs(20000);
    }    
    load_display(&robot);
//
// user must press switch A to continue
//
    set_LED(LED_A, FLASH_ON);
    FOREVER {
        if (switch_A == PRESSED) {
            WAIT_SWITCH_RELEASED(switch_A);
            break;
        }
    }
    SOUND_SYSTEM_INIT;
    R_MODE_LEDS;
    show_dual_chars('r', '0', (A_TO_FLASH | 10));
    last_mode = LAST_SYS_MODE - 1;     // hide experiment mode 

    mode = 0;
 
//
// check for GO or mode increment button
//        
    FOREVER {
        if (switch_A == PRESSED) {    // GO button
            clr_LED(LED_A);
            clr_LED(LED_D);       
            show_dual_chars('r', ('0'+ mode), 0);
            WAIT_SWITCH_RELEASED(switch_A);     // wait until button returns to quiescent state
            play_tune(&snd_goto_selection);
            switch (mode){
                case JOYSTICK_MODE :                             // done
                    run_joystick_mode();
                    break;                                                     
                case ACTIVITY_MODE :                             // done
                    run_activity_mode();
                    break; 
                case BUMP_MODE :                                 // in progress
                    run_bump_mode();
                    break;             
                case FOLLOW_MODE :                               // done
                    run_follow_mode();
                    break;    
                case PROGRAM_MODE :                              // in progress
                    run_program_mode();
                    break;
                case SKETCH_MODE :                               // in progress
                    run_sketch_mode();
                    break; 
                case LAB_MODE :                                  // in progress
                    run_lab_mode();
                    break; 
                case DISTANCE_MODE :                             // in progress
                    run_distance_mode();
                    break; 
                case EXPERIMENT_MODE :                           // done
                    run_experiment_mode();
                    break;              
                default :
                    break;
            }
            R_MODE_LEDS;
            show_dual_chars('r', ('0' + mode), (A_TO_FLASH | 10));
        }
//
//  check for mode change button
//
        
        if (switch_D == PRESSED) {
            CLR_TIMER16;                        // clear 16-bit 8mS tick counter
            mode++; 
            if (mode > last_mode) {
                mode = 0;
            }           
            show_dual_chars('r', ('0' + mode), (A_TO_FLASH | 10));
            SOUND_NEXT_SELECTION;
            WAIT_SWITCH_RELEASED(switch_D);     // wait until button returns to quiescent state 
            GET_TIMER16(ticks);                 // read 16-bit 8mS tick counter
            if (ticks > (5 * TICKS_IN_ONE_SECOND)) {     // button press time > 5 seconds
                last_mode = EXPERIMENT_MODE;
            }
        }  
    }
}

/* END user_code */
