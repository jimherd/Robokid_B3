//----------------------------------------------------------------------------
//
//                  Robokid
//
//----------------------------------------------------------------------------
// user_defines.h : application specific program constants 
// ==============
//
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd           31/07/2008    
///----------------------------------------------------------------------------

 
#ifndef __user_defines_H
#define __user_defines_H

#include "global.h"

//----------------------------------------------------------------------------
// define the version of vehicle hardware 
//
// Version A : single 7-segment display
// Version B : dual 7-segment display + USB interface
//
#define   VERSION_B

#define   MAJOR_VERSION   'b'
#define   MINOR_VERSION   '3' 

//----------------------------------------------------------------------------
// Macros
// ======
//
// sound macros
//
#define     SOUND_TAPE_BUMP          play_tune(&snd_bump);
#define     SOUND_NEXT_SELECTION     play_tune(&snd_next_selection);
#define     SOUND_EXIT_SELECTION     play_tune(&snd_exit_selection);
#define     SOUND_READ_POTS          play_tune(&snd_read_pots);
#define     SOUND_SYSTEM_INIT        play_tune(&snd_system_init);
//
// macros to read debounced switch states
//
#define     WAIT_SWITCH_RELEASED(switch_n)      while((switch_n) == PRESSED);
#define     WAIT_SWITCH_PRESSED(switch_n)       while((switch_n) == RELEASED);
#define     WAIT_ANY_SWITCH_PRESSED             while(switch_ABCD == ALL_RELEASED);
#define     WAIT_ALL_SWITCHES_RELEASED          while(switch_ABCD != ALL_RELEASED);
#define     PROMPT_SWITCH_A    set_LED(LED_A, FLASH_ON);WAIT_SWITCH_PRESSED(switch_A);WAIT_SWITCH_RELEASED(switch_A);clr_LED(LED_A);

#define     BLACK            0
#define     WHITE            1
#define     READ_TAPE_SENSOR(line)     (get_adc((line)) < BLACK_WHITE_THRESHOLD ? WHITE : BLACK);
//
// macros to set LED patterns
//
#define  R_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); clr_LED(LED_C); set_LED(LED_D, FLASH_ON) 
#define  J_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); set_LED(LED_C, FLASH_ON); set_LED(LED_D, FLASH_ON);  
#define  F_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); set_LED(LED_C, FLASH_ON); set_LED(LED_D, FLASH_ON);  
#define  B_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); set_LED(LED_C, FLASH_ON); set_LED(LED_D, FLASH_ON);  
#define  P_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); set_LED(LED_C, FLASH_ON); set_LED(LED_D, FLASH_ON);   
#define  A_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); set_LED(LED_C, FLASH_ON); set_LED(LED_D, FLASH_ON);  
#define  E_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); set_LED(LED_C, FLASH_ON); set_LED(LED_D, FLASH_ON); 
#define  D_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); set_LED(LED_C, FLASH_ON); set_LED(LED_D, FLASH_ON); 
#define  L_MODE_LEDS    set_LED(LED_A, FLASH_ON); clr_LED(LED_B); set_LED(LED_C, FLASH_ON); set_LED(LED_D, FLASH_ON); 

//
// macros to access the 16-bit tick counter : protect by disabling/enabling interrupts
//
#define  CLR_TIMER16              { asm sei; tick_count_16 = 0; asm cli; }
#define  GET_TIMER16(variable)    { asm sei; (variable) = tick_count_16; asm cli; }

#define  DISABLE_INTERRUPTS       { asm sei;}
#define  ENABLE_INTERRUPTS        { asm cli;}

#define  CLEAR_AD_WHEEL_COUNTERS  { asm sei; left_wheel_count = 0; right_wheel_count = 0; asm cli; }

#define  INSTRUCTION(OP_CODE, MODIFIER, DATA)  ((((OP_CODE)<<8)&0x3F00) | (((MODIFIER)<<8)&0xC000) | (((DATA))&0x00FF))    

