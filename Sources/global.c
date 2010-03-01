//----------------------------------------------------------------------------
//                  Robokid
//----------------------------------------------------------------------------
// global.c : declaration for global variables
// ========
//
// Description
//
// Author                Date          Comment
//----------------------------------------------------------------------------
// Jim Herd    14/02/09      
//----------------------------------------------------------------------------

#include    "global.h"

//----------------------------------------------------------------------------
// Global variables
//
uint16_t         right_speed, left_speed, current_right_speed, current_left_speed, current_speed;
uint8_t          left_PWM, right_PWM, new_left_PWM, new_right_PWM;
uint16_t         left_motor_state, right_motor_state;
vehicle_state_t  state_of_vehicle;
uint16_t         straight_line_speed, turn_speed;
uint8_t          pwm_differential;
uint8_t          init_mode;
error_codes_t    sys_error;
uint8_t          left_motor_tweak, right_motor_tweak;

seven_seg_display_t   display_buff;

char             tempstring[TEMP_STRING_SIZE];
//
// In RAM copy FLASH data
//
FLASH_data_t   FLASH_data_image;

//
// general data area for different types of command data
//
union {
    uint8_t   cmd_data[MAX_STRIP_CMDS * 2];
    uint8_t   strip_data[MAX_STRIP_CMDS][2];
} seq = { 
   STRIP_CMD_FORWARD,    30,
   STRIP_CMD_SPIN_RIGHT, 20,
   STRIP_CMD_FORWARD,    30,
   STRIP_CMD_SPIN_LEFT,  10,
   STRIP_CMD_FORWARD,    10,   
   STRIP_CMD_STOP    ,    0        // exit
};

//
// union to allow easy changes between different sized types
//
union {
    uint32_t    int32;
    uint16_t    int16[2];
    uint8_t     int8[4];
} bytes;

//----------------------------------------------------------------------------
// table of PWM settings for speed variation - % of full speed
//
const uint8_t motor_speeds[16] = {
    30,33,35,40,45,50,55,60,60,65,70,75,80,85,90,92 
};

//----------------------------------------------------------------------------
// table of delta settings for left/right motor adjustments - ((% of full speed - 7)
//
const uint8_t speed_delta[16] = {
    0,1,2,3,4,5,6,7,7,8,9,10,11,12,13,14 
};

//----------------------------------------------------------------------------
// table of bump reverse times - in units of 0.05 second
//
const uint8_t reverse_times[8] = {
    1,2,3,4,5,6,7,8 
};

//----------------------------------------------------------------------------
// table of bump spin times - in units of 0.05 second
//
const uint8_t spin_times[16] = {
    1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 
};

//----------------------------------------------------------------------------
// set of sound files
//
const sound_file_t   snd_start_up = {
    SOUND_DISABLE, 4,
    NOTE_C, 68, NOTE_D, 68, NOTE_E, 68, NOTE_F, 68
};

const sound_file_t   snd_beeps_1 = {
    SOUND_DISABLE, 24,
    NOTE_C, 25, SILENT_NOTE, 250, NOTE_C, 25, SILENT_NOTE, 250,
    NOTE_C, 25, SILENT_NOTE, 250, NOTE_C, 25, SILENT_NOTE, 250,
    NOTE_C, 25, SILENT_NOTE, 250, NOTE_C, 25, SILENT_NOTE, 250,
    NOTE_C, 25, SILENT_NOTE, 250, NOTE_C, 25, SILENT_NOTE, 250,
    NOTE_C, 25, SILENT_NOTE, 250, NOTE_C, 25, SILENT_NOTE, 250,
    NOTE_C, 25, SILENT_NOTE, 250, NOTE_C, 25, SILENT_NOTE, 250
};

const sound_file_t   snd_next_selection = {
    SOUND_DISABLE, 5,
    NOTE_F, 10, SILENT_NOTE, 5, NOTE_F, 10, SILENT_NOTE, 5, NOTE_F, 10
};

