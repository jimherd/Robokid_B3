#ifndef __global_H
#define __global_H

#pragma  MESSAGE DISABLE C2705
#pragma  MESSAGE DISABLE C1420
//
// set of system and application header files
//
#include <stdio.h>
#include <setjmp.h>

#include "derivative.h"
#include "hidef.h"
#include "pindef.h"
#include "PE_Types.h"
#include "sys_defines.h"
#include "user_defines.h"
#include "user_display.h"
#include "interrupt.h"
#include "user_code.h"
#include "delay.h"
#include "sci.h"
#include "init.h"
#include "adc.h"
#include "pwm.h"
#include "flashio.h"
#include "experiment.h"
#include "string.h"
#include "sound.h"
#include "activity.h"
#include "joystick.h"
#include "program.h"
#include "bump.h"
#include "follow.h"
#include "sketch.h"
#include "lab.h"
#include "distance.h"
#include "interpreter.h"
//
//
//
extern   FLASH_data_t   FLASH_data;
extern   FLASH_data_t   FLASH_data_image;
extern   uint16_t       FLASH_SEQ_0[256];
//
// extern definitions to global variables
//
extern  uint16_t         right_speed, left_speed, current_right_speed, current_left_speed, current_speed;
extern  uint8_t          left_PWM, right_PWM, new_left_PWM, new_right_PWM;
extern  uint16_t         left_motor_state, right_motor_state;
extern  vehicle_state_t  state_of_vehicle;
extern  uint16_t         straight_line_speed, turn_speed;
extern  uint8_t          pwm_differential;
extern  uint8_t          init_mode;
extern  error_codes_t    sys_error;
extern  uint8_t          left_motor_tweak, right_motor_tweak;
//
// time count variables
//
extern  uint16_t    tick_count_16;
extern  uint8_t     tick_count_8; 
extern  uint8_t     second_count;   
extern  uint8_t     tick_for_second_count;

extern  uint8_t     debounced_state;    // switch debounce variables
extern  uint8_t     switch_A, switch_B, switch_C, switch_D, switch_ABCD;

extern  uint16_t    left_wheel_count, right_wheel_count;
extern  uint8_t     LED_image, display_image, swap_image, LED_flash_map, display_flash_mode, flash_count;

extern  uint16_t    left_wheel_count, right_wheel_count;
extern  uint8_t     left_wheel_sensor_value, right_wheel_sensor_value;
extern  uint8_t     left_speed_index, right_speed_index;
extern  uint16_t    left_speed_array[64], right_speed_array[64];



extern  seven_seg_display_t    robot_display;
extern  const uint8_t          seven_segment_codes[];

extern  seven_seg_display_t  intro;

extern  uint8_t     display_no;

extern  sound_file_t  sound_file;
extern  uint8_t       note_pt, note_duration;

extern  const uint16_t tone_codes[12];

extern  const uint8_t motor_speeds[16];
extern  const uint8_t speed_delta[16];
extern  const uint8_t reverse_times[8];
extern  const uint8_t spin_times[16];

extern  seven_seg_display_t   display_buff;

extern  char    tempstring[TEMP_STRING_SIZE];

extern union {
    uint8_t   cmd_data[MAX_STRIP_CMDS * 2];
    uint8_t   strip_data[MAX_STRIP_CMDS][2];
} seq;


extern union {
    uint32_t    int32;
    uint16_t    int16[2];
    uint8_t     int8[4];
} bytes;


extern const sound_file_t   snd_start_up;
extern const sound_file_t   snd_beeps_1;
extern const sound_file_t   snd_next_selection;
extern const sound_file_t   snd_exit_selection;
extern const sound_file_t   snd_goto_selection;
extern const sound_file_t   snd_read_pots;
extern const sound_file_t   snd_system_init;
extern const sound_file_t   snd_battery_low;
extern const sound_file_t   snd_battery_recharge;
extern const sound_file_t   snd_bump;

extern  seven_seg_display_t  zero_display;

extern uint16_t  program_a[50];

extern struct  {
    uint8_t     op_code;
    uint8_t     modifier;
    uint16_t    data;
} robot_command;

extern  union {
    uint16_t  uint16[RAM_SEQUENCE_SIZE];
    uint8_t   uint8[RAM_SEQUENCE_SIZE*2];
} RAM_sequence;


extern union {
    uint16_t  uint16[256];
    uint8_t   uint8[512];
} FLASH_seq_0;

#endif /* __global_H */