//----------------------------------------------------------------------------
// commands from reading strip scans
//
#define  STRIP_SCAN_BOTH_WHITE     0b11
#define  STRIP_SCAN_RIGHT_WHITE    0b01 
#define  STRIP_SCAN_LEFT_WHITE     0b10 
#define  STRIP_SCAN_BOTH_BLACK     0b00 

#define  STRIP_CMD_FORWARD         STRIP_SCAN_BOTH_BLACK
#define  STRIP_CMD_SPIN_RIGHT      STRIP_SCAN_RIGHT_WHITE
#define  STRIP_CMD_SPIN_LEFT       STRIP_SCAN_LEFT_WHITE
#define  STRIP_CMD_STOP            STRIP_SCAN_BOTH_WHITE

#define  STRIP_PLAY_SPIN_SPEED     30
#define  STRIP_PLAY_FORWARD_SPEED  75

//----------------------------------------------------------------------------
// system clock
//
#define BUSCLK  20000000  //Bus clock frequency (Hz)

//----------------------------------------------------------------------------
// timing defines
//
#define     PWM_FREQ    5000                // PWM set to 5kHz for motors
#define     PWM_COUNT   (BUSCLK/PWM_FREQ)   // main PWM count to give PWM_FREQ

#define     TICK_TIME_IN_MS          8
#define     TICKS_IN_ONE_SECOND    (1000/TICK_TIME_IN_MS)
//
#define     BAUD        57600               // Baud rate (BPS)

#define     MOTOR_TEST_TIME_OUT     (6 * TICKS_IN_ONE_SECOND)

#define     LINE_BUMP_TIME_OUT      (120 * TICKS_IN_ONE_SECOND)

#define     DEFAULT_SAMPLE_TIME     100

#define     WAIT_1SEC       DelayMs(1000);

//----------------------------------------------------------------------------
// 
//
#define     FORWARD_VALUE    129
#define     BACKWARD_VALUE     0
#define     STOP_VALUE       255
#define     DEADBAND          30

#define     DIFFERENTIAL_NULL   7

#define     JOYSTICK_FORWARD_VALUE    129
#define     JOYSTICK_BACKWARD_VALUE     0
#define     JOYSTICK_LEFT_VALUE       129
#define     JOYSTICK_RIGHT_VALUE        0
#define     JOYSTICK_STOP_VALUE       255

#define     CORNER_MODE_STOP_VALUE          0
#define     CORNER_MODE_HALF_SPEED_VALUE  255
#define     CORNER_MODE_FULL_SPEED_VALUE  129

#define     NO_BUMP     255
#define     YES_BUMP      0

#define     YES_LINE                  230
#define     NO_LINE                    60
#define     BLACK_WHITE_THRESHOLD     120     // lower for white, higher for black

#define     SWITCH_SAMPLES     3     // number of samples to debounce push switches

#define     DEFAULT_SPEED             60    // 60% full speed
#define     DEFAULT_LINE_BUMP_SPEED   60    // %
#define     DEFAULT_REVERSE_TIME       3
#define     DEFAULT_SPIN_TIME          5
#define     DEFAULT_PWM               60

#define     DEFAULT_LINE_FOLLOW_SPEED    40
#define     DEFAULT_LIGHT_FOLLOW_SPEED   40
#define     SLOW_SPEED                   40

#define     DEFAULT_DEADBAND          10
#define     DEFAULT_AMBIENT           30 

#define     FLASH_ERASE_STATE       0xff

#define     MAX_SEQ           64

#define     MAX_EXPERIMENT     9

#define     CRITICAL_BATTERY_THRESHOLD  150
#define     LOW_BATTERY_THRESHOLD       170     // 4.4v level

#define     MAX_STRIP_CMDS     30


#define   DRAWING_MODE_0_TIME_OUT      (30 * TICKS_IN_ONE_SECOND) 
#define   LEFT_SPIRAL                  0x00
#define   RIGHT_SPIRAL                 0xFF
#define   DEFAULT_SPIRAL_UPDATE_TIME   50
#define   MAX_SPIRAL_SPEED             70
#define   STOP_SPEED                   30
#define   SENSE_LOW                    10