const sound_file_t   snd_exit_selection = {
    SOUND_DISABLE, 5,
    NOTE_C, 10, SILENT_NOTE, 5, NOTE_F, 10, SILENT_NOTE, 5, NOTE_B, 10
};

const sound_file_t   snd_goto_selection = {
    SOUND_DISABLE, 5,
    NOTE_B, 10, SILENT_NOTE, 5, NOTE_F, 10, SILENT_NOTE, 5, NOTE_C, 10
};

const sound_file_t   snd_read_pots = {
    SOUND_DISABLE, 5,
    NOTE_F, 20, SILENT_NOTE, 10, NOTE_F, 20, SILENT_NOTE, 10, NOTE_F, 20
};

const sound_file_t   snd_system_init = {
    SOUND_DISABLE, 7,
    NOTE_C, 20, NOTE_D, 20, NOTE_E, 20, NOTE_F, 20, NOTE_G, 20, NOTE_A, 20, NOTE_B, 20
};

const sound_file_t   snd_fault = {
    SOUND_DISABLE, 1,
    NOTE_C, 100
};

const sound_file_t   snd_battery_low = {
    SOUND_DISABLE, 13,
    NOTE_B, 20, SILENT_NOTE, 10, NOTE_A, 20, SILENT_NOTE, 10, NOTE_G, 20, SILENT_NOTE, 10,
    NOTE_F, 20, SILENT_NOTE, 10, NOTE_E, 20, SILENT_NOTE, 10, NOTE_D, 20, SILENT_NOTE, 10,
    NOTE_C, 20   
};

const sound_file_t   snd_battery_recharge = {
    SOUND_DISABLE, 5,
    NOTE_C, 100, SILENT_NOTE, 100, NOTE_C, 100, SILENT_NOTE, 100, NOTE_C, 100
};

const sound_file_t   snd_bump = {
    SOUND_DISABLE, 2,
    NOTE_G, 125,  NOTE_C, 125
};

//#pragma INTO_ROM
seven_seg_display_t  zero_display = { 
    SEVEN_SEG_AB, 1, 0, 0, 0,
    CHAR_0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,
    CHAR_0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,
};

//----------------------------------------------------------------------------
// test sequence  : move forward for 2 seconds.
//
uint16_t  program_a[50] = {

    INSTRUCTION(PUSH_L8,        IMMEDIATE,  40              ), 
    INSTRUCTION(PUSH_L8,        IMMEDIATE,  MOTOR_FORWARD   ),
    INSTRUCTION(PUSH_L8,        IMMEDIATE,  LEFT_MOTOR      ),
    INSTRUCTION(SET_PARAMETER,  NO_MOD,     SPEED           ),
    INSTRUCTION(PUSH_L8,        IMMEDIATE,  40              ), 
    INSTRUCTION(PUSH_L8,        IMMEDIATE,  MOTOR_FORWARD   ),
    INSTRUCTION(PUSH_L8,        IMMEDIATE,  RIGHT_MOTOR     ),
    INSTRUCTION(SET_PARAMETER,  NO_MOD,     SPEED           ),
    INSTRUCTION(EXECUTE,        NO_MOD,     START           ),
    INSTRUCTION(DELAY,          IMMEDIATE,  20              ),
    INSTRUCTION(EXECUTE,        NO_MOD,     STOP            ),
    INSTRUCTION(EXIT,           NO_MOD,     NO_DATA         ),
};

//
// decompressed robot command data structure
//
struct  {
    uint8_t     op_code;
    uint8_t     modifier;
    uint16_t    data;
} robot_command;
//
// RAM store for current sequence
//
union {
    uint16_t  uint16[RAM_SEQUENCE_SIZE];
    uint8_t   uint8[RAM_SEQUENCE_SIZE*2];
} RAM_sequence;