#define   TEMP_STRING_SIZE             30

#define   WHEEL_SENSOR_CALIBRATE_SPEED     35
#define   NOS_WHEEL_SENSOR_CALIBRATE_READINGS          250
#define   V_MAX_VALUE    255
#define   V_MIN_VALUE      0


//----------------------------------------------------------------------------
// wheel sensor distance values
//
#define     PULSES_PER_TURN     36
#define     WHEEL_DIAM_MM       75    // circum = 235.6mm

#define     PULSES_FORWARD       5
#define     PULSES_BACKWARD     16

#define     WHEEL_CONSTANT     153     // 1.53 pulses/cm

//----------------------------------------------------------------------------
// PID values
//
#define     I_MAX             10
#define     I_MIN              0

#define     P_GAIN_DEFAULT    40
#define     I_GAIN_DEFAULT     3
#define     D_GAIN_DEFAULT     2

#define     E_GAIN_DEFAULT    10
     
//----------------------------------------------------------------------------
// switch values
//
#define     PRESSED        0
#define     RELEASED       1
#define     ALL_RELEASED   0b00111100 

//----------------------------------------------------------------------------
// error codes
//
#define     OK          0
#define     FAIL        1

//----------------------------------------------------------------------------
// ON/OFF codes
//
#define     ON          0x55
#define     OFF         0xCC

//----------------------------------------------------------------------------
// constants for tone generation
//
#define     C_COUNT     19084       // base count for PWM system to produce a "C"

#define     FREQ_C      262
#define     FREQ_CS     277
#define     FREQ_D      294
#define     FREQ_DS     311
#define     FREQ_E      330
#define     FREQ_F      349
#define     FREQ_FS     370
#define     FREQ_G      382
#define     FREQ_GS     415
#define     FREQ_A      440
#define     FREQ_AS     455
#define     FREQ_B      484

#define     NOTE_C      0
#define     NOTE_CS     1
#define     NOTE_D      2
#define     NOTE_DS     3
#define     NOTE_E      4
#define     NOTE_F      5
#define     NOTE_FS     6
#define     NOTE_G      7
#define     NOTE_GS     8
#define     NOTE_A      9
#define     NOTE_AS    10
#define     NOTE_B     11
#define     SILENT_NOTE    12

//----------------------------------------------------------------------------
// Motor action/state definitions
//
typedef enum {FULL_SPEED=100, HALF_SPEED=50} speed_t;
typedef enum {MOTOR_OFF, MOTOR_FORWARD, MOTOR_BACKWARD, MOTOR_BRAKE} motor_state_t;
typedef enum {STOPPED, MOVING_FORWARD, MOVING_BACKWARD, TURNING_LEFT, TURNING_RIGHT} vehicle_state_t;
typedef enum {LEFT_MOTOR, RIGHT_MOTOR} motor_t;
typedef enum {FORWARD, BACKWARD, SPIN_RIGHT, SPIN_LEFT} direction_t;
typedef enum {MODE_INIT, MODE_RUNNING, MODE_STOPPED} mode_state_t;

    
typedef enum {LCR, LCx, LxR, Lxx, xCR, xCx, xxR, xxx} bump_options_t;
    
//----------------------------------------------------------------------------
// error codes
//
typedef enum {
    NO_ERROR, TIME_OUT
} error_codes_t;    

//----------------------------------------------------------------------------
// analogue channels  (0->13)
//
typedef enum {
        BATTERY_VOLTS, 
        POT_3, POT_2, POT_1, 
        PAD_SWL,PAD_SWR, 
        LINE_SENSOR_L, LINE_SENSOR_R, 
        FRONT_SENSOR_L, FRONT_SENSOR_C, FRONT_SENSOR_R,
        WHEEL_SENSOR_L, WHEEL_SENSOR_R, REAR_SENSOR
} a2d_channels_t;
 
//
// list of different system modes
//
typedef enum {
    JOYSTICK_MODE, ACTIVITY_MODE, BUMP_MODE, FOLLOW_MODE, PROGRAM_MODE, 
    SKETCH_MODE, LAB_MODE, DISTANCE_MODE, EXPERIMENT_MODE
} sys_modes_t;

#define   FIRST_SYS_MODE  JOYSTICK_MODE
#define   LAST_SYS_MODE   EXPERIMENT_MODE

#define   INIT_MODE_CODE         'r'
#define   JOYSTICK_MODE_CODE     'J'
#define   ACTIVITY_MODE_CODE     'A'
#define   BUMP_MODE_CODE         'b'
#define   FOLLOW_MODE_CODE       'F'
#define   PROGRAM_MODE_CODE      'P'
#define   SKETCH_MODE_CODE       'S'
#define   LAB_MODE_CODE          'L'
#define   DISTANCE_MODE_CODE     'd'
#define   EXPERIMENT_MODE_CODE   'E'

typedef enum 
    { JOYSTICK_MODE_1, JOYSTICK_MODE_2, JOYSTICK_MODE_3
} joystick_mode_t;

#define   FIRST_JOYSTICK_MODE  JOYSTICK_MODE_1
#define   LAST_JOYSTICK_MODE   JOYSTICK_MODE_3

typedef enum 
    { RUN_FORWARD, RUN_BACKWARD, RUN_SPIN_RIGHT, RUN_SPIN_LEFT, RUN_TEST,  DEMO_MODE
} activity_mode_t;

#define   FIRST_ACTIVITY_MODE  RUN_FORWARD
#define   LAST_ACTIVITY_MODE   RUN_TEST
    
typedef enum 
    { LINE_BUMP_MODE, LINE_BUG_BUMP_MODE, WALL_BUMP_MODE 
} bump_mode_t;

#define   FIRST_BUMP_MODE  LINE_BUMP_MODE
#define   LAST_BUMP_MODE   WALL_BUMP_MODE

typedef enum 
    { LINE_FOLLOW_MODE, LIGHT_FOLLOW_MODE
} follow_mode_t;

typedef enum 
    { TAPE_MANUAL_MODE, TAPE_MOTOR_MODE
} program_mode_t;

#define   FIRST_FOLLOW_MODE  LINE_FOLLOW_MODE
#define   LAST_FOLLOW_MODE   LIGHT_FOLLOW_MODE

typedef enum 
    { PROGRAM_MODE_0, PROGRAM_MODE_1, PROGRAM_MODE_2, PROGRAM_MODE_3, 
} program_mode_t;

#define   FIRST_PROGRAM_MODE  PROGRAM_MODE_0
#define   LAST_PROGRAM_MODE   PROGRAM_MODE_1

typedef enum {PLAY, COLLECT, SAVE, RECALL, DUMP} sequence_mode_t;

#define   FIRST_SEQUENCE_MODE    PLAY
#define   LAST_SEQUENCE_MODE     DUMP

typedef enum 
    { SKETCH_MODE_0, SKETCH_MODE_1, SKETCH_MODE_2
} drawing_mode_t;

#define   FIRST_SKETCH_MODE  SKETCH_MODE_0
#define   LAST_SKETCH_MODE   SKETCH_MODE_2

typedef enum 
    { LAB_MODE_0, LAB_MODE_1, LAB_MODE_2
} lab_mode_t;

typedef enum 
    { DISTANCE_MODE_0, DISTANCE_MODE_1, DISTANCE_MODE_2
} distance_mode_t;

#define   FIRST_DISTANCE_MODE  DISTANCE_MODE_0
#define   LAST_DISTANCE_MODE   DISTANCE_MODE_2

#define   FIRST_LAB_MODE  LAB_MODE_0
#define   LAST_LAB_MODE   LAB_MODE_2

typedef enum 
    { CYCLE_DISPLAYS
} experiment_mode_t;

#define   FIRST_EXPERIMENT_MODE  CYCLE_DISPLAYS
#define   LAST_EXPERIMENT_MODE   9


#define   RAM_SEQUENCE_SIZE    100

#endif